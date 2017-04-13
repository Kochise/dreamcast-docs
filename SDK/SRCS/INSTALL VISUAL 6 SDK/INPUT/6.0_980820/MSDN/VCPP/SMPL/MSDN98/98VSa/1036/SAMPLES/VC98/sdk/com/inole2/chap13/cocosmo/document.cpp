/*
 * DOCUMENT.CPP
 * Component Cosmo Chapter 13
 *
 * Implementation of the CCosmoDoc derivation of CDocument
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "cocosmo.h"


/*
 * CCosmoDoc::CCosmoDoc
 * CCosmoDoc::~CCosmoDoc
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE of the application.
 *  pFR             PCFrame of the frame object.
 *  pAdv            PCDocumentAdviseSink to notify on events
 */

CCosmoDoc::CCosmoDoc(HINSTANCE hInst, PCFrame pFR
    , PCDocumentAdviseSink pAdv)
    : CDocument(hInst, pFR, pAdv)
    {
    m_pPL=NULL;
    m_pPLAdv=NULL;
    m_uPrevSize=SIZE_RESTORED;
    m_pIConnectPt=NULL;
    m_dwCookie=0;

    m_pIStorage=NULL;
    m_pp.psModel=PERSIST_UNKNOWN;
    m_pp.pIP.pIPersistStorage=NULL; //Affects all pointers

    m_pImpIAdviseSink=NULL;
    m_dwConn=0;
    m_pIDataClip=NULL;

    //CHAPTER13MOD
    m_pDropTarget=NULL;
    m_fDragSource=FALSE;
    //End CHAPTER13MOD

    return;
    }


CCosmoDoc::~CCosmoDoc(void)
    {
    LPDATAOBJECT        pIDataObject;
    HRESULT             hr;

    if (NULL!=m_pIDataClip)
        m_pIDataClip->Release();

    //Turn off the advise.
    if (NULL!=m_pPL && 0!=m_dwConn)
        {
        hr=m_pPL->QueryInterface(IID_IDataObject
            , (PPVOID)&pIDataObject);

        if (SUCCEEDED(hr))
            {
            pIDataObject->DUnadvise(m_dwConn);
            pIDataObject->Release();
            }
        }

    DeleteInterfaceImp(m_pImpIAdviseSink);
    ReleaseInterface(m_pp.pIP.pIPersistStorage);
    ReleaseInterface(m_pIStorage);

    if (NULL!=m_pIConnectPt)
        {
        m_pIConnectPt->Unadvise(m_dwCookie);
        ReleaseInterface(m_pIConnectPt);
        }

    ReleaseInterface(m_pPL);
    ReleaseInterface(m_pPLAdv);

    CoFreeUnusedLibraries();
    return;
    }






/*
 * CCosmoDoc::Init
 *
 * Purpose:
 *  Initializes an already created document window.  The client
 *  actually creates the window for us, then passes that here for
 *  further initialization.
 *
 * Parameters:
 *  pDI             PDOCUMENTINIT containing initialization
 *                  parameters.
 *
 * Return Value:
 *  BOOL            TRUE if the function succeeded, FALSE otherwise.
 */

