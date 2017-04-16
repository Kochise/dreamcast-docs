// rotary.h : header file
//

#define PI  3.14159265359
#define TRANS_COLOR PALETTERGB(0,255,255) // cyan

/////////////////////////////////////////////////////////////////////////////
// CRotaryCtl window

class CRotaryCtl : public CWnd
{
    DECLARE_DYNCREATE(CRotaryCtl)
// Construction
public:
    CRotaryCtl();

// Implementation
public:
    virtual ~CRotaryCtl();
    virtual WNDPROC* GetSuperWndProcAddr();
    void Render();
    static BOOL Register();
    void SetRange(int iMin, int iMax);
    void SetPos(int iPos);
    int GetPos() {return m_iPos;}

private:
    static BOOL m_bRegistered;
    CDIBSurface m_dsBuffer;
    CDIBSurface m_dsImage;
    CDIBSurface m_dsBackground;
    BOOL m_bGotBackground;
    int m_iWidth;
    int m_iHeight;
    CPalette* m_pPal;
    CPoint m_ptCenter;
    int m_iRadius;
    int m_iMin;
    int m_iMax;
    int m_iPos;
    int m_bCaptured;

    void CreateImage();

    // Generated message map functions
protected:
    //{{AFX_MSG(CRotaryCtl)
    afx_msg void OnNcDestroy();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnPaint();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg LRESULT OnSetPalette(WPARAM wParam, LPARAM lParam);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

// static initialization functions
#ifdef __cplusplus
extern "C" {
#endif
LRESULT CALLBACK RotaryWndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
#ifdef __cplusplus
}
#endif

/////////////////////////////////////////////////////////////////////////////
