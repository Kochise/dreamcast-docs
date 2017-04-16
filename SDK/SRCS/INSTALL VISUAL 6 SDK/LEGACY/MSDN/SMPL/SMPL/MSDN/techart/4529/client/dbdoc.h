// DBdoc.h : interface of the CDBDoc class
//
/////////////////////////////////////////////////////////////////////////////

#include "..\interface\DBsrv.h"

class CDBDoc : public CDocument
{
protected: // create from serialization only
	CDBDoc();
	DECLARE_DYNCREATE(CDBDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBDoc)
	public:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
  IDB *m_pDB; // pointer to database object

  CString m_csData; // last data read from database
	int m_nCount;			// number of writes to database
  short m_nTable;		// number of last table created

public:
	virtual ~CDBDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDBDoc)
	afx_msg void OnDatabaseCreate();
	afx_msg void OnDatabaseWrite();
	afx_msg void OnDatabaseRead();
	afx_msg void OnUpdateDatabaseWrite(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDatabaseRead(CCmdUI* pCmdUI);
	afx_msg void OnDatabaseReadMultiple();
	afx_msg void OnUpdateDatabaseReadMultiple(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
