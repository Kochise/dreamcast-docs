/////////////////////////////////////////////////////////////////////////////
// Options.cpp : implementation file
//

// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.

#include "stdafx.h"
#include "API2Help.h"
#include "Options.h"
#include <afxtempl.h>
#include <afxdlgs.h>
#include "APISplit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptions dialog


COptions::COptions(CString strSelectedAPI, CWnd* pParent /*=NULL*/)
	: CDialog(COptions::IDD, pParent)
{
	m_strPrototype = strSelectedAPI;
	//{{AFX_DATA_INIT(COptions)
	//}}AFX_DATA_INIT
}


void COptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptions)
	DDX_Control(pDX, IDC_TOPICIDEDIT, m_TopicID);
	DDX_Control(pDX, IDC_TOPICNAME, m_TopicName);
	DDX_Control(pDX, IDC_STATIC4, m_Static4);
	DDX_Control(pDX, IDC_STATIC3, m_Static3);
	DDX_Control(pDX, IDC_STATIC2, m_Static2);
	DDX_Control(pDX, IDC_STATIC1, m_Static1);
	DDX_Control(pDX, IDC_RTFFILENAME, m_RTFFileName);
	DDX_Control(pDX, IDC_RTF, m_RTF);
	DDX_Control(pDX, IDC_HTMLFILENAME, m_HTMLFileName);
	DDX_Control(pDX, IDC_HTML, m_HTML);
	DDX_Control(pDX, IDC_BROWSERTF, m_BrowseRTF);
	DDX_Control(pDX, IDC_BROWSEHTML, m_BrowseHTML);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptions, CDialog)
	//{{AFX_MSG_MAP(COptions)
	ON_BN_CLICKED(IDC_HTML, OnHTML)
	ON_BN_CLICKED(IDC_RTF, OnRTF)
	ON_BN_CLICKED(IDC_BROWSEHTML, OnBrowseHTML)
	ON_BN_CLICKED(IDC_BROWSERTF, OnBrowseRTF)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptions message handlers

void COptions::OnHTML()
{
	if (m_HTML.GetCheck() == 1)
	{
		m_Static3.EnableWindow();
		m_HTMLFileName.EnableWindow();
		m_BrowseHTML.EnableWindow();
	}
	else
	{
		m_Static3.EnableWindow(FALSE);
		m_HTMLFileName.EnableWindow(FALSE);
		m_BrowseHTML.EnableWindow(FALSE);
	}
}

void COptions::OnRTF()
{
	if (m_RTF.GetCheck() == 1)
	{
		m_Static1.EnableWindow();
		m_Static2.EnableWindow();
		m_Static4.EnableWindow();
		m_RTFFileName.EnableWindow();
		m_TopicID.EnableWindow();
		m_TopicName.EnableWindow();
		m_BrowseRTF.EnableWindow();
	}
	else
	{
		m_Static1.EnableWindow(FALSE);
		m_Static2.EnableWindow(FALSE);
		m_Static4.EnableWindow(FALSE);
		m_RTFFileName.EnableWindow(FALSE);
		m_TopicID.EnableWindow(FALSE);
		m_TopicName.EnableWindow(FALSE);
		m_BrowseRTF.EnableWindow(FALSE);
	}
}

void COptions::OnBrowseHTML()
{
	CString strFileSpec;
	strFileSpec.LoadString(IDS_HTMLFILESPEC);
	CFileDialog Browser(FALSE, "", "", OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
			strFileSpec);
	if (Browser.DoModal() == IDOK)
	{
		m_HTMLFileName.SetWindowText(Browser.GetPathName());
	}
}

void COptions::OnBrowseRTF()
{
	CString strFileSpec;
	strFileSpec.LoadString(IDS_RTFFILESPEC);
	CFileDialog Browser(FALSE, "", "", OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
			strFileSpec);
	if(Browser.DoModal() == IDOK)
	{
		m_RTFFileName.SetWindowText(Browser.GetPathName());
	}
}

