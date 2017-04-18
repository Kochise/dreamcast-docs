// npscevw.h : interface of the CSecSrvView class
//
/////////////////////////////////////////////////////////////////////////////


class CSecuredNamedPipe;
class CSecuredFileMapping;
class ServerChainedQueue;
class CSecSrvDoc;
class CSecuredMutex;

class CEasyOutputView;

class CSecSrvView : public CEasyOutputView
{

private: 
 CSecuredNamedPipe *m_cpPipe;
 CSecuredFileMapping *m_cpFileMap;
 void *m_lpSharedMem;
 ServerChainedQueue *m_cqQueue;
 CSecuredMutex *m_cpMutex;
 char m_szDiagnosticMessage[MESSAGELENGTH];
 HANDLE m_hThread;
 BOOL m_bThreadIsActive;
protected: // create from serialization only
 CSecSrvView();
 DECLARE_DYNCREATE(CSecSrvView)
protected: // helper functions
 LPSTR ObtainErrorFromCode(DWORD dwErrorCode);
 void DisplayTextErrorMessage(LPSTR lpString, DWORD dwErrorCode);

// Attributes
public:
 CSecSrvDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSecSrvView)
public:
 virtual void OnDraw(CDC* pDC);  // overridden to draw this view
protected:
	//}}AFX_VIRTUAL

// Implementation
public:
 virtual ~CSecSrvView();
 friend long WINAPI PipeThreadFunction(CSecSrvView *cvTarget); 

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSecSrvView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnMutexpermissions();
	afx_msg void OnPermissions();
	afx_msg void OnWaittoconnect();
	afx_msg void OnDatabaseAddarecord();
	afx_msg void OnDatabaseRemovearecord();
	afx_msg void OnDatabaseViewcontents();
	afx_msg void OnFilemappingsPermissions();
	afx_msg void OnFileCancelwait();
	afx_msg void OnUpdateFileCancelwait(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWaittoconnect(CCmdUI* pCmdUI);
	afx_msg void OnDatabasePermissions();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in npscevw.cpp
inline CSecSrvDoc* CSecSrvView::GetDocument()
   { return (CSecSrvDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
