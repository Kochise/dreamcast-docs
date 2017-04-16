// ModelviewView.cpp : implementation of the CModelviewView class
//

#include "stdafx.h"
#include "Modelview.h"

#include "ModelviewDoc.h"
#include "ModelviewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModelviewView

IMPLEMENT_DYNCREATE(CModelviewView, COpenGLView)

BEGIN_MESSAGE_MAP(CModelviewView, COpenGLView)
	//{{AFX_MSG_MAP(CModelviewView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModelviewView construction/destruction

CModelviewView::CModelviewView()
{
	// TODO: add construction code here
}

CModelviewView::~CModelviewView()
{
}

void CModelviewView::OnInitialUpdate() 
{
	COpenGLView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	// now set up the lighting and materials so that we get a nice
	// effect when moving the object
	GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_position[] = { 0.0f, 1.0f, 2.0f, 0.0f };

	::glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	::glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	::glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	::glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	::glEnable(GL_LIGHTING);
	::glEnable(GL_LIGHT0);
	::glEnable(GL_AUTO_NORMAL);
	::glEnable(GL_NORMALIZE);
	::glDepthFunc(GL_LEQUAL);
	::glEnable(GL_DEPTH_TEST);
	::glShadeModel (GL_FLAT);

	GLfloat material_ambient[]   = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat material_diffuse[]   = { 0.1f, 0.5f, 0.8f, 1.0f };
	GLfloat material_specular[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat material_shininess[] = { 100.0f };
	GLfloat material_emission[]  = { 0.0f, 0.0f, 0.0f, 1.0f };

	::glMaterialfv(GL_FRONT, GL_AMBIENT,   material_ambient );
	::glMaterialfv(GL_FRONT, GL_DIFFUSE,   material_diffuse );
	::glMaterialfv(GL_FRONT, GL_SPECULAR,  material_specular );
	::glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess );
	::glMaterialfv(GL_FRONT, GL_EMISSION,  material_emission );


	// put up the modeless dialog boxes
	m_ViewMatrixDlg.Create( this );
	
}

// We need to override the COpenGLView version since we need to
// set up two viewports at render time. However, we do need to save
// the dimensions of the window for use at render time. Since we have
// two view, we need to set up the viewing transforms at that time also.
void CModelviewView::OnSize( UINT nType, int w, int h ) 
{
	CView::OnSize( nType, w, h );
	
	// TODO: Add your message handler code here
	if ( 0 >= w || 0 >= h )
		{
		return;
		}

	// OK, now save the dimensions of the window, cutting the width in half
	m_width = w/2;
	m_height = h;

	// Now that the dimensions are set up, we can set up the projection
	// matrix. Since we've overridden OnSize(), we need to do it ourselves

	// select the viewing volumn
    ::glMatrixMode ( GL_PROJECTION );
    ::glLoadIdentity ();

	GLfloat aspectRatio;

    if (m_width <= m_height) 
		{
		aspectRatio = (GLfloat)m_height/(GLfloat)m_width;
		::glFrustum( -2.5, 2.5, -2.5*aspectRatio, 2.5*aspectRatio, 4.0, 25.0 );
		}
    else
		{
		aspectRatio = (GLfloat)m_width/(GLfloat)m_height;
		::glFrustum( -2.5*aspectRatio, 2.5*aspectRatio, -2.5, 2.5, 4.0, 25.0 );
		}
	
	// switch back to the modelview matrix and clear it
    ::glMatrixMode( GL_MODELVIEW );
}


BOOL CModelviewView::RenderScene()
{

	DrawLeftView( );
	DrawRightView( );

	return TRUE;
}

void CModelviewView::DrawCommonStockScene()
{
	::glLoadIdentity();  // clear all matrices

	// Now, rotate about the Y axis, X axis, then move
	// away from the origin. (Remember, these are in reverse
	// order!) This will provide a viewpoint looking down onto
	// the scene that we can pretend isn't here for the purpose
	// of the demonstration.
	::glTranslatef( 0.0f, -1.0f, -8.0f );
	::glRotatef( 15.0f, 1.0f, 0.0f, 0.0f );
	::glRotatef( -25.0f, 0.0f, 1.0f, 0.0f );

	// We don't want the axes effected by lighting
	// so temporarily turn it off.
	::glDisable(GL_LIGHTING);
	Draw3DAxes( -5.0f, 5.0f, 10 );
	::glEnable(GL_LIGHTING);

}

void CModelviewView::DrawCommonScene()
{

	// show the teapot?
	if ( 1 == m_ViewMatrixDlg.m_ShowTeapot)
		{
		auxSolidTeapot(1.0);
		return;
		}


	// Construct the letter "F" out of three blocks
	glPushMatrix();
	    glTranslatef ( -0.5f, 0.0f, 0.0f );  /*  viewing transformation  */
    	glScalef ( 1.0f, 4.0f, 1.0f );   /*  modeling transformation */
		auxSolidCube( 0.5f );   /*  draw the cube   */
	glPopMatrix();

	glPushMatrix();
	    glTranslatef ( 0.0f, -0.25f, 0.0f );  /*  viewing transformation  */
	    auxSolidCube( 0.5f );   /*  draw the cube   */
	glPopMatrix();

	glPushMatrix();
	    glTranslatef ( 0.25f, 0.75f, 0.0f );  /*  viewing transformation  */
	    glScalef ( 2.0f, 1.0f, 1.0f );   /*  modeling transformation */
	    auxSolidCube( 0.5f );   /*  draw the cube   */
	glPopMatrix();

}

void CModelviewView::DrawLeftView()
{
	// Left view	

	// Select viewport
	::glViewport( 0, 0, m_width, m_height );

	DrawCommonStockScene();

	DrawCommonScene();
}

/////////////////////////////////////////////////////////////////////////////
// CMatrixView drawing - Right View

void CModelviewView::DrawRightView()
{
	// Right view	

	// Select viewport
	::glViewport( m_width, 0, m_width, m_height );

	DrawCommonStockScene();

	// Apply the Dialog Box matricies
	::glMultMatrixf( (float *) m_ViewMatrixDlg.m_PreMatrix);
	::glMultMatrixf( (float *) m_ViewMatrixDlg.m_Matrix);

	DrawCommonScene();
}



/////////////////////////////////////////////////////////////////////////////
// CModelviewView diagnostics

#ifdef _DEBUG
void CModelviewView::AssertValid() const
{
	CView::AssertValid();
}

void CModelviewView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CModelviewDoc* CModelviewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CModelviewDoc)));
	return (CModelviewDoc*)m_pDocument;
}
#endif //_DEBUG