BOOL CCosmoDoc::Init(PDOCUMENTINIT pDI)
    {
    RECT                        rc;
    HRESULT                     hr;
    IConnectionPointContainer  *pCPC;
    FORMATETC                   fe;
    LPDATAOBJECT                pIDataObject;

    //Change the stringtable range to our customization.
    pDI->idsMin=IDS_DOCUMENTMIN;
    pDI->idsMax=IDS_DOCUMENTMAX;

    //Do default initialization
    if (!CDocument::Init(pDI))
        return FALSE;

    //Create the Polyline Component
    hr=CoCreateInstance(CLSID_Polyline10, NULL, CLSCTX_INPROC_SERVER
        , IID_IPolyline10, (PPVOID)&m_pPL);

    if (FAILED(hr))
        {
        //Warn that we could not load the Polyline
        MessageBox(pDI->hWndDoc, PSZ(IDS_NOPOLYLINE)
            , PSZ(IDS_CAPTION), MB_OK);
        return FALSE;
        }

    //Initialize the contained Polyline which creates a window.
    GetClientRect(m_hWnd, &rc);
    InflateRect(&rc, -8, -8);

    if (FAILED(m_pPL->Init(m_hWnd, &rc, WS_CHILD | WS_VISIBLE
        , ID_POLYLINE)))
        return FALSE;

    //Set up an advise on the Polyline.
    m_pPLAdv=new CPolylineAdviseSink(this);
    m_pPLAdv->AddRef();

    if (SUCCEEDED(m_pPL->QueryInterface(IID_IConnectionPointContainer
        , (PPVOID)&pCPC)))
        {
        //CHAPTER10MOD
        if (SUCCEEDED(pCPC->FindConnectionPoint
            (IID_IPolylineAdviseSink10, &m_pIConnectPt)))
        //End CHAPTER10MOD
            {
            m_pIConnectPt->Advise((LPUNKNOWN)m_pPLAdv, &m_dwCookie);
            }

        pCPC->Release();
        }

    /*
     * Check for the storage model being used in Polyline.
     * Any InitNew member will be called from CCosmoDoc::Load.
     */
    hr=m_pPL->QueryInterface(IID_IPersistStorage
        , (PPVOID)&m_pp.pIP.pIPersistStorage);

    if (SUCCEEDED(hr))
        m_pp.psModel=PERSIST_STORAGE;
    else
        {
        hr=m_pPL->QueryInterface(IID_IPersistStreamInit
            , (PPVOID)&m_pp.pIP.pIPersistStreamInit);

        if (SUCCEEDED(hr))
            m_pp.psModel=PERSIST_STREAMINIT;
        else
            {
            hr=m_pPL->QueryInterface(IID_IPersistStream
            , (PPVOID)&m_pp.pIP.pIPersistStream);

            if (SUCCEEDED(hr))
                m_pp.psModel=PERSIST_STREAM;
            else
                return FALSE;
            }
        }


    /*
     * Create an IAdviseSink and send it to the Polyline's
     * IDataObject with the clipboard format for the Polyline
     * (as in IPOLY10.H).
     */

    //This is a private macro.
    SETDefFormatEtc(fe, m_cf, TYMED_HGLOBAL);

    m_pImpIAdviseSink=new CImpIAdviseSink(this, this);

    if (NULL==m_pImpIAdviseSink)
        return FALSE;

    //Set up an advise for the Polyline format
    hr=m_pPL->QueryInterface(IID_IDataObject, (PPVOID)&pIDataObject);

    if (FAILED(hr))
        return FALSE;

    pIDataObject->DAdvise(&fe, ADVF_NODATA, m_pImpIAdviseSink
        , &m_dwConn);
    pIDataObject->Release();

    //CHAPTER13MOD
    m_pDropTarget=new CDropTarget(this);

    if (NULL!=m_pDropTarget)
        {
        m_pDropTarget->AddRef();
        CoLockObjectExternal(m_pDropTarget, TRUE, FALSE);
        RegisterDragDrop(m_hWnd, m_pDropTarget);
        }
    //End CHAPTER13MOD

    return TRUE;
    }




//IUnknown interface for all others we implement in the document

/*
 * CCosmoDoc::QueryInterface
 * CCosmoDoc::AddRef
 * CCosmoDoc::Release
 *
 * Purpose:
 *  IUnknown members for the CCosmoDoc implementation.
 */

STDMETHODIMP CCosmoDoc::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    //The document is the unknown
    if (IID_IUnknown==riid)
        *ppv=(LPUNKNOWN)this;

    //Return contained interfaces for others.
    if (IID_IPolylineAdviseSink10==riid)
        *ppv=m_pPLAdv;

    if (IID_IAdviseSink==riid)
        *ppv=m_pImpIAdviseSink;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(S_FALSE);
    }


STDMETHODIMP_(ULONG) CCosmoDoc::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CCosmoDoc::Release(void)
    {
    return --m_cRef;
    }





