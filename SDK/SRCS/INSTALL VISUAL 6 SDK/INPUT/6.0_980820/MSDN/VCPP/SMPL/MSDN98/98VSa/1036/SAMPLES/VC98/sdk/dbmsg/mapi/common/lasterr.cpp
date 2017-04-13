//
//  LASTERR.CPP
//
// implementation file for CLastError which implements the
// GetLastError helper
//
//  
//
// Copyright (C) 1995 Microsoft Corp.
//

#define STRICT

#include <windows.h>
#include <stdarg.h>
#include <stdio.h>
#include <tchar.h>
#include <ctype.h>
#include <mapix.h>
#include <mapidbg.h>
#include "lasterr.h"

const int       CchMaxErrorMessage = 256;

extern const CHAR FAR  SzNull[] = "";
char szErrUnknown[] = "Error description is not available";

//
// some stuff to put a "Help" button on the error msgbox
//
#if defined(_WIN32)
char szHelpFile[_MAX_PATH];
VOID CALLBACK ErrorBoxCallBack(LPHELPINFO lpHelpInfo);
#endif //_WIN32

static LPSTR aszErrorStrings[] = 
{
    "Not enough memory",
    "Invalid arguments",
    "Invalid object",
    "Interface not supported",
    "Access denied",
    "No support",
    "Wrong character set",
    "Item not found",
    "Call failed",
    "User cancel",
    "Errors returned",
    "Invalid flags",
    "Unexpected error",
    "Can't perform the required action at this time"
};

enum 
{
    IDS_E_OUTOFMEMORY,
    IDS_INVALID_ARGUMENT,
    IDS_INVALID_OBJECT,
    IDS_INTERFACE_NOT_SUPPORTED,
    IDS_ACCESS_DENIED,
    IDS_NOT_SUPPORTED,
    IDS_INVALID_CHARWIDTH,
    IDS_NOT_FOUND,
    IDS_CALL_FAILED,
    IDS_USER_CANCEL,
    IDS_ERRORS_RETURNED,
    IDS_UNKNOWN_FLAGS,
    IDS_UNEXPECTED,
    IDS_CANTNOW
};  

static int iFromHR(HRESULT hr)
{
    switch(GetScode(hr)) {
    case MAPI_E_NOT_ENOUGH_MEMORY:      return IDS_E_OUTOFMEMORY;
    case MAPI_E_INVALID_PARAMETER:      return IDS_INVALID_ARGUMENT;
    case MAPI_E_INVALID_OBJECT:         return IDS_INVALID_OBJECT;
    case MAPI_E_INTERFACE_NOT_SUPPORTED: return IDS_INTERFACE_NOT_SUPPORTED;
    case MAPI_E_NO_ACCESS:              return IDS_ACCESS_DENIED;
    case MAPI_E_NO_SUPPORT:             return IDS_NOT_SUPPORTED;
    case MAPI_E_BAD_CHARWIDTH:          return IDS_INVALID_CHARWIDTH;
    case MAPI_E_NOT_FOUND:              return IDS_NOT_FOUND;
    case MAPI_E_CALL_FAILED:            return IDS_CALL_FAILED;
    case MAPI_E_USER_CANCEL:            return IDS_USER_CANCEL;
    case MAPI_W_ERRORS_RETURNED:        return IDS_ERRORS_RETURNED;
    case MAPI_E_UNKNOWN_FLAGS:          return IDS_UNKNOWN_FLAGS;
    case E_UNEXPECTED:                  return IDS_UNEXPECTED;
    case OLEOBJ_S_CANNOT_DOVERB_NOW:    return IDS_CANTNOW;
    // if it's not in this list you need to add it.
    default:
        DebugTrace("lasterr: bad arg to FORMScodeFromHR");
        Assert(FALSE);
        return 0;
    }
}

HRESULT CLastError::HrSetLastError(HRESULT hr)
{
#if defined(DEBUG)
    //
    //  Ensure that the error string exists -- when we set it not when
    //  they ask for it.
    //

    (void) iFromHR(hr);
#endif

    //
    //  Release any previous error
    //

    if (m_pmapierr != NULL) {
        MAPIFreeBuffer(m_pmapierr);
        m_pmapierr = NULL;
    }

    if (hr) {
        m_eLastErr = eMAPI;
    }
    else {
        m_eLastErr = eNoError;
    }

    return (m_hrLast = hr);
}

