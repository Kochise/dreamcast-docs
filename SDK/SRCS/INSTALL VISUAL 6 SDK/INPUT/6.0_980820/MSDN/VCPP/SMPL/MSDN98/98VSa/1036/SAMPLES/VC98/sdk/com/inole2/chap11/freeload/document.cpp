/*
 * DOCUMENT.CPP
 * Freeloader Chapter 11
 *
 * Implementation of the CFreeloaderDoc derivation of CDocument.
 * We create a default handler object and use it for drawing, data
 * caching, and serialization.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "freeload.h"


/*
 * CFreeloaderDoc::CFreeloaderDoc
 * CFreeloaderDoc::~CFreeloaderDoc
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE of the application.
 *  pFR             PCFrame of the frame object.
 *  pAdv            PCDocumentAdviseSink to notify on events
 */

CFreeloaderDoc::CFreeloaderDoc(HINSTANCE hInst, PCFrame pFR
    , PCDocumentAdviseSink pAdv)
    : CDocument(hInst, pFR, pAdv)
    {
    m_pIStorage=NULL;
    m_pIUnknown=NULL;
    m_dwConn=0;
    m_clsID=CLSID_NULL;
    return;
    }


CFreeloaderDoc::~CFreeloaderDoc(void)
    {
    ReleaseObject();
    ReleaseInterface(m_pIStorage);
    return;
    }




/*
 * CFreeloaderDoc::ReleaseObject
 *
 * Purpose:
 *  Centralizes cleanup code for the object and its cache.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CFreeloaderDoc::ReleaseObject(void)
    {
    LPOLECACHE      pIOleCache;
    HRESULT         hr;

    if (0!=m_dwConn)
        {
        hr=m_pIUnknown->QueryInterface(IID_IOleCache
            , (PPVOID)&pIOleCache);

        if (SUCCEEDED(hr))
            {
            pIOleCache->Uncache(m_dwConn);
            pIOleCache->Release();
            }
        }

    ReleaseInterface(m_pIUnknown);
    CoFreeUnusedLibraries();
    m_dwConn=0;
    return;
    }



/*
 * CFreeloaderDoc::FInit
 *
 * Purpose:
 *  Initializes an already created document window.  Here we
 *  only change the stringtable bounds.
 *
 * Parameters:
 *  pDI             PDOCUMENTINIT containing initialization
 *                  parameters.
 *
 * Return Value:
 *  BOOL            TRUE if the function succeeded, FALSE otherwise.
 */

BOOL CFreeloaderDoc::FInit(PDOCUMENTINIT pDI)
    {
    //Change the stringtable range to our customization.
    pDI->idsMin=IDS_DOCUMENTMIN;
    pDI->idsMax=IDS_DOCUMENTMAX;

    //Do default initialization
    return CDocument::Init(pDI);
    }





/*
 * CFreeloaderDoc::FMessageHook
 *
 * Purpose:
 *  Processes WM_PAINT for the document so we can draw the object.
 *
 * Parameters:
 *  <WndProc Parameters>
 *  pLRes           LRESULT * in which to store the return
 *                  value for the message.
 *
 * Return Value:
 *  BOOL            TRUE to prevent further processing,
 *                  FALSE otherwise.
 */

BOOL CFreeloaderDoc::FMessageHook(HWND hWnd, UINT iMsg
    , WPARAM wParam, LPARAM lParam, LRESULT *pLRes)
    {
    PAINTSTRUCT     ps;
    HDC             hDC;
    RECT            rc;
    RECTL           rcl;
    LPVIEWOBJECT2   pIViewObject2;
    HRESULT         hr;

    if (WM_PAINT!=iMsg)
        return FALSE;

    hDC=BeginPaint(hWnd, &ps);
    GetClientRect(hWnd, &rc);

    //Draw the object with IViewObject2::Draw, allowing ESC
    if (NULL!=m_pIUnknown)
        {
        hr=m_pIUnknown->QueryInterface(IID_IViewObject2
            , (PPVOID)&pIViewObject2);

        if (SUCCEEDED(hr))
            {
            //Put "Hit Esc to stop" in the status line
            m_pFR->StatusLine()->MessageSet(PSZ(IDS_HITESCTOSTOP));

            RECTLFROMRECT(rcl, rc);
            pIViewObject2->Draw(DVASPECT_CONTENT, -1, NULL, NULL
                , 0, hDC, &rcl, NULL, ContinuePaint, 0);
            pIViewObject2->Release();

            m_pFR->StatusLine()->MessageDisplay(ID_MESSAGEREADY);
            }
        }

    EndPaint(hWnd, &ps);
    return FALSE;
    }



