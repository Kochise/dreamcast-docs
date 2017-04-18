/*
 *		frmtbar.c
 *
 *		Implementation of a richedit format bar
 *
 */

#include "preinc.h"

#include <windows.h>
#include <windowsx.h>

#include <richedit.h>

#include <commctrl.h>
#include "dbugit.h"

#include "reitp.rh"
#include "frmtbar.h"


ASSERTDATA

/*
 *	The current format state
 */
typedef struct tagFormatBarState
{
	HWND			hwndToolbar;				// Toolbar
	HWND			hwndName;					// Font name combo
	HWND			hwndSize;					// Font size combo
	HWND			hwndColor;					// Font color combo

	HDC				hdc;						// Our copy of the DC to use
	INT				cyPerInch;					// Pixels per inch vertically

	HBRUSH			hbrushWindow;				// Common brushes
	HBRUSH			hbrushHighlight;
	HBRUSH			hbrushButtonFace;
	COLORREF		crWindow;					// Common colors
	COLORREF		crHighlight;
	COLORREF		crButtonFace;

	CHARFORMAT		cf;							// The current char format
	PARAFORMAT		pf;							// The current paragraph format
	DWORD			dwCFMaskChange;				// What changed

	LONG			rglSize[128];				// Possible font sizes
	LONG			clSize;						// Number of font sizes
	BOOL			fTrueType;					// TrueType flag

	BOOL			fExpectChoice;				// Flag that we want next CBN_*
	BOOL			fGiveUpFocus;				// Flag that we are done
} FormatBarState;

#define	PfbsGetWindowPtr(_hwnd)	\
						((FormatBarState *) GetWindowLong(_hwnd, 0))
#define	SetWindowPtr(_hwnd, _p)	SetWindowLong(_hwnd, 0, (LONG) _p)

#define	GetFormatBarField(_hwnd, _fld)	(PfbsGetWindowPtr(_hwnd)->_fld)

/*
 *		Range of sizes we'll show user for TrueType fonts
 */
#define	lTrueTypeSizeMin	4
#define	lTrueTypeSizeMac	127

static TCHAR	szFormatBar[] = FORMATBARCLASSNAME;
static TCHAR	szToolbar[] = TOOLBARCLASSNAME;
static TCHAR	szComboBox[] = "ComboBox";

/*
 *	Our own private messages from the combobox edit control to the format bar
 *	letting up know about important keyevents
 *		wParam =	window ID of the combobox owning the edit control
 *		lParam =	window handle of the combobox owning the edit control
 *		returns: none
 */
#define	WM_TAB		( WM_USER + 1 )
#define	WM_RETURN	( WM_USER + 2 )
#define	WM_ESCAPE	( WM_USER + 3 )

#define	cxDownButton	16
#define cxName			128 + cxDownButton
#define cxSize			40 + cxDownButton
#define cxColor			24 + cxDownButton
#define	cxGap1			(8 + cxName + 8 + cxSize + 8)
#define	cxGap2			(cxColor + 8)

#define	CFM_MASKS		( CFM_BOLD | CFM_ITALIC | CFM_UNDERLINE | CFM_COLOR )
#define	CFE_EFFECTS		( CFE_BOLD | CFE_ITALIC | CFE_UNDERLINE | \
							CFE_AUTOCOLOR )

#define	INITIAL_COLOR		0x40000000


static TBBUTTON rgtbbutton[] =
{
	{ cxGap1, 0L, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0L, -1},

	{ tbBold, TBI_Bold, TBSTATE_ENABLED, TBSTYLE_CHECK, 0, 0, 0L, -1},
	{ tbItalic, TBI_Italic, TBSTATE_ENABLED, TBSTYLE_CHECK, 0, 0, 0L, -1}, 
	{ tbUnderline, TBI_Underline, TBSTATE_ENABLED, TBSTYLE_CHECK, 0, 0, 0L, -1}, 
	{ cxGap2, 0L, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0L, -1},

	{ tbBullet, TBI_Bullet, TBSTATE_ENABLED, TBSTYLE_CHECK, 0, 0, 0L, -1},
	{ 0, 0L, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0L, -1},

	{ tbDecreaseIndent, TBI_DecreaseIndent, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0L, -1},
	{ tbIncreaseIndent, TBI_IncreaseIndent, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0L, -1},
	{ 0, 0L, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0L, -1},

	{ tbLeft, TBI_Left, TBSTATE_ENABLED, TBSTYLE_CHECKGROUP, 0, 0, 0L, -1},
	{ tbCenter, TBI_Center, TBSTATE_ENABLED, TBSTYLE_CHECKGROUP, 0, 0, 0L, -1}, 
	{ tbRight, TBI_Right, TBSTATE_ENABLED, TBSTYLE_CHECKGROUP, 0, 0, 0L, -1}, 
	{ 0, 0L, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0L, -1},
};
#define ctbbutton	(sizeof(rgtbbutton) / sizeof(TBBUTTON))

static DWORD	rgdwCFEffect[]	=	{ CFE_BOLD, CFE_ITALIC, CFE_UNDERLINE };
static WORD		rgwPFAlignment[]	=	{ PFA_LEFT, PFA_CENTER, PFA_RIGHT };

// Hold the old wndproc's !
//$ REVIEW: Make this per instance ?
static WNDPROC	pfnEditWndProc = NULL;
static WNDPROC	pfnComboBoxWndProc = NULL;
static WNDPROC	pfnToolbarWndProc = NULL;

/*
 *	Color table for dropdown on toolbar.  Matches COMMDLG colors
 *	exactly.
 */
static DWORD rgrgbColors[] = {
	RGB(  0,   0, 0),  	/* Black	*/
	RGB(128,   0, 0),  	/* Dark red	*/
	RGB(  0, 128, 0),  	/* Dark green	*/
	RGB(128, 128, 0),  	/* Dark yellow	*/
	RGB(  0,   0, 128),	/* Dark blue	*/
	RGB(128,   0, 128),	/* Dark purple	*/
	RGB(  0, 128, 128),	/* Dark aqua	*/
	RGB(128, 128, 128),	/* Dark grey	*/
	RGB(192, 192, 192),	/* Light grey	*/
	RGB(255,   0, 0),  	/* Light red	*/
	RGB(  0, 255, 0),  	/* Light green	*/
	RGB(255, 255, 0),  	/* Light yellow */
	RGB(  0,   0, 255),	/* Light blue	*/
	RGB(255,   0, 255),	/* Light purple */
	RGB(  0, 255, 255),	/* Light aqua	*/
	RGB(255, 255, 255),	/* White	*/
};

const INT crgbColorsMax = sizeof(rgrgbColors) / sizeof(rgrgbColors[0]);

#define	TraceCharFormat(_sz, _pcf)


/*
 *	UpdateBrush
 *
 *	Purpose:
 *		Syncs up the brushes with the known color scheme as needed
 *
 *	Arguments:
 *		hwnd		Handle of the format bar
 *
 *	Returns:
 *		None.
 */
LOCAL VOID UpdateBrush(HBRUSH * phbrush, COLORREF * pcr, INT nIndex)
{
	COLORREF			cr;

	if (((cr = GetSysColor(nIndex)) != *pcr) ||
		!*phbrush)
	{
		if (*phbrush)
			DeleteObject(*phbrush);
		*phbrush = CreateSolidBrush(*pcr = cr);
	}
}


/*
 *	UpdateBrushes
 *
 *	Purpose:
 *		Syncs up the brushes with the known color scheme as needed
 *
 *	Arguments:
 *		hwnd		Handle of the format bar
 *
 *	Returns:
 *		None.
 */
