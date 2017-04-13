// DlgSave.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "DlgSave.h"
#include <afxdlgs.h>
#include "Brkpntmgr.h"
#include "brkpnts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSave dialog


CDlgSave::CDlgSave(CWnd* pParent /*=NULL*/)
	: CSubDialog(CDlgSave::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSave)
	m_fSaveOnlyEnabled = FALSE;
	m_strFile = _T("");
	m_fOutputWnd = FALSE;
	m_strComment = _T("");
	m_fOld = FALSE;
	m_strStats = _T("");
	//}}AFX_DATA_INIT

}

CDlgSave::~CDlgSave()
{
}


BOOL CDlgSave::Create(CWnd *pParent)
{
	BOOL fOK;
	fOK = CDialog::Create(IDD, pParent);
	return(fOK);
}

void CDlgSave::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSave)
	DDX_Check(pDX, IDC_CHECKSAVEONLYENABLED, m_fSaveOnlyEnabled);
	DDX_Text(pDX, IDC_EDITFILE, m_strFile);
	DDX_Text(pDX, IDC_EDITCOMMENT, m_strComment);
	DDX_Text(pDX, IDC_STATS, m_strStats);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSave, CDialog)
	//{{AFX_MSG_MAP(CDlgSave)
	ON_BN_CLICKED(IDC_BUTTONBROWSE, OnButtonbrowse)
	ON_BN_CLICKED(IDC_BUTTONLOAD, OnButtonload)
	ON_BN_CLICKED(IDC_BUTTONCLEAR, OnButtonclear)
	ON_BN_CLICKED(IDOK, OnOK)
	ON_BN_CLICKED(IDC_BTNOUTPUTWND, OnBtnoutputwnd)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(ID_SAVE, OnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSave message handlers

void CDlgSave::OnButtonbrowse() 
{
	CFileDialog dlgGetFile(FALSE, NULL, NULL, OFN_EXPLORER,
		_T("brk files(*.brk)|*.brk|All Files (*.*)|*.*||"),
		this);
	
	if (dlgGetFile.DoModal() == IDOK)
	{
		UpdateData();
		m_strFile = dlgGetFile.GetPathName();
		if (m_strFile.ReverseFind(_T('.')) == -1)
		{
			m_strFile += _T(".brk"); // add the missing extension
		}

		UpdateData(FALSE);
	}
}

void CDlgSave::OnButtonload() 
{
	UpdateData(TRUE);
	if (!m_strFile.IsEmpty() && m_pbrksmgr)
	{
		m_strComment.Empty();
		m_pbrksmgr->Load(m_strFile, m_strComment, m_fOld);	
		SetStats();
		UpdateData(FALSE);
	}
}

BOOL CDlgSave::OnInitDialog() 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CDialog::OnInitDialog();

	_ASSERTE(m_pbrksmgr);
	SetStats();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgSave::OnButtonclear() 
{
	if (m_pbrksmgr)
	{
		m_pbrksmgr->ClearAll();
		SetStats(TRUE);
	}	
}

void CDlgSave::OnOK()
{
	CDialog::OnOK();
}

void CDlgSave::OnSave() 
{
	UpdateData(TRUE);
	if (!m_strFile.IsEmpty() && m_pbrksmgr)
	{
		m_pbrksmgr->Save(FALSE, m_strFile, m_fSaveOnlyEnabled, m_strComment);	
	}
	
}

void CDlgSave::OnBtnoutputwnd() 
{
	UpdateData(TRUE);
	if (m_pbrksmgr)
	{
		m_pbrksmgr->Save(TRUE, "\0", m_fSaveOnlyEnabled, m_strComment);	
	}
	
}

void CDlgSave::SetStats(BOOL fUpdate /*= FALSE*/)
{
	long lTotal, lEnabled;
	if (m_pbrksmgr)
	{
		m_pbrksmgr->GetCounts(lTotal, lEnabled);
		if (lTotal > 0)
		{
			m_strStats.Format(_T("Total: %ld, Enabled: %ld"), lTotal, lEnabled);
		}
		else
		{
			m_strStats = _T("No Breakpoints Set");
		}
	}
	else
	{
		m_strStats = _T("No Breakpoints Set");
	}
	if (fUpdate)
	{
		UpdateData(FALSE);
	}
}

void CDlgSave::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if (bShow)
	{
		SetStats(TRUE);
	}
}
