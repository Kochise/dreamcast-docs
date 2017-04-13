/*
 * OLEINST.C
 *
 * OLE-Specific installation-time functions that should be performed
 * once when the application is first added to the system.
 *
 * Note that there are embedded strings in this file.  We do not use
 * strings from the application wide source in rgpsz since we want this
 * module to be reusable in installation programs.
 *
 * Copyright(c) Microsoft Corp. 1992-1994 All Rights Reserved
 * Win32 version, January 1994
 */


#ifdef MAKEOLESERVER

#include <windows.h>
#include "cosmo.h"
#include "oleinst.h"


/*
 * FRegDBInstall
 *
 * Purpose:
 *  Handles any installations the applciation must handle for the
 *  registration database.  In this application, we just set up to
 *  call FOLEInstall that handles the OLE specific strings.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if installation succeeded, FALSE otherwise.
 *
 */

BOOL FAR PASCAL FRegDBInstall(void)
    {
    REGINSTALL  ri;
    HMODULE     hMod;
    LPSTR       rgszVerbs[OBJVERB_MAX];
    char        szPath[CCHPATHMAX];

    /*
     * Fill the REGINSTALL structure for calling FOLEServerInstall.
     * Must do this after the strings are loaded since we use strings
     * from the stringtable.
     */
    ri.pszServerName    =(LPSTR)rgpsz[IDS_FULLNAME];
    ri.pszServerClass   =(LPSTR)rgpsz[IDS_CLASSCOSMO];
    ri.pszHandlerPath   =(LPSTR)NULL;
    ri.pszExt           =(LPSTR)rgpsz[IDS_DOTEXT];
    ri.pszSetFormats    =(LPSTR)rgpsz[IDS_NATIVE];
    ri.pszRequestFormats=(LPSTR)rgpsz[IDS_DATAFORMATS];
    ri.fExecute         =FALSE;

    //Get the module path
    hMod=GetModuleHandle(rgpsz[IDS_MODULE]);

    if (NULL==hMod)
        return FALSE;

    GetModuleFileName(hMod, szPath, CCHPATHMAX);

    ri.pszServerPath    =(LPSTR)szPath;

    //Fill the array of pointers to verbs.
    rgszVerbs[OBJVERB_EDIT]=(LPSTR)rgpsz[IDS_VERBEDIT];

    ri.ppszVerbs        =rgszVerbs;
    ri.cVerbs           =OBJVERB_MAX;

    return FOLEServerInstall(&ri);
    }





/*
 * FOLEServerInstall
 *
 * Purpose:
 *  Registers the server application and it's editable data types
 *  with the registration database through the SHELL.DLL functions.
 *
 *  This function will register the server in the database if it
 *  is not there already.
 *
 * Limitations:
 *  FOLEServerInstall supports only a single class of data.
 *
 * Parameters:
 *  pszServer       LPSTR name of the server.
 *  pszData         LPSTR name of the data edited by the server.
 *
 * Return Value:
 *  BOOL            TRUE if registration took place or the application
 *                  was already registered, FALSE otherwise.
 */


