/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/

// CustomizeCtxMenuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "wndtabs.h"
#include "HHSupp.h"
#include "Config.h"
#include "CustomizeCtxMenuDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CCustomizeCtxMenuDlg dialog

BEGIN_HELP_IDS(CCustomizeCtxMenuDlg)
    IDC_NONE_FM,        IDC_NONE_WM,
	IDC_NONE_CLIP,      IDC_NONE_WM,
	IDC_NONE_DS,        IDC_NONE_WM,
	IDC_REGULAR_WM,     IDC_NONE_WM,
	IDC_REGULAR_FM,     IDC_NONE_WM,
	IDC_REGULAR_CLIP,   IDC_NONE_WM,
	IDC_REGULAR_DS,     IDC_NONE_WM,
	IDC_CASCADING_WM,   IDC_NONE_WM,
	IDC_CASCADING_FM,   IDC_NONE_WM,
	IDC_CASCADING_CLIP, IDC_NONE_WM,
	IDC_CASCADING_DS,   IDC_NONE_WM
END_HELP_IDS();    


CCustomizeCtxMenuDlg::CCustomizeCtxMenuDlg(CWnd* pParent /*=NULL*/)
	: CHHDialog(CCustomizeCtxMenuDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomizeCtxMenuDlg)
	m_MenuClip = cfg_iMenuClip;
	m_MenuDS = cfg_iMenuDS;
	m_MenuFM = cfg_iMenuFileMan;
	m_MenuWM = cfg_iMenuWinMan;
	//}}AFX_DATA_INIT
}


void CCustomizeCtxMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CHHDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomizeCtxMenuDlg)
	DDX_Radio(pDX, IDC_NONE_CLIP, m_MenuClip);
	DDX_Radio(pDX, IDC_NONE_DS, m_MenuDS);
	DDX_Radio(pDX, IDC_NONE_FM, m_MenuFM);
	DDX_Radio(pDX, IDC_NONE_WM, m_MenuWM);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomizeCtxMenuDlg, CHHDialog)
	//{{AFX_MSG_MAP(CCustomizeCtxMenuDlg)
	ON_BN_CLICKED(IDC_RESET_MENUS, OnResetMenus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomizeCtxMenuDlg message handlers

void CCustomizeCtxMenuDlg::OnResetMenus() 
{
    UpdateData();
    if (AfxMessageBox(IDS_MENU_RESET_CONFIRM, MB_YESNO | MB_ICONQUESTION) == 
        IDYES)
    {
        EndDialog(IDOK);	
    }
}
