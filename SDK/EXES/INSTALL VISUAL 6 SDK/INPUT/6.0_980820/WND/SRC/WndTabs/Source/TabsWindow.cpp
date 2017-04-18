/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// TabsWindow.cpp : implementation file
//
// This class implements the "Tabs Window" - the window with tabs and menu
// button.
//

#include "stdafx.h"
#include "WndTabs.h"
#include "TabsWindow.h"
#include "TabManagerWindow.h"
#include "DevStudioWnd.h"
#include "Options.h"
#include "Commands.h"
#include "DSWindow.h"
#include "DS_MDIWnd.h"
#include "DSAddin.h"
#include "Options.h"
#include "Config.h"
#include "ShellContextMenu.h"
#include "Utils.h"
#include "Extensions.h"
#include "Help\HelpIDs.h"
#include "MainFrame.h"
#include "SDK_Supp.h"
#include "VCVerMgr.h"
#include "3rdParty\WWhizInterface2.h"

#include <exception>

#define CATCH_EXCEPTIONS

#ifdef _DEBUG
#define new DEBUG_NEW
#undef CATCH_EXCEPTIONS
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_TAB          1000
#define ID_MENU         1001

#define MENU_WIDTH      (14 + 8)       // width for menu button
#define MENU_HEIGHT     (14 + 8)       // height for menu button

#define GRIPPER_SIZE    10             // short side

CTabsWindow *pGlobalTabs = NULL;
int g_cTabRows = -1;


void CTabsWindow::tabdata_t::UpdatePath()
{
    if (pWindow == NULL)
    {
        pGlobalTabs->FindDSWindow(hWnd, &pWindow);
    }
    if (pWindow  &&  pDoc == NULL)
    {
        pGlobalTabs->GetDocumentObject(pWindow, pDoc);
    }
    if (pDoc)
    {
        CComBSTR bStr;
        pDoc->get_FullName(&bStr);
        cPath = bStr;
        bStr.Empty();
    }
    else
    {
        cPath.Empty();
    }
}


/////////////////////////////////////////////////////////////////////////////
// CTabsWindow

CTabsWindow::CTabsWindow(CCommands* pCommands) : 
    m_bTracking(FALSE),
    m_bIsDragging(false),
    m_RectGripper(0, 0, 0, 0),
    m_iLockUpdates(0), 
    m_bAboutToUpdate(false),
    m_pTabCtrl(NULL), 
    m_hSavedCursor(NULL),
    m_bIsWTTab(false),
    m_pCommands(pCommands), 
    m_pApplication(pCommands->GetApplicationObject()),
    m_penShadowTop(PS_SOLID, 0, ::GetSysColor(COLOR_BTNHIGHLIGHT)),
    m_penShadowBottom(PS_SOLID, 0, ::GetSysColor(COLOR_BTNSHADOW))
{
    m_NumberOverlays.Create(IDB_NUMBERS, 16, 1, RGB(255, 255, 255));
}

CTabsWindow::~CTabsWindow()
{
    FreeData();
    delete m_pTabCtrl;
    m_pTabCtrl = NULL;
    DestroyWindow();
}

void CTabsWindow::FreeData()
{
    POSITION p = m_TabData.GetStartPosition();
    tabdata_t *pData;
    HWND key;
    while (p)
    {
        m_TabData.GetNextAssoc(p, key, pData);
        try
        {
            delete pData;
        }
        catch (...)
        {
            WT_L1_TRACE("Exception in FreeData()\n");
        }
    }
    m_TabData.RemoveAll();
}

BEGIN_MESSAGE_MAP(CTabsWindow, CReBar)
    //{{AFX_MSG_MAP(CTabsWindow)
    ON_WM_CREATE()
    ON_WM_WINDOWPOSCHANGED()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_DRAWITEM()
	ON_WM_MBUTTONDOWN()
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_UPDATETABS, UpdateTabs)
    ON_NOTIFY(TCN_SELCHANGE, ID_TAB,  OnSelChangeTabCtrl)
    ON_NOTIFY(NM_CLICK,      ID_TAB,  OnLClickTabCtrl)
    ON_NOTIFY(NM_RCLICK,     ID_TAB,  OnRClickTabCtrl)
    ON_NOTIFY(TTN_NEEDTEXTA,  0,  OnToolTipTabCtrl)
    ON_NOTIFY(TTN_NEEDTEXTW,  0,  OnToolTipTabCtrlW)
    ON_NOTIFY(TBN_QUERYDELETE,  ID_MENU,       OnToolBarQueryDelete)
    ON_NOTIFY(TBN_QUERYINSERT,  ID_MENU,       OnToolBarQueryDelete)
    ON_NOTIFY(WTXN_TAB_CLOSE, ID_TAB,  OnWTXTabClose)
    ON_NOTIFY(WTXN_R_TAB_CLOSE, ID_TAB,  OnWTXRTabClose)
	ON_NOTIFY_REFLECT(RBN_BEGINDRAG, OnBeginDrag)
	ON_NOTIFY_REFLECT(RBN_ENDDRAG, OnEndDrag)
	ON_WM_MEASUREITEM()
    ON_MESSAGE(WM_TABINFOUPDATE, OnTabInfoUpdate)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTabsWindow message handlers

int CTabsWindow::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CReBar::OnCreate(lpCreateStruct) == -1)
        return -1;

    m_TabImages.Create(16, 16, ILC_MASK, 10, 5);

    UpdateStyle();

    // we want a flat menu button, so we'll use a tool bar
    m_mfh.CreateEx(0, NULL, "MFH", WS_CHILD | WS_VISIBLE, 
        CRect(0, 0, 1, 1), this, 0);
    m_mfh.SetMF((CMainFrame *)AfxGetApp()->m_pMainWnd);

    AddBar(&m_mfh, (LPCTSTR)NULL, NULL, RBBS_VARIABLEHEIGHT);
    AddBar(m_pTabCtrl, ""/*"Tabs"*/, NULL, RBBS_GRIPPERALWAYS | RBBS_VARIABLEHEIGHT);

    return 0;
}

void CTabsWindow::UpdateReBar()
{
    static int iLastWasVertical = -1;

    bool bVertical = !IS_HORIZONTAL(cfg_iOrientation);

    if (iLastWasVertical != (int)bVertical)
    {
        g_pMainFrame->RecalcLayout();
    }

    if (iLastWasVertical != -1)
    {
        iLastWasVertical = bVertical;
        GetReBarCtrl().ModifyStyle(bVertical? 0 : CCS_VERT,
                                   bVertical? CCS_VERT : 0);

        g_pMainFrame->RecalcLayout();
        if (!g_pMainFrame->m_wndMenuBar.IsFloating())
        {
            g_pMainFrame->DockControlBar(&g_pMainFrame->m_wndMenuBar,
                bVertical? AFX_IDW_DOCKBAR_LEFT : AFX_IDW_DOCKBAR_TOP);
        }
    }

    CRect r;
    GetClientRect(r);

    if (r.Width() < 10) return;    
    iLastWasVertical = bVertical;

    if (pGlobalActiveManager->GetSafeHwnd())
    {
        r.DeflateRect(pGlobalActiveManager->GetBorder());
        r.DeflateRect(1, 1);
    }
    if (bVertical)
    {
        CRect rflip = r;
        r.bottom = rflip.right;
        r.right = rflip.bottom;
    }

    GetReBarCtrl().DeleteBand(1);
    GetReBarCtrl().DeleteBand(0);
    AddBar(&m_mfh, (LPCTSTR)NULL, NULL, RBBS_VARIABLEHEIGHT);
    AddBar(m_pTabCtrl, (LPCTSTR)NULL, NULL, 
        RBBS_GRIPPERALWAYS | RBBS_VARIABLEHEIGHT);

    REBARBANDINFO rbbi;
    rbbi.cbSize = sizeof(rbbi);
    rbbi.fMask = RBBIM_CHILDSIZE | RBBIM_IDEALSIZE | RBBIM_SIZE ;

    rbbi.cxMinChild = 0; //32;
    rbbi.cyMinChild = r.Height();
    rbbi.cx = rbbi.cxIdeal = cfg_iReBarWidth;
    rbbi.cyChild = rbbi.cyMinChild;
    rbbi.cyMaxChild = rbbi.cyMinChild;
    rbbi.cyIntegral = 0;
    GetReBarCtrl().SetBandInfo(0, &rbbi);

    rbbi.cxMinChild = 0;
    rbbi.cyMinChild = r.Height();
    rbbi.cx = r.Width();
    rbbi.cxIdeal = 10240;
    rbbi.cyChild = rbbi.cyMinChild;
    rbbi.cyMaxChild = rbbi.cyMinChild;
    rbbi.cyIntegral = 0;
    GetReBarCtrl().SetBandInfo(1, &rbbi);

}

void CTabsWindow::OnDestroy() 
{
    REBARBANDINFO rbbi;

    rbbi.cbSize = sizeof(rbbi);
    rbbi.fMask = RBBIM_SIZE;
    GetReBarCtrl().GetBandInfo(0, &rbbi);
    cfg_iReBarWidth = rbbi.cx;
    CReBar::OnDestroy();
}

void CTabsWindow::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
    CReBar::OnWindowPosChanged(lpwndpos);

    if (pGlobalMDIManager->GetSafeHwnd())
    {
        SetWindowPos(pGlobalMDIManager->GetWindow(GW_HWNDPREV), 0, 0, 0, 0, 
            SWP_NOMOVE | SWP_NOSIZE);
    }

    if ((lpwndpos->flags & (SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER)) == 
        (SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER))
    {
        return;
    }

    return;
}

