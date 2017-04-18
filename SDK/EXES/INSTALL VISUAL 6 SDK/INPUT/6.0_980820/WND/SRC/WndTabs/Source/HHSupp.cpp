////////////////////////////////////////////////////////////////////
// HHSupp.cpp : HTML Help Support Module for MFC Applications
//
// by Oz Solomonovich (osolo@bigfoot.com)

#include "stdafx.h"
#include <afxpriv.h>   // for WM_COMMANDHELP
#include <afxtempl.h>
//#include "htmlhelp.h"  // from HTML Help SDK
#include "HHSupp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


LPCTSTR g_pszPopupWinTypeName         = _T("PopupTopicWnd");
bool    g_bHTMLHelp_ShowNoHelpMessage = true;


typedef HWND (WINAPI fnHtmlHelp)(HWND hwndCaller, LPCTSTR pszFile,
                                 UINT uCommand, DWORD_PTR dwData); 

static HMODULE     s_modHH;
static fnHtmlHelp *s_pfnHtmlHelp;
static CMenu       s_WhatsThis;
static CMap<int, int, CString, LPCTSTR> s_WinTypeMap;



#define WHATS_THIS      _T("&What's This?")
#define FILE_NOT_FOUND  _T("Cannot find the help file %s.\n") \
                        _T("Would you like to locate it yourself?")
#define NO_HELP_FNT     _T("MS Sans Serif,8,,")
#define NO_HELP_TXT     \
    _T("No help information is available for this item.")

// forward declarations
static void ShowHelp(HWND hWnd, int ctrlID, DWORD helpID, 
    LPCTSTR pszHelpWndType = NULL, LPCTSTR pszHelpFile = APP_CHM);
static DWORD FindHelpID(const DWORD *ids, DWORD ctrlID, 
    bool bAllowImplicit);
static BOOL DoHelpInfo(CWnd *pDlg, const DWORD *pHelpIDs, 
    HELPINFO* pHelpInfo, bool bAllowImplicit);
static void DoContextMenu(CWnd *pDlg, const DWORD *pHelpIDs, 
    CWnd *pWnd, CPoint point, bool bAllowImplicit);
static CString& GetHelpFile();


void InitHHSupp()
{
    s_modHH = AfxLoadLibrary(_T("HHCTRL.OCX"));
    if (s_modHH)
        s_pfnHtmlHelp = (fnHtmlHelp *)::GetProcAddress(s_modHH, 
#ifdef UNICODE
            (LPCSTR)ATOM_HTMLHELP_API_UNICODE);
#else    
            ATOM_HTMLHELP_API_ANSI);
#endif
    else
        s_pfnHtmlHelp = NULL;

    if (s_pfnHtmlHelp)
    {
        s_WhatsThis.CreatePopupMenu();
        s_WhatsThis.InsertMenu(0, MF_BYPOSITION, 1, WHATS_THIS);
    }
}

void EndHHSupp()
{
    if (s_modHH)
    {
        AfxFreeLibrary(s_modHH);
        s_modHH = NULL;
    }
}

// this auto initializing/destructing object will ensure that the
// that the initialization/cleanup code is called on program
// start/end
static struct auto_init
{ 
    auto_init()  { InitHHSupp(); }
    ~auto_init() { EndHHSupp(); }
} autoinit;



////////////////////////////////////////////////////////////////////
// Internal operations

static DWORD FindHelpID(const DWORD *ids, DWORD ctrlID, 
    bool bAllowImplicit)
{
    while (*ids)
    {
        if (*ids == ctrlID)
            return (*++ids);
        ids += 2;
    }

    if (bAllowImplicit  &&  
        (unsigned short)ctrlID != (unsigned short)IDC_STATIC)
        return ctrlID;

    return 0;
}

