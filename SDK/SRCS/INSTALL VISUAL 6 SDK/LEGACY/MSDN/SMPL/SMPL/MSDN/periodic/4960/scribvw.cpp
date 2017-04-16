////////////////////////////////////////////////////////////////
// Modified SCRIBBLE Copyright 1996 Microsoft Systems Journal. 
// Portions Copyright (C) 1992-1995 Microsoft Corporation.
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// See SCRIBBLE.CPP for Description of program.
//
// NOTE: Only changes from original SCRIBBLE code are shown.
// Full source available on any MSJ bulletin board.

#include "stdafx.h"
#include "Scribble.h"
#include "ScribDoc.h"
#include "ScribVw.h"

.
.
.

/////////////////////////////////////////////////////////////////////////////
// CScribbleView drawing
//
void CScribbleView::OnDraw(CDC* pDC)
{
   CScribbleDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);
   if (pDoc->IsInitialized()) { 
      // The view delegates the drawing of individual strokes to
      // CStroke::DrawStroke().
      CTypedPtrList<CObList,CStroke*>& strokeList = pDoc->m_strokeList;
      POSITION pos = strokeList.GetHeadPosition();
      while (pos != NULL) {
         CStroke* pStroke = strokeList.GetNext(pos);
         pStroke->DrawStroke(pDC);
      }
   } else {
      // ***PD Draw "empty" background if doc not initialized.
      // Note: be sure to use COLOR_3DSHADOW to get the
      // right logical color, in case user has customized it.
      //
      CRect rc;
      GetClientRect(&rc);
      HGDIOBJ hOldBrush = pDC->SelectObject(GetSysColorBrush(COLOR_3DSHADOW));
      pDC->PatBlt(rc.left, rc.top, rc.Width(), rc.Height(), PATCOPY);
      pDC->SelectObject(hOldBrush);
   }
}

//////////////////
// ***PD: Change so drawing is allowed only if doc is initialized.
//
void CScribbleView::OnLButtonDown(UINT, CPoint point) 
{
   CScribbleDoc* pDoc = GetDocument();
   if (pDoc->IsInitialized()) {
      m_pStrokeCur = pDoc->NewStroke();
      // Add first point to the new stroke
      m_pStrokeCur->m_pointArray.Add(point);

      SetCapture();       // Capture the mouse until button up.
      m_ptPrev = point;   // Serves as the MoveTo() anchor point for the
                          // LineTo() the next point, as the user drags the
                          // mouse.
   }
   return;
}

//////////////////
// ***PD: If doc not initialized, disable all doc/view commands by
// returning FALSE here--i.e., do not even route through doc/view msg maps.
// Command routing behaves as if there were no doc nor view. NOTE: this 
// only works if CFrameWnd::m_bAutoMenuEnable = TRUE, the default.
//
BOOL CScribbleView::OnCmdMsg(UINT nID, int nCode, void* pExtra,
   AFX_CMDHANDLERINFO* pHandlerInfo)
{
   CScribbleDoc *pDoc = GetDocument();
   return pDoc->IsInitialized() ?
      CView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo) : FALSE;
}
