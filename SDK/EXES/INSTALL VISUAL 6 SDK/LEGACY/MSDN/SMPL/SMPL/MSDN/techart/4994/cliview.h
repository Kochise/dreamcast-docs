// npsecvw.h : interface of the CSecCliView class
//
/////////////////////////////////////////////////////////////////////////////


// these are the operation modes that the client/server interaction
// can be in

#define OPERATION_MODE_NOT_CONNECTED 0
#define OPERATION_MODE_LOCAL 1
#define OPERATION_MODE_REMOTE 2

#define TRANSACTIONS 1000

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
        CHAINLIST m_clStuff[TRANSACTIONS];
        int m_iIndices[TRANSACTIONS];
        LARGE_INTEGER m_liAddSum,m_liDeleteSum;


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
	virtual void OnInitialUpdate();
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
	afx_msg void OnRemoteaccessAddarecord();
	afx_msg void OnRemoteaccessRemovearecord();
	afx_msg void OnRemoteaccessViewcontents();
	afx_msg void OnDisconnect();
	afx_msg void OnUpdateNotRemote(CCmdUI* pCmdUI);
	afx_msg void On100transact();
	afx_msg void On1000deletes();
	afx_msg void OnUpdateRemote(CCmdUI* pCmdUI);
	afx_msg void OnBatch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in npsecvw.cpp
inline CSecCliDoc* CSecCliView::GetDocument()
   { return (CSecCliDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
