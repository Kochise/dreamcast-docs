/*
 * DOCUMENT.CPP
 * Component Cosmo Chapter 5
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

    //CHAPTER5MOD
    m_pIConnectPt=NULL;
    m_dwCookie=0;
    //End CHAPTER5MOD
    return;
    }


CCosmoDoc::~CCosmoDoc(void)
    {
    //CHAPTER5MOD
    if (NULL!=m_pIConnectPt)
        {
        m_pIConnectPt->Unadvise(m_dwCookie);
        ReleaseInterface(m_pIConnectPt);
        }

    ReleaseInterface(m_pPL);
    ReleaseInterface(m_pPLAdv);

    CoFreeUnusedLibraries();
    //End CHAPTER5MOD

    //The client takes care of destroying document windows.
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
    //CHAPTER5MOD
    IConnectionPointContainer  *pCPC;
    //EndCHAPTER5MOD

    //Change the stringtable range to our customization.
    pDI->idsMin=IDS_DOCUMENTMIN;
    pDI->idsMax=IDS_DOCUMENTMAX;

    //Do default initialization
    if (!CDocument::Init(pDI))
        return FALSE;

    //CHAPTER5MOD
    //Create the Polyline component
    hr=CoCreateInstance(CLSID_Polyline5, NULL, CLSCTX_INPROC_SERVER
        , IID_IPolyline5, (PPVOID)&m_pPL);

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
        if (SUCCEEDED(pCPC->FindConnectionPoint
            (IID_IPolylineAdviseSink5, &m_pIConnectPt)))
            {
            m_pIConnectPt->Advise((LPUNKNOWN)m_pPLAdv, &m_dwCookie);
            }

        pCPC->Release();
        }
    //End CHAPTER5MOD

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

    if (NULL==pszFile)
        {
        //For a new untitled document, just rename ourselves.
        Rename(NULL);
        return DOCERR_NONE;
        }

    //CHAPTER5MOD
    hr=m_pPL->ReadFromFile(pszFile);

    if (POLYLINE_E_READFAILURE==GetScode(hr))
        return DOCERR_READFAILURE;
    //End CHAPTER5MOD

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
    BOOL                fRename=TRUE;
    //CHAPTER5MOD
    HRESULT             hr;
    //End CHAPTER5MOD

    if (NULL==pszFile)
        {
        fRename=FALSE;
        pszFile=m_szFile;
        }

    /*
     * In Component Cosmo, we only deal with one version of data,
     * so all the code in Chapter 1 Cosmo that dealt with 1.0 and
     * 2.0 files has been removed.
     */

    //CHAPTER5MOD
    hr=m_pPL->WriteToFile(pszFile);

    if (FAILED(hr))
        return DOCERR_WRITEFAILURE;
    //End CHAPTER5MOD

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
    BOOL            fRet=TRUE;
    HGLOBAL         hMem;
    UINT            i;

    //This array is so we can loop over the formats we provide.
    static UINT     rgcf[3]={0, CF_METAFILEPICT, CF_BITMAP};
    const UINT      cFormats=3;

    if (!OpenClipboard(hWndFrame))
        return FALSE;

    //Clean out whatever junk is in the clipboard.
    EmptyClipboard();

    rgcf[0]=m_cf;

    for (i=0; i < cFormats; i++)
        {
        //Copy private data first.
        hMem=RenderFormat(rgcf[i]);

        if (NULL!=hMem)
            SetClipboardData(rgcf[i], hMem);
        else
            fRet &=FALSE;
        }

    //Free clipboard ownership.
    CloseClipboard();

    //Delete our current data if copying succeeded.
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
        //CHAPTER5MOD
        m_pPL->DataGetMem(&hMem);
        //End CHAPTER5MOD
        return hMem;
        }

    switch (cf)
        {
        case CF_METAFILEPICT:
            //CHAPTER5MOD
            m_pPL->RenderMetafilePict(&hMem);
            return hMem;
            //End CHAPTER5MOD

        case CF_BITMAP:
            m_pPL->RenderBitmap((HBITMAP *)&hMem);
            return hMem;
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
    return IsClipboardFormatAvailable(m_cf);
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
    HGLOBAL         hMem;
    PPOLYLINEDATA   ppl;
    BOOL            fRet=FALSE;

    if (!OpenClipboard(hWndFrame))
        return FALSE;

    hMem=GetClipboardData(m_cf);

    if (NULL!=hMem)
        {
        ppl=(PPOLYLINEDATA)GlobalLock(hMem);

        //TRUE in wParam to cause PLN_SIZECHANGE notification
        m_pPL->DataSet(ppl, FALSE, TRUE);
        GlobalUnlock(hMem);

        FDirtySet(TRUE);
        fRet=TRUE;
        }

    CloseClipboard();
    return fRet;
    }






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
    //CHAPTER5MOD
    COLORREF    crRet;

    m_pPL->ColorSet(iColor, cr, &crRet);
    return crRet;
    //End CHAPTER5MOD
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
    //CHAPTER5MOD
    COLORREF    crRet;

    m_pPL->ColorGet(iColor, &crRet);
    return crRet;
    //End CHAPTER5MOD
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
    //CHAPTER5MOD
    UINT    i;

    m_pPL->LineStyleSet(iStyle, &i);
    return i;
    //End CHAPTER5MOD
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
    //CHAPTER5MOD
    UINT    i=0;

    //m_pPL might not be valid yet.
    if (NULL!=m_pPL)
        m_pPL->LineStyleGet(&i);

    return i;
    //End CHAPTER5MOD
    }







