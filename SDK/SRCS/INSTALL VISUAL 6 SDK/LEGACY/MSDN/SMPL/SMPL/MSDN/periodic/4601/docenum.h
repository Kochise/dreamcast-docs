////////////////////////////////////////////////////////////////
// CDocEnumerator Copyright 1995 Microsoft Systems Journal. 
//
// CDocEnumerator Enumerates all the documents in an application.
// See ENUMDOC.CPP for an example of how to use it.

class CDocEnumerator {
private:
#if (_MFC_VER >= 0x0400)
	CDocManager*	m_pDocManager;		// MFC 4.0+ uses doc manager
#else
   CPtrList*      m_pTemplateList;  // list of CDocTemplate's
#endif
   POSITION       m_posNextTemplate;// current POSITION in above
   CDocTemplate*  m_pDocTemplate;   // current document template
   POSITION       m_posNextDoc;     // current POSITION in above
public:
   CDocEnumerator();
   void Rewind();
   CDocument* GetNextDoc();
   CDocument* operator() ()         { return GetNextDoc(); }
};
