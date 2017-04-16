//////////////////////////////////////////////////////////////////////////////
// SketchPad.cpp	- Copyright (C) 1997 Microsoft Corporation				//
//					- All rights reserved.									//
// Date				- 12/11/97												//
// Purpose			- Sketch dialog	implementation							//
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CE.h"
#include "SketchPad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Draw in black and erase in white
#define PENDRAWCOLOR		RGB(0,0,0)
#define PENERASECOLOR		RGB(255,255,255)

#define WIDTHBYTES(bits) ((((bits) + 31) / 32) * 4)

// translate all colors to white except black
static RGBQUAD rgbStd256[256] =
{
	{  0,   0,   0, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},
	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0},	{255, 255, 255, 0}
};

	

// Constructor ///////////////////////////////////////////////////////////////
//																			//
// Purpose		- Initialize class members									//
//////////////////////////////////////////////////////////////////////////////
CSketchPad::CSketchPad(CWnd* pParent)
	: CDialog(CSketchPad::IDD, pParent)
{

	// Initialize sketch data to NULL
	m_lpData	= NULL;
	m_nDataSize = 0;

	m_bBitmapLoaded = FALSE;

	m_pDrawingPen = m_pErasingPen = NULL;
	m_lpbi = NULL;

	//{{AFX_DATA_INIT(CSketchPad)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

// Destructor ////////////////////////////////////////////////////////////////
//																			//
// Purpose		- Clean up													//
//////////////////////////////////////////////////////////////////////////////
CSketchPad::~CSketchPad()
{
	if(m_lpData)
		delete m_lpData;

	if(m_pDrawingPen)
		delete m_pDrawingPen;

	if(m_pErasingPen)
		delete m_pErasingPen;

	if(m_lpbi)
		delete m_lpbi;
}

void CSketchPad::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSketchPad)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSketchPad, CDialog)
	//{{AFX_MSG_MAP(CSketchPad)
	ON_WM_CLOSE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP

	// Our handlers for the command bar buttons
	ON_COMMAND(ID_SAVEANDEXIT,	OnSave)
	ON_COMMAND(ID_PEN_INCREASE,	OnPenIncrease)
	ON_COMMAND(ID_PEN_DECREASE,	OnPenDecrease)
	ON_COMMAND(ID_DRAW,			OnDrawMode)
	ON_COMMAND(ID_ERASE,		OnEraseMode)
	ON_COMMAND(ID_CLEAR,		OnClear)
END_MESSAGE_MAP()


// Set up our command bar buttons

#define SEPARATOR 0

TBBUTTON Buttons[] =
{
	{0, SEPARATOR,			TBSTATE_ENABLED, TBSTYLE_SEP,		0, 0},

	{0,	ID_SAVEANDEXIT,		TBSTATE_ENABLED, TBSTYLE_BUTTON,	0, 0},
	{0, SEPARATOR,			TBSTATE_ENABLED, TBSTYLE_SEP,		0, 0},

	{1, ID_PEN_INCREASE,	TBSTATE_ENABLED, TBSTYLE_BUTTON,	0, 0},
	{2, ID_PEN_DECREASE,	TBSTATE_ENABLED, TBSTYLE_BUTTON,	0, 0},
	{0, SEPARATOR,			TBSTATE_ENABLED, TBSTYLE_SEP,		0, 0},

	{3, ID_DRAW,			TBSTATE_ENABLED | TBSTATE_CHECKED, TBSTYLE_BUTTON | TBSTYLE_CHECK,	0, 0},
	{4, ID_ERASE,			TBSTATE_ENABLED, TBSTYLE_BUTTON | TBSTYLE_CHECK,	0, 0},
	{0, SEPARATOR,			TBSTATE_ENABLED, TBSTYLE_SEP,		0, 0},

	{5, ID_CLEAR,			TBSTATE_ENABLED, TBSTYLE_BUTTON,	0, 0}
};


