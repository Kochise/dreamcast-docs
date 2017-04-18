 #include "stdafx.h"
 #include "CMyStatusBar.h"

//
// Constructor
//
CMyStatusBar::CMyStatusBar()
{
	m_iCurrentDIB = -1 ;

	m_pScenes[0] = NULL;
	m_pScenes[1] = NULL;
	m_pScenes[2] = NULL;

}

//
// Destructor
//
CMyStatusBar::~CMyStatusBar()
{
	if (m_pScenes[0]) delete m_pScenes[0] ;
	if (m_pScenes[1]) delete m_pScenes[1] ;
	if (m_pScenes[2]) delete m_pScenes[2] ;
}

//
// Set the index of the bitmap to display in the statusbar.
//
void CMyStatusBar::SetBitmap(int i)
{	
	// Set new index.
	m_iCurrentDIB = i ;

	// Invalidate pane on statusbar to generate a paint message.
	CRect rect ;
	GetItemRect(1, &rect) ; 	
	InvalidateRect(rect, FALSE) ;
}

void CMyStatusBar::Init()
{
	//
	// Make a new font.
	//
	CFont* pFont = GetFont();
	LOGFONT logFont ;
	pFont->GetObject(sizeof(LOGFONT),(void*)&logFont ) ;
	logFont.lfHeight *= 2 ;
	lstrcpy(logFont.lfFaceName, _T("Arial"));

	m_Font.CreateFontIndirect(&logFont) ; 
	SetFont(&m_Font, TRUE) ;

	//
	// Resize panes.
	//
	UINT nID[5], nStyle[5] ;
	int iWidth[5] ;	
	GetPaneInfo(0, nID[0], nStyle[0], iWidth[0]) ;
	GetPaneInfo(1, nID[1], nStyle[1], iWidth[1]) ;
	GetPaneInfo(2, nID[2], nStyle[2], iWidth[2]) ;
	GetPaneInfo(3, nID[3], nStyle[3], iWidth[3]) ;
	GetPaneInfo(4, nID[4], nStyle[4], iWidth[4]) ;
	iWidth[1] = iWidth[0] - (iWidth[2]+iWidth[3]+iWidth[4])*2;
	if (iWidth[1] < 0) iWidth[1] = iWidth[0]/4 ;
	SetPaneInfo(0, nID[0], SBPS_STRETCH, 0) ;
	SetPaneInfo(1, nID[1], nStyle[1], iWidth[1]) ;
	SetPaneInfo(2, nID[2], nStyle[2], iWidth[2]*2) ; // CAPS
	SetPaneInfo(3, nID[3], nStyle[3], iWidth[3]*2) ; // NUM 
	SetPaneInfo(4, nID[4], nStyle[4], iWidth[4]*2) ; // SRCL

	//
	// Recalc the layout of the panes in the statusbar.
	//
	GetParentFrame()->RecalcLayout() ;

	//
	// Build the bitmaps and render on them with OpenGL.
	//		
	m_iCurrentDIB = 0 ;
	CRect aRect ;
	GetItemRect(1, &aRect) ;

	m_pScenes[0] = new CSceneBox ;
	m_pScenes[1] = new CScenePyramid ;
	m_pScenes[2] = new CSceneDodec ;

	CClientDC dc(NULL) ;
	int iBitsPixel = dc.GetDeviceCaps(BITSPIXEL) ;	
	if (iBitsPixel == 16) iBitsPixel = 8 ;

	for(int i = 0 ; i < 3 ; i++)
	{
		// Create the DIBs.
		m_DIB[i].Create(aRect.Width(), aRect.Height(), iBitsPixel) ;
		CDC* pdcTemp = m_DIB[i].GetDC() ;

		// Create the OpenGL scene.
		m_pScenes[i]->Create(pdcTemp) ;

		// Get the palettes from the Scene and set the DIB to that palette.
		CPalette* pPalTemp = m_pScenes[i]->GetPalette() ;
		if (pPalTemp) m_DIB[i].SetPalette(pPalTemp) ;

		// Render the scene.
		m_pScenes[i]->Resize(aRect.Width(), aRect.Height()) ; //Doesn't resize the DIB!!!!
		m_pScenes[i]->Init() ;
		m_pScenes[i]->Render() ;
	}			
}

void CMyStatusBar::DoPaint(CDC* pDC)
{
	// Let CStatusBar paint the bar.
	CStatusBar::DoPaint(pDC) ;

	// Return if no currently selected DIB.
	if (m_iCurrentDIB == -1) return ;

	// Get bounding rectangle for the pane.
	CRect aRect ;
	GetItemRect(1, &aRect) ;

	// Select and realize the palette for the DIB.
	CPalette* pOldPal = NULL;
	CPalette* pPalTemp = m_pScenes[m_iCurrentDIB]->GetPalette() ;
	if (pPalTemp != NULL)
	{
		pOldPal = pDC->SelectPalette(pPalTemp, FALSE) ;
		pDC->RealizePalette() ;		
	}

	// Draw the DIB.	
	m_DIB[m_iCurrentDIB].Draw(pDC, aRect.left, aRect.top) ;

	// Select in the previous palette.
 	if (pOldPal != NULL) pDC->SelectPalette(pOldPal, FALSE) ;
}


// All done.
