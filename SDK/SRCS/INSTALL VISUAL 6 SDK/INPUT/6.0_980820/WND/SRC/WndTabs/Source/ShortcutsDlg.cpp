/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/

// ShortcutsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "wndtabs.h"
#include "ShortcutsDlg.h"
#include "MainFrame.h"
#include "Config.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

struct ShortcutCmd
{
    UINT    idCmd;
    UINT    idVirtKey;
    UINT    idModifier;
    bool    bSetByDefault;
};

static const ShortcutCmd Cmds[] = 
{
    { IDC_OPTIONS,      191 /*/*/,  HOTKEYF_CONTROL | HOTKEYF_SHIFT, false },
    { IDC_HEADERFLIP,   'H',        HOTKEYF_CONTROL | HOTKEYF_SHIFT, true  },
    { IDC_OPENASTEXT,   'T',        HOTKEYF_CONTROL | HOTKEYF_SHIFT, true  },
    { IDC_SETCURRDIR,   'D',        HOTKEYF_CONTROL | HOTKEYF_SHIFT, false },
    { IDC_RENUMBER,     'N',        HOTKEYF_CONTROL | HOTKEYF_SHIFT, true  },
    { IDC_REORDER,      'O',        HOTKEYF_CONTROL | HOTKEYF_SHIFT, true, },
    { IDC_TAB_NEXT,     190 /*.*/,  HOTKEYF_CONTROL,                 true, },
    { IDC_TAB_PREV,     188 /*,*/,  HOTKEYF_CONTROL,                 true, }
};


/////////////////////////////////////////////////////////////////////////////
// CShortcutsBase

CShortcutsBase::CShortcutsBase()
{
    m_hAccelTable = g_pMainFrame->m_hAccelTable;
	m_nAccelSize = ::CopyAcceleratorTable (m_hAccelTable, NULL, 0);

	m_lpAccel = new ACCEL [m_nAccelSize];
	ASSERT (m_lpAccel != NULL);

	::CopyAcceleratorTable (m_hAccelTable, m_lpAccel, m_nAccelSize);
}

CShortcutsBase::~CShortcutsBase()
{
    delete [] m_lpAccel;
}

void CShortcutsBase::SetHKInAccel(int idCmd, int iVK, int iHKMod,
    CString& sConflicts)
{
    if (iVK == 0)
    {
        UnsetHKInAccel(idCmd);
        return;
    }
    ACCEL *pAcc = NULL;
    int fVirt = HKMod2ACCELMod(iHKMod);

    for (int iAccel = 0; iAccel < m_nAccelSize; iAccel++)
    {
        ACCEL& a = m_lpAccel[iAccel];
        if (a.cmd == idCmd)
        {
            if (!pAcc)
            {
                pAcc = &a;
            }
        }
        else
        {
            if (a.fVirt == fVirt  &&  a.key == iVK)
            {
                sConflicts += GetCmdName(idCmd);
                sConflicts += " (conflicts with hotkey for \"";
                sConflicts += GetCmdName(a.cmd);
                sConflicts += "\")\n";
                return;
            }
        }
    }

    if (!pAcc)
    {
        // wasn't already in table - create new entry
        LPACCEL lpAccelNew = new ACCEL[m_nAccelSize + 1];
        memcpy(lpAccelNew, m_lpAccel, sizeof(ACCEL) * m_nAccelSize);
        delete [] m_lpAccel;
        m_lpAccel = lpAccelNew;
        pAcc = &m_lpAccel[m_nAccelSize];
        m_nAccelSize++;
    }

    pAcc->cmd = idCmd;
    pAcc->fVirt = fVirt;
    pAcc->key = iVK;
}

