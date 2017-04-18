/*
 * DOCUMENT.CPP
 * Cosmo Chapter 23
 *
 * Implementation of the CCosmoDoc derivation of CDocument as
 * well as an implementation of CPolylineAdviseSink.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "cosmo.h"


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

    m_pDropTarget=NULL;
    m_fDragSource=FALSE;

    m_cfEmbedSource=RegisterClipboardFormat(CFSTR_EMBEDSOURCE);
    m_cfObjectDescriptor=RegisterClipboardFormat
        (CFSTR_OBJECTDESCRIPTOR);

    m_pFigure=NULL;
    m_pMoniker=NULL;
    m_dwRegROT=0L;

    m_cfLinkSource=RegisterClipboardFormat(CFSTR_LINKSOURCE);
    m_cfLinkSrcDescriptor=RegisterClipboardFormat
        (CFSTR_LINKSRCDESCRIPTOR);

    return;
    }


CCosmoDoc::~CCosmoDoc(void)
    {
    //Make sure the object is saved
    m_pFigure->SendAdvise(OBJECTCODE_SAVEOBJECT);
    m_pFigure->SendAdvise(OBJECTCODE_HIDEWINDOW);
    m_pFigure->SendAdvise(OBJECTCODE_CLOSED);

    //If the document is reg'd as running, revoke and free the moniker
    INOLE_RevokeAsRunning(&m_dwRegROT);

    if (NULL!=m_pMoniker)
        m_pMoniker->Release();

    if (NULL!=m_pFigure)
        {
        m_pFigure->AddRef();
        CoDisconnectObject(m_pFigure, 0L);
        m_pFigure->Release();   //Starts shutdown if necessary.
        delete m_pFigure;
        }

    //Clean up the allocations we did in Init
    if (NULL!=m_pPL)
        delete m_pPL;

    if (NULL!=m_pPLAdv)
        delete m_pPLAdv;

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
    RECT        rc;

    //Change the stringtable range to our customization.
    pDI->idsMin=IDS_DOCUMENTMIN;
    pDI->idsMax=IDS_DOCUMENTMAX;

    //Do default initialization
    if (!CDocument::Init(pDI))
        return FALSE;

    //Add the Polyline stuff we need.
    m_pPLAdv=new CPolylineAdviseSink(this);
    m_pPL   =new CPolyline(m_hInst);

    //Attempt to create our contained Polyline.
    GetClientRect(m_hWnd, &rc);
    InflateRect(&rc, -8, -8);

    if (!m_pPL->Init(m_hWnd, &rc, WS_CHILD | WS_VISIBLE
        , ID_POLYLINE, m_pPLAdv))
        return FALSE;

    m_pDropTarget=new CDropTarget(this);

    if (NULL!=m_pDropTarget)
        {
        m_pDropTarget->AddRef();
        CoLockObjectExternal(m_pDropTarget, TRUE, FALSE);
        RegisterDragDrop(m_hWnd, m_pDropTarget);
        }

    m_pFigure=new CFigure(ObjectDestroyed, this);

    if (NULL==m_pFigure)
        return FALSE;

    //We created an object, so count it.
    g_cObj++;

    if (!m_pFigure->Init())
        return FALSE;

    return TRUE;
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

    if (WM_LBUTTONDOWN==iMsg)
        {
        LPDROPSOURCE    pIDropSource;
        LPDATAOBJECT    pIDataObject;
        HRESULT         hr;
        SCODE           sc;
        DWORD           dwEffect;

        /*
         * The document has an 8 pixel border around the polyline
         * window where we'll see mouse clicks.  A left mouse button
         * click here means the start of a drag-drop operation.
         *
         * Since this is a modal operation, this IDropSource
         * is entirely local.
         */

        pIDropSource=new CDropSource(this);

        if (NULL==pIDropSource)
            return FALSE;

        pIDropSource->AddRef();
        m_fDragSource=TRUE;

        //Go get the data and start the ball rolling.
        pIDataObject=TransferObjectCreate(FALSE);

        if (NULL!=pIDataObject)
            {
            hr=DoDragDrop(pIDataObject, pIDropSource
                , DROPEFFECT_COPY | DROPEFFECT_MOVE | DROPEFFECT_LINK
                , &dwEffect);

            pIDataObject->Release();
            sc=GetScode(hr);
            }
        else
            sc=E_FAIL;

        /*
         * When we return from DoDragDrop, either cancel or drop.
         * First toss the IDropSource we have here, then bail out
         * on cancel, and possibly clear our data on a move drop.
         */

        pIDropSource->Release();

        /*
         * If dropped on the same document (determined using
         * this flag, then dwEffect will be DROPEFFECT_NONE (see
         * IDropTarget::Drop in DROPTGT.CPP).  In any case,
         * reset this since the operation is done.
         */

        m_fDragSource=FALSE;

        if (DRAGDROP_S_DROP==sc && DROPEFFECT_MOVE==dwEffect)
            {
            m_pPL->New();
            FDirtySet(TRUE);
            }

        //On a canceled drop or a copy we don't do anything else
        return TRUE;
        }

    if (WM_DESTROY==iMsg)
        {
        /*
         * We have to revoke the drop target here because the window
         * will be destroyed and the property forcefully removed
         * before we could do this in the destructor.
         */
        if (NULL!=m_pDropTarget)
            {
            RevokeDragDrop(m_hWnd);
            CoLockObjectExternal(m_pDropTarget, FALSE, TRUE);
            ReleaseInterface(m_pDropTarget);
            }

        return FALSE;
        }


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
    m_lVer=0;
    return;
    }



