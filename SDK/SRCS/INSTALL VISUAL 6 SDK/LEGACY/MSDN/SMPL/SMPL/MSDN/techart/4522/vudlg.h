// vudlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVUDlg dialog

class CVUDlg : public CDialog
{
// Construction
public:
    CVUDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CVUDlg)
    enum { IDD = IDD_VUDLG };
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA
    CDIBPal* m_pPal; // 9/28/95 NigelT Added palette

// Implementation
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

private:
    CScrollBar* m_pSB;
    CVUMeter m_VU;

    // Generated message map functions
    //{{AFX_MSG(CVUDlg)
    virtual void OnOK();
    virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
