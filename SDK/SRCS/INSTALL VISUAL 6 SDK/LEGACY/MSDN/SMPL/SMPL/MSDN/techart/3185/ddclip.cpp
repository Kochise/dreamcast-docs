//////////////////////////////////////////////////////////////
// Clipboard and Drag/drop support functions

#include "stdafx.h"
#include "afxpriv.h" // for CSharedFile
#include "resource.h" // for IDC_DDCNODROP and IDC_DDCDROPOK
#include "ddclip.h"

// messages 
UINT ddcMsgQueryDrop = ::RegisterWindowMessage("DDCQUERYDROP");
UINT ddcMsgDoDrop = ::RegisterWindowMessage("DDCDODROP");
UINT ddcMsgBeginDragDrop = ::RegisterWindowMessage("DDCBEGINDRAGDROP");

// private constants
#define MAPFILENAME "\\DDC-DATA.TMP"

// private data
static const char* szWndClass = NULL;

// Create a global memory chunk for the clipboard
HGLOBAL CreateClipboardData(CObject* pObject)
{
    // Create a memory file based archive
    CSharedFile mf (GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT);
    CArchive ar(&mf, CArchive::store);  
    pObject->Serialize(ar);
    ar.Close(); // flush and close
    HGLOBAL hMem = mf.Detach();
    ASSERT(hMem);
    return hMem;
}

BOOL SetClipboardObject(UINT uiFmt, CObject* pObject)
{
    HGLOBAL hMem = CreateClipboardData(pObject);
    if (!hMem) return FALSE;
    // Send the clipboard the data
    ::OpenClipboard(NULL);
    ::EmptyClipboard();
    ::SetClipboardData(uiFmt, hMem);
    ::CloseClipboard();
    return TRUE;
}

BOOL GetClipboardObject(CWnd* pWnd, UINT uiFmt, CObject* pObject)
{
    ASSERT(pWnd);
    ASSERT(pObject);
    ::OpenClipboard(pWnd->m_hWnd);
    HGLOBAL hMem = ::GetClipboardData(uiFmt);
    if (!hMem) {
        TRACE("No data found in clipboard");
        ::CloseClipboard();
        return FALSE;
    }
    // Create a mem file
    CSharedFile mf;
    mf.SetHandle(hMem);
    // Create the archive and get the data
    CArchive ar(&mf, CArchive::load);  
    pObject->Serialize(ar);
    ar.Close();
    mf.Detach();
    ::CloseClipboard();
    return TRUE;
}

// Initiate a drag and drop sequence
void BeginDragDrop(CWnd* pSourceWnd, UINT uiFmt, CObject* pObject)
{
    // Serialize the object to a file
    // Get the directory for temp files
    char szPath[_MAX_PATH];
    ::GetTempPath(sizeof(szPath), szPath);
    // Create the full file name
    strcat(szPath, MAPFILENAME);
    // Create a new file
    CFile DataFile(szPath, CFile::modeCreate|CFile::modeReadWrite);
    CArchive ar(&DataFile, CArchive::store);  
    pObject->Serialize(ar);
    ar.Close(); // flush and close
    DataFile.Close();
    // Capture the mouse so we can control what happens next
    CDdcWnd* pWnd = new CDdcWnd(pSourceWnd, uiFmt);
    ASSERT(pWnd);
}

BOOL GetDropData(CObject* pObject)
{
    ASSERT(pObject);
    // Open the temp file
    char szPath[_MAX_PATH];
    ::GetTempPath(sizeof(szPath), szPath);
    // Create the full file name
    strcat(szPath, MAPFILENAME);
    CFile DataFile(szPath, CFile::modeRead);
    // Create the archive and get the data
    CArchive ar(&DataFile, CArchive::load);  
    pObject->Serialize(ar);
    ar.Close();
    DataFile.Close();
    return TRUE;
}

/////////////////////////////////////////////////////////////////
// CDdcWnd

BEGIN_MESSAGE_MAP(CDdcWnd, CWnd)
    //{{AFX_MSG_MAP(CDdcWnd)
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CDdcWnd::CDdcWnd(CWnd* pSourceWnd, UINT uiFmt)
{
    // Save the paramters
    ASSERT(pSourceWnd);
    m_hwndSource = pSourceWnd->m_hWnd; 
    m_uiFmt = uiFmt;
    // Create the window
    if (!szWndClass) {
        szWndClass = AfxRegisterWndClass(WS_POPUP);
    }
    CreateEx(0, szWndClass, "", WS_POPUP, 0, 0, 0, 0, NULL, NULL);
    m_hwndUnder = NULL;
    // Load the cursors
    m_hcurNoDrop = ::LoadCursor(AfxGetResourceHandle(),
                                MAKEINTRESOURCE(IDC_DDCNODROP));
    m_hcurDropOK = ::LoadCursor(AfxGetResourceHandle(),
                                MAKEINTRESOURCE(IDC_DDCDROPOK));

    // Save the existing cursor
    m_hcurOld = ::SetCursor(NULL);
    ::SetCursor(m_hcurOld);
    // Capture the mouse
    m_hwndOldCapture = ::GetCapture();
    SetCapture();
}

void CDdcWnd::OnMouseMove(UINT nFlags, CPoint point)
{
    // Convert the mouse coords to screen coords
    ClientToScreen(&point);
    // Find the window it's over
    CWnd* pWnd = WindowFromPoint(point);
    // Note; pWnd is temporary so don't store it!
    if (!pWnd) {
        ::SetCursor(m_hcurNoDrop);
        m_hwndUnder = NULL;
        return;
    }
    HWND hWnd = pWnd->m_hWnd;
    // See if this is a new window
    if (hWnd == m_hwndUnder) {
        // no it isn't so don't do anything
        return;
    }
    // If this is the source window show the OK to drop cursor
    // See if this window will accept a drop
    // The window will set the cursor if it wants drop etc.
    if ((hWnd == m_hwndSource)
    || (pWnd->SendMessage(ddcMsgQueryDrop, m_uiFmt, 0))) {
        ::SetCursor(m_hcurDropOK);
    } else {
        ::SetCursor(m_hcurNoDrop);
    }
    m_hwndUnder = hWnd;
}

void CDdcWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
    // don't drop on the source window
    if ((m_hwndUnder) 
    && (m_hwndUnder != m_hwndSource)) {

        // See if we can drop here
        if (::SendMessage(m_hwndUnder, ddcMsgQueryDrop, m_uiFmt, 0)) {
            // Yes
            ::SendMessage(m_hwndUnder,
                          ddcMsgDoDrop,
                          m_uiFmt,
                          (LPARAM)0);
        }
    }
    m_hwndUnder = NULL;
    // Restore the cursor etc.
    ::SetCursor(m_hcurOld);
    ReleaseCapture();
    if (m_hwndOldCapture) {
        ::SetCapture(m_hwndOldCapture); 
    }   
    DestroyWindow();
    delete this;
}

