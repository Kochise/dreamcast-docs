// glpalvw.cpp : implementation of the CGLpalView class
//

#include "stdafx.h"
#include "glpal.h"

#include "glpaldoc.h"
#include "glpalvw.h"
#include "paldlg.h"
#include <math.h> //for pow function
#include <stdio.h> //sprintf
#include <string.h> //strlen


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGLpalView

IMPLEMENT_DYNCREATE(CGLpalView, CView)

BEGIN_MESSAGE_MAP(CGLpalView, CView)
	//{{AFX_MSG_MAP(CGLpalView)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_OPTIONS_DITHER, OnOptionsDither)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_DITHER, OnUpdateOptionsDither)
	ON_COMMAND(ID_OPTIONS_PALETTE, OnOptionsPalette)
	ON_COMMAND(ID_OPTIONS_SELECTBEFOREWGLMAKECURRENT, OnOptionsSelectbeforewglmakecurrent)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_SELECTBEFOREWGLMAKECURRENT, OnUpdateOptionsSelectbeforewglmakecurrent)
	ON_COMMAND(ID_OPTIONS_TRACECOLOR, OnOptionsTracecolor)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_TRACECOLOR, OnUpdateOptionsTracecolor)
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGLpalView construction/destruction

CGLpalView::CGLpalView()
{
	m_pPal = NULL ;

	m_bDither 		= FALSE ;
	m_iWhichPal 	= PAL_332 ;
	m_bTraceColor 	= TRUE;
	m_bSysColor 	= TRUE ;
	m_bSelPalBeforeMakeCurrent = TRUE ;

	m_hrc = NULL;

	m_bCaptured = FALSE;

	m_iGamma = 10 ;
}

CGLpalView::~CGLpalView()
{
	if (m_pPal) delete m_pPal;
}

/////////////////////////////////////////////////////////////////////////////
// CGLpalView drawing

void CGLpalView::OnDraw(CDC* pDC)
{
	CGLpalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Get a DC to draw on and a CRect to draw in.
	CRect rc ;
	GetClientRect(&rc) ;
	int iWidth = rc.Width() ;
	int iHeight = rc.Height() ;

	// Select the palette into the OnDraw DC.
   	CPalette* ppalOld = NULL ;
	if (m_pPal)
	{
   		ppalOld = pDC->SelectPalette(m_pPal, 0);
   		pDC->RealizePalette();
	}
 
	// Paint the background.	
	CBrush br;
    br.CreateHatchBrush(HS_FDIAGONAL, RGB(128,128,128));
    pDC->FillRect(&rc, &br);	
	
	// Draw the palette using CDIBPal routine.
	CRect rect(0,0,iWidth/2, iHeight/2) ;
	DrawCaptions(pDC,&rect) ;

	// Draw the palette using OpenGL.
	rect.OffsetRect(iWidth/2, iHeight/2) ;
	DrawGlPalette(pDC,&rect) ;

	// Draw the system palette.
	rect.OffsetRect(-iWidth/2,0) ;
	DrawSysPalette(pDC,&rect) ;

    // Select old palette if we altered it.
    if (ppalOld) pDC->SelectPalette(ppalOld, 0);
}

