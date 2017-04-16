// SceneVw.cpp : implementation of the CSceneView class
//

#include "stdafx.h"
#include "EasyBit.h"

#include "mainfrm.h"

#include "EasyBdoc.h"
#include "SceneVw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSceneView

IMPLEMENT_DYNCREATE(CSceneView, CView /* CGLView */)

BEGIN_MESSAGE_MAP(CSceneView, /* ## CView */  CGLView)
	//{{AFX_MSG_MAP(CSceneView)
	ON_COMMAND(ID_ROTATE_START, OnRotateStart)
	ON_UPDATE_COMMAND_UI(ID_ROTATE_START, OnUpdateRotateStart)
	ON_COMMAND(ID_ROTATE_STOP, OnRotateStop)
	ON_UPDATE_COMMAND_UI(ID_ROTATE_STOP, OnUpdateRotateStop)
	ON_COMMAND(ID_ROTATE_BOX, OnRotateBox)
	ON_UPDATE_COMMAND_UI(ID_ROTATE_BOX, OnUpdateRotateBox)
	ON_COMMAND(ID_ROTATE_DODEC, OnRotateDodec)
	ON_UPDATE_COMMAND_UI(ID_ROTATE_DODEC, OnUpdateRotateDodec)
	ON_COMMAND(ID_ROTATE_PYRAMID, OnRotatePyramid)
	ON_UPDATE_COMMAND_UI(ID_ROTATE_PYRAMID, OnUpdateRotatePyramid)
	ON_WM_SIZE()
	ON_COMMAND(ID_TIMING_BLTING, OnTimingBlting)
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSceneView construction/destruction

CSceneView::CSceneView()
{
	m_bRotate = FALSE ;
	m_bTiming = FALSE ;
}

CSceneView::~CSceneView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CSceneView message handlers

int CSceneView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (/* ## CView */  CGLView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Create and get metrics for our font used in the captions.
	m_font.CreateStockObject(ANSI_FIXED_FONT); 

	CDC dc ;
	dc.CreateCompatibleDC(NULL) ;
	CFont* pOldFont = (CFont*)dc.SelectObject(&m_font) ;
	TEXTMETRIC tm ;
	dc.GetTextMetrics(&tm) ;
	if (pOldFont) dc.SelectObject(pOldFont) ;
	m_iFontHeight = tm.tmHeight ;
	m_iFontWidth = tm.tmMaxCharWidth ;

	
	return 0;
}

void CSceneView::OnInitialUpdate() 
{
 	CGLView::OnInitialUpdate();
 
	//
	// The Rotating Object is also displayed in the Status Bar.
	//
	m_pMainFrame = (CMainFrame*)GetParentFrame() ;
	m_pMainFrame->m_wndStatusBar.SetBitmap(m_aScene.GetRotatingObject()-1) ;
}

