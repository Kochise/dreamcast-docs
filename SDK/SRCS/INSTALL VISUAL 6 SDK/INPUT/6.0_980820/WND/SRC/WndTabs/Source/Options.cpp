/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// Options.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Options.h"
#include "WndTabs.h"
#include "TabsWindow.h"
#include "TabManagerWindow.h"
#include "Commands.h"
#include "Config.h"
#include "Extensions.h"
#include "SelectCharDialog.h"
#include "InfoDlg.h"
#include "BugReportsDlg.h"
#include "Help\HelpIDs.h"
#include "PIDL.h"
#include "DevStudioWnd.h"
#include "ToolbarSetup.h"
#include "ShortcutsDlg.h"
#include "TabActivationShortcutsDlg.h"
#include "SDK_Supp.h"
#include "CustomizeCtxMenuDlg.h"
#include "CmdSelDialog.h"
#include "AddInComm\AICLoader.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define CPropertyPage CAutoPropPage
#define CPropertySheet CTreePropertySheet

IMPLEMENT_DYNAMIC(COptionsSheet, CPropertySheet)
IMPLEMENT_DYNCREATE(CArrangementPage, CPropertyPage)
IMPLEMENT_DYNCREATE(CTabDisplayPage, CPropertyPage)
IMPLEMENT_DYNCREATE(CMenusPage, CPropertyPage)
IMPLEMENT_DYNCREATE(CMiscPage, CPropertyPage)
IMPLEMENT_DYNCREATE(CAboutPage, CPropertyPage)


/////////////////////////////////////////////////////////////////////////////
// COptionsSheet

COptionsSheet::COptionsSheet(int iInitialPage, CWnd* pWndParent)
	 : CPropertySheet(IDS_OPTIONSSHEET_CAPTION, pWndParent)
{
    CommonInit();
    if (iInitialPage < 0) iInitialPage += GetPageCount();
    SetActivePage(iInitialPage);
    m_bUseConfigVar = false;
}

COptionsSheet::COptionsSheet(CWnd* pWndParent)
	 : CPropertySheet(IDS_OPTIONSSHEET_CAPTION, pWndParent)
{
    CommonInit();
    if (cfg_iLastOptionTreeSel < 0  ||  
        cfg_iLastOptionTreeSel >= GetPageCount())
    {
        cfg_iLastOptionTreeSel = 0;
    }
    SetActivePage(cfg_iLastOptionTreeSel);
    m_bUseConfigVar = true;
}

void COptionsSheet::CommonInit()
{
    AddPage(&m_TabsPage);
     AddPage(&m_ArrangmentPage);
     AddPage(&m_TabDisplayPage);
     AddPage(&m_OrderingPage);
     AddPage(&m_TrimmingPage);
     AddPage(&m_WTTabCtrlPage);
     AddPage(&m_WTTabCtrlPage2);
    AddPage(&m_WinFileManPage);
    AddPage(&m_CustomizePage);
     AddPage(&m_MenusPage);
     AddPage(&m_KeyboardPage);
     AddPage(&m_MousePage);
	AddPage(&m_MiscPage);
    AddPage(&m_LanguagePage);
    AddPage(&m_RegistrationPage);
	AddPage(&m_AboutPage);

    SetTreeConfig(cfg_sOptionsDlgTree);

	// set the language-specific tree width
	CString cStr;
	cStr.LoadString(IDS_OPTIONS_TREEWIDTH);
    m_iTreeWidth = atoi(cStr);

    // sniffing time!
    RefreshActiveAddonsList();
}

COptionsSheet::~COptionsSheet()
{
    cfg_sOptionsDlgTree = GetTreeConfig();
}


BEGIN_MESSAGE_MAP(COptionsSheet, CPropertySheet)
	//{{AFX_MSG_MAP(COptionsSheet)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CUSTOMIZE, OnCustomize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// COptionsSheet message handlers

BOOL COptionsSheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();

    CRect r, r_client;
    CWnd *pRightMostBtn = GetDlgItem(IDHELP);
    pRightMostBtn->GetWindowRect(r);
    GetClientRect(r_client);
    ScreenToClient(r);
    int iMargin = r_client.right - r.right;
    r.right = iMargin + r.Width();
    r.left = iMargin;
    CString sCaption;
    sCaption.LoadString(IDS_CUSTOMIZE);
    m_CustomizeBtn.Create(sCaption, WS_CHILD | WS_VISIBLE, r, this, 
        IDC_CUSTOMIZE);
    m_CustomizeBtn.SetFont(GetFont());
    m_CustomizeBtn.SetImage(IDB_CUSTOMIZE3);
    m_CustomizeBtn.m_nFlatStyle = CBCGButton::BUTTONSTYLE_FLAT;
	// adjust the size of the button if it's too small 
    // (may be language dependent)
	CDC* pDC = m_CustomizeBtn.GetDC();
	if( pDC )
	{
        CFont *pOldFont = pDC->SelectObject(GetFont());
		CSize sz = pDC->GetTextExtent(sCaption);
        const int iNewWidth = (sz.cx + 4 + 12 + 16 /* border, margins, icon */);
		if( r.Width() < iNewWidth )
		{
			r.right = r.left + iNewWidth;
			m_CustomizeBtn.MoveWindow(r);
		}
        pDC->SelectObject(pOldFont);
		m_CustomizeBtn.ReleaseDC(pDC);
	}

    // force init of all pages
    const int iCount = GetPageCount();
    const int iOldActive = GetActiveIndex();
    for (int i = 0; i < iCount; ++i)
    {
//        SetActivePage(i);
    }
    SetActivePage(iOldActive);

	return bResult;
}

void COptionsSheet::OnDestroy() 
{
    if (m_bUseConfigVar)
    {
        cfg_iLastOptionTreeSel = GetActiveIndex();
    }

    CPropertySheet::OnDestroy();
}

int COptionsSheet::DoModal() 
{
    int iRetVal = CPropertySheet::DoModal();

    if (iRetVal == IDOK)
    {
        WriteConfiguration();
    }
    return iRetVal;
}

void COptionsSheet::OnCustomize()
{
    CWnd *pBtnApply = GetDlgItem(ID_APPLY_NOW);
    if (pBtnApply->IsWindowEnabled())
    {
        if (AfxMessageBox(IDS_WARN_GOTO_CUSTOMIZE, 
            MB_OKCANCEL | MB_ICONINFORMATION) != IDOK)
        {
            return;
        }
    }
    PressButton(PSBTN_OK);
    DoCustomize((CFrameWnd *)g_pMainFrame);
}



/////////////////////////////////////////////////////////////////////////////
// CTabsPage property page

IMPLEMENT_DYNCREATE(CTabsPage, CPropertyPage)

CTabsPage::CTabsPage() : CPropertyPage(CTabsPage::IDD)
{
	//{{AFX_DATA_INIT(CTabsPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CTabsPage::~CTabsPage()
{
}

void CTabsPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabsPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabsPage, CPropertyPage)
	//{{AFX_MSG_MAP(CTabsPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabsPage message handlers

BOOL CTabsPage::OnSetActive() 
{
    COptionsSheet *pParent = ((COptionsSheet *)GetParent());
    pParent->SetActivePage(&pParent->m_ArrangmentPage);
    return FALSE;
}



/////////////////////////////////////////////////////////////////////////////
// CArrangementPage property page

BEGIN_HELP_IDS(CArrangementPage)
    IDC_STATIC_ORIENTATION, IDC_STATIC_ORIENTATION,
    IDC_TOP,                IDC_STATIC_ORIENTATION,
    IDC_BOTTOM,             IDC_STATIC_ORIENTATION,
    IDC_LEFT,               IDC_STATIC_ORIENTATION,
    IDC_RIGHT,              IDC_STATIC_ORIENTATION,

    IDC_ROWS,               IDC_STATIC_ROWS,
    IDC_AUTO,               IDC_STATIC_ROWS,
    IDC_FIXED,              IDC_STATIC_ROWS,
    IDC_SPIN,               IDC_STATIC_ROWS,

    ID_EVERY,               IDC_AUTOREFRESH,
    IDC_INTERVAL,           IDC_AUTOREFRESH,
    IDC_INTERVALTEXT,       IDC_AUTOREFRESH
END_HELP_IDS();    

CArrangementPage::CArrangementPage() : m_bInited(false), 
    CPropertyPage(CArrangementPage::IDD)
{
    m_iHelpID = IDH_OPTPAGE_TABS_LAYOUT;

	//{{AFX_DATA_INIT(CArrangementPage)
	m_RadioOrientation = 0;
	m_iRows = 0;
	m_bFixedTabRows = -1;
	m_bAutoRefresh = 0;
	m_iInterval = 0;
	m_bNoRaggedRight = FALSE;
	//}}AFX_DATA_INIT

    varpair vars[] = 
    {
        { &m_RadioOrientation,      &cfg_iOrientation            },
        { &m_bFixedTabRows,         &cfg_bFixedRowCount          },
        { &m_iRows,                 (int *)&cfg_iRows            },
    	{ &m_bAutoRefresh,          &cfg_bAutoRefresh            },
    	{ &m_iInterval,             (int *)&cfg_iRefreshInterval },
        { &m_bNoRaggedRight,        &cfg_bNoRaggedRight          }
    };

    InitAutoVars(countof(vars), vars);
}

void CArrangementPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArrangementPage)
	DDX_Control(pDX, IDC_SPIN, m_RowSpin);
	DDX_Radio(pDX, IDC_TOP, m_RadioOrientation);
	DDX_Text(pDX, IDC_ROWS, m_iRows);
	DDV_MinMaxUInt(pDX, m_iRows, 1, 10);
	DDX_Radio(pDX, IDC_AUTO, m_bFixedTabRows);
	DDX_Check(pDX, IDC_AUTOREFRESH, m_bAutoRefresh);
	DDX_Text(pDX, IDC_INTERVAL, m_iInterval);
	DDV_MinMaxInt(pDX, m_iInterval, 1, 10000);
	DDX_Check(pDX, IDC_NORAGGEDRIGHT, m_bNoRaggedRight);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArrangementPage, CPropertyPage)
	//{{AFX_MSG_MAP(CArrangementPage)
	ON_EN_CHANGE(IDC_ROWS, DoModify)
    ON_EN_CHANGE(IDC_INTERVAL, DoModify)
	ON_BN_CLICKED(IDC_AUTO, UpdateAutoTabRows)
	ON_BN_CLICKED(IDC_AUTOREFRESH, OnAutorefresh)
	ON_BN_CLICKED(IDC_BOTTOM, DoModify)
	ON_BN_CLICKED(IDC_TOP, DoModify)
	ON_BN_CLICKED(IDC_LEFT, DoModify)
	ON_BN_CLICKED(IDC_RIGHT, DoModify)
	ON_BN_CLICKED(IDC_FIXED, UpdateAutoTabRows)
	ON_BN_CLICKED(IDC_NORAGGEDRIGHT, DoModify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CArrangementPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

    UpdateAutoTabRows();

    OnAutorefresh();

    m_RowSpin.SetRange(1, 10);

    m_bInited = true;

    return TRUE;
}

BOOL CArrangementPage::OnSetActive() 
{
    COptionsSheet * const pParent = (COptionsSheet *)GetParent();
    BOOL b = (pParent->m_WTTabCtrlPage.m_bUseWTTabCtrl);

    GetDlgItem(IDC_LEFT) ->EnableWindow(!b);
    GetDlgItem(IDC_RIGHT)->EnableWindow(!b);

	return CPropertyPage::OnSetActive();
}

