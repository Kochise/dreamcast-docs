// dlgpanfm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPanelFrame frame

class CDlgPanelFrame : public CMDIChildWnd
{
    DECLARE_DYNCREATE(CDlgPanelFrame)
public:
    CDlgPanelFrame(); 
    BOOL Create(LPCSTR lpszWindowName,
                const RECT& rect,
                CMDIFrameWnd* pParentWnd,
                UINT uiTemplateID,
                UINT uiResourceID,
                CPalette* pPal = NULL);

// Implementation
protected:
    CPalette* m_pPal;
    CDlgPanel m_wndPanel;
    UINT m_uiTemplateID;

    virtual ~CDlgPanelFrame();

    // Generated message map functions
    //{{AFX_MSG(CDlgPanelFrame)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    virtual void OnOK();
    virtual void OnCancel();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