BOOL CSketchPad::OnInitDialog() 
{
	CRect	FrameRect;

	CDialog::OnInitDialog();
	
	// Create command bar
	m_CommandWnd = CommandBar_Create(AfxGetInstanceHandle(), this->m_hWnd, WM_USER + 25);
	if (m_CommandWnd == NULL)
	{
		MessageBox(_T("Error creating command bar!"), _T("OK"), MB_ICONEXCLAMATION);
		return TRUE;
	}

	// add bitmaps to command bar
	if (CommandBar_AddBitmap(m_CommandWnd, AfxGetInstanceHandle(), IDB_SAVE, 1, 0, 0) == -1 ||
		CommandBar_AddBitmap(m_CommandWnd, AfxGetInstanceHandle(), IDB_PEN_INCREASE, 1, 0, 0) == -1 ||
		CommandBar_AddBitmap(m_CommandWnd, AfxGetInstanceHandle(), IDB_PEN_DECREASE, 1, 0, 0) == -1 ||
		CommandBar_AddBitmap(m_CommandWnd, AfxGetInstanceHandle(), IDB_DRAW, 1, 0, 0) == -1 ||
		CommandBar_AddBitmap(m_CommandWnd, AfxGetInstanceHandle(), IDB_ERASE, 1, 0, 0) == -1 ||
		CommandBar_AddBitmap(m_CommandWnd, AfxGetInstanceHandle(), IDB_CLEAR, 1, 0, 0) == -1)
	{
		MessageBox(_T("Error adding bitmap to command bar!"), _T("OK"), MB_ICONEXCLAMATION);
		return TRUE;
	}

	// add buttons to command bar
	if (CommandBar_AddButtons(m_CommandWnd, sizeof(Buttons) / sizeof(TBBUTTON), Buttons) == FALSE)
	{
		MessageBox(_T("Error adding buttons to command bar!"), _T("OK"), MB_ICONEXCLAMATION);
		return TRUE;
	}

	// show the command bar
	CommandBar_Show(m_CommandWnd, TRUE);

	// initial pen size
	m_PenSize		= 1;

	// start in drawing mode
	m_bDrawing		= TRUE;

	// no changed data, so we're currently saved
	m_bSaved		= TRUE;

	// create drawing and erasing pens
	m_pDrawingPen = new CPen;
	m_pDrawingPen->CreatePen(PS_SOLID, m_PenSize, PENDRAWCOLOR);
	m_pErasingPen = new CPen;
	m_pErasingPen->CreatePen(PS_SOLID, m_PenSize, PENERASECOLOR);

	// set up bitmap header information
	GetClientRect(&FrameRect);
	ClientToScreen(&FrameRect);

	// Fill in the BITMAPINFOHEADER
	m_lpbi = (LPBITMAPINFO) new BYTE[sizeof(BITMAPINFOHEADER) + (256 * sizeof(RGBQUAD))];
	m_lpbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_lpbi->bmiHeader.biWidth = FrameRect.Width();
	m_lpbi->bmiHeader.biHeight = FrameRect.Height();
	m_lpbi->bmiHeader.biPlanes = 1;
	m_lpbi->bmiHeader.biBitCount = 1;
	m_lpbi->bmiHeader.biCompression = BI_RGB;
	m_lpbi->bmiHeader.biSizeImage = WIDTHBYTES((DWORD)FrameRect.Width() * 1) * FrameRect.Height();
	m_lpbi->bmiHeader.biXPelsPerMeter = 0;
	m_lpbi->bmiHeader.biYPelsPerMeter = 0;
	m_lpbi->bmiHeader.biClrUsed = 0;
	m_lpbi->bmiHeader.biClrImportant = 0;

	// Fill in the color table
	memcpy(m_lpbi->bmiColors, rgbStd256, sizeof(RGBQUAD) * 256 );

	// if we have data, then we need to load the sketch in OnPaint()
	if(m_nDataSize)
		m_bBitmapLoaded = TRUE;

	// our first time drawing we will clear the dialog
	m_bFirstDraw = TRUE;

	return TRUE;  
}

//////////////////////////////////////////////
// Here are our command bar handlers		//
//////////////////////////////////////////////


// OnSave ////////////////////////////////////////////////////////////////
//																		//
// Called when the 'Save' command bar button is pressed					//
// Save and Exit the sketch dialog										//
//////////////////////////////////////////////////////////////////////////
void CSketchPad::OnSave()
{
	// Save...
	SaveSketch();

	// ...and Exit
	OnOK();
}

// OnPenIncrease /////////////////////////////////////////////////////////
//																		//
// Called when the 'Increase pen size' button is pressed				//
// Increase the pen size												//
//////////////////////////////////////////////////////////////////////////
void CSketchPad::OnPenIncrease()
{
	m_PenSize++;
	if(m_PenSize > 15)
		m_PenSize = 15;

	// Re-create pens

	delete m_pDrawingPen;
	delete m_pErasingPen;

	m_pDrawingPen = new CPen;
	m_pDrawingPen->CreatePen(PS_SOLID, m_PenSize, PENDRAWCOLOR);
	m_pErasingPen = new CPen;
	m_pErasingPen->CreatePen(PS_SOLID, m_PenSize, PENERASECOLOR);
}

