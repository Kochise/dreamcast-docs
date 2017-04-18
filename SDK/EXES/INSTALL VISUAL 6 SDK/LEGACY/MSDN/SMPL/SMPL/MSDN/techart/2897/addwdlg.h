// addwdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddWordDlg dialog

class CAddWordDlg : public CDialog
{
// Construction
public:
    CAddWordDlg(CWnd* pParent = NULL);  // standard constructor

    CWave* m_pWave;  // supplied by caller
// Dialog Data
    //{{AFX_DATA(CAddWordDlg)
    enum { IDD = IDD_ADDWORD };
    CButton m_wndPlay;
    CButton m_wndOK;
    CEdit   m_wndText;
    CString m_strText;
    //}}AFX_DATA

// Implementation
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(CAddWordDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnClickedWavefile();
    virtual void OnCancel();
    virtual void OnOK();
    afx_msg void OnChangeText();
    afx_msg void OnClickedPlay();
	afx_msg void OnClickedRecord();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    void ValidateButtons();

};

