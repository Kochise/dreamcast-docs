// morepfd.cpp : implementation file
//

#include "stdafx.h"
#include "mygl.h"
#include "morepfd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMorePFD dialog

CMorePFD::CMorePFD(CWnd* pParent /*=NULL*/)
	: CDialog(CMorePFD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMorePFD)
	m_accumalphabits = 0;
	m_accumbluebits = 0;
	m_accumgreenbits = 0;
	m_accumredbits = 0;
	m_alphabits = 0;
	m_alphashift = 0;
	m_bluebits = 0;
	m_blueshift = 0;
	m_damagemask = 0;
	m_greenbits = 0;
	m_greenshift = 0;
	m_layermask = 0;
	m_redbits = 0;
	m_redshift = 0;
	m_visiblemask = 0;
	//}}AFX_DATA_INIT
}

void CMorePFD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMorePFD)
	DDX_Text(pDX, IDC_ACCUMALPHABITS, m_accumalphabits);
	DDV_MinMaxInt(pDX, m_accumalphabits, 0, 32);
	DDX_Text(pDX, IDC_ACCUMBLUEBITS, m_accumbluebits);
	DDV_MinMaxInt(pDX, m_accumbluebits, 0, 32);
	DDX_Text(pDX, IDC_ACCUMGREENBITS, m_accumgreenbits);
	DDV_MinMaxInt(pDX, m_accumgreenbits, 0, 32);
	DDX_Text(pDX, IDC_ACCUMREDBITS, m_accumredbits);
	DDX_Text(pDX, IDC_ALPHABITS, m_alphabits);
	DDV_MinMaxInt(pDX, m_alphabits, 0, 32);
	DDX_Text(pDX, IDC_ALPHASHIFT, m_alphashift);
	DDV_MinMaxInt(pDX, m_alphashift, 0, 32);
	DDX_Text(pDX, IDC_BLUEBITS, m_bluebits);
	DDV_MinMaxInt(pDX, m_bluebits, 0, 32);
	DDX_Text(pDX, IDC_BLUESHIFT, m_blueshift);
	DDV_MinMaxInt(pDX, m_blueshift, 0, 32);
	DDX_Text(pDX, IDC_DAMAGEMASK, m_damagemask);
	DDX_Text(pDX, IDC_GREENBITS, m_greenbits);
	DDV_MinMaxInt(pDX, m_greenbits, 0, 32);
	DDX_Text(pDX, IDC_GREENSHIFT, m_greenshift);
	DDV_MinMaxInt(pDX, m_greenshift, 0, 32);
	DDX_Text(pDX, IDC_LAYERMASK, m_layermask);
	DDX_Text(pDX, IDC_REDBITS, m_redbits);
	DDV_MinMaxInt(pDX, m_redbits, 0, 32);
	DDX_Text(pDX, IDC_REDSHIFT, m_redshift);
	DDV_MinMaxInt(pDX, m_redshift, 0, 32);
	DDX_Text(pDX, IDC_VISIBLEMASK, m_visiblemask);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMorePFD, CDialog)
	//{{AFX_MSG_MAP(CMorePFD)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMorePFD message handlers

BOOL CMorePFD::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	LPPIXELFORMATDESCRIPTOR ppfd = (LPPIXELFORMATDESCRIPTOR)m_ppfd;

	CenterWindow(NULL);
 	SetDlgItemInt(IDC_ACCUMALPHABITS, ppfd->cAccumAlphaBits, TRUE);
 	SetDlgItemInt(IDC_ACCUMBLUEBITS, ppfd->cAccumBlueBits, TRUE);
 	SetDlgItemInt(IDC_ACCUMGREENBITS, ppfd->cAccumGreenBits, TRUE);
 	SetDlgItemInt(IDC_ACCUMREDBITS, ppfd->cAccumRedBits, TRUE);
 	SetDlgItemInt(IDC_ALPHABITS, ppfd->cAlphaBits, TRUE);
 	SetDlgItemInt(IDC_ALPHASHIFT, ppfd->cAlphaShift, TRUE);
 	SetDlgItemInt(IDC_BLUEBITS, ppfd->cBlueBits, TRUE);
 	SetDlgItemInt(IDC_BLUESHIFT, ppfd->cBlueShift, TRUE);
 	SetDlgItemInt(IDC_DAMAGEMASK, ppfd->dwDamageMask, TRUE);
 	SetDlgItemInt(IDC_GREENBITS, ppfd->cGreenBits, TRUE);
 	SetDlgItemInt(IDC_GREENSHIFT, ppfd->cGreenShift, TRUE);
 	SetDlgItemInt(IDC_LAYERMASK, ppfd->dwLayerMask, TRUE);
 	SetDlgItemInt(IDC_REDBITS, ppfd->cRedBits, TRUE);
 	SetDlgItemInt(IDC_REDSHIFT, ppfd->cRedShift, TRUE);
 	SetDlgItemInt(IDC_VISIBLEMASK, ppfd->dwVisibleMask, TRUE);
    
	return TRUE;  // return TRUE  unless you set the focus to a control
}
