// threadlibtestDoc.h : interface of the CThreadlibtestDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CThreadlibtestDoc : public CDocument
{
protected: // create from serialization only
	CThreadlibtestDoc();
	DECLARE_DYNCREATE(CThreadlibtestDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThreadlibtestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CThreadlibtestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CThreadlibtestDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
