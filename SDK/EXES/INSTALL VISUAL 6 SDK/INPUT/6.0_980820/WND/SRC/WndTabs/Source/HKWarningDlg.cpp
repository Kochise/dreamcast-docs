/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// HKWarningDlg.cpp : implementation file
//

#include "stdafx.h"
#include "wndtabs.h"
#include "HKWarningDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHKWarningDlg dialog


CHKWarningDlg::CHKWarningDlg(CString cKeyComb, CString cKeys, 
    CString cCommands, CString cEditors, CWnd* pParent /*=NULL*/)
	: CDialog(CHKWarningDlg::IDD, pParent), m_cKeyComb(cKeyComb),
    m_cKeys(cKeys), m_cCommands(cCommands), m_cEditors(cEditors)
{
	//{{AFX_DATA_INIT(CHKWarningDlg)
	m_sHotKey = _T("");
	//}}AFX_DATA_INIT
}


void CHKWarningDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHKWarningDlg)
	DDX_Control(pDX, IDC_LIST, m_ListCtrl);
	DDX_Text(pDX, IDC_HOTKEY, m_sHotKey);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHKWarningDlg, CDialog)
	//{{AFX_MSG_MAP(CHKWarningDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHKWarningDlg message handlers

BOOL CHKWarningDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

    int         i;
    LPCTSTR     cColumns[] = {_T("Key"), _T("Command"), _T("Editor")};
    LVCOLUMN    lvc;

    lvc.mask = LVCF_FMT | /*LVCF_WIDTH |*/ LVCF_TEXT | LVCF_SUBITEM;

    lvc.fmt = LVCFMT_LEFT;

    for(i = 0; i < 3; i++)
    {
        lvc.iSubItem = i;
        lvc.pszText = (char *)cColumns[i];
        lvc.cx = LVSCW_AUTOSIZE;
        m_ListCtrl.InsertColumn(i,&lvc);
    }

    CString cKey, cCommand, cEditor;
    int nPos;

    while (m_cKeys.GetLength() > 1)
    {
        nPos    = m_cKeys.Find('\n');
        cKey    = m_cKeys.Left(nPos);
        m_cKeys = m_cKeys.Mid(nPos + 1);

        nPos        = m_cCommands.Find('\n');
        cCommand    = m_cCommands.Left(nPos);
        m_cCommands = m_cCommands.Mid(nPos + 1);

        nPos       = m_cEditors.Find('\n');
        cEditor    = m_cEditors.Left(nPos);
        m_cEditors = m_cEditors.Mid(nPos + 1);

        AddRow(cKey + "   ", cCommand + "   ", cEditor + "   ");
    }
    
    for(i = 0; i < 3; i++)
    {
        m_ListCtrl.SetColumnWidth(i, LVSCW_AUTOSIZE);
    }

    m_sHotKey = m_cKeyComb;
    UpdateData(FALSE);

    MessageBeep(MB_ICONEXCLAMATION);

	return TRUE; 
}

void CHKWarningDlg::AddRow(LPCTSTR cKey, LPCTSTR cCommand, LPCTSTR cEditor)
{
    LV_ITEM lvi;

    lvi.mask = LVIF_TEXT;
    lvi.iItem = m_ListCtrl.GetItemCount();

    lvi.iSubItem = 0;
    lvi.pszText = (char *)cKey;
    m_ListCtrl.InsertItem(&lvi);

    m_ListCtrl.SetItemText(lvi.iItem, 1, cCommand);
    m_ListCtrl.SetItemText(lvi.iItem, 2, cEditor);
}
