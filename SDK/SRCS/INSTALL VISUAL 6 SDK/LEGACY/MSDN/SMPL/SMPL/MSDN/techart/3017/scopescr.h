// scopescr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScopeScreen window

class CScopeScreen : public CWnd
{
// Construction
public:
    CScopeScreen();
    BOOL Create(CWnd* pParentWnd,
                UINT nID,
                CPalette* pPal = NULL);
    CDC* GetDC();
    void GetRect(CRect* prc);

// Attributes
public:

// Operations
public:
    void Erase();
    void DrawGrid();

// Implementation
public:
    virtual ~CScopeScreen();

    CDIBSurface m_dibSurf;
    int m_iScreenWidth;
    int m_iScreenHeight;
    CPalette* m_pPal;

    // Generated message map functions
protected:
    //{{AFX_MSG(CScopeScreen)
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnPaint();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
