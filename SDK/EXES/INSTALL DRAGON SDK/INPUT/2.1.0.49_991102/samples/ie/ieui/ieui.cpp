/********************************************************************
 * Copyright (c) 1999 Microsoft Corporation
 *
 * ieui.cpp
 *
 * Description
 *   Implementation for the CIEUI class to handle replaceable UI for
 *   the HTML control. 
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include <windows.h>    // Standard Windows API
#include <uiresource.h> // IDs of error messages from HTML control
#include <wininet.h>    // Errors for wininet
#include "global.h"     // Global variables and function prototypes
#include "ieui.h"       // CIEUI class definition
#include "resource.h"   // Resource string IDs and bitmap IDs

/********************************************************************
 * Constants
 ********************************************************************/
// IID for Iieui   {B048FC80-122D-11D3-9590-00C04FAEA6D4}
const IID IID_Iieui    = {0xB048FC80,0x122D,0x11D3,{0x95,0x90,0x00,0xC0,0x4F,0xAE,0xA6,0xD4}};
// CLSID for CIEUI {B048FC81-122D-11D3-9590-00C04FAEA6D4}
const CLSID CLSID_ieui = {0xB048FC81,0x122D,0x11D3,{0x95,0x90,0x00,0xC0,0x4F,0xAE,0xA6,0xD4}};

/********************************************************************
 * CIEUI::CIEUI
 *
 * Description
 *   Only constructor for the CIEUI class. The object starts with a 
 *   zero reference count, and it increments the number of objects 
 *   in the DLL.
 ********************************************************************/
CIEUI::CIEUI(void)
{ 
    g_ulLocks++;
    _ulRefCount = 0;
    _hdcBitmap  = NULL;
    _hbmBitmap  = NULL;
}

/********************************************************************
 * CIEUI::~CIEUI
 *
 * Description
 *   Destructor for the CIEUI class. It decrements the number of 
 *   objects in the DLL.
 ********************************************************************/
CIEUI::~CIEUI(void)
{ 
    // Clean up DC and bitmap for focus rect bitmap.

    if (_hdcBitmap && (_hdcBitmap != (HDC)0xffffffff))
    {
        DeleteObject(_hdcBitmap);
    }

    if (_hbmBitmap)
    {
        DeleteObject(_hbmBitmap);
    }

    g_ulLocks--;
}

/********************************************************************
 * IUnknown
 ********************************************************************/

/********************************************************************
 * CIEUI::IUnknown::QueryInterface
 *
 * Description
 *    Return requested interface pointer.
 *
 * Parameters
 *    riid    in  Interface ID.
 *    ppvObj  out Pointer to requested interface pointer.
 *
 * Result
 *    S_OK           Success.
 *    E_POINTER      If ppvObj not supplied.
 *    E_NOINTERFACE  If IID is not known. 
 ********************************************************************/
STDMETHODIMP CIEUI::QueryInterface(REFIID riid, LPVOID *ppvObj)
{
    // Validate return parameter.
    if (!ppvObj)
    {
        return E_POINTER;
    }

    // Initialize return pointer to NULL.
    *ppvObj = NULL;

    // Check for known and handled interface ID.
    if (riid == IID_IUnknown)
    {
        *ppvObj = (IUnknown *)(IClassFactory *)this;
    }
    else if (riid == IID_IClassFactory)
    {
        *ppvObj = (IClassFactory *)this;
    }
    else if (riid == IID_Iieui)
    {
        *ppvObj = (Iieui *)this;
    }
    else
    {
        // IID unknown, return error.
        return E_NOINTERFACE;
    }

    // Found interface, Add Ref it and return success
    ((IUnknown *)(*ppvObj))->AddRef();

    return S_OK;
}

/********************************************************************
 * CIEUI::IUnknown::AddRef
 *
 * Description
 *    Increments refrerence count.
 *
 * Parameters
 *    None.
 *
 * Result
 *    Number of reference counts on object.
 ********************************************************************/
STDMETHODIMP_(ULONG) CIEUI::AddRef(void)
{
    _ulRefCount++;

    return _ulRefCount;
}

/********************************************************************
 * CIEUI::IUnknown::Release
 *
 * Description
 *    Decrements reference count, and deletes object when count = 0.
 *
 * Parameters
 *    None.
 *
 * Result
 *    Number of reference counts on object.
 ********************************************************************/
STDMETHODIMP_(ULONG) CIEUI::Release(void)
{
    _ulRefCount--;

    if (_ulRefCount)
    {
        return _ulRefCount;
    }

    delete this;

    return 0;
}

/********************************************************************
 * IClassFactory
 ********************************************************************/

/********************************************************************
 * CIEUI::IClassFactory::CreateInstance
 *
 * Description
 *    The replaceable UI object and the class factory are the same 
 *    object, so CreateInstance simply gets the requested interface 
 *    from itself.
 *
 * Parameters
 *    pUnkOuter  in  Not used.
 *    riid       in  Interface ID.
 *    ppvObj     out Pointer to requested interface pointer.
 *
 * Result
 *    S_OK                   Success.
 *    CLASS_E_NOAGGREGATION  If pUnkOuter is non null.
 *    other                  Result of QueryInterface
 ********************************************************************/
STDMETHODIMP CIEUI::CreateInstance(IUnknown *pUnkOuter, REFIID riid, LPVOID *ppvObj)
{
    if (pUnkOuter)
    {
        return CLASS_E_NOAGGREGATION;
    }

    return QueryInterface(riid, ppvObj);
}

