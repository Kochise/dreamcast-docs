
#ifndef __CBitmapObject_H__
#define __CBitmapObject_H__

class CBitmapObject : 	public CUnknown,
				      		public IDrawing,
				      		public IBitmap
{
public:
    // Delegating IUnknown
	DECLARE_IUNKNOWN ; 

	// Create used by ClassFactory...
	static CUnknown* CreateInstance(IUnknown* pUnk, HRESULT* phr) ;

	// Overload To support IDrawing and IBitmap
	virtual HRESULT __stdcall NonDelegatingQueryInterface(REFIID riid, void** ppv) ;
	
	// IDrawing Interface Implementation
    virtual HRESULT __stdcall Draw(CDC* pDC, int x, int y);
    virtual HRESULT __stdcall SetPalette(CPalette* pPal);
    virtual HRESULT __stdcall GetRect(CRect* pRect);

	// IBitmap Interface Implementation
    virtual HRESULT __stdcall LoadResource(WORD wResID);

protected:
	// Constructor
	CBitmapObject(IUnknown* pUnk, HRESULT* phr) ;

    // Destructor
	~CBitmapObject() ; 		

    // member variables
    CDIB m_dibImage;
    WORD m_wResID;
    CPalette* m_pPal;	
} ;

#endif //__CBitmapObject_H__
