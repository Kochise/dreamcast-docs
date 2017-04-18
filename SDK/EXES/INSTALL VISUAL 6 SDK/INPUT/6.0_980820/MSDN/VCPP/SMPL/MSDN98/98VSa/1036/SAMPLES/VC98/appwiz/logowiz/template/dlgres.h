//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by $$ROOT$$.RC
//
$$IF(PRESS_ME_DIALOG)
#define IDB_SMILE_UP                    120
#define IDB_SMILE_DOWN                  121
#define IDB_SMILE_FOCUS                 122
#define IDB_FROWN_UP                    123
#define IDB_FROWN_DOWN                  124
#define IDB_FROWN_FOCUS                 125
$$ENDIF //PRESS_ME_DIALOG
$$IF(PROJTYPE_DLG)
#define IDR_MAINFRAME                   128
$$IF(ABOUT)
#define IDM_ABOUTBOX                    0x0010
#define IDD_ABOUTBOX                    100
$$ENDIF //ABOUT
$$IF(AUTOMATION)
#define IDP_OLE_INIT_FAILED             100
$$ENDIF //AUTOMATION
$$IF(ABOUT)
#define IDS_ABOUTBOX                    101
$$ENDIF //ABOUT
#define IDD_$$SAFE_ROOT$$_DIALOG                102
$$ENDIF //PROJTYPE_DLG
$$IF(SOCKETS)
$$IF(PROJTYPE_DLG)
#define IDP_SOCKETS_INIT_FAILED         103
$$ELSE //!PROJTYPE_DLG (i.e., PROJTYPE_DLL)
#define IDP_SOCKETS_INIT_FAILED         101
$$ENDIF //PROJTYPE_DLG
$$ENDIF //SOCKETS
$$IF(PROJTYPE_DLG)
$$IF(PRESS_ME_DIALOG)
#define IDD_PRESS_ME                    104
#define IDC_PRESS_ME                    105
$$ENDIF  //PRESS_ME
$$ENDIF //PROJTYPE_DLG

// Next default values for new objects
//
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS

$$IF(PROJTYPE_DLL || PROJTYPE_OCX)
#define _APS_NEXT_RESOURCE_VALUE    $$START_RES$$
#define _APS_NEXT_CONTROL_VALUE     $$START_RES$$
#define _APS_NEXT_SYMED_VALUE       $$START_RES$$
$$ELSE
#define _APS_NEXT_RESOURCE_VALUE    129
#define _APS_NEXT_CONTROL_VALUE     1000
#define _APS_NEXT_SYMED_VALUE       101
$$ENDIF
#define _APS_NEXT_COMMAND_VALUE     32771
#endif
#endif
