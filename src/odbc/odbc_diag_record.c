/*
 * Copyright (C) 2008 Search Solution Corporation. All rights reserved by Search Solution. 
 *
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met: 
 *
 * - Redistributions of source code must retain the above copyright notice, 
 *   this list of conditions and the following disclaimer. 
 *
 * - Redistributions in binary form must reproduce the above copyright notice, 
 *   this list of conditions and the following disclaimer in the documentation 
 *   and/or other materials provided with the distribution. 
 *
 * - Neither the name of the <ORGANIZATION> nor the names of its contributors 
 *   may be used to endorse or promote products derived from this software without 
 *   specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE. 
 *
 */  
  
#include		"odbc_portable.h"
#include		"odbc_util.h"
#include		"sqlext.h"
#include		"odbc_diag_record.h"
#include		"odbc_env.h"
#include		"odbc_connection.h"
#include		"odbc_statement.h"
  
#define		ISO_CLASS_ORIGIN			"ISO 9075"
#define		ODBC_CLASS_ORIGIN		"ODBC 3.0"
#define		DIAG_PREFIX				"[CUBRID][ODBC CUBRID Driver]"










{
  
  {
  "01000", "General warning"}, 
  {
  "01001", "Cursor operation conflict"}, 
  {
  "01002", "Disconnect error"}, 
  {
  "01003", "NULL value eliminated in set function"}, 
  {
  "01004", "String data, right truncated"}, 
  {
  "01006", "Privilege not revoked"}, 
  {
  "01007", "Privilege not granted"}, 
  {
  "01S00", "Invalid connection string attribute"}, 
  {
  "01S01", "Error in row"}, 
  {
  "01S02", "Option value changed"}, 
  {
  "01S06", "Attempt to fetch before the result set retunred the first rowset"}, 
  {
  "01S07", "Fractional truncation"}, 
  {
  "01S08", "Error saving File DSN"}, 
  {
  "01S09", "Invalid keyword"}, 
  {
  "07001", "Wrong number of parameters"}, 
  {
  "07002", "COUNT field incorrect"}, 
  {
  "07005", "Prepared statement not a cursor-specification"}, 
  {
  "07006", "Restricted data type attribute violation"}, 
  {
  "07009", "Invalid descriptor index"}, 
  {
  "07S01", "Invalid use of default parameter"}, 
  {
  "08001", "Client unable to establish connection"}, 
  {
  "08002", "Connection name in use"}, 
  {
  "08003", "Connection does not exist"}, 
  {
  "08004", "Server rejected the connection"}, 
  {
  "08007", "Connection failure during transaction"}, 
  {
  "08S01", "Communication link failure"}, 
  {
  "21S01", "Insert value list does not match column list"}, 
  {
  "21S02", "Degree of derived table does not match column list"}, 
  {
  "22001", "String data, right truncated"}, 
  {
  "22002", "Indicator variable required but not supplied"}, 
  {
  "22003", "Numeric value out of range"}, 
  {
  "22007", "Invalid datetime format"}, 
  {
  "22008", "Datetime field overflow"}, 
  {
  "22012", "Division by zero"}, 
  {
  "22015", "Invalid field overflow"}, 
  {
  "22018", "Invalid charcter value for cast specification"}, 
  {
  "22019", "Invalid escape character"}, 
  {
  "22025", "Invalid escape sequence"}, 
  {
  "22026", "String data, length mismatch"}, 
  {
  "23000", "Integrity constraint violation"}, 
  {
  "24000", "Invalid cursor state"}, 
  {
  "25000", "Invalid transaction state"}, 
  {
  "25S01", "Transaction state"}, 
  {
  "25S02", "Transaction is still active"}, 
  {
  "25S03", "Transaction is rolled back"}, 
  {
  "28000", "Invalid authorization specification"}, 
  {
  "34000", "Invalid cursor name"}, 
  {
  "3C000", "Duplicate cursor name"}, 
  {
  "3D000", "Invalid catalog name"}, 
  {
  "3F000", "Invalid schema name"}, 
  {
  "40001", "Serialization failure"}, 
  {
  "40002", "Integrity constraint violation"}, 
  {
  "40003", "Statement completion unknown"}, 
  {
  "42000", "Syntax error or access violation"}, 
  {
  "42S01", "Base table or view already exists"}, 
  {
  "42S02", "Base table or view not found"}, 
  {
  "42S11", "Index already exists"}, 
  {
  "42S12", "Index not found"}, 
  {
  "42S21", "Column already exists"}, 
  {
  "42S22", "Column not found"}, 
  {
  "44000", "WITH CHECK OPTION violation"}, 
  {
  "HY000", "General error"}, 
  {
  "HY001", "Memory allocation error"}, 
  {
  "HY003", "Invalid application buffer type"}, 
  {
  "HY004", "Invalid SQL data type"}, 
  {
  "HY007", "Associated statement is not prepared"}, 
  {
  "HY008", "Operation canceled"}, 
  {
  "HY009", "Invalid use of null pointer"}, 
  {
  "HY010", "Function sequence error"}, 
  {
  "HY011", "Attribute cannot be set now"}, 
  {
  "HY012", "Invalid transaction operation code"}, 
  {
  "HY013", "Memory management error"}, 
  {
  "HY014", "Limit on the number of handles exceeded"}, 
  {
  "HY015", "No cursor name available"}, 
  {
  "HY016", "Cannot modify an implementation row descriptor"}, 
  {
  "HY017", "Invalid use of an automatically allocated descriptor handle"}, 
  {
  "HY018", "Server declined cancel request"}, 
  {
  "HY019", "Non-character and non-binary data sent in pieces"}, 
  {
  "HY020", "Attempt to concatenate a null value"}, 
  {
  "HY021", "Inconsistent descriptor information"}, 
  {
  "HY024", "Invalid attribute value"}, 
  {
  "HY090", "Invalid string or buffer length"}, 
  {
  "HY091", "Invalid descriptor field identifier"}, 
  {
  "HY092", "Invalid attribute/option identifier"}, 
  {
  "HY095", "Function type out of range"}, 
  {
  "HY096", "Invalid information type"}, 
  {
  "HY097", "Column type out of range"}, 
  {
  "HY098", "Scope type out of range"}, 
  {
  "HY099", "Nullable type out of range"}, 
  {
  "HY100", "Uniqueness option type out of range"}, 
  {
  "HY101", "Accuracy option type out of range"}, 
  {
  "HY103", "Invalid retrieval code"}, 
  {
  "HY104", "Invalid precision or scale value"}, 
  {
  "HY105", "Invalid parameter type"}, 
  {
  "HY106", "Fetch type out of range"}, 
  {
  "HY107", "Row value out of range"}, 
  {
  "HY109", "Invalid cursor position"}, 
  {
  "HY110", "Invalid driver completion"}, 
  {
  "HY111", "Invalid bookmark value"}, 
  {
  "HYC00", "Optional feature not implemented"}, 
  {
  "HYT00", "Timeout expired"}, 
  {
  "HYT01", "Connection timeout expired"}, 
  {
  "IM001", "Driver does not support this function"}, 
  {
  "IM002", "Data source name not found and no default driver specified"}, 
  {
  "IM003", "Specified driver could not be loaded"}, 
  {
  "IM004", "Driver's SQLAllocHandle on SQL_HANDLE_ENV failed"}, 
  {
  "IM005", "Driver's SQLAllocHandle on SQL_HANDLE_DBC failed"}, 
  {
  "IM006", "Driver's SQLSetConnectAttr failed"}, 
  {
  "IM007", "No data source or driver specified; dalo prohibited"}, 
  {
  "IM008", "Dialog failed"}, 
  {
  "IM009", "Unable to load translation DLL"}, 
  {
  "IM010", "Data source name too long"}, 
  {
  "IM011", "Driver name too long"}, 
  {
  "IM012", "DRIVER keyword syntax error"}, 
  {
  "IM013", "Trace file error"}, 
  {
  "IM014", "Invalid name of File DSN"}, 
  {
  "IM015", "Corrupt file data source"}, 
  {
NULL, NULL} 


/************************************************************************
 * name: odbc_alloc_diag
 * arguments:
 * returns/side-effects:
 * description:
 * NOTE:
 ************************************************************************/ 
  PUBLIC ODBC_DIAG * 
{
  
  
  
  



/************************************************************************
 * name: odbc_free_diag
 * arguments:
 *    option -
 *		INIT - �ʱ�ȭ
 *		RESET - member reset
 *		FREE_MEBER - member�� free
 *		FREE_ALL - member �� node free
 * returns/side-effects:
 * description:
 * NOTE:
 ************************************************************************/ 
PUBLIC void 
odbc_free_diag (ODBC_DIAG * diag, int option) 
{
  
    
  
    
    {
    
      
      
    
      
      
      
    
      
      
    
      
      
      
    



/************************************************************************
 * name: odbc_alloc_diag_record
 * arguments:
 * returns/side-effects:
 * description:
 * NOTE:
 ************************************************************************/ 
  PUBLIC ODBC_DIAG_RECORD * 
{
  
  
  
  



/************************************************************************
 * name: odbc_free_diag_record
 * arguments:
 * returns/side-effects:
 * description:
 * NOTE:
 ************************************************************************/ 
PUBLIC void 
odbc_free_diag_record (ODBC_DIAG_RECORD * diag_record, int option) 
{
  
    
  
    
    {
    
      
      
    
      
      
      
    
      
      
    
      
      
      
    


odbc_free_diag_record_list (ODBC_DIAG_RECORD * diag_record) 
{
  
  
  
    
    {
      
      
      
    


odbc_move_diag (ODBC_DIAG * target_diag, ODBC_DIAG * src_diag) 
{
  
  
    
  
  
    
  
  else
    
    {
      
	
    
  
  
  
  
  



/* recored added to head */ 
PUBLIC void 
odbc_set_diag (ODBC_DIAG * diag, char *sql_state, int native_code, 
{
  
  
  
    
  
  
    
  
+(diag->rec_number);
  
  
  
  
    {
      
    
  else
    {
      
	{
	  
	    {
	      
	    
	
      
    
  
  


odbc_set_diag_by_cci (ODBC_DIAG * diag, int cci_retval, T_CCI_ERROR * error) 
{
  
  
  
    
  
  
    
  
+(diag->rec_number);
  
  
  
    {
      
	{
	  
	  
	
      else
	{
	  
	  
	
    
  else
    {
      
	{
	  
	
      
      
    
  
  



/************************************************************************
* name: odbc_get_diag_field
* arguments:
* returns/side-effects:
* description:
* NOTE:
*	record field�� SQL_DIAG_COLUMN_NUMBER�� SQL_DIAG_ROW_NUMBER��
*	�� data cell�� ���� fetch�� �Ͼ�� error�� ���� �����̴�.
*	���� �������� �ʴ´�.
************************************************************************/ 
  PUBLIC RETCODE 
					
					
{
  
  
  
  
  
  
  
	 || 
	&& 
    
    {
      
    
  
    
    {
      
	
	{
	
	
	  
	    
	  
	    
	    {
	      
	    
	  
	
	
	  
	    /* Yet not implemented */ 
	    return ODBC_ERROR;
	
	  
	    
	  
	    
	    {
	      
	    
	  
	
	  
	    
	  
	    
	    {
	      
	    
	  
	
	  
	
    
  
  else
    
    {
      
	/* record field */ 
	if (rec_number <= 0 || rec_number > env->diag->rec_number)
	
	{
	  
	
      
      
	
	{
	  
	
      
	
	{
	
	  
	  
	  
	    
	    {
	      
	    
	  
	
	  
	    
	  
	    
	    {
	      
	    
	  
	
	  
	
	  
	  {
	    
	    
	    
	    
	      
	    
	    
	    
	    
	    
	      
	      {
		
	      
	    
	  
	  
	
	  
	    
	  
	    
	    {
	      
	    
	  
	
	  
	    
	  
	    
	    {
	      
	    
	  
	
	  
	    
	    {
	      
	    
	  
	  else
	    
	    {
	      
		
		{
		  
		
	      
	      else if (handle_type == SQL_HANDLE_STMT)
		
		{
		  
		
	      
	      else if (handle_type == SQL_HANDLE_DESC)
		
		{
		  
		
	      
	      
		
		{
		  
		
	    
	  
	
	  
	    
	    {
	      
	    
	  
	  else
	    
	    {
	      
	    
	  
	  
	    
	    {
	      
	    
	  
	
	  
	  
	    
	    {
	      
	    
	  
	  
	    
	    {
	      
	    
	  
	
	  
	
    
  



/************************************************************************
* name: odbc_get_diag_rec
* arguments:
* returns/side-effects:
* description:
* NOTE:
************************************************************************/ 
  PUBLIC RETCODE 
				      
				      
{
  
  
  
  
  
  
  
  
  
    
  
    /* Sequence error record is not implemented */ 
    if (rec_number > env->diag->rec_number)
    
  
    
    {
      
    
  
    
    {
      
    
  
    
    {
      
    
  
  
    
  
  
  
  
  
    
    {
      
    
  
  


get_diag_message (ODBC_DIAG_RECORD * record) 
{
  
    
    {
      
    
  
  else
    
    {
      
    


get_diag_subclass_origin (char *sql_state) 
{
  
    
    {
      
    
  
	|| 
	|| 
	|| 
	|| 
	|| 
	|| 
	|| 
	|| 
	|| 
	|| 
	|| 
	|| 
	|| 
    
    {
      
    
  



{
  
  
  
    
      
  
    else
      
  


odbc_init_diag (ODBC_DIAG * diag) 
{
  
    
  


odbc_clear_diag (ODBC_DIAG * diag) 
{
  
    
  


odbc_init_diag_record (ODBC_DIAG_RECORD * node) 
{
  
    
    {
      
    


odbc_clear_diag_record (ODBC_DIAG_RECORD * node) 
{
  
    
  
  


is_header_field (short field_id) 
{
  
    
    {
    
    
    
    
    
    
      
    
      
    


get_diag_class_origin (char *sql_state) 
{
  
    
  
  else
    


