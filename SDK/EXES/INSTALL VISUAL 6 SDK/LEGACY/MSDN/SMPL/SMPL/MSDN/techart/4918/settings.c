/*-----------------------------------------------------------------------------
    This is a part of the Microsoft Source Code Samples. 
    Copyright (C) 1995 Microsoft Corporation.
    All rights reserved. 
    This source code is only intended as a supplement to 
    Microsoft Development Tools and/or WinHelp documentation.
    See these sources for detailed information regarding the 
    Microsoft samples programs.

    MODULE: Settings.c

    PURPOSE: Controls all dialog controls in the Settings Dialog as well
	     as the comm events dialog, flow control dialog, and timeouts
	     dialog.  The module also controls the tty settings based on
	     these dialogs and also control comm port settings using 
	     SetCommState and SetCommTimeouts.

    FUNCTIONS:
	OpenSettingsToolbar - Creates the Settings Dialog
	ChangeConnection    - Modifies menus & controls based on connection state
	UpdateTTYInfo       - Modifies TTY data from Settings Dialog and
			      if connected, updates open comm port settings
	FillComboBox        - Fills a combo box with strings
	SetComboBox         - Selects an entry from a combo box
	SettingDlgInit      - Initializes settings dialog
	GetdwTTYItem        - returns a DWORD value from a dialog control
	GetbTTYItem         - returns a BYTE value from a dialog control
	ToolbarProc         - Dialog procedure for Settings Dialog
	InitHexControl      - Places a byte value into edit controls of a dialog
	GetHexControl       - returns hex data from a control and converts to a char
	InitCommEventsDlg   - Initializes Comm Events Dialog
	SaveCommEventsDlg   - Saves comm events flag if changed
	CommEventsProc      - Dialog procedure for Comm Events Dialog
	SaveFlowControlDlg  - Saves flow control settings if changed
	InitFlowControlDlg  - Inititlizes Flow Control Dialog
	FlowDefault         - sets "hardware" or "software" flow control
	FlowControlProc     - Dialog procedure for Flow Control Dialog
	InitTimeoutsDlg     - Initializes Timeouts Dialog
	SaveTimeoutsDlg     - Saves comm timeouts from Timeouts Dialog
	TimeoutsProc        - Dialog procedure for Timeouts Dialog

-----------------------------------------------------------------------------*/

#include <windows.h>
#include <stdio.h>
#include "mttty.h"

#define MAXLEN_TEMPSTR  20

/*
    Prototypes for functions called only within this file
*/
void FillComboBox( HWND, char ** szString, DWORD *, WORD, DWORD );
BOOL SettingsDlgInit( HWND );
DWORD GetdwTTYItem( HWND, int, char **, DWORD *, int );
BYTE GetbTTYItem( HWND, int, char **, DWORD *, int);
BOOL CALLBACK CommEventsProc( HWND, UINT, WPARAM, LPARAM );
BOOL CALLBACK ToolbarProc( HWND, UINT, WPARAM, LPARAM );
void InitHexControl(HWND, WORD, WORD, char);
char GetHexControl(HWND, WORD, WORD);
void SaveCommEventsDlg( HWND );
void InitCommEventsDlg( HWND, DWORD );
BOOL CALLBACK FlowControlProc( HWND, UINT, WPARAM, LPARAM );
void InitFlowControlDlg( HWND );
void SaveFlowControlDlg( HWND );
void FlowDefault(HWND hdlg, WORD wId);
BOOL CALLBACK TimeoutsProc( HWND, UINT, WPARAM, LPARAM );
void InitTimeoutsDlg( HWND, COMMTIMEOUTS );
void SaveTimeoutsDlg( HWND );
BOOL CALLBACK GetADWORDProc( HWND, UINT, WPARAM, LPARAM );

/*
    GLOBALS for this file
    The string arrays are the items in the dialog list controls.
*/

DCB dcbTemp;

char * szBaud[] = {
	    "110", "300", "600", "1200", "2400", 
	    "4800", "9600", "14400", "19200",
	    "38400", "56000", "57600", "115200", 
	    "128000", "256000"
	};

DWORD   BaudTable[] =  {
	    CBR_110, CBR_300, CBR_600, CBR_1200, CBR_2400,
	    CBR_4800, CBR_9600, CBR_14400, CBR_19200, CBR_38400,
	    CBR_56000, CBR_57600, CBR_115200, CBR_128000, CBR_256000
	} ;

char * szParity[] =   {   "None", "Even", "Odd", "Mark", "Space" };

DWORD   ParityTable[] = {  NOPARITY, EVENPARITY, ODDPARITY, MARKPARITY, SPACEPARITY  } ;

char * szStopBits[] =  {  "1", "1.5", "2"  };

DWORD   StopBitsTable[] =  { ONESTOPBIT, ONE5STOPBITS, TWOSTOPBITS } ;

char * szDTRControlStrings[] = { "Enable", "Disable", "Handshake" };

DWORD   DTRControlTable[] = { DTR_CONTROL_ENABLE, DTR_CONTROL_DISABLE, DTR_CONTROL_HANDSHAKE };

char * szRTSControlStrings[] = { "Enable", "Disable", "Handshake", "Toggle" };

DWORD   RTSControlTable[] = {   RTS_CONTROL_ENABLE, RTS_CONTROL_DISABLE, 
				RTS_CONTROL_HANDSHAKE, RTS_CONTROL_TOGGLE };

DWORD   EventFlagsTable[] = {
	    EV_BREAK, EV_CTS, EV_DSR, EV_ERR, EV_RING,
	    EV_RLSD, EV_RXCHAR, EV_RXFLAG, EV_TXEMPTY
	};

