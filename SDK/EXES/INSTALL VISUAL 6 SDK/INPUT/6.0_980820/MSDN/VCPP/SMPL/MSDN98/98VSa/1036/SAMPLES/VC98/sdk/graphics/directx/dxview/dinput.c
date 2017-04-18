/****************************************************************************

    Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.

    PROGRAM: dinput.c

    PURPOSE: DirectX Device Viewer - DirectInput module

    FUNCTIONS:

    COMMENTS:

****************************************************************************/

#include "dxview.h"

#define DICAPDEF(name,val,flag) {name, FIELD_OFFSET(DIDEVCAPS,val), flag}
#define DIVALDEF(name,val)      {name, FIELD_OFFSET(DIDEVCAPS,val), 0}

/****************************************************************************
 *
 *  DI_CreateDI
 *
 *  Create a DirectInput pointer.  Try the current DirectInput version
 *  first; if that doesn't work, try version 3.0.
 *
 ****************************************************************************/

LPDIRECTINPUT
DI_CreateDI(void)
{
    LPDIRECTINPUT pdi;

    if (SUCCEEDED(DirectInputCreate(g_hInstance, DIRECTINPUT_VERSION,
                                    &pdi, NULL))) {
    } else
    if (SUCCEEDED(DirectInputCreate(g_hInstance, 0x0300,
                                    &pdi, NULL))) {
    } else {
        pdi = 0;
    }

    return pdi;
}

/****************************************************************************
 *
 *  DI_CreateDevice
 *
 *  Create a device with the specified instance GUID.
 *
 ****************************************************************************/

LPDIRECTINPUTDEVICE
DI_CreateDevice(LPCGUID pguid)
{
    LPDIRECTINPUT pdi;
    LPDIRECTINPUTDEVICE pdev;

    pdi = DI_CreateDI();
    if (pdi) {
        if (SUCCEEDED(IDirectInput_CreateDevice(pdi, pguid, &pdev, NULL))) {
        } else {
            pdev = 0;
        }
        IDirectInput_Release(pdi);
    } else {
        pdev = 0;
    }
    return pdev;
}

/****************************************************************************
 *
 *  DI3Info
 *
 *      Structure that describes the caps maintained by DIDEVCAPS
 *      that existed in DirectX 3.
 *
 ****************************************************************************/

CAPDEF DI3Info[] =
{
    DIVALDEF("Axes",                dwAxes),
    DIVALDEF("Buttons",             dwButtons),
    DIVALDEF("POVs",                dwPOVs),

    DICAPDEF("ATTACHED",            dwFlags,        DIDC_ATTACHED),
    DICAPDEF("POLLEDDEVICE",        dwFlags,        DIDC_POLLEDDEVICE),
    DICAPDEF("EMULATED",            dwFlags,        DIDC_EMULATED),

    {"", 0, 0}
};

/****************************************************************************
 *
 *  DI5Info
 *
 *      Structure that describes the caps maintained by DIDEVCAPS
 *      that exist in DirectX 5 and were't in DirectX 3.
 *
 ****************************************************************************/

CAPDEF DI5Info[] =
{
    DICAPDEF("FORCEFEEDBACK",       dwFlags,        DIDC_FORCEFEEDBACK),
    DICAPDEF("FFATTACK",            dwFlags,        DIDC_FFATTACK),
    DICAPDEF("FFFADE",              dwFlags,        DIDC_FFFADE),
    DICAPDEF("SATURATION",          dwFlags,        DIDC_SATURATION),
    DICAPDEF("POSNEGCOEFFICIENTS",  dwFlags,        DIDC_POSNEGCOEFFICIENTS),
    DICAPDEF("POSNEGSATURATION",    dwFlags,        DIDC_POSNEGSATURATION),

    DIVALDEF("FFSamplePeriod",      dwFFSamplePeriod),
    DIVALDEF("FFMinTimeResolution", dwFFMinTimeResolution),
    {"", 0, 0}
};

/****************************************************************************
 *
 *  DISubTypeList
 *
 *      List of various DirectInput device subtypes and their names.
 *
 ****************************************************************************/

typedef struct SUBTYPEINFO {
    DWORD dwDevType;
    LPCTSTR pszName;
} SUBTYPEINFO;

