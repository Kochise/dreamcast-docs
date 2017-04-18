// pviewdoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPViewDoc document

class CPViewDoc : public CDocument
{
protected:
	CPViewDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPViewDoc)
    
// Attributes
public:

   char szStatusMessage[300];

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPViewDoc)
	public:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPViewDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void RefreshProcessList();
	// Generated message map functions
protected:
	//{{AFX_MSG(CPViewDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