static BOOL DoHelpInfo(CWnd *pDlg, const DWORD *pHelpIDs, 
                       HELPINFO* pHelpInfo, bool bAllowImplicit) 
{
    HWND    hWnd = (HWND)pHelpInfo->hItemHandle;
    TCHAR   szClassName[256];
    int     ctrlID;
    DWORD   id;

    // check to see if the user pressed F1 from inside a popup help
    // window 
    ::GetClassName(hWnd, (LPTSTR)szClassName, sizeof(szClassName));
    if (_tcscmp(szClassName, _T("hh_popup")) == 0)
    {
        // we're inside a popup window, so exit
        return FALSE;
    }

    if (pHelpInfo->iCtrlId >= 0)
        ctrlID = pHelpInfo->iCtrlId;
    else
        ctrlID = (unsigned short)::GetDlgCtrlID(hWnd);

    id = FindHelpID(pHelpIDs, (DWORD)ctrlID, bAllowImplicit);

    if (id == 0)
    {
        // there's no help message for this item.

        // display an error popup message?
        if (!g_bHTMLHelp_ShowNoHelpMessage)
        {
            return FALSE;  // no - exit
        }

        // Either:
        // 1. The user pressed F1  - or -
        // 2. The user pressed the dialog's '?' and used the mouse 
        //    to click on a control.
        // For the latter, we want to avoid displaying error 
        // messages for controls that aren't tab stops, otherwise
        // an error message will be displayed needlessly for every
        // static control and the likes
        if ((::GetWindowLong(hWnd, GWL_STYLE) & WS_TABSTOP) != 
            WS_TABSTOP)
        {
            return FALSE;
        }


        // Display the error message popup

        HH_POPUP    hhp;
        CRect       r;

        hhp.cbStruct = sizeof(hhp);
        hhp.idString = 0;
        hhp.pszText  = NO_HELP_TXT;
        hhp.pszFont  = NO_HELP_FNT;
        hhp.clrBackground = -1;
        hhp.clrForeground = -1;
        ::SetRect(&hhp.rcMargins, -1, -1, -1, -1);

        ::GetWindowRect(hWnd, r);
        hhp.pt = r.CenterPoint();

        HtmlHelp(pDlg->m_hWnd, NULL, HH_DISPLAY_TEXT_POPUP, 
            (DWORD)&hhp);
        return TRUE;
    }

    ShowHelp(hWnd, ctrlID, id);

    return TRUE;
}

static void DoContextMenu(CWnd *pDlg, const DWORD *pHelpIDs, 
    CWnd *pWnd, CPoint point, bool bAllowImplicit)
{
    DWORD id;

    // avoid showing the "What's This?" menu if we don't actually 
    // have the HTML help library loaded
    if (!s_pfnHtmlHelp)
        return;

    /* static controls won't send this message, so if the user 
       right-clicks on a static control, the dialog's pointer - and
       not the control's - will be passed in pWnd.
       The code below tries to identify the actual control that 
       should be handled:
    */
    if (pWnd->m_hWnd == pDlg->m_hWnd)
    {
        CPoint  pt(GetMessagePos());
        CRect   r;
        CWnd  * pWndFound = NULL;

        // it would have been nice to use the ChildWindowFromPoint
        // function, but in case of one control over the other,
        // ChildWindowFromPoint would return the handle to the 
        // control on the bottom, whereas we want the control on
        // the top.
        pWnd = pDlg->GetTopWindow();
        while (pWnd)
        {
            if (pWnd->IsWindowVisible())
            {
                pWnd->GetWindowRect(r);
                if (r.PtInRect(pt))
                {
                    pWndFound = pWnd;
                }
            }
            pWnd = pWnd->GetNextWindow();
        }

        if (pWndFound->GetSafeHwnd() == NULL)  // nothing there?
            return;

        pWnd = pWndFound;
    }

    id = FindHelpID(pHelpIDs, (DWORD)pWnd->GetDlgCtrlID(), 
        bAllowImplicit);

    if (id == 0)
        return;

    if (s_WhatsThis.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | 
        TPM_RIGHTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD,
        point.x, point.y, pDlg) == 1)
    {
        ShowHelp(pWnd->m_hWnd, pWnd->GetDlgCtrlID(), id);
    }
}

static void ShowHelp(HWND hWnd, int ctrlID, DWORD helpID,
    LPCTSTR pszHelpWndType /*= NULL*/, 
    LPCTSTR pszHelpFile /*=APP_CHM*/)
{
    if (ctrlID)
    {
        if (helpID < 0x20000000) /* display a popup? */
        {
            DWORD ids[] = { (DWORD)ctrlID, helpID, 0 };
            HtmlHelp(hWnd, APP_CHM, HH_TP_HELP_WM_HELP, (DWORD)ids);
            return;
        }
    }

    CString szHelpFile;
    if (pszHelpFile == APP_CHM)
        szHelpFile = GetHelpFile();
    else
        szHelpFile = pszHelpFile;
    if (szHelpFile.IsEmpty())
        return;

    // determine which window type to use
    if (!pszHelpWndType  &&  helpID >= 0x20000000)
    {
        if (helpID < 0x30000000)
        {
            // 0x20000000...0x2FFFFFFF
            pszHelpWndType = g_pszPopupWinTypeName;
        }
        else
        {
            if (helpID < 0x40000000)
            {
                // 0x30000000...0x3FFFFFFF (0x30nnXXXX)
                int nn = (helpID >> 16) & 0xFF;
                if (nn)
                {
                    CString val;
                    // if this bombs, then you are trying to use an
                    // unregistered window type
                    VERIFY(s_WinTypeMap.Lookup(nn, val) != 0);
                    pszHelpWndType = s_WinTypeMap[nn];
                }
            }
        }
    }

    if (pszHelpWndType)
    {
        szHelpFile += '>';
        szHelpFile += pszHelpWndType;
    }

    HtmlHelp(hWnd, szHelpFile, HH_HELP_CONTEXT, helpID);
}

