// spritedl.cpp : implementation file
//

#include "stdafx.h"
#include "gravity.h"
#include "spritedl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpriteDlg dialog

CSpriteDlg::CSpriteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpriteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpriteDlg)
	m_phases = 0;
	m_vx = 0.0;
	m_vy = 0.0;
	m_x = 0.0;
	m_y = 0.0;
	m_mass = 0.0;
	//}}AFX_DATA_INIT
}

void CSpriteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpriteDlg)
	DDX_Text(pDX, IDC_PHASES, m_phases);
	DDX_Text(pDX, IDC_VX, m_vx);
	DDX_Text(pDX, IDC_VY, m_vy);
	DDX_Text(pDX, IDC_X, m_x);
	DDX_Text(pDX, IDC_Y, m_y) ;
	DDX_Text(pDX, IDC_MASS, m_mass);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSpriteDlg, CDialog)
	//{{AFX_MSG_MAP(CSpriteDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpriteDlg message handlers
