/*
 * POLYLINE.CPP
 * Cosmo Chapter 21
 *
 * Implementation of the CPolyline class.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "cosmo.h"


/*
 * CPolyline:CPolyline
 * CPolyline::~CPolyline
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE of the application we're in.
 */

CPolyline::CPolyline(HINSTANCE hInst)
    : CWindow(hInst)
    {
    m_pAdv=NULL;
    m_hWnd=NULL;
    m_fReadFromOLE10=FALSE;
    return;
    }


CPolyline::~CPolyline(void)
    {
    return;
    }





/*
 * CPolyline::Init
 *
 * Purpose:
 *  Instantiates a polyline window within a given parent.  The
 *  parent may be a main application window, could be an MDI child
 *  window. We really do not care.
 *
 * Parameters:
 *  hWndParent      HWND of the parent of this window
 *  pRect           LPRECT that this window should occupy
 *  dwStyle         DWORD containing the window's style flags
 *  uID             UINT ID to associate with this window
 *  pAdv            PCPolylineAdviseSink of the sink wanting our
 *                  notifications.
 *
 * Return Value:
 *  BOOL            TRUE if the function succeeded, FALSE otherwise.
 */

BOOL CPolyline::Init(HWND hWndParent, LPRECT pRect, DWORD dwStyle
    , UINT uID, PCPolylineAdviseSink pAdv)
    {
    m_hWnd=CreateWindowEx(WS_EX_NOPARENTNOTIFY, SZCLASSPOLYLINE
        , SZCLASSPOLYLINE, dwStyle, pRect->left, pRect->top
        , pRect->right-pRect->left, pRect->bottom-pRect->top
        , hWndParent, (HMENU)uID, m_hInst, this);

    if (NULL!=m_hWnd)
        m_pAdv=pAdv;

    return (NULL!=m_hWnd);
    }







/*
 * CPolyline::New
 *
 * Purpose:
 *  Cleans out and reinitializes the data to defaults.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CPolyline::New(void)
    {
    UINT        i;
    RECT        rc;

    m_pl.wVerMaj=VERSIONMAJOR;
    m_pl.wVerMin=VERSIONMINOR;

    //Our rectangle is the size of our window's client area.
    GetClientRect(m_hWnd, &rc);
    RECTTORECTS(rc, m_pl.rc);

    //Clean out the POLYLINE structure and repaint the window.
    for (i=0; i< CPOLYLINEPOINTS; i++)
        {
        m_pl.rgpt[i].x=0;
        m_pl.rgpt[i].y=0;
        }

    m_pl.cPoints      =0;
    m_pl.rgbBackground=GetSysColor(COLOR_WINDOW);
    m_pl.rgbLine      =GetSysColor(COLOR_WINDOWTEXT);
    m_pl.iLineStyle   =PS_SOLID;

    InvalidateRect(m_hWnd, NULL, TRUE);
    UpdateWindow(m_hWnd);

    //Inform the advise sink of this data change.
    if (NULL!=m_pAdv)
        m_pAdv->OnDataChange();

    return;
    }




/*
 * CPolyline::Undo
 *
 * Purpose:
 *  Reverses previous actions in a Polyline.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if we can Undo more, FALSE otherwise.
 */

BOOL CPolyline::Undo(void)
    {
    //Decrement the number of active points and repaint.
    if (m_pl.cPoints > 0)
        {
        m_pl.cPoints--;
        InvalidateRect(m_hWnd, NULL, TRUE);
        UpdateWindow(m_hWnd);
        }

    if (NULL!=m_pAdv)
        m_pAdv->OnPointChange();

    //Return if we can undo any more.
    return (0!=m_pl.cPoints);
    }





/*
 * CPolyline::ReadFromStorage
 *
 * Purpose:
 *  Loads our data (any known version) from an IStorage returning
 *  the version number of the data or an error value.
 *
 * Parameters:
 *  pIStorage       LPSTORAGE from which we'll read.
 *
 * Return Value:
 *  LONG            Version number or negative POLYLINE_E_* value.
 */

LONG CPolyline::ReadFromStorage(LPSTORAGE pIStorage)
    {
    LONG            lRet;
    LPSTREAM        pIStream;
    HRESULT         hr;

    if (NULL==pIStorage)
        return POLYLINE_E_READFAILURE;

    //Open the CONTENTS stream
    hr=pIStorage->OpenStream(SZSTREAM, 0, STGM_DIRECT | STGM_READ
        | STGM_SHARE_EXCLUSIVE, 0, &pIStream);

    if (FAILED(hr))
        return POLYLINE_E_READFAILURE;

    /*
     * Since we had to create ReadFromStream for IPersistStorage,
     * use it ourselves.
     */
    lRet=ReadFromStream(pIStream);
    pIStream->Release();

    return lRet;
    }