/*
 * CCosmoDoc::FMessageHook
 *
 * Purpose:
 *  Processes WM_SIZE for the document so we can resize
 *  the Polyline.
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

BOOL CCosmoDoc::FMessageHook(HWND hWnd, UINT iMsg, WPARAM wParam
    , LPARAM lParam, LRESULT *pLRes)
    {
    UINT        dx, dy;
    RECT        rc;

    *pLRes=0;

    if (WM_DESTROY==iMsg)
        {
        /*
         * Flush the clipboard data object if it's still on the
         * clipboard before the document window is destroyed which
         * also destroys the polyline, which is a child.  Flushing
         * now avoid errors that would occur if flushing happened
         * at application shutdown, for the Polyline would still be
         * alive but without a valid window.
         */
        if (NULL!=m_pIDataClip)
            {
            if (NOERROR==OleIsCurrentClipboard(m_pIDataClip))
                OleFlushClipboard();
            }

        //CHAPTER13MOD
        /*
         * We have to revoke the drop target here because the window
         * will be destroyed and the property forcefully removed
         * before we could do this in the destructor.
         */
        if (NULL!=m_pDropTarget)
            {
            RevokeDragDrop(m_hWnd);
            CoLockObjectExternal(m_pDropTarget, FALSE, TRUE);
            m_pDropTarget->Release();
            }
        //End CHAPTER13MOD
        }

    if (WM_SIZE==iMsg)
        {
        //Don't effect the Polyline size to or from minimized state.
        if (SIZE_MINIMIZED!=wParam && SIZE_MINIMIZED !=m_uPrevSize)
            {
            //When we change size, resize any Polyline we hold.
            dx=LOWORD(lParam);
            dy=HIWORD(lParam);

            /*
             * If we are getting WM_SIZE in response to a Polyline
             * notification, then don't resize the Polyline window
             * again.
             */
            if (!m_fNoSize && NULL!=m_pPL)
                {
                //Resize the polyline to fit the new client
                SetRect(&rc, 8, 8, dx-8, dy-8);
                m_pPL->RectSet(&rc, FALSE);

                /*
                 * We consider sizing something that makes the file
                 * dirty, but not until we've finished the create
                 * process, which is why we set fNoDirty to FALSE
                 * in WM_CREATE since we get a WM_SIZE on the first
                 * creation.
                 */
                if (!m_fNoDirty)
                    FDirtySet(TRUE);

                SetRect(&rc, 0, 0, dx, dy);

                if (NULL!=m_pAdv)
                    m_pAdv->OnSizeChange(this, &rc);

                m_fNoDirty=FALSE;
                }
            }

        m_uPrevSize=wParam;
        }

    //CHAPTER13MOD
    if (WM_LBUTTONDOWN==iMsg)
        {
        LPDROPSOURCE    pIDropSource;
        LPDATAOBJECT    pIDataObject;
        HRESULT         hr;
        SCODE           sc;
        DWORD           dwEffect;

        pIDropSource=new CDropSource(this);

        if (NULL==pIDropSource)
            return FALSE;

        pIDropSource->AddRef();
        m_fDragSource=TRUE;

        //Go get the data and start the ball rolling.
        pIDataObject=TransferObjectCreate();

        if (NULL!=pIDataObject)
            {
            hr=DoDragDrop(pIDataObject, pIDropSource
                , DROPEFFECT_COPY | DROPEFFECT_MOVE, &dwEffect);

            pIDataObject->Release();
            sc=GetScode(hr);
            }
        else
            sc=E_FAIL;

        pIDropSource->Release();
        m_fDragSource=FALSE;

        if (DRAGDROP_S_DROP==sc && DROPEFFECT_MOVE==dwEffect)
            {
            m_pPL->New();
            FDirtySet(TRUE);
            }

        return TRUE;
        }
    //End CHAPTER13MOD


    /*
     * We return FALSE even on WM_SIZE so we can let the default
     * procedure handle maximized MDI child windows appropriately.
     */
    return FALSE;
    }








/*
 * CCosmoDoc::Clear
 *
 * Purpose:
 *  Sets all contents in the document back to defaults with
 *  no filename.
 *
 * Paramters:
 *  None
 *
 * Return Value:
 *  None
 */

void CCosmoDoc::Clear(void)
    {
    //Completely reset the polyline
    m_pPL->New();

    CDocument::Clear();
    return;
    }






/*
 * CCosmoDoc::Load
 *
 * Purpose:
 *  Loads a given document without any user interface overwriting
 *  the previous contents of the Polyline window.  We do this by
 *  opening the file and telling the Polyline to load itself from
 *  that file.
 *
 * Parameters:
 *  fChangeFile     BOOL indicating if we're to update the window
 *                  title and the filename from using this file.
 *  pszFile         LPTSTR to the filename to load, NULL if the file
 *                  is new and untitled.
 *
 * Return Value:
 *  UINT            An error value from DOCERR_*
 */

