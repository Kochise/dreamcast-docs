/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// MainFrame.cpp : implementation file
//

#include "stdafx.h"
#include "wndtabs.h"
#include "MainFrame.h"

#include <afxpriv.h>
#include <bcgdockbar.h>
#include <dde.h>

#include "options.h"
#include "DevStudioWnd.h"
#include "TabsWindow.h"
#include "Commands.h"
#include "Config.h"
#include "TabManagerWindow.h"
#include "DS_MDIWnd.h"
#include "AddInComm\AddInComm.h"
#include "Utils.h"
#include "ShellContextMenu.h"
#include "Imports.h"
#include "SDK_Supp.h"
#include "help\HelpIDs.h"
#include "Extensions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


WTSDK_CommandContext * CMainFrame::m_pCmdCtx = NULL;

const UINT uiUserBarId = AFX_IDW_CONTROLBAR_FIRST + 21;

// determined with Spy++ for VC5/VC6
const int IDC_DEVSTUDIO_STARTBUILD = 33803;
const int IDC_DEVSTUDIO_STOPBUILD  = 34049;


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CBCGFrameWnd)

CToolTipCtrl m_ToolTipCtrl;

CMainFrame::CMainFrame() : m_pSCM(NULL), m_bCanClose(false)
{
}

CMainFrame::~CMainFrame()
{
}


BEGIN_MESSAGE_MAP(CMainFrame, CBCGFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_COMMAND(IDC_OPTIONS, OnOptions)
	ON_COMMAND(IDC_CUSTOMIZE, OnCustomize)
	ON_WM_CREATE()
	ON_COMMAND(IDC_RENUMBER, OnRenumber)
	ON_COMMAND(IDC_REORDER, OnReorder)
	ON_UPDATE_COMMAND_UI(IDC_RENUMBER, OnUpdateRenumber)
	ON_UPDATE_COMMAND_UI(IDC_REORDER, OnUpdateReorder)
	ON_COMMAND(IDC_WT_HELP, OnHelp)
	ON_COMMAND(IDC_ABOUT, OnAbout)
	ON_MESSAGE_VOID(WM_IDLEUPDATECMDUI, OnIdleUpdateCmdUI)
	ON_COMMAND(IDC_SAVE, OnSave)
	ON_COMMAND(IDC_SAVEALL, OnSaveall)
	ON_COMMAND(IDC_SELECT, OnSelect)
	ON_COMMAND(IDC_SETCURRDIR, OnSetcurrdir)
	ON_COMMAND(IDC_ROATTR, OnRoattr)
	ON_COMMAND(IDC_PROPERTIES, OnProperties)
	ON_COMMAND(IDC_OPENASTEXT, OnOpenastext)
	ON_COMMAND(IDC_MINIMIZE_ALL, OnMinimizeAll)
	ON_COMMAND(IDC_HEADERFLIP, OnHeaderflip)
	ON_COMMAND(IDC_COPYPATH, OnCopypath)
	ON_COMMAND(IDC_COPYFILENAME, OnCopyfilename)
	ON_COMMAND(IDC_COPYFILENAME_NOPATH, OnCopyfilenameNoPath)
	ON_COMMAND(IDC_COPYDOC, OnCopydoc)
	ON_COMMAND(IDC_CLOSEGROUP, OnClosegroup)
	ON_COMMAND(IDC_CLOSEALLEXCEPT, OnCloseallexcept)
	ON_COMMAND(IDC_CLOSEALL, OnCloseall)
	ON_COMMAND(IDC_CLOSE, OnCmdClose)
	ON_UPDATE_COMMAND_UI(IDC_OPENASTEXT, OnUpdateOpenastext)
	ON_UPDATE_COMMAND_UI(IDC_HEADERFLIP, OnUpdateHeaderflip)
	ON_UPDATE_COMMAND_UI(IDC_SAVEGROUP, OnUpdateCmdMustHaveFileAndDoc)
	ON_UPDATE_COMMAND_UI(IDC_CLOSE, OnUpdateCmdMustHaveOpenWindows)
	ON_UPDATE_COMMAND_UI(IDC_ROATTR, OnUpdateCmdMustHaveFile)
	ON_UPDATE_COMMAND_UI(IDC_SAVE, OnUpdateCmdMustHaveDoc)
	ON_UPDATE_COMMAND_UI(IDC_COPYDOC, OnUpdateCmdMustHaveTextDoc)
	ON_COMMAND(IDC_SAVEGROUP, OnSaveGroup)
	ON_WM_ERASEBKGND()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_COMMAND(IDC_OPENFOLDER, OnOpenfolder)
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDC_GROUP_NEXT, OnGroupNext)
	ON_COMMAND(IDC_GROUP_PREV, OnGroupPrev)
	ON_UPDATE_COMMAND_UI(IDC_GROUP_NEXT, OnUpdateCmdGroupPrevNext)
	ON_COMMAND(IDC_SMARTHELP, OnSmarthelp)
	ON_UPDATE_COMMAND_UI(IDC_SMARTHELP, OnUpdateSmarthelp)
	ON_UPDATE_COMMAND_UI(IDC_CLOSEALL, OnUpdateCmdMustHaveOpenWindows)
	ON_UPDATE_COMMAND_UI(IDC_CLOSEALLEXCEPT, OnUpdateCmdMustHaveOpenWindows)
	ON_UPDATE_COMMAND_UI(IDC_PROPERTIES, OnUpdateCmdMustHaveOpenWindows)
	ON_UPDATE_COMMAND_UI(IDC_CLOSEGROUP, OnUpdateCmdMustHaveOpenWindows)
	ON_UPDATE_COMMAND_UI(IDC_COPYFILENAME, OnUpdateCmdMustHaveFile)
	ON_UPDATE_COMMAND_UI(IDC_COPYFILENAME_NOPATH, OnUpdateCmdMustHaveFile)
	ON_UPDATE_COMMAND_UI(IDC_COPYPATH, OnUpdateCmdMustHaveFile)
	ON_UPDATE_COMMAND_UI(IDC_MINIMIZE_ALL, OnUpdateCmdMustHaveOpenWindows)
	ON_UPDATE_COMMAND_UI(IDC_SAVEALL, OnUpdateCmdMustHaveOpenWindows)
	ON_UPDATE_COMMAND_UI(IDC_SELECT, OnUpdateCmdMustHaveOpenWindows)
	ON_UPDATE_COMMAND_UI(IDC_SETCURRDIR, OnUpdateCmdMustHaveFile)
	ON_UPDATE_COMMAND_UI(IDC_OPENFOLDER, OnUpdateCmdMustHaveFile)
	ON_UPDATE_COMMAND_UI(IDC_GROUP_PREV, OnUpdateCmdGroupPrevNext)
	ON_COMMAND(IDC_TAB_NEXT, OnTabNext)
	ON_COMMAND(IDC_TAB_PREV, OnTabPrev)
	ON_UPDATE_COMMAND_UI(IDC_TAB_NEXT, OnUpdateCmdMustHaveOpenWindows)
	ON_UPDATE_COMMAND_UI(IDC_TAB_PREV, OnUpdateCmdMustHaveOpenWindows)
	//}}AFX_MSG_MAP
    ON_COMMAND_RANGE(IDC_GOTOTAB1, IDC_GOTOTAB9, OnGoToTab)
    ON_COMMAND_RANGE(iAddOnCmdsStart, iAddOnCmdsEnd, OnAddOnCmd)
	ON_UPDATE_COMMAND_UI_RANGE(iAddOnCmdsStart, iAddOnCmdsEnd, OnUpdateAddOnCmd)
	ON_REGISTERED_MESSAGE(BCGM_RESETMENU, OnMenubarReset)
	ON_REGISTERED_MESSAGE(BCGM_TOOLBARMENU, OnToolbarContextMenu)
	ON_REGISTERED_MESSAGE(BCGM_CUSTOMIZEHELP, OnCustomizeHelp)
	ON_REGISTERED_MESSAGE(BCGM_SELECTMENUITEM, OnSelectMenuItem)
    ON_COMMAND_RANGE(IDM_SHELLCTXFIRST, IDM_SHELLCTXLAST, OnShellContextCmd)
    ON_MESSAGE(WM_SETMESSAGESTRING, OnSetMessageString)
    ON_MESSAGE(WM_DDE_EXECUTE, OnDDEExecute)
    ON_MESSAGE(WM_APPCOMMAND, OnAppCommand)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

