// ILight.h

// {C91E0930-4386-11ce-9EE8-00AA004231BF}
DEFINE_GUID(IID_ILight, 
0xc91e0930, 0x4386, 0x11ce, 0x9e, 0xe8, 0x0, 0xaa, 0x0, 0x42, 0x31, 0xbf);

class ILight : public IUnknown
{
public:
    // Standard IUnknown interface functions
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,
                                                     LPVOID* ppvObj) = 0;
    virtual ULONG STDMETHODCALLTYPE AddRef(void) = 0;
    virtual ULONG STDMETHODCALLTYPE Release(void) = 0;

    // This interface
    virtual HRESULT STDMETHODCALLTYPE SetBrightness(BYTE bLevel) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetBrightness(BYTE* pLevel) = 0;
};
