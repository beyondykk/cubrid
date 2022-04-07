/*
 *
 * Copyright (c) 2016 CUBRID Corporation.
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

package com.cubrid.jsp.data;

import com.cubrid.jsp.exception.TypeMismatchException;
import com.cubrid.jsp.value.NullValue;
import com.cubrid.jsp.value.Value;
import java.util.ArrayList;
import java.util.List;

public class GetByOIDInfo {

    public String className = null;
    public List<String> attrNames = null;
    public List<ColumnInfo> columnInfos = null;
    public List<Value> dbValues = null;

    public GetByOIDInfo(CUBRIDUnpacker unpacker) {

        className = unpacker.unpackCString();

        attrNames = new ArrayList<String>();
        columnInfos = new ArrayList<ColumnInfo>();
        dbValues = new ArrayList<Value>();

        int numAttrNames = unpacker.unpackInt();
        for (int i = 0; i < numAttrNames; i++) {
            String name = unpacker.unpackCString();
            attrNames.add(name);
        }

        int numValues = unpacker.unpackInt();
        for (int i = 0; i < numValues; i++) {
            int paramType = unpacker.unpackInt();
            Value v = null;
            try {
                v = unpacker.unpackValue(paramType);
            } catch (TypeMismatchException e) {
                v = new NullValue();
            }
            dbValues.add(v);
        }

        int numColumnInfos = unpacker.unpackInt();
        for (int i = 0; i < numColumnInfos; i++) {
            ColumnInfo cInfo = new ColumnInfo(unpacker);
            columnInfos.add(cInfo);
        }
    }
}
