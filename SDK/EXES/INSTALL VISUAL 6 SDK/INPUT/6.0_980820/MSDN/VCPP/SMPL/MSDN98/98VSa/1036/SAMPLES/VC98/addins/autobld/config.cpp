// Config.cpp : implementation file
//

// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.

#include "stdafx.h"
#include "AutoBld.h"
#include "Config.h"
#include "Workspcs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigure dialog


CConfigure::CConfigure(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigure::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigure)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConfigure::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigure)
	DDX_Control(pDX, IDC_STATUSWARNERR, m_StatusWarnErr);
	DDX_Control(pDX, IDC_STATUSTEXT, m_StatusText);
	DDX_Control(pDX, IDC_STATUSLINE, m_StatusLine);
	DDX_Control(pDX, IDC_SENDTO, m_SendTo);
	DDX_Control(pDX, IDC_SENDTEXT, m_SendText);
	DDX_Control(pDX, IDC_SENDMAIL, m_SendMail);
	DDX_Control(pDX, IDC_SENDGROUP, m_SendGroup);
	DDX_Control(pDX, IDC_FILENAMETEXT, m_FileName);
	DDX_Control(pDX, IDC_CLOSEWHENDONE, m_CloseWhenDone);
	DDX_Control(pDX, IDC_BROWSE, m_Browse);
	DDX_Control(pDX, IDC_BODYGROUP, m_BodyGroup);
	DDX_Control(pDX, IDC_BODYFILENAME, m_BodyFileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigure, CDialog)
	//{{AFX_MSG_MAP(CConfigure)
	ON_BN_CLICKED(IDC_WORKSPACES, OnWorkspaces)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_SENDFILEASBODY, OnSendFileAsBody)
	ON_BN_CLICKED(IDC_BLANKBODY, OnBlankBody)
	ON_BN_CLICKED(IDC_SENDMAIL, OnSendMail)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigure message handlers

void CConfigure::OnWorkspaces()
{
	//The user wishes to configure which workspaces should be built.
	CWorkspaces Workspaces;
	Workspaces.DoModal();
}

void CConfigure::OnBrowse()
{
	//The user wants to browse for a file to send as the message body
	CString strFileSpec;
	strFileSpec.LoadString(IDS_TEXTFILES);
	CFileDialog Browser(TRUE, "", "", OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
			strFileSpec);
	if (Browser.DoModal() == IDOK)
	{
		m_strFileToSend = Browser.GetPathName();
		m_BodyFileName.SetWindowText(m_strFileToSend);
	}
}

void CConfigure::OnSendFileAsBody()
{
	//If the user does want to send a file as the message body,
	//then enable the file name edit box.
	m_FileName.EnableWindow(TRUE);
	m_BodyFileName.EnableWindow(TRUE);
	m_Browse.EnableWindow(TRUE);
}

void CConfigure::OnBlankBody()
{
	//If the user does not want to send a file as the message body,
	//then disable the file name edit box.
	m_FileName.EnableWindow(FALSE);
	m_BodyFileName.EnableWindow(FALSE);
	m_Browse.EnableWindow(FALSE);
}

void CConfigure::OnSendMail()
{
	m_bSendMail = (m_SendMail.GetCheck() == 1) ? TRUE : FALSE;
	m_StatusWarnErr.EnableWindow(m_bSendMail);
	m_StatusText.EnableWindow(m_bSendMail);
	m_StatusLine.EnableWindow(m_bSendMail);
	m_BodyFileName.EnableWindow(m_bSendMail);
	m_BodyGroup.EnableWindow(m_bSendMail);
	m_Browse.EnableWindow(m_bSendMail);
	m_SendGroup.EnableWindow(m_bSendMail);
	m_SendTo.EnableWindow(m_bSendMail);
	m_SendText.EnableWindow(m_bSendMail);
	((CButton*)GetDlgItem(IDC_EVERYCONFIG))->EnableWindow(m_bSendMail);
	((CButton*)GetDlgItem(IDC_ENTIREWORKSPACE))->EnableWindow(m_bSendMail);
	((CButton*)GetDlgItem(IDC_SENDFILEASBODY))->EnableWindow(m_bSendMail);
	((CButton*)GetDlgItem(IDC_BLANKBODY))->EnableWindow(m_bSendMail);
	((CButton*)GetDlgItem(IDC_FILENAMETEXT))->EnableWindow(m_bSendMail);
	if (m_bSendFile == TRUE)
	{
		((CButton*)GetDlgItem(IDC_SENDFILEASBODY))->SetCheck(1);
		m_FileName.EnableWindow(TRUE);
		m_BodyFileName.EnableWindow(TRUE);
		m_Browse.EnableWindow(TRUE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_BLANKBODY))->SetCheck(1);
		m_FileName.EnableWindow(FALSE);
		m_BodyFileName.EnableWindow(FALSE);
		m_Browse.EnableWindow(FALSE);
	}
}

