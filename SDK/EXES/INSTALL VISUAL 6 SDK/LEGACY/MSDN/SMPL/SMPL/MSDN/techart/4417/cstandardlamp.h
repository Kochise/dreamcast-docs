#ifndef __CStandardLamp_h__
#define __CStandardLamp_h__

class CStandardLamp : 	public CUnknown,
						public IDrawing,
						public IOutlet,
						public ILight
{
public:
	// Delegating IUnknown
	DECLARE_IUNKNOWN ; 

	// Called by ClassFactory
	static CUnknown* CreateInstance(IUnknown* pUnk, HRESULT* phr) ;

	// Adds Aggregates
	virtual BOOL OnInit() ;

	// Overload To support IDrawing, ILight and IOutlet
	virtual HRESULT __stdcall NonDelegatingQueryInterface(REFIID riid, void** ppv) ;

	// IDrawing Interface Implementation
    virtual HRESULT __stdcall Draw(CDC* pDC, int x, int y);
    virtual HRESULT __stdcall SetPalette(CPalette* pPal);
    virtual HRESULT __stdcall GetRect(CRect* pRect);

	// IOutlet Interface Implementation
    virtual HRESULT __stdcall On();
    virtual HRESULT __stdcall Off();
    virtual HRESULT __stdcall GetState(BOOL* pState);

	// ILight Interface Implementation
	virtual HRESULT __stdcall CStandardLamp::SetBrightness(BYTE bLevel)	;
	virtual HRESULT __stdcall CStandardLamp::GetBrightness(BYTE* pLevel) ;

protected:
	// Constructor
	CStandardLamp(IUnknown* pUnk, HRESULT* phr) ;

	// Destructor
	virtual ~CStandardLamp() ;

protected:
    // member variables
    CDIB m_dibImageOff;
    CDIB m_dibImageDim;
    CDIB m_dibImageBright;
    CPalette* m_pPal;
    BYTE m_bLevel;

    // Notification list
    IUnknown* m_punkNotifyList;
    INotifySrc* m_pINotifySrc; // cached ptr 

    // helpers
    void NotifyChange();

} ;

#endif