void CSceneView::OnSize(UINT nType, int cx, int cy) 
{
	if ( (cx <= 0) || (cy <= 0) ) return ;
	//
	// Set Size for bitmaps ;
	//
	m_sizeBitmap.cy = cy / 4;
	m_sizeBitmap.cx = m_sizeBitmap.cy ;

	//
	// Move m_aScene's origin over to make room for the bitmaps on the left side of display.
	//
	m_aScene.SetOrigin(m_sizeBitmap.cx, 0) ;
	CGLView::OnSize(nType, cx - m_sizeBitmap.cx, cy);

	CDC* pdcTemp;
	CPalette* pPalTemp;
		
	//
	// Use Nigel's Animation Library CDIBSection
	//	
		// Create DIB.
		m_aDIBSurface.Create(m_sizeBitmap.cx, m_sizeBitmap.cy, (HPALETTE)NULL) ;	
		pdcTemp = m_aDIBSurface.GetDC() ;

		// Create Scene.
		m_aSceneOnDIB.Create(pdcTemp) ;									

		// Set palette in DIB to palette in scene.
		pPalTemp = m_aSceneOnDIB.GetPalette() ;
		if (pPalTemp) m_aDIBSurface.SetPalette(pPalTemp) ;

		// Render scene onto DIB.
		m_aSceneOnDIB.Resize(m_sizeBitmap.cx, m_sizeBitmap.cy) ; //Doesn't resize?!!!!
		m_aSceneOnDIB.Init() ;
		m_aSceneOnDIB.Render() ;

		// Draw a border around the DIB.
		DrawBlueBorder(pdcTemp) ;


	//
	// Use my CSimpleDIB to create an 8 bpp DIB section and render a CSceneDodec on it.
	//
		m_theSimpleDIB[0].Create(m_sizeBitmap.cx, m_sizeBitmap.cy, 8) ;
	 	pdcTemp = m_theSimpleDIB[0].GetDC() ;

		CSceneDodec aSceneDodec;
		aSceneDodec.Create(pdcTemp) ;

		pPalTemp = aSceneDodec.GetPalette() ;	
		if (pPalTemp) m_theSimpleDIB[0].SetPalette(pPalTemp) ;

		aSceneDodec.Resize(m_sizeBitmap.cx, m_sizeBitmap.cy) ; //Doesn't resize?!!!!
		aSceneDodec.Init() ;
		aSceneDodec.Render() ;

		DrawBlueBorder(pdcTemp) ;
	   	DrawCaption(pdcTemp, _T("8 bpp")) ;
 
	//
	// Use my CSimpleDIB to create a 16 bpp DIB section and render a Box on it.
	//

		m_theSimpleDIB[1].Create(m_sizeBitmap.cx, m_sizeBitmap.cy, 16) ;
		pdcTemp = m_theSimpleDIB[1].GetDC() ;

		CSceneBox aSceneBox ;
		aSceneBox.Create(pdcTemp) ;

		// Not needed because its a 16 bpp DIB.
		//pPalTemp = aSceneBox.GetPalette() ;
		//if (pPalTemp) m_theSimpleDIB[1].SetPalette(pPalTemp) ;

		aSceneBox.Resize(m_sizeBitmap.cx, m_sizeBitmap.cy) ; //Doesn't resize?!!!!
		aSceneBox.Init() ;
		aSceneBox.Render() ;

		DrawBlueBorder(pdcTemp) ;
	   	DrawCaption(pdcTemp, _T("16 bpp")) ;

	//
	// Use my CSimpleDIB to create a 24 bpp DIB and render a pyramid on it.
	//
		m_theSimpleDIB[2].Create(m_sizeBitmap.cx, m_sizeBitmap.cy, 24) ;
		pdcTemp = m_theSimpleDIB[2].GetDC() ;

		CScenePyramid aScenePyramid ;
		aScenePyramid.Create(pdcTemp) ;

		// Not needed DIB is 24 bpp.
		//	pPalTemp = aScenePyramid.GetPalette() ;
		//	if (pPalTemp) m_theSimpleDIB[2].SetPalette(pPalTemp) ;

		aScenePyramid.Resize(m_sizeBitmap.cx, m_sizeBitmap.cy) ; //Doesn't resize?!!!!
		aScenePyramid.Init() ;
		aScenePyramid.Render() ;

		DrawBlueBorder(pdcTemp) ;
	   	DrawCaption(pdcTemp, _T("24 bpp")) ;
}

//
// OnDraw
//

void CSceneView::OnDraw(CDC* pDC) 
{
	CGLView::OnDraw(pDC);	

	if (!m_bRotate)
	{
		// Don't show the bitmaps when an object is rotating.

	    // if we have a palette for background scene, 
	    // select and realize it.
      CPalette *ppalOld = NULL;
      CPalette* pPalScene = m_aScene.GetPalette() ;
      if(pPalScene)
      {
        ppalOld = pDC->SelectPalette(pPalScene, 0);
        pDC->RealizePalette();		
      }

      // Draw the DIBSurface.
      m_aDIBSurface.Draw(pDC) ;

      // Draw the simple DIBs.
      m_theSimpleDIB[0].Draw(pDC, 0, m_sizeBitmap.cy) ;
      // 16 and 32 bpp DIBs do not need palettes.
      m_theSimpleDIB[1].Draw(pDC, 0, m_sizeBitmap.cy*2) ; // Must have palette selected if drawing on 8bpp display
      m_theSimpleDIB[2].Draw(pDC, 0, m_sizeBitmap.cy*3) ; // Must have palette selected if drawing on 8bpp display

      // select old palette if we altered it
      if (ppalOld) pDC->SelectPalette(ppalOld, 0);	
 	}

}