void CConfigure::OnOK()
{
	// save this little flag for always.
	AfxGetApp()->WriteProfileInt(_T("Configure"), _T("SendMail"), m_bSendMail);

	m_SendTo.GetWindowText(m_strSendTo);

	if (m_SendMail.GetCheck() == 1)
	{
		if (m_strSendTo == _T(""))
			AfxMessageBox(IDS_NEEDMAILADDR);
		else
		{
			//Prepare to write data to the registry by checking the appropriate
			//  control to see what should be saved.
			m_StatusLine.GetWindowText(m_strStatusLine);
			m_bIncBuildResults = (m_StatusWarnErr.GetCheck() == 1) ? TRUE : FALSE;
			m_bSendMail = (m_SendMail.GetCheck() == 1) ? TRUE : FALSE;
			m_bMailOnEach = (((CButton*)GetDlgItem(IDC_EVERYCONFIG))->GetCheck()
						== 1) ? TRUE : FALSE;
			m_bSendFile = (((CButton*)GetDlgItem(IDC_SENDFILEASBODY))->GetCheck()
						== 1) ? TRUE : FALSE;
			m_bCloseWhenDone = (m_CloseWhenDone.GetCheck() == 1) ? TRUE : FALSE;

			//Here the data for general configuration of AutoBuild is saved
			//  for later use...
			AfxGetApp()->WriteProfileString(_T("Configure"), _T("SendTo"),
						m_strSendTo);
			AfxGetApp()->WriteProfileString(
						_T("Configure"), _T("StatusText"), m_strStatusLine);
			AfxGetApp()->WriteProfileInt(
						_T("Configure"), _T("MailOnEach"), m_bMailOnEach);
			AfxGetApp()->WriteProfileInt(
						_T("Configure"), _T("SendMail"), m_bSendMail);
			AfxGetApp()->WriteProfileInt(
						_T("Configure"), _T("IncludeBuildResults"),
						m_bIncBuildResults);
			AfxGetApp()->WriteProfileInt(
						_T("Configure"), _T("SendFile"), m_bSendFile);
			AfxGetApp()->WriteProfileInt(
						_T("Configure"), _T("CloseWhenDone"), m_bCloseWhenDone);
			AfxGetApp()->WriteProfileString(
						_T("Configure"), _T("FileToSend"), m_strFileToSend);


			CDialog::OnOK();
		}
	}
	else
		CDialog::OnOK();
}

BOOL CConfigure::OnInitDialog()
{
	CDialog::OnInitDialog();

	//This method checks for existing data values, and enables/disables
	//controls based on the corresponding value
	m_SendMail.SetCheck(m_bSendMail);
	if (m_bIncBuildResults == TRUE)
		m_StatusWarnErr.SetCheck(1);
	else
		m_StatusWarnErr.SetCheck(0);

	if (m_bMailOnEach == TRUE)
		((CButton*)GetDlgItem(IDC_EVERYCONFIG))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_ENTIREWORKSPACE))->SetCheck(1);

	((CButton*)GetDlgItem(IDC_CLOSEWHENDONE))->SetCheck(m_bCloseWhenDone);

	m_BodyFileName.SetWindowText(m_strFileToSend);
	if (m_bSendFile == TRUE)
	{
		((CButton*)GetDlgItem(IDC_SENDFILEASBODY))->SetCheck(1);
		m_FileName.EnableWindow(TRUE);
		m_BodyFileName.EnableWindow(TRUE);
		m_Browse.EnableWindow(TRUE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_BLANKBODY))->SetCheck(1);
		m_FileName.EnableWindow(FALSE);
		m_BodyFileName.EnableWindow(FALSE);
		m_Browse.EnableWindow(FALSE);
	}

	m_SendTo.SetWindowText(m_strSendTo);
	m_StatusLine.SetWindowText(m_strStatusLine);

	//This tangled mess is just a bunch of enabling/disabling windows,
	//setting up stored values, etc.
	m_StatusWarnErr.EnableWindow(m_bSendMail);
	m_StatusText.EnableWindow(m_bSendMail);
	m_StatusLine.EnableWindow(m_bSendMail);

	m_BodyGroup.EnableWindow(m_bSendMail);
	m_SendGroup.EnableWindow(m_bSendMail);
	m_SendTo.EnableWindow(m_bSendMail);
	m_SendText.EnableWindow(m_bSendMail);
	((CButton*)GetDlgItem(IDC_EVERYCONFIG))->EnableWindow(m_bSendMail);
	((CButton*)GetDlgItem(IDC_ENTIREWORKSPACE))->EnableWindow(m_bSendMail);
	((CButton*)GetDlgItem(IDC_SENDFILEASBODY))->EnableWindow(m_bSendMail);
	((CButton*)GetDlgItem(IDC_BLANKBODY))->EnableWindow(m_bSendMail);
	((CButton*)GetDlgItem(IDC_FILENAMETEXT))->EnableWindow(m_bSendMail);
	m_SendTo.SetWindowText(m_strSendTo);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
