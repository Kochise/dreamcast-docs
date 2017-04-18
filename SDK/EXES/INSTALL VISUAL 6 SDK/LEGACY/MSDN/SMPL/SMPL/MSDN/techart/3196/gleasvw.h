// gleasvw.h : interface of the CGLEasyView class
//
/////////////////////////////////////////////////////////////////////////////

class CGLEasyView : public CView
{
protected: // create from serialization only
	CGLEasyView();
	DECLARE_DYNCREATE(CGLEasyView)

// Attributes
public:
	CGLEasyDoc* GetDocument()   { return (CGLEasyDoc*)m_pDocument; }

	HGLRC m_hrc ; 			//OpenGL Rendering Context
	CPalette* m_pPal ;		//Palette

// Operations
public:
	void PrepareScene() ; 	//OPENGL build display lists
	void DrawScene() ;		//OPENGL draws OpenGL scene
	void OutputGlError(char* label) ; //OPENGL function to display OpenGL errors using TRACE
	
	//
	// Rotation support
	//
	CSize m_angle[4];
	BOOL m_bRotate ;
	void Tick() ;  // See GLEasy.cpp
	void Rotate(BOOL bRotate) ;

	//
	// Multiple object support
	//
	enum enum_OBJECTS {Box=1, Pyramid=2, Dodec=3} ;		
	enum_OBJECTS m_RotatingObject ;
	
	//
	// Support for generating RGB color palette
	//
	BOOL CreateRGBPalette(HDC hDC)	;
	unsigned char ComponentFromIndex(int i, UINT nbits, UINT shift) ;
 	static unsigned char   m_oneto8[2];
    static unsigned char   m_twoto8[4];
    static unsigned char   m_threeto8[8];
    static int             m_defaultOverride[13];
    static PALETTEENTRY    m_defaultPalEntry[20];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLEasyView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGLEasyView();
protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGLEasyView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnRotateStart();
	afx_msg void OnUpdateRotateStart(CCmdUI* pCmdUI);
	afx_msg void OnRotateStop();
	afx_msg void OnUpdateRotateStop(CCmdUI* pCmdUI);
	afx_msg void OnRotateBox();
	afx_msg void OnUpdateRotateBox(CCmdUI* pCmdUI);
	afx_msg void OnRotatePyramid();
	afx_msg void OnUpdateRotatePyramid(CCmdUI* pCmdUI);
	afx_msg void OnRotateDodec();
	afx_msg void OnUpdateRotateDodec(CCmdUI* pCmdUI);
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
