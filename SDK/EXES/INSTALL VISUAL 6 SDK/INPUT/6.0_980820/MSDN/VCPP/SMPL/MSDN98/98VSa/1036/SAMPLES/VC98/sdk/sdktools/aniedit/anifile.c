/****************************************************************************\
*
*     MODULE: anifile.c
*
*     PURPOSE: Processes files for the Animated Cursor Editor
*
*     Copyright 1993-1996 Microsoft Corp.
*
*
* History:
*   21-Apr-1993 JonPa   Wrote it.
*
\****************************************************************************/

#include <windows.h>
#include <commdlg.h>
#include "anidefs.h"

/****************************************************************************\
*
*     FUNCTION: BOOL CreateFrameFromCursorFile( LPSTR pszFile )
*
*     PURPOSE:  Opens a cursor file, reads the icon info out of it,
*               and creates a frame and step for that icon, then links
*               everything together and updates the listbox.
*
*     NOTES:    This function accesses the global flag gfEditFrame.
*               If this bool is TRUE, then the currently selected frame
*               in the listbox is overwritten.  If it is false, then
*               a new frame is created and inserted after the currently
*               selected frame (or at the end if no selection).
*
* History:
*   21-Apr-1993 JonPa   Created it
*
\****************************************************************************/
BOOL CreateFrameFromCursorFile(HWND hwnd,  LPTSTR pszFile, BOOL fEdit) {
    PFRAME pf;
    HANDLE hf;
    PSTEP psOld, psNew;
    DWORD ckSize;
    int iSel;
    int cSel;

    cSel = GetSelStepCount(hwnd);

    if ( (fEdit && (cSel != 1)) || cSel > 1) {
        FmtMessageBox( hwnd, TITL_ERROR, NULL, MB_OK | MB_ICONSTOP,
                TRUE, fEdit ? MSG_MUSTEQONEFAME : MSG_LESSEQONEFRAME);
        return FALSE;
    }

    /* get currently selected frame */
    GetCurrentSel(hwnd, DLG_MAIN_FRAMELIST, &iSel, 1, &cSel );

    if (cSel == 0)
        psOld = NULL;
    else
        psOld = GetStep(hwnd, iSel);

    /*
     * If not editing, create a new step
     */
    if (!fEdit || !IsValidPS(psOld)) {
        psNew = NewStep();

        if (psNew == NULL) {
            return FALSE;
        }
    } else {
        psNew = NULL;
    }

    hf = CreateFile(pszFile, GENERIC_READ,
             0, NULL,
             OPEN_EXISTING,
             FILE_ATTRIBUTE_NORMAL,
             NULL);

    if (hf == INVALID_HANDLE_VALUE)
        return FALSE;

    ckSize = GetFileSize(hf, NULL);

    /* get the frame out of the file */
    pf = ReadIconFromFile(hwnd, hf, ckSize);
    CloseHandle(hf);

    if (pf == NULL) {
        if (psNew != NULL)
            FreeMem(psNew);
        return FALSE;
    }

    if (psNew != NULL) {

        if (IsValidPS(psOld)) {
            psNew->jif = psOld->jif;
            iSel += 1;
        } else {
            psNew->jif = ganiAcon.anih.jifRate;
            iSel = SendDlgItemMessage(hwnd, DLG_MAIN_FRAMELIST, LB_GETCOUNT,
                    0, 0);
        }

        LinkStepFrame(psNew, pf);

        SendDlgItemMessage(hwnd, DLG_MAIN_FRAMELIST, LB_INSERTSTRING, iSel,
            (LPARAM)psNew);

        SetCurrentSel(hwnd, DLG_MAIN_FRAMELIST, FALSE, iSel);

    } else {
        HWND hwndLB = GetDlgItem(hwnd, DLG_MAIN_FRAMELIST);

        /*
         * Delete the old frame and point the step to the new one.
         */
        LinkStepFrame(psOld, pf);

        InvalidateRect(hwndLB, NULL, TRUE);
    }

    return TRUE;
}