LRESULT CMainFrame::OnSetMessageString (WPARAM wParam, LPARAM lParam)
{
    if (g_pDevStudioWnd)
    {
        CString cStr;

        // load from resource?
        if (wParam)
        {
            // we must do the resource load ourselves, otherwise DevStudio
            // will attempt to load the corresponding resource ID from it's
            // own resources

            ASSERT(lParam == 0);  // can't have wParam!=0 && lParam!=0

			// is this a Shell item?
			if (wParam >= IDM_SHELLCTXFIRST || wParam <= IDM_SHELLCTXLAST)
			{
				// get shell item description
				m_pSCM->GetCommandDescription((UINT)wParam, cStr);
			}
			else
			{
				CString sFullText;
				sFullText.LoadString(wParam);

				// get command id part from resource
    			AfxExtractSubString(cStr, sFullText, 1, '\n');
			}

            // re-adjust parameters
            lParam = (LPARAM)(LPCSTR)cStr;
            wParam = 0;
        }
        g_pDevStudioWnd->SendMessage(WM_SETMESSAGESTRING, wParam, lParam);
        return TRUE;
    }

    return CBCGFrameWnd::OnSetMessageString(wParam, lParam);
}


void CMainFrame::OnOptions() 
{
    WT_MANAGE_STATE();
    COptionsSheet dlg;
//    if (theApp.Focus())
    {
        dlg.DoModal();
    }

//    theApp.UnFocus();
}

void CMainFrame::OnCustomize() 
{
    DoCustomize(this);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    WT_FN_TRACE("CMainFrame::OnCreate");

    g_pMainFrame = this;

    if (CBCGFrameWnd::OnCreate(lpCreateStruct) == -1)
		RETURN_INT(-1);
    
    CBCGPopupMenu::SetForceShadow(TRUE);

/*    m_AddOnImages.Load(IDB_2CLIPBOARD);
    if (CBCGToolBar::GetUserImages())
    {
    	m_AddOnImages.SetImageSize(CSize(16, 16));
    }
    CBCGToolBar::SetUserImages(&g_pMainFrame->m_AddOnImages);
*/
    if (!m_wndMenuBar.Create (this)) //, dwDefaultToolbarStyle & ~WS_VISIBLE))
	{
		WT_L1_TRACE("Failed to create menubar\n");
		RETURN_INT(-1);
	}
	m_wndMenuBar.SetBarStyle((m_wndMenuBar.GetBarStyle() 
        | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY) & ~CBRS_BORDER_ANY);
    m_wndMenuBar.SetForceDownArrows(cfg_bMenuArrows);

    m_wndMenuBar.CalculateCustomizeButton();
    m_wndMenuBar.SetWindowText("WndTabs Dockbar");

	if (!m_wndAddOnToolbar.Create(this, 
        WS_CHILD | CBRS_BOTTOM | CBRS_HIDE_INPLACE, uiUserBarId))
	{
		WT_L1_TRACE("Failed to create user toolbar\n");
		RETURN_INT(-1);
	}

    m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
    m_wndAddOnToolbar.EnableDocking(CBRS_ALIGN_BOTTOM);
	EnableDocking(CBRS_ALIGN_ANY);

	DockControlBar(&m_wndMenuBar);
	DockControlBar(&m_wndAddOnToolbar);
    m_wndMenuBar.ShowWindow(SW_SHOW);
    m_wndAddOnToolbar.ShowWindow(SW_HIDE);

    CBCGToolBar::EnableQuickCustomization ();

	// Create vertical font:
	//----------------------
	CFont font;
	if (font.CreateStockObject (DEFAULT_GUI_FONT))
	{
		LOGFONT lf;
		memset (&lf, 0, sizeof (LOGFONT));

		if (font.GetLogFont (&lf) != 0)
		{
			lf.lfOrientation = 900;
			lf.lfEscapement = 900;
			
			lf.lfHeight = -15;
			lf.lfWeight = 700;
			lf.lfItalic = TRUE;
			_tcscpy (lf.lfFaceName, _T("Arial"));

			m_fontVertCaption.CreateFontIndirect (&lf);
		}
	}

    ResetBCGHooks();

    EnableToolTips();

    RETURN_INT(0);
}

