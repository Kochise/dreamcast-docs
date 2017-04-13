// MainFrm.cpp : implementation of the CMFCMainFrame class
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
#include "MFCTangram.h"
#include "MainFrm.h"
#include "MFCTangramConfigDlg.h"
#include "objbase.h"
#include <oleauto.h>
#include <stdlib.h> //for rand()
#include <time.h>

// Interface definitions.
#include "ATLModel.h"
#include "ATLModel_i.c"
#include "AtlTangramCanvas.h"
#include "AtlTangramCanvas_i.c"
#include "AtlGdiWorld_i.c"
#include "AtlGdiWorld.h"
#include "AtlGLWorld.h"
#include "AtlGLWorld_i.c"

// Others
#include "util.h"
#include "util.cpp"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int POLYGONS = 7;

///////////////////////////////////////////////////////////
//
// Statics
//
CString CMFCMainFrame::s_strClassName = "" ;

/////////////////////////////////////////////////////////////////////////////
// CMFCMainFrame

BEGIN_MESSAGE_MAP(CMFCMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMFCMainFrame)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMFCMainFrame construction/destruction

///////////////////////////////////////////////////////////
//
// Constructor
//
CMFCMainFrame::CMFCMainFrame()
:   m_pWorld(NULL),
	m_pSelectedVisual(NULL)
{
	m_sizedDiff.cx = 0.0 ;
	m_sizedDiff.cy = 0.0 ;
}

///////////////////////////////////////////////////////////
//
// Destructor
//
CMFCMainFrame::~CMFCMainFrame()
{
	if (m_pWorld != NULL)
	{
		m_pWorld->Release() ;
	}
	POSITION pos = m_ModelList.GetHeadPosition();
	while( pos != NULL )
	{
		IATLTangramModel* pITangramModel = m_ModelList.GetNext( pos ) ;
		pITangramModel->Release();
		m_ModelList.RemoveHead();
	}
	m_ModelList.RemoveAll();

/**/
}


int CMFCMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
	{
		TRACE0("Could not create main window.\r\n") ;
		return -1;
	}

	// Initialize
	CRect aRect ;
	GetClientRect(&aRect) ;
	if (!Initialize(aRect.Width(), aRect.Height()))
	{
		TRACE0("Cannot initialize main window.\r\n") ;
		return -1 ;
	}

	return 0;
}

BOOL CMFCMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMFCMainFrame diagnostics

#ifdef _DEBUG
void CMFCMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMFCMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

