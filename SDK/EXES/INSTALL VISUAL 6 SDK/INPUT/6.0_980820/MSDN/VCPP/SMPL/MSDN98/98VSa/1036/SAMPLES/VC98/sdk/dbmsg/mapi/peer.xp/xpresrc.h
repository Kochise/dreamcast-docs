/*
 -  R E S O U R C E . H
 -
 *  Resource definitions for the Sample Transport Provider.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

/*   DialogBox IDs  */

#define GeneralPage                     100
#define PeerPage                        200
#define LoggingPage                     300
#define PerMsgOpt                       400
#define PerRecipOpt                     500


/*   EditText IDs   */

#define IDE_DISPLAY                     106
#define IDE_EMAIL_TYPE                  107
#define IDE_EMAIL_ADDR                  108
#define IDE_IN_DIR                      109
#define IDE_OUT_DIR                     110
#define IDE_WGAP_FNAME                  112
#define IDE_WGAP_DIR                    114
#define IDE_LOG_NAME                    118
#define IDE_LOG_HIGH                    119
#define IDE_LOG_LOW                     120

/*  CheckBox IDs    */

#define IDC_PEER                        121
#define IDC_LOGON_UI                    122
#define IDC_LOG_EVENTS                  123
#define IDC_SAVE_DIALOG                 124
#define IDC_PER_MSG_DEFER               125
#define IDC_PER_RECIP_DEFER             126

/* Static Label IDs */

#define IDT_WGAP_FNAME                  127
#define IDT_WGAP_DIR                    128
#define IDT_DISPLAY                     129
#define IDT_EMAIL_TYPE                  130
#define IDT_EMAIL_ADDR                  131
#define IDT_IN_DIR                      132
#define IDT_OUT_DIR                     133
#define IDT_LOG_NAME                    134
#define IDT_LOG_HIGH                    135
#define IDT_LOG_LOW                     136

/* String Table IDs */

/* Error messages offset and strings */

#define LIB_ERRORS                      1000
#define IDS_SUCCESS                     1000
#define IDS_E_BUSY                      1001
#define IDS_E_CALL_FAILED               1002
#define IDS_E_INVALID_PARAMETER         1003
#define IDS_E_NO_ACCESS                 1004
#define IDS_E_NO_SUPPORT                1005
#define IDS_E_NOT_FOUND                 1006
#define IDS_E_UNKNOWN_FLAGS             1007
#define IDS_E_VERSION                   1008
#define IDS_E_NOT_ENOUGH_MEMORY         1009
#define IDS_W_ERRORS_RETURNED           1010
#define IDS_NO_DISPLAY_NAME             1011
#define IDS_NO_ADDR_TYPE                1012
#define IDS_NO_EMAIL_ADDRESS            1013
#define IDS_NO_INBOUND_DIR              1014
#define IDS_NO_OUTBOUND_DIR             1015
#define IDS_BAD_EMAIL_ADDRESS           1016
#define IDS_BAD_INBOUND_DIR             1017
#define IDS_UNC_DIR_MISMATCH            1018
#define IDS_UNKNOWN_ERROR               1999

/* Report Text */

#define IDS_REPORT_TEXT_MSG             2001

/* Status Table Strings */

#define LIB_STATUS                      3000
#define IDS_STATUS_OFFLINE              3000
#define IDS_STATUS_AVAILABLE            3001
#define IDS_STATUS_ONLINE               3002
#define IDS_STATUS_UPLOADING            3003
#define IDS_STATUS_DOWNLOADING          3004
#define IDS_STATUS_INFLUSHING           3005
#define IDS_STATUS_OUTFLUSHING          3006

/* Configuration dialog title */

#define IDS_CONFIG_TITLE                4001
#define IDS_BAD_LOGON_PROPS_TITLE       4002
#define IDS_BAD_LOGON_PROPS_FORMAT      4003

/* Wizard IDs */

enum {ipgName, ipgType, ipgInbox, ipgPath, cpageMax };
#define WIZ_BASE                        5000
#define IDC_NameText                    5010
#define IDC_NameLbl                     5011
#define IDC_NameEdit                    5012
#define IDC_TypeText                    5020
#define IDC_TypeLbl                     5021
#define IDC_TypeEdit                    5022
#define IDC_UNCText                     5030
#define IDC_UNCLbl                      5031
#define IDC_UNCEdit                     5032
#define IDC_PathText                    5040
#define IDC_PathLbl                     5041
#define IDC_PathEdit                    5042