/*
 * CPolyline::WriteToStorage
 *
 * Purpose:
 *  Ignorantly writes our current data into a storage in a
 *  particular version.
 *
 * Parameters:
 *  pIStorage       LPSTORAGE in which to save.
 *  lVer            LONG providing version number Major (HI) and
 *                  Minor (Low)
 *
 * Return Value:
 *  LONG            A POLYLINE_E_* value.
 */

LONG CPolyline::WriteToStorage(LPSTORAGE pIStorage, LONG lVer)
    {
    LONG            lRet;
    LPSTREAM        pIStream;
    HRESULT         hr;

    if (NULL==pIStorage)
        return POLYLINE_E_READFAILURE;

    hr=pIStorage->CreateStream(SZSTREAM, STGM_DIRECT | STGM_CREATE
        | STGM_WRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &pIStream);

    if (FAILED(hr))
        return POLYLINE_E_WRITEFAILURE;

    /*
     * Use our function that will save to a stream now that
     * we needed it for IPersistStorage.
     */

    lRet=WriteToStream(pIStream, lVer);
    pIStream->Release();

    return lRet;
    }




/*
 * CPolyline::ReadFromStream
 *
 * Purpose:
 *  Loads our data (any known version) from an IStream that we
 *  do not open nor maintain.  This is for the compound document
 *  object's implementation of IPersistStorage.
 *
 * Parameters:
 *  pIStream        LPSTREAM from which we'll read.
 *
 * Return Value:
 *  LONG            Version number or negative POLYLINE_E_* value.
 */

LONG CPolyline::ReadFromStream(LPSTREAM pIStream)
    {
    POLYLINEDATA    pl;
    ULONG           cb=(ULONG)-1;
    ULONG           cbExpect=0;
    HRESULT         hr;
    LARGE_INTEGER   li;

    if (NULL==pIStream)
        return POLYLINE_E_READFAILURE;

    /*
     * If IPersistStorage::Load failed to find CONTENTS but did
     * open "\1Ole10Native" then m_fReadFromOLE10 is set.  So
     * we have to start reading past the leading DWORD.
     */

    if (m_fReadFromOLE10)
        {
        DWORD       dw;

        /*
         * Skip the DWORD length at the beginning of the
         * Ole10Native stream.
         */
        pIStream->Read(&dw, sizeof(DWORD), &cb);
        }


    //Read version numbers and seek back to file beginning.
    hr=pIStream->Read(&pl, 2*sizeof(WORD), &cb);

    //If we read OLE 1, seek back but skip the size header.
    LISet32(li, m_fReadFromOLE10 ? sizeof(DWORD) : 0);
    pIStream->Seek(li, STREAM_SEEK_SET, NULL);

    if (FAILED(hr) || 2*sizeof(WORD)!=cb)
        {
        pIStream->Release();
        return POLYLINE_E_READFAILURE;
        }

    /*
     * For version 2.0, read the entire file.  For version 1.0 read
     * the file up to CBPOLYLINEDATAVER10.  For anything else, give
     * an error.
     */

    switch (pl.wVerMaj)
        {
        case VERSIONMAJOR:  //2.x
            switch (pl.wVerMin)
                {
                case VERSIONMINOR:  //2.0
                    cbExpect=CBPOLYLINEDATA;
                    break;

                default:
                    break;
                }
            break;

        case 1: //1.x
            switch (pl.wVerMin)
                {
                case 0:  //1.0
                    cbExpect=CBPOLYLINEDATA10;
                    break;

                default:
                    break;
                }
            break;

        default:
            break;
        }

    if (0==cbExpect)
        return POLYLINE_E_UNSUPPORTEDVERSION;

    hr=pIStream->Read(&pl, cbExpect, &cb);

    if (cbExpect!=cb)
        return POLYLINE_E_READFAILURE;

    /*
     * If we loaded successfully, make the data current.  By using
     * DataSet we centralize our version upgrading.  We size the
     * polyline window to the data AND notify the document so it
     * sizes to the polyline.
     */
    DataSet(&pl, TRUE, TRUE);

    //Return what version we just loaded.
    return MAKELONG(pl.wVerMin, pl.wVerMaj);
    }




/*
 * CPolyline::WriteToStream
 *
 * Purpose:
 *  Ignorantly writes our current data into a stream in a
 *  particular version.
 *
 * Parameters:
 *  pIStream        LPSTREAM in which to save.
 *  lVer            LONG providing version number Major (HI) and
 *                  Minor (Low)
 *
 * Return Value:
 *  LONG            A POLYLINE_E_* value.
 */

