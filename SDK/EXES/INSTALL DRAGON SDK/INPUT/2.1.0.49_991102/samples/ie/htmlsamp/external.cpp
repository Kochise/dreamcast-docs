/********************************************************************
 * external.cpp
 *
 * Description
 *     Wrappers for external functions in mshtml.dll, urlmon.dll, and
 *     vmimime.dll
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "headers.h"            // common headers
#include <mshtml.h>             // for mshtml
#include <mshtmhst.h>           // for mshtml
#include "external.h"           // wrapper prototypes

/********************************************************************
 * Global variables
 ********************************************************************/
HINSTANCE g_hInstMSHTML  = NULL;        // mshtml.dll instance
HINSTANCE g_hInstURLMON  = NULL;        // urlmon.dll instance
HINSTANCE g_hInstVMIMIME = NULL;        // vmimime.dll instance
HINSTANCE g_hInstRESHELP = NULL;        // reshelp.dll instance

/********************************************************************
 * Typedefs for external functions
 ********************************************************************/
typedef HRESULT (STDAPICALLTYPE *PFNREGISTERHTMLDIALOGCALLBACK)(PFNHTMLDIALOGCALLBACK pHTMLDialogCallback, ULONG ulData, ULONG *pulCookie);
typedef HRESULT (STDAPICALLTYPE *PFNUNREGISTERHTMLDIALOGCALLBACK)(ULONG ulCookie);
typedef HRESULT (STDAPICALLTYPE *PFNGETCURRENTFOCUSELEMENT)(IHTMLDocument2 *pHTMLDocument2, IHTMLElement **ppHTMLElement);
typedef HRESULT (STDAPICALLTYPE *PFNCREATEURLMONIKER)(IMoniker *pmkContext, LPWSTR pszURL, IMoniker **ppMoniker);
typedef HRESULT (STDAPICALLTYPE *PFNSETSHOWVMUMESSAGECALLBACK)(PFNSHOWVMUMESSAGECALLBACK pShowVMUMessage);
typedef HRESULT (STDAPICALLTYPE *PFNSETGETVMUDEVICECALLBACK)(PFNGETVMUDEVICECALLBACK pGetVMUDevice);

/********************************************************************
 * LoadDLLs
 *
 * Description
 *    Load all of the DLLs that we will be commonly using. reshelp.dll
 *    does not have any functions that will be used, but since it is
 *    often used for HTML pages, the pages will access quicker if it 
 *    is in memory.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    S_OK     sucessfully loaded all DLLs
 *    S_FALSE  did not load all DLLs
 ********************************************************************/
HRESULT LoadDLLs(void)
{
    // if any have already been loaded, there is no point in trying
    // again for the others
    if (g_hInstMSHTML || g_hInstURLMON || g_hInstVMIMIME || 
        g_hInstRESHELP)
    {
        return S_FALSE;
    }

    // load all the DLLs
    g_hInstMSHTML  = LoadLibrary(TEXT("mshtml.dll"));
    g_hInstURLMON  = LoadLibrary(TEXT("urlmon.dll"));
    g_hInstVMIMIME = LoadLibrary(TEXT("vmimime.dll"));
    g_hInstRESHELP = LoadLibrary(TEXT("reshelp.dll"));

    // return status of loaded DLLs
    return (g_hInstMSHTML && g_hInstURLMON  && g_hInstVMIMIME && 
            g_hInstRESHELP) ? S_OK : S_FALSE;
}

/********************************************************************
 * FreeDLLs
 *
 * Description
 *    Unload all of the DLLs that we have been using. 
 *
 * Parameters
 *    None
 * 
 * Returns
 *    S_OK     sucessfully unloaded all loaded DLLs
 ********************************************************************/
HRESULT FreeDLLs(void)
{
    // free all loaded libraries
    if (g_hInstMSHTML)
    {
       FreeLibrary(g_hInstMSHTML);
       g_hInstMSHTML = NULL;
    }
    
    if (g_hInstURLMON)
    {
        FreeLibrary(g_hInstURLMON);
        g_hInstURLMON = NULL;
    }    

    if (g_hInstVMIMIME)
    {
        FreeLibrary(g_hInstVMIMIME);
        g_hInstVMIMIME = NULL;
    }

    if (g_hInstRESHELP)
    {
        FreeLibrary(g_hInstRESHELP);
        g_hInstRESHELP = NULL;
    }

    return S_OK;
}