// this handler is needed for the case when the active tab/window is
// minimized, and the user clicks on the tab, wanting the window to restore
void CTabsWindow::OnLClickTabCtrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
    if (pGlobalActiveDSWindow->GetSaferHwnd())
    {
        ActivateWindow(pGlobalActiveDSWindow->m_hWnd, true);
        SendWndTabsEvent(WndTabs_Ev_TabClicked, m_pTabCtrl->GetCurSel());
    }
    else
    {
        ForceTabUpdate();
    }

}

void CTabsWindow::OnSelChangeTabCtrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
    HWND hWnd;

    if (FindDSWindow(m_pTabCtrl->GetCurSel(), NULL, &hWnd))
    {
        ActivateWindow(hWnd);
    }
    SendWndTabsEvent(WndTabs_Ev_TabClicked, m_pTabCtrl->GetCurSel());
}

void CTabsWindow::ResyncActiveTab()
{
    WT_FN_TRACE("ResyncActiveTab");
    WT_ASSERT(pGlobalMDIManager != NULL);
    m_bAboutToUpdate = false;

    if (cfg_TabOrdering != toMDI)
    {
        const int cTabs = m_pTabCtrl->GetItemCount();
        HWND hWndActive = ::GetTopWindow(pGlobalMDIManager->m_hWnd);
        for (int i = 0; i < cTabs; i++)
        {
            tabdata_t& data = *GetTabData(i);
            if (data.hWnd == hWndActive)
            {
                m_pTabCtrl->SetCurSel(i);
                UpdateCommandContext(i);
                return;
            }
        }

        // not found - force full rebuild..
    }

    pGlobalActiveManager->PostUpdateMessage();
}


// the following event handler is called when the user right-clicks on a tab.
void CTabsWindow::OnRClickTabCtrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
    CPoint point;

    WT_MANAGE_STATE();

    if (!theApp.IsFocused())
    {
        VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));

        point = m_pTabCtrl->m_LastRClickPos;
        m_pTabCtrl->ClientToScreen(&point);
        if (UpdateCommandContext(point))
        {
            GetCursorPos(&point);
            if (GetKeyState(cfg_iShellKey) & 0x8000)
            {
                if (CMainFrame::m_pCmdCtx->bHasFile)
                {
                    theApp.ShowPopupMenu(IDR_SHELL_CONTEXT, point, this);
                }
            }
            else
            {
                theApp.ShowPopupMenu(IDR_POPUP, point, this);
            }
        }

        VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
    }
}


void CTabsWindow::OnWTXTabClose(NMHDR* pNMHDR, LRESULT* pResult)
{
    if (UpdateCommandContext(pNMHDR->idFrom))
    {
        g_pMainFrame->DoCloseGroup((GetKeyState(VK_SHIFT) & 0x8000) != 0);
    }
}

void CTabsWindow::OnWTXRTabClose(NMHDR* pNMHDR, LRESULT* pResult)
{
    WT_MANAGE_STATE();

    if (!theApp.IsFocused())
    {
        VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));
        if (UpdateCommandContext(pNMHDR->idFrom))
        {
			// this is always a group operation
			CMainFrame::m_pCmdCtx->bIsGroupOperation = TRUE;

            CPoint pt;
            GetCursorPos(&pt);
            theApp.ShowPopupMenu(IDR_CLOSEBTN, pt, this);
        }
        VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
    }
}


// The tool tip handler displays the full path of a document.
// All open documents are scanned, looking for a the respective window's
// document.  Once the document is found, the full path is extracted.
// This function demonstrates enumeration of both documents and windows.
void CTabsWindow::OnToolTipTabCtrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    LPTOOLTIPTEXTA  lpttt = (LPTOOLTIPTEXT)pNMHDR;
    TCHITTESTINFO   hti;
    int             iTab;
    static CString  cStr; // safe - there can be only one tip at a time

    *pResult = 0;

    if (lpttt->hdr.idFrom == IDC_MENU)
    {
        cStr.LoadString(IDS_MENU_TT);
    }
    else
    {
        hti.pt = CPoint(GetMessagePos());
        m_pTabCtrl->ScreenToClient(&hti.pt);
        iTab = m_pTabCtrl->HitTest(&hti);

        if (iTab >= 0)
        {
            tabdata_t *pTabData = GetTabData(iTab);

            if (pTabData->pDoc)
            {
                CComBSTR bStr;
                pTabData->pDoc->get_FullName(&bStr);
                cStr = bStr;
                bStr.Empty();
    
                if (cStr.IsEmpty())
                {
                    // no name?  it's a text editor without an associated 
                    // file
                    cStr.LoadString(IDS_UNSAVED_TT);
                }
                else
                {
                    if (cfg_bShowAttribsTT)
                    {
                        CString cAttrib;

                        if( FormatAttributesString(cAttrib, cStr) )
    					{
                            cStr += ' ';
                            cStr += cAttrib;
    					}
                    }
                }
            }
            else
            {
                cStr.LoadString(IDS_DSWIN_TT);
            }
        }
    }
    // variation on original fix by Christian Rodemeyer 
    // (Christian.Rodemeyer@t-online.de): use lpszText instead of szText so 
    // strings over 80 chars will be handled properly.
    lpttt->lpszText = LPTSTR(LPCTSTR(cStr));
}

void CTabsWindow::OnToolTipTabCtrlW(NMHDR* pNMHDR, LRESULT* pResult) 
{
    USES_CONVERSION;

    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    LPTOOLTIPTEXTW lpttt = (LPTOOLTIPTEXTW)pNMHDR;
    TOOLTIPTEXTA   ttta;

    ttta.hdr    = lpttt->hdr;
    ttta.hinst  = lpttt->hinst;
    ttta.lParam = lpttt->lParam;
    ttta.uFlags = lpttt->uFlags;

    OnToolTipTabCtrl((NMHDR *)&ttta, pResult);

    char *p = m_sToolTip.GetBuffer((strlen(ttta.lpszText) + 1) * 2);
    LPWSTR x = A2W(ttta.lpszText);
    wcscpy((LPWSTR)p, x);
    lpttt->lpszText = (LPWSTR)p;    
}


/////////////////////////////////////////////////////////////////////////////
// CTabsWindow commands


