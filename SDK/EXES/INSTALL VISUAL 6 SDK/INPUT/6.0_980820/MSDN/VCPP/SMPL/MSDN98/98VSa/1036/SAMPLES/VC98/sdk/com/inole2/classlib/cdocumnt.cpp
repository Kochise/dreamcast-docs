/*
 * CDOCUMNT.CPP
 * Sample Code Class Libraries
 *
 * Implementation of the CDocument class.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include <windows.h>
#include <string.h>
#include "classlib.h"


/*
 * CDocument::CDocument
 * CDocument::~CDocument
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE of the application.
 *  pFR             PCFrame, a back pointer to the frame window.
 *  pAdv            PCDocumentAdviseSink to notify on events.
 */

CDocument::CDocument(HINSTANCE hInst, PCFrame pFR
    , PCDocumentAdviseSink pAdv)
    : CWindow(hInst)
    {
    m_pFR=pFR;
    m_pST=NULL;
    m_pAdv=pAdv;
    return;
    }


CDocument::~CDocument(void)
    {
    if (NULL!=m_pST)
        delete m_pST;

    return;
    }






/*
 * CDocument::Init
 *
 * Purpose:
 *  Initializes an already created document window.  The client
 *  actually creates the window then passes that here for further
 *  initialization.
 *
 * Parameters:
 *  pDI             PDOCUMENTINIT containing initialization params
 *
 * Return Value:
 *  BOOL            TRUE if the function succeeded, FALSE otherwise.
 */

BOOL CDocument::Init(PDOCUMENTINIT pDI)
    {
    if (NULL==pDI)
        return FALSE;

    if (NULL==pDI->hWndDoc)
        return FALSE;

    //Create our stringtable
    m_pST=new CStringTable(m_hInst);

    if (!m_pST->Init(pDI->idsMin, pDI->idsMax))
        return FALSE;

    m_hWnd=pDI->hWndDoc;
    m_cf=RegisterClipboardFormat(PSZ(IDS_CLIPBOARDFORMAT));

    m_fDirty=FALSE;
    m_fNoDirty=FALSE;
    m_fNoSize=FALSE;

    m_fFileKnown=FALSE;
    m_szFile[0]=0;

    return TRUE;
    }








/*
 * CDocument::FMessageHook
 *
 * Purpose:
 *  Provides a derivation of the base CDocument class to hook all
 *  messages to the window procedure for special processing,
 *  including WM_COMMAND since that is much less common for a
 *  document than for a frame (see CFrame::OnCommand).
 *
 * Parameters:
 *  <WndProc Parameters>
 *  pLRes           LRESULT * in which to store the return value
 *                  for the message.
 *
 * Return Value:
 *  BOOL            TRUE to prevent further processing, FALSE
 *                  otherwise.
 */

BOOL CDocument::FMessageHook(HWND hWnd, UINT iMsg, WPARAM wParam
    , LPARAM lParam, LRESULT *pLRes)
    {
    *pLRes=0;
    return FALSE;
    }






/*
 * CDocument::FDirtySet
 *
 * Purpose:
 *  Sets or clears the document 'dirty' flag returning the previous
 *  state of that same flag.
 *
 * Parameters:
 *  fDirty          BOOL indicating the new contents of the dirty
 *                  flag.
 *
 * Return Value:
 *  BOOL            Previous value of the dirty flag.
 */

BOOL CDocument::FDirtySet(BOOL fDirty)
    {
    BOOL        fPrevious;

    /*
     * If we are a hidden window, then there's nothing that could
     * make us dirty since there cannot be any user interaction here.
     */
    if (!IsWindowVisible(m_hWnd))
        return m_fDirty;

    //Ignore the initial WM_SIZE on creation.
    if (m_fNoDirty)
        return m_fDirty;

    fPrevious=m_fDirty;
    m_fDirty=fDirty;

    return fPrevious;
    }





/*
 * CDocument::FDirtyGet
 *
 * Purpose:
 *  Returns the current dirty status of the document.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if the file is clean, FALSE otherwise.
 */

BOOL CDocument::FDirtyGet()
    {
    return m_fDirty;
    }





/*
 * CDocument::Clear
 *
 * Purpose:
 *  Sets all contents in the document back to defaults with no
 *  filename.
 *
 * Paramters:
 *  None
 *
 * Return Value:
 *  None
 */

void CDocument::Clear()
    {
    FDirtySet(FALSE);
    Rename(NULL);
    return;
    }






/*
 * CDocument::Load
 *
 * Purpose:
 *  Function that derived classes override.  Does nothing in base
 *  class.
 *
 * Parameters:
 *  fChangeFile     BOOL indicating if we're to update the window
 *                  title and the filename from using this file.
 *  pszFile         LPTSTR to the filename to load.  If NULL then this
 *                  is a new, untitled file, so perform any
 *                  initialization for such a case.
 *
 * Return Value:
 *  UINT            An error value from DOCERR_.  Always
 *                  DOCERR_NOFILE here.
 */

UINT CDocument::Load(BOOL fChangeFile, LPTSTR pszFile)
    {
    Rename(NULL);
    return DOCERR_NOFILE;
    }







/*
 * CDocument::Save
 *
 * Purpose:
 *  Function that derived classes override.  Does nothing in base
 *  class.
 *
 * Parameters:
 *  uType           UINT type of file to save (from Save As dialog).
 *  pszFile         LPTSTR providing the name under which we should
 *                  save.  If NULL, then use the current name.  If
 *                  non-NULL, then call Rename if save is successful
 *                  and the name has changed.
 * Return Value:
 *  UINT            An error value from DOCERR_.  Always
 *                  DOCERR_NOFILE here.
 */