/////////////////////////////////////////////////////////////////////////////
// Palette Drawing Functions
void CGLpalView::DrawGlPalette(CDC* pdc, CRect* pRect)
{
	int i, j, top, left, bottom, right;	
	const int iMaxColors = 256 ;
	PALETTEENTRY pal[iMaxColors] ;

	// Get the logical palette colors.
	m_pPal->GetPaletteEntries(0,iMaxColors,pal) ;
	int iColors = iMaxColors ;
	int iCurColor = 0 ;
  	
	// Setup OpenGL for 2-D drawing.
	glPushMatrix() ;
	glLoadIdentity() ;
	gluOrtho2D(pRect->left, pRect->right, pRect->bottom, pRect->top) ;
	glViewport (pRect->left, pRect->top, pRect->Width(), pRect->Height());
	glShadeModel(GL_FLAT) ;	// No shading so we can see what we are drawing.
    glDisable (GL_DEPTH_TEST);
    glDisable (GL_ALPHA_TEST);

	// Turn dithering on/off
	if (m_bDither)
    	glEnable (GL_DITHER);
	else
    	glDisable (GL_DITHER);

	// Draw a 16x16 grid of the palette colors. (Code stolen from Nigel.)		
    for (j=0, top= pRect->top; j<16 ; j++, top=bottom)
    {
        bottom = pRect->top + (j+1) * pRect->Height() / 16 + 1;
        for(i=0, left=pRect->left ; i<16; i++, left=right)
        {
            right = pRect->left + (i+1) * pRect->Width() / 16 + 1;

			// Set the current palette color for OpenGL.
			glColor3ub(	pal[iCurColor].peRed, 
						pal[iCurColor].peGreen, 
						pal[iCurColor].peBlue) ;

			// Set the current palette color for GDI.
			CBrush br ;
			br.CreateSolidBrush(PALETTERGB(	pal[iCurColor].peRed, 
											pal[iCurColor].peGreen, 
											pal[iCurColor].peBlue)) ;

			// Draw a solid rectangle using GDI.
            CBrush *brold = pdc->SelectObject(&br);           
            pdc->Rectangle(left-1, top-1, right, bottom);
			pdc->SelectObject(brold) ;

			// Draw a solid rectangle using OpenGL.
	    	glBegin (GL_POLYGON);
	        	glVertex2d ((left-1), 	(top-1));
	        	glVertex2d (right, 		(top-1));            
	        	glVertex2d (right, 		bottom);           
	        	glVertex2d ((left-1), 	bottom);            
	    	glEnd ();

			// Draw a black line around rectangle using OpenGL.	    	
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) ;
			glColor3ub(0,0,0) ;
	    	glBegin (GL_POLYGON);
	        	glVertex2d ((left-1), 	(top-1));
	        	glVertex2d (right, 		(top-1));            
	        	glVertex2d (right, 		bottom);           
	        	glVertex2d ((left-1), 	bottom);            
	    	glEnd ();		
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) ;

			// Put a black dot on the rectangles that are differ between OpenGL and GDI.
			if (m_bTraceColor)
			{
				glFlush() ;
				::GdiFlush() ;
				int xx = left + (right - left)/2 ;
				int yy = top + (bottom - top) /2 ;
				COLORREF crGDI = pdc->GetPixel(xx, yy) ;
				COLORREF crGL = pdc->GetPixel(xx, yy - pRect->top ) ;
				if ( crGDI != crGL)
				{
				 	/*
					TRACE("%d: GDI(%d,%d,%d) != GL(%d,%d,%d)\r\n",iCurColor,
						GetRValue(crGDI),GetGValue(crGDI),GetBValue(crGDI),
						GetRValue(crGL),GetGValue(crGL),GetBValue(crGL)) ;					
					*/					  

					CBrush br2 (PALETTEINDEX(0));
            		CBrush *brold2 = pdc->SelectObject(&br2); 
					pdc->Ellipse(xx-2,yy-2,xx+2,yy+2) ;
					pdc->Ellipse(xx-2,yy - pRect->top - 2,xx+2,yy - pRect->top +2) ;
					pdc->SelectObject(brold2) ;
				}
			}
	
            iCurColor++ ;
		}
	}	
	::GdiFlush() ;
	glFlush() ;
	glPopMatrix() ;
}

