// glpalvw.h : interface of the CGLpalView class
//
/////////////////////////////////////////////////////////////////////////////

class CGLpalView : public CView
{
protected: // create from serialization only
	CGLpalView();
	DECLARE_DYNCREATE(CGLpalView)

// Attributes
public:
	CGLpalDoc* GetDocument()    { return (CGLpalDoc*)m_pDocument; }

	CPalette* m_pPal ;

	HGLRC m_hrc ; 

	unsigned char ComponentFromIndex(int i, UINT nbits, UINT shift) ;
 	static unsigned char   m_oneto8[2];
    static unsigned char   m_twoto8[4];
    static unsigned char   m_threeto8[8];
    static int             m_defaultOverride[13];
    static PALETTEENTRY    m_defaultPalEntry[20];

	int m_iGamma ;
	unsigned char   m_twoto8gamma[4] ;
	unsigned char   m_threeto8gamma[8] ;

	CFont m_font ;
	int m_iFontHeight ;
	int m_iFontWidth ;

//Flags
	BOOL m_bDither ;
	BOOL m_bSelPalBeforeMakeCurrent;
	enum enumPALETTE { PAL_332, PAL_WASH } ;
	enumPALETTE m_iWhichPal ;
	BOOL m_bTraceColor ;
	BOOL m_bSysColor ;

	BOOL m_bCaptured;

// Operations
public:
	void SetDCPixelFormat(HDC hdc) ; 
	void OutputGlError(char* label) ; 
	void RestartOpenGL(int cx = -1, int cy = -1) ;
	void DrawGlPalette(CDC* pdc, CRect* pRect) ; 
	void DrawSysPalette(CDC* pdc, CRect* pRect) ;
	void DrawCaptions(CDC* pdc, CRect* pRect) ;

	BOOL CreatePalette(HDC hDC)	;
	void GammaCorrect() ;
	void Fill332Palette(HDC hDC, LOGPALETTE* pPal);
	void FillWashPalette(HDC hDC, LOGPALETTE* pPal) ;

	void ShowRGB(CPoint point);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLpalView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGLpalView();

protected:


// Generated message map functions
protected:
	//{{AFX_MSG(CGLpalView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnOptionsDither();
	afx_msg void OnUpdateOptionsDither(CCmdUI* pCmdUI);
	afx_msg void OnOptionsPalette();
	afx_msg void OnOptionsSelectbeforewglmakecurrent();
	afx_msg void OnUpdateOptionsSelectbeforewglmakecurrent(CCmdUI* pCmdUI);
	afx_msg void OnOptionsTracecolor();
	afx_msg void OnUpdateOptionsTracecolor(CCmdUI* pCmdUI);
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
