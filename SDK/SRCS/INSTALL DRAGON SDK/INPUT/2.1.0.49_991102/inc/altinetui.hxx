#ifndef __ALTNETUI_HXX_
#define __ALTNETUI_HXX_



#define IDS_FTP_ROOT                    28
#define IDS_FTP_DIR                     29
#define IDS_FTP_UPLEVEL                 30
#define IDS_TAG_DIRECTORY               35
#define IDS_TAG_SEARCH                  36
#define IDS_CACHE_DEFAULT_SUBDIR        37
#define IDS_COOKIES_DEFAULT_SUBDIR      38
#define IDS_HISTORY_DEFAULT_SUBDIR      39
#define IDD_CERTPICKER                  101
#define IDD_INVALID_CA                  102
#define IDD_CONFIRM_COOKIE              104
#define IDI_COOKIE_ICON                 105
#define IDD_GOONLINE                    110
#define IDC_GOONLINE_TOPMESSAGE         111
#define IDS_GOONLINE_REFRESH_CAPTION    112
#define IDS_GOONLINE_REFRESH_TOPMESSAGE 113
#define IDI_SECURITY1                   116
#define IDD_HTTP_POST_REDIRECT          117
#define IDI_SECURITY2                   118
#define IDI_SECURITY3                   119
#define IDD_CERT_EXPIRED                121
#define IDB_DIAL                        122
#define IDC_DONT_WANT_WARNING           1001
#define IDC_COOKIE_DATA                 1010
#define IDC_COOKIE_ALLOW_ALL            1013
#define IDC_COOKIE_NAME                 1014
#define IDC_COOKIE_DOMAIN               1016
#define IDC_COOKIE_PATH                 1017
#define IDC_COOKIE_EXPIRES              1018
#define IDC_COOKIE_SECURE               1019
#define IDC_COOKIE_SERVER               1021
#define IDC_COOKIE_ICON                 1022
#define IDC_COOKIE_INFO                 1023
#define IDC_SAVE_PASSWORD               1024
#define ID_CONNECT                      1026
#define IDC_URL                         1027
#define ID_STAYOFFLINE                  1028
#define IDD_WARN_ON_POST                1175
#define IDD_HTTP_TO_HTTPS_ZONE_CROSSING 1177
#define IDD_HTTPS_TO_HTTP_ZONE_CROSSING 1178
#define IDD_MIXED_SECURITY              1179
#define IDD_BAD_CN                      1188
#define IDD_BASIC_AUTHENTICATION        1216
#define IDC_REALM_NAME                  1217
#define IDC_USERNAME                    1218
#define IDC_PASSWORD                    1219
#define IDD_HTTPS_TO_HTTP_SUBMIT_REDIRECT 1303
#define IDS_SETTING_COOKIE              1800
#define IDS_SETTING_COOKIE_TITLE        1801
#define IDS_YES                         1802
#define IDS_NO                          1803
#define IDS_COOKIE_EXPIRES_ENDSESSION   1804
#ifdef WEB_TELEPHONE
#define IDS_WEBPHONE_SECERR				4013
#endif
// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        123
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1041
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif


// useful macro
#define ARRAYSIZE(a)         (sizeof(a)/sizeof(a[0]))

#define IDS_AUTODIAL_CONFIRM_TITLE  200
#define IDS_AUTODIAL_CONFIRM_TEXT   201
#define IDM_AUTODIAL_CONFIRM		202

#define IDS_ACCESS_DENIED			103
#define	IDM_ACCESS_DENIED			251


#endif //_ALTNETUI_HXX_

