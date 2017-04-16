// formwnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormWnd window

class CFormWnd : public CWnd
{
    DECLARE_DYNAMIC(CFormWnd)
// Construction
protected:      // must derive your own class
    CFormWnd(LPCSTR lpszTemplateName);
    CFormWnd(UINT nIDTemplate);

// Implementation
public:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    LPCSTR m_lpszTemplateName;
    CCreateContext* m_pCreateContext;

    virtual void OnDraw(CDC* pDC);      // default does nothing
    virtual void OnInitialUpdate();
    // special case override of child window creation
    virtual BOOL Create(LPCSTR, LPCSTR, DWORD,
        const RECT&, CWnd*, UINT, CCreateContext*);
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    virtual WNDPROC* GetSuperWndProcAddr();

    //{{AFX_MSG(CFormWnd)
    afx_msg int OnCreate(LPCREATESTRUCT lpcs);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