/********************************************************************
 * CIEUI::IClassFactory::LockServer
 *
 * Description
 *    Locks or unlocks the DLL.
 *
 * Parameters
 *    bLock  in  TRUE   Lock the DLL from being unloaded.
 *               FALSE  Unlock the DLL.
 *
 * Result
 *    S_OK
 ********************************************************************/
STDMETHODIMP CIEUI::LockServer(BOOL bLock)
{
    if (bLock)
    {
        g_ulLocks++;
    }
    else
    {
        g_ulLocks--;
    }

    return S_OK;
}

/********************************************************************
 * Iieui
 ********************************************************************/

/********************************************************************
 * CIEUI::Iieui::ShowScriptErrorDialog
 *
 * Description
 *    Provide a dialog for scripting errors. In retail builds, script 
 *    errors are simply ignored. 
 *
 *    You can ignore all scripting errors or always show scripting 
 *    errors or only show certain errors.
 *
 * Parameters
 *    hwndParent    in  parent window of error message
 *    pDispatch     in  parameter to ShowHTMLDialog
 *
 * Result
 *    S_OK          did not show script error dialog (retail) OR
 *                  sucessfully showed script error dialog (debug)
 *    E_FAIL        could not show script error dialog (debug)
 ********************************************************************/
STDMETHODIMP CIEUI::ShowScriptErrorDialog(HWND hwndParent, IDispatch *pDispatch)
{
    HRESULT hr = S_OK;

#ifdef DEBUG
    // Verify helper functions.
    if (!g_pfnCreateUrlMoniker || !g_pfnShowHTMLDialog)
    {
        return E_FAIL;
    }

    IMoniker *pMoniker = NULL;
    VARIANT   varArgIn = { 0 };

    // Create moniker for error.dlg URL.
    hr = (*g_pfnCreateUrlMoniker)(NULL, L"res://ieui.dll/error.dlg", &pMoniker);
    if (FAILED(hr))
    {
        goto Cleanup;
    }

    // Pass dispatch pointer to ShowHTMLDialog.
    V_VT(&varArgIn) = VT_DISPATCH;
    V_DISPATCH(&varArgIn) = pDispatch;
    pDispatch->AddRef();

    // Show the error dialog.
    hr = (*g_pfnShowHTMLDialog)(hwndParent, pMoniker, &varArgIn, NULL, NULL);

Cleanup:
    // Done with the moniker.
    if (pMoniker)
    {
        pMoniker->Release();
    }

    // Done with the dispatch pointer (this will release it).
    VariantClear(&varArgIn);
#endif // DEBUG

    // Return result.
    return hr;
}

/********************************************************************
 * CIEUI::Iieui::ShowFindDialog
 *
 * Description
 *    Find dialog is not used in Dreamcast HTML control, so this 
 *    function is left unimplemented.
 *
 * Parameters
 *    N/A
 *
 * Result
 *    E_NOTIMPL
 ********************************************************************/
STDMETHODIMP CIEUI::ShowFindDialog(HWND hwndParent, IDispatch *pDispatch)
{
    return E_NOTIMPL;
}

/********************************************************************
 * CIEUI::Iieui::ShowPromptDialog
 *
 * Description
 *    Provide a dialog to allow the user to enter a string showing the
 *    prompt text and defaulting to the given text. 
 *
 *    To prevent prompts from displaying to the user, you can leave 
 *    this function unimplemented. 
 *
 * Parameters
 *    hwndParent    in  parent window of error message
 *    bstrMessage   in  text of prompt instructions
 *    bstrDefault   in  default text in prompt edit field
 *    szEditResult  out user entered text
 *
 * Result
 *    S_OK       prompt shown sucessfully, user entered string
 *    S_FALSE    prompt shown sucessfully, user canceled
 *    E_FAIL     internal error
 *    E_OUTOFMEM out of memory
 ********************************************************************/
STDMETHODIMP CIEUI::ShowPromptDialog(HWND hwndParent, BSTR bstrMessage, BSTR bstrDefault, LPTSTR *szEditResult)
{
    HRESULT hr  = S_OK;
 
    // Verify helper functions.
    if (!g_pfnCreateUrlMoniker || !g_pfnShowHTMLDialog)
    {
        return E_FAIL;
    }

    VARIANT   varArgIn  = { 0 };
    VARIANT   varArgRet = { 0 };
    IMoniker *pMoniker  = NULL;

    // Use default text if none is supplied.
    if (!bstrMessage)
    {
        bstrMessage = L"javascript prompt:";
    }

    // Build argument list (Message String + '\0' + Default String)
    // for prompt.dlg
    int cchMessage = lstrlen(bstrMessage);
    int cchDefstr  = bstrDefault ? lstrlen(bstrDefault) : 0;
    int cbArgs     = cchMessage + 1 + cchDefstr;

    varArgIn.vt      = VT_BSTR;
    varArgIn.bstrVal = SysAllocStringLen(NULL, cbArgs);
    if (!varArgIn.bstrVal)
    {
         hr = E_OUTOFMEMORY;
         goto Cleanup;
    }
    memcpy(varArgIn.bstrVal, bstrMessage, (cchMessage + 1) * sizeof(WCHAR));
    if (cchDefstr)
    {
        memcpy(&varArgIn.bstrVal[cchMessage+1], bstrDefault, cchDefstr * sizeof(WCHAR));
    }

    // Create moniker for prompt.dlg URL.
    hr = (*g_pfnCreateUrlMoniker)(NULL, L"res://ieui.dll/prompt.dlg", &pMoniker);
    if (FAILED(hr))
    {
        goto Cleanup;
    }

    // Show dialog.
    hr = (*g_pfnShowHTMLDialog)(hwndParent, pMoniker, &varArgIn, NULL, &varArgRet);

    // If anything other than a string is returned, assume user canceled.
    if (varArgRet.vt != VT_BSTR)
    {
        *szEditResult = NULL;
        hr = S_FALSE;
    }
    else
    {
        // Return user typed in value.
        *szEditResult = new TCHAR[wcslen(varArgRet.bstrVal) + 1];
        if (*szEditResult)
        {
            wcscpy(*szEditResult, varArgRet.bstrVal);
        }
    }

Cleanup:
    // Done with the moniker.
    if (pMoniker)
    {
        pMoniker->Release();
    }

    // Done with the parameters.
    VariantClear(&varArgIn);
    VariantClear(&varArgRet);

    return hr;
}

