// StopLiteCtl.h : Declaration of the CStopLiteCtrl OLE control class.

/////////////////////////////////////////////////////////////////////////////
// CStopLiteCtrl : See StopLiteCtl.cpp for implementation.

class CStopLiteCtrl : public COleControl
{
	DECLARE_DYNCREATE(CStopLiteCtrl)

// Constructor
public:
	CStopLiteCtrl();

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
	~CStopLiteCtrl();

	DECLARE_OLECREATE_EX(CStopLiteCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CStopLiteCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CStopLiteCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CStopLiteCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CStopLiteCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CStopLiteCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CStopLiteCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CStopLiteCtrl)
		// NOTE: ClassWizard will add and remove enumeration elements here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISP_ID
	};
};
