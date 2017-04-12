#ifndef _WABAPI_H_
#define _WABAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN16
#ifdef GetLastError
#undef GetLastError
#endif // GetLastError
#endif // WIN16

/* IWABObject Interface ---------------------------------------------------- */

#define CBIWABOBJECT sizeof(IWABOBJECT)


#define WAB_IWABOBJECT_METHODS(IPURE)                       \
        MAPIMETHOD(GetLastError)                            \
            (THIS_  HRESULT hResult,                        \
                    ULONG   ulFlags,                        \
                    LPMAPIERROR FAR * lppMAPIError) IPURE;  \
        MAPIMETHOD(AllocateBuffer)                          \
            (THIS_  ULONG   cbSize,                         \
                    LPVOID FAR *    lppBuffer) IPURE;       \
        MAPIMETHOD(AllocateMore)                            \
            (THIS_  ULONG   cbSize,                         \
                    LPVOID  lpObject,                       \
                    LPVOID  FAR *   lppBuffer) IPURE;       \
        MAPIMETHOD(FreeBuffer)                              \
            (THIS_  LPVOID  lpBuffer) IPURE;                \
        MAPIMETHOD(Backup)                                  \
            (THIS_  LPTSTR  lpFileName) IPURE;              \
        MAPIMETHOD(Import)                                  \
            (THIS_   LPTSTR lpFileName) IPURE;              \
        MAPIMETHOD(Find)                                    \
            (THIS_  LPADRBOOK lpIAB,                        \
                    HWND    hWnd) IPURE;                    \
        MAPIMETHOD(VCardDisplay)                            \
            (THIS_  LPADRBOOK lpIAB,                        \
                    HWND    hWnd,                           \
                    LPTSTR  lpszFileName) IPURE;            \
        MAPIMETHOD(LDAPUrl)                                 \
            (THIS_  LPADRBOOK   lpIAB,                      \
                    HWND        hWnd,                       \
                    ULONG       ulFlags,                    \
                    LPTSTR      lpszURL,                    \
                    LPMAILUSER *lppMailUser) IPURE;         \
        MAPIMETHOD(VCardCreate)                             \
            (THIS_  LPADRBOOK   lpIAB,                      \
                    ULONG       ulFlags,                    \
                    LPTSTR      lpszVCard,                  \
                    LPMAILUSER  lpMailUser) IPURE;          \
        MAPIMETHOD(VCardRetrieve)                           \
            (THIS_  LPADRBOOK   lpIAB,                      \
                    ULONG       ulFlags,                    \
                    LPTSTR      lpszVCard,                  \
                    LPMAILUSER *lppMailUser) IPURE;         \
        MAPIMETHOD(GetMe)                                   \
            (THIS_  LPADRBOOK   lpIAB,                      \
                    ULONG       ulFlags,                    \
                    DWORD *     lpdwAction,                 \
                    SBinary *   lpsbEID,                    \
                    ULONG       ulReserved) IPURE;          \
        MAPIMETHOD(SetMe)                                   \
            (THIS_  LPADRBOOK   lpIAB,                      \
                    ULONG       ulFlags,                    \
                    SBinary     sbEID,                      \
                    ULONG       ulReserved) IPURE;          \



#undef           INTERFACE
#define          INTERFACE      IWABObject
DECLARE_MAPI_INTERFACE_(IWABObject, IUnknown)
{
        BEGIN_INTERFACE
        MAPI_IUNKNOWN_METHODS(PURE)
        WAB_IWABOBJECT_METHODS(PURE)
};

DECLARE_MAPI_INTERFACE_PTR(IWABObject, LPWABOBJECT);


#undef  INTERFACE
#define INTERFACE       struct _IWABOBJECT

#undef  METHOD_PREFIX
#define METHOD_PREFIX   IWABOBJECT_

#undef  LPVTBL_ELEM
#define LPVTBL_ELEM             lpvtbl