///////////////////////////////////////////////////////////
//
// Initialize
//
BOOL CMFCMainFrame::Initialize(int cx, int cy)
{
	ASSERT( (cx != 0) && (cy != 0)) ;

	// Which components are in the IWorldComponent Category.
	CMFCTangramConfigDlg dlg;
	if (dlg.DoModal() != IDOK)
	{
		TRACE0("User canceled the dialog box. Fail initialization.\r\n") ;
		return FALSE ;
	}

	// Did the user want to use local or inproc?
	DWORD clsctx = (dlg.m_bLocalModel) ? CLSCTX_LOCAL_SERVER : CLSCTX_INPROC_SERVER ;

	// Create the desired world selected component.
	HRESULT hr = ::CoCreateInstance(    dlg.m_clsid,           // either Gdi or GL
										NULL,
										CLSCTX_INPROC_SERVER,
										IID_IAtlTangramWorld,
										reinterpret_cast<void**>(&m_pWorld)) ;
	if (FAILED(hr))
	{
		ErrorMessage("Failed to create the world component.", hr) ;
		return FALSE ;
	}

	// Initialize the world.
	hr = m_pWorld->Initialize(m_hWnd, 20.0, 20.0) ;
	if (FAILED(hr))
	{
		ErrorMessage("Cannot initialize World.\r\n", hr) ;
		m_pWorld->Release() ;
		m_pWorld = NULL ;
		return FALSE ;
	}

	// Create and initialize the tangrams pieces.
	struct PolygonInit{
		int iSides ;
		TangramPoint2d points[4] ;
	};

	PolygonInit polygons[7] = {
		// Sides   Vertex 0     1            2            3
		{ 4,  {{0.0, 0.0 }, {1.0, 0.0 }, {1.0, 1.0 }, {0.0, 1.0 }} }, // Square
		{ 3,  {{0.0, 0.0 }, {1.0, 0.0 }, {0.0, 1.0 }, {9.9, 9.9 }} }, // Small Triangle
		{ 3,  {{0.0, 0.0 }, {1.0, 0.0 }, {0.0, 1.0 }, {9.9, 9.9 }} }, // Small Triangle
		{ 3,  {{0.0, 0.0 }, {2.0, 0.0 }, {1.0, 1.0 }, {9.9, 9.9 }} }, // Medium Triangle
		{ 3,  {{0.0, 0.0 }, {2.0, 0.0 }, {0.0, 2.0 }, {9.9, 9.9 }} }, // Big Triangle
		{ 3,  {{0.0, 0.0 }, {2.0, 0.0 }, {0.0, 2.0 }, {9.9, 9.9 }} }, // Big Triangle
		{ 4,  {{0.0, 0.0 }, {1.0, 0.0 }, {2.0, 1.0 }, {1.0, 1.0 }} }, // Paralelagram
	};

	double x = 0.0 ;
	IATLTangramModel* pITangramModel = NULL ;

	for (int i = 0 ; i < POLYGONS ; i ++)
	{
		hr = ::CoCreateInstance(CLSID_ATLTangramModel,
								NULL,
								clsctx ,
								IID_IATLTangramModel,
								(void**)&pITangramModel);
		if (FAILED(hr))
		{
			ErrorMessage("Failed to create Tangram piece.", hr) ;
			return FALSE ;
		}

		// Set the vertices for this model.
		hr = pITangramModel->SetVertices(polygons[i].iSides, polygons[i].points) ;
		ASSERT_HRESULT(hr) ;

		// Add the interface to the array.
		// This makes a copy of the pointer without
		// an AddRef(), so we don't have to Release() the
		// model
		m_ModelList.AddTail(pITangramModel) ;

		hr = m_pWorld->CreateVisualForModel(pITangramModel) ;
		ASSERT_HRESULT(hr) ;

		// Get the IATLTangramTransform interface.
		IATLTangramTransform* pITangramTransform = NULL ;
		HRESULT hr = pITangramModel->QueryInterface(IID_IATLTangramTransform, (void**)&pITangramTransform ) ;
		ASSERT_HRESULT(hr) ;

		// Place the tangram piece.
		pITangramTransform->Translate(x, 1.0) ;
		x += 2.0  ;

		// We are done with IATLTangramTransform.
		pITangramTransform->Release() ;

	}

	return TRUE ;
}

///////////////////////////////////////////////////////////
//
// Create - Helper function for creating  the window class
//              and window.
//
BOOL CMFCMainFrame::Create()
{
	if (s_strClassName.IsEmpty())
	{
		s_strClassName = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,
											AfxGetApp()->LoadStandardCursor(IDC_ARROW),
											0,
											AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	}

	// Set screen size.
	CClientDC dc(NULL) ;
	int cx = 640 ;
	int cy = 480 ;

	return CWnd::CreateEx(  0, s_strClassName, AfxGetAppName(),
							WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|
							WS_BORDER|WS_MINIMIZEBOX|WS_VISIBLE,
							0,0, cx, cy,
							NULL, NULL);
}

///////////////////////////////////////////////////////////
//
// OnPaint
//
void CMFCMainFrame::OnPaint()
{
	CPaintDC dc(this);

	// Get ICanvas interface pointer.
	IAtlTangramCanvas* pCanvas = NULL ;
	HRESULT hr = m_pWorld->QueryInterface(IID_IAtlTangramCanvas, (void**)&pCanvas) ;
	ASSERT_HRESULT(hr) ;

	// Use it.
	hr = pCanvas->Paint(dc.m_hDC, dc.m_ps.rcPaint) ;
	ASSERT_HRESULT(hr) ;

	// Lose it.
	pCanvas->Release() ;
}

