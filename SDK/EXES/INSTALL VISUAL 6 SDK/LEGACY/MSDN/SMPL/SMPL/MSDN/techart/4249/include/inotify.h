// INotify.h

// {53AD5A20-4E6D-11ce-9EED-00AA004231BF}
DEFINE_GUID(IID_INotify, 
0x53ad5a20, 0x4e6d, 0x11ce, 0x9e, 0xed, 0x0, 0xaa, 0x0, 0x42, 0x31, 0xbf);

class INotify : public IUnknown
{
public:
    // Standard IUnknown interface functions
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,
                                                     LPVOID* ppvObj) = 0;
    virtual ULONG STDMETHODCALLTYPE AddRef(void) = 0;
    virtual ULONG STDMETHODCALLTYPE Release(void) = 0;

    // This interface
    virtual HRESULT STDMETHODCALLTYPE Change(LPVOID pUserInfo) = 0;
};
