/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/

// Options.h : header file
//

#ifndef __OPTIONS_H
#define __OPTIONS_H

#include "TreePropertySheet.h"
#include "AutoPropPage.h"

/////////////////////////////////////////////////////////////////////////////
// CArrangementPage dialog

class CArrangementPage : public CAutoPropPage
{
    DECLARE_DYNCREATE(CArrangementPage)

// Construction
public:
    CArrangementPage();

// Dialog Data
    //{{AFX_DATA(CArrangementPage)
	enum { IDD = IDD_OPTPAGE_TABS_ARRANGEMENT };
    CSpinButtonCtrl m_RowSpin;
    int     m_RadioSnap;
    int     m_RadioOrientation;
    int     m_iRows;
	int		m_bFixedTabRows;
    BOOL    m_bAutoRefresh;
    int     m_iInterval;
	BOOL	m_bNoRaggedRight;
	//}}AFX_DATA

    bool    m_bInited;

// Overrides
    // ClassWizard generate virtual function overrides
    //{{AFX_VIRTUAL(CArrangementPage)
    public:
    virtual BOOL OnApply();
    virtual BOOL OnSetActive();
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(CArrangementPage)
    afx_msg void OnSnapmdi();
    virtual BOOL OnInitDialog();
    afx_msg void OnSnapwindow();
    afx_msg void DoModify();
	afx_msg void UpdateAutoTabRows();
    afx_msg void OnAutorefresh();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    DECLARE_HELP_IDS();
};


/////////////////////////////////////////////////////////////////////////////
// CTabDisplayPage dialog

class CTabDisplayPage : public CAutoPropPage
{
    DECLARE_DYNCREATE(CTabDisplayPage)

// Construction
public:
    CTabDisplayPage();

// Dialog Data
    //{{AFX_DATA(CTabDisplayPage)
	enum { IDD = IDD_OPTPAGE_TABS_CONTENT };
	CBCGButton	m_GoButton;
    BOOL    m_bShowIcons;
    BOOL    m_bShowNumbers;
    BOOL    m_bStripPath;
    BOOL    m_bStripExt;
    BOOL    m_bDispRC;
    BOOL    m_bDispResLang;
    BOOL    m_bDispResType;
    BOOL    m_bDispRID;
	int		m_FontType;
	//}}AFX_DATA

// Overrides
    // ClassWizard generate virtual function overrides
    //{{AFX_VIRTUAL(CTabDisplayPage)
    public:
    virtual BOOL OnApply();
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(CTabDisplayPage)
    afx_msg void DoModify();
    virtual BOOL OnInitDialog();
	afx_msg void OnGo();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    DECLARE_HELP_IDS();
};


/////////////////////////////////////////////////////////////////////////////
// COrderingPage dialog

class COrderingPage : public CAutoPropPage
{
// Construction
public:
	COrderingPage();

// Dialog Data
	//{{AFX_DATA(COrderingPage)
	enum { IDD = IDD_OPTPAGE_TABS_ORDERING };
    BOOL    m_bFill1To9;
    BOOL    m_bPreserveNumbering;
    CBCGButton   m_Reorder;
    CBCGButton   m_Renumber;
	int		m_iTabOrdering;
	BOOL	m_bSaveTabNums;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COrderingPage)
    public:
    virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COrderingPage)
	afx_msg void DoModify();
	virtual BOOL OnInitDialog();
    afx_msg void DoUpdateDlgItems();
    afx_msg void OnRenumber();
    afx_msg void OnReorder();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    DECLARE_HELP_IDS();
};


/////////////////////////////////////////////////////////////////////////////
// CTrimmingPage dialog

class CTrimmingPage : public CAutoPropPage
{
// Construction
public:
	CTrimmingPage();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTrimmingPage)
	enum { IDD = IDD_OPTPAGE_TABS_TRIMMING };
    BOOL    m_bLimitChars;
    BOOL    m_bLimitResChars;
    BOOL    m_bLimitIgnoreExt;
    BOOL    m_bUseLimitChar;
    int     m_iCharLimit;
    CString m_sLimitCharacter;
	BOOL	m_bTrimPrefix;
	BOOL	m_bTrimSuffix;
	BOOL	m_bUsePrefixChar;
	BOOL	m_bUseSuffixChar;
	CString	m_sSuffixChar;
	CString	m_sPrefixChar;
	CString	m_sPrefixes;
	CString	m_sSuffixes;
	//}}AFX_DATA

    int     m_iLimitChar;
    int     m_iPrefixChar;
    int     m_iSuffixChar;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrimmingPage)
    public:
    virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTrimmingPage)
    afx_msg void DoModify();
    virtual BOOL OnInitDialog();
    afx_msg void OnSelect();
	afx_msg void DoUpdateDlgItems();
	afx_msg void OnSelectPrefixChar();
	afx_msg void OnSelectSuffixChar();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    void SelectChar(CString& s);

    DECLARE_HELP_IDS();
};


