// televisi.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTelevision command target

class CTelevision : public CCmdTarget
{
	DECLARE_DYNCREATE(CTelevision)
protected:
	CTelevision();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
    BOOL IsOn() {return m_bIsOn;}
    BOOL Power(BOOL b);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelevision)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTelevision();

	// Generated message map functions
	//{{AFX_MSG(CTelevision)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CTelevision)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CTelevision)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

    // Declare the interface map for this object
    DECLARE_INTERFACE_MAP()

    // IApplianceUI interface
    BEGIN_INTERFACE_PART(ApplianceUI, IApplianceUI)
        STDMETHOD(ShowControl)(HWND hwndParent);
    END_INTERFACE_PART(ApplianceUI)

    // overrides for aggregation
    virtual BOOL OnCreateAggregates();

    // member variables
    BOOL m_bIsOn;
    IUnknown* m_punkBitmap;     // aggregated bitmapobject
    IBitmap* m_pIBitmap;        // cached ptr
    IUnknown* m_punkNotifyList; // aggregated notify object
    INotifySrc* m_pINotifySrc;  // cached ptr 
};

/////////////////////////////////////////////////////////////////////////////