#define SUBTYPE(type, subtype, name)    \
    {   MAKEWORD(DIDEVTYPE_##type, \
        DIDEVTYPE##type##_##subtype), \
        TEXT("%d - ") TEXT(name) }

SUBTYPEINFO DISubTypes[] = {
    SUBTYPE(MOUSE,          UNKNOWN,            "Unknown"),
    SUBTYPE(MOUSE,          TRADITIONAL,        "Traditional"),
    SUBTYPE(MOUSE,          FINGERSTICK,        "Fingerstick"),
    SUBTYPE(MOUSE,          TOUCHPAD,           "Touchpad"),
    SUBTYPE(MOUSE,          TRACKBALL,          "Trackball"),

    SUBTYPE(KEYBOARD,       UNKNOWN,            "Unknown"),
    SUBTYPE(KEYBOARD,       PCXT,               "XT"),
    SUBTYPE(KEYBOARD,       OLIVETTI,           "Olivetti"),
    SUBTYPE(KEYBOARD,       PCAT,               "AT"),
    SUBTYPE(KEYBOARD,       PCENH,              "Enhanced"),
    SUBTYPE(KEYBOARD,       NOKIA1050,          "Nokia 1050"),
    SUBTYPE(KEYBOARD,       NOKIA9140,          "Nokia 9140"),
    SUBTYPE(KEYBOARD,       NEC98,              "NEC98"),
    SUBTYPE(KEYBOARD,       NEC98LAPTOP,        "NEC98 Laptop"),
    SUBTYPE(KEYBOARD,       NEC98106,           "NEC98 106"),
    SUBTYPE(KEYBOARD,       JAPAN106,           "Japan 106"),
    SUBTYPE(KEYBOARD,       JAPANAX,            "Japan AX"),
    SUBTYPE(KEYBOARD,       J3100,              "J3100"),

    SUBTYPE(JOYSTICK,       UNKNOWN,            "Unknown"),
    SUBTYPE(JOYSTICK,       TRADITIONAL,        "Traditional"),
    SUBTYPE(JOYSTICK,       FLIGHTSTICK,        "Flightstick"),
    SUBTYPE(JOYSTICK,       GAMEPAD,            "Gamepad"),
    SUBTYPE(JOYSTICK,       RUDDER,             "Rudder"),
    SUBTYPE(JOYSTICK,       WHEEL,              "Wheel"),
    SUBTYPE(JOYSTICK,       HEADTRACKER,        "Head tracker"),
    { 0, 0 },
};

/****************************************************************************
 *
 *  DIAddRow
 *
 *  Add a row to the growing two-column listview or printer.
 *
 *      lpInfo = print context or NULL if adding to listview
 *      pszName = name of cap
 *      pszFormat = wsprintf-style format string
 *      ... = inserts for wsprintf
 *
 ****************************************************************************/

BOOL __cdecl
DIAddRow(PRINTCBINFO *lpInfo, LPCTSTR pszName, LPCTSTR pszFormat, ...)
{
    BOOL fRc;
    TCHAR szBuf[1024];
    int cch;
    va_list ap;

    va_start(ap, pszFormat);
    cch = wvsprintf(szBuf, pszFormat, ap);
    va_end(ap);

    if (lpInfo == NULL) {
        LVAddText(g_hwndLV, 0, pszName, 0);
        LVAddText(g_hwndLV, 1, TEXT("%s"), szBuf);
    } else {
        int xName, xVal, yLine;

        // Calculate Name and Value column x offsets
        xName   = (lpInfo->dwCurrIndent * DEF_TAB_SIZE * lpInfo->dwCharWidth);
        xVal    = xName + (32 * lpInfo->dwCharWidth);
        yLine = lpInfo->dwCurrLine * lpInfo->dwLineHeight;

        // Print name
        fRc = PrintLine(xName, yLine, pszName, lstrlen(pszName), lpInfo);
        if (!fRc) goto done;

        // Print value
        fRc = PrintLine(xVal, yLine, szBuf, cch, lpInfo);
        if (!fRc) goto done;

        // Advance to next line on page
        fRc = PrintNextLine(lpInfo);
        if (!fRc) goto done;
    }

    fRc = TRUE;

done:;
    return fRc;
}

/****************************************************************************
 *
 *  DIAddTypes
 *
 *  Emit the device type information to the output device.
 *
 *      lpInfo = print context or NULL if adding to listview
 *      dwDevType = device type to decode
 *
 ****************************************************************************/

BOOL DIAddTypes(PRINTCBINFO *lpInfo, DWORD dwDevType)
{
    BOOL fRc;
    DWORD dwType;
    LPCTSTR pszValue;
    SUBTYPEINFO *psti;

    /*
     *  Add the type code.
     */

    dwType = GET_DIDEVICE_TYPE(dwDevType);
    switch (dwType) {
    case DIDEVTYPE_MOUSE:   pszValue = TEXT("%d - Mouse"); break;
    case DIDEVTYPE_KEYBOARD:pszValue = TEXT("%d - Keyboard"); break;
    case DIDEVTYPE_JOYSTICK:pszValue = TEXT("%d - Joystick"); break;
    default:                pszValue = TEXT("%d"); break;
    }

    fRc = DIAddRow(lpInfo, "Type", pszValue, dwType);
    if (!fRc) goto done;

    /*
     *  Add the sub type code.
     */

    pszValue = TEXT("%d");
    for (psti = DISubTypes; psti->dwDevType; psti++) {
        if (psti->dwDevType == (dwDevType & 0xFFFF)) {
            pszValue = psti->pszName;
            break;
        }
    }

    fRc = DIAddRow(lpInfo, TEXT("Subtype"), pszValue,
                   GET_DIDEVICE_SUBTYPE(dwDevType));
    if (!fRc) goto done;

    fRc = TRUE;
done:;
    return fRc;
}

/****************************************************************************
 *
 *  DIAddCapsToTarget
 *
 *  Add the caps either to the listview or to the printer.
 *
 *      lpInfo = print context or NULL if adding to listview
 *      pcd = pointer to CAPDEF array describing the caps
 *      pv = pointer to structure to be parsed
 *
 ****************************************************************************/

BOOL
DIAddCapsToTarget(PRINTCBINFO *lpInfo, CAPDEF *pcd, LPVOID pv)
{
    BOOL fRc;

    if (lpInfo) {
        fRc = PrintCapsToDC(pcd, pv, lpInfo);
    } else {
        AddMoreCapsToLV(pcd, pv);
        fRc = TRUE;
    }
    return fRc;
}

/****************************************************************************
 *
 *  DIPrintCaps
 *
 *      lpInfo = print context or NULL if adding to listview
 *      lParam1 = state info recorded by DIEnumDevCallback (LPGUID)
 *      lParam2 = refdata (not used)
 *
 ****************************************************************************/

BOOL
DIPrintCaps(LPARAM lParam1, LPARAM lParam2, PRINTCBINFO *lpInfo)
{
    BOOL fRc;
    LPGUID pguid = (LPGUID)lParam1;
    LPDIRECTINPUTDEVICE pdev;

    if (lpInfo == NULL) {
        AddColsToLV();
    }

    fRc = TRUE;

    pdev = DI_CreateDevice(pguid);

    if (pdev) {
        DIDEVCAPS caps;
        HRESULT hres;

        /*
         *  First use the DX3 caps.
         */
        caps.dwSize = sizeof(DIDEVCAPS_DX3);

        hres = IDirectInputDevice_GetCapabilities(pdev, &caps);
        if (SUCCEEDED(hres)) {

            fRc = DIAddTypes(lpInfo, caps.dwDevType) &&
                  DIAddCapsToTarget(lpInfo, DI3Info, &caps);
        }

        /*
         *  Now get the DX5 caps if we haven't cancelled printing yet.
         */
        if (fRc) {
            caps.dwSize = sizeof(DIDEVCAPS);

            hres = IDirectInputDevice_GetCapabilities(pdev, &caps);
            if (SUCCEEDED(hres)) {

                fRc = DIAddCapsToTarget(lpInfo, DI5Info, &caps);
            }
        }

        IDirectInputDevice_Release(pdev);
    }
    return fRc;
}

/****************************************************************************
 *
 *  DIAddCaps
 *
 *      lParam1 = state info recorded by DIEnumDevCallback (LPGUID)
 *      lParam2 = refdata (not used)
 *
 ****************************************************************************/

void
DIAddCaps(LPARAM lParam1, LPARAM lParam2)
{
    DIPrintCaps(lParam1, lParam2, NULL);
}

/****************************************************************************
 *
 *  DIEnumEffCallback
 *
 *  Add the enumerated DirectInput effect to the listview.
 *
 ****************************************************************************/

BOOL CALLBACK
DIEnumEffCallback(LPCDIEFFECTINFO pei, LPVOID lpInfo)
{
    BOOL fRc;
    const GUID *pguid = &pei->guid;

    fRc = DIAddRow(lpInfo, pei->tszName,
                   TEXT("{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}"),
                    pguid->Data1, pguid->Data2, pguid->Data3,
                    pguid->Data4[0], pguid->Data4[1],
                    pguid->Data4[2], pguid->Data4[3],
                    pguid->Data4[4], pguid->Data4[5],
                    pguid->Data4[6], pguid->Data4[7]);
    if (fRc) {
        return DIENUM_CONTINUE;
    } else {
        return DIENUM_STOP;
    }
}

/****************************************************************************
 *
 *  DIPrintEffects
 *
 *      lpInfo = print context or NULL if adding to listview
 *      lParam1 = state info recorded by DIEnumDevCallback (LPGUID)
 *      lParam2 = refdata (not used)
 *
 ****************************************************************************/

BOOL
DIPrintEffects(LPARAM lParam1, LPARAM lParam2, PRINTCBINFO *lpInfo)
{
    BOOL fRc;
    LPGUID pguid = (LPGUID)lParam1;
    LPDIRECTINPUTDEVICE pdev;

    /*
     *  The effects are not a simple name/value thing.
     *  But DXView doesn't like multiple nesting levels,
     *  so we mash it into the name/value paradigm
     *  because I'm lazy.  Someday I won't be quite so
     *  lazy and do it right.
     */

    if (lpInfo == NULL) {
        AddColsToLV();
    }

    fRc = TRUE;
    pdev = DI_CreateDevice(pguid);

    if (pdev) {
        LPDIRECTINPUTDEVICE2 pdev2;
        HRESULT hres;

        hres = IDirectInputDevice_QueryInterface(
                        pdev, &IID_IDirectInputDevice2, (LPVOID *)&pdev2);

        if (SUCCEEDED(hres)) {
            /*
             *  Enumerate the effects and add them to the listview.
             */
            IDirectInputDevice2_EnumEffects(pdev2,
                                            DIEnumEffCallback, lpInfo,
                                            DIEFT_ALL);

            IDirectInputDevice2_Release(pdev2);
        }

        IDirectInputDevice_Release(pdev);
    }

    return fRc;
}

/****************************************************************************
 *
 *  DIAddEffects
 *
 *      lParam1 = state info recorded by DIEnumDevCallback (LPGUID)
 *      lParam2 = refdata (not used)
 *
 ****************************************************************************/

void
DIAddEffects(LPARAM lParam1, LPARAM lParam2)
{
    DIPrintEffects(lParam1, lParam2, NULL);
}

/****************************************************************************
 ***************************************************************************/

CAPDEFS DICapDefs[] =
{
    {"",                    DIAddCaps,          0,              DIPrintCaps},
    {"Effects",             DIAddEffects,       0,              DIPrintEffects},
    {NULL, 0, 0, NULL}
};

/****************************************************************************
 *
 *  DIEnumDevCallback
 *
 *  Add the enumerated DirectInput device to the treeview.
 *
 ****************************************************************************/

BOOL CALLBACK
DIEnumDevCallback(LPCDIDEVICEINSTANCE pinst, LPVOID pv)
{
    HTREEITEM hParent = pv;
    TCHAR     szText[MAX_PATH + 2 + MAX_PATH + 2];
    LPGUID    pguid;

    pguid = LocalAlloc(LPTR, sizeof(GUID));
    if (pguid == NULL) {
        return DIENUM_STOP;
    }

    *pguid = pinst->guidInstance;

    wsprintf(szText, "%s (%s)", pinst->tszInstanceName,
                                pinst->tszProductName);

    DICapDefs[0].szName = szText;
    AddCapsToTV(hParent, DICapDefs, (LPARAM)pguid);

    return(DIENUM_CONTINUE);
}

/****************************************************************************
 *
 *  DI_FillTree
 *
 *  Add the DirectInput nodes to the treeview.
 *
 ****************************************************************************/

void
DI_FillTree(void)
{
    LPDIRECTINPUT pdi;
    HTREEITEM hTree;

    // Add direct input devices if DInput is found

    pdi = DI_CreateDI();
    if (pdi) {

        hTree = TVAddNode(TVI_ROOT, "DirectInput Devices", TRUE,
                          IDI_DIRECTX, NULL, 0, 0, NULL);

        IDirectInput_EnumDevices(pdi, 0, DIEnumDevCallback, hTree,
                                 DIEDFL_ALLDEVICES);

        TreeView_Expand(g_hwndTV, hTree, TVE_EXPAND);

        IDirectInput_Release(pdi);
    }
}
