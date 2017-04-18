// VConCtl.h : Declaration of the CVControlCtrl OLE control class.

/////////////////////////////////////////////////////////////////////////////
// CVerificationResult
//
// This class contains the result of a single verification of an interface or method
// Simple result containment class so they can be stroed on a CObArray
class CVerificationResult : public CObject
{

public:
	CVerificationResult(){};

	void SetResult(BOOL bMandatory, BOOL bVerified,
						const CString& rstrVerification, const CString& rstrResult)
	{
		m_bMandatory = bMandatory;
		m_bVerified = bVerified;
		m_strVerification = rstrVerification;
		m_strResult = rstrResult;
	};

	// methods to get at member variables
	BOOL IsMandatory(void){ return m_bMandatory; };
	BOOL IsVerified(void){ return m_bVerified; };
	CString* GetDescription(void){ return &m_strVerification; };
	CString* GetResult(void){ return &m_strResult; };

protected:
	BOOL m_bMandatory;	// Is this a mandatory Interface or Method?
	BOOL m_bVerified;		// Was this result successful against the guidelines?
	CString m_strVerification; //Description of the verification
	CString m_strResult;	// Description of result, including return codes etc.
};


/////////////////////////////////////////////////////////////////////////////
// CInterfaceVerificationResult
//
// This class contains the result of a single verification of an interface
// in addition to the inherrited functionality of the result 
// it has an array of results of method calls n the interface
class CInterfaceVerificationResult : public CVerificationResult
{

public:
	CInterfaceVerificationResult(){};
	~CInterfaceVerificationResult();

	void LogMethodResult( BOOL bMandatory, BOOL bSuccess, UINT nDescriptionID, const CString& rstrResult);

	// methods to get at member variables
	CObArray* GetMethodResultArray(void){ return &m_resultMethodArray; };

protected:
	CObArray m_resultMethodArray;
};




/////////////////////////////////////////////////////////////////////////////
// CVControlCtrl : See VConCtl.cpp for implementation.

class CVControlCtrl : public COleControl
{
	DECLARE_DYNCREATE(CVControlCtrl)

// Constructor
public:
	CVControlCtrl();

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
	~CVControlCtrl();

	DECLARE_OLECREATE_EX(CVControlCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CVControlCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CVControlCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CVControlCtrl)		// Type name and misc status

	// Subclassed control support
	BOOL PreCreateWindow(CREATESTRUCT& cs);
	BOOL IsSubclassedControl();
	LRESULT OnOcmCommand(WPARAM wParam, LPARAM lParam);

	CObArray m_resultsInterfaceArray;
	
	// Interface Verification routines
	void OnVerify();
	void VerifyIOleClientSite( LPUNKNOWN lpIUnknown );
	void VerifyIAdviseSink( LPUNKNOWN lpIUnknown );
	void VerifyIErrorInfo( LPUNKNOWN lpIUnknown );
	void VerifyIOleInPlaceSite( LPUNKNOWN lpIUnknown );
	void VerifyIOleControlSite( LPUNKNOWN lpIUnknown );
	void VerifyIOleInPlaceFrame( LPUNKNOWN lpIUnknown );
	void VerifyIOleContainer( LPUNKNOWN lpIUnknown );
	void VerifyIDispatchAmbients( LPUNKNOWN lpIUnknown );
	void VerifyIDispatchEvents( void );
	void VerifyISimpleFrameSite( LPUNKNOWN lpIUnknown );
	void VerifyIPropertyNotifySink( void );
	void VerifyExtendedControl( void );

	void DeleteResults(void);
	CInterfaceVerificationResult* LogInterfaceResult( BOOL bMandatory, BOOL bSuccess, UINT nDescriptionID, const CString& rstrResult);
	void GetSCodeDescription( HRESULT hresult, CString& strLine );

// Message maps
	//{{AFX_MSG(CVControlCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CVControlCtrl)
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CVControlCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CVControlCtrl)
	//}}AFX_DISP_ID
	};
};