/********************************************************************
 * CIEUI::Iieui::ShowAlertConfirm
 *
 * Description
 *    Provide a dialog to allow the user to view a message and respond
 *    by selecting a button (OK, cancel). 
 *
 *    To prevent alerts and confirms from displaying to the user, you 
 *    can leave this function unimplemented. You can display only 
 *    alerts or confirms by looking at the uType parameter. Alerts will
 *    have MB_OK set, and confirms will have MB_OKCANCEL set.
 *
 * Parameters
 *    hwndParent    in  parent window of error message
 *    szText        in  message to be displayed
 *    uType         in  type of message box (MB_OK, etc.)
 *
 * Result
 *    ID of button pushed (IDOK, IDCANCEL, IDYES, etc.)
 ********************************************************************/
STDMETHODIMP_(int) CIEUI::ShowAlertConfirm(HWND hwndParent, LPCTSTR szText, UINT uType)
{
    // Show message box with given message and buttons.
    return ShowMessageBoxInternal(FALSE, hwndParent, szText, MAKEINTRESOURCE(IDS_TITLE), uType);
}

/********************************************************************
 * CIEUI::Iieui::ShowMessageBox
 *
 * Description
 *    Provide a dialog to allow the user to view a message and respond
 *    by selecting a button (OK, cancel, or any of the other standard
 *    message box buttons). 
 *
 *    To prevent message boxes from displaying to the user, you can 
 *    leave this function unimplemented. 
 *
 * Parameters
 *    hwndParent    in  parent window of error message
 *    szText        in  message to be display (or format string)
 *    szCaption     in  title of message box
 *    uType         in  type of message box (MB_OK, etc.)
 *    ...           in  arguments for formatting the message
 *
 * Result
 *    ID of button pushed (IDOK, IDCANCEL, IDYES, etc.)
 ********************************************************************/
STDMETHODIMP_(int) CIEUI::ShowMessageBox(HWND hwndParent, LPCTSTR szText, LPCTSTR szCaption, UINT uType, ...)
{
    va_list ArgList;
    va_start(ArgList, uType);

    // Show message box with given message, buttons, title, and message arguments.
    int nResult = ShowMessageBoxInternal(TRUE, hwndParent, szText, szCaption, uType, ArgList);

    va_end(ArgList);

    return nResult;
}

/********************************************************************
 * CIEUI::Iieui::ShowPrintCancelDialog
 *
 * Description
 *    Printing is not handled in Dreamcast HTML control, so this 
 *    function is left unimplemented.
 *
 * Parameters
 *    N/A
 *
 * Result
 *    E_NOTIMPL
 ********************************************************************/
STDMETHODIMP CIEUI::ShowPrintCancelDialog(HWND hwndParent, HWND *phwndPrintCancelDlg, BOOL *pfAbortPrintJob)
{
    return E_NOTIMPL;
}

/********************************************************************
 * CIEUI::Iieui::ShowPageSetupDialog
 *
 * Description
 *    Printing is not handled in Dreamcast HTML control, so this 
 *    function is left unimplemented.
 *
 * Parameters
 *    N/A
 *
 * Result
 *    E_NOTIMPL
 ********************************************************************/
STDMETHODIMP CIEUI::ShowPageSetupDialog(PAGESETUPDLG *pdlgPageSetup, PAGESETUPOPT *poptPageSetup, BOOL *pfResult)
{
    return E_FAIL;
}

/********************************************************************
 * CIEUI::Iieui::ShowGetSaveFileName
 *
 * Description
 *    File saving is not handled in Dreamcast HTML control, so this 
 *    function is left unimplemented.
 *
 * Parameters
 *    N/A
 *
 * Result
 *    FALSE  do not save
 ********************************************************************/
STDMETHODIMP_(BOOL) CIEUI::ShowGetSaveFileName(OPENFILENAME *pofn)
{
    return FALSE;
}

/********************************************************************
 * CIEUI::Iieui::ShowGetOpenFileName
 *
 * Description
 *    File opening is not handled in Dreamcast HTML control, so this 
 *    function is left unimplemented.
 *
 * Parameters
 *    N/A
 *
 * Result
 *    FALSE  do not open
 ********************************************************************/
STDMETHODIMP_(BOOL) CIEUI::ShowGetOpenFileName(OPENFILENAME *pofn)
{
    return FALSE;
}