/*-----------------------------------------------------------------------------

FUNCTION: OpenSettingsToolbar(HWND)

PURPOSE: Open Settings Dialog

PARAMETERS:
    hWnd - dialog owner window handle

HISTORY:   Date:      Author:     Comment:
	   10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void OpenSettingsToolbar(HWND hWnd)
{
    ghWndToolbarDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_TOOLBARSETTINGS), hWnd, ToolbarProc);

    if (ghWndToolbarDlg == NULL)
	ErrorReporter("CreateDialog (Toolbar Dialog)");

    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: ChangeConnection(HWND, BOOL)

PURPOSE: Modifies connection appearance

PARAMETERS:
    hwnd       - menu owner windows
    fConnected - TRUE sets connection appearance to connected
		 FALSE sets appearance to not connected

HISTORY:   Date:      Author:     Comment:
	   10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void ChangeConnection( HWND hwnd, BOOL fConnected )
{
    HMENU hMenu;
    int i;

    if (fConnected) {
	/*
	    The port is connected.  Need to :
	    Disable connect menu and enable disconnect menu.
	    Enable file transfer menu
	    Disable comm port selection box
	    Disable no writing, no reading, no events, no status check boxes
	    Enable status check boxes
	    Set focus to the child tty window
	*/
	hMenu = GetMenu( hwnd ) ;
	EnableMenuItem( hMenu, ID_FILE_CONNECT,
		       MF_GRAYED | MF_DISABLED | MF_BYCOMMAND ) ;
	EnableMenuItem( hMenu, ID_FILE_DISCONNECT,
		       MF_ENABLED | MF_BYCOMMAND ) ;

	EnableMenuItem( hMenu, ID_TRANSFER_SENDFILETEXT,
		       MF_ENABLED | MF_BYCOMMAND ) ;
	EnableMenuItem( hMenu, ID_TRANSFER_RECEIVEFILETEXT,
		       MF_ENABLED | MF_BYCOMMAND ) ;
	EnableMenuItem( hMenu, ID_TRANSFER_SENDREPEATEDLY,
		       MF_ENABLED | MF_BYCOMMAND ) ;
	EnableMenuItem( hMenu, ID_TRANSFER_ABORTSENDING,
		       MF_DISABLED | MF_GRAYED | MF_BYCOMMAND );
	EnableMenuItem( hMenu, ID_TRANSFER_ABORTREPEATEDSENDING,
		       MF_DISABLED | MF_GRAYED | MF_BYCOMMAND );

	EnableWindow( GetDlgItem(ghWndToolbarDlg, IDC_PORTCOMBO), FALSE);
	EnableWindow( GetDlgItem(ghWndToolbarDlg, IDC_NOWRITINGCHK), FALSE);
	EnableWindow( GetDlgItem(ghWndToolbarDlg, IDC_NOREADINGCHK), FALSE);
	EnableWindow( GetDlgItem(ghWndToolbarDlg, IDC_NOEVENTSCHK),  FALSE);
	EnableWindow( GetDlgItem(ghWndToolbarDlg, IDC_NOSTATUSCHK),  FALSE);

	for (i = IDC_STATCTS; i <= IDC_STATRLSD; i++)
	    EnableWindow( GetDlgItem(ghWndStatusDlg, i), TRUE );

	for (i = IDC_CTSHOLDCHK; i <= IDC_RXCHAREDIT; i++)
	    EnableWindow( GetDlgItem(ghWndStatusDlg, i), TRUE);
    
	SetFocus(ghWndTTY);
    }
    else {
	//
	// Not connected, do opposite of above.
	//
	hMenu = GetMenu( hwnd ) ;
	EnableMenuItem( hMenu, ID_FILE_CONNECT,
		       MF_ENABLED | MF_BYCOMMAND ) ;
	EnableMenuItem( hMenu, ID_FILE_DISCONNECT,
		       MF_GRAYED | MF_DISABLED | MF_BYCOMMAND ) ;

	EnableMenuItem( hMenu, ID_TRANSFER_SENDFILETEXT,
		       MF_DISABLED | MF_GRAYED | MF_BYCOMMAND ) ;
	EnableMenuItem( hMenu, ID_TRANSFER_RECEIVEFILETEXT,
		       MF_DISABLED | MF_GRAYED | MF_BYCOMMAND ) ;
	EnableMenuItem( hMenu, ID_TRANSFER_SENDREPEATEDLY,
		       MF_DISABLED | MF_GRAYED | MF_BYCOMMAND ) ;
	EnableMenuItem( hMenu, ID_TRANSFER_ABORTSENDING,
		       MF_DISABLED | MF_GRAYED | MF_BYCOMMAND ) ;
	EnableMenuItem( hMenu, ID_TRANSFER_ABORTREPEATEDSENDING,
		       MF_DISABLED | MF_GRAYED | MF_BYCOMMAND );

	EnableWindow( GetDlgItem(ghWndToolbarDlg, IDC_PORTCOMBO), TRUE);
	EnableWindow( GetDlgItem(ghWndToolbarDlg, IDC_NOWRITINGCHK), TRUE);
	EnableWindow( GetDlgItem(ghWndToolbarDlg, IDC_NOREADINGCHK), TRUE);
	EnableWindow( GetDlgItem(ghWndToolbarDlg, IDC_NOEVENTSCHK),  TRUE);
	EnableWindow( GetDlgItem(ghWndToolbarDlg, IDC_NOSTATUSCHK),  TRUE);

	for (i = IDC_STATCTS; i <= IDC_STATRLSD; i++) {
	    CheckDlgButton(ghWndStatusDlg, i, 0);
	    EnableWindow( GetDlgItem(ghWndStatusDlg, i), FALSE );
	}

	for (i = IDC_CTSHOLDCHK; i <= IDC_RXCHAREDIT; i++) {
	    if (i != IDC_TXCHAREDIT && i != IDC_RXCHAREDIT)
		CheckDlgButton(ghWndStatusDlg, i, 0);
	    else
		SetDlgItemInt(ghWndStatusDlg, i, 0, FALSE);

	    EnableWindow( GetDlgItem(ghWndStatusDlg, i), FALSE);
	}

	SetFocus(ghwndMain);
    }

    return;
}


