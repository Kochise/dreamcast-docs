// ===========================================================================
// File: S E C C L N T . C P P
// 
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Description:
// 
//  This is the client-portion of the SECURE Network OLE sample. This
// application displays UI to allow you to select security settings for
// the client process's connections to the server, connect to local or remote
// instances of either the "LocalServer32" (CLSID_SecureObject) or "LocalService"
// (CLSID_SecureObjectService) objects.
// 
//  The purpose of this sample is to demonstrate client-side security
// capabilities.
// 
// Instructions:
// 
//  To use this sample:
//   * build the samples using the NMAKE command. NMAKE will create SECCLNT.EXE,
//     SECSVR.EXE, and PSMYPROP.DLL. PSMYPROP.DLL is the remoting proxies and
//     stubs for the custom interface used between the client and the server.
//   * install the server on the current machine or on a remote machine
//     by running INSTALL.BAT in the same directory with SECSVR.EXE and
//     PSMYPROP.DLL. This program registers the proxy-stub DLL using the
//     REGSVR32 tool (included in the \mstools\bin directory of the SDK) and
//     runs the SECSVR.EXE program with "-AutoRegister" on the command-line,
//     which forces it to install itself.
//   * next, run SECCLNT.EXE. it will bring up a user interface with 3 different
//     sections.
//   * In Section 1, choose the security parameters to CoInitializeSecurity from
//     the two drop-down lists, and press the Initialize button.
//   * Next, in Section 2, choose a machine name to instantiate the object on
//     (leave this field blank to use the current machine) and choose between the
//     "LocalService" or the standard "LocalServer32" implementation of the object.
//     Then, press the "Create Now" button to create an instance.
//   * With some security settings, you will receive a message box at this point
//     telling you that the connection to the object has no authentication. In this
//     case, the call-level security choices in Section 3 will not be made available.
//   * Next, go to Section 3 and set the color and the "Name" on the object.
//     These UI elements make calls on the custom IMyProperties interface. If you
//     have pre-launched SECSVR.EXE with the "-Interactive" flag on the local or
//     remote machine that you are connected to, you will be able to see the
//     changes you make to the color and the name reflected in its UI, and may
//     adjust some simple security settings (see the Instructions section of
//     SECSVR.CPP for details).
//   * Push the "Release" button in Section 2 to release the object and connect to
//     a different object. When you are done, close the dialog box or push the
//     "Exit" button in Section 1 at any time to exit.
// 
// Copyright 1996 Microsoft Corporation. All Rights Reserved.
// ===========================================================================

// %%Includes: ---------------------------------------------------------------
#define INC_OLE2
#define UNICODE
#include <windows.h>
#include <initguid.h>
#include "myprop.h"
#include <rpcdce.h>
#include "secclnt.h"

// %%Macros: -----------------------------------------------------------------
#define ENTRY(sz, val)      { sz, val }
#define RGSIZEOF(rg)        (sizeof(rg)/sizeof((rg)[0]))

// %%Constants: --------------------------------------------------------------
#define cServerEntries      RGSIZEOF(rgServerEntries)
#define cAuthnLevelEntries  RGSIZEOF(rgAuthnLevelEntries)
#define cAuthzEntries       RGSIZEOF(rgAuthzEntries)
#define cImpLevelEntries    RGSIZEOF(rgImpLevelEntries)
#define cAuthnEntries       RGSIZEOF(rgAuthnEntries)

// %%Types: ------------------------------------------------------------------
typedef struct tagENTRY{
    TCHAR   *szName;
    DWORD   dwVal;
} ENTRY, *PENTRY;

// %%Globals: ----------------------------------------------------------------
COLORREF s_crCurrent;
HBRUSH   s_hbrCurrent = NULL;

ENTRY   rgServerEntries[] = {
    ENTRY(TEXT("Secure Object"), (DWORD)(LPVOID)&CLSID_SecureObject),
    ENTRY(TEXT("Secure Object Service"), (DWORD)(LPVOID)&CLSID_SecureObjectService),
    };

