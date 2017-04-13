// cstm1dlg.cpp : implementation file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "logowiz.h"
#include "cstm1dlg.h"
#include "logowaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// these are expected to be in the same order as the radio buttons corresponding to these choices
// they are also assumed to start at zero
#define RAD_UPLEFT  0       // logo goes in upper left corner
#define RAD_LOLEFT  1       // logo goes in lower left corner
#define RAD_LORIGHT 2       // logo goes in lower right corner
#define RAD_NOLOGO  3       // no logo
// other buttons
#define BT_PRESS_ME 4       // press me button (keep below radio button set)
#define BT_DLGPIC   5       // dialog box picture (keep at bottom of list: not part of radio button set)

// Size of dialog box bitmap
#define BMP_LEFT 16
#define BMP_TOP 16
#define BMP_WIDTH 195
#define BMP_HEIGHT 147

// Other values used for drawing around the dialog box bitmap
#define RIGHT_YELLOW (163 + BMP_LEFT)
#define BOTTOM_YELLOW_DLGU 197
#define RIGHT_GRAY_DLGU 125

/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg dialog


CCustom1Dlg::CCustom1Dlg()
	: CAppWizStepDlg(CCustom1Dlg::IDD)
{
	//{{AFX_DATA_INIT(CCustom1Dlg)
	m_nLogoSpot = -1;
	m_nPressMe = FALSE;
	//}}AFX_DATA_INIT
}


void CCustom1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustom1Dlg)
	DDX_Radio(pDX, IDC_LOGO_UL, m_nLogoSpot);
	DDX_Check(pDX, IDC_PRESS_ME, m_nPressMe);
	//}}AFX_DATA_MAP
}

// set appropriate entries in the dictionary
// Parameters:
//  bWriteSymbol - Boolean value determining whether we need to write (TRUE) or delete (FALSE)
//                  a dictionary value
//       strName - the dictionary value we're working with
void CCustom1Dlg::SetSymbol(BOOL bWriteSymbol, LPCTSTR strName)
{
	if (bWriteSymbol)
		logowizaw.m_Dictionary.SetAt(strName, CString("1"));
	else
		logowizaw.m_Dictionary.RemoveKey(strName);
}

// This is called whenever the user presses Next, Back, or Finish with this step
//  present.  Do all validation & data exchange from the dialog in this function.
BOOL CCustom1Dlg::OnDismiss()
{
	if (!UpdateData(TRUE))
		return FALSE;

	// set the template variables
	SetSymbol(m_nLogoSpot == RAD_UPLEFT, _T("LOGO_UPLEFT"));
	SetSymbol(m_nLogoSpot == RAD_LOLEFT, _T("LOGO_LOLEFT"));
	SetSymbol(m_nLogoSpot == RAD_LORIGHT, _T("LOGO_LORIGHT"));
	// don't need to set a symbol for LOGO_NONE
	SetSymbol(RAD_UPLEFT || RAD_LOLEFT || RAD_LORIGHT, _T("LOGO_YES"));
	SetSymbol(m_nPressMe == TRUE, _T("PRESS_ME_DIALOG"));

	return TRUE;    // return FALSE if the dialog shouldn't be dismissed
}


BEGIN_MESSAGE_MAP(CCustom1Dlg, CAppWizStepDlg)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_LOGO_UL, IDC_LOGO_NONE, OnLogoClicked)
	//{{AFX_MSG_MAP(CCustom1Dlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_PRESS_ME, OnPressMe)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg message handlers

// draw a logo on the AppWiz page in the right place.  will erase the old logo if one exists
//  Parameters:
//      nOldID - logo location to erase (if it exists)
//      nNewID - logo location to draw in now
void CCustom1Dlg::DrawLogo(int nOldID, int nNewID)
{
	CDC* pdc = GetDC();

	if (nNewID == nOldID && nOldID >= RAD_UPLEFT)       // redraw without erase if same spot
	{
		DrawBitmap(pdc, IDB_LOGO_SMALL, nNewID);
		return;
	}

	if (nOldID >= RAD_UPLEFT)   // there is an old ID present, so erase it
		EraseBitmap(pdc, nOldID);

	// draw the logo in the new spot
	DrawBitmap(pdc, IDB_LOGO_SMALL, nNewID);
}

