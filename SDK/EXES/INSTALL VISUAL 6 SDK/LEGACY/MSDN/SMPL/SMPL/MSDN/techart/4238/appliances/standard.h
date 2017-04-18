// standard.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CStandardLamp command target

class CStandardLamp : public CCmdTarget
{
	DECLARE_DYNCREATE(CStandardLamp)
protected:
	CStandardLamp();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStandardLamp)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CStandardLamp();

	// Generated message map functions
	//{{AFX_MSG(CStandardLamp)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CStandardLamp)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CStandardLamp)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

    // Declare the interface map for this object
    DECLARE_INTERFACE_MAP()

    // IOutlet interface
    BEGIN_INTERFACE_PART(Outlet, IOutlet)
        STDMETHOD(On)();
        STDMETHOD(Off)();
        STDMETHOD(GetState)(BOOL* pState);
    END_INTERFACE_PART(Outlet)

    // ILight interface
    BEGIN_INTERFACE_PART(Light, ILight)
        STDMETHOD(SetBrightness)(BYTE bLevel);
        STDMETHOD(GetBrightness)(BYTE* pLevel);
    END_INTERFACE_PART(Light)

    // overrides for aggregation
    virtual BOOL OnCreateAggregates();

    // member variables
    BYTE m_bLevel;
    IUnknown* m_punkBitmap;     // aggregated bitmapobject
    IBitmap* m_pIBitmap;        // cached ptr
    // Notification list
    IUnknown* m_punkNotifyList; // aggregated notify object
    INotifySrc* m_pINotifySrc;  // cached ptr 

    // helpers
    void SetLevel(BYTE bLevel);
};

/////////////////////////////////////////////////////////////////////////////
