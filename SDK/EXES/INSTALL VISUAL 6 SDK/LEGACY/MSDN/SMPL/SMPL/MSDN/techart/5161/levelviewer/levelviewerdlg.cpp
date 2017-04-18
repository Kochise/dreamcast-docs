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

//---------------------------------------------------------------------------------
interface ILevelGetter : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE GetLowestPossibleSafeLevel(long* plLowestSafeLevel) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetHighestPossibleSafeLevel(long* plLowestSafeLevel) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetCurrentLevel(long* plLowestSafeLevel) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetTextMessage(BSTR* pbstrMessage) = 0;
};

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
void CLevelViewerDlg::OnFish() 
{
	m_sLastCalled = _T("CheckedFish");
	CLSID clsid;
	IID   iid;	
	HRESULT hRes = AfxGetClassIDFromString("{7F0DFAA3-F56D-11D0-A980-0020182A7050}", &clsid);
	
	if(SUCCEEDED(hRes))
		hRes = AfxGetClassIDFromString("{7F0DFAA2-F56D-11D0-A980-0020182A7050}", &iid);

	if(SUCCEEDED(hRes))
		SetNewData(clsid, iid);
}

//-----------------------------------------------------------------------------------
void CLevelViewerDlg::OnGas() 
{
	m_sLastCalled = _T("CheckedGas");
	CLSID clsid;
	IID   iid;	
	HRESULT hRes = AfxGetClassIDFromString("{8A544DC6-F531-11D0-A980-0020182A7050}", &clsid);
	
	if(SUCCEEDED(hRes))
		hRes = AfxGetClassIDFromString("{8A544DC5-F531-11D0-A980-0020182A7050}", &iid);
		

	if(SUCCEEDED(hRes))
		SetNewData(clsid, iid);
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
		//we are checking the fish tank now
		sItem = _T("Fish Tank");
	}
	else //m_sLastCalled == _T("CheckedGas")
	{
		//we are checking the fish tank now
		sItem = _T("Gas Tank");
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