/*
 * ContinuePaint
 *
 * Purpose:
 *  Callback function for IViewObject2::Draw that allows us to
 *  abort a long repaint.  This implementation watches the
 *  Esc key through GetAsyncKeyState.
 *
 * Parameters:
 *  dwContinue      DWORD custom data passed to IViewObject::Draw
 *                  which in our case holds the document pointer.
 *
 * Return Value:
 *  BOOL            TRUE to continue painting, FALSE to stop it.
 */

BOOL CALLBACK ContinuePaint(DWORD dwContinue)
    {
    return !(GetAsyncKeyState(VK_ESCAPE) < 0);
    }





/*
 * CFreeloaderDoc::Load
 *
 * Purpose:
 *  Loads a given document without any user interface overwriting
 *  the previous contents of the window.
 *
 * Parameters:
 *  fChangeFile     BOOL indicating if we're to update the window
 *                  title and the filename from using this file.
 *  pszFile         LPTSTR to the filename to load, NULL if the file
 *                  is new and untitled.
 *
 * Return Value:
 *  UINT            An error value from DOCERR_...
 */

UINT CFreeloaderDoc::Load(BOOL fChangeFile, LPTSTR pszFile)
    {
    HRESULT             hr;
    LPSTORAGE           pIStorage;
    LPUNKNOWN           pIUnknown;
    LPPERSISTSTORAGE    pIPersistStorage;
    DWORD               dwMode=STGM_TRANSACTED | STGM_READWRITE
                            | STGM_SHARE_EXCLUSIVE;
    CLSID               clsID;

    if (NULL==pszFile)
        {
        //Create a new temp file.
        hr=StgCreateDocfile(NULL, dwMode | STGM_CREATE
            | STGM_DELETEONRELEASE, 0, &pIStorage);

        if (FAILED(hr))
            return DOCERR_COULDNOTOPEN;

        m_pIStorage=pIStorage;

        FDirtySet(FALSE);
        Rename(NULL);
        return DOCERR_NONE;
        }

    //Attempt to open the storage.
    hr=StgOpenStorage(pszFile, NULL, dwMode, NULL, 0, &pIStorage);

    if (FAILED(hr))
        return DOCERR_COULDNOTOPEN;

    /*
     * When we previously called IPersistStorage::Save, we saved
     * the class of this object type with WriteClassStg.  Now
     * we read that CLSID, create a data cache for it, then
     * have it reload its data into the cache through
     * IPersistStorage::Load.
     */

    hr=ReadClassStg(pIStorage, &clsID);

    hr=CreateDataCache(NULL, clsID, IID_IUnknown
        , (PPVOID)&pIUnknown);

    if (FAILED(hr))
        {
        pIStorage->Release();
        return DOCERR_READFAILURE;
        }

    //Get IPersistStorage for the data we hold.
    pIUnknown->QueryInterface(IID_IPersistStorage
        , (PPVOID)&pIPersistStorage);

    //Load might fail because the object is already open...
    hr=pIPersistStorage->Load(pIStorage);
    pIPersistStorage->Release();

    if (FAILED(hr))
        {
        pIUnknown->Release();
        pIStorage->Release();
        return DOCERR_READFAILURE;
        }

    m_pIStorage=pIStorage;
    m_pIUnknown=pIUnknown;

    Rename(pszFile);
    SizeToGraphic(FALSE);
    FDirtySet(FALSE);
    return DOCERR_NONE;
    }







/*
 * CFreeloaderDoc::Save
 *
 * Purpose:
 *  Writes the file to a known filename, requiring that the user
 *  has previously used FileOpen or FileSaveAs in order to have
 *  a filename.
 *
 * Parameters:
 *  uType           UINT indicating the type of file the user
 *                  requested to save in the File Save As dialog.
 *  pszFile         LPTSTR under which to save.  If NULL, use the
 *                  current name.
 *
 * Return Value:
 *  UINT            An error value from DOCERR_...
 */