///////////////////////////////////////////////////////////
//
// Handle both left and right button down messages.
//
void CMFCMainFrame::DoButtonDown(UINT nWhichButton, CPoint point)
{
	if (m_pSelectedVisual != NULL)
	{
		// User may have pressed right button then left button.
		TRACE0("OnLButtonDown: Visual already selected.\r\n") ;
		return ;
	}

	HRESULT hr = m_pWorld->VisualFromPoint(point, IID_IAtlTangramVisual, (IUnknown**)&m_pSelectedVisual) ; //@
	ASSERT(SUCCEEDED(hr)) ;
	if (hr == S_OK)
	{
		ASSERT(m_pSelectedVisual != NULL) ;
		//
		// Get mouse pointer offset from model's origin.
		//

		// Convert to Model Coordinates.
		TangramPoint2d ptModel ;
		hr = m_pWorld->DeviceToModel(point, &ptModel);
		ASSERT_HRESULT(hr) ;

		// Get the Model's ITrangramTransform interface.
		IATLTangramTransform* pITangramTransform = NULL ;
		hr = m_pSelectedVisual->GetModel(IID_IATLTangramTransform, (IUnknown**)&pITangramTransform) ;
		ASSERT_HRESULT(hr) ;

		// Where does the model reside.
		TangramPoint2d ptOrigin ;
		hr = pITangramTransform->GetTranslation(&ptOrigin) ;
		ASSERT_HRESULT(hr) ;

		// Release ITangramTransfrom.
		pITangramTransform->Release() ;
		pITangramTransform = NULL ;

		// Get difference between where the mouse clicked and the origin of the piece.
		m_sizedDiff.cx = ptModel.x - ptOrigin.x ;
		m_sizedDiff.cy = ptModel.y - ptOrigin.y ;

		// Select the visual.
		hr = m_pWorld->SelectVisual(m_pSelectedVisual, TRUE) ;
		ASSERT_HRESULT(hr) ;

		// Update the display
		hr = m_pWorld->Animate() ;
		ASSERT_HRESULT(hr) ;

		// Capture the mouse.
		SetCapture() ;
		}
	else
	{
		TRACE0("DoButtonDown: PtInVisual returned Null.\r\n") ;
	}
}

void CMFCMainFrame::PostNcDestroy()
{
	delete this;
}

///////////////////////////////////////////////////////////
//
// OnLButtonDown Message Handler
//
void CMFCMainFrame::OnLButtonDown(UINT nWhichButton, CPoint point)
{
	DoButtonDown(nWhichButton, point) ;
}

///////////////////////////////////////////////////////////
//
// OnLButtonUp Message Handler
//
void CMFCMainFrame::OnLButtonUp(UINT nWhichButton, CPoint point)
{
	if (::GetCapture() != m_hWnd)
	{
		return ;
	}

	if (m_pSelectedVisual != NULL)
	{
		// De-select the currently selected model.
		HRESULT hr = m_pWorld->SelectVisual(m_pSelectedVisual, FALSE) ;
		ASSERT_HRESULT(hr) ;

		// Cleanup
		m_pSelectedVisual->Release() ;
		m_pSelectedVisual = NULL ;
	}

	// We don't need the mouse capture any more.
	::ReleaseCapture() ;
}

///////////////////////////////////////////////////////////
//
// OnMouseMove Message Handler
//
void CMFCMainFrame::OnMouseMove(UINT nWhichButton, CPoint point)
{
	if ((::GetCapture() != m_hWnd) ||
		(nWhichButton & (MK_SHIFT | MK_CONTROL)))
	{
		// Return if another window has captured the mouse or
		// if the SHIFT or CTRL key is pressed, signaling rotation.
		return ;
	}

	// Make sure that mouse is not outside of our client area.
	CRect rectClient ;
	GetClientRect(&rectClient) ;
	if (!rectClient.PtInRect(point))
	{
		return ;
	}

	ASSERT(m_pSelectedVisual != NULL) ;

	// Convert to Model Coordinates.
	TangramPoint2d ptModel ;
	HRESULT hr = m_pWorld->DeviceToModel(point, &ptModel);
	ASSERT_HRESULT(hr) ;

	//Get the Model's ITangramTransfrom interface.
	IATLTangramTransform* pITangramTransform = NULL ;
	hr = m_pSelectedVisual->GetModel(IID_IATLTangramTransform, (IUnknown**)&pITangramTransform) ;
	ASSERT_HRESULT(hr) ;

	// Move the model.
	hr = pITangramTransform->Translate(ptModel.x - m_sizedDiff.cx, ptModel.y - m_sizedDiff.cy);
	ASSERT_HRESULT(hr) ;

	// Release the interface.
	pITangramTransform->Release() ;
}

