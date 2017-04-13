// AtlGLWorldImpl.cpp : Implementation of CAtlGLWorld
//
// This is a part of the Active Template Library.
// Copyright (C) 1996-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#include "stdafx.h"
#include "AtlGLWorld.h"
#include "AtlGLWorldImpl.h"

#include <windows.h>
#include <math.h>

#include <comcat.h> // Component Categories

// MIDL generated header files
#include "AtlModel.h"
// #include "Canvas_C.h"
#include "ATLTangramCanvas.h"


// Definition and Declaration of CATID_AtlTangramWorldCategory
#include <initguid.h>
#include "AtlWorldCat.h"

///////////////////////////////////////////////////////////
//
//  Global Constants
//
const GLdouble g_Rotation = -60.0 ; //-75.0 ;
const GLdouble g_TranslateCameraBack = -1.0 ;
static const double PI = 3.141592654;

///////////////////////////////////////////////////////////
//
//  SpecialReg -    Used to register and unregister the component
//                      categories.
//
void CAtlGLWorld::SpecialReg(BOOL bRegister)
{
	// Create the standard COM Category Manager
	ICatRegister* pICatRegister = NULL ;
	HRESULT hr = ::CoCreateInstance(    CLSID_StdComponentCategoriesMgr,
										NULL, CLSCTX_ALL, IID_ICatRegister,
										(void**)&pICatRegister) ;
	if (FAILED(hr))
	{
		ErrorMessage("Could not create the ComCat component.", hr);
		return ;
	}

	// Fill in a Category Info structure.
	CATEGORYINFO CatInfo ;
	CatInfo.catid               = CATID_AtlTangramWorldCategory ;
	CatInfo.lcid                = LOCALE_SYSTEM_DEFAULT ;
	wcscpy(CatInfo.szDescription, L"Atl Tangram World Component Category" ) ;

	// Array of Categories
	int cIDs = 1 ;
	CATID IDs[1] ;
	IDs[0] = CATID_AtlTangramWorldCategory ;

	// Register or Unregister
	if (bRegister)
	{
		// Register the component category.
		hr = pICatRegister->RegisterCategories(1, &CatInfo) ;
		ASSERT_HRESULT(hr) ;

		// Register this component as a member of TangramWorldCategory
		hr = pICatRegister->RegisterClassImplCategories(    CLSID_AtlTangramGLWorld,
															cIDs, IDs ) ;
		ASSERT_HRESULT(hr) ;
	}
	else
	{
		// Unregister the component from its categories.
		hr = pICatRegister->UnRegisterClassImplCategories(  CLSID_AtlTangramGLWorld,
															cIDs, IDs);
		ASSERT_HRESULT(hr) ;

		// --- Check to see if there are other components in this category before we delete it. ---

		// Get the ICatInformation interface.
		ICatInformation* pICatInformation = NULL ;
		hr = pICatRegister->QueryInterface(IID_ICatInformation, (void**)&pICatInformation) ;
		ASSERT_HRESULT(hr) ;

		// Get the IEnumCLSID interface.
		IEnumCLSID* pIEnumCLSID = NULL ;
		hr = pICatInformation->EnumClassesOfCategories(cIDs, IDs, 0, NULL, &pIEnumCLSID) ;
		ASSERT_HRESULT(hr) ;

		// Get the next CLSID in the list.
		CLSID clsid ;
		hr = pIEnumCLSID->Next(1, &clsid, NULL) ;
		ASSERT_HRESULT(hr) ;

		// If hr is S_FALSE, there no components are in this category, so remove it.
		if (hr == S_FALSE)
		{
			// Unregister the component category
			hr = pICatRegister->UnRegisterCategories(cIDs, IDs) ;
			ASSERT_HRESULT(hr) ;
		}

		// CleanUp
		pIEnumCLSID->Release() ;
		pICatInformation->Release() ;
	}

	if (pICatRegister)
	{
		pICatRegister->Release() ;
	}
}

