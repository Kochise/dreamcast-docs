//***************************************************************************
//
//  SizeDlg.cpp
//
//***************************************************************************

#include <afxwin.h>

#include "Resource.h"
#include "SizeDlg.h"

BOOL CGridSizeDialog::OnInitDialog ()
{
    CDialog::OnInitDialog ();

    CEdit* pEditHorz = (CEdit*) GetDlgItem (IDC_HORZ);
    CEdit* pEditVert = (CEdit*) GetDlgItem (IDC_VERT);
    pEditHorz->LimitText (4);
    pEditVert->LimitText (4);

    CenterWindow ();
    return TRUE;
}

void CGridSizeDialog::OnCancel ()
{
    // Do nothing so the dialog box will not be destroyed
}

void CGridSizeDialog::DoDataExchange (CDataExchange* pDX)
{
    CDialog::DoDataExchange (pDX);

    DDX_Text (pDX, IDC_HORZ, m_cx);
    DDV_MinMaxInt (pDX, m_cx, 8, 512);
    DDX_Text (pDX, IDC_VERT, m_cy);
    DDV_MinMaxInt (pDX, m_cy, 8, 512);
}