UINT CFreeloaderDoc::Save(UINT uType, LPTSTR pszFile)
    {
    HRESULT             hr;
    LPSTORAGE           pIStorage;
    LPPERSISTSTORAGE    pIPersistStorage;
    CLSID               clsID;

    //If we have no data object, there's nothing to save.
    if (NULL==m_pIUnknown)
        return DOCERR_WRITEFAILURE;

    //Get IPersistStorage for the data we hold.
    hr=m_pIUnknown->QueryInterface(IID_IPersistStorage
        , (PPVOID)&pIPersistStorage);

    if (FAILED(hr))
        return DOCERR_WRITEFAILURE;

    //Save or Save As with the same file is just a commit.
    if (NULL==pszFile || (NULL!=pszFile
        && 0==lstrcmpi(pszFile, m_szFile)))
        {
        pIPersistStorage->Save(m_pIStorage, TRUE);
        m_pIStorage->Commit(STGC_ONLYIFCURRENT);

        pIPersistStorage->SaveCompleted(NULL);
        pIPersistStorage->Release();

        FDirtySet(FALSE);
        return DOCERR_NONE;
        }

    /*
     * When we're given a name, open the storage, creating it new
     * ifit does not exist or overwriting the old one.  Then CopyTo
     * from the current to the new, Commit the new, then Release
     * the old.
     */

    hr=StgCreateDocfile(pszFile, STGM_TRANSACTED | STGM_READWRITE
        | STGM_CREATE | STGM_SHARE_EXCLUSIVE, 0, &pIStorage);

    if (FAILED(hr))
        return DOCERR_COULDNOTOPEN;

    //Insure the image is up to date, then tell it we're changing
    pIPersistStorage->Save(m_pIStorage, TRUE);
    pIPersistStorage->HandsOffStorage();

    //Save the class, bitmap or metafile
    if (FAILED(pIPersistStorage->GetClassID(&clsID)))
        clsID=m_clsID;

    hr=WriteClassStg(m_pIStorage, clsID);

    hr=m_pIStorage->CopyTo(NULL, NULL, NULL, pIStorage);

    if (FAILED(hr))
        {
        pIPersistStorage->SaveCompleted(m_pIStorage);
        pIPersistStorage->Release();
        pIStorage->Release();
        return DOCERR_WRITEFAILURE;
        }

    pIStorage->Commit(STGC_ONLYIFCURRENT);

    /*
     * Revert changes on the original storage.  If this was a temp
     * file, it's deleted since we used STGM_DELETEONRELEASE.
     */
    m_pIStorage->Release();

    //Make this new storage current
    m_pIStorage=pIStorage;
    pIPersistStorage->SaveCompleted(m_pIStorage);
    pIPersistStorage->Release();

    Rename(pszFile);
    FDirtySet(FALSE);
    return DOCERR_NONE;
    }






/*
 * CFreeloaderDoc::Clip
 *
 * Purpose:
 *  Places a private format, a metafile, and a bitmap of the display
 *  on the clipboard, optionally implementing Cut by deleting the
 *  data in the current window after rendering.
 *
 * Parameters:
 *  hWndFrame       HWND of the main window.
 *  fCut            BOOL indicating cut (TRUE) or copy (FALSE).
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CFreeloaderDoc::Clip(HWND hWndFrame, BOOL fCut)
    {
    BOOL            fRet=TRUE;
    static UINT     rgcf[3]={CF_METAFILEPICT, CF_DIB, CF_BITMAP};
    const UINT      cFormats=3;
    UINT            i;
    HGLOBAL         hMem;

    if (NULL==m_pIUnknown)
        return FALSE;

    if (!OpenClipboard(hWndFrame))
        return FALSE;

    //Clean out whatever junk is in the clipboard.
    EmptyClipboard();

    for (i=0; i < cFormats; i++)
        {
        hMem=RenderFormat(rgcf[i]);

        if (NULL!=hMem)
            {
            SetClipboardData(rgcf[i], hMem);
            fRet=TRUE;
            break;
            }
        }

    //Free clipboard ownership.
    CloseClipboard();

    //If we're cutting, clean out the cache and the object we hold.
    if (fRet && fCut)
        {
        ReleaseObject();
        InvalidateRect(m_hWnd, NULL, TRUE);
        UpdateWindow(m_hWnd);
        FDirtySet(TRUE);
        }

    return fRet;
    }





/*
 * CFreeloaderDoc::RenderFormat
 *
 * Purpose:
 *  Renders a specific clipboard format into global memory.
 *
 * Parameters:
 *  cf              UINT format to render.
 *
 * Return Value:
 *  HGLOBAL         Global memory handle containing the data.
 */

