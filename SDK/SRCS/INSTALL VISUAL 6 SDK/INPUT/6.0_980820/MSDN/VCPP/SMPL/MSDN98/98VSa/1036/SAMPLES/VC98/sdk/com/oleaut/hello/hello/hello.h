#ifdef WIN32

#ifdef UNICODE
    #define FROM_OLE_STRING(str) str
    #define TO_OLE_STRING(str) str 
#else
    #define FROM_OLE_STRING(str) ConvertToAnsi(str)
    char* ConvertToAnsi(OLECHAR FAR* szW);  
    #define TO_OLE_STRING(str) ConvertToUnicode(str)
    OLECHAR* ConvertToUnicode(char FAR* szA);   
    // Maximum length of string that can be converted between Ansi & Unicode
    #define STRCONVERT_MAXLEN 300         
#endif

#else  // WIN16
  #define APIENTRY far pascal  
  #define TCHAR char
  #define TEXT(sz) sz 
  #define FROM_OLE_STRING(str) str  
  #define TO_OLE_STRING(str) str  
  #define LPTSTR LPSTR
  
  // Windows NT defines the following in windowsx.h
  #define GET_WM_COMMAND_ID(w,l) (w)
  #define GET_WM_COMMAND_CMD(w,l) HIWORD(l)
  #define GET_WM_COMMAND_HWND(w,l) LOWORD(l)
#endif

#undef STRICT
#define STRICT

// Resource IDs
#define IDD_MAINWINDOW   101 
#define IDI_ICON         102

// Child window IDs
#define IDC_HELLODISPLAY 101  
#define IDC_SAYHELLO     102

// MAX len of string table entries
#define STR_LEN   100

// String table constants
#define IDS_Name                 1  
#define IDS_HelloMessage         2     
#define IDS_ErrorLoadingTypeLib  3
#define IDS_SayHello             4
#define IDS_ProgID               5
#define IDS_Unexpected           1001

// SCODEs for the Hello Application. This is required for vtable-binding
// Automation objects want to return custom HRESULTs. All the OLE-defined 
// FACILITY_ITF codes have a code value which lies in the region 0x0000-0x01FFF.
// While it is legal for the definer to use any code, it is highly recommended
// that only code values in the range 0x0200-0xFFFF be used, as this will reduce the
// possiblity of accidental confusion with any OLE-defined errors.
#define HELLO_E_FIRST       MAKE_SCODE(SEVERITY_ERROR, FACILITY_ITF, 0x0200)  

#define HELLO_E_UNEXPECTED  (HELLO_E_FIRST + 0x0) 
// Unexpected error   

// Number of SCODEs
#define SCODE_COUNT 1 

// Function prototypes
int APIENTRY WinMain (HINSTANCE, HINSTANCE, LPSTR, int);
BOOL InitApplication (HINSTANCE);
BOOL InitInstance (HINSTANCE);
BOOL ProcessCmdLine(LPSTR lpCmdLine, LPDWORD pdwRegisterCF, LPDWORD pdwRegisterActiveObject, int nCmdShow);
void Uninitialize(DWORD dwRegisterCF, DWORD dwRegisterActiveObject);                 
HRESULT LoadTypeInfo(ITypeInfo FAR* FAR* pptinfo, REFCLSID clsid);
HRESULT RaiseException(int nID, REFGUID rguid);
#ifdef WIN16
extern "C" LRESULT __export CALLBACK MainWndProc (HWND, UINT, WPARAM, LPARAM);  
#else 
extern "C" LRESULT CALLBACK MainWndProc (HWND, UINT, WPARAM, LPARAM);  
#endif 

#include "tlb.h"

// ISupportErrorInfo interface implementation
interface CSupportErrorInfo : public ISupportErrorInfo 
{
public:
    // IUnknown methods 
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR* ppvObj);
    STDMETHOD_(ULONG, AddRef)(void);
    STDMETHOD_(ULONG, Release)(void); 
    
    // ISupportErrorInfo method
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);  
     
    CSupportErrorInfo(IUnknown FAR* punkObject, REFIID riid); 
private:
    LPUNKNOWN m_punkObject;  // IUnknown of Object that implements this interface 
    GUID m_iid;
};     

class FAR CHello : public IHello
{
public:
    // IUnknown methods 
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR* ppvObj);
    STDMETHOD_(ULONG, AddRef)(void);
    STDMETHOD_(ULONG, Release)(void);
    
    // IDispatch methods 
    STDMETHOD(GetTypeInfoCount)(UINT FAR* pctinfo);
    STDMETHOD(GetTypeInfo)(
      UINT itinfo,
      LCID lcid,
      ITypeInfo FAR* FAR* pptinfo);
    STDMETHOD(GetIDsOfNames)(
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid);
    STDMETHOD(Invoke)(
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      DISPPARAMS FAR* pdispparams,
      VARIANT FAR* pvarResult,
      EXCEPINFO FAR* pexcepinfo,
      UINT FAR* puArgErr);
    
    // IHello methods   
    STDMETHOD(get_Application)(IHello FAR* FAR* ppHello);
    STDMETHOD(get_FullName)(BSTR FAR* pbstr);
    STDMETHOD(get_Name)(BSTR FAR* pbstr);
    STDMETHOD(get_Parent)(IHello FAR* FAR* ppHello);
    STDMETHOD(put_Visible)(VARIANT_BOOL bVisible);
    STDMETHOD(get_Visible)(VARIANT_BOOL FAR* pbool);
    STDMETHOD(Quit)();
    STDMETHOD(put_HelloMessage)(BSTR bstrMessage);
    STDMETHOD(get_HelloMessage)(BSTR FAR* pbstrMessage);
    STDMETHOD(SayHello)();  
    
    // CHello methods   
    STDMETHOD_(void, ShowWindow)(int nCmdShow);
    static HRESULT Create(HINSTANCE hinst, LPTSTR lpszHelloMessage, CHello FAR* FAR* pphello); // Creates and intializes Hello object    
    CHello();
    ~CHello();

public:
    HWND m_hwnd;                   // Application window.     
    HINSTANCE m_hinst;             // Hinstance of application. 
    BSTR m_bstrName;               // Name of application.
    BSTR m_bstrProgID;             // ProgID of application.
     
private:
    LPTYPEINFO m_ptinfo;           // Type information of Hello application interface.
    BSTR m_bstrHelloMsg;           // Hello message
    BSTR m_bstrFullName;           // Full name of application.
    BOOL m_bVisible;               // Is window visible?
    ULONG m_cRef;                  // Reference count   
    CSupportErrorInfo m_SupportErrorInfo; // ISupportErrorInfo interface implementation 
};

class FAR CHelloCF : public IClassFactory
{
public:
    // IUnknown methods 
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR* ppvObj);
    STDMETHOD_(ULONG, AddRef)(void);
    STDMETHOD_(ULONG, Release)(void); 
    
    // IClassFactory methods
    STDMETHOD(CreateInstance)(IUnknown FAR* punkOuter, REFIID riid, 
                              void FAR* FAR* ppv);
    STDMETHOD(LockServer)(BOOL fLock);    
    
    CHelloCF();
    
private:
    ULONG m_cRef;                   // Reference count
};

extern CHello FAR* g_phello;     


     
                                             
