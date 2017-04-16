// panelfra.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPanelFrame frame

class CPanelFrame : public CDlgPanelFrame
{
    DECLARE_DYNCREATE(CPanelFrame)
public:
    CPanelFrame();      

// Attributes
public:

// Operations
public:

// Implementation
protected:
    virtual ~CPanelFrame();

private:
    // Generated message map functions
    //{{AFX_MSG(CPanelFrame)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    virtual void OnOK();
    afx_msg void OnClickedButton();
    afx_msg void OnClickedRadio1();
    afx_msg void OnClickedRadio2();
    afx_msg void OnClickedCheck();
    afx_msg void OnSelchangeList();
    afx_msg void OnClickedClose();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    virtual void OnCancel();
	afx_msg void OnSelchangeCombo();
	afx_msg void OnEditchangeCombo();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