HGLOBAL CFreeloaderDoc::RenderFormat(UINT cf)
    {
    LPDATAOBJECT        pIDataObject;
    FORMATETC           fe;
    STGMEDIUM           stm;

    if (NULL==m_pIUnknown)
        return NULL;

    //We only have to ask the data object (cache) for the data.
    switch (cf)
        {
        case CF_METAFILEPICT:
            stm.tymed=TYMED_MFPICT;
            break;

       case CF_DIB:
            stm.tymed=TYMED_HGLOBAL;
            break;

       case CF_BITMAP:
            stm.tymed=TYMED_GDI;
            break;

        default:
            return NULL;
        }

    stm.hGlobal=NULL;
    SETDefFormatEtc(fe, cf, stm.tymed);

    m_pIUnknown->QueryInterface(IID_IDataObject
        , (PPVOID)&pIDataObject);
    pIDataObject->GetData(&fe, &stm);
    pIDataObject->Release();

    return stm.hGlobal;
    }






/*
 * CFreeloaderDoc::FQueryPaste
 *
 * Purpose:
 *  Determines if we can paste data from the clipboard.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if data is available, FALSE otherwise.
 */

BOOL CFreeloaderDoc::FQueryPaste(void)
    {
    return IsClipboardFormatAvailable(CF_BITMAP)
        || IsClipboardFormatAvailable(CF_DIB)
        || IsClipboardFormatAvailable(CF_METAFILEPICT);
    }





/*
 * CFreeloaderDoc::Paste
 *
 * Purpose:
 *  Retrieves the private data format from the clipboard and sets it
 *  to the current figure in the editor window.
 *
 *  Note that if this function is called, then the clipboard format
 *  is available because the Paste menu item is only enabled if the
 *  format is present.
 *
 * Parameters:
 *  hWndFrame       HWND of the main window.
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CFreeloaderDoc::Paste(HWND hWndFrame)
    {
    UINT                cf=0;
    HGLOBAL             hMem;
    HRESULT             hr;
    DWORD               dwConn;
    LPUNKNOWN           pIUnknown;
    LPOLECACHE          pIOleCache;
    LPPERSISTSTORAGE    pIPersistStorage;
    FORMATETC           fe;
    STGMEDIUM           stm;
    CLSID               clsID;

    if (!OpenClipboard(hWndFrame))
        return FALSE;

    /*
     * Try to get data in order of metafile, dib, bitmap.  We set
     * stm.tymed up front so if we actually get something a call
     * to ReleaseStgMedium will clean it up for us.
     */

    stm.pUnkForRelease=NULL;
    stm.tymed=TYMED_MFPICT;
    hMem=GetClipboardData(CF_METAFILEPICT);

    if (NULL!=hMem)
        cf=CF_METAFILEPICT;

    if (0==cf)
        {
        stm.tymed=TYMED_HGLOBAL;
        hMem=GetClipboardData(CF_DIB);

        if (NULL!=hMem)
            cf=CF_DIB;
        }

    if (0==cf)
        {
        stm.tymed=TYMED_GDI;
        hMem=GetClipboardData(CF_BITMAP);

        if (NULL!=hMem)
            cf=CF_BITMAP;
        }

    stm.hGlobal=OleDuplicateData(hMem, cf, NULL);
    CloseClipboard();

    //Didn't get anything?  Then we're finished.
    if (0==cf)
        return FALSE;

    //This now describes the data we have.
    SETDefFormatEtc(fe, cf, stm.tymed);


    /*
     * Create a data cache to deal with this data using
     * either CoCreateInstance for an OLE-supported CLSID or
     * CreateDataCache.  The first will go through all the
     * exercises of looking up the CLSID in the regDB, finding
     * the OLE DLL (registered for these classes), getting a class
     * factory, and using IClassFactory::CreateInstance.  The
     * second goes into OLE directly, creating the same object
     * with less overhead.  Thus we use CreateDataCache.
     */

    if (CF_METAFILEPICT==cf)
        clsID=CLSID_Picture_Metafile;
    else
        clsID=CLSID_Picture_Dib;

    hr=CreateDataCache(NULL, clsID, IID_IUnknown
        , (PPVOID)&pIUnknown);

    if (FAILED(hr))
        {
        ReleaseStgMedium(&stm);
        return FALSE;
        }

    /*
     * Our contract says we provide storage through
     * IPersistStorage::InitNew.  We know that the object we're
     * dealing with supports IPersistStorage and IOleCache, so
     * we don't bother to check return values.  I guess we're
     * living dangerously...
     */
    pIUnknown->QueryInterface(IID_IPersistStorage
        , (PPVOID)&pIPersistStorage);
    pIPersistStorage->InitNew(m_pIStorage);
    pIPersistStorage->Release();

    /*
     * Now that we have the cache object, shove the data into it.
     * No advise flags are necessary for static data.
     */
    pIUnknown->QueryInterface(IID_IOleCache, (PPVOID)&pIOleCache);
    pIOleCache->Cache(&fe, ADVF_PRIMEFIRST, &dwConn);

    hr=pIOleCache->SetData(&fe, &stm, TRUE);
    pIOleCache->Release();

    if (FAILED(hr))
        {
        ReleaseStgMedium(&stm);
        pIUnknown->Release();
        return FALSE;
        }

    //Now that that's all done, replace our current with the new.
    ReleaseObject();
    m_pIUnknown=pIUnknown;
    m_dwConn=dwConn;
    m_clsID=clsID;

    FDirtySet(TRUE);

    InvalidateRect(m_hWnd, NULL, TRUE);
    UpdateWindow(m_hWnd);
    return TRUE;
    }



