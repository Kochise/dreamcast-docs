// Interdoc.h : interface of the CInterpDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CInterpDoc : public CDocument
{
protected: // create from serialization only
	CInterpDoc();
	DECLARE_DYNCREATE(CInterpDoc)

// Attributes
public:

// Operations
public:
    CDIB m_dib;
    CDIBPal m_pal;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterpDoc)
	public:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInterpDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CInterpDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
