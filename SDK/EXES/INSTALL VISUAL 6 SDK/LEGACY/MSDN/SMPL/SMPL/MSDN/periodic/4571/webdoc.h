/////////////////////////////////////////////////////////////////////////////
// WebDoc.h : interface of the CWebDoc class
//
// This is a part of the Webster HTTP Server application
// for Microsoft Systems Journal
//

class CListen ;	// forward reference
class CClient ;	//...ditto...

#include "logger.h"		// ofstream

class CWebDoc : public CDocument
{
protected: // create from serialization only
	CWebDoc();
	DECLARE_DYNCREATE(CWebDoc)

// Attributes
public:
	CStringList	m_strList ;		// Status text buffer
	CString		m_strInfo ;		// Current text construction buffer
	int			m_nLines ;		// Number of lines currently in the
								//   status text buffer
	int			m_nMaxLines ;	// Size of status text buffer
								//   Static for now, but we may want to make
								//   this configurable someday

private:
	// Server
	CListen*	m_pSocket ;			// our document's one and only listening socket (service port)
	CPtrList	m_listConnects ;	// list of active connections
	// Logging
	ofstream	m_fileLog ;

// Operations
public:
	// Server
	void OnAccept() ;
	void CheckIdleConnects() ;
	void KillSocket ( CClient* pSocket ) ;
	// Logging
	void OpenLogfile() ;
	void WriteLog ( COMLOGREC& LogRec ) ;
	// Status
	void Message ( LPCTSTR lpszMessage ) ;
	void Message ( CString cMessage ) ;
	void VMessage ( LPCTSTR lpszFormat, ... ) ;
	void DbgMessage ( LPCTSTR lpszMessage ) ;
	void DbgMessage ( CString cMessage ) ;
	void DbgVMessage ( LPCTSTR lpszFormat, ... ) ;
	BOOL ActiveClients() { return ( ! m_listConnects.IsEmpty() ) ; }


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWebDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	virtual void SetTitle(LPCTSTR lpszTitle);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWebDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWebDoc)
	afx_msg void OnClearView();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