LONG CPolyline::WriteToStream(LPSTREAM pIStream, LONG lVer)
    {
    ULONG           cb;
    ULONG           cbExpect=0;
    WORD            wVerMaj=HIWORD(lVer);
    WORD            wVerMin=LOWORD(lVer);
    POLYLINEDATA    pl;
    HRESULT         hr;

    if (NULL==pIStream)
        return POLYLINE_E_READFAILURE;

    //Get a copy of our data in the version we're going to save.
    DataGet(&pl, lVer);

    switch (wVerMaj)
        {
        case VERSIONMAJOR:  //2.x
            switch (wVerMin)
                {
                case VERSIONMINOR:  //2.0
                    cbExpect=CBPOLYLINEDATA;
                    break;

                default:
                    break;
                }
            break;

        case 1: //1.x
            switch (wVerMin)
                {
                case 0:  //1.0
                    cbExpect=CBPOLYLINEDATA10;
                    break;

                default:
                    break;
                }
            break;

        default:
            break;
        }

    if (0==cbExpect)
        return POLYLINE_E_UNSUPPORTEDVERSION;

    /*
     * If writing to an OLE 1 storage, include the length of
     * data as the first DWORD in the stream.
     */

     if (m_fReadFromOLE10 && CBPOLYLINEDATA10==cbExpect)
        {
        hr=pIStream->Write(&cbExpect, sizeof(DWORD), &cb);

        if (FAILED(hr) || sizeof(DWORD)!=cb)
            return POLYLINE_E_WRITEFAILURE;
        }

    hr=pIStream->Write(&pl, cbExpect, &cb);

    if (FAILED(hr) || cbExpect!=cb)
        return POLYLINE_E_WRITEFAILURE;

    return POLYLINE_E_NONE;
    }







/*
 * CPolyline::ReadFromFile
 *
 * Purpose:
 *  Loads our data (any known version) from a file handle returning
 *  the version number of the data or an error value.
 *
 * Parameters:
 *  pszFile         LPTSTR of the file to open.
 *
 * Return Value:
 *  LONG            Version number or negative POLYLINE_E_* value.
 */

LONG CPolyline::ReadFromFile(LPTSTR pszFile)
    {
    OFSTRUCT        of;
    HFILE           hFile;
    POLYLINEDATA    pl;
    UINT            cb=(UINT)-1;
    UINT            cbExpect=0;

    if (NULL==pszFile)
        return POLYLINE_E_READFAILURE;

    //OpenFileW is a member of CPolyline.
    hFile=OpenFileW(pszFile, &of, OF_READ);

    if (HFILE_ERROR==hFile)
        return POLYLINE_E_READFAILURE;

    //Read version numbers and seek back to file beginning.
    cb=_lread(hFile, &pl, 2*sizeof(WORD));
    _llseek(hFile, 0L, 0);

    if (2*sizeof(WORD)!=cb)
        {
        _lclose(hFile);
        return POLYLINE_E_READFAILURE;
        }

    /*
     * For version 2.0, read the entire file.  For version 1.0 read
     * the file up to CBPOLYLINEDATAVER10.  For anything else, give
     * an error.
     */

    switch (pl.wVerMaj)
        {
        case VERSIONMAJOR:  //2.x
            switch (pl.wVerMin)
                {
                case VERSIONMINOR:  //2.0
                    cbExpect=CBPOLYLINEDATA;
                    break;

                default:
                    break;
                }
            break;

        case 1: //1.x
            switch (pl.wVerMin)
                {
                case 0:  //1.0
                    cbExpect=CBPOLYLINEDATA10;
                    break;

                default:
                    break;
                }
            break;

        default:
            break;
        }

    if (0==cbExpect)
        {
        _lclose(hFile);
        return POLYLINE_E_UNSUPPORTEDVERSION;
        }

    cb=_lread(hFile, &pl, cbExpect);
    _lclose(hFile);

    if (cbExpect!=cb)
        return POLYLINE_E_READFAILURE;

    /*
     * If we loaded successfully, make the data current.  By using
     * DataSet we centralize our version upgrading.  We size the
     * polyline window to the data AND notify the document so it
     * sizes to the polyline.
     */
    DataSet(&pl, TRUE, TRUE);

    //Return what version we just loaded.
    return MAKELONG(pl.wVerMin, pl.wVerMaj);
    }






