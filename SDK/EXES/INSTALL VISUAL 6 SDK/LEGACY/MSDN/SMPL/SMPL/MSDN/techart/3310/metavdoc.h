// metavdoc.h : interface of the CMetavw1Doc class
//
/////////////////////////////////////////////////////////////////////////////
#include "CEMF.H"

class CMetavw1Doc : public CDocument
{
protected: // create from serialization only
	CMetavw1Doc();
	DECLARE_DYNCREATE(CMetavw1Doc)

// Attributes
public:
   CString m_szPathName;
   CEMF m_cemf;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMetavw1Doc)
	public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMetavw1Doc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMetavw1Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
