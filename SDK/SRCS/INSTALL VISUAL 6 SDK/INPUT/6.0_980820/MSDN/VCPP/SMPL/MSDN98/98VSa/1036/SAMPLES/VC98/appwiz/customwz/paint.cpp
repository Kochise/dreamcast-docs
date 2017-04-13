// paint.cpp: helper functions used when drawing bitmaps on the dialogs
//
// Copyright (c) 1985-1998, Microsoft Corporation. All rights reserved.
//

#include "stdafx.h"
#include "customwz.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// Coordinates for yellow rectangle in dialog-box units
#define RIGHT_YELLOW_DLGU   124
#define BOTTOM_YELLOW_DLGU  197

// Draws a background of yellow on the left side of the dialog
void PaintBackground(CPaintDC* pdc, CDialog* pDlg)
{
	//  Get the yellow brush
	CBitmap pattern;
	pattern.LoadBitmap(IDB_YELLOW_PATTERN);
	CBrush brush(&pattern);

	// Draw the yellow background
	CRect rect(0, 0, RIGHT_YELLOW_DLGU+1, BOTTOM_YELLOW_DLGU+1);
	pDlg->MapDialogRect(&rect);
	pdc->DPtoLP(&rect);
	pdc->FillRect(&rect, &brush);
}

// Draw the specified bitmap at the specified location
void PaintBitmap(UINT nBmp, int x, int y, int nWidth, int nHeight,
	CPaintDC* pdc, CDC* pdcMem)
{
	CBitmap picture;

	// Load & select the bitmap into the device-context
	picture.LoadBitmap(nBmp);
	BITMAP bitmap;
	picture.GetObject(sizeof (BITMAP), &bitmap);
	CBitmap* pOldBitmap = pdcMem->SelectObject(&picture);

	ASSERT(nWidth == bitmap.bmWidth);
	ASSERT(nHeight == bitmap.bmHeight);

	// Draw the bitmap
	pdc->BitBlt(x, y, nWidth, nHeight, pdcMem, 0, 0, SRCCOPY);

	// Reselect the previous bitmap object
	pdcMem->SelectObject(pOldBitmap);
}
