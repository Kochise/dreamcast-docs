//=--------------------------------------------------------------------------=
// CardPPG.Cpp
//=--------------------------------------------------------------------------=
// Copyright 1995 - 1997 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// property page implementations for Card control.
//
#include "IPServer.H"

#include "LocalObj.H"
#include "CARDPPG.H"
#include "CARDCtl.H"
#include "Resource.H"
#include "Util.H"


// for ASSERT and FAIL
//
SZTHISFILE

//=--------------------------------------------------------------------------=
// Property Page messages
//=--------------------------------------------------------------------------=
// in addition to regular windows messages you'll receive for a dialog box,
// you'll receive the following messages in your property page implementation:
//
// PPM_NEWOBJECTS:
//    wParam = 0;
//    lParam = (LPARAM)(HRESULT *)hr
//
//  - in this message, you should call FirstControl() to get a pointer to a
//    control, and initialize the values in the property page dialog with
//    values from the control object.  put results from the operation in
//    the HRESULT pointed to by LPARAM.
//
// PPM_APPLY:
//    wParam = 0;
//    lParam = (LPARAM)(HRESULT *)hr
//
//  - this message is sent to your dialog whenever the user clicks APPLY or OK
//    in the dialog.  you should have a loop with the following code in it:
//
//      for (pUnk = FirstControl(&dwCookie) ; pUnk; pUnk = NextControl(&dwCookie)) {
//            hr = pUnk->QueryInterface(IID_IMyCtlInterface, (void **)&pMyCtl);
//            // set properties here!!!
//      }
//
//    call PropPageException() if there is an error while setting propertites
//    to show the exception set up by the property set routine.
//
// PPM_EDITPROPERTY:
//    wParam = dispid
//    lParam = (LPARAM)(HRESULT *)hr
//
//  - sent to your dialog when somebody wants you to set the focus to a specific
//    property [typically, one will see a call to this when one returns a page
//    from IPerPropertyBrowsing::MapPropertyToPage].  you can use this
//    to bring up dialogs, or do whatever flaps your flagella.
//


//=--------------------------------------------------------------------------=
// CCardGeneralPage::Create
//=--------------------------------------------------------------------------=
// global static creation function.
//
// Parameters:
//    IUnknown *    - [in] controlling unknown
//
// Output:
//    IUnknown *    - new prop page.
//
// Notes:
//
IUnknown *CCardGeneralPage::Create
(
    IUnknown *pUnkOuter
)
{
    return (IUnknown *)new CCardGeneralPage(pUnkOuter);
}

//=--------------------------------------------------------------------------=
// CCardGeneralPage::CCardGeneralPage
//=--------------------------------------------------------------------------=
// constructor.
//
// Parameters:
//    IUnknown *        - [in] controlling unknown.
//
// Notes:
//
CCardGeneralPage::CCardGeneralPage
(
    IUnknown *pUnkOuter
)
: CPropertyPage(pUnkOuter, OBJECT_TYPE_PPGCARDGENERAL)
{
    // initialize local variables here.
}

//=--------------------------------------------------------------------------=
// CCardGeneralPage::~CCardGeneralPage
//=--------------------------------------------------------------------------=
// destructor.
//
// Notes:
//
CCardGeneralPage::~CCardGeneralPage()
{
    // clean up
}

static int SimpleAtoi( const char *str )
{
	int num = 0;
	const char *s;

	for( s = (*str == '-' ? str+1 : str); *s >= '0' && *s <= '9'; s++ )
		num = num * 10 + (*s - '0');

	return( *str == '-' ? -num : num );
}

static void SetDropDown( HWND hwnd, const char *strs[], int id, short set )
{
	short newset;
	int i;

	newset = -1000;
	for( i = 0; strs[i]; i++ )
	{
		SendMessage( GetDlgItem( hwnd, id ), CB_ADDSTRING, 
			0, (LPARAM) strs[i] );
		if( SimpleAtoi(strs[i]) == set )
			newset = i;
	}
	if( newset != -1000 )
		SendMessage( GetDlgItem( hwnd, id ), CB_SETCURSEL,
				(WPARAM) newset, 0 );
}