/********************************************************************
 * RegisterHTMLDialogCallback (mshtml.dll)
 *
 * Description
 *    Registers a call back function in mshtml. The call back will
 *    be called whenever an HTML dialog is created or destroyed and
 *    from within the message loop of the modal HTML dialog. See
 *    HTML control documentation. There can be multiple call back
 *    functions active at a time. This function is only available
 *    for Dreamcast version of the HTML control.
 * 
 * Parameters
 *    pfnHTMLDialogCallback     call back function
 *    ulData                    user data that will be passed to 
 *                              call back function
 *    pulCookie                 filled with cookie value for 
 *                              unregistering call back function
 * 
 * Returns
 *    See HTML control documentation
 ********************************************************************/
HRESULT RegisterHTMLDialogCallback(PFNHTMLDIALOGCALLBACK pfnHTMLDialogCallback, 
                                   ULONG ulData, ULONG *pulCookie)
{
    // verify DLL has been loaded
    if (!g_hInstMSHTML)
    {
        return E_FAIL;
    }

    // get the mshtml function address
    PFNREGISTERHTMLDIALOGCALLBACK pRegisterHTMLDialogCallback = 
        (PFNREGISTERHTMLDIALOGCALLBACK)GetProcAddress(g_hInstMSHTML, 
        TEXT("RegisterHTMLDialogCallback"));

    if (!pRegisterHTMLDialogCallback)
    {
        return E_FAIL;
    }

    // call the mshtml function
    return (*pRegisterHTMLDialogCallback)(pfnHTMLDialogCallback, 
                                          ulData, pulCookie);
}

/********************************************************************
 * UnRegisterHTMLDialogCallback (mshtml.dll)
 *
 * Description
 *    Unregisters a call back function in mshtml. The call back will
 *    no longer be called for HTML dialogs. See HTML control 
 *    documentation. This function is only available for Dreamcast 
 *    version of the HTML control.
 * 
 * Parameters
 *    ulCookie  cookie received when registering the call back function
 * 
 * Returns
 *    See HTML control documentation
 ********************************************************************/
HRESULT UnRegisterHTMLDialogCallback(ULONG ulCookie)
{
    // verify DLL has been loaded
    if (!g_hInstMSHTML)
    {
        return E_FAIL;
    }

    // get the mshtml function address
    PFNUNREGISTERHTMLDIALOGCALLBACK pUnRegisterHTMLDialogCallback = 
        (PFNUNREGISTERHTMLDIALOGCALLBACK)GetProcAddress(g_hInstMSHTML, 
        TEXT("UnRegisterHTMLDialogCallback"));

    if (!pUnRegisterHTMLDialogCallback)
    {
        return E_FAIL;
    }

    // call the mshtml function
    return (*pUnRegisterHTMLDialogCallback)(ulCookie);
}

/********************************************************************
 * GetCurrentFocusElement (mshtml.dll)
 *
 * Description
 *    Gets the element pointer of the active element even if the 
 *    element is inside a frame. See HTML control documentation. 
 *    This function is only available for Dreamcast version of the 
 *    HTML control.
 * 
 * Parameters
 *    pHTMLDocument2    the document for which to find active element
 *    ppHTMLElement     fill with active element pointer
 * 
 * Returns
 *    See HTML control documentation
 ********************************************************************/
HRESULT GetCurrentFocusElement(IHTMLDocument2 *pHTMLDocument2, 
                               IHTMLElement **ppHTMLElement)
{
    // verify DLL has been loaded
    if (!g_hInstMSHTML)
    {
        return E_FAIL;
    }

    // get the mshtml function address
    PFNGETCURRENTFOCUSELEMENT pGetCurrentFocusElement = 
        (PFNGETCURRENTFOCUSELEMENT)GetProcAddress(g_hInstMSHTML, 
        TEXT("GetCurrentFocusElement"));

    if (!pGetCurrentFocusElement)
    {
        return E_FAIL;
    }

    // call the mshtml function
    return (*pGetCurrentFocusElement)(pHTMLDocument2, ppHTMLElement);
}

/********************************************************************
 * ShowHTMLDialog (mshtml.dll)
 *
 * Description
 *    Displays a modal dialog whose contents are an HTML page. See 
 *    online or MSDN documentation. This function is available in all 
 *    versions of the HTML control.
 * 
 * Parameters
 *    hwndParent  parent window of dialog
 *    pMoniker    URL of page to display in dialog
 *    pvarArgIn   arguments passed to dialog
 *    pchOptions  options passed to dialog
 *    pvarArgOut  return value from dialog
 * 
 * Returns
 *    See mshtml documentation
 ********************************************************************/
