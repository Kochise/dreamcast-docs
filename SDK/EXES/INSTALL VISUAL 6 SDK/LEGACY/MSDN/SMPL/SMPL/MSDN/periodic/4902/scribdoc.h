// Forward declaration of data structure class
class CStroke;

class CScribbleDoc : public CDocument {
protected:
	CScribbleDoc();
	DECLARE_DYNCREATE(CScribbleDoc)

	// The document keeps track of the current pen width on
	// behalf of all views. We'd like the user interface of
	// Scribble to be such that if the user chooses the Draw
	// Thick Line command, it will apply to all views, not just
	// the view that currently has the focus.

	UINT            m_nPenWidth;        // current user-selected pen width
	CPen            m_penCur;           // pen created according to
										// user-selected pen style (width)
public:
	CTypedPtrList<CObList,CStroke*>     m_strokeList;   
	CPen*           GetCurrentPen() { return &m_penCur; }

	CStroke* NewStroke();
	
	//{{AFX_VIRTUAL(CScribbleDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

	virtual ~CScribbleDoc();

	virtual void SetModifiedFlag(BOOL bModified=TRUE); // **MOD** new

protected:
	void            InitDocument();
	//{{AFX_MSG(CScribbleDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// class CStroke
//
// A stroke is a series of connected points in the scribble drawing.
// A scribble document may have multiple strokes.

class CStroke : public CObject {
public:
	CStroke(UINT nPenWidth);
	CArray<CPoint,CPoint>  m_pointArray;   // series of connected points
	BOOL DrawStroke(CDC* pDC);
	virtual void Serialize(CArchive& ar);

protected:
	CStroke();
	DECLARE_SERIAL(CStroke)
	UINT	m_nPenWidth;    // one pen width applies to entire stroke
};