/*-----------------------------------------------------------------------------

FUNCTION: UpdateTTYInfo(void)

PURPOSE: Modifies TTY data based on the settings and calls UpdateConnection

COMMENTS: Modifies the data based on the dialog. If connected, 
	  calls UpdateConnection.

HISTORY:   Date:      Author:     Comment:
	   10/27/95   AllenD      Wrote it
	    1/ 9/96   AllenD      Split DCB settings to new function

-----------------------------------------------------------------------------*/
void UpdateTTYInfo()
{
    //
    // update globals from dialog settings
    //
    GetDlgItemText(ghWndToolbarDlg, IDC_PORTCOMBO, gszPort, sizeof(gszPort));

    BAUDRATE(TTYInfo) = GetdwTTYItem( ghWndToolbarDlg, 
					IDC_BAUDCOMBO, 
					szBaud, 
					BaudTable, 
					sizeof(BaudTable)/sizeof(BaudTable[0]));

    PARITY(TTYInfo) = GetbTTYItem( ghWndToolbarDlg, 
				     IDC_PARITYCOMBO, 
				     szParity, 
				     ParityTable, 
				     sizeof(ParityTable)/sizeof(ParityTable[0]));

    STOPBITS(TTYInfo) = GetbTTYItem( ghWndToolbarDlg, 
				       IDC_STOPBITSCOMBO, 
				       szStopBits, 
				       StopBitsTable, 
				       sizeof(StopBitsTable)/sizeof(StopBitsTable[0]));

    LOCALECHO(TTYInfo) = IsDlgButtonChecked(ghWndToolbarDlg, IDC_LOCALECHOCHK);
    BYTESIZE(TTYInfo) = GetDlgItemInt(ghWndToolbarDlg, IDC_DATABITSCOMBO, NULL, FALSE);
    NEWLINE(TTYInfo) = IsDlgButtonChecked(ghWndToolbarDlg, IDC_LFBTN);
    AUTOWRAP(TTYInfo) = IsDlgButtonChecked(ghWndToolbarDlg, IDC_AUTOWRAPCHK);
    DISPLAYERRORS(TTYInfo) = IsDlgButtonChecked(ghWndToolbarDlg, IDC_DISPLAYERRORSCHK);

    NOREADING(TTYInfo) = IsDlgButtonChecked(ghWndToolbarDlg, IDC_NOREADINGCHK);
    NOWRITING(TTYInfo) = IsDlgButtonChecked(ghWndToolbarDlg, IDC_NOWRITINGCHK);
    NOEVENTS(TTYInfo)  = IsDlgButtonChecked(ghWndToolbarDlg, IDC_NOEVENTSCHK);
    NOSTATUS(TTYInfo)  = IsDlgButtonChecked(ghWndToolbarDlg, IDC_NOSTATUSCHK);

    if (CONNECTED(TTYInfo))      // if connected, then update port state
	UpdateConnection();

    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: UpdateConnection( void )

PURPOSE: Sets port state based on settings from the user

COMMENTS: Sets up DCB structure and calls SetCommState.
	  Sets up new timeouts by calling SetCommTimeouts.

HISTORY:   Date:      Author:     Comment:
	    1/ 9/96   AllenD      Wrote it

-----------------------------------------------------------------------------*/
BOOL UpdateConnection()
{
    DCB dcb = {0};
    
    dcb.DCBlength = sizeof(dcb);

    //
    // get current DCB settings
    //
    if (!GetCommState(COMDEV(TTYInfo), &dcb))
	ErrorReporter("GetCommState");

    //
    // update DCB rate, byte size, parity, and stop bits size
    //
    dcb.BaudRate = BAUDRATE(TTYInfo);
    dcb.ByteSize = BYTESIZE(TTYInfo);
    dcb.Parity   = PARITY(TTYInfo);
    dcb.StopBits = STOPBITS(TTYInfo);

    //
    // update event flags
    //
    if (EVENTFLAGS(TTYInfo) & EV_RXFLAG)
	dcb.EvtChar = FLAGCHAR(TTYInfo);      
    else
	dcb.EvtChar = '\0';

    //
    // update flow control settings
    //
    dcb.fDtrControl     = DTRCONTROL(TTYInfo);
    dcb.fRtsControl     = RTSCONTROL(TTYInfo);

    dcb.fOutxCtsFlow    = CTSOUTFLOW(TTYInfo);
    dcb.fOutxDsrFlow    = DSROUTFLOW(TTYInfo);
    dcb.fDsrSensitivity = DSRINFLOW(TTYInfo);
    dcb.fOutX           = XONXOFFOUTFLOW(TTYInfo);
    dcb.fInX            = XONXOFFINFLOW(TTYInfo);
    dcb.fTXContinueOnXoff = TXAFTERXOFFSENT(TTYInfo);
    dcb.XonChar         = XONCHAR(TTYInfo);
    dcb.XoffChar        = XOFFCHAR(TTYInfo);
    dcb.XonLim          = XONLIMIT(TTYInfo);
    dcb.XoffLim         = XOFFLIMIT(TTYInfo);

    //
    // DCB settings not in the user's control
    //
    dcb.fParity = TRUE;

    //
    // set new state
    //
    if (!SetCommState(COMDEV(TTYInfo), &dcb))
	ErrorReporter("SetCommState");

    //
    // set new timeouts
    //
    if (!SetCommTimeouts(COMDEV(TTYInfo), &(TIMEOUTSNEW(TTYInfo))))
	ErrorReporter("SetCommTimeouts");

    return TRUE;
}


/*-----------------------------------------------------------------------------

FUNCTION: FillComboBox(HWND, char **, DWORD *, WORD, DWORD)

PURPOSE: Populates dialog controls with proper strings

PARAMETERS:
    hCtrlWnd         - window handle of control being filled
    szString         - string table contains strings to fill control with
    npTable          - table of values corresponding to strings
    wTableLen        - length of the string table
    dwCurrentSetting - initialz combo box selection

COMMENTS: This function originally found in the Win32 COMM sample
	  Written by BryanW.  Modified for Win32 MTTTY Sample.

HISTORY:   Date:      Author:     Comment:
	   10/27/95   AllenD      Modified for MTTTY

-----------------------------------------------------------------------------*/
void FillComboBox( HWND hCtrlWnd, char ** szString,
			DWORD * npTable, WORD wTableLen, DWORD dwCurrentSetting )
{
    WORD wCount, wPosition ;

    for (wCount = 0; wCount < wTableLen; wCount++) {
	wPosition = LOWORD( SendMessage( hCtrlWnd, CB_ADDSTRING, 0,
					(LPARAM) (LPSTR) szString[wCount] ) ) ;

	//
	// use item data to store the actual table value
	//
	SendMessage( hCtrlWnd, CB_SETITEMDATA, (WPARAM) wPosition,
		     (LPARAM) *(npTable + wCount) ) ;

	//     
	// if this is our current setting, select it
	//
	if (*(npTable + wCount) == dwCurrentSetting)
	    SendMessage( hCtrlWnd, CB_SETCURSEL, (WPARAM) wPosition, 0L ) ;
    }
    return ;
}

/*-----------------------------------------------------------------------------

FUNCTION: SetComboBox(HWND, WORD, DWORD)

PURPOSE: Selects an entry from a dialog combobox

PARAMETERS:
    hCtrlWnd     - windows handle of control
    wTableLen    - length of value table for this control
    dwNewSetting - new item to base selection on

HISTORY:   Date:      Author:     Comment:
	   11/20/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void SetComboBox( HWND hCtrlWnd, WORD wTableLen, DWORD dwNewSetting )
{
    WORD wCount, wItemData ;

    for (wCount = 0; wCount < wTableLen; wCount++) {
	wItemData = LOWORD( SendMessage( hCtrlWnd, CB_GETITEMDATA, (WPARAM) wCount, 0L ) );

	if (wItemData == dwNewSetting) {
	    SendMessage( hCtrlWnd, CB_SETCURSEL, (WPARAM) wCount, 0L ) ;
	break;
	}
    }
    return ;
}

/*-----------------------------------------------------------------------------

FUNCTION: SettingsDlgInit(HWND)

PURPOSE: Initializes Settings Dialog

PARAMETERS:
    hDlg - Dialog window handle

RETURN: always TRUE

COMMENTS: This function originally found in the Win32 COMM sample
	  Written by BryanW.  Modified for Win32 MTTTY Sample.

HISTORY:   Date:      Author:     Comment:
	   10/27/95   AllenD      Modified for MTTTY

-----------------------------------------------------------------------------*/
BOOL SettingsDlgInit( HWND hDlg )
{
    char szBuffer[ MAXLEN_TEMPSTR ], szTemp[ MAXLEN_TEMPSTR ] ;
    WORD wCount, wMaxCOM, wPosition ;

    wMaxCOM = MAXPORTS ;
    strcpy(szTemp, "COM");

    //
    // fill port combo box and make initial selection
    //
    for (wCount = 0; wCount < wMaxCOM; wCount++) {
	wsprintf( szBuffer, "%s%d", (LPSTR) szTemp, wCount + 1 ) ;
	SendDlgItemMessage( hDlg, IDC_PORTCOMBO, CB_ADDSTRING, 0,
			    (LPARAM) (LPSTR) szBuffer ) ;
    }

    SendDlgItemMessage( hDlg, IDC_PORTCOMBO, CB_SETCURSEL,
		       (WPARAM) (PORT( TTYInfo ) - 1), 0L ) ;
   
    GetDlgItemText(hDlg, IDC_PORTCOMBO, gszPort, sizeof(gszPort));

    //
    // fill baud combo box and make initial selection
    //
    FillComboBox( GetDlgItem( hDlg, IDC_BAUDCOMBO ),
		  szBaud, BaudTable,
		  sizeof( BaudTable ) / sizeof( BaudTable[ 0 ] ),
		  BAUDRATE( TTYInfo ) ) ;

    //
    // fill data bits combo box and make initial selection
    //
    for (wCount = 5; wCount < 9; wCount++) {
	wsprintf( szBuffer, "%d", wCount ) ;
	wPosition = LOWORD( SendDlgItemMessage( hDlg, IDC_DATABITSCOMBO,
						CB_ADDSTRING, 0,
						(LPARAM) (LPSTR) szBuffer ) ) ;

	//
	// if wCount is current selection, tell the combo box
	//
	if (wCount == BYTESIZE( TTYInfo ))
	    SendDlgItemMessage( hDlg, IDC_DATABITSCOMBO, CB_SETCURSEL,
				(WPARAM) wPosition, 0L ) ;
    }

    //
    // fill parity combo box and make initial selection
    //
    FillComboBox(   GetDlgItem( hDlg, IDC_PARITYCOMBO ),
		    szParity, ParityTable,
		    sizeof( ParityTable ) / sizeof( ParityTable[ 0 ] ),
		    PARITY( TTYInfo ) ) ;

    //
    // fill stop bits combo box and make initial selection
    //
    FillComboBox(   GetDlgItem( hDlg, IDC_STOPBITSCOMBO ),
		    szStopBits, StopBitsTable,
		    sizeof( StopBitsTable ) / sizeof ( StopBitsTable[ 0 ] ),
		    STOPBITS( TTYInfo ) ) ;
    //
    // set check marks based on TTY data
    //
    CheckDlgButton( hDlg, IDC_LOCALECHOCHK, LOCALECHO( TTYInfo ) ) ;
    CheckDlgButton( hDlg, IDC_DISPLAYERRORSCHK, DISPLAYERRORS( TTYInfo ) );
    CheckDlgButton( hDlg, IDC_LFBTN, NEWLINE( TTYInfo ) );
    CheckDlgButton( hDlg, IDC_AUTOWRAPCHK, AUTOWRAP( TTYInfo ) );

    CheckDlgButton( hDlg, IDC_NOWRITINGCHK, NOWRITING( TTYInfo ) );
    CheckDlgButton( hDlg, IDC_NOREADINGCHK, NOREADING( TTYInfo ) );
    CheckDlgButton( hDlg, IDC_NOSTATUSCHK,  NOSTATUS( TTYInfo ) );
    CheckDlgButton( hDlg, IDC_NOEVENTSCHK,  NOEVENTS( TTYInfo ) );

    return ( TRUE ) ;

} // end of SettingsDlgInit()


/*-----------------------------------------------------------------------------

FUNCTION: GetdwTTYItem(HWND, int, char **, DWORD *, int)

PURPOSE: Returns a DWORD item from a dialog control

PARAMETERS:
    hDlg      - Dialog window handle
    idControl - id of control to get data from
    szString  - table of strings that the control displays
    pTable    - table of data associated with strings
    iNumItems - size of table

RETURN:  
    DWORD item corresponding to control selection
    0 if item not found correctly

HISTORY:   Date:      Author:     Comment:
	   10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
DWORD GetdwTTYItem(HWND hDlg, int idControl, char ** szString, DWORD * pTable, int iNumItems)
{
    int i;
    char szItem[MAXLEN_TEMPSTR];

    //
    // Get current selection (a string)
    //
    GetDlgItemText(hDlg, idControl, szItem, sizeof(szItem));
    
    /*
	Compare current selection with table to find index of item.
	If index is found, then return the DWORD item from table.
    */ 
    for (i = 0; i < iNumItems; i++) {
	if (strcmp(szString[i], szItem) == 0)
	    return pTable[i];
    }

    return 0;
}