/********************************************************************
 * CIEUI::Iieui::ShowBindingErrorMessageBox
 *
 * Description
 *    Provide a dialog showing the user what error occurred. In this
 *    implementation, the errors are consolidated to a few simple
 *    phrases that the user can more easily understand. You can 
 *    choose whatever you would like to display for these various
 *    error messages, or not the error at all by leaving this function
 *    unimplemented.
 * 
 *
 * Parameters
 *    hwndParent    in  parent window of error message
 *    hrError       in  code for error to display
 *    dwResource    in  not used
 *    szUrlParam    in  URL (to be used as parameter in error message)
 *    fuFlags       in  type of message box (MB_OK, etc.)
 *
 * Result
 *    S_OK
 ********************************************************************/
STDMETHODIMP_(int) CIEUI::ShowBindingErrorMessageBox(HWND hwndParent, HRESULT hrError, DWORD dwResource, LPCTSTR szUrlParam, UINT fuFlags)
{
    TCHAR  szMsg[256];
    UINT   uID = IDS_ERRORTRYDIFFERENT;

    // Check for all cases where the user should try again.
    if (HRESULT_FROM_WIN32(ERROR_INTERNET_TIMEOUT) == hrError)
    {
        uID = IDS_ERRORTRYAGAIN;
    }

    // Check for all cases where the server could not find the requested file.
    if ((HRESULT_FROM_WIN32(ERROR_INTERNET_CANNOT_CONNECT) == hrError) ||
        (HRESULT_FROM_WIN32(ERROR_INTERNET_INVALID_URL) == hrError) ||
        (HRESULT_FROM_WIN32(ERROR_INTERNET_NAME_NOT_RESOLVED) == hrError) ||
        (INET_E_UNKNOWN_PROTOCOL == hrError) ||
        (INET_E_DATA_NOT_AVAILABLE == hrError))
    {
        uID = IDS_ERRORNOTFOUND;
    }

    // Load the actual error message.
    LoadString(g_hinst, uID, szMsg, 256);

    // Show the message box with the given string and general title.
    ShowMessageBoxInternal(TRUE, hwndParent, szMsg, MAKEINTRESOURCE(IDS_TITLE), fuFlags);

    return S_OK;    
}

/********************************************************************
 * CIEUI::Iieui::ShowDownLoad_UI
 *
 * Description
 *    File downloading is not handled in Dreamcast HTML control, so 
 *    this function is left unimplemented.
 *
 * Parameters
 *    N/A
 *
 * Result
 *    None
 ********************************************************************/
STDMETHODIMP_(void) CIEUI::ShowCDownLoad_UI(IMoniker *pMoniker, IBindCtx *pBindCtx, BOOL fSync, BOOL fSaveAs, BOOL fSafe, LPWSTR szHeaders, DWORD dwVerb, DWORD grfBINDF, BINDINFO *pBindInfo, LPCTSTR szRedir, HANDLE hSig, LONG *pcModelessDlg, HWND *phwndDlgActive, CRITICAL_SECTION *pcs)
{
    if (szHeaders)
    {
        CoTaskMemFree(szHeaders);
    }
}

/********************************************************************
 * CIEUI::Iieui::ShowCDownLoad_UIURL
 *
 * Description
 *    File downloading is not handled in Dreamcast HTML control, so 
 *    this function is left unimplemented.
 *
 * Parameters
 *    N/A
 *
 * Result
 *    E_NOTIMPL
 ********************************************************************/
STDMETHODIMP CIEUI::ShowCDownLoad_UIURL(LPCWSTR szURL, IBindCtx *pBindCtx, LPWSTR szHeaders, BOOL fSync, BOOL fSaveAs, BOOL fSafe, DWORD dwVerb, DWORD grfBINDF, BINDINFO *pBindInfo, LPCTSTR szRedir, HANDLE hSig, LONG *pcModelessDlg, HWND *phwmdDlgActive, CRITICAL_SECTION *pcs)
{
    if (szHeaders)
    {
        CoTaskMemFree(szHeaders);
    }
 
    return E_NOTIMPL;
}

/********************************************************************
 * CIEUI::Iieui::ShowLastErrorInfo
 *
 * Description
 *    Provide a dialog showing the user the last error that occurred.
 *    If the error text of the last error cannot be determined, the
 *    given string ID is used for the error (if one is not given, a
 *    default error is displayed). You can choose to not display the 
 *    error at all by leaving this function unimplemented.
 *
 * Parameters
 *    idsDefault    in  resource ID of default error string to show
 *                      if a more specific error message cannot be
 *                      found
 *    hwndParent    in  parent window of error message
 *
 * Result
 *    S_OK
 ********************************************************************/
STDMETHODIMP CIEUI::ShowLastErrorInfo(int idsDefault, HWND hwndParent)
{
    HRESULT      hr;
    IErrorInfo * pErrorInfo      = NULL;
    BSTR         bstrDescription = NULL;

    // Get error information object.
    hr = GetErrorInfo(0, &pErrorInfo);
    if (FAILED(hr))
    {
        goto Cleanup;
    }

    // Get description of error.
    hr = pErrorInfo->GetDescription(&bstrDescription);

    if (FAILED(hr))
    {
        goto Cleanup;
    }

    // If no description and no default description, supply one.
    if (!bstrDescription)
    {
        if (!idsDefault)
        {
            idsDefault = IDS_NODESCRIPTION;
        }
    }

    // Show error message box.
    ShowMessageBoxInternal(TRUE, hwndParent, bstrDescription? bstrDescription : MAKEINTRESOURCE(idsDefault), MAKEINTRESOURCE(IDS_TITLE), MB_ICONEXCLAMATION | MB_OK);

Cleanup:
    // Done with error info.
    if (pErrorInfo)
    {
        pErrorInfo->Release();
    }

    // Done with description.
    if (bstrDescription)
    {
        SysFreeString(bstrDescription);
    }

    return S_OK;
}