/////////////////////////////////////////////////////////////////////////////
// CWTTabCtrlPage dialog

class CWTTabCtrlPage : public CAutoPropPage
{
// Construction
public:
    CWTTabCtrlPage();

// Dialog Data
    //{{AFX_DATA(CWTTabCtrlPage)
	enum { IDD = IDD_OPTPAGE_TABS_WTTABCTRL };
    BOOL    m_bGroupTabs;
    BOOL    m_bUseWTTabCtrl;
    BOOL    m_bGroupRes;
    BOOL    m_bGroupPath;
    int     m_Period;
	BOOL	m_bShowGroupDelim;
	BOOL	m_bUseGroupOps;
	BOOL	m_bSortMiniTB;
	BOOL	m_bGroupPrj;
	//}}AFX_DATA

    int     m_iRegColor;
    int     m_iSelColor;
    bool    m_bInited;

    void UpdateUsage();


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CWTTabCtrlPage)
    public:
    virtual BOOL OnApply();
    virtual BOOL OnSetActive();
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(CWTTabCtrlPage)
    afx_msg void DoModify();
    afx_msg void OnUsewttabctrl();
    afx_msg void OnGrouptabs();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    void UpdateGroupTabs();

    DECLARE_HELP_IDS();
};


/////////////////////////////////////////////////////////////////////////////
// CWTTabCtrlPage2 dialog

class CWTTabCtrlPage2 : public CAutoPropPage
{
// Construction
public:
    CWTTabCtrlPage2();

// Dialog Data
    //{{AFX_DATA(CWTTabCtrlPage2)
	enum { IDD = IDD_OPTPAGE_TABS_WTTABCTRL2 };
    CBCGColorButton m_SelColor;
    CBCGColorButton m_RegColor;
	BOOL	m_bTabCloseBtn;
	BOOL	m_bForceMiniTB;
	//}}AFX_DATA

    int     m_iRegColor;
    int     m_iSelColor;
    bool    m_bInited;

    void UpdateUsage();


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CWTTabCtrlPage2)
    public:
    virtual BOOL OnApply();
    virtual BOOL OnSetActive();
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(CWTTabCtrlPage2)
    afx_msg void DoModify();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    DECLARE_HELP_IDS();
};


/////////////////////////////////////////////////////////////////////////////
// CWinFileManPage dialog

class CWinFileManPage : public CAutoPropPage
{
	DECLARE_DYNCREATE(CWinFileManPage)

// Construction
public:
	CWinFileManPage();
	~CWinFileManPage();

// Dialog Data
	//{{AFX_DATA(CWinFileManPage)
	enum { IDD = IDD_OPTPAGE_WINFILEMAN };
	CBCGMenuButton	m_DirOptions;
    int     m_iWinLimit;
    BOOL    m_bLimitWin;
	BOOL	m_bIsGroupLimit;
	BOOL	m_bAutoOpenAlt;
	BOOL	m_bLimitWinDbg;
	int 	m_iWinLimitDbg;
	CString	m_sDirs;
	BOOL	m_bAutoCloseDbg;
	//}}AFX_DATA

    CMenu   m_MenuDirOptions;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CWinFileManPage)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CWinFileManPage)
	virtual BOOL OnInitDialog();
	afx_msg void DoModify();
	afx_msg void OnDirpicker();
	afx_msg void DoUpdateDlgItems();
	afx_msg void OnDiroptions();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    DECLARE_HELP_IDS();
};


/////////////////////////////////////////////////////////////////////////////
// CMenusPage dialog