void CMainFrame::OnRenumber() 
{
	pGlobalTabs->m_pCommands->WTRenumber();
}

void CMainFrame::OnReorder() 
{
	pGlobalTabs->m_pCommands->WTReorder();
}

void CMainFrame::OnUpdateRenumber(CCmdUI* pCmdUI) 
{
    int items = pGlobalTabs->m_pTabCtrl? 
        pGlobalTabs->m_pTabCtrl->GetItemCount() : 0;
    pCmdUI->Enable(cfg_TabOrdering != toMDI  &&  
        cfg_bPreserveNumbering  &&  items);
}

void CMainFrame::OnUpdateReorder(CCmdUI* pCmdUI) 
{
    int items = pGlobalTabs->m_pTabCtrl? 
        pGlobalTabs->m_pTabCtrl->GetItemCount() : 0;
    pCmdUI->Enable(cfg_TabOrdering == toControlled  &&  items);
}

void CMainFrame::OnHelp() 
{
    pGlobalTabs->m_pCommands->WTHelp();
}

void CMainFrame::OnAbout() 
{
    if (theApp.Focus())
    {
    	pGlobalTabs->m_pCommands->WTAbout();
    }
    theApp.UnFocus();
}

void CMainFrame::OnIdleUpdateCmdUI()
{
    CBCGFrameWnd::OnIdleUpdateCmdUI();

    SendMessageToDescendants(WM_IDLEUPDATECMDUI, TRUE, 0, TRUE, TRUE);
}


void CMainFrame::OnSave() 
{
	if (m_pCmdCtx->bIsGroupOperation)
    {
        OnSaveGroup();
    }
    else
    {
        DsSaveStatus iSaved;
        CComVariant  varPrompt = true, v = _T("");

        m_pCmdCtx->pDoc->Save(v, varPrompt, &iSaved);
    }
}


void CMainFrame::OnUpdateCmdMustHaveFileAndDoc(CCmdUI* pCmdUI) 
{
    ASSERT(m_pCmdCtx);
    pCmdUI->Enable(m_pCmdCtx->bHasDoc  &&  m_pCmdCtx->bHasFile);
}

void CMainFrame::OnUpdateCmdMustHaveDoc(CCmdUI* pCmdUI) 
{
    ASSERT(m_pCmdCtx);
    pCmdUI->Enable(m_pCmdCtx->bHasDoc);
}

void CMainFrame::OnSaveall() 
{
    CComBSTR bStr = _T("FileSaveAll");
    pGlobalTabs->m_pApplication->ExecuteCommand(bStr);
}

void CMainFrame::OnSelect() 
{
    pGlobalTabs->ActivateWindow(m_pCmdCtx->hWnd);
}

void CMainFrame::OnSetcurrdir() 
{
    pGlobalTabs->m_pCommands->DoSetCurrDir(
        CString(m_pCmdCtx->szFullPath));
}

void CMainFrame::OnRoattr() 
{
    DWORD attr = GetFileAttributes(m_pCmdCtx->szFullPath);
    SetFileAttributes(m_pCmdCtx->szFullPath, 
        attr ^ FILE_ATTRIBUTE_READONLY);
    pGlobalMDIManager->PostUpdateMessage();  // force update
}

void CMainFrame::OnProperties() 
{
    if (!m_pCmdCtx->bIsActiveWindow)
    {
        // this will force the window to the foreground
        m_pCmdCtx->pWindow->put_Active(VARIANT_FALSE);
    }
    m_pCmdCtx->pWindow->put_Active(VARIANT_TRUE);

    CComBSTR bStr = _T("Properties");
    pGlobalTabs->m_pApplication->ExecuteCommand(bStr);
}

void CMainFrame::OnOpenastext() 
{
    pGlobalTabs->m_pCommands->DoOpenAsText(m_pCmdCtx->szFullPath);
}

void CMainFrame::OnUpdateOpenastext(CCmdUI* pCmdUI) 
{
    ASSERT(m_pCmdCtx);
    pCmdUI->Enable(m_pCmdCtx->bHasDoc   &&  
                   m_pCmdCtx->bHasFile  &&
                   !m_pCmdCtx->bIsTextWindow);
}

void CMainFrame::OnUpdateCmdMustHaveTextDoc(CCmdUI* pCmdUI) 
{
    ASSERT(m_pCmdCtx);
    pCmdUI->Enable(m_pCmdCtx->bHasDoc  &&  m_pCmdCtx->bIsTextWindow);
}

void CMainFrame::OnMinimizeAll() 
{
    CWaitCursor wc;

    // "minimize all" code contributed by Mark Cooke 
    // [mark.cooke@oxinst.co.uk]
    HWND hWnd = ::GetTopWindow( pGlobalMDIManager->m_hWnd ), hWndNext;
   
    while( hWnd )
    {
        hWndNext = ::GetNextWindow( hWnd, GW_HWNDNEXT );
        ::ShowWindow( hWnd, SW_MINIMIZE );
        hWnd = hWndNext;
    }
}

