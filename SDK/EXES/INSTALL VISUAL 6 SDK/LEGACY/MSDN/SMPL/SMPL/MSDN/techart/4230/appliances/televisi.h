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

    // IDrawing interface
    BEGIN_INTERFACE_PART(Drawing, IDrawing)
        STDMETHOD(Draw)(CDC* pDC,int x, int y);
        STDMETHOD(SetPalette)(CPalette* pPal);
        STDMETHOD(GetRect)(CRect* pRect);
    END_INTERFACE_PART(Drawing)

    // IApplianceUI interface
    BEGIN_INTERFACE_PART(ApplianceUI, IApplianceUI)
        STDMETHOD(ShowControl)(CWnd* pParent);
    END_INTERFACE_PART(ApplianceUI)

    // member variables
    CDIB m_dibImage;
    CPalette* m_pPal;
    BOOL m_bIsOn;
};

/////////////////////////////////////////////////////////////////////////////