//
// DrawSysPalette
//
void CGLpalView::DrawSysPalette(CDC* pdc, CRect* pRect)
{
	// Draw the system palette in the bottom left hand corner.

	int i, j, top, left, bottom, right;	
	CPalette pal ;
   // Create a palette
    // allocate a log pal and fill it with the color table info
    LOGPALETTE *pPal = (LOGPALETTE *) malloc(sizeof(LOGPALETTE) 
                                 + 256 * sizeof(PALETTEENTRY));
    if (pPal) {
        pPal->palVersion = 0x300; // Windows 3.0
        pPal->palNumEntries = 256; // table size
        for (int i=0; i<256; i++) {
            pPal->palPalEntry[i].peRed = i;
            pPal->palPalEntry[i].peGreen = 0;
            pPal->palPalEntry[i].peBlue = 0;
            pPal->palPalEntry[i].peFlags = PC_EXPLICIT;
        }
        pal.CreatePalette(pPal);
        free (pPal);
    }

	// To see the system palette we need to play some games with
	// GDI. So, select the system palette into the background. This
	// way we will not get any palette messages.
	pdc->SelectPalette(&pal, TRUE);
    pdc->RealizePalette();

	int iCurColor = 0 ;    
    for (j=0, top= pRect->top; j<16 ; j++, top=bottom)
    {
        bottom = pRect->top + (j+1) * pRect->Height() / 16 + 1;
        for(i=0, left=pRect->left ; i<16; i++, left=right)
        {
            right = pRect->left + (i+1) * pRect->Width() / 16 + 1;

			CBrush br (PALETTEINDEX(iCurColor++));
            CBrush *brold = pdc->SelectObject(&br);           
            pdc->Rectangle(left-1, top-1, right, bottom);
			pdc->SelectObject(brold) ;
		}
	}
}

//
// DrawCaptions
//
void CGLpalView::DrawCaptions(CDC* pDC, CRect* pRect)
{
	//
	// Draw the captions for the three palette displays.
	//
	static char szSystem[] = "System" ;
	static char szOpenGL[] = "OpenGL" ;
	static char szGDI[] = "GDI" ;

	int iCaptionWidth ;
	CFont* pOldFont = (CFont*)pDC->SelectObject(&m_font) ;
	// Caption for System Palette.
	pDC->TextOut(pRect->left+m_iFontWidth*4, pRect->bottom - m_iFontHeight*2,	
			szSystem, sizeof(szSystem)-1) ;

	// Caption for OpenGL Palette.
	iCaptionWidth = m_iFontWidth * (sizeof(szOpenGL)+2) ;
	pDC->TextOut(pRect->right - iCaptionWidth, pRect->top+5, 
				szOpenGL,sizeof(szOpenGL)-1) ;

	// Caption for GDI Palette.
	iCaptionWidth = m_iFontWidth * (sizeof(szGDI)+2) ;
	pDC->TextOut(pRect->right - iCaptionWidth, pRect->bottom - m_iFontHeight*2,
		 		szGDI,sizeof(szGDI)-1) ;

	if (pOldFont) pDC->SelectObject(pOldFont) ;
}

/////////////////////////////////////////////////////////////////////////////
// OpenGL Helper Functions

//
// SetDCPixelFormat
//
void CGLpalView::SetDCPixelFormat (HDC hdc) //OPENGL
{
	//
	// Set the Pixel format.
	//
	int dc = ::GetDeviceCaps(hdc, RASTERCAPS);
	if (!(RC_PALETTE & dc))
		AfxMessageBox("This program is designed for palettized devices. Run in 8 bpp mode or see black and red!") ;
	
    PIXELFORMATDESCRIPTOR pfd ;
	memset(&pfd,0, sizeof(PIXELFORMATDESCRIPTOR)) ;

    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);     // Size of this structure
    pfd.nVersion = 1 ;                               // Version number
	pfd.dwFlags = PFD_SUPPORT_GDI| PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW ;  
	pfd.iPixelType = PFD_TYPE_RGBA ;
    pfd.cColorBits = 24;                             // 24-bit color
	pfd.cDepthBits = 32 ;							// 32-bit depth buffer
    pfd.iLayerType = PFD_MAIN_PLANE ;               // Layer type

    int nPixelFormat = ChoosePixelFormat (hdc, &pfd);
	if (nPixelFormat == 0)
	{
		TRACE("ChoosePixelFormat Failed %d\r\n",GetLastError()) ;
	}
	TRACE("Pixel Format %d\r\n",nPixelFormat) ;

    BOOL bResult = SetPixelFormat (hdc, nPixelFormat, &pfd);
	if (!bResult)
	{
		TRACE("SetPixelFormat Failed %d\r\n",GetLastError()) ;
	}

}
//
// RestartOpenGL
//
void CGLpalView::RestartOpenGL(int cx, int cy)
{			
	if ( cx== -1 && cy== -1)
	{
		CRect rc ;
		GetClientRect(&rc) ;
		cx = rc.Width() ;
		cy = rc.Height() ;			
	}

	if (m_hrc)
	{
		//Cleanup.
		wglMakeCurrent(NULL,NULL) ;
		wglDeleteContext(m_hrc) ;
		m_hrc = NULL ;
	}

	//
	// Setup pixel format.
	//
	CDC* pdc = GetDC() ;   
    SetDCPixelFormat (pdc->m_hDC); 

	//
	// Create the Palette
	//
 	CreatePalette(pdc->m_hDC) ;

	//
	// Create the context
	//	
    m_hrc = wglCreateContext (pdc->m_hDC);
	if (!m_hrc)
	{
		TRACE("wglCreateContext Failed %x\r\n", GetLastError()) ;
		return /*FALSE*/ ;
	}

	//
	// Select the palette.  	
	//
   	CPalette *ppalOld = NULL;
	if (m_pPal && m_bSelPalBeforeMakeCurrent)
	{
    	ppalOld = pdc->SelectPalette(m_pPal, TRUE);
    	pdc->RealizePalette();
	}

	//
	// Make the rendering context current.
	//
	BOOL bResult = wglMakeCurrent (pdc->m_hDC, m_hrc); 
	if (!bResult)
	{
		TRACE("wglMakeCurrent Failed %x\r\n", GetLastError() ) ;
	}

    // select old palette if we altered it
    if (ppalOld) pdc->SelectPalette(ppalOld, 0); 
}