void CMainFrame::OnHeaderflip() 
{
    pGlobalTabs->m_pCommands->DoHeaderFlip(
        CString(m_pCmdCtx->szFullPath), cfg_bUseWorkspaceUtils);
}

void CMainFrame::OnCopypath() 
{
    CString cFullPath(m_pCmdCtx->szFullPath);

    // remove file name
    cFullPath = cFullPath.Left(cFullPath.ReverseFind('\\'));
    CopyStringToClipboard(cFullPath);
}

void CMainFrame::OnCopyfilename() 
{
    CopyStringToClipboard(m_pCmdCtx->szFullPath);
}

void CMainFrame::OnCopyfilenameNoPath() 
{
    CString cStr(m_pCmdCtx->szFullPath);

    // remove file name
    cStr = cStr.Mid(cStr.ReverseFind('\\') + 1);
    CopyStringToClipboard(cStr);
}

void CMainFrame::OnCopydoc() 
{
    bool        bIsVAWin = false;
    int         iResult;
    HADDIN      hAddIn;
    CString     cStr;
    CComBSTR    bStr;
    CComQIPtr<ITextWindow, &IID_ITextWindow> pTextWin;
    CComQIPtr<ITextSelection, &IID_ITextSelection> pSel;
    CComPtr<IDispatch> pDisp;

    pTextWin = m_pCmdCtx->pWindow;
    pTextWin->get_Selection(&pDisp);
    pSel = pDisp;
	pDisp = NULL;

    long row, col, col2;
    pSel->get_CurrentColumn(&col);
    pSel->get_CurrentLine(&row);

    hAddIn = cfg_bUseVA_RTF? AICGetAddIn("VisualAssist") : NULL;

    if (hAddIn)
    {
        // Visual Assist RTF Copy command (ver 3.0.0 Build 1093+)
        cStr.Format("RTFFileCopy %x", m_pCmdCtx->hWnd);

        iResult = AICSendCommand(hAddIn, cStr);
        // -2 -> not a Vistual Assist window
        // -1 -> command not supported (old Visual Assist)
        //  0 -> RTF copy was not successful
        //  1 -> RTF copy was successful

        if (iResult == 0  ||  iResult < -1)
        {
            // indicate to the block below that this isn't a Visual Assist 
            // Window
            hAddIn = NULL; 
        }
        else
        {
            if (iResult == -1 /* old VA */  &&  
                m_pCmdCtx->bIsActiveWindow) 
            {
                // special care for old Visual Assist versions to those of 
                // you who don't like the free upgrades...

                // go to end or VA won't select all
                bStr = "DocumentEnd";
                pGlobalTabs->m_pApplication->ExecuteCommand(bStr);

                pSel->SelectAll();

                // regular copy in case VA copy fails
                pSel->Copy();  

                bStr = "VisualAssistCopyRTFToClipboard";
                pGlobalTabs->m_pApplication->ExecuteCommand(bStr);

                // ITextSelection->MoveTo won't work with VA, so "walk" to 
                // the destination manually
                bStr = "DocumentStart";
                pGlobalTabs->m_pApplication->ExecuteCommand(bStr);
                bStr = "LineDown";
                while (--row) 
                    pGlobalTabs->m_pApplication->ExecuteCommand(bStr);
                bStr = "CharRight";
                col2 = 1;
                while (col2 < col)
                {
                    pGlobalTabs->m_pApplication->ExecuteCommand(bStr);
                    pSel->get_CurrentColumn(&col2);
                }
            }
        }
    }

    // hAddIn == NULL if:
    // 1. cfg_bUseVA_RTF == FALSE
    // 2. Visual Assist wasn't found by AICGetAddIn()
    // 3. This isn't a Visual Assist window
    if (hAddIn == NULL)
    {
        pSel->SelectAll();
        pSel->Copy();
        pSel->MoveTo(row, col, CComVariant(false));
    }
}

void CMainFrame::OnClosegroup() 
{
    DoCloseGroup();
}


void DoCloseWndAction(HWND hWnd)
{
    ::PostMessage(hWnd, WM_CLOSE, 0, 0);
}

void CMainFrame::DoCloseGroup(bool bInverse /*= false*/)
{
    CWaitCursor wc;
    if (m_pCmdCtx == NULL) return;
    pGlobalTabs->DoForGroup(DoCloseWndAction, 
        m_pCmdCtx->iTab, bInverse);
}

void CMainFrame::DoCloseAll(HWND hWndExcept /*= NULL*/)
{
    // BUG BUG: When executed through IApplication->ExecutreCommand, the 
    //  WindowCloseAll, FileSaveAll and FileSave commands work properly only 
    //  when there is no new unsaved document opened (create a new text file
    //  to see this).  For this reason, this implementation doesn't use
    //  ExecuteCommand("WindowCloseAll") 

    CWaitCursor wc;

    if (hWndExcept)
    {
        pGlobalMDIManager->PostMessage(WM_MDIACTIVATE, (WPARAM)hWndExcept);
    }

    HWND hWnd = ::GetTopWindow(pGlobalMDIManager->m_hWnd), hWndNext;

    while (hWnd)
    {
        hWndNext = ::GetNextWindow(hWnd, GW_HWNDNEXT);
        if (hWnd != hWndExcept)
            ::PostMessage(hWnd, WM_CLOSE, 0, 0);
        hWnd = hWndNext;
    }
}

void CMainFrame::OnCloseallexcept() 
{
    if (m_pCmdCtx->bIsGroupOperation)
    {
        DoCloseGroup(true);
    }
    else
    {
        DoCloseAll(m_pCmdCtx->hWnd);
    }
}

void CMainFrame::OnCloseall() 
{
    DoCloseAll();
}

void CMainFrame::OnCmdClose() 
{
    if (m_pCmdCtx->bIsGroupOperation)
    {
        OnClosegroup();
    }
    else
    {
        // BUG BUG: Embedded windows (e.g. Word/Excel documents) can't handle 
        // a COM Close command.  We'll use a direct Windows "close window" 
        // message.
        ::PostMessage(m_pCmdCtx->hWnd, WM_CLOSE, 0, 0);
    }
}