void COptions::OnOK()
{
	if ((m_RTF.GetCheck() == 0) && (m_HTML.GetCheck() == 0))
	{
		CString strNoneSel;
		strNoneSel.LoadString(IDS_NONESEL);
		AfxMessageBox(strNoneSel);
		return;
	}
	else
	{
		BOOL bRTF = FALSE;
		BOOL bHTML = FALSE;
		CString strFuncName;
		CString strNewFunc;
		CString strReturn;
		CString strSuggestedReturn;
		CString strParameters;
		CArray<CString,CString> Scoping;
		CArray<CString,CString> ReturnsArray;
		CArray<CString,CString> ParamList;
		CArray<CString,CString> ParamNames;
		CArray<CString,CString> ParamDescription;
		int nAppendStar = 0;

		ConvertWSToSpace (m_strPrototype);

		//Remove all multiple instances of '  ' (double space).
		RemoveUnnecessary(m_strPrototype);
		int nBeginningOfParameters = GetParameters(strParameters, m_strPrototype,
				ParamList);

		strFuncName = m_strPrototype.Left(nBeginningOfParameters);
		GetListOfParamNames(ParamList, ParamNames);

		//At this point, all parameters have been located.
		//  Now find the function name
		strFuncName.TrimRight();
		strReturn = strFuncName;
		strFuncName = strFuncName.Right(strFuncName.GetLength()-strFuncName.ReverseFind(' '));
		strFuncName.TrimLeft();

		//Check to make sure there is a '(' and a ')', and the '(' is before the ')'
		//strFuncName

		//Now, we have a function name, but this function could be of the form
		//      class1::class2::...::classn::function. Try to split off each scope,
		//      and build a list of these scopings (this list is not used in this
		//  version).
		GetFunctAndScope(strFuncName, Scoping, strNewFunc);

		//Remove '*' from the function name, and count them for adding
		//  onto the return type.
		if (strNewFunc != "")
		{
			while (strNewFunc[0] == '*')
			{
				strNewFunc.SetAt(0,' ');
				strNewFunc.TrimLeft();
				nAppendStar++;
			}
		}

		GetReturnType(strReturn, ReturnsArray, strSuggestedReturn, nAppendStar);

		if ((m_RTF.GetCheck() == 0) && (m_HTML.GetCheck() == 0))
			CDialog::OnOK();

		if (m_RTF.GetCheck() == 1)
		{
			CString strFileName;
			m_RTFFileName.GetWindowText(strFileName);
			strFileName.TrimLeft();
			strFileName.TrimRight();
			if (strFileName.GetLength() == 0)
			{
				AfxMessageBox(IDS_NOFILE);
				return;
			}
			else if(m_TopicID.GetWindowTextLength() == 0)
			{
				AfxMessageBox(IDS_NOTOPICID);
				return;
			}
			else if(m_TopicName.GetWindowTextLength() == 0)
			{
				AfxMessageBox(IDS_NOTOPICNAME);
				return;
			}
			else
			{
				CString strID, strTopicName;
				m_TopicID.GetWindowText(strID);
				m_TopicName.GetWindowText(strTopicName);
				GenerateHelpFile(strFileName, strFuncName, strNewFunc, ParamList,
						ParamNames, strSuggestedReturn, strID, strTopicName);
			}
		}

		if (m_HTML.GetCheck() == 1)
		{
			CString strFileName;
			m_HTMLFileName.GetWindowText(strFileName);
			strFileName.TrimLeft();
			strFileName.TrimRight();
			if (strFileName.GetLength() == 0)
			{
				AfxMessageBox(IDS_NOFILEHTML);
				return;
			}
			else
			{
				GenerateHTML(strFileName, strFuncName, strNewFunc, ParamList, ParamNames,
						strSuggestedReturn);
			}
		}

		AfxMessageBox(IDS_FINISHED);
		CDialog::OnOK();
	}
}
