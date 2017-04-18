/*
 * INIT.C
 *
 * Application (not OLE) specific initialization code.
 *  FApplicationInit
 *  FFileInit
 *  HLoadAppStrings
 *  HListParse
 *  PszWhiteSpaceScan
 *
 * FApplicationInit makes some calls into OLEINST.C and OLEINIT.C
 *
 * Copyright(c) Microsoft Corp. 1992-1994 All Rights Reserved
 * Win32 version, January 1994
 */


#include <windows.h>
#include <ole.h>
#include "cosmo.h"
#include "oleinst.h"
#include "oleglobl.h"



/*
 * FApplicationInit
 *
 * Purpose:
 *  All application specific initialization including loading
 *  the stringtable, registering window classes, and calling any
 *  OLE specific initialziation code.
 *
 * Parameters:
 *  pGlob           LPGLOBALS to global variable block.
 *  hPrevInst       HINSTANCE to the previous application instance, if any.
 *
 * Return Value:
 *  BOOL            TRUE if everything succeeds, FALSE otherwise.
 *                  If FALSE is returned, allocated memory and objects
 *                  are not necessarily freed.  The caller should then
 *                  use the FApplicationExit function to perform cleanup.
 */

BOOL WINAPI FApplicationInit(LPGLOBALS pGlob, HINSTANCE hPrevInst)
    {
    HLOCAL      hMem;
    LPSTR FAR * ppszCmds;
    LPSTR FAR * ppszT;
    BOOL        fRet=TRUE;

#ifdef MAKEOLESERVER
    //Make sure this is NULLed in case we fail
    pOLE->pSvr=NULL;
#endif

    /*
     * InitApp allocates local memory for strings. WinMain must free.
     * If this fails, we should quit BEFORE we register any classes
     * or do anything else to suck up USER or GDI resources.
     */
    hMem=HLoadAppStrings(pGlob);

    if (NULL==hMem)
        return FALSE;

    pGlob->hStringMem=hMem;

    //Classes are only registered if hPrevInstance is NULL.
    if (!FClassRegister(pGlob, hPrevInst))
        {
        LocalFree(pGlob->hStringMem);
        return FALSE;
        }

    //Register a private clipboard format, same as the class name.
    pGlob->cfCosmo=RegisterClipboardFormat(rgpsz[IDS_CLASSCOSMO]);

    hMem=HListParse(pGlob->pszCmdLine);
    ppszCmds=(LPSTR FAR *)(PSTR)hMem;
    ppszT=ppszCmds;

    /*
     * Scan the command line list for the first thing without a
     * / or - which is out initial file.
     */

    while (*ppszT)
        {
        if ('-'!=**ppszT && '/'!=**ppszT)
            break;

        ppszT++;
        }

    //Copy this filename for later loading during WM_CREATE.
    if (NULL==*ppszT)
        pGlob->szFile[0]=0;
    else
        lstrcpy(pGlob->szFile, *ppszT);


#ifdef MAKEOLESERVER
    /*
     * Go do anything that deals with the registration database.
     * Installation could be moved to an installation program
     */
    if (!FRegDBInstall())
        {
        LocalFree(hMem);
        return FALSE;
        }

    //Initialize OLE specific data.  FOLEInstanceInit affects pGlob->fOLE
    if (FOLEInstanceInit(pOLE, pGlob->hInst, rgpsz[IDS_CLASSCOSMO]
        , ppszCmds, pGlob->nCmdShow))
        {
        //We will open any linked file later in WM_CREATE.

        //Copy the new ShowWindow parameter.
        pGlob->nCmdShow=pOLE->pSvr->nCmdShow;
        }
    else
        fRet=FALSE;

#endif //MAKEOLESERVER

    //Free the command-line string list in hMem.
    LocalFree(hMem);
    return fRet;
    }







/*
 * FClassRegister
 *
 * Purpose:
 *  Registers classes used by the application:  "Cosmo" the main
 *  window, and "Polyline" the editing window.
 *
 * Parameters:
 *  pGlob           LPGLOBALS to the global variables block.
 *  hPrevInst       HINSTANCE of any previous application instance.
 *
 * Return Value:
 *  BOOL            TRUE if all classes are successfully registered
 *                  (or if hPrevInstance is non-NULL).  FALSE is
 *                  any registration fails.
 *
 */