///////////////////////////////////////////////////////////
//
// Rotate using the right mouse button.
//
void CMFCMainFrame::OnRButtonDown(UINT nWhichButton, CPoint point)
{
	DoButtonDown(nWhichButton, point) ;
}

///////////////////////////////////////////////////////////
//
// Rotate the model. Shift key determines direction.
//
void CMFCMainFrame::OnRButtonUp(UINT nWhichButton, CPoint point)
{
	if (::GetCapture() != m_hWnd)
	{
		return ;
	}

	if (m_pSelectedVisual != NULL)
	{
		//----- Rotate the shape. -----

		// Check to see of the mouse pointer is still over the same visual.
		IAtlTangramVisual* pSameVisual = NULL ;
		HRESULT hr = m_pWorld->VisualFromPoint(point, IID_IAtlTangramVisual, (IUnknown**)&pSameVisual) ;
		ASSERT_HRESULT(hr) ;
		ASSERT(pSameVisual != NULL) ;

		if (::InterfacesAreOnSameComponent(m_pSelectedVisual, pSameVisual))
		{
			//Get the Model's IATLTangramTransform interface.
			IATLTangramTransform* pITangramTransform = NULL ;
			hr = m_pSelectedVisual->GetModel(IID_IATLTangramTransform, (IUnknown**)&pITangramTransform);
			ASSERT_HRESULT(hr) ;

			// Rotate the model.
			int iRotationDirection = (nWhichButton & MK_SHIFT) ? -1 : 1 ;
			double dDegrees  ;
			pITangramTransform->GetRotation(&dDegrees) ;
			pITangramTransform->Rotate(dDegrees + 45.0*iRotationDirection);

			// Release IATLTangramTransform
			pITangramTransform->Release() ;
			pITangramTransform = NULL ;
		}

		// Cleanup
		pSameVisual->Release() ;
		pSameVisual = NULL ;

		// De-select the currently selected model.
		hr = m_pWorld->SelectVisual(m_pSelectedVisual, FALSE) ;
		ASSERT_HRESULT(hr) ;

		// Cleanup
		m_pSelectedVisual->Release() ;
		m_pSelectedVisual = NULL ;
	}

	// We don't need the mouse capture any more.
	::ReleaseCapture() ;
}

///////////////////////////////////////////////////////////
//
// OnPaletteChanged Message Handler
//
void CMFCMainFrame::OnPaletteChanged(CWnd* pFocusWnd)
{
	if (pFocusWnd != this)
	{
		OnQueryNewPalette() ;
	}
}

///////////////////////////////////////////////////////////
//
// QueryNewPalette Message Handler
//
BOOL CMFCMainFrame::OnQueryNewPalette()
{
	if (m_hWnd == NULL)
	{
		return FALSE ;
	}

	// Get ICanvas interface pointer.
	IAtlTangramCanvas* pCanvas = NULL ;
	HRESULT hr = m_pWorld->QueryInterface(IID_IAtlTangramCanvas, (void**)&pCanvas) ;
	if (SUCCEEDED(hr))
	{
		// Use it.
		hr = pCanvas->OnQueryNewPalette(m_hWnd);

		// Lose it.
		pCanvas->Release() ;
	}
	return SUCCEEDED(hr);
}



void CMFCMainFrame::OnDestroy()
{
	CFrameWnd::OnDestroy();
/*
	POSITION pos = m_ModelList.GetHeadPosition();
	while( pos != NULL )
	{
		IATLTangramModel* pITangramModel = m_ModelList.GetNext( pos ) ;
		pITangramModel->Release();
		m_ModelList.RemoveHead();
	}
	m_ModelList.RemoveAll();
	if (m_pWorld != NULL)
	{
		m_pWorld->Release() ;
	}
	*/
}
