// myobjdlg.cpp : implementation file
//

#include "stdafx.h"
#include "mfcclip.h"
#include "myobjdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyObjDlg dialog

CMyObjDlg::CMyObjDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyObjDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyObjDlg)
	m_strText = "";
	//}}AFX_DATA_INIT
}

void CMyObjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyObjDlg)
	DDX_Text(pDX, IDC_TEXT, m_strText);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyObjDlg, CDialog)
	//{{AFX_MSG_MAP(CMyObjDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyObjDlg message handlers