BOOL WINAPI FClassRegister(LPGLOBALS pGlob, HINSTANCE hPrevInst)
    {
    WNDCLASS        wc;

    if (hPrevInst)
        return TRUE;

    /*
     * Note that we do not need to unregister classes on a failure
     * since that's part of automatic app cleanup.
     */
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = CosmoWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = pGlob->hInst;
    wc.hIcon         = LoadIcon(pGlob->hInst, "Icon");
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE + 1);
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU);
    wc.lpszClassName = rgpsz[IDS_CLASSCOSMO];

    if (!RegisterClass(&wc))
        return FALSE;


    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = PolylineWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = CBPOLYLINEWNDEXTRA;
    wc.hInstance     = pGlob->hInst;
    wc.hIcon         = NULL;
    wc.hCursor       = LoadCursor(NULL, IDC_CROSS);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = rgpsz[IDS_CLASSPOLYLINE];

    if (!RegisterClass(&wc))
        return FALSE;

    return TRUE;
    }





/*
 * FFileInit
 *
 * Purpose:
 *  Loads a file specified on the command line and sets the polyline
 *  window data to reflect the contents of that file.  This is set
 *  in a different function instead of in FApplicationInit since
 *  it depends on the Polyline window being created which has not
 *  happened by FApplicationInit time.
 *
 * Parameters:
 *  pGlob           LPGLOBALS to global variable block.
 *
 * Return Value:
 *  BOOL            TRUE if everything succeeded, FALSE otherwise.
 *
 */

BOOL WINAPI FFileInit(LPGLOBALS pGlob)
    {
    POLYLINE        pl;

    /*
     * If there is a file to load, then load it and change the
     * window title.  If loading fails, then default to a new
     * untitled document.
     */
    if (0!=pGlob->szFile[0])
        {
        if (!FCosFileRead(pGlob, pGlob->szFile, &pl))
            {
            //If we're in OLE linking mode, return unsuccessful
            if (pGlob->fOLE)
                return FALSE;

            pGlob->szFile[0]=0;
            WindowTitleSet(pGlob->hWnd, rgpsz[IDS_UNTITLED]);
            pGlob->fOpenFile=FALSE;

            }
        else
            {
            SendMessage(pGlob->hWndPolyline, PLM_POLYLINESET, TRUE,
                        (LONG)(LPSTR)&pl);
            WindowTitleSet(pGlob->hWnd, pGlob->szFile);
            pGlob->fOpenFile=TRUE;
            }
        }

    return TRUE;
    }







/*
 * HLoadAppStrings
 *
 * Purpose:
 *  Allocates FIXED local memory and reads the applications
 *  string resources into that memory.  Each string's pointer
 *  is available with rgpsz[i] where i is the ID value of the
 *  string.  The strings must have sequential IDs.
 *
 * Parameters:
 *  pGlob           LPGLOBALS to global variable block.
 *
 * Return Value:
 *  HLOCAL          Handle to the local memory.  NULL if memory could
 *                  not be allocated.
 */

HLOCAL WINAPI HLoadAppStrings(LPGLOBALS pGlob)
    {
    HLOCAL      hLocalMem;
    char NEAR   *pch;
    UINT        cchUsed=0;
    UINT        cch;
    short       i;

    /*
     * Allocate memory and load strings.  NOTE!  The LPTR style
     * specifies FIXED memory.  This should not be a big deal
     * since this is an early allocation into the local heap.
     * But it should be watched if the number of strings becomes
     * large.
     */
    hLocalMem=LocalAlloc(LPTR, CSTRINGS*CCHSTRINGMAX);

    if (hLocalMem==NULL)
        return (HLOCAL)NULL;

    /*
     * This operation is only valid for FIXED memory.  Otherwise use
     * LocalLock.
     */
    pch=(char *)hLocalMem;


    /*
     * Load the strings into the memory and retain the specific
     * pointer to that string.
     */
    for (i=0; i<CSTRINGS; i++)
        {
        cch=LoadString(pGlob->hInst, i, (LPSTR)(pch+cchUsed), CCHSTRINGMAX-1);
        rgpsz[i]=(char *)(pch+cchUsed);

        /*
         * One is added to cch to include a NULL.  The memory was ZEROINITed
         * on allocation so by skipping a byte we get the NULL.
         */
        cchUsed +=cch+1;
        }

    /*
     * We are assuming that no string is over CCHSTRINGMAX, and therefore
     * we did not use all the allocated memory.  Therefore LocalReAlloc
     * will only SHRINK the block, never expand it.  So if it fails, we
     * don't care--all the strings are still there, we just wasted some
     * space.
     */
    LocalReAlloc(hLocalMem, cchUsed+1, LPTR);

    return hLocalMem;
    }