// Updates the tabs by enumerating DevStudio's windows
// This method demonstrates enumeration using the "Item" property.
LRESULT CTabsWindow::UpdateTabs(WPARAM wParam, LPARAM lParam)
{
    WT_FN_TRACE("UpdateTabs");

    HWND                hWnd, hWndActive;
    CWnd *              pWnd;
    CString             cStr, cTitle;
    CComVariant         index;
    HICON               hIcon, hIconOverlay;
    CTypedPtrArray      <CPtrArray, tabdata_t *> TabList;
    CTypedPtrList       <CPtrList,  tabdata_t *> TabsNotInList;
    CPtrList            BadPointers;
    tabdata_t           *pData, *pOldData;
    POSITION            p;
    int                 iIndex, iTabListCount = 0, iSel = -1;

    WT_L3_TRACE("UpdateTabs: lock=%d, aboutto=%d\n", m_iLockUpdates, 
        m_bAboutToUpdate);

    hWnd = GetSafeHwnd();
    if (!hWnd                          ||
        !::IsWindow(hWnd)              ||
        !::IsWindow(::GetParent(hWnd)) ||
        !pGlobalActiveManager          ||
        !m_pTabCtrl->GetSafeHwnd())
    {
        static int counter = 0;
        if (++counter > 1)
        {
            WT_L1_TRACE("Illegal window handle detected - update aborted\n");
        }
        RETURN_INT(0);
    }

    if (m_iLockUpdates  &&  (--m_iLockUpdates > 0))
    {
        RETURN_INT(0);
    }

    m_bAboutToUpdate = false;

#ifdef CATCH_EXCEPTIONS
    try
#endif
    {
        hWndActive = pGlobalActiveDSWindow->GetSaferHwnd();

        CCommands::Positions& positions = CCommands::m_Positions;
        const long cWindows = pGlobalMDIManager->GetWindowCount();
        const bool bIsWorkspaceReload = (positions.data.GetSize() > 0);

        pWnd = pGlobalMDIManager->GetTopWindow();

        // enumerate the windows
        for (int i = 0; pWnd; i++)
        {
            pWnd->GetWindowText(cTitle);

            // DevStudio will sometimes (temporarily) open a window without a 
            // name (usually while displaying a message box like: "Lines 
            // ending with only a carriage return have been detected...").  
            // We'll ignore these windows.
            if (!cTitle.IsEmpty())
            {
                pData = m_TabData[pWnd->m_hWnd];
                if (pData  &&  !bIsWorkspaceReload)
                {
                    if (cfg_TabOrdering == toMDI  ||  
                        (!cfg_bPreserveNumbering  &&  cfg_TabOrdering == toAlphabetic)) 
                    {
                        pData->iNumber = i;
                    }
                    if (pData->iNumber >= 0)
                    {
                        TabList.SetAtGrow(pData->iNumber, pData);
                    }
                    else
                    {
                        TabList.Add(pData);
                    }
                    iTabListCount++;
                }
                else
                {
                    if (!pData) 
                    {
                        pData = new tabdata_t;
                        pData->iNumber = -1;
                    }
                    pData->hWnd = pWnd->m_hWnd;
                    if (cfg_TabOrdering != toMDI  &&  !bIsWorkspaceReload)
                    {
                        TabsNotInList.AddTail(pData);
                    }
                    else
                    {
                        int tab_index;
                        if (bIsWorkspaceReload)
                        {
                            pData->UpdatePath();
                            CString cPath = cTitle + "|" + pData->cPath;
                            for (tab_index = 0; 
                                 tab_index < positions.data.GetSize();
                                 tab_index++)
                            {
                                if (positions.data[tab_index].cPath.CompareNoCase(cPath) == 0)
                                {
                                    break;
                                }
                            }
                            if (tab_index >= positions.data.GetSize())
                            {
                                pGlobalActiveManager->PostUpdateMessage();
                                delete pData;
                                m_TabData[pWnd->m_hWnd] = NULL;
                                goto skip;
                            }
                            pData->iNumber = positions.data[tab_index].iNumber;
                        }
                        else
                        {
                            tab_index = i;
                        }
                        if (pData->iNumber < 0  ||  !cfg_bPreserveNumbering)
                        {
                            pData->iNumber = tab_index;
                        }
                        if (TabList.GetSize() > tab_index  &&  
                            TabList.GetAt(tab_index) != NULL)
                        {
                            // slot already taken -- possibly corrupted
                            // .positions file
                            pData->iNumber = -1;
                            TabList.Add(pData);
                        }
                        else
                        {
                            TabList.SetAtGrow(tab_index, pData);
                        }
                        iTabListCount++;
                    }
                }
                m_TabData[pWnd->m_hWnd] = NULL;
                
                // if the user modified the document, there will be a asterisk
                // appended to the window title (removed if the file was just
                // saved), so we'll make sure we have the latest title:
                pData->cTitle = cTitle;
                pData->UpdatePath();
            }
skip:
            pWnd = pWnd->GetWindow(GW_HWNDNEXT);
        }

        ResetTabEventAddinCache();

        WWhizInterface *pWWI = theApp.GetWWhizInterface();
        if (pWWI != NULL)
        {
            try
            {
                pWWI->RefreshFileList();
            }
            catch (...)
            {
                theApp.ReportWWhizInterfaceException();
            }
        }

        m_pTabCtrl->SetRedraw(FALSE);

        if (cfg_bShowIcons  &&  ImageList_GetImageCount(m_TabImages) < cWindows)
        {    
            m_pTabCtrl->SetImageList(NULL);
            ImageList_SetImageCount(m_TabImages, cWindows + 5);
            m_pTabCtrl->SetImageList(&m_TabImages);
        }
    
        // delete pointers to windows that no longer exist
        p = m_TabData.GetStartPosition();
        while (p)
        {
            m_TabData.GetNextAssoc(p, hWnd, pData);
            if (pData)
            {
                m_TabData.RemoveKey(hWnd);
                BadPointers.AddHead(pData);
                delete pData;
            }
        }

        // reclaim 1..9 indexes
        if (cfg_bPreserveNumbering  &&  cfg_bFill1To9)
        {
            iIndex = 0;

            while (p = TabsNotInList.GetHeadPosition())
            {
                while (iIndex <= TabList.GetUpperBound()  &&  
                       TabList[iIndex] != NULL)
                {
                    iIndex++;
                    if (iIndex == 9) goto out;
                }

                pData = TabsNotInList.GetAt(p);
                pData->iNumber = iIndex;
                TabList.SetAtGrow(iIndex, pData);
                iTabListCount++;
                TabsNotInList.RemoveAt(p);
            }

    out:;
        }

        if (cfg_TabOrdering == toAlphabetic  &&  !bIsWorkspaceReload)
        {
            int j;
            if (TabsNotInList.GetHeadPosition())
            {
                int iIndex = iTabListCount + 1;
                int iNumber = 0;
                for (j = 0; j < TabList.GetSize(); j++)
                {
                    if (TabList[j]  &&  TabList[j]->iNumber >= iNumber)
                        iNumber = TabList[j]->iNumber + 1;
                }
                tabdata_t *p;
                while (TabsNotInList.GetHeadPosition() != NULL)
                {
                    p = TabsNotInList.RemoveHead();
                    p->iIndex = iIndex;
                    p->iNumber = iNumber;
                    ++iIndex;
                    ++iNumber;
                    TabList.Add(p);
                    iTabListCount++;
                }
            }
            const int sz = TabList.GetSize();
            tabdata_t **ppdata = new tabdata_t *[sz];
            for (i = 0; i < sz; ++i) 
            {
                ppdata[i] = TabList[i];
                if (ppdata[i])
                {
                    MangleName(ppdata[i]->cPath,
                        ppdata[i]->cTitle, -1, ppdata[i]->cName);
                }
            }
            // bubble sort
            for (i = 0; i < sz - 1; ++i)
            {
                for (j = 0; j < sz - 1 - i; ++j)
                {
                    if (ppdata[j + 1] != NULL)
                    {
                        if (ppdata[j] == NULL  ||
                            ppdata[j]->cName.CompareNoCase(ppdata[j + 1]->cName) > 0)
                        {
                            // swap
                            tabdata_t * const ptemp = ppdata[j];
                            ppdata[j] = ppdata[j + 1];
                            ppdata[j + 1] = ptemp;
                        }
                    }
                }
            }

            // update tab numbers
            TabList.RemoveAll();
            for (i = 0; i < sz; ++i)
            {
                TabList.Add(ppdata[i]);
                if (ppdata[i])
                {
                    ppdata[i]->iIndex = i;
    /*                if (cfg_bPreserveNumbering)
                    ppdata[i]->iNumber = i;
    */            }
            }

            delete [] ppdata;
        }

        // create the actual tabs
        TC_ITEM     newTabItem, oldTabItem;
        int         iCurrTabNumber = 0;    // the number displayed on the tab
        int         iCurrTabIndex  = 0;    // the index of the inserted tab
    
        iIndex = 0;
        newTabItem.mask = TCIF_PARAM | TCIF_TEXT;
        oldTabItem.mask = TCIF_PARAM;

        while (1)
        {
            p = TabsNotInList.GetHeadPosition();
            if (!iTabListCount)
            {
                if (!p) break;
                pData = TabsNotInList.GetAt(p);
                TabsNotInList.RemoveAt(p);

                if (!iTabListCount)
                {
                    pData->iNumber = iCurrTabNumber;
                }
            }
            else
            {
                iTabListCount--;
                do
                {
                    // bug fix courtacy of Ocke Janssen [Ocke.Janssen@sun.com]
                    if(TabList.GetSize() > iIndex) // check if index out of range
                    {
                        pData = TabList[iIndex++];
                    }
                } while (!pData && TabList.GetSize() > iIndex);
            }

            if (!cfg_bPreserveNumbering)
            {
                pData->iNumber = iCurrTabNumber;
            }
            else
            {
                iCurrTabNumber = pData->iNumber;
            }

            hIcon = (HICON)GetClassLong(pData->hWnd, GCL_HICONSM);
            hIconOverlay = NULL;
        
            if (cfg_bShowIcons  &&  hIcon)
            {
                newTabItem.mask |= TCIF_IMAGE;
                m_TabImages.Replace(iCurrTabIndex, hIcon);

                if (cfg_bShowNumbers  &&  pData->iNumber < 9)
                {
                    if (m_bIsWTTab)
                    {
                        hIconOverlay = 
                            m_NumberOverlays.ExtractIcon(pData->iNumber);
                    }
                    else
                    {
                        HIMAGELIST  hilmTemp;

                        hilmTemp = ImageList_Merge(m_TabImages, 
                            iCurrTabIndex, m_NumberOverlays, pData->iNumber, 
                            0, 0);
                        hIcon = ImageList_ExtractIcon(0, hilmTemp, 0);
                        m_TabImages.Replace(iCurrTabIndex, hIcon);
                        ::DestroyIcon(hIcon);
                        ImageList_Destroy(hilmTemp);
                    }
                }

                newTabItem.iImage = iCurrTabIndex;
            }
            else
            {
                newTabItem.mask &= ~TCIF_IMAGE;
            }

            if (pData->cName.IsEmpty()  ||  !cfg_bShowIcons  ||  !hIcon)
            {
                MangleName(pData->cPath, pData->cTitle, 
                    (cfg_bShowIcons  &&  hIcon)? -1 : iCurrTabNumber, cStr);
            }
            else
            {
                cStr = pData->cName;
            }

            newTabItem.pszText = (LPSTR)(LPCSTR)cStr;
            newTabItem.lParam = (LPARAM)(pData);
        
            pOldData = m_TabData[pData->hWnd];
            if (pOldData  &&  pOldData != pData)
            {
                BadPointers.AddHead(pData);
                delete pOldData;
            }

            m_TabData[pData->hWnd] = pData;
                                        
            pData->iIndex = iCurrTabIndex;

            // do our best to just replace the text (avoid flicker)
            do
            {
                if (m_pTabCtrl->GetItem(iCurrTabIndex, &oldTabItem) == FALSE)
                {
                    oldTabItem.lParam = NULL;
                    break;
                }

                if (BadPointers.Find((void *)oldTabItem.lParam) != NULL)
                {
                    oldTabItem.lParam = NULL;
                    break;
                }

                ASSERT(oldTabItem.lParam != NULL);

                if (((tabdata_t *)(oldTabItem.lParam))->hWnd == pData->hWnd)
                {
                    break;
                }

                if (m_pTabCtrl->GetItemCount() <= cWindows)
                {
                    oldTabItem.lParam = NULL;
                    break;
                }

                m_pTabCtrl->DeleteItem(iCurrTabIndex);
            } while (1);

            if ((HWND)oldTabItem.lParam != NULL)
            {
                m_pTabCtrl->SetItem(iCurrTabIndex, &newTabItem);
            }
            else
            {
                m_pTabCtrl->InsertItem(iCurrTabIndex, &newTabItem);
            }

            if (m_bIsWTTab)  // set/remove overlay
            {
                WTTabCtrlSetTabOverlay(m_pTabCtrl, iCurrTabIndex, 
                    hIconOverlay, true);
            }

            if (pData->hWnd == hWndActive)
            {
                iSel = iCurrTabIndex;
            }

            iCurrTabNumber++;
            iCurrTabIndex++;
        }

        while (m_pTabCtrl->GetItemCount() > cWindows)
        {
            m_pTabCtrl->DeleteItem(m_pTabCtrl->GetItemCount() - 1);
        }

        if (!bIsWorkspaceReload)
        {
            if (iSel >= 0)
            {
                m_pTabCtrl->SetCurSel(iSel);
            }
        }
        else
        {
            if (positions.iActiveTab < m_pTabCtrl->GetItemCount() &&
                positions.iActiveTab >= 0)
            {
                m_pTabCtrl->SetCurSel(positions.iActiveTab);
                ActivateWindow(GetTabData(m_pTabCtrl->GetCurSel())->hWnd);
            }
            positions.data.RemoveAll();

            // force an update in case the user has changed the ordering 
            // parameters
            pGlobalActiveManager->PostUpdateMessage();
        }

        UpdateCommandContext(m_pTabCtrl->GetCurSel());

        if (m_bIsWTTab)
        {
            WTTabCtrlRefresh(m_pTabCtrl);
        }

    //    m_pTabCtrl->ShowWindow(cWindows? SW_SHOW : SW_HIDE);
        m_pTabCtrl->SetRedraw(TRUE);
        if (CheckRowCount())
        {
            m_pTabCtrl->RedrawWindow();
        }
        ApplyWindowLimit();
    }
#ifdef CATCH_EXCEPTIONS
    catch (std::exception& e)
    {
        WT_L1_TRACE("Exception in UpdateTabs(): w.what=%s\n", e.what());
        goto cleanup;
    }
    catch (const char *pszWhat)
    {
        WT_L1_TRACE("Exception in UpdateTabs(): pszWhat=%s\n", pszWhat);
        goto cleanup;
    }
    catch (int what)
    {
        WT_L1_TRACE("Exception in UpdateTabs(): iWhat=%d\n", what);
        goto cleanup;
    }
    catch (...) 
    {
        WT_L1_TRACE("Exception in UpdateTabs()\n");
cleanup:
        WT_ASSERT(false);
        try
        {
            if (this  &&  ::IsWindow(m_hWnd))
            {
                FreeData();
                m_pTabCtrl->DeleteAllItems();
                PostMessage(WM_UPDATETABS);
            }
        }
        catch (...)
        {
            WT_L1_TRACE("Nested exception in UpdateTabs()\n");
        }
    }
#endif  // CATCH_EXCEPTIONS

    RETURN_INT(1);
}

