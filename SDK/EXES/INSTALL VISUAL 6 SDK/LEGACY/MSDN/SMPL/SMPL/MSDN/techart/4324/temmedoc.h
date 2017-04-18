// TemMedoc.h : interface of the CTemMemPtrDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CTemMemPtrDoc : public CDocument
{
protected: // create from serialization only
	CTemMemPtrDoc();
	DECLARE_DYNCREATE(CTemMemPtrDoc)

// Attributes
public:

// Operations
public:
   CString& CalledByDialog() ;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTemMemPtrDoc)
	public:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTemMemPtrDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTemMemPtrDoc)
	afx_msg void OnCallitFromdoc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
