// DlgNote.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "DlgNote.h"
#include <afxdlgs.h>
#include "booknote.h"
#include "markit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNote dialog


CDlgNote::CDlgNote(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNote::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNote)
	m_strNote = _T("");
	m_strLogFile = _T("");
	m_fEcho = FALSE;
	//}}AFX_DATA_INIT

	m_pMarkIt = NULL;

}


void CDlgNote::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNote)
	DDX_Text(pDX, IDC_EDITNOTE, m_strNote);
	DDV_MaxChars(pDX, m_strNote, 1024);
	DDX_Text(pDX, IDC_EDITFILE, m_strLogFile);
	DDX_Check(pDX, IDC_CHECKECHO, m_fEcho);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNote, CDialog)
	//{{AFX_MSG_MAP(CDlgNote)
	ON_BN_CLICKED(IDC_BUTTONBROWSE, OnButtonbrowse)
	ON_BN_CLICKED(IDC_BUTTON_DUMP, OnButtonDump)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNote message handlers

BOOL CDlgNote::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgNote::OnButtonbrowse() 
{
	CFileDialog dlgGetFile(FALSE, NULL, NULL, OFN_EXPLORER,
		_T("txt files(*.txt)|*.txt|All Files (*.*)|*.*||"),
		this);
	
	if (dlgGetFile.DoModal() == IDOK)
	{
		UpdateData();
		m_strLogFile = dlgGetFile.GetPathName();
		UpdateData(FALSE);
	}
}

void CDlgNote::OnOK() 
{
	if (m_strLogFile.ReverseFind(_T('.')) < 0)
	{
		m_strLogFile += _T(".txt");
	}
	CDialog::OnOK();
}

void CDlgNote::OnButtonDump() 
{
	if (m_pMarkIt)
	{
		m_pMarkIt->Dump(m_strLogFile);
	}
}