/*
 * CPolyline::WriteToFile
 *
 * Purpose:
 *  Ignorantly writes our current data into an opened file in a
 *  particular version.
 *
 * Parameters:
 *  pszFile         LPTSTR filename in which to store the data.
 *  lVer            LONG providing version number Major (HI)
 *                  and Minor (Low)
 *
 * Return Value:
 *  LONG            A POLYLINE_E_* value.
 */

LONG CPolyline::WriteToFile(LPTSTR pszFile, LONG lVer)
    {
    OFSTRUCT        of;
    HFILE           hFile;
    UINT            cb;
    UINT            cbExpect=0;
    WORD            wVerMaj=HIWORD(lVer);
    WORD            wVerMin=LOWORD(lVer);
    POLYLINEDATA    pl;

    if (NULL==pszFile)
        return POLYLINE_E_READFAILURE;

    //Get a copy of our data in the version we're going to save.
    DataGet(&pl, lVer);

    switch (wVerMaj)
        {
        case VERSIONMAJOR:  //2.x
            switch (wVerMin)
                {
                case VERSIONMINOR:  //2.0
                    cbExpect=CBPOLYLINEDATA;
                    break;

                default:
                    break;
                }
            break;

        case 1: //1.x
            switch (wVerMin)
                {
                case 0:  //1.0
                    cbExpect=CBPOLYLINEDATA10;
                    break;

                default:
                    break;
                }
            break;

        default:
            break;
        }

    if (0==cbExpect)
        return POLYLINE_E_UNSUPPORTEDVERSION;

    hFile=OpenFileW(pszFile, &of, OF_CREATE | OF_WRITE);

    if (HFILE_ERROR==hFile)
        return DOCERR_COULDNOTOPEN;

    cb=_lwrite(hFile, (LPCSTR)&pl, cbExpect);
    _lclose(hFile);

    return (cbExpect==cb) ? POLYLINE_E_NONE
        : POLYLINE_E_WRITEFAILURE;
    }






/*
 * CPolyline::OpenFileW (Private)
 *
 * Purpose:
 *  Under Win32, OpenFile does not take Unicode strings.  This
 *  function converts a Unicode string into an ANSI string and
 *  calls OpenFile.  This just maps to OpenFile without Unicode.
 *
 * Parameters, Return Value:
 *  Same as OpenFile.
 */

HFILE CPolyline::OpenFileW(LPTSTR pszFile, LPOFSTRUCT pof
    , UINT uFlags)
    {
   #ifdef UNICODE
    CHAR        szTemp[CCHPATHMAX];

    UNICODETOANSI(pszFile, szTemp, CCHPATHMAX);
    return OpenFile(szTemp, pof, uFlags);
   #else
    return OpenFile(pszFile, pof, uFlags);
   #endif
    }







/*
 * CPolyline::DataSet
 *
 * Purpose:
 *  Sets the current data in this Polyline to a given structure.
 *
 * Parameters:
 *  ppl             PPOLYLINEDATA to initialize to.
 *  fSizeToData     BOOL indicating if we're to size to the data or
 *                  scale it.
 *  fNotify         BOOL indicating if we're to send an advise on
 *                  this change.
 *
 * Return Value:
 *  LONG            A POLYLINE_E_* value.
 */

