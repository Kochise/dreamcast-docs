#include "stdafx.h"
#include "view3.h"
#include "doc.h"
#include "view.h"
#include "dyntempl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CView3Doc, CDocument)

BEGIN_MESSAGE_MAP(CView3Doc, CDocument)
   //{{AFX_MSG_MAP(CView3Doc)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CView3Doc::CView3Doc() : m_sText("Use \"File Edit\" to change this text.")
{
   m_nViewID = 0; // default view = 1st view in table
}

CView3Doc::~CView3Doc()
{
}

/////////////////
// Change document text
//
void CView3Doc::SetText(const char* pszText)
{ 
   m_sText = pszText; 
   SetModifiedFlag();
   UpdateAllViews(NULL);
}

////////////////
// Serialization: Save doc text and class "ID" of current active view.
// The ID is the 0-based index into the doc template's view class table.
//
void CView3Doc::Serialize(CArchive& ar)
{
   if (ar.IsStoring()) {
      ar << m_sText;
      POSITION pos = GetFirstViewPosition();
      ASSERT(pos);
      m_nViewID = ((CDynViewDocTemplate*)GetDocTemplate())->
         GetViewID(GetNextView(pos));
      ar << m_nViewID;
   } else {
      ar >> m_sText;       // restore text and view class ID
      ar >> m_nViewID;     // CDynViewDocTemplate will change the view
   }
}

///////////////////
// This function should be in dyntempl.cpp, but since it's the only
// function that needs to know about the document, it's easier to put it
// here and require that the "programmer" implement it. Otherwise, I'd
// have to implement a new class CDynViewDoc, and require apps to derive
// their doc from it. 
//
int CDynViewDocTemplate::GetViewID(CDocument *pDoc) 
{
   ASSERT_KINDOF(CView3Doc, pDoc);
   return ((CView3Doc*)pDoc)->GetViewID();
}
