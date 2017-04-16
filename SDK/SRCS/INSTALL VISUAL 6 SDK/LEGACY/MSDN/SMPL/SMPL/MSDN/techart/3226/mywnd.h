// mywnd.h : header file
//

#include "animwnd.h"

#define BACK_SCREEN 0
#define BACK_BLACK 1

/////////////////////////////////////////////////////////////////////////////
// CMyWnd window

class CMyWnd : public CAnimWnd
{
// Construction
public:
	CMyWnd();
    BOOL Create();


private:
    CDIBPal m_Pal;
    CDIBSurface m_dsBackground; // background image
    UINT m_uiTimer;
    CSprite m_spGui;
    CPhasedSprite m_spHeads;
    int m_iBackMode;

// Overrides
    virtual void Render(RECT* pClipRect = NULL);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyWnd();

private:
    void ErasePaintSurface();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
