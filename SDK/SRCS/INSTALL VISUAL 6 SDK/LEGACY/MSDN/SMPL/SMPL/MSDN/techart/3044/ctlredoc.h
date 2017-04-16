// ctlredoc.h : interface of the CCtlregDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CCtlregDoc : public CDocument
{
protected: // create from serialization only
	CCtlregDoc();
	DECLARE_DYNCREATE(CCtlregDoc)

// Attributes
public:
// Operations
public:

// Implementation
public:
	virtual ~CCtlregDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnNewDocument();

// Generated message map functions
protected:
	//{{AFX_MSG(CCtlregDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