LOCAL VOID UpdateBrushes(HWND hwnd)
{
	FormatBarState *	pfbs = PfbsGetWindowPtr(hwnd);

	UpdateBrush(&pfbs->hbrushWindow, &pfbs->crWindow, COLOR_WINDOW);
	UpdateBrush(&pfbs->hbrushHighlight, &pfbs->crHighlight, COLOR_HIGHLIGHT);
	UpdateBrush(&pfbs->hbrushButtonFace, &pfbs->crButtonFace, COLOR_BTNFACE);
}


/*
 *	LFBEditWndProc
 *
 *	Purpose:
 *		Take care of handling the notifications from the combobox controls we
 *		get for the format bar
 *
 *	Arguments:
 *		hwnd
 *		wMsg
 *		wParam
 *		lParam
 *
 *	Returns:
 *		LRESULT
 */
LRESULT CALLBACK LFBEditWndProc(HWND hwnd, UINT wMsg, WPARAM wParam,
									LPARAM lParam)
{
	switch (wMsg)
	{
	case WM_KEYDOWN:
		{
			HWND	hwndCombo = GetParent(hwnd);
			HWND	hwndFormatBar = GetParent(GetParent(hwndCombo));
			INT		nID = GetWindowID(hwndCombo);

			switch(wParam)
			{

			case VK_ESCAPE:
				SendMessage(hwndFormatBar, WM_ESCAPE, nID,
							(LPARAM) (LPTSTR) hwndCombo);

			case VK_TAB:
			case VK_RETURN:
				return 0;
			}
		}
		break;

	case WM_CHAR:
		{
			HWND	hwndCombo = GetParent(hwnd);
			HWND	hwndFormatBar = GetParent(GetParent(hwndCombo));
			INT		nID = GetWindowID(hwndCombo);

			switch(wParam)
			{
			case VK_RETURN:
				SendMessage(hwndFormatBar, WM_RETURN, nID,
							(LPARAM) (LPTSTR) hwndCombo);
				return 0;

			case VK_TAB:
				SendMessage(hwndFormatBar, WM_TAB, nID,
							(LPARAM) (LPTSTR) hwndCombo);
				return 0;

		   	case VK_ESCAPE:
				return 0;
			}
		}
		break;

	case WM_KEYUP:
		switch (wParam)
		{
		case VK_RETURN:
		case VK_TAB:
		case VK_ESCAPE:
			return 0;
		}
		break;
	}

	return CallWindowProc(pfnEditWndProc, hwnd, wMsg, wParam, lParam);
}


/*
 *	LFBComboBoxWndProc
 *
 *	Purpose:
 *		Take care of handling the notifications from the combobox controls we
 *		get for the format bar
 *
 *	Arguments:
 *		hwnd
 *		wMsg
 *		wParam
 *		lParam
 *
 *	Returns:
 *		LRESULT
 */
LRESULT CALLBACK LFBComboBoxWndProc(HWND hwnd, UINT wMsg, WPARAM wParam,
									LPARAM lParam)
{
	switch (wMsg)
	{
	case WM_KEYDOWN:
		{
			HWND	hwndFormatBar = GetParent(GetParent(hwnd));
			INT		nID = GetWindowID(hwnd);

			switch(wParam)
			{
			case VK_TAB:
				SendMessage(hwndFormatBar, WM_TAB, nID,
							(LPARAM) (LPTSTR) hwnd);
				return 0;

			case VK_RETURN:
				SendMessage(hwndFormatBar, WM_RETURN, nID,
							(LPARAM) (LPTSTR) hwnd);
				return 0;

			case VK_ESCAPE:
				SendMessage(hwndFormatBar, WM_ESCAPE, nID,
							(LPARAM) (LPTSTR) hwnd);
				return 0;
			}
		}
		break;

	case WM_KEYUP:
	case WM_CHAR:
		switch(wParam)
		{
			case VK_TAB:
			case VK_RETURN:
			case VK_ESCAPE:
				return 0;
		}
		break;
	}

	return CallWindowProc(pfnComboBoxWndProc, hwnd, wMsg, wParam, lParam);
}


/*
 *	LFBToolbarWndProc
 *
 *	Purpose:
 *		Take care of handling the notifications from the combobox controls we
 *		get for the format bar
 *
 *	Arguments:
 *		hwnd
 *		wMsg
 *		wParam
 *		lParam
 *
 *	Returns:
 *		LRESULT
 */

LRESULT CALLBACK LFBToolbarWndProc(HWND hwnd, UINT wMsg, WPARAM wParam,
									LPARAM lParam)
{
	switch (wMsg)
	{
	case WM_CTLCOLORLISTBOX:
			{
				FormatBarState *	pfbs = PfbsGetWindowPtr(GetParent(hwnd));

				// Peek at the current information
				UpdateBrush(&pfbs->hbrushButtonFace, &pfbs->crButtonFace,
							COLOR_BTNFACE);
				return (LRESULT) (LPTSTR) pfbs->hbrushButtonFace;
			}
		break;
	}

	return CallWindowProc(pfnToolbarWndProc, hwnd, wMsg, wParam, lParam);
}


/*
 *	NEnumFontNameProc
 *
 *	Purpose:
 *		The callback for EnumFontFamilies which fills the font names combobox
 *		with the available fonts
 *
 *	Arguments:
 *
 *	Returns:
 *		Non-zero as long a font name can be inserted into the combobox
 */
INT CALLBACK NEnumFontNameProc(LOGFONT * plf, TEXTMETRIC * ptm,
								INT nFontType, LPARAM lParam)
{
	LRESULT lr;
	DWORD	dw;

	lr = SendMessage((HWND) lParam, CB_ADDSTRING, 0, (LPARAM) plf->lfFaceName);
	if (!(lr == CB_ERR || lr == CB_ERRSPACE))
	{
		Assert (!(plf->lfCharSet & 0xFFFFFF00));
		Assert (!(plf->lfPitchAndFamily & 0xFFFFFF00));
		Assert (!(nFontType & 0xFFFF0000));
		dw = plf->lfCharSet & 0xFF;
		dw <<= 8;
		dw |= plf->lfPitchAndFamily & 0xFF;
		dw <<= 16;
		dw |= nFontType & 0xFFFF;
		SendMessage((HWND) lParam, CB_SETITEMDATA, LOWORD(lr), (LPARAM) dw);
	}
	return !(lr == CB_ERR || lr == CB_ERRSPACE);
}


/*
 *	FillNames
 *
 *	Purpose:
 *		Fills the font name combobox with the names of the available fonts
 *
 *	Arguments:
 *		hwnd			Handle of the names combobox
 *
 *	Returns:
 *		None.
 */
LOCAL void FillNames(HWND hwnd)
{
	FormatBarState *	pfbs = PfbsGetWindowPtr(hwnd);
	HDC					hdc = pfbs->hdc;
	HWND				hwndName = pfbs->hwndName;

	// Empty the current list
	SendMessage(hwndName, CB_RESETCONTENT, 0, 0);

	// Ask for all the font families
	EnumFontFamilies((HDC) hdc, (LPTSTR) NULL,
					 (FONTENUMPROC) NEnumFontNameProc,
					 (LPARAM) (LPTSTR) hwndName);
}



/*
 *	FInsertSize
 *
 *	Purpose:
 *		Inserts a font size entry into the array. Takes care of the necessary
 *		conversion from logical units to points size. The array is kept in
 *		ascending order.
 *
 *	Arguments:
 *		lSize			The font size in logical units
 *		pfbs			The current format bar state
 *		fPoints			Flag whether the size is in points or not
 *
 *	Returns:
 *		TRUE if the font size was successfully added to the array, or was
 *		present.
 */
