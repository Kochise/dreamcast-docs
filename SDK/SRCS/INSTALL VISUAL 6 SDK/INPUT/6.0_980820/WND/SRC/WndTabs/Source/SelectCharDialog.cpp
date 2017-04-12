/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// SelectCharDialog.cpp : implementation file
//

#include "stdafx.h"
#include "wndtabs.h"
#include "SelectCharDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectCharDialog dialog


CSelectCharDialog::CSelectCharDialog(int ch, CWnd* pParent /*=NULL*/)
	: CDialog(CSelectCharDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectCharDialog)
	m_Char = (unsigned char)ch;
	m_iCode = ch;
	//}}AFX_DATA_INIT
}


void CSelectCharDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectCharDialog)
	DDX_Text(pDX, IDC_LIMITCHARACTER, m_Char);
	DDV_MaxChars(pDX, m_Char, 2);
	DDX_Text(pDX, IDC_CHARCODE, m_iCode);
	DDV_MinMaxInt(pDX, m_iCode, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectCharDialog, CDialog)
	//{{AFX_MSG_MAP(CSelectCharDialog)
	ON_BN_CLICKED(IDC_RUNPROG, OnRunprog)
	ON_EN_CHANGE(IDC_LIMITCHARACTER, OnChangeLimitcharacter)
	ON_EN_CHANGE(IDC_CHARCODE, OnChangeCharcode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectCharDialog message handlers

void CSelectCharDialog::OnRunprog() 
{
     ShellExecute(NULL, NULL, "charmap.exe", NULL, NULL,
         SW_SHOWDEFAULT);
}

void CSelectCharDialog::OnChangeLimitcharacter() 
{
    CString CharOld = m_Char;
    if (CharOld.IsEmpty()) CharOld = " ";
    UpdateData();
    if (m_Char.GetLength() > 0)
    {
        int ch = -1;
        for (int i = 0; i < m_Char.GetLength(); ++i)
        {
            if (m_Char[i] != CharOld[0])
            {
                ch = (unsigned char)m_Char[i];
                break;
            }
        }
        m_Char = (char)((ch >= 0)? ch : CharOld[0]);
        m_iCode = (unsigned char)m_Char[0];
    }
    else
        m_iCode = 0;
    UpdateData(FALSE);
}

void CSelectCharDialog::OnChangeCharcode() 
{
    CString cStr;
    GetDlgItem(IDC_CHARCODE)->GetWindowText(cStr);
    if (cStr.GetLength())
    {
        UpdateData();
        m_Char = (char)m_iCode;
        UpdateData(FALSE);
    }
}

