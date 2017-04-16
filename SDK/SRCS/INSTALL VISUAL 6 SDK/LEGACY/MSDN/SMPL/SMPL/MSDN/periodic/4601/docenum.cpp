////////////////////////////////////////////////////////////////
// DOCENUM Copyright 1995 Microsoft Systems Journal. 
//
// CDocEnumerator Enumerates all the documents in an application.
// See ENUMDOC.CPP for an example of how to use it.
//
// Revised  12-18-95 for MFC 4.0 CDocManager

#include "stdafx.h"
#include "docenum.h"

//////////////////
// Construction: do rewind.
//
CDocEnumerator::CDocEnumerator()
{
   Rewind();
}

//////////////////
// Rewind: start at the beginning
//
void CDocEnumerator::Rewind()
{
#if (_MFC_VER >= 0x0400)
	m_pDocManager    = AfxGetApp()->m_pDocManager;
   m_posNextTemplate= m_pDocManager->GetFirstDocTemplatePosition();
#else
   m_pTemplateList  = &AfxGetApp()->m_templateList;
   m_posNextTemplate= m_pTemplateList->GetHeadPosition();
#endif
   m_pDocTemplate   = NULL;
   m_posNextDoc     = NULL;
}

//////////////////
// GetNextDoc: translate AFX silly POSITION implementation to
// more programmer-friendly style (if you don't like it, sue me).
//
CDocument* CDocEnumerator::GetNextDoc()
{
   if (m_posNextDoc!=NULL) {
      // If there's another doc in this template, return it and advance pos
      ASSERT(m_pDocTemplate);
      return m_pDocTemplate->GetNextDoc(m_posNextDoc); // return it

   } else if (m_posNextTemplate!=NULL) { 
      // If there's another doc template in the app, get its first doc
#if (_MFC_VER >= 0x400)
      m_pDocTemplate = m_pDocManager->GetNextDocTemplate(m_posNextTemplate);
#else
      m_pDocTemplate = 
			(CDocTemplate*)m_pTemplateList->GetNext(m_posNextTemplate);
#endif
      m_posNextDoc = m_pDocTemplate->GetFirstDocPosition();
      return GetNextDoc();
   } 
   return NULL; // no more docs, sob sob
}
