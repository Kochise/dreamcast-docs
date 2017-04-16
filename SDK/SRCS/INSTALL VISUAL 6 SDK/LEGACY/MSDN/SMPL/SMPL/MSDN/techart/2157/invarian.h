// invarian.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInvariantDoc document

class CInvariantDoc : public CPetriNetDoc
{
	DECLARE_SERIAL(CInvariantDoc)
protected:
	CInvariantDoc();			// protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Implementation
protected:
	virtual ~CInvariantDoc();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
	virtual	BOOL OnNewDocument();
	CString GrabNameFromNet(BOOL, int);

	// Generated message map functions
protected:
	//{{AFX_MSG(CInvariantDoc)
	afx_msg void OnUpdateViewAsanet(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