BOOL FInsertSize(LONG lSize, FormatBarState * pfbs, BOOL fPoints)
{
	LONG	clLeft = pfbs->clSize;
	LONG *	plSize = pfbs->rglSize;

	if (clLeft >= sizeof(pfbs->rglSize) / sizeof(LONG))
		return FALSE;

	// Convert to point sizes
	if (!fPoints)
		lSize = MulDiv((INT) lSize, 72, pfbs->cyPerInch);

	while (clLeft > 0 && *plSize < lSize)
	{
		++plSize;
		--clLeft;
	}
	if (clLeft && *plSize == lSize)
		;
	else
	{
		if (clLeft)
		{
			MoveMemory(plSize + 1, plSize, clLeft * sizeof(LONG));
		}
		*plSize = lSize;
		++pfbs->clSize;
	}
	return TRUE;
}


/*
 *	NEnumFontSizeProc
 *
 *	Purpose:
 *		The callback for EnumFontFamilies which fills the font names combobox
 *		with the available fonts
 *
 *	Arguments:
 *
 *	Returns:
 *		Non-zero as long a font name can be inserted into the combobox
 */
INT CALLBACK NEnumFontSizeProc(LOGFONT * plf, TEXTMETRIC * ptm,
								INT nFontType, LPARAM lParam)
{
	FormatBarState *	pfbs = (FormatBarState *) lParam;

	if (ptm->tmPitchAndFamily & TMPF_TRUETYPE)
		pfbs->fTrueType |= TRUE;
	return FInsertSize(ptm->tmHeight - ptm->tmInternalLeading, pfbs, FALSE);
}


/*
 *	FFillSizes
 *
 *	Purpose:
 *		Fills the font name combobox with the names of the available fonts
 *
 *	Arguments:
 *		hwnd			Handle of the names combobox
 *
 *	Returns:
 *		TRUE if successful
 */
LOCAL BOOL FFillSizes(HWND hwnd)
{
	FormatBarState *	pfbs = PfbsGetWindowPtr(hwnd);
	HDC					hdc = pfbs->hdc;
	HWND				hwndSize = pfbs->hwndSize;
	TCHAR *				pszFaceName = pfbs->cf.szFaceName;
	LONG				ilSize;
	LONG				lCurrSize;
	LONG				ilMatch;
	LONG *				plSize  = pfbs->rglSize;
	TCHAR				szT[10];
	LRESULT				lr;
	BOOL				fSuccess = FALSE;

	// Empty the current list
	SendMessage(hwndSize, CB_RESETCONTENT, 0, 0);
	pfbs->clSize = 0;
	pfbs->fTrueType = FALSE;

	// Ask for all the font sizes for the given font
	EnumFontFamilies((HDC) hdc, pszFaceName,
					 (FONTENUMPROC) NEnumFontSizeProc, (LPARAM) pfbs);

// If we got a TrueType font, just fill in the array with our sizes
	if (pfbs->fTrueType)
	{
		ilSize = lTrueTypeSizeMin;
		while (ilSize < lTrueTypeSizeMac)
			*plSize++ = ilSize++;
		*plSize = ilSize;
		pfbs->clSize = lTrueTypeSizeMac - lTrueTypeSizeMin + 1;
	}
	// Save ourselves some dereferencing and covert to points
	lCurrSize = MulDiv((INT) pfbs->cf.yHeight, 72, 1440);

	// Now go through our entries and put them into our listbox
	plSize  = pfbs->rglSize;
	ilMatch = -1;
	for (ilSize = 0; ilSize < pfbs->clSize; ++ilSize, ++plSize)
	{
		wsprintf(szT, "%ld", *plSize);
		lr = SendMessage(hwndSize, CB_ADDSTRING, 0, (LPARAM) szT);
		AssertSz(!(lr == CB_ERR || lr == CB_ERRSPACE), "Can't add more sizes");
		if (lr == CB_ERR || lr == CB_ERRSPACE)
			goto CleanUp;

		// Try to find out which element will become our current selection
		if (*plSize == lCurrSize)
			ilMatch = ilSize;
	}

	// Set our current selection
	if (ilMatch >= 0)
		SendMessage(hwndSize, CB_SETCURSEL, (WPARAM) ilMatch, 0);
	else
	{
		if (lCurrSize)
			wsprintf(szT, "%ld", lCurrSize);
		else
			szT[0] = 0;
		SetWindowText(hwndSize, szT);
	}
	fSuccess = TRUE;

CleanUp:
	return fSuccess;
}


/*
 *	FillColors
 *
 *	Purpose:
 *		Fills the font colors combobox with samples of the available colors
 *
 *	Arguments:
 *		hwnd			Handle of the names combobox
 *
 *	Returns:
 *		None.
 */
LOCAL void FillColors(HWND hwnd)
{
	FormatBarState *	pfbs = PfbsGetWindowPtr(hwnd);
	HWND				hwndColor = pfbs->hwndColor;
	INT					ilMatch = -1;
	LRESULT				lr;
	INT					icr;
	DWORD *				pdw;

	// Empty the current list
	SendMessage(hwndColor, CB_RESETCONTENT, 0, 0);

	for (icr = 0, pdw = rgrgbColors; icr < crgbColorsMax; ++icr, ++pdw)
	{
		lr = SendMessage(hwndColor, CB_ADDSTRING, 0, (LPARAM) *pdw);
		if (lr == CB_ERR || lr == CB_ERRSPACE)
		{
			TraceError("FillColors: No more room for colors", -1);
			break;
		}

		if (*pdw == pfbs->cf.crTextColor)
			ilMatch = icr;
	}

	SendMessage(hwndColor, CB_SETCURSEL, (WPARAM) ilMatch > 0 ? ilMatch : 0, 0);
}


/*
 *	FB_OnNcCreate
 *
 *	Purpose:
 *		We want to draw our own colors for the colors combobox
 *
 *	Arguments:
 *		hwnd		The window
 *		pmis		Pointer to a MEASUREITEMSTRUCT to be filled out
 *
 *	Returns:
 *		None.
 */
