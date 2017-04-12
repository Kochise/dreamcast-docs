/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/

// TabActivationShortcutsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "wndtabs.h"
#include "Config.h"
#include "HHSupp.h"
#include "TabActivationShortcutsDlg.h"
#include "HKWarningDlg.h"
#include "ShortcutsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

enum DSEditor { Main = 1, Text = 2, Dialog = 4, Image = 8 };

static LPCTSTR szEdNames[] = 
{   
    NULL,
    _T("Main"), 
    _T("Text"), 
    NULL,
    _T("Dialog"), 
    NULL,
    NULL,
    NULL,
    _T("Image") 
};
const cEdNames = sizeof(szEdNames)/sizeof(LPCTSTR);


struct DSHK
{
    DSEditor    ed;
    LPCTSTR     cCommand;
    WORD        mod;
    LPCTSTR     cKey;
};

DSHK const DSHKs[] =
{
    { Text,   "ToggleViewWhitespace",               HOTKEYF_CONTROL | HOTKEYF_SHIFT, "8" },
    { Text,   "BookmarkClearAll",                   HOTKEYF_CONTROL | HOTKEYF_SHIFT, "F2" },
    { Text,   "FindPrevWord",                       HOTKEYF_CONTROL | HOTKEYF_SHIFT, "F3" },
    { Main,   "DebugRestart",                       HOTKEYF_CONTROL | HOTKEYF_SHIFT, "F5" },
    { Text,   "SelectColumn",                       HOTKEYF_CONTROL | HOTKEYF_SHIFT, "F8" },
    { Main,   "DebugRemoveAllBreakpoints",          HOTKEYF_CONTROL | HOTKEYF_SHIFT, "F9" },
    { Dialog, "LayoutCenterInDialogHorizontally",   HOTKEYF_CONTROL | HOTKEYF_SHIFT, "F9" },
    { Text,   "BookmarkPrev",                       HOTKEYF_SHIFT, "F2" },
    { Main,   "FindPrev",                           HOTKEYF_SHIFT, "F3" },
    { Main,   "GoToPrevErrorTag",                   HOTKEYF_SHIFT, "F4" },
    { Main,   "DebugStopDebugging",                 HOTKEYF_SHIFT, "F5" },
    { Main,   "WindowPrevPane",                     HOTKEYF_SHIFT, "F6" },
    { Dialog, "LayoutSizeToContent",                HOTKEYF_SHIFT, "F7" },
    { Main,   "DebugQuickWatch",                    HOTKEYF_SHIFT, "F9" },
    { Dialog, "LayoutAlignHorizontalCenter",        HOTKEYF_SHIFT, "F9" },
    { Text,   "BookmarkToggle",                     HOTKEYF_CONTROL, "F2" },
    { Text,   "FindNextWord",                       HOTKEYF_CONTROL, "F3" },
    { Main,   "BuildExecute",                       HOTKEYF_CONTROL, "F5" },
    { Main,   "BuildCompile",                       HOTKEYF_CONTROL, "F7" },
    { Text,   "SelectLine",                         HOTKEYF_CONTROL, "F8" },
    { Main,   "DebugEnableBreakpoint",              HOTKEYF_CONTROL, "F9" },
    { Dialog, "LayoutCenterInDialogVertically",     HOTKEYF_CONTROL, "F9" },
    { Main,   "InsertDialog",                       HOTKEYF_CONTROL, "1" },
    { Main,   "InsertMenu",                         HOTKEYF_CONTROL, "2" },
    { Main,   "InsertCursor",                       HOTKEYF_CONTROL, "3" },
    { Main,   "InsertIcon",                         HOTKEYF_CONTROL, "4" },
    { Main,   "InsertBitmap",                       HOTKEYF_CONTROL, "5" },
    { Main,   "InsertToolbar",                      HOTKEYF_CONTROL, "6" },
    { Main,   "InsertAcceleratorTable",             HOTKEYF_CONTROL, "7" },
    { Main,   "InsertStringTable",                  HOTKEYF_CONTROL, "8" },
    { Main,   "InsertVersionInfo",                  HOTKEYF_CONTROL, "9" },
    { Main,   "ActivateOutputWindow",               HOTKEYF_ALT, "2" },
    { Main,   "ActivateWatchWindow",                HOTKEYF_ALT, "3" },
    { Main,   "ActivateVariablesWindow",            HOTKEYF_ALT, "4" },
    { Main,   "ActivateRegistersWindow",            HOTKEYF_ALT, "5" },
    { Main,   "ActivateMemoryWindow",               HOTKEYF_ALT, "6" },
    { Main,   "ActivateCallStackWindow",            HOTKEYF_ALT, "7" },
    { Main,   "ActivateDisassemblyWindow",          HOTKEYF_ALT, "8" },
    { Main,   "Bookmarks",                          HOTKEYF_ALT, "F2" },
    { Main,   "Find",                               HOTKEYF_ALT, "F3" },
    { Main,   "WindowDockingView",                  HOTKEYF_ALT, "F6" },
    { Main,   "ProjectSettings",                    HOTKEYF_ALT, "F7" },
    { Text,   "SelectionFormat",                    HOTKEYF_ALT, "F8" },
    { Main,   "DebugBreakpoints",                   HOTKEYF_ALT, "F9" }
};
const cDSHKs = sizeof(DSHKs)/sizeof(DSHK);

