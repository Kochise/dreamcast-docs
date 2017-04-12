// Based On Code From CVSIn by Jerzy Kaczorowski (www.cvsin.org) 

// ToolbarSetup.cpp : implementation file
//

#include "stdafx.h"
#include "Wndtabs.h"
#include "HHSupp.h"
#include "ToolbarSetup.h"
#include "DSAddin.h"
#include "TabsWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolbarSetup dialog


CToolbarSetup::CToolbarSetup(CWnd* pParent /*=NULL*/)
	: CHHDialog(CToolbarSetup::IDD, pParent)
{
	//{{AFX_DATA_INIT(CToolbarSetup)
	m_strDescription = _T("");
	//}}AFX_DATA_INIT
}


void CToolbarSetup::DoDataExchange(CDataExchange* pDX)
{
	CHHDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolbarSetup)
	DDX_Control(pDX, IDC_LIST_COMMANDS, m_CommandsListBox);
	DDX_Text(pDX, IDC_EDIT_DESCRIPTION, m_strDescription);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CToolbarSetup, CHHDialog)
	//{{AFX_MSG_MAP(CToolbarSetup)
	ON_LBN_SELCHANGE(IDC_LIST_COMMANDS, OnSelchangeListCommands)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_HELP_IDS(CToolbarSetup)
IDC_LIST_COMMANDS, IDH_TBSETUP_LIST_COMMANDS,
IDC_EDIT_DESCRIPTION, IDH_TBSETUP_EDIT_DESCRIPTION,
IDOK, IDH_TBSETUP_OK
END_HELP_IDS();

/////////////////////////////////////////////////////////////////////////////
// CToolbarSetup message handlers

BOOL CToolbarSetup::OnInitDialog() 
{
	CHHDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    CString cStr;
	int nIndex = 0;

    for (nIndex = 0; nIndex < cAddInCommands; nIndex++)
    {
    	const AddInCmd& AddinCommand = AddInCommands[nIndex];
        
		int nPos = m_CommandsListBox.AddString( AddinCommand.szCommand );
		if( -1 != nPos )
		{
			m_CommandsListBox.SetCheck( nPos, 
                AddinCommand.bToolBarByDefault );
		}
	}

	if( m_CommandsListBox.GetCount() > 0 )
	{
		m_CommandsListBox.SetCurSel(0);
		OnSelchangeListCommands();
		GotoDlgCtrl(GetDlgItem(IDC_LIST_COMMANDS));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CToolbarSetup::OnSelchangeListCommands() 
{
	// TODO: Add your control notification handler code here
	int nPos = m_CommandsListBox.GetCurSel();
	if( -1 != nPos )
	{
		const AddInCmd& AddinCommand = AddInCommands[nPos];
		CString cStr, strDescription;
        cStr.LoadString(AddinCommand.idCmdString);
        AfxExtractSubString(strDescription, cStr, 2);
		CWnd* pWnd = GetDlgItem(IDC_EDIT_DESCRIPTION);
		if( IsWindow(pWnd->GetSafeHwnd()) )
		{
			pWnd->SetWindowText( strDescription );
		}
	}
}

void CToolbarSetup::OnOK() 
{
	// TODO: Add extra validation here
	for( int nIndex = 0; nIndex < m_CommandsListBox.GetCount(); nIndex++ )
	{
        if (m_CommandsListBox.GetCheck( nIndex) )
        {
    		const AddInCmd& AddinCommand = AddInCommands[nIndex];
            VERIFY_OK(pGlobalTabs->m_pApplication->
                AddCommandBarButton(dsGlyph, 
                    CComBSTR(AddinCommand.szCommand), g_dwCookie));
        }
    }
	
	CHHDialog::OnOK();
}

void CToolbarSetup::OnCancel() 
{
	CHHDialog::OnCancel();
}
