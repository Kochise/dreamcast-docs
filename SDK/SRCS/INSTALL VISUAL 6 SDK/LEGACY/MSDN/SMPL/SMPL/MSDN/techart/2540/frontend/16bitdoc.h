// 16bitdoc.h : interface of the C16bitDoc class
//
/////////////////////////////////////////////////////////////////////////////

class C16bitDoc : public CDocument
{
protected: // create from serialization only
	C16bitDoc();
	DECLARE_DYNCREATE(C16bitDoc)

// Attributes
public:
// Operations
public:

// Implementation
public:
	virtual ~C16bitDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnNewDocument();

// Generated message map functions
protected:
	//{{AFX_MSG(C16bitDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