//
// Helper functions
//
void CSceneView::DrawBlueBorder(CDC* pdc)
{
	CPen aPen(PS_SOLID, 4, RGB(0,0,255)) ;
	CPen* pOldPen = (CPen*)pdc->SelectObject(&aPen) ;
	CBrush* pOldBrush = (CBrush*)pdc->SelectStockObject(NULL_BRUSH) ;
	pdc->Rectangle(0,0,m_sizeBitmap.cx, m_sizeBitmap.cy) ;
	pdc->SelectObject(pOldPen) ;
	pdc->SelectObject(pOldBrush) ;
}


//
//
//
void CSceneView::DrawCaption(CDC* pdc, LPCTSTR str)
{
	int iOldMode = pdc->SetBkMode(TRANSPARENT) ;
	CFont* pOldFont = (CFont*)pdc->SelectObject(&m_font) ;
	// Caption for System Palette.
	pdc->TextOut(	m_iFontWidth,
				 	(int) (m_sizeBitmap.cy - (double)m_iFontHeight*1.5),	
					str, 
					_tcsclen(str)) ;

	pdc->SelectObject(pOldFont) ;
	pdc->SetBkMode(iOldMode) ;
}

/////////////////////////////////////////////////////////////////////////////
// CGLEasyView OnIdle rotation support
//
void CSceneView::Rotate(BOOL bRotate)
{
	m_bRotate = bRotate ;
 	// Stop idle loop mode
 	CEasyBitApp* pApp = (CEasyBitApp*) AfxGetApp();
 	pApp->SetIdleEvent(m_bRotate ? this : NULL);
}

void CSceneView::Tick()
{
	m_aScene.Rotate() ;
	Invalidate(FALSE) ;
	UpdateWindow() ;
}

void CSceneView::OnRotateStart() 
{
	Rotate(TRUE) ;
}

void CSceneView::OnUpdateRotateStart(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bRotate) ;
}

void CSceneView::OnRotateStop() 
{
	Rotate(FALSE) ;
	Invalidate(FALSE) ;
	UpdateWindow() ;

}

void CSceneView::OnUpdateRotateStop(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(!m_bRotate) ;
}

void CSceneView::OnRotateBox() 
{
	m_aScene.SetRotatingObject(CScene::Box) ;
	m_pMainFrame->m_wndStatusBar.SetBitmap(CScene::Box -1) ;
}

void CSceneView::OnUpdateRotateBox(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_aScene.GetRotatingObject() == CScene::Box) ;
	pCmdUI->Enable(!m_bRotate) ;
}

void CSceneView::OnRotateDodec() 
{
	m_aScene.SetRotatingObject(CScene::Dodec) ;
	m_pMainFrame->m_wndStatusBar.SetBitmap(CScene::Dodec -1) ;
}

void CSceneView::OnUpdateRotateDodec(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_aScene.GetRotatingObject() == CScene::Dodec) ;
	pCmdUI->Enable(!m_bRotate) ;
}

void CSceneView::OnRotatePyramid() 
{
	m_aScene.SetRotatingObject(CScene::Pyramid) ;
	m_pMainFrame->m_wndStatusBar.SetBitmap(CScene::Pyramid -1) ;
}


void CSceneView::OnUpdateRotatePyramid(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_aScene.GetRotatingObject() == CScene::Pyramid) ;
	pCmdUI->Enable(!m_bRotate) ;
}

/////////////////////////////////////////////////////////////////////////////
// Timing support
//

