//--------------------------------------------------------------------
// Microsoft ADO
//
// (c) 1996 Microsoft Corporation.  All Rights Reserved.
//
// @doc
//
// @module	adoisapi.cpp | ADO ISAPI sample application
//
// @devnote None
//--------------------------------------------------------------------


#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF", "EndOfFile")
#include <httpext.h>
#include <stdio.h>

VOID PatchQuery(char *szQuery, char **ppszPatchedQuery);
HRESULT	FetchData(EXTENSION_CONTROL_BLOCK *pECB);
VOID OutputErrors(EXTENSION_CONTROL_BLOCK *pECB, HRESULT hrError);
VOID OutputString(EXTENSION_CONTROL_BLOCK *pECB, LPCSTR szBuffer);

const PCSTR g_pszConnection = "dsn=OLE_DB_NWind_Jet;uid=Admin;pwd=;";

BOOL WINAPI	GetExtensionVersion(HSE_VERSION_INFO *pVer)
{
	pVer->dwExtensionVersion = MAKELONG( HSE_VERSION_MINOR, HSE_VERSION_MAJOR );

	lstrcpynA( pVer->lpszExtensionDesc, "Sample ADO ISAPI Application", HSE_MAX_EXT_DLL_NAME_LEN );

	return TRUE;
}			   

DWORD WINAPI HttpExtensionProc(EXTENSION_CONTROL_BLOCK *pECB )
{
	DWORD	dwWritten;
	char	szContent[] = "Content-type: text/html\r\n\r\n";
	
	dwWritten = sizeof(szContent);
    pECB->ServerSupportFunction (pECB->ConnID,
                                 HSE_REQ_SEND_RESPONSE_HEADER,
                                 NULL,
                                 &dwWritten,
                                 (LPDWORD)szContent);

	if (FAILED(FetchData(pECB)))
		return HSE_STATUS_ERROR;
	else
		return HSE_STATUS_SUCCESS;
}

char ConvertHexToDec(char cHex)
{
	if ((toupper(cHex) >= 'A') && (toupper(cHex) <= 'F'))
		return cHex - 'A' + 10;
	else
		return cHex - '0';
}

// Hack to clean up the query string. This code will work
// for most, but not all cases. For instance when the query 
// string has embedded '+', this code will not work.
VOID PatchQuery(char *szQuery, char **ppszPatchedQuery)
{
	char *p = szQuery + 1;
	
	while (*p++)
	{
		if (*p == '+') //replace '+' by ' '
			*p = ' ';

		if (*p == '%') //a number begins
		{
			char ch;

			if (*++p)
			{
				ch = ConvertHexToDec(*p) << 4; //convert the first digit

				if (*++p)
				{
					ch |= ConvertHexToDec(*p);  //convert the 2nd digit
					
					if (!*(p + 1))
					{
						*(p-2) = ch;
						*(p-1) = '\0';
						break;
					}
					else
					{
						*(p-2) = ' ';
						*(p-1) = ' ';
						*p = ch;
					}
				}
			}
		}
	}

	*ppszPatchedQuery = szQuery + 1;
  	return;
}

VOID OutputString(EXTENSION_CONTROL_BLOCK *pECB, LPCSTR szBuffer)
{
	DWORD dwBuffer = strlen(szBuffer);
	pECB->WriteClient(pECB->ConnID, (PVOID) szBuffer, &dwBuffer, 0);
}

VOID OutputErrors(EXTENSION_CONTROL_BLOCK *pECB, _com_error &e)
{
	char		szBuffer[512];
	
	// output hresult
	OutputString(pECB, "<P><H1>Error Fetching Data</H1>");

	sprintf(szBuffer, "<p>Code = %08lx", e.Error());
	OutputString(pECB, szBuffer);

    sprintf(szBuffer, "<p>Code meaning = %s", e.ErrorMessage());
    OutputString(pECB, szBuffer);

	_bstr_t bstrSource(e.Source());
    sprintf(szBuffer, "<p>Source = %s", (LPCSTR) bstrSource);
	OutputString(pECB, szBuffer);
    
	_bstr_t bstrDescription(e.Description());
    sprintf(szBuffer, "<p>Description = %s", (LPCSTR) bstrDescription);
	OutputString(pECB, szBuffer);
    
	return;
}

HRESULT	FetchData(EXTENSION_CONTROL_BLOCK *pECB)
{
	HRESULT			hr = NOERROR;
	bool			fComInitialized = false;
	_RecordsetPtr	pRs = NULL;
	FieldPtr		*rgflds = NULL;
	long			lNumFields, lFld;
	char			*pszPatchedQuery;
	_variant_t		vValue;
	
	OutputString(pECB, "<HEAD><TITLE>Query Results"
						"</TITLE></HEAD>\r\n<BODY>\r\n");
		
	PatchQuery(pECB->lpszQueryString, &pszPatchedQuery);

	OutputString(pECB, "<P><H1>Query String</H1>");
	OutputString(pECB, pszPatchedQuery);		
	
	try
	{
		if (FAILED(hr = ::CoInitialize(NULL)))
			_com_issue_error(hr);
		
		fComInitialized = true;

		// Open the recordset
		pRs.CreateInstance("ADODB.Recordset.1.5");
		pRs->Open(pszPatchedQuery, g_pszConnection, adOpenForwardOnly, adLockReadOnly, adCmdUnknown);
			
		lNumFields = pRs->Fields->Count;

		rgflds = new FieldPtr[lNumFields];
		if (!rgflds)
			_com_issue_error(E_OUTOFMEMORY);
		memset(rgflds, 0, lNumFields * sizeof(FieldPtr));

		for (lFld = 0; lFld < lNumFields; lFld++)
			rgflds[lFld] = pRs->Fields->GetItem(lFld);
		
		OutputString(pECB, "<P><H1>Query Results</H1>");
		OutputString(pECB, "<P><TABLE BORDER=1 CELLSPACING=4>");

		//
		// print column names
		//
		OutputString(pECB, "<TR>");

		for (lFld = 0; lFld < lNumFields; lFld++)
		{
			OutputString(pECB, "<TH>");
			OutputString(pECB, (PCSTR)(_bstr_t)rgflds[lFld]->Name);
		}
		
		//
		// print data
		// 
		while (VARIANT_FALSE == pRs->EndOfFile)
		{
 			OutputString(pECB, "<TR>");

			for (lFld = 0; lFld < lNumFields; lFld++)
			{
 				OutputString(pECB, "<TD>");

				vValue = rgflds[lFld]->Value;
				if (VT_NULL == vValue.vt)
					OutputString(pECB, "(Null)");
				else
					OutputString(pECB, (PCSTR)(_bstr_t)vValue);
			}

 			OutputString(pECB, "</TR>");

			pRs->MoveNext();
		}

		OutputString(pECB, "</TABLE>");
		OutputString(pECB, "</BODY>\r\n");
	}
	catch (_com_error &e)
	{
		OutputErrors(pECB, e);
		hr = e.Error();
	}

	if (rgflds)
			delete[] rgflds;
	
	pRs = NULL;

	if (fComInitialized)
		::CoUninitialize();
	
	OutputString(pECB, "</BODY>\r\n");

	return hr;
}
