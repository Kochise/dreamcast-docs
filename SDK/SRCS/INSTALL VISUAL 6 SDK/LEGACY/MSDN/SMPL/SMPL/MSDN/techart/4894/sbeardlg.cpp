// SBearDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ithread.h"
#include "SurfBear.h"
#include "SBearDlg.h"

#include "ATypeDlg.h"

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
// CSurfBearDlg dialog

CSurfBearDlg::CSurfBearDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSurfBearDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSurfBearDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSurfBearDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSurfBearDlg)
	DDX_Control(pDX, IDC_BTN_ACCESS, m_btnAccess);
	DDX_Control(pDX, IDOK, m_btnGoto);
	DDX_Control(pDX, IDCANCEL, m_btnClose);
	DDX_Control(pDX, IDC_EDIT_BROWSE, m_editBrowse);
	DDX_Control(pDX, IDC_EDIT_ADDRESS, m_editAddress);
	DDX_Control(pDX, IDC_ANIMATE, m_ctrlAnimate);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSurfBearDlg, CDialog)
	//{{AFX_MSG_MAP(CSurfBearDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, OnGotoBtn)
	ON_WM_SIZE()
   ON_MESSAGE(WM_READFILECOMPLETED, OnReadFileCompleted) 
	ON_BN_CLICKED(IDC_BTN_ACCESS, OnBtnAccess)
  	ON_COMMAND(IDC_HELPIMAGE, OnHelpAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSurfBearDlg message handlers

BOOL CSurfBearDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

   // Initialize the Browse Edit Control
   CRect rectClient ;
   GetClientRect(&rectClient) ;
   SetEditBrowseSize(rectClient.Width(), rectClient.Height()) ;

   // Initialize the Address Edit Control
   m_editAddress.SetWindowText("http://www.microsoft.com") ;

   // Initialize the InternetThread
   m_InternetThread.Init(GetSafeHwnd()) ;

   // Initialize Animation Control
   m_ctrlAnimate.Open(IDR_AVI_BOOKS) ;

   // Initialize the Help Bitmap Button
   m_btnBitmapHelp.AutoLoad(IDC_HELPIMAGE, this) ;

   return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSurfBearDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSurfBearDlg::OnPaint() 
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
HCURSOR CSurfBearDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//
// User has pressed the Goto Button. Start worker thread.
//
void CSurfBearDlg::OnGotoBtn() 
{
   TRACE0("OnGotoBtn\r\n") ;

   CString strAddress ;
   m_editAddress.GetWindowText(strAddress) ;
   if (strAddress.IsEmpty()
      || "http://" != strAddress.Left(7))
   {
      AfxMessageBox("Please, http address required.", MB_OK | MB_ICONINFORMATION) ;
      return ;
   }

   //
   // Disable the UI
   //
   EnableUI(FALSE) ;

   //
   // Get the thread to get a page.
   //
   m_InternetThread.GetPage(strAddress) ;
 
}

//
// OnSize
//
void CSurfBearDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
   if (nType == SIZE_MAXIMIZED || nType == SIZE_RESTORED) 	
      SetEditBrowseSize(cx, cy) ;   
}


//
// Enable or disable the controls .
//
void CSurfBearDlg::EnableUI(BOOL bEnable)
{
   m_btnGoto.EnableWindow(bEnable) ;
   m_editAddress.EnableWindow(bEnable) ;
   m_btnAccess.EnableWindow(bEnable); 

   if (bEnable)
   {
      m_ctrlAnimate.Stop() ;
      m_ctrlAnimate.Seek(0) ;
   }
   else
   {
      m_ctrlAnimate.Play(0, (UINT)-1, (UINT)-1) ;
   }
}

//
// Set the size of the edit control which displays the raw HTML.
//
void CSurfBearDlg::SetEditBrowseSize(int cx, int cy)
{
   if (cx > 0 && cy >0)
   {
      CRect aRect ;
      if (m_editBrowse.m_hWnd != NULL)
      {
         m_editBrowse.GetWindowRect(aRect) ;
         ScreenToClient(aRect) ;
	      m_editBrowse.MoveWindow(0, aRect.top,
                                 cx, cy-aRect.top) ;
      }
   }
}

//
// OnReadFileCompleted -   Internet Thread sends a user defined WM_READFILECOMPLETED
//                         message to this window, when the thread has finished.
//
afx_msg LRESULT CSurfBearDlg::OnReadFileCompleted(WPARAM wParam, LPARAM lParam)
{
   TRACE0("CSurfBearDlg::OnReadFileCompleted\r\n") ;
   UINT uiResult = (UINT)lParam ;
   if ( uiResult == THREAD_GOOD)
   {
      m_editBrowse.SetWindowText(m_InternetThread.GetBuffer()) ;
      m_InternetThread.EmptyBuffer() ;
   }
   
   EnableUI(TRUE) ;

   return TRUE ;
}

//
// Display dialog box which allows changing the access type.
//
void CSurfBearDlg::OnBtnAccess() 
{
	CAccessTypeDlg aDlg ;

   aDlg.m_strProxyServer = m_InternetThread.GetProxyServer() ;
   aDlg.m_iRadioBtns = m_InternetThread.GetAccessTypeIndex() ;

   if (aDlg.DoModal() == IDOK)
   {
      m_InternetThread.SetProxyServer(aDlg.m_strProxyServer) ;
      m_InternetThread.SetAccessTypeIndex(aDlg.m_iRadioBtns); 
   }
	
}

//
//
//
void CSurfBearDlg::OnHelpAbout()
{
   CAboutDlg aDlg ;
   aDlg.DoModal() ;
}
