// timedlg.cpp : implementation file
//

#include "stdafx.h"
#include "gravity.h"
#include "timedlg.h"
#include "uni.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeDlg dialog

CTimeDlg::CTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTimeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimeDlg)
	m_time = 0;
	m_SecsPerTick = 0;
	//}}AFX_DATA_INIT
}

void CTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimeDlg)
	DDX_Text(pDX, IDC_TIME, m_time);
	DDX_Text(pDX, IDC_SECS_PER_TICK, m_SecsPerTick);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTimeDlg, CDialog)
	//{{AFX_MSG_MAP(CTimeDlg)
	ON_BN_CLICKED(IDC_DEFAULT, OnClickedDefault)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeDlg message handlers

void CTimeDlg::OnClickedDefault()
{
	m_time = G_TIME ;
	m_SecsPerTick = G_SECS_PER_TICK ;
	UpdateData(FALSE) ;	
}