void CMainFrame::OnUpdateHeaderflip(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(pGlobalTabs->m_pCommands->DoHeaderFlip(
        CString(m_pCmdCtx->szFullPath), cfg_bUseWorkspaceUtils, TRUE));
}


void CMainFrame::OnUpdateCmdMustHaveOpenWindows(CCmdUI* pCmdUI) 
{
    ASSERT(::IsWindow(pGlobalMDIManager->GetSafeHwnd()));
    pCmdUI->Enable(pGlobalTabs->m_pTabCtrl->GetItemCount() > 0);
}


void CMainFrame::OnUpdateCmdMustHaveFile(CCmdUI* pCmdUI) 
{
    ASSERT(m_pCmdCtx);
    pCmdUI->Enable(m_pCmdCtx->bHasFile);
}

void DoSaveWndAction(HWND hWnd)
{
    CComPtr<IGenericWindow> pWindow;
    if (pGlobalTabs->FindDSWindow(hWnd, &pWindow))
    {
        CComPtr<IGenericDocument> pDoc;
        if (pGlobalTabs->GetDocumentObject(pWindow.p, pDoc))
        {
            CComVariant  varPrompt = true, v = _T("");
            DsSaveStatus iSaved;
            pDoc->Save(v, varPrompt, &iSaved);
        }
    }
}

void CMainFrame::OnSaveGroup() 
{
    pGlobalTabs->DoForGroup(DoSaveWndAction, m_pCmdCtx->iTab);
}

void CMainFrame::CopyStringToClipboard(LPCTSTR str)
{
    // copy to clipboard using an edit control
    CEdit cEdit;
    if (!cEdit.Create(0, CRect(0, 0, 1, 1), this, 0))
    {
        ASSERT(0);
        return;
    }
    cEdit.SetWindowText(str);
    cEdit.SetSel(0, -1);
    cEdit.Copy();
}

void CMainFrame::OnClosePopupMenu (CBCGPopupMenu* pPopupMenu)
{
	CBCGToolbarButton* pButton = pPopupMenu->GetMenuItem(0);

	if (pButton && pButton->m_nID == IDM_SHELLCTXFIRST)
	{
		delete(m_pSCM);
		m_pSCM = NULL;
		m_scm.DestroyMenu();
	}

	CBCGFrameWnd::OnClosePopupMenu(pPopupMenu);
}

BOOL CMainFrame::OnShowPopupMenu (CBCGPopupMenu* pPopupMenu)
{
    BOOL bRetVal = CBCGFrameWnd::OnShowPopupMenu (pPopupMenu);

	if (pPopupMenu == NULL)
	{
        return TRUE;
    }

	CBCGPopupMenuBar* pMenuBar = pPopupMenu->GetMenuBar ();
	ASSERT_VALID (pMenuBar);

    for (int i = 0; i < pMenuBar->GetCount (); i ++)
	{
		CBCGToolbarButton* pButton = pMenuBar->GetButton (i);
		ASSERT_VALID (pButton);

		if (pButton->m_nID == ID_SHELLCONTEXT)
		{
        	if (CBCGToolBar::IsCustomizeMode ())
        	{
        		return FALSE;
        	}

            ASSERT(m_pCmdCtx != NULL);
            delete(m_pSCM);

            m_pSCM = new CShellContextMenu(g_pDevStudioWnd->m_hWnd,
                CString(m_pCmdCtx->szFullPath));

			m_scm.DestroyMenu();
			m_scm.CreatePopupMenu();
			// TODO: localize string
            m_scm.AppendMenu(MF_STRING, ID_UNAVAILABLE, "Unavailable");

            m_pSCM->SetMenu(&m_scm);
            
			pMenuBar->ImportFromMenu (m_scm, TRUE);
//			pPopupMenu->SetMaxWidth (300);

			return TRUE;
		}

        if (pButton->m_nID == ID_ADDONS)
        {
        	if (CBCGToolBar::IsCustomizeMode ())
        	{
        		return FALSE;
            }

            CMenu menu, submenu;
            menu.CreatePopupMenu();
            POSITION p = g_PermanentAddons.GetStartPosition();
            PermanentAddonInfo info;
            CString sName;
            while (p)
            {
                g_PermanentAddons.GetNextAssoc(p, sName, info);
                if (info.bIsValid)
                {
                    if (cfg_bCascadingAddons)
                    {
                        submenu.CreatePopupMenu();
                    }
                    else
                    {
                        if (menu.GetMenuItemCount() != 0)
                        {
                            menu.AppendMenu(MF_SEPARATOR);
                        }
                    }
                    CMenu * const pWorkMenu = 
                        (cfg_bCascadingAddons) ? &submenu : &menu;
                    for (int i = 0; i < info.Commands.GetSize(); i++)
                    {
                        ImportedCommand& cmd = info.Commands[i];
                        if (cmd.iAddOnCmdNum < 0)
                        {
                            pWorkMenu->AppendMenu(MF_SEPARATOR);
                        }
                        else
                        {
                            pWorkMenu->AppendMenu(MF_STRING, 
                                cmd.uiAssignedCmdID, cmd.sName);
                        }
                    }
                    if (cfg_bCascadingAddons)
                    {
                        if( 0 == i )
                        {
							CString cStr;
							cStr.LoadString(IDS_ADDONS_NONE);
                            submenu.AppendMenu(MF_STRING, 1, cStr);
                        }
                        if ( i != 0  ||  !cfg_bSupressNoCmdAddons )
                        {
                            menu.AppendMenu(MF_POPUP, (UINT)submenu.m_hMenu, 
                                sName);
                            submenu.Detach();
                        }
                        else
                        {
                            submenu.DestroyMenu();
                        }
                    }
                }
            }
            if (menu.GetMenuItemCount() == 0)
            {
				CString cStr;
				cStr.LoadString(IDS_ADDONS_NONE);
                menu.AppendMenu(MF_STRING, 1, cStr);
            }
			pMenuBar->ImportFromMenu(menu, TRUE);
            return TRUE;
        }

        if (pButton->m_nID == IDC_ROATTR)
        {
        	if (CBCGToolBar::IsCustomizeMode()  ||  !m_pCmdCtx->bHasFile)
        	{
                pButton->m_strText.LoadString(IDS_RO_TOGGLE);
            }
            else
            {
                if (GetFileAttributes(m_pCmdCtx->szFullPath) & 
                    FILE_ATTRIBUTE_READONLY)
                {
                    pButton->m_strText.LoadString(IDS_RO_MAKE_RW);
                }
                else
                {
                    pButton->m_strText.LoadString(IDS_RO_MAKE_RO);
                }
            }
        }
    }

	int iIndex = -1;
	if (m_wndMenuBar.GetDroppedDownMenu (&iIndex) == 
		pPopupMenu->GetParentButton () &&
		iIndex == 0)
	{
		pPopupMenu->EnableMenuLogo(26);
	}

	return TRUE;
}