BOOL CArrangementPage::OnApply() 
{
    BOOL bRetVal;

    if ((bRetVal = CPropertyPage::OnApply()))
    {
        if (Changed(m_RadioOrientation) ||
            Changed(m_bNoRaggedRight)   ||
            Changed(m_iRows)            ||
            Changed(m_bFixedTabRows))
        {
            COptionsSheet * const pParent = (COptionsSheet *)GetParent();
            BOOL b = (pParent->m_WTTabCtrlPage.m_bUseWTTabCtrl);
            cfg_bUseWTTabCtrl = b;

            int tempo = cfg_iOrientation;
            cfg_iOrientation = PrevVal(m_RadioOrientation);
            pGlobalActiveManager->SetManaging(false);
            cfg_iOrientation = tempo;

            if (m_bFixedTabRows)
            {
                g_cTabRows = cfg_iRows;
            }

            pGlobalTabs->UpdateStyle();
            pGlobalActiveManager->SetManaging(true);
        }
    }

    return bRetVal;
}

void CArrangementPage::UpdateAutoTabRows() 
{
    SetModified();	
    UpdateData();
    GetDlgItem(IDC_ROWS)->EnableWindow(m_bFixedTabRows);
}

void CArrangementPage::OnAutorefresh() 
{
    if (UpdateData())
    {
        GetDlgItem(ID_EVERY)        ->EnableWindow(m_bAutoRefresh);
        GetDlgItem(IDC_INTERVAL)    ->EnableWindow(m_bAutoRefresh);
        GetDlgItem(IDC_INTERVALTEXT)->EnableWindow(m_bAutoRefresh);
        SetModified();
    }
    else
    {
        m_bAutoRefresh = !m_bAutoRefresh;
        UpdateData(FALSE);
    }
}

void CArrangementPage::DoModify() 
{
    SetModified();
}


/////////////////////////////////////////////////////////////////////////////
// CTabDisplayPage property page

BEGIN_HELP_IDS(CTabDisplayPage)
    IDC_DISP_RC,            IDC_STATIC_RESOURCES,
    IDC_DISP_RID,           IDC_STATIC_RESOURCES,
    IDC_DISP_RESTYPE,       IDC_STATIC_RESOURCES,
    IDC_DISP_RESLANG,       IDC_STATIC_RESOURCES,

    IDC_SERIF,              IDC_FONT_STATIC,
    IDC_SANS_SERIF,         IDC_FONT_STATIC
END_HELP_IDS()

CTabDisplayPage::CTabDisplayPage() : CPropertyPage(CTabDisplayPage::IDD)
{
    m_iHelpID = IDH_OPTPAGE_TABS_CONTENT;

	//{{AFX_DATA_INIT(CTabDisplayPage)
	m_bShowIcons = 0;
	m_bShowNumbers = 0;
	m_bStripPath = 0;
	m_bStripExt = 0;
	m_bDispRC = 0;
	m_bDispResLang = 0;
	m_bDispResType = 0;
	m_bDispRID = 0;
	m_FontType = -1;
	//}}AFX_DATA_INIT

    varpair vars[] = 
    {
        { &m_bShowIcons,         &cfg_bShowIcons      },
        { &m_bShowNumbers,       &cfg_bShowNumbers    },
        { &m_bStripPath,         &cfg_bStripPath      },
        { &m_bStripExt,          &cfg_bStripExt       },
        { &m_bDispRC,            &cfg_bDispRC         },
        { &m_bDispResLang,       &cfg_bDispResLang    },
        { &m_bDispResType,       &cfg_bDispResType    },
        { &m_bDispRID,           &cfg_bDispRID        },
        { &m_FontType,           &cfg_ftFontType      }
    };

    InitAutoVars(countof(vars), vars);
}

void CTabDisplayPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabDisplayPage)
	DDX_Control(pDX, IDC_GO_TO_TRIMMING, m_GoButton);
	DDX_Check(pDX, IDC_SHOWICONS, m_bShowIcons);
	DDX_Check(pDX, IDC_SHOWNUMBERS, m_bShowNumbers);
	DDX_Check(pDX, IDC_STRIPDIRS, m_bStripPath);
	DDX_Check(pDX, IDC_STRIPEXT, m_bStripExt);
	DDX_Check(pDX, IDC_DISP_RC, m_bDispRC);
	DDX_Check(pDX, IDC_DISP_RESLANG, m_bDispResLang);
	DDX_Check(pDX, IDC_DISP_RESTYPE, m_bDispResType);
	DDX_Check(pDX, IDC_DISP_RID, m_bDispRID);
	DDX_Radio(pDX, IDC_SERIF, m_FontType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabDisplayPage, CPropertyPage)
	//{{AFX_MSG_MAP(CTabDisplayPage)
	ON_BN_CLICKED(IDC_STRIPDIRS, DoModify)
	ON_BN_CLICKED(IDC_SHOWNUMBERS, DoModify)
	ON_BN_CLICKED(IDC_SHOWICONS, DoModify)
	ON_BN_CLICKED(IDC_DISP_RC, DoModify)
	ON_BN_CLICKED(IDC_DISP_RESLANG, DoModify)
	ON_BN_CLICKED(IDC_DISP_RESTYPE, DoModify)
	ON_BN_CLICKED(IDC_DISP_RID, DoModify)
	ON_BN_CLICKED(IDC_LIMITRESCHARS, DoModify)
	ON_BN_CLICKED(IDC_IGNOREEXT, DoModify)
	ON_BN_CLICKED(IDC_STRIPEXT, DoModify)
	ON_BN_CLICKED(IDC_SERIF, DoModify)
	ON_BN_CLICKED(IDC_SANS_SERIF, DoModify)
	ON_EN_CHANGE(IDC_CHARLIMIT, DoModify)
	ON_BN_CLICKED(IDC_GO_TO_TRIMMING, OnGo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CTabDisplayPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
    m_GoButton.SetImage(IDB_GO, IDB_GO_HOVER);
    m_GoButton.m_nFlatStyle = CBCGButton::BUTTONSTYLE_FLAT;
	return TRUE;
}


BOOL CTabDisplayPage::OnApply() 
{
    BOOL bRetVal;

    if ((bRetVal = CPropertyPage::OnApply()))
    {
        if (ChangedAny())
        {
            if (Changed(m_FontType) || Changed(m_bShowIcons))
            {
                pGlobalActiveManager->SetManaging(false);
                pGlobalTabs->UpdateStyle();
                pGlobalActiveManager->SetManaging(true);
            }
            else
            {
                pGlobalActiveManager->PostUpdateMessage();
            }
        }
    }
	
	return bRetVal;
}

void CTabDisplayPage::OnGo() 
{
    COptionsSheet *pParent = ((COptionsSheet *)GetParent());
    pParent->SetActivePage(&pParent->m_TrimmingPage);
}

void CTabDisplayPage::DoModify() 
{
    SetModified();
}



/////////////////////////////////////////////////////////////////////////////
// COrderingPage property page

BEGIN_HELP_IDS(COrderingPage)
    IDC_STATIC_MDI_ORDER,       IDC_MDI_ORDER,
    IDC_STATIC_PRESERVE_ORDER,  IDC_PRESERVE_ORDER
END_HELP_IDS()

COrderingPage::COrderingPage() : CPropertyPage(COrderingPage::IDD)
{
    m_iHelpID = IDH_OPTPAGE_TABS_ORDERING;

    //{{AFX_DATA_INIT(COrderingPage)
	m_bFill1To9 = 0;
	m_bPreserveNumbering = 0;
	m_iTabOrdering = -1;
	m_bSaveTabNums = FALSE;
	//}}AFX_DATA_INIT

    varpair vars[] = 
    {
        { &m_iTabOrdering,          &cfg_TabOrdering        },
        { &m_bPreserveNumbering,    &cfg_bPreserveNumbering },
        { &m_bFill1To9,             &cfg_bFill1To9          },
        { &m_bSaveTabNums,          &cfg_bSaveTabNumbers    }
    };

    InitAutoVars(countof(vars), vars);
}


void COrderingPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COrderingPage)
	DDX_Check(pDX, IDC_FILL1TO9, m_bFill1To9);
	DDX_Check(pDX, IDC_PRESERVE_NUMBERING, m_bPreserveNumbering);
	DDX_Control(pDX, IDC_REORDER, m_Reorder);
	DDX_Control(pDX, IDC_RENUMBER, m_Renumber);
	DDX_Radio(pDX, IDC_MDI_ORDER, m_iTabOrdering);
	DDX_Check(pDX, IDC_SAVE_TAB_NUM, m_bSaveTabNums);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COrderingPage, CPropertyPage)
	//{{AFX_MSG_MAP(COrderingPage)
	ON_BN_CLICKED(IDC_PRESERVE_ORDER, DoUpdateDlgItems)
	ON_BN_CLICKED(IDC_PRESERVE_NUMBERING, DoUpdateDlgItems)
	ON_BN_CLICKED(IDC_RENUMBER, OnRenumber)
	ON_BN_CLICKED(IDC_REORDER, OnReorder)
	ON_BN_CLICKED(IDC_FILL1TO9, DoModify)
    ON_BN_CLICKED(IDC_SAVE_TAB_NUM, DoUpdateDlgItems)
	ON_BN_CLICKED(IDC_MDI_ORDER, DoUpdateDlgItems)
	ON_BN_CLICKED(IDC_ALPHABETICAL, DoUpdateDlgItems)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COrderingPage message handlers

BOOL COrderingPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
    DoUpdateDlgItems();

    m_Renumber.SetImage(IDB_RENUMBER);
    m_Reorder. SetImage(IDB_REORDER);

	return TRUE;
}

BOOL COrderingPage::OnApply() 
{
    BOOL bRetVal;

    if ((bRetVal = CPropertyPage::OnApply()))
    {
        if (Changed(m_iTabOrdering))
        {
            pGlobalActiveManager->PostUpdateMessage();
        }
    }

    return bRetVal;
}

void COrderingPage::DoModify() 
{
    SetModified();
}

void COrderingPage::DoUpdateDlgItems()
{
    static int idcs[] = 
    { 
        IDC_FILL1TO9, IDC_PRESERVE_NUMBERING, IDC_SAVE_TAB_NUM,
        // ** //
        IDC_RENUMBER
    };

    SetModified();
    UpdateData();

    GetDlgItem(IDC_RENUMBER)->EnableWindow(m_bPreserveNumbering);
    GetDlgItem(IDC_FILL1TO9)->EnableWindow(m_bPreserveNumbering);
    GetDlgItem(IDC_REORDER) ->EnableWindow(m_iTabOrdering == toControlled);

    int count = sizeof(idcs)/sizeof(int);
    const bool bControlled = (m_iTabOrdering != toMDI);
    if (bControlled) count -= 1;

    for (int i = 0; i < count; i++)
    {
        GetDlgItem(idcs[i])->EnableWindow(bControlled);
    }

    if (!m_bPreserveNumbering)
        GetDlgItem(IDC_SAVE_TAB_NUM)->EnableWindow(FALSE);
}

void COrderingPage::OnRenumber() 
{
    pGlobalTabs->Renumber();
}

void COrderingPage::OnReorder() 
{
    pGlobalTabs->Reorder();
}


/////////////////////////////////////////////////////////////////////////////
// CTrimmingPage property page

