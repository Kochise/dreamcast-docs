// OCCSampDoc.h : interface of the COCCSampDoc class
//
/////////////////////////////////////////////////////////////////////////////

#include "msoc97.h"

class COCCSampDoc : public CDocument
{
protected: // create from serialization only
	COCCSampDoc();
	DECLARE_DYNCREATE(COCCSampDoc)

// Attributes
public:
	IMsocRouteSlip * m_RouteSlip;
	IMsocOutlookJournalEntry* m_pJournalEntry;
	CStringArray m_rgstrFileList;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COCCSampDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COCCSampDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COCCSampDoc)
	afx_msg void OnInsertFile();
	afx_msg void OnPostFile();
	afx_msg void OnFileSend();
	afx_msg void OnFileAddroutingslip();
	afx_msg void OnFileRoute();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