void CSceneView::OnTimingBlting() 
{
	if (m_bRotate) OnRotateStop() ;

	m_bTiming = TRUE ;

	CClientDC dc(this) ;
	CDC* pDC = &dc ;


	int x = 0 ;
	int y = 0;
	int i ;
	int iReps = 30 ;
	DWORD start;
	DWORD diff[5] ;

	timeBeginPeriod(1) ;
//
//	8 bpp CDIBSurface
//
    CPalette *ppalOld = NULL;
	CPalette* pPalScene = m_aScene.GetPalette() ;
    if(pPalScene) {
        ppalOld = pDC->SelectPalette(pPalScene, 0);
        pDC->RealizePalette();		
    }

	x = 0 ;
	y = 0 ;
	CDC* pdcSrc = m_aDIBSurface.GetDC() ;
	GdiFlush(); 
	start = timeGetTime() ;
		for (i = 0 ; i < iReps; i++)
		{
			pDC->BitBlt(x, 0, m_sizeBitmap.cx, m_sizeBitmap.cy, pdcSrc, 0, 0, SRCCOPY) ;
			x+=20 ;
		}
		GdiFlush() ;
	diff[0] = timeGetTime() - start ;

//
//	8 bpp DIB section using CSimpleDIB 
//
	x = 0 ;
	y = m_sizeBitmap.cy ;
	GdiFlush(); 
	start = timeGetTime() ;
		for (i = 0 ; i < iReps; i++)
		{
			m_theSimpleDIB[0].Draw(pDC, x, y) ;			
			x+=20 ;
		}
		GdiFlush() ;
	diff[1] = timeGetTime() - start ;

//
//	16 bpp DIB section using CSimpleDIB 
//
	x = 0 ;
	y += m_sizeBitmap.cy ;
	GdiFlush(); 
	start = timeGetTime() ;
		for (i = 0 ; i < iReps; i++)
		{
			m_theSimpleDIB[1].Draw(pDC, x, y) ;			
			x+=20 ;
		}
		GdiFlush() ;
	diff[2] = timeGetTime() - start ;

//
//	24 bpp DIB section using CSimpleDIB 
//
	x = 0 ;
	y += m_sizeBitmap.cy ;
	start = timeGetTime() ;
		for (i = 0 ; i < iReps; i++)
		{
			m_theSimpleDIB[2].Draw(pDC, x, y) ;			
			x+=20 ;
		}
		GdiFlush() ;
	diff[3] = timeGetTime() - start ;

//
// Do Identity palette timing test.
//
	diff[4] = TimeIdentity(iReps) ;	
//
// Cleanup
//
	timeEndPeriod(1) ;
    if (ppalOld) pDC->SelectPalette(ppalOld, 0);

//
// Display the results
//
	CString aString	;
	aString.Format("Timing Results\n\tCDIBSurface:\t\t\t%d\n\tCSimpleDIB(8 bpp):\t\t%d\n\tCSimpleDIB(16 bpp):\t\t%d\n\tCSimpleDIB(24 bpp):\t\t%d\n\tCDIBSurface(Identity):\t\t%d\n",
			diff[0],diff[1],diff[2],diff[3],diff[4]) ;

	AfxMessageBox(aString) ;

	m_bTiming = FALSE;

	Invalidate(FALSE) ;
	UpdateWindow() ;

}



DWORD CSceneView::TimeIdentity(int iReps) 
{
	CClientDC dc(this) ;
	CDC* pDC = &dc ;

	CDC* pdcTemp;
	CPalette* pPalTemp;

	//
	// Use Nigel's Animation Library CDIBSection and make an Identity palette
	//
	CDIBSurface aDIBSurfaceIdent ;
	aDIBSurfaceIdent.Create(m_sizeBitmap.cx, m_sizeBitmap.cy, (HPALETTE)NULL) ;
	pdcTemp = aDIBSurfaceIdent.GetDC() ;

	CSceneCI aSceneCI ;	// Use Color Index mode
	aSceneCI.Create(pdcTemp) ;

	pPalTemp = aSceneCI.GetPalette() ;
	if (pPalTemp)
	{
		aDIBSurfaceIdent.SetPalette(pPalTemp) ;
	}

   aSceneCI.Resize(m_sizeBitmap.cx, m_sizeBitmap.cy) ; //Doesn't resize?!!!!
   aSceneCI.Init() ;
   aSceneCI.Render() ;

   int iColors = 0;
   pPalTemp->GetObject(sizeof(iColors), &iColors) ;
   int iSysColors = pDC->GetDeviceCaps(NUMCOLORS);

   // allocate a log pal and fill it with the color table info
   LOGPALETTE *pPal = (LOGPALETTE *) malloc(sizeof(LOGPALETTE) + iColors * sizeof(PALETTEENTRY));
   PALETTEENTRY* pe = pPal->palPalEntry ;
   pPal->palVersion = 0x300; // Windows 3.0
   pPal->palNumEntries = (WORD) iColors; // table size
   pPalTemp->GetPaletteEntries(0,iColors, pe) ;
   int i ;
   for (i = 0; i < iSysColors/2; i++) {
     pe[i].peFlags = 0;
   }
   for (; i < iColors-iSysColors/2; i++) {
     pe[i].peFlags = PC_NOCOLLAPSE;
   }
   for (; i < iColors; i++) {
     pe[i].peFlags = 0;
   }

	CDIBPal aIdentPal ;
   BOOL bResult = aIdentPal.CreatePalette(pPal);
   free (pPal);
	ASSERT(bResult) ;

   aIdentPal.SetSysPalColors() ;

   CPalette *ppalOld = pDC->SelectPalette((CPalette*)&aIdentPal, 0);
   pDC->RealizePalette();		

	if (!IsIdentityPal(pDC)) MessageBeep(0) ;
	
	DWORD dwDiff,start ;
	if (iReps == 0)
	{
		
		aIdentPal.Draw(pDC,&CRect(100,0,400,300));
		dwDiff = 0 ;
	}
	else
	{
		int x = 0 ;
		int y = m_sizeBitmap.cy*3;
		CDC* pdcSrc = aDIBSurfaceIdent.GetDC();
		//aIdentPal.Draw(pDC,&CRect(100,0,400,300));
		GdiFlush(); 
		start = timeGetTime() ;
			for (i = 0 ; i < iReps ; i++)
			{
				pDC->BitBlt(x, y, m_sizeBitmap.cx, m_sizeBitmap.cy, pdcSrc, 0, 0, SRCCOPY) ;
				x += 20 ;
			}
			GdiFlush() ;
		dwDiff = timeGetTime() - start ;
	}
    if (ppalOld) pDC->SelectPalette(ppalOld, 0);

	return dwDiff ;
}
			