BEGIN_HELP_IDS(CTrimmingPage)
    IDC_CHARLIMIT,          IDC_LIMITCHARS,
    IDC_STATIC_LIMIT_CHAR,  IDC_LIMITCHARACTER,
    IDC_SELECT,             IDH_SELECT_LIMIT_CHAR,

    IDC_PREFIXES,           IDC_TRIMPREFIX,
    IDC_PREFIXCHAR,         IDC_SELECT_PREFIX_CHAR,

    IDC_SUFFIXES,           IDC_TRIMSUFFIX,
    IDC_SUFFIXCHAR,         IDC_SELECT_SUFFIX_CHAR
END_HELP_IDS()


CTrimmingPage::CTrimmingPage() : CPropertyPage(CTrimmingPage::IDD)
{
    m_iHelpID = IDH_OPTPAGE_TABS_TRIMMING;

	//{{AFX_DATA_INIT(CTrimmingPage)
	m_bLimitChars = 0;
	m_bLimitResChars = 0;
	m_bLimitIgnoreExt = 0;
	m_bUseLimitChar = 0;
	m_iCharLimit = 0;
    m_sLimitCharacter = "'";
	m_bTrimPrefix = FALSE;
	m_bTrimSuffix = FALSE;
	m_bUsePrefixChar = FALSE;
	m_bUseSuffixChar = FALSE;
	m_sSuffixChar = _T("'");
	m_sPrefixChar = _T("'");
	m_sPrefixes = _T("");
	m_sSuffixes = _T("");
	//}}AFX_DATA_INIT

    if (cfg_LimitCharacter == 0)
        cfg_LimitCharacter = (unsigned char)'@';

    if (cfg_TrimPrefixChar == 0)
        cfg_TrimPrefixChar = (unsigned char)'@';

    if (cfg_TrimSuffixChar == 0)
        cfg_TrimSuffixChar = (unsigned char)'@';

    varpair vars[] = 
    {
        { &m_bLimitChars,        &cfg_bLimitChars        },
        { &m_bLimitResChars,     &cfg_bLimitResChars     },
        { &m_bLimitIgnoreExt,    &cfg_bLimitIgnoreExt    },
        { &m_bUseLimitChar,      &cfg_bUseLimitChar      },
        { &m_iCharLimit,         &cfg_iCharLimit         },
        { &m_iLimitChar,         &cfg_LimitCharacter     },
        { &m_bTrimPrefix,        &cfg_bTrimPrefixes      },
        { &m_bTrimSuffix,        &cfg_bTrimSuffixes      },
        { &m_bUsePrefixChar,     &cfg_bUseTrimPrefixChar },
        { &m_bUseSuffixChar,     &cfg_bUseTrimSuffixChar },
        { &m_iPrefixChar,        &cfg_TrimPrefixChar     },
        { &m_iSuffixChar,        &cfg_TrimSuffixChar     }
    };

    strpair strs[] =
    {
        { &m_sPrefixes,          &cfg_sTrimablePrefixes },
        { &m_sSuffixes,          &cfg_sTrimableSuffixes }
    };

    InitAutoVars(countof(vars), vars);
    InitAutoStrs(countof(strs), strs);

    m_sLimitCharacter += (unsigned char)m_iLimitChar;
    m_sLimitCharacter += "'";

    m_sPrefixChar += (unsigned char)m_iPrefixChar;
    m_sPrefixChar += "'";

    m_sSuffixChar += (unsigned char)m_iSuffixChar;
    m_sSuffixChar += "'";
}

void UpdateTrimChar(CDataExchange* pDX, CString& str, int& ch)
{
    if (pDX->m_bSaveAndValidate)
    {
        if (str.GetLength() == 3  &&  str[1])
        {
            ch = (unsigned char)str[1];
        }
        else
        {
            ch = (unsigned char)'@';
        }
    }
    else
    {
        str.Format("'%c'", (unsigned char)ch);
    }
}

void CTrimmingPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrimmingPage)
	DDX_Check(pDX, IDC_LIMITCHARS, m_bLimitChars);
	DDX_Check(pDX, IDC_LIMITRESCHARS, m_bLimitResChars);
	DDX_Check(pDX, IDC_IGNOREEXT, m_bLimitIgnoreExt);
	DDX_Check(pDX, IDC_USELIMITCHAR, m_bUseLimitChar);
	DDX_Text(pDX, IDC_CHARLIMIT, m_iCharLimit);
	DDV_MinMaxInt(pDX, m_iCharLimit, 1, 256);
	DDX_Text(pDX, IDC_LIMITCHARACTER, m_sLimitCharacter);
	DDX_Check(pDX, IDC_TRIMPREFIX, m_bTrimPrefix);
	DDX_Check(pDX, IDC_TRIMSUFFIX, m_bTrimSuffix);
	DDX_Check(pDX, IDC_USEPREFIXCHAR, m_bUsePrefixChar);
	DDX_Check(pDX, IDC_USESUFFIXCHAR, m_bUseSuffixChar);
	DDX_Text(pDX, IDC_SUFFIXCHAR, m_sSuffixChar);
	DDX_Text(pDX, IDC_PREFIXCHAR, m_sPrefixChar);
	DDX_Text(pDX, IDC_PREFIXES, m_sPrefixes);
	DDX_Text(pDX, IDC_SUFFIXES, m_sSuffixes);
	//}}AFX_DATA_MAP

    UpdateTrimChar(pDX, m_sLimitCharacter, m_iLimitChar);
    UpdateTrimChar(pDX, m_sPrefixChar,     m_iPrefixChar);
    UpdateTrimChar(pDX, m_sSuffixChar,     m_iSuffixChar);
}


BEGIN_MESSAGE_MAP(CTrimmingPage, CPropertyPage)
	//{{AFX_MSG_MAP(CTrimmingPage)
	ON_EN_CHANGE(IDC_PREFIXES, DoModify)
	ON_BN_CLICKED(IDC_SELECT, OnSelect)
	ON_BN_CLICKED(IDC_LIMITCHARS, DoUpdateDlgItems)
	ON_BN_CLICKED(IDC_SELECT_PREFIX_CHAR, OnSelectPrefixChar)
	ON_BN_CLICKED(IDC_SELECT_SUFFIX_CHAR, OnSelectSuffixChar)
	ON_BN_CLICKED(IDC_USELIMITCHAR, DoUpdateDlgItems)
	ON_BN_CLICKED(IDC_TRIMPREFIX, DoUpdateDlgItems)
	ON_BN_CLICKED(IDC_USEPREFIXCHAR, DoUpdateDlgItems)
	ON_BN_CLICKED(IDC_TRIMSUFFIX, DoUpdateDlgItems)
	ON_BN_CLICKED(IDC_USESUFFIXCHAR, DoUpdateDlgItems)
	ON_EN_CHANGE(IDC_SUFFIXES, DoModify)
	ON_EN_CHANGE(IDC_CHARLIMIT, DoModify)
	ON_BN_CLICKED(IDC_LIMITRESCHARS, DoModify)
	ON_BN_CLICKED(IDC_IGNOREEXT, DoModify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrimmingPage message handlers

BOOL CTrimmingPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
//    OnLimitchars();
    DoUpdateDlgItems();
	return TRUE;
}

BOOL CTrimmingPage::OnApply() 
{
    BOOL bRetVal;

    if ((bRetVal = CPropertyPage::OnApply()))
    {
        if (ChangedAny())
        {
            pGlobalActiveManager->PostUpdateMessage();
        }
    }
	
	return bRetVal;
}

void CTrimmingPage::DoModify() 
{
    SetModified();
}

void CTrimmingPage::DoUpdateDlgItems() 
{
    CWnd *pWnd;

    SetModified();
    UpdateData();

    pWnd = GetDlgItem(IDC_LIMITCHARS)->GetNextWindow();
    while (pWnd->GetDlgCtrlID() != IDC_SELECT)
    {
        pWnd->EnableWindow(m_bLimitChars);
        pWnd = pWnd->GetNextWindow();
    }                              
    pWnd->EnableWindow(m_bLimitChars  &&  m_bUseLimitChar);

    pWnd = GetDlgItem(IDC_TRIMPREFIX)->GetNextWindow();
    while (pWnd->GetDlgCtrlID() != IDC_SELECT_PREFIX_CHAR)
    {
        pWnd->EnableWindow(m_bTrimPrefix);
        pWnd = pWnd->GetNextWindow();
    }
    pWnd->EnableWindow(m_bTrimPrefix && m_bUsePrefixChar);

    pWnd = GetDlgItem(IDC_TRIMSUFFIX)->GetNextWindow();
    while (pWnd->GetDlgCtrlID() != IDC_SELECT_SUFFIX_CHAR)
    {
        pWnd->EnableWindow(m_bTrimSuffix);
        pWnd = pWnd->GetNextWindow();
    } 
    pWnd->EnableWindow(m_bTrimSuffix && m_bUseSuffixChar);
}

void CTrimmingPage::OnSelectPrefixChar() 
{
    SelectChar(m_sPrefixChar);
}

void CTrimmingPage::OnSelectSuffixChar() 
{
    SelectChar(m_sSuffixChar);
}

void CTrimmingPage::OnSelect() 
{
    SelectChar(m_sLimitCharacter);
}

void CTrimmingPage::SelectChar(CString& s)
{
    CSelectCharDialog dlg((unsigned char)s[1]);

    if (dlg.DoModal() == IDOK)
    {
        s = "'" + dlg.m_Char + "'";
        UpdateData(FALSE);
        SetModified();
    }
}



/////////////////////////////////////////////////////////////////////////////
// CWTTabCtrlPage dialog

BEGIN_HELP_IDS(CWTTabCtrlPage)
    IDC_GROUP_SEP,      IDC_GROUPTABS,

    IDC_LEFTMOST,       IDC_STATIC_DELIM,
    IDC_RIGHTMOST,      IDC_STATIC_DELIM,

    IDC_REASON,         IDH_REASON,
    ID_REGFIRST,        IDH_REASON,

    IDC_GROUPOPS,       IDH_USE_GROUP_OPS,

    IDC_DISP_DELIM,     IDH_DISP_DELIM,

    IDC_AVAILABLE,      0

END_HELP_IDS();    

CWTTabCtrlPage::CWTTabCtrlPage() : CPropertyPage(CWTTabCtrlPage::IDD)
{
    m_iHelpID = IDH_OPTPAGE_TABS_ADVANCED;

    //{{AFX_DATA_INIT(CWTTabCtrlPage)
	m_bGroupTabs = 0;
	m_bUseWTTabCtrl = 0;
	m_bGroupRes = 0;
	m_bGroupPath = 0;
	m_Period = 0;
	m_bShowGroupDelim = FALSE;
	m_bUseGroupOps = FALSE;
	m_bSortMiniTB = FALSE;
	m_bGroupPrj = FALSE;
	//}}AFX_DATA_INIT

    varpair vars[] = 
    {
        { &m_bGroupTabs,       &cfg_bGroupTabs        },        
        { &m_bUseWTTabCtrl,    &cfg_bUseWTTabCtrl     },     
        { &m_bGroupPrj,        &cfg_bGroupPrj         },
        { &m_bGroupRes,        &cfg_bGroupRes         },
        { &m_bGroupPath,       &cfg_bGroupDiffPaths   },
        { &m_Period,           &cfg_bUseRightMostDot  },
        { &m_bShowGroupDelim,  &cfg_bShowGroupDelim   },
        { &m_bUseGroupOps,     &cfg_bUseGroupOps      },
        { &m_bSortMiniTB,      &cfg_bSortMiniTB       }
    };

    InitAutoVars(countof(vars), vars);
}

void CWTTabCtrlPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWTTabCtrlPage)
	DDX_Check(pDX, IDC_GROUPTABS, m_bGroupTabs);
	DDX_Check(pDX, IDC_USEWTTABCTRL, m_bUseWTTabCtrl);
	DDX_Check(pDX, IDC_GROUPRES, m_bGroupRes);
	DDX_Check(pDX, IDC_GROUPPATH, m_bGroupPath);
	DDX_Radio(pDX, IDC_LEFTMOST, m_Period);
	DDX_Check(pDX, IDC_DISP_DELIM, m_bShowGroupDelim);
	DDX_Check(pDX, IDC_GROUPOPS, m_bUseGroupOps);
	DDX_Check(pDX, IDC_SORTMINITB, m_bSortMiniTB);
	DDX_Check(pDX, IDC_GROUPPRJ, m_bGroupPrj);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWTTabCtrlPage, CPropertyPage)
	//{{AFX_MSG_MAP(CWTTabCtrlPage)
	ON_BN_CLICKED(IDC_GROUPPATH, OnGrouptabs)
	ON_BN_CLICKED(IDC_USEWTTABCTRL, OnUsewttabctrl)
	ON_BN_CLICKED(IDC_GROUPTABS, OnGrouptabs)
	ON_BN_CLICKED(IDC_GROUPRES, DoModify)
	ON_BN_CLICKED(IDC_LEFTMOST, DoModify)
	ON_BN_CLICKED(IDC_RIGHTMOST, DoModify)
	ON_BN_CLICKED(IDC_GROUPOPS, DoModify)
	ON_BN_CLICKED(IDC_DISP_DELIM, DoModify)
	ON_BN_CLICKED(IDC_SORTMINITB, DoModify)
	ON_BN_CLICKED(IDC_GROUPPRJ, DoModify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CWTTabCtrlPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	return TRUE;
}

BOOL CWTTabCtrlPage::OnSetActive() 
{
    UpdateUsage();
	
	return CPropertyPage::OnSetActive();
}

BOOL CWTTabCtrlPage::OnApply() 
{
    BOOL bRetVal;

    // force arrangment page to update first
    COptionsSheet * const pParent = (COptionsSheet *)GetParent();
    CArrangementPage * const pPageArrangment = &pParent->m_ArrangmentPage;
    if (pPageArrangment->m_bInited  &&  !pPageArrangment->OnApply())
        return FALSE;

    if ((bRetVal = CPropertyPage::OnApply()))
    {
        if (m_bUseWTTabCtrl != (BOOL)pGlobalTabs->m_bIsWTTab  ||  
            ChangedAny())
        {
            pGlobalTabs->UpdateStyle();
        }
    }

    return bRetVal;
}

void CWTTabCtrlPage::DoModify() 
{
    SetModified();
}


void CWTTabCtrlPage::OnUsewttabctrl() 
{
    UpdateUsage();
    DoModify();
}

void CWTTabCtrlPage::UpdateUsage()
{
    if (!IsWindow(m_hWnd))
    {
        return;
    }
    
    COptionsSheet * const pParent = (COptionsSheet *)GetParent();
    CArrangementPage * const pPageArrangment = &pParent->m_ArrangmentPage;
    int iDummy = -1;
    int& o = pPageArrangment->m_bInited? 
        pPageArrangment->m_RadioOrientation : iDummy;

    UpdateData();

    CWnd *pWnd = GetDlgItem(IDC_GROUPTABS);
    const BOOL bEnable = (g_bUseWndTabsExt & m_bUseWTTabCtrl);
    while (pWnd)
    {
        pWnd->EnableWindow(bEnable);
        pWnd = pWnd->GetNextWindow();
    }

    GetDlgItem(IDC_USEWTTABCTRL)->EnableWindow(g_bUseWndTabsExt);

    if (g_bUseWndTabsExt)
    {
        if (m_bUseWTTabCtrl  &&  
            (o == (int)soLeft  ||  o == (int)soRight))
        {
            // CWTTabCtrl doesn't support vertical tabs
            if (AfxMessageBox(IDS_VERTWTTABCTRL, MB_YESNO | MB_ICONQUESTION) == IDYES)
            {
                o = (int)soBottom;
                if (pPageArrangment->m_bInited)
                    pPageArrangment->UpdateData(FALSE);
            }
            else
            {
                m_bUseWTTabCtrl = FALSE;
                if (m_bInited)
                {
                    UpdateData(FALSE);
                }
            }
        }
    }

/*    CWnd *pWnd = GetDlgItem(IDC_GROUPTABS);
    while (pWnd->GetDlgCtrlID() != ID_REGFIRST)
    {
        pWnd->EnableWindow(m_bUseWTTabCtrl);
        pWnd = pWnd->GetNextWindow();
    }
*/    
    GetDlgItem(IDC_USEWTTABCTRL)->SetFocus();
    UpdateGroupTabs();
}

void CWTTabCtrlPage::OnGrouptabs() 
{                  
    UpdateGroupTabs();
    DoModify();
}

void CWTTabCtrlPage::UpdateGroupTabs()
{
    UpdateData();
    CWnd *pWnd = GetDlgItem(IDC_GROUPTABS)->GetNextWindow();
    BOOL bEnable = m_bGroupTabs & g_bUseWndTabsExt & m_bUseWTTabCtrl;
    while (pWnd) //->GetDlgCtrlID() != IDC_TABCOLOR_SEP)
    {
        pWnd->EnableWindow(bEnable);
        pWnd = pWnd->GetNextWindow();
    }
    GetDlgItem(IDC_GROUPPRJ)->EnableWindow(bEnable & m_bGroupPath);
}


/////////////////////////////////////////////////////////////////////////////
// CWTTabCtrlPage2 dialog

BEGIN_HELP_IDS(CWTTabCtrlPage2)
    IDC_STATIC_CLOSEBTN, IDC_TAB_CLOSE_BTN,

    IDC_TABCOLOR_SEP2,   IDC_TABCOLOR_SEP,
    IDC_STATIC_REG_CLR,  IDC_TABCOLOR_SEP,
    IDC_STATIC_SEL_CLR,  IDC_TABCOLOR_SEP,
    IDC_CHANGEREG,       IDC_TABCOLOR_SEP,
    IDC_CHANGESEL,       IDC_TABCOLOR_SEP
END_HELP_IDS();    

CWTTabCtrlPage2::CWTTabCtrlPage2() : CPropertyPage(CWTTabCtrlPage2::IDD)
{
    m_iHelpID = IDH_OPTPAGE_TABS_ADVANCED;

    //{{AFX_DATA_INIT(CWTTabCtrlPage2)
	m_bTabCloseBtn = FALSE;
	m_bForceMiniTB = FALSE;
	//}}AFX_DATA_INIT

    varpair vars[] = 
    {
        { &m_bForceMiniTB,     &cfg_bWTXAllSpecial    },
        { &m_bTabCloseBtn,     &cfg_bWTXCloseButton   },
        { &m_iSelColor,        (int *)&cfg_SelTxtColor},
        { &m_iRegColor,        (int *)&cfg_RegTxtColor} 
    };

    InitAutoVars(countof(vars), vars);
}

void CWTTabCtrlPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWTTabCtrlPage2)
	DDX_Control(pDX, IDC_CHANGESEL, m_SelColor);
	DDX_Control(pDX, IDC_CHANGEREG, m_RegColor);
	DDX_Check(pDX, IDC_TAB_CLOSE_BTN, m_bTabCloseBtn);
	DDX_Check(pDX, IDC_FORCE_MINITB, m_bForceMiniTB);
	//}}AFX_DATA_MAP

    if (pDX->m_bSaveAndValidate)
    {
        m_iRegColor = m_RegColor.GetColor();
        m_iSelColor = m_SelColor.GetColor();
    }
    else
    {
        m_RegColor.SetColor(m_iRegColor);
        m_SelColor.SetColor(m_iSelColor);
    }
}


BEGIN_MESSAGE_MAP(CWTTabCtrlPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CWTTabCtrlPage2)
	ON_BN_CLICKED(IDC_CHANGESEL, DoModify)
	ON_BN_CLICKED(IDC_CHANGEREG, DoModify)
	ON_BN_CLICKED(IDC_FORCE_MINITB, DoModify)
	ON_BN_CLICKED(IDC_TAB_CLOSE_BTN, DoModify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CWTTabCtrlPage2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_SelColor.EnableOtherButton (_T("Other"));
	m_SelColor.SetColumnsNumber (10);

    m_RegColor.EnableOtherButton (_T("Other"));
	m_RegColor.SetColumnsNumber (10);
	
	return TRUE;
}

BOOL CWTTabCtrlPage2::OnSetActive() 
{
    UpdateUsage();
	
	return CPropertyPage::OnSetActive();
}

BOOL CWTTabCtrlPage2::OnApply() 
{
    BOOL bRetVal;

    // force arrangment page to update first
    COptionsSheet * const pParent = (COptionsSheet *)GetParent();
    CWTTabCtrlPage * const pPage1 = &pParent->m_WTTabCtrlPage;
    if (pPage1->m_bInited  &&  !pPage1->OnApply())
        return FALSE;

    if ((bRetVal = CPropertyPage::OnApply()))
    {
        if (ChangedAny())
        {
            pGlobalTabs->UpdateStyle();
        }
    }

    return bRetVal;
}

void CWTTabCtrlPage2::DoModify() 
{
    SetModified();
}


void CWTTabCtrlPage2::UpdateUsage()
{
    if (!IsWindow(m_hWnd))
    {
        return;
    }
    
    COptionsSheet * const pParent = (COptionsSheet *)GetParent();
    CWTTabCtrlPage * const pPage1 = &pParent->m_WTTabCtrlPage;

    UpdateData();

    const BOOL bEnable = (g_bUseWndTabsExt & pPage1->m_bUseWTTabCtrl);
    CWnd *pWnd = GetDlgItem(IDC_OTHERSTYLES);
    while (pWnd)
    {
        pWnd->EnableWindow(bEnable);
        pWnd = pWnd->GetNextWindow();
    }
}


/////////////////////////////////////////////////////////////////////////////
// CWinFileManPage property page

BEGIN_HELP_IDS(CWinFileManPage)
    IDC_WINLIMIT,                   IDC_LIMITWIN,
    IDC_WINLIMIT_TEXT,              IDC_LIMITWIN,

    IDC_WINLIMIT_DEBUG,             IDC_LIMITWIN_DEBUG,
    IDC_WINLIMIT_TEXT_DEBUG,        IDC_LIMITWIN_DEBUG,

    IDC_STATIC_AUTOCLOSE_DEBUG,     IDC_AUTOCLOSE_DEBUG,
    IDC_DIRS,                       IDC_AUTOCLOSE_DEBUG
END_HELP_IDS();    

IMPLEMENT_DYNCREATE(CWinFileManPage, CPropertyPage)