LONG CPolyline::DataSet(PPOLYLINEDATA ppl, BOOL fSizeToData
    , BOOL fNotify)
    {
    RECTS       rcs;
    RECT        rc;
    UINT        i;

    /*
     * Copy the structure in ppl and repaint to reflect the new
     * point set.  Note that unlike the RectSet message, we do no
     * scaling, assuming that the rect in the structure is
     * appropriate for the data.
     */

    if (NULL==ppl)
        return POLYLINE_E_INVALIDPOINTER;

    //Preserve the old rectangle
    rcs=m_pl.rc;

    /*
     * For version 2.0 we perform a straight copy.  For version
     * 1.0 we copy the 1.0 structure and fill in defaults for
     * the 2.0 additions.
     */

    switch (ppl->wVerMaj)
        {
        case VERSIONMAJOR:          //2.x
            switch (ppl->wVerMin)
                {
                case VERSIONMINOR:  //2.0
                    m_pl=*ppl;
                    break;

                default:
                    return POLYLINE_E_UNSUPPORTEDVERSION;
                }
            break;

        case 1:                     //1.x
            switch (ppl->wVerMin)
                {
                case 0:             //1.0
                    *((PPOLYLINEDATA10)&m_pl)=
                        *((PPOLYLINEDATA10)ppl);

                    /*
                     * Update this structure to 2.0.  Note that we
                     * assume whoever loaded us to save the loaded
                     * version so it can later ask what version
                     * the user wants to save.
                     */
                    m_pl.wVerMaj=VERSIONMAJOR;
                    m_pl.wVerMin=VERSIONMINOR;

                    /*
                     * Version 1.0 stored rc in parent coordinates.
                     * We need those now in our client coodinates.
                     */
                    RECTSTORECT(m_pl.rc, rc);
                    OffsetRect(&rc, -m_pl.rc.left, -m_pl.rc.top);

                    /*
                     * 1.0 data had points relative to size of the
                     * rectangle.  We need to scale these to 0-32767
                     * independent of the rectangle for the version
                     * upgrade.
                     */
                    for (i=0; i < m_pl.cPoints; i++)
                        PointScale(&rc, &m_pl.rgpt[i], FALSE);

                    RECTTORECTS(rc, m_pl.rc);

                    //New 2.0 features
                    m_pl.rgbBackground=GetSysColor(COLOR_WINDOW);
                    m_pl.rgbLine=GetSysColor(COLOR_WINDOWTEXT);
                    m_pl.iLineStyle=PS_SOLID;
                    break;

                default:
                    return POLYLINE_E_UNSUPPORTEDVERSION;
                }
            break;

        default:
            return POLYLINE_E_UNSUPPORTEDVERSION;
        }


    //Inform our parent of the data change
    if (NULL!=m_pAdv)
        m_pAdv->OnDataChange();

    /*
     * If we're scaling the window to fit the data, then use
     * RectSet passing our current rectangle as the new one.
     * That makes sure that the data won't change but that the
     * window is resized.
     */

    if (fSizeToData)
        {
        POINT       pt;

        /*
         * Get our offset in the parent window so we can RectSet
         * to the right place since RectSet expects rectangle in
         * parent coordinates and we get it in client coordinates.
         */
        GetWindowRect(m_hWnd, &rc);
        pt.x=rc.left;
        pt.y=rc.top;
        ScreenToClient(GetParent(m_hWnd), &pt);
        RECTSTORECT(m_pl.rc, rc);
        OffsetRect(&rc, pt.x, pt.y);

        //This will also cause a repaint.
        RectSet(&rc, fNotify);
        }
    else
        {
        //Make sure we're updated.
        InvalidateRect(m_hWnd, NULL, TRUE);
        UpdateWindow(m_hWnd);
        }

    return POLYLINE_E_NONE;
    }







/*
 * CPolyline::DataGet
 *
 * Purpose:
 *  Retrieves the Polyline's current data.
 *
 * Parameters:
 *  ppl             PPOLYLINEDATA into which we copy the data.
 *  lVer            LONG version of the data to retrieve.  Use
 *                  VERSIONCURRENT to retrieve the most current.
 *
 * Return Value:
 *  LONG            A POLYLINE_E_* value
 */

LONG CPolyline::DataGet(PPOLYLINEDATA ppl, LONG lVer)
    {
    UINT        i;
    RECT        rc;

    //Retieve the current version
    if (lVer==MAKELONG(VERSIONMINOR, VERSIONMAJOR)
        || VERSIONCURRENT==lVer)
        {
        *ppl=m_pl;
        return POLYLINE_E_NONE;
        }

    //Check for versions we support, 1.x
    if (HIWORD(lVer)!=1)
        return POLYLINE_E_UNSUPPORTEDVERSION;

    if (LOWORD(lVer)==0)    //Check for 1.0
        {
        //Do 2.0 to 1.0 conversion
        *((PPOLYLINEDATA10)ppl)=*((PPOLYLINEDATA10)&m_pl);

        RECTSTORECT(ppl->rc, rc);

        //Get the parent coordinates of our rectangle
        if (!IsWindow(m_hWnd))
            OffsetRect(&rc, 8, 8); //This is always the offset.
        else
            RectGet(&rc);

        /*
         * 1.0 data has points relative to size of the rectangle.
         * We need to scale these from 0-32767 so we have the
         * right values.
         */
        for (i=0; i < ppl->cPoints; i++)
            PointScale(&rc, &ppl->rgpt[i], TRUE);

        RECTTORECTS(rc, ppl->rc);

        //Insure old version numbers.
        ppl->wVerMaj=1;
        ppl->wVerMin=0;

        ((PPOLYLINEDATA10)ppl)->fDrawEntire=TRUE;
        return POLYLINE_E_NONE;
        }

    return POLYLINE_E_UNSUPPORTEDVERSION;
    }








