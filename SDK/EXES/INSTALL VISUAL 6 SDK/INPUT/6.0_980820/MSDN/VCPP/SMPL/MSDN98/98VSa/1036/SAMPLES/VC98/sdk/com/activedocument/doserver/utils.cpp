/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          Utils.cpp
   
   Description:   Contains utility routines for the DOServer sample.

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include <windows.h>
#include "utils.h"

/**************************************************************************

   ParseCommandLine()
   
   Parses the Windows command line which was passed to WinMain.
   This function determines if the -Embedding switch has been given.

**************************************************************************/

STDAPI_(void) ParseCommandLine(LPSTR pszCommandLine, LPBOOL pfEmbedFlag, LPTSTR pszFileName)
{
int      i;
TCHAR    szCmdLine[MAX_PATH];
LPTSTR   pszCmdLine = szCmdLine;
TCHAR    szBuf[MAX_PATH];

if(!pszCommandLine)
   return;
   
if(!pfEmbedFlag)
   return;
   
*pfEmbedFlag = FALSE;

#ifdef UNICODE
MultiByteToWideChar( CP_ACP, 
                     MB_PRECOMPOSED, 
                     pszCommandLine, 
                     -1, 
                     pszCmdLine,
                     ARRAYSIZE(szCmdLine));
#else
lstrcpy(pszCmdLine, pszCommandLine);
#endif

// skip blanks
while(isspace(*pszCmdLine)) 
   pszCmdLine++;

// No filename or options, so start a fresh document.
if(!*pszCmdLine)   
   return;

// Check for "-Embedding" or "/Embedding" and set fEmbedding.
if((*pszCmdLine == '-') || (*pszCmdLine == '/'))
   {
   pszCmdLine++;
   pszCmdLine = GetWord(pszCmdLine, szBuf);
   *pfEmbedFlag = !lstrcmp(szBuf, EMBEDDINGFLAG);
   }

if(!pszFileName)
   return;
   
*pszFileName = 0;

// skip blanks
while(isspace(*pszCmdLine)) 
   pszCmdLine++;

// set pszFileName to argument
for(i = 0; *(pszCmdLine + i); i++) 
   {
   *(pszFileName + i) = *(pszCmdLine + i);
   }

*(pszFileName + i) = 0;
}


/**************************************************************************

   GetWord()
   
   LPSTR lpszSrc - Pointer to a source string
   LPSTR lpszDst - Pointer to destination buffer

   Will copy one space-terminated or null-terminated word from the source
   string to the destination buffer.
   
   returns: pointer to next character following the word.

**************************************************************************/

static LPTSTR GetWord(LPTSTR lpszSrc, LPTSTR lpszDst)
{
while (*lpszSrc && !isspace(*lpszSrc))
   *lpszDst++ = *lpszSrc++;

*lpszDst = '\0';

return lpszSrc;
}

/* GetOleObjectDataHere
** ----------------------
**    Render CF_EMBEDSOURCE/CF_EMBEDDEDOBJECT data on an TYMED_ISTORAGE
**    medium by asking the object to save into the storage.
**    the object must support IPersistStorage.
**
**    if lpMedium->tymed == TYMED_NULL, then a delete-on-release
**    storage is allocated (either file-based or memory-base depending
**    the value of fUseMemory). this is useful to support an
**    IDataObject::GetData call where the callee must allocate the
**    medium.
**
**    if lpMedium->tymed == TYMED_ISTORAGE, then the data is writen
**    into the passed in IStorage. this is useful to support an
**    IDataObject::GetDataHere call where the caller has allocated his
**    own IStorage.
*/
STDAPI GetOleObjectDataHere(  LPPERSISTSTORAGE lpPStg,
                              LPFORMATETC lpformatetc,
                              LPSTGMEDIUM lpMedium)
{
LPSTORAGE   lpstg = NULL;
DWORD       reserved = 0;
HRESULT     hr = DATA_E_FORMATETC;

lpMedium->pUnkForRelease = NULL;

if(lpMedium->tymed != TYMED_ISTORAGE) 
   {
   return hr;
   }

//AddRef the IStorage pointer
lpPStg->AddRef();

// NOTE: even if OleSave returns an error you should still call
// SaveCompleted.

hr = OleSave(lpPStg, lpMedium->pstg, FALSE /* fSameAsLoad */);

lpPStg->SaveCompleted(NULL);

return hr;
}