// OnPenDecrease /////////////////////////////////////////////////////////
//																		//
// Called when the 'Decrease pen size' button is pressed				//
// Decrease the pen size												//
//////////////////////////////////////////////////////////////////////////
void CSketchPad::OnPenDecrease()
{
	m_PenSize--;
	if(m_PenSize < 1)
		m_PenSize = 1;

	// Re-create pens

	delete m_pDrawingPen;
	delete m_pErasingPen;

	m_pDrawingPen = new CPen;
	m_pDrawingPen->CreatePen(PS_SOLID, m_PenSize, PENDRAWCOLOR);
	m_pErasingPen = new CPen;
	m_pErasingPen->CreatePen(PS_SOLID, m_PenSize, PENERASECOLOR);
}

// OnClear ///////////////////////////////////////////////////////////////
//																		//
// Called when the 'clear' button is pressed							//
// Clear the sketch														//
//////////////////////////////////////////////////////////////////////////
void CSketchPad::OnClear()
{
	CRect r;
	GetClientRect(&r);

	CDC* pDC = GetDC();
	pDC->FillSolidRect(&r, PENERASECOLOR);
	
	ReleaseDC(pDC);
}

// OnDrawMode ////////////////////////////////////////////////////////////
//																		//
// Called when the 'draw' button is pressed								//
// Sets the current pen to the drawing pen								//
//////////////////////////////////////////////////////////////////////////
void CSketchPad::OnDrawMode()
{
	m_bDrawing = TRUE;
	::SendMessage(m_CommandWnd, TB_CHECKBUTTON, ID_ERASE, 0);
	::SendMessage(m_CommandWnd, TB_CHECKBUTTON, ID_DRAW, 1);
}

// OnEraseMode ///////////////////////////////////////////////////////////
//																		//
// Called when the 'erase' button is pressed							//
// Sets the current pen to the erasing pen								//
//////////////////////////////////////////////////////////////////////////
void CSketchPad::OnEraseMode()
{
	m_bDrawing = FALSE;
	::SendMessage(m_CommandWnd, TB_CHECKBUTTON, ID_DRAW, 0);
	::SendMessage(m_CommandWnd, TB_CHECKBUTTON, ID_ERASE, 1);
}

// OnClose ///////////////////////////////////////////////////////////////
//																		//
// Called when the user tries to close the window						//
// Prompts for save if the sketch isn't saved							//
//////////////////////////////////////////////////////////////////////////
void CSketchPad::OnClose() 
{
	if (!m_bSaved)
	{
		SaveSketch();
		if(MessageBox(_T("Save Sketch?"), _T("OK"), MB_YESNO) == IDYES)
			OnOK();
		else
			OnCancel();

		return;
	}
	OnCancel();

	CDialog::OnClose();
}

// OnLButtonDown /////////////////////////////////////////////////////////
//																		//
// Called when the user initially presses the stylus to the screen		//
//////////////////////////////////////////////////////////////////////////
void CSketchPad::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// Set the first point of our line
	m_Line[0] = point;
	
	CDialog::OnLButtonDown(nFlags, point);
}

// OnMouseMove ///////////////////////////////////////////////////////////
//																		//
// Called when the user moves the stylus								//
//////////////////////////////////////////////////////////////////////////
void CSketchPad::OnMouseMove(UINT nFlags, CPoint point) 
{
	// Check that the LButton is down
	if (nFlags & MK_LBUTTON)
	{
		CDC* pDC = GetDC();
		m_Line[1] = point;

		// If they've moved...
		if (m_Line[0] != m_Line[1])
		{
			CPen * PreviousPen;

			// select our pen

			if (m_bDrawing)
				PreviousPen = pDC->SelectObject(m_pDrawingPen);
			else
				PreviousPen = pDC->SelectObject(m_pErasingPen);
			
			// draw the line
			pDC->Polyline(m_Line, 2);

			// select the original pen
			pDC->SelectObject(PreviousPen);

			// mark sketch as 'dirty'
			m_bSaved = FALSE;
		}
		// update the first point of our new line
		m_Line[0] = m_Line[1];
		ReleaseDC(pDC);
	}
	
	CDialog::OnMouseMove(nFlags, point);
}

