//*---------------------------------------------------------------------------------
//|  ODBC System Administrator
//|
//|  This code is furnished on an as-is basis as part of the ODBC SDK and is
//|  intended for example purposes only.
//|
//|   Title:   STANDARD.C
//|      This module contains standard functions which can be used by many
//|      different tools.
//|
//|      The DumpDebugInfo function when enabled will cause all memory requests
//|      and frees to be written to a comma separated file.  This file can then
//|      be queries via the sample Text ODBC Driver to find memory problems.
//*---------------------------------------------------------------------------------
#include "standard.h"
#include <windowsx.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "errcheck.h"
#include "strings.h"



//*---------------------------------------------------------------------------------
//|   Global variables
//*---------------------------------------------------------------------------------
char OutStr[MAXBUFF];
dCSEG(char) szui[]                        =  "%u";
dCSEG(char) szEmpty[]                     =  "\0";
dCSEG(char) szcrlf[]                      =  "\r\n";

#ifdef _DEBUG
#include "time.h"
#define szASSERTERROR (LPSTR)"Assert: %s, %s, %d"
#define szDEBUGFILE (LPSTR)"C:\\TMP\\MEM"
char szDbgOut[200];
BOOL fNew=TRUE;

void WinAssertReal(int exp, LPSTR msg, LPSTR file, int line)
{
   if(!exp) {
      wsprintf(szDbgOut, szASSERTERROR, msg, file, line);
      MessageBox(GetActiveWindow(), szDbgOut, szErrTitle, MB_OK);
   }
}

void DumpDebugInfo(LPVOID tmp, LPSTR szFile, int cbLine, int stat,
         DWORD rqSize, DWORD aSize)
{
   static   OFSTRUCT    ofs;
   static   HFILE       hf;
   static   time_t      thetime;
   static   struct tm * tmVal;

   if(fNew) {
      fNew = FALSE;
      ofs.cBytes = sizeof(OFSTRUCT);
      hf = OpenFile(szDEBUGFILE, &ofs, OF_DELETE);
      _lclose(hf);
   }

   // Creates file MEM which is a comma separated text file.
   // Issue the select statement to find memory ptrs
   // which were allocated but never freed (status=1), and
   // pointers which were freed but never allocated (status=-1).
   // Of course "No data found" is the desired response.
   //    create table mem
   //        (address char(9),
   //         logtime char(8),
   //         status integer,
   //         desired integer,
   //         actual integer,
   //         line integer,
   //         file char(45))
   //    select address, sum(status) from mem
   //      group by address having sum(status) <> 0
   time(&thetime);
   tmVal = localtime(&thetime);
   wsprintf(szDbgOut, (LPSTR)"%04X:%04X,%02u:%02u:%02u,%d,%lu,%lu,%u,%s\r\n",
            HIWORD(tmp), LOWORD(tmp), tmVal->tm_hour, tmVal->tm_min, tmVal->tm_sec,
            stat, rqSize, aSize, cbLine, (LPSTR)szFile);
   if((hf = _lopen(szDEBUGFILE, WRITE)) == -1)  // File not found
      hf = OpenFile(szDEBUGFILE, &ofs, OF_CREATE);
   _llseek(hf, 0L, 2);                    // Try to go to end of file
   _lwrite(hf, szDbgOut, lstrlen(szDbgOut));  // Write wherever we are
   _lclose(hf);
}

void FAR * DebugGetMemory(DWORD size, LPSTR szFile, int cbLine)
{
   LPVOID   ptr;
   DWORD    aSize;

   ptr = DoGetMemory(size);
   if(!ptr)
      return ptr;
   aSize = GlobalSize(GlobalPtrHandle(ptr));
   DumpDebugInfo(ptr, szFile, cbLine, 1, size, aSize);

   return ptr;
}

void DebugReleaseMemory(LPVOID ptr, LPSTR szFile, int cbLine)
{
   GlobalFreePtr(ptr);
   DumpDebugInfo(ptr, szFile, cbLine, -1, 0, 0);
}
#endif      // Debug memory routines


//*---------------------------------------------------------------------------------
//| DoGetMemory:
//|   This function allocates the specified amount of memory.
//| Parms:
//|   in       size                 How much memory
//| Returns:
//|   Long pointer to void
//*---------------------------------------------------------------------------------
void FAR * DoGetMemory(DWORD size)
{
   LPVOID   tmp;

   tmp = GlobalAllocPtr(GMEM_FIXED | GMEM_ZEROINIT, size);
   if(!tmp)
      szMessageBox(GetActiveWindow(),
                   MB_ICONEXCLAMATION,
                   (LPSTR)szErrTitle,
                   GetidsString(idsOutOfMemory, OutStr, MAXBUFF));
   return tmp;
}


//*---------------------------------------------------------------------------------
//| DoReleaseMemory:
//|   Free up the memory we have requested
//| Parms:
//|   ptr         The pointer to free
//| Returns:
//|   Nothing.
//*---------------------------------------------------------------------------------
void DoReleaseMemory(LPVOID ptr)
{
   GlobalFreePtr(ptr);
}


//*---------------------------------------------------------------------------------
//| RemoveCrLf:
//|   This will remove all carriage return/line feeds from the input buffer.
//| Parms:
//|   in       instr                Null terminated string
//| Returns:
//|   Nothing
//*---------------------------------------------------------------------------------
void RemoveCrLf(LPSTR instr)
{
   LPSTR str=instr;

   if(!str ||
      !*str)
      return;
   while((str = _fstrstr(str, (LPSTR)szcrlf))) {
      *str++ = ' ';
      *str++ = ' ';
   }
}


