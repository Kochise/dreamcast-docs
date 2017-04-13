//----------------------------------------------------------------------
//       Copyright (C) 1993-1997 Microsoft Corporation.
//       All rights reserved.
//----------------------------------------------------------------------

//----------------------------------------------------------------------
//	WebPost API usage example
//
//  This example allows the user to post files to a web site.
//
//----------------------------------------------------------------------

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <tchar.h>

#include <wpapi.h>
#include <wpspi.h>

#include "wbpost.h"

//global buffer for holding the error message
TCHAR	g_rgchErr[MAX_PATH];

//you can always call WpGetErrorString to get the full error string text.
VOID
GetErrorString(LONG lErr)
{
	DWORD	dwErr;
	LONG	lRet;

	dwErr=MAX_PATH;

	lRet=WpGetErrorString(
		(UINT)lErr,			//uErrCode
		(LPTSTR)g_rgchErr,	//sOutputBuf
		&dwErr);			//pdwBufLen

	if(FAILED(lRet))
		g_rgchErr[0]=NULL;

	return;
}

LONG
SimpleWebPost( LPTSTR lpszFileName )
{
	LONG 	lRet;

	_tprintf("Calling WpPost(...,%s,...)\n", lpszFileName);

	lRet = WpPost(	NULL,		// hWin
			1,		// count of files
			&lpszFileName,	// file list
			NULL,		// lpcbSiteName
			NULL,		// lpszSiteName
			NULL,		// lpcbURL
			NULL,		// lpszURL
			0 );		// flags
	
	GetErrorString(lRet);

	_tprintf("WpPost returned 0x%x which means %s\n", lRet, g_rgchErr);
	
	return lRet;
}

LONG
EnumProviders()
{
	static TCHAR	buffer[8192];
	LPWPPROVINFO	lpbProv;
	DWORD			cProv, cbProv, lRet, i;

	cbProv=sizeof(buffer);
	cProv=0;
	lpbProv=(LPWPPROVINFO)buffer;

	printf("Calling WpEnumProviders()\n");

	lRet=WpEnumProviders(&cbProv,	//pdwProvidersBufLen
		lpbProv,					//pProvidersBuffer
		&cProv);					//pdwNumProviders

	GetErrorString(lRet);

	_tprintf("WpEnumProviders() returned 0x%x which means %s\n", lRet, g_rgchErr);

	if(lRet)
		return lRet;

	printf("Total Providers: %d\n", cProv);

	for(i=0; i<cProv; i++, lpbProv++)
	{
		_tprintf("%d, Name =%s\n", i, lpbProv->lpszProviderName);
		_tprintf("   CLSID=%s\n", lpbProv->lpszProviderCLSID);
		_tprintf("   Path =%s\n", lpbProv->lpszDllPath);
	}

	return lRet;
}


LONG
ListSites()
{
	static TCHAR	buffer[8192];
	LPWPSITEINFO	lpbSites;
	DWORD		cSites, cbSites, lRet, i;

	cbSites = sizeof( buffer );
	cSites = 0;
	lpbSites = (LPWPSITEINFO) buffer;

	printf("Calling WpListSites()\n");

	lRet = WpListSites( &cbSites, lpbSites, &cSites );

	GetErrorString(lRet);

	_tprintf("WpListSites() returned 0x%x which means %s\n", lRet, g_rgchErr);

	if (lRet)
		return lRet;
	
	printf("Total Sites: %d\n", cSites);

	for (i = 0; i < cSites; i++, lpbSites++)
		_tprintf("%d. SiteName=%s\n", i, lpbSites->lpszSiteName);
	
	return lRet;
}

//
// The next function illustrates getting a pointer to the web post
// provider's interface and calling the functions in that interface.
//

