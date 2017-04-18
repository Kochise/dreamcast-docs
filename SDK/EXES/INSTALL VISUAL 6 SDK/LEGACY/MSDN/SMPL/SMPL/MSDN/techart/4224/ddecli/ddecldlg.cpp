// DDECldlg.cpp : implementation file
//

#include "stdafx.h"
#include "DDECli.h"
#include "myclient.h"
#include "myconv.h"
#include "DDECldlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
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

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
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
// CAboutDlg message handlers

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();
	
	// TODO: Add extra about dlg initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

/////////////////////////////////////////////////////////////////////////////
// CDDECliDlg dialog

CDDECliDlg::CDDECliDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDDECliDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDDECliDlg)
	m_strExecCmd = _T("");
	m_strItem = _T("");
	m_strItemData = _T("");
	m_strService = _T("");
	m_strTopic = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_pConversation = NULL;
}

void CDDECliDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDDECliDlg)
	DDX_Control(pDX, IDC_STATUS, m_wndStatus);
	DDX_Control(pDX, IDC_POKE, m_wndPoke);
	DDX_Control(pDX, IDC_EXEC, m_wndExec);
	DDX_Control(pDX, IDC_DISCONNECT, m_wndDisconnect);
	DDX_Control(pDX, IDC_CONNECT, m_wndConnect);
	DDX_Text(pDX, IDC_EXECCMD, m_strExecCmd);
	DDX_Text(pDX, IDC_ITEM, m_strItem);
	DDX_Text(pDX, IDC_ITEMDATA, m_strItemData);
	DDX_Text(pDX, IDC_SERVICE, m_strService);
	DDX_Text(pDX, IDC_TOPIC, m_strTopic);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDDECliDlg, CDialog)
	//{{AFX_MSG_MAP(CDDECliDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, OnConnectBtn)
	ON_BN_CLICKED(IDC_DISCONNECT, OnDisconnectBtn)
	ON_EN_CHANGE(IDC_SERVICE, OnChangeService)
	ON_EN_CHANGE(IDC_TOPIC, OnChangeTopic)
	ON_EN_CHANGE(IDC_ITEM, OnChangeItem)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_EXEC, OnExecBtn)
	ON_BN_CLICKED(IDC_POKE, OnPokeBtn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDDECliDlg message handlers

BOOL CDDECliDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();

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
	
	Status("Initializing service");

    if (!m_DDEClient.Create(AfxGetAppName())) {
        AfxMessageBox("Failed to initialize DDE client");
        return FALSE;
    }
	
	Status("Service running");
    UpdateUI();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDDECliDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDDECliDlg::OnPaint() 
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
HCURSOR CDDECliDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDDECliDlg::Status(const char* pszFormat, ...)
{
    char buf[1024];
	va_list arglist;
	va_start(arglist, pszFormat);
    vsprintf(buf, pszFormat, arglist);
	va_end(arglist);

    // Get the number of lines in the listbox
    int iLines = m_wndStatus.GetCount();
    if (iLines == LB_ERR) iLines = 0;

    // make sure it's not getting too big
    m_wndStatus.SetRedraw(FALSE);
    while (iLines > 100) {
        
        m_wndStatus.DeleteString(0);
        iLines--;
    }

    // Add the new text to the end
    m_wndStatus.AddString(buf);

    // Select the last string so it will be scrolled into view
    m_wndStatus.SetCurSel(iLines);

    // remove the selection
    m_wndStatus.SetCurSel(-1);
    m_wndStatus.SetRedraw(TRUE);
}

void CDDECliDlg::OnConnectBtn() 
{
    ASSERT(!m_pConversation);

    //
    // Get the current data set
    //

    UpdateData(TRUE);
    if (m_strService.GetLength() == 0) {
        AfxMessageBox("You must enter a service name");
        return;
    }
    if (m_strTopic.GetLength() == 0) {
        AfxMessageBox("You must enter a topic name");
        return;
    }

    //
    // Try and connect to the specified service and topic
    //

    m_pConversation = new CMyConv(&m_DDEClient, this);
    ASSERT(m_pConversation);
    m_pConversation->AddRef();
    if (!m_pConversation->ConnectTo(m_strService, m_strTopic)) {

        m_pConversation->Release(); // and it should get deleted
        m_pConversation = NULL;
        return;
    }

    Status("Connected to %s|%s",
           (const char*)m_strService,
           (const char*)m_strTopic);

    //
    // if an item is listed, get the current value and 
    // set up an advise request for changes
    //
    
    if (m_strItem.GetLength() > 0) { 

        DWORD dwSize = 0;
        void* pData = NULL;
        m_pConversation->Request(m_strItem, &pData, &dwSize);
        if (dwSize) {
            m_strItemData = (char*)pData;
            UpdateData(FALSE);
            delete pData;
        
            //
            // ask for notice if it changes
            //

            m_pConversation->Advise(m_strItem);

        } else {

            Status("Failed to get data from %s",
                   (const char*) m_strItem);
        }
    }
    UpdateUI();
}

void CDDECliDlg::OnDisconnectBtn() 
{
    if (m_pConversation) {
        m_pConversation->Terminate();
        m_pConversation->Release();
        m_pConversation = NULL;
	    Status("Disconnected");
        UpdateUI();
    }
}

void CDDECliDlg::UpdateUI()
{
    //
    // Enable/disable buttons and so on
    //

    UpdateData(TRUE); // get state of variables

    if ((!m_pConversation)
    && (m_strService.GetLength() > 0)
    && (m_strTopic.GetLength() > 0)) {

        m_wndConnect.EnableWindow(TRUE);

    } else {

        m_wndConnect.EnableWindow(FALSE);

    }

    if (m_pConversation) {

        m_wndDisconnect.EnableWindow(TRUE);

    } else {

        m_wndDisconnect.EnableWindow(FALSE);

    }

    if ((m_pConversation)
    && (m_strItem.GetLength() > 0)) {

        m_wndPoke.EnableWindow(TRUE);

    } else {

        m_wndPoke.EnableWindow(FALSE);

    }

    if ((m_pConversation)
    && (m_strTopic.GetLength() > 0)) {

        m_wndExec.EnableWindow(TRUE);

    } else {

        m_wndExec.EnableWindow(FALSE);

    }
}

void CDDECliDlg::OnChangeService() 
{
	UpdateUI();	
}

void CDDECliDlg::OnChangeTopic() 
{
	UpdateUI();	
}

void CDDECliDlg::OnChangeItem() 
{
	UpdateUI();	
}

void CDDECliDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
    //
    // Shutdown any conversation
    //

    if (m_pConversation) {
        m_pConversation->Terminate();
        m_pConversation->Release();
    }

    //
    // Shut down the DDE service
    //

    m_DDEClient.Shutdown();
    	
}

void CDDECliDlg::NewData(const char* pszItem, const char* pData)
{
    //
    // See if it's for the current item
    //

    if (stricmp(pszItem, (const char*)m_strItem) == 0) {
        m_strItemData = pData;
        UpdateData(FALSE);
    }

}

void CDDECliDlg::OnExecBtn() 
{
	ASSERT(m_pConversation);
    UpdateData(TRUE);
    if (!m_pConversation->Exec(m_strExecCmd)) {
        Status("Exec failed");
    }
}

void CDDECliDlg::OnPokeBtn() 
{
	ASSERT(m_pConversation);
    UpdateData(TRUE);
    if (!m_pConversation->Poke(CF_TEXT,
                          m_strItem,
                          (void*)(const char*)m_strItemData,
                          m_strItemData.GetLength() + 1)) {
        Status("Poke failed");
    }
}