/////////////////////////////////////////////////////////////////////////////
// Palette Creation Functions

//
// OpenGL 332 palette
//
unsigned char CGLpalView::m_threeto8[8] = {
    0, 0111>>1, 0222>>1, 0333>>1, 0444>>1, 0555>>1, 0666>>1, 0377
};

unsigned char CGLpalView::m_twoto8[4] = {
   0, 0x55, 0xaa, 0xff
};

unsigned char CGLpalView::m_oneto8[2] = {
    0, 255
};

int CGLpalView::m_defaultOverride[13] = {
    0, 3, 24, 27, 64, 67, 88, 173, 181, 236, 247, 164, 91
};

  PALETTEENTRY CGLpalView::m_defaultPalEntry[20] = {
    { 0,   0,   0,    0 }, //0
    { 0x80,0,   0,    0 }, 
    { 0,   0x80,0,    0 }, 
    { 0x80,0x80,0,    0 }, 
    { 0,   0,   0x80, 0 },
    { 0x80,0,   0x80, 0 },
    { 0,   0x80,0x80, 0 },
    { 0xC0,0xC0,0xC0, 0 }, //7

    { 192, 220, 192,  0 }, //8
    { 166, 202, 240,  0 },
    { 255, 251, 240,  0 },
    { 160, 160, 164,  0 }, //11

    { 0x80,0x80,0x80, 0 }, //12
    { 0xFF,0,   0,    0 },
    { 0,   0xFF,0,    0 },
    { 0xFF,0xFF,0,    0 },
    { 0,   0,   0xFF, 0 },
    { 0xFF,0,   0xFF, 0 },
    { 0,   0xFF,0xFF, 0 },
    { 0xFF,0xFF,0xFF, 0 }  //19
  };

//
// ComponentFromIndex
//
unsigned char CGLpalView::ComponentFromIndex(int i, UINT nbits, UINT shift)
{
    unsigned char val = (unsigned char) (i >> shift);

    switch (nbits) {
    case 1:
        val &= 0x1;
        return m_oneto8[val];
		break ;
    case 2:
        val &= 0x3;
        return m_twoto8gamma[val];
		break ;
    case 3:
        val &= 0x7;
        return m_threeto8gamma[val];
		break ;
    default:
        return 0;
    }

}