/*
 * CPolyline::DataSetMem
 *
 * Purpose:
 *  Sets the Polyline's data using a global memory handle
 *  instead of a pointer.
 *
 * Parameters:
 *  hMem            HGLOBAL containing the data.
 *  fFree           BOOL indicating if we're to free the data.
 *                  The memory will be freed regardless of any
 *                  error returned from here.
 *  fSizeToData     BOOL indicating if we're to size to the data
 *                  or scale it.
 *  fNotify         BOOL indicating if we're to send an advise
 *                  on this change.
 *
 * Return Value:
 *  LONG            A POLYLINE_E_* value.
 */

LONG CPolyline::DataSetMem(HGLOBAL hMem, BOOL fFree
    , BOOL fSizeToData, BOOL fNotify)
    {
    PPOLYLINEDATA   ppl;
    LONG            lRet=POLYLINE_E_INVALIDPOINTER;

    if (NULL!=hMem)
        {
        ppl=(PPOLYLINEDATA)GlobalLock(hMem);
        lRet=DataSet(ppl, fSizeToData, fNotify);

        GlobalUnlock(hMem);

        if (fFree)
            GlobalFree(hMem);
        }

    return lRet;
    }







/*
 * CPolyline::DataGetMem
 *
 * Purpose:
 *  Retrieves the Polyline's data in a global memory handle.
 *
 * Parameters:
 *  lVer            LONG version of data to retrieve.
 *  phMem           HGLOBAL * in which to store the handle.
 *
 * Return Value:
 *  LONG            A POLYLINE_E_* value.
 */

LONG CPolyline::DataGetMem(LONG lVer, HGLOBAL *phMem)
    {
    HGLOBAL         hMem;
    PPOLYLINEDATA   ppl;
    LONG            lRet;

    if (NULL==phMem)
        return POLYLINE_E_INVALIDPOINTER;

    hMem=GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE
        , CBPOLYLINEDATA);

    if (NULL!=hMem)
        {
        ppl=(PPOLYLINEDATA)GlobalLock(hMem);
        lRet=DataGet(ppl, lVer);
        GlobalUnlock(hMem);

        if (POLYLINE_E_NONE!=lRet)
            {
            GlobalFree(hMem);
            hMem=NULL;
            }
        }

    *phMem=hMem;
    return lRet;
    }







/*
 * CPolyline::RectGet
 *
 * Purpose:
 *  Returns the rectangle of the Polyline in parent coordinates.
 *
 * Parameters:
 *  pRect           LPRECT in which to return the rectangle.
 *
 * Return Value:
 *  None
 */

void CPolyline::RectGet(LPRECT pRect)
    {
    RECT        rc;
    POINT       pt;

    //Retrieve the size of our rectangle in parent coordinates.
    GetWindowRect(m_hWnd, &rc);
    pt.x=rc.left;
    pt.y=rc.top;
    ScreenToClient(GetParent(m_hWnd), &pt);

    SetRect(pRect, pt.x, pt.y, pt.x+(rc.right-rc.left)
        , pt.y+(rc.bottom-rc.top));

    return;
    }





/*
 * CPolyline::SizeGet
 *
 * Purpose:
 *  Retrieves the size of the Polyline in parent coordinates.
 *
 * Parameters:
 *  pRect           LPRECT in which to return the size.  The right
 *                  and bottom fields will contain the dimensions.
 *
 * Return Value:
 *  None
 */

void CPolyline::SizeGet(LPRECT pRect)
    {
    RectGet(pRect);
    return;
    }






/*
 * CPolyline::RectSet
 *
 * Purpose:
 *  Sets a new rectangle for the Polyline which sizes to fit.
 *
 * Parameters:
 *  pRect           LPRECT containing the new rectangle.
 *  fNotify         BOOL indicating if we're to notify anyone of
 *                  the change.
 *
 * Return Value:
 *  None
 */

void CPolyline::RectSet(LPRECT pRect, BOOL fNotify)
    {
    UINT        cx, cy;
    RECT        rc;

    //Scale the points from our current size to the new size
    cx=pRect->right-pRect->left;
    cy=pRect->bottom-pRect->top;

    SetWindowPos(m_hWnd, NULL, pRect->left, pRect->top
        , cx, cy, SWP_NOZORDER);

    SetRect(&rc, 0, 0, cx, cy);
    RECTTORECTS(rc, m_pl.rc);

    if (fNotify && NULL!=m_pAdv)
        m_pAdv->OnSizeChange();

    InvalidateRect(m_hWnd, NULL, TRUE);

    return;
    }







/*
 * CPolyline::SizeSet
 *
 * Purpose:
 *  Sets a new size for the Polyline which sizes to fit.
 *
 * Parameters:
 *  pRect           LPRECT containing the new rectangle.
 *  fNotify         BOOL indicating if we're to notify anyone of
 *                  the change.
 *
 * Return Value:
 *  None
 */

