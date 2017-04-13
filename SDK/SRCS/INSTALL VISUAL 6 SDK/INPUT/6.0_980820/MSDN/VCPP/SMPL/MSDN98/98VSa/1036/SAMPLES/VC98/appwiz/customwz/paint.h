// paint.h: declare helper functions used when drawing bitmaps on the dialogs
//
// Copyright (c) 1985-1998, Microsoft Corporation. All rights reserved.
//

void PaintBackground(CPaintDC* pdc, CDialog* pDlg);
void PaintBitmap(UINT nBmp, int x, int y, int nWidth, int nHeight,
	CPaintDC* pdc, CDC* pdcMem);