//
// GammaCorrect
//
void CGLpalView::GammaCorrect()
{
	if (m_iGamma == 10)
	{
		// No Gamma correction needed. Optomize
		int i ;
		for( i = 0 ; i < 8 ; i++)
		{
			m_threeto8gamma[i] = m_threeto8[i] ;
		}

		for(i = 0 ; i < 4 ; i++) 
		{
			m_twoto8gamma[i] = m_twoto8[i];
		}
	}
	else
	{
		// Gamma Correct. 
	    int i;
    	unsigned char v, nv;
    	double dv;
		double gamma = (double)m_iGamma/10.0 ;

    	for (i=0; i<8; i++)
    	{
        	v = m_threeto8[i];
        	dv = (255.0 * pow(v/255.0, 1.0/gamma)) + 0.5;
    		nv = (unsigned char)dv;
        	m_threeto8gamma[i] = nv;
    	}

    	for (i=0; i<4; i++)
    	{
        	v = m_twoto8[i];
        	dv = (255.0 * pow(v/255.0, 1.0/gamma)) + 0.5;
    		nv = (unsigned char)dv;
        	m_twoto8gamma[i] = nv;
    	}
	}
}

//
// Fill332Palette
//
void CGLpalView::Fill332Palette(HDC hDC, LOGPALETTE* pPal)
{
	PIXELFORMATDESCRIPTOR pfd;
    int n = GetPixelFormat(hDC);
    DescribePixelFormat(hDC, n, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

    if (pfd.dwFlags & PFD_NEED_PALETTE)
    {
        n = 1 << pfd.cColorBits;
        for (int i=0; i<n; i++)
        {
            pPal->palPalEntry[i].peRed =
                    ComponentFromIndex(i, pfd.cRedBits, pfd.cRedShift);
            pPal->palPalEntry[i].peGreen =
                    ComponentFromIndex(i, pfd.cGreenBits, pfd.cGreenShift);
            pPal->palPalEntry[i].peBlue =
                    ComponentFromIndex(i, pfd.cBlueBits, pfd.cBlueShift);
            pPal->palPalEntry[i].peFlags = 0;
        }

		if (m_bSysColor)
		{
       		for (int j = 1 ; j <= 12 ; j++)
              	pPal->palPalEntry[m_defaultOverride[j]] = m_defaultPalEntry[j];
		}
  
  	}	
}

//
// FillWashPalette
//
void CGLpalView::FillWashPalette(HDC hDC, LOGPALETTE* pPal)
{
	// Blame this code on Nigel. I stoled it from him. :-)

    // Get the system colors in the first and last 10 slots
    ::GetSystemPaletteEntries(hDC, 0, 10, &pPal->palPalEntry[0]);
    ::GetSystemPaletteEntries(hDC, 246, 10, &pPal->palPalEntry[246]);
    // Create a color cube 6x6x6
    PALETTEENTRY* ppe = &pPal->palPalEntry[10];
    for (int r = 0; r < 6; r++){
        for (int g = 0; g < 6; g++) {
            for (int b = 0; b < 6; b++) {
                ppe->peRed = r * 255 / 6;
                ppe->peGreen = g * 255 / 6;
                ppe->peBlue = b * 255 / 6;
                ppe->peFlags = PC_NOCOLLAPSE;
                ppe++;
            }
        }
    }
    // Create a grey scale
    for (int i = 0; i < 20; i++)
    {
        ppe->peRed = i * 255 / 20;
        ppe->peGreen = i * 255 / 20;
        ppe->peBlue = i * 255 / 20;
        ppe->peFlags = PC_NOCOLLAPSE;
        ppe++;
    }

}

//
// CreatePalette
//
BOOL CGLpalView::CreatePalette(HDC hDC)
{
    // allocate a log pal and fill it with the color table info
    LOGPALETTE* pPal = (LOGPALETTE*) malloc(sizeof(LOGPALETTE) 
                     + 256 * sizeof(PALETTEENTRY));
    if (!pPal) {
        TRACE("Out of memory for logpal");
        return FALSE;
    }
    pPal->palVersion = 0x300; // Windows 3.0
    pPal->palNumEntries = 256; // table size

	//
	// Fill 3-3-3 Palette
	//
	if (m_iWhichPal == PAL_332)
	{
		GammaCorrect() ;
		Fill332Palette(hDC, pPal) ;
	}
	else
		FillWashPalette(hDC, pPal) ; 

	if (m_pPal) delete m_pPal ;
	m_pPal = new CPalette;

    BOOL bResult = m_pPal->CreatePalette(pPal);
    free (pPal);

    return bResult;
}


/////////////////////////////////////////////////////////////////////////////
// CGLpalView message handlers

BOOL CGLpalView::PreCreateWindow(CREATESTRUCT& cs) 
{
  	cs.style = cs.style | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;	
	return CView::PreCreateWindow(cs);
}

void CGLpalView::OnSize(UINT nType, int cx, int cy) 
{
	TRACE0("OnSize\r\n") ;
	CView::OnSize(nType, cx, cy);
	
	if ( (cx <= 0) || (cy <= 0) ) return ;
	RestartOpenGL( cx, cy) ;		
}

void CGLpalView::OnInitialUpdate() 
{
	// Create and get metrics for our font.
	m_font.CreateStockObject(ANSI_FIXED_FONT); 

	CDC dc ;
	dc.CreateCompatibleDC(NULL) ;
	CFont* pOldFont = (CFont*)dc.SelectObject(&m_font) ;
	TEXTMETRIC tm ;
	dc.GetTextMetrics(&tm) ;
	if (pOldFont) dc.SelectObject(pOldFont) ;
	m_iFontHeight = tm.tmHeight ;
	m_iFontWidth = tm.tmMaxCharWidth ;
	
	CView::OnInitialUpdate();
}

BOOL CGLpalView::OnEraseBkgnd(CDC* pDC) 
{	
	//return CView::OnEraseBkgnd(pDC);
	return TRUE ;
}

void CGLpalView::OnDestroy() 
{
	TRACE0("OnDestroy\r\n") ;	
	wglMakeCurrent(NULL,NULL) ; 
	if (m_hrc) 
	{
		wglDeleteContext(m_hrc) ;
		m_hrc = NULL ;
	}

	CView::OnDestroy();			
}

void CGLpalView::OnLButtonDown(UINT nFlags, CPoint point) 
{		
	//
	// Show RGB value of point where mouse is.
	//
	//CView::OnLButtonDown(nFlags, point);
    SetCapture();
    m_bCaptured = TRUE;
    ShowRGB(point);
}

void CGLpalView::OnMouseMove(UINT nFlags, CPoint point) 
{
	//
	// Track RGB value of point where mouse is.
	//
	//CView::OnMouseMove(nFlags, point);
    if (m_bCaptured) {
        ShowRGB(point);
    }
}

void CGLpalView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	//
	// Track RGB value of point where mouse is.
	//
	//CView::OnLButtonUp(nFlags, point);
    if (m_bCaptured) {
       ReleaseCapture();
       m_bCaptured = FALSE;
       SetWindowText("TSurf"); // Restore title.
    }
}