/////////////////////////////////////////////////////////////////////////////
// CTabActivationShortcutsDlg dialog


CTabActivationShortcutsDlg::CTabActivationShortcutsDlg(CWnd* pParent /*=NULL*/)
	: CHHDialog(CTabActivationShortcutsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTabActivationShortcutsDlg)
	m_GotoKey = cfg_VKsGoToTab;
	m_bGotoAlt = ((cfg_ModGoToTab & HOTKEYF_ALT) != 0);
	m_bGotoControl = ((cfg_ModGoToTab & HOTKEYF_CONTROL) != 0);
	m_bGotoShift = ((cfg_ModGoToTab & HOTKEYF_SHIFT) != 0);
	//}}AFX_DATA_INIT
}


void CTabActivationShortcutsDlg::DoDataExchange(CDataExchange* pDX)
{
	CHHDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabActivationShortcutsDlg)
	DDX_Radio(pDX, IDC_1TO9, m_GotoKey);
	DDX_Check(pDX, IDC_ALT, m_bGotoAlt);
	DDX_Check(pDX, IDC_CONTROL, m_bGotoControl);
	DDX_Check(pDX, IDC_SHIFT, m_bGotoShift);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabActivationShortcutsDlg, CHHDialog)
	//{{AFX_MSG_MAP(CTabActivationShortcutsDlg)
	ON_BN_CLICKED(IDC_GENERATE_SHORTCUTS, OnGenerateShortcuts)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabActivationShortcutsDlg message handlers

BOOL CTabActivationShortcutsDlg::OnInitDialog() 
{
	CHHDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTabActivationShortcutsDlg::OnGenerateShortcuts() 
{
    bool bDoBeep = false;

    UpdateData();
    if (m_GotoKey == VKS1To9 &&
        !m_bGotoAlt  &&  !m_bGotoControl  &&  m_bGotoShift)
    {
        AfxMessageBox(IDS_SHIFT1TO9WARNING, MB_OK | MB_ICONEXCLAMATION);
        return;  // fail
    }

    WORD    mod;
    CString cCommands, cKey, cKeys, cEditors, cStr;

    mod  = (m_bGotoAlt?     HOTKEYF_ALT     : 0);
    mod += (m_bGotoControl? HOTKEYF_CONTROL : 0);
    mod += (m_bGotoShift?   HOTKEYF_SHIFT   : 0);

    cCommands.Empty();
    cKeys.Empty();
    cEditors.Empty();
    cKey.Empty();
    if (mod & HOTKEYF_CONTROL)  cKey += "Ctrl+";
    if (mod & HOTKEYF_ALT)      cKey += "Alt+";
    if (mod & HOTKEYF_SHIFT)    cKey += "Shift+";

    for (int i = 0; i < cDSHKs; i++)
    {
        if (DSHKs[i].mod == mod)
        {
            if ((m_GotoKey == VKS1To9    &&  DSHKs[i].cKey[0] != 'F')  ||
                (m_GotoKey == VKSF1ToF9  &&  DSHKs[i].cKey[0] == 'F'))
            {
                cKeys += cKey;
                cKeys += DSHKs[i].cKey;
                cKeys += '\n';

                cCommands += DSHKs[i].cCommand;
                cCommands += '\n';

                cEditors += szEdNames[DSHKs[i].ed];
                cEditors += '\n';
            }
        }
    }

    if (cCommands.GetLength() > 0)
    {
        cKey += (m_GotoKey == VKS1To9? "1..9" : "F1..F9");

        CHKWarningDlg dlg(cKey, cKeys, cCommands, cEditors);

        if (dlg.DoModal() != IDOK)
        {
            return;
        }
    }
    else
    {
        bDoBeep = true;
    }

    int iVK;
    CString sConflicts;
    for (i = 0; i < 9 ; i++)
    {
        if (m_GotoKey == VKS1To9)
        {
            iVK = '1' + i;
        }
        else
        {
            iVK = VK_F1 + i;
        }
        SetHKInAccel(IDC_GOTOTAB1 + i, iVK, mod, sConflicts);
    }
    ApplyAccelChanges();

    if (!sConflicts.IsEmpty())
    {
        ShowConflicts(sConflicts);
    }
    else
    {
        if (bDoBeep)
        {
//            MessageBeep(-1);
        }
    }
    EndDialog(IDOK);
}


void CTabActivationShortcutsDlg::OnCancel() 
{
    UpdateData();
    cfg_VKsGoToTab = m_GotoKey;
    cfg_ModGoToTab = (HOTKEYF_ALT     * m_bGotoAlt) +
                     (HOTKEYF_CONTROL * m_bGotoControl) +
                     (HOTKEYF_SHIFT   * m_bGotoShift);
	
	CHHDialog::OnCancel();
}
