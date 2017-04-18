// IDrawing.h

// {15038B10-3D3E-11ce-9EE5-00AA004231BF}
DEFINE_GUID(IID_IDrawing, 
0x15038b10, 0x3d3e, 0x11ce, 0x9e, 0xe5, 0x0, 0xaa, 0x0, 0x42, 0x31, 0xbf);

class IDrawing : public IUnknown
{
public:
    // Standard IUnknown interface functions
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,
                                                     LPVOID* ppvObj) = 0;
    virtual ULONG STDMETHODCALLTYPE AddRef(void) = 0;
    virtual ULONG STDMETHODCALLTYPE Release(void) = 0;

    // This interface
    virtual HRESULT STDMETHODCALLTYPE Draw(HDC hDC,
                                           int x,
                                           int y) = 0;
    virtual HRESULT STDMETHODCALLTYPE SetPalette(HPALETTE hPal) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetRect(RECT* pRect) = 0;
};