LOCAL BOOL FB_OnNcCreate(HWND hwnd, CREATESTRUCT * pcs)
{
	RECT				rc;
	INT					cyButton;
	INT					cyList;
	INT					yPos;
	INT					xPos;
	HFONT				hfont;
	FormatBarState *	pfbs = NULL;
	HINSTANCE			hinst = pcs->hInstance;
	WNDPROC 			pfnWndProcT;
	POINT				pt = { 1, 1 };
	HWND				hwndT;

	// Tell format bar where to find it's state information
	pfbs = (FormatBarState *) GlobalAllocPtr(GHND, sizeof(FormatBarState));
	if (!pfbs)
		goto ErrorNoState;
	SetWindowPtr(hwnd, pfbs);
	AssertSz(PfbsGetWindowPtr(hwnd) == pfbs, "We didn't write it!");

	// Get a few brushes that we'll be using all the time
	UpdateBrushes(hwnd);

	// Create the toolbar
	pfbs->hwndToolbar = CreateToolbarEx(hwnd, CCS_TOP | WS_CHILD,
										0, tbFormatBarMax, hinst,
										BMP_FormatBar, rgtbbutton, ctbbutton,
										16, 16, 16, 16, sizeof(TBBUTTON));

	if (!pfbs->hwndToolbar)
		goto ErrorNoToolbar;

	// Subclass the toolbar
	pfnWndProcT = (WNDPROC) SetWindowLong(pfbs->hwndToolbar, GWL_WNDPROC,
												(LONG) LFBToolbarWndProc);

	// If we don't know what the global ToolbarWndProc is, save it
	if (!pfnToolbarWndProc)
		pfnToolbarWndProc = pfnWndProcT;
	
	// Determine how tall the buttons are so we can size our other controls
	// accordingly
	SendMessage(pfbs->hwndToolbar, TB_GETITEMRECT, 1, (LPARAM) &rc);
	cyButton = rc.bottom - rc.top + 1;

	// Determine how tall the toolbar is so that we can center the comboboxes
	GetClientRect(pfbs->hwndToolbar, &rc);
	yPos = (rc.bottom - rc.top + 1 - cyButton) / 2 + 1;

	// Let's make the comboboxes dropdown about 5 times the height
	cyList = 5 * cyButton;

	// Get the font to use for the comboboxes
	hfont = (HFONT) SendMessage(pfbs->hwndToolbar, WM_GETFONT, 0, 0);

	// Now create the other format bar controls

	// The name
	xPos = 8;
	pfbs->hwndName = CreateWindow(szComboBox, NULL,
									WS_CHILD | WS_VSCROLL | CBS_DROPDOWN |
									CBS_SORT | CBS_HASSTRINGS | WS_VISIBLE,
									xPos, yPos, cxName, cyList,
									pfbs->hwndToolbar, (HMENU) TBI_Name,
									hinst, NULL);
	if (!pfbs->hwndName)
		goto ErrorNoName;
	SetWindowFont(pfbs->hwndName, hfont, TRUE);
	xPos += cxName + 8;


	// The Size
	pfbs->hwndSize = CreateWindow(szComboBox, NULL,
									WS_CHILD | WS_VSCROLL | CBS_DROPDOWN |
									WS_VISIBLE,
									xPos, yPos, cxSize, cyList,
									pfbs->hwndToolbar, (HMENU) TBI_Size,
									hinst, NULL);
	if (!pfbs->hwndSize)
		goto ErrorNoSize;
	SetWindowFont(pfbs->hwndSize, hfont, TRUE);

	// The color
	//$ REVIEW: Magic number
	SendMessage(pfbs->hwndToolbar, TB_GETITEMRECT, 3, (LPARAM) &rc);
	pfbs->hwndColor = CreateWindow(szComboBox, NULL,
									WS_CHILD | WS_VSCROLL | CBS_DROPDOWNLIST |
									CBS_OWNERDRAWFIXED | WS_VISIBLE,
									rc.right, yPos - 1, cxColor, cyList,
									pfbs->hwndToolbar, (HMENU) TBI_Color,
									hinst, NULL);
	if (!pfbs->hwndColor)
		goto ErrorNoColor;
	SetWindowFont(pfbs->hwndColor, hfont, TRUE);

	// Set the initial color to black so it won't be redrawn.
	pfbs->cf.dwMask |= INITIAL_COLOR;

	// Subclass the comboboxes' edit controls

	// Do the name first
	hwndT = ChildWindowFromPoint(pfbs->hwndName, pt);
	pfnWndProcT = (WNDPROC) SetWindowLong(hwndT, GWL_WNDPROC,
												(LONG) LFBEditWndProc);

	// If we don't know what the global EditWndProc is, save it
	if (!pfnEditWndProc)
		pfnEditWndProc = pfnWndProcT;

	// Next the size
	hwndT = ChildWindowFromPoint(pfbs->hwndSize, pt);
	(WNDPROC) SetWindowLong(hwndT, GWL_WNDPROC, (LONG) LFBEditWndProc);
	
	// Lastly the color
	pfnWndProcT = (WNDPROC) SetWindowLong(pfbs->hwndColor, GWL_WNDPROC,
												(LONG) LFBComboBoxWndProc);

	// If we don't know what the global ComboBoxWndProc is, save it
	if (!pfnComboBoxWndProc)
		pfnComboBoxWndProc = pfnWndProcT;
	
	// Create a copy of the DC that the user gave up to play with
	if(pcs->lpCreateParams)
	{
		HDC *	phdc = (HDC *) pcs->lpCreateParams;

		pfbs->hdc = CreateCompatibleDC(*phdc);
	}
	else
	{
		HDC hdc = GetDC(pcs->hwndParent);

		pfbs->hdc = CreateCompatibleDC(hdc);
		ReleaseDC(pcs->hwndParent, hdc);
	}

	if (!pfbs->hdc)
		goto ErrorNoColor;
	
	// Get the number of pixels per inch vertically so we can do point sizes
	pfbs->cyPerInch = GetDeviceCaps(pfbs->hdc, LOGPIXELSY);

	// Load up the names of the fonts and colors
	FillNames(hwnd);
	FillColors(hwnd);
	// Continue creating
	return TRUE;

ErrorNoColor:
	DestroyWindow(pfbs->hwndSize);
	pfbs->hwndSize = NULL;

ErrorNoSize:
	DestroyWindow(pfbs->hwndName);
	pfbs->hwndName = NULL;

ErrorNoName:
	DestroyWindow(pfbs->hwndToolbar);
	pfbs->hwndToolbar = NULL;

ErrorNoToolbar:
	if (pfbs)
		GlobalFreePtr(pfbs);

ErrorNoState:
	return FALSE;
}


/*
 *	FB_OnMeasureItem
 *
 *	Purpose:
 *		We want to draw our own colors for the colors combobox
 *
 *	Arguments:
 *		hwnd		The window
 *		pmis		Pointer to a MEASUREITEMSTRUCT to be filled out
 *
 *	Returns:
 *		None.
 */
LOCAL void FB_OnMeasureItem(HWND hwnd, MEASUREITEMSTRUCT * pmis)
{
	switch (pmis->CtlID)
	{
	case TBI_Color:
		pmis->itemWidth = 128;
		pmis->itemHeight = 16;
		break;
	default:
		TraceError("Don't know anything about CtlID", -1);
		break;
	}
}


/*
 *	FB_OnDrawItem
 *
 *	Purpose:
 *		We want to drawn our own colors for our color combobox
 *
 *	Arguments:
 *		hwnd		The window
 *		pdis		Pointer to a DRAWITEMSTRUCT to be filled out
 *
 *	Returns:
 *		None.
 */
LOCAL void FB_OnDrawItem(HWND hwnd, DRAWITEMSTRUCT * pdis)
{
	FormatBarState *	pfbs = PfbsGetWindowPtr(hwnd);
	HDC					hdc = pdis->hDC;
	RECT				rc;
	HBRUSH				hbrush;
	COLORREF			cr = (COLORREF) pdis->itemData;
	INT					nIter = 2;

	// As far as we know we have only one owner drawn control
	AssertSz(pdis->CtlType == ODT_COMBOBOX, "Know only comboboxes");
	if (pdis->CtlID != TBI_Color)
		return;

	// NULL object wanted ?
	if (pdis->itemData == -1)
		goto HandleFocus;

	switch (pdis->itemAction)
	{
	case ODA_DRAWENTIRE:
		rc = pdis->rcItem;
		InflateRect(&rc, -3, -3);
		hbrush = CreateSolidBrush((COLORREF)cr);
		FillRect(hdc, &rc, hbrush);
		DeleteObject(hbrush);
		FrameRect(hdc, &rc, GetStockObject(BLACK_BRUSH));

		// *** FALL THROUGH ***

	case ODA_SELECT:
		rc = pdis->rcItem;
		if (pdis->itemState & ODS_SELECTED)
			hbrush = pfbs->hbrushHighlight;
		else
			hbrush = pfbs->hbrushWindow;
		while (nIter--)
		{
			InflateRect(&rc, -1, -1);
			FrameRect(hdc, &rc, hbrush);
		}

		if (pdis->itemAction != ODA_DRAWENTIRE)
			break;

		// *** FALL THROUGH ***

HandleFocus:
	case ODA_FOCUS:
		if (pdis->itemState & ODS_FOCUS)
			hbrush = pfbs->hbrushHighlight;
		else
			hbrush = pdis->itemData == -1 ? pfbs->hbrushButtonFace :
											pfbs->hbrushWindow;
		FrameRect(hdc, &pdis->rcItem, hbrush);
		break;
	}

}