HRESULT CLastError::HrSetLastError(HRESULT hr, IUnknown* punk)
{
    Assert(punk && hr);     // we have to have an object and an error.

    m_eLastErr = eObject;
    m_hrLast = hr;

    IMAPIProp* pmprp = (IMAPIProp*)punk;  // I hate this cast but c'est la vie.

    MAPIFreeBuffer(m_pmapierr);     // clean up previous error.
    m_pmapierr = NULL;

    m_hrGLE = pmprp->GetLastError(hr, 0, &m_pmapierr);
    if (m_hrGLE == S_OK) {
        if (m_pmapierr == NULL) {
            if (MAPIAllocateBuffer(sizeof(MAPIERROR), (void **) &m_pmapierr)) {
                m_hrGLE = ResultFromScode(MAPI_E_NOT_ENOUGH_MEMORY);
            }
            else {
                memset(m_pmapierr, 0, sizeof(MAPIERROR));
                m_pmapierr->ulVersion = MAPI_ERROR_VERSION;
                m_pmapierr->lpszError = szErrUnknown;
                m_pmapierr->lpszComponent = (char *) SzNull;
            }
        }
        else if (m_pmapierr->lpszError == NULL) {
            m_pmapierr->lpszError = (char *) SzNull;
        }
        else if (m_pmapierr->lpszComponent == NULL) {
            m_pmapierr->lpszComponent = (char *) SzNull;
        }
    }
    else {
        if (m_pmapierr != NULL) {
            MAPIFreeBuffer(m_pmapierr);
            m_pmapierr = NULL;
        }
    }
    return m_hrLast;
}

HRESULT CLastError::HrGetLastError(HRESULT hr, DWORD dwFlags,
                                   LPMAPIERROR FAR * lppMAPIError)
{
    //
    //  Start with parameter validation
    //

    if (IsBadWritePtr(lppMAPIError, sizeof(LPMAPIERROR))) {
        return HrSetLastError(ResultFromScode(MAPI_E_INVALID_PARAMETER));
    }

    if (MAPI_UNICODE == (dwFlags & MAPI_UNICODE)) {
        return HrSetLastError(ResultFromScode(MAPI_E_BAD_CHARWIDTH));
    }

    //
    //  Is the error asked for the last error registered with us?
    //

    if (hr != m_hrLast) {
        *lppMAPIError = NULL;
        return S_OK;
    }

    int         cch;
    int         cb;
    int         idsError;
    TCHAR*      szMessage = 0;
    TCHAR*      szComponent = 0;
    LPMAPIERROR pmapierr = NULL;

    //
    //  Based on the type of the last error, construct the appropriate
    //  return object
    //

    switch (m_eLastErr) {
    case eMAPI:
        //
        //  The last error registered was a MAPI error code.  For mapi
        //      error codes we map the MAPI error code into a resource
        //      id and return the appropriate string.
        //
        // as to spec, we allocate a single buffer for message and
        //      component.  no one will notice that we aren't doing
        //      MAPIAllocateMore for component.
        //
        //   We make an assumption as to the maximum possible length
        //      of the two strings combined.
        //

        Assert(m_pmapierr == NULL);
        if (MAPIAllocateBuffer(CchMaxErrorMessage*sizeof(TCHAR)+sizeof(MAPIERROR),
                               (void**)&pmapierr)) {
            return ResultFromScode(MAPI_E_NOT_ENOUGH_MEMORY);
        }

        //
        //  Set the version number
        //

        pmapierr->ulVersion = MAPI_ERROR_VERSION;
        pmapierr->ulLowLevelError = 0;

        //
        //   do the maping from the MAPI error code into a FORM string
        //      value.  The FORM eror code code will be set as the low
        //      level error value.
        //

        idsError = iFromHR(m_hrLast);
        pmapierr->ulContext = idsError;

        //
        //  Set the error string pointer to the appropriate location
        //      in the error buffer and load the error string.
        //

        pmapierr->lpszError = (LPTSTR) (sizeof(MAPIERROR) +
                                          (BYTE *) pmapierr);

        lstrcpy(pmapierr->lpszError, aszErrorStrings[idsError]);
        cch = lstrlen(aszErrorStrings[idsError]);
        
        
        //
        // Set the componment string pointer to the appropriate location
        //      in the error buffer and load the component string.
        //

        pmapierr->lpszComponent = pmapierr->lpszError + cch + 1;
        cch = CchMaxErrorMessage - cch - 1;

        lstrcpy(pmapierr->lpszComponent,
                        m_szComponent ? m_szComponent : SzNull);
        cch = lstrlen(pmapierr->lpszComponent);
        
        if (cch == 0) {
            *(pmapierr->lpszComponent) = 0;
        }

        break;


    case eObject:
        //
        //  The last regisered error message came from an object.  If we
        //      could not get the last error from the object, just return
        //      the error it returned and we are done.
        //

        if (m_hrGLE != NOERROR) {
            Assert( m_pmapierr == NULL );
            *lppMAPIError = NULL;
            return m_hrGLE;
        }

    case eExtended:
        //
        //  The last error was an extended error.  The error is in the
        //      structure, we need to copy this structure and return
        //      it back to the user
        //

        Assert( m_pmapierr != NULL );
        cb = lstrlen(m_pmapierr->lpszError) + lstrlen(m_pmapierr->lpszComponent);

        if (MAPIAllocateBuffer(cb + 2 + sizeof(MAPIERROR),
                               (void **) &pmapierr)) {
            return ResultFromScode(MAPI_E_NOT_ENOUGH_MEMORY);
        }

        *pmapierr = *m_pmapierr;
        pmapierr->lpszError = (LPTSTR) (sizeof(MAPIERROR) + (BYTE *) pmapierr);
        lstrcpy(pmapierr->lpszError, m_pmapierr->lpszError);
        pmapierr->lpszComponent = pmapierr->lpszError +
          lstrlen(pmapierr->lpszError) + 1;
        lstrcpy(pmapierr->lpszComponent, m_pmapierr->lpszComponent);

        break;

    case eNoError:
        break;

    default:
        Assert(0);
        return NOERROR;
    }

    *lppMAPIError = pmapierr;
    return ResultFromScode(S_OK);
}