void CPolyline::SizeSet(LPRECT pRect, BOOL fNotify)
    {
    UINT        cx, cy;

    //Scale the points from our current size to the new size
    cx=pRect->right-pRect->left;
    cy=pRect->bottom-pRect->top;

    SetWindowPos(m_hWnd, NULL, 0, 0, (UINT)cx, (UINT)cy
        , SWP_NOMOVE | SWP_NOZORDER);

    if (fNotify && NULL!=m_pAdv)
        m_pAdv->OnSizeChange();

    InvalidateRect(m_hWnd, NULL, TRUE);

    return;
    }






/*
 * CPolyline::ColorSet
 *
 * Purpose:
 *  Changes for background or line color in the Polyline
 *
 * Parameters:
 *  iColor          UINT index of the color to change.
 *  cr              COLORREF new color to use.
 *
 * Return Value:
 *  COLORREF        Previous color for the index iColor.
 */

COLORREF CPolyline::ColorSet(UINT iColor, COLORREF cr)
    {
    COLORREF    crRet;

    switch (iColor)
        {
        case POLYLINECOLOR_BACKGROUND:
            crRet=m_pl.rgbBackground;
            m_pl.rgbBackground=cr;
            break;

        case POLYLINECOLOR_LINE:
            crRet=m_pl.rgbLine;
            m_pl.rgbLine=cr;
            break;
        }

    //If the color changed, repaint
    if (crRet!=cr)
        {
        if (NULL!=m_pAdv)
            m_pAdv->OnColorChange();

        InvalidateRect(m_hWnd, NULL, TRUE);
        UpdateWindow(m_hWnd);
        }

    return crRet;
    }







/*
 * CPolyline::ColorGet
 *
 * Purpose:
 *  Retrieves one of the colors currently in use by the Polyline.
 *
 * Parameters:
 *  iColor          UINT identifying the color of interest.
 *
 * Return Value:
 *  COLORREF        Current color for iColor.
 */

COLORREF CPolyline::ColorGet(UINT iColor)
    {
    COLORREF    crRet;

    crRet=(POLYLINECOLOR_BACKGROUND==iColor)
        ? m_pl.rgbBackground : m_pl.rgbLine;

    return crRet;
    }








/*
 * CPolyline::LineStyleSet
 *
 * Purpose:
 *  Changes the line style in use by the Polyline
 *
 * Parameters:
 *  iStyle          UINT style of the line to use.
 *
 * Return Value:
 *  UINT            Previous style.
 */

UINT CPolyline::LineStyleSet(UINT iStyle)
    {
    UINT        uRet=(UINT)m_pl.iLineStyle;

    //Validate the line style
    if (PS_SOLID==iStyle || PS_DASH==iStyle || PS_DOT==iStyle
        || PS_DASHDOT==iStyle || PS_DASHDOTDOT==iStyle)
        {
        m_pl.iLineStyle=iStyle;

        if (uRet!=(UINT)m_pl.iLineStyle)
            {
            if (NULL!=m_pAdv)
                m_pAdv->OnLineStyleChange();

            InvalidateRect(m_hWnd, NULL, TRUE);
            UpdateWindow(m_hWnd);
            }
        }

    return uRet;
    }







/*
 * CPolyline::LineStyleGet
 *
 * Purpose:
 *  Retrieves the current line style in use in the Polyline
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  UINT            Current line style.
 */

UINT CPolyline::LineStyleGet(void)
    {
    return m_pl.iLineStyle;
    }






/*
 * CPolyline::RenderBitmap
 *
 * Purpose:
 *  Creates a bitmap image of the current Polyline.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HBITMAP         Handle to the newly rendered bitmap.
 */

HBITMAP CPolyline::RenderBitmap(void)
    {
    HDC         hDC;
    HDC         hMemDC;
    HBITMAP     hBmp;
    RECT        rc;
    HGDIOBJ     hObj;

    //Render a bitmap the size of the current rectangle.
    hDC=GetDC(m_hWnd);
    hMemDC=CreateCompatibleDC(hDC);

    GetClientRect(m_hWnd, &rc);
    hBmp=CreateCompatibleBitmap(hDC, rc.right, rc.bottom);

    if (NULL!=hBmp)
        {
        //Draw the POLYLINEDATA into the bitmap.
        hObj=SelectObject(hMemDC, hBmp);
        Draw(hMemDC, FALSE, TRUE);
        SelectObject(hMemDC, hObj);
        }

    DeleteDC(hMemDC);
    ReleaseDC(m_hWnd, hDC);

    return hBmp;
    }