/*
 *	PaintName
 *
 *	Purpose:
 *		Paint the current name
 *
 *	Arguments:
 *		pfbs		The current format bar state
 *
 *	Returns:
 *		None.
 */
LOCAL VOID PaintName(FormatBarState * pfbs)
{
	LONG	ilFound;

	TraceCharFormat("PaintName", &pfbs->cf);
	if (pfbs->cf.dwMask & CFM_FACE)
	{
		ilFound = SendMessage(pfbs->hwndName, CB_FINDSTRING, 0,
								(LPARAM) pfbs->cf.szFaceName);
		SendMessage(pfbs->hwndName, CB_SETCURSEL, (WPARAM) ilFound, 0);
		if (ilFound == CB_ERR)
			SetWindowText(pfbs->hwndName, pfbs->cf.szFaceName);
	}
	else
		SetWindowText(pfbs->hwndName, TEXT(""));

}


/*
 *	PaintSize
 *
 *	Purpose:
 *		Paint the current size
 *
 *	Arguments:
 *		pfbs		The current format bar state
 *
 *	Returns:
 *		None.
 */
LOCAL VOID PaintSize(FormatBarState * pfbs)
{
	LONG	lSize = MulDiv((INT) pfbs->cf.yHeight, 72, 1440);
	LONG	ilFound;
	TCHAR	szT[10];

	TraceCharFormat("PaintSize", &pfbs->cf);
	szT[0] = 0;
	if (lSize > 0 && (pfbs->cf.dwMask & CFM_SIZE))
		wsprintf(szT, "%ld", lSize);
	ilFound = SendMessage(pfbs->hwndSize, CB_FINDSTRINGEXACT, 0,
							(LPARAM) szT);
	SendMessage(pfbs->hwndSize, CB_SETCURSEL, (WPARAM) ilFound, 0);
	SetWindowText(pfbs->hwndSize, szT);
}


/*
 *	PaintColor
 *
 *	Purpose:
 *		Paint the current color
 *
 *	Arguments:
 *		pfbs		The current format bar state
 *
 *	Returns:
 *		None.
 */
LOCAL VOID PaintColor(FormatBarState * pfbs)
{
	LONG		ilFound = -1;
	COLORREF	crTextColor = pfbs->cf.crTextColor;

	//$ FUTURE: Handle autocolor

	// If color isn't known, choose white
	TraceCharFormat("PaintColor", &pfbs->cf);
	if (pfbs->cf.dwMask & CFM_COLOR)
	{
		ilFound = SendMessage(pfbs->hwndColor, CB_FINDSTRINGEXACT, 0,
								(LPARAM) crTextColor);
		if (ilFound < 0)
		{
			// Not found, add a new color
			ilFound = SendMessage(pfbs->hwndColor, CB_ADDSTRING, 0,
								(LPARAM) crTextColor);
		}
	}
	SendMessage(pfbs->hwndColor, CB_SETCURSEL, (WPARAM) ilFound, 0);
}


/*
 *	PaintEffects
 *
 *	Purpose:
 *		Paint the current effects
 *
 *	Arguments:
 *		pfbs		The current format bar state
 *
 *	Returns:
 *		None.
 */
LOCAL VOID PaintEffects(FormatBarState * pfbs)
{
	HWND	hwndToolbar = pfbs->hwndToolbar;
	DWORD	dwMask = pfbs->cf.dwMask;
	DWORD	dwEffects = pfbs->cf.dwEffects;
	BOOL	fEffect;
	BOOL	fMask;
	INT		nID;

	TraceCharFormat("PaintEffects", &pfbs->cf);
	for (nID = TBI_Bold; nID <= TBI_Underline; nID++)
	{
		fMask = dwMask & rgdwCFEffect[nID - TBI_Bold] ? TRUE : FALSE;
		fEffect = dwEffects & rgdwCFEffect[nID - TBI_Bold] ? TRUE : FALSE;
#ifdef LIKE_WORD2
		// Act like Word
		SendMessage(hwndToolbar, TB_CHECKBUTTON, nID, MAKELONG(fEffect, 0));
		SendMessage(hwndToolbar, TB_INDETERMINATE, nID, MAKELONG(!fMask, 0));
#elif defined(LIKE_T3)
		// Act like T3
		SendMessage(hwndToolbar, TB_CHECKBUTTON, nID,
					MAKELONG(fEffect && fMask, 0));
#else
		//$ Raid 2375: Show the user what is actually going to happen
		SendMessage(hwndToolbar, TB_CHECKBUTTON, nID, MAKELONG(fEffect, 0));
#endif
	}

}


/*
 *	PaintAlignment
 *
 *	Purpose:
 *		Paint the current alignment
 *
 *	Arguments:
 *		pfbs		The current format bar state
 *
 *	Returns:
 *		None.
 */
LOCAL VOID PaintAlignment(FormatBarState * pfbs)
{
	HWND	hwndToolbar = pfbs->hwndToolbar;
	DWORD	wAlignment = pfbs->pf.wAlignment;
	INT		nID;

	if (pfbs->pf.dwMask & PFM_ALIGNMENT)
	{
#ifdef LIKE_WORD
		// Make all the buttons active
		for (nID = TBI_Left; nID <= TBI_Right; nID++)
			SendMessage(hwndToolbar, TB_INDETERMINATE, nID,
						MAKELONG(FALSE, 0));
#endif
		// And press down one of them
		switch (wAlignment)
		{
		case PFA_CENTER:
			nID = TBI_Center;
			break;

		case PFA_RIGHT:
			nID = TBI_Right;
			break;

		case PFA_LEFT:
		default:
			nID = TBI_Left;
			break;
		}
		SendMessage(hwndToolbar, TB_CHECKBUTTON, nID, MAKELONG(TRUE, 0));
	}
	else
	{
#ifdef LIKE_WORD
		// Make all the buttons indeterminate
		for (nID = TBI_Left; nID <= TBI_Right; nID++)
			SendMessage(hwndToolbar, TB_INDETERMINATE, nID, MAKELONG(TRUE, 0));
#else
		// Pop all the buttons
		for (nID = TBI_Left; nID <= TBI_Right; nID++)
			SendMessage(hwndToolbar, TB_CHECKBUTTON, nID, MAKELONG(FALSE, 0));
#endif
	}
}


/*
 *	FB_OnCommand
 *
 *	Purpose:
 *		Handle some of the notifications
 *
 *	Arguments:
 *		hwnd		The window
 *		pdis		Pointer to a DRAWITEMSTRUCT to be filled out
 *
 *	Returns:
 *		None.
 */