void CMainFrame::OnDrawMenuLogo (CDC* pDC, CBCGPopupMenu* pMenu, const CRect& rectLogo)
{
    ASSERT_VALID (pDC);
    
    //------------------------------------------------------
    // Fill menu side logo by gradient color:
    // (this code was copied from BCGSizingControlBar.cpp
    // Copyright (C) 1998, 1999 by Cristi Posea)
    //------------------------------------------------------
    
    // this will make 2^6 = 64 fountain steps
    int nShift = 6;
    int nSteps = 1 << nShift;
    
    COLORREF clrCptn = RGB (0, 128, 128);
    COLORREF clrCptnRight = RGB (0, 0, 128);
    
    for (int i = 0; i < nSteps; i++)
    {
        // do a little alpha blending
        BYTE bR = (BYTE) ((GetRValue(clrCptn) * (nSteps - i) +
            GetRValue(clrCptnRight) * i) >> nShift);
        BYTE bG = (BYTE) ((GetGValue(clrCptn) * (nSteps - i) +
            GetGValue(clrCptnRight) * i) >> nShift);
        BYTE bB = (BYTE) ((GetBValue(clrCptn) * (nSteps - i) +
            GetBValue(clrCptnRight) * i) >> nShift);
        
        CBrush br (RGB(bR, bG, bB));
        
        // then paint with the resulting color
        CRect r2 = rectLogo;
        
        r2.bottom = rectLogo.bottom - 
            ((i * rectLogo.Height()) >> nShift);
        r2.top = rectLogo.bottom - 
            (((i + 1) * rectLogo.Height()) >> nShift);
        if (r2.Height() > 0)
            pDC->FillRect(r2, &br);
    }
    
    pDC->Draw3dRect (rectLogo, ::GetSysColor (COLOR_3DLIGHT), ::GetSysColor (COLOR_3DSHADOW));
    
    int nOldBkMode = pDC->SetBkMode(TRANSPARENT);
    COLORREF clrOldText = pDC->SetTextColor (RGB (255, 255, 255));
    
    CFont* pOldFont = pDC->SelectObject (&m_fontVertCaption);
    CString sTitle = _T("WndTabs");
    if (g_bUseWndTabsExt)
    {
        sTitle += " Extended";
    }
    
    CPoint ptOrg = CPoint(rectLogo.left + 5, rectLogo.bottom - 10);
    
    pDC->ExtTextOut (ptOrg.x, ptOrg.y,
        ETO_CLIPPED, rectLogo, sTitle, NULL);
    
    pDC->SelectObject(pOldFont);
    pDC->SetBkMode(nOldBkMode);
    pDC->SetTextColor(clrOldText);
    
/*    //-----------
    // Draw logo:
    //-----------
    pDC->DrawState (CPoint (rectLogo.left + 4, rectLogo.top + 10),
        CSize (23, 23), &m_bmpLogo, 0);
*/}


BOOL CMainFrame::OnDrawMenuImage (CDC* pDC,
    const CBCGToolbarMenuButton* pMenuButton,
	const CRect& rectImage)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (pMenuButton);

    const int pt_x = rectImage.left + (rectImage.Width  () - 16) / 2;
    const int pt_y = rectImage.top  + (rectImage.Height () - 16) / 2;

    if (m_pSCM)
    {
		CMenu* pMenu;
		int item;
		if (!GetShellMenuItem(pMenuButton, pMenu, item))
			return FALSE;

        CImageList *pil;
        int         index;
        if (m_pSCM->GetCommandImage(pMenu, item, pil, index))
        {
            pil->Draw(pDC, index, CPoint(pt_x, pt_y), ILD_TRANSPARENT);
            return TRUE;
        }
    }

	return FALSE;
}

LRESULT CMainFrame::OnSelectMenuItem(WPARAM wParam, LPARAM lParam)
{
	// wParam = item index
	// lParam = item id

	// is this a Shell item?
	if (lParam >= IDM_SHELLCTXFIRST || lParam <= IDM_SHELLCTXLAST)
	{
		if (!::IsMenu(m_scm.GetSafeHmenu()))
			return 0;

		const int count = m_scm.GetMenuItemCount();
		for (int i=0; i<count; i++)
		{
            CMenu* pSubMenu = m_scm.GetSubMenu(i);
			// look for the SendTo submenu
            if (pSubMenu && pSubMenu->GetMenuItemID(wParam) == (UINT)lParam)
            {
				// Shell knows which item to execute
				// by storing the last selected item
				m_pSCM->SelectItem(pSubMenu, wParam);
				break;
			}
		}
	}

	return 0;
}

void CMainFrame::OnShellContextCmd(UINT nID)
{
    ASSERT(m_pSCM != NULL);
    ASSERT(m_pSCM->IsMenuCommand(nID));

    m_pSCM->InvokeCommand(nID);
}