//=--------------------------------------------------------------------------=
// CCardGeneralPage::DialogProc
//=--------------------------------------------------------------------------=
// our dialog proc.
//
// Parameters:
//    - see win32sdk docs on DialogProc
//
// Notes:
//
BOOL CCardGeneralPage::DialogProc
(
    HWND   hwnd,
    UINT   msg,
    WPARAM wParam,
    LPARAM lParam
)
{
    HRESULT     hr;
    ICard *pCard;
    IUnknown   *pUnk;
    DWORD       dwDummy;
    enumCardNumber number;
    enumCardSuite suite;
    enumCardAlignment cardalignment;
	VARIANT_BOOL invert;

	static const char *numstr[] = {
		"1   - Ace",
		"2", "3", "4", "5", "6", "7", "8", "9", "10",
		"11  - Jack",
		"12  - Queen",
		"13  - King",
	        "14  - Joker",
		NULL };

	static const char *alignstr[] = {
		"0   - Top Left",
		"1   - Top Center",
		"2   - Top Right",
		"3   - Center Left",
		"4   - Center",
		"5   - Center Right",
		"6   - Bottom Left",
		"7   - Bottom Center",
		"8   - Bottom Right",
		"9   - Stretch",
		NULL };

	static const char *suitestr[] = {
		"0   - Invisible",
		"1   - Clubs", 
		"2   - Spades", 
		"3   - Hearts", 
		"4   - Diamonds",
		"-1  - Card Back: Weave 1",		
		"-2  - Card Back: Weave 2",		
		"-3  - Card Back: Robot",		
		"-4  - Card Back: Roses",		
		"-5  - Card Back: Vine 1 (black)",
		"-6  - Card Back: Vine 2 (blue)",		
		"-7  - Card Back: Fish 1 (light blue)",		
		"-8  - Card Back: Fish 2 (dark blue)",		
		"-9  - Card Back: Seashell",		
		"-10 - Card Back: Castel",
		"-11 - Card Back: Beach",
		"-12 - Card Back: Hand",
		"-13 - Card Back: Casino", 
		NULL };

    switch (msg) {

      // we've been given some new objects, so go and re-set up the dialog page.
      //
      case PPM_NEWOBJECTS:
        {

        pUnk = FirstControl(&dwDummy);
        if (!pUnk) return FALSE;

        hr = pUnk->QueryInterface(IID_ICard, (void **)&pCard);
        if (FAILED(hr)) return FALSE;

        pCard->get_Number(&number);
        pCard->get_Suite(&suite);
        pCard->get_Invert(&invert);
	pCard->get_CardAlignment(&cardalignment);

	SetDropDown( hwnd, suitestr, IDC_SUITE, suite );
	SetDropDown( hwnd, numstr, IDC_NUMBER, number );
	SetDropDown( hwnd, alignstr, IDC_ALIGNMENT, cardalignment );

	CheckDlgButton( hwnd, IDC_INVERT, invert == VARIANT_TRUE ? 1 : 0 );

        pCard->Release();
        }
        return TRUE;

      case PPM_APPLY:
        {
        char      szTmp[128];

        // get all the controls we have to update.
        //
        for (pUnk = FirstControl(&dwDummy) ; pUnk; pUnk = NextControl(&dwDummy)) 
		{
            hr = pUnk->QueryInterface(IID_ICard, (void **)&pCard);
            if (FAILED(hr)) continue;
    
            GetDlgItemText(hwnd, IDC_NUMBER, szTmp, 128);
	    number = (enumCardNumber) SimpleAtoi(szTmp);
            GetDlgItemText(hwnd, IDC_SUITE, szTmp, 128);
	    suite = (enumCardSuite) SimpleAtoi(szTmp);
            GetDlgItemText(hwnd, IDC_ALIGNMENT, szTmp, 128);
	    cardalignment = (enumCardAlignment) SimpleAtoi(szTmp);
	    invert = IsDlgButtonChecked( hwnd, IDC_INVERT ) ? VARIANT_TRUE : VARIANT_FALSE;
	    
            pCard->put_Number(number);
	    pCard->put_Suite(suite);
	    pCard->put_Invert(invert);
	    pCard->put_CardAlignment(cardalignment);
            pCard->Release();
        }
        }
        return TRUE;

      case WM_COMMAND:
        switch (LOWORD(wParam)) {
          case IDC_SUITE: case IDC_NUMBER: case IDC_ALIGNMENT:
            if (HIWORD(wParam) == CBN_SELCHANGE)
                MakeDirty();
	  case IDC_INVERT:
	    if( HIWORD(wParam) == BN_CLICKED )
		MakeDirty();
        }
        break;
    }

	return(FALSE);
}
