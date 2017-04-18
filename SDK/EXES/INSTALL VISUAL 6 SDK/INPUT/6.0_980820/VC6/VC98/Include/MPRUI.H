/*++

Copyright (c) 1996, Microsoft Corporation

Module Name:
    mprui.h

Abstract:
    Declarations for the Multi-Protocol router's UI plugin interface.

--*/

// forward declarations
#ifdef _cplusplus
  struct IMprUIHost;
  struct IMprUIPlugin;
#else
  typedef struct IMprUIHost IMprUIHost;
  typedef struct IMprUIPlugin IMprUIPlugin;
#endif

// {73A827F0-FF6E-11cf-AA6B-00805F0C9232}
DEFINE_GUID(IID_IMprUIHost, 
0x73a827f0, 0xff6e, 0x11cf, 0xaa, 0x6b, 0x0, 0x80, 0x5f, 0xc, 0x92, 0x32);

// {73A827F1-FF6E-11cf-AA6B-00805F0C9232}
DEFINE_GUID(IID_IMprUIPlugin, 
0x73a827f1, 0xff6e, 0x11cf, 0xaa, 0x6b, 0x0, 0x80, 0x5f, 0xc, 0x92, 0x32);

#undef INTERFACE
#define INTERFACE IMprUIHost

DECLARE_INTERFACE_(IMprUIHost, IUnknown)
{
  // *** IUnknown methods ***
  STDMETHOD(QueryInterface) (
    THIS_
    REFIID riid,
    LPVOID FAR* ppvObj
    ) PURE;
  
  STDMETHOD_(ULONG,AddRef) (
    THIS
    ) PURE;
  
  STDMETHOD_(ULONG,Release) (
    THIS
    ) PURE;

  // *** IMprUIHost methods ***

  // Create a floating window for the given control
  //  Use CoTaskMemAlloc to allocate pszTitle
  STDMETHOD(FloatWindow) (
    THIS_
    REFCLSID rguidModule,            // CLSID representing the object
    REFCLSID rclsidCtrl,             // CLSID of Ole Control to create
    IMprUIPlugin* pConnection,       // Plugin in node making request
    DWORD dwContext,                 // constant context passed back to Ole Control
    PWCHAR pszTitle                  // Title of floating window
    ) PURE;

  // Force all nodes to be refreshed
  STDMETHOD(GlobalRefresh) (
    THIS
    ) PURE;
};

#undef INTERFACE
#define INTERFACE IMprUIPlugin

DECLARE_INTERFACE_(IMprUIPlugin, IUnknown)
{
  // *** IUnknown methods ***
  STDMETHOD(QueryInterface) (
    THIS_
    REFIID riid,
    LPVOID FAR* ppvObj
    ) PURE;
  
  STDMETHOD_(ULONG,AddRef) (
    THIS
    ) PURE;
  
  STDMETHOD_(ULONG,Release) (
    THIS
    ) PURE;

  // *** IMprUIPlugin Methods ***
  
  // Connect to router.  The plugin module should disconnect from the
  //  router when the IMprUIPlugin is released.
  STDMETHOD(ConnectToRouter) (
    THIS_
    LPCTSTR pRouterName,
    IMprUIHost *pMprUIHost
    ) PURE;

  // Returns the text for the given node.
  //  Use CoTaskMemAlloc to allocate memory for ppszTitle
  STDMETHOD(GetTitle) (
    THIS_
    PWSTR*      ppszTitle
    ) PURE;

  // Returns a context menu for the given node.
  //  Menu will be destroyed by host.
  STDMETHOD(GetContextMenu) (
    THIS_
    HMENU*      phMenu
    ) PURE;

  // Processes the command returned by the context menu
  // There are reserved commands (used to pass down the Hotkeys)
  // such as IDM_HOTKEY_INSERT, IDM_HOTKEY_DELETE, and
  // IDM_HOTKEY_RETURN.  These commands are to be assigned to
  // the appropriate task by the implementor of this interface.
  STDMETHOD(ProcessCommand) (
    THIS_
    WPARAM      wParam,
    LPARAM      lParam,
    HWND        hWndParent
    ) PURE;

  // Returns CLSID for the ole control which displays right hand pane
  //  Use CoTaskMemAlloc to allocate space for CLSID*
  STDMETHOD(GetCLSID) (
    THIS_
    CLSID**     ppClsid
    ) PURE;
};

#define IDM_HOTKEY_INSERT		(1024)
#define IDM_HOTKEY_DELETE		(1025)
#define IDM_HOTKEY_RETURN		(1026)

/* name mangling off */
#ifdef __cplusplus
extern "C" {
#endif

typedef DWORD
(APIENTRY* PFNMPRUITRANSPORTCONFIG)(
    IN      HWND        hwndParent,
    IN      LPCWSTR     pwsMachine,
    IN      DWORD       dwTransportId,
    IN      DWORD       dwReserved
    );

#define MPRUITRANSPORTCONFIG                    MprUITransportConfig
#define SZMPRUITRANSPORTCONFIG                  "MprUITransportConfig"


typedef DWORD
(APIENTRY* PFNMPRUIPROTOCOLCONFIG)(
    IN      HWND        hwndParent,
    IN      LPCWSTR     pwsMachine,
    IN      DWORD       dwTransportId,
    IN      DWORD       dwProtocolId,
    IN      DWORD       dwReserved
    );

#define MPRUIPROTOCOLCONFIG                     MprUIProtocolConfig
#define SZMPRUIPROTOCOLCONFIG                   "MprUIProtocolConfig"



typedef DWORD
(APIENTRY* PFNMPRUITRANSPORTINTERFACECONFIG)(
    IN      HWND        hwndParent,
    IN      LPCWSTR     pwsMachine,
    IN      LPCWSTR     pwsInterface,
    IN      DWORD       dwIfType,
    IN      DWORD       dwTransportId,
    IN      DWORD       dwReserved
    );

#define MPRUITRANSPORTINTERFACECONFIG           MprUITransportInterfaceConfig
#define SZMPRUITRANSPORTINTERFACECONFIG         "MprUITransportInterfaceConfig"



typedef DWORD
(APIENTRY* PFNMPRUIPROTOCOLINTERFACECONFIG)(
    IN      HWND        hwndParent,
    IN      LPCWSTR     pwsMachine,
    IN      LPCWSTR     pwsInterface,
    IN      DWORD       dwIfType,
    IN      DWORD       dwTransportId,
    IN      DWORD       dwProtocolId,
    IN      DWORD       dwReserved
    );

#define MPRUIPROTOCOLINTERFACECONFIG            MprUIProtocolInterfaceConfig
#define SZMPRUIPROTOCOLINTERFACECONFIG          "MprUIProtocolInterfaceConfig"


#ifdef __cplusplus
}
#endif

