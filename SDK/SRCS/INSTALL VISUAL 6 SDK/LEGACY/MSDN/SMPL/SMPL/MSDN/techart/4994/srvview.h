// npscevw.h : interface of the CSecSrvView class
//
/////////////////////////////////////////////////////////////////////////////
#define MAXCLIENTCOUNT 25 // absolutely random number...


class CServerNamedPipe;
class CServerFileMapping;
class ServerChainedQueue;
class CSecSrvDoc;
class CServerMutex;

class CServerDatabaseProtocol;
class CEasyOutputView;
class CClientObject;

typedef struct
{
 CServerNamedPipe *Client_hPipe;
 CClientObject *Client_ClientObject;
} CLIENTBLOCK, *PCLIENTBLOCK;



class CSecSrvView : public CEasyOutputView
{

private:
 HANDLE m_hConnectThread;
 BOOL m_bFinished; 
 CServerNamedPipe *m_cpPipe;
 CServerFileMapping *m_cpFileMap;
 void *m_lpSharedMem;
 ServerChainedQueue *m_cqQueue;
 CServerMutex *m_cpMutex;
 char m_szDiagnosticMessage[MESSAGELENGTH];
 CServerDatabaseProtocol *m_Protocol;
// HANDLE m_hThread;
 BOOL m_bThreadIsActive;
 CLIENTBLOCK m_ciClientBlock[MAXCLIENTCOUNT];
protected: // create from serialization only
 friend long WINAPI PipeThreadFunction(void *); 
 CSecSrvView();
 DECLARE_DYNCREATE(CSecSrvView)
protected: // helper functions
 LPSTR ObtainErrorFromCode(DWORD dwErrorCode);
 void DisplayTextErrorMessage(LPSTR lpString, DWORD dwErrorCode);
 void OnWaittoconnect();

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
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
 virtual ~CSecSrvView();
// friend long WINAPI PipeThreadFunction(CSecSrvView *cvTarget); 

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
	afx_msg void OnDatabaseAddarecord();
	afx_msg void OnDatabaseRemovearecord();
	afx_msg void OnDatabaseViewcontents();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in npscevw.cpp
inline CSecSrvDoc* CSecSrvView::GetDocument()
   { return (CSecSrvDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