bool CShortcutsBase::UnsetHKInAccel(int idCmd)
{
    int iAccel;
    bool bDeleted = false;

    for (iAccel = 0; iAccel < m_nAccelSize; iAccel++)
    {
        ACCEL& a = m_lpAccel[iAccel];
        if (a.cmd == idCmd)
        {
            // delete it
            memmove(&a, &m_lpAccel[iAccel + 1], 
                sizeof(ACCEL) * (m_nAccelSize - iAccel - 1));
            --m_nAccelSize;
            --iAccel;
            bDeleted = true;
        }
    }

    return bDeleted;
}

int CShortcutsBase::ACCELMod2HKMod(int iAccelMod)
{
    int iMod = 0;
    if (iAccelMod & FALT)     iMod |= HOTKEYF_ALT;
    if (iAccelMod & FCONTROL) iMod |= HOTKEYF_CONTROL;
    if (iAccelMod & FSHIFT)   iMod |= HOTKEYF_SHIFT;
    return iMod;
}

int CShortcutsBase::HKMod2ACCELMod(int iHKMod)
{
    int iMod = 0;
    if (iHKMod & HOTKEYF_ALT)     iMod |= FALT;
    if (iHKMod & HOTKEYF_CONTROL) iMod |= FCONTROL;
    if (iHKMod & HOTKEYF_SHIFT)   iMod |= FSHIFT;
    iMod |= FVIRTKEY;
    return iMod;
}

CString CShortcutsBase::GetCmdName(int idCmd)
{
    CString cStr;
    if (!cStr.LoadString(idCmd))
    {
        cStr = "(unknown)";
    }
    else
    {
        CString cStr2;
        AfxExtractSubString(cStr2, cStr, 1);
        return cStr2;
    }

    return cStr;
}

void CShortcutsBase::ShowConflicts(const CString& sConflicts)
{
    CString cMsg;
    AfxFormatString1(cMsg, IDS_HK_NOT_SET, sConflicts);
    AfxMessageBox(cMsg, MB_OK | MB_ICONEXCLAMATION);
}

void CShortcutsBase::ApplyAccelChanges()
{
    DestroyAcceleratorTable(m_hAccelTable);
    m_hAccelTable = CreateAcceleratorTable(m_lpAccel, m_nAccelSize);
    theApp.GetKeyboardManager()->UpdateAcellTable(NULL, m_lpAccel, 
        m_nAccelSize);
}

/////////////////////////////////////////////////////////////////////////////
// CShortcutsDlg dialog


CShortcutsDlg::CShortcutsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShortcutsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShortcutsDlg)
	//}}AFX_DATA_INIT
}

CShortcutsDlg::~CShortcutsDlg()
{
}

void CShortcutsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShortcutsDlg)
	DDX_Control(pDX, IDC_SHOW_SUGGESTED, m_SuggestedBtn);
	DDX_Control(pDX, IDC_CLEAR_SHORTCUTS, m_ClearBtn);
	DDX_Control(pDX, IDC_SET_SHORTCUTS, m_SetBtn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShortcutsDlg, CDialog)
	//{{AFX_MSG_MAP(CShortcutsDlg)
	ON_BN_CLICKED(IDC_OPTIONS, DoUpdateDlgItems)
	ON_BN_CLICKED(IDC_SHOW_SUGGESTED, OnShowSuggested)
	ON_BN_CLICKED(IDC_CLEAR_SHORTCUTS, OnClearShortcuts)
	ON_BN_CLICKED(IDC_SET_SHORTCUTS, OnSetShortcuts)
	ON_BN_CLICKED(IDC_HEADERFLIP, DoUpdateDlgItems)
	ON_BN_CLICKED(IDC_OPENASTEXT, DoUpdateDlgItems)
	ON_BN_CLICKED(IDC_SETCURRDIR, DoUpdateDlgItems)
	ON_BN_CLICKED(IDC_RENUMBER, DoUpdateDlgItems)
	ON_BN_CLICKED(IDC_REORDER, DoUpdateDlgItems)
	ON_BN_CLICKED(IDC_GROUP_NEXT, DoUpdateDlgItems)
	ON_BN_CLICKED(IDC_GROUP_PREV, DoUpdateDlgItems)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShortcutsDlg message handlers