/*
 * CCosmoDoc::FDirtySet
 *
 * Purpose:
 *  Sets or clears the document 'dirty' flag returning the previous
 *  state of that same flag.  We override this in Cosmo server to
 *  send the OnDataChange notification as necessary.
 *
 * Parameters:
 *  fDirty          BOOL indicating the new contents of the dirty
 *                  flag.
 *
 * Return Value:
 *  BOOL            Previous value of the dirty flag.
 */

BOOL CCosmoDoc::FDirtySet(BOOL fDirty)
    {
    BOOL        fRet;

    fRet=CDocument::FDirtySet(fDirty);
    m_pFigure->SendAdvise(OBJECTCODE_DATACHANGED);

    return fRet;
    }




/*
 * CCosmoDoc::FDirtyGet
 *
 * Purpose:
 *  Override of the normal FDirtyGet such that we never return dirty
 *  for an embedded object we're serving since updates constantly
 *  happen and since the object will be saved on closure.  This then
 *  prevents any message boxes asking the user to save.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if the document is dirty, FALSE otherwise.
 */

BOOL CCosmoDoc::FDirtyGet(void)
    {
    if (m_pFigure->FIsEmbedded())
        return FALSE;

    return m_fDirty;
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
    HRESULT         hr;
    LPSTORAGE       pIStorage;

    if (NULL==pszFile)
        {
        //For a new untitled document, just rename ourselves.
        Rename(NULL);
        m_lVer=VERSIONCURRENT;
        return DOCERR_NONE;
        }

    /*
     * If not a Compound File, open the file using STGM_CONVERT in
     * transacted mode to see old files as a storage with one stream
     * called "CONTENTS" (which is conveniently the name we use
     * in the new files).  We must use STGM_TRANSACTED here or else
     * the old file will be immediately converted on disk:  we only
     * want a converted image in memory from which to read.  In
     * addition, note that we need STGM_READWRITE as well since
     * conversion is inherently a write operation.
     */

    pIStorage=NULL;

    if (NOERROR!=StgIsStorageFile(pszFile))
        {
        hr=StgCreateDocfile(pszFile,STGM_TRANSACTED | STGM_READWRITE
            | STGM_CONVERT | STGM_SHARE_EXCLUSIVE, 0, &pIStorage);

        if (FAILED(hr))
            {
            //If denied write access, try to load the old way
            if (STG_E_ACCESSDENIED==GetScode(hr))
                m_lVer=m_pPL->ReadFromFile(pszFile);
            else
                return DOCERR_COULDNOTOPEN;
            }
        }
    else
        {
        hr=StgOpenStorage(pszFile, NULL, STGM_DIRECT | STGM_READ
            | STGM_SHARE_EXCLUSIVE, NULL, 0, &pIStorage);

        if (FAILED(hr))
            return DOCERR_COULDNOTOPEN;
        }

    if (NULL!=pIStorage)
        {
        m_lVer=m_pPL->ReadFromStorage(pIStorage);
        pIStorage->Release();
        }

    if (POLYLINE_E_READFAILURE==m_lVer)
        return DOCERR_READFAILURE;

    if (POLYLINE_E_UNSUPPORTEDVERSION==m_lVer)
        return DOCERR_UNSUPPORTEDVERSION;

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
 *  Writes the file to a known filename, requiring that the user has
 *  previously used FileOpen or FileSaveAs to provide a filename.
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
    LONG        lVer, lRet;
    UINT        uTemp;
    BOOL        fRename=TRUE;
    HRESULT     hr;
    LPSTORAGE   pIStorage;
    BOOL        fEmbedding;

    fEmbedding=m_pFigure->FIsEmbedded();

    if (NULL==pszFile)
        {
        fRename=FALSE;
        pszFile=m_szFile;
        }

    /*
     * Type 1 is the current version, type 2 is version 1.0 of the
     * Polyline so we use this to send the right version to
     * CPolyline::WriteToFile/WriteToStorage.
     */

    switch (uType)
        {
        case 0:         //From Save, use loaded version.
            lVer=m_lVer;
            break;

        case 1:
            lVer=VERSIONCURRENT;
            break;

        case 2:
            lVer=MAKELONG(0, 1);    //1.0
            break;

        default:
            return DOCERR_UNSUPPORTEDVERSION;
        }

    /*
     * If the version the user wants to save is different from the
     * version that we loaded and m_lVer is not zero (new doc),
     * then inform the user of the version change and verify.
     */

    //For embedding, this is Save Copy As, so don't ask about versions.
    if (0!=m_lVer && m_lVer!=lVer && !fEmbedding)
        {
        TCHAR       szMsg[128];

        wsprintf(szMsg, PSZ(IDS_VERSIONCHANGE)
            , (UINT)HIWORD(m_lVer), (UINT)LOWORD(m_lVer)
            , (UINT)HIWORD(lVer), (UINT)LOWORD(lVer));

        uTemp=MessageBox(m_hWnd, szMsg, PSZ(IDS_DOCUMENTCAPTION)
            , MB_YESNOCANCEL);

        if (IDCANCEL==uTemp)
            return DOCERR_CANCELLED;

        //If the user won't upgrade, revert to loaded version.
        if (IDNO==uTemp)
            lVer=m_lVer;
        }

    /*
     * For 1.0 files, still use the old code.  For new files, use
     * storages instead
     */
    if (lVer==MAKELONG(0, 1))
        lRet=m_pPL->WriteToFile(pszFile, lVer);
    else
        {
        hr=StgCreateDocfile(pszFile, STGM_DIRECT | STGM_READWRITE
            | STGM_CREATE | STGM_SHARE_EXCLUSIVE, 0, &pIStorage);

        if (FAILED(hr))
            return DOCERR_COULDNOTOPEN;

        //Mark this as one of our class
        WriteClassStg(pIStorage, CLSID_CosmoFigure);

        //Write user-readable class information
        WriteFmtUserTypeStg(pIStorage, m_cf
            , PSZ(IDS_CLIPBOARDFORMAT));

        lRet=m_pPL->WriteToStorage(pIStorage, lVer);
        pIStorage->Release();
        }

    if (POLYLINE_E_NONE!=lRet)
        return DOCERR_WRITEFAILURE;

    //Saving makes us clean, but this doesn't apply to embedding.
    if (!fEmbedding)
        FDirtySet(FALSE);

    //Update the known version of this document.
    m_lVer=lVer;

    /*
     * If we're embedding, this is Save Copy As, so no rename.
     * Note that we also don't care about having been set to clean
     * since we're always 'clean' as an embedded object from
     * the user's perspective.
     */
    if (fRename && !fEmbedding)
        Rename(pszFile);

    return DOCERR_NONE;
    }