/****************************************************************************\
*
*     FUNCTION: HICON ConvertDataToIcon( PFRAME pf )
*
*     PURPOSE:
*
*
*
*
* History:
*   23-Apr-1993 JonPa   copied from Win NT USERs ReadIconGuts
*
\****************************************************************************/
HICON ConvertDataToIcon( PFRAME pf, WORD *pxHotSave, WORD *pyHotSave )
{
    NEWHEADER *pnh;
    NEWHEADER *pnhBase;
    RESDIR *prd;
    int offMatch;
    ICONFILERESDIR *pird;
    PCURSORRESOURCE pcres;
    BOOL fIcon;
    HICON hicon;
    WORD x, y;
    LPBYTE pbBits;

    pnhBase = (NEWHEADER *)pf->abIcon;

    /*
     * Construct a fake array of RESDIR entries using the info at the head
     * of the file.  Store the data offset in the idIcon WORD so it can be
     * returned by RtlGetIdFromDirectory.
     */
    pnh = (NEWHEADER *)LocalAlloc(LMEM_FIXED, sizeof(NEWHEADER) +
            (pnhBase->cResources * sizeof(RESDIR)));
    if (pnh == NULL)
        return NULL;

    *pnh = *pnhBase;
    prd = (RESDIR *)(pnh + 1);
    pird = (ICONFILERESDIR *)(pnhBase + 1);

    /* prime pird for first line of loop */
    pird--;

    for (offMatch = 0; offMatch < (int)pnh->cResources; offMatch++, prd++) {

        /*
         * Get the next resource directory from the icon file.
         */

        ++pird;

        /*
         * Convert from the icon editor's resource directory format
         * to the post-RC.EXE format LookupIconIdFromDirectory expects.
         */
        if (pnh->rt == 1) {     // ICON
            prd->ResInfo.Icon.Width = pird->bWidth;
            prd->ResInfo.Icon.Height = pird->bHeight;
            prd->ResInfo.Icon.ColorCount = pird->bColorCount;
            prd->ResInfo.Icon.reserved = 0;
        } else {                // CURSOR
            prd->ResInfo.Cursor.Width = pird->bWidth;
            prd->ResInfo.Cursor.Height = pird->bHeight;
        }
        prd->Planes = 0;                // Hopefully nobody uses this
        prd->BitCount = 0;              //        "        "
        prd->BytesInRes = pird->dwDIBSize;
        prd->idIcon = (WORD)pird->dwDIBOffset;
    }

    /*
     * NOTE: nh.rt is NOT an RT_ type value.  For instance, nh.rt == 1 for
     * an icon file where as 1 == RT_CURSOR, not RT_ICON.
     */

    fIcon = (pnhBase->rt == 1);
    offMatch = LookupIconIdFromDirectory((PBYTE)pnh, fIcon);

    LocalFree(pnh);

    if (fIcon) {
        pcres = (PCURSORRESOURCE)&(pf->abIcon[offMatch]);
        *pxHotSave = gcxCursor / 2;
        *pyHotSave = gcyCursor / 2;
    } else {

        offMatch -= (sizeof(pcres->xHotspot) + sizeof(pcres->yHotspot));

        for(; pird->dwDIBOffset != (WORD)offMatch &&
                pird != (ICONFILERESDIR *)(pnhBase + 1); pird--);

        pcres = (PCURSORRESOURCE)&(pf->abIcon[offMatch]);

        x = pcres->xHotspot;
        y = pcres->yHotspot;
        *pxHotSave = pcres->xHotspot = pird->xHotspot;
        *pyHotSave = pcres->yHotspot = pird->yHotspot;
    }


    // Buffer must be aligned
    pbBits = LocalAlloc(LMEM_FIXED, pf->rtag.ckSize - offMatch );
    if (pbBits) {
        CopyMemory( pbBits, pcres, pf->rtag.ckSize - offMatch );

        hicon = CreateIconFromResource( pbBits,
                pf->rtag.ckSize - offMatch, fIcon, 0x00030000);

        LocalFree( pbBits );
    } else
        hicon = NULL;

    if(!fIcon) {
        pcres->xHotspot = x;
        pcres->yHotspot = y;
    }

    return hicon;
}




