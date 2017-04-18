/*
 * OLECLIP.C
 *
 * Routines to handle placing Native, ObjectLink, and OwnerLink
 * information on the clipboard.
 *
 * Copyright(c) Microsoft Corp. 1992-1994 All Rights Reserved
 * Win32 version, January 1994
 */


#ifdef MAKEOLESERVER

#include <windows.h>
#include <ole.h>
#include "cosmo.h"
#include "oleglobl.h"



/*
 * FOLECopyNative
 *
 * Purpose:
 *  Allocates a memory block for Native data and places it on the clipboard,
 *  assuming that the application has opened the clipboard.
 *
 * Parameters:
 *  pOLE            LPXOLEGLOBALS containing clipboard formats.
 *
 * Return Value:
 *  BOOL            TRUE if the data was copied, FALSE otherwise.
 */

BOOL WINAPI FOLECopyNative(LPXOLEGLOBALS pOLE)
    {
    HGLOBAL      hMem;

    hMem=HGetPolyline(pGlob->hWndPolyline);

    //Place Native data on clipboard.
    if (NULL==hMem)
        return FALSE;

    SetClipboardData(pOLE->cfNative, hMem);
    return TRUE;
    }




/*
 * FOLECopyLink
 *
 * Purpose:
 *  Places ObjectLink OR OwnerLink information on the clipboard.
 *  This function assumes that the application already has the
 *  clipboard open.
 *
 * Parameters:
 *  pOLE            LPXOLEGLOBALS containing clipboard formats.
 *  fOwnerLink      BOOL indicating to set OwnerLink (TRUE)/ObjectLink (FALSE)
 *  pszDoc          LPSTR to the document name.
 *
 * Return Value:
 *  BOOL            TRUE if copying to the clipboard was successful.
 *                  FALSE on any failure.
 */

BOOL WINAPI FOLECopyLink(LPXOLEGLOBALS pOLE, BOOL fOwnerLink, LPSTR pszDoc)
    {
    HGLOBAL         hMem;
    OLECLIPFORMAT   cf;

    //Retrieve a handle to the OwnerLink/ObjectLink format.
    hMem=HLinkConstruct(rgpsz[IDS_CLASSCOSMO], pszDoc, rgpsz[IDS_FIGURE]);

    if (NULL==hMem)
        return FALSE;

    //Set one or the other format.
    cf=(fOwnerLink) ? (pOLE->cfOwnerLink) : (pOLE->cfObjectLink);
    hMem=SetClipboardData(cf, hMem);

    return (NULL!=hMem);
    }






/*
 * HLinkConstruct
 *
 * Purpose:
 *  Builds an ObjectLink and OwnerLink text string for OLE clipboard
 *  interaction in the format of "classname\0document\0object\0\0"
 *
 * Parameters:
 *  pszClass        LPSTR to the classname.
 *  pszDoc          LPSTR to the document name.
 *  pszObj          LPSTR to the object name.
 *
 * Return Value:
 *  HGLOBAL         Global memory handle to an block containing
 *                  the three strings with the appropriate separator.
 */

HGLOBAL WINAPI HLinkConstruct(LPSTR pszClass, LPSTR pszDoc, LPSTR pszObj)
    {
    HGLOBAL     hMem;
    UINT        cch1, cch2, cch3;
    LPSTR       psz;

    if (NULL==pszClass || NULL==pszDoc || NULL==pszObj)
        return NULL;

    //We'll need lengths later.
    cch1=lstrlen(pszClass);
    cch2=lstrlen(pszDoc);
    cch3=lstrlen(pszObj);

    //Extra 4 is for the null-terminators.
    hMem=GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, (DWORD)(4+cch1+cch2+cch3));

    if (NULL==hMem)
        return NULL;

    psz=GlobalLock(hMem);

    lstrcpy(psz, pszClass);
    psz+=cch1+1;

    lstrcpy(psz, pszDoc);
    psz+=cch2+1;

    lstrcpy(psz, pszObj);
    *(psz+cch3+1)=0;        //Add the final null terminator.

    GlobalUnlock(hMem);
    return hMem;
    }




#endif //MAKEOLESERVER