/*
 * CCosmoDoc::Rename
 *
 * Purpose:
 *  Overrides the normal rename to manage a moniker for the open
 *  file.  We maintain no moniker for untitled documents, and
 *  therefore do not allow linking to such documents.
 *
 * Parameters:
 *  pszFile         LPTSTR to the new filename.
 *
 * Return Value:
 *  None
 */

void CCosmoDoc::Rename(LPTSTR pszFile)
    {
    LPMONIKER   pmk;

    //We don't need to change the base class, just augment...
    CDocument::Rename(pszFile);

    //Unregister the old moniker (m_dwRegROT set to zero).
    INOLE_RevokeAsRunning(&m_dwRegROT);

    ReleaseInterface(m_pMoniker);

    if (NULL!=pszFile)
        {
        CreateFileMoniker(pszFile, &pmk);

        if (NULL!=pmk)
            {
            m_pMoniker=pmk;     //pmk AddRef'd in CreateFileMoniker
            INOLE_RegisterAsRunning(m_pFigure, m_pMoniker
                , 0, &m_dwRegROT);

            m_pFigure->SendAdvise(OBJECTCODE_RENAMED);
            }
        }

    return;
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
    //CHAPTER23MOD
    //Give the in-place object a chance for DeactivateAndUndo.
    if (m_pFigure->Undo())
        return;
    //End CHAPTER23MOD

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
    BOOL            fRet=TRUE;
    LPDATAOBJECT    pIDataObject;

    pIDataObject=TransferObjectCreate(fCut);

    if (NULL==pIDataObject)
        return FALSE;

    fRet=SUCCEEDED(OleSetClipboard(pIDataObject));
    pIDataObject->Release();

    //Delete our current data if "cut" succeeded.
    if (fRet && fCut)
        {
        m_pPL->New();
        FDirtySet(TRUE);
        }


    return fRet;
    }





