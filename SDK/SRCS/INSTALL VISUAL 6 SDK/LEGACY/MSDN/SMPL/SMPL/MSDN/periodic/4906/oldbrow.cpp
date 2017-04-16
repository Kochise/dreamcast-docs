// OLDBROW.CPP - Implementation file for your Internet Server
//    OldBrow Filter

#include <afx.h>
#include <afxwin.h>
#include <afxisapi.h>
#include "resource.h"
#include "OldBrow.h"

// NOTE!
// You will (probably) need to change this #define to point at the
// right file as installed on your system.  You'll get "Not found"
// errors from your browser if it isn't working.

#define TOO_OLD "C:\\INETSRV\\WWWROOT\\OLDBROW.HTM"

///////////////////////////////////////////////////////////////////////
// The one and only COldBrowFilter object

COldBrowFilter theFilter;


///////////////////////////////////////////////////////////////////////
// COldBrowFilter implementation

COldBrowFilter::COldBrowFilter()
{
}

COldBrowFilter::~COldBrowFilter()
{
}

BOOL COldBrowFilter::GetFilterVersion(PHTTP_FILTER_VERSION pVer)
{
	// Call default implementation for initialization
	CHttpFilter::GetFilterVersion(pVer);

	// Clear the flags set by base class
	pVer->dwFlags &= ~SF_NOTIFY_ORDER_MASK;

	// Set the flags we are interested in
	pVer->dwFlags |= SF_NOTIFY_ORDER_LOW | SF_NOTIFY_SECURE_PORT | SF_NOTIFY_NONSECURE_PORT
			 | SF_NOTIFY_URL_MAP;

	// Load description string
	TCHAR sz[SF_MAX_FILTER_DESC_LEN+1];
	ISAPIVERIFY(::LoadString(AfxGetResourceHandle(),
			IDS_FILTER, sz, SF_MAX_FILTER_DESC_LEN));
	_tcscpy(pVer->lpszFilterDesc, sz);
	return TRUE;
}

DWORD COldBrowFilter::OnUrlMap(CHttpFilterContext* pCtxt,
	PHTTP_FILTER_URL_MAP pMapInfo)
{
	char szUserAgent[1024];

	DWORD dwSize = sizeof(szUserAgent);
	if (pCtxt->GetServerVariable("HTTP_USER_AGENT", szUserAgent, &dwSize))
	{
		// Old versions of Microsoft Internet Explorer say "Microsoft
		// Internet Explorer" in their User-Agent: header.  We'll not
		// allow access from those browsers because the user should
		// upgrade to Microsoft Internet Explorer 2.0, which uses
		// the abbreviation "MSIE" instead.

		szUserAgent[dwSize] = '\0';
		if (strncmp(szUserAgent, "Microsoft Internet Explorer", 25) == 0)
			strncpy(pMapInfo->pszPhysicalPath, TOO_OLD, pMapInfo->cbPathBuff-1);
	}

	return SF_STATUS_REQ_NEXT_NOTIFICATION;
}

///////////////////////////////////////////////////////////////////////
// If your extension will not use MFC, you'll need this code to make
// sure the extension objects can find the resource handle for the
// module.  If you convert your extension to not be dependent on MFC,
// remove the comments arounn the following AfxGetResourceHandle()
// and DllMain() functions, as well as the g_hInstance global.

/****

static HINSTANCE g_hInstance;

HINSTANCE AFXISAPI AfxGetResourceHandle()
{
	return g_hInstance;
}

BOOL WINAPI DllMain(HINSTANCE hInst, ULONG ulReason,
					LPVOID lpReserved)
{
	if (ulReason == DLL_PROCESS_ATTACH)
	{
		g_hInstance = hInst;
	}

	return TRUE;
}

****/