/*
 * CPolyline::RenderMetafile
 *
 * Purpose:
 *  Renders the current image of the Polyline into a metafile.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HMETAFILE       Handle to the newly created metafile.
 */

HMETAFILE CPolyline::RenderMetafile(void)
    {
    HDC         hDC;
    HMETAFILE   hMF;
    RECT        rc;

    //Create a memory metafile and return its handle.
    hDC=(HDC)CreateMetaFile(NULL);
    hMF=NULL;

    if (NULL!=hDC)
        {
        /*
         * This is absolutely essential to the metafile so it
         * can be scaled in the clipboard and any destination
         * application.
         */
        SetMapMode(hDC, MM_ANISOTROPIC);
        GetClientRect(m_hWnd, &rc);
        SetWindowOrgEx(hDC, 0, 0, NULL);
        SetWindowExtEx(hDC, rc.right, rc.bottom, NULL);

        Draw(hDC, TRUE, TRUE);
        hMF=CloseMetaFile(hDC);
        }

    return hMF;
    }






/*
 * CPolyline::RenderMetafilePict
 *
 * Purpose:
 *  Renders the current Polyline into a METAFILEPICT structure in
 *  global memory.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HGLOBAL         Memory containing the METAFILEPICT structure.
 */

HGLOBAL CPolyline::RenderMetafilePict(void)
    {
    HGLOBAL         hMem;
    HMETAFILE       hMF;
    LPMETAFILEPICT  pMF;
    RECT            rc;


    //Get the metafile
    hMF=RenderMetafile();

    if (NULL==hMF)
        return NULL;

    //Allocate the METAFILEPICT structure.
    hMem=GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE
        , sizeof(METAFILEPICT));

    if (NULL==hMem)
        {
        DeleteMetaFile(hMF);
        return NULL;
        }

    /*
     * Global lock only fails in PMODE if the selector is invalid
     * (like it was discarded) or references a 0 length segment,
     * neither of which can happen here.
     */
    pMF=(LPMETAFILEPICT)GlobalLock(hMem);

    pMF->hMF=hMF;
    pMF->mm=MM_ANISOTROPIC;

    //Insert the extents in MM_HIMETRIC units.
    GetClientRect(m_hWnd, &rc);
    RectConvertMappings(&rc, FALSE);
    pMF->xExt=rc.right;
    pMF->yExt=rc.bottom;

    GlobalUnlock(hMem);
    return hMem;
    }






/*
 * CPolyline::RectConvertMappings
 *
 * Purpose:
 *  Converts the contents of a rectangle from device (MM_TEXT) or
 *  HIMETRIC to the other.
 *
 * Parameters:
 *  pRect           LPRECT containing the rectangle to convert.
 *  fToDevice       BOOL TRUE to convert from HIMETRIC to device,
 *                  FALSE to convert device to HIMETRIC.
 *
 * Return Value:
 *  None
 */

void CPolyline::RectConvertMappings(LPRECT pRect, BOOL fToDevice)
    {
    HDC      hDC;
    int      iLpx, iLpy;

    if (NULL==pRect)
        return;

    hDC=GetDC(NULL);
    iLpx=GetDeviceCaps(hDC, LOGPIXELSX);
    iLpy=GetDeviceCaps(hDC, LOGPIXELSY);
    ReleaseDC(NULL, hDC);

    if (fToDevice)
        {
        pRect->left=MulDiv(iLpx, pRect->left, HIMETRIC_PER_INCH);
        pRect->top =MulDiv(iLpy, pRect->top , HIMETRIC_PER_INCH);

        pRect->right=MulDiv(iLpx, pRect->right,  HIMETRIC_PER_INCH);
        pRect->bottom=MulDiv(iLpy, pRect->bottom,HIMETRIC_PER_INCH);

       #ifdef NEVER
        /*
         * In this conversion we may get situations where the top
         * coordinate is larger than the bottom, which messes us up.
         */
        if (pRect->bottom < pRect->top)
            {
            iLpy=pRect->top;
            pRect->top=pRect->bottom;
            pRect->bottom=iLpy;
            }
       #endif
        }
    else
        {
        pRect->left=MulDiv(pRect->left, HIMETRIC_PER_INCH, iLpx);
        pRect->top =MulDiv(pRect->top , HIMETRIC_PER_INCH, iLpy);

        pRect->right =MulDiv(pRect->right, HIMETRIC_PER_INCH, iLpx);
        pRect->bottom=MulDiv(pRect->bottom,HIMETRIC_PER_INCH, iLpy);
        }

    return;
    }