LOCAL void FB_OnCommand(HWND hwnd, INT nID, HWND hwndCtl, INT nNotify)
{
	FormatBarState *	pfbs = PfbsGetWindowPtr(hwnd);
	LONG				iSel;
	if (nNotify == CBN_ERRSPACE)
	{
		//$ FUTURE: Handle error out of space
		return;
	}

	switch (nNotify)
	{
	case CBN_SELENDOK:
		// Flag the next combobox message as somethng we want
		pfbs->fExpectChoice = TRUE;
		pfbs->fGiveUpFocus = TRUE;
		return;

	case 0:
		// This is a button from the toolbar if hwndCtl == pfbs->hwndToolbar
		if (hwndCtl != pfbs->hwndToolbar)
			return;
		break;

	case CBN_KILLFOCUS:
		switch (nID)
		{
		case TBI_Name:
			PaintName(pfbs);
			break;

		case TBI_Size:
			PaintSize(pfbs);
			break;

		case TBI_Color:
			PaintColor(pfbs);
			break;
		}
		return;

	case CBN_SELCHANGE:
		// The user is making up his mind so ignore the sel change
		if (!pfbs->fExpectChoice)
			return;
		break;

	case CBN_DROPDOWN:
		if (nID == TBI_Size)
			FFillSizes(hwnd);
		return;

	//$ REVIEW: Just check for fExpectChoice to shorten this switch ?

	// Throw away these notifications from the toolbar
	case TBN_BEGINDRAG:
	case TBN_ENDDRAG:

	// Throw away these notifications from the comboboxes
	case CBN_SETFOCUS:
	case CBN_CLOSEUP:
	case CBN_SELENDCANCEL:
	case CBN_EDITCHANGE:
	case CBN_EDITUPDATE:
	case CBN_DBLCLK:

	default:
		return;
	}

	switch (nID)
	{
	case TBI_Name:
		if (pfbs->fExpectChoice)
		{
			DWORD	dw;

			// Get the new font name
			pfbs->cf.dwMask |= CFM_FACE | CFM_CHARSET;
			pfbs->dwCFMaskChange = CFM_FACE | CFM_CHARSET;

			// Get the new selection
			iSel = SendMessage(pfbs->hwndName, CB_GETCURSEL, 0, 0);
			if (iSel < 0)
			{
		//DebugStr("\pBefore GetWindowText in Frmtbar.c");
				GetWindowText(pfbs->hwndName, pfbs->cf.szFaceName,
							sizeof(pfbs->cf.szFaceName) / sizeof(TCHAR));
				pfbs->cf.bPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
				pfbs->cf.bCharSet = DEFAULT_CHARSET;
			}
			else
			{
				SendMessage(pfbs->hwndName, CB_GETLBTEXT, (WPARAM) iSel,
							(LPARAM) pfbs->cf.szFaceName);

				// Pull the other bits of data we had packed away.
				dw = ComboBox_GetItemData(pfbs->hwndName, iSel);
				dw >>= 16;
				pfbs->cf.bPitchAndFamily = (BYTE) dw & 0xFF;
				dw >>= 8;
				pfbs->cf.bCharSet = (BYTE) dw & 0xFF;
			}

			// Update the list of font sizes
			FFillSizes(hwnd);
			pfbs->fExpectChoice = FALSE;
		}
		break;

	case TBI_Size:
		if (pfbs->fExpectChoice)
		{
			TCHAR	szT[10];
			TCHAR *	pch = szT;
			LONG	lSize = 0;

			// Get the new font size
			pfbs->cf.dwMask |= CFM_SIZE;
			pfbs->dwCFMaskChange = CFM_SIZE;
			szT[0] = 0;

			// Get the new selection
			iSel = SendMessage(pfbs->hwndSize, CB_GETCURSEL, 0, 0);
			if (iSel < 0)
			{
	//	DebugStr("\pBefore GetWindowText in Format.c2");
				GetWindowText(pfbs->hwndSize, szT, sizeof(szT) / sizeof(TCHAR));
			}
			else
				SendMessage(pfbs->hwndSize, CB_GETLBTEXT, (WPARAM) iSel,
							(LPARAM) szT);

			while (*pch)
			{
				if (TEXT('0') <= *pch && *pch <= TEXT('9'))
				{
					lSize *= 10;
					lSize += *pch - '0';
				}
				else
				{
					// Got a bad character, reject the user's input
					lSize = 0;
					break;
				}
				*pch++;
			}

			if (lSize > 0 && lSize <= yHeightCharPtsMost)
				pfbs->cf.yHeight = lSize * 20;		// Make twips
			else
				MessageBox(hwnd, "Size must be between 1 and 1638", "Font",
							MB_ICONINFORMATION | MB_OK);
			pfbs->fExpectChoice = FALSE;
		}
		break;

	case TBI_Color:
		if (pfbs->fExpectChoice)
		{
			LONG ilSel = SendMessage(pfbs->hwndColor, CB_GETCURSEL, 0, 0);

			// Remember that we are picking a color
			pfbs->cf.dwMask |= CFM_COLOR;
			pfbs->dwCFMaskChange = CFM_COLOR;

			//$ FUTURE: For now always turn-off autocolor, but later we'll
			//			have to handle picking autocolor
			pfbs->cf.dwEffects &= ~CFE_AUTOCOLOR;

			if (ilSel < 0)
				pfbs->cf.crTextColor = 0;
			else
				pfbs->cf.crTextColor = (COLORREF) SendMessage(pfbs->hwndColor,
											CB_GETITEMDATA, (WPARAM) ilSel, 0);
			pfbs->fExpectChoice = FALSE;
		}
		break;

	case TBI_Bold:
	case TBI_Italic:
	case TBI_Underline:
	
		// NOTE: We reverse the if condition because by the time we get the
		//		 notification, the button has already been pressed.
		pfbs->dwCFMaskChange = rgdwCFEffect[nID - TBI_Bold];
		pfbs->cf.dwMask |= rgdwCFEffect[nID - TBI_Bold];
#ifdef NEVER
		if (!SendMessage(pfbs->hwndToolbar, TB_ISBUTTONCHECKED, nID, 0))
			pfbs->cf.dwEffects &= ~rgdwCFEffect[nID - TBI_Bold];
		else
			pfbs->cf.dwEffects |= rgdwCFEffect[nID - TBI_Bold];
#else
		pfbs->cf.dwEffects ^= rgdwCFEffect[nID - TBI_Bold];
#endif
		pfbs->fGiveUpFocus = TRUE;
		break;

	case TBI_Bullet:
		// NOTE: The button has already been pushed,
		// so the checked state is accurate
		pfbs->pf.dwMask |= PFM_NUMBERING | PFM_OFFSET;
		if (SendMessage(pfbs->hwndToolbar, TB_ISBUTTONCHECKED, nID, 0))
		{
			pfbs->pf.wNumbering = PFN_BULLET;
			pfbs->pf.dxOffset = cxBulletIndent;
		}
		else
		{
			pfbs->pf.wNumbering = 0;
			pfbs->pf.dxOffset = 0;
		}
		pfbs->fGiveUpFocus = TRUE;
		break;

	case TBI_IncreaseIndent:
	case TBI_DecreaseIndent:
		pfbs->fGiveUpFocus = TRUE;
		break;

	case TBI_Left:
	case TBI_Center:
	case TBI_Right:
		pfbs->pf.dwMask |= PFM_ALIGNMENT;
		pfbs->pf.wAlignment = rgwPFAlignment[nID - TBI_Left];
		pfbs->fGiveUpFocus = TRUE;
		PaintAlignment(pfbs);
		break;



	}



	// Give up the focus ?
	if (pfbs->fGiveUpFocus)
	{
		pfbs->fGiveUpFocus = FALSE;
		SetFocus(hwnd);
	}

	// Go tell our parent
	SendMessage(GetParent(hwnd), WM_COMMAND,
				GET_WM_COMMAND_MPS(nID, hwndCtl, nNotify));
}


