#ifndef __CTelevision_h__
#define __CTelevision_h__

class CTelevision : 	public CUnknown,
				 		public IDrawing,
						public IApplianceUI
{
public:
	// Delegating IUnknown
	DECLARE_IUNKNOWN ; 

	// Called by ClassFactory
	static CUnknown* CreateInstance(IUnknown* pUnk, HRESULT* phr) ;

	// Overload To support IDrawing and IApplianceUI
	virtual HRESULT __stdcall NonDelegatingQueryInterface(REFIID riid, void** ppv) ;

	// IDrawingUI
    STDMETHOD(Draw)(CDC* pDC,int x, int y);
    STDMETHOD(SetPalette)(CPalette* pPal);
    STDMETHOD(GetRect)(CRect* pRect);
		
	// IApplianceUI
    HRESULT __stdcall ShowControl(CWnd* pParent);

protected:
	// Constructor
	CTelevision(IUnknown* pUnk, HRESULT* phr) ;

	// Destructor
	virtual ~CTelevision() ;

public:
	// Operations
    BOOL IsOn() {return m_bIsOn;}
    BOOL Power(BOOL b);

protected:
	// Member Variables
    CDIB m_dibImage;
    CPalette* m_pPal;
    BOOL m_bIsOn;
} ;

#endif