/********************************************************************
 * CIEUI::Iieui::ShowLoadError
 *
 * Description
 *    Provide a dialog showing the load error that occurred by finding
 *    the error text to display and popping up a message box. You can
 *    change how the error text is determined or not show the error at
 *    all by leaving this function unimplemented.
 *
 * Parameters
 *    hrDisplay     in  code for error to display
 *    hwndParent    in  parent window of error message
 *    szUrl         in  URL to display in error message
 *
 * Result
 *    S_OK
 ********************************************************************/
STDMETHODIMP CIEUI::ShowLoadError(HRESULT hrDisplay, HWND hwndParent, LPCTSTR szUrl)
{
    // Get error string.
    TCHAR achReason[256];
    HRESULT hr;

    hr = GetErrorText(hrDisplay, achReason, 256);
    if (FAILED(hr))
    {
        goto Cleanup;
    }

    // Show error string in message box.
    ShowMessageBoxInternal(TRUE, hwndParent, MAKEINTRESOURCE(IDS_CANNOTLOAD), MAKEINTRESOURCE(IDS_TITLE), MB_OK, szUrl, achReason);

Cleanup:
    return S_OK;
}

/********************************************************************
 * CIEUI::Iieui::GetErrorText
 *
 * Description
 *    Return the error text associated with the given error. In this
 *    implementation, the errors are consolidated to a few simple
 *    phrases that the user can more easily understand. You can 
 *    choose whatever you would like to return for these various
 *    error messages.
 *
 * Parameters
 *    hrError       in  code for error to fetch
 *    pstr          out buffer for where to store fetched string
 *    cch           in  size of buffer hrError
 *
 * Result
 *    S_OK              Error string retrieved.
 *    E_INVALIDARG      No return buffer supplied.
 ********************************************************************/
STDMETHODIMP CIEUI::GetErrorText(HRESULT hrError, LPTSTR pstr, int cch)
{
    // Validate parameters.
    if (!pstr || !cch)
    {
        return E_INVALIDARG;
    }

    UINT uID = IDS_ERRORTRYDIFFERENT;

    // Check for all cases where the user should try again.
    if (HRESULT_FROM_WIN32(ERROR_INTERNET_TIMEOUT) == hrError)
    {
        uID = IDS_ERRORTRYAGAIN;
    }

    // Check for all cases where the server could not find the requested file.
    if ((HRESULT_FROM_WIN32(ERROR_INTERNET_CANNOT_CONNECT) == hrError) ||
        (HRESULT_FROM_WIN32(ERROR_INTERNET_INVALID_URL) == hrError) ||
        (HRESULT_FROM_WIN32(ERROR_INTERNET_NAME_NOT_RESOLVED) == hrError) ||
        (INET_E_UNKNOWN_PROTOCOL == hrError) ||
        (INET_E_DATA_NOT_AVAILABLE == hrError))
    {
        uID = IDS_ERRORNOTFOUND;
    }

    // Load the actual error message.
    LoadString(g_hinst, uID, pstr, cch);

    return S_OK;
}

/********************************************************************
 * CIEUI::Iieui::GetSolutionText
 *
 * Description
 *    Just return a blank string. 
 *
 * Parameters
 *    hrError       in  code for error to fetch
 *    pstr          out buffer for where to store fetched string
 *    cch           in  size of buffer hrError
 * 
 * Result
 *    S_OK
 ********************************************************************/
STDMETHODIMP CIEUI::GetSolutionText(HRESULT hrError, LPTSTR pstr, int cch)
{
    // Validate parameters.
    if (!pstr || !cch)
    {
        return E_INVALIDARG;
    }

    // Return blank string.
    *pstr = 0; 

    return S_OK;
}

/********************************************************************
 * CIEUI::Iieui::MessageBoxW
 *
 * Description
 *    Simulate the MessageBoxW function for HTML control by showing
 *    and HTML dialog.
 *
 * Parameters
 *    hwndParent    in  parent window for message box
 *    lpText        in  message to be displayed in message box
 *    lpCaption     in  title of message box
 *    uType         in  type of message box (MB_OK, etc.)
 *
 * Result
 *    ID of button pushed (IDOK, IDCANCEL, IDYES, etc.)
 ********************************************************************/
STDMETHODIMP_(int) CIEUI::MessageBoxW(HWND hwndParent, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType)
{
    int nResult = IDCANCEL;

    // Verify helper functions.
    if (!g_pfnShowHTMLDialog || !g_pfnCreateUrlMoniker)
    {
        return nResult;
    }

    IMoniker *pMoniker = NULL;
    (*g_pfnCreateUrlMoniker)(NULL, L"res://ieui.dll/msgbox.dlg", &pMoniker);

    if (pMoniker)
    {
        HRESULT  hr;
        TCHAR    szButtons[64];
        int      cbButtons = 0;
        VARIANT  varArgs;
        VARIANT  varReturn;

        // Fabricate the string with the button text.
        switch (uType & 0x0000000FL)
        {
            case MB_OK:
            {
                cbButtons = LoadString(g_hinst, IDS_OK, szButtons, MAX_PATH);
                break;
            }

            case MB_OKCANCEL:
            {
                cbButtons = LoadString(g_hinst, IDS_OK, szButtons, MAX_PATH);
                // Skip over the NULL to use it as the delimiter.
                cbButtons++;
                cbButtons += LoadString(g_hinst, IDS_CANCEL, szButtons + cbButtons, MAX_PATH - cbButtons);
                break;
            }

            case MB_YESNOCANCEL:
            {
                cbButtons = LoadString(g_hinst, IDS_YES, szButtons, MAX_PATH);
                // Skip over the NULL to use it as the delimiter.
                cbButtons++;
                cbButtons += LoadString(g_hinst, IDS_NO, szButtons + cbButtons, MAX_PATH - cbButtons);
                // Skip over the NULL to use it as the delimiter.
                cbButtons++;
                cbButtons += LoadString(g_hinst, IDS_CANCEL, szButtons + cbButtons, MAX_PATH - cbButtons);
                break;
            }

            case MB_YESNO:
            {
                cbButtons = LoadString(g_hinst, IDS_YES, szButtons, MAX_PATH);
                // Skip over the NULL to use it as the delimiter.
                cbButtons++;
                cbButtons += LoadStringW(g_hinst, IDS_NO, szButtons + cbButtons, MAX_PATH - cbButtons);
                break;
            }

#ifdef DEBUG
            default:
            {
                lstrcpy(szButtons, TEXT("Invalid Button"));
                cbButtons = lstrlen(szButtons);
                break;
            }
#endif
        }

        // Pick the right icon.
        LPCTSTR pcszImg;
        switch (uType & 0x000000F0L)
        {
            default:
            case MB_ICONEXCLAMATION:
                pcszImg = TEXT("Exclamation.gif");
                break;

            case MB_ICONQUESTION:
                pcszImg = TEXT("Question.gif");
                break;
        }

        // Build the argument string (format is: img src\0text\0button captions).
        int cbImg = lstrlen(pcszImg);
        int cbText = lstrlen(lpText);
        int cbArgs =  cbImg + 1 + cbText + 1 + cbButtons;
        LPTSTR pszArgs = (LPTSTR) _alloca(cbArgs * sizeof(WCHAR));
        LPTSTR pszCopy = pszArgs;

        lstrcpy(pszCopy, pcszImg);
        // Move past the img string and the null.
        pszCopy += cbImg + 1;
        lstrcpy(pszCopy, lpText);
        // Move past the text and the null.
        pszCopy += cbText + 1;
        // Mem copy the button text since it might already have embedded nulls.
        memcpy(pszCopy, szButtons, cbButtons * sizeof(TCHAR));

        varArgs.vt = VT_BSTR;
        varArgs.bstrVal = SysAllocStringLen(pszArgs, cbArgs);

        // Init the return value.
        VariantInit(&varReturn);

        // Save the window with the focus.
        HWND hwndFocus = GetFocus();

        hr = (*g_pfnShowHTMLDialog)(hwndParent, pMoniker, &varArgs, NULL, &varReturn);

        // Restore focus to the saved window.
        SetFocus(hwndFocus);

        // Check for OK.
        LoadString(g_hinst, IDS_OK, szButtons, MAX_PATH);
        if (!lstrcmpi(varReturn.bstrVal, szButtons))
        {
            nResult = IDOK;
        }
        else
        {
            // Check for YES.
            LoadString(g_hinst, IDS_YES, szButtons, MAX_PATH);
            if (!lstrcmpi(varReturn.bstrVal, szButtons))
            {
                nResult = IDYES;
            }
            else
            {
                // Check for NO.
                LoadString(g_hinst, IDS_NO, szButtons, MAX_PATH);
                if (!lstrcmpi(varReturn.bstrVal, szButtons))
                {
                    nResult = IDNO;
                }
            }
        }

        // Cleanup
        VariantClear(&varArgs);
        VariantClear(&varReturn);
        pMoniker->Release();
    }

    return nResult;
}

/********************************************************************
 * CIEUI::Iieui::RenderFullTVFocusRect
 *
 * Description
 *    Draw a focus rect within given rectangle (all corners and all
 *    sides).
 *
 * Parameters
 *    hdc       in  device context into which to draw
 *    lprc      in  rectangle in which to draw focus rect
 *    wFlags    in  color of focus rect
 *
 * Result
 *    TRUE      drew focus rect successfully
 *    FALSE     invalid parameter
 ********************************************************************/
