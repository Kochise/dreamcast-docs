/*****************************************************************************
  File: chartdlg.cpp

  Purpose: Dialog box used for selecting a chart type

  Functions: CChartDlg::OnInitDialog    - Initializes combobox
             CChartDlg::OnOK            - Return selected chart type 

  Development Team: Steve Roeder

  Written by Microsoft Product Support Services, Languages Developer Support
  Copyright (c) 1995 Microsoft Corporation. All rights reserved.
\****************************************************************************/

// chartdlg.cpp : implementation file
//

#include "stdafx.h"
#include "XlAuto.h"
#include "chartdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChartDlg dialog


CChartDlg::CChartDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChartDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChartDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CChartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChartDlg)
	DDX_Control(pDX, IDC_COMBO1, m_cbChart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChartDlg, CDialog)
	//{{AFX_MSG_MAP(CChartDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChartDlg message handlers

/************************************************************************
  Function:	CChartDlg::OnInitDialog

  Purpose: Initialize the contents of the dialog box

  Parameters: None

  Returns: TRUE

  Comments:	This functions first resets the size of the combobox contained 
            in the dialog box, then adds each of the chart types to the 
		    combobox.

  History:

  Date     Comment                                           Initials
  ======== ================================================= ========
  04/13/95 Created                                             SJR
\***********************************************************************/

BOOL CChartDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRect rc;
	m_cbChart.GetClientRect(&rc);
	m_cbChart.SetWindowPos(NULL, 0, 0, rc.right, 75, SWP_NOMOVE | SWP_NOZORDER);

	m_cbChart.AddString("Area");
	m_cbChart.AddString("Bar");
	m_cbChart.AddString("Column");
	m_cbChart.AddString("Line");
	m_cbChart.AddString("Pie");
	m_cbChart.AddString("Radar");
	m_cbChart.AddString("XYScatter");
	m_cbChart.AddString("Combination");
	m_cbChart.AddString("3DArea");
	m_cbChart.AddString("3DBar");
	m_cbChart.AddString("3DColumn");
	m_cbChart.AddString("3DLine");
	m_cbChart.AddString("3DPie");
	m_cbChart.AddString("3DSurface");
	m_cbChart.AddString("Doughnut");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// CChartDlg::OnOK
// Sets m_cbIndex member variable when the OK button is pushed
void CChartDlg::OnOK() 
{
	m_cbIndex = m_cbChart.GetCurSel();	
	
	CDialog::OnOK();
}