void CGLpalView::ShowRGB(CPoint point)
{
	//
	// Display RGB value of point where mouse is.
	//
    CPoint pt(point) ;
	CClientDC dc(this) ;
	// Get the RGB value of the pixel.
    COLORREF rgb = dc.GetPixel(pt.x, pt.y);

    char buf[64];
    sprintf(buf, "RGB(%4d,%4d,%4d)",
            GetRValue(rgb),
            GetGValue(rgb),
            GetBValue(rgb));

	CFont* pOldFont = (CFont*)dc.SelectObject(&m_font) ;
	// Display the RGB value.
	dc.TextOut(m_iFontWidth,m_iFontHeight, buf, strlen(buf)) ;

	CRect rcClient ;
	GetClientRect(&rcClient) ;
	int iWidth = rcClient.Width() / 2 ;
	int iHeight = rcClient.Height() / 2 ;
	double iBlkWidth = (iWidth /16.0) ;
	double iBlkHeight = (iHeight / 16.0) ;
	CRect rcUpLeft(0,0,iWidth, iHeight) ;
	CRect rcUpRight(rcUpLeft) ; 
	CRect rcBotLeft(rcUpLeft); 
	CRect rcBotRight(rcUpLeft);
	rcBotLeft.OffsetRect(0,iHeight) ;
	rcUpRight.OffsetRect(iWidth,0) ;
	rcBotRight.OffsetRect(iWidth,iHeight) ;

	if ( rcUpLeft.PtInRect(point) )
	{
		sprintf(buf,"Index: ----") ;
	}
	else
	{
		CPoint ptTopLeft ;
	 	if (rcUpRight.PtInRect(point)) 
	 		ptTopLeft = rcUpRight.TopLeft() ;
		else if (rcBotRight.PtInRect(point)) 
	 		ptTopLeft = rcBotRight.TopLeft() ;
		else if (rcBotLeft.PtInRect(point)) 
	 		ptTopLeft = rcBotLeft.TopLeft() ;

		point -= (CSize)ptTopLeft ;
		int index = (int)((double)point.y / iBlkHeight)*16 +
					(int)((double)point.x / iBlkWidth ) ;
		sprintf(buf,"Index: %4d",index) ;	
	}
	dc.TextOut(m_iFontWidth,m_iFontHeight*2, buf, strlen(buf)) ;
	if (pOldFont) dc.SelectObject(pOldFont) ;
}


