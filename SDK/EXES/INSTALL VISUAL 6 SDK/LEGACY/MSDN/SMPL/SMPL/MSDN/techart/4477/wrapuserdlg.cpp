// WrapUserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WrapUser.h"
#include "WrapUserDlg.h"

//#include "CInterfaceWrap.h"

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
// CWrapUserDlg dialog

CWrapUserDlg::CWrapUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWrapUserDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWrapUserDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWrapUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWrapUserDlg)
	DDX_Control(pDX, IDC_INCBTN, m_btnInc);
	DDX_Control(pDX, IDC_RELEASEBTN, m_btnRelease);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_EDIT, m_EditCtl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWrapUserDlg, CDialog)
	//{{AFX_MSG_MAP(CWrapUserDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CREATEBTN, OnCreateBtn)
	ON_BN_CLICKED(IDC_RELEASEBTN, OnReleaseBtn)
	ON_BN_CLICKED(IDC_INCBTN, OnIncBtn)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeListBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWrapUserDlg message handlers

BOOL CWrapUserDlg::OnInitDialog()
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
   //m_pISimple = NULL ;
   m_ObjectNum = 0 ;
   EnableBtns(FALSE) ;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWrapUserDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWrapUserDlg::OnPaint() 
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
HCURSOR CWrapUserDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWrapUserDlg::OnCreateBtn() 
{
#if 0
   // Create an IUnknown wrapper.
   CUnknownWrap WIUnknown ;
   // Create the object.
   WIUnknown.CreateObject(CLSID_SimpleObject) ;
   if (!WIUnknown.IsOK())
      return ;

   // Create a ISimple wrapper.
   CSimpleWrap* pWISimple = new CSimpleWrap ;

   // Attach the ISimple wrapper to the IUnknown wrapper's object.
   pWISimple->Attach(WIUnknown) ;
   if (!pWISimple->IsOK())
   {
       TRACE("ISimple not supported");
       delete pWISimple ;
       return;
   }
#else
   // Create the object and get the ISimple interface in one step.
   CSimpleWrap* pWISimple = new CSimpleWrap ;
   pWISimple->CreateObject(CLSID_SimpleObject) ;
   if (!pWISimple->IsOK())
   {
       TRACE("ISimple not supported.\r\n");
       delete pWISimple ;
       return;
   }

#endif
   
   // Set initial count to 10.
   pWISimple->SetCount(10) ;

   // Add the objec to the map. Use m_ObjectNum as its key.
   m_SimpleMap.SetAt(++m_ObjectNum, pWISimple) ;

   // Add a string about the object to the listbox.
   CString aStr ;
   aStr.Format("Object Number : %d",m_ObjectNum) ;
   int index = m_ListBox.AddString(aStr) ;

   // Add the key to the listbox as data.
   m_ListBox.SetItemData(index, m_ObjectNum) ;
}

void CWrapUserDlg::OnReleaseBtn() 
{
   int index = m_ListBox.GetCurSel()  ;
   if (index != LB_ERR)
   {
      // Get the map key for the object from the listbox's data.
      int iKey = (int)m_ListBox.GetItemData(index) ;
      m_ListBox.DeleteString(index) ;

      // Get the wrapper pointer to the object to release
      CSimpleWrap* pWISimple ; 
      m_SimpleMap.Lookup(iKey, pWISimple) ;

      // Remove the object.
      VERIFY(m_SimpleMap.RemoveKey(iKey));

      // Delete the wrapper and Release the interface.
      delete pWISimple ; // was Release. Caught by private Release function.

      // Update the UI.
      m_EditCtl.SetWindowText("") ;
      m_ListBox.SetCurSel(-1) ;
      EnableBtns(FALSE) ;
   }
}

void CWrapUserDlg::OnIncBtn() 
{
   int index = m_ListBox.GetCurSel()  ;
   if (index != LB_ERR)
   {
      // Get the map key for the object from the listbox's data.
      int iKey = (int)m_ListBox.GetItemData(index) ;

      // Get the wrapper pointer to the object to release
      CSimpleWrap* pWISimple ; 
      m_SimpleMap.Lookup(iKey, pWISimple) ;

      // Increment the count in the simple object.
      pWISimple->Inc() ;

      // Update the inteface.
      DrawHelper(pWISimple) ;
   }
}

void CWrapUserDlg::OnSelchangeListBox() 
{
   int index = m_ListBox.GetCurSel()  ;
   if (index != LB_ERR)
   {
      // Get the map key for the object from the listbox's data.
      int iKey = (int)m_ListBox.GetItemData(index) ;

      // Get the wrapper pointer to the object to release
      CSimpleWrap* pWISimple ; 
      m_SimpleMap.Lookup(iKey, pWISimple) ;

      ASSERT(pWISimple->IsOK()) ;

      // Update the inteface.
      DrawHelper(pWISimple) ;
      EnableBtns(TRUE) ;      
   }		
   else
      EnableBtns(FALSE) ;
}

//
// Helper Functions.
//

void CWrapUserDlg::DrawHelper(CSimpleWrap* pWISimple)
{
   CString aString ;
   if (pWISimple != NULL)
   {
      int i = pWISimple->GetCount() ;
      aString.Format("Count: %d", i) ;
   }
   else
   {
      aString = "Count: xxxx" ;
   }
   m_EditCtl.SetWindowText(aString) ;
}

void CWrapUserDlg::cleanUp()
{
   // Delete all of the wrapper objects in the map.
   CSimpleWrap* pWISimple ;
   int iKey ;
   POSITION pos = m_SimpleMap.GetStartPosition() ;
   while (pos != NULL)
   {
      m_SimpleMap.GetNextAssoc(pos, iKey, pWISimple) ;
      delete pWISimple;
   }
   m_SimpleMap.RemoveAll() ;
}



void CWrapUserDlg::EnableBtns(BOOL bEnable)
{
   m_btnRelease.EnableWindow(bEnable) ;
   m_btnInc.EnableWindow(bEnable) ;
}
