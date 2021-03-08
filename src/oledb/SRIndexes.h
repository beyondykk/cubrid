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
  
#pragma once
  
{

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  {
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

									     m_szTableCatalog) 
    PROVIDER_COLUMN_ENTRY_WSTR ("TABLE_SCHEMA", 2, m_szTableSchema) 
												    m_szTableName) 
    PROVIDER_COLUMN_ENTRY_WSTR ("INDEX_CATALOG", 4, m_szIndexCatalog) 
												      m_szIndexSchema)
    
												     DBTYPE_BOOL,
												     0xFF, 0xFF,
												     m_bPrimaryKey) 
    PROVIDER_COLUMN_ENTRY_TYPE_PS ("UNIQUE", 8, DBTYPE_BOOL, 0xFF, 0xFF,
				     m_bUnique) 
										   0xFF,
										   m_bClustered) 
    PROVIDER_COLUMN_ENTRY_TYPE_PS ("TYPE", 10, DBTYPE_UI2, 5, ~0,
				     m_uType) 
										 m_FillFactor) 
    PROVIDER_COLUMN_ENTRY_TYPE_PS ("INITIAL_SIZE", 12, DBTYPE_I4, 10, ~0,
				     m_InitialSize) 
										       m_Nulls) 
    PROVIDER_COLUMN_ENTRY_TYPE_PS ("SORT_BOOKMARKS", 14, DBTYPE_BOOL, 0xFF, 0xFF,
				     m_bSortBookmarks) 
											  DBTYPE_BOOL, 0xFF, 0xFF,
											  m_bAutoUpdate) 
    PROVIDER_COLUMN_ENTRY_TYPE_PS ("NULL_COLLATION", 16, DBTYPE_I4, 10, ~0,
				     m_NullCollation) 
											 DBTYPE_UI4, 10, ~0,
											 m_uOrdinalPosition) 
    PROVIDER_COLUMN_ENTRY_WSTR ("COLUMN_NAME", 18, m_szColumnName) 
												      DBTYPE_GUID,
												      0xFF, 0xFF,
												      m_ColumnGUID) 
    PROVIDER_COLUMN_ENTRY_TYPE_PS ("COLUMN_PROPID", 20, DBTYPE_UI4, 10, ~0,
				     m_uColumnPropID) 
											 ~0,
											 m_Collation) 
    PROVIDER_COLUMN_ENTRY_TYPE_PS ("CARDINALITY", 22, DBTYPE_UI8, 20, ~0,
				     m_ulCardinality) 
											 m_Pages) 
    PROVIDER_COLUMN_ENTRY_WSTR ("FILTER_CONDITION", 24,
				  m_szFilterCondition) 
											  0xFF, 0xFF,
											  m_bIntegrated) 
    END_PROVIDER_COLUMN_MAP () 

{

  
							const char *table_name, const char *index_name);
  
  
