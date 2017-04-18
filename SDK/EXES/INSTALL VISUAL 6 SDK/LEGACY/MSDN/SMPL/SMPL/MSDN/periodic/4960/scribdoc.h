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

class CScribbleDoc : public CDocument {
protected:
   BOOL            m_bInitialized; // ***PD: whether doc is initialized
public:
	.
	.
   void     InitDocument();

   // ***PD new functions
   BOOL     Initialize();
   BOOL     IsInitialized() { return m_bInitialized; }
	.
	.
};