UINT CDocument::Save(UINT uType, LPTSTR pszFile)
    {
    return DOCERR_NOFILE;
    }





/*
 * CDocument::ErrorMessage
 *
 * Purpose:
 *  Displays an error message to the user appropriate for a given
 *  error code.  If the code is DOCERR_NONE then this is a NOP.
 *
 * Parameters:
 *  uErr            UINT identifying the error code.
 *
 * Return Value:
 *  None
 */

void CDocument::ErrorMessage(UINT uErr)
    {
    LPTSTR      psz;

    switch (uErr)
        {
        case DOCERR_NONE:
            psz=NULL;
            break;

        case DOCERR_NOFILE:
            psz=PSZ(IDS_FILEDOESNOTEXIST);
            break;

        case DOCERR_COULDNOTOPEN:
            psz=PSZ(IDS_FILEOPENERROR);
            break;

        case DOCERR_READFAILURE:
            psz=PSZ(IDS_FILELOADERROR);
            break;

        case DOCERR_UNSUPPORTEDVERSION:
            psz=PSZ(IDS_VERSIONMISMATCH);
            break;

        case DOCERR_WRITEFAILURE:
            psz=PSZ(IDS_FILESAVEERROR);
            break;

        case DOCERR_CANCELLED:
            //No message on this.
            return;

        default:
            psz=PSZ(IDS_UNKNOWNERROR);
            break;
        }

    if (NULL!=psz)
        MessageBox(m_hWnd, psz, PSZ(IDS_DOCUMENTCAPTION), MB_OK);

    return;
    }










/*
 * CDocument::Clip
 *
 * Purpose:
 *  Places document data on the clipboard, optionally implementing
 *  Cut by deleting the data in the current window after rendering.
 *
 * Parameters:
 *  hWndFrame       HWND of the main window.
 *  fCut            BOOL indicating cut (TRUE) or copy (FALSE).
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CDocument::Clip(HWND hWndFrame, BOOL fCut)
    {
    return FALSE;
    }




/*
 * CDocument::RenderFormat
 *
 * Purpose:
 *  Returns a global memory handle containing a specific clipboard
 *  format.
 *
 * Parameters:
 *  cf              UINT format to render
 *
 * Return Value:
 *  HGLOBAL         Memory handle of the rendering.
 */

HGLOBAL CDocument::RenderFormat(UINT cf)
    {
    return NULL;
    }






/*
 * CDocument::FQueryPaste
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

BOOL CDocument::FQueryPaste(void)
    {
    return IsClipboardFormatAvailable(m_cf);
    }





/*
 * CDocument::Paste
 *
 * Purpose:
 *  Retrieves the private data format from the clipboard and sets it
 *  as the current data.
 *
 *  Note that if this function is called, then the clipboard format
 *  is available because the Paste menu item is only enabled if the
 *  format is present.
 *
 * Parameters:
 *  hWndFrame       HWND of the main window
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CDocument::Paste(HWND hWndFrame)
    {
    return FALSE;
    }







/*
 * CDocument::Undo
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

void CDocument::Undo(void)
    {
    return;
    }






/*
 * CDocument::FQuerySave
 *
 * Purpose:
 *  Returns whether or not a call to FSave will work.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if we have a known file, FALSE otherwise.
 */

BOOL CDocument::FQuerySave(void)
    {
    return m_fFileKnown;
    }






/*
 * CDocument::Rename
 *
 * Purpose:
 *  Changes the name of the current file we're dealing with but
 *  does no disk action.  FSave should be used after this
 *  call to implement a Save As operation.
 *
 * Parameters:
 *  pszFile         LPTSTR to the filename to save ourselves under.
 *
 * Return Value:
 *  None
 */

void CDocument::Rename(LPTSTR pszFile)
    {
    //Clear out the filename on pszFile==NULL.
    if (NULL==pszFile)
        {
        m_szFile[0]=0;
        m_fFileKnown=FALSE;

        //Tell the associate window to change captions.
        if (NULL!=m_pAdv)
            m_pAdv->OnCaptionChange(this);
        }

    //First, check if anything changed
    if (NULL!=pszFile && 0!=lstrcmpi(m_szFile, pszFile))
        {
        /*
         * Copy the new filename to the document structure and inform
         * associate
         */
        lstrcpyn(m_szFile, pszFile, CCHPATHMAX);

        if (NULL!=m_pAdv)
            m_pAdv->OnCaptionChange(this);

        m_fFileKnown=TRUE;
        }

    return;
    }





/*
 * CDocument::FilenameGet
 *
 * Purpose:
 *  Retrieves the current filename used in the document.
 *
 * Parameters:
 *  psz             LPTSTR in which to store the filename.
 *  cchMax          UINT maximum number of characters to copy.
 *
 * Return Value:
 *  UINT            Number of characters copied.
 */

UINT CDocument::FilenameGet(LPTSTR psz, UINT cchMax)
    {
    UINT        uRet=0;

    if (NULL!=psz)
        {
        lstrcpyn(psz, m_szFile, cchMax);
        uRet=lstrlen(m_szFile);
        }

    return uRet;
    }




/*
 * CDocument::FrameGet
 *
 * Purpose:
 *  Returns the CFrame pointer of the application frame.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  PCFrame         Pointer to the frame object.
 */

PCFrame CDocument::FrameGet(void)
    {
    return m_pFR;
    }