/*
 *	FB_OnPaint
 *
 *	Purpose:
 *		Update our screen
 *
 *	Arguments:
 *		hwnd		The window
 *
 *	Returns:
 *		None.
 */
LOCAL void FB_OnPaint(HWND hwnd)
{
	FormatBarState *	pfbs = PfbsGetWindowPtr(hwnd);
	PAINTSTRUCT			ps;

	// Repaint the toolbar as needed
	BeginPaint(hwnd, &ps);
//	PaintName(pfbs);
//	PaintSize(pfbs);
//	PaintColor(pfbs);
//	PaintEffects(pfbs);
//	PaintAlignment(pfbs);
	SendMessage(pfbs->hwndToolbar, WM_PAINT, 0, 0);
	EndPaint(hwnd, &ps);
}


/*
 *	SetCharFormat
 *
 *	Purpose:
 *		Set the current char format
 *
 *	Arguments:
 *		hwnd		The format bar window
 *		pcfNew		The new formatting
 *
 *	Returns:
 *		None.
 */
LOCAL VOID SetCharFormat(HWND hwnd, CHARFORMAT *pcfNew)
{
	FormatBarState *	pfbs = PfbsGetWindowPtr(hwnd);
	CHARFORMAT *		pcf = &pfbs->cf;
	DWORD				dwMask;
	DWORD				dwEffects;

	TraceCharFormat("EM_SETCHARFORMAT", pcfNew);

	if(pcfNew->cbSize != sizeof(CHARFORMAT))
		return;

	// Change in font name ?
	if (lstrcmpi(pcf->szFaceName, pcfNew->szFaceName) ||
		(pcf->bPitchAndFamily != pcfNew->bPitchAndFamily) ||
		(pcf->dwMask & CFM_FACE) != (pcfNew->dwMask & CFM_FACE))
	{
		pcf->dwMask &= ~CFM_FACE;
		pcf->dwMask |= pcfNew->dwMask & CFM_FACE;
		lstrcpy(pcf->szFaceName, pcfNew->szFaceName);
		pcf->bPitchAndFamily = pcfNew->bPitchAndFamily;
		PaintName(pfbs);
	}

	// Change in charset ?
	if (pcf->bCharSet != pcfNew->bCharSet ||
		(pcf->dwMask & CFM_CHARSET) != (pcfNew->dwMask & CFM_CHARSET))
	{
		pcf->dwMask &= ~CFM_CHARSET;
		pcf->dwMask |= pcfNew->dwMask & CFM_CHARSET;
		pcf->bCharSet = pcfNew->bCharSet;
		PaintSize(pfbs);
	}

	// Change in font size ?
	if (pcf->yHeight != pcfNew->yHeight ||
		(pcf->dwMask & CFM_SIZE) != (pcfNew->dwMask & CFM_SIZE))
	{
		pcf->dwMask &= ~CFM_SIZE;
		pcf->dwMask |= pcfNew->dwMask & CFM_SIZE;
		pcf->yHeight = pcfNew->yHeight;
		PaintSize(pfbs);
	}

	// Change in font color ?
	if (pcf->crTextColor != pcfNew->crTextColor ||
		(pcf->dwMask & CFM_COLOR) != (pcfNew->dwMask & CFM_COLOR))
	{		
		pcf->dwMask &= ~CFM_COLOR;
		pcf->dwMask |= pcfNew->dwMask & CFM_COLOR;
		pcf->crTextColor = pcfNew->crTextColor;
		PaintColor(pfbs);
	}

	// Change in effects ?
	dwMask = pcf->dwMask & CFM_MASKS;
	dwEffects = pcf->dwEffects & CFE_EFFECTS;
	if (((pcfNew->dwMask & CFM_MASKS) != dwMask) ||
		((pcfNew->dwEffects & CFE_EFFECTS) != dwEffects))
	{
		pcf->dwMask &= ~CFM_MASKS;
		pcf->dwMask |= pcfNew->dwMask & CFM_MASKS;
		pcf->dwEffects = pcfNew->dwEffects & CFE_EFFECTS;
		PaintEffects(pfbs);
	}
}


/*
 *	SetParaFormat
 *
 *	Purpose:
 *		Set the current char format
 *
 *	Arguments:
 *		hwnd		The format bar window
 *		ppfNew		The new formatting
 *
 *	Returns:
 *		None.
 */
LOCAL VOID SetParaFormat(HWND hwnd, PARAFORMAT *ppfNew)
{
	FormatBarState *	pfbs = PfbsGetWindowPtr(hwnd);
	PARAFORMAT *		ppf = &pfbs->pf;
	DWORD				dwMaskOld = ppf->dwMask;
	BOOL				fChanged = FALSE;

	// update the mask for tri-state sake
	ppf->dwMask = (ppf->dwMask & ~(PFM_NUMBERING | PFM_ALIGNMENT)) |
		(ppfNew->dwMask & (PFM_NUMBERING | PFM_ALIGNMENT));

	// Change in numbering ?
	if (ppf->wNumbering != ppfNew->wNumbering)
	{
		const BOOL fBulleted = ppfNew->wNumbering == PFN_BULLET;

		ppf->wNumbering = ppfNew->wNumbering;
		SendMessage(pfbs->hwndToolbar, TB_CHECKBUTTON, TBI_Bullet, MAKELONG(fBulleted, 0));
	}

	// Change in alignment ?
	if (ppf->wAlignment != ppfNew->wAlignment)
	{
		ppf->wAlignment = ppfNew->wAlignment;
		fChanged |= TRUE;
	}

	if (fChanged || dwMaskOld != ppf->dwMask)
		PaintAlignment(pfbs);
}


/*
 *	LFormatBarWndProc
 *
 *	Purpose:
 *		Take care of handling the notifications from the combobox controls we
 *		get from the format bar
 *
 *	Arguments:
 *		hwnd
 *		wMsg
 *		wParam
 *		lParam
 *
 *	Returns:
 *		LRESULT
 */
