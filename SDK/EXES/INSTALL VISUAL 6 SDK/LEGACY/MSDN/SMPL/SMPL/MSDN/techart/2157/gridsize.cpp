// gridsize.cpp : implementation file
//

#include "stdafx.h"
#include "dldetect.h"
#include "gridsize.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// gridsize dialog

gridsize::gridsize(CWnd* pParent /*=NULL*/)
	: CDialog(gridsize::IDD, pParent)
{
	//{{AFX_DATA_INIT(gridsize)
	m_GridSize = 0;
	//}}AFX_DATA_INIT
}

void gridsize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(gridsize)
	DDX_Text(pDX, IDC_EDIT1, m_GridSize);
	DDV_MinMaxInt(pDX, m_GridSize, 10, 1000);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(gridsize, CDialog)
	//{{AFX_MSG_MAP(gridsize)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// gridsize message handlers
