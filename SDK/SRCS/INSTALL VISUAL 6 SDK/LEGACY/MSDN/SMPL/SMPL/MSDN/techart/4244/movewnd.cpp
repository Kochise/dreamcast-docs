// movewnd.cpp : implementation file
//

#include "stdafx.h"
#include "PicCube.h"
#include "GLlib.h"
#include "Scene.h"
#include "glwnd.h"
#include "savewnd.h"	   
#include "movewnd.h"

#include <stdlib.h>
#include <time.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMovingChildWnd

CMovingChildWnd::CMovingChildWnd()
{ 
	m_bInit = FALSE ;

   m_uiTimer = 0;

	m_wxSize = 0;
	m_wySize = 0;
	m_xTransInc = 2.0;
	m_yTransInc = 2.5;
	m_xSize = 0 ;
	m_ySize = 0 ;

}

CMovingChildWnd::~CMovingChildWnd()
{

}


BEGIN_MESSAGE_MAP(CMovingChildWnd, CSaveWnd)
	//{{AFX_MSG_MAP(CMovingChildWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Helpers
void CMovingChildWnd::MoveBuffer(int curX, int curY)
{
    m_wndMovingChild.SetWindowPos( 	&wndTopMost, 
    								curX, curY, 
    								0, 0, 
    								SWP_NOSIZE | SWP_NOCOPYBITS | SWP_NOZORDER |SWP_SHOWWINDOW | SWP_NOREDRAW);
}


BOOL CMovingChildWnd::ShowBuffer()
{
   static double xtrans = 0.0;
   static double ytrans = 0.0;
   static int lastXt = 0;
   static int lastYt = 0;
   static int bInited = FALSE;
   static int interBounce = 0;
   int bounce = FALSE;
   int xt, yt;

   if (!bInited)
   {
      bInited = TRUE;

      srand(clock() & 0xffff);
      rand();
      xtrans = ((double)rand() / (double)RAND_MAX) * (double)(m_xSize - m_wxSize);
      ytrans = ((double)rand() / (double)RAND_MAX) * (double)(m_ySize - m_wySize);
      lastXt = (int) xtrans;
      lastYt = (int) ytrans;
	}
// Move the window to its next position.

   xt = (int)xtrans;
   yt = (int)ytrans;

   MoveBuffer(xt, yt);
   m_wndMovingChild.Invalidate(FALSE) ;
   m_wndMovingChild.UpdateWindow() ;

// Compute the next window position.

   lastXt = xt;
   lastYt = yt;

   xtrans += m_xTransInc;
   ytrans += m_yTransInc;

   if ((xtrans + m_wxSize) > m_xSize) {
       xtrans = (double) (m_xSize - m_wxSize);
       m_xTransInc = -m_xTransInc;
       bounce = TRUE;
   } else if (xtrans < 0.0) {
       xtrans = 0.0;
       m_xTransInc = -m_xTransInc;
       bounce = TRUE;
   }

   if ((ytrans + m_wySize) > m_ySize) {
       ytrans = (double) (m_ySize - m_wySize);
       m_yTransInc = -m_yTransInc;
       bounce = TRUE;
   } else if (ytrans < 0.0) {
       ytrans = 0.0;
       m_yTransInc = -m_yTransInc;
       bounce = TRUE;
   }

   m_wndMovingChild.m_aScene.Rotate() ;

    interBounce++;

    if (bounce) {
		m_wndMovingChild.m_aScene.Bounce() ;
        if (interBounce < 10)
            bounce = FALSE;
        else
            interBounce = 0;
    }


   TRACE0("*****************ShowBuffer-END\r\n") ;

    return bounce;
}
/////////////////////////////////////////////////////////////////////////////
// CMovingChildWnd message handlers

int CMovingChildWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CClientDC dc(this);

	//
	// Calc sizes
	//
	m_xSize = dc.GetDeviceCaps(DESKTOPHORZRES);
	m_ySize = dc.GetDeviceCaps(DESKTOPVERTRES);

	UINT uSize = 100 ;
	double sizeScale = (double)uSize / 100.0f;
	double sizeFact = 0.25f + (0.25f * sizeScale);
	m_xTransInc = 2.0f + (4.0f * sizeScale);
	m_yTransInc = 2.0f + (4.5f * sizeScale);
	m_wxSize = m_wySize = (int)((double)m_ySize * sizeFact);

    // Create the child window
	BOOL bResult = m_wndMovingChild.Create(this, m_wxSize, m_wySize) ;
	
	ASSERT(bResult) ;

    m_uiTimer = SetTimer(1, 16, NULL);
		
	return bResult;
}

void CMovingChildWnd::OnDestroy() 
{
	//CSaveWnd::OnDestroy();	
	if (m_uiTimer) KillTimer(1);	
}

void CMovingChildWnd::OnTimer(UINT nIDEvent) 
{
	ShowBuffer() ;		
}

BOOL CMovingChildWnd::OnEraseBkgnd(CDC* pdc) 
{
   //
   // Paint background black
   //
   CBrush br(PALETTERGB(0, 0, 0));
   CRect rc ;
   pdc->GetClipBox(&rc) ;
   pdc->FillRect(&rc, &br);

	return TRUE ;
}



void CMovingChildWnd::OnPaletteChanged(CWnd* pFocusWnd) 
{
      //	CSaveWnd::OnPaletteChanged(pFocusWnd);
       m_wndMovingChild.SendMessage(WM_PALETTECHANGED,
                                    (WPARAM)(pFocusWnd->GetSafeHwnd()),
                                    (LPARAM)0);
}

BOOL CMovingChildWnd::OnQueryNewPalette() 
{

   //	return CSaveWnd::OnQueryNewPalette();
   return m_wndMovingChild.SendMessage(WM_QUERYNEWPALETTE,
                                       (WPARAM)0,
                          				   (LPARAM)0);

}


