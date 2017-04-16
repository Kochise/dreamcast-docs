// VCDravw.cpp : implementation of the CVCDrawView class
//

#include "stdafx.h"
#include "VCDraw.h"
#include <initguid.h>               // create GUIDs here
#include "..\include\drawingid.h"   // drawing GUIDs
#include "VCDradoc.h"
#include "VCDravw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVCDrawView

IMPLEMENT_DYNCREATE(CVCDrawView, CView)

BEGIN_MESSAGE_MAP(CVCDrawView, CView)
	//{{AFX_MSG_MAP(CVCDrawView)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVCDrawView construction/destruction

CVCDrawView::CVCDrawView()
{
}

CVCDrawView::~CVCDrawView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CVCDrawView drawing

void CVCDrawView::OnDraw(CDC* pDC)
{
	CVCDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    // Apply the palette
    m_iPalette.Apply((long)pDC->GetSafeHdc());

    // Draw the background
    pDC->TextOut(2, 2, "Bkgnd:", 6);
    m_iBkgnd.Draw((long)(pDC->GetSafeHdc()),
                         2, 20);

    // Draw the palette
    pDC->TextOut(350, 2, "Palette:", 8);
    m_iPalette.Draw((long)(pDC->GetSafeHdc()),
                        350, 20, 500, 170);


    // Draw the red ball
    pDC->TextOut(350, 180, "Sprite:", 7);
    m_iRedBall.Draw((long)(pDC->GetSafeHdc()),
                         350, 200);


    // Draw the buffer
    pDC->TextOut(2, 230, "Buffer:", 7);
    m_iBuffer.Draw((long)(pDC->GetSafeHdc()),
                          2, 250);


    // Done with palette
    m_iPalette.Remove((long)pDC->GetSafeHdc());

}

/////////////////////////////////////////////////////////////////////////////
// CVCDrawView printing

BOOL CVCDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVCDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVCDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CVCDrawView diagnostics

#ifdef _DEBUG
void CVCDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CVCDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVCDrawDoc* CVCDrawView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVCDrawDoc)));
	return (CVCDrawDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVCDrawView message handlers

void CVCDrawView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

    COleException oe;
    int w, h;

    // Create a drawing surface object for the background
    BOOL b = m_iBkgnd.CreateDispatch("Drawing.DrawingSurface", &oe);
    if (!b) goto _exit;

    // Load the image
    b = m_iBkgnd.LoadFile("dogbk1.bmp");
    if (!b) {
        AfxMessageBox("Failed to load dogbk1.bmp");
        goto _exit;
    }

    // Create a palette from the background image
    b = m_iPalette.CreateDispatch("Drawing.ColorPalette", &oe);
    if (!b) goto _exit;

    b = m_iPalette.CreateFromImage(m_iBkgnd.m_lpDispatch);
    if (b) {
        m_iPalette.MakeIdentity();
    } else {
        goto _exit;
    }

    // Map the image colors to the new palette
    b = m_iBkgnd.MapToPalette(m_iPalette.GetHPal());
    if (!b) goto _exit;

    // Create a drawing surface object for the red ball
    b = m_iRedBall.CreateDispatch("Drawing.DrawingSurface", &oe);
    if (!b) goto _exit;
    b = m_iRedBall.LoadFile("redball.bmp");
    if (!b) {
        AfxMessageBox("Failed to load redball.bmp");
        goto _exit;
    }

    // Map it to the palette
    m_iRedBall.MapToPalette(m_iPalette.GetHPal());

    // Set its initial position
    m_iRedBallX = 0;
    m_iRedBallY = 50;
    m_vy = 0;

    // Create the off-screen buffer
    b = m_iBuffer.CreateDispatch("Drawing.DrawingSurface", &oe);
    if (!b) goto _exit;
    w = m_iBkgnd.GetWidth();
    h = m_iBkgnd.GetHeight();
    b = m_iBuffer.CreateNew(w, h, m_iPalette.GetHPal());
    if (!b) goto _exit;

    // Start the update timer
    m_uiTimer = SetTimer(1, 50, NULL);

	// Prevent stupid save? messages
_exit:
	CVCDrawDoc* pDoc = GetDocument();
    pDoc->SetModifiedFlag(FALSE);
}

void CVCDrawView::OnDestroy() 
{
	CView::OnDestroy();
	
    // Finished with the palette now
    m_iPalette.ReleaseDispatch();

    // Finished with the ds objects now
    m_iBkgnd.ReleaseDispatch();
    m_iRedBall.ReleaseDispatch();
    m_iBuffer.ReleaseDispatch();
}

// Compose a new image in the off-screen buffer
void CVCDrawView::Render()
{
    // Copy the background image to the off-screen buffer
    m_iBkgnd.Draw(m_iBuffer.GetHDC(), 0, 0);

    // Draw the sprites in position
    m_iRedBall.CopyWithTransparency(m_iBuffer.m_lpDispatch,
                                    m_iRedBallX, m_iRedBallY);

}

// Copy the off-screen buffer to the screen
void CVCDrawView::Draw()
{
    CDC* pDC = GetDC();
    
    // Apply the palette
    m_iPalette.Apply((long)pDC->GetSafeHdc());

    // Draw the buffer
    m_iBuffer.Draw((long)(pDC->GetSafeHdc()),
                          2, 250);

    // Done with palette
    m_iPalette.Remove((long)pDC->GetSafeHdc());
}

// Update the animation
void CVCDrawView::OnTimer(UINT nIDEvent) 
{
	// move the ball
    m_iRedBallX += 5;
    if (m_iRedBallX > 320) m_iRedBallX = -20;
    m_vy += 1; // accn
    m_iRedBallY += m_vy;
	if (m_iRedBallY > 170) {
        m_vy = -m_vy;
        m_iRedBallY = 170;
    }

    // Build new image
    Render();

    // Show the changes
    Draw();
}
