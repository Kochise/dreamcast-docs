// npsecvw.h : interface of the CSecCliView class
//
/////////////////////////////////////////////////////////////////////////////


// these are the operation modes that the client/server interaction
// can be in

#define OPERATION_MODE_NOT_CONNECTED 0
#define OPERATION_MODE_LOCAL 1
#define OPERATION_MODE_REMOTE 2

class CClientNamedPipe;
class CMutex;
class CFileMapping;
class ChainedQueue;
class CClientDatabaseProtocol;

class CSecCliView : public CEasyOutputView
{
private: CClientNamedPipe *m_cpPipe;
        CMutex *m_cpMutex;
		CFileMapping *m_cpFileMap;
		void *m_lpSharedMemory;
		BOOL m_bRemote, m_bLocal;
		char m_szDiagnosticMessage[MESSAGELENGTH];
		int m_iOperationMode;
		ChainedQueue *m_cqQueue;
		CClientDatabaseProtocol *m_cpDB;


protected: // create from serialization only
	CSecCliView();
	DECLARE_DYNCREATE(CSecCliView)

protected:
    LPSTR ObtainErrorFromCode(DWORD dwErrorCode);
    void DisplayTextErrorMessage(LPSTR lpString, DWORD dwErrorCode);


// Attributes
public:
	CSecCliDoc* GetDocument();


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSecCliView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSecCliView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSecCliView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnConnect();
	afx_msg void OnUpdateLocal(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRemote(CCmdUI* pCmdUI);
	afx_msg void OnLocalaccessAddarecord();
	afx_msg void OnLocalaccessRemovearecord();
	afx_msg void OnLocalaccessViewcontents();
	afx_msg void OnRemoteaccessAddarecord();
	afx_msg void OnRemoteaccessRemovearecord();
	afx_msg void OnRemoteaccessViewcontents();
	afx_msg void OnDisconnect();
	afx_msg void OnLocalaccessCloseshareddatabase();
	afx_msg void OnLocalaccessOpenshareddatabase();
	afx_msg void OnUpdateNotRemote(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNotLocal(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in npsecvw.cpp
inline CSecCliDoc* CSecCliView::GetDocument()
   { return (CSecCliDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
