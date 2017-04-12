/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// AutoPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "AutoPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoPropPage property page

IMPLEMENT_DYNCREATE(CAutoPropPage, CHHPropPage)

CAutoPropPage::~CAutoPropPage()
{
}

void CAutoPropPage::DoDataExchange(CDataExchange* pDX)
{
	CHHPropPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAutoPropPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAutoPropPage, CHHPropPage)
	//{{AFX_MSG_MAP(CAutoPropPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoPropPage message handlers

BOOL CAutoPropPage::OnApply()
{
    if (!UpdateData())
        return FALSE;

	m_varpair.OnApply();
	m_strpair.OnApply();

    return CHHPropPage::OnApply();
}

void CAutoPropPage::OnCancel() 
{
	m_varpair.OnCancel();
	m_strpair.OnCancel();

    UpdateData(FALSE);
    OnApply();
	
	return;
}

void CAutoPropPage::InitAutoVars(int argc, varpair *argv)
{
	m_varpair.InitAutoVars(argc, argv);
}

void CAutoPropPage::InitAutoStrs(int argc, strpair *argv)
{
	m_strpair.InitAutoVars(argc, argv);
}

bool CAutoPropPage::Changed(int& member)
{
    return m_varpair.Changed(member);
}

bool CAutoPropPage::Changed(CString& member)
{
    return m_strpair.Changed(member);
}

bool CAutoPropPage::ChangedAny()
{
    return ( m_varpair.ChangedAny() || m_strpair.ChangedAny() );
}

int CAutoPropPage::OrigVal(int& member)
{
    return m_varpair.OrigVal(member);
}

CString CAutoPropPage::OrigVal(CString& member)
{
    return m_strpair.OrigVal(member);
}

int CAutoPropPage::PrevVal(int& member)
{
    return m_varpair.PrevVal(member);
}

CString CAutoPropPage::PrevVal(CString& member)
{
    return m_strpair.PrevVal(member);
}