void CTabsWindow::ForceTabUpdate()
{
    m_iLockUpdates = 0;
    UpdateTabs();
}

static void TrimWhite(CString& s)
{
    int iLeft = 0, iRight;
    while (isspace(s[iLeft])) ++iLeft;
    iRight = s.GetLength();
    while (iRight > iLeft  &&  isspace(s[iRight - 1])) --iRight;
    s = s.Mid(iLeft, iRight - iLeft);
}

void CTabsWindow::MangleName(CString& sPathIn, CString& sNameIn, 
    int iNum, CString &sNameOut)
{
    CString cStr, cPrefix, cSuffix, cBase, cTrimable, s, sNonShared;
    BOOL bHasAsterisk, bIsRC;
    int nPos, nRight, cLimit, i;

    cStr = sNameIn;
    cStr.Replace("&", "&&");

    cPrefix.Empty();
    cSuffix.Empty();

    if (sNameIn.Right(2) == " *")
    {
        cStr = cStr.Left(cStr.GetLength() - 2);
        bHasAsterisk = TRUE;
    }
    else
    {
        bHasAsterisk = FALSE;
    }

    if (m_bIsWTTab)
    {
        if (cfg_bGroupTabs)
        {
            cBase = sPathIn;
            if (cBase.IsEmpty())
            {
                cBase = cStr;
            }
            else
            {
                if ((nPos = GetExtensionPos(cBase)) >= 0)
                {
                    cBase = cBase.Left(nPos);
                }
                if (cfg_bGroupDiffPaths)
                {
                    cBase = cBase.Right(
                        cBase.GetLength() - cBase.ReverseFind('\\') - 1);
                    if (cfg_bGroupPrj  &&  theApp.m_bAllowWWhizInterface)
                    {
                        WWhizInterface *pWWI = theApp.GetWWhizInterface();
                        if (pWWI == NULL)
                        {
                            AfxMessageBox(IDS_NO_WWHIZINT_GROUP_PRJ, 
                                MB_OK | MB_ICONEXCLAMATION);
                            cfg_bGroupPrj = FALSE;
                        }
                        else
                        {
                            CString cStr;
                            try
                            {
                                WWhizProjectList& plist = pWWI->GetProjectList();
                                int cProjects = plist.GetProjectCount();
                                for (int i = 0; i < cProjects; ++i)
                                {
                                    WWhizProject *pprj = plist.GetProjectByIndex(i);
                                    if (pprj)
                                    {
                                        if (pprj->GetFileList().Find(sPathIn))
                                        {
                                            cStr = pprj->GetName();
                                            break;
                                        }
                                    }
                                }
                                cStr += ',';
                                cBase.Insert(0, cStr);
                            }
                            catch (...)
                            {
                                theApp.ReportWWhizInterfaceException();
                            }
                        }
                    }
                }
            }
            cBase.MakeUpper();
        }
        else
        {
            cBase = sNameIn;
        }
    }

    if (cfg_bStripPath)
    {
        cStr = cStr.Right(cStr.GetLength() - cStr.ReverseFind('\\') - 1);
    }

    // process .rc files
    CString cStrRC = cStr;
    cStrRC.MakeUpper();
    
    if (cStrRC.Find(".RC") >= 0  &&  cStrRC.Find(" - ") >= 0)
    {
        bIsRC = TRUE;

        if (m_bIsWTTab)
        {
            if (cfg_bGroupRes)
            {
                // just differentiate resource tabs from other tabs
                cBase += '*';
            }
            else
            {
                // make each tab unique
                cBase = sNameIn;
            }
        }

        if (!cfg_bDispRID)
        {
            nPos   = cStr.Find("- ");
            cStrRC = cStr.Left(nPos + 2);
            cStr   = cStr.Mid(nPos + 2);
            nPos   = cStr.Find('(');
            if (nPos < 0)
                nPos = cStr.Find(' ');
            else
                nPos--;
            cStr   = cStrRC + cStr.Mid(nPos + 1);
        }

        if (!cfg_bDispResType)
        {
            nPos = cStr.ReverseFind('(');
            cStr = cStr.Left(nPos);
        }

        if (!cfg_bDispResLang)
        {
            nPos   = cStr.Find('[');
            nRight = cStr.Find(']');

            // fix by Mark Cooke [mark.cooke@iee.org]:
            // DevStudio can omit the language part, so check for this
            if( (0 <= nPos)  &&  (0 <= nRight) )
            {
                cStrRC = cStr.Mid(nRight + 2);
                cStr   = cStr.Left(nPos);
                cStr  += cStrRC;
            }
        }

        nPos = cStr.Find(" - ");
        if (!cfg_bDispRC)
        {
            cSuffix = cStr.Mid(nPos + 2);
            cTrimable = "";
        }
        else
        {
            cTrimable = cStr.Left(nPos + 2);
            if (nPos != (cStr.GetLength() - 3))
            {
                cSuffix = cStr.Mid(nPos + (cfg_bGroupRes? 2 : 2));
            }
        }
    }
    else
    {
        // not a resource file

        bIsRC = FALSE;
        cTrimable = cStr;
    }

    cStr.Empty();
    cLimit = 0;  // count of chars for limit

    // trim prefix
    if (cfg_bTrimPrefixes  &&  !cfg_sTrimablePrefixes.IsEmpty())
    {
        i = 0;                
        cStr = cTrimable;
        AfxExtractSubString(s, cfg_sTrimablePrefixes, i, ',');
        while (!s.IsEmpty())
        {
            TrimWhite(s);
            if (!s.IsEmpty())
            {
                if (s.GetLength() <= cStr.GetLength()  &&
                    cStr.Left(s.GetLength()).CompareNoCase(s) == 0)
                {
                    cTrimable.Delete(0, s.GetLength());
                    if (cfg_bUseTrimPrefixChar)
                    {
                        cTrimable.Insert(0, (TCHAR)cfg_TrimPrefixChar);
                    }
                    break;
                }
            }
            ++i;
            AfxExtractSubString(s, cfg_sTrimablePrefixes, i, ',');
        }
        cStr.Empty();
    }

    // trim suffix
    if (cfg_bTrimSuffixes  &&  !cfg_sTrimableSuffixes.IsEmpty())
    {
        nPos = GetExtensionPos(cTrimable);
        i = 0;                
        cStr = cTrimable;
        AfxExtractSubString(s, cfg_sTrimableSuffixes, i, ',');
        while (!s.IsEmpty())
        {
            TrimWhite(s);
            if (!s.IsEmpty())
            {
                const int sLen = s.GetLength();
                if (sLen <= nPos  &&  
                    cStr.Mid(nPos - sLen, sLen).CompareNoCase(s) == 0)
                {
                    cTrimable.Delete(nPos - sLen, sLen);
                    if (cfg_bUseTrimSuffixChar)
                    {
                        cTrimable.Insert(nPos - sLen, 
                            (TCHAR)cfg_TrimSuffixChar);
                    }
                    break;
                }
            }
            ++i;
            AfxExtractSubString(s, cfg_sTrimableSuffixes, i, ',');
        }
        cStr.Empty();
    }

    nPos = GetExtensionPos(cTrimable);
    if (nPos >= 0)
    {
        if (cfg_bStripExt)
        {
            if (m_bIsWTTab)
            {
                sNonShared = cTrimable.Mid(nPos);
            }
            cTrimable = cTrimable.Left(nPos);
        }
        else
        {
            if (m_bIsWTTab  &&  cfg_bGroupTabs)
            {
                if (!bIsRC)
                {
                    cSuffix = cTrimable.Mid(nPos);
                    cTrimable = cTrimable.Left(nPos);
                }
            }
            else
                if (cfg_bLimitIgnoreExt)
                {
                    // move extension to part that isn't counted
                    cSuffix = cTrimable.Mid(nPos) + cSuffix;
                    cTrimable = cTrimable.Left(nPos);
                }
        }
    }

    if (cfg_bLimitChars  &&  (cfg_bLimitResChars  ||  !bIsRC))
    {
        if (bIsRC  &&  (!m_bIsWTTab  ||  !cfg_bGroupRes))
        {
            cTrimable += cSuffix;
            cSuffix.Empty();
        }

        if (cTrimable.GetLength() > cfg_iCharLimit)
        {
            if (cTrimable.GetLength() == cfg_iCharLimit  ||  
                !cfg_bUseLimitChar)
            {
                cTrimable = cTrimable.Left(cfg_iCharLimit);
            }
            else
            {
                cTrimable = cTrimable.Left(cfg_iCharLimit - 1);
                cTrimable += (char)cfg_LimitCharacter;
            }
        }
    }

    cStr = cTrimable;

    if (!cfg_bShowIcons  &&  cfg_bShowNumbers  &&  iNum >= 0  &&  iNum < 9)
    {
        CString cNum;
        cNum.Format("%d. ", iNum + 1);
        if (m_bIsWTTab  &&  cfg_bGroupTabs)
        {
            cPrefix = cNum;
        }
        else
        {
            cStr = cNum + cStr;
        }
    }

    if (bHasAsterisk)
    {
        cSuffix += " *";
    }

    if (m_bIsWTTab)
    {
        cTrimable.GetBuffer(128);
        cTrimable.ReleaseBuffer(0);
        cTrimable = cPrefix;
        cTrimable += '?';
        cTrimable += cStr;
        cTrimable += '?';
        cTrimable += cSuffix;
        cTrimable += '?';
        cTrimable += cBase;
        if (!sNonShared.IsEmpty())
        {
            cTrimable += '?';
            cTrimable += cPrefix;
            cTrimable += sNonShared;
        }
    }
    else
        cTrimable = cStr + cSuffix;

    sNameOut = cTrimable;
}


