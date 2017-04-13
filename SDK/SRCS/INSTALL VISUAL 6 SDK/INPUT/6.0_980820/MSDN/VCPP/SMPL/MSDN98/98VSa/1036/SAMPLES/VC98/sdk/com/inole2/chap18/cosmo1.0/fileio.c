/*
 * FILEIO.C
 *
 * Functions for low-level reading and writing of .COS files.
 *
 * Functions:
 *  FCosFileRead, FCosFileWrite
 *
 * Copyright(c) Microsoft Corp. 1992-1994 All Rights Reserved
 * Win32 version, January 1994
 */

#include <windows.h>
#include "cosmo.h"


/*
 * FCosFileRead
 *
 * Purpose:
 *  Reads a Cos file into the POLYLINE structure pointed to by lppl.
 *  Clears pGlob->fDirty on success.
 *
 * Parameters:
 *  pGlob           LPGLOBALS to the global variable block.
 *  pszFile         LPSTR of the filename to read.
 *  lppl            LPPOLYLINE to the structure to fill.
 *
 * Return Value:
 *  BOOL            TRUE if the file was successfully read,
 *                  FALSE otherwise.
 */

BOOL WINAPI FCosFileRead(LPGLOBALS pGlob, LPSTR pszFile, LPPOLYLINE lppl)
    {
    int         hFile;
    OFSTRUCT    of;
    UINT        cb;

    hFile=OpenFile(pszFile, &of, OF_READ);

    if (-1==hFile)
        return FALSE;

    cb=_lread(hFile, (LPSTR)lppl, CBPOLYLINE);
    _lclose(hFile);

    if (CBPOLYLINE==cb && VERSIONMAJOR==lppl->wVerMaj
        && VERSIONMINOR==lppl->wVerMin)
        {
        pGlob->fDirty=FALSE;
        return TRUE;
        }

    return FALSE;
    }




/*
 * FCosFileWrite
 *
 * Purpose:
 *  Writes a Cos file into the POLYLINE structure pointed to by lppl.
 *  Clears pGlob->fDirty.
 *
 * Parameters:
 *  pGlob           LPGLOBALS to the global variable block.
 *  pszFile         LPSTR of the filename to read.
 *  lppl            LPPOLYLINE to the structure to write from.
 *
 * Return Value:
 *  BOOL            TRUE if the file was successfully written,
 *                  FALSE otherwise.
 */

BOOL WINAPI FCosFileWrite(LPGLOBALS pGlob, LPSTR pszFile, LPPOLYLINE lppl)
    {
    int         hFile;
    OFSTRUCT    of;
    UINT        cb;

    hFile=OpenFile(pszFile, &of, OF_CREATE | OF_WRITE);

    if (-1==hFile)
        return FALSE;

    cb=_lwrite(hFile, (LPSTR)lppl, CBPOLYLINE);
    _lclose(hFile);

    if (CBPOLYLINE==cb)
        {
        pGlob->fDirty=FALSE;
        return TRUE;
        }

    return FALSE;
    }