// Determine the rectangle we need to draw the desired bitmap in
//  there are three kinds of bitmaps expected here:
//   1. the 'big' bitmap with the picture of the dialog box on it
//   2. the 'baby' bitmap that represents the logo that shifts around on the 'big' bitmap
//   3. the 'press me' bitmap that goes in the middle of the dialog box
void CCustom1Dlg::GetBitmapRect(int nLocID, LPRECT rect)
{
	if (nLocID == BT_DLGPIC)    // major bitmap
	{
		rect->left = BMP_LEFT;
		rect->top = BMP_TOP;
		rect->right = BMP_LEFT + BMP_WIDTH;
		rect->bottom = BMP_TOP + BMP_HEIGHT;
		return;
	}
	else if (nLocID == BT_PRESS_ME)     // looking for location of 'press me' bitmap
	{
		rect->left = BMP_LEFT - 10 + (BMP_WIDTH - m_nPressWidth)/2;
		rect->top = BMP_TOP + (BMP_HEIGHT - m_nPressHeight)/2;
		rect->right = rect->left + m_nPressWidth;
		rect->bottom = rect->top + m_nPressHeight;
		return;

	}
	else if (nLocID == RAD_NOLOGO)      // no baby bitmap needed
	{
		rect->top = rect->bottom = rect->left = rect->right = 0;
		return;
	}

	// figure out where to put the baby bitmap (small logo)
	if (nLocID == RAD_LOLEFT || nLocID == RAD_LORIGHT)
		rect->top = BMP_TOP + BMP_HEIGHT - 30;
	else
		rect->top = BMP_TOP + 25;
	if (nLocID == RAD_LOLEFT || nLocID == RAD_UPLEFT)
		rect->left = BMP_LEFT + 15;
	else
		rect->left = BMP_LEFT + BMP_WIDTH - 30;

	rect->right = rect->left + m_nLogoWidth;
	rect->bottom = rect->top + m_nLogoHeight;
}