// true - row count is ok
// false - row count was reset
bool CTabsWindow::CheckRowCount()
{
    static int iRowCheckRef = 0;
    static int iLastDelta = 0;

    WT_FN_TRACE("CheckRowCount");

    const int iTabCount = m_pTabCtrl->GetItemCount();
    if (cfg_bFixedRowCount ||  !pGlobalActiveManager->GetManaging())
    {
        return true;
    }

    WT_ASSERT(g_cTabRows > 0);

    int iDelta = 0;

    if (iTabCount <= 1)
    {
        iDelta = 1 - g_cTabRows;
    }
    else
    {
        CRect r_client, r_tab;
        m_pTabCtrl->GetClientRect(r_client);
        m_pTabCtrl->GetExtremeItemRect(r_tab);
           
        const int MARGIN_X = min(r_tab.Width(), r_client.Width()) - 2;
        const int MARGIN_Y = r_tab.Height() - 4;

        WT_L2_TRACE("Client Rect = (%d, %d, %d, %d)\n", 
            r_client.left, r_client.top, r_client.right, r_client.bottom);
        WT_L2_TRACE("Extreme Rect = (%d, %d, %d, %d)\n", 
            r_tab.left, r_tab.top, r_tab.right, r_tab.bottom);

        switch (cfg_iOrientation)
        {
            case soTop:
                if (r_tab.bottom > r_client.bottom)
                {
                    iDelta = 1;
                }
                else
                {
                    if ((r_client.bottom - r_tab.bottom) > MARGIN_Y)
                    {
                        iDelta = -1;
                    }
                }
                break;

            case soBottom:
                if (r_tab.top < r_client.top)
                {
                    iDelta = 1;
                }
                else
                {
                    if ((r_tab.top - r_client.top) > MARGIN_Y)
                    {
                        iDelta = -1;
                    }
                }
                break;

            case soLeft:
                if (r_tab.right > r_client.right)
                {
                    iDelta = 1;
                }
                else
                {
                    if ((r_client.right - r_tab.right) > MARGIN_X)
                    {
                        iDelta = -1;
                    }
                }
                break;

            case soRight:
                if (r_tab.left < r_client.left)
                {
                    iDelta = 1;
                }
                else
                {
                    if ((r_tab.left - r_client.left) >= MARGIN_X)
                    {
                        iDelta = -1;
                    }
                }
                break;

            DEFAULT_UNREACHABLE;
        }
    }

    ++iRowCheckRef;
    WT_L3_TRACE("Delta is %d, ref=%d, rows=%d\n", iDelta, iRowCheckRef,
        g_cTabRows);
    if (iRowCheckRef == 1)
    {
        iLastDelta = iDelta;
    }
    else
    {
        if (iDelta != iLastDelta)
        {
            iDelta = 0;
        }
    }
    if (iDelta)
    {
        g_cTabRows += iDelta;
        pGlobalActiveManager->SetManaging(false);
        pGlobalActiveManager->SetManaging(true);
        --iRowCheckRef;
        return false;
    }
    --iRowCheckRef;

    return true;
}


// Retrieves the pointer to a DevStudio window that corresponds to a tab,
// by scanning the DevStudio document windows, looking for a window with the
// same title as the tab.
// This method demonstrates enumeration using the enumeration 
// function/property.
bool CTabsWindow::FindDSWindow(int iSel, IGenericWindow **ppWindow, 
    HWND *phWnd/* = NULL*/)
{
    if (iSel < 0)
    {
        // this shoulden't be, but to avoid a crash in case of bugs, we'll
        // just return gracefully
        return FALSE;
    }

    const tabdata_t * const pTabData = GetTabData(iSel);
    HWND hWnd = pTabData->hWnd;

    if (!hWnd  ||  !::IsWindow(hWnd))
        return FALSE;

    if (phWnd)
        *phWnd = hWnd;

    if (ppWindow)
    {
        return FindDSWindow(hWnd, ppWindow);
    }

    return TRUE;
}

bool CTabsWindow::FindDSWindow(HWND hWnd, IGenericWindow **ppWindow)
{
    WT_ASSERT(ppWindow != NULL);

    CComPtr<IDispatch> pDisp;
    CComQIPtr<IWindows, &IID_IWindows> pWindows;
    CComBSTR bStr, bStrWindowName;
    CString cStr;
    CWnd::FromHandle(hWnd)->GetWindowText(cStr);
    bStrWindowName = cStr; //pTabData->cPath;

    m_pApplication->get_Windows(&pDisp);
    pWindows = pDisp;
    pDisp = NULL;

    CComPtr<IUnknown> pUnk;
    CComQIPtr<IEnumVARIANT, &IID_IEnumVARIANT> pNewEnum;
    if (SUCCEEDED(pWindows->get__NewEnum(&pUnk)) && pUnk != NULL)
    {
        pNewEnum = pUnk;
        VARIANT varWindow;
        CComQIPtr<IGenericWindow, &IID_IGenericWindow> pWindowItem;
        while (pNewEnum->Next(1, &varWindow, NULL) == S_OK)
        {
            ASSERT (varWindow.vt == VT_DISPATCH);
            pWindowItem = varWindow.pdispVal;
            VariantClear(&varWindow);
            pWindowItem->get_Caption(&bStr);
            if (bStr == bStrWindowName)
            {
                AtlComPtrAssign((IUnknown **)ppWindow, pWindowItem);
                return TRUE;
            }
            bStr.Empty();
        }
    }

    return FALSE;
}

// styles to remove before we change to the new style
#define REM_STYLE  (TCS_RIGHT | TCS_BOTTOM | TCS_VERTICAL | TCS_MULTILINE | TCS_RAGGEDRIGHT)
#define MIN_STYLE  (WS_VISIBLE | WS_CHILD | TCS_TOOLTIPS | TCS_FOCUSNEVER | TCS_FORCELABELLEFT)

