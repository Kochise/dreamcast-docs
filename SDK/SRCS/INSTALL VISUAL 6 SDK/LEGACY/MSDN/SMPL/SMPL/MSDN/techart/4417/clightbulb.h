
#ifndef __CLightBulb_H__
#define __CLightBulb_H__

class CLightBulb : 	public CUnknown,
				 	      public IDrawing,
					      public IOutlet
{
public:
	// Delegating IUnknown
	DECLARE_IUNKNOWN ; 

	// Called by ClassFactory
	static CUnknown* CreateInstance(IUnknown* pUnk, HRESULT* phr) ;

	// Overload To support IDrawing and IOutlet
	virtual HRESULT __stdcall NonDelegatingQueryInterface(REFIID riid, void** ppv) ;

	// IDrawing Interface Implementation
    virtual HRESULT __stdcall Draw(CDC* pDC, int x, int y);
    virtual HRESULT __stdcall SetPalette(CPalette* pPal);
    virtual HRESULT __stdcall GetRect(CRect* pRect);

	// IOutlet Interface Implementation
    virtual HRESULT __stdcall On();
    virtual HRESULT __stdcall Off();
    virtual HRESULT __stdcall GetState(BOOL* pState);

protected:
	// Constructor
	CLightBulb(IUnknown* pUnk, HRESULT* phr) ;

	// Destructor
	virtual ~CLightBulb() ;

protected:
    // member variables
    CDIB m_dibImageOn;
    CDIB m_dibImageOff;
    CPalette* m_pPal;
    BOOL m_bIsOn;	
} ;

#endif
