//***************************************************************************
//
//  AboutDlg.cpp
//
//***************************************************************************

#include <afxwin.h>

#include "Resource.h"
#include "AboutDlg.h"

BEGIN_MESSAGE_MAP (CAboutDialog, CDialog)
    ON_WM_PAINT ()
END_MESSAGE_MAP ()

BOOL CAboutDialog::OnInitDialog ()
{
    CDialog::OnInitDialog ();

    CStatic* pStatic = (CStatic*) GetDlgItem (IDC_ICONRECT);
    pStatic->GetWindowRect (&m_rect);
    pStatic->DestroyWindow ();
    ScreenToClient (&m_rect);

    CenterWindow ();
    return TRUE;
}

void CAboutDialog::OnPaint ()
{
    CPaintDC dc (this);
    HICON hIcon = (HICON) ::GetClassLong (AfxGetMainWnd ()->m_hWnd,
        GCL_HICON);

    if (hIcon != NULL) {
        CDC mdc;
        mdc.CreateCompatibleDC (&dc);

        CBrush brush;
        brush.CreateStockObject (LTGRAY_BRUSH);

        CBitmap bitmap;
        bitmap.CreateCompatibleBitmap (&dc, 32, 32);
        CBitmap* pOldBitmap = mdc.SelectObject (&bitmap);

        CRect rcIcon (0, 0, 32, 32);
        mdc.FillRect (&rcIcon, &brush);
        mdc.DrawIcon (0, 0, hIcon);

        dc.StretchBlt (m_rect.left, m_rect.top, m_rect.Width(),
            m_rect.Height (), &mdc, 0, 0, 32, 32, SRCCOPY);

        mdc.SelectObject (pOldBitmap);
    }
}