// erase a bitmap.  do NOT call this from OnPaint.  doing so causes an infinite recursion
//  and crashes MSVC very nicely (not).  (MSVC will crash in this case only because the
//  program you are actually running is the IDE itself.  If you do this kind of stuff in
//  a different .exe, you will crash that .exe instead.)
void CCustom1Dlg::EraseBitmap(CDC* pdc, int nLocID)
{
	RECT rect;

	GetBitmapRect(nLocID, &rect);
	RedrawWindow(&rect, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
}

// draw a bitmap
//  Parameters:
//            pdc - device context to draw in
//      nBitmapID - which bitmap to draw
//         nLocID - where to draw it
void CCustom1Dlg::DrawBitmap(CDC* pdc, int nBitmapID, int nLocID)
{
	CDC dcMem;
	RECT rect;

	if (nLocID == RAD_NOLOGO)   // nothing to do
		return;

	if (!dcMem.CreateCompatibleDC(pdc))
		return;

	CBitmap picture;
	picture.LoadBitmap(nBitmapID);
	BITMAP bitmap;
	picture.GetObject(sizeof (BITMAP), &bitmap);

	GetBitmapRect(nLocID, &rect);

	CBitmap* pOldBitmap = dcMem.SelectObject(&picture);
	pdc->BitBlt(rect.left, rect.top, bitmap.bmWidth, bitmap.bmHeight, &dcMem, 0, 0, SRCCOPY);
	dcMem.SelectObject(pOldBitmap);
}

// user clicked one of the logo location radio buttons
void CCustom1Dlg::OnLogoClicked(UINT /* nCmdID */)
{
	int oldLogoSpot = m_nLogoSpot;

	UpdateData();
	DrawLogo(oldLogoSpot, m_nLogoSpot);
}

void CCustom1Dlg::OnPressMe()
{
	UpdateData();

	CPaintDC dc(this); // device context for painting

	// this erase forces a redraw of the 'press me' button area.
	//  if we don't do a RedrawWindow (such as is done in EraseBitmap()),
	//  the bitmap won't paint regardless of the value of m_nPressMe.
	//  by restricting the area that gets redrawn (erased first in this
	//  case), we avoid flicker.
	EraseBitmap(&dc, BT_PRESS_ME);
	if (m_nPressMe)
		DrawBitmap(&dc, IDB_PRESS_ME, BT_PRESS_ME);
}

BOOL CCustom1Dlg::OnInitDialog()
{
	CAppWizStepDlg::OnInitDialog();

	// pick up sizing information for the logo
	SetBitmapSize(IDB_LOGO_SMALL, &m_nLogoWidth, &m_nLogoHeight);

	// pick up sizing information for the 'press me' button
	SetBitmapSize(IDB_PRESS_ME, &m_nPressWidth, &m_nPressHeight);

	m_nLogoSpot = IDC_LOGO_LL - IDC_LOGO_UL;
	m_nPressMe = TRUE;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

// initialize the bitmap size for the specified bitmap ID
void CCustom1Dlg::SetBitmapSize(int nID, int* pwidth, int* pheight)
{
	CBitmap picture;
	picture.LoadBitmap(nID);
	BITMAP bitmap;
	picture.GetObject(sizeof (BITMAP), &bitmap);
	*pwidth = bitmap.bmWidth;
	*pheight = bitmap.bmHeight;
}

// returns which dialog box bitmap we need (with or without help button on it as appropriate)
int CCustom1Dlg::GetDlgBitmapID()
{
	if (logowizaw.m_Dictionary.Lookup(_T("HELP"), CString("1")))
		return IDB_DLGPIC_WHELP;
	else
		return IDB_DLGPIC_NOHLP;
}

void CCustom1Dlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CBitmap pattern;
	pattern.LoadBitmap(IDB_YELLOW_PATTERN);
	CBrush brush(&pattern);
	RECT rectBmp;
	GetBitmapRect(BT_DLGPIC, &rectBmp);
	CPen penBogus(PS_SOLID, 0, COLORREF(0));
	CPen* pOldPen = dc.SelectObject(&penBogus);  // Remember current pen.

	DrawBitmap(&dc, GetDlgBitmapID(), BT_DLGPIC);   // major bitmap (dialog box picture)
	DrawBitmap(&dc, IDB_LOGO_SMALL, m_nLogoSpot);   // baby bitmap (logo to go on above)
	if (m_nPressMe)
		DrawBitmap(&dc, IDB_PRESS_ME, BT_PRESS_ME); // 'press me' button

	// Since the other two bitmaps are contained entirely on the major bitmap, we only have
	//  to worry about the major one when we draw the background.  If all of the bitmaps
	//  were not contained in the same rectangle, we would have to worry about all of them
	//  when drawing the background.

	// Draw yellow ABOVE bitmap(s)
	RECT rect = {0, 0, 0, 0};
	rect.bottom = rectBmp.top;
	rect.right = RIGHT_YELLOW + 1;
	dc.DPtoLP(&rect);
	dc.FillRect(&rect, &brush);

	// draw yellow to LEFT of bitmap(s)
	rect.left = 0;
	rect.top = rectBmp.top;
	rect.right = rectBmp.left;
	rect.bottom = rectBmp.bottom;
	dc.DPtoLP(&rect);
	dc.FillRect(&rect, &brush);

	// Draw yellow BELOW bitmap(s)
	rect.left = 0;
	rect.top = 0;
	rect.right = 1;
	rect.bottom = BOTTOM_YELLOW_DLGU;
	MapDialogRect(&rect);
	rect.right = RIGHT_YELLOW + 1;
	rect.top = rectBmp.bottom;
	dc.DPtoLP(&rect);
	dc.FillRect(&rect, &brush);

	// Draw right border lines
	CPen penGray(PS_SOLID, 0, 0x00808080);
	dc.SelectObject(&penGray);
	dc.MoveTo(rect.right, 0);
	POINT point;
	point.x = rect.right;
	point.y = rectBmp.top;
	dc.DPtoLP(&point);
	dc.LineTo(point.x, point.y);
	point.x = rect.right;
	point.y = rectBmp.bottom;
	dc.DPtoLP(&point);
	dc.MoveTo(point.x, point.y);
	dc.LineTo(point.x, rect.bottom);

	CPen penWhite(PS_SOLID, 0, 0x00ffffff);
	dc.SelectObject(&penWhite);
	dc.MoveTo(rect.right+1, 0);
	point.x = rect.right+1;
	point.y = rectBmp.top;
	dc.DPtoLP(&point);
	dc.LineTo(point.x, point.y);
	point.x = rect.right+1;
	point.y = rectBmp.bottom;
	dc.DPtoLP(&point);
	dc.MoveTo(point.x, point.y);
	dc.LineTo(point.x, rect.bottom);

	// Restore original pen
	dc.SelectObject(pOldPen);
}