/****************************************************************************\
*
*     FUNCTION: PFRAME ReadIconFromFile(HWND hwnd, HANDLE hf, DWORD ckSize)
*
*     PURPOSE:  Reads the icon info out of a file,
*               and creates a frame for that icon.
*
*
* History:
*   22-Apr-1993 JonPa   Created it
*
\****************************************************************************/
PFRAME ReadIconFromFile(HWND hwnd, HANDLE hf, DWORD ckSize) {
    PFRAME pf = AllocMem( sizeof( FRAME ) + ckSize );
    DWORD cbRead;
    PFRAME pfList;

    if (pf != NULL) {
        pf->cRef = 0;

        if (ReadFile(hf, pf->abIcon, ckSize, &cbRead, NULL) &&
                cbRead == ckSize) {
            /* got the data, now set up the rest of the frame and link it in */
            pf->dwCheckSum = CalcCheckSum( pf->abIcon, ckSize );
            pf->rtag.ckID = FOURCC_icon;
            pf->rtag.ckSize = ckSize;

            /* Check if this fram is already in the list */
            for (pfList = gpfrmFrames; pfList != NULL;
                    pfList = pfList->pfrmNext ) {
                if (pf->dwCheckSum == pfList->dwCheckSum &&
                        pf->rtag.ckSize == pfList->rtag.ckSize &&
                        memcmp( pf->abIcon, pfList->abIcon, ckSize ) == 0) {
                    /*
                     * These frames are the same, coalesce them into a
                     * sequence.
                     */
                    FreeMem(pf);
                    pf = pfList;
                    break;
                }
            }

            if (pfList == NULL) {
                /*
                 * Did not find a dup, create an icon for this frame
                 */
                pf->hcur = ConvertDataToIcon( pf, &(pf->xHotSpot),
                        &(pf->yHotSpot) );

                pf->pfrmNext = gpfrmFrames;
                gpfrmFrames = pf;
            }

        } else {
            /* File Error */
            FreeMem(pf);
            pf = NULL;
        }

    }

    return pf;
}

/****************************************************************************\
*
*     FUNCTION: HANDLE PromptAndOpenFile( )
*
*     PURPOSE:  Pust up the standard open dialog and then opens the file
*
*
*
*
* History:
*   21-Apr-1993 JonPa   Created it
*
\****************************************************************************/
HANDLE PromptAndOpenFile(
    HWND hwnd,
    DWORD  cchFileTitle,
    LPTSTR pszFileTitle,
    DWORD  cchFileName,
    LPTSTR pszFileName,
    LPTSTR pszFilter
    )
{
    HANDLE hf = INVALID_HANDLE_VALUE;

    if (PromptForFile( hwnd, cchFileTitle, pszFileTitle, cchFileName,
                pszFileName, pszFilter, NULL, FALSE )) {

        /* Open the file. */

        hf = CreateFile(pszFileName, GENERIC_READ,
                0, NULL,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                NULL);

        if (hf == INVALID_HANDLE_VALUE) {
            FmtMessageBox( hwnd, TITL_ERROR, NULL, MB_OK | MB_ICONSTOP, TRUE,
                MSG_CANTOPENFILE, pszFileName );
        }
    }

    return hf;
}


/****************************************************************************\
*
*     FUNCTION: HANDLE PromptForFile( )
*
*     PURPOSE:  Pust up the standard open dialog
*
*
*
*
* History:
*   28-Apr-1993 JonPa   Created it from PromptAndOpenFile
*
\****************************************************************************/
BOOL PromptForFile(
    HWND hwnd,
    DWORD  cchFileTitle,
    LPTSTR pszFileTitle,
    DWORD  cchFileName,
    LPTSTR pszFile,
    LPTSTR pszFilter,
    LPTSTR pszDlgTitle,
    BOOL fSave
    )
{
    OPENFILENAME ofn;

    ZeroMemory(&ofn, sizeof(ofn));

    /* Set the members of the OPENFILENAME structure. */

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hwnd;

    ofn.lpstrFilter = pszFilter;
    ofn.nFilterIndex = 0;

    ofn.lpstrFile = pszFile;
    ofn.nMaxFile = cchFileName;

    ofn.lpstrFileTitle = pszFileTitle;
    ofn.nMaxFileTitle = cchFileTitle;

    ofn.lpstrTitle = pszDlgTitle;

    ofn.lpstrDefExt = gpszANI;

    if (fSave) {
        ofn.Flags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
    } else {
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    }

    /* Display the SaveAs or Open dialog box. */

    return fSave ? GetSaveFileName(&ofn) : GetOpenFileName(&ofn);

}

