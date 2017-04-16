// INotifySrc.h

// {A7B3F570-4E8D-11ce-9EED-00AA004231BF}
DEFINE_GUID(IID_INotifySrc, 
0xa7b3f570, 0x4e8d, 0x11ce, 0x9e, 0xed, 0x0, 0xaa, 0x0, 0x42, 0x31, 0xbf);

class INotifySrc : public IUnknown
{
public:
    // Standard IUnknown interface functions
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,
                                                     LPVOID* ppvObj) = 0;
    virtual ULONG STDMETHODCALLTYPE AddRef(void) = 0;
    virtual ULONG STDMETHODCALLTYPE Release(void) = 0;

    // This interface
    virtual HRESULT STDMETHODCALLTYPE AddUser(INotify* pNotify,
                                              LPVOID pUserInfo) = 0;
    virtual HRESULT STDMETHODCALLTYPE RemoveUser(INotify* pNotify) = 0;
    virtual HRESULT STDMETHODCALLTYPE NotifyAll(void) = 0;
};
