// IApplianceUI.h

// {3087F4A0-4387-11ce-9EE8-00AA004231BF}
DEFINE_GUID(IID_IApplianceUI, 
0x3087f4a0, 0x4387, 0x11ce, 0x9e, 0xe8, 0x0, 0xaa, 0x0, 0x42, 0x31, 0xbf);

class IApplianceUI : public IUnknown
{
public:
    // Standard IUnknown interface functions
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,
                                                     LPVOID* ppvObj) = 0;
    virtual ULONG STDMETHODCALLTYPE AddRef(void) = 0;
    virtual ULONG STDMETHODCALLTYPE Release(void) = 0;

    // This interface
    virtual HRESULT STDMETHODCALLTYPE ShowControl(CWnd* pParent) = 0;
};