/****************************************************************************\
*
*     FUNCTION: BOOL ReadAniFile( HWND hwnd, HANDLE hf ) {
*
*     PURPOSE:
&
*   Loads an animatied cursor from a RIFF file.  The RIFF file format for
*   animated cursors looks like this:
*
*   RIFF( 'ACON'
*       LIST( 'INFO'
*           INAM( <name> )
*           IART( <artist> )
*       )
*       anih( <anihdr> )
*       [rate( <rateinfo> )  ]
*       ['seq '( <seq_info> )]
*       LIST( 'fram' icon( <icon_file> ) )
*   )
*
*
* History:
*   02-Oct-1991 DarrinM     Created. (in Win32 user)
*   17-Mar-1993 JonPa       Rewrote to use RIFF format instead of RAD
*   21-Apr-1993 JonPa       Copied it to anifile.c and tweeked it.
*
\****************************************************************************/
BOOL ReadAniFile( HWND hwnd, HANDLE hf ) {

    RTAG tag;
    DWORD cbRead;
    BOOL fSuccess = FALSE;
    JIF *pjifRate = NULL;
    DWORD *pseq = NULL;
    PFRAME *ppfram = NULL;
    int iFrame = 0;
    int i;

    if (!ReadTag(hf, &tag))
        goto laiFileErr;

    /*
     * Make sure it's a RIFF ANI file
     */
    if (tag.ckID != FOURCC_RIFF)
        goto laiFileErr;

    /* read the chunk type */
    if(!ReadFile(hf, &tag.ckID, sizeof(tag.ckID), &cbRead, NULL) ||
            cbRead < sizeof(tag.ckID)) {
        goto laiFileErr;
    }

    if (tag.ckID != FOURCC_ACON)
        goto laiFileErr;

    /* look for 'anih', 'rate', 'seq ', and 'icon' chunks */
    while( ReadTag(hf, &tag)) {

        switch( tag.ckID ) {
        case FOURCC_anih:
            if (!ReadChunk(hf, &tag, &ganiAcon.anih))
                goto laiFileErr;

            if (!(ganiAcon.anih.fl & AF_ICON) || (ganiAcon.anih.cFrames == 0))
                goto laiFileErr;

            /*
             * Allocate space for the ANIHEADER, and a seq and
             * rate table (in case we run into one later).
             */

            pjifRate = AllocMem( ganiAcon.anih.cSteps * sizeof(JIF) +
                    ganiAcon.anih.cSteps * sizeof(DWORD) +
                    ganiAcon.anih.cSteps * sizeof(PFRAME));


            if (pjifRate == NULL)
                goto laiFileErr;

            pseq = (DWORD *)(pjifRate + ganiAcon.anih.cSteps);
            ppfram = (PFRAME *)(pseq + ganiAcon.anih.cSteps);

            for( i = 0; i < (int)ganiAcon.anih.cSteps; i++ ) {
                pjifRate[i] = ganiAcon.anih.jifRate;
                pseq[i] = i;
                ppfram[i] = NULL;
            }
            break;


        case FOURCC_rate:
            /*
             * If we find a rate chunk, read it into its preallocated
             * space.
             */
            if(!ReadChunk(hf, &tag, (PBYTE)pjifRate))
                goto laiFileErr;
            break;


        case FOURCC_seq:
            /*
             * If we find a seq chunk, read it into its preallocated
             * space.
             */
            if(!ReadChunk(hf, &tag, (PBYTE)pseq))
                goto laiFileErr;
            break;


        case FOURCC_LIST: {
            DWORD cbChunk = PADUP(tag.ckSize);

            /*
             * See if this list is the 'fram' list of icon chunks
             */
            if(!ReadFile(hf, &tag.ckID, sizeof(tag.ckID), &cbRead, NULL) ||
                    cbRead < sizeof(tag.ckID)) {
                goto laiFileErr;
            }

            cbChunk -= cbRead;

            if (tag.ckID == FOURCC_fram) {

                while(cbChunk >= sizeof(tag)) {
                    if (!ReadTag(hf, &tag))
                        goto laiFileErr;

                    cbChunk -= sizeof(tag);

                    if(tag.ckID == FOURCC_icon) {
                        PFRAME pfrm;

                        /*
                         * Ok, load the icon/cursor bits,
                         */
                        pfrm = ReadIconFromFile(hwnd, hf, tag.ckSize);

                        if (pfrm == NULL) {
                            goto laiFileErr;
                        }

                        for( i = 0; i < (int)ganiAcon.anih.cSteps; i++ ) {
                            if (pseq[i] == (DWORD)iFrame) {
                                ppfram[i] = pfrm;
                            }
                        }

                        iFrame++;

                    } else {
                        /*
                         * Unknown chunk in fram list, just ignore it
                         */
                        SkipChunk(hf, &tag);
                    }

                    cbChunk -= PADUP(tag.ckSize);
                }
            } else if (tag.ckID == FOURCC_INFO) {
                /* now look for INAM and IART chunks */

                while( cbChunk >= sizeof(tag) ) {

                    if (!ReadTag(hf, &tag))
                        goto laiFileErr;

                    cbChunk -= sizeof(tag);

                    switch( tag.ckID ) {
                    case FOURCC_INAM:
                        if (cbChunk < tag.ckSize ||
                                !ReadChunkN(hf, &tag, ganiAcon.azTitle,
                                                sizeof(ganiAcon.azTitle)))
                            goto laiFileErr;

                        cbChunk -= PADUP(tag.ckSize);
                        break;

                    case FOURCC_IART:
                        if (cbChunk < tag.ckSize ||
                                !ReadChunkN(hf, &tag, ganiAcon.azCreator,
                                        sizeof(ganiAcon.azCreator)))
                            goto laiFileErr;

                        cbChunk -= PADUP(tag.ckSize);
                        break;

                    default:
                        if (!SkipChunk( hf, &tag ))
                            goto laiFileErr;

                        cbChunk -= PADUP(tag.ckSize);
                        break;
                    }
                }

            } else {
                /*
                 * Not the fram list or the INFO list.  Skip
                 * the rest of this chunk.  (Don't forget that we have
                 * already skipped one dword!)
                 */
                tag.ckSize = cbChunk;
                SkipChunk(hf, &tag);
                break;
            }

            break;
        }



        default:
            /*
             * We're not interested in this chunk, skip it.
             */
            if(!SkipChunk(hf, &tag))
                goto laiFileErr;
            break;

        }

    }

    /*
     * Update the frame count incase we coalesced some frames while reading
     * in the file.
     */
    ganiAcon.anih.cFrames = iFrame;

    /*
     * Now build up the listbox
     */

    for( i = 0; i < (int)ganiAcon.anih.cSteps; i++ ) {
        PSTEP ps;

        ps = NewStep();
        if (ps == NULL)
            goto laiFileErr;

        ps->jif = pjifRate[i];
        LinkStepFrame(ps, ppfram[i]);

        SendDlgItemMessage(hwnd, DLG_MAIN_FRAMELIST, LB_INSERTSTRING, i,
                (LPARAM)ps);
    }

    SetDlgItemText(hwnd, DLG_MAIN_TITLE, ganiAcon.azTitle);
    SetDlgItemText(hwnd, DLG_MAIN_AUTHOR, ganiAcon.azCreator);

    SendDlgItemMessage(hwnd, DLG_MAIN_PREVIEW, PM_NEWCURSOR, 0, 0);
    fSuccess = TRUE;

laiFileErr:

    if (pjifRate != NULL)
        FreeMem(pjifRate);

    if (!fSuccess)
        NewAniCursor(hwnd);

    CloseHandle(hf);

    return fSuccess;
}



