// spritedl.cpp : implementation file
//

#include "stdafx.h"
#include "anim32.h"
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
	m_bSelectable = FALSE;
	m_vx = 0;
	m_vy = 0;
	m_x = 0;
	m_y = 0;
	m_z = 0;
	m_phases = 0;
	//}}AFX_DATA_INIT
}

void CSpriteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpriteDlg)
	DDX_Control(pDX, IDC_W, m_wndWidth);
	DDX_Control(pDX, IDC_H, m_wndHeight);
	DDX_Check(pDX, IDC_SELECTABLE, m_bSelectable);
	DDX_Text(pDX, IDC_VX, m_vx);
	DDX_Text(pDX, IDC_VY, m_vy);
	DDX_Text(pDX, IDC_X, m_x);
	DDX_Text(pDX, IDC_Y, m_y);
	DDX_Text(pDX, IDC_Z, m_z);
	DDX_Text(pDX, IDC_PHASES, m_phases);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSpriteDlg, CDialog)
	//{{AFX_MSG_MAP(CSpriteDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpriteDlg message handlers