//
//
//

BOOL CSceneView::IsIdentityPal(CDC* pDC)
{
   int iColors = 0 ;
   PALETTEENTRY peCurrent[256];
   PALETTEENTRY peSystem[256] ;

	// Current Palette
   CPalette* pCurrentPal = pDC->GetCurrentPalette() ;
   pCurrentPal->GetObject(sizeof(iColors), &iColors);
   ASSERT(iColors > 0);
   pCurrentPal->GetPaletteEntries(0, iColors, peCurrent);

	// System Palette
   int iPalEntries = pDC->GetDeviceCaps(SIZEPALETTE);
   ::GetSystemPaletteEntries( pDC->GetSafeHdc(), 
                               0,
                               iPalEntries,
                               peSystem);


    // Build a table of RGBQUADS
	int iNum = min(iColors, iPalEntries) ;
   for (int i = 0; i < iColors; i++) {
      if (peCurrent[i].peRed != peSystem[i].peRed) return FALSE ;
      if (peCurrent[i].peGreen != peSystem[i].peGreen) return FALSE ;
      if (peCurrent[i].peBlue != peSystem[i].peBlue) return FALSE ;
   }
    
	return TRUE ;			
}									  

void CSceneView::OnPaletteChanged(CWnd* pFocusWnd) 
{
	if (m_bTiming) return ;
	/* ## CView */  CGLView::OnPaletteChanged(pFocusWnd);
		
}

BOOL CSceneView::OnQueryNewPalette() 
{
	if (m_bTiming) 
		return TRUE ;
	else
		return /* ## CView */  CGLView::OnQueryNewPalette();
}


//
// CopyPalette -
//
CPalette* CSceneView::CopyPalette(CPalette* pPalOrg)
{
	ASSERT(pPalOrg != NULL) ;
#if _DEBUG
	pPalOrg->AssertValid() ;
#endif
	int iNumColors ; 
	pPalOrg->GetObject(sizeof(iNumColors), &iNumColors) ;
	LOGPALETTE* pLogPal = (LOGPALETTE*)malloc(sizeof(LOGPALETTE) + (iNumColors-1)*sizeof(PALETTEENTRY)) ;
	ASSERT(pLogPal != NULL) ;
	pLogPal->palVersion = 0x300 ;
	pLogPal->palNumEntries = iNumColors ;

	pPalOrg->GetPaletteEntries(0, iNumColors, pLogPal->palPalEntry) ;
	
	CPalette* pPalNew = new CPalette ;
	ASSERT(pPalNew != NULL) ;
	pPalNew->CreatePalette(pLogPal) ;

	return pPalNew ;
}
