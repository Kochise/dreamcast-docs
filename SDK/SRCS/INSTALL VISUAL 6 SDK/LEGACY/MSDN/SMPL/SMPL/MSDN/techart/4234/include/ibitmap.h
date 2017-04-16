// IBitmap.h

// {C8863020-5408-11ce-9EF1-00AA004231BF}
DEFINE_GUID(IID_IBitmap, 
0xc8863020, 0x5408, 0x11ce, 0x9e, 0xf1, 0x0, 0xaa, 0x0, 0x42, 0x31, 0xbf);

class IBitmap : public IUnknown
{
public:
    // Standard IUnknown interface functions
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,
                                                     LPVOID* ppvObj) = 0;
    virtual ULONG STDMETHODCALLTYPE AddRef(void) = 0;
    virtual ULONG STDMETHODCALLTYPE Release(void) = 0;

    // This interface
    virtual HRESULT STDMETHODCALLTYPE LoadResource(WORD wResID) = 0;
};