ENTRY   rgAuthnLevelEntries[] = {
    ENTRY(TEXT("Default    "), RPC_C_AUTHN_DEFAULT),
    ENTRY(TEXT("None       "), RPC_C_AUTHN_LEVEL_NONE),
    ENTRY(TEXT("Connect    "), RPC_C_AUTHN_LEVEL_CONNECT),
    ENTRY(TEXT("Call       "), RPC_C_AUTHN_LEVEL_CALL),
    ENTRY(TEXT("Packet     "), RPC_C_AUTHN_LEVEL_PKT),
    ENTRY(TEXT("Integrity  "), RPC_C_AUTHN_LEVEL_PKT_INTEGRITY),
    ENTRY(TEXT("Privacy    "), RPC_C_AUTHN_LEVEL_PKT_PRIVACY),
    };
ENTRY   rgAuthzEntries[] = {
    ENTRY(TEXT("None       "), RPC_C_AUTHZ_NONE),
    ENTRY(TEXT("Name       "), RPC_C_AUTHZ_NAME),
    ENTRY(TEXT("DCE        "), RPC_C_AUTHZ_DCE),
    };

ENTRY   rgImpLevelEntries[] = {
    ENTRY(TEXT("Anonymous  "), RPC_C_IMP_LEVEL_ANONYMOUS),
    ENTRY(TEXT("Identify   "), RPC_C_IMP_LEVEL_IDENTIFY),
    ENTRY(TEXT("Impersonate"), RPC_C_IMP_LEVEL_IMPERSONATE),
    ENTRY(TEXT("Delegate   "), RPC_C_IMP_LEVEL_DELEGATE),
    };

ENTRY   rgAuthnEntries[] = {
    ENTRY(TEXT("None       "), RPC_C_AUTHN_NONE),
    ENTRY(TEXT("DCE Private"), RPC_C_AUTHN_DCE_PRIVATE),
    ENTRY(TEXT("DCE Public "), RPC_C_AUTHN_DCE_PUBLIC),
    ENTRY(TEXT("DEC Public "), RPC_C_AUTHN_DEC_PUBLIC),
    ENTRY(TEXT("Windows NT "), RPC_C_AUTHN_WINNT),
    ENTRY(TEXT("Default    "), RPC_C_AUTHN_DEFAULT),
    };

// ---------------------------------------------------------------------------
// %%Function: ErrorMessage
// ---------------------------------------------------------------------------
 void
ErrorMessage(HWND hwnd, LPTSTR szFunction, HRESULT hr)
{
    LPTSTR   szMessage;

    if (HRESULT_FACILITY(hr) == FACILITY_WINDOWS)
        hr = HRESULT_CODE(hr);
 
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        hr,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), //The user default language
        (LPTSTR)&szMessage,
        0,
        NULL );

    MessageBox(hwnd, szMessage, szFunction, MB_OK);
    
    LocalFree(szMessage);
}  // ErrorMessage

// ---------------------------------------------------------------------------
// %%Function: SelectEntry
// ---------------------------------------------------------------------------
 void
SelectEntry(HWND hwnd, ENTRY* rgEntries, int cEntries, DWORD dwVal)
{
    for (int i=0; i<cEntries; i++)
        {
        if (rgEntries[i].dwVal == dwVal)
            {
            SendMessage(hwnd, CB_SETCURSEL, i, 0);
            return;
            }
        }
}  // SelectEntry

// ---------------------------------------------------------------------------
// %%Function: GetField
// ---------------------------------------------------------------------------
 DWORD
GetField(HWND hwndDlg, UINT idItem)
{
    HWND    hwnd;
    int     iCur;

    hwnd = GetDlgItem(hwndDlg, idItem);
    iCur = SendMessage(hwnd, CB_GETCURSEL, 0, 0);
    return SendMessage(hwnd, CB_GETITEMDATA, iCur, 0);
}  // GetField

// ---------------------------------------------------------------------------
// %%Function: UpdateSecurityFields
// ---------------------------------------------------------------------------
 void
