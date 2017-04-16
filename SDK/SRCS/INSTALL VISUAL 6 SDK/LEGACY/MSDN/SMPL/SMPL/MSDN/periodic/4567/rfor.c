/******************************************************************************
Module name: RFoR.c
Written by:  Jeffrey Richter
Note:        This function abstracts the differences between Windows 95 and 
             Windows NT for replacing/deleting a file when the system reboots.
******************************************************************************/


#define STRICT
#include <windows.h>


///////////////////////////////////////////////////////////////////////////////


#include "RFoR.h"


///////////////////////////////////////////////////////////////////////////////


BOOL WINAPI ReplaceFileOnReboot (LPCTSTR pszExisting, LPCTSTR pszNew) {

   // First, attempt to use the MoveFileEx function.
   BOOL fOk = MoveFileEx(pszExisting, pszNew, MOVEFILE_DELAY_UNTIL_REBOOT);
   if (fOk) return(fOk);

   // If MoveFileEx failed, we are running on Windows 95 and need to add
   // entries to the WININIT.INI file (an ANSI file).
   // Start a new scope for local variables.
   {
   char szRenameLine[1024];   

   int cchRenameLine = wsprintfA(szRenameLine, 
#ifdef UNICODE
      "%ls=%ls\r\n", 
#else
      "%hs=%hs\r\n", 
#endif
      (pszNew == NULL) ? __TEXT("NUL") : pszNew, pszExisting);
      char szRenameSec[] = "[Rename]\r\n";
      int cchRenameSec = sizeof(szRenameSec) - 1;
      HANDLE hfile, hfilemap;
      DWORD dwFileSize, dwRenameLinePos;
      TCHAR szPathnameWinInit[_MAX_PATH];

      // Construct the full pathname of the WININIT.INI file.
      GetWindowsDirectory(szPathnameWinInit, _MAX_PATH);
      lstrcat(szPathnameWinInit, __TEXT("\\WinInit.Ini"));

      // Open/Create the WININIT.INI file.
      hfile = CreateFile(szPathnameWinInit,	
         GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 
         FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

      if (hfile == INVALID_HANDLE_VALUE) 
         return(fOk);

      // Create a file mapping object that is the current size of 
      // the WININIT.INI file plus the length of the additional string
      // that we're about to insert into it plus the length of the section
      // header (which we might have to add).
      dwFileSize = GetFileSize(hfile, NULL);
      hfilemap = CreateFileMapping(hfile, NULL, PAGE_READWRITE, 0, 
         dwFileSize + cchRenameLine + cchRenameSec, NULL);

      if (hfilemap != NULL) {

         // Map the WININIT.INI file into memory.  Note: The contents 
         // of WININIT.INI is always ANSI; never Unicode.
         LPSTR pszWinInit = (LPSTR) MapViewOfFile(hfilemap, 
            FILE_MAP_WRITE, 0, 0, 0);

         if (pszWinInit != NULL) {

            // Search for the [Rename] section in the file.
            LPSTR pszRenameSecInFile = strstr(pszWinInit, szRenameSec);

            if (pszRenameSecInFile == NULL) {

               // There is no [Rename] section in the WININIT.INI file.
               // We must add insert the section too.
               dwFileSize += wsprintfA(&pszWinInit[dwFileSize], "%s", 
                  szRenameSec);
               dwRenameLinePos = dwFileSize;

            } else {

               // We found the [Rename] section, shift all the lines down
               PSTR pszFirstRenameLine = strchr(pszRenameSecInFile, '\n');
               // Shift the contents of the file down to make room for 
               // the newly added line.  The new line is always added 
               // to the top of the list.
               pszFirstRenameLine++;   // 1st char on the next line
               memmove(pszFirstRenameLine + cchRenameLine, 
                  pszFirstRenameLine, 
                  pszWinInit + dwFileSize - pszFirstRenameLine);                  
               dwRenameLinePos = pszFirstRenameLine - pszWinInit;
            }

            // Insert the new line
            memcpy(&pszWinInit[dwRenameLinePos], szRenameLine, 
               cchRenameLine);

            UnmapViewOfFile(pszWinInit);

            // Calculate the true, new size of the file.
            dwFileSize += cchRenameLine;

            // Everything was successful.
            fOk = TRUE; 
         }
         CloseHandle(hfilemap);
      }

      // Force the end of the file to be the calculated, new size.
      SetFilePointer(hfile, dwFileSize, NULL, FILE_BEGIN);
      SetEndOfFile(hfile);

      CloseHandle(hfile);
   }

   return(fOk);
}


///////////////////////////////// End of File /////////////////////////////////
