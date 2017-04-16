//---------------------------------------------------------------------------
//  DLLSTUFF - Windows DLL support functions
//
//  This File contains the source code for the standard DLL functions
//
//  Author:     Kyle Marsh
//              Windows Developer Technology Group
//              Microsoft Corp.
//
//---------------------------------------------------------------------------

#include "vlistint.h"

//---------------------------------------------------------------------------
// Function declarations
//---------------------------------------------------------------------------

int   FAR PASCAL LibMain(HANDLE hModule, WORD wDataSeg, WORD cbHeapSize, LPSTR lpszCmdLine);
int   FAR PASCAL WEP (int bSystemExit);

//---------------------------------------------------------------------------
// Global Variables...
//---------------------------------------------------------------------------

HANDLE  hInstance;              // Global instance handle for  DLL

//---------------------------------------------------------------------------
// LibMain
//---------------------------------------------------------------------------
#ifdef WIN32
BOOL CALLBACK DllEntryPoint(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch( dwReason ) {
	 case DLL_PROCESS_ATTACH:
                hInstance = hModule;
                RegisterVListBox(hInstance);
	}
	return	TRUE;
}
#else
int WINAPI LibMain(HANDLE hModule, WORD wDataSeg, WORD cbHeapSize, LPSTR lpszCmdLine)
{

        hInstance = hModule;

        RegisterVListBox(hInstance);

        return 1;

}
#endif	// win32

#pragma alloc_text(FIXEDSEG, WEP)

//---------------------------------------------------------------------------
// WEP
//---------------------------------------------------------------------------
int FAR PASCAL WEP (int bSystemExit)
{
    return(1);
}
