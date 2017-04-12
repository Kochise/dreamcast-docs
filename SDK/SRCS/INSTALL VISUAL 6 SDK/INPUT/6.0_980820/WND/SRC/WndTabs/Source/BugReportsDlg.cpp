// BugReportsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "wndtabs.h"
#include "BugReportsDlg.h"
#include "Extensions.h"
#include "Help\HelpIDs.h"
#include "VCVerMgr.h"

#include "AddInComm\AddInComm.h"
#include "AddInComm\AICLoader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBugReportsDlg dialog

CBugReportsDlg::CBugReportsDlg(CWnd* pParent /*=NULL*/)
	: CHHDialog(CBugReportsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBugReportsDlg)
	//}}AFX_DATA_INIT
}


void CBugReportsDlg::DoDataExchange(CDataExchange* pDX)
{
	CHHDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBugReportsDlg)
	DDX_Control(pDX, ID_EDIT_COPY, m_CopyBtn);
	DDX_Control(pDX, IDC_MAIL, m_MailLink);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBugReportsDlg, CHHDialog)
	//{{AFX_MSG_MAP(CBugReportsDlg)
	ON_BN_CLICKED(ID_EDIT_COPY, OnCopy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBugReportsDlg message handlers

BOOL CBugReportsDlg::OnInitDialog() 
{
    CHHDialog::OnInitDialog();

    CString cSysSummary;
    CString cStr;

    cSysSummary = GetSysSummary();
    GetDlgItem(IDC_INFO4BUGREP)->SetWindowText(cSysSummary);

    m_MailLink.SetURL(MakeSupportMailURL());

    m_CopyBtn.SetImage(IDB_2CLIPBOARD);

	return TRUE;  
}

CString CBugReportsDlg::MakeSupportMailURL()
{
    CString cSysSummary = GetSysSummary();
    cSysSummary.Insert(0, "\n\n------\n");
    cSysSummary.Replace("\n", "%0D%0A");
    cSysSummary.Replace("\t", "%09");
    cSysSummary.Replace(" ", "%20");

    CString cStr;
    cStr.LoadString(IDS_MAILLINK);
    cStr += "?Body=";
    cStr += cSysSummary;
    return cStr;
}

static AddDetectedAddin(const char *pszAddinName, const char *pszShortHand,
    CString& res)
{
    int iVerMaj, iVerMin, iVerExtra;
    HADDIN hAddIn = AICGetAddIn(pszAddinName);
    if (hAddIn)
    {
        CString cStr;
        AICGetAddInVersion(hAddIn, iVerMaj, iVerMin, iVerExtra);
        cStr.Format("%s %d.%d.%d", pszShortHand, iVerMaj, iVerMin, iVerExtra);
        if (!res.IsEmpty())
        {
            res += ", ";
        }
        res += cStr;
    }
}

CString CBugReportsDlg::GetSysSummary()
{
    int iVerMaj, iVerMin, iVerExtra;
    CString cStr1, cStr2, cStr3;
    char ver[256];

    {
        CDialog dlg;
        dlg.Create(IDD_BUGREPORTS);
        dlg.GetDlgItem(IDC_INFO4BUGREP)->GetWindowText(cStr1);
        dlg.DestroyWindow();
    }
    
    // WndTabs Version
    cStr2 = g_cVersion;
    if (GetExtensionsErr() == 0) 
    {
        if (g_sRegUserName.IsEmpty())
            cStr2 += "  (Trial Registered)";
        else
            cStr2 += "  (Registered)";
    }
    CString_Replace(cStr1, "%1", cStr2);

    // AddInComm Version
    if (!aiclIsAICLoaded())
    {
        cStr2 = "Not loaded";
    }
    else
    {
        AICGetDllVersion(iVerMaj, iVerMin, iVerExtra);
        aiclGetModuleVersion("AIC.mod", (LPSTR)ver);
        cStr2.Format("Version %d.%d.%d (%s)", iVerMaj, iVerMin, iVerExtra,
            ver);
    }
    CString_Replace(cStr1, "%5", cStr2);

    // DevStudio Version
    aiclGetModuleVersion(g_pszVCExeName, (LPSTR)ver);
    CString_Replace(cStr1, "%2", (LPCTSTR)ver);
    CString_Replace(cStr1, "%7", g_pszVCExeName);

    // Common Controls Library Version
    aiclGetModuleVersion("COMCTL32.DLL", (LPSTR)ver);
    CString_Replace(cStr1, "%3", (LPCTSTR)ver);

    // OS Version
    CString_Replace(cStr1, "%4", GetOSVersion());

    // Incluencing Add-Ins
    if (!aiclIsAICLoaded())
    {
        cStr2 = "(Cannot detect without AddInComm)";
    }
    else
    {
        cStr2.Empty();
        AddDetectedAddin("WorkspaceWhiz", "WWhiz!", cStr2);
        AddDetectedAddin("VisualAssist", "VA", cStr2);
        AddDetectedAddin("SmartHelp", "SH", cStr2);
        AddDetectedAddin("ZManagers", "UM", cStr2);

        if (cStr2.IsEmpty())
        {
            cStr2 = "None detected";
        }
    }
    CString_Replace(cStr1, "%6", cStr2);

    return cStr1;
}

CString CBugReportsDlg::GetOSVersion()
{
    CString         cStr1;
    OSVERSIONINFO   osvi;

    osvi.dwOSVersionInfoSize = sizeof(osvi);
    GetVersionEx(&osvi);

    const char *pszOS;

    if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
        pszOS = "NT";
    }
    else
    {
        // Windows 9x
        switch (osvi.dwMinorVersion)
        {
            case 0:
                pszOS = "95";
                break;

            case 10:
                pszOS = "98";
                break;

            case 90:
                pszOS = "ME";
                break;

            default:
                pszOS = "9x";
        }
    }

    cStr1.Format("Windows %s %d.%d %s", pszOS, osvi.dwMajorVersion,
        osvi.dwMinorVersion, osvi.szCSDVersion);

    return cStr1;
}

void CBugReportsDlg::OnCopy() 
{
    CEdit   cEdit;
    CString cStr;

    GetDlgItem(IDC_INFO4BUGREP)->GetWindowText(cStr);

    if (cEdit.Create(0, CRect(0, 0, 1, 1), this, 0))
    {
        cEdit.SetWindowText(cStr);
        cEdit.SetSel(0, -1);
        cEdit.Copy();
    }
    else
    {
        AfxMessageBox("Failed to copy information.", 
            MB_OK | MB_ICONEXCLAMATION);
    }
}
