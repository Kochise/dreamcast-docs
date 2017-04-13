// DlgBrkPnts.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "DlgBrkPnts.h"
#include <afxdlgs.h>
#include "dlgAdvanced.h"
#include "brkpntmgr.h"
#include "brkpnts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBrkPnts dialog


CDlgBrkPnts::CDlgBrkPnts(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBrkPnts::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBrkPnts)
	m_fSaveOnlyEnabled = FALSE;
	m_strFile = _T("");
	//}}AFX_DATA_INIT
	m_pBrkPnts = NULL;
}


void CDlgBrkPnts::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBrkPnts)
	DDX_Control(pDX, IDC_EDITCOMMENTS, m_ctlEditComment);
	DDX_Control(pDX, IDC_COUNT, m_ctlCount);
	DDX_Check(pDX, IDC_CHECKSAVEONLYENABLED, m_fSaveOnlyEnabled);
	DDX_Text(pDX, IDC_EDITFILE, m_strFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBrkPnts, CDialog)
	//{{AFX_MSG_MAP(CDlgBrkPnts)
	ON_BN_CLICKED(IDC_BUTTONBROWSE, OnButtonbrowse)
	ON_BN_CLICKED(IDC_BUTTONLOAD, OnButtonload)
	ON_BN_CLICKED(IDC_BUTTONCLEAR, OnButtonclear)
	ON_BN_CLICKED(IDB_OUTPUT, OnOutput)
	ON_BN_CLICKED(IDSAVE, OnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBrkPnts message handlers

void CDlgBrkPnts::OnButtonbrowse() 
{
	CFileDialog dlgGetFile(FALSE, NULL, NULL, OFN_EXPLORER,
		_T("brk files(*.brk)|*.brk|All Files (*.*)|*.*||"),
		this);
	
	if (dlgGetFile.DoModal() == IDOK)
	{
		UpdateData();
		m_strFile = dlgGetFile.GetPathName();
		UpdateData(FALSE);
	}
}

void CDlgBrkPnts::OnButtonload() 
{
	CString strComment;

	if (m_pBrkPnts)
	{
		UpdateData();
		m_pBrkPnts->Load(m_strFile, strComment);
		m_ctlEditComment.SetWindowText(strComment);
		UpdateInfo();
	}
}

BOOL CDlgBrkPnts::OnInitDialog() 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CDialog::OnInitDialog();
	
	UpdateInfo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgBrkPnts::OnButtonclear() 
{
	if (m_pBrkPnts)
	{
		m_pBrkPnts->ClearAll();
		UpdateInfo();
	}
}

void CDlgBrkPnts::OnOutput() 
{
	CString strComment;

	if (m_pBrkPnts)
	{
		UpdateData();
		m_ctlEditComment.GetWindowText(strComment);
		m_pBrkPnts->Save(TRUE, NULL, m_fSaveOnlyEnabled, strComment);
	}
}

void CDlgBrkPnts::UpdateInfo()
{
	CString strInfo;
	long lEnabled, lTotal;

	if (m_pBrkPnts)
	{
		m_pBrkPnts->GetCounts(lTotal, lEnabled);
		strInfo.Format(IDS_INFO, lEnabled, lTotal);
		m_ctlCount.SetWindowText(strInfo);
	}
}

void CDlgBrkPnts::OnSave() 
{
	CString strComment;

	if (m_pBrkPnts)
	{
		UpdateData();
		m_ctlEditComment.GetWindowText(strComment);
		m_pBrkPnts->Save(FALSE, m_strFile, m_fSaveOnlyEnabled, strComment);
	}
}