STDMETHODIMP_(BOOL) CIEUI::RenderFullTVFocusRect(HDC hdc, LPRECT lprc, UINT wFlags)
{ 
    // Validate parameters.
    if (!hdc || !lprc)
    {
        return FALSE;
    }

    RECT rc;

    // Make sure they have only color info.
    wFlags &= 0xFF00; 

    // Draw upper left corner of focus rect.
    rc.top = lprc->top;
    rc.left = lprc->left;
    rc.bottom = rc.top + FOCUSRECT_THICKNESS;
    rc.right = rc.left + FOCUSRECT_THICKNESS;
    DrawTVFocusRect(hdc, &rc, wFlags | FF_TOPLEFT);

    // Draw left edge of focus rect.
    rc.top = rc.bottom;
    rc.bottom = lprc->bottom - FOCUSRECT_THICKNESS;
    DrawTVFocusRect(hdc, &rc, wFlags | FF_LEFT);

    // Draw upper edge of focus rect.
    rc.top = lprc->top;
    rc.left = rc.right;
    rc.right = lprc->right - FOCUSRECT_THICKNESS;
    rc.bottom = rc.top + FOCUSRECT_THICKNESS;
    DrawTVFocusRect(hdc, &rc, wFlags | FF_TOP);

    // Draw upper left corner of focus rect.
    rc.left = rc.right;
    rc.right = lprc->right;
    DrawTVFocusRect(hdc, &rc, wFlags | FF_TOPRIGHT);

    // Draw right edge of focus rect.
    rc.top = rc.bottom;
    rc.bottom = lprc->bottom - FOCUSRECT_THICKNESS;
    DrawTVFocusRect(hdc, &rc, wFlags | FF_RIGHT);

    // Draw lower left corner of focus rect.
    rc.top = rc.bottom;
    rc.left = lprc->left;
    rc.bottom = lprc->bottom;
    rc.right = rc.left + FOCUSRECT_THICKNESS;
    DrawTVFocusRect(hdc, &rc, wFlags | FF_BOTTOMLEFT);

    // Draw lower edge of focus rect.
    rc.left = rc.right;
    rc.right = lprc->right - FOCUSRECT_THICKNESS;
    DrawTVFocusRect(hdc, &rc, wFlags | FF_BOTTOM);

    // Draw lower right corner of focus rect.
    rc.left = rc.right;
    rc.right = lprc->right;
    DrawTVFocusRect(hdc, &rc, wFlags | FF_BOTTOMRIGHT);

    return TRUE;
}

/********************************************************************
 * CIEUI::Iieui::DrawTVFocusRect
 *
 * Description
 *    Draw a focus rect segment (corner or edge) within the given
 *    rectangle. You can change the drawing to draw a sharper edged
 *    rectangle, a rounder rectangle, a rectangle with shadows, a
 *    striped rectangle, etc.
 *
 * Parameters
 *    hdc       in  device context into which to draw
 *    lprc      in  rectangle in which to draw focus rect segment
 *    wFlags    in  color and requested segment of focus rect 
 *
 * Result
 *    TRUE      drew focus rect successfully
 *    FALSE     invalid parameter
 ********************************************************************/
STDMETHODIMP_(BOOL) CIEUI::DrawTVFocusRect(HDC hdc, LPCRECT lprc, UINT wFlags)
{
    // Validate parameters.
    if (!hdc || !lprc)
    {
        return FALSE;
    }

    UINT xImage =0, yImage = 0, srcwidth= 0, srcheight=0;
    UINT left=lprc->left, top=lprc->top;
    UINT dstwidth = lprc->right - lprc->left;
    UINT dstheight = lprc->bottom - lprc->top;

    // Load bitmap with focus rect pieces.
    if (!InitResources())
    {
        return FALSE;
    }

    // Find offset in bitmap for focus rect pieces of requested color.
    switch (wFlags & 0xFF00)
    {
        case FF_YELLOW:
            xImage = YELLOW_FOCUSRECT_X_OFFSET;
            yImage = YELLOW_FOCUSRECT_Y_OFFSET;
            break;

        case FF_BLUE:
            xImage = BLUE_FOCUSRECT_X_OFFSET;
            yImage = BLUE_FOCUSRECT_Y_OFFSET;
            break;

        case FF_RED:
            xImage = RED_FOCUSRECT_X_OFFSET;
            yImage = RED_FOCUSRECT_Y_OFFSET;
            break;

        case FF_GREEN:
            xImage = GREEN_FOCUSRECT_X_OFFSET;
            yImage = GREEN_FOCUSRECT_Y_OFFSET;
            break;

        default:
            return FALSE;
    }

    // Find offset in bitmap for focus piece of requested segment.
    switch (wFlags & 0x00FF)
    {
        case FF_TOPLEFT:
            xImage += FOCUSRECT_LEFT;
            yImage += FOCUSRECT_TOP;
            srcwidth = srcheight = FOCUSRECT_THICKNESS;
            break;

        case FF_TOPRIGHT:
            xImage += FOCUSRECT_RIGHT;
            yImage += FOCUSRECT_TOP;
            srcwidth = srcheight = FOCUSRECT_THICKNESS;
            break;

        case FF_BOTTOMLEFT:
            xImage += FOCUSRECT_LEFT;
            yImage += FOCUSRECT_BOTTOM;
            srcwidth = srcheight = FOCUSRECT_THICKNESS;
            break;

        case FF_BOTTOMRIGHT:
            xImage += FOCUSRECT_RIGHT;
            yImage += FOCUSRECT_BOTTOM;
            srcwidth = srcheight = FOCUSRECT_THICKNESS;
            break;

        case FF_TOP:
            xImage += FOCUSRECT_LEFT + FOCUSRECT_THICKNESS + 1;
            yImage += FOCUSRECT_TOP;
            srcwidth = FOCUSRECT_EDGE_LENGTH;
            srcheight = FOCUSRECT_THICKNESS;
            break;

        case FF_LEFT:
            xImage += FOCUSRECT_LEFT;
            yImage += FOCUSRECT_TOP + FOCUSRECT_THICKNESS + 1;
            srcwidth = FOCUSRECT_THICKNESS;
            srcheight = FOCUSRECT_EDGE_LENGTH;
            break;

        case FF_BOTTOM:
            xImage += FOCUSRECT_LEFT + FOCUSRECT_THICKNESS + 1;
            yImage += FOCUSRECT_BOTTOM;
            srcwidth = FOCUSRECT_EDGE_LENGTH;
            srcheight = FOCUSRECT_THICKNESS;
            break;

        case FF_RIGHT:
            xImage += FOCUSRECT_RIGHT;
            yImage += FOCUSRECT_TOP + FOCUSRECT_THICKNESS + 1;
            srcwidth = FOCUSRECT_THICKNESS;
            srcheight = FOCUSRECT_EDGE_LENGTH;
            break;

        default:
            return FALSE;
    }

    // Transparent color in the bitmap is bright yellow.
    // Draw the requested segment of the focus rect.
    TransparentImage(hdc, left, top, dstwidth, dstheight,
                     _hdcBitmap, xImage, yImage,
                     srcwidth, srcheight, (COLORREF) 0x00FFFF);  

    return TRUE;
}