class CMenusPage : public CAutoPropPage
{
    DECLARE_DYNCREATE(CMenusPage)

// Construction
public:
	CMenusPage();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMenusPage)
	enum { IDD = IDD_OPTPAGE_CUST_MENUS };
	CBCGButton	m_btnCreateVCToolbar;
	CBCGButton	m_btnCustomizeWTToolbar;
	CBCGButton	m_btnCustomizeContextMenuGroups;
	CBCGButton	m_btnCustomizeContextMenu;
    int     m_ShellKey;
	BOOL	m_bCascadingAddons;
	BOOL	m_bSuppressNoCmd;
	//}}AFX_DATA
    int     m_cfgiShellKey;

    static void ResetMenu(LPCTSTR pszMenuName, CMenu *pPopup);
	static void ResetMenusFromConfig();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMenusPage)
    virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMenusPage)
	afx_msg void DoModify();
	afx_msg void DoEnableDisable();
	virtual BOOL OnInitDialog();
	afx_msg void OnCustomizeWtToolbar();
	afx_msg void OnCustomizeContextMenu();
	afx_msg void OnCustomizeContextMenuGroups();
	afx_msg void OnToolbarCust();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    DECLARE_HELP_IDS();
};


/////////////////////////////////////////////////////////////////////////////
// CMiscPage dialog

class CMiscPage : public CAutoPropPage
{
    DECLARE_DYNCREATE(CMiscPage)

// Construction
public:
    CMiscPage();

// Dialog Data
    //{{AFX_DATA(CMiscPage)
	int		m_iOpenMethod;
    BOOL    m_bUseWWhiz;
	enum { IDD = IDD_OPTPAGE_MISC };
    CBCGButton   m_DoWizBtn;
    BOOL    m_bShowAttribs;
	BOOL	m_bRTFCopy;
	BOOL	m_bDisableSplash;
	//}}AFX_DATA

// Overrides
    // ClassWizard generate virtual function overrides
    //{{AFX_VIRTUAL(CMiscPage)
	public:
    virtual BOOL OnApply();
	virtual BOOL OnSetActive();
	protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(CMiscPage)
    afx_msg void DoModify();
    afx_msg void OnWizard();
    virtual BOOL OnInitDialog();
	afx_msg void OnResetShowonce();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    DECLARE_HELP_IDS();
};


/////////////////////////////////////////////////////////////////////////////
// CLanguagePage dialog

class CLanguagePage : public CAutoPropPage
{
	DECLARE_DYNCREATE(CLanguagePage)

// Construction
public:
	CLanguagePage();
	~CLanguagePage();

    CString m_sLangDLL;

// Dialog Data
	//{{AFX_DATA(CLanguagePage)
	enum { IDD = IDD_OPTPAGE_LANG };
	CComboBox	m_Languages;
	CBCGURLLinkButton m_Hyperlink;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CLanguagePage)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CLanguagePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboLang();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CRegistrationPage dialog

class CRegistrationPage : public CAutoPropPage
{
	DECLARE_DYNCREATE(CRegistrationPage)

// Construction
public:
	CRegistrationPage();
	~CRegistrationPage();

// Dialog Data
	//{{AFX_DATA(CRegistrationPage)
	enum { IDD = IDD_OPTPAGE_REGISTRATION };
	CBCGButton	m_StopTrialBtn;
	CBCGButton	m_TrialBtn;
	CBCGButton	m_KeyBtn;
	CBCGButton	m_RegBtn;
	CBCGButton	m_IntoBtn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CRegistrationPage)
    public:
    virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CRegistrationPage)
	afx_msg void OnInfo();
	afx_msg void OnRegister();
	afx_msg void OnEnterKey();
	virtual BOOL OnInitDialog();
	afx_msg void OnBegintrial();
	afx_msg void OnStoptrial();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    DECLARE_HELP_IDS();

    void CheckExt();
    void UpdateUsage();
};


/////////////////////////////////////////////////////////////////////////////
// CAboutPage dialog

class CAboutPage : public CAutoPropPage
{
    DECLARE_DYNCREATE(CAboutPage)

// Construction
public:
    CAboutPage();
    ~CAboutPage();

// Dialog Data
    //{{AFX_DATA(CAboutPage)
	enum { IDD = IDD_OPTPAGE_ABOUT };
	CBCGButton	m_FAQBtn;
	CBCGURLLinkButton m_TourHyperlink;
    CBCGButton   m_WWW;
    CBCGButton   m_Bugs;
    CBCGButton   m_Info;
    CTabCtrl    m_TabCtrl;
	//}}AFX_DATA