CWinFileManPage::CWinFileManPage() : CPropertyPage(CWinFileManPage::IDD)
{
    m_iHelpID = IDH_OPTPAGE_WINFILEMAN;

	//{{AFX_DATA_INIT(CWinFileManPage)
	m_iWinLimit = 0;
	m_bLimitWin = 0;
	m_bIsGroupLimit = FALSE;
	m_bAutoOpenAlt = FALSE;
	m_bLimitWinDbg = FALSE;
	m_iWinLimitDbg = 0;
	m_sDirs = _T("");
	m_bAutoCloseDbg = FALSE;
	//}}AFX_DATA_INIT

    varpair vars[] =
    {
    	{ &m_iWinLimit,         (int *)&cfg_iWindowLimit     },
        { &m_iWinLimitDbg,      (int *)&cfg_iWindowLimitDbg  },
    	{ &m_bLimitWin,         &cfg_bUseWindowLimit         },
        { &m_bLimitWinDbg,      &cfg_bUseWindowLimitDbg      },
        { &m_bAutoCloseDbg,     &cfg_bAutoCloseDbgWins       },
        { &m_bIsGroupLimit,     &cfg_bLimitGroups            },
        { &m_bAutoOpenAlt,      &cfg_bAutoOpenAlt            }
    };

    strpair strs[] =
    {
        { &m_sDirs,             &cfg_sAutoCloseDirsDbg       }
    };

    InitAutoVars(countof(vars), vars);
    InitAutoStrs(countof(strs), strs);
}

CWinFileManPage::~CWinFileManPage()
{
}

void CWinFileManPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWinFileManPage)
	DDX_Control(pDX, IDC_DIROPTIONS, m_DirOptions);
	DDX_Text(pDX, IDC_WINLIMIT, m_iWinLimit);
	DDV_MinMaxInt(pDX, m_iWinLimit, 1, 1000);
	DDX_Text(pDX, IDC_WINLIMIT_DEBUG, m_iWinLimitDbg);
	DDV_MinMaxInt(pDX, m_iWinLimitDbg, 1, 1000);
	DDX_Check(pDX, IDC_LIMITWIN, m_bLimitWin);
	DDX_Check(pDX, IDC_LIMITGROUPS, m_bIsGroupLimit);
	DDX_Check(pDX, IDC_AUTOOPENALT, m_bAutoOpenAlt);
	DDX_Check(pDX, IDC_LIMITWIN_DEBUG, m_bLimitWinDbg);
	DDX_Text(pDX, IDC_DIRS, m_sDirs);
	DDX_Check(pDX, IDC_AUTOCLOSE_DEBUG, m_bAutoCloseDbg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWinFileManPage, CPropertyPage)
	//{{AFX_MSG_MAP(CWinFileManPage)
	ON_BN_CLICKED(IDC_AUTOOPENALT, DoModify)
	ON_BN_CLICKED(IDC_DIRPICKER, OnDirpicker)
	ON_BN_CLICKED(IDC_LIMITWIN, DoUpdateDlgItems)
	ON_BN_CLICKED(IDC_DIROPTIONS, OnDiroptions)
	ON_BN_CLICKED(IDC_AUTOCLOSE_DEBUG, DoUpdateDlgItems)
	ON_BN_CLICKED(IDC_USE_WWHIZ, DoModify)
	ON_EN_CHANGE(IDC_WINLIMIT, DoModify)
	ON_BN_CLICKED(IDC_OPEN, DoModify)
	ON_BN_CLICKED(IDC_EXPLORE, DoModify)
	ON_EN_CHANGE(IDC_DIRS, DoModify)
	ON_BN_CLICKED(IDC_LIMITWIN_DEBUG, DoUpdateDlgItems)
	ON_EN_CHANGE(IDC_WINLIMIT_DEBUG, DoUpdateDlgItems)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinFileManPage message handlers

BOOL CWinFileManPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
    DoUpdateDlgItems();

    m_MenuDirOptions.LoadMenu(IDR_DIR_OPTIONS);
    m_DirOptions.m_hMenu = m_MenuDirOptions.GetSubMenu(0)->m_hMenu;
    m_DirOptions.m_bStayPressed = TRUE;

	return TRUE;
}

BOOL CWinFileManPage::OnApply() 
{
    BOOL bRetVal;

    if ((bRetVal = CPropertyPage::OnApply()))
    {
        if (Changed(m_sDirs))
        {
            g_pDevStudioWnd->m_sCloseDebWndPath.Empty();
        }
    }

    return bRetVal;
}

void CWinFileManPage::DoModify() 
{
    SetModified();
}


void CWinFileManPage::OnDirpicker() 
{
    if (UpdateData())
    {
        BROWSEINFO bi;
        char path[MAX_PATH];
        bi.hwndOwner = m_hWnd;
        bi.pszDisplayName = path;
        bi.pidlRoot = NULL;
        bi.ulFlags = BIF_RETURNONLYFSDIRS;
        bi.lpszTitle = "Please select a directory";
        bi.lpfn = NULL;
        CPIDL pidl = SHBrowseForFolder(&bi);
        if (pidl.m_pidl != NULL)
        {
            SHGetPathFromIDList(pidl, path);
            if (!m_sDirs.IsEmpty()) m_sDirs += ";";
            m_sDirs += path;
            UpdateData(FALSE);
        };
    }
}

void CWinFileManPage::DoUpdateDlgItems() 
{
    if (UpdateData())
    {
        GetDlgItem(IDC_WINLIMIT)           ->EnableWindow(m_bLimitWin);
        GetDlgItem(IDC_WINLIMIT_TEXT)      ->EnableWindow(m_bLimitWin);
        GetDlgItem(IDC_WINLIMIT_DEBUG)     ->EnableWindow(m_bLimitWinDbg);
        GetDlgItem(IDC_WINLIMIT_TEXT_DEBUG)->EnableWindow(m_bLimitWinDbg);

        GetDlgItem(IDC_LIMITGROUPS)->EnableWindow(g_bUseWndTabsExt);

        GetDlgItem(IDC_DIRS)     ->EnableWindow(m_bAutoCloseDbg);
        GetDlgItem(IDC_DIRPICKER)->EnableWindow(m_bAutoCloseDbg);
        m_DirOptions.EnableWindow(m_bAutoCloseDbg);

        SetModified();
    }
}

void CWinFileManPage::OnDiroptions() 
{
    char *pszToAdd = NULL;

    if (!UpdateData())
        return;

    switch (m_DirOptions.m_nMenuResult)
    {
        case IDC_DS_INCLUDE_PATH:
            pszToAdd = PATH_DS_INCLUDE;
            break;

        case IDC_DS_LIB_PATH:
            pszToAdd = PATH_DS_LIB;
            break;

        case IDC_DS_SOURCE_PATH:
            pszToAdd = PATH_DS_SOURCE;
            break;

        case IDC_DS_EXEC_PATH:
            pszToAdd = PATH_DS_EXEC;
            break;

        case IDC_WORKSPACE_DIR:
            pszToAdd = PATH_WORKSPACE;
            break;

        case IDC_ACTIVE_PROJ_DIR:
            pszToAdd = PATH_ACTIVE_PRJ;
            break;

        case IDC_ALL_PRJS_DIR:
            pszToAdd = PATH_ALL_PRJS;
            break;

        DEFAULT_UNREACHABLE;
    }

    if (pszToAdd)
    {
        if (!m_sDirs.IsEmpty()) m_sDirs += ";";
        m_sDirs += pszToAdd;
        UpdateData(FALSE);
        SetModified();
    }
}



/////////////////////////////////////////////////////////////////////////////
// CCustomizePage property page

IMPLEMENT_DYNCREATE(CCustomizePage, CPropertyPage)

CCustomizePage::CCustomizePage() : CPropertyPage(CCustomizePage::IDD)
{
	//{{AFX_DATA_INIT(CCustomizePage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCustomizePage::~CCustomizePage()
{
}

void CCustomizePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomizePage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomizePage, CPropertyPage)
	//{{AFX_MSG_MAP(CCustomizePage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomizePage message handlers

BOOL CCustomizePage::OnSetActive() 
{
    COptionsSheet *pParent = ((COptionsSheet *)GetParent());
    pParent->SetActivePage(&pParent->m_MenusPage);
    return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CMenusPage dialog

BEGIN_HELP_IDS(CMenusPage)
    IDC_STATIC_ACCESSCONTEXTMENU2,  IDC_STATIC_ACCESSCONTEXTMENU,
    IDC_STATIC_ACCESSCONTEXTMENU3,  IDC_STATIC_ACCESSCONTEXTMENU,
    IDC_CONTROL,                    IDC_STATIC_ACCESSCONTEXTMENU,
    IDC_SHIFT,                      IDC_STATIC_ACCESSCONTEXTMENU
END_HELP_IDS();    

CMenusPage::CMenusPage() : CPropertyPage(CMenusPage::IDD)
{
    m_iHelpID = IDH_OPTPAGE_CUST_MENUS;

	//{{AFX_DATA_INIT(CMenusPage)
	m_ShellKey = 0;
	m_bCascadingAddons = FALSE;
	m_bSuppressNoCmd = FALSE;
	//}}AFX_DATA_INIT

    m_cfgiShellKey = (cfg_iShellKey == VK_CONTROL? 0 : 1);

    varpair vars[] =
    {
    	{ &m_ShellKey,         &m_cfgiShellKey          },
        { &m_bCascadingAddons, &cfg_bCascadingAddons    },
        { &m_bSuppressNoCmd,   &cfg_bSupressNoCmdAddons }
    };

    InitAutoVars(countof(vars), vars);
}


void CMenusPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMenusPage)
	DDX_Control(pDX, IDC_TOOLBAR_CUST, m_btnCreateVCToolbar);
	DDX_Control(pDX, IDC_CUSTOMIZE_WT_TOOLBAR, m_btnCustomizeWTToolbar);
	DDX_Control(pDX, IDC_CUSTOMIZE_CONTEXT_MENU_GROUPS, m_btnCustomizeContextMenuGroups);
	DDX_Control(pDX, IDC_CUSTOMIZE_CONTEXT_MENU, m_btnCustomizeContextMenu);
	DDX_Radio(pDX, IDC_CONTROL, m_ShellKey);
	DDX_Check(pDX, IDC_CASCADINGADDONS, m_bCascadingAddons);
	DDX_Check(pDX, IDC_SUPRESS_NOCMD, m_bSuppressNoCmd);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMenusPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMenusPage)
	ON_BN_CLICKED(IDC_SHIFT, DoModify)
	ON_BN_CLICKED(IDC_CASCADINGADDONS, DoEnableDisable)
	ON_BN_CLICKED(IDC_CUSTOMIZE_WT_TOOLBAR, OnCustomizeWtToolbar)
	ON_BN_CLICKED(IDC_CUSTOMIZE_CONTEXT_MENU, OnCustomizeContextMenu)
	ON_BN_CLICKED(IDC_CUSTOMIZE_CONTEXT_MENU_GROUPS, OnCustomizeContextMenuGroups)
	ON_BN_CLICKED(IDC_TOOLBAR_CUST, OnToolbarCust)
	ON_BN_CLICKED(IDC_CONTROL, DoModify)
	ON_BN_CLICKED(IDC_SUPRESS_NOCMD, DoModify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CMenusPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

    m_btnCustomizeWTToolbar.SetImage(IDB_CUSTOMIZE2);
    m_btnCustomizeContextMenu.SetImage(IDB_CUSTOMIZE2);
    m_btnCustomizeContextMenu.SetImage(IDB_CUSTOMIZE2);
    m_btnCreateVCToolbar.SetImage(IDB_TOOLBAR_PIC);

    DoEnableDisable();
	
	return TRUE;
}