/********************************************************************
 * Helper functions
 ********************************************************************/

/********************************************************************
 * CIEUI::ShowMessageBoxInternal
 *
 * Description
 *    Helper function for displaying a message box. The caller can 
 *    send a string to be formatted, a string to be displayed, or the
 *    ID of a string to be formatted/displayed. Some error messages
 *    are filtered out and ignored. You can choose to filter out more
 *    of them or fewer of them or choose to handle the message box in
 *    a different way.
 *
 * Parameters
 *    bFormat       in  TRUE, if message needs to be formatted
 *    hwndParent    in  parent window of error message
 *    szText        in  message to be displayed OR resource ID of
 *                      message to be displayed OR format string
 *    szCaption     in  title to be displayed OR resource ID of title
 *                      to be displayed
 *    uType         in  type of message box (MB_OK, etc.)
 *    ...           in  arguments for formatting the message
 *
 * Result
 *    ID of button pushed (IDOK, IDCANCEL, IDYES, etc.)
 ********************************************************************/
int CIEUI::ShowMessageBoxInternal(BOOL bFormat, HWND hwndParent, LPCTSTR szText, LPCTSTR szCaption, UINT uType, ...)
{
    int nResult = IDOK;

    TCHAR   szResText[256];
    TCHAR   szResCaption[256];
    int     idResource = 0;

    // Convert error string resource if necessary.
    if (!HIWORD(szText))
    {
        switch (LOWORD(szText))
        {
            // From MSHTML:
            case IDS_REPOSTFORMDATA:
            case IDS_MAILTO_SUBMITALERT:
            case IDS_OCXDISABLED:
            case IDS_PROTECTEDFROMUNSAFEOCX:
            case IDS_PROTECTEDFROMOCXINIT:
            case IDS_ONBEFOREUNLOAD:
            case IDS_RUNAWAYSCRIPT:
                break;

            // From SHDOCVW:
            case IDS_CONFIRM_SCRIPT_CLOSE_TEXT:
            case IDS_ERR_OLESVR:
            case IDS_ERR_LOAD:
                break;
            case IDS_ERROR_GOTO:
                idResource = IDS_ERRORTRYDIFFERENT;
                break;

            default:
                idResource = LOWORD(szText);
                break;
        }
        
        // Check for something to show.
        if (idResource && LoadString(g_hinst, idResource, szResText, 256))
        {
            szText = szResText;
        }
        else
        {
            // Error should not be shown at all.
            return nResult;
        }
    }

    // Load caption resource if necessary.
    if (!HIWORD(szCaption) && LOWORD(szCaption) && LoadString(g_hinst, LOWORD(szCaption), szResCaption, 256))
    {
        szCaption = szResCaption;
    }

    // Format the message if necessary.
    if (bFormat)
    {
        LPTSTR  pszRet = NULL;
        va_list ArgList;

        va_start(ArgList, uType);

        // Format the message and any args, allocating a buffer (freed below).
        // If it formatted, use that. If it failed, retain the original buffer passed in.
        if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_STRING, szText, 0, 0, (LPTSTR)&pszRet, 0, &ArgList))
        {
            szText = pszRet;
        }

        // Show the message box.
        nResult = MessageBoxW(hwndParent, szText, szCaption, uType);
    
        LocalFree(pszRet);

        va_end(ArgList);
    }
    else
    {
        nResult = MessageBoxW(hwndParent, szText, szCaption, uType);
    }

    return nResult;
}

/********************************************************************
 * CIEUI::InitResources
 *
 * Description
 *    Helper function for loading bitmap containing focus rect pieces
 *    into a private device context for later bltting.
 *
 * Parameters
 *    None
 *
 * Result
 *    TRUE      bitmap successfully loaded into DC
 *    FALSE     could not find bitmap or create DC
 ********************************************************************/
BOOL CIEUI::InitResources(void)
{
    // If already tried to load, return whether the load was successful.
    if (_hdcBitmap)
    {
        return (_hdcBitmap != (HDC)0xffffffff);
    }

    // Load bitmap from resources.
    _hbmBitmap = LoadBitmap (g_hinst, MAKEINTRESOURCE(IDB_FOCUSRECT));
    if (!_hbmBitmap)
    {
        // Could not load bitmap. Flag as already attempted to load.
        _hdcBitmap = (HDC)0xffffffff;
        return FALSE;
    }

    // Create DC for bitmap.
    _hdcBitmap = CreateCompatibleDC (NULL);
    if (!_hdcBitmap)
    {
        // Could not create bitmap. Flag as already attempted to load.
        _hdcBitmap = (HDC)0xffffffff;
        return FALSE;
    }

    // Fill DC with bitmap.
    SelectObject(_hdcBitmap, (HGDIOBJ) _hbmBitmap);

    // Loaded sucessfully.
    return TRUE;
}