/***************************************************************************\
* DWORD CalcCheckSum( PBYTE pb );
*
*
* History:
*
* 23-Apr-1993 JonPa     Created.
\***************************************************************************/
DWORD CalcCheckSum( PBYTE pb, DWORD cb ) {
    DWORD dw = 0;

    while(cb--)
        dw += (DWORD)*pb++;

    return dw;
}

/***************************************************************************\
* ReadTag, ReadChunk, SkipChunk
*
* Some handy functions for reading RIFF files.
*
* History:
* 10-02-91 DarrinM      Created.
* 03-25-93 Jonpa        Changed to use RIFF format instead of ASDF
* 23-Apr-1993 JonPa     Copied from Win NT USER.
\***************************************************************************/
BOOL ReadTag(
    HANDLE hf,
    PRTAG ptag)
{
    DWORD cbActual;

    ptag->ckID = ptag->ckSize = 0L;

    if (!ReadFile(hf, ptag, sizeof(RTAG), &cbActual, NULL) ||
            (cbActual != sizeof(RTAG)))
        return FALSE;

    /* no need to align file pointer since RTAG is already word aligned */
    return TRUE;
}


BOOL ReadChunk(
    HANDLE hf,
    PRTAG ptag,
    PVOID pv)
{
    DWORD cbActual;

    if (!ReadFile(hf, pv, ptag->ckSize, &cbActual, NULL) ||
            (cbActual != ptag->ckSize))
        return FALSE;

    /* WORD align file pointer */
    if( ptag->ckSize & 1 )
        SetFilePointer(hf, 1, NULL, FILE_CURRENT);

    return TRUE;
}


