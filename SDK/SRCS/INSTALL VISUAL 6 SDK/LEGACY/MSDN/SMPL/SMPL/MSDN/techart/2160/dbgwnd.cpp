// dbgwnd.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "dbgwnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDbgWnd

CDbgWnd::CDbgWnd()
{
    theDbgLevel = 1;
}

CDbgWnd::~CDbgWnd()
{
}

BEGIN_MESSAGE_MAP(CDbgWnd, CWnd)
    //{{AFX_MSG_MAP(CDbgWnd)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_WM_SETFOCUS()
    ON_WM_MEASUREITEM()
    ON_WM_DRAWITEM()
    ON_COMMAND(ID_DEBUG_0, OnDebug0)
    ON_COMMAND(ID_DEBUG_1, OnDebug1)
    ON_COMMAND(ID_DEBUG_2, OnDebug2)
    ON_COMMAND(ID_DEBUG_3, OnDebug3)
    ON_COMMAND(ID_DEBUG_4, OnDebug4)
    ON_COMMAND(ID_DEBUG_CLEAR, OnDebugClear)
    ON_WM_INITMENUPOPUP()
    ON_WM_DESTROY()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDbgWnd message handlers


int CDbgWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;
        
    // Create the listbox
    CRect rcClient;
    GetClientRect(&rcClient); 
    m_wndList.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL
                        | LBS_DISABLENOSCROLL
                        | LBS_HASSTRINGS 
                        | LBS_OWNERDRAWFIXED
                        | LBS_NOINTEGRALHEIGHT,
                     rcClient,
                     this,
                     IDC_LIST);

    // Get the last known debug level
    SetDebugLevel(AfxGetApp()->GetProfileInt("Debug",
                                             "Level",
                                             1));

    return 0;
}

void CDbgWnd::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);
    
    m_wndList.SetWindowPos(NULL,
                           0, 0,
                           cx, cy,
                           SWP_NOZORDER);
}

void CDbgWnd::OnSetFocus(CWnd* pOldWnd)
{
    m_wndList.SetFocus();
}

void CDbgWnd::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMIS)
{
    TEXTMETRIC tm;
    CDC *pDC;

    pDC = GetDC();
    pDC->GetTextMetrics(&tm);
    ReleaseDC(pDC);
    lpMIS->itemHeight = tm.tmHeight;
}

void CDbgWnd::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDI)
{
    HBRUSH hbrBkGnd;
    RECT rc;
    HDC hDC;
    char buf[256];
    
    hDC = lpDI->hDC;
    rc = lpDI->rcItem;
    switch (lpDI->itemAction) {
    case ODA_SELECT:
    case ODA_DRAWENTIRE:

        // erase the rectangle
        hbrBkGnd = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
        ::FillRect(hDC, &rc, hbrBkGnd);
        ::DeleteObject(hbrBkGnd);

        // show the text in our standard font
        ::SetBkMode(hDC, TRANSPARENT);
        ::SendMessage(lpDI->hwndItem, 
                      LB_GETTEXT, 
                      lpDI->itemID, 
                      (LPARAM)(LPSTR)buf);
        ExtTextOut(hDC, 
                   rc.left+2, rc.top,
                   ETO_CLIPPED,
                   &rc, 
                   buf,
                   lstrlen(buf), 
                   NULL);
        break;
    }
}

// Set the current debug level
void CDbgWnd::SetDebugLevel(int i)
{
    theDbgLevel = i;
    dprintf("The debug level is %i", i);
}

// function to add a string to the end of the debug list
void CDbgWnd::DbgOut(LPSTR lpFormat, ...) 
{
    int i;
    char buf[256];

    // format the string
    vsprintf(buf, lpFormat, (LPSTR)(&lpFormat+1));

    // get the item count
    i = m_wndList.GetCount();
    if (i == LB_ERR) i = 0;

    // scrub a few if we have too many
    while (i >= MAXLISTLINES) {
        m_wndList.DeleteString(0);
        i--;
    }

    // add the new one on at the end and scroll it into view
    i = m_wndList.AddString(buf);
    m_wndList.SetCurSel(i);
}

void CDbgWnd::Create()
{
    CMenu menu;
    menu.LoadMenu(IDR_DEBUG);
    CreateEx(0,
             AfxRegisterWndClass(CS_NOCLOSE,
                                 0,
                                 0,
                                 AfxGetApp()->LoadIcon(IDR_DEBUG)),
             "Anim Debug",
             WS_POPUP | WS_VISIBLE 
                 | WS_CAPTION | WS_SYSMENU
                 | WS_BORDER | WS_THICKFRAME | WS_MINIMIZEBOX,
             GetSystemMetrics(SM_CXSCREEN) * 3 / 4,
             GetSystemMetrics(SM_CYSCREEN) / 2,
             GetSystemMetrics(SM_CXSCREEN) / 4,
             GetSystemMetrics(SM_CYSCREEN) / 2,
             NULL,
             menu.m_hMenu);
}

void CDbgWnd::OnDebug0()
{
    SetDebugLevel(0);
}

void CDbgWnd::OnDebug1()
{
    SetDebugLevel(1);
}

void CDbgWnd::OnDebug2()
{
    SetDebugLevel(2);
}

void CDbgWnd::OnDebug3()
{
    SetDebugLevel(3);
}

void CDbgWnd::OnDebug4()
{
    SetDebugLevel(4);
}

void CDbgWnd::OnDebugClear()
{
    m_wndList.ResetContent();
}

void CDbgWnd::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
    pPopupMenu->CheckMenuItem(ID_DEBUG_0, 
                              theDbgLevel == 0 ? MF_CHECKED : MF_UNCHECKED); 
    pPopupMenu->CheckMenuItem(ID_DEBUG_1,
                              theDbgLevel == 1 ? MF_CHECKED : MF_UNCHECKED); 
    pPopupMenu->CheckMenuItem(ID_DEBUG_2, 
                              theDbgLevel == 2 ? MF_CHECKED : MF_UNCHECKED); 
    pPopupMenu->CheckMenuItem(ID_DEBUG_3,
                              theDbgLevel == 3 ? MF_CHECKED : MF_UNCHECKED); 
    pPopupMenu->CheckMenuItem(ID_DEBUG_4,
                              theDbgLevel == 4 ? MF_CHECKED : MF_UNCHECKED); 
}

// Save the current debug level
void CDbgWnd::OnDestroy()
{
    AfxGetApp()->WriteProfileInt("Debug",
                                 "Level",
                                 theDbgLevel);
    CWnd::OnDestroy();
}

//////////////
// global timing stuff


DWORD dbgGetTime()
{
    LARGE_INTEGER liStart;
    QueryPerformanceCounter(&liStart);
    return liStart.LowPart;
}

void dbgShowElapsedTime(LPSTR pMsg, DWORD dwStart)
{
    LARGE_INTEGER liEnd;
    QueryPerformanceCounter(&liEnd);
    DWORD dwTime;
    dwTime = liEnd.LowPart - dwStart;
    LARGE_INTEGER liFreq;
    QueryPerformanceFrequency(&liFreq);
    dwTime /= liFreq.LowPart / 10000; // 1/10 ms units
    dprintf4("%s%u.%ums",
             pMsg,
             dwTime / 10,
             dwTime % 10);
}