BOOL CMenusPage::OnApply() 
{
    BOOL bRetVal;

    if ((bRetVal = CPropertyPage::OnApply()))
    {
        cfg_iShellKey = ((m_cfgiShellKey == 0)? VK_CONTROL : VK_SHIFT);
    }
    
    return bRetVal;
}

void CMenusPage::DoModify() 
{
    SetModified();
}

void CMenusPage::DoEnableDisable() 
{
    UpdateData();
    GetDlgItem(IDC_SUPRESS_NOCMD)->EnableWindow(m_bCascadingAddons);
    SetModified();
}

static void CopyMenu(CMenu *pDest, CMenu *pSource, const bool bFirst = false)
{
    char buf[1024];
    MENUITEMINFO mii;

    const int iCount = pSource->GetMenuItemCount();
    int iSubMenu = -2, iLastCfg = 2;
    
    for (int i = 0; i < iCount; ++i)
    {
        mii.cbSize = sizeof(mii);
        mii.fMask = MIIM_ID | MIIM_STATE | MIIM_SUBMENU | MIIM_TYPE;
        mii.cch = sizeof(buf);
        mii.dwTypeData = (LPSTR)buf;
        pSource->GetMenuItemInfo(i, &mii, TRUE);
        if (mii.hSubMenu)
        {
            ++iSubMenu;
            if (bFirst  &&  iSubMenu >= 0)
            {
                int MenuCfgs[] = { cfg_iMenuWinMan, cfg_iMenuFileMan,
                    cfg_iMenuClip, cfg_iMenuDS };
                WT_ASSERT(iSubMenu < countof(MenuCfgs));
                if (MenuCfgs[iSubMenu] == 0)  // remove the submenu
                {
//                  iLastCfg = 0;
                    continue;
                }
                if (MenuCfgs[iSubMenu] == 1)  // inline the submenu
                {
                    if (i != 0)
                    {
                        pDest->AppendMenu(MF_SEPARATOR);
                    }
                    iLastCfg = 1;
                    CopyMenu(pDest, CMenu::FromHandle(mii.hSubMenu));
                    continue;
                }
                if (iLastCfg != 2)
                {
                    pDest->AppendMenu(MF_SEPARATOR);
                }
                iLastCfg = 2;  // cascading submenu
            }
            HMENU hMenuNew = ::CreatePopupMenu();
            pDest->AppendMenu(MF_POPUP, (UINT)hMenuNew, buf);
            CopyMenu(CMenu::FromHandle(hMenuNew), 
                CMenu::FromHandle(mii.hSubMenu));
        }
        else
        {
            if (mii.fType & MFT_SEPARATOR)
            {
                pDest->AppendMenu(MF_SEPARATOR, mii.wID);
            }
            else
            {
                WT_ASSERT(mii.fType == MFT_STRING);
                pDest->AppendMenu(MF_STRING, mii.wID, buf);
            }
        }
    }

}

// destroy the contents of a submenu
static void ClearMenu(HMENU hMenu)
{
    MENUITEMINFO mii;
    mii.cbSize = sizeof(mii);
    mii.fMask = MIIM_SUBMENU;

    for (int i = ::GetMenuItemCount(hMenu) - 1; i >= 0; --i)
    {
        ::GetMenuItemInfo(hMenu, i, TRUE, &mii);
        if (mii.hSubMenu)
        {
            ::DestroyMenu(mii.hSubMenu);
        }
        ::RemoveMenu(hMenu, i, MF_BYPOSITION);
    }
}

void CMenusPage::OnCustomizeWtToolbar() 
{
    ((COptionsSheet *)GetParent())->PostMessage(WM_COMMAND, IDC_CUSTOMIZE);
}

void CMenusPage::OnCustomizeContextMenu() 
{
    ((COptionsSheet *)GetParent())->PostMessage(WM_COMMAND, IDC_CUSTOMIZE);
}

void CMenusPage::OnCustomizeContextMenuGroups() 
{
    CCustomizeCtxMenuDlg dlg;
    
    if (dlg.DoModal() != IDOK)
    {
        return;
    }

    cfg_iMenuClip    = dlg.m_MenuClip;
	cfg_iMenuDS      = dlg.m_MenuDS;
	cfg_iMenuFileMan = dlg.m_MenuFM;
	cfg_iMenuWinMan  = dlg.m_MenuWM;
	ResetMenusFromConfig();
}

void CMenusPage::ResetMenu(LPCTSTR pszMenuName, CMenu *pPopup)
{
    CBCGContextMenuManager& mgr = *theApp.GetContextMenuManager();
    unsigned uiResID;

    HMENU hMenu = mgr.GetMenuByName(pszMenuName, &uiResID);
    WT_ASSERT(hMenu != NULL);
    if (hMenu == NULL)
    {
        WT_L1_TRACE("Could not find menu %s", pszMenuName);
        AfxMessageBox("Could not find menu handle.", MB_OK | MB_ICONSTOP);
        return;
    }

    HMENU hOldPopup = ::GetSubMenu (hMenu, 0);
    WT_ASSERT(hOldPopup != NULL);
    if (hOldPopup == NULL)
    {
        AfxMessageBox("Could not find popup menu handle.", 
            MB_OK | MB_ICONSTOP);
        return;
    }
    WT_L2_TRACE("Clearing popup menu");
    ClearMenu(hOldPopup);

    WT_L2_TRACE("Performing menu copy");
    CopyMenu(CMenu::FromHandle(hOldPopup), pPopup, true);

    mgr.ResyncMenu(uiResID);
}

void CMenusPage::ResetMenusFromConfig()
{
	CString cStrName;
	cStrName.LoadString(IDS_TAB_CONTEXT_MENU_NAME);

    CMenu menu, *pPopup;
    menu.LoadMenu(IDR_POPUP);
    pPopup = menu.GetSubMenu(0);

    ResetMenu(cStrName, pPopup);
}

void CMenusPage::OnToolbarCust() 
{
    CToolbarSetup dlg;
    dlg.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CMiscPage property page

BEGIN_HELP_IDS(CMiscPage)
    IDC_USE_WWHIZ,                  IDH_USE_WWHIZ,

    IDC_OPEN,                       IDC_STATIC_OCF_CMD,
    IDC_EXPLORE,                    IDC_STATIC_OCF_CMD
END_HELP_IDS()

CMiscPage::CMiscPage() : CPropertyPage(CMiscPage::IDD)
{
    m_iHelpID = IDH_OPTPAGE_GENERAL;

	//{{AFX_DATA_INIT(CMiscPage)
	m_iOpenMethod = -1;
	m_bUseWWhiz = 0;
	m_bShowAttribs = 0;
	m_bRTFCopy = FALSE;
	m_bDisableSplash = FALSE;
	//}}AFX_DATA_INIT

    varpair vars[] =
    {
        { &m_bUseWWhiz,         &cfg_bUseWorkspaceUtils      },
        { &m_iOpenMethod,       &cfg_bOpenFolderUseExplore   },
    	{ &m_bShowAttribs,      &cfg_bShowAttribsTT          },
        { &m_bRTFCopy,          &cfg_bUseVA_RTF              },
        { &m_bDisableSplash,    &cfg_bDisableSplash          }
    };

    InitAutoVars(countof(vars), vars);
}

void CMiscPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMiscPage)
	DDX_Radio(pDX, IDC_OPEN, m_iOpenMethod);
	DDX_Check(pDX, IDC_USE_WWHIZ, m_bUseWWhiz);
	DDX_Check(pDX, IDC_SHOWATTRIBS, m_bShowAttribs);
	DDX_Check(pDX, IDC_RTFCOPY, m_bRTFCopy);
	DDX_Check(pDX, IDC_SPLASH, m_bDisableSplash);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMiscPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMiscPage)
	ON_BN_CLICKED(IDC_SHOWATTRIBS, DoModify)
	ON_BN_CLICKED(IDC_RESET_SHOWONCE, OnResetShowonce)
	ON_BN_CLICKED(IDC_RTFCOPY, DoModify)
	ON_BN_CLICKED(IDC_SPLASH, DoModify)
	ON_BN_CLICKED(IDC_USE_WWHIZ, DoModify)
	ON_BN_CLICKED(IDC_OPEN, DoModify)
	ON_BN_CLICKED(IDC_EXPLORE, DoModify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CMiscPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	return TRUE;
}

BOOL CMiscPage::OnApply() 
{
    return CPropertyPage::OnApply();
}

BOOL CMiscPage::OnSetActive() 
{
    GetDlgItem(IDC_SPLASH)->EnableWindow(GetExtensionsActive());
	
	return CPropertyPage::OnSetActive();
}

void CMiscPage::DoModify() 
{
    SetModified();
}

void CMiscPage::OnResetShowonce() 
{
    cfg_bShowWWhizFlipWarn   =
    cfg_bShowKeyBindingsWarn =
    cfg_bShowAddonWTXInfo    =
    cfg_bShowMultiUseReg     = TRUE;   

    AfxMessageBox(IDS_WARNINGS_RESET, MB_OK | MB_ICONINFORMATION);
}

/////////////////////////////////////////////////////////////////////////////
// CKeyboardPage property page

IMPLEMENT_DYNCREATE(CKeyboardPage, CPropertyPage)

BEGIN_HELP_IDS(CKeyboardPage)
    IDC_BACKFORWARD_IGNORE,     IDC_STATIC_INET_KBD,
    IDC_BACKFORWARD_CTRLTAB,    IDC_STATIC_INET_KBD,
    IDC_BACKFORWARD_CYCLEGROUP, IDC_STATIC_INET_KBD,
    IDC_BACKFORWARD_TABORDER,   IDC_STATIC_INET_KBD
END_HELP_IDS()

CKeyboardPage::CKeyboardPage() : CPropertyPage(CKeyboardPage::IDD)
{
    m_iHelpID = IDH_OPTPAGE_CUST_KBD;

	//{{AFX_DATA_INIT(CKeyboardPage)
	m_bStopButton = FALSE;
	m_iBackForward = -1;
	//}}AFX_DATA_INIT

    varpair vars[] = 
    {
        { &m_bStopButton,  &cfg_bInetKbdStopBuilds  },
        { &m_iBackForward, &cfg_iInetKbdBackForward }
    };

    InitAutoVars(countof(vars), vars);
}

CKeyboardPage::~CKeyboardPage()
{
}

void CKeyboardPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKeyboardPage)
	DDX_Control(pDX, IDC_KEYBOARD_CUST_TAB_ACTIVATION, m_btnTabActivation);
	DDX_Control(pDX, IDC_KEYBOARD_CUST_BCG, m_btnAnyCommand);
	DDX_Control(pDX, IDC_KEYBOARD_CUST, m_btnCommonCommands);
	DDX_Check(pDX, IDC_STOP_BUTTON, m_bStopButton);
	DDX_Radio(pDX, IDC_BACKFORWARD_IGNORE, m_iBackForward);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKeyboardPage, CPropertyPage)
	//{{AFX_MSG_MAP(CKeyboardPage)
	ON_BN_CLICKED(IDC_KEYBOARD_CUST_TAB_ACTIVATION, OnKeyboardCustTabActivation)
	ON_BN_CLICKED(IDC_KEYBOARD_CUST_BCG, OnKeyboardCustBcg)
	ON_BN_CLICKED(IDC_KEYBOARD_CUST, OnKeyboardCust)
	ON_BN_CLICKED(IDC_STOP_BUTTON, DoModify)
	ON_BN_CLICKED(IDC_BACKFORWARD_IGNORE, DoModify)
	ON_BN_CLICKED(IDC_BACKFORWARD_CTRLTAB, DoModify)
	ON_BN_CLICKED(IDC_BACKFORWARD_CYCLEGROUP, DoModify)
	ON_BN_CLICKED(IDC_BACKFORWARD_TABORDER, DoModify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeyboardPage message handlers

BOOL CKeyboardPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
    m_btnCommonCommands.SetImage(IDB_KEYBOARD);
    m_btnTabActivation.SetImage(IDB_TABACTIVATE);
    m_btnAnyCommand.SetImage(IDB_CUSTOMIZE2);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CKeyboardPage::DoModify() 
{
    SetModified();
}

void CKeyboardPage::OnKeyboardCustTabActivation() 
{
    CTabActivationShortcutsDlg dlg;
    dlg.DoModal();
}

void CKeyboardPage::OnKeyboardCustBcg() 
{
    ((COptionsSheet *)GetParent())->PostMessage(WM_COMMAND, IDC_CUSTOMIZE);
}

void CKeyboardPage::OnKeyboardCust() 
{
    CShortcutsDlg dlg;
    dlg.DoModal();
}



/////////////////////////////////////////////////////////////////////////////
// CMousePage property page

IMPLEMENT_DYNCREATE(CMousePage, CPropertyPage)

BEGIN_HELP_IDS(CMousePage)
    IDC_ACCESSCONTEXTMENU,          IDC_STATIC_ACCESSCONTEXTMENU,
    IDC_STATIC_ACCESSCONTEXTMENU3,  IDC_STATIC_ACCESSCONTEXTMENU,

    IDC_STATIC_MIDBTN,              IDC_MIDBTN
END_HELP_IDS()

CMousePage::CMousePage() : CPropertyPage(CMousePage::IDD)
{
    m_iHelpID = IDH_OPTPAGE_CUST_MOUSE;

	//{{AFX_DATA_INIT(CMousePage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

    varpair vars[] = 
    {
        { &m_iMidBtnCommand, (int *)&cfg_iMidBtnCommand },
    };

    InitAutoVars(countof(vars), vars);
}

CMousePage::~CMousePage()
{
}

void CMousePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMousePage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMousePage, CPropertyPage)
	//{{AFX_MSG_MAP(CMousePage)
	ON_BN_CLICKED(IDC_SET_ACCESSCONTEXTMENU, OnSetAccesscontextmenu)
	ON_BN_CLICKED(IDC_ASSIGN_MIDBTN, OnAssignMidbtn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMousePage message handlers

void CMousePage::OnSetAccesscontextmenu() 
{
    COptionsSheet *pParent = ((COptionsSheet *)GetParent());
    pParent->SetActivePage(&pParent->m_MenusPage);
}

BOOL CMousePage::OnSetActive() 
{
    COptionsSheet * const pParent = (COptionsSheet *)GetParent();
	CMenusPage &menusPage = pParent->m_MenusPage;
	if (menusPage.m_hWnd)
	{
		menusPage.UpdateData();

		CString cStrShellKeyOpt;
		if (menusPage.m_ShellKey == 0)
		{
			cStrShellKeyOpt.LoadString(IDS_CONTROL_KEY_NAME);
		}
		else
		{
			cStrShellKeyOpt.LoadString(IDS_SHIFT_KEY_NAME);
		}
		GetDlgItem(IDC_ACCESSCONTEXTMENU)->SetWindowText(cStrShellKeyOpt);
	}

    UpdateMidBtnCommand();

	return TRUE;
}

void CMousePage::OnAssignMidbtn() 
{
    CCmdSelDialog dlg;
    if (dlg.DoModal())
    {
        m_iMidBtnCommand = dlg.m_iCurrCommandID;
        UpdateMidBtnCommand();
        SetModified();
    }
}

void CMousePage::UpdateMidBtnCommand()
{
    CString strCommand;
    CFrameWnd *pFrame = (CFrameWnd *)g_pMainFrame;
	pFrame->GetMessageString(m_iMidBtnCommand, strCommand);
    GetDlgItem(IDC_MIDBTN)->SetWindowText(strCommand);
}


/////////////////////////////////////////////////////////////////////////////
// CLanguagePage property page

IMPLEMENT_DYNCREATE(CLanguagePage, CPropertyPage)

CLanguagePage::CLanguagePage() : CPropertyPage(CLanguagePage::IDD)
{
    m_iHelpID = IDH_OPTPAGE_LANGUAGES;

	//{{AFX_DATA_INIT(CLanguagePage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

    strpair strs[] =
    {
        { &m_sLangDLL, &cfg_sLangDLL }
    };

    InitAutoStrs(countof(strs), strs);
}

CLanguagePage::~CLanguagePage()
{
}

void CLanguagePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLanguagePage)
	DDX_Control(pDX, IDC_COMBO_LANG, m_Languages);
	DDX_Control(pDX, IDC_HYPERLINK_LANGUAGES, m_Hyperlink);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLanguagePage, CPropertyPage)
	//{{AFX_MSG_MAP(CLanguagePage)
	ON_CBN_SELCHANGE(IDC_COMBO_LANG, OnSelchangeComboLang)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLanguagePage message handlers

BOOL CLanguagePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

    int iSel = 0;
    for (int i = 0; i < theApp.m_LangDLLs.GetSize(); ++i)
    {
        CLanguageDLL& dll = theApp.m_LangDLLs[i];
        int ndx = m_Languages.AddString(dll.m_sLanguageNameEnglish + "\t" + 
            dll.m_sLanguageNameNative);
        m_Languages.SetItemData(ndx, i);
        if (dll.m_sDLLName == m_sLangDLL)
        {
            iSel = i;
        }
    }
    m_Languages.SetCurSel(iSel);

    OnSelchangeComboLang();  // update author name
	
    return TRUE;
}

void CLanguagePage::OnSelchangeComboLang() 
{
    CLanguageDLL& dll = theApp.m_LangDLLs[m_Languages.GetCurSel()];
    m_sLangDLL = dll.m_sDLLName;
    GetDlgItem(IDC_STATIC_LANG_AUTHOR)->SetWindowText(dll.m_sAuthor);
    SetModified();
}
           

const int ENG_LANG_NAME_WIDTH = 130;

void CLanguagePage::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDIS) 
{
    if (nIDCtl == IDC_COMBO_LANG)
    {
	    WT_ASSERT(lpDIS->CtlType == ODT_COMBOBOX);

	    CLanguageDLL& dll = theApp.m_LangDLLs[lpDIS->itemData];
        CDC *pDC = CDC::FromHandle(lpDIS->hDC);

        CRect r = lpDIS->rcItem;

        COLORREF crBck, crTxt;
        if (lpDIS->itemState & ODS_SELECTED)
        {
            crBck = GetSysColor(COLOR_HIGHLIGHT);
            crTxt = GetSysColor(COLOR_HIGHLIGHTTEXT);
        }
        else
        {
            crBck = GetSysColor(COLOR_WINDOW);
            crTxt = GetSysColor(COLOR_WINDOWTEXT);
        }

        pDC->FillSolidRect(r, crBck);
        pDC->SetTextColor(crTxt);
        pDC->SetBkMode(TRANSPARENT);

        r.right = ENG_LANG_NAME_WIDTH;
        pDC->DrawText(dll.m_sLanguageNameEnglish, r, 
            DT_SINGLELINE | DT_VCENTER);

        if (dll.m_sLanguageNameNative != dll.m_sLanguageNameEnglish)
        {
            r = lpDIS->rcItem;
            r.left = ENG_LANG_NAME_WIDTH;    
            CFont *pFontOld, fontLang;
            fontLang.CreatePointFont(dll.m_iFontPoint, dll.m_sFont, pDC);
            pFontOld = pDC->SelectObject(&fontLang);
            pDC->DrawText(dll.m_sLanguageNameNative, r, 
                DT_SINGLELINE | DT_VCENTER);
            pDC->SelectObject(pFontOld);
        }
    }
    else
    {
    	CPropertyPage::OnDrawItem(nIDCtl, lpDIS);
    }
}

void CLanguagePage::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMIS) 
{
    if (nIDCtl == IDC_COMBO_LANG)
    {
	    WT_ASSERT(lpMIS->CtlType == ODT_COMBOBOX);

        if (lpMIS->itemID == (unsigned)-1) return;
	    CLanguageDLL& dll = theApp.m_LangDLLs[lpMIS->itemID];

        CDC *pDC = /*m_Languages.*/GetDC();
        CFont *pFontOld, fontLang;
        fontLang.CreatePointFont(dll.m_iFontPoint, dll.m_sFont, pDC);
        pFontOld = pDC->SelectObject(&fontLang);
        CSize sz = pDC->GetTextExtent(dll.m_sLanguageNameNative);
        lpMIS->itemWidth  = ENG_LANG_NAME_WIDTH + sz.cx;
        lpMIS->itemHeight = max(20, sz.cy);

        pDC->SelectObject(pFontOld);
        /*m_Languages.*/ReleaseDC(pDC);
    }
    else
    {
        CPropertyPage::OnMeasureItem(nIDCtl, lpMIS);
    }
}


