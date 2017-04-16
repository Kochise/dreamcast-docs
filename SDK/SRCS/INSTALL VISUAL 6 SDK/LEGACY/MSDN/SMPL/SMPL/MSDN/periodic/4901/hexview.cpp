//***********************************************************************
//
//  HexView.cpp
//
//***********************************************************************

#include <afxwin.h>
#include <afxext.h>
#include "HexDoc.h"
#include "HexView.h"

#define PRINTMARGIN 2

IMPLEMENT_DYNCREATE (CHexView, CScrollView)

BEGIN_MESSAGE_MAP (CHexView, CScrollView)
    ON_WM_CREATE ()
    ON_COMMAND (ID_FILE_PRINT, CScrollView::OnFilePrint)
    ON_COMMAND (ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
    ON_COMMAND (ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP ()

int CHexView::OnCreate (LPCREATESTRUCT lpcs)
{
    if (CScrollView::OnCreate (lpcs) == -1)
        return -1;

    CClientDC dc (this);
    int nHeight = -((dc.GetDeviceCaps (LOGPIXELSY) * 10) / 72);

    m_screenFont.CreateFont (nHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0,
        DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Courier New");

    TEXTMETRIC tm;
    CFont* pOldFont = dc.SelectObject (&m_screenFont);
    dc.GetTextMetrics (&tm);
    m_cyScreen = tm.tmHeight + tm.tmExternalLeading;
    dc.SelectObject (pOldFont);
    return 0;
}

void CHexView::OnInitialUpdate ()
{
    UINT nDocLength = GetDocument ()->GetDocumentLength ();
    m_nLinesTotal = (nDocLength + 15) / 16;

    SetScrollSizes (MM_TEXT, CSize (0, m_nLinesTotal * m_cyScreen),
        CSize (0, m_cyScreen * 10), CSize (0, m_cyScreen));
    ScrollToPosition (CPoint (0, 0));

    CScrollView::OnInitialUpdate ();
}

void CHexView::OnDraw (CDC* pDC)
{
    if (m_nLinesTotal != 0) {
        CRect rect;
        pDC->GetClipBox (&rect);

        UINT nStart = rect.top / m_cyScreen;
        UINT nEnd = min (m_nLinesTotal - 1,
            (rect.bottom + m_cyScreen - 1) / m_cyScreen);

        CString string;
        CFont* pOldFont = pDC->SelectObject (&m_screenFont);

        for (UINT i=nStart; i<=nEnd; i++) {
            FormatLine (i, string);
            pDC->TextOut (2, (i * m_cyScreen) + 2, string);
        }
        pDC->SelectObject (pOldFont);
    }
}

BOOL CHexView::OnPreparePrinting (CPrintInfo* pInfo)
{
    return DoPreparePrinting (pInfo);
}

void CHexView::OnBeginPrinting (CDC* pDC, CPrintInfo* pInfo)
{
    int nHeight = -((pDC->GetDeviceCaps (LOGPIXELSY) * 10) / 72);

    m_printerFont.CreateFont (nHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0,
        DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Courier New");

    TEXTMETRIC tm;
    CFont* pOldFont = pDC->SelectObject (&m_printerFont);
    pDC->GetTextMetrics (&tm);
    m_cyPrinter = tm.tmHeight + tm.tmExternalLeading;
    CSize size = pDC->GetTextExtent ("---------1---------2---------" \
        "3---------4---------5---------6---------7---------8-", 81);
    pDC->SelectObject (pOldFont);

    m_nLinesPerPage = (pDC->GetDeviceCaps (VERTRES) -
        (m_cyPrinter * (3 + (2 * PRINTMARGIN)))) / m_cyPrinter;
    UINT nMaxPage = max (1, (m_nLinesTotal + (m_nLinesPerPage - 1)) /
        m_nLinesPerPage);
    pInfo->SetMaxPage (nMaxPage);

    m_cxOffset = (pDC->GetDeviceCaps (HORZRES) - size.cx) / 2;
    m_cxWidth = size.cx;
}

void CHexView::OnPrint (CDC* pDC, CPrintInfo* pInfo)
{
    PrintPageHeader (pDC, pInfo->m_nCurPage);
    PrintPage (pDC, pInfo->m_nCurPage);
}

void CHexView::OnEndPrinting (CDC* pDC, CPrintInfo* pInfo)
{
    m_printerFont.DeleteObject ();
}

void CHexView::FormatLine (UINT nLine, CString& string)
{
    BYTE b[17];
    ::FillMemory (b, 16, 32);
    UINT nCount = GetDocument ()->GetBytes (nLine * 16, 16, b);

    string.Format ("%0.8X    %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X " \
        "%0.2X %0.2X - %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X " \
        "%0.2X    ", nLine * 16,
        b[0], b[1],  b[2],  b[3],  b[4],  b[5],  b[6],  b[7],
        b[8], b[9], b[10], b[11], b[12], b[13], b[14], b[15]);

    for (UINT i=0; i<nCount; i++) {
        if (!::IsCharAlphaNumeric (b[i]))
            b[i] = 0x2E;
    }

    b[nCount] = 0;
    string += b;

    if (nCount < 16) {
        UINT pos1 = 59;
        UINT pos2 = 60;
        UINT j = 16 - nCount;

        for (i=0; i<j; i++) {
            string.SetAt (pos1, ' ');
            string.SetAt (pos2, ' ');
            pos1 -= 3;
            pos2 -= 3;
            if (pos1 == 35) {
                string.SetAt (35, ' ');
                string.SetAt (36, ' ');
                pos1 = 33;
                pos2 = 34;
            }
        }
    }
}

void CHexView::PrintPageHeader (CDC* pDC, UINT nPageNumber)
{
    CString strHeader = GetDocument ()->GetPathName ();
    if (strHeader.GetLength () > 68)
        strHeader = GetDocument ()->GetTitle ();

    CString strPageNumber;
    strPageNumber.Format ("Page %d", nPageNumber);

    UINT nSpaces = 81 - strPageNumber.GetLength () -
        strHeader.GetLength ();
    for (UINT i=0; i<nSpaces; i++)
        strHeader += ' ';
    strHeader += strPageNumber;

    UINT y = m_cyPrinter * PRINTMARGIN;
    CFont* pOldFont = pDC->SelectObject (&m_printerFont);
    pDC->TextOut (m_cxOffset, y, strHeader);

    y += (m_cyPrinter * 3) / 2;
    pDC->MoveTo (m_cxOffset, y);
    pDC->LineTo (m_cxOffset + m_cxWidth, y);

    pDC->SelectObject (pOldFont);
}

void CHexView::PrintPage (CDC* pDC, UINT nPageNumber)
{
    if (m_nLinesTotal != 0) {
        UINT nStart = (nPageNumber - 1) * m_nLinesPerPage;
        UINT nEnd = min (m_nLinesTotal - 1, nStart + m_nLinesPerPage - 1);

        CString string;
        CFont* pOldFont = pDC->SelectObject (&m_printerFont);

        UINT y;
        for (UINT i=nStart; i<=nEnd; i++) {
            FormatLine (i, string);
            y = ((i - nStart) + PRINTMARGIN + 3) * m_cyPrinter;
            pDC->TextOut (m_cxOffset, y, string);
        }
        pDC->SelectObject (pOldFont);
    }
}
