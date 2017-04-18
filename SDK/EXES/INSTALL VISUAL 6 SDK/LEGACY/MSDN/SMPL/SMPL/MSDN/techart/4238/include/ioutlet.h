// IOutlet.h

// {6F1C2CE0-4386-11ce-9EE8-00AA004231BF}
DEFINE_GUID(IID_IOutlet, 
0x6f1c2ce0, 0x4386, 0x11ce, 0x9e, 0xe8, 0x0, 0xaa, 0x0, 0x42, 0x31, 0xbf);

class IOutlet : public IUnknown
{
public:
    // Standard IUnknown interface functions
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,
                                                     LPVOID* ppvObj) = 0;
    virtual ULONG STDMETHODCALLTYPE AddRef(void) = 0;
    virtual ULONG STDMETHODCALLTYPE Release(void) = 0;

    // This interface
    virtual HRESULT STDMETHODCALLTYPE On(void) = 0;
    virtual HRESULT STDMETHODCALLTYPE Off(void) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetState(BOOL* pState) = 0;
};