LRESULT CALLBACK LFormatBarWndProc(HWND hwnd, UINT wMsg, WPARAM wParam,
									LPARAM lParam)
{
	FormatBarState *pfbs = PfbsGetWindowPtr(hwnd);
	BOOL fShift;

	switch(wMsg)
	{
	HANDLE_MSG(hwnd, WM_MEASUREITEM, FB_OnMeasureItem);

	case WM_COMMAND:
		FB_OnCommand(hwnd, GET_WM_COMMAND_ID(wParam, lParam),
					 GET_WM_COMMAND_HWND(wParam, lParam),
					 GET_WM_COMMAND_CMD(wParam, lParam));
		return 0;

	case WM_NCCREATE:
		return FB_OnNcCreate(hwnd, (CREATESTRUCT *) lParam);


	case WM_DRAWITEM:
		FB_OnDrawItem(hwnd, (DRAWITEMSTRUCT *) lParam);
		return TRUE;

	case WM_PAINT:
		FB_OnPaint(hwnd);
		break;

	case WM_DESTROY:
		if (pfbs)
		{
			if (pfbs->hwndName)
				DestroyWindow(pfbs->hwndName);
			if (pfbs->hwndSize)
				DestroyWindow(pfbs->hwndSize);
			if (pfbs->hwndColor)
				DestroyWindow(pfbs->hwndColor);
			if (pfbs->hwndToolbar)
				DestroyWindow(pfbs->hwndToolbar);
			if (pfbs->hbrushWindow)
				DeleteObject(pfbs->hbrushWindow);
			if (pfbs->hbrushHighlight)
				DeleteObject(pfbs->hbrushHighlight);
			if (pfbs->hbrushButtonFace)
				DeleteObject(pfbs->hbrushButtonFace);
			if (pfbs->hdc)
				DeleteDC(pfbs->hdc);
			GlobalFreePtr(pfbs);
			SetWindowPtr(hwnd, NULL);
		}
		break;

	case WM_SHOWWINDOW:
		if (pfbs)
		{
			INT	nCmd =	wParam ? SW_SHOW : SW_HIDE;

			ShowWindow(pfbs->hwndToolbar, nCmd);
			SendMessage(pfbs->hwndToolbar, WM_SIZE, 0, 0);
			ShowWindow(pfbs->hwndName, nCmd);
			ShowWindow(pfbs->hwndSize, nCmd);
			ShowWindow(pfbs->hwndColor, nCmd);
		}
		return 0;

	case WM_SIZE:
		if (pfbs)
		{
			RECT	rcMe;
			RECT	rcParent;

			// Get our current dimensions
			GetClientRect(pfbs->hwndToolbar, &rcMe);
			rcMe.bottom += 3;

			// We want to fit our parent's width
			GetClientRect(GetParent(hwnd), &rcParent);

			// Make it so
			SetWindowPos(hwnd, HWND_TOP, 0, 0, rcParent.right - rcParent.left,
						rcMe.bottom - rcMe.top, SWP_NOMOVE | SWP_NOZORDER);
		}
		return 0;

	case WM_ENABLE:
		if (pfbs)
		{
			INT	nID;

			EnableWindow(pfbs->hwndToolbar, wParam);
			EnableWindow(pfbs->hwndName, wParam);
			EnableWindow(pfbs->hwndSize, wParam);
			EnableWindow(pfbs->hwndColor, wParam);
			for (nID = TBI_Bold; nID <= TBI_Right; nID++)
				SendMessage(pfbs->hwndToolbar, TB_ENABLEBUTTON, nID,
							MAKELONG(wParam, 0));
		}
		break;

	case WM_SYSCOLORCHANGE:
		// Update our concept of the brushes
		if (pfbs)
			UpdateBrushes(hwnd);
		break;

	case EM_GETPARAFORMAT:
		Assert(lParam);
		if (lParam)
		{
			PARAFORMAT * const ppf = (PARAFORMAT *) lParam;

			if(ppf->cbSize == sizeof(PARAFORMAT))
			{
				CopyMemory(((LPBYTE) ppf) + sizeof(ppf->cbSize),
					((LPBYTE) &pfbs->pf) + sizeof(ppf->cbSize),
					sizeof(PARAFORMAT) - sizeof(ppf->cbSize));
			}
		}
		return 0;

	case EM_SETPARAFORMAT:
		Assert(lParam);
		if (lParam)
			SetParaFormat(hwnd, (PARAFORMAT *) lParam);
		return TRUE;

	case EM_GETCHARFORMAT:
		Assert(lParam);
		if (lParam)
		{
			CHARFORMAT * const pcf = (CHARFORMAT *) lParam;

			if(pcf->cbSize == sizeof(CHARFORMAT))
			{
				CopyMemory(((LPBYTE) pcf) + sizeof(pcf->cbSize),
					((LPBYTE) &pfbs->cf) + sizeof(pcf->cbSize),
					sizeof(CHARFORMAT) - sizeof(pcf->cbSize));
				pcf->dwMask &= pfbs->dwCFMaskChange;
				TraceCharFormat("EM_GETCHARFORMAT", pcf);
			}
		}
		return 0;

	case EM_SETCHARFORMAT:
		Assert(lParam);
		if (lParam)
			SetCharFormat(hwnd, (CHARFORMAT *) lParam);
		return TRUE;

	case WM_RETURN:
		// The user made a choice
		pfbs->fExpectChoice = TRUE;
		pfbs->fGiveUpFocus = TRUE;
		FB_OnCommand(hwnd, wParam, (HWND) lParam, CBN_SELCHANGE);
		return 0;

	case WM_TAB:
		// Only change the choice if TAB was pressed on a closed dropdown
		pfbs->fExpectChoice = !SendMessage((HWND) lParam, CB_GETDROPPEDSTATE,
											0, 0);
		FB_OnCommand(hwnd, wParam, (HWND) lParam, CBN_SELCHANGE);

		// Change focus, FB_OnCommand will take care of copying changed data
		fShift = GetKeyState(VK_SHIFT) & 0x8000 ? TRUE : FALSE;
		switch (wParam)
		{
		case TBI_Name:
			SetFocus(fShift ? pfbs->hwndColor : pfbs->hwndSize);
			break;

		case TBI_Size:
			SetFocus(fShift ? pfbs->hwndName : pfbs->hwndColor);
			break;

		case TBI_Color:
			SetFocus(fShift ? pfbs->hwndSize : pfbs->hwndName);
			break;
		}
		return 0;

	case WM_ESCAPE:
		SetFocus(hwnd);
		FB_OnPaint(hwnd);
		return 0;
	}

	return DefWindowProc(hwnd, wMsg, wParam, lParam);
}


/*
 *	FInitFormatBarClass()
 *
 *	Purpose:
 *		Superclasses the toolbar so that we get support for a format bar
 *
 *	Arguments:
 *		hinst		This instance
 *
 *	Returns:
 *		TRUE if class is successfully initialized.
 */
BOOL FInitFormatBarClass(HINSTANCE hinst)
{
	WNDCLASS wc;

	// Are format bars registered yet ?
	if (!GetClassInfo(hinst, szFormatBar, &wc))
	{
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = LFormatBarWndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = sizeof(FormatBarState *);
		wc.hInstance = hinst;
		wc.hIcon = NULL;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = szFormatBar;
	
		if (!RegisterClass(&wc))
		{
			TraceError("FInitFormatBarClass: Couldn't register", -1);
			return FALSE;
		}
	}
	return TRUE;
}


/*
 *	FCreateFormatBar
 *
 *	Purpose:
 *		Creates a format bar
 *
 *	Arguments:
 *		hwndParent		The parent of this format bar
 *		wID				The control ID to be associated with this format bar
 *		hdc				A device context that we can copy so we can do various
 *						font information functions
 *
 *	Returns:
 *		The window handle of the format bar
 */
HWND HwndCreateFormatBar(HWND hwndParent, WORD wID, HDC hdc)
{
	HWND		hwndFormatBar = NULL;
	HINSTANCE	hinst = (HINSTANCE) GetWindowLong(hwndParent, GWL_HINSTANCE);
	RECT		rc;

	// Initialize the format bar class
	//$ REVIEW: Move into WinMain or LibMain
	if (!FInitFormatBarClass(hinst))
	{
		TraceError("HwndCreateFormatBar: Not registered", -1);
		return NULL;
	}

	// Create the main toolbar
	GetClientRect(hwndParent, &rc);
	hwndFormatBar = CreateWindow(szFormatBar, NULL, WS_CHILD | WS_VISIBLE,
									0, 0, rc.right - rc.left, 29,
									hwndParent, (HMENU) wID, hinst,
									(LPVOID) (hdc ? &hdc : NULL));
	if (!hwndFormatBar)
	{
		TraceError("HwndCreateFormatBar: Can't create", -1);
		goto Error;
	}

	// Return a pointer to our state information
	return hwndFormatBar;
	
Error:
	return NULL;
}
