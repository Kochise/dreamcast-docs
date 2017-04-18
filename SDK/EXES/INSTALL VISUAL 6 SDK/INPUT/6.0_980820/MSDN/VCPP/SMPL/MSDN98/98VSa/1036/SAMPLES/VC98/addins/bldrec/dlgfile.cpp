// DlgFile.cpp : implementation file
//

#include "stdafx.h"
#include "bldrec.h"
#include "DlgFile.h"
#include <afxdlgs.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFile dialog


CDlgFile::CDlgFile(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFile::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFile)
	m_strFile = _T("");
	//}}AFX_DATA_INIT
}


void CDlgFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFile)
	DDX_Control(pDX, IDC_EDITFILE, m_ctlEditFile);
	DDX_Text(pDX, IDC_EDITFILE, m_strFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFile, CDialog)
	//{{AFX_MSG_MAP(CDlgFile)
	ON_BN_CLICKED(IDC_BUTTONBROWSE, OnButtonbrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFile message handlers

CString& CDlgFile::GetFile()
{
	return(m_strFile);
}

void CDlgFile::OnOK() 
{
	if (m_strFile.ReverseFind(_T('.')) < 0)
	{
		m_strFile += _T(".txt");
	}
	CDialog::OnOK();
}

void CDlgFile::SetFile(LPCTSTR szFile)
{
	m_strFile = szFile;
}

BOOL CDlgFile::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgFile::OnButtonbrowse() 
{
	CString strFilter, strExt;
	strFilter.LoadString(IDS_TXTFILTER);
	CFileDialog dlgGetFile(FALSE, NULL, NULL, OFN_EXPLORER,
		strFilter,
		this);
	
	if (dlgGetFile.DoModal() == IDOK)
	{
		m_strFile = dlgGetFile.GetPathName();
		if (m_strFile.ReverseFind(_T('.')) < 0)
		{
			strExt.LoadString(IDS_DEFAULT_EXTENSION);
			m_strFile += strExt;
		}
		m_ctlEditFile.SetWindowText(m_strFile);
	}
}