/*
 * CCosmoDoc::RenderFormat
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

HGLOBAL CCosmoDoc::RenderFormat(UINT cf)
    {
    HGLOBAL     hMem;

    if (cf==m_cf)
        {
        m_pPL->DataGetMem(VERSIONCURRENT, &hMem);
        return hMem;
        }

    switch (cf)
        {
        case CF_METAFILEPICT:
            return m_pPL->RenderMetafilePict();

        case CF_BITMAP:
            return (HGLOBAL)m_pPL->RenderBitmap();
        }

    return NULL;
    }




/*
 * CCosmoDoc::RenderMedium
 *
 * Purpose:
 *  Like RenderFormat, this function creates a specific data format
 *  based on the cf parameter.  Unlike RenderFormat, we store the
 *  result in a STGMEDIUM in case it has a medium other than
 *  TYMED_HGLOBAL.  For conveniece we'll centralize all compound
 *  document formats here, hGlobal or not.
 *
 * Parameters:
 *  cf              UINT clipboard format of interest.
 *  pSTM            LSTGMEDIUM to fill.  We only fill the union
 *                  and tymed.
 *
 * Return Value:
 *  BOOL            TRUE if we could render the format,
 *                  FALSE otherwise.
 */

BOOL CCosmoDoc::RenderMedium(UINT cf, LPSTGMEDIUM pSTM)
    {
    if (NULL==pSTM)
        return FALSE;

    if (cf==m_cfEmbedSource)
        {
        /*
         * Embed Source data is an IStorage containing the native
         * data (same as Embedded Object).  Since our data is small,
         * it makes the most sense to create an IStorage in memory
         * and put transfer that instead of a disk-based IStorage.
         */

        pSTM->pstg=INOLE_CreateStorageOnHGlobal(STGM_DIRECT
            | STGM_READWRITE | STGM_SHARE_EXCLUSIVE);

        if (NULL==pSTM->pstg)
            return FALSE;

        //Now save the data to the storage.
        WriteClassStg(pSTM->pstg, CLSID_CosmoFigure);
        WriteFmtUserTypeStg(pSTM->pstg, m_cf
            , PSZ(IDS_CLIPBOARDFORMAT));

        if (POLYLINE_E_NONE!=m_pPL->WriteToStorage(pSTM->pstg
            , VERSIONCURRENT))
            {
            /*
             * When someone releases the IStorage, STORAGE.DLL will
             * release the ILockBytes which, having fDeleteOnRelease
             * TRUE (second parameter) will release the memory.
             * That's why we don't have STGM_DELETEONRELEASE on the
             * IStorage.
             */
            pSTM->pstg->Release();
            return FALSE;
            }

        pSTM->tymed=TYMED_ISTORAGE;
        return TRUE;
        }

    /*
     * CFSTR_OBJECTDESCRIPTOR and CFSTR_LINKSRCDESCRIPTOR are the
     * same formats, but only copy link source if we have a moniker.
     */
    if (cf==m_cfLinkSrcDescriptor && NULL==m_pMoniker)
        return FALSE;

    if (cf==m_cfObjectDescriptor || cf==m_cfLinkSrcDescriptor)
        {
        SIZEL   szl, szlT;
        POINTL  ptl;
        RECT    rc;
        LPTSTR  psz=NULL;

        m_pPL->SizeGet(&rc);
        SETSIZEL(szlT, rc.right, rc.bottom);
        XformSizeInPixelsToHimetric(NULL, &szlT, &szl);

        SETPOINTL(ptl, 0, 0);

        //Include the moniker display name now, if we have one.
        if (m_pMoniker)
            {
            LPBC    pbc;

            CreateBindCtx(0, &pbc);
           #ifdef WIN32ANSI
            LPOLESTR    pszW;

            m_pMoniker->GetDisplayName(pbc, NULL, &pszW);
            psz=(LPTSTR)CoTaskMemAlloc(512);
            WideCharToMultiByte(CP_ACP, 0, pszW, -1, psz, 512
                , NULL, NULL);
            CoTaskMemFree((void *)pszW);
           #else
            m_pMoniker->GetDisplayName(pbc, NULL, &psz);
           #endif
            pbc->Release();
            }

        pSTM->hGlobal=INOLE_AllocObjectDescriptor
            (CLSID_CosmoFigure, DVASPECT_CONTENT, szl, ptl
            , OLEMISC_RECOMPOSEONRESIZE, PSZ(IDS_OBJECTDESCRIPTION)
            , psz);

        CoTaskMemFree((void *)psz);
        pSTM->tymed=TYMED_HGLOBAL;
        return (NULL!=pSTM->hGlobal);
        }

    if (cf==m_cfLinkSource)
        {
        if (NULL!=m_pMoniker)
            {
            FORMATETC   fe;
            HRESULT     hr;

            pSTM->tymed=TYMED_NULL;
            SETDefFormatEtc(fe, cf, TYMED_ISTREAM);
            hr=INOLE_GetLinkSourceData(m_pMoniker
                , (LPCLSID)&CLSID_CosmoFigure, &fe, pSTM);

            return SUCCEEDED(hr);
            }
        }

    return FALSE;
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

    fRet=FQueryPasteFromData(pIDataObject);
    pIDataObject->Release();
    return fRet;
    }



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

    fRet=PasteFromData(pIDataObject);
    pIDataObject->Release();

    return fRet;
    }




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

    if (fRet && NULL!=stm.hGlobal)
        {
        m_pPL->DataSetMem(stm.hGlobal, FALSE, FALSE, TRUE);
        ReleaseStgMedium(&stm);
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
 *  fCut            BOOL TRUE if we're cutting, FALSE if we're
 *                  copying.
 *
 * Return Value:
 *  LPDATAOBJECT    Pointer to the object created, NULL on failure
 */

LPDATAOBJECT CCosmoDoc::TransferObjectCreate(BOOL fCut)
    {
    UINT            i;
    HRESULT         hr;
    STGMEDIUM       stm;
    FORMATETC       fe;
    LPDATAOBJECT    pIDataObject=NULL;
    const UINT      cFormats=7;
    static UINT     rgcf[7]={0, 0, 0, CF_METAFILEPICT, CF_BITMAP, 0, 0};
    static DWORD    rgtm[7]={TYMED_HGLOBAL, TYMED_ISTORAGE, TYMED_HGLOBAL
        , TYMED_MFPICT, TYMED_GDI, TYMED_ISTREAM, TYMED_HGLOBAL};

    hr=CoCreateInstance(CLSID_DataTransferObject, NULL
        , CLSCTX_INPROC_SERVER, IID_IDataObject
        , (PPVOID)&pIDataObject);

    if (FAILED(hr))
        return NULL;

    rgcf[0]=m_cf;
    rgcf[1]=m_cfEmbedSource;
    rgcf[2]=m_cfObjectDescriptor;

    //Don't include link stuff for cutting (0 format always fails)
    if (!fCut)
        {
        rgcf[5]=m_cfLinkSource;
        rgcf[6]=m_cfLinkSrcDescriptor;
        }

    for (i=0; i < cFormats; i++)
        {
        /*
         * RenderFormat handles memory handles, but for compound doc
         * formats we need something more.  So if RenderFormat fails
         * (which it will for i=1, try our latest addition which
         * writes to a different field in the STGMEDIUM.
         */
        stm.hGlobal=RenderFormat(rgcf[i]);

        if (NULL==stm.hGlobal)
            {
            if (!RenderMedium(rgcf[i], &stm))
                continue;
            }

        stm.tymed=rgtm[i];
        stm.pUnkForRelease=NULL;
        SETDefFormatEtc(fe, rgcf[i], rgtm[i]);
        pIDataObject->SetData(&fe, &stm, TRUE);
        }

    return pIDataObject;    //Caller now responsible
    }



/*
 * CCosmoDoc::DropSelectTargetWindow
 * (Protected)
 *
 * Purpose:
 *  Creates a thin inverted frame around a window that we use to
 *  show the window as a drop target.  This is a toggle function:
 *  It uses XOR to create the effect so it must be called twice to
 *  leave the window as it was.
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

    hWnd=m_pPL->Window();
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





//CHAPTER23MOD
/*
 * CCosmoDoc::OpenInPlaceObject
 *
 * Purpose:
 *  Instructs the current figure object to open into a window from
 *  in-place active state, if applicable.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CCosmoDoc::OpenInPlaceObject(void)
    {
    if (NULL!=m_pFigure)
        m_pFigure->OpenIntoWindow();

    return;
    }

//End CHAPTER23MOD




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
    return m_pPL->ColorSet(iColor, cr);
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
    return m_pPL->ColorGet(iColor);
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
    return m_pPL->LineStyleSet(iStyle);
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
    if (NULL==m_pPL)    //m_pPL might not be valid yet
        return 0L;

    return m_pPL->LineStyleGet();
    }








/*
 * CPolylineAdviseSink::CPolylineAdviseSink
 * CPolylineAdviseSink::~CPolylineAdviseSink
 *
 * Constructor Parameters:
 *  pv              LPVOID to store in this object
 */

CPolylineAdviseSink::CPolylineAdviseSink(LPVOID pv)
    {
    m_pv=pv;
    return;
    }


CPolylineAdviseSink::~CPolylineAdviseSink(void)
    {
    return;
    }





/*
 * CPolylineAdviseSink::OnPointChange
 *
 * Purpose:
 *  Informs the document that the polyline added or removed a point.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CPolylineAdviseSink::OnPointChange(void)
    {
    PCDocument      pDoc=(PCDocument)m_pv;

    pDoc->FDirtySet(TRUE);
    return;
    }






/*
 * CPolylineAdviseSink::OnSizeChange
 *
 * Purpose:
 *  Informs the document that the polyline changed size.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CPolylineAdviseSink::OnSizeChange(void)
    {
    PCCosmoDoc      pDoc=(PCCosmoDoc)m_pv;
    RECT            rc;
    DWORD           dwStyle;

    /*
     * Polyline window is informing us that it changed size in
     * response to setting it's data.  Therefore we have to
     * size ourselves accordingly but without moving the screen
     * position of the polyline window.
     */

    pDoc->m_fNoSize=TRUE;

    //Set the document window size.
    GetWindowRect(pDoc->m_pPL->Window(), &rc);
    InflateRect(&rc, 8, 8);

    //Adjust for a window sans menu
    dwStyle=GetWindowLong(pDoc->m_hWnd, GWL_STYLE);
    AdjustWindowRect(&rc, dwStyle, FALSE);

    SetWindowPos(pDoc->m_hWnd, NULL, 0, 0, rc.right-rc.left
        , rc.bottom-rc.top, SWP_NOMOVE | SWP_NOZORDER);

    if (NULL!=pDoc->m_pAdv)
        pDoc->m_pAdv->OnSizeChange(pDoc, &rc);

    pDoc->m_fNoSize=FALSE;
    pDoc->FDirtySet(TRUE);

    return;
    }





/*
 * CPolylineAdviseSink::OnDataChange
 *
 * Purpose:
 *  Informs the document that the polyline data changed.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CPolylineAdviseSink::OnDataChange(void)
    {
    PCCosmoDoc      pDoc=(PCCosmoDoc)m_pv;

    if (NULL!=pDoc->m_pAdv)
        pDoc->m_pAdv->OnDataChange(pDoc);

    pDoc->FDirtySet(TRUE);
    return;
    }





/*
 * CPolylineAdviseSink::OnColorChange
 *
 * Purpose:
 *  Informs the document that the polyline data changed a color.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CPolylineAdviseSink::OnColorChange(void)
    {
    PCCosmoDoc      pDoc=(PCCosmoDoc)m_pv;

    pDoc->FDirtySet(TRUE);
    return;
    }





/*
 * CPolylineAdviseSink::OnLineStyleChange
 *
 * Purpose:
 *  Informs the document that the polyline changed its line style.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CPolylineAdviseSink::OnLineStyleChange(void)
    {
    PCCosmoDoc      pDoc=(PCCosmoDoc)m_pv;

    pDoc->FDirtySet(TRUE);
    return;
    }
