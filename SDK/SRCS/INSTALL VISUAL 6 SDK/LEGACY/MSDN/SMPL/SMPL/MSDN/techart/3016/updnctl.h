// updnctl.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CUpDnCtl window

class CUpDnCtl : public CWnd
{
    DECLARE_DYNCREATE(CUpDnCtl)
// Construction
public:
    CUpDnCtl();

// Attributes
public:

// Operations
public:

// Implementation
public:
    virtual ~CUpDnCtl();
    virtual WNDPROC* GetSuperWndProcAddr();
    static BOOL Register();
    void SetTextSet(const char* pszText)
        {m_strTextSet = pszText;}
    void SetButtonText(const char* pszUp, const char* pszDn);
    void SetCurSel(int iSel);

private:
    static BOOL m_bRegistered;
    int m_iWidth;
    int m_iHeight;
    CPalette* m_pPal;
    CDIBSurface m_dsPanel;
    CButton m_btnUp;
    CButton m_btnDn;
    CFont m_font;
    CString m_strCaption;
    CString m_strTextSet;
    int m_iCurSel;

    void Render();

    // Generated message map functions
protected:
    //{{AFX_MSG(CUpDnCtl)
    afx_msg void OnNcDestroy();
    afx_msg void OnPaint();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg LRESULT OnSetPalette(WPARAM wParam, LPARAM lParam);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnGetText(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnGetTextLength(WPARAM wParam, LPARAM lParam);
    afx_msg void OnUpClicked();
    afx_msg void OnDnClicked();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

// static initialization functions
#ifdef __cplusplus
extern "C" {
#endif
LRESULT CALLBACK UpDnWndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
#ifdef __cplusplus
}
#endif

/////////////////////////////////////////////////////////////////////////////
