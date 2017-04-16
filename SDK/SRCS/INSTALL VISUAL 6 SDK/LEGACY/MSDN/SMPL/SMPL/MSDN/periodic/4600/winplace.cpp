////////////////////////////////////////////////////////////////
// CWindowPlacement Copyright 1996 Microsoft Systems Journal.
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.

#include "stdafx.h"
#include "winplace.h"

CWindowPlacement::CWindowPlacement()
{
	// Note: "length" is inherited from WINDOWPLACEMENT
	length = sizeof(WINDOWPLACEMENT);
}

CWindowPlacement::~CWindowPlacement()
{
}

//////////////////
// Restore window placement from profile key
//
BOOL CWindowPlacement::Restore(LPCSTR lpKeyName, CWnd* pWnd)
{
	GetProfileWP(lpKeyName);

	// Only restore if window intersets the screen.
	//
	CRect rcTemp, rcScreen(0,0,GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN));
	if (!::IntersectRect(&rcTemp, &rcNormalPosition, &rcScreen))
		return FALSE;

	pWnd->SetWindowPlacement(this);	// set placement
	return TRUE;
}

//////////////////
// Get window placement from profile.
//
void CWindowPlacement::GetProfileWP(LPCSTR lpKeyName)
{
	CWinApp *pApp = AfxGetApp();
	ASSERT_VALID(pApp);

   showCmd = pApp->GetProfileInt(lpKeyName, "wp.showCmd",  showCmd);
   flags   = pApp->GetProfileInt(lpKeyName, "wp.flags",    flags);

	ptMinPosition.x = pApp->GetProfileInt(lpKeyName, "wp.ptMinPosition.x", 
		ptMinPosition.x);
   ptMinPosition.y = pApp->GetProfileInt(lpKeyName, "wp.ptMinPosition.y",
		ptMinPosition.y);
   ptMaxPosition.x = pApp->GetProfileInt(lpKeyName, "wp.ptMaxPosition.x", 
		ptMaxPosition.x);
   ptMaxPosition.y = pApp->GetProfileInt(lpKeyName, "wp.ptMaxPosition.y",
		ptMaxPosition.y);

	RECT& rc = rcNormalPosition;	// because I hate typing
   rc.left	= pApp->GetProfileInt(lpKeyName,	"wp.left",	 rc.left);
   rc.right = pApp->GetProfileInt(lpKeyName, "wp.right",  rc.right);
   rc.top	= pApp->GetProfileInt(lpKeyName,	"wp.top",    rc.top);
   rc.bottom= pApp->GetProfileInt(lpKeyName, "wp.bottom", rc.bottom);
}

////////////////
// Save window placement in app profile
//
void CWindowPlacement::Save(LPCSTR lpKeyName, CWnd* pWnd)
{
	pWnd->GetWindowPlacement(this);
	WriteProfileWP(lpKeyName);
}

//////////////////
// Write window placement to app profile
//
void CWindowPlacement::WriteProfileWP(LPCSTR lpKeyName)
{
	CWinApp *pApp = AfxGetApp();
	ASSERT_VALID(pApp);
   pApp->WriteProfileInt(lpKeyName, "wp.showCmd",			 showCmd);
   pApp->WriteProfileInt(lpKeyName, "wp.flags",				 flags);
   pApp->WriteProfileInt(lpKeyName, "wp.ptMinPosition.x", ptMinPosition.x);
   pApp->WriteProfileInt(lpKeyName, "wp.ptMinPosition.y", ptMinPosition.y);
   pApp->WriteProfileInt(lpKeyName, "wp.ptMaxPosition.x", ptMaxPosition.x);
   pApp->WriteProfileInt(lpKeyName, "wp.ptMaxPosition.y", ptMaxPosition.y);
   pApp->WriteProfileInt(lpKeyName,	"wp.left",	rcNormalPosition.left);
   pApp->WriteProfileInt(lpKeyName,	"wp.right", rcNormalPosition.right);
   pApp->WriteProfileInt(lpKeyName,	"wp.top",   rcNormalPosition.top);
   pApp->WriteProfileInt(lpKeyName,	"wp.bottom",rcNormalPosition.bottom);
}

// The ugly casts are required to help the VC++ 3.0 compiler decide which
// operator<< or operator>> to use. If you're using VC++ 4.0 or later, you 
// can delete this stuff.
//
#if (_MSC_VER < 1000)		// 1000 = VC++ 4.0
#define UINT_CAST (LONG)
#define UINT_CASTREF (LONG&)
#else
#define UINT_CAST
#define UINT_CASTREF
#endif

//////////////////
// Write window placement to archive
// WARNING: archiving functions are untested.
//
CArchive& operator<<(CArchive& ar, const CWindowPlacement& wp)
{
	ar << UINT_CAST wp.length;
   ar << UINT_CAST wp.flags;
	ar << UINT_CAST wp.showCmd;
   ar << wp.ptMinPosition;
   ar << wp.ptMaxPosition;
   ar << wp.rcNormalPosition;
	return ar;
}

//////////////////
// Read window placement from archive
// WARNING: archiving functions are untested.
//
CArchive& operator>>(CArchive& ar, CWindowPlacement& wp)
{
	ar >> UINT_CASTREF wp.length;
   ar >> UINT_CASTREF wp.flags;
	ar >> UINT_CASTREF wp.showCmd;
   ar >> wp.ptMinPosition;
   ar >> wp.ptMaxPosition;
   ar >> wp.rcNormalPosition;
	return ar;
}
