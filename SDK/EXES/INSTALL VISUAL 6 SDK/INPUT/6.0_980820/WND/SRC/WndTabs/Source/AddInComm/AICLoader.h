/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/

// AddInComm Loader, (AIC 1.4.0 - December 2000)

#ifndef __AICLOADER_H
#define __AICLOADER_H

/* Will load the AIC library.  
   Debug builds try to load AICD.mod be default, release builds try to load 
   AIC.mod.  To override this behavior use UseDeubgLibrary();
*/
bool aiclLoadAICLibrary(HINSTANCE hInst);

/* Will force the AIC library to unload.  The Use of this function is 
   optional. 
*/
void aiclUnloadAICLibrary();

/* Override default library load:
   TRUE   -  Use debugging version of AIC (AICD.mod)
   FALSE  -  Use release version of AIC (AIC.mod)
*/
void aiclUseDebugLibrary(BOOL bUse);

bool aiclIsAICLoaded();


/* == AICL functionality not related to AddInComm == */
/* (some internal loader function that should be useful to outsiders) */

/* These functions allow you to extract the content of a file's version 
   resource.  You can either specify a file name (aiclGetFileVersion()) or
   a name or a running module (aiclGetModuleVersion()).
   Return value: 'true'-success, 'false'-failure
*/
bool aiclGetFileVersion  (LPCTSTR pszPath, LPSTR out_pszVer);
bool aiclGetModuleVersion(LPCTSTR pszMod,  LPSTR out_pszVer);

/* Returns DevStudio's registry key in HKEY_CURRENT_USER (works only when
   DevStudio is running).
   Return value: 'true'-success, 'false'-failure
*/
bool aiclGetDSCurrentUserRegKey(LPSTR out_pszKeyName);

/* Returns DevStudio's add-in directory (empty string returned on error) */
void aiclGetDSAddInDir(LPSTR out_pszPath, DWORD cb);


/* aicl's version of the Win32 ::LoadLibrary() function will attempt to
   load the a .dll in the following order:
     1. the standard Win32 search order (see description of LoadLibrary)
     2. in the same directory your add-in resides
     3. in the DevStudio add-ins directory
*/
HINSTANCE aiclLoadLibByFileName(HINSTANCE hMyInst, const char *pszFileName);


#endif // __AICLOADER_H
