// AccessTypeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SurfBear.h"
#include "ATypeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAccessTypeDlg dialog


CAccessTypeDlg::CAccessTypeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAccessTypeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAccessTypeDlg)
	m_iRadioBtns = -1;
	m_strProxyServer = _T("");
	//}}AFX_DATA_INIT
}


void CAccessTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAccessTypeDlg)
	DDX_Radio(pDX, IDC_RADIO1, m_iRadioBtns);
	DDX_Text(pDX, IDC_EDIT_SERVERNAME, m_strProxyServer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAccessTypeDlg, CDialog)
	//{{AFX_MSG_MAP(CAccessTypeDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAccessTypeDlg message handlers
