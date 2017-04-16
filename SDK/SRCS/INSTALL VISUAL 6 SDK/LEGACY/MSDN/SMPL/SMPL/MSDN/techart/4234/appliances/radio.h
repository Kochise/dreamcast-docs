// radio.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CRadio command target

class CRadio : public CCmdTarget
{
	DECLARE_DYNCREATE(CRadio)
protected:
	CRadio();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
    BOOL IsOn() {return m_bIsOn;}
    void Power(BOOL b);
    int GetStation() {return m_iStation;}
    BOOL SetStation(int iStation);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRadio)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRadio();

	// Generated message map functions
	//{{AFX_MSG(CRadio)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CRadio)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CRadio)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

    // Declare the interface map for this object
    DECLARE_INTERFACE_MAP()

    // IApplianceUI interface
    BEGIN_INTERFACE_PART(ApplianceUI, IApplianceUI)
        STDMETHOD(ShowControl)(CWnd* pParent);
    END_INTERFACE_PART(ApplianceUI)

    // overrides for aggregation
    virtual BOOL OnCreateAggregates();

    // member variables
    BOOL m_bIsOn;
    int m_iStation;
    CMCIObject m_mciTune;
    IUnknown* m_punkBitmap; // aggregated object
};

/////////////////////////////////////////////////////////////////////////////