BOOL ReadChunkN(
    HANDLE hf,
    PRTAG ptag,
    PVOID pv,
    DWORD cbMax)
{
    DWORD cbActual;
    DWORD cbRead = min( cbMax, ptag->ckSize );

    if (!ReadFile(hf, pv, ptag->ckSize, &cbActual, NULL) ||
            (cbActual != cbRead))
        return FALSE;

    /* WORD align file pointer */

    cbRead = ptag->ckSize - cbActual;

    if( ptag->ckSize & 1 )
        cbRead++;

    return SetFilePointer(hf, cbRead, NULL, FILE_CURRENT) != 0xFFFFFFFF;
}

BOOL SkipChunk(
    HANDLE hf,
    PRTAG ptag)
{
    /* Round ptag->ckSize up to nearest word boundary to maintain alignment */
    return SetFilePointer(hf, PADUP(ptag->ckSize), NULL, FILE_CURRENT) !=
            0xFFFFFFFFL;
}

/****************************************************************************\
*
*     FUNCTION: VOID GetTempCursorFileName( szFileName );
*
*     PURPOSE:  Create a temporary .cur filename
*
*
* History:
*   22-Apr-1993 JonPa   Created it
*
\****************************************************************************/
BOOL GetTempCursorFileName( LPTSTR pszName ) {
    TCHAR szPath[MAX_PATH];

    if( GetTempPath( MAX_PATH, szPath ) >= MAX_PATH )
        lstrcpy( pszName, TEXT(".") );


    return GetTempFileName(szPath, TEXT("ae"), 0, pszName) != 0;
}

