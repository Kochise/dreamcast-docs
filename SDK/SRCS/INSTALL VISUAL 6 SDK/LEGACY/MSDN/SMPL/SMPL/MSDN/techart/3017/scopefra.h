// scopefra.h : header file
//

#include "scopescr.h"

/////////////////////////////////////////////////////////////////////////////
// CScopeFrame frame

typedef struct _YCHANNEL {
    double* pData;
    int iPoints;
    double dInterval;
    int iPos;
    double dScale;
    BOOL bGnd;
} YCHANNEL;

class CScopeFrame : public CMDIChildWnd
{
    DECLARE_DYNCREATE(CScopeFrame)
public:
    CScopeFrame();
    BOOL Create(LPCSTR lpszWindowName,
                const RECT& rect,
                CMDIFrameWnd* pParentWnd,
                UINT uiResourceID,
                CPalette* pPal = NULL);
    void SetData(double* pData, int iPoints,
                 double dInterval, int iChannel = 0);


// Attributes
public:

// Operations
public:

// Implementation
protected:
    virtual ~CScopeFrame();
    virtual void RecalcLayout();
    void PlotData();
    void Plot(CDC* pDC, YCHANNEL* pCh, CRect* pRect);
    double GetScale(CUpDnCtl* pUD);
    void OnScroll(UINT nSBCode, UINT nPos, CRotaryCtl* pCtl);
    void DrawYButton(YCHANNEL* pCh, DRAWITEMSTRUCT* pDrawItemStruct);

    CDlgPanel m_wndBarLeft;
    CDlgPanel m_wndBarRight;
    CDlgPanel m_wndBarBottom;
    CScopeScreen m_wndScreen;
    CPalette* m_pPal;
    YCHANNEL m_A;        
    YCHANNEL m_B;
    int m_iXPos;
    double m_dXScale;

    // Generated message map functions
    //{{AFX_MSG(CScopeFrame)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
    afx_msg void OnClickedAGnd();
    afx_msg void OnClickedBGnd();
    afx_msg void OnEditchangeAScale();
    afx_msg void OnEditchangeBScale();
    afx_msg void OnEditchangeXScale();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
