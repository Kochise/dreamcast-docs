#ifndef __ALTINETUISTRUCT_HXX_
#define __ALTINETUISTRUCT_HXX_


typedef struct {
    DWORD       dwDlgFlags;
    DWORD       dwDlgId;
    BOOL		fUpdateGlobalSecuritySettings;
} ERRORINFODLGTYPE, *PERRORINFODLGTYPE;

//
// REPLACEABLE_UI Galahad vladimi: Need info on IDC_COOKIE_ALLOW_ALL
// so code calling CookieDlgProc can update registry based on it
//
typedef struct _COOKIE_DLG_INFO {
    LPSTR pszServer;
    //DWORD cbSize;
    LPSTR pszName;
    LPSTR pszData;
    LPSTR pszDomain;
    LPSTR pszPath;
    FILETIME *pftExpires;
    DWORD dwFlags;
    INT     cx;
    INT     cy;
	BOOL	fAllowAllCookies;
} COOKIE_DLG_INFO, *PCOOKIE_DLG_INFO;

typedef struct _offline_dlgparams {
    LPTSTR lpszURL;
    DWORD dwFlags;
} OFFLINE_DLGPARAMS;

#endif //_ALTINETUI_HXX_

