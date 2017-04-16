// animwnd.h : header file
//

#ifndef _ANIMWND_
#define _ANIMWND_

/////////////////////////////////////////////////////////////////////////////
// CAnimWnd window

class CAnimWnd;

class CAnimWndSpriteNotifyObj : public CSpriteNotifyObj
{
public:
    CAnimWndSpriteNotifyObj();
    void Change(CSprite* pSprite, CHANGETYPE change, CRect* pRect1, CRect* pRect2);

    CAnimWnd* m_pAnimWnd;
};

class CAnimWnd : public CWnd
{
// Construction
public:
	CAnimWnd();
    BOOL Create(const char* pszTitle, DWORD dwStyle, 
                CWnd* pParent, int x, int y, int cx, int cy,
                HCURSOR hCur, CPalette* pPal = NULL);
// Attributes
public:

// Operations
public:
    virtual void Render(RECT* pClipRect = NULL);

    void Draw(RECT* pClipRect = NULL);
    void AddDirtyRegion(RECT* pRect);
    BOOL InsertSprite(CSprite* pNewSprite);
    CSprite* RemoveSprite(CSprite *pSprite);
    void ReorderSprite(CSprite* pSprite);
    CSprite* CAnimWnd::HitTestSprite(CPoint point);
    void RenderAndDrawDirtyList();
    void RenderSprites(RECT* pClipRect = NULL);

protected:
    CPalette* m_pPal;           // current palette
    BOOL m_bMyPal;              // TRUE if we created the palette
    CDIBSurface m_dsBuffer;     // rendering buffer
    COLORREF m_clrBackground;   // default background color
    CAnimWndSpriteNotifyObj m_NotifyObj; // sprite event callback
    CObList m_DirtyList;        // dirty region list
    CObList m_SpriteList;       // sprite list

    void EmptyDirtyList();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAnimWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAnimWnd)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif // _ANIMWND_
