// EntryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LogView.h"
#include "EntryDlg.h"
#include "time.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewEntryDlg dialog


CNewEntryDlg::CNewEntryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewEntryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewEntryDlg)
	m_strDate = _T("");
	m_strDesc = _T("(none)");
	m_dFreq = 0.0;
	m_strStation = _T("(unknown)");
	m_strTime = _T("");
	//}}AFX_DATA_INIT
}


void CNewEntryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewEntryDlg)
	DDX_Control(pDX, IDC_MODE, m_cbMode);
	DDX_Text(pDX, IDC_DATE, m_strDate);
	DDX_Text(pDX, IDC_DESC, m_strDesc);
	DDX_Text(pDX, IDC_FREQ, m_dFreq);
	DDX_Text(pDX, IDC_STATION, m_strStation);
	DDX_Text(pDX, IDC_TIME, m_strTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewEntryDlg, CDialog)
	//{{AFX_MSG_MAP(CNewEntryDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewEntryDlg message handlers

BOOL CNewEntryDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Get the current time and date
    time_t lt;
    time(&lt);
    struct tm* pl = localtime(&lt);
	char buf[64];
	sprintf(buf, "%d/%d/%d", pl->tm_mon+1, pl->tm_mday, pl->tm_year);
	m_strDate = buf;
	m_Date.SetDate(pl->tm_year, pl->tm_mon+1, pl->tm_mday);
	sprintf(buf, "%2.2d:%2.2d", pl->tm_hour, pl->tm_min);
	m_strTime = buf;

	// Fill the mode combo box with the list
	m_cbMode.AddString("AM");
	m_cbMode.AddString("FM");
	m_cbMode.AddString("CW");
	m_cbMode.AddString("USB");
	m_cbMode.AddString("LSB");
	m_cbMode.SetCurSel(0);

	// Update the display from the local data
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CNewEntryDlg::OnOK() 
{
	// Get the updated data
	UpdateData(TRUE);

	// Get the mode selection
	m_cbMode.GetWindowText(m_strMode); 

	// Close the dialog
	CDialog::OnOK();
}

