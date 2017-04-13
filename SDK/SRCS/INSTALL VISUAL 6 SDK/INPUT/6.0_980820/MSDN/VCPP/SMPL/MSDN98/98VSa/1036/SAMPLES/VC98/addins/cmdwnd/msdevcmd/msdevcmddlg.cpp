// msdevcmdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "msdevcmd.h"
#include "msdevcmdDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsdevcmdDlg dialog

CMsdevcmdDlg::CMsdevcmdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMsdevcmdDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMsdevcmdDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bmPinned.LoadBitmap(IDB_BM_PINNED);
	m_bmNotPinned.LoadBitmap(IDB_BM_NOTPINNED);
}

CMsdevcmdDlg::~CMsdevcmdDlg()
{
}

void CMsdevcmdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsdevcmdDlg)
	DDX_Control(pDX, IDC_BTN_PIN, m_ctlBtnPinned);
	DDX_Control(pDX, IDC_EDITCMD, m_ctlEditCmd);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMsdevcmdDlg, CDialog)
	//{{AFX_MSG_MAP(CMsdevcmdDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CHAR()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_PIN, OnBtnPin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsdevcmdDlg message handlers

BOOL CMsdevcmdDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_fTopMost = FALSE;
	m_ctlBtnPinned.SetBitmap(m_bmNotPinned);
	m_ctlEditCmd.SetParent(this);
	m_ctlEditCmd.LimitText();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMsdevcmdDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMsdevcmdDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMsdevcmdDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMsdevcmdDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar == _T('\n'))
	{
		//process command.
	}
	CDialog::OnChar(nChar, nRepCnt, nFlags);
}

void CMsdevcmdDlg::OnSize(UINT nType, int cx, int cy) 
{
	CRect rect, rectButton;

	if (m_ctlBtnPinned.GetSafeHwnd())
	{
		m_ctlBtnPinned.GetClientRect(rectButton);
		if (cx > rectButton.Width() * 3 && cy > rectButton.Height() * 3)
		{
			CDialog::OnSize(nType, cx, cy);
			
			m_ctlEditCmd.GetClientRect(rect);
			rect.top += rectButton.Height() + 5;
			m_ctlEditCmd.MoveWindow(rect.left, rect.top, cx, cy - 5 - 2);
		}
		else
		{
			GetWindowRect(rect);
			if (cy < rectButton.Height() * 3)
				rect.bottom = rect.top + rectButton.Height() * 3;
			if (cx < rectButton.Width() * 3)
				rect.right = rect.left + rectButton.Width() * 3;
			MoveWindow(rect);
		}
	}
}

void CMsdevcmdDlg::Pin(BOOL fPin, BOOL fShow /* = TRUE*/) 
{
	if (fPin)
	{
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOREDRAW);
		if (fShow)
			m_ctlBtnPinned.SetBitmap(m_bmPinned);
	}
	else
	{ 
		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOREDRAW);
		if (fShow)
			m_ctlBtnPinned.SetBitmap(m_bmNotPinned);
	}
	m_fTopMost = fPin;
}

void CMsdevcmdDlg::OnBtnPin() 
{
	Pin(~m_fTopMost);
}