/****************************************************************************\
*
*     FUNCTION: BOOL SaveAniFile( HWND hwnd, HANDLE hf )
*
*     PURPOSE:
&
*   Saves an animatied cursor to a RIFF file.  The RIFF file format for
*   animated cursors looks like this:
*
*   RIFF( 'ACON'
*       [LIST( 'INFO'
*           [INAM( <name> )]
*           [IART( <artist> )]
*       )]
*       anih( <anihdr> )
*       [rate( <rateinfo> )  ]
*       ['seq '( <seq_info> )]
*       LIST( 'fram' icon( <icon_file> ) )
*   )
*
*
* History:
*   29-Apr-1993 JonPa   Created it.
*
\****************************************************************************/
BOOL SaveAniFile( HWND hwnd, HANDLE hf ) {
    int cSteps, i;
    int cFrames;
    PFRAME pf;
    DWORD cbFile, cbFram, cbINFO, cbTitle, cbAuthor;
    BOOL fRate, fSeq;
    RTAG rtag;
    PJIF pjif;
    DWORD *pseq;
    PFRAME *pfrm;

    fRate = fSeq = FALSE;
    cbINFO = cbFram = cbFile = cbTitle = cbAuthor = 0;

    PausePreview(hwnd, DLG_MAIN_PREVIEW);

    cSteps = GetStepCount(hwnd);

    if( cSteps == LB_ERR ) {
        FmtMessageBox( ghwndMain, TITL_ERROR, NULL, MB_OK | MB_ICONSTOP,
                TRUE, MSG_OUTOFRESOUCES );
        return FALSE;
    }

    cFrames = 0;
    for( pf = gpfrmFrames; pf != NULL; pf = pf->pfrmNext ) {
        pf->iFrame = -1;
        cFrames++;
    }

    ganiAcon.anih.cSteps = cSteps;

    pjif = AllocMem( (sizeof(JIF) + sizeof(DWORD) + sizeof(PFRAME)) * cSteps );

    if(pjif == NULL)
        return FALSE;

    pseq = (DWORD *)&pjif[cSteps];
    pfrm = (PFRAME *)&pseq[cSteps];

    cFrames = 0;

    for( i = 0; i < cSteps; i++ ) {
        PSTEP ps;

        ps = GetStep(hwnd, i);

        if( IsValidPS(ps) ) {

            if (ps->pfrmFrame->iFrame == -1) {

                cbFram += sizeof(RTAG);
                cbFram += PADUP(ps->pfrmFrame->rtag.ckSize);

                ps->pfrmFrame->iFrame = cFrames;
                pfrm[cFrames++] = ps->pfrmFrame;

            } else
                fSeq = TRUE;

            pseq[i] = ps->pfrmFrame->iFrame;

            if ((pjif[i] = ps->jif) != ganiAcon.anih.jifRate) {
                fRate = TRUE;
            }
        }
    }

    ganiAcon.anih.cbSizeof = sizeof(ganiAcon.anih);
    ganiAcon.anih.cFrames = cFrames;
    ganiAcon.anih.fl = AF_ICON | (fSeq ? AF_SEQUENCE : 0);

    cbTitle = GetDlgItemTextA(hwnd, DLG_MAIN_TITLE, ganiAcon.azTitle,
                            COUNTOF(ganiAcon.azTitle));

    cbAuthor = GetDlgItemTextA(hwnd, DLG_MAIN_AUTHOR, ganiAcon.azCreator,
                            COUNTOF(ganiAcon.azCreator));

    /*
     * At this point, cbFram == the size required by all the frames,
     * add in the rate, seq, anih, and INFO list sizes as well as
     * all the other overhead.
     */

    cbFram += sizeof(FOURCC);     //fram type

    cbFile = cbFram;

    cbFile += sizeof(FOURCC) +    //ACON type
                    sizeof(RTAG) +      //anih tag
                        PADUP(sizeof(ANIHEADER)) +
                    sizeof(RTAG);       //LIST tag (for fram list)


    if( cbTitle || cbAuthor) {
        /*
         * Remember, azCreator, and azTitle are ANSI strings!
         */
        if( cbTitle ) {
            cbTitle += 1; //add in ASCIIZ terminator
            cbINFO +=   sizeof(RTAG) +     //INAM tag
                        PADUP( cbTitle * sizeof(char));
        }

        if (cbAuthor) {
            cbAuthor += 1; //add in ASCIIZ terminator
            cbINFO +=   sizeof(RTAG) +     //IART tag
                        PADUP(cbAuthor * sizeof(char));
        }

        cbINFO +=  sizeof(FOURCC);      //INFO type

        cbFile +=   sizeof(RTAG) +      //LIST tag
                    cbINFO;
    }


    if (fSeq) {
        cbFile += sizeof(RTAG) +    //seq tag
                    PADUP(cSteps * sizeof(DWORD));
    }

    if (fRate) {
        cbFile += sizeof(RTAG) +    //rate tag
                    PADUP(cSteps * sizeof(JIF));
    }

    /*
     * Now we have all the structures built in memory, it's time to
     * write them out in RIFF ACON format!
     */
    rtag.ckID = FOURCC_RIFF;
    rtag.ckSize = cbFile;

    RET_CLOSE_IF_ERR( WriteTag(hf, &rtag), hf );

    RET_CLOSE_IF_ERR( WriteType(hf, FOURCC_ACON), hf );

    if( cbTitle || cbAuthor) {
        rtag.ckID = FOURCC_LIST;
        rtag.ckSize = cbINFO;

        RET_CLOSE_IF_ERR( WriteTag(hf, &rtag), hf );

        RET_CLOSE_IF_ERR( WriteType(hf, FOURCC_INFO), hf );

        if (cbTitle) {
            rtag.ckID = FOURCC_INAM;
            rtag.ckSize = cbTitle;
            RET_CLOSE_IF_ERR( WriteTagData(hf, &rtag, ganiAcon.azTitle), hf );
        }

        if (cbAuthor) {
            rtag.ckID = FOURCC_IART;
            rtag.ckSize = cbAuthor;
            RET_CLOSE_IF_ERR( WriteTagData(hf, &rtag, ganiAcon.azCreator), hf );
        }
    }

    /* write anih */
    rtag.ckID = FOURCC_anih;
    rtag.ckSize = sizeof(ganiAcon.anih);

    RET_CLOSE_IF_ERR( WriteTagData(hf, &rtag, &(ganiAcon.anih)), hf );

    /* if rate then write it */
    if (fRate) {
        rtag.ckID = FOURCC_rate;
        rtag.ckSize = cSteps * sizeof(JIF);

        RET_CLOSE_IF_ERR( WriteTagData(hf, &rtag, pjif), hf );
    }

    /* if seq, then write it */
    if (fSeq) {
        rtag.ckID = FOURCC_seq;
        rtag.ckSize = cSteps * sizeof(DWORD);

        RET_CLOSE_IF_ERR( WriteTagData(hf, &rtag, pseq), hf );
    }

    /* write the fram list */
    rtag.ckID = FOURCC_LIST;
    rtag.ckSize = cbFram;

    RET_CLOSE_IF_ERR( WriteTag(hf, &rtag), hf );
    RET_CLOSE_IF_ERR( WriteType(hf, FOURCC_fram), hf );

    for( i = 0; i < cFrames; i++ ) {
        RET_CLOSE_IF_ERR( WriteTagData(hf, &(pfrm[i]->rtag), pfrm[i]->abIcon),
                hf);
    }

    /* Close the file */
    CloseHandle(hf);

    return TRUE;
}


