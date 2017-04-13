#pragma message("Test of Msi External Database Access - Resequences InstallSequence table.  Copyright (c) 1997 Microsoft Corp.")
#if 0  // makefile definitions, to build: %vcbin%\nmake -fApiTstDb.cpp
DESCRIPTION = Test of Msi external database access
MODULENAME = ApiTstDb
SUBSYSTEM = console
FILEVERSION = 0.20
!include <MsiTool.Mak>
!if 0  #nmake skips the rest of this file
#endif // end of makefile definitions

// test of external database access
#define WINDOWS_LEAN_AND_MEAN  // faster compile
#include <windows.h>
#ifndef RC_INVOKED    // start of source code
#include <stdio.h>   // printf/wprintf
#include <tchar.h>   // define UNICODE=1 on nmake command line to build UNICODE
#include "MsiQuery.h"

// routine to check return status for ERROR_SUCCESS, and throw exception if not
TCHAR*  g_szErrorContext = 0;
void CheckMsi(UINT iStat, TCHAR* szContext)
{
	if (iStat != ERROR_SUCCESS)
	{
		g_szErrorContext = szContext;
		throw iStat;
	}
}

void SmoothSequence(MSIHANDLE hDatabase, int iSpacing)
{
	PMSIHANDLE hView;
	CheckMsi(MsiDatabaseOpenView(hDatabase, TEXT("SELECT Action, Sequence FROM InstallSequence ORDER BY Sequence"),&hView),TEXT("OpenView"));
	CheckMsi(MsiViewExecute(hView, 0), TEXT("Execute View"));
	int iLast = 0;
	for (;;)
	{
		PMSIHANDLE hRecord;
		UINT iStat = MsiViewFetch(hView, &hRecord);
		if (iStat == ERROR_NO_MORE_ITEMS)
			break;
		CheckMsi(iStat, TEXT("Fetch"));
		TCHAR szAction[60];
		int iSequence, iNew;
		DWORD cchAction = sizeof(szAction)/sizeof(TCHAR);
		MsiRecordGetString(hRecord, 1, szAction, &cchAction);
		iSequence = MsiRecordGetInteger(hRecord, 2);
		if (iSequence > 0)
		{
			iLast += iSpacing;
			iNew = iLast;
			CheckMsi(MsiRecordSetInteger(hRecord, 2, iNew), TEXT("SetInteger"));
			CheckMsi(MsiViewModify(hView, MSIMODIFY_UPDATE, hRecord), TEXT("UpdateView"));
		}
		else
			iNew = iSequence;
		_tprintf(TEXT("%3i %3i  %s\n"), iSequence, iNew, szAction);
	}
}

extern "C" int __cdecl _tmain(int argc, TCHAR* argv[])
{
	if (argc < 2)
	{
		_tprintf(TEXT("Usage: ApiTstDb {database path} [{sequence spacing}]"));
		return 1;
	}
	int iSpacing = 10;
	if (argc >= 3)
	{
		int i = _ttoi(argv[2]);
		if (i > 0)
			iSpacing = i;
	}
	try
	{
		PMSIHANDLE hDatabase;
		CheckMsi(MsiOpenDatabase(argv[1], MSIDBOPEN_TRANSACT, &hDatabase),TEXT("OpenDatabase"));
		SmoothSequence(hDatabase, iSpacing);
		MsiDatabaseCommit(hDatabase);
		TCHAR rgchBuf[MAX_PATH];
		GetTempPath(MAX_PATH, rgchBuf);
		CheckMsi(MsiDatabaseExport(hDatabase, TEXT("InstallSequence"), rgchBuf, TEXT("InstallSequence.idt")),TEXT("ExportTable"));
	}
	catch (UINT iError)
	{
		_tprintf(TEXT("%s error %i"), g_szErrorContext, iError);
		return 1;
	}
	int iOpenHandles = MsiCloseAllHandles();  // diagnostic check only
	if (iOpenHandles != 0)
		_tprintf(TEXT("%i Handle(s) not closed"), iOpenHandles);
	return 0;
}

#else // RC_INVOKED, end of source code, start of resources
// resource definition go here
#endif // RC_INVOKED
#if 0 
!endif // makefile terminator
#endif
