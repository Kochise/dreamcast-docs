/*
** CONVDSN.C - This is the ODBC sample code for
** creating File DSN pointers to machine DSNs.
**
**	This code is furnished on an as-is basis as part of the ODBC SDK and is
**	intended for example purposes only.
**
*/

#include <windows.h>
#include <stdio.h>
#include "sql.h"
#include "sqlext.h"
#include "odbcinst.h"

// prototypes

void ExpandFileName(LPSTR szFileDSNName, LPCSTR szDSNName);
void MakeLegalName(LPSTR szLegalDSNName, LPCSTR szDSNName);

// main routine:  Iterate through the user and system DSNs, creating a pointer
//                to each.

int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
   LPSTR lpszCmdLine, int nCmdShow)
{
	HENV    henv;
	RETCODE retcode;
	CHAR    szDSNName[SQL_MAX_DSN_LENGTH + 1];
	CHAR    szLegalDSNName[SQL_MAX_DSN_LENGTH + 1];
	CHAR    szFileDSNName[MAX_PATH + 1];

	if(SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_ENV, NULL, &henv)))
	{
		// set the ODBC behavior version.
		(void) SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION,
					(SQLPOINTER) SQL_OV_ODBC3, SQL_IS_INTEGER);

		// Enumerate the user data sources.
		retcode = SQLDataSources(henv, SQL_FETCH_FIRST_SYSTEM, szDSNName,
			sizeof(szDSNName), NULL, NULL, 0, NULL);

		while(SQL_SUCCEEDED(retcode))
		{
			// Make a version of the name acceptable for use as a filename.
			MakeLegalName(szLegalDSNName, szDSNName);
			
			// Build the full filename.
			ExpandFileName(szFileDSNName, szLegalDSNName);

			// Write the DSN= keyword into the File DSN.
			SQLWriteFileDSN(szFileDSNName, "ODBC", "DSN", szDSNName);

			// Do the next one, if it exists.
			retcode = SQLDataSources(henv, SQL_FETCH_NEXT, szDSNName,
				sizeof(szDSNName), NULL, NULL, 0, NULL);		
		}

		// Enumerate the system data sources.
		retcode = SQLDataSources(henv, SQL_FETCH_FIRST_USER, szDSNName,
			sizeof(szDSNName), NULL, NULL, 0, NULL);

		while(SQL_SUCCEEDED(retcode))
		{
			// Make a version of the name acceptable for use as a filename.
			MakeLegalName(szLegalDSNName, szDSNName);

			// Build the full filename.
			ExpandFileName(szFileDSNName, szLegalDSNName);

			// Write the DSN= keyword into the File DSN.
			SQLWriteFileDSN(szFileDSNName, "ODBC", "DSN", szDSNName);
			
			// Do the next one, if it exists.
			retcode = SQLDataSources(henv, SQL_FETCH_NEXT, szDSNName,
				sizeof(szDSNName), NULL, NULL, 0, NULL);		
		}

		SQLFreeHandle(SQL_HANDLE_ENV, henv);
	}

	return 0;
}

// ExpandFileName:  Take the pieces of the filename, and form a complete
//                  filename.

void ExpandFileName(LPSTR szFileDSNName, LPCSTR szDSNName)
{
	strcpy(szFileDSNName, szDSNName);

	// Hint that we're not sharable
	strcat(szFileDSNName, " (not sharable)");
}

// MakeLegalName:  Make a version of the DSN name suitable for use as a 
//                 filename.

void MakeLegalName(LPSTR szLegalDSNName, LPCSTR szDSNName)
{
	CHAR   szIllegalChars[] = "\\/:*?\"<>|";
	LPSTR  pchIllegalChar;
	LPCSTR pchDSNSource     = szDSNName;
	LPSTR  pchDSNTarget     = szLegalDSNName;
	BOOL   fIllegal;

	while(*pchDSNSource)
	{
		pchIllegalChar = szIllegalChars;
		
		fIllegal = FALSE;
		
		// if the character is double byte, copy it and move ahead
		if(IsDBCSLeadByte(*pchDSNSource))
		{
			*(pchDSNTarget++) = *(pchDSNSource++);
			*(pchDSNTarget++) = *(pchDSNSource++);
		}
		else
		{
			// single byte
			if(!isalpha(*pchDSNSource) && !isdigit(*pchDSNSource))
			{
				while(*pchIllegalChar)
				{
					if(*pchDSNSource == *(pchIllegalChar++))
					{
						fIllegal = TRUE;
						break;
					}
				}
			}

			if(fIllegal)
			{
				pchDSNSource++;
			}
			else
			{
				*(pchDSNTarget++) = *(pchDSNSource++);
			}
		}
	}
	*pchDSNTarget = '\0';
}