//*---------------------------------------------------------------------------------
//| GetNewDirectory:
//|   This function will take a complete file name (must have path included)
//|   and return only the path portion with no trailing '\'
//| Parms:
//|   outstr            Output path name with no file
//|   instr             Input complete file name
//| Returns:
//|   Nothing
//*---------------------------------------------------------------------------------
void GetNewDirectory(LPSTR outstr, LPSTR instr)
{
   LPSTR    str=outstr;
   LPSTR    lstr=outstr;

   lstrcpy(str, instr);
   while((str = _fstrchr(lstr+1, '\\')))
      lstr = str++;
   *++lstr = '\0';
}


//*---------------------------------------------------------------------------------
//| ValidName:
//|   This function parses a string to look for invalid characters which would
//|   preclude it from being written as a section or entry in an .ini file.
//| Parms:
//|   instr             Input complete file name
//| Returns:
//|   TRUE if it is valid, FALSE on error
//*---------------------------------------------------------------------------------
BOOL ValidName(LPSTR instr)
{
   LPSTR str=instr;
   if(!str)
      return TRUE;
   while(*str)
      switch(*str) {
        case '[':
        case ']':
        case '=':
         return FALSE;

        default:
         ++str;
      }
   return TRUE;
}


//*---------------------------------------------------------------------------------
//| lpatoi:
//|   atoi only works for NEAR host vars, which makes it useless in a large
//|   application.  This function tricks atoi by copy the long string to a
//|   local variable and then doing the conversion.  This is a major cluge,
//|   but a necessary one.
//| Parms:
//|   instr             Input number
//| Returns:
//|   The integer value of instr
//*---------------------------------------------------------------------------------
int lpatoi(LPSTR instr)
{
   char szStr[35];
   lstrcpy((LPSTR)szStr, instr);
   return atoi(szStr);
}


//*------------------------------------------------------------------------
//|  GetidsString:
//|      Will retrieve a string from our resource fork given the id.
//|  Parms:
//|      ids            The id of the string
//|      szOut          Output buffer for string
//|      cbSize         How big is the buffer
//|  Returns:
//|      Pointer to szOut
//*------------------------------------------------------------------------
LPSTR EXTFUN GetidsString(UINT ids, LPSTR szOut, UINT cbSize)
{
   extern HINSTANCE hInst;

   if(!szOut)
      return NULL;
   if(!LoadString(hInst, ids, szOut, cbSize))
      lstrcpy(szOut, "Not found");
   return szOut;
}



//*------------------------------------------------------------------------
//|  szWrite:
//|      Allows you to format an output string which is then added
//|      to the specified edit window.
//|  Parms:
//|      hwnd           Edit window for output
//|      szFmt          Format string
//|      (varying)      Arguements for format string
//|  Returns:
//|      Nothing
//*------------------------------------------------------------------------
VOID FAR CDECL szWrite(HWND hwnd, LPSTR szFmt, ...)
{
#define MAXEDITBUFF 30000
   static      char  szBuffer[MAXBUFF];
   UCHAR *     pszBuffer;
   UCHAR       bufFmt[MAXBUFF];
   va_list           marker;
   UINT              rtn=0;
   UINT              len=0;


   pszBuffer = &szBuffer[0];
   lstrcpy(bufFmt, szFmt);

   // Use format and arguements as input
   va_start(marker, szFmt);
   if (_vsnprintf(pszBuffer, MAXBUFF, bufFmt, marker) < 0) {
      wsprintf(pszBuffer,"Buffer overflow reporting '%*.*s'", 50,50,(LPSTR)szBuffer);
      return;
   }
   va_end(marker);


   // Now we have the string to add to the end of our output.  Verify that the
   // new string will not be too large and set selection accordingly.
   len = (UINT)SendMessage(hwnd, WM_GETTEXTLENGTH, 0, 0L);
   if(len + lstrlen(pszBuffer) > MAXEDITBUFF) {    //  Need to truncate
      SendMessage(hwnd, EM_SETSEL, 0, MAKELPARAM(0,len + 10));
      SendMessage(hwnd, EM_REPLACESEL, 0, (LPARAM)((LPSTR)"...\r\n"));
      SendMessage(hwnd, EM_SETSEL, 0, MAKELPARAM(len,len));
   }
   SendMessage(hwnd, EM_REPLACESEL, 0, (LPARAM)((LPSTR)pszBuffer));
}


//*------------------------------------------------------------------------
//|  szMessageBox:
//|      Works like sprintf only the output goes to a message box.
//|  Parms:
//|      hwnd           Owner window, NULL uses GetActiveWindow
//|      style          Flags for MessageBox
//|      szTitle        Title for message box
//|      szFmt          Format string
//|      (varying)      Arguements for format string
//|  Returns:
//|      Id from MessageBox
//*------------------------------------------------------------------------
int FAR CDECL szMessageBox(HWND hwnd, UINT style, LPSTR szTitle, LPSTR szFmt, ...)
{
   char        szBuffer[MAXBUFF];
   char *      pszBuffer;
   UCHAR       bufFmt[MAXBUFF];
   va_list     marker;

   pszBuffer = &szBuffer[0];
   lstrcpy(bufFmt, szFmt);

   // Use format and arguements as input
   va_start(marker, szFmt);
   if (_vsnprintf(pszBuffer, MAXBUFF, bufFmt, marker) < 0)
      wsprintf(pszBuffer,"Buffer overflow reporting '%*.*s'", 50,50,szBuffer);
   va_end(marker);

   return(MessageBox((hwnd) ? hwnd : GetActiveWindow(),
                     pszBuffer,
                     szTitle,
                     style) == IDOK);
}