/*-----------------------------------------------------------------------------

FUNCTION: GetbTTYItem(HWND, int, char **, DWORD *, int)

PURPOSE: Returns a BYTE item from a dialog control

PARAMETERS:
    hDlg      - Dialog window handle
    idControl - id of control to get data from
    szString  - table of strings that the control displays
    pTable    - table of data associated with strings
    iNumItems - size of table

RETURN:
    BYTE item from corresponding to control selection 
    0 if item data not found

HISTORY:   Date:      Author:     Comment:
	   10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
BYTE GetbTTYItem(HWND hDlg, int idControl, char ** szString, DWORD * pTable, int iNumItems)
{
    int i;
    char szItem[MAXLEN_TEMPSTR];

    //
    // Get current selection (a string)
    //
    GetDlgItemText(hDlg, idControl, szItem, sizeof(szItem));
    
    /*
	Compare current selection with table to find index of item.
	If index is found, then return the BYTE item from table.
    */ 
    for (i = 0; i < iNumItems; i++) {
	if (strcmp(szString[i], szItem) == 0)
	    return (BYTE) pTable[i];
    }
    
    return 0;
}


/*-----------------------------------------------------------------------------

FUNCTION: ToolbarProc(HWND, UINT, WPARAM, LPARAM)

PURPOSE: Dialog Procedure for Settings Dialog

PARAMETERS:
    hWndDlg - Dialog window handle
    uMsg    - Window message
    wParam  - message parameter (depends on message)
    lParam  - message parameter (depends on message)

RETURN:
    TRUE if message is handled
    FALSE if message is not handled
    Exception is WM_INITDIALOG: returns FALSE since focus is not set

HISTORY:   Date:      Author:     Comment:
	   10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
BOOL CALLBACK ToolbarProc(HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    BOOL fRet = FALSE;

    switch(uMsg)
    {
	case WM_INITDIALOG:     // setup dialog with defaults
	    SettingsDlgInit(hWndDlg);
	    break;

	case WM_COMMAND: 
	    {
		switch(LOWORD(wParam))
		{
		    case IDC_FONTBTN:       // font button pressed
			{
			    CHOOSEFONT cf = {0};
			    LOGFONT lf;

			    lf = LFTTYFONT(TTYInfo);
			    cf.lStructSize = sizeof(CHOOSEFONT);
			    cf.hwndOwner = hWndDlg;
			    cf.lpLogFont = &lf;
			    cf.rgbColors = FGCOLOR(TTYInfo);
			    cf.Flags = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_FIXEDPITCHONLY | \
				       CF_EFFECTS;

			    if (!ChooseFont(&cf))
				break;

			    InitNewFont(lf, cf.rgbColors);

			    //
			    // fix scroll bar sizes since we may have more or less pixels per
			    // character now
			    //
			    SizeTTY(ghWndTTY, (WORD)XSIZE(TTYInfo), (WORD)YSIZE(TTYInfo));
			    
			    //
			    // repaint screen contents
			    //
			    InvalidateRect(ghWndTTY, NULL, TRUE);
			    
			    //
			    // kill old cursor
			    //
			    KillTTYFocus(ghWndTTY);
			    
			    //
			    // create new cursor
			    //
			    SetTTYFocus(ghWndTTY);
			}
			fRet = FALSE;
			break;

		    case IDC_COMMEVENTSBTN:     // comm events button pressed
			DialogBox(ghInst, MAKEINTRESOURCE(IDD_COMMEVENTSDLG), ghwndMain, CommEventsProc);
			fRet = FALSE;
			break;

		    case IDC_FLOWCONTROLBTN:
			DialogBox(ghInst, MAKEINTRESOURCE(IDD_FLOWCONTROLDLG), ghwndMain, FlowControlProc);
			fRet = FALSE;
			break;

		    case IDC_TIMEOUTSBTN:
			DialogBox(ghInst, MAKEINTRESOURCE(IDD_TIMEOUTSDLG), ghwndMain, TimeoutsProc);
			fRet = FALSE;
			break;

		    default:                    // some other control has been modified
			if (CONNECTED(TTYInfo))
			    UpdateTTYInfo();
			break;
		}
	    }
	    break;

	default:
	    break;
    }    

    return fRet;
}

/*-----------------------------------------------------------------------------

FUNCTION: InitHexControl(HWND, WORD, WORD, char)

PURPOSE: Places byte value into two edit boxes of the dialog

PARAMETERS:
    hdlg         - Dialog Handle
    wIdNumberBox - Edit control ID ; displays hex
    wIdCharBox   - Edit control ID ; displays char
    chData       - data to display

COMMENTS: Some dialogs may have an edit control designed to accept
	  hexidecimal input from the user.  This function initializes
	  such edit controls.  First, the byte (char) is placed into a
	  zero terminated string.  This is set as the item text of one
	  of the controls.  Next, the byte is converted to a hexidecimal
	  string.  This is set as the item text of the other control.

HISTORY:   Date:      Author:     Comment:
	   10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void InitHexControl(HWND hdlg, WORD wIdNumberBox, WORD wIdCharBox, char chData)
{
    char szFlagText[3] = {0};
    char szFlagChar[2] = {0};
    
    //
    // put character into char edit display control
    //
    szFlagChar[0] = chData;
    SetDlgItemText(hdlg, wIdCharBox, szFlagChar);
    
    //
    // put flag character into hex numeric edit control
    //
    wsprintf(szFlagText, "%02x", 0x000000FF & chData);
    SetDlgItemText(hdlg, wIdNumberBox, szFlagText);

    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: GetHexControl(HWND, WORD, WORD)

PURPOSE: Get hex data from control and convert to character

PARAMETERS:
    hdlg         - Dialog Handle
    wIdNumberBox - Edit control ID ; contains hex string
    wIdCharBox   - Edit control ID ; displays the char

RETURN:
    0 if can't get hex string from edit control
    byte value of hex string otherwise

COMMENTS: Function does the following:
	  1) Gets first two characters from edit control
	  2) Converts hex string to numeric value
	  3) Displays ascii char of numeric value
	  4) Returns numeric value

HISTORY:   Date:      Author:     Comment:
	   10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
char GetHexControl(HWND hdlg, WORD wIdNumberBox, WORD wIdCharBox)
{
    UINT uFlagValue;
    char chFlagEntered[3] = {0};
    char chFlag[2] = {0};
    
    //
    // get numeric value from control
    //
    if (0 == GetDlgItemText(hdlg, wIdNumberBox, chFlagEntered, 3))
	return 0;

    sscanf(chFlagEntered, "%x", &uFlagValue);

    chFlag[0] = (char) uFlagValue;
    SetDlgItemText(hdlg, wIdCharBox, chFlag); // display character

    return chFlag[0];
}
    
/*-----------------------------------------------------------------------------

FUNCTION: InitCommEventsDlg(HWND, DWORD)

PURPOSE: Initializes Comm Event Dialog Control

PARAMETERS:
    hdlg         - Dialog window handle
    dwEventFlags - event flag to set controls to

COMMENTS: Since controls are checked based on the dwEventFlags parameter, 
	  it is easy to init control based on current settings, 
	  or default settings.

HISTORY:   Date:      Author:     Comment:
	   10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void InitCommEventsDlg(HWND hdlg, DWORD dwEventFlags)
{
    int i,j;

    for (i = IDC_EVBREAKBTN, j = 0; i <= IDC_EVTXEMPTYBTN; i++, j++)
	CheckDlgButton( hdlg, i, dwEventFlags & EventFlagsTable[j]) ;

    InitHexControl(hdlg, IDC_FLAGEDIT, IDC_FLAGCHAR, FLAGCHAR(TTYInfo));

    EnableWindow(GetDlgItem(hdlg, IDC_FLAGEDIT),  dwEventFlags & EV_RXFLAG);
    EnableWindow(GetDlgItem(hdlg, IDC_FLAGCHAR),  dwEventFlags & EV_RXFLAG);

    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: SaveCommEventsDlg(HWND)

PURPOSE: Saves new Comm Events Flag

PARAMETERS:
    hdlg - Dialog window handle

COMMENTS: Builds a new flag based on current dialog control.
	  If the new flag differs from old, then new is updated.

HISTORY:   Date:      Author:     Comment:
	   10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void SaveCommEventsDlg(HWND hdlg)
{
    int i,j;
    DWORD dwNew = {0};
    char chNewFlag = '\0';
    BOOL fChangingRXFLAG;

    //
    // create a flag out of dialog selections
    //
    for (i = IDC_EVBREAKBTN, j = 0; i <= IDC_EVTXEMPTYBTN; i++, j++) {
	if (IsDlgButtonChecked(hdlg, i))
	    dwNew |= EventFlagsTable[j];
    }

    //
    // get current flag character from dialog
    //
    chNewFlag = GetHexControl(hdlg, IDC_FLAGEDIT, IDC_FLAGCHAR);
    fChangingRXFLAG = (EVENTFLAGS(TTYInfo) & EV_RXFLAG) != (dwNew & EV_RXFLAG);
    if (chNewFlag != FLAGCHAR(TTYInfo) || fChangingRXFLAG) {
	FLAGCHAR(TTYInfo) = chNewFlag;
	UpdateTTYInfo();
    }

    //
    // if new flags have been selected, or
    //
    if (dwNew != EVENTFLAGS(TTYInfo))
	EVENTFLAGS(TTYInfo) = dwNew;

    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: CommEventsProc(HWND, UINT, WPARAM, LPARAM)

PURPOSE: Dialog Procedure for Comm Events Dialog

PARAMETERS:
    hdlg     - Dialog window handle
    uMessage - window message
    wparam   - message parameter (depends on message)
    lparam   - message parameter (depends on message)

RETURN:
    TRUE if message is handled
    FALSE if message is not handled
    Exception is WM_INITDIALOG: returns FALSE since focus is not set

HISTORY:   Date:      Author:     Comment:
	   10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
BOOL CALLBACK CommEventsProc(HWND hdlg, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    switch(uMessage)
    {
	case WM_INITDIALOG:     // init controls
	    InitCommEventsDlg(hdlg, EVENTFLAGS(TTYInfo));
	    break;

	case WM_COMMAND: 
	    switch(LOWORD(wparam))
	    {
		case IDOK:
		    SaveCommEventsDlg(hdlg);
		    
		    //
		    // FALL THROUGH
		    //

		case IDCANCEL:
		    EndDialog(hdlg, LOWORD(wparam));
		    return TRUE;

		case IDC_DEFAULTSBTN:
		    InitCommEventsDlg(hdlg, EVENTFLAGS_DEFAULT);
		    return TRUE;

		case IDC_EVRXFLAGBTN:
		    EnableWindow(GetDlgItem(hdlg, IDC_FLAGEDIT),  IsDlgButtonChecked(hdlg, IDC_EVRXFLAGBTN));
		    EnableWindow(GetDlgItem(hdlg, IDC_FLAGCHAR),  IsDlgButtonChecked(hdlg, IDC_EVRXFLAGBTN));
		    return TRUE;

		case IDC_FLAGEDIT:
		    GetHexControl(hdlg, IDC_FLAGEDIT, IDC_FLAGCHAR);
		    return TRUE;
	    }
	    break;
    }

    return FALSE;
}

/*-----------------------------------------------------------------------------

FUNCTION: SaveFlowControlDlg(HWND)

PURPOSE: Sets TTY flow control settings based on dlg controls

PARAMETERS:
    hdlg - Dialog window handle

HISTORY:   Date:      Author:     Comment:
	   10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void SaveFlowControlDlg(HWND hdlg)
{
    BOOL    fNewCTSOut, fNewDSROut, fNewDSRIn, fNewXOut, fNewXIn, fNewTXafterXoffSent;
    DWORD   dwNewDTRControl, dwNewRTSControl;
    WORD    wNewXONLimit, wNewXOFFLimit;
    char    chNewXON, chNewXOFF;
    BOOL    fSuccess;

    BOOL fUpdateDCB = FALSE;

    //
    // update DTR and RTS control if needed
    //
    dwNewDTRControl = GetdwTTYItem( hdlg, IDC_DTRCONTROLCOMBO, 
				    szDTRControlStrings, DTRControlTable, 
				    sizeof(DTRControlTable)/sizeof(DTRControlTable[0]));

    dwNewRTSControl = GetdwTTYItem( hdlg, IDC_RTSCONTROLCOMBO, 
				    szRTSControlStrings, RTSControlTable, 
				    sizeof(RTSControlTable)/sizeof(RTSControlTable[0]));
    if (dwNewRTSControl != RTSCONTROL(TTYInfo) ||
	    dwNewDTRControl != DTRCONTROL(TTYInfo)) {
	RTSCONTROL(TTYInfo) = dwNewRTSControl;
	DTRCONTROL(TTYInfo) = dwNewDTRControl;
	fUpdateDCB = TRUE;
    }

    //
    // update XON/XOFF limits if needed
    //
    wNewXONLimit = GetDlgItemInt(hdlg, IDC_XONLIMITEDIT, &fSuccess, FALSE);
    wNewXOFFLimit = GetDlgItemInt(hdlg, IDC_XOFFLIMITEDIT, &fSuccess, FALSE);
    if (wNewXOFFLimit != XOFFLIMIT(TTYInfo) ||
	    wNewXONLimit != XONLIMIT(TTYInfo)) {
	XOFFLIMIT(TTYInfo) = wNewXOFFLimit;
	XONLIMIT(TTYInfo)  = wNewXONLimit;
	fUpdateDCB = TRUE;
    }

    //
    // update XON/XOFF chars if needed
    //
    chNewXON = GetHexControl(hdlg, IDC_XONCHAREDIT, IDC_XONCHARDISP);
    chNewXOFF = GetHexControl(hdlg, IDC_XOFFCHAREDIT, IDC_XOFFCHARDISP);
    if (chNewXOFF != XOFFCHAR(TTYInfo) ||
	    chNewXON != XONCHAR(TTYInfo)) {
	XOFFCHAR(TTYInfo) = chNewXOFF;
	XONCHAR(TTYInfo)  = chNewXON;
	fUpdateDCB = TRUE;
    }

    //
    // update booleans from check boxes
    //
    fNewTXafterXoffSent = IsDlgButtonChecked(hdlg, IDC_TXAFTERXOFFSENTCHK);
    fNewCTSOut = IsDlgButtonChecked(hdlg, IDC_CTSOUTCHK);
    fNewDSROut = IsDlgButtonChecked(hdlg, IDC_DSROUTCHK);
    fNewDSRIn  = IsDlgButtonChecked(hdlg, IDC_DSRINCHK);
    fNewXOut   = IsDlgButtonChecked(hdlg, IDC_XONXOFFOUTCHK);
    fNewXIn    = IsDlgButtonChecked(hdlg, IDC_XONXOFFINCHK);

    if (fNewTXafterXoffSent != TXAFTERXOFFSENT(TTYInfo) || 
	    fNewCTSOut != CTSOUTFLOW(TTYInfo) ||
	    fNewDSROut != DSROUTFLOW(TTYInfo) ||
	    fNewDSRIn  != DSRINFLOW(TTYInfo)  ||
	    fNewXOut   != XONXOFFOUTFLOW(TTYInfo) ||
	    fNewXIn    != XONXOFFINFLOW(TTYInfo) ) {
	CTSOUTFLOW(TTYInfo) = fNewCTSOut;
	DSROUTFLOW(TTYInfo) = fNewDSROut;
	DSRINFLOW(TTYInfo)  = fNewDSRIn;
	XONXOFFOUTFLOW(TTYInfo) = fNewXOut;
	XONXOFFINFLOW(TTYInfo)  = fNewXIn;
	TXAFTERXOFFSENT(TTYInfo) = fNewTXafterXoffSent;
	fUpdateDCB = TRUE;
    }    

    //
    // update current settings if they have actually changed
    //
    if (fUpdateDCB)
	UpdateTTYInfo();

    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: InitFlowControlDlg(HWND)

PURPOSE: Sets controls based on current tty flow control settings

PARAMETERS:
    hdlg - Dialog window handle

HISTORY:   Date:      Author:     Comment:
	   10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void InitFlowControlDlg(HWND hdlg)
{
    //
    // fill and init DTR control combo
    //
    FillComboBox( GetDlgItem( hdlg, IDC_DTRCONTROLCOMBO ),
		 szDTRControlStrings, DTRControlTable,
		 sizeof( DTRControlTable) / sizeof( DTRControlTable[0] ),
		 DTRCONTROL( TTYInfo ) );

    //
    // fill and init RTS control combo
    //
    FillComboBox( GetDlgItem( hdlg, IDC_RTSCONTROLCOMBO ),
		 szRTSControlStrings, RTSControlTable,
		 sizeof( RTSControlTable) / sizeof( RTSControlTable[0] ),
		 RTSCONTROL( TTYInfo ) );

    //
    // XON/XOFF characters
    //
    InitHexControl(hdlg, IDC_XONCHAREDIT, IDC_XONCHARDISP, XONCHAR(TTYInfo));   
    InitHexControl(hdlg, IDC_XOFFCHAREDIT, IDC_XOFFCHARDISP, XOFFCHAR(TTYInfo));    

    //
    // XON/XOFF limits
    //
    SetDlgItemInt(hdlg, IDC_XONLIMITEDIT, XONLIMIT(TTYInfo), FALSE);
    SetDlgItemInt(hdlg, IDC_XOFFLIMITEDIT, XOFFLIMIT(TTYInfo), FALSE);

    //
    // check boxes
    //
    CheckDlgButton(hdlg, IDC_CTSOUTCHK, CTSOUTFLOW(TTYInfo));
    CheckDlgButton(hdlg, IDC_DSROUTCHK, DSROUTFLOW(TTYInfo));
    CheckDlgButton(hdlg, IDC_DSRINCHK, DSRINFLOW(TTYInfo));
    CheckDlgButton(hdlg, IDC_XONXOFFOUTCHK, XONXOFFOUTFLOW(TTYInfo));
    CheckDlgButton(hdlg, IDC_XONXOFFINCHK, XONXOFFINFLOW(TTYInfo));
    CheckDlgButton(hdlg, IDC_TXAFTERXOFFSENTCHK, TXAFTERXOFFSENT(TTYInfo));

    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: FlowDefault(HWND, WORD)

PURPOSE: Sets controls based on hardware or software flow control

PARAMETERS:
    hdlg - Dialog window handle
    wId  - ID of button used to set the default:
	IDC_DTRDSRBTN     - DTR/DSR hardware flow-control
	IDC_RTSCTSBTN     - RTS/CTS hardware flow-control
	IDC_XOFFXONBTNBTN - XOFF/XON software flow control
	IDC_NONEBTN       - no flow control

HISTORY:   Date:      Author:     Comment:
	   10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void FlowDefault(HWND hdlg, WORD wId)
{
    //
    // set dtr control to handshake if using DTR/DSR flow-control 
    //
    SetComboBox( GetDlgItem( hdlg, IDC_DTRCONTROLCOMBO ),
		  sizeof( DTRControlTable) / sizeof( DTRControlTable[0] ),
		  wId == IDC_DTRDSRBTN ? DTR_CONTROL_HANDSHAKE : DTR_CONTROL_ENABLE);

    //
    // set rts control to handshake if using RTS/CTS flow-control 
    //
    SetComboBox( GetDlgItem( hdlg, IDC_RTSCONTROLCOMBO ),
		  sizeof( RTSControlTable) / sizeof( RTSControlTable[0] ),
		  wId == IDC_RTSCTSBTN ? RTS_CONTROL_HANDSHAKE : RTS_CONTROL_ENABLE);

    //
    // set check boxes according to wId
    //
    switch(wId)
    {
	case IDC_RTSCTSBTN:
	case IDC_DTRDSRBTN:
	    CheckDlgButton(hdlg, IDC_CTSOUTCHK, wId == IDC_RTSCTSBTN);
	    CheckDlgButton(hdlg, IDC_DSROUTCHK, wId == IDC_DTRDSRBTN);
	    CheckDlgButton(hdlg, IDC_XONXOFFOUTCHK, FALSE);
	    CheckDlgButton(hdlg, IDC_XONXOFFINCHK, FALSE);
	    break;

	case IDC_XOFFXONBTN:
	case IDC_NONEBTN:
	    CheckDlgButton(hdlg, IDC_CTSOUTCHK, FALSE);
	    CheckDlgButton(hdlg, IDC_DSROUTCHK, FALSE);
	    CheckDlgButton(hdlg, IDC_XONXOFFOUTCHK, wId == IDC_XOFFXONBTN);
	    CheckDlgButton(hdlg, IDC_XONXOFFINCHK, wId == IDC_XOFFXONBTN);
	    break;
    }

    //
    // settings that are disabled when any 'default' flow-control is used
    //
    CheckDlgButton(hdlg, IDC_DSRINCHK, FALSE);
    CheckDlgButton(hdlg, IDC_TXAFTERXOFFSENTCHK, FALSE);
     

    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: FlowControlProc(HWND, UINT, WPARAM, LPARAM)

PURPOSE: Dialog Procedure for Flow Control Settings Dialog

PARAMETERS:
    hdlg     - Dialog window handle
    uMessage - window message
    wparam   - message parameter (depends on message)
    lparam   - message parameter (depends on message)

RETURN:
    TRUE if message is handled
    FALSE if message is not handled
    Exception is WM_INITDIALOG: returns FALSE since focus is not set

HISTORY:   Date:      Author:     Comment:
	   10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
BOOL CALLBACK FlowControlProc(HWND hdlg, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    switch(uMessage)
    {
	case WM_INITDIALOG:     // init controls
	    InitFlowControlDlg(hdlg);
	    break;

	case WM_COMMAND: 
	    switch(LOWORD(wparam))
	    {
		case IDOK:
			SaveFlowControlDlg(hdlg);
			//
			// FALL THROUGH
			//
		
		case IDCANCEL:          
			EndDialog(hdlg, LOWORD(wparam));          
			return TRUE;

		case IDC_RTSCTSBTN:
		case IDC_DTRDSRBTN:
		case IDC_XOFFXONBTN:
		case IDC_NONEBTN:
			FlowDefault(hdlg, LOWORD(wparam));
			return TRUE;

		case IDC_XONCHAREDIT:
			GetHexControl(hdlg, IDC_XONCHAREDIT, IDC_XONCHARDISP);
			return TRUE;

		case IDC_XOFFCHAREDIT:
			GetHexControl(hdlg, IDC_XOFFCHAREDIT, IDC_XOFFCHARDISP);
			return TRUE;
	    }
	    break;
    }

    return FALSE;
}

/*-----------------------------------------------------------------------------

FUNCTION: InitTimeoutsDlg(HWND, COMMTIMEOUTS)

PURPOSE: Initializes timeouts dialog controls based on parameter

PARAMETERS:
    hdlg - Dialog window handle
    ct   - COMMTIMEOUTS used to set the dialog controls

HISTORY:   Date:      Author:     Comment:
	   10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void InitTimeoutsDlg(HWND hdlg, COMMTIMEOUTS ct)
{
    SetDlgItemInt(hdlg, IDC_READINTERVALEDIT, ct.ReadIntervalTimeout, FALSE);
    SetDlgItemInt(hdlg, IDC_READMULTIPLIEREDIT, ct.ReadTotalTimeoutMultiplier, FALSE);
    SetDlgItemInt(hdlg, IDC_READCONSTANTEDIT, ct.ReadTotalTimeoutConstant, FALSE);
    SetDlgItemInt(hdlg, IDC_WRITEMULTIPLIEREDIT, ct.WriteTotalTimeoutMultiplier, FALSE);
    SetDlgItemInt(hdlg, IDC_WRITECONSTANTEDIT, ct.WriteTotalTimeoutConstant, FALSE);
    CheckDlgButton(hdlg, IDC_DISPLAYTIMEOUTS, SHOWTIMEOUTS(TTYInfo));
    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: SaveTimeoutsDlg(HWND)

PURPOSE: Saves values from controls into tty timeout settings

PARAMETERS:
    hdlg - Dialog window handle

HISTORY:   Date:      Author:     Comment:
	   10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void SaveTimeoutsDlg(HWND hdlg)
{
    COMMTIMEOUTS ctNew;

    //
    // get new timeouts from dialog controls
    //
    ctNew.ReadIntervalTimeout         = GetDlgItemInt(hdlg, IDC_READINTERVALEDIT,    NULL, FALSE);
    ctNew.ReadTotalTimeoutMultiplier  = GetDlgItemInt(hdlg, IDC_READMULTIPLIEREDIT,  NULL, FALSE);
    ctNew.ReadTotalTimeoutConstant    = GetDlgItemInt(hdlg, IDC_READCONSTANTEDIT,    NULL, FALSE);
    ctNew.WriteTotalTimeoutMultiplier = GetDlgItemInt(hdlg, IDC_WRITEMULTIPLIEREDIT, NULL, FALSE);
    ctNew.WriteTotalTimeoutConstant   = GetDlgItemInt(hdlg, IDC_WRITECONSTANTEDIT,   NULL, FALSE);

    SHOWTIMEOUTS(TTYInfo) = IsDlgButtonChecked(hdlg, IDC_DISPLAYTIMEOUTS);

    //
    // set new timeouts if they are different
    //
    if (memcmp(&ctNew, &(TIMEOUTSNEW(TTYInfo)), sizeof(COMMTIMEOUTS))) {
	//
	// if connected, set new time outs and purge pending operations
	//
	if (CONNECTED(TTYInfo)) {
	    if (!SetCommTimeouts(COMDEV(TTYInfo), &ctNew)) {
		ErrorReporter("SetCommTimeouts");
		return;
	    }
	    
	    if (!PurgeComm(COMDEV(TTYInfo), PURGE_TXABORT | PURGE_RXABORT))
		ErrorReporter("PurgeComm");
	}

	//
	// save timeouts in the tty info structure
	//
	TIMEOUTSNEW(TTYInfo) = ctNew;
    }
    
    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: TimeoutsProc(HWND, UINT, WPARAM, LPARAM)

PURPOSE: Dialog Procedure for comm timeouts

PARAMETERS:
    hdlg     - Dialog window handle
    uMessage - window message
    wparam   - message parameter (depends on message)
    lparam   - message parameter (depends on message)

RETURN:
    TRUE if message is handled
    FALSE if message is not handled
    Exception is WM_INITDIALOG: returns FALSE since focus is not set

HISTORY:   Date:      Author:     Comment:
	   10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
BOOL CALLBACK TimeoutsProc(HWND hdlg, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    switch(uMessage)
    {
	case WM_INITDIALOG:     // init controls
	    InitTimeoutsDlg(hdlg, TIMEOUTSNEW(TTYInfo));
	    break;

	case WM_COMMAND:
	    switch(LOWORD(wparam))
	    {
		case IDOK:
			SaveTimeoutsDlg(hdlg);
			
			//
			// FALL THROUGH
			// 
		
		case IDCANCEL:
			EndDialog(hdlg, LOWORD(wparam));          
			return TRUE;

		case IDC_DEFAULTSBTN:
			InitTimeoutsDlg(hdlg, gTimeoutsDefault);
			return TRUE;
	    }
	    break;
    }

    return FALSE;
}

BOOL CALLBACK GetADWORDProc(HWND hDlg, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
    int iRet = 0;

    if (uMessage == WM_COMMAND) {
	switch(LOWORD(wParam)) {
	    case IDOK:
		iRet = GetDlgItemInt(hDlg, IDC_DWORDEDIT, NULL, FALSE);
		//
		// FALL THROUGH
		// 
	
	    case IDCANCEL:
		EndDialog(hDlg, iRet);          
		return TRUE;
	}
    }

    return FALSE;
}

DWORD GetAFrequency()
{
    return ((DWORD) DialogBox(ghInst, MAKEINTRESOURCE(IDD_GETADWORD), ghwndMain, GetADWORDProc));
}