void CTabsWindow::UpdateStyle()
{
    WT_FN_TRACE("UpdateStyle");

    bool    bCreate;
    int     iStyle = 0, iOldStyle, iOldTabCount = 0;
    CRect   r;

    if (cfg_iOrientation != soBottom  &&  cfg_iOrientation != soTop)
    {
        cfg_iOrientation = soBottom;
    }

    SetRedraw(FALSE);

    if (g_cTabRows <= 0)
    {
        if (cfg_iRows <= 0) cfg_iRows = 1;
        g_cTabRows = cfg_bFixedRowCount? cfg_iRows : 1;
    }

    if (m_pTabCtrl  &&  !::IsWindow(m_pTabCtrl->GetSafeHwnd()))
    {
        delete m_pTabCtrl;
        m_pTabCtrl = NULL;
    }

    
    r = CRect(0, 0, 1, 1);
    if (m_pTabCtrl)
    {
        iOldTabCount = m_pTabCtrl->GetItemCount();
        if (pGlobalActiveManager->GetManaging())
        {
            m_pTabCtrl->GetWindowRect(r);
            ScreenToClient(r);
        }
        if (cfg_bUseWTTabCtrl != (BOOL)m_bIsWTTab)
        {
            m_pTabCtrl->SendMessage(WM_CLOSE);
            delete m_pTabCtrl;
            m_pTabCtrl = NULL;
        }   
        else
        {
			m_pTabCtrl->DeleteAllItems();
        }
    }

    if (!m_pTabCtrl)
    {
        if (g_bUseWndTabsExt  &&  cfg_bUseWTTabCtrl)
        {
            m_pTabCtrl = NewWTTabCtrl();
        }

        if (!m_pTabCtrl)  // NewWTTabCtrl() may fail
        {
            m_pTabCtrl = new CFancyTabCtrl();
            m_bIsWTTab = false;
        }
        else
            m_bIsWTTab = true;

        REBARBANDINFO rbbi;
        rbbi.cbSize = sizeof(rbbi);
        rbbi.fMask = RBBIM_CHILD;
        rbbi.hwndChild = m_pTabCtrl->m_hWnd;
        GetReBarCtrl().SetBandInfo(1, &rbbi);
    }

    switch (cfg_iOrientation)
    {
        case soRight:
            iStyle |= TCS_RIGHT;
            // fall through

        case soLeft:
            iStyle |= TCS_VERTICAL; // | TCS_MULTILINE;
            break;

        case soBottom:
            iStyle |= TCS_BOTTOM;
            // fall through

        case soTop:
            break;

        DEFAULT_UNREACHABLE;
    }

    if (g_cTabRows > 1  ||  !cfg_bFixedRowCount)
    {
        iStyle |= TCS_MULTILINE;
        if (!cfg_bNoRaggedRight)
            iStyle |= TCS_RAGGEDRIGHT;
    }
    else
    {
        iStyle |= TCS_RAGGEDRIGHT;
    }

    bCreate = true;
    if (::IsWindow(m_pTabCtrl->m_hWnd))
    {
        iOldStyle = m_pTabCtrl->GetStyle();
        iStyle    = ((iOldStyle & ~REM_STYLE) | iStyle);

        if (iStyle != iOldStyle)
        {
            // simply calling ModifyStyle() isn't good enough, so instead 
            // we'll destroy the control and start over:
            m_pTabCtrl->DestroyWindow();
        }
        else
            bCreate = false;
    }

    WT_L2_TRACE("Orientation = %d\n", cfg_iOrientation);
    WT_L2_TRACE("WTTabCtrl   = %d\n", m_bIsWTTab);

    if (bCreate)
    {
        if (!m_pTabCtrl->Create(iStyle | MIN_STYLE, r, this, ID_TAB))
        {
            AfxMessageBox("Failed to create tab control!", 
                MB_OK | MB_ICONSTOP);
            delete m_pTabCtrl;
            m_pTabCtrl = NULL;
            m_bIsWTTab = false;
        }
    }

    CMainFrame *pFrame = ((CMainFrame *)AfxGetApp()->m_pMainWnd);

    if (pFrame)
    {
        pFrame->m_wndMenuBar.EnableDocking(
            IS_HORIZONTAL(cfg_iOrientation)? CBRS_ALIGN_TOP : CBRS_ALIGN_LEFT);
    }


    if (m_pTabCtrl)
    {
        CFont *pFont = new CFont();
        if (cfg_ftFontType == ftSerif)
        {
            pFont->CreatePointFont(90, "MS Serif");
        }
        else
        {
            pFont->CreatePointFont(80, "MS Sans Serif");
        }
        m_pTabCtrl->SetTabFont(pFont, cfg_bShowIcons);

        if (cfg_bButtonTabs)
        {
            // based on original suggestion by ov@aport.ru
            m_pTabCtrl->ModifyStyle(TCS_TABS | TCS_BOTTOM, 
                TCS_BUTTONS | TCS_FLATBUTTONS | TCS_HOTTRACK);
        }

        if (m_bIsWTTab)
        {
            SetWTTabCtrlColors(m_pTabCtrl, cfg_RegTxtColor, cfg_SelTxtColor);
            int flags = 0;
            if (!cfg_bShowGroupDelim) flags |= WTXF_STRIP_FIRST_GROUP_CHAR;
            if (cfg_bWTXAllSpecial)   flags |= WTXF_ALL_SPECIAL;
            if (cfg_bWTXCloseButton)  flags |= WTXF_TAB_CLOSE_BUTTON;
            if (cfg_bSortMiniTB)      flags |= WTXF_SORT_MINI_TB;
            WTTabCtrlSetFlags(m_pTabCtrl, flags);
        }

        if (cfg_bShowIcons)
            m_pTabCtrl->SetImageList(&m_TabImages);
        else
            m_pTabCtrl->SetImageList(NULL);

        // a direct update (UpdateTabs()) at this point causes less flicker 
        // than an update post, but can cause problems (for instance, due to
        // a bug in the tab control it will cause a crash if there is only 
        // one tab).
        if (pGlobalActiveManager)
        {
            pGlobalActiveManager->PostUpdateMessage();
        }
    }
    UpdateReBar();
    
	// disable visual styles
	typedef HRESULT (STDAPICALLTYPE *pfnSetWindowTheme)
		(HWND hwnd, LPCWSTR pszSubAppName, LPCWSTR pszSubIdList);
	pfnSetWindowTheme SetWindowTheme = (pfnSetWindowTheme)
		::GetProcAddress(::GetModuleHandle(_T("uxtheme.dll")), "SetWindowTheme");
	if (SetWindowTheme != NULL)
	{
		SetWindowTheme(GetSafeHwnd(), L"", L"");
		SetWindowTheme(m_pTabCtrl->GetSafeHwnd(), L"", L"");
	}

    SetRedraw(TRUE);
    UpdateWindow();
}

CTabsWindow::tabdata_t * CTabsWindow::GetTabData(int iTabIndex)
{
    TC_ITEM tab_item;

    tab_item.mask = TCIF_PARAM;
    m_pTabCtrl->GetItem(iTabIndex, &tab_item);    

    return ((tabdata_t *)tab_item.lParam);
}

void CTabsWindow::Reorder()
{
    int temp = cfg_TabOrdering;
    cfg_TabOrdering = toMDI;
    UpdateTabs();
    cfg_TabOrdering = temp;
}

void CTabsWindow::Renumber()
{
    BOOL bTemp = cfg_bPreserveNumbering;
    cfg_bPreserveNumbering = FALSE;
    UpdateTabs();
    cfg_bPreserveNumbering = bTemp;
}

void CTabsWindow::ActivateTab(int iNumber)
{
    HWND        hWnd;
    tabdata_t * pData;

    iNumber--;
    
    // find the tab to select
    for (int i = 0; i < m_pTabCtrl->GetItemCount(); i++)
    {
        pData = GetTabData(i);
        if (pData->iNumber == iNumber)
        {
            if (FindDSWindow(i, NULL, &hWnd))
            {
                ActivateWindow(hWnd);
            }
            break;
        }
    }
}