    HBITMAP m_hBmpLight;

// Overrides
    // ClassWizard generate virtual function overrides
    //{{AFX_VIRTUAL(CAboutPage)
    public:
    virtual BOOL OnSetActive();
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(CAboutPage)
    virtual BOOL OnInitDialog();
    afx_msg void OnBugreports();
    afx_msg void OnInfo();
    afx_msg void OnWWW();
    afx_msg void OnCredits();
	afx_msg void OnCheckVer();
	afx_msg void OnFAQ();
	afx_msg void OnShowPrivacyInfo();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    DECLARE_HELP_IDS();
};



/////////////////////////////////////////////////////////////////////////////
// CCustomizePage dialog

class CCustomizePage : public CAutoPropPage
{
	DECLARE_DYNCREATE(CCustomizePage)

// Construction
public:
	CCustomizePage();
	~CCustomizePage();

// Dialog Data
	//{{AFX_DATA(CCustomizePage)
	enum { IDD = IDD_OPTPAGE_CUST };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCustomizePage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCustomizePage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// CMousePage dialog

class CMousePage : public CAutoPropPage
{
	DECLARE_DYNCREATE(CMousePage)

// Construction
public:
	CMousePage();
	~CMousePage();

// Dialog Data
	//{{AFX_DATA(CMousePage)
	enum { IDD = IDD_OPTPAGE_CUST_MOUSE };
	//}}AFX_DATA

    int m_iMidBtnCommand;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMousePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnSetActive();
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMousePage)
	afx_msg void OnSetAccesscontextmenu();
	afx_msg void OnAssignMidbtn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    void UpdateMidBtnCommand();

	DECLARE_HELP_IDS();
};
/////////////////////////////////////////////////////////////////////////////
// CKeyboardPage dialog

class CKeyboardPage : public CAutoPropPage
{
	DECLARE_DYNCREATE(CKeyboardPage)

// Construction
public:
	CKeyboardPage();
	~CKeyboardPage();

// Dialog Data
	//{{AFX_DATA(CKeyboardPage)
	enum { IDD = IDD_OPTPAGE_CUST_KBD };
	CBCGButton	m_btnTabActivation;
	CBCGButton	m_btnAnyCommand;
	CBCGButton	m_btnCommonCommands;
	BOOL	m_bStopButton;
	int		m_iBackForward;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CKeyboardPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CKeyboardPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnKeyboardCustTabActivation();
	afx_msg void OnKeyboardCustBcg();
	afx_msg void OnKeyboardCust();
	afx_msg void DoModify();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    DECLARE_HELP_IDS();
};

/////////////////////////////////////////////////////////////////////////////
// CTabsPage dialog

class CTabsPage : public CAutoPropPage
{
	DECLARE_DYNCREATE(CTabsPage)

// Construction
public:
	CTabsPage();
	~CTabsPage();

// Dialog Data
	//{{AFX_DATA(CTabsPage)
	enum { IDD = IDD_OPTPAGE_TABS };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTabsPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTabsPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};




/////////////////////////////////////////////////////////////////////////////
// COptionsSheet

class COptionsSheet : public CTreePropertySheet
{
    DECLARE_DYNAMIC(COptionsSheet)

// Construction
public:
    COptionsSheet(int iInitialPage, CWnd* pWndParent = NULL);
    COptionsSheet(CWnd* pWndParent = NULL);

// Attributes
public:
    CTabsPage           m_TabsPage;
     CArrangementPage    m_ArrangmentPage;
     CTabDisplayPage     m_TabDisplayPage;
     COrderingPage       m_OrderingPage;
     CTrimmingPage       m_TrimmingPage;
     CWTTabCtrlPage      m_WTTabCtrlPage;
     CWTTabCtrlPage2     m_WTTabCtrlPage2;
    CWinFileManPage     m_WinFileManPage;
    CCustomizePage      m_CustomizePage;
     CMenusPage          m_MenusPage;
     CKeyboardPage       m_KeyboardPage;
     CMousePage          m_MousePage;
    CMiscPage           m_MiscPage;
    CLanguagePage       m_LanguagePage;
    CRegistrationPage   m_RegistrationPage;
    CAboutPage          m_AboutPage;

    CBCGButton             m_CustomizeBtn;

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(COptionsSheet)
	public:
    virtual int DoModal();
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
    virtual ~COptionsSheet();

// Generated message map functions
protected:
    //{{AFX_MSG(COptionsSheet)
	afx_msg void OnDestroy();
	afx_msg void OnCustomize();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP();

    void CommonInit();

    bool m_bUseConfigVar;
};

/////////////////////////////////////////////////////////////////////////////


#endif // __OPTIONS_H

