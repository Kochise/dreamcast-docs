// MSJDragCtl.h : Declaration of the CMSJDragCtrl OLE control class.

/////////////////////////////////////////////////////////////////////////////
// CMSJDragCtrl : See MSJDragCtl.cpp for implementation.

class CMSJDragCtrl : public COleControl
{
	DECLARE_DYNCREATE(CMSJDragCtrl)

	friend CVBFrameWnd;

// Constructor
public:
	CMSJDragCtrl();

	CVBFrameWnd m_framewnd;

	// New function, gets immediate container HWND
	HWND GetContainerHWnd();

	HWND m_parentwnd;

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
	~CMSJDragCtrl();

	DECLARE_OLECREATE_EX(CMSJDragCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CMSJDragCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CMSJDragCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CMSJDragCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CMSJDragCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CMSJDragCtrl)
	afx_msg OLE_HANDLE GetParentWnd();
	afx_msg void SetParentWnd(OLE_HANDLE nNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CMSJDragCtrl)
	void FireFileDrop(OLE_HANDLE hWnd, LPCTSTR FName)
		{FireEvent(eventidFileDrop,EVENT_PARAM(VTS_HANDLE  VTS_BSTR), hWnd, FName);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CMSJDragCtrl)
	dispidParentWnd = 1L,
	eventidFileDrop = 1L,
	//}}AFX_DISP_ID
	};
};
