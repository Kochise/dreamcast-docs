//***************************************************************************
//
//  AboutDlg.h
//
//***************************************************************************

class CAboutDialog : public CDialog
{
private:
    CRect m_rect;

public:
    CAboutDialog (CWnd* pParentWnd = NULL) :
        CDialog ("About", pParentWnd) {}

protected:
    virtual BOOL OnInitDialog ();

    afx_msg void OnPaint ();
    DECLARE_MESSAGE_MAP ()
};
