/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// InfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "wndtabs.h"
#include "InfoDlg.h"

#include "AddInComm\AddInComm.h"
#include "AddInComm\AICLoader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg dialog


CInfoDlg::CInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInfoDlg)
	//}}AFX_DATA_INIT
}


void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfoDlg)
	DDX_Control(pDX, IDC_VA, m_VALink);
	DDX_Control(pDX, IDC_WWHIZ, m_WWhizLink);
	DDX_Control(pDX, IDC_SMARTHELP, m_SHLink);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CInfoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg message handlers

BOOL CInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

    SetVerText("WorkspaceWhiz", IDC_WWHIZ_VER);
    SetVerText("VisualAssist",  IDC_VA_VER);
    SetVerText("SmartHelp",     IDC_SH_VER);

    CString cLink;
    cLink.LoadString(IDS_WWHIZ_WWW);
    m_WWhizLink.SetURL(cLink);
    cLink.LoadString(IDS_VA_WWW);
    m_VALink.SetURL(cLink);
    cLink.LoadString(IDS_SH_WWW);
    m_SHLink.SetURL(cLink);

    BOOL bAIC = aiclIsAICLoaded();
    CWnd *pWnd = GetDlgItem(ID_TEXTFIRST);
    do 
    {
        pWnd->ShowWindow(bAIC? SW_SHOW : SW_HIDE);
        pWnd = pWnd->GetNextWindow();
    } while (pWnd->GetDlgCtrlID() != IDC_SH_VER);
    GetDlgItem(ID_AICTEXT)  ->ShowWindow(bAIC? SW_HIDE : SW_SHOW);
    GetDlgItem(ID_AICBORDER)->ShowWindow(bAIC? SW_HIDE : SW_SHOW);
	
	return TRUE;  
}

void CInfoDlg::SetVerText(LPCTSTR pName, int nID)
{
    HADDIN  hAddIn;
    CString cStr = "Not Detected";
    
    hAddIn = AICGetAddIn(pName);
    if (hAddIn)
    {
        LPCTSTR pszVerStr;
        int iVerMin, iVerMaj, iVerExtra;

        pszVerStr = AICGetAddInVersionString(hAddIn);

        if (!pszVerStr)
        {
            // pszVerStr is NULL if the user is running an old version of
            // AddInComm.  in that case, the loader won't find the above 
            // function and return NULL --- no harm done (just some extra
            // work for us).
            // BTW - the AddInComm version could have been checked directly.
            // since we know AICGetAddInVersionString() is available starting
            // with v1.2.0, we could have done:
            //     AICGetDllVersion(iVerMaj, iVerMin, iVerExtra);
            //     if (iVerMaj >= 1  &&  iVerMin >= 2) ...

            AICGetAddInVersion(hAddIn, iVerMaj, iVerMin, iVerExtra);
            cStr.Format("Detected, Version %d.%d.%d.", iVerMaj, iVerMin, 
                iVerExtra);
        }
        else
        {
            cStr.Format("Detected, Version %s", pszVerStr);
        }
    }

    GetDlgItem(nID)->SetWindowText(cStr);
}
