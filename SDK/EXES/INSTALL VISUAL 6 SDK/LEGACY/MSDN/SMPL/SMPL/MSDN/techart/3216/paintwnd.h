// paintwnd.h : header file
//

#include "animwnd.h"

/////////////////////////////////////////////////////////////////////////////
// CPaintWnd window

class CPaintWnd : public CAnimWnd
{
// Construction
public:
	CPaintWnd();
    BOOL Create(const char* pszTitle, DWORD dwStyle, 
                CWnd* pParent, int x, int y, int cx, int cy);


private:
    CDIBPal m_Pal;
    CDIBSurface m_dsPaint;      // drawing surface
    CCrayon m_Crayon[8];        // pens
    int m_iNumPens;
    CEraser m_Eraser;           // elephant
    CDrawingTool* m_pCurrentTool; // current tool
    CPoint m_ptPrev;
    UINT m_uiTimer;
    int m_iChangeLockoutTime;
    CSprite m_Corner;           // page turn corner
    CDIB m_dibRing;             // ring binder part
    CSprite m_Binder;           // entire ring binder

// Overrides
    virtual void Render(RECT* pClipRect = NULL);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaintWnd)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPaintWnd();

private:
    // Data and functions used to perform the background fade
    int m_iFadeBlockHeight;
    int m_iFadeBlockWidth;
    CPoint* m_pCellPoints;
    int m_iNumCellPoints;
    int m_iCellPoint;
    int m_iNumFadeBands;
    int m_iFadeBand;

    void InitFade();
    void Fade(int iCycles);
    void ErasePaintSurface();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPaintWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
