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

//////////////////
// **MOD**
// Overloaded version of OnOpenDocument loads SCRIBBLE doc from resource
// data instead of disk file. Arg is ID of resource.
//
BOOL CScribbleDoc::OnOpenDocument(UINT uID)
{
	// Load the resource into memory
	//
	HINSTANCE hinst = AfxGetInstanceHandle();
	HRSRC hRes = FindResource(hinst, (LPCSTR)uID, "SCRIBDOC");
	if (hRes==NULL) {
		TRACE("Couldn't find SCRIBDOC resource %d!\n", uID);
		return FALSE;
	}
	DWORD len = SizeofResource(hinst, hRes);

	// Note: Under Win16, you have to do Lock/UnlockResource, but
	// in Win32 these are no-ops and you can just cast the HGLOBAL
	// returned by LoadResource to a BYTE*.
	//
	BYTE* lpRes = (BYTE*)LoadResource(hinst, hRes);
	ASSERT(lpRes);

	// Create mem file
	// 
	CMemFile file(lpRes, len);

	// Create archive and load from it. 
	// This is just like CDocument::OnOpenDocument
	//
	BOOL bRet = FALSE;		// assume failure
	DeleteContents();

	CArchive ar(&file, CArchive::load);
	ar.m_pDocument = this;
	ar.m_bForceFlat = FALSE;
	TRY {
		CWaitCursor wait;		// hourglass
		Serialize(ar);			// do normal Serialize thing
		ar.Close();				// done
		bRet = TRUE;			// success
		SetModifiedFlag(FALSE);

	} CATCH_ALL(e) {
		TRACE("Unexpected exception loading SCRIBDOC %d\n", uID);
		DeleteContents();
			
	} END_CATCH_ALL

	FreeResource((HANDLE)lpRes);
	return bRet;
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