UpdateSecurityFields(HWND hwndDlg, LPUNKNOWN punk, BOOL fSet)
{
    HWND    hwnd;
    DWORD   dwAuthn, dwAuthz, dwAuthnLevel, dwImpLevel;
    LPOLESTR wszPrinciple;
    HRESULT hr;

    // in response to a CBN_SELCHANGE, we try to set the new proxy
    // security parameters first
    if (fSet)
        {
        hr = CoSetProxyBlanket(punk,
            GetField(hwndDlg, IDC_PROXY_AUTHN),
            GetField(hwndDlg, IDC_PROXY_AUTHZ),
            NULL,
            GetField(hwndDlg, IDC_PROXY_AUTHNLEVEL),
            GetField(hwndDlg, IDC_PROXY_IMPLEVEL),
            NULL,
            NULL);
        if (FAILED(hr))
            {
            ErrorMessage(hwndDlg, TEXT("CoSetProxyBlanket"), hr);
            }
        }

    // in all cases, update the fields to reflect the actual state of
    // security on the proxy
    hr = CoQueryProxyBlanket(punk,
        &dwAuthn, &dwAuthz, &wszPrinciple, &dwAuthnLevel, &dwImpLevel,
        NULL, NULL);
    if (FAILED(hr))
        {
        ErrorMessage(hwndDlg, TEXT("CoQueryProxyBlanket"), hr);
        }
    else
        {
        hwnd = GetDlgItem(hwndDlg, IDC_PROXY_AUTHN);
        EnableWindow(hwnd, TRUE);
        SelectEntry(hwnd, rgAuthnEntries, cAuthnEntries, dwAuthn);

        hwnd = GetDlgItem(hwndDlg, IDC_PROXY_AUTHZ);
        EnableWindow(hwnd, TRUE);
        SelectEntry(hwnd, rgAuthzEntries, cAuthzEntries, dwAuthz);

        hwnd = GetDlgItem(hwndDlg, IDC_PROXY_AUTHNLEVEL);
        EnableWindow(hwnd, TRUE);
        SelectEntry(hwnd, rgAuthnLevelEntries, cAuthnLevelEntries, dwAuthnLevel);

        hwnd = GetDlgItem(hwndDlg, IDC_PROXY_IMPLEVEL);
        EnableWindow(hwnd, TRUE);
        SelectEntry(hwnd, rgImpLevelEntries, cImpLevelEntries, dwImpLevel);

        SetWindowTextW(GetDlgItem(hwndDlg, IDC_PROXY_PRINCIPLENAME),
            wszPrinciple);
        }
}  // UpdateSecurityFields

// ---------------------------------------------------------------------------
// %%Function: UpdatePropertyFields
// ---------------------------------------------------------------------------
 void
UpdatePropertyFields(HWND hwndDlg, LPMYPROPERTIES pmp)
{
    COLORREF    cr;
    WCHAR       rgchUserName[20];
    HRESULT     hr;

    hr = pmp->GetColor(&cr);
    if (FAILED(hr))
        {
        ErrorMessage(hwndDlg, TEXT("Get Color"), hr);
        }
    else
        {
        s_crCurrent = cr;
        if (s_hbrCurrent != NULL)
            DeleteObject(s_hbrCurrent);
        s_hbrCurrent = CreateSolidBrush(s_crCurrent);
        InvalidateRect(GetDlgItem(hwndDlg, IDC_COLOR), NULL, TRUE);
        }

    hr = pmp->GetUserName(rgchUserName);
    if (FAILED(hr))
        {
        ErrorMessage(hwndDlg, TEXT("Get User Name"), hr);
        }
    else
        {
        SetWindowTextW(GetDlgItem(hwndDlg, IDC_USERNAME), rgchUserName);
        }
}  // UpdatePropertyFields

// ---------------------------------------------------------------------------
// %%Function: ClientDialogProc
// ---------------------------------------------------------------------------
 BOOL CALLBACK
ClientDialogProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static BOOL s_fInitialized = FALSE;
    static LPMYPROPERTIES s_pmp = NULL;
    static COLORREF s_rgcrCustom[16];
    HRESULT     hr;

    switch (message)
        {
        case WM_INITDIALOG:
            {
            HWND    hwnd1, hwnd2;
            int     i, cxScreen, cyScreen;
            RECT    rcDlg;

            cxScreen = GetSystemMetrics(SM_CXFULLSCREEN);
            cyScreen = GetSystemMetrics(SM_CYFULLSCREEN);

            GetWindowRect(hwndDlg, &rcDlg);
            OffsetRect(&rcDlg,
                (cxScreen - rcDlg.right - rcDlg.left)/2,
                (cyScreen - rcDlg.bottom - rcDlg.top)/2);

            MoveWindow(hwndDlg, rcDlg.left, rcDlg.top,
                rcDlg.right-rcDlg.left, rcDlg.bottom-rcDlg.top, TRUE);

            // build the list of servers, select the Remote Server by default
            hwnd1 = GetDlgItem(hwndDlg, IDC_SERVER_CLASS);
            for (i=0; i<cServerEntries; i++)
                {
                SendMessage(hwnd1, CB_INSERTSTRING, i, (LPARAM)rgServerEntries[i].szName);
                SendMessage(hwnd1, CB_SETITEMDATA, i, rgServerEntries[i].dwVal);
                }
            SendMessage(hwnd1, CB_SETCURSEL, 0, 0);

            // build the lists of authentication levels. choose None for the
            // process default. the proxy setting will be retrieved via CoQueryProxyBlanket
            // once the object is instantiated
            hwnd1 = GetDlgItem(hwndDlg, IDC_CLIENT_AUTHNLEVEL);
            hwnd2 = GetDlgItem(hwndDlg, IDC_PROXY_AUTHNLEVEL);
            for (i=0; i<cAuthnLevelEntries; i++)
                {
                SendMessage(hwnd1, CB_INSERTSTRING, i, (LPARAM)rgAuthnLevelEntries[i].szName);
                SendMessage(hwnd1, CB_SETITEMDATA, i, rgAuthnLevelEntries[i].dwVal);
                SendMessage(hwnd2, CB_INSERTSTRING, i, (LPARAM)rgAuthnLevelEntries[i].szName);
                SendMessage(hwnd2, CB_SETITEMDATA, i, rgAuthnLevelEntries[i].dwVal);
                }
            SelectEntry(hwnd1, rgAuthnLevelEntries, cAuthnLevelEntries, RPC_C_AUTHN_LEVEL_NONE);

            // build the lists of impersonation levels. choose Anonymous for the
            // process default. the proxy setting will be retrieved via CoQueryProxyBlanket
            // once the object is instantiated
            hwnd1 = GetDlgItem(hwndDlg, IDC_CLIENT_IMPLEVEL);
            hwnd2 = GetDlgItem(hwndDlg, IDC_PROXY_IMPLEVEL);
            for (i=0; i<cImpLevelEntries; i++)
                {
                SendMessage(hwnd1, CB_INSERTSTRING, i, (LPARAM)rgImpLevelEntries[i].szName);
                SendMessage(hwnd1, CB_SETITEMDATA, i, rgImpLevelEntries[i].dwVal);
                SendMessage(hwnd2, CB_INSERTSTRING, i, (LPARAM)rgImpLevelEntries[i].szName);
                SendMessage(hwnd2, CB_SETITEMDATA, i, rgImpLevelEntries[i].dwVal);
                }
            SelectEntry(hwnd1, rgImpLevelEntries, cImpLevelEntries, RPC_C_IMP_LEVEL_ANONYMOUS);

            // build the list of authorization services. the actual setting will
            // be retrieved via CoQueryProxyBlanket once the object is instantiated,
            // and can be modified after that.
            hwnd1 = GetDlgItem(hwndDlg, IDC_PROXY_AUTHZ);
            for (i=0; i<cAuthzEntries; i++)
                {
                SendMessage(hwnd1, CB_INSERTSTRING, i, (LPARAM)rgAuthzEntries[i].szName);
                SendMessage(hwnd1, CB_SETITEMDATA, i, rgAuthzEntries[i].dwVal);
                }

            // build the list of authentication services. the actual setting will
            // be retrieved via CoQueryProxyBlanket once the object is instantiated,
            // and can be modified after that.
            hwnd1 = GetDlgItem(hwndDlg, IDC_PROXY_AUTHN);
            for (i=0; i<cAuthnEntries; i++)
                {
                SendMessage(hwnd1, CB_INSERTSTRING, i, (LPARAM)rgAuthnEntries[i].szName);
                SendMessage(hwnd1, CB_SETITEMDATA, i, rgAuthnEntries[i].dwVal);
                }
            return 1;
            }

        case WM_SYSCOMMAND:
            if (wParam == SC_CLOSE)
                goto LClose;
            break;

        case WM_COMMAND:
            if (HIWORD(wParam) == CBN_SELCHANGE && s_pmp != NULL)
                {
                UpdateSecurityFields(hwndDlg, s_pmp, TRUE);
                }
            switch (LOWORD(wParam))
                {
                case IDCANCEL:
LClose:
                    if (s_pmp != NULL)
                        {
                        s_pmp->Release();
                        s_pmp = NULL;
                        }
                    if (s_fInitialized == TRUE)
                        {
                        CoUninitialize();
                        s_fInitialized = FALSE;
                        }
                    if (s_hbrCurrent != NULL)
                        {
                        DeleteObject(s_hbrCurrent);
                        s_hbrCurrent = NULL;
                        }
                    EndDialog(hwndDlg, 0);
                    break;

                case IDC_INITIALIZE:
                    hr = CoInitialize(NULL);
                    if (FAILED(hr))
                        {
                        ErrorMessage(hwndDlg, TEXT("CoInitialize"), hr);
                        }
                    else
                        {
                        hr = CoInitializeSecurity(NULL,
                            -1,
                            NULL,
                            NULL,
                            GetField(hwndDlg, IDC_CLIENT_AUTHNLEVEL),
                            GetField(hwndDlg, IDC_CLIENT_IMPLEVEL),
                            NULL,
                            0,
                            NULL);
                        if (FAILED(hr))
                            {
                            ErrorMessage(hwndDlg, TEXT("CoInitializeSecurity"), hr);
                            }
                        else
                            {
                            // Disable Initialization Step (#1)
                            EnableWindow(GetDlgItem(hwndDlg, IDC_INITIALIZE), FALSE);
                            EnableWindow(GetDlgItem(hwndDlg, IDC_CLIENT_AUTHNLEVEL), FALSE);
                            EnableWindow(GetDlgItem(hwndDlg, IDC_CLIENT_IMPLEVEL), FALSE);

                            // Enable Object Creation Step (#2)
                            EnableWindow(GetDlgItem(hwndDlg, IDC_SERVER_CLASS), TRUE);
                            EnableWindow(GetDlgItem(hwndDlg, IDC_MACHINENAME), TRUE);
                            EnableWindow(GetDlgItem(hwndDlg, IDC_CREATE), TRUE);
                            s_fInitialized = TRUE;
                            }
                        }
                    break;
                        
                case IDC_CREATE:
                    {
                    OLECHAR rgchName[MAX_PATH];
                    LPCLASSFACTORY  pcf;
                    COSERVERINFO    csi, *pcsi;
                    CLSID   *pclsid;
                    HWND    hwnd;
                    int     iCur;

                    // retrieve the class to instantiate
                    hwnd = GetDlgItem(hwndDlg, IDC_SERVER_CLASS);
                    iCur = SendMessage(hwnd, CB_GETCURSEL, 0, 0);
                    pclsid = (LPCLSID)SendMessage(hwnd, CB_GETITEMDATA, iCur, 0);

                    // retrieve the machine name to run the server on. if this
                    // is blank or ".", instantiate locally by passing a NULL ComServerInfo
                    memset(&csi, 0, sizeof(COSERVERINFO));
                    csi.pwszName = rgchName;
                    GetWindowTextW(GetDlgItem(hwndDlg, IDC_MACHINENAME),
                        rgchName, RGSIZEOF(rgchName));
                    if (lstrlenW(rgchName) == 0 || lstrcmpiW(rgchName, L".") == 0)
                        pcsi = NULL;
                    else
                        pcsi = &csi;

                    // create the object
                    hr = CoGetClassObject(*pclsid, CLSCTX_SERVER,
                        pcsi, IID_IClassFactory, (void**)&pcf);
                    if (FAILED(hr))
                        {
                        ErrorMessage(hwndDlg, TEXT("CoGetClassObject"), hr);
                        break;
                        }
                    hr = pcf->CreateInstance(NULL, IID_IMyProperties, (void**)&s_pmp);
                    pcf->Release();
                    if (FAILED(hr))
                        {
                        ErrorMessage(hwndDlg, TEXT("IClassFactory::CreateInstance"), hr);
                        break;
                        }

                    // Allow a different instance to get created only if the Release
                    // button is pushed first
                    EnableWindow(GetDlgItem(hwndDlg, IDC_CREATE), FALSE);
                    EnableWindow(GetDlgItem(hwndDlg, IDC_SERVER_CLASS), FALSE);
                    EnableWindow(GetDlgItem(hwndDlg, IDC_MACHINENAME), FALSE);
                    EnableWindow(GetDlgItem(hwndDlg, IDC_RELEASE), TRUE);

                    // Enable manipulation of the object's properties. Allow
                    // this even if the values of the object's call-security
                    // parameters can not be determined, due to errors in
                    // UpdateSecurityFields
                    EnableWindow(GetDlgItem(hwndDlg, IDC_CHOOSECOLOR), TRUE);
                    EnableWindow(GetDlgItem(hwndDlg, IDC_USERNAME), TRUE);

                    UpdateSecurityFields(hwndDlg, s_pmp, FALSE);
                    UpdatePropertyFields(hwndDlg, s_pmp);
                    break;
                    }

                case IDC_RELEASE:
                    s_pmp->Release();
                    s_pmp = NULL;

                    // Disable manipulating the properties and selecting the call
                    // security parameters
                    EnableWindow(GetDlgItem(hwndDlg, IDC_CHOOSECOLOR), FALSE);
                    EnableWindow(GetDlgItem(hwndDlg, IDC_USERNAME), FALSE);
                    EnableWindow(GetDlgItem(hwndDlg, IDC_PROXY_AUTHN), FALSE);
                    EnableWindow(GetDlgItem(hwndDlg, IDC_PROXY_AUTHN), FALSE);
                    EnableWindow(GetDlgItem(hwndDlg, IDC_PROXY_AUTHNLEVEL), FALSE);
                    EnableWindow(GetDlgItem(hwndDlg, IDC_PROXY_IMPLEVEL), FALSE);

                    // Enable a new object to be created
                    EnableWindow(GetDlgItem(hwndDlg, IDC_RELEASE), FALSE);
                    EnableWindow(GetDlgItem(hwndDlg, IDC_CREATE), TRUE);
                    EnableWindow(GetDlgItem(hwndDlg, IDC_SERVER_CLASS), TRUE);
                    EnableWindow(GetDlgItem(hwndDlg, IDC_MACHINENAME), TRUE);
                    break;

                case IDC_CHOOSECOLOR:
                    {
                    CHOOSECOLOR cc;

                    cc.lStructSize = sizeof(CHOOSECOLOR);
                    cc.hwndOwner = hwndDlg;
                    cc.rgbResult = s_crCurrent;
                    cc.lpCustColors = s_rgcrCustom;
                    cc.Flags = CC_RGBINIT | CC_SHOWHELP;

                    if (ChooseColor(&cc))
                        {
                        hr = s_pmp->PutColor(cc.rgbResult);
                        if (FAILED(hr))
                            {
                            ErrorMessage(hwndDlg, TEXT("Put Color"), hr);
                            }
                        else
                            {
                            UpdatePropertyFields(hwndDlg, s_pmp);
                            }
                        }
                    break;
                    }

                case IDC_USERNAME:
                    {
                    static s_fDirty = FALSE;

                    if (HIWORD(wParam) == EN_CHANGE)
                        {
                        s_fDirty = TRUE;
                        }
                    else if (HIWORD(wParam) == EN_KILLFOCUS && s_fDirty)
                        {
                        WCHAR   rgchUserName[20];

                        GetWindowTextW(GetDlgItem(hwndDlg, IDC_USERNAME), rgchUserName, 20);
                        hr = s_pmp->PutUserName(rgchUserName);
                        if (FAILED(hr))
                            ErrorMessage(hwndDlg, TEXT("Put User Name"), hr);
                        UpdatePropertyFields(hwndDlg, s_pmp);
                        s_fDirty = FALSE;
                        }
                    break;
                    }
                }
            break;

        case WM_DRAWITEM:
            {
            LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT)lParam;

            FillRect(lpdis->hDC, &lpdis->rcItem,
                s_hbrCurrent != NULL ? s_hbrCurrent : (HBRUSH)GetStockObject(WHITE_BRUSH));
            FrameRect(lpdis->hDC, &lpdis->rcItem, (HBRUSH)GetStockObject(BLACK_BRUSH));
            if (lpdis->itemState & ODS_SELECTED)
                InvertRect(lpdis->hDC, (LPRECT)&lpdis->rcItem);
            if (lpdis->itemState & ODS_FOCUS)
                DrawFocusRect(lpdis->hDC, (LPRECT) &lpdis->rcItem);
            return TRUE;
            }
        }
    return FALSE;
}  // ClientDialogProc

// ---------------------------------------------------------------------------
// %%Function: WinMain
// ---------------------------------------------------------------------------
 int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_SECCLNT), GetDesktopWindow(), (DLGPROC)ClientDialogProc);
}  // WinMain

// EOF =======================================================================