BOOL FAR PASCAL FOLEServerInstall(LPREGINSTALL lpRI)
    {
    char        szKey[128];
    char        szTemp[20];
    DWORD       dw=128;
    LONG        lRet;
    UINT        iVerb;
    LPSTR       *ppsz;

    //Check if this server is already around.
    lRet=RegQueryValue(HKEY_CLASSES_ROOT, lpRI->pszServerClass, szKey, &dw);

    if ((LONG)ERROR_SUCCESS==lRet)
        return TRUE;


    /*
     * Add various strings to the registration database:
     *  1.  English-readable class name.
     *  2.  Simple class name.
     *  3.  Full path to the server executable.
     *  4.  Full path to the handler DLL, if available.
     *  5.  Verbs
     *  6.  Any formats supported through OleSetData and OleRequestData.
     *  7.  Full application path if the server supports StdExecute.
     */

    //Validate essential strings
    if (NULL==lpRI->pszServerClass)
        return FALSE;

    if (NULL==lpRI->pszServerName)
        return FALSE;

    if (NULL==lpRI->pszServerPath)
        return FALSE;

    if (NULL==lpRI->pszExt)
        return FALSE;

    if (NULL==lpRI->ppszVerbs || 0==lpRI->cVerbs)
        return FALSE;


    //1. English class name.  Subkey is ""
    FKeyCreate(lpRI->pszServerClass, rgpsz[IDS_EMPTY], lpRI->pszServerName);


    //2. Simple class name associated with the file extension.  Subkey is ""
    FKeyCreate(lpRI->pszExt, rgpsz[IDS_EMPTY], lpRI->pszServerClass);


    /*
     * The server path, handler path, and verbs are all part of
     * the \\classname\\protocol\\StdFileEditing\\ key.  Before
     * creating any of the keys, create a string with the class
     * name embedded.
     */
    wsprintf(szKey, "%s\\protocol\\StdFileEditing\\", lpRI->pszServerClass);


    //3. Server path, append "server" onto szKey.
    FKeyCreate(szKey, "server", lpRI->pszServerPath);

    //4. Add the handler path, if one exists, appening "handler" on szKey.
    if (NULL!=lpRI->pszHandlerPath)
        FKeyCreate(szKey, "handler", lpRI->pszHandlerPath);

    //5.  Add each verb.  Append to szKey "verb\\n" where n is a simple count.
    ppsz=lpRI->ppszVerbs;

    for (iVerb=0; iVerb < lpRI->cVerbs; iVerb++)
        {
        //Create key and skip to next verb.
        wsprintf(szTemp, "verb\\%d", iVerb);
        FKeyCreate(szKey, szTemp, *ppsz++);
        }


    //6. Add the strings for formats, to "SetDataFormats" and "RequestDataFormats"
    if (NULL!=lpRI->pszSetFormats)
        FKeyCreate(szKey, "SetDataFormats", lpRI->pszSetFormats);

    if (NULL!=lpRI->pszSetFormats)
        FKeyCreate(szKey, "RequestDataFormats", lpRI->pszRequestFormats);


    //7. Add the StdExecute string, appending the server path.
    if (lpRI->fExecute)
        {
        wsprintf(szKey, "%s\\protocol\\StdExecute\\", lpRI->pszServerClass);
        FKeyCreate(szKey, "server", lpRI->pszServerPath);
        }

    return TRUE;
    }



/*
 * FKeyCreate
 *
 * Purpose:
 *  Short function to simplify the key creation process, centralizing
 *  calls to RegCreateKey, RegSetValue, and RegCloseKey.  If the RegSetValue
 *  fails, the key is deleted with RegDeleteKey.
 *
 * Parameters:
 *  pszKey          LPSTR to keyname.
 *  pszSubKey       LPSTR to last word in keyname.  This parameter is
 *                  separate to enable calling RegDeleteKey on error.
 *  pszValue        LPSTR to value to associate with keyname.
 *
 * Return Value:
 *  BOOL            TRUE if registration succeeded, FALSE otherwise.
 */

BOOL PASCAL FKeyCreate(LPSTR pszKey, LPSTR pszSubKey, LPSTR pszValue)
    {
    char        szKey[128];
    HKEY        hKey;
    UINT        cch;
    LONG        lRet;

    cch=lstrlen(pszValue)+1;

    lstrcpy(szKey, pszKey);
    lstrcat(szKey, pszSubKey);

    lRet=RegCreateKey(HKEY_CLASSES_ROOT, szKey, &hKey);

    if (lRet!=ERROR_SUCCESS)
        return FALSE;


    lRet=RegSetValue(HKEY_CLASSES_ROOT, szKey, REG_SZ, pszValue, cch);

    if (lRet!=ERROR_SUCCESS)
        {
        //Delete key if we could not set a value.
        RegDeleteKey(hKey, pszSubKey);
        return FALSE;
        }

    lRet=RegCloseKey(hKey);

    if (lRet!=ERROR_SUCCESS)
        return FALSE;

    return TRUE;
    }



#endif   //MAKEOLESERVER