CMenu* CMainFrame::FindExactMenuItem(CMenu *pMenu, int idx, UINT nID, CString text)
{
	const int count = pMenu->GetMenuItemCount();
	for (int i=0; i<count; i++)
	{
		if (i == idx && pMenu->GetMenuItemID(i) == nID)
		{
			CString str;
			pMenu->GetMenuString(i, str, MF_BYPOSITION);
			if (str == text)
				return pMenu;
		}
		// try if it's a popup menu
		CMenu* pSubMenu = pMenu->GetSubMenu(i);
		if (pSubMenu != NULL)
		{
			pSubMenu = FindExactMenuItem(pSubMenu, idx, nID, text);
			if (pSubMenu != NULL)
				return pSubMenu;
			// else go on!
		}
	}
	return NULL;
}

BOOL CMainFrame::GetShellMenuItem(const CBCGToolbarMenuButton* pMenuButton,
								  CMenu*& pMenu, int& item)
{
	if (pMenuButton == NULL)
		return FALSE;

	ASSERT_VALID (pMenuButton);
	CBCGPopupMenuBar* pMenuBar = DYNAMIC_DOWNCAST(CBCGPopupMenuBar, pMenuButton->GetParentWnd());
	ASSERT_VALID (pMenuBar);

	item = pMenuBar->ButtonToIndex(pMenuButton);
	pMenu = FindExactMenuItem(&m_scm, item, pMenuButton->m_nID, pMenuButton->m_strText);

	return (pMenu != NULL);
}


BOOL CMainFrame::OnEraseBkgnd(CDC* pDC) 
{
    if (m_wndMenuBar.IsFloating())
    {
        CRect r;
        GetClientRect(r);
        pDC->FillSolidRect(r, ::GetSysColor(COLOR_BTNFACE));
    }
    return TRUE;

//	return CBCGFrameWnd::OnEraseBkgnd(pDC);
}


void CMainFrame::OnClose() 
{
    WT_MANAGE_STATE();
    if (GetParent() == NULL  &&  m_bCanClose)
    {
    	CBCGFrameWnd::OnClose();
    }
}

void CMainFrame::OnGoToTab(UINT nID)
{
    if (pGlobalTabs)
    {
        pGlobalTabs->ActivateTab(nID - IDC_GOTOTAB1 + 1);                  
    }
}

void CMainFrame::OnAddOnCmd(UINT nID)
{
    WT_MANAGE_STATE();
    ExecuteImportedCommand(nID);
}

void CMainFrame::OnUpdateAddOnCmd(CCmdUI* pCmdUI)
{
    const int nID = pCmdUI->m_nID;
    const ImportedCommand * const pICmd = GetImportedCommand(nID);

    if (!pICmd) return;

    ExecuteUIUpdate(nID, pCmdUI);
}


LRESULT CMainFrame::OnMenubarReset(WPARAM, LPARAM)
{
//	UINT uiToolBarId = (UINT) wp;

    m_wndMenuBar.EnableCustomizeButton(TRUE, IDC_CUSTOMIZE, IDS_CUSTOMIZE);

    CBCGToolbarButton *pButton = m_wndMenuBar.GetButton(0);

    pButton->SetImage(0);
    pButton->m_bText = FALSE;
	pButton->m_bImage = TRUE;

    return 1;   
}

void CMainFrame::OnDestroy() 
{
    g_pMainFrame = NULL;
    StopBCGHooks();

    delete m_pCmdCtx;
    delete m_pSCM;
    m_pCmdCtx = NULL;
    m_pSCM    = NULL;

    CBCGFrameWnd::OnDestroy();
}

void CMainFrame::OnOpenfolder() 
{
    WT_ASSERT(m_pCmdCtx);
    WT_ASSERT(m_pCmdCtx->szFullPath[0]);

    CWaitCursor wc;

    CString sFolder = m_pCmdCtx->szFullPath;
    const int nPos = sFolder.ReverseFind('\\');
    if (nPos >= 0)
    {
        ShellExecute(g_pDevStudioWnd->m_hWnd, 
            cfg_bOpenFolderUseExplore? "explore" : "open", 
            sFolder.Left(nPos), 
            NULL, NULL, SW_SHOWNORMAL);
    }
}

LRESULT CMainFrame::OnToolbarContextMenu(WPARAM,LPARAM lp)
{
	CPoint point (LOWORD (lp), HIWORD(lp));

	CMenu menu;
	VERIFY(menu.LoadMenu (IDR_POPUP_TOOLBAR));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	CBCGPopupMenu* pPopupMenu = new CBCGPopupMenu;
	pPopupMenu->SetAutoDestroy (FALSE);
	pPopupMenu->Create (this, point.x, point.y, pPopup->GetSafeHmenu ());

	return 0;
}


void CMainFrame::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CBCGFrameWnd::OnRButtonUp(nFlags, point);
    ClientToScreen(&point);

    OnToolbarContextMenu(0, (LPARAM)MAKELONG(point.x, point.y));
}

void CMainFrame::OnGroupNext() 
{
    pGlobalTabs->m_pCommands->WTGroupNext();
}

void CMainFrame::OnUpdateCmdGroupPrevNext(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(pGlobalTabs->m_bIsWTTab  &&  
        pGlobalTabs->m_pTabCtrl->GetItemCount() != 0);
}

void CMainFrame::OnGroupPrev() 
{
    pGlobalTabs->m_pCommands->WTGroupPrev();
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	return CBCGFrameWnd::PreTranslateMessage(pMsg);
}

LRESULT CMainFrame::OnDDEExecute(WPARAM wParam, LPARAM lParam)
{
    WT_FN_TRACE_PARAMS("OnDDEExecute", "%d, %d", wParam);
	return 0L;
}