///////////////////////////////////////////////////////////
//
//  Destructor
//
CAtlGLWorld::~CAtlGLWorld()
{
#pragma warning(disable:4786)
	CVisualList::iterator p ;
	for(p = m_VisualList.begin() ; p != m_VisualList.end() ; p++)
	{
		(*p)->ReleaseConnectionPoint();
		(*p)->Release() ;
	}
#pragma warning(default:4786)

	ASSERT(m_pCanvasUnknown == NULL) ;
	ASSERT(m_pCanvas == NULL) ;

	if (m_pGL != NULL)
	{
		delete m_pGL ;
	}
}

///////////////////////////////////////////////////////////
//
//                  ITangramWorld Implementation
//
///////////////////////////////////////////////////////////
//
//  Initialize
//
HRESULT CAtlGLWorld::Initialize(HWND hWnd, double modelWidth, double modelHeight)
{
	// Preconditions
	if (m_pCanvas != NULL)
	{
		ASSERT(m_pCanvas == NULL) ;
		return E_FAIL ;
	}

	if ((hWnd == NULL) || (!::IsWindow(hWnd)) ||
		(modelWidth == 0.0) || (modelHeight == 0.0))
	{
		ASSERT(hWnd != NULL) ;
		ASSERT(::IsWindow(hWnd)) ;
		ASSERT( m_pCanvas != NULL) ;
		ASSERT( (modelWidth != 0.0) && (modelHeight != 0.0)) ;
		return E_INVALIDARG ;
	}

	// Cache the window handle.
	m_hMainWnd = hWnd ;

	// ----- Aggregate the canvas object to handle Canvas messages ------

	// Create the canvas on which the world draws.
	HRESULT hr = ::CoCreateInstance(    CLSID_AtlTangramCanvas,
										GetControllingUnknown(),
										CLSCTX_INPROC_SERVER,
										IID_IUnknown, (void**)&m_pCanvasUnknown) ;
	if (FAILED(hr))
	{
		ErrorMessage("Could not aggregate the canvas component.", hr) ;
		return E_FAIL ;
	}

	//------ Get the IAtlTangramCanvas interface -----

	// Query for the IAtlTangramCanvas interface.
	hr = m_pCanvasUnknown->QueryInterface(IID_IAtlTangramCanvas, (void**)&m_pCanvas) ;
	if (FAILED(hr))
	{
		ErrorMessage("Could not get required interface from Canvas.", hr) ;
		m_pCanvas->Release() ;
		m_pCanvas = NULL ;
		return E_FAIL ;
	}

	// Release the AddRef placed on the outer object by the QI call above.
	GetControllingUnknown()->Release() ;

	// ----- Initialize the canvas component. -----
	RECT rectClient ;
	::GetClientRect(hWnd, &rectClient) ;

	int widthClient = rectClient.right - rectClient.left ;
	int heightClient = rectClient.bottom - rectClient.top ;
	hr = m_pCanvas->Initialize(hWnd, widthClient, heightClient) ;
	ASSERT_HRESULT(hr) ;

	// ------ Create the OpenGL HGRC ------

	// Get the dc from the canvas.
	HDC hdc = NULL ;
	hr = m_pCanvas->GetHDC(&hdc) ;
	ASSERT_HRESULT(hr) ;

	ASSERT(hdc != NULL) ;
	m_hdc = hdc ;

	// Create the OpenGL Context object.
	m_pGL = new CGL ;
	m_pGL->Create(m_hdc) ;

	// Set up the palette.
	HPALETTE hPalTemp = m_pGL->GetPalette() ;
	if (hPalTemp)
	{
		m_pCanvas->SetPalette(hPalTemp) ;
	}

	// Set up CGL.
	m_pGL->MakeCurrent(); // MakeCurrent After the palette is set!
	GLResize(widthClient, heightClient) ;
	GLSetup() ;

	return S_OK;
}

///////////////////////////////////////////////////////////
//
// DeviceToModel -- Do not use with size parameters because addin the org...
//
#pragma optimize( "p", on ) // The following function doesn't work without this.

HRESULT CAtlGLWorld::DeviceToModel(POINT ptIn, TangramPoint2d* pptdOut)
{
	if (!IsValidAddress(pptdOut, sizeof(TangramPoint2d), TRUE))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}
	GLdouble matrixModel[16] ;
	GLdouble matrixProj[16];
	GLint viewport[4] ;
	glGetIntegerv(GL_VIEWPORT, viewport) ;
	glGetDoublev( GL_MODELVIEW_MATRIX, matrixModel) ;
	glGetDoublev(GL_PROJECTION_MATRIX, matrixProj) ;

	// Windows GDI device units have 0,0 as upper left corner.
	// OpenGL puts 0,0 in lower left hand corner. Change it.
	double Xw = static_cast<double>(ptIn.x) ;
	double Yw = static_cast<double>(viewport[3] - ptIn.y) ;

	double Tx = m_ptLowerLeft.x ;
	double Ty = m_ptLowerLeft.y ;
	double Tz = g_TranslateCameraBack ;
	double r = m_ptUpperRight.x ;
	double t = m_ptUpperRight.y ;
	const double n = 1.0 ;
	const double f = 50.0 ;

	double Xn = (2.0 * Xw / static_cast<double>(viewport[2])) - 1.0 ;
	double Yn = (2.0 * Yw / static_cast<double>(viewport[3])) - 1.0 ;

	double sinRot = sin(g_Rotation*PI/180.0) ;
	double cosRot = cos(g_Rotation*PI/180.0) ;

	//double y = -((2*f*n/(f+n)) + Tz)/sinRot ;
	double y = -((Yn*t*Tz/n) + Ty)/(cosRot + (Yn*t*sinRot/n)) ;
	double x = -Xn*r*(y*sinRot + Tz)/n - Tx ;

	pptdOut->x = (x * 20.0 / (m_ptUpperRight.x * 2.0) );
	pptdOut->y = (y * 20.0 / (m_ptUpperRight.y * 2.0) );

	return S_OK ;
}

#pragma optimize( "p", off )

///////////////////////////////////////////////////////////
//
// VisualFromPoint -    Finds the visual which contains POINT pt.
//                      Returns the requested IID for the visual.
//
//  Results:
//          S_OK     -  Found a Visual.
//          S_FALSE -   No visual containing this point.
//                      *ppITangramVisual will be NULL.
//
HRESULT CAtlGLWorld::VisualFromPoint(   POINT pt,
									REFIID iid,
									IUnknown** ppITangramVisual)
{
	// Preconditions.
	if (!IsValidInterfaceOutParam(ppITangramVisual))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}

	// Initialize out parameter.
	*ppITangramVisual = NULL ;

	// Find the shape we clicked on.

	int index = Pick(pt) ;
	// Search the list in reverse order because the
	// most recently selected and last painted object is
	// on the end.

	if (0 <= index && index < m_VisualList.size())
	{
#pragma warning(disable:4786)
		CVisualList::reverse_iterator p = m_VisualList.rbegin() ;
		while(p != m_VisualList.rend())
		{
			if (index-- == 0 )
			{
				return (*p)->QueryInterface(iid, (void**)ppITangramVisual) ;
			}
			p++ ;
		}
#pragma warning(default:4786)
	}
	return S_FALSE ;
}

///////////////////////////////////////////////////////////
//
// ITangramWorld::CreateVisualForModel Implementation
//
HRESULT CAtlGLWorld::CreateVisualForModel(IATLTangramModel* pModel)
{
	// Preconditions.
	if (!IsValidInterface(pModel))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}

	// Create the visual for this model.
	IAtlTangramGLVisual* pVisual = NULL ;
	HRESULT hr = ::CoCreateInstance(CLSID_AtlTangramGLVisual,
									NULL,
									CLSCTX_INPROC_SERVER,
									IID_IAtlTangramGLVisual,
									(void**)&pVisual) ;
	if (FAILED(hr))
	{
		ErrorMessage("Could not create visual for model.", hr) ;
		return  E_FAIL ;
	}

	// Initialize visual.
	hr = pVisual->Initialize(pModel, this) ;
	ASSERT_HRESULT(hr) ;

	// Add visual to list.
	m_VisualList.push_back(pVisual) ;

	return S_OK ;
}

///////////////////////////////////////////////////////////
//
//  SelectVisual
//
HRESULT CAtlGLWorld::SelectVisual(IAtlTangramVisual* pSelectedVisual, BOOL bSelect)
{
	// Precondition
	if (!IsValidInterface(pSelectedVisual))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}

	// Move the selected object to the end of the list so that it
	// will paint last.
	pSelectedVisual->SetSelected(bSelect) ;

	if (bSelect)
	{
		// Cycle through the array looking for pSelectedVisual.
#pragma warning(disable:4786)
		CVisualList::iterator ppV ;
		for(ppV = m_VisualList.begin() ; ppV != m_VisualList.end() ; ppV++)
		{
			// Must compare IUnknown pointers.
			if (::InterfacesAreOnSameComponent(*ppV, pSelectedVisual))
			{
				// Move to the back of the list.
				m_VisualList.push_back(*ppV) ;
				// Remove other entry.
				m_VisualList.erase(ppV) ;

				return S_OK ;
			}
		}
#pragma warning(default:4786)
		return E_FAIL;
	}
	return S_OK ;
}

///////////////////////////////////////////////////////////
//
//  Animate
//
HRESULT __stdcall CAtlGLWorld::Animate()
{
	// Render the OpenGL Scene.
	GLRender() ;

	// Now transfer it to the screen.
	RECT rectDummy ;
	::SetRectEmpty(&rectDummy) ;
	HDC hdcMainWnd = ::GetDC(m_hMainWnd) ;

	HRESULT hr = m_pCanvas->Paint(hdcMainWnd, rectDummy) ;
	ASSERT_HRESULT(hr) ;

	::ReleaseDC(m_hMainWnd, hdcMainWnd);

	return S_OK ;
}


///////////////////////////////////////////////////////////
//
//                  ITangramGLWorld
//
///////////////////////////////////////////////////////////
//
// ModelToDevice
//
HRESULT __stdcall CAtlGLWorld::ModelToDevice(TangramPoint2d ptIn, TangramPoint2d* pptOut)
{
	//Precondition
	if (!IsValidAddress(pptOut, sizeof(TangramPoint2d), TRUE))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}

	//Do the Isotropic scaling
	pptOut->x = ptIn.x * 2.0*(double)m_ptUpperRight.x / 20.0 ;
	pptOut->y = ptIn.y * 2.0*(double)m_ptUpperRight.y / 20.0 ;

	return S_OK ;
}

/////////////////////////////////////////////////////
//
// OpenGL Code
//

#define NUM_MATERIALS 24

#define NUM_GOOD_MATS 16  // good ones among the 24

#define NUM_TEX_MATS 4  // materials for texture

enum {
	EMERALD = 0,
	JADE,
	OBSIDIAN,
	PEARL,
	RUBY,
	TURQUOISE,
	BRASS,
	BRONZE,
	CHROME,
	COPPER,
	GOLD,
	SILVER,
	BLACK_PLASTIC,
	CYAN_PLASTIC,
	GREEN_PLASTIC,
	RED_PLASTIC,
	WHITE_PLASTIC,
	YELLOW_PLASTIC,
	BLACK_RUBBER,
	CYAN_RUBBER,
	GREEN_RUBBER,
	RED_RUBBER,
	WHITE_RUBBER,
	YELLOW_RUBBER
};

/*
int goodMaterials[NUM_GOOD_MATS] = {
		EMERALD, JADE, PEARL, RUBY, TURQUOISE, BRASS, BRONZE,
		COPPER, GOLD, SILVER, CYAN_PLASTIC, WHITE_PLASTIC, YELLOW_PLASTIC,
		CYAN_RUBBER, GREEN_RUBBER, WHITE_RUBBER };
*/
/*  materials:  emerald, jade, obsidian, pearl, ruby, turquoise
 *              brass, bronze, chrome, copper, gold, silver
 *              black, cyan, green, red, white, yellow plastic
 *              black, cyan, green, red, white, yellow rubber

	description: ambient(RGB), diffuse(RGB), specular(RGB), shininess
 *
 */
// 'tea' materials, from aux teapots program
static GLfloat teaMaterial[NUM_MATERIALS][10] = {
	 0.0215f, 0.1745f, 0.0215f,
		0.07568f, 0.61424f, 0.07568f, 0.633f, 0.727811f, 0.633f, 0.6f,
	 0.135f, 0.2225f, 0.1575f,
		0.54f, 0.89f, 0.63f, 0.316228f, 0.316228f, 0.316228f, 0.1f,
	 0.05375f, 0.05f, 0.06625f, // XX
		0.18275f, 0.17f, 0.22525f, 0.332741f, 0.328634f, 0.346435f, 0.3f,
	 0.25f, 0.20725f, 0.20725f,
		1.0f, 0.829f, 0.829f, 0.296648f, 0.296648f, 0.296648f, 0.088f,
	 0.1745f, 0.01175f, 0.01175f,
		0.61424f, 0.04136f, 0.04136f, 0.727811f, 0.626959f, 0.626959f, 0.6f,
	 0.1f, 0.18725f, 0.1745f,
		0.396f, 0.74151f, 0.69102f, 0.297254f, 0.30829f, 0.306678f, 0.1f,
	 0.329412f, 0.223529f, 0.027451f,
		0.780392f, 0.568627f, 0.113725f, 0.992157f, 0.941176f, 0.807843f,
		0.21794872f,
	 0.2125f, 0.1275f, 0.054f,
		0.714f, 0.4284f, 0.18144f, 0.393548f, 0.271906f, 0.166721f, 0.2f,
	 0.25f, 0.25f, 0.25f,  // XX
		0.4f, 0.4f, 0.4f, 0.774597f, 0.774597f, 0.774597f, 0.6f,
	 0.19125f, 0.0735f, 0.0225f,
		0.7038f, 0.27048f, 0.0828f, 0.256777f, 0.137622f, 0.086014f, 0.1f,
	 0.24725f, 0.1995f, 0.0745f,
		0.75164f, 0.60648f, 0.22648f, 0.628281f, 0.555802f, 0.366065f, 0.4f,
	 0.19225f, 0.19225f, 0.19225f,
		0.50754f, 0.50754f, 0.50754f, 0.508273f, 0.508273f, 0.508273f, 0.4f,
	 0.0f, 0.0f, 0.0f, 0.01f, 0.01f, 0.01f,
		0.50f, 0.50f, 0.50f, .25f,
	 0.0f, 0.1f, 0.06f, 0.0f, 0.50980392f, 0.50980392f,
		0.50196078f, 0.50196078f, 0.50196078f, .25f,
	 0.0f, 0.0f, 0.0f,
		0.1f, 0.35f, 0.1f, 0.45f, 0.55f, 0.45f, .25f,
	 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, // XX
		0.7f, 0.6f, 0.6f, .25f,
	 0.0f, 0.0f, 0.0f, 0.55f, 0.55f, 0.55f,
		0.70f, 0.70f, 0.70f, .25f,
	 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f,
		0.60f, 0.60f, 0.50f, .25f,
	 0.02f, 0.02f, 0.02f, 0.01f, 0.01f, 0.01f, // XX
		0.4f, 0.4f, 0.4f, .078125f,
	 0.0f, 0.05f, 0.05f, 0.4f, 0.5f, 0.5f,
		0.04f, 0.7f, 0.7f, .078125f,
	 0.0f, 0.05f, 0.0f, 0.4f, 0.5f, 0.4f,
		0.04f, 0.7f, 0.04f, .078125f,
	 0.05f, 0.0f, 0.0f, 0.5f, 0.4f, 0.4f,
		0.7f, 0.04f, 0.04f, .078125f,
	 0.05f, 0.05f, 0.05f, 0.5f, 0.5f, 0.5f,
		0.7f, 0.7f, 0.7f, .078125f,
	 0.05f, 0.05f, 0.0f, 0.5f, 0.5f, 0.4f,
		0.7f, 0.7f, 0.04f, .078125f };

void specifyMaterial( unsigned int mIndex );

void specifyMaterial( unsigned int mIndex )
{
	if( mIndex >= NUM_MATERIALS )
	{
		mIndex = NUM_MATERIALS - 1;
	}

	GLfloat* pMat = &teaMaterial[mIndex][0] ;

	glMaterialfv (GL_FRONT, GL_AMBIENT, pMat);
	glMaterialfv (GL_BACK, GL_AMBIENT, pMat);
	pMat += 3;
	glMaterialfv (GL_FRONT, GL_DIFFUSE, pMat);
	glMaterialfv (GL_BACK, GL_DIFFUSE, pMat);
	pMat += 3;
	glMaterialfv (GL_FRONT, GL_SPECULAR, pMat);
	glMaterialfv (GL_BACK, GL_SPECULAR, pMat);
	pMat++;
	glMaterialf (GL_FRONT, GL_SHININESS, *pMat*128.0f);
	glMaterialf (GL_BACK, GL_SHININESS, *pMat*128.0f);
}

///////////////////////////////////////////////////////////
//
//  GLResize - Sizes OpenGL to fix the screen.
//
BOOL CAtlGLWorld::GLResize(int cx, int cy)
{

	ASSERT(m_pGL->IsCurrent()) ;

	// Set up mapping 3-D coordinates to the 2-D screen
	GLdouble gldAspect = (GLdouble) cx / (GLdouble) cy;
	m_pGL->OutputGlError("Clear") ;
	glMatrixMode(GL_PROJECTION); m_pGL->OutputGlError("MatrixMode") ;
	glLoadIdentity();
	gluPerspective(30.0, gldAspect, 1.0, 50.0);
	glViewport(0, 0, cx, cy);

	// Do tempory model view
	glMatrixMode(GL_MODELVIEW) ;
	glLoadIdentity() ;
	glTranslated(0.0, 0.0, g_TranslateCameraBack) ;

	// Figure screen dimensions.
	GLdouble matrixModel[16] ;
	GLdouble matrixProj[16];
	GLint viewport[4] ;
	glGetIntegerv(GL_VIEWPORT, viewport) ;
	glGetDoublev( GL_MODELVIEW_MATRIX, matrixModel) ;
	glGetDoublev(GL_PROJECTION_MATRIX, matrixProj) ;

	gluUnProject((double)viewport[0], (double)viewport[1], 0.0,
					matrixModel, matrixProj, viewport,
					&m_ptLowerLeft.x, &m_ptLowerLeft.y, &m_ptLowerLeft.z) ;
	gluUnProject((double)viewport[2], (double)viewport[3], 0.0,
					matrixModel, matrixProj, viewport,
					&m_ptUpperRight.x, &m_ptUpperRight.y, &m_ptUpperRight.z) ;

	glTranslated(m_ptLowerLeft.x, m_ptLowerLeft.y, 0.0) ;
	glRotated(g_Rotation, 1.0, 0.0, 0.0) ;

	m_pGL->OutputGlError("__LINE__") ;
	return TRUE ;
}

///////////////////////////////////////////////////////////
//
// GLSetup - Prepares OpenGL for rendering.
//
static float position[] = {0.0f, 0.5f, 0.25f, 1.0f};

BOOL CAtlGLWorld::GLSetup()
{
	ASSERT(m_pGL->IsCurrent()) ;

	// Enable depth calculations
	glEnable(GL_DEPTH_TEST);    m_pGL->OutputGlError("glEnable (GL_DEPTH_TEST);") ;

	// Lighting from pipe
	static float ambient[] = {1.0f, 1.0f, 1.0f, 1.0f};
	static float diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
	static float specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	static float lmodel_ambient[] = {1.0f, 1.0f, 1.0f, 1.0f};

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	// Enable lighting calculations
	glEnable(GL_LIGHTING) ;         m_pGL->OutputGlError("glEnable (GL_LIGHTING) ;") ;
	glEnable(GL_LIGHT0) ;           m_pGL->OutputGlError("glEnable (GL_LIGHT0) ;") ;

	// Set the color to clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f) ; m_pGL->OutputGlError("__LINE__") ;

	return TRUE ;
}

///////////////////////////////////////////////////////////
//
//  GLRender - Renders the Tangram playing field.
//
BOOL CAtlGLWorld::GLRender()
{
	ASSERT(m_pGL->IsCurrent()) ;

	// Set up some colors
	static GLdouble red[3] = {0.8, 0.0, 0.0 } ;
	static GLdouble green[3] = {0.0, 0.75, 0.0} ;
	static GLdouble purple[3] = {1.0, 0.14, 0.6667} ;
	static GLdouble blue[3] = {0.0, 0.0, 0.75} ;

	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); m_pGL->OutputGlError("__LINE__") ;

	int iIndex ;
	if (m_bPicking)
	{
		iIndex = m_VisualList.size() ;
	}
	else
	{
		// Draw table
		specifyMaterial(COPPER) ;

		glBegin(GL_POLYGON);
			glNormal3d(0.0, 0.0, 1.0) ;
			glVertex3d(0.0, 0.0, 0.0) ;
			glVertex3d(2*m_ptUpperRight.x, 0.0, 0.0) ;
			glVertex3d(2*m_ptUpperRight.x, 2*m_ptUpperRight.y, 0.0) ;
			glVertex3d(0.0, 2*m_ptUpperRight.y, 0.0) ;
		glEnd() ;
	}

// Draw Sphere.
	specifyMaterial(GOLD) ;

	glPushMatrix() ;
	glTranslatef(position[0],position[1],position[2]) ;
	auxSolidSphere(.075) ;
	glPopMatrix() ;

	// Draw tanrgam pieces.
	specifyMaterial(SILVER) ;

	// Draw each piece.
#pragma warning(disable: 4786)
	CVisualList::iterator p ;
	for(p = m_VisualList.begin() ; p != m_VisualList.end() ; p++)
	{
		if (m_bPicking)
		{
			glPushName((GLuint)iIndex--) ; // Picking
		}

		(*p)->DrawOn(m_pCanvas) ;

		if (m_bPicking)
		{
			glPopName() ;
		}
	}
#pragma warning(default: 4786)
	glFlush() ;
	GdiFlush() ;

	m_pGL->OutputGlError("__LINE__") ;
	return TRUE ;
}

///////////////////////////////////////////////////////////
//
//  Pick - Find shape corresponding to point.
//
int CAtlGLWorld::Pick(POINT pt)
{
	// Set Picking Mode
	m_bPicking = TRUE ;

	// Get Viewport
	GLint viewport[4] ;
	glGetIntegerv(GL_VIEWPORT, viewport) ; m_pGL->OutputGlError("__LINE__") ;

	// Set Selection Buffer.
	#define BUFSIZE 512
	GLuint selectBuf[BUFSIZE] ;
	glSelectBuffer(BUFSIZE, selectBuf) ;

	// Turn On Selection Mode.
	glRenderMode(GL_SELECT) ;

	// Initialize Name Stack
	glInitNames() ;
	// NOTE: Depends on the Visual to push the name...

	// Set Up Picking Matrix
	glMatrixMode(GL_PROJECTION) ; m_pGL->OutputGlError("__LINE__") ;
	glPushMatrix() ;
	glLoadIdentity() ;
	gluPickMatrix( (double)pt.x,
					(double)(viewport[3]-pt.y),
					5.0, 5.0,
					viewport) ;
	gluPerspective(30.0, (GLdouble)viewport[2]/(GLdouble)viewport[3], 1.0, 50.0); // Copied from OnResize!

	glMatrixMode(GL_MODELVIEW) ;
	glPushMatrix() ;
		glLoadIdentity() ;
		glTranslated(m_ptLowerLeft.x,m_ptLowerLeft.y, g_TranslateCameraBack) ;
		glRotated(g_Rotation, 1.0, 0.0, 0.0) ;

		// Re-Render Scene for Picking.
		GLRender() ;
	glPopMatrix() ;

	glMatrixMode(GL_PROJECTION) ;
	glPopMatrix() ;

	glFlush() ; // Just in Case.

	// Turn Off Selection Mode.
	GLint hits = glRenderMode(GL_RENDER) ; m_pGL->OutputGlError("__LINE__") ;

	// OnRender requires this...
	glMatrixMode(GL_MODELVIEW) ;

	// Find Hits
	int NameHit = 0 ;
	GLuint Z1 = 0 ;
	GLuint Zi ;

	if (hits < -1)
	{
		ASSERT(0) ;
	}
	else
	{
		GLuint* ptr = selectBuf ;
		for (int i = 0 ; i < hits ; i++)
		{
			GLuint cNames = *ptr ;
			ptr++ ;
			Zi = *ptr ;
			ptr++ ;
			ptr++ ;
			for (GLuint j = 0 ; j < cNames ; j++)
			{
				if ((Z1==0) || (Zi < Z1))
				{
					Z1 = Zi ;
					NameHit = (int)*ptr ;
				}
				ptr++ ;
			} //for j ;
		} // for i
	} //else

	// Turn Picking Mode Off
	m_bPicking = FALSE ;
	if ( (NameHit > 0) && (NameHit <= m_VisualList.size()) )
	{
		return --NameHit;
	}
	else
	{
		return -1 ;
	}
}