/*
 * CFreeloaderDoc::SizeToGraphic
 *
 * Purpose:
 *  Determines if we can size the window to the contained
 *  graphic and alternately performs the operation.
 *
 * Parameters:
 *  fQueryOnly      BOOL indicating if we just want to know
 *                  if sizing is possible (TRUE) or that we
 *                  want to perform the sizing (FALSE).
 *
 * Return Value:
 *  BOOL            TRUE if data is available, FALSE otherwise.
 */

BOOL CFreeloaderDoc::SizeToGraphic(BOOL fQueryOnly)
    {
    HRESULT             hr;
    LPVIEWOBJECT2       pIViewObject2;
    SIZEL               szl;
    RECT                rc;
    UINT                cx, cy;
    HDC                 hDC;
    DWORD               dwStyle;

    if (NULL==m_pIUnknown)
        return FALSE;

    m_pIUnknown->QueryInterface(IID_IViewObject2
        , (PPVOID)&pIViewObject2);

    if (FAILED(hr))
        return FALSE;

    if (fQueryOnly)
        {
        pIViewObject2->Release();
        return TRUE;
        }

    hr=pIViewObject2->GetExtent(DVASPECT_CONTENT, -1, NULL, &szl);
    pIViewObject2->Release();

    if (FAILED(hr))
        return FALSE;

    //Calculate new doc rectangle based on these extents.

    hDC=GetDC(NULL);
    cx=MulDiv((int)szl.cx, GetDeviceCaps(hDC, LOGPIXELSX)
        , HIMETRIC_PER_INCH);
    cy=MulDiv((int)szl.cy, GetDeviceCaps(hDC, LOGPIXELSY)
        , HIMETRIC_PER_INCH);
    ReleaseDC(NULL, hDC);

    SetRect(&rc, 0, 0, cx, cy);
    dwStyle=GetWindowLong(m_hWnd, GWL_STYLE);
    AdjustWindowRect(&rc, dwStyle, FALSE);

    /*
     * If the window is currently maximized, then we have to
     * restore it first before sizing.
     */
    if (IsZoomed(m_hWnd))
        ShowWindow(m_hWnd, SW_RESTORE);

    SetWindowPos(m_hWnd, NULL, 0, 0
        , rc.right-rc.left , rc.bottom-rc.top
        , SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);

    return TRUE;
    }