/***************************************************************************\
* WriteTag, WriteType, WriteTagData
*
* Some handy functions for writing RIFF files.
*
* History:
*   30-Apr-1993 JonPa   Created them.
\***************************************************************************/
BOOL WriteTag(HANDLE hf, PRTAG prtag) {
    DWORD cbWritten;

    return (WriteFile(hf, prtag, sizeof(RTAG), &cbWritten, NULL) &&
            cbWritten == sizeof(RTAG));
}

BOOL WriteType(HANDLE hf, FOURCC ckID ) {
    DWORD cbWritten;

    return (WriteFile(hf, &ckID, sizeof(FOURCC), &cbWritten, NULL) &&
            cbWritten == sizeof(FOURCC));
}

BOOL WriteTagData(HANDLE hf, PRTAG prtag, VOID *pvData ) {
    DWORD cbWritten;
    DWORD cbWrite = PADUP(prtag->ckSize);

    return  WriteTag(hf, prtag) && WriteFile(hf, pvData, cbWrite,
            &cbWritten, NULL) && cbWritten == cbWrite;
}




/***************************************************************************\
* VOID SaveFile(HWND hwnd, BOOL fPrompt)
*
* Conditionally Prompt the user for a name and then save the file
*
* History:
*   04-May-1993 JonPa   It
\***************************************************************************/
VOID SaveFile(HWND hwnd, BOOL fPrompt) {
    TCHAR szFileTitle[MAX_PATH];
    HANDLE hf;

    szFileTitle[0] = TEXT('\0');

    if (fPrompt || ganiAcon.szFile[0] == TEXT('\0')) {
tryagain:
        if (!PromptForFile(hwnd, COUNTOF(szFileTitle), szFileTitle,
                COUNTOF(ganiAcon.szFile), ganiAcon.szFile, gpszAniFilter,
                NULL, TRUE)) {
            return;
        }
    }

    hf = CreateFile( ganiAcon.szFile, GENERIC_WRITE, 0, NULL,
            CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hf == INVALID_HANDLE_VALUE) {
        FmtMessageBox(hwnd, TITL_ERROR, NULL, MB_OK | MB_ICONSTOP, TRUE,
                MSG_CANTCREATEFILE, ganiAcon.szFile);

        goto tryagain;
    }

    if( !SaveAniFile(hwnd, hf) ) {
        FmtMessageBox(hwnd, TITL_ERROR, NULL, MB_OK | MB_ICONSTOP, TRUE,
                MSG_FILEWRITEERR, ganiAcon.szFile);
        return;
    }

    if (szFileTitle[0] != TEXT('\0'))
        SetWindowFileTitle(hwnd, szFileTitle);

    ganiAcon.fDirty = FALSE;
}