UINT CCosmoDoc::Load(BOOL fChangeFile, LPTSTR pszFile)
    {
    HRESULT             hr;
    LPSTORAGE           pIStorage;

    if (NULL==pszFile)
        {
        /*
         * As a user of an IPersistStorage we have to provide all
         * objects with an IStorage they can use for incremental
         * access passing that storage to InitNew.  Here we create
         * a temporary file that we don't bother holding on to.
         * If the object doesn't use it, then our Release destroys
         * it immediately.
         */

        hr=StgCreateDocfile(NULL, STGM_DIRECT | STGM_READWRITE
            | STGM_CREATE | STGM_DELETEONRELEASE
            | STGM_SHARE_EXCLUSIVE, 0, &pIStorage);

        if (FAILED(hr))
            return DOCERR_COULDNOTOPEN;

        if (PERSIST_STORAGE==m_pp.psModel)
            m_pp.pIP.pIPersistStorage->InitNew(pIStorage);
        else
            {
            if (PERSIST_STREAMINIT==m_pp.psModel)
                m_pp.pIP.pIPersistStreamInit->InitNew();
            }

        m_pIStorage=pIStorage;

        Rename(NULL);
        return DOCERR_NONE;
        }

    /*
     * Open a storage and have the Polyline read its data
     * using whatever persistence model it employs.
     */
    hr=StgOpenStorage(pszFile, NULL, STGM_DIRECT | STGM_READWRITE
        | STGM_SHARE_EXCLUSIVE, NULL, 0, &pIStorage);

    if (FAILED(hr))
        return DOCERR_COULDNOTOPEN;

    if (PERSIST_STORAGE==m_pp.psModel)
        hr=m_pp.pIP.pIPersistStorage->Load(pIStorage);
    else
        {
        LPSTREAM    pIStream;

        hr=pIStorage->OpenStream(SZSTREAM, 0, STGM_DIRECT
            | STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, &pIStream);

        if (SUCCEEDED(hr))
            {
            //This also works for PERSIST_STREAMINIT
            hr=m_pp.pIP.pIPersistStream->Load(pIStream);
            pIStream->Release();
            }
        }

    m_pIStorage=pIStorage;

    if (FAILED(hr))
        return DOCERR_READFAILURE;

    if (fChangeFile)
        Rename(pszFile);

    //Importing a file makes things dirty
    FDirtySet(!fChangeFile);

    return DOCERR_NONE;
    }







/*
 * CCosmoDoc::Save
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
 *  UINT            An error value from DOCERR_*
 */

UINT CCosmoDoc::Save(UINT uType, LPTSTR pszFile)
    {
    BOOL                fRename=TRUE;
    HRESULT             hr;
    LPSTORAGE           pIStorage;
    BOOL                fSameAsLoad;

    //If Save or Save As under the same name, do Save.
    if (NULL==pszFile || 0==lstrcmpi(pszFile, m_szFile))
        {
        fRename=FALSE;
        pszFile=m_szFile;

        /*
         * If we're saving to an existing storage, just pass
         * the IStorage we have from Load along with TRUE
         * in fSameAsLoad.
         */

        fSameAsLoad=TRUE;
        }
    else
        {
        /*
         * In Component Cosmo, we only deal with one version of
         * data; all the code in Chapter 1 Cosmo that dealt with
         * 1.0 and 2.0 files has been removed.
         */

        hr=StgCreateDocfile(pszFile, STGM_DIRECT | STGM_READWRITE
            | STGM_CREATE | STGM_SHARE_EXCLUSIVE, 0, &pIStorage);

        if (FAILED(hr))
            return DOCERR_COULDNOTOPEN;

        //Tell the object to save into this new storage
        fSameAsLoad=FALSE;

        //Update our variable
        m_pIStorage->Release();
        m_pIStorage=pIStorage;
        }

    if (PERSIST_STORAGE==m_pp.psModel)
        {
        hr=m_pp.pIP.pIPersistStorage->Save(m_pIStorage, fSameAsLoad);

        if (SUCCEEDED(hr))
            {
            hr=m_pp.pIP.pIPersistStorage->SaveCompleted(fSameAsLoad
                ? NULL : m_pIStorage);
            }
        }
    else
        {
        LPSTREAM    pIStream;

        hr=m_pIStorage->CreateStream(SZSTREAM, STGM_DIRECT
            | STGM_CREATE | STGM_WRITE | STGM_SHARE_EXCLUSIVE
            , 0, 0, &pIStream);

        if (SUCCEEDED(hr))
            {
            //This also works for PERSIST_STREAMINIT
            hr=m_pp.pIP.pIPersistStream->Save(pIStream, TRUE);
            pIStream->Release();
            }
        }


    if (FAILED(hr))
        return DOCERR_WRITEFAILURE;

    //Saving makes us clean
    FDirtySet(FALSE);

    if (fRename)
        Rename(pszFile);

    return DOCERR_NONE;
    }






