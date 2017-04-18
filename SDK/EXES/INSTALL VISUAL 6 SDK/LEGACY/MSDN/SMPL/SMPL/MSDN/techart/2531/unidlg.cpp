// unidlg.cpp : implementation file
//

#include "stdafx.h"
#include "gravity.h"
#include "unidlg.h"
#include "uni.h" //der

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUniDlg dialog

CUniDlg::CUniDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUniDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUniDlg)
	m_G = 0;
	m_height = 0;
	m_width = 0;
	//}}AFX_DATA_INIT
}

void CUniDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUniDlg)
	DDX_Text(pDX, IDC_G, m_G);
	DDX_Text(pDX, IDC_HEIGHT, m_height);
	DDX_Text(pDX, IDC_WIDTH, m_width);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUniDlg, CDialog)
	//{{AFX_MSG_MAP(CUniDlg)
	ON_BN_CLICKED(IDC_DEFAULT, OnClickedDefault)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUniDlg message handlers

void CUniDlg::OnClickedDefault()
{
	m_G = G_G ;
	m_height = G_HEIGHT ;
	m_width = G_WIDTH ;	
	UpdateData(FALSE) ;
}
