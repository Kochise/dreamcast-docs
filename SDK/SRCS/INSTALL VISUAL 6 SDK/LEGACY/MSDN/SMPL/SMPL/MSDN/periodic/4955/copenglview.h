/////////////////////////////////////////////////////////////////////////////
//
// COpenGLView.h : interface of the COpenGLView class
//
/////////////////////////////////////////////////////////////////////////////


// Include the OpenGL headers
#include "gl\gl.h"
#include "gl\glu.h"
#include "gl\glaux.h"

class COpenGLImage; // forward reference

class COpenGLView : public CView
{
    friend  COpenGLImage;

protected: // create from serialization only
	COpenGLView();
	DECLARE_DYNCREATE(COpenGLView)

// Attributes
public:
	CDocument* GetDocument();  // returns generic document

// Operations
public:
private:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenGLView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COpenGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	const char*	m_ErrorString;  // holds the first wgl/OGL error found

// Generated message map functions
protected:
	//{{AFX_MSG(COpenGLView)
	afx_msg virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg virtual void OnDestroy();
	afx_msg virtual BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg virtual void OnSize(UINT nType, int cx, int cy);
	afx_msg virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// These virtual functions are the user overridable routines
	// Use these routines to customize COpenGLView to
	// your own needs.

	virtual BOOL SetupPixelFormat( void );

	// The Viewport & Frustrum Member Functions
	virtual BOOL SetupViewport( int cx, int cy );
	virtual BOOL SetupViewingFrustum( GLdouble aspect_ratio );
	virtual BOOL SetupViewingTransform( void );

	// Provide a standard animation viewpoint
	BOOL	ViewpointOriginRotation();

	// The Rendering Member Functions
	virtual BOOL PreRenderScene( void ){ return TRUE; }
 	virtual void RenderStockScene( void );
	virtual BOOL RenderScene( void );
	virtual void PostRenderScene( void );

	// A routine that draw the three axes lines
	void	Draw3DAxes( float start = -10.0, float finish = 10.0, int ticks = -1 );

private:

	// Private routines

	void	SetError( int e );
	BOOL	InitializeOpenGL( void );
	void	Draw3DAxesLine( float start, float finish,	int axis_id, int ticks );
	// Private data

	int		m_PixelFormat;
	HGLRC	m_hRC;
	CDC*	m_pDC;

	static const char* const _ErrorStrings[];
};

#ifndef _DEBUG  // debug version in COpenGLView.cpp
inline CDocument* COpenGLView::GetDocument()
   { return (CCDocument*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
