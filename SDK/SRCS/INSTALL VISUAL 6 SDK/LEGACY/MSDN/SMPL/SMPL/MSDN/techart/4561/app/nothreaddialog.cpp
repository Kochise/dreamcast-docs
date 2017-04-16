// NoThreadDialog.cpp : implementation file
//

#include "stdafx.h"
#include "threadlibtest.h"
#include "NoThreadDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNoThreadDialog dialog


CNoThreadDialog::CNoThreadDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CNoThreadDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNoThreadDialog)
	m_NoThreads = 0;
	m_Delay = 0;
	//}}AFX_DATA_INIT
}


void CNoThreadDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNoThreadDialog)
	DDX_Text(pDX, IDC_EDIT1, m_NoThreads);
	DDV_MinMaxInt(pDX, m_NoThreads, 0, 2000);
	DDX_Text(pDX, IDC_DELAYFACTOR, m_Delay);
	DDV_MinMaxInt(pDX, m_Delay, 0, 50000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNoThreadDialog, CDialog)
	//{{AFX_MSG_MAP(CNoThreadDialog)
	ON_BN_CLICKED(IDC_IOBOUND, OnIobound)
	ON_BN_CLICKED(IDM_CPUBOUND, OnCpubound)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNoThreadDialog message handlers

void CNoThreadDialog::OnIobound() 
{
    m_iCompType=IDC_IOBOUND;	
}

void CNoThreadDialog::OnCpubound() 
{
	m_iCompType=IDM_CPUBOUND;
	
}