void CGLpalView::OnOptionsPalette() 
{
	CPaletteDlg aDlg(this) ;

	aDlg.m_bSysColor = m_bSysColor ;
	aDlg.m_iGamma = m_iGamma ;
	aDlg.m_b332 = (m_iWhichPal == PAL_332) ? TRUE : FALSE ;

	int iResult = aDlg.DoModal() ;
	if (iResult == IDOK)
	{
		m_bSysColor = aDlg.m_bSysColor ;
		m_iWhichPal = (aDlg.m_b332) ? PAL_332 : PAL_WASH ;
		m_iGamma = aDlg.m_iGamma ;
		RestartOpenGL() ;
		GetDocument()->UpdateAllViews(NULL) ;	
		UpdateWindow() ;	
	}
}

void CGLpalView::OnOptionsDither() 
{
	m_bDither = !m_bDither ;
	GetDocument()->UpdateAllViews(NULL) ;
	UpdateWindow() ;
}

void CGLpalView::OnUpdateOptionsDither(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bDither) ;
}

void CGLpalView::OnOptionsSelectbeforewglmakecurrent() 
{
	m_bSelPalBeforeMakeCurrent = !m_bSelPalBeforeMakeCurrent ;
	RestartOpenGL() ;
	GetDocument()->UpdateAllViews(NULL) ;	
	UpdateWindow() ;	
}

void CGLpalView::OnUpdateOptionsSelectbeforewglmakecurrent(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bSelPalBeforeMakeCurrent) ;
}

void CGLpalView::OnOptionsTracecolor() 
{
	m_bTraceColor = !m_bTraceColor ;
	GetDocument()->UpdateAllViews(NULL) ;
	UpdateWindow() ;
}

void CGLpalView::OnUpdateOptionsTracecolor(CCmdUI* pCmdUI) 
{		
	pCmdUI->SetCheck(m_bTraceColor) ;
}


void CGLpalView::OnPaletteChanged(CWnd* pFocusWnd) 
{
	//CView::OnPaletteChanged(pFocusWnd);
	TRACE("OnPaletteChanged\r\n") ;
    // See if the change was caused by us and ignore it if not.
    if (pFocusWnd != this) {
        OnQueryNewPalette();
    }
}

BOOL CGLpalView::OnQueryNewPalette() 
{	
	//	return CView::OnQueryNewPalette();
	TRACE0("OnQueryNewPalette\r\n") ;
    // We are going active or the system palette has changed,
    // so realize our palette.
    if (m_pPal) {   	
        CDC* pDC = GetDC();
        CPalette* pOldPal = pDC->SelectPalette(m_pPal, FALSE);
        UINT u = pDC->RealizePalette();
        ReleaseDC(pDC);
       	if (u != 0) {
            // Some colors changed, so we need to do a repaint.
            InvalidateRect(NULL, TRUE); // Repaint the lot.
        }
    }
    return TRUE; // Windows ignores this.	
}


