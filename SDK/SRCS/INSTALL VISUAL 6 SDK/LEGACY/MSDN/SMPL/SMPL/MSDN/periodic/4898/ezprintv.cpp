//***********************************************************************
//
//  EZPrintView.cpp
//
//***********************************************************************

#include <afxwin.h>
#include <afxext.h>
#include "EZPrintView.h"

IMPLEMENT_DYNCREATE (CPrintView, CView)

BEGIN_MESSAGE_MAP (CPrintView, CView)
    ON_COMMAND (ID_FILE_PRINT, CView::OnFilePrint)
    ON_COMMAND (ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP ()

void CPrintView::OnDraw (CDC* pDC)
{
    CPen pen (PS_SOLID, 50, RGB (0, 0, 255));
    CBrush brush (RGB (255, 255, 0));

    pDC->SetMapMode (MM_LOMETRIC);
    CPen* pOldPen = pDC->SelectObject (&pen);
    CBrush* pOldBrush = pDC->SelectObject (&brush);

    pDC->Ellipse (100, -100, 1100, -1100);

    pDC->SelectObject (pOldBrush);
    pDC->SelectObject (pOldPen);
}

BOOL CPrintView::OnPreparePrinting (CPrintInfo* pInfo)
{
    pInfo->SetMaxPage (1);
    return DoPreparePrinting (pInfo);
}