HRESULT ShowHTMLDialog(HWND hwndParent, IMoniker *pMoniker, 
                       VARIANT *pvarArgIn, TCHAR *pchOptions, 
                       VARIANT *pvarArgOut)
{
    // verify DLL has been loaded
    if (!g_hInstMSHTML)
    {
        return E_FAIL;
    }

    // get the mshtml function address
    SHOWHTMLDIALOGFN *pShowHTMLDialog = 
        (SHOWHTMLDIALOGFN *)GetProcAddress(g_hInstMSHTML, 
        TEXT("ShowHTMLDialog"));

    if (!pShowHTMLDialog)
    {
        return E_FAIL;
    }

    // call the mshtml function
    return (*pShowHTMLDialog)(hwndParent, pMoniker, pvarArgIn, 
                              pchOptions, pvarArgOut);
}

/********************************************************************
 * CreateURLMoniker (urlmon.dll)
 *
 * Description
 *    Creates an IMoniker using the given URL. See online or MSDN 
 *    documentation. This function is available in all versions of 
 *    the HTML control.
 * 
 * Parameters
 *    pmkContext  context moniker
 *    pszURL      URL
 *    ppMoniker   filled with new Moniker based on pszURL
 * 
 * Returns
 *    See urlmon documentation
 ********************************************************************/
HRESULT CreateURLMoniker(IMoniker *pmkContext, LPWSTR pszURL, 
                         IMoniker **ppMoniker)
{
    // verify DLL has been loaded
    if (!g_hInstURLMON)
    {
        return E_FAIL;
    }
 
    // get the urlmon function address
    PFNCREATEURLMONIKER pCreateURLMoniker = 
        (PFNCREATEURLMONIKER)GetProcAddress(g_hInstURLMON, 
        TEXT("CreateURLMoniker"));
    if (!pCreateURLMoniker)

    {
        return E_FAIL;
    }

    // call the urlmon function
    return (*pCreateURLMoniker)(pmkContext, pszURL, ppMoniker);
}

/********************************************************************
 * SetShowVMUMessageCallback (vmimime.dll)
 *
 * Description
 *    Registers a call back function in vmimime. The call back will
 *    be called whenever a vmimime needs to display an alert. See
 *    HTML control documentation. There can be only one call back
 *    function active at a time. This function is only available
 *    for Dreamcast version of the HTML control.
 * 
 * Parameters
 *    pShowVMUMessage   call back function
 * 
 * Returns
 *    See HTML control documentation
 ********************************************************************/
HRESULT SetShowVMUMessageCallback(PFNSHOWVMUMESSAGECALLBACK pShowVMUMessage)
{
    // verify DLL has been loaded
    if (!g_hInstVMIMIME)
    {
        return E_FAIL;
    }

    // get the vmimime function address
    PFNSETSHOWVMUMESSAGECALLBACK pSetShowVMUMessageCallback = 
        (PFNSETSHOWVMUMESSAGECALLBACK)GetProcAddress(g_hInstVMIMIME, 
        TEXT("SetShowVMUMessageCallback"));

    if (!pSetShowVMUMessageCallback)
    {
        return E_FAIL;
    }

    // call the vmimime function
    return (*pSetShowVMUMessageCallback)(pShowVMUMessage);
}

/********************************************************************
 * SetGetVMUDeviceCallback (vmimime.dll)
 *
 * Description
 *    Registers a call back function in vmimime. The call back will
 *    be called whenever a vmimime needs to get the destination VMU
 *    device for a set of VMS files. See HTML control documentation. 
 *    There can be only one call back function active at a time. This 
 *    function is only available for Dreamcast version of the HTML 
 *    control.
 * 
 * Parameters
 *    pGetVMUDevice     call back function
 * 
 * Returns
 *    See HTML control documentation
 ********************************************************************/
HRESULT SetGetVMUDeviceCallback(PFNGETVMUDEVICECALLBACK pGetVMUDevice)
{
    // verify DLL has been loaded
    if (!g_hInstVMIMIME)
    {
        return E_FAIL;
    }

    // get the vmimime function address
    PFNSETGETVMUDEVICECALLBACK pSetGetVMUDeviceCallback = 
        (PFNSETGETVMUDEVICECALLBACK)GetProcAddress(g_hInstVMIMIME, 
        TEXT("SetGetVMUDeviceCallback"));

    if (!pSetGetVMUDeviceCallback)
    {
        return E_FAIL;
    }

    // call the vmimime function
    return (*pSetGetVMUDeviceCallback)(pGetVMUDevice);
}
