// LevelViewerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LevelViewer.h"
#include "LevelViewerDlg.h"
#include "DlgProxy.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CLevelViewerDlg dialog


IMPLEMENT_DYNAMIC(CLevelViewerDlg, CDialog);

BEGIN_MESSAGE_MAP(CLevelViewerDlg, CDialog)
	//{{AFX_MSG_MAP(CLevelViewerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(ID_FISH, OnFish)
	ON_BN_CLICKED(ID_GAS, OnGas)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------------
CLevelViewerDlg::CLevelViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLevelViewerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLevelViewerDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;

	m_pILevelGetter = NULL;
	m_sLastCalled = _T("CheckedGas");
}

//-----------------------------------------------------------------------------------
CLevelViewerDlg::~CLevelViewerDlg()
{
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

//-----------------------------------------------------------------------------------
void CLevelViewerDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	KillTimer(1);
}

//-----------------------------------------------------------------------------------
void CLevelViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLevelViewerDlg)
	//}}AFX_DATA_MAP
}

//-----------------------------------------------------------------------------------
BOOL CLevelViewerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	ClearMembers();
	OnGas();
	SetTimer(1, 4000, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

//-----------------------------------------------------------------------------------
void CLevelViewerDlg::OnPaint() 
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

//-----------------------------------------------------------------------------------
HCURSOR CLevelViewerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//-----------------------------------------------------------------------------------
void CLevelViewerDlg::OnClose() 
{
	if (CanExit())
		CDialog::OnClose();
}

//-----------------------------------------------------------------------------------
void CLevelViewerDlg::OnOK() 
{
	if (CanExit())
		CDialog::OnOK();
}

//-----------------------------------------------------------------------------------
void CLevelViewerDlg::OnCancel() 
{
	if (CanExit())
		CDialog::OnCancel();
}

//-----------------------------------------------------------------------------------
BOOL CLevelViewerDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}

//-----------------------------------------------------------------------------------
void CLevelViewerDlg::ClearMembers()
{
	CWnd* pWnd = GetDlgItem(IDC_TANK_TYPE);
	if(pWnd != NULL)
		pWnd->SetWindowText("");

	pWnd = GetDlgItem(IDC_LOWEST_SAFE);
	if(pWnd != NULL)
		pWnd->SetWindowText("");

	pWnd = GetDlgItem(IDC_HIGHEST_SAFE);
	if(pWnd != NULL)
		pWnd->SetWindowText("");

	pWnd = GetDlgItem(IDC_CURRENT);
	if(pWnd != NULL)
		pWnd->SetWindowText("");

	pWnd = GetDlgItem(IDC_MESSAGE);
	if(pWnd != NULL)
		pWnd->SetWindowText("");
}

//-----------------------------------------------------------------------------------
void CLevelViewerDlg::OnFish() 	//mapped to BaseLevelGetter
{
	m_sLastCalled = _T("CheckedFish");

	CLSID clsid;
	HRESULT hRes = AfxGetClassIDFromString("BaseLevelGetterDLL.BaseLevelGetter", &clsid);

	if(SUCCEEDED(hRes))
		SetNewData(clsid, IID_ILevelGetter);
}

//-----------------------------------------------------------------------------------
void CLevelViewerDlg::OnGas()  //mapped to HotTubLevelGetter
{
	m_sLastCalled = _T("CheckedGas");

	CLSID clsid;
	HRESULT hRes = AfxGetClassIDFromString("HotTubLevelGetterDLL.HotTubLevelGetter", &clsid);
	
	if(SUCCEEDED(hRes))
		SetNewData(clsid, IID_ILevelGetter);
}

//-----------------------------------------------------------------------------------
void CLevelViewerDlg::SetNewData(const CLSID& clsid, const IID& iid)
{
	ClearMembers();

	ASSERT(m_pILevelGetter == NULL);

    HRESULT hRes = CoCreateInstance(clsid, NULL, CLSCTX_ALL, 
									iid, (void**)&m_pILevelGetter);

    if(!SUCCEEDED(hRes))
	{
		m_pILevelGetter = NULL;
		return;
	}

	long lLowestSafeLevel, lHighestSafeLevel, lCurrentLevel;
	BSTR bstrMessage = NULL;

	m_pILevelGetter->GetLowestPossibleSafeLevel(&lLowestSafeLevel);
	m_pILevelGetter->GetHighestPossibleSafeLevel(&lHighestSafeLevel);
	m_pILevelGetter->GetCurrentLevel(&lCurrentLevel);
	m_pILevelGetter->GetTextMessage(&bstrMessage);

	m_pILevelGetter->Release();
	m_pILevelGetter = NULL;

	CString sLowest, sHighest, sCurrent, sMessage;
	sLowest.Format("%d",lLowestSafeLevel);
	sHighest.Format("%d",lHighestSafeLevel);
	sCurrent.Format("%d",lCurrentLevel);
	sMessage = bstrMessage;
	::SysFreeString(bstrMessage);

	CString sItem;
	if(m_sLastCalled == _T("CheckedFish"))
	{
		//mapped to base tank
		sItem = _T("Base Tank Level");
	}
	else //m_sLastCalled == _T("CheckedGas")
	{
		//mapped to hot tub
		sItem = _T("Hot Tub Level");
	}

	CWnd* pWnd = GetDlgItem(IDC_TANK_TYPE);
	if(pWnd != NULL)
		pWnd->SetWindowText(sItem);

	pWnd = GetDlgItem(IDC_LOWEST_SAFE);
	if(pWnd != NULL)
		pWnd->SetWindowText(sLowest);

	pWnd = GetDlgItem(IDC_HIGHEST_SAFE);
	if(pWnd != NULL)
		pWnd->SetWindowText(sHighest);

	pWnd = GetDlgItem(IDC_CURRENT);
	if(pWnd != NULL)
		pWnd->SetWindowText(sCurrent);

	pWnd = GetDlgItem(IDC_MESSAGE);
	if(pWnd != NULL)
		pWnd->SetWindowText(sMessage);
}

//-----------------------------------------------------------------------------------
void CLevelViewerDlg::OnTimer(UINT nIDEvent) 
{
	if(m_sLastCalled == _T("CheckedFish"))
		OnGas();
	else
		OnFish();
}
