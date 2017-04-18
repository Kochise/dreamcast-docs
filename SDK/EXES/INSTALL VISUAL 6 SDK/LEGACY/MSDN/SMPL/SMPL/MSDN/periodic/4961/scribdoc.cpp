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
//
#include "stdafx.h"
#include "Scribble.h"
#include "ScribDoc.h"

.
.
.

BOOL CScribbleDoc::OnNewDocument()
{
   if (!CDocument::OnNewDocument())
      return FALSE;
   InitDocument();
   m_bInitialized = FALSE; // ***PD: Not initialized yet
   return TRUE;
}

BOOL CScribbleDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
   if (!CDocument::OnOpenDocument(lpszPathName))
      return FALSE;
   InitDocument();
   return m_bInitialized = TRUE; // ***PD: an open doc is initialized
}

void CScribbleDoc::DeleteContents() 
{
   while (!m_strokeList.IsEmpty()) {
      delete m_strokeList.RemoveHead();
   }
   CDocument::DeleteContents();
}

//////////////////
// ***PD: NOTE: This is the old function from the tutorial code. It's called
// InitDocument but it's only the raw initialization, not the
// "real" initialization, which requires setting m_bInitialized to TRUE.
//
void CScribbleDoc::InitDocument()
{
   m_bThickPen = FALSE;
   m_nThinWidth = 2;   // default thin pen is 2 pixels wide
   m_nThickWidth = 5;  // default thick pen is 5 pixels wide
   ReplacePen();       // initialize pen according to current width
}

//////////////////
// ***PD: This function REALLY initializes a new document, as opposed to
// OnNewDocument. That is, it performs the initialization required
// to use the document. It's called when the user invokes the File New
// command from the menu. This implementation doesn't actually do anything,
// it just sleeps to simulate some long operation a real app might do.
//
BOOL CScribbleDoc::Initialize()
{
   // This implementation doesn't actually do anything
   // except sleep for three seconds to simulate a lengthy operation
   //
   CWaitCursor wait;   // display wait cursor
   Sleep(3000);
   return m_bInitialized = TRUE;
}

