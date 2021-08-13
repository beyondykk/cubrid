/*
 *
 * Copyright 2016 CUBRID Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#include "method_scan.hpp"

#include "dbtype.h" /* db_value_* */
#include "list_file.h" /* qfile_ */
#include "object_representation.h" /* OR_ */

int method_Num_method_jsp_calls = 0;

namespace cubscan
{
  namespace method
  {
    scanner::scanner ()
      : m_thread_p (nullptr)
      , m_method_group (nullptr)
      , m_list_id (nullptr)
      , m_dbval_list (nullptr)
    {

    }

    int
    scanner::init (cubthread::entry *thread_p, METHOD_SIG_LIST *sig_list, qfile_list_id *list_id)
    {
      // check initialized
      if (m_thread_p != thread_p)
	{
	  m_thread_p = thread_p;
	}

      if (m_method_group == nullptr) // signature is not initialized
	{
	  m_method_group = new cubmethod::method_invoke_group (sig_list);
	}

      if (m_list_id == nullptr)
	{
	  m_list_id = list_id;
	  int arg_count = m_list_id->type_list.type_cnt;
	  m_arg_vector.resize (arg_count);
	  m_arg_dom_vector.resize (arg_count);

	  for (int i = 0; i < arg_count; i++)
	    {
	      TP_DOMAIN *domain = list_id->type_list.domp[i];
	      if (domain == NULL || domain->type == NULL)
		{
		  return ER_FAILED;
		}
	      m_arg_dom_vector[i] = domain;
	    }
	}

      if (m_dbval_list == nullptr)
	{
	  m_dbval_list = (qproc_db_value_list *) db_private_alloc (m_thread_p,
			 sizeof (m_dbval_list[0]) * m_method_group->get_num_methods ());
	  if (m_dbval_list == NULL)
	    {
	      return ER_FAILED;
	    }
	}
      return NO_ERROR;
    }

    void
    scanner::clear (bool is_final)
    {
      close_value_array ();
      for (DB_VALUE &value : m_arg_vector)
	{
	  db_value_clear (&value);
	}

      if (is_final)
	{
	  m_method_group->end ();
	  if (m_method_group != nullptr)
	    {
	      delete m_method_group;
	      m_method_group = nullptr;
	    }
	}
    }

    int
    scanner::open ()
    {
      int error = NO_ERROR;
      error = qfile_open_list_scan (m_list_id, &m_scan_id);

      // connect
      m_method_group->begin (m_thread_p);

      return error;
    }

    int
    scanner::close ()
    {
      int error = NO_ERROR;

      clear (false);
      qfile_close_scan (m_thread_p, &m_scan_id);

      return error;
    }

    SCAN_CODE
    scanner::next_scan (val_list_node &vl)
    {
      SCAN_CODE scan_code = S_SUCCESS;

      next_value_array (vl);

      scan_code = get_single_tuple ();
      if (scan_code == S_SUCCESS && m_method_group->prepare (m_arg_vector) != NO_ERROR)
	{
	  scan_code = S_ERROR;
	}

      if (scan_code == S_SUCCESS && m_method_group->execute (m_arg_vector) != NO_ERROR)
	{
	  scan_code = S_ERROR;
	}

      if (scan_code == S_SUCCESS)
	{
	  int num_methods = m_method_group->get_num_methods ();
	  for (int i = 0; i < num_methods; i++)
	    {
	      DB_VALUE *dbval_p = (DB_VALUE *) db_private_alloc (m_thread_p, sizeof (DB_VALUE));
	      db_make_null (dbval_p);

	      DB_VALUE &result = m_method_group->get_return_value (i);
	      db_value_clone (&result, dbval_p);

	      m_dbval_list[i].val = dbval_p;
	      db_value_clear (&result);
	    }

	  m_method_group->reset ();
	}

      // clear
      for (DB_VALUE &value : m_arg_vector)
	{
	  db_value_clear (&value);
	}

      return scan_code;
    }

    int
    scanner::close_value_array ()
    {
      db_private_free_and_init (m_thread_p, m_dbval_list);
      return NO_ERROR;
    }

    void
    scanner::next_value_array (val_list_node &vl)
    {
      qproc_db_value_list *dbval_list = m_dbval_list;

      vl.val_cnt = m_method_group->get_num_methods ();
      for (int n = 0; n < vl.val_cnt; n++)
	{
	  dbval_list->val = nullptr;
	  dbval_list->next = dbval_list + 1;
	  dbval_list++;
	}

      m_dbval_list[vl.val_cnt - 1].next = NULL;
      vl.valp = m_dbval_list;
    }

    SCAN_CODE
    scanner::get_single_tuple ()
    {
      QFILE_TUPLE_RECORD tuple_record = { NULL, 0 };
      SCAN_CODE scan_code = qfile_scan_list_next (m_thread_p, &m_scan_id, &tuple_record, PEEK);
      if (scan_code == S_SUCCESS)
	{
	  char *ptr;
	  int length;
	  OR_BUF buf;
	  for (int i = 0; i < m_list_id->type_list.type_cnt; i++)
	    {
	      QFILE_TUPLE_VALUE_FLAG flag = (QFILE_TUPLE_VALUE_FLAG) qfile_locate_tuple_value (tuple_record.tpl, i, &ptr, &length);
	      OR_BUF_INIT (buf, ptr, length);

	      DB_VALUE *value = &m_arg_vector [i];
	      TP_DOMAIN *domain = m_arg_dom_vector [i];
	      PR_TYPE *pr_type = domain->type;

	      db_make_null (value);
	      if (flag == V_BOUND)
		{
		  if (pr_type->data_readval (&buf, value, domain, -1, true, NULL, 0) != NO_ERROR)
		    {
		      scan_code = S_ERROR;
		      break;
		    }
		}
	      else
		{
		  /* If value is NULL, properly initialize the result */
		  db_value_domain_init (value, pr_type->id, DB_DEFAULT_PRECISION, DB_DEFAULT_SCALE);
		}
	    }
	}
      return scan_code;
    }
  }
}