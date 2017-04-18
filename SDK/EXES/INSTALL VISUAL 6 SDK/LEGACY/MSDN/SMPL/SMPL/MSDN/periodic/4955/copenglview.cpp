/////////////////////////////////////////////////////////////////////////////
//
// COpenGLView.cpp : implementation of the COpenGLView class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//#include "resource.h"       // main symbols

#include "COpenGLView.h"

#include <mmsystem.h> // for MM timers (you'll need WINMM.LIB)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



// add support for OpenGL 1.1 if we're using an old header
// These are new PIXELFORMATDESCRIPTOR flags for OpenGL 1.1

#ifndef PFD_GENERIC_ACCELERATED
#define PFD_GENERIC_ACCELERATED		0x00001000
#endif

#ifndef PFD_DEPTH_DONTCARE
#define PFD_DEPTH_DONTCARE			0x20000000
#endif

#define INSTALLABLE_DRIVER_TYPE_MASK  (PFD_GENERIC_ACCELERATED|PFD_GENERIC_FORMAT)


/////////////////////////////////////////////////////////////////////////////

const char* const COpenGLView::_ErrorStrings[]= {
				{"No Error"},					// 0
				{"Unable to get a DC"},			// 1
				{"ChoosePixelFormat failed"},	// 2
				{"SelectPixelFormat failed"},	// 3
				{"wglCreateContext failed"},	// 4
				{"wglMakeCurrent failed"},		// 5
				{"wglDeleteContext failed"},	// 6
				{"SwapBuffers failed"},			// 7

		};

/////////////////////////////////////////////////////////////////////////////
// COpenGLView

IMPLEMENT_DYNCREATE(COpenGLView, CView)

BEGIN_MESSAGE_MAP(COpenGLView, CView)
	//{{AFX_MSG_MAP(COpenGLView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	// If you don't have an ID_ANIMATE, you can either add one
	// to your menu (Add an Animate command) or comment out the
	// references
#if defined ID_ANIMATE
	ON_COMMAND(ID_ANIMATE, OnAnimate)
	ON_UPDATE_COMMAND_UI(ID_ANIMATE, OnUpdateAnimate)
#else
	#pragma message( "No Animation Accelerator Interface Defined in COpenGLView" )
#endif
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenGLView construction/destruction

COpenGLView::COpenGLView() :
	m_PixelFormat(0),m_hRC(0), m_pDC(0),
	m_ErrorString(_ErrorStrings[0])
{
	// TODO: add construction code here

}

/////////////////////////////////////////////////////////////////////////////
COpenGLView::~COpenGLView()
{
}

/////////////////////////////////////////////////////////////////////////////
BOOL COpenGLView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class

	// An OpenGL window must be created with the following flags and must not
    // include CS_PARENTDC for the class style. Refer to SetPixelFormat
    // documentation in the "Comments" section for further information.
    cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// COpenGLView drawing

void COpenGLView::OnDraw(CDC* pDC)
{

	CDocument* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	// Clear out the color & depth buffers
	::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	PreRenderScene();

	::glPushMatrix();
	RenderStockScene();
 	::glPopMatrix();

	::glPushMatrix();
	RenderScene();
	::glPopMatrix();

	// Tell OpenGL to flush its pipeline
	::glFinish();

	// Now Swap the buffers
	if ( FALSE == ::SwapBuffers( m_pDC->GetSafeHdc() ) )
		{
		SetError(7);
		}

	PostRenderScene();
}

//////////////////////////////////////////////////////////////////////////////
// PostRenderScene
// perform post display processing
//
// The default PostRenderScene places the framerate in the
// view's title. Replace this with your own title if you like.
void COpenGLView::PostRenderScene( void )
{

}



/////////////////////////////////////////////////////////////////////////////
// COpenGLView diagnostics

#ifdef _DEBUG
/////////////////////////////////////////////////////////////////////////////
void COpenGLView::AssertValid() const
{
	CView::AssertValid();
}

/////////////////////////////////////////////////////////////////////////////
void COpenGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

/////////////////////////////////////////////////////////////////////////////
CDocument* COpenGLView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDocument)));
	return (CDocument*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////

int COpenGLView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	InitializeOpenGL();

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
void COpenGLView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here

//	NOTE:wglDeleteContext makes the RC non-current, so this step is unnecessary
//	(but you can do it if it makes you feel secure)
//    if ( FALSE ==  ::wglMakeCurrent( 0, 0 ) )
//		{
//		SetError(2);
//        return FALSE;
//		}


    if ( FALSE == ::wglDeleteContext( m_hRC ) )
		{
		SetError(6);
 		}

//	For Color-Index mode, you should reset the palette to the original here

    if ( m_pDC )
		{
        delete m_pDC;
		}
}


/////////////////////////////////////////////////////////////////////////////
// OnEraseBkgnd
// OpenGL has its own routine to erase the background. Here we tell MFC
// not to do it, that we'll take care of it. If we didn't the scene might
// flash.	
BOOL COpenGLView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	//	return CView::OnEraseBkgnd(pDC);
	return TRUE; // tell Windows not to erase the background
}

/////////////////////////////////////////////////////////////////////////////
// OnSize
// We need to set up the viewport when the size changes, and this is the best
// place for it, as long as you don't need to render more than one scene, in which
// case you'd have to do it just before each scene gets rendered.
// We also set up the viewing volumn here since we're using perspective mode. For
// Orthographic you could do it anywhere since you don't need the aspect ratio.
// Finally we also set up the default veiwing transform. For an animated scene you'd
// have to do it just before the scene was rendered.

void COpenGLView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	GLdouble aspect_ratio; // width/height ratio
	
	if ( 0 >= cx || 0 >= cy )
		{
		return;
		}

	SetupViewport( cx, cy );

	// compute the aspect ratio
	// this will keep all dimension scales equal
	aspect_ratio = (GLdouble)cx/(GLdouble)cy;

	// select the projection matrix and clear it
    ::glMatrixMode(GL_PROJECTION);
    ::glLoadIdentity();

	// select the viewing volumn
	SetupViewingFrustum( aspect_ratio );
	
	// switch back to the modelview matrix and clear it
    ::glMatrixMode(GL_MODELVIEW);
    ::glLoadIdentity();
  
	// now perform any viewing transformations
	SetupViewingTransform();
}


//////////////////////////////////////////////////////////////////////////////
// SetError-error string manipulation

/////////////////////////////////////////////////////////////////////////////
void COpenGLView::SetError( int e )
{
	// if there was no previous error,
	// then save this one
	if ( _ErrorStrings[0] == m_ErrorString ) 
		{
		m_ErrorString = _ErrorStrings[e];
		}
}


//////////////////////////////////////////////////////////////////////////////
// InitializeOpenGL
// - just that. This is set up for RGB mode, though I've indicated
// where you would add code for color-index mode.
BOOL COpenGLView::InitializeOpenGL()
{
	// Can we put this in the constructor?
    m_pDC = new CClientDC(this);

    if ( NULL == m_pDC ) // failure to get DC
		{
		SetError(1);
		return FALSE;
		}

	if (!SetupPixelFormat())
		{
        return FALSE;
		}

//	For Color-Index mode, you'd probably create your palette here, right
//	after you select the pixel format

    if ( 0 == (m_hRC = ::wglCreateContext( m_pDC->GetSafeHdc() ) ) )
		{
		SetError(4);
		return FALSE;
		}

    if ( FALSE == ::wglMakeCurrent( m_pDC->GetSafeHdc(), m_hRC ) )
		{
		SetError(5);
		return FALSE;
		}	


	// specify black as clear color
    ::glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// specify the back of the buffer as clear depth
    ::glClearDepth(1.0f);
	// enable depth testing
    ::glEnable(GL_DEPTH_TEST);


	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
BOOL COpenGLView::SetupPixelFormat()
{
  static PIXELFORMATDESCRIPTOR pfd = 
	{
        sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
        1,                              // version number
        PFD_DRAW_TO_WINDOW |            // support window
          PFD_SUPPORT_OPENGL |          // support OpenGL
          PFD_DOUBLEBUFFER,             // double buffered
        PFD_TYPE_RGBA,                  // RGBA type
        24,                             // 24-bit color depth
        0, 0, 0, 0, 0, 0,               // color bits ignored
        0,                              // no alpha buffer
        0,                              // shift bit ignored
        0,                              // no accumulation buffer
        0, 0, 0, 0,                     // accum bits ignored
        16,                             // 16-bit z-buffer
        0,                              // no stencil buffer
        0,                              // no auxiliary buffer
        PFD_MAIN_PLANE,                 // main layer
        0,                              // reserved
        0, 0, 0                         // layer masks ignored
    };
    
    if ( 0 == (m_PixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) )
	    {
		SetError(2);
        return FALSE;
		}

    if ( FALSE == ::SetPixelFormat(m_pDC->GetSafeHdc(), m_PixelFormat, &pfd) )
	    {
       	SetError(3);
        return FALSE;
		}

    return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// SetupViewport
BOOL COpenGLView::SetupViewport( int cx, int cy )
{
	// select the full client area
    ::glViewport(0, 0, cx, cy);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// SetupViewingFrustum
BOOL COpenGLView::SetupViewingFrustum( GLdouble aspect_ratio )
{
	// select a default viewing volumn
    ::gluPerspective(40.0f, aspect_ratio, .1f, 20.0f);
	// here's an ortho view
//	glOrtho( -2.0f, 2.0f, -2.0f, 2.0f, -.10f, 20.0f );

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// SetupViewingTransform
// This is a static, default viewing transform
BOOL COpenGLView::SetupViewingTransform()
{
	// select a default viewing transformation
	// of a 20 degree rotation about the X axis
	// then a -5 unit transformation along Z
	// (It's as good as any I guess...)
	::glTranslatef( 0.0f, 0.0f, -5.0f );
	::glRotatef( 20.0f, 1.0f, 0.0f, 0.0f );
    return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// RenderScene
// This is the default scene for the COpenGLView class.
// draw a red wire sphere inside a light blue cube
BOOL COpenGLView::RenderScene()
{
	// rotate the wire sphere so it's vertically
	// oriented
	::glRotatef( 90.0f, 1.0f, 0.0f, 0.0f );
	::glColor3f( 1.0f, 0.0f, 0.0f );
	::auxWireSphere( .5 );
	::glColor3f( 0.5f, 0.5f, 1.0f );
	::auxWireCube( 1.0 );
    return TRUE;
}	

 
/////////////////////////////////////////////////////////////////////////////
// RenderStockScene
void COpenGLView::RenderStockScene()
{
	// define all vertices   X     Y     Z
	GLfloat v0[3], v1[3], v2[3], v3[3], delta;
	int color = 0;

	delta = 0.5f;

	// define the two colors
	GLfloat color1[3] = { 0.9f, 0.9f, 0.9f };
 	GLfloat color2[3] = { 0.05f, 0.05f, 0.05f };

	v0[1] = v1[1] = v2[1] = v3[1] = 0.0f;

	::glBegin( GL_QUADS );

	for ( int x = -5 ; x <= 5 ; x++ )
		{
		for ( int z = -5 ; z <= 5 ; z++ )
			{
			::glColor3fv( (color++)%2 ? color1 : color2 );
		
			v0[0] = 0.0f+delta*z;
			v0[2] = 0.0f+delta*x;

			v1[0] = v0[0]+delta;
			v1[2] = v0[2];

			v2[0] = v0[0]+delta;
			v2[2] = v0[2]+delta;

			v3[0] = v0[0];
			v3[2] = v0[2]+delta;

			::glVertex3fv( v0 );
			::glVertex3fv( v1 );
			::glVertex3fv( v2 );
			::glVertex3fv( v3 );
			}
		}
	::glEnd();	
	
}


/////////////////////////////////////////////////////////////////////////////
// Draw3DAxes
// Draws lines along the current 3 axes from "start" units to "finish", with 
// "ticks" tickmarks spaced out along it.
void COpenGLView::Draw3DAxes( float start, float finish, int ticks )
{
	// make sure that start < finish
	if ( start > finish )
		{
		float temp = start;
		start = finish;
		finish = start;
		}

	// if ticks < 0 and delta is larger than 1, place the ticks
	// on each scales unit length
	if ( 0 > ticks )
		{
		float delta = finish-start;
		ticks = delta > 1.0 ? (int)delta : 0;
		}

	// draw the tickmarked axes
	Draw3DAxesLine( start, finish, 0, ticks );
	Draw3DAxesLine( start, finish, 1, ticks );
	Draw3DAxesLine( start, finish, 2, ticks );
}

/////////////////////////////////////////////////////////////////////////////
// Draw3DAxesLine
// This routine draws a colored line along a specified axis.
// axis_id = 0 for the x, 1 for the y, and anything else for the z
// start and finish are the starting and ending location, start < finish.
// ticks is the number of ticks to place along the axis.
// If you are using lighting/materials, you might want to wrapper this routine
// so that it's called with lighting disabled, or else the axis lines will be effected
// by lighting claculations - which generally means hard to see.
void COpenGLView::Draw3DAxesLine( float start, float finish, int axis_id, int ticks )
{
	float *px, *py, *pz, zero = 0.0f;
	float tickx, ticky, tickz;
	float *pdx, *pdy, *pdz, tinytick, delta = (finish-start)/(ticks<1?1:ticks);
	GLfloat negativeColor[3] = { 1.0f, 0.0f, 0.0f };
	GLfloat positiveColor[3] = { 0.0f, 1.0f, 0.0f };

	pdx = pdy = pdz = px = py = pz = &zero;
	tickx = ticky = tickz = 0.0f;
	tinytick = 0.05f;

	// select which of the 3 axes is going to vary
	if ( 0 == axis_id ) // X axis
		{
		pdx = &delta;	  
		ticky = tinytick;	  
		px = &start;	  
		}
	else if ( 1 == axis_id ) // Y axis
		{
		pdy = &delta;	  
		tickx = tinytick;	  
		py = &start;	  
		}
	else 	// default Z axis
		{
		pdz = &delta;	  
		ticky = tinytick;	  
		pz = &start;	  
		}

	// turn off the lighting effects
	// since we don't want the axes lines effected by the
	// lighting. You might need to call ::glDisable(GL_LIGHTING)
	// before this routine

	::glBegin(GL_LINES);

	// now draw the two lines that make up the axis
	::glColor3fv( negativeColor ); // negative color
	::glVertex3f( *px, *py, *pz );
	::glVertex3f( 0.0f, 0.0f, 0.0f );

	::glColor3fv( positiveColor ); // positive color
	::glVertex3f( 0.0f, 0.0f, 0.0f );
	::glVertex3f( *px+*pdx*ticks, *py+*pdy*ticks, *pz+*pdz*ticks );

	// now draw the tick marks
	for (int i = 0; i < ticks  ; i++ )
		{
		if ( i < ticks/2 )
			{
			::glColor3fv( negativeColor );
			}
		else
			{
			::glColor3fv( positiveColor );
			}

		::glVertex3f( *px-tickx, *py-ticky, *pz-tickz );
		::glVertex3f( *px+tickx, *py+ticky, *pz+tickz );

		*px += *pdx;
		*py += *pdy;
		*pz += *pdz;
		}

	::glEnd();

	// don't forget to turn lighting effects back on
	// via glEnable(GL_LIGHTING)

}


/////////////////////////////////////////////////////////////////////////////
// OnKeyDown
// This routine runs the keyboard interface.
// Most of the keys accepted are from the numeric keypad

// HOME: Resets viewpoint to initial values (animation keeps going)
// SHIFT-HOME: reset viewpoint & clear movement vectors
// 5: Clear movement vectors
// Up/Down Arrows: change velocity in Z (if shifted, change rotation)
// Left/Right Arrows: change velocity in X (if shifted, change rotation)
// Plus/Minus: change velocity in Y (if shifted, change rotation)
// ESC: Exit animation

void COpenGLView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch ( nChar )
	   {
	   case VK_ESCAPE:	// close down the app
			GetParent()->PostMessage(WM_CLOSE);
			return;
	   default:
			return;
	   }

	// Probably don't ever need this
	//CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
