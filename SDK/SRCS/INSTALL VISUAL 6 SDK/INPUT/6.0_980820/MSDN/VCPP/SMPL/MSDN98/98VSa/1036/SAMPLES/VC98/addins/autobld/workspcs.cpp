// Workspcs.cpp : implementation file
//

// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.

#include "stdafx.h"
#include "AutoBld.h"
#include "Workspcs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkspaces dialog


CWorkspaces::CWorkspaces(CWnd* pParent /*=NULL*/)
	: CDialog(CWorkspaces::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWorkspaces)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CWorkspaces::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWorkspaces)
	DDX_Control(pDX, IDC_WORKSPACELIST, m_WorkspaceList);
	DDX_Control(pDX, IDC_REMOVE, m_Remove);
	DDX_Control(pDX, IDC_ADDWORKSPACE, m_Add);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWorkspaces, CDialog)
	//{{AFX_MSG_MAP(CWorkspaces)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_ADDWORKSPACE, OnAddWorkspace)
	ON_BN_CLICKED(IDC_MOVEDOWN, OnMoveDown)
	ON_BN_CLICKED(IDC_MOVEUP, OnMoveUp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaces message handlers

void CWorkspaces::OnRemove()
{
	//The user wants to remove a workspace from the list of workspaces to
	//build. Start at the top of the list and walk through it until an item
	//that is selected is found, Do not worry about fiddling with the registry
	//now, because it is updated when OK is pressed
	int nItem = m_WorkspaceList.GetNextItem(-1, LVNI_ALL);
	while (nItem != -1)
	{
		UINT nState = m_WorkspaceList.GetItemState(nItem, LVIS_SELECTED);
		if ((nState & LVIS_SELECTED) == LVIS_SELECTED)
		{
			m_WorkspaceList.DeleteItem(nItem);
			nItem = m_WorkspaceList.GetNextItem(-1, LVNI_ALL);
			break;
		}
		else
			nItem = m_WorkspaceList.GetNextItem(nItem, LVNI_ALL);
	}
}

void CWorkspaces::OnAddWorkspace()
{
	//The user wants to add a workspace to the list of workspaces to build
	CString strFileSpec;
	strFileSpec.LoadString(IDS_PROJECTFILES);
	CFileDialog Browser(TRUE, "", "", OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
			strFileSpec);
	if (Browser.DoModal() == IDOK)
	{
		//put the item into the list
		m_WorkspaceList.InsertItem(0, "", 0);
		m_WorkspaceList.SetItem(0, 1, LVIF_TEXT, Browser.GetPathName(),
				0, 0, 0, 0);
		m_WorkspaceList.SetItem(0, 0, LVIF_TEXT, Browser.GetFileTitle(),
				0, 0, 0, 0);
	}
}

void CWorkspaces::OnMoveDown()
{
	int nItem = m_WorkspaceList.GetNextItem(-1, LVNI_ALL);
	while (nItem != -1)
	{
		UINT nState = m_WorkspaceList.GetItemState(nItem, LVIS_SELECTED);
		if ((nState & LVIS_SELECTED) == LVIS_SELECTED)
		{
			int nBelowItem = m_WorkspaceList.GetNextItem(nItem, LVNI_BELOW);
			if (nBelowItem != -1)
			{
				CString strThisName = m_WorkspaceList.GetItemText(nItem, 0);
				CString strThisPath = m_WorkspaceList.GetItemText(nItem, 1);
				CString strBelowName = m_WorkspaceList.GetItemText(nBelowItem, 0);
				CString strBelowPath = m_WorkspaceList.GetItemText(nBelowItem, 1);
				m_WorkspaceList.SetItemText(nItem, 0, strBelowName);
				m_WorkspaceList.SetItemText(nItem, 1, strBelowPath);
				m_WorkspaceList.SetItemText(nBelowItem, 0, strThisName);
				m_WorkspaceList.SetItemText(nBelowItem, 1, strThisPath);
				m_WorkspaceList.SetItemState(nBelowItem, LVIS_SELECTED,
						LVIS_SELECTED);
				m_WorkspaceList.SetFocus();
			}
			break;
		}
		else
			nItem = m_WorkspaceList.GetNextItem(nItem, LVNI_ALL);
	}
}

void CWorkspaces::OnMoveUp()
{
	int nItem = m_WorkspaceList.GetNextItem(-1, LVNI_ALL);
	while (nItem != -1)
	{
		UINT nState = m_WorkspaceList.GetItemState(nItem, LVIS_SELECTED);
		if ((nState & LVIS_SELECTED) == LVIS_SELECTED)
		{
			int nAboveItem = m_WorkspaceList.GetNextItem(nItem, LVNI_ABOVE);
			if (nAboveItem != -1)
			{
				CString strThisName = m_WorkspaceList.GetItemText(nItem, 0);
				CString strThisPath = m_WorkspaceList.GetItemText(nItem, 1);
				CString strAboveName = m_WorkspaceList.GetItemText(nAboveItem, 0);
				CString strAbovePath = m_WorkspaceList.GetItemText(nAboveItem, 1);
				m_WorkspaceList.SetItemText(nItem, 0, strAboveName);
				m_WorkspaceList.SetItemText(nItem, 1, strAbovePath);
				m_WorkspaceList.SetItemText(nAboveItem, 0, strThisName);
				m_WorkspaceList.SetItemText(nAboveItem, 1, strThisPath);
				m_WorkspaceList.SetItemState(nAboveItem, LVIS_SELECTED,
						LVIS_SELECTED);
				m_WorkspaceList.SetFocus();
			}
			break;
		}
		else
			nItem = m_WorkspaceList.GetNextItem(nItem, LVNI_ALL);
	}
}

void CWorkspaces::OnOK()
{
	AfxGetApp()->WriteProfileInt(_T("Configure"), _T("NumWorkspaces"),
			m_WorkspaceList.GetItemCount());
	for (int i = 0 ; i < m_WorkspaceList.GetItemCount() ; i++)
	{
		char szRegKey[50];
		wsprintf(szRegKey, "Workspace%d", i);
		AfxGetApp()->WriteProfileString(_T("Configure"), szRegKey,
				m_WorkspaceList.GetItemText(i, 1));
		wsprintf(szRegKey, "WorkspaceName%d", i);
		AfxGetApp()->WriteProfileString(_T("Configure"), szRegKey,
				m_WorkspaceList.GetItemText(i, 0));
	}

	CDialog::OnOK();
}

BOOL CWorkspaces::OnInitDialog()
{
	CDialog::OnInitDialog();

	//Need to set up to display the little icons next to each workspace name.
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_WORKSPACE);
	m_ImageList.Create(16, 16, ILC_COLOR, 1, 1);
	m_ImageList.SetBkColor(GetSysColor(COLOR_WINDOW));
	m_ImageList.Add(hIcon);
	m_WorkspaceList.SetImageList(&m_ImageList, LVSIL_SMALL);

	//Set up columns inside the list view
	CString strWrkspcName;
	CString strWrkspcPath;
	strWrkspcName.LoadString(IDS_WKSPCNAME);
	strWrkspcPath.LoadString(IDS_WKSPCPATH);
	m_WorkspaceList.InsertColumn(0, strWrkspcName, LVCFMT_LEFT, 100);
	m_WorkspaceList.InsertColumn(1, strWrkspcPath, LVCFMT_LEFT, 230);

	//Start getting information from the registry. First get the total number
	//  of workspaces that we want to work with.
	int nNumWorkspaces = AfxGetApp()->GetProfileInt(_T("Configure"),
			_T("NumWorkspaces"), 0);
	for (int i = 0 ; i < nNumWorkspaces ; i++)
	{
		//Now load each workspace name and path
		char szRegKey[50];
		wsprintf(szRegKey, "Workspace%d", i);
		CString strWorkspacePath = AfxGetApp()->GetProfileString(_T("Configure"),
				szRegKey, "");
		wsprintf(szRegKey, "WorkspaceName%d", i);
		CString strWorkspaceName = AfxGetApp()->GetProfileString(_T("Configure"),
				szRegKey, "");
		m_WorkspaceList.InsertItem(i, "", 0);

		//Store this information in the list view
		m_WorkspaceList.SetItem(i, 1, LVIF_TEXT, strWorkspacePath, 0, 0, 0, 0);
		m_WorkspaceList.SetItem(i, 0, LVIF_TEXT, strWorkspaceName, 0, 0, 0, 0);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
