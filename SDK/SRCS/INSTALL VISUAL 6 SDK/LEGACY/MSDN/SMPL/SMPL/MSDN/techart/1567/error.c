/*
    error.c

    Some error handling stuff

*/

#include "global.h"

typedef struct _ERRINFO {
    SCODE scode;
    LPSTR szDescription;
} ERRINFO, FAR *PERRINFO;

ERRINFO errinfo[] = {
    E_UNEXPECTED,                   "relatively catastrophic failure",
    E_NOTIMPL,                      "not implemented",
    E_OUTOFMEMORY,                  "ran out of memory",
    E_INVALIDARG,                   "one or more arguments are invalid",
    E_NOINTERFACE,                  "no such interface supported",
    E_POINTER,                      "invalid pointer",
    E_HANDLE,                       "invalid handle",
    E_ABORT,                        "operation aborted",
    E_FAIL,                         "unspecified error",
    E_ACCESSDENIED,                 "general access denied error",

    CLIPBRD_E_CANT_OPEN,            "CLIPBRD_E_CANT_OPEN", 
    CLIPBRD_E_CANT_EMPTY,           "CLIPBRD_E_CANT_EMPTY",
    CLIPBRD_E_CANT_SET,             "CLIPBRD_E_CANT_SET",  
    CLIPBRD_E_BAD_DATA,             "CLIPBRD_E_BAD_DATA",  
    CLIPBRD_E_CANT_CLOSE,           "CLIPBRD_E_CANT_CLOSE",

    OLE_E_OLEVERB,                  "invalid OLEVERB structure  ",
    OLE_E_ADVF,                     "invalid advise flags",
    OLE_E_ENUM_NOMORE,              "you can't enuemrate any more, because the associated data is missing",
    OLE_E_ADVISENOTSUPPORTED,       "this implementation doesn't take advises",
    OLE_E_NOCONNECTION,             "there is no connection for this connection id",
    OLE_E_NOTRUNNING,               "need run the object to perform this operation",
    OLE_E_NOCACHE,                  "there is no cache to operate on",
    OLE_E_BLANK,                    "Uninitialized object",
    OLE_E_CLASSDIFF,                "linked object's source class has changed ",
    OLE_E_CANT_GETMONIKER,          "not able to get the moniker of the object",
    OLE_E_CANT_BINDTOSOURCE,        "not able to bind to the source",
    OLE_E_STATIC,                   "object is static, operation not allowed",
    OLE_E_PROMPTSAVECANCELLED,      "user cancelled out of save dialog",
    OLE_E_INVALIDRECT,              "invalid rectangle ",
    OLE_E_WRONGCOMPOBJ,             "compobj.dll is too old for the ole2.dll initialized",
    OLE_E_INVALIDHWND,              "invalid window handle",
    OLE_E_NOT_INPLACEACTIVE,        "object is not in any of the inplace active states  ",
    DV_E_FORMATETC,                 "invalid FORMATETC structure",
    DV_E_DVTARGETDEVICE,            "invalid DVTARGETDEVICE structure",
    DV_E_STGMEDIUM,                 "invalid STDGMEDIUM structure",
    DV_E_STATDATA,                  "invalid STATDATA structure",
    DV_E_LINDEX,                    "invalid lindex",
    DV_E_TYMED,                     "invalid tymed",
    DV_E_CLIPFORMAT,                "invalid clipboard format",
    DV_E_DVASPECT,                  "invalid aspect(s) ",
    DV_E_DVTARGETDEVICE_SIZE,       "tdSize paramter of the DVTARGETDEVICE structure is invalid",
    DV_E_NOIVIEWOBJECT,             "object doesn't support IViewObject interface",

    STG_E_INVALIDFUNCTION,          "INVALIDFUNCTION",    
    STG_E_FILENOTFOUND,             "FILENOTFOUND",        
    STG_E_PATHNOTFOUND,             "PATHNOTFOUND",
    STG_E_TOOMANYOPENFILES,         "TOOMANYOPENFILES",
    STG_E_ACCESSDENIED,             "ACCESSDENIED",
    STG_E_INVALIDHANDLE,            "INVALIDHANDLE",
    STG_E_INSUFFICIENTMEMORY,       "INSUFFICIENTMEMORY",
    STG_E_INVALIDPOINTER,           "INVALIDPOINTER",
    STG_E_NOMOREFILES,              "NOMOREFILES",
    STG_E_DISKISWRITEPROTECTED,     "DISKISWRITEPROTECTED",
    STG_E_SEEKERROR,                "SEEKERROR",
    STG_E_WRITEFAULT,               "WRITEFAULT",
    STG_E_READFAULT,                "READFAULT",
    STG_E_LOCKVIOLATION,            "LOCKVIOLATION",
    STG_E_FILEALREADYEXISTS,        "FILEALREADYEXISTS",
    STG_E_INVALIDPARAMETER,         "INVALIDPARAMETER",
    STG_E_MEDIUMFULL,               "MEDIUMFULL",
    STG_E_ABNORMALAPIEXIT,          "ABNORMALAPIEXIT",
    STG_E_INVALIDHEADER,            "INVALIDHEADER",
    STG_E_INVALIDNAME,              "INVALIDNAME",
    STG_E_UNKNOWN,                  "UNKNOWN",
    STG_E_UNIMPLEMENTEDFUNCTION,    "UNIMPLEMENTEDFUNCTION",
    STG_E_INVALIDFLAG,              "INVALIDFLAG",          
    STG_E_INUSE,                    "INUSE",
    STG_E_NOTCURRENT,               "NOTCURRENT",
    STG_E_REVERTED,                 "REVERTED",
    STG_E_CANTSAVE,                 "CANTSAVE",
    STG_E_OLDFORMAT,                "OLDFORMAT",
    STG_E_OLDDLL,                   "OLDDLL",
    STG_E_SHAREREQUIRED,            "SHAREREQUIRED",
    STG_S_CONVERTED,                "CONVERTED",
    STG_S_BUFFEROVERFLOW,           "BUFFEROVERFLOW",
    STG_S_TRYOVERWRITE,             "TRYOVERWRITE",
    NULL, NULL};


//
// test an hResult to see if it's ok.  Returns true if no
// error and false if there is.  Shows error info in debug window
//


BOOL MyTestOleResult(HRESULT hResult)
{
    SCODE scode;
    DWORD dwFacility;
    DWORD dwCode;
    LPSTR pszFacility;
    PERRINFO pEI;

    if (! FAILED(hResult)) {
        return TRUE;
    }

    scode = GetScode(hResult);
    dwFacility = SCODE_FACILITY(scode);
    dwCode = SCODE_CODE(scode);

    switch (dwFacility) {
    case FACILITY_NULL:
        pszFacility = "NULL";
        break;    
    case FACILITY_RPC:    
        pszFacility = "RPC";
        break;    
    case FACILITY_DISPATCH:
        pszFacility = "DISPATCH";
        break;    
    case FACILITY_STORAGE:
        pszFacility = "STORAGE";
        break;    
    case FACILITY_ITF:    
        pszFacility = "ITF";
        break;    
    default:
        pszFacility = "(???)";
        break;    
    }

    //
    // try to find it
    //

    pEI = errinfo;
    while (pEI->scode) {
        if (pEI->scode == scode) break;
        pEI++;
    }

    if (pEI->szDescription) {
        dprintf1("OLE %s error: '%s'", pszFacility, pEI->szDescription);
    } else {
        dprintf1("OLE %s error: %4.4XH", pszFacility, LOWORD(dwCode));
    }
    return FALSE;
}