/*
 * HListParse
 *
 * Purpose:
 *  Parses any string containing text separated by whitespace into
 *  a list of pointers into that string as well as overwriting the
 *  whitespace with null terminators.  The result is that each
 *  pointer in the list points to its own null-terminated string,
 *  but those strings are not necessarily contiguous.
 *
 *  Since MS-DOS command lines are limited to 128 characters, this
 *  function limits the number of arguments to 64 separate strings.
 *
 * Parameters:
 *  psz             LPSTR to the string to parse.
 *
 * Return Value:
 *  HLOCAL          Local LMEM_FIXED memory handle containing the
 *                  list of LPSTRs to the list items.  NULL if memory
 *                  could not be allocated.
 */

HLOCAL WINAPI HListParse(LPSTR psz)
    {
    HLOCAL       hMem;
    LPSTR FAR   *ppsz;
    LPSTR        pszT;
    UINT         cp;

    //Allocate space for 64 pointers.
    hMem=LocalAlloc(LPTR, 64*sizeof(LPSTR));

    if (NULL==hMem)
        return NULL;

    ppsz=(LPSTR FAR *)(PSTR)hMem;
    cp=0;

    /*
     * For each string, scan for whitespace, save that pointer in
     * ppsz, and null-terminate that string.  If it was already
     * null-terminated, then there are no more pieces in the list.
     */

    while (0!=*psz)
        {
        //Skip to beginning of first item.
        psz=PszWhiteSpaceScan(psz, TRUE);

        //If it's a zero, stop here.
        if (0==*psz)
            break;

        //Find the end of this item.
        pszT=PszWhiteSpaceScan(psz, FALSE);

        //Null terminate this string and point to next character.
        if (0!=*pszT)
            *pszT++=0;

        //Save this string pointer.
        *ppsz++=psz;
        cp++;

        //Check our limit of 64.
        if (64 <= cp)
            break;

        //Check next item.
        psz=pszT;
        }

    return hMem;
    }






/*
 * PszWhiteSpaceScan
 *
 * Purpose:
 *  Skips characters in a string until a whitespace or non-whitespace
 *  character is seen.  Whitespace is defined as \n, \r, \t, or ' '.
 *
 * NOTE:  This function is not extremely well suited to localization.
 *        It assumes that an existing application seeking to become
 *        and OLE server probably already has such a string function
 *        available.
 *
 * Parameters:
 *  psz             LPSTR to string to manipulate
 *  fSkip           BOOL  TRUE if we want to skip whitespace.
 *                  FALSE if we want to skip anything but whitespace.
 *
 * Return Value:
 *  LPSTR           Pointer to first character in the string that either
 *                  non-whitespace (fSkip=TRUE) or whitespace (fSkip=FALSE),
 *                  which may be the null terminator.
 */

LPSTR PASCAL PszWhiteSpaceScan(LPSTR psz, BOOL fSkip)
    {
    char        ch;
    BOOL        fWhite;

    while (ch=*psz)
        {
        fWhite=('\n'==ch || '\r'==ch || '\t'==ch || ' '==ch);

        //Too bad C doesn't have a logical XOR (^^) operator.
        if ((fSkip && !fWhite) || (!fSkip && fWhite))
            break;

        psz++;
        }

    return psz;
    }
