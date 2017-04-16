// deletedi.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "dbdialog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeleteDialog dialog


CDeleteDialog::CDeleteDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDeleteDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeleteDialog)
	m_DeleteIndex = 0;
	//}}AFX_DATA_INIT
}


void CDeleteDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeleteDialog)
	DDX_Text(pDX, IDC_EDIT1, m_DeleteIndex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDeleteDialog, CDialog)
	//{{AFX_MSG_MAP(CDeleteDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDeleteDialog message handlers

// addrecor.cpp : implementation file
//

/////////////////////////////////////////////////////////////////////////////
// CAddrecordDialog dialog


CAddrecordDialog::CAddrecordDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAddrecordDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddrecordDialog)
	m_Val1 = 0;
	m_Val2 = 0;
	//}}AFX_DATA_INIT
}


void CAddrecordDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddrecordDialog)
	DDX_Text(pDX, IDC_EDIT1, m_Val1);
	DDX_Text(pDX, IDC_EDIT2, m_Val2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddrecordDialog, CDialog)
	//{{AFX_MSG_MAP(CAddrecordDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAddrecordDialog message handlers
