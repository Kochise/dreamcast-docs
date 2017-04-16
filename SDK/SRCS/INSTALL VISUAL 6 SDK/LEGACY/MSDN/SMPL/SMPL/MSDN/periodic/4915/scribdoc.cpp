#include "stdafx.h"
#include "Scribble.h"
#include "ScribDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CScribbleDoc, CDocument)

BEGIN_MESSAGE_MAP(CScribbleDoc, CDocument)
	//{{AFX_MSG_MAP(CScribbleDoc)
	ON_UPDATE_COMMAND_UI(ID_TITLE_MOD,		   OnUpdateMod)
	ON_UPDATE_COMMAND_UI(ID_TITLE_NUMSTROKES, OnUpdateNumStrokes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CScribbleDoc::CScribbleDoc()
{
}

CScribbleDoc::~CScribbleDoc()
{
}

BOOL CScribbleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	InitDocument();
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CScribbleDoc serialization

void CScribbleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring()) {
	} else {
	}
	m_strokeList.Serialize(ar);
}

BOOL CScribbleDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	InitDocument(); 
	return TRUE;
}

void CScribbleDoc::DeleteContents() 
{
	while (!m_strokeList.IsEmpty()) {
		delete m_strokeList.RemoveHead();
	}
	CDocument::DeleteContents();
}

void CScribbleDoc::InitDocument()
{
	m_nPenWidth = 2; // default 2 pixel pen width
	m_penCur.CreatePen(PS_SOLID, m_nPenWidth, RGB(0,0,0)); // solid, black pen
}

CStroke* CScribbleDoc::NewStroke()
{
	CStroke* pStrokeItem = new CStroke(m_nPenWidth);
	m_strokeList.AddTail(pStrokeItem);
	SetModifiedFlag();  // Mark the document as having been modified, for
							  // purposes of confirming File Close.
	return pStrokeItem;
}

void CScribbleDoc::OnUpdateMod(CCmdUI* pCmdUI)
{
	pCmdUI->SetText(IsModified() ? "*" : "");
	pCmdUI->m_bContinueRouting = TRUE;
}

void CScribbleDoc::OnUpdateNumStrokes(CCmdUI* pCmdUI)
{
	CString s;
	s.Format(" [S:%d]", m_strokeList.GetCount());
	pCmdUI->SetText(s);
	pCmdUI->m_bContinueRouting = TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CStroke

IMPLEMENT_SERIAL(CStroke, CObject, 1)

CStroke::CStroke()
{
}

CStroke::CStroke(UINT nPenWidth)
{
	m_nPenWidth = nPenWidth;
}

void CStroke::Serialize(CArchive& ar)
{
	if (ar.IsStoring()) {
		ar << (WORD)m_nPenWidth;
		m_pointArray.Serialize(ar);
	} else {
		WORD w;
		ar >> w;
		m_nPenWidth = w;
		m_pointArray.Serialize(ar);
	}
}

BOOL CStroke::DrawStroke(CDC* pDC)
{
	CPen penStroke;
	if (!penStroke.CreatePen(PS_SOLID, m_nPenWidth, RGB(0,0,0)))
		return FALSE;
	CPen* pOldPen = pDC->SelectObject(&penStroke);
	pDC->MoveTo(m_pointArray[0]);
	for (int i=1; i < m_pointArray.GetSize(); i++) {
		pDC->LineTo(m_pointArray[i]);
	}
	pDC->SelectObject(pOldPen);
	return TRUE;
}
