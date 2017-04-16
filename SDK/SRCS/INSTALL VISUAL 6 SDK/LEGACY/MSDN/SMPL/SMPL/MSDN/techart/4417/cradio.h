#ifndef __CRadio_h__
#define __CRadio_h__

class CRadio : 	public CUnknown,
				      public IApplianceUI
{
public:
	// Delegating IUnknown
	DECLARE_IUNKNOWN ; 

	// Called by ClassFactory
	static CUnknown* CreateInstance(IUnknown* pUnk, HRESULT* phr) ;
	
	// Adds Aggregates
	virtual BOOL OnInit() ;

	// Overload To support IApplianceUI
	virtual HRESULT __stdcall NonDelegatingQueryInterface(REFIID riid, void** ppv) ;
	
	// IApplianceUI
    HRESULT __stdcall ShowControl(CWnd* pParent);

protected:
	// Constructor
	CRadio(IUnknown* pUnk, HRESULT* phr) ;

	// Destructor
	virtual ~CRadio() ;

public:
	// Operations
    BOOL IsOn() {return m_bIsOn;}
    int GetStation() {return m_iStation;}
    void Power(BOOL b);
    BOOL SetStation(int iStation);

protected:
	// Member Variables
    BOOL m_bIsOn;
    int m_iStation;
    CMCIObject m_mciTune;
    IUnknown* m_punkBitmap; // aggregated object
} ;

#endif 