LRESULT CMainFrame::OnCustomizeHelp(WPARAM wParam, LPARAM lParam)
{
    static int help_pages[] = 
    { 
        IDH_CUSTOMIZE_COMMANDS, IDH_CUSTOMIZE_KEYBOARD, 
        IDH_CUSTOMIZE_OPTIONS
    };

    if (wParam >= 0  &&  wParam <= 2)
    {
        ShowHTMLHelp(m_hWnd, help_pages[wParam]);
    }
    else
    {
        WT_ASSERT(FALSE);
    }
    return 0;
}

void CMainFrame::OnSmarthelp() 
{
    int iCmd = ImportedCommandToWndTabsCommand("SmartHelp", 1);
	if (iCmd >= 0)
    {
        ExecuteImportedCommand(iCmd);
    }
}

void CMainFrame::OnUpdateSmarthelp(CCmdUI* pCmdUI) 
{
    int iCmd = ImportedCommandToWndTabsCommand("SmartHelp", 1);
	if (iCmd >= 0)
    {
        ExecuteUIUpdate(iCmd, pCmdUI);
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}

void CycleTabs(bool bForward = true)
{
    CTabCtrl& tabCtrl = *pGlobalTabs->m_pTabCtrl;

    int iTab = tabCtrl.GetCurSel(), iNextTab = -1;
    const int cTabs = tabCtrl.GetItemCount();

    if (cTabs == 0)
    {
        MessageBeep(-1);
        return;
    }

    HWND hWnd = NULL;
    int *pInfo = NULL;
    int iGroupID = -1;
    
    int iDelta = bForward? 1 : -1;
    if (pGlobalTabs->m_bIsWTTab)
    {
        pInfo = new int[cTabs];
        WTTabCtrlGetGroupInfo(pGlobalTabs->m_pTabCtrl, pInfo);
        bool bGroupCycle = false;
        CArray<CArray<int, int>, CArray<int, int>&> arrGroups;
        CMap<int, int, int, int> mapGroups;
        int iGroupNdx = 0;
        int iTabNum = -1, iTabGroupNum = -1;

        for (int i = 0; i < cTabs; ++i)
        {
            int iGroupID;
            if (mapGroups.Lookup(pInfo[i], iGroupID) == FALSE)
            {
                mapGroups[pInfo[i]] = iGroupNdx;
                iGroupID = iGroupNdx;
                ++iGroupNdx;
            }
            if (arrGroups.GetSize() <= iGroupID)
            {
                arrGroups.SetSize(iGroupID + 1);
            }
            if (i == iTab)
            {
                iTabNum = arrGroups[iGroupID].GetSize();
                iTabGroupNum = iGroupID;
            }
            arrGroups[iGroupID].Add(i);
        }

        iTabNum += iDelta;
        if (iTabNum >= arrGroups[iTabGroupNum].GetSize())
        {
            iTabNum = 0;
            ++iTabGroupNum;
        }
        if (iTabNum < 0)
        {
            --iTabGroupNum;
        }
        if (iTabGroupNum >= arrGroups.GetSize())
        {
            iTabGroupNum = 0;
        }
        else if (iTabGroupNum < 0)
        {
            iTabGroupNum = arrGroups.GetSize() -1;
        }
        if (iTabNum < 0)
        {
            iTabNum = arrGroups[iTabGroupNum].GetSize() - 1;
        }
        ASSERT(iTabNum >= 0);

        iNextTab = arrGroups[iTabGroupNum][iTabNum];
        ASSERT(iNextTab >= 0);
    }
    else
    {
        iNextTab = iTab + iDelta;
        if (iNextTab < 0)
        {
            iNextTab = cTabs - 1;
        }
        else
        {
            if (iNextTab >= cTabs)
            {
                iNextTab = 0;
            }
        }
    }

    hWnd = pGlobalTabs->GetTabData(iNextTab)->hWnd;

    if (hWnd)
    {
        pGlobalMDIManager->PostMessage(WM_MDIACTIVATE, (WPARAM)hWnd, 0);
    }
}

LRESULT CMainFrame::OnAppCommand(WPARAM wParam, LPARAM lParam)
{
    int cmd = GET_APPCOMMAND_LPARAM(lParam);
    switch (cmd)
    {
        case APPCOMMAND_BROWSER_BACKWARD:
        {
            switch (cfg_iInetKbdBackForward)
            {
                case bfIgnore: // do nothing
                {
                    return FALSE;
                }

                case bfCycleGroup:
                {
                    PostMessage(WM_COMMAND, IDC_GROUP_PREV);
                    break;
                }

                case bfCtrlTabOrder:
                {
                    pGlobalMDIManager->PostMessage(WM_MDINEXT, NULL, TRUE);
                    break;
                }

                case bfTabOrder:
                {
                    CycleTabs(FALSE);
                    break;
                }

                DEFAULT_UNREACHABLE;
            }
            return TRUE;
        }

        case APPCOMMAND_BROWSER_FORWARD:
        {
            switch (cfg_iInetKbdBackForward)
            {
                case bfIgnore: // do nothing
                {
                    return FALSE;
                }

                case bfCycleGroup:
                {
                    PostMessage(WM_COMMAND, IDC_GROUP_NEXT);
                    break;
                }

                case bfCtrlTabOrder:
                {
                    pGlobalMDIManager->PostMessage(WM_MDINEXT, NULL, FALSE);
                    break;
                }

                case bfTabOrder:
                {
                    CycleTabs(TRUE);
                    break;
                }

                DEFAULT_UNREACHABLE;
            }
            return TRUE;
        }

        case APPCOMMAND_BROWSER_STOP:
        {
            if (cfg_bInetKbdStopBuilds)
            {
                g_pDevStudioWnd->PostMessage(WM_COMMAND, IDC_DEVSTUDIO_STOPBUILD);
                return TRUE;
            }
            break;
        }
    }
    return FALSE;
}

void CMainFrame::OnTabNext() 
{
    CycleTabs(true);
}

void CMainFrame::OnTabPrev() 
{
    CycleTabs(false);
}
