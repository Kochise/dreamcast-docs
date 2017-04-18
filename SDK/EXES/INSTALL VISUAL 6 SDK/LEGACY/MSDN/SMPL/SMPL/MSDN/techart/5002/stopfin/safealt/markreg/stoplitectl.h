// StopLiteCtl.h : Declaration of the CStopLiteCtrl OLE control class.

/////////////////////////////////////////////////////////////////////////////
// CStopLiteCtrl : See StopLiteCtl.cpp for implementation.

class CStopLiteCtrl : public COleControl
{
	DECLARE_DYNCREATE(CStopLiteCtrl)

// stoplight state (values of m_color/Color property)
	enum { SL_NONE = 0,
			SL_FIRST = 1,	// first light in cycle
			SL_RED = 1, SL_GREEN = 2, SL_YELLOW = 3, // cycle order
			SL_LAST = 3,	// last light in cycle
			SL_TEST = 4 };	// test MUST be last (see SetColor)
	
// bits corresponding to the three lights; used for drawing
	enum { SLBIT_RED = 1, SLBIT_GREEN = 2, SLBIT_YELLOW = 4,  };

// possible colors for light: off, red, green, yellow
	enum { SLCOLOR_OFF = RGB(63, 63, 63),	// dark gray
			SLCOLOR_RED = RGB(255, 0, 0),
			SLCOLOR_GREEN = RGB(0, 255, 0), 
			SLCOLOR_YELLOW = RGB(255, 255, 0) };
		
// Constructor
public:
	CStopLiteCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStopLiteCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual void OnAmbientPropertyChange(DISPID dispid);
	//}}AFX_VIRTUAL



// Implementation
private:
	void FireRightEvent();
	short m_color;

protected:
	~CStopLiteCtrl();

	DECLARE_OLECREATE_EX(CStopLiteCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CStopLiteCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CStopLiteCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CStopLiteCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CStopLiteCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CStopLiteCtrl)
	afx_msg short GetColor();
	afx_msg void SetColor(short nNewValue);
	afx_msg void Next();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CStopLiteCtrl)
	void FireStop()
		{FireEvent(eventidStop,EVENT_PARAM(VTS_NONE));}
	void FireCaution()
		{FireEvent(eventidCaution,EVENT_PARAM(VTS_NONE));}
	void FireGo()
		{FireEvent(eventidGo,EVENT_PARAM(VTS_NONE));}
	void FireTesting()
		{FireEvent(eventidTesting,EVENT_PARAM(VTS_NONE));}
	void FireOff()
		{FireEvent(eventidOff,EVENT_PARAM(VTS_NONE));}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CStopLiteCtrl)
	dispidColor = 1L,
	dispidNext = 2L,
	eventidStop = 1L,
	eventidCaution = 2L,
	eventidGo = 3L,
	eventidTesting = 4L,
	eventidOff = 5L,
	//}}AFX_DISP_ID
	};
private:
	int TranslateLights();
	void DrawLight(CDC* pdc, 
		const CRect& rcBounds, 
		int nPercentDown, 
		int nPercentDiameter, 
		COLORREF crColor
		);
};