/*
 * CCosmoDoc::Undo
 *
 * Purpose:
 *  Reverses a previous action.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CCosmoDoc::Undo(void)
    {
    m_pPL->Undo();
    return;
    }






/*
 * CCosmoDoc::Clip
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

BOOL CCosmoDoc::Clip(HWND hWndFrame, BOOL fCut)
    {
    //CHAPTER13MOD
    BOOL            fRet=TRUE;
    LPDATAOBJECT    pIDataObject;

    pIDataObject=TransferObjectCreate();

    if (NULL==pIDataObject)
        return FALSE;
    //CHAPTER13MOD

    fRet=SUCCEEDED(OleSetClipboard(pIDataObject));

    if (NULL!=m_pIDataClip)
        m_pIDataClip->Release();

    m_pIDataClip=pIDataObject;

    //Delete our current data if a "cut" succeeded.
    if (fRet && fCut)
        {
        m_pPL->New();
        FDirtySet(TRUE);
        }

    return fRet;
    }





/*
 * CCosmoDoc::FQueryPaste
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

BOOL CCosmoDoc::FQueryPaste(void)
    {
    LPDATAOBJECT    pIDataObject;
    BOOL            fRet;

    if (FAILED(OleGetClipboard(&pIDataObject)))
        return FALSE;

    //CHAPTER13MOD
    fRet=FQueryPasteFromData(pIDataObject);
    //End CHAPTER13MOD

    pIDataObject->Release();
    return fRet;
    }



//CHAPTER13MOD
/*
 * CCosmoDoc::FQueryPasteFromData
 * (Protected)
 *
 * Purpose:
 *  Determines if we can paste data from a data object.
 *
 * Parameters:
 *  pIDataObject    LPDATAOBJECT from which we might want to paste.
 *
 * Return Value:
 *  BOOL            TRUE if data is available, FALSE otherwise.
 */

BOOL CCosmoDoc::FQueryPasteFromData(LPDATAOBJECT pIDataObject)
    {
    FORMATETC       fe;

    SETDefFormatEtc(fe, m_cf, TYMED_HGLOBAL);
    return (NOERROR==pIDataObject->QueryGetData(&fe));
    }
//End CHAPTER13MOD




/*
 * CCosmoDoc::Paste
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

BOOL CCosmoDoc::Paste(HWND hWndFrame)
    {
    LPDATAOBJECT    pIDataObject;
    BOOL            fRet;

    if (FAILED(OleGetClipboard(&pIDataObject)))
        return FALSE;

    //CHAPTER13MOD
    fRet=PasteFromData(pIDataObject);
    //End CHAPTER13MOD

    pIDataObject->Release();
    return TRUE;
    }






//CHAPTER13MOD
/*
 * CCosmoDoc::PasteFromData
 * (Protected)
 *
 * Purpose:
 *  Retrieves the private data format from a data object and sets
 *  it to the current figure in the editor window.
 *
 * Parameters:
 *  pIDataObject    LPDATAOBJECT from which to paste.
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CCosmoDoc::PasteFromData(LPDATAOBJECT pIDataObject)
    {
    FORMATETC       fe;
    STGMEDIUM       stm;
    BOOL            fRet;

    SETDefFormatEtc(fe, m_cf, TYMED_HGLOBAL);
    fRet=SUCCEEDED(pIDataObject->GetData(&fe, &stm));

    if (!fRet || NULL==stm.hGlobal)
        return FALSE;

    if (fRet && NULL!=stm.hGlobal)
        {
        m_pPL->QueryInterface(IID_IDataObject
            , (PPVOID)&pIDataObject);
        pIDataObject->SetData(&fe, &stm, TRUE);
        pIDataObject->Release();

        FDirtySet(TRUE);
        }

    return fRet;
    }




/*
 * CCosmoDoc::TransferObjectCreate
 * (Protected)
 *
 * Purpose:
 *  Creates a DataTransferObject and stuffs the current Polyline
 *  data into it, used for both clipboard and drag-drop operations.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  LPDATAOBJECT    Pointer to the object created, NULL on failure
 */

