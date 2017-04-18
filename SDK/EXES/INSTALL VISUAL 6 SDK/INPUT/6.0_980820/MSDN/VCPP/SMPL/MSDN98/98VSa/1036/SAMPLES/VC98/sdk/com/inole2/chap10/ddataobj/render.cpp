/*
 * RENDER.CPP
 * Data Object Chapter 10
 *
 * CDataObject::Render* functions to create text, bitmaps, and
 * metafiles in a variety of sizes.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "dataobj.h"
#include <string.h>


/*
 * CDataObject::RenderText
 *
 * Purpose:
 *  Creates a global memory block containing the letter 'k' of sizes
 *  of 64 bytes, 1024 bytes, and 16384 bytes, into a caller-supplied
 *  STGMEDIUM.
 *
 * Parameters:
 *  pSTM            LPSTGMEDIUM in which to render.
 *
 * Return Value:
 *  HRESULT         Return value for GetData
 */

HRESULT CDataObject::RenderText(LPSTGMEDIUM pSTM)
    {
    DWORD       cch;
    HGLOBAL     hMem;
    LPTSTR      psz;
    UINT        i;

    //Get the size of data we're dealing with
    switch (m_iSize)
        {
        case DOSIZE_SMALL:
            cch=CCHTEXTSMALL;
            break;

        case DOSIZE_MEDIUM:
            cch=CCHTEXTMEDIUM;
            break;

        case DOSIZE_LARGE:
            cch=CCHTEXTLARGE;
            break;

        default:
            return ResultFromScode(E_FAIL);
        }

    hMem=GlobalAlloc(GMEM_SHARE | GMEM_MOVEABLE, cch*sizeof(TCHAR));

    if (NULL==hMem)
        return ResultFromScode(STG_E_MEDIUMFULL);

    psz=(LPTSTR)GlobalLock(hMem);

    for (i=0; i < cch-1; i++)
        *(psz+i)=TEXT(' ') + (i % 32);

    *(psz+i)=0;

    GlobalUnlock(hMem);

    pSTM->hGlobal=hMem;
    pSTM->tymed=TYMED_HGLOBAL;
    pSTM->pUnkForRelease=NULL;
    return NOERROR;
    }




/*
 * CDataObject::RenderBitmap
 *
 * Purpose:
 *  Creates a new bitmap into which we copy a bitmap loaded
 *  from our resources.
 *
 * Parameters:
 *  pSTM            LPSTGMEDIUM in which to render.
 *
 * Return Value:
 *  HRESULT         Return value for GetData
 */

HRESULT CDataObject::RenderBitmap(LPSTGMEDIUM pSTM)
    {
    HBITMAP     hBmp, hBmpT;
    UINT        cxy;
    HDC         hDC, hDCSrc, hDCDst;

    //Get the size of bitmap we're dealing with
    switch (m_iSize)
        {
        case DOSIZE_SMALL:
            cxy=CXYBITMAPSMALL;
            break;

        case DOSIZE_MEDIUM:
            cxy=CXYBITMAPMEDIUM;
            break;

        case DOSIZE_LARGE:
            cxy=CXYBITMAPLARGE;
            break;

        default:
            return ResultFromScode(E_FAIL);
        }

    //Get two memory DCs between which to BitBlt.
    hDC=GetDC(NULL);
    hDCSrc=CreateCompatibleDC(hDC);
    hDCDst=CreateCompatibleDC(hDC);
    ReleaseDC(NULL, hDC);

    if (NULL==hDCSrc || NULL==hDCDst)
        {
        if (NULL!=hDCDst)
            DeleteDC(hDCDst);

        if (NULL!=hDCSrc)
            DeleteDC(hDCSrc);

        return ResultFromScode(STG_E_MEDIUMFULL);
        }

    SelectObject(hDCSrc, m_rghBmp[m_iSize-DOSIZE_SMALL]);

    hBmp=CreateCompatibleBitmap(hDCSrc, cxy, cxy);

    if (NULL==hBmp)
        {
        DeleteDC(hDCDst);
        DeleteDC(hDCSrc);

        return ResultFromScode(STG_E_MEDIUMFULL);
        }

    //Copy from the source to destination
    hBmpT=(HBITMAP)SelectObject(hDCDst, hBmp);
    BitBlt(hDCDst, 0, 0, cxy, cxy, hDCSrc, 0, 0, SRCCOPY);
    SelectObject(hDCDst, hBmpT);

    DeleteDC(hDCDst);
    DeleteDC(hDCSrc);

    pSTM->hGlobal=(HGLOBAL)hBmp;
    pSTM->tymed=TYMED_GDI;
    pSTM->pUnkForRelease=NULL;
    return NOERROR;
    }






/*
 * CDataObject::RenderMetafilePict
 *
 * Purpose:
 *  Creates a metafile containing blue shaded bands.
 *
 * Parameters:
 *  pSTM            LPSTGMEDIUM in which to render.
 *
 * Return Value:
 *  HRESULT         Return value for GetData
 */

HRESULT CDataObject::RenderMetafilePict(LPSTGMEDIUM pSTM)
    {
    HDC             hDC;
    HGLOBAL         hMem;
    HMETAFILE       hMF;
    LPMETAFILEPICT  pMF;
    HBRUSH          hBrush;
    HGDIOBJ         hBrT;
    UINT            cRec;
    int             x, y, dxy;
    RECT            rc;

    switch (m_iSize)
        {
        case DOSIZE_SMALL:
            cRec=CRECMETAFILESMALL;
            break;

        case DOSIZE_MEDIUM:
            cRec=CRECMETAFILEMEDIUM;
            break;

        case DOSIZE_LARGE:
            cRec=CRECMETAFILELARGE;
            break;

        default:
            return ResultFromScode(E_FAIL);
        }


    hDC=(HDC)CreateMetaFile(NULL);

    if (NULL!=hDC)
        {
        /*
         * Draw something into the metafile.  For this object we
         * draw some number of rectangles equal to the number of
         * records we want.  So take the square root of the number
         * of records and iterate over that number in both x & y.
         */

        dxy=(int)1024/cRec;


        //This creates a blue shading from light to dark
        for (y=1024; y >=0; y-=dxy)
            {
            hBrush=CreateSolidBrush(RGB(0, 0, (1024-y)/4));
            hBrT=SelectObject(hDC, (HGDIOBJ)hBrush);

            for (x=0; x < 1024; x+=dxy)
                {
                SetRect(&rc, x, y, x+dxy, y+dxy);
                FillRect(hDC, &rc, hBrush);
                }

            SelectObject(hDC, hBrT);
            DeleteObject(hBrush);
            }

        hMF=CloseMetaFile(hDC);
        }

    if (NULL==hMF)
        return ResultFromScode(STG_E_MEDIUMFULL);

    //Allocate the METAFILEPICT structure.
    hMem=GlobalAlloc(GMEM_SHARE | GMEM_MOVEABLE
        , sizeof(METAFILEPICT));

    if (NULL==hMem)
        {
        DeleteMetaFile(hMF);
        return ResultFromScode(STG_E_MEDIUMFULL);
        }

    pMF=(LPMETAFILEPICT)GlobalLock(hMem);

    pMF->hMF=hMF;
    pMF->mm=MM_ANISOTROPIC;
    pMF->xExt=1024;
    pMF->yExt=1024;

    GlobalUnlock(hMem);

    pSTM->hGlobal=hMem;
    pSTM->tymed=TYMED_MFPICT;
    pSTM->pUnkForRelease=NULL;
    return NOERROR;
    }