// Finds the program's default .chm file (i.e. MyApp.chm for the
// application MyApp).
static CString& GetHelpFile()
{
    static CString CachedName;

    if (CachedName.IsEmpty())
    {
        CachedName = AfxGetApp()->m_pszHelpFilePath;

        // does the application still think we're using a WinHelp 
        // help file?
        if (CachedName.Right(3) == _T("HLP"))
        {
            // yes - change to HTML help file
            LPTSTR pszHelpFilePath = 
                (LPTSTR)AfxGetApp()->m_pszHelpFilePath;
            _tcscpy(pszHelpFilePath + _tcslen(pszHelpFilePath) - 3, 
                _T("chm"));
            CachedName = pszHelpFilePath;
        }

        HANDLE fh = CreateFile(CachedName, GENERIC_READ, 
            FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    
        if (fh == INVALID_HANDLE_VALUE)  // not found?
        {
            // search for help file on path

            TCHAR path_buffer[2048];
            TCHAR drive[_MAX_DRIVE];
            TCHAR dir[_MAX_DIR];
            TCHAR fname[_MAX_FNAME];
            TCHAR ext[_MAX_EXT];
            LPTSTR p;
            int len;
        
            _tsplitpath(CachedName, drive, dir, fname, ext);
            len = SearchPath(NULL, fname, ext, sizeof(path_buffer), 
                path_buffer, &p);

            if (len == 0)
            {
                CachedName.Empty();
            }
            else
            {
                CachedName = path_buffer;
            }
        }
        else
        {
            CloseHandle(fh);
        }
    }

    // Unlike WinHelp, HTML Help is not smart enough to ask the user
    // for the location of the help file if it can't find it in the
    // program-specified location.  The following code will do just
    // just that.
    if (CachedName.IsEmpty()) // not found? 
    {
        // build message box test
        CString msg, file;
        int p;
        file = AfxGetApp()->m_pszHelpFilePath;
        if ((p = file.ReverseFind('\\')) >= 0) 
        {
            file = file.Mid(p + 1);
        }

        // ask user: will you locate the file?
        msg.Format(FILE_NOT_FOUND, file);
        if (AfxMessageBox(msg, MB_YESNO | MB_ICONEXCLAMATION) 
            == IDYES)
        {
            // yes - activate standard file selection dialog
            CFileDialog dlg(TRUE, _T(".chm"), file, 
                OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | 
                OFN_HIDEREADONLY,
                _T("HTML Help Files (*.chm)|*.chm||"));
            if (dlg.DoModal() == IDOK)
            {
                CachedName = dlg.GetFileName();
            }
        }
    }

    return CachedName;
}


#define IMPLEMENT_CLASS(classname, baseclass)                      \
                                                                   \
IMPLEMENT_DYNCREATE(classname, baseclass)                          \
                                                                   \
const DWORD classname::m_dwHelpIDs[] = { 0, 0 };                   \
                                                                   \
BEGIN_MESSAGE_MAP(classname, baseclass)                            \
    ON_WM_CONTEXTMENU()                                            \
    ON_WM_HELPINFO()                                               \
	ON_MESSAGE(WM_COMMANDHELP, OnCommandHelp)                      \
	ON_COMMAND(ID_HELP, OnIDHelp)                                  \
END_MESSAGE_MAP()                                                  \
                                                                   \
void classname::OnIDHelp()                                         \
{                                                                  \
    OnCommandHelp(0, 0);                                           \
}                                                                  \
                                                                   \
LRESULT classname::OnCommandHelp(WPARAM wParam, LPARAM lParam)     \
{                                                                  \
    if (m_iHelpID >= 0)                                            \
    {                                                              \
        ShowHTMLHelp(this->m_hWnd, m_iHelpID);                     \
        return TRUE;                                               \
    }                                                              \
    return FALSE;                                                  \
}                                                                  \
                                                                   \
void classname::OnContextMenu(CWnd *pWnd, CPoint point)            \
{                                                                  \
    DoContextMenu(this, GetHelpIDs(), pWnd, point,                 \
        m_bAllowImplicit);                                         \
}                                                                  \
                                                                   \
BOOL classname::OnHelpInfo(HELPINFO* pHelpInfo)                    \
{                                                                  \
    return DoHelpInfo(this, GetHelpIDs(), pHelpInfo,               \
        m_bAllowImplicit);                                         \
}


IMPLEMENT_CLASS(CHHDialog,   CDialog);
IMPLEMENT_CLASS(CHHPropPage, CPropertyPage);

void CHHPropPage::CommonInit()
{
    if (m_iHelpID >= 0)
        m_psp.dwFlags |= PSP_HASHELP;
    else
        m_psp.dwFlags &= ~PSP_HASHELP;
}


////////////////////////////////////////////////////////////////////
// CHHPropSheet

IMPLEMENT_DYNAMIC(CHHPropSheet, CPropertySheet)

BEGIN_MESSAGE_MAP(CHHPropSheet, CPropertySheet)
    //{{AFX_MSG_MAP(CHHPropSheet)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////
// CHHPropSheet message handlers

BOOL CHHPropSheet::OnInitDialog()
{
    BOOL bResult = CPropertySheet::OnInitDialog();
    ModifyStyleEx(0, WS_EX_CONTEXTHELP);
    return bResult;
}

int CHHPropSheet::DoModal()
{
    CHHPropPage *pPage;

    m_psh.dwFlags &= ~PSH_HASHELP;

    for (int i = 0; i < GetPageCount(); i++)
    {
        pPage = (CHHPropPage *)GetPage(i);
        ASSERT(pPage->IsKindOf(RUNTIME_CLASS(CHHPropPage)));
        if (pPage->m_iHelpID < 0)
        {
            pPage->m_iHelpID = m_iHelpID;
        }
        if (pPage->m_iHelpID >= 0)
        {
            pPage->m_psp.dwFlags |= PSP_HASHELP;
            m_psh.dwFlags |= PSH_HASHELP;
        }
    }

    return CPropertySheet::DoModal();
}

void CHHPropSheet::AddPage(CHHPropPage* pPage)
{
    if (pPage->m_iHelpID < 0)
    {
        pPage->m_iHelpID = m_iHelpID;
    }

    if (pPage->m_iHelpID >= 0)
    {
        pPage->m_psp.dwFlags |= PSP_HASHELP;
    }

    CPropertySheet::AddPage(pPage);
}


void ShowHTMLHelp(HWND hWnd, DWORD helpID, LPCTSTR pszHelpWndType,
    LPCTSTR pszHelpFile /*=APP_CHM*/)
{
    ShowHelp(hWnd, 0, helpID, pszHelpWndType, pszHelpFile);
}

bool RegisterHHWindowType(int n, LPCTSTR name)
{
    CString val;

    if (s_WinTypeMap.Lookup(n, val) != 0)
        return false;  // already exists

    s_WinTypeMap[n] = name;

    return true;
}


// The following function mimics the HtmlHelp function provided by
// HtmlHelp.lib.  This allows us to call the HTML Help control
// without linking to HtmlHelp.lib.
// "HtmlHelp" is actually a macro alias that is mapped to either 
// HtmlHelpA or HtmlHelpW (depending on whether or not Unicode is 
// used).  Notice the use of LPCTSTR which allows this function to 
// compile correctly as either version.
HWND WINAPI HtmlHelp(HWND hwndCaller, LPCTSTR pszFile, 
                     UINT uCommand, DWORD_PTR dwData)
{
    if (s_pfnHtmlHelp)
    {
        // use program's default .chm?
        if (pszFile == APP_CHM) 
        {
            pszFile = GetHelpFile();
            if (pszFile == NULL  ||  !*pszFile) // not found? 
                return NULL;
        }

        return (*s_pfnHtmlHelp)(hwndCaller, pszFile, uCommand, 
            dwData);
    }
    else
    {
        TRACE(_T("An HTML Help function was called, but the ")
              _T("library isn't loaded."));
    }

    return NULL;
}

void WinHelpToHTMLHelp(CWinApp *pApp, DWORD dwData, UINT nCmd)
{
    HWND hWnd = pApp->GetMainWnd()->m_hWnd;

    // translate WinHelp commands to HTML Help commands

    switch (nCmd)
    {
        case HELP_CONTEXT:
            dwData &= 0xFFFF;  // remove MFC's hi-word addition
            HtmlHelp(hWnd, APP_CHM, HH_HELP_CONTEXT, dwData);
            break;

        case HELP_FINDER:
            dwData &= 0xFFFF;  // remove MFC's hi-word addition
            HtmlHelp(hWnd, APP_CHM, HH_HELP_FINDER, dwData);
            break;

        case HELP_QUIT:
            HtmlHelp(NULL, NULL, HH_CLOSE_ALL, 0);

        case HELP_CONTEXTMENU:
            HtmlHelp(hWnd, APP_CHM, HH_TP_HELP_CONTEXTMENU, dwData);
            break;

        case HELP_WM_HELP:
            HtmlHelp(hWnd, APP_CHM, HH_TP_HELP_WM_HELP, dwData);
            break;

        default:
            ASSERT(0);  // unsupported WinHelp command
    }
}
