//---------------------------------------------------------------------------------
// TVXSampDlg.cpp : TV Viewer sample application
//---------------------------------------------------------------------------------
// Copyright (C) 1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Broadcast Architecture Programmer's Reference.
// For more information about writing applications that interact
// with TV Viewer, see `` Creating TV Viewer Controls ``
// in the Broadcast Architecture Programmer's Reference.
//
//

#include "stdafx.h"
#include "TVXSamp.h"
#include "TVXSampDlg.h"
#include "DlgProxy.h"
#include "Tvdisp.h"
#include <atlbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

ITVViewer *TVX;

/////////////////////////////////////////////////////////////////////////////
// CTVXSampDlg dialog

IMPLEMENT_DYNAMIC(CTVXSampDlg, CDialog);

CTVXSampDlg::CTVXSampDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTVXSampDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTVXSampDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CTVXSampDlg::~CTVXSampDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CTVXSampDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTVXSampDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTVXSampDlg, CDialog)
	//{{AFX_MSG_MAP(CTVXSampDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTVXSampDlg message handlers

BOOL CTVXSampDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTVXSampDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTVXSampDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CTVXSampDlg::OnClose() 
{
	if (CanExit())
		CDialog::OnClose();
}

void CTVXSampDlg::OnOK() 
{
	if (CanExit())
		CDialog::OnOK();
}

void CTVXSampDlg::OnCancel() 
{
	if (CanExit())
		CDialog::OnCancel();
}

BOOL CTVXSampDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}

//-----------< event handler that toggles TV Viewer mode >-----------
//---------------------------------------------------------------------------------
/*
The following code implements an event handler 
that toggles TV Viewer between desktop and full 
screen mode when the user clicks Button1. It checks 
which mode TV Viewer is displaying in, and toggles 
it to the other mode. For example, if TV Viewer is 
in desktop mode, this method sets it to full screen
mode and vide versa.
*/

void CTVXSampDlg::OnButton1() 
{
	
	//check whether TV Viewer is in 
	//full screen mode
	if (TVX->IsTVMode())
	{
		//if it is, 
		//change the mode to desktop
		TVX->SetTVMode(false);
	}
	else	
	{
		//if it is not,
		//change the mode to full screen
		TVX->SetTVMode(true);
	}
	
}


//-----< event handler that tunes TV Viewer to a new channel >------
//---------------------------------------------------------------------------------
/*
The following code implements an event handler 
that tunes TV Viewer to the TV configuration 
channel when they click Button2. 

The TV configuration channel was chosen for 
this example because it is installed with TV Viewer 
and is present on all client machines. 
*/
void CTVXSampDlg::OnButton2() 
{

	//Tune TVViewer to channel 1 of tuning space -2
	//the audio and video substreams have been set to 
	//-1, causing TV Viewer to use the default values.

	TVX->Tune(-2,1,-1,-1,NULL);

}


//---------< event handler that tunes to a previous channel >-----------
//---------------------------------------------------------------------------------
/*
The following code implements an event handler that 
tunes TV Viewer to the previously displayed channel 
when the user clicks Button4. 
*/

void CTVXSampDlg::OnButton4() 
{
	long lTuningSpacePrev;
	long lChannelNumberPrev;
	long lAudioStreamPrev;
	long lVideoStreamPrev;
	BSTR bstrIPAddressPrev;

	//get the tuning information about the previous channel
	//from TV Viewer
	TVX->GetPreviousTuningInfo(&lTuningSpacePrev, &lChannelNumberPrev,
			 &lVideoStreamPrev, &lAudioStreamPrev, &bstrIPAddressPrev);

	if ((lTuningSpacePrev != NULL) && (lChannelNumberPrev != NULL))
	{
		//Tune TV Viewer to the previous channel
		TVX->Tune(lTuningSpacePrev, lChannelNumberPrev,
				lVideoStreamPrev, lAudioStreamPrev, (LPCTSTR) bstrIPAddressPrev);
	}

}

