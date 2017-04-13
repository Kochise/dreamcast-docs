/*
 * DOCUMENT.CPP
 * Cosmo Chapter 12
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
    return;
    }


CCosmoDoc::~CCosmoDoc(void)
    {
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
    if (0!=m_lVer && m_lVer!=lVer)
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

    //Saving makes us clean
    FDirtySet(FALSE);

    //Update the known version of this document.
    m_lVer=lVer;

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
    BOOL            fRet=TRUE;
    HGLOBAL         hMem;
    UINT            i;
    static UINT     rgcf[3]={0, CF_METAFILEPICT, CF_BITMAP};
    const UINT      cFormats=3;

    //CHAPTER12MOD
    static DWORD    rgtm[3]={TYMED_HGLOBAL, TYMED_MFPICT, TYMED_GDI};
    LPDATAOBJECT    pIDataObject;
    HRESULT         hr;
    STGMEDIUM       stm;
    FORMATETC       fe;

    hr=CoCreateInstance(CLSID_DataTransferObject
        , NULL, CLSCTX_INPROC_SERVER
        , IID_IDataObject, (PPVOID)&pIDataObject);

    if (FAILED(hr))
        return NULL;
    //End CHAPTER12MOD

    rgcf[0]=m_cf;

    for (i=0; i < cFormats; i++)
        {
        //Copy private data first.
        hMem=RenderFormat(rgcf[i]);

        if (NULL!=hMem)
            {
            //CHAPTER12MOD
            stm.hGlobal=hMem;
            stm.tymed=rgtm[i];
            stm.pUnkForRelease=NULL;

            SETDefFormatEtc(fe, rgcf[i], rgtm[i]);
            pIDataObject->SetData(&fe, &stm, TRUE);
            //End CHAPTER12MOD
            }
        }

    //CHAPTER12MOD
    fRet=SUCCEEDED(OleSetClipboard(pIDataObject));
    pIDataObject->Release();
    //End CHAPTER12MOD

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
    //CHAPTER12MOD
    LPDATAOBJECT    pIDataObject;
    BOOL            fRet;

    if (FAILED(OleGetClipboard(&pIDataObject)))
        return FALSE;

    fRet=FQueryPasteFromData(pIDataObject);
    pIDataObject->Release();
    return fRet;
    //End CHAPTER12MOD
    }



//CHAPTER12MOD
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
//End CHAPTER12MOD




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
    //CHAPTER12MOD
    LPDATAOBJECT    pIDataObject;
    BOOL            fRet;

    if (FAILED(OleGetClipboard(&pIDataObject)))
        return FALSE;

    fRet=PasteFromData(pIDataObject);
    pIDataObject->Release();

    //End CHAPTER12MOD
    return fRet;
    }




//CHAPTER12MOD
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
//End CHAPTER12MOD




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
