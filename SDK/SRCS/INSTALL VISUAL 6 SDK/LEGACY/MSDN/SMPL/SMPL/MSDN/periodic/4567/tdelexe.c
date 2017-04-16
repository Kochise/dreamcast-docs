/******************************************************************************
Module name: TDelExe.c
Written by:  Jeffrey Richter
Note:        This function test the functions that delete our own executable.
******************************************************************************/


#define STRICT
#include <Windows.h>


///////////////////////////////////////////////////////////////////////////////


#include "RFoR.h"       // to delete this executable file on reboot.
#include "DelExe.h"     // to delete this executable file using a batch file.
#include "DelExeBF.h"   // to delete this executable file using code.


///////////////////////////////////////////////////////////////////////////////


int WINAPI WinMain (HINSTANCE hinstExe, HINSTANCE hinstExePrev, 
   LPSTR lpszCmdLine, int nCmdShow) {

   int nId = MessageBox(NULL, 
      __TEXT("Choose Yes to delete this executable file on reboot.\n")
      __TEXT("Choose No to delete this executable file using a batch file.\n")
      __TEXT("Choose Cancel to delete this executable file using code.\n"),
      __TEXT("Delete Executable"), MB_YESNOCANCEL);

   switch (nId) {
      case IDYES:
         {
         TCHAR szPathname[_MAX_PATH];
         GetModuleFileName(NULL, szPathname, _MAX_PATH);
         ReplaceFileOnReboot(szPathname, NULL);
         }
         break;

      case IDNO:
         DeleteExecutableBF();
         // We want to terminate right away so that we can be deleted
         break;

      case IDCANCEL:
      	DeleteExecutable(0, TRUE);
      	// DeleteExecutable never returns back to us.
         break;
   }

	return(0);
}


///////////////////////////////// End of File /////////////////////////////////