LONG
AdvancedWebPost( LPTSTR lpszSiteName, LPTSTR lpszFileName )
{
	LONG	cbURL = 0;
	LONG	lRet;
	LONG	lErrType;
	LONG	lErrBufLen;

	WCHAR	rgwchFileName[MAX_PATH];
	WCHAR	rgwchError[MAX_PATH];
	LPWSTR	lpwFileName;

	IWPProvider	*lpSite = NULL;

	_tprintf("Calling WpBindToSite(..., %s, ...)\n", lpszSiteName);

	lRet = WpBindToSite(NULL,		// hWin
				lpszSiteName,
				NULL,		// lpszURL
				0,		// fdwFlags
				0,		// dwReserved
				(PVOID *)&lpSite );	// Interface pointer

	GetErrorString(lRet);

	_tprintf("WpBindToSite returned 0x%x which means %s\n", lRet, g_rgchErr);

	if (lRet)
		return lRet;

	//note that both the old IWPSite interface and the IWPProvider interface
	//are unicode only.

	lRet = lpSite->NetworkConnect(NULL, NULL);
	printf("NetworkConnect returned 0x%x\n", HRESULT_CODE(lRet));
	if (lRet)
		goto cleanup;

	lRet = lpSite->ServerLogin(NULL, NULL);
	printf("ServerLogin returned 0x%x\n", HRESULT_CODE(lRet));
	if (lRet)
		goto cleanup;
	
	_tprintf("Calling PostFiles(...,%s,..)\n", lpszFileName);

#ifdef _UNICODE
	lpwFileName=lpszFileName;
#else
	MultiByteToWideChar(CP_ACP, 0, lpszFileName, lstrlenA(lpszFileName), rgwchFileName, MAX_PATH);
	lpwFileName=rgwchFileName;
#endif

	lRet = lpSite->PostFiles(	1,	// cLocalPaths
					&lpwFileName,	//this has to be unicode
					&cbURL,	// lpcbURL
					NULL,	// lpszURL
					0 );	// fdwFlags
	
	lErrType=0;
	lErrBufLen=MAX_PATH;
	lpSite->GetError(
		&lErrType,		//pdwErrorType
		&lRet,			//pdwErrorCode
		&lErrBufLen,	//pdwErrorBufLen
		rgwchError);	//wsError

	wprintf(L"PostFiles returned 0x%x which means %s\n", HRESULT_CODE(lRet), rgwchError);

	lRet = lpSite->ServerLogout();
	printf("ServerLogout returned 0x%x\n", HRESULT_CODE(lRet));
	if (lRet)
		goto cleanup;

	lRet = lpSite->NetworkDisconnect();
	printf("NetworkDisconnect returned 0x%x\n", HRESULT_CODE(lRet));

cleanup:
	lRet = lpSite->Release();
	printf("Release returned 0x%x\n", HRESULT_CODE(lRet));

	return lRet;
}

void
usage(void)
{
	printf("Usage: wbpost [-s sitename] [filename]\n");
	printf("       wbpost -l\t: lists the web sites\n");
	printf("       wbpost -e\t: numerates the available providers\n");
	exit(1);
}

int __cdecl
main(int argc, char *argv[])
{
	LPTSTR	lpszSiteName = NULL, lpszFileName = NULL;
	int	fList = 0;
	int	fEnum = 0;
	LONG	lRet;
	char	c;

#ifdef _UNICODE
	WCHAR	rgwch[MAX_PATH];
#endif

	// parse the arguments

	while (--argc > 0 && (*++argv)[0] == '-')
		if (c = *++argv[0])
			switch (c) {
			case 'l':
				fList = 1;
				break;
			case 'e':
				fEnum = 1;
				break;
			case 's':
				if (--argc) {
#ifdef _UNICODE
					MultiByteToWideChar(CP_ACP, 0, *++argv, lstrlenA(*argv), rgwch, MAX_PATH);
					lpszSiteName=rgwch;
#else
					lpszSiteName = *++argv;
#endif
				}
				break;
			default:
				printf("Error: illegal option %c\n", c);
				usage();
				break;
			}
	if (argc == 1) {
#ifdef _UNICODE
		MultiByteToWideChar(CP_ACP, 0, *argv, lstrlenA(*argv), rgwch, MAX_PATH);
		lpszFileName=rgwch;
#else
		lpszFileName = *argv;
#endif
		argc--;
	}
	
	if (argc)
		usage();
	
	// call the apis

	if (fList)
		lRet = ListSites();
	else if (fEnum)
		lRet = EnumProviders();
	else if (lpszSiteName)
		lRet = AdvancedWebPost(lpszSiteName, lpszFileName);
	else
		lRet = SimpleWebPost(lpszFileName);
	
	return lRet;
}