LPDATAOBJECT CCosmoDoc::TransferObjectCreate(void)
    {
    UINT            i;
    HRESULT         hr;
    STGMEDIUM       stm;
    FORMATETC       fe;
    LPDATAOBJECT    pIDataSrc;
    LPDATAOBJECT    pIDataObject=NULL;
    const UINT      cFormats=3;
    static UINT     rgcf[3]={0, CF_METAFILEPICT, CF_BITMAP};
    static DWORD    rgtm[3]={TYMED_HGLOBAL, TYMED_MFPICT
                        , TYMED_GDI};

    hr=CoCreateInstance(CLSID_DataTransferObject, NULL
        , CLSCTX_INPROC_SERVER, IID_IDataObject
        , (PPVOID)&pIDataObject);

    if (FAILED(hr))
        return NULL;

    rgcf[0]=m_cf;

    hr=m_pPL->QueryInterface(IID_IDataObject, (PPVOID)&pIDataSrc);

    if (FAILED(hr))
        {
        pIDataObject->Release();
        return NULL;
        }

    for (i=0; i < cFormats; i++)
        {
        //Copy private data first.
        SETDefFormatEtc(fe, rgcf[i], rgtm[i]);

        if (SUCCEEDED(pIDataSrc->GetData(&fe, &stm)))
            pIDataObject->SetData(&fe, &stm, TRUE);
        }

    pIDataSrc->Release();
    return pIDataObject;    //Caller now responsible
    }





/*
 * CCosmoDoc::DropSelectTargetWindow
 * (Protected)
 *
 * Purpose:
 *  Creates a thin inverted frame around a window that we use to
 *  show the window as a drop target.  This is a toggle function:
 *  it uses XOR to create the effect so it must be called twice
 *  to leave the window as it was.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CCosmoDoc::DropSelectTargetWindow(void)
    {
    HDC         hDC;
    RECT        rc;
    UINT        dd=3;
    HWND        hWnd;

    m_pPL->Window(&hWnd);
    hDC=GetWindowDC(hWnd);
    GetClientRect(hWnd, &rc);

    //Frame this window with inverted pixels

    //Top
    PatBlt(hDC, rc.left, rc.top, rc.right-rc.left, dd, DSTINVERT);

    //Bottom
    PatBlt(hDC, rc.left, rc.bottom-dd, rc.right-rc.left, dd
        , DSTINVERT);

    //Left excluding regions already affected by top and bottom
    PatBlt(hDC, rc.left, rc.top+dd, dd, rc.bottom-rc.top-(2*dd)
        , DSTINVERT);

    //Right excluding regions already affected by top and bottom
    PatBlt(hDC, rc.right-dd, rc.top+dd, dd, rc.bottom-rc.top-(2*dd)
        , DSTINVERT);

    ReleaseDC(hWnd, hDC);
    return;
    }

//End CHAPTER13MOD




/*
 * CCosmoDoc::ColorSet
 *
 * Purpose:
 *  Changes a color used in our contained Polyline.
 *
 * Parameters:
 *  iColor          UINT index of the color to change.
 *  cr              COLORREF new color.
 *
 * Return Value:
 *  COLORREF        Previous color for the given index.
 */

COLORREF CCosmoDoc::ColorSet(UINT iColor, COLORREF cr)
    {
    COLORREF    crRet;

    m_pPL->ColorSet(iColor, cr, &crRet);
    return crRet;
    }





/*
 * CCosmoDoc::ColorGet
 *
 * Purpose:
 *  Retrieves a color currently in use in the Polyline.
 *
 * Parameters:
 *  iColor          UINT index of the color to retrieve.
 *
 * Return Value:
 *  COLORREF        Current color for the given index.
 */

COLORREF CCosmoDoc::ColorGet(UINT iColor)
    {
    COLORREF    crRet;

    m_pPL->ColorGet(iColor, &crRet);
    return crRet;
    }






/*
 * CCosmoDoc::LineStyleSet
 *
 * Purpose:
 *  Changes the line style currently used in the Polyline
 *
 * Parameters:
 *  iStyle          UINT index of the new line style to use.
 *
 * Return Value:
 *  UINT            Previous line style.
 */

UINT CCosmoDoc::LineStyleSet(UINT iStyle)
    {
    UINT    i;

    m_pPL->LineStyleSet(iStyle, &i);
    return i;
    }







/*
 * CCosmoDoc::LineStyleGet
 *
 * Purpose:
 *  Retrieves the line style currently used in the Polyline
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  UINT            Current line style.
 */


UINT CCosmoDoc::LineStyleGet(void)
    {
    UINT    i=0;

    //m_pPL might not be valid yet.
    if (NULL!=m_pPL)
        m_pPL->LineStyleGet(&i);

    return i;
    }