#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)       MAPIMETHOD_DECLARE(type, method, IWABOBJECT_)
                MAPI_IUNKNOWN_METHODS(IMPL)
       WAB_IWABOBJECT_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)       MAPIMETHOD_TYPEDEF(type, method, IWABOBJECT_)
                MAPI_IUNKNOWN_METHODS(IMPL)
       WAB_IWABOBJECT_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)       STDMETHOD_(type, method)

DECLARE_MAPI_INTERFACE(IWABOBJECT_)
{
        BEGIN_INTERFACE
        MAPI_IUNKNOWN_METHODS(IMPL)
   WAB_IWABOBJECT_METHODS(IMPL)
};


// WABObject_LDAPUrl flag
// If this flag is specified and the LDAPUrl returns a single
// query result, instructs the WAB to return the result in the
// form of a MailUser object instead of displaying Details on it
// If there are multiple results to the query, fail ..
#define WABOBJECT_LDAPURL_RETURN_MAILUSER   0x00000001


// WABObject_GetMe returned parameter
// If the GetMe call results in the creation of a new 'Me' contact,
// the lpdwAction returned parameter will contain this value
// indicating to the caller that the object is freshly created and
// does not have an properties in it
#define WABOBJECT_ME_NEW                    0x00000001


// IWABObject_VCard Create/Retrieve
// Flags the WAB whether the lpszVCard parameter is a filename or if
// it is a NULL terminated string containing the compelte VCard contents
//
#define WAB_VCARD_FILE                      0x00000000
#define WAB_VCARD_STREAM                    0x00000001

#ifdef WIN16
BOOL WINAPI WABInitThread();
#endif

//
// Input information to pass to WABOpen
//
typedef struct _tagWAB_PARAM
{
    ULONG   cbSize;         // sizeof(WAB_PARAM).
    HWND    hwnd;           // hWnd of calling client Application. Can be NULL
    LPTSTR  szFileName;     // WAB File name to open. if NULL, opens default.
    ULONG   ulFlags;        // Currently no flags.
} WAB_PARAM, * LPWAB_PARAM;

//
// Root public entry points for WAB API
//
STDMETHODIMP WABOpen(LPADRBOOK FAR * lppAdrBook, LPWABOBJECT FAR * lppWABObject,
  LPWAB_PARAM lpWP, DWORD Reserved2);

typedef HRESULT (STDMETHODCALLTYPE WABOPEN)(
    LPADRBOOK FAR * lppAdrBook,
    LPWABOBJECT FAR * lppWABObject,
    LPWAB_PARAM lpWP,
    DWORD Reserved2
);
typedef WABOPEN FAR * LPWABOPEN;


STDMETHODIMP WABOpenEx(LPADRBOOK FAR * lppAdrBook,
  LPWABOBJECT FAR * lppWABObject,
  LPWAB_PARAM lpWP,
  DWORD Reserved,
  ALLOCATEBUFFER * fnAllocateBuffer,
  ALLOCATEMORE * fnAllocateMore,
  FREEBUFFER * fnFreeBuffer);

typedef HRESULT (STDMETHODCALLTYPE WABOPENEX)(
    LPADRBOOK FAR * lppAdrBook,
    LPWABOBJECT FAR * lppWABObject,
    LPWAB_PARAM lpWP,
    DWORD Reserved,
    ALLOCATEBUFFER * fnAllocateBuffer,
    ALLOCATEMORE * fnAllocateMore,
    FREEBUFFER * fnFreeBuffer
);
typedef WABOPENEX FAR * LPWABOPENEX;

#ifndef WIN16
#define WAB_DLL_NAME "WAB32.DLL"
#else
#define WAB_DLL_NAME "WAB16.DLL"
#endif

#define WAB_DLL_PATH_KEY TEXT("Software\\Microsoft\\WAB\\DLLPath")

#ifdef __cplusplus
}
#endif

#endif /* _WABAPI_H */
