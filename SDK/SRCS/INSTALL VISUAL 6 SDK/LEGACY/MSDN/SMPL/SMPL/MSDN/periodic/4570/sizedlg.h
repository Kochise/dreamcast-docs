//***************************************************************************
//
//  SizeDlg.h
//
//***************************************************************************

class CGridSizeDialog : public CDialog
{
public:
    int m_cx;
    int m_cy;

    CGridSizeDialog (CWnd* pParentWnd = NULL) :
        CDialog ("GridSize", pParentWnd) {}

protected:
    virtual BOOL OnInitDialog ();
    virtual void OnCancel ();
    virtual void DoDataExchange (CDataExchange*);
};