// GetDocumentObject: Retrieves a window's document object.
//
// BUG BUG: DevStudio provides the get_Parent that returns a window's 
// document object.  But using get_Parent on a non-text window, might 
// cause DevStudio to crash (a good example of this is a resource window).  
// Since such windows might actually have a document, this function is used
// to get document "the hard way"
bool CTabsWindow::GetDocumentObject(
    CComPtr<IGenericWindow> pWindow,
    CComPtr<IGenericDocument>& pDoc)
{
    // Matching the document to a window is a two-step process:
    //  1. get a document object from the document list
    //  2. scan all windows belonging to the document
    //  All of the documents/document windows are scanned until the
    //  window is matched.
    CComPtr<IUnknown> pUnk;
    CComPtr<IDispatch> pDisp;
    CComQIPtr<IDocuments, &IID_IDocuments_Resolved> pDocuments;
    CComQIPtr<IEnumVARIANT, &IID_IEnumVARIANT> pNewEnum;
    CComQIPtr<IGenericDocument, &IID_IGenericDocument_Resolved> pDocGen;

    CComBSTR bStr;

    WT_ASSERT(pWindow.p != NULL);
    if (pWindow.p == NULL)
    {
        return FALSE;
    }

    pWindow->get_Type(&bStr);
    if (bStr == L"Text")
    {
        pWindow->get_Parent(&pDisp);
        pDocGen = pDisp;
        pDoc = pDocGen;
        return (pDoc != NULL);
    }
    bStr.Empty();

    m_pApplication->get_Documents(&pDisp);
    pDocuments = pDisp;
    pDisp = NULL;
    pDoc = NULL;

    if (SUCCEEDED(pDocuments->get__NewEnum(&pUnk)) && pUnk != NULL)
    {
        pNewEnum = pUnk;
        VARIANT varDoc;
        while (pNewEnum->Next(1, &varDoc, NULL) == S_OK)
        {
            ASSERT (varDoc.vt == VT_DISPATCH);
            pDocGen = varDoc.pdispVal;
            VariantClear(&varDoc);
            
            // iterate the document's windows
            CComQIPtr<IWindows, &IID_IWindows> pWindows;
            pDocGen->get_Windows(&pDisp);
            pWindows = pDisp;
            pDisp = NULL;
            
            CComPtr<IUnknown> pUnk2;
            CComQIPtr<IEnumVARIANT, &IID_IEnumVARIANT> pEnum2;
            if (SUCCEEDED(pWindows->get__NewEnum(&pUnk2)) && pUnk2 != 
                NULL)
            {
                pEnum2 = pUnk2;
                VARIANT varWindow;
                CComQIPtr<IGenericWindow, &IID_IGenericWindow> pWindow2;
                while (pEnum2->Next(1, &varWindow, NULL) == S_OK)
                {
                    ASSERT (varWindow.vt == VT_DISPATCH);
                    pWindow2 = varWindow.pdispVal;
                    VariantClear(&varWindow);
                    if (pWindow2 == pWindow)
                    {
                        pDoc = pDocGen.p;
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

void CTabsWindow::OnPaint() 
{
    CReBar::OnPaint();

    CClientDC dc(this); // device context for painting

    CRect r, r2;

    if (!(m_mfh.GetSafeHwnd()))
        return;

    GetClientRect(r);
    if (IS_HORIZONTAL(cfg_iOrientation))
    {
        CPen *pOldPen;
        pOldPen = dc.SelectObject(
            cfg_iOrientation == soBottom? 
            &m_penShadowBottom : &m_penShadowTop);
        dc.MoveTo(r.right - 1, r.top);
        dc.LineTo(r.right - 1, r.bottom - 1);
        dc.SelectObject(pOldPen);
    }
}


void CTabsWindow::OnLButtonDown(UINT nFlags, CPoint point) 
{
    if (m_RectGripper.PtInRect(point) || true)
    {
        m_TrackingOrientation = SnapOrientations(cfg_iOrientation);
        m_bVisibleTracking = false;
        RecalcTrackingRect();        
        DrawTrackingRect();
        SetCapture();
        m_hSavedCursor = GetCursor();
        SetCursor(LoadCursor(NULL, IDC_SIZEALL));
        m_bTracking = TRUE;
    }
	
	CReBar::OnLButtonDown(nFlags, point);
}

void CTabsWindow::OnLButtonUp(UINT nFlags, CPoint point) 
{
    if (m_bTracking)
    {
        WT_ASSERT(m_hSavedCursor);
        SetCursor(m_hSavedCursor);
        m_hSavedCursor = NULL;
        if (m_bVisibleTracking)
        {
            DrawTrackingRect();
            ::ReleaseCapture();
            m_bTracking = FALSE;

            if (m_TrackingOrientation != SnapOrientations(cfg_iOrientation))
            {
                pGlobalActiveManager->SetManaging(false);
                cfg_iOrientation = m_TrackingOrientation;
                pGlobalTabs->UpdateStyle();
                WriteConfiguration();
                pGlobalActiveManager->SetManaging(true);
            }
        }
        else
        {
            m_bTracking = FALSE;
        }
    }
	
	CReBar::OnLButtonUp(nFlags, point);

    CheckRowCount();
}

void CTabsWindow::OnMouseMove(UINT nFlags, CPoint point) 
{
    if (m_bTracking)
    {
        CRect r;
        GetClientRect(r);
        if (( IS_HORIZONTAL(cfg_iOrientation) && point.y < r.bottom) ||
            (!IS_HORIZONTAL(cfg_iOrientation) && point.x < r.right) )
        {
        	CReBar::OnMouseMove(nFlags, point);
        }

        if (m_bIsDragging == false  ||  !r.PtInRect(point))
        {
            SetCursor(LoadCursor(NULL, IDC_SIZEALL));
            SnapOrientations o;
            o = CalcTrackingOrientation(point);
            if (o != m_TrackingOrientation  ||  !m_bVisibleTracking)
            {
                if (m_bVisibleTracking)
                    DrawTrackingRect();
                m_TrackingOrientation = o;
                RecalcTrackingRect();
                DrawTrackingRect();
            }
        }
        else
        {
            SetCursor(LoadCursor(NULL, IDC_SIZEWE));
            if (m_bVisibleTracking)
                DrawTrackingRect();
        }
    }
    else
    {
    	CReBar::OnMouseMove(nFlags, point);
    }
}

void CTabsWindow::DrawTrackingRect()
{
    m_bVisibleTracking = !m_bVisibleTracking;
    CDC *pDC = g_pDevStudioWnd->GetDC();
    pDC->PatBlt(m_RectTracking.left, m_RectTracking.top, m_RectTracking.Width(), 2, DSTINVERT);
    pDC->PatBlt(m_RectTracking.left, m_RectTracking.bottom - 2, m_RectTracking.Width(), 2, DSTINVERT);
    pDC->PatBlt(m_RectTracking.right - 2, m_RectTracking.top, 2, m_RectTracking.Height(), DSTINVERT);
    pDC->PatBlt(m_RectTracking.left, m_RectTracking.top, 2, m_RectTracking.Height(), DSTINVERT);
	g_pDevStudioWnd->ReleaseDC(pDC);
}

SnapOrientations CTabsWindow::CalcTrackingOrientation(CPoint pt)
{
    CRect r;
    SnapOrientations o;
    int delta, minDelta;

    pGlobalActiveManager->GetWindowRect(r);
    ClientToScreen(&pt);

    o = soBottom;
    minDelta = (r.bottom - pt.y);
/*
    delta = (r.right - pt.x);
    if (delta < minDelta  &&  !cfg_bUseWTTabCtrl)
    {
        o = soRight;
        minDelta = delta;
    }

    delta = (pt.x - r.left);
    if (delta < minDelta  &&  !cfg_bUseWTTabCtrl)
    {
        o = soLeft;
        minDelta = delta;
    }
*/
    delta = (pt.y - r.top);
    if (delta < minDelta  &&  SnapStates(cfg_iSnap) != ssWindow)
    {
        o = soTop;
        minDelta = delta;
    }

    return o;
}

void CTabsWindow::RecalcTrackingRect()
{
    if (m_TrackingOrientation == SnapOrientations(cfg_iOrientation))
    {
        GetWindowRect(m_RectTracking);
    }
    else
    {
        CRect r;
        pGlobalActiveManager->GetWindowRect(r);
        pGlobalActiveManager->GetParent()->ScreenToClient(r);
        pGlobalActiveManager->CalcTabsPosition(r, m_RectTracking, 
            m_TrackingOrientation);
    }

    g_pDevStudioWnd->ScreenToClient(m_RectTracking);
}


// activates and window and restores it's size (i.e. unminimizes it)
// idea and primary implementation: Alexey N. Kirpa (alexeykirpa@mail.ru)
void CTabsWindow::ActivateWindow(HWND hWnd, bool bZoomOnly)
{
    ::ShowWindow(hWnd, ::IsZoomed(hWnd)? SW_SHOW : SW_RESTORE);

    if (!bZoomOnly)
    {
        // only send a message if it's a new window that needs activation
        if ((HWND)pGlobalMDIManager->SendMessage(WM_MDIGETACTIVE) != hWnd)
        {
            m_bAboutToUpdate = true;
            pGlobalMDIManager->PostMessage(WM_MDIACTIVATE, (WPARAM)hWnd);
        }
    }
    UpdateCommandContext(m_pTabCtrl->GetCurSel());
}


// **************************************************************************
// BUG BUG: MFC's _AFXFindPopupMenuFromID won't find submenu text entries.
// Instead of recompiling the MFC dll's, I've placed the following two 
// replacement functions (_FixedAfxFindPopupMenuFromID and OnMeasureItem) 
// here.  They two functions are basically copies of their respective MFC
// functions - but with the necessery fixes.

static CMenu* AFXAPI _FixedAfxFindPopupMenuFromID(CMenu* pMenu, UINT nID)
{
	ASSERT_VALID(pMenu);
	// walk through all items, looking for ID match
	UINT nItems = pMenu->GetMenuItemCount();
	for (int iItem = 0; iItem < (int)nItems; iItem++)
	{
		CMenu* pPopup = pMenu->GetSubMenu(iItem);
		if (pPopup != NULL)
		{
            if ((UINT)pPopup->GetSafeHmenu() != nID)
            {
    			// recurse to child popup
	    		pPopup = _FixedAfxFindPopupMenuFromID(pPopup, nID);
            }

			if (pPopup != NULL)
				return pPopup;
		}
		else if (pMenu->GetMenuItemID(iItem) == nID)
		{
			// it is a normal item inside our popup
			pMenu = CMenu::FromHandlePermanent(pMenu->m_hMenu);
			return pMenu;
		}
	}
	// not found
	return NULL;
}

bool CTabsWindow::GetCommandContext(int iTab, WTSDK_CommandContext& ctx)
{
    bool     bRetVal = true;
    CString  cStr;
    CComBSTR bStr;

    UINT cbSize = ctx.cbSize;
    ZeroMemory(&ctx, sizeof(ctx));
    WT_ASSERT(cbSize == 296  || // original ctx 
              cbSize == 300     // added: ctx.iTab
              );

    tabdata_t *pTabData;

    if (cbSize >= 300)
    {
        ctx.iTab = iTab;
    }

    if (iTab >= 0)
    {
        pTabData = GetTabData(iTab);
    }
    else
    {
        pTabData = NULL;
    }

    if (pTabData == NULL  ||  
        pTabData->pWindow == NULL  ||  
        !::IsWindow(pTabData->hWnd))
    {
        ctx.bHasDoc = false;
        ctx.bHasFile = false;
        ctx.bIsActiveWindow = false;
        ctx.bIsTextWindow = false;
        ctx.bIsGroupOperation = false;
        ctx.hWnd = NULL;
        ctx.szFullPath[0] = '\0';
        goto exit;
    }

    ctx.hWnd            = pTabData->hWnd;
    ctx.pWindow         = pTabData->pWindow;
    ctx.pDoc            = pTabData->pDoc;
    ctx.bHasDoc         = (ctx.pDoc != NULL);
    ctx.bIsActiveWindow = (iTab == m_pTabCtrl->GetCurSel());

    ctx.pWindow->get_Type(&bStr);
    ctx.bIsTextWindow = bool(bStr == L"Text");
    bStr.Empty();

    if (ctx.bHasDoc)
    {
        ctx.pDoc->get_FullName(&bStr);
        cStr = bStr;
        strcpy(ctx.szFullPath, cStr);
        bStr.Empty();
    }
    else
    {
        ctx.szFullPath[0] = '\0';
    }

    ctx.bHasFile = (ctx.szFullPath[0] != '\0');

    ctx.bIsGroupOperation = false;

exit:
    if (::IsWindow(g_pMainFrame->GetSafeHwnd()))
        g_pMainFrame->SendMessage(WM_IDLEUPDATECMDUI, (WPARAM)TRUE);

    return bRetVal;
}

// trick to access protected member
class CBCGPopupMenu2 : public CBCGPopupMenu
{
    friend class CTabsWindow;
};

bool CTabsWindow::UpdateCommandContext(int iTab)
{
    if (CMainFrame::m_pCmdCtx)
    {
        if (CBCGPopupMenu2::m_pActivePopupMenu != NULL)
        {
            return false;
        }
        delete CMainFrame::m_pCmdCtx;
        CMainFrame::m_pCmdCtx = NULL;
    }

    CMainFrame::m_pCmdCtx = new WTSDK_CommandContext;
    CMainFrame::m_pCmdCtx->cbSize = sizeof(*CMainFrame::m_pCmdCtx);

    return GetCommandContext(iTab, *CMainFrame::m_pCmdCtx);
}


bool CTabsWindow::UpdateCommandContext(CPoint ptHitTest)
{
    TCHITTESTINFO   hti;
    int             iTab;

    hti.pt = ptHitTest; 
    m_pTabCtrl->ScreenToClient(&hti.pt);
    iTab = m_pTabCtrl->HitTest(&hti);

    if (UpdateCommandContext(iTab))
    {
        if (g_bUseWndTabsExt  &&  cfg_bUseWTTabCtrl  &&  cfg_bUseGroupOps  &&  
            WTTabCtrlIsGroupSection(m_pTabCtrl, hti.pt))
        {
            CMainFrame::m_pCmdCtx->bIsGroupOperation = true;
        }
        return true;
    }

    return false;
}

LRESULT CTabsWindow::OnTabInfoUpdate(WPARAM wParam, LPARAM lParam)
{
    DoTabEvent((WTSDK_TabUpdateInfo *)wParam);
    return 1;
}

void CTabsWindow::OnToolBarQueryDelete(NMHDR* pNMHDR, LRESULT* pResult)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    *pResult = 1;
}

void CTabsWindow::OnBeginDrag(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    m_bIsDragging = true;
    if (m_bTracking)
    {
        DrawTrackingRect();
    }
}

void CTabsWindow::OnEndDrag(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    m_bIsDragging = false;

    REBARBANDINFO rbbi;

    rbbi.cbSize = sizeof(rbbi);
    rbbi.fMask = RBBIM_SIZE;
    GetReBarCtrl().GetBandInfo(0, &rbbi);
    cfg_iReBarWidth = rbbi.cx;
}

void CTabsWindow::DoForGroup(pfnWndCmd cmdfn, int iTab /*= -1*/, 
                             boolean bInverse /*= false*/)
{
    const int cTabs = m_pTabCtrl->GetItemCount();

    if (cTabs == 0)
    {
        MessageBeep(-1);
        return;
    }

    if (iTab < 0)
    {
        iTab = m_pTabCtrl->GetCurSel();
    }

    HWND *pHWND = new HWND[cTabs];
    int   cWindows = 0;

    if (m_bIsWTTab)
    {
        // more precise method (based on user options)
        int *       pInfo = new int[cTabs];
        WTTabCtrlGetGroupInfo(m_pTabCtrl, pInfo);
        const int   iGroupID = pInfo[iTab];

        for (int i = 0; i < cTabs; ++i)
        {
            if ((pInfo[i] == iGroupID) != bInverse)
            {
                pHWND[cWindows] = GetTabData(i)->hWnd;
                ++cWindows;
            }
        }

        delete [] pInfo;
    }
    else
    {
        CString     cCaption, cStr;
        HWND        hWnd, hWndNext;
        
        CWnd::FromHandle(GetTabData(iTab)->hWnd)->GetWindowText(cStr);
        GetGroupString(cStr);
    
        hWnd = ::GetTopWindow(pGlobalMDIManager->m_hWnd);
        while (hWnd)
        {
            hWndNext = ::GetNextWindow(hWnd, GW_HWNDNEXT);
            ::GetWindowText(hWnd, cCaption.GetBuffer(256), 256);
            cCaption.ReleaseBuffer();
            GetGroupString(cCaption);
        
            if ((cStr.Compare(cCaption) == 0) != bInverse)
            {
                pHWND[cWindows] = hWnd;
                ++cWindows;
            }
            hWnd = hWndNext;
        }
    }

    while (--cWindows >= 0)
    {
        cmdfn(pHWND[cWindows]);
    }

    delete [] pHWND;
}

void CTabsWindow::ApplyWindowLimit()
{
    // limit amount of open windows
    // original idea by: Anatoly Sennov [a_s@softhome.net]

    if (pGlobalActiveDSWindow->GetSafeHwnd() == NULL)
    {
        return;
    }

    // limits enabled by user?
    const bool bIsDebug = g_pDevStudioWnd->m_bInDebuggingSession;
    if (!(bIsDebug? cfg_bUseWindowLimitDbg : cfg_bUseWindowLimit))
    {
        return;
    }

    const unsigned int iWindowLimit = 
        bIsDebug? cfg_iWindowLimitDbg : cfg_iWindowLimit;
    int cWindows = pGlobalMDIManager->GetWindowCount();

    const int  cTabs = pGlobalTabs->m_pTabCtrl->GetItemCount();
    int *      pInfo = new int[cTabs];
    const bool bIsGroupCount = 
        (cfg_bLimitGroups  &&  pGlobalTabs->m_bIsWTTab);

    if (bIsGroupCount)
    {
        cWindows = WTTabCtrlGetGroupInfo(pGlobalTabs->m_pTabCtrl, pInfo);
    }

    if (cWindows > iWindowLimit) 
    {
        bool        bClosed = false;
        unsigned    cIgnored = 0;
        unsigned    i = 0;
        CWnd *      pWnd = pGlobalMDIManager->GetTopWindow()->GetWindow(GW_HWNDLAST);
        CWnd *      pPrevWnd;
        CString     cStr;
        int         tab_index = cTabs - 1;

        while (pWnd  &&  cWindows > iWindowLimit)
        {
            // make sure the user can open at least one window over the 
            // limit when all the documents have been modified
            if (i == (cWindows - 1)  &&  cIgnored >= iWindowLimit)
                break;

            pPrevWnd = pWnd->GetWindow(GW_HWNDPREV);

            pWnd->GetWindowText(cStr);
            if (cStr.Right(2) != " *" ) 
            {
                WT_L3_TRACE("Limit close wnd=%p\n", pWnd->m_hWnd);
                pWnd->PostMessage(WM_CLOSE);
                if (bIsGroupCount)
                {
                    bool bClosedAGroup = true;
                    const int group_id = pInfo[tab_index];
                    pInfo[tab_index] = 0;
                    for (int j = 0; j < cTabs; j++)
                    {
                        if (pInfo[j] == group_id)
                        {
                            bClosedAGroup = false;
                            break;
                        }
                    }
                    if (bClosedAGroup)
                    {
                        --cWindows;
                    }
                }
                else
                {
                    --cWindows;
                }
                bClosed = true;
            }
            else
            {
                cIgnored++;
                i++;
            }

            pWnd = pPrevWnd;
            --tab_index;
        }
    }

    delete pInfo;
}

void CTabsWindow::OnMButtonDown(UINT nFlags, CPoint point) 
{
    TCHITTESTINFO hti;
    ClientToScreen(&point);
    hti.pt = point;
    m_pTabCtrl->ScreenToClient(&hti.pt);
    int iTab = m_pTabCtrl->HitTest(&hti);
    if (iTab >= 0)
    {
        VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));

        if (UpdateCommandContext(point))
        {
            // apply middle button command
            CString strTemp;
	        g_pMainFrame->GetMessageString(cfg_iMidBtnCommand, strTemp);
            if (!strTemp.IsEmpty())  // fail safe
            {
                g_pMainFrame->SendMessage(WM_COMMAND, cfg_iMidBtnCommand);
            }
        }

        VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
    }
	CReBar::OnMButtonDown(nFlags, point);
}