BOOL CLanguagePage::OnApply() 
{
    BOOL bRetVal;

    if ((bRetVal = CPropertyPage::OnApply()))
    {
        if (Changed(m_sLangDLL))
        {
            CString cStrOldCtxMenuName;
	        cStrOldCtxMenuName.LoadString(IDS_TAB_CONTEXT_MENU_NAME);
            CLanguageDLL *pDLL = theApp.GetLanguageDLL(m_sLangDLL);
            if (pDLL)
            {
                if (!pDLL->Apply())
                {
                    pDLL = NULL;
                }
            }
            if (pDLL == NULL)
            {
                CString msg;
                AfxFormatString1(msg, IDS_ERR_LANG_CANT_LOAD, m_sLangDLL);
                AfxMessageBox(msg, MB_OK | MB_ICONEXCLAMATION);
                cfg_sLangDLL = m_sLangDLL = "";
                VERIFY(theApp.m_LangDLLs[0].Apply());
            }

            CString cStrNewCtxMenuName;
	        cStrNewCtxMenuName.LoadString(IDS_TAB_CONTEXT_MENU_NAME);
            CBCGContextMenuManager& mgr = *theApp.GetContextMenuManager();
            if (cStrOldCtxMenuName != cStrNewCtxMenuName)
            {
                mgr.RenameMenu(cStrOldCtxMenuName, cStrNewCtxMenuName);
            }

            // this is already in the new language :)
			if (AfxMessageBox(IDS_LANG_RESET_MENUS, 
				MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				CMenusPage::ResetMenusFromConfig();

                CMenu menu, *pPopup;
                menu.LoadMenu(IDR_CLOSEBTN);
                pPopup = menu.GetSubMenu(0);
                CMenusPage::ResetMenu(MENU_NAME_CLOSE_BTN, pPopup);

                AfxMessageBox(IDS_LANG_RESTART, 
                    MB_OK | MB_ICONINFORMATION);

                g_bResetLanguage = true;
			}
        }
    }

    return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
// CRegistrationPage property page

IMPLEMENT_DYNCREATE(CRegistrationPage, CPropertyPage)

BEGIN_HELP_IDS(CRegistrationPage)
    IDC_STATIC_THANKYOU, 0,
    ID_REG_NAME,         0,
    IDC_STATIC_REG,      0
END_HELP_IDS()

CRegistrationPage::CRegistrationPage() : CPropertyPage(CRegistrationPage::IDD)
{
    m_iHelpID = IDH_OPTPAGE_REGISTRATION;

	//{{AFX_DATA_INIT(CRegistrationPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CRegistrationPage::~CRegistrationPage()
{
}

void CRegistrationPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegistrationPage)
	DDX_Control(pDX, IDC_STOPTRIAL, m_StopTrialBtn);
	DDX_Control(pDX, IDC_BEGINTRIAL, m_TrialBtn);
	DDX_Control(pDX, IDC_ENTER_KEY, m_KeyBtn);
	DDX_Control(pDX, IDC_REGISTER, m_RegBtn);
	DDX_Control(pDX, IDC_INFO_WTX, m_IntoBtn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegistrationPage, CPropertyPage)
	//{{AFX_MSG_MAP(CRegistrationPage)
	ON_BN_CLICKED(IDC_INFO_WTX, OnInfo)
	ON_BN_CLICKED(IDC_REGISTER, OnRegister)
	ON_BN_CLICKED(IDC_ENTER_KEY, OnEnterKey)
	ON_BN_CLICKED(IDC_BEGINTRIAL, OnBegintrial)
	ON_BN_CLICKED(IDC_STOPTRIAL, OnStoptrial)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegistrationPage message handlers

BOOL CRegistrationPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

    m_TrialBtn.    SetImage(IDB_OK);
    m_StopTrialBtn.SetImage(IDB_CANCEL);
    m_IntoBtn.     SetImage(IDB_INFO2);
    m_RegBtn.      SetImage(IDB_MENUBUTTON16);
    m_KeyBtn.      SetImage(IDB_KEY);

	return TRUE;
}


BOOL CRegistrationPage::OnSetActive() 
{
    CheckExt();
	return CPropertyPage::OnSetActive();
}

void CRegistrationPage::OnInfo() 
{
    ShowHTMLHelp(m_hWnd, IDH_WNDTABSEXT);
}

void CRegistrationPage::OnRegister() 
{
    CString cStr, url;
    url.LoadString(IDS_WWW_REG);
    AfxFormatString1(cStr, IDS_GOTOREG, url);
    if (AfxMessageBox(cStr, MB_OKCANCEL | MB_ICONINFORMATION) == IDOK)
    {
        CHyperLink::GotoURL(url, SW_SHOW);
    }
}

void CRegistrationPage::OnEnterKey() 
{
    if (ActivateExtensions(1))
    {
        SetModified();
    }
    CheckExt();
}

void CRegistrationPage::OnBegintrial() 
{
    if (ActivateExtensions(2))
    {
        SetModified();
    }
    CheckExt();
}


void CRegistrationPage::OnStoptrial() 
{
    if (AfxMessageBox(IDS_CONFIRM_STOP_TRIAL, MB_YESNO | MB_ICONQUESTION) == IDYES)
    {
        HKEY hKey;
        if (RegOpenKey(HKEY_LOCAL_MACHINE, "Software\\WndTabsExt", &hKey) ==
            ERROR_SUCCESS)
        {
            RegDeleteValue(hKey, "UserName");
            RegCloseKey(hKey);
        }
        AfxMessageBox(IDS_RESTART);
    }
}

void CRegistrationPage::CheckExt()
{
    CWaitCursor wc;
    int         iErr = 0;

    UpdateData();

    if (!GetExtensionsInited())
    {
        // try to reload the extensions
        InitExtensions();
        iErr = GetExtensionsErr();
    }

    if (iErr == 0  &&  !GetExtensionsActive())
    {
        // try to reactivate
        ActivateExtensions();
        iErr = GetExtensionsErr();
        if (iErr == 0)
        {
            SetModified();
        }
    }

    if (!g_sRegUserName.IsEmpty())
    {
        CString cStr;
        cStr.LoadString(IDS_THANKYOU);
//        GetDlgItem(IDC_AVAILABLE)->SetWindowText(cStr);
    }

    const bool bRegErr = (iErr == IDS_XERR_REGISTRATION);

    // hide/show regular stuff
    CWnd *pWnd = GetDlgItem(IDC_STATIC_THANKYOU);
    do 
    {
        pWnd->ShowWindow(iErr == 0?  SW_SHOW : SW_HIDE);
        pWnd = pWnd->GetNextWindow();
    } while (pWnd->GetDlgCtrlID() != IDC_STATIC_EXT_FAIL);

    // hide/show registration stuff
//    pWnd = GetDlgItem(ID_REGFIRST);
    do
    {
        pWnd->ShowWindow(iErr != 0? SW_SHOW : SW_HIDE);
        pWnd = pWnd->GetNextWindow();
    } while (pWnd->GetDlgCtrlID() != IDC_BEGINTRIAL);



    if (iErr != 0)
    {
        // make sure we're not using the extension module
        g_bUseWndTabsExt = FALSE;

        // show reason for failure
        CString cErr;
        cErr.LoadString(GetExtensionsErr());
        GetDlgItem(IDC_REASON)->SetWindowText(cErr);
        g_bUseWndTabsExt = FALSE;
    }
    else
    {
        CString sName = g_sRegUserName;
        if (sName.IsEmpty()) sName.LoadString(IDS_USER_TRIAL_REG);
        GetDlgItem(ID_REG_NAME)->SetWindowText(sName);
        g_bUseWndTabsExt = TRUE;
    }

    pWnd = GetDlgItem(IDC_BEGINTRIAL);
    if (!g_bUseWndTabsExt)
    {
        CString s;
        s.LoadString(IDS_OPTION_TRIAL_REG);
        SetWindowText(s);
        pWnd->ShowWindow(SW_SHOW);
    }
    else
    {
        pWnd->ShowWindow(SW_HIDE);
    }
    GetDlgItem(IDC_STOPTRIAL)->ShowWindow(
        g_bUseWndTabsExt  &&  g_sRegUserName.IsEmpty());

    UpdateUsage();
}

void CRegistrationPage::UpdateUsage()
{
    if (!IsWindow(m_hWnd))
    {
        return;
    }
    COptionsSheet *pParent = (COptionsSheet *)GetParent();
    CWTTabCtrlPage *pWTPage = &pParent->m_WTTabCtrlPage;
    CWTTabCtrlPage2 *pWTPage2 = &pParent->m_WTTabCtrlPage2;

    if (pGlobalTabs->m_bIsWTTab  &&  !g_bUseWndTabsExt)
    {
        pGlobalTabs->UpdateStyle();
    }
    
    pWTPage->UpdateUsage();
    pWTPage2->UpdateUsage();
}


/////////////////////////////////////////////////////////////////////////////
// CAboutPage property page

BEGIN_HELP_IDS(CAboutPage)
    IDC_TAB,        0,      // disable help for these ites
    IDC_ANIMATE,    0,

    IDC_LIGHT,      IDC_TOUR,

    ID_DISCLAMER,   IDH_DISCLAMER
END_HELP_IDS();    

CAboutPage::CAboutPage() : CPropertyPage(CAboutPage::IDD)
{
	//{{AFX_DATA_INIT(CAboutPage)
	//}}AFX_DATA_INIT
    m_psp.dwFlags |= PSP_USEICONID;
    m_psp.pszIcon = MAKEINTRESOURCE(IDI_ABOUT);

    // use AfxLoadSysColorBitmap to ensure that the background is the right
    // color.
    HRSRC hRes = FindResource(LoadLibrary("wndtabs.dll"),
        MAKEINTRESOURCE(IDB_BULB2), RT_BITMAP);
    m_hBmpLight = AfxLoadSysColorBitmap(AfxGetInstanceHandle(), hRes, 
        FALSE);
}

CAboutPage::~CAboutPage()
{
    ::DeleteObject(m_hBmpLight);
}

void CAboutPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutPage)
	DDX_Control(pDX, IDC_FAQ, m_FAQBtn);
	DDX_Control(pDX, IDC_TOUR, m_TourHyperlink);
	DDX_Control(pDX, IDC_WWW, m_WWW);
	DDX_Control(pDX, IDC_BUGREPORTS, m_Bugs);
	DDX_Control(pDX, IDC_INFO, m_Info);
	DDX_Control(pDX, IDC_TAB, m_TabCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutPage, CPropertyPage)
	//{{AFX_MSG_MAP(CAboutPage)
	ON_BN_CLICKED(IDC_BUGREPORTS, OnBugreports)
	ON_BN_CLICKED(IDC_INFO, OnInfo)
	ON_BN_CLICKED(IDC_WWW, OnWWW)
	ON_BN_CLICKED(IDC_CHECKVER_NOW, OnCheckVer)
	ON_BN_CLICKED(IDC_FAQ, OnFAQ)
	ON_BN_CLICKED(IDC_INFO_INET_SEND, OnShowPrivacyInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutPage::OnInitDialog() 
{
    CString cVersion;

    CPropertyPage::OnInitDialog();

    TC_ITEM tci;
    tci.mask = TCIF_TEXT;

    for (int i = 0; i < 4; i++)
    {
        tci.pszText = "     ";
        m_TabCtrl.InsertItem(0, &tci);
    }

    tci.pszText = "Window Tabs";
    m_TabCtrl.InsertItem(0, &tci);	

    CWnd *pVersion = GetDlgItem(IDC_VERSION);

    pVersion->GetWindowText(cVersion);
    CString_Replace(cVersion, _T("%1"), g_cVersion);
    pVersion->SetWindowText(cVersion);

    m_Bugs.  SetImage(IDB_BUG);
    m_Info.  SetImage(IDB_INFO);
    m_WWW.   SetImage(IDB_NET);
    m_FAQBtn.SetImage(IDB_QMARK);

    ((CStatic *)GetDlgItem(IDC_LIGHT))->SetBitmap(m_hBmpLight);

    CString tt;
    tt.LoadString(IDS_TOUR_TT);
    m_TourHyperlink.SizeToContent();
    m_TourHyperlink.SetTooltip(tt);
    m_TourHyperlink.SetURL("http://www.wndtabs.com/wt/tour/");

    return TRUE;
}

BOOL CAboutPage::OnSetActive() 
{
	return CPropertyPage::OnSetActive();
}

void CAboutPage::OnBugreports() 
{
    CBugReportsDlg dlg;
    dlg.DoModal();
}

void CAboutPage::OnInfo() 
{
    CInfoDlg dlg;
    dlg.DoModal();
}

void CAboutPage::OnWWW() 
{
    ShowHTMLHelp(m_hWnd, IDH_CONTACT_INFO);
}

void CAboutPage::OnCheckVer() 
{
    // this will open up a browser with a page that knows about the latest
    // version
    char ver[1024];
    aiclGetModuleVersion("WndTabs.dll", ver);
    float fVer;
    if (sscanf(ver, "%f", &fVer) != 1)
    {
        // error
        strcpy(ver, "0");
    }
    else
    {
        sprintf(ver, "%04d", (int)(fVer * 100 + 0.01));
    }
    CString sURL;
    sURL.Format(
        "http://www.wndtabs.com/version/check_ver.asp?app=%s&ver=%s",
        "wt", ver);
    ShellExecute(NULL, "open", sURL, NULL, NULL, SW_SHOW);
}

void CAboutPage::OnFAQ() 
{
    CWaitCursor wc;
    CHyperLink::GotoURL("http://www.wndtabs.com/wt/faq.asp", SW_SHOW);
}

void CAboutPage::OnShowPrivacyInfo() 
{
    ShowHTMLHelp(m_hWnd, IDH_PIPELINE);
}