int CLastError::ShowError(HWND hWnd)
{
    char szMessage[512];
    char szbuf[256];

    if(m_eLastErr != eObject || NULL == m_pmapierr) return 0;

    wsprintf(szMessage, "%s\n%s\nLowLevelError: 0x%08lx context: %ld ",
                        (m_pmapierr->lpszError ? m_pmapierr->lpszError:""),
                        m_pmapierr->lpszComponent ? m_pmapierr->lpszComponent:"",
                        m_pmapierr->ulLowLevelError, m_pmapierr->ulContext);
   
    wsprintf (szbuf, "\nReturn Code: 0x%08lx", SCODE(m_hrLast));
    lstrcat (szMessage, szbuf);
    
#if defined (_WIN32)
    *szHelpFile = '\0';

    int iret;
    BOOL fCanHelp;

    if(m_pmapierr->lpszError  &&  m_pmapierr->ulContext)
        fCanHelp = TRUE;
    else
        fCanHelp = FALSE;
        
    if(fCanHelp)
    {
        DWORD dw = GetPrivateProfileString("Help File Mappings", m_pmapierr->lpszComponent,
                            "", szHelpFile, _MAX_PATH, "mapisvc.inf");
        if(0 == dw)
            fCanHelp = FALSE;

        if(fCanHelp)
        {
            MSGBOXPARAMS mbp = {0};

            mbp.cbSize = sizeof(MSGBOXPARAMS);
            mbp.hwndOwner = hWnd;
            mbp.hInstance = NULL;
            mbp.lpszText = szMessage;
            mbp.lpszCaption = m_szComponent ? m_szComponent : "Error!";
            mbp.dwStyle = MB_ICONSTOP | MB_OK | MB_HELP;
            mbp.lpszIcon = NULL;
            mbp.dwContextHelpId = m_pmapierr->ulContext;
            mbp.lpfnMsgBoxCallback = ErrorBoxCallBack;
            mbp.dwLanguageId = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);

            iret = MessageBoxIndirect(&mbp);
        }
        
    }

    
    if(!fCanHelp)
        iret = MessageBox (hWnd, szMessage,
                    m_szComponent ? m_szComponent : "Error!",
                        MB_ICONSTOP | MB_OK );

    *szHelpFile = '\0';

    return iret;

#else
    return MessageBox (hWnd, szMessage,
                     m_szComponent ? m_szComponent : "Error!",
                         MB_ICONSTOP | MB_OK );
#endif
}

#if defined(_WIN32)
VOID CALLBACK ErrorBoxCallBack(LPHELPINFO lpHelpInfo)
{
    Assert(*szHelpFile != '\0');

    WinHelp(NULL, szHelpFile, HELP_CONTEXT,
            lpHelpInfo->dwContextId);
}
#endif //_WIN32


