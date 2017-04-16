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

class CScribbleView : public CView {
protected:
   // ***PD new override
   BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra,
      AFX_CMDHANDLERINFO* pHandlerInfo);

   // ***PD overrides
   virtual void OnDraw(CDC* pDC);
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
