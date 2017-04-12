/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/

// CmdSelDialog.cpp : implementation file
//

#include "stdafx.h"
#include "wndtabs.h"
#include "CmdSelDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCmdSelDialog dialog


CCmdSelDialog::CCmdSelDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCmdSelDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCmdSelDialog)
	m_strButtonDescription = _T("");
	//}}AFX_DATA_INIT

    m_pDlgCust = NULL;
    m_iCurrCommandID = -1;
}

CCmdSelDialog::~CCmdSelDialog()
{
    delete m_pDlgCust;
}

void CCmdSelDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCmdSelDialog)
	DDX_Control(pDX, IDC_BCGBARRES_COMMANDS_LIST, m_wndCommandsList);
	DDX_Control(pDX, IDC_BCGBARRES_CATEGORY, m_wndCategoryList);
	DDX_Text(pDX, IDC_BCGBARRES_BUTTON_DESCR, m_strButtonDescription);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCmdSelDialog, CDialog)
	//{{AFX_MSG_MAP(CCmdSelDialog)
	ON_LBN_SELCHANGE(IDC_BCGBARRES_COMMANDS_LIST, OnSelchangeCommandList)
	ON_LBN_SELCHANGE(IDC_BCGBARRES_CATEGORY, OnSelchangeCategory)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCmdSelDialog message handlers

BOOL CCmdSelDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//---------------------------------
	// Initialize commands by category:
	//---------------------------------	
	m_pDlgCust = new CBCGToolbarCustomize((CFrameWnd *)g_pMainFrame, TRUE);
    m_pDlgCust->AddMenu(IDR_COMMANDS);
	m_pDlgCust->EnableUserDefinedToolbars();
	m_pDlgCust->FillCategotiesListBox (m_wndCategoryList);
	
	m_wndCategoryList.SetCurSel (0);
	OnSelchangeCategory ();

    return TRUE;
}

void CCmdSelDialog::OnSelchangeCommandList() 
{
    UpdateData();
	int iIndex = m_wndCommandsList.GetCurSel ();
    m_strButtonDescription = "";
    m_iCurrCommandID = -1;
	if (iIndex != LB_ERR)
	{
        GetDlgItem(IDOK)->EnableWindow(TRUE);
        CBCGToolbarButton *pSelButton = (CBCGToolbarButton*) 
            m_wndCommandsList.GetItemData (iIndex);
	    if (pSelButton != NULL)
	    {
            m_iCurrCommandID = pSelButton->m_nID;
		    if (pSelButton->m_nID == 0)
		    {
			    m_strButtonDescription = pSelButton->m_strText;
		    }
		    else
		    {
				((CFrameWnd *)g_pMainFrame)->GetMessageString(
                    pSelButton->m_nID, m_strButtonDescription);
		    }
	    }
	}
    GetDlgItem(IDOK)->EnableWindow(!m_strButtonDescription.IsEmpty());
    UpdateData(FALSE);
}

void CCmdSelDialog::OnSelchangeCategory() 
{
	UpdateData ();

	int iIndex = m_wndCategoryList.GetCurSel ();
	if (iIndex == LB_ERR)
	{
		ASSERT (FALSE);
		return;
	}

	CWaitCursor wait;
	m_wndCommandsList.SetRedraw (FALSE);

	m_wndCommandsList.ResetContent ();

	//------------------------------------------
	// Only "All commands" list shoud be sorted!
	//------------------------------------------
	CString strCategory;
	m_wndCategoryList.GetText (iIndex, strCategory);

	BOOL bAllCommands = (iIndex == (m_wndCategoryList.GetCount() - 1));

	CObList* pCategoryButtonsList = 
		(CObList*) m_wndCategoryList.GetItemData (iIndex);
	ASSERT_VALID (pCategoryButtonsList);

	for (POSITION pos = pCategoryButtonsList->GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) pCategoryButtonsList->GetNext (pos);
		ASSERT (pButton != NULL);

        if (pButton->IsKindOf(RUNTIME_CLASS(CBCGToolbarMenuButton)))
        {
            continue;
        }

		pButton->m_bUserButton = pButton->m_nID != (UINT) -1 &&
			CMD_MGR.GetCmdImage (pButton->m_nID, FALSE) == -1;

		int iIndex = -1;
		
		if (bAllCommands)
		{
			for (int i = 0; iIndex == -1 && i < m_wndCommandsList.GetCount (); i ++)
			{
				CString strCommand;
				m_wndCommandsList.GetText (i, strCommand);

				if (strCommand > pButton->m_strText)
				{
					iIndex = m_wndCommandsList.InsertString (i, pButton->m_strText);
				}
			}
		}

		if (iIndex == -1)	// Not inserted yet
		{
			iIndex = m_wndCommandsList.AddString (pButton->m_strText);
		}

		m_wndCommandsList.SetItemData (iIndex, (DWORD) pButton);
	}

    OnSelchangeCommandList();
	m_wndCommandsList.SetRedraw (TRUE);
}