BOOL CShortcutsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_SuggestedBtn.SetImage(IDB_RELOAD);
	m_ClearBtn.    SetImage(IDB_CANCEL);
	m_SetBtn.      SetImage(IDB_OK);

    UpdateDlgFromAccel();
    DoUpdateDlgItems();
    
	return TRUE;
}

void CShortcutsDlg::UpdateDlgFromAccel()
{
    for (int iCmd = 0; iCmd < countof(Cmds); iCmd++)
    {
        CHotKeyCtrl *pHK = GetHKCtrl(Cmds[iCmd].idCmd);
        for (int i = 0; i < m_nAccelSize; i++)
        {
            ACCEL& a = m_lpAccel[i];
            if (a.cmd == Cmds[iCmd].idCmd)
            {
                if (pHK)
                {
                    pHK->SetHotKey(a.key, ACCELMod2HKMod(a.fVirt));
                }
                goto next;
            }
        }
        pHK->SetHotKey(0, 0);
next:;        
    }
}

CHotKeyCtrl *CShortcutsDlg::GetHKCtrl(UINT idCmd)
{
    CWnd *pWnd = GetDlgItem(idCmd);
    WT_ASSERT(pWnd);
    if (!pWnd) return NULL;
    return (CHotKeyCtrl *)pWnd->GetNextWindow();
}

void CShortcutsDlg::DoUpdateDlgItems() 
{
    for (int i = 0; i < countof(Cmds); i++)
    {
        CButton *pCheck = (CButton *)GetDlgItem(Cmds[i].idCmd);
        pCheck->GetNextWindow()->EnableWindow(pCheck->GetCheck());
    }
}

void CShortcutsDlg::OnShowSuggested() 
{
    for (int i = 0; i < countof(Cmds); i++)
    {
        const ShortcutCmd& cmd = Cmds[i];
        CButton *pCheck = (CButton *)GetDlgItem(cmd.idCmd);
        if (!pCheck) continue;
        CHotKeyCtrl *pHK = (CHotKeyCtrl *)pCheck->GetNextWindow();
        if (!pHK) continue;

        pCheck->SetCheck(cmd.bSetByDefault);
        pHK->SetHotKey(cmd.idVirtKey, cmd.idModifier);
    }
    DoUpdateDlgItems();
}

void CShortcutsDlg::OnClearShortcuts() 
{
    const int iOldCount = m_nAccelSize;

    for (int i = 0; i < countof(Cmds); i++)
    {
        const ShortcutCmd& cmd = Cmds[i];

        if (((CButton *)GetDlgItem(cmd.idCmd))->GetCheck())
        {
            UnsetHKInAccel(cmd.idCmd);
        }
    }

    MessageBeep(-1);
    UpdateAccelFromDlgData();
}

void CShortcutsDlg::OnSetShortcuts() 
{
    WORD wVK, wMod;
    CString sConflicts;

    for (int i = 0; i < countof(Cmds); i++)
    {
        const ShortcutCmd& cmd = Cmds[i];
        if (((CButton *)GetDlgItem(cmd.idCmd))->GetCheck())
        {
            CHotKeyCtrl *pHK = GetHKCtrl(cmd.idCmd);
            if (!pHK) continue;

            pHK->GetHotKey(wVK, wMod);
            SetHKInAccel(cmd.idCmd, wVK, wMod, sConflicts);
        }
    }

    UpdateAccelFromDlgData();
    if (!sConflicts.IsEmpty())
    {
        ShowConflicts(sConflicts);
    }
    else
    {
        MessageBeep(-1);
    }
}

void CShortcutsDlg::UpdateAccelFromDlgData()
{
    ApplyAccelChanges();
    UpdateDlgFromAccel();
}

void CShortcutsDlg::OnCancel() 
{
    CDialog::OnCancel();
}
