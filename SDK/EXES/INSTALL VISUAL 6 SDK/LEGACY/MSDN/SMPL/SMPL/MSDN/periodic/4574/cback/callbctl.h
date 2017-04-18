// callbctl.h : Declaration of the CCallBackCtrl OLE control class.

/////////////////////////////////////////////////////////////////////////////
// CCallBackCtrl : See callbctl.cpp for implementation.

class CCallBackCtrl : public COleControl
{
	DECLARE_DYNCREATE(CCallBackCtrl)

// Constructor
public:
	CCallBackCtrl();

	CWordArray m_msglist;  // List of registered messages

// Overrides

	// We want first crack at the user messages!
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	// Drawing function
	virtual void OnDraw(
				CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);

	// Persistence
	virtual void DoPropExchange(CPropExchange* pPX);

	// Reset control state
	virtual void OnResetState();

// Implementation
protected:
	~CCallBackCtrl();

	DECLARE_OLECREATE_EX(CCallBackCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CCallBackCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CCallBackCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CCallBackCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CCallBackCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CCallBackCtrl)
	afx_msg short WatchMsg(short msg);
	afx_msg long PtrValL(OLE_HANDLE lpPtr);
	afx_msg short PtrValI(OLE_HANDLE lpPtr);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CCallBackCtrl)
	void FireCallback(short msg, long wParam, long lParam)
		{FireEvent(eventidCallback,EVENT_PARAM(VTS_I2  VTS_I4  VTS_I4), msg, wParam, lParam);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CCallBackCtrl)
	dispidWatchMsg = 1L,
	dispidPtrValL = 2L,
	dispidPtrValI = 4L,
	eventidCallback = 1L,
	//}}AFX_DISP_ID
	};
};
