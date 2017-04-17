/********************************************************************
 * Copyright (c) 1999 Microsoft Corporation
 *
 * wininetui.cpp
 *
 * Description
 *   Implementation for the wininet replaceable UI components. 
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include <windows.h>
#include <altinetui.hxx>
#include <wininet.h>
#include "wininetui.h"
#include "resource.h"
#include "xlate.h"

/********************************************************************
 * Defines
 ********************************************************************/
#define MESSAGE_TEXT_LENGTH_MAX         512
#define RESULT_DELIMITER                L"\\0"  // string (2 chars) that separated return values in reply from HTML dialogs
#define RESULT_DELIMETER_LENGTH_CHARS   2       // length in characters of the delimeter (\0) char x5c x30
#define BUTTON_CAPTION_LENGHT_MAX       64

/********************************************************************
 * Typedefs for functions from dynamically loaded DLLs
 ********************************************************************/
typedef int WINAPI MESSAGEBOXWFN(HWND, LPCWSTR, LPCWSTR, UINT);
typedef HRESULT STDAPICALLTYPE SHOWHTMLDIALOGFN(HWND, IMoniker *, VARIANT *, TCHAR *, VARIANT *);
typedef HRESULT STDAPICALLTYPE CREATEURLMONIKERFN(LPMONIKER, LPCWSTR, LPMONIKER *);

/********************************************************************
 * Structure typedefs 
 ********************************************************************/
typedef struct tagInvalidPassType
{
    LPSTR             lpszRealm;
    LPSTR             lpszUsername;
    LPSTR             lpszPassword;
    LPSTR             lpszHost;
    ULONG             ulMaxField;
} InvalidPassType;

/********************************************************************
 * Global variables
 ********************************************************************/
HINSTANCE      g_hinst          = NULL;
HINSTANCE      g_hinstIECEEXT   = NULL;
MESSAGEBOXWFN *g_pfnMessageBoxW = NULL;

/********************************************************************
 * Helper functions
 ********************************************************************/

DWORD DoBasicAuthentication(HWND hwndParent, LPVOID lpParam)
{
    WCHAR   wszButtons[BUTTON_CAPTION_LENGHT_MAX];
    WCHAR   wszButtonsReturn[BUTTON_CAPTION_LENGHT_MAX];
    int     cbButtons = 0;
    int     cbArgs    = 0;
    LPWSTR  pwszArgs  = NULL;
    LPWSTR  pwszCopy  = NULL;
    LPWSTR  pwszTemp  = NULL;
    DWORD   dwRet     = ERROR_CANCELLED;
    VARIANT varArgs;
    VARIANT varReturn;

    // Dynamically link to mshtml and urlmon 
    HINSTANCE   hinstMSHTML = LoadLibrary(TEXT("MSHTML.DLL"));
    HINSTANCE   hinstUrlMon = LoadLibrary(TEXT("URLMON.DLL"));
    if (!hinstMSHTML || !hinstUrlMon)
    {
        goto Cleanup;
    }

    SHOWHTMLDIALOGFN   *pfnShowHTMLDialog;
    CREATEURLMONIKERFN *pfnCreateURLMoniker;
    pfnShowHTMLDialog   = (SHOWHTMLDIALOGFN*)GetProcAddress(hinstMSHTML, L"ShowHTMLDialog");
    pfnCreateURLMoniker = (CREATEURLMONIKERFN*)GetProcAddress(hinstUrlMon, L"CreateURLMoniker");
    if (!pfnShowHTMLDialog || !pfnCreateURLMoniker)
    {
        goto Cleanup;
    }

    IMoniker *pMoniker;
    (*pfnCreateURLMoniker)(NULL, L"res://wininetui.dll/basic.dlg", &pMoniker);

    InvalidPassType *pInvalidPasswordType;
    pInvalidPasswordType = (InvalidPassType *)lpParam;

    // OK, CANCEL button caption 
    cbButtons = LoadString(g_hinst, IDS_OK, wszButtons, ARRAYSIZE(wszButtons));

    // Skip over the NULL to use it as the delimiter
    cbButtons++;
    cbButtons += LoadString(g_hinst, IDS_CANCEL, wszButtons + cbButtons, ARRAYSIZE(wszButtons) - cbButtons);

    // the NULL;
    cbButtons++;

    // build the argument string (format is: 
    // button_caption_OK\0button_caption_CANCEL\0Username\0Password\0)
    // Even if lpszUsername/lpszPassword are empty, we still 
    // need \0 for them as delimeters. The NULL char after 
    // Password will be added by SysAllocStringLen that's why 
    // cbPassword is not including it

    // UserName/Password ANSI->UNICODE
    USES_CONVERSION;
    LPWSTR pwszUsername, pwszPassword;
    pwszUsername = A2W(pInvalidPasswordType->lpszUsername);
    pwszPassword = A2W(pInvalidPasswordType->lpszPassword);

    int cbUserName, cbPassword;
    cbUserName = lstrlenW(pwszUsername) + 1; 
    cbPassword = lstrlenW(pwszPassword);
    cbArgs = cbButtons + cbUserName + cbPassword;
    pwszArgs = (LPWSTR) _alloca(cbArgs * sizeof(WCHAR));
    pwszCopy = pwszArgs;
    pwszTemp = NULL;

    // Mem copy the button text since it might already have embedded nulls
    memcpy(pwszCopy, wszButtons, cbButtons * sizeof(WCHAR));
    // move past buttons captions including last NULL
    pwszCopy += cbButtons;

    if (*pwszUsername)
    {                            
        lstrcpyW(pwszCopy, pwszUsername);
    }
    else
    {
        *pwszCopy = 0;
    }

    // Move past the Username string and the null
    pwszCopy += cbUserName;

    if (*pwszPassword)
    {                            
        // memcpy since we don't want ot include the NULL (see comment above)
        memcpy(pwszCopy, pwszPassword, cbPassword * sizeof(WCHAR));
    }

    varArgs.vt = VT_BSTR;
    varArgs.bstrVal = SysAllocStringLen(pwszArgs, cbArgs);

    // init the return value
    VariantInit(&varReturn);

    // save the window with the focus
    HWND hwndFocus;
    hwndFocus = GetFocus();

    (*pfnShowHTMLDialog)(hwndParent, pMoniker, &varArgs, NULL, &varReturn);

    // restore focus to the saved window
    SetFocus(hwndFocus);

    // parse return values that are in the format 
    // result_button_captionDDuser_nameDDpassword\0
    // This string shoud have 2 DD (delimeter substrings), button caption
    // can't be empty, the name/password can
    if (varReturn.bstrVal == NULL)
    {
        goto Cleanup;
    }

    pwszCopy = varReturn.bstrVal;
    pwszTemp = wcsstr(pwszCopy, RESULT_DELIMITER);
    if (pwszTemp != NULL)
    {   
        *pwszTemp = 0; // to be able to use str functions                             
        lstrcpyW(wszButtonsReturn, pwszCopy);                               
        cbButtons = lstrlenW(pwszCopy) + RESULT_DELIMETER_LENGTH_CHARS;
        // Step over result_button_captionDD                        
        pwszCopy += cbButtons;
        // get the use name
        pwszTemp = wcsstr(pwszCopy, RESULT_DELIMITER);
        if (pwszTemp != NULL)
        {
            *pwszTemp = 0; // to be able to use str functions
            strcpyAW(pInvalidPasswordType->lpszUsername, pwszCopy);
            cbUserName = lstrlenW(pwszCopy) + RESULT_DELIMETER_LENGTH_CHARS;;
            // Step over user_nameDD
            pwszCopy += cbUserName;
            // get the password
            strcpyAW(pInvalidPasswordType->lpszPassword, pwszCopy);
        }
    }

    // If result_button_caption is the same as IDS_OK's one, 
    // return ERROR_SUCCESS 
    if (!lstrcmpiW(wszButtons, wszButtonsReturn))
    {
        dwRet = ERROR_SUCCESS;
    }

Cleanup:
    VariantClear(&varArgs);
    VariantClear(&varReturn);

    if (pMoniker)
    {
        pMoniker->Release();
    }

    if (hinstMSHTML)
    {
        FreeLibrary(hinstMSHTML);
    }

    if (hinstUrlMon)
    {
        FreeLibrary(hinstUrlMon);
    }

    return dwRet;
}

/********************************************************************
 * Exported functions
 ********************************************************************/

DWORD LaunchDlg(HWND hwndParent, LPVOID lpParam, DWORD dwDlgResource)
{
    if (!g_pfnMessageBoxW)
    {
        return ERROR_CANCELLED;
    }

    DWORD dwRet = ERROR_SUCCESS;
    
    // based on the dwDlgResource get the strings needed for button 
    // caption text (pooled out of resources for localization purposes) 
    // and dlg params

    switch (dwDlgResource)
    {
        case IDD_BASIC_AUTHENTICATION:
        {
            dwRet = DoBasicAuthentication(hwndParent, lpParam);
            break;
        } 

        case IDD_BAD_CN:
        case IDD_CERT_EXPIRED:
        case IDD_INVALID_CA:
        case IDD_CERTPICKER:
        case ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED:
        {
            WCHAR szMessageText[MESSAGE_TEXT_LENGTH_MAX]; 

            // Load message body & display the message
            LoadStringW(g_hinst, IDS_SECURITY, szMessageText, ARRAYSIZE(szMessageText));

            (*g_pfnMessageBoxW)(hwndParent, szMessageText, NULL, MB_OK | MB_ICONEXCLAMATION);

            // Don't care about the return value, all user can press is
            // either CONTINUE button or ESC button, in both cases, we 
            // cosider the operation canceled for all the CERTIFICATE 
            // cases.
            dwRet = ERROR_CANCELLED;
            
            break;
        }

        case IDD_MIXED_SECURITY:
        case IDD_HTTP_TO_HTTPS_ZONE_CROSSING:
        case IDD_HTTPS_TO_HTTP_ZONE_CROSSING:
        case IDD_HTTP_POST_REDIRECT:
        case IDD_WARN_ON_POST:
        case IDD_HTTPS_TO_HTTP_SUBMIT_REDIRECT:
        default:
            // For all these situation, silent acceptance, no UI                            
            dwRet = ERROR_SUCCESS;
            break;
    } 

    return dwRet;
}

int LaunchMessageBox(HWND hwndParent, DWORD dwMsgBoxID)   
{
#define TITLE_TEXT_MAX 80

    int     iReturn = IDNO;
    TCHAR   szMessageText[MESSAGE_TEXT_LENGTH_MAX];
    TCHAR   szTitleText[TITLE_TEXT_MAX];

    if (!g_pfnMessageBoxW)
    {
       return iReturn;
    }

    switch (dwMsgBoxID)
    {
        case IDM_AUTODIAL_CONFIRM:
        {
            LoadString(g_hinst, IDS_AUTODIAL_CONFIRM_TITLE, szTitleText, ARRAYSIZE(szTitleText));
            LoadString(g_hinst, IDS_AUTODIAL_CONFIRM_TEXT, szMessageText, ARRAYSIZE(szMessageText));
            iReturn = (g_pfnMessageBoxW)(NULL, szMessageText, szTitleText, MB_YESNO | MB_SETFOREGROUND);
            break;
        }

        case IDM_ACCESS_DENIED:
        {
            LoadString(g_hinst,IDS_ACCESS_DENIED, szMessageText, ARRAYSIZE(szMessageText));
            iReturn = (*g_pfnMessageBoxW)(hwndParent, szMessageText, NULL, MB_OK | MB_ICONEXCLAMATION);
            break;
        }
        
        default:
        {
            // Unknown dwMessageBoxId
        }
        
    } 

    return iReturn;
}

/********************************************************************
 * DllMain 
 *
 * Description
 *    Handle initialization and shutdown of DLL. It loads the DLLs 
 *    and functions that it will be frequently using.
 *
 * Parameters
 *    None.
 *
 * Result
 *    TRUE   All ok
 ********************************************************************/
BOOL WINAPI DllMain(HANDLE hinst, DWORD dwReason, LPVOID lpvReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        // Keep track of DLL instance handle while DLL is active.
        g_hinst = (HINSTANCE)hinst;

        // Load all the functions that are used frequently from the proper DLLs.

        // From IECEEXT:
        g_hinstIECEEXT = LoadLibrary(L"IECEEXT");
        if (g_hinstIECEEXT)
        {
            g_pfnMessageBoxW = (MESSAGEBOXWFN*)GetProcAddress(g_hinstIECEEXT, L"MessageBoxW");
        }
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        // Free all the libaries that this DLL has been using.

        if (g_hinstIECEEXT)
        {
            g_pfnMessageBoxW = NULL;
            FreeLibrary(g_hinstIECEEXT);
            g_hinstIECEEXT = NULL;
        }

        g_hinst = NULL;
    }

    return TRUE;
}