/*
 * CPolylineAdviseSink::CPolylineAdviseSink
 * CPolylineAdviseSink::~CPolylineAdviseSink
 *
 * Constructor Parameters:
 *  pDoc            PCCosmoDoc to store in this object
 */

CPolylineAdviseSink::CPolylineAdviseSink(PCCosmoDoc pDoc)
    {
    //CHAPTER5MOD
    m_pDoc=pDoc;
    m_cRef=0;
    AddRef();
    //End CHAPTER5MOD
    return;
    }


CPolylineAdviseSink::~CPolylineAdviseSink(void)
    {
    return;
    }




//CHAPTER5MOD
/*
 * CPolylineAdviseSink::QueryInterface
 * CPolylineAdviseSink::AddRef
 * CPolylineAdviseSink::Release
 *
 * Purpose:
 *  IUnknown members for this IPolylineAdviseSink implementations.
 */

STDMETHODIMP CPolylineAdviseSink::QueryInterface(REFIID riid
    , PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IPolylineAdviseSink5==riid)
        *ppv=this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(S_FALSE);
    }


STDMETHODIMP_(ULONG) CPolylineAdviseSink::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CPolylineAdviseSink::Release(void)
    {
    if (0L!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }
//End CHAPTER5MOD




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

STDMETHODIMP_(void) CPolylineAdviseSink::OnPointChange(void)
    {
    m_pDoc->FDirtySet(TRUE);
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

STDMETHODIMP_(void) CPolylineAdviseSink::OnSizeChange(void)
    {
    RECT            rc;
    DWORD           dwStyle;

    //CHAPTER5MOD
    HWND            hWnd;

    /*
     * Polyline window is informing us that it changed size in
     * response to setting it's data.  Therefore we have to
     * size ourselves accordingly but without moving the screen
     * position of the polyline window.
     */

    m_pDoc->m_fNoSize=TRUE;

    //Set the document window size.
    //CHAPTER5MOD
    m_pDoc->m_pPL->Window(&hWnd);
    //End CHAPTER5MOD
    GetWindowRect(hWnd, &rc);
    InflateRect(&rc, 8, 8);

    //Adjust for a window sans menu
    dwStyle=GetWindowLong(m_pDoc->m_hWnd, GWL_STYLE);
    AdjustWindowRect(&rc, dwStyle, FALSE);

    SetWindowPos(m_pDoc->m_hWnd, NULL, 0, 0, rc.right-rc.left
        , rc.bottom-rc.top, SWP_NOMOVE | SWP_NOZORDER);

    if (NULL!=m_pDoc->m_pAdv)
        m_pDoc->m_pAdv->OnSizeChange(m_pDoc, &rc);

    m_pDoc->m_fNoSize=FALSE;
    m_pDoc->FDirtySet(TRUE);

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

STDMETHODIMP_(void) CPolylineAdviseSink::OnDataChange(void)
    {
    if (NULL!=m_pDoc->m_pAdv)
        m_pDoc->m_pAdv->OnDataChange(m_pDoc);

    m_pDoc->FDirtySet(TRUE);
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

STDMETHODIMP_(void) CPolylineAdviseSink::OnColorChange(void)
    {
    m_pDoc->FDirtySet(TRUE);
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

STDMETHODIMP_(void) CPolylineAdviseSink::OnLineStyleChange(void)
    {
    m_pDoc->FDirtySet(TRUE);
    return;
    }