// SaveSketch ////////////////////////////////////////////////////////////
//																		//
// Purpose		- To save the current sketch as a byte array			//
// Assumptions	- None													//
// Inputs		- None													//
// Outputs		- None													//
//////////////////////////////////////////////////////////////////////////
void CSketchPad::SaveSketch()
{
	CDC			*pDC,
				*pMemDC;

	HBITMAP		 hBitmap;
	CBitmap		*pBitmap;
	BOOL		 brc;
	LPBYTE		 pBitmapBuffer;

	pDC = GetDC();

	// create a compatible memory device context
	pMemDC = new CDC;
	pMemDC->CreateCompatibleDC(pDC);


	// create a bitmap from the client area
	hBitmap = ::CreateDIBSection(pMemDC->m_hDC, m_lpbi, DIB_RGB_COLORS, (void **)&pBitmapBuffer, NULL, 0);
	pBitmap = new CBitmap;
	pBitmap->Attach(hBitmap);

	// select bitmap into DC and bitblt screen into memory
	pMemDC->SelectObject(pBitmap);

	brc = pMemDC->BitBlt(0, 
						 0, 
						 m_lpbi->bmiHeader.biWidth,
						 m_lpbi->bmiHeader.biHeight, 
						 pDC, 
						 0, 
						 0, 
						 SRCCOPY);

	// save a copy of the data
	m_nDataSize = m_lpbi->bmiHeader.biSizeImage;
	m_lpData = new BYTE[m_nDataSize];
	memcpy(m_lpData, pBitmapBuffer, m_nDataSize);

	// release resources
	delete pBitmap;

	ReleaseDC(pMemDC);
	delete pMemDC;

	m_bSaved = TRUE;
}

// GetData ///////////////////////////////////////////////////////////////
//																		//
// Purpose		- To return the sketch data as a byte array				//
// Assumptions	- None													//
// Inputs		- None													//
// Outputs		- (LPBYTE) a pointer to a copy of the sketch data		//
//////////////////////////////////////////////////////////////////////////
LPBYTE CSketchPad::GetData()
{	
	// return a copy of the data
	if(!m_nDataSize)
		return NULL;

	LPBYTE lpData = new BYTE[m_nDataSize];
	memcpy(lpData, m_lpData, m_nDataSize);

	return lpData;
}

// GetDataSize ///////////////////////////////////////////////////////////
//																		//
// Purpose		- To return the size of the sketch array				//
// Outputs		- (long) length of sketch array							//
//////////////////////////////////////////////////////////////////////////
long CSketchPad::GetDataSize()
{
	return m_nDataSize;
}

// SetData ///////////////////////////////////////////////////////////////
//																		//
// Purpose		- To initialize the sketch before the dialog is shown	//
// Assumptions	- None													//
// Inputs		- (LPBYTE) lpData	- The byte array of sketch data		//
//				- (long)   nSize	- The length of the array			//
// Outputs		- None													//
//////////////////////////////////////////////////////////////////////////
void CSketchPad::SetData(LPBYTE lpData, long nSize)
{
	// store copy of data
	if(nSize)
	{
		m_lpData = new BYTE[nSize];
		m_nDataSize = nSize;
		memcpy(m_lpData, lpData, nSize);
	}
	else
	{
		m_lpData	= NULL;
		m_nDataSize	= 0;
	}
}

// LoadSketch ////////////////////////////////////////////////////////////
//																		//
// Purpose		- To load the current sketch data onto the display		//
// Assumptions	- The current sketch data is valid						//
// Inputs		- None													//
// Outputs		- None													//
//////////////////////////////////////////////////////////////////////////
void CSketchPad::LoadSketch()
{
	CDC			*pDC,
				*pMemDC;

	HBITMAP		 hBitmap;
	CBitmap		*pBitmap;
	BOOL		 brc;
	LPBYTE		 pBitmapBuffer;

	OnClear();

	pDC = GetDC();
	pMemDC = new CDC;
	pMemDC->CreateCompatibleDC(pDC);

	// create a bitmap from the client area
	hBitmap = ::CreateDIBSection(pMemDC->m_hDC, m_lpbi, DIB_RGB_COLORS, (void **)&pBitmapBuffer, NULL, 0);

	// copy stored data to buffer
	memcpy(pBitmapBuffer, m_lpData, m_nDataSize);

	// create a bitmap from the bitmap handle
	pBitmap = new CBitmap;
	pBitmap->Attach(hBitmap);

	// select bitmap into DC and bitblt screen into memory
	pMemDC->SelectObject(pBitmap);
	brc = pDC->BitBlt(0, 
					  0, 
					  m_lpbi->bmiHeader.biWidth,
					  m_lpbi->bmiHeader.biHeight,
					  pMemDC, 
					  0, 
					  0, 
					  SRCCOPY);

	// release resources
	delete pBitmap;

	ReleaseDC(pMemDC);
	delete pMemDC;

	m_bSaved = TRUE;
}

// OnPaint ///////////////////////////////////////////////////////////
//																	//
// Called by the framework to update the display					//
//////////////////////////////////////////////////////////////////////
void CSketchPad::OnPaint() 
{
	// If it's our first time drawing, clear the display
	if(m_bFirstDraw)
	{
		OnClear();
		m_bFirstDraw = FALSE;
	}

	// if there is sketch data passed in, load it
	if(m_bBitmapLoaded)
	{
		LoadSketch();
		m_bBitmapLoaded = FALSE;
	}
}

