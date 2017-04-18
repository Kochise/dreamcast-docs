// MSJSockCtl.h : Declaration of the CMSJSockCtrl OLE control class.

#define WSANOERROR     0
#define WS_VER_REQD    0x0101
#define WSCB_GETHOST   (WM_USER + 100)
#define WSCB_ASELECT   (WM_USER + 101)

/////////////////////////////////////////////////////////////////////////////
// CMSJSockCtrl : See MSJSockCtl.cpp for implementation.

class CMSJSockCtrl : public COleControl
{
	DECLARE_DYNCREATE(CMSJSockCtrl)

// Constructor
public:
	CMSJSockCtrl();

// Overrides

	// Drawing function
	virtual void OnDraw(
				CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);

	// Persistence
	virtual void DoPropExchange(CPropExchange* pPX);

	// Reset control state
	virtual void OnResetState();

// Implementation
protected:
	~CMSJSockCtrl();

	DECLARE_OLECREATE_EX(CMSJSockCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CMSJSockCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CMSJSockCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CMSJSockCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CMSJSockCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	afx_msg LONG OnGetHostCB(UINT wParam, LONG lParam);
	afx_msg LONG OnASelectCB(UINT wParam, LONG lParam);
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CMSJSockCtrl)
	afx_msg short GetVersion();
	afx_msg void SetVersion(short nNewValue);
	afx_msg BSTR GetSystemStatus();
	afx_msg void SetSystemStatus(LPCTSTR lpszNewValue);
	afx_msg short GetMaxSockets();
	afx_msg void SetMaxSockets(short nNewValue);
	afx_msg short GetHiVersion();
	afx_msg void SetHiVersion(short nNewValue);
	afx_msg BSTR GetDescription();
	afx_msg void SetDescription(LPCTSTR lpszNewValue);
	afx_msg long CreateSocket();
	afx_msg OLE_HANDLE gethostbyname(LPCTSTR host);
	afx_msg short getservbyname(LPCTSTR service);
	afx_msg long AsyncSelect(long socket, long msg);
	afx_msg OLE_HANDLE connect(long socket, short port, OLE_HANDLE hostent);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CMSJSockCtrl)
	void FireConnect(OLE_HANDLE hTask)
		{FireEvent(eventidConnect,EVENT_PARAM(VTS_HANDLE), hTask);}
	void FireRecvData(OLE_HANDLE hTask, LPCTSTR Data)
		{FireEvent(eventidRecvData,EVENT_PARAM(VTS_HANDLE  VTS_BSTR), hTask, Data);}
	void FireSockError(OLE_HANDLE hTask, short ENum)
		{FireEvent(eventidSockError,EVENT_PARAM(VTS_HANDLE  VTS_I2), hTask, ENum);}
	void FireGotHost(OLE_HANDLE hostent)
		{FireEvent(eventidGotHost,EVENT_PARAM(VTS_HANDLE), hostent);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CMSJSockCtrl)
	dispidVersion = 1L,
	dispidSystemStatus = 2L,
	dispidMaxSockets = 3L,
	dispidHiVersion = 4L,
	dispidDescription = 5L,
	dispidCreateSocket = 6L,
	dispidGethostbyname = 7L,
	dispidGetservbyname = 8L,
	dispidAsyncSelect = 9L,
	dispidConnect = 10L,
	eventidConnect = 1L,
	eventidRecvData = 2L,
	eventidSockError = 3L,
	eventidGotHost = 4L,
	//}}AFX_DISP_ID
	};
};
