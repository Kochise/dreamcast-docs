//-----------------------------------------------------------------------------
// Microsoft OLE DB Main Include File
// Copyright (C) 1995-1998 Microsoft Corporation
//
// @doc
//
// @module main include file
//
//-----------------------------------------------------------------------------

#ifdef RC_INVOKED
#define ID(id) id
#else
#define ID(id) MAKEINTRESOURCE(id)
#endif

/* Resource Identifiers */
#define BMP_NEWQUERY		ID(10)	// new window button bitmap
#define BMP_RUNQUERY		ID(20)	// exec query button bitmap
#define	APPICON				ID(30)	// application icon
#define QUERYWINDOWICON		ID(40)	// MDI Child window icon
#define QURYDEMOMENU		ID(50)	// Application menu
#define INITDIALOG			ID(60)	// connect modal dialog box
#define DISCONNECTDIALOG	ID(70)	// disconnect modal dialog box
#define ABOUTDIALOG			ID(80)	// about modal dialog box
#define MDICHILDDIALOG		ID(90)	// MDI Child modeless dialog box
#define APPACCELERATOR		ID(100)	// Accelerator table for the app

/* Menu Identifiers */
#define IDM_POPUPAPPSYS		10		// Placeholder, used by status bar
#define IDM_POPUPMDISYS		20		// Placeholder, used by status bar
#define IDM_POPUPLOGIN		100		// Placeholder, used by status bar
#define IDM_INITIALIZE		110
#define IDM_DISCONNECT		120	
#define IDM_EXIT			130
#define IDM_POPUPQUERY		140		// Placeholder, used by status bar
#define IDM_QUERY			150
#define IDM_NEW				160
#define IDM_POPUPSCHEMA		170     // Placeholder, used by status bar


#define IDM_POPUPWINDOW		210     // Placeholder, used by status bar
#define IDM_TILE			220
#define IDM_CASCADE			230
#define IDM_ICONS			240
#define IDM_CLOSEALL		250
#define IDM_POPUPHELP		260		// Placeholder, used by status bar
#define IDM_APPHELP			270
#define IDM_ABOUT			280
#define IDM_MDICHILD		290


#define	IDM_ASSERTIONS				300
#define IDM_CATALOGS				310
#define IDM_CHARACTER_SETS			320
#define IDM_CHECK_CONSTRAINTS		330
#define IDM_COLLATIONS				340
#define IDM_COLUMN_DOMAIN_USAGE		350
#define IDM_COLUMN_PRIVILEGES		360
#define IDM_COLUMNS					370
#define IDM_CONSTRAINT_COLUMN_USAGE 380
#define IDM_CONSTRAINT_TABLE_USAGE  390
#define IDM_FOREIGN_KEYS			400
#define IDM_INDEXES					410
#define IDM_KEY_COLUMN_USAGE		420
#define IDM_PRIMARY_KEYS			430
#define IDM_PROCEDURE_COLUMNS		440
#define IDM_PROCEDURE_PARAMETERS	450
#define IDM_PROCEDURES				460
#define IDM_PROVIDER_TYPES			470
#define IDM_REFERENTIAL_CONSTRAINTS	480
#define IDM_SCHEMATA				490
#define IDM_SQL_LANGUAGES			500
#define IDM_STATISTICS				510
#define IDM_TABLE_CONSTRAINTS		520
#define IDM_TABLE_PRIVILEGES		530
#define IDM_TABLES					540
#define IDM_TRANSLATIONS			550
#define IDM_USAGE_PRIVILEGES		560
#define IDM_VIEW_COLUMN_USAGE		570
#define IDM_VIEW_TABLE_USAGE		580
#define IDM_VIEWS					590  //ADDED

/* child window ids */
#define IDW_TOOLBAR			10
#define IDW_STATUSBAR		20
#define IDW_MDICLIENT		30

#define IDW_CRSRLIST		10		// toolbar comboboxes
#define IDW_COMMANDLIST		20

#define IDCOMBO_PROVIDER	10		// connect dialog box controls
#define IDCOMBO_NAME		20
#define IDTEXT_USERID		30
#define IDTEXT_PASSWORD		40
#define IDCOMBO_PROMPT		45
#define IDENUM              50

#define IDLIST_SESSION		10		// disconnect dialog box controls
#define IDLIST_COMMAND		20
#define IDCLOSE_ACTVTY		30
#define IDDISCONNECT		40
#define IDICON_WARN			50

#define IDTEXT_PRMPT		10		// MDI child's modeless dialog controls
#define IDTEXT_SQL			20
#define IDLIST_RSLT			30

/* MDI Child Window Offsets */
#define CBWNDEXTRA			4		// storage in MDI Child Window
#define GWLAPP_HDLG			0		// child dialog handle

/* Other Constants */
#define MAXCHILDWNDS    	10						//maximum child windows allowed
#define MAXBUFLEN			256						//display buffer size
#define MAX_COL				35						//maximum column in result set
#define MAX_ROW				100						//maximum number of rows
#define MAXDATALEN			25						//maximum data length per column
#define MAXCOLNAMELEN		20
#define MAXCOLNDATALENGTH   23
#define MAXDISPLAYSIZE		MAX_COL*(MAXDATALEN+1)
#define	MINWIDTH			415						//minimum width of app window
#define	MINHEIGHT			350						//minimum height of app window
#define LISTTABSTOP			100						//tabstop in the display listbox
#define LISTHORZSCROLL		(LISTTABSTOP*2)			//horizontal scroll for the listbox
#define LISTHORZEXT			0						//horizontal extent inthe list box
#define WINDOWMENUPLACE		2						//Window menu place for adding MDI child windows
#define IDT_STATUSTIMER		1						//timer id
#define TIMERDELAY			60000					//timer duration
#define BTTNX				345						//first toolbar button location
#define BTTNY				2						//button y position
#define	BTTNWIDTH			25                      //button width
#define BTTNHEIGHT			23                      //button height
#define BTTNMARGIN			5						//distance between toolbar buttons
#define TOOLBARMARGINY		5						//fixed margin w/o combobox height
#define STATUSBARMARGINY	8						//fixed margin w/o textbox height

/* String Constants */
#define POPUPLOGIN			"&Login"
#define MENUITEMCONNECT		"&Connect... \aCtrl+C"
#define MENUITEMDISCONNECT	"&Unitialize... \aCtrl+U"
#define	MENUITEMEXIT		"E&xit"
#define POPUPQUERY			"&Command"
#define MENUITEMQUERY		"&Execute Command Text \aCtrl+E"
#define MENUITEMNEW			"&New Command \aCtrl+N"
#define POPUPSCHEMA			"&Schema \aCtrl+S"
#define MENUITEMTYPES		"&PROVIDER_TYPES \aCtrl+P"
#define	MENUITEMTABLES		"T&ABLES \aCtrl+A"
#define MENUITEMCOLUMNS		"&COLUMNS \aCtrl+C"
#define POPUPWINDOW			"&Window"
#define MENUITEMTILE		"&Tile"
#define	MENUITEMCASCADE		"&Cascade"
#define MENUITEMICONS		"Arrange &Icons"
#define	MENUITEMCLOSEALL	"Close &All"
#define POPUPHELP			"&Help"
#define MENUITEMAPPHELP		"&Help on Qurydemo \aF1"
#define	MENUITEMABOUT		"&About Qurydemo..."

#define OLEDBFRAMECLASS		"QDEMO32MAIN"

#define OLEDBTOOLCLASS		"QDEMOTool"
#define OLEDBSTATUSCLASS	"QDEMOStatus"
#define OLEDBMDICLASS		"QDEMOMDI"
#define COMBOBOXCLASS		"COMBOBOX"
#define MDICLIENTCLASS		"MDICLIENT"
#define UNTITLED			"Untitled"
#define APPTITLE			"Microsoft OLE DB Sample Query Program"
#define	EXECERROR			"Execution Error"
#define INITERROR			"Failed to initialize Session interface"
#define CLASSERROR			"Failed to register application class"
#define CREATEMAINERR		"Failed to create application main window"
#define CREATECHILDERR		"Failed to create a new Command"
#define ALPHABETS			"abcdefghijklmnopqrstuvwxyz"
#define TIMETEXT			"MM:MM MM"
#define DATETEXT			"MMM-MM"
#define TIMEFORMAT			" %I:%M %p"
#define DATEFORMAT			" %b-%d"
#define NOPROVIDERERR		"Please provide a Data Source"
#define MOREINFO			"Incomplete Information"

#define STATUSPOPUPAPPSYS   " Control menu for the application "
#define STATUSPOPUPMDISYS	" Control menu for the window "
#define STATUSRESTORE       " Restore window to normal "
#define STATUSMOVE          " Move window "
#define STATUSSIZE          " Size window "
#define STATUSMINIMIZE      " Minimize window "
#define STATUSMAXIMIZE      " Maximize window "
#define STATUSCLOSE         " Close window "
#define STATUSNEXTWINDOW    " Switch to next window "
#define STATUSPREVWINDOW    " Switch to previous window "
#define STATUSTASKLIST      " Bring up task list "
#define STATUSPOPUPLOGIN	" Login and logout commands "
#define STATUSCONNECT		" Connect with default parameters... "
#define STATUSDISCONNECT	" Release open sessions... "
#define STATUSEXIT			" Exit application "
#define STATUSPOPUPQUERY	" Commands "
#define STATUSQUERY			" Execute Command text... "
#define STATUSNEW			" New Command on current Session... "
#define STATUSPOPUPSCHEMA	" IDBSchema Commands "

#define	STATUSASSERTIONS			  " DBSCHEMA_ASSERTIONS Rowset "
#define STATUSCATALOGS				  " DBSCHEMA_CATALOGS Rowset "
#define STATUSCHARACTER_SETS		  " DBSCHEMA_CHARACTER_SETS Rowset "
#define STATUSCHECK_CONSTRAINTS		  " DBSCHEMA_CHECK_CONSTRAINTS Rowset "
#define STATUSCOLLATIONS			  " DBSCHEMA_COLLATIONS Rowset "
#define STATUSCOLUMN_DOMAIN_USAGE	  " DBSCHEMA_COLUMN_DOMAIN_USAGE Rowset "
#define STATUSCOLUMN_PRIVILEGES		  " DBSCHEMA_COLUMN_PRIVILEGES Rowset "
#define STATUSCOLUMNS				  " DBSCHEMA_COLUMNS Rowset "
#define STATUSCONSTRAINT_COLUMN_USAGE " DBSCHEMA_CONSTRAINT_COLUMN_USAGE Rowset "
#define STATUSCONSTRAINT_TABLE_USAGE  " DBSCHEMA_CONSTRAINT_TABLE_USAGE Rowset "
#define STATUSFOREIGN_KEYS			  " DBSCHEMA_FOREIGN_KEYS Rowset "
#define STATUSINDEXES				  " DBSCHEMA_INDEXES Rowset "
#define STATUSKEY_COLUMN_USAGE		  " DBSCHEMA_KEY_COLUMN_USAGE Rowset "
#define STATUSPRIMARY_KEYS			  " DBSCHEMA_PRIMARY_KEYS Rowset "
#define STATUSPROCEDURE_COLUMNS		  " DBSCHEMA_PROCEDURE_COLUMNS Rowset "
#define STATUSPROCEDURE_PARAMETERS	  " DBSCHEMA_PROCEDURE_PARAMETERS Rowset "
#define STATUSPROCEDURES			  " DBSCHEMA_PROCEDURES Rowset "
#define STATUSPROVIDER_TYPES		  " DBSCHEMA_PROVIDER_TYPES Rowset "
#define STATUSREFERENTIAL_CONSTRAINTS " DBSCHEMA_REFERENTIAL_CONSTRAINTS Rowset "	
#define STATUSSCHEMATA				  " DBSCHEMA_SCHEMATA Rowset "
#define STATUSSQL_LANGUAGES			  " DBSCHEMA_SQL_LANGUAGES Rowset "
#define STATUSSTATISTICS			  " DBSCHEMA_STATISTICS	Rowset "
#define STATUSTABLE_CONSTRAINTS		  " DBSCHEMA_TABLE_CONSTRAINTS Rowset "
#define STATUSTABLE_PRIVILEGES		  " DBSCHEMA_TABLE_PRIVILEGES Rowset "	
#define STATUSTABLES				  " DBSCHEMA_TABLES Rowset "
#define STATUSTRANSLATIONS		      " DBSCHEMA_TRANSLATIONS Rowset "	
#define STATUSUSAGE_PRIVILEGES		  " DBSCHEMA_USAGE_PRIVILEGES Rowset "	
#define STATUSVIEW_COLUMN_USAGE		  " DBSCHEMA_VIEW_COLUMN_USAGE Rowset "	
#define STATUSVIEW_TABLE_USAGE		  " DBSCHEMA_VIEW_TABLE_USAGE Rowset "		
#define STATUSVIEWS					  " DBSCHEMA_VIEWS Rowset "	//ADDED

#define STATUSPOPUPWINDOW	" Window management commands "
#define STATUSTILE			" Tile all normal child windows "
#define STATUSCASCADE		" Cascade all normal child windows "
#define STATUSICONS			" Arrange iconic child windows "
#define STATUSCLOSEALL		" Close all child windows "
#define STATUSMDICHILD      " Activate the window marked as %d"
#define STATUSPOPUPHELP		" Help commands "
#define STATUSAPPHELP		" Display help on application "
#define STATUSABOUT			" About application "
#define STATUSDEFAULT		" Ready "

#define DEFDBNAME						"?"
#define PROVIDER_SESSION_FORMAT			"%s!%lX"
#define PROVIDER_SESSION_COMMAND_FORMAT	"Provider:=%s!Session=%lX!Command=%lX"
#define SCANPROVIDERSESSION_FORMAT		"%[^!]!%lX"
#define SCANSESSION_FORMAT				"%*[^!]!%lX"
#define SCANSESSION_TITLEFORMAT			"Provider:=%*[^!]!Session=%lX"
#define SCANSESSIONCOMMAND_FORMAT		"Provider:=%*[^!]!Session=%lX!Command=%lX"
#define SCANCOMMAND_TITLEFORMAT			"Provider:=%*[^!]!Session=%*lX!Command=%lX"
#define CUR_MARK				"<-"
#define CURQUERY_STRING			"Command!%lX<-"
#define QUERY_STRING			"Command!%lX"
#define MAKECONNECT				"Please connect to a data source using Login menu."
#define	OPENWINDOW				"Please open a window from Query menu."
#define NOSESSIONERROR			"No Session Available"
#define NOCOMMANDERROR			"No Command Window Available"
#define MAXCHILDEXCEEDED		"Please close a child window and try again."
#define MAXCHLDERR				"Error - Too many Child Windows"
#define COLTRUNC_WARNG			"Number of columns in display truncated to %u"
#define ROWTRUNC_WARNG			"Number of rows in display truncated to %u"
#define TRUNCERR				"Data Truncation"
#define CLOSEALLSESSION			"All open sessions have been released."
#define LOGOUTINFO				"Log Out Information"
#define SQLERR_FORMAT			"SQL Error State:%s, Native Error Code: %lX, OLEDB Error: %s"
#define SQLERRMSGTITLE			"SQL_ERROR results"
#define SQLERRCNTDTITLE			"SQL_ERROR results continued"
#define SQLWRNMSGTITLE			"SQL_SUCCESS_WITH_INFO results"
#define SQLWRNCNTDTITLE			"SQL_SUCCESS_WITH_INFO results continued"
#define NULLDATASTRING			"SQL_NULL_DATA"

/* Globals */
//HWND		hWndFrame;      	// Main Frame Window handle
//HWND		hWndCrsrList;   	// hdbc(s) combobox on the tool bar
//HWND		hWndStmtList;   	// hstmt(s) combobox on the tool bar
//HWND		hWndMDIClient;  	// MDI Client window handle
//HWND		hWndActiveChild;	// Current active MDI Child window
//HINSTANCE	hAppInstance;   	// Application instance


/* Macros and Function Prototypes */
#ifdef WIN32
#define		ACTIVATEWINDOW(h)	SetForegroundWindow(h)
#else
#define		ACTIVATEWINDOW(h)	SetFocus(h)
#endif

#define DRAWBTTNRECT(h,x,y,cx,cy)	MoveToEx(h,x+1,y,NULL);\
					LineTo(h,x+cx,y);\
					MoveToEx(h,x+cx,y+1,NULL);\
					LineTo(h,x+cx,y+cy);\
					MoveToEx(h,x+cx-1,y+cy,NULL);\
					LineTo(h,x,y+cy);\
					MoveToEx(h,x,y+cy-1,NULL);\
					LineTo(h,x,y);

#define DRAWBTTNLIFT1(h,x,y,cx,cy)	MoveToEx(h,x+1,y+cy-1,NULL);\
					LineTo(h,x+1,y+1);\
					LineTo(h,x+cx-1,y+1);

#define	DRAWBTTNLIFT2(h,x,y,cx,cy)	MoveToEx(h,x+1,y+cy-1,NULL);\
					LineTo(h,x+cx-1,y+cy-1);\
					LineTo(h,x+cx-1,y);\
					MoveToEx(h,x+2,y+cy-2,NULL);\
					LineTo(h,x+cx-2,y+cy-2);\
					LineTo(h,x+cx-2,y+1);
// MAIN.CPP
int		PASCAL		WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
long	CALLBACK	MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
long	CALLBACK	ToolbarProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
long	CALLBACK	StatusbarProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
long	CALLBACK	MDIChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL	CALLBACK	ConnectDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL	CALLBACK	DisconnectDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL	CALLBACK	AboutDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL	CALLBACK	MDIChildDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
VOID	FAR PASCAL	DrawBitmap(HDC hDC, int iLeft, int iTop, HBITMAP hBitmap);

// QURYDEMO.CPP
BOOL	FAR PASCAL	InitEnvironment();
void	FAR PASCAL	DisplayProviders(HWND hWnd);
BOOL	FAR PASCAL  ConnectDatabase(HWND hWnd);
void	FAR PASCAL	DisplayConnections(HWND hWndhdbc);
void	FAR PASCAL	DisplayICommands(HWND hWndhstmt, HWND hWndhdbc, int nCrsrIndex);
void	FAR PASCAL	NewICommandWindow();
void	FAR PASCAL	NewIOpenRowsetWindow();
void	FAR PASCAL	ChangeCurrentICommand(HWND hWndStmtList);
void	FAR PASCAL	ChangeCurrentCursor(HWND hWndCrsrList);
void	FAR PASCAL	DisplayNewCrsrAndICommand();
void	FAR PASCAL	FreeConnect(HWND hWndhdbc);
void	FAR PASCAL	FreeICommand(HWND hWndhstmt, HWND hWndhdbc, int nIndex);
void	FAR PASCAL	CloseICommandWindow(HWND hWnd);
void	FAR PASCAL	ExecuteQuery();
BOOL	FAR PASCAL	CloseIDBCreateCommand();
HRESULT DisplayDataSource(HWND hWnd);
HRESULT	FreeEnvironment();
void	FAR PASCAL	GetSchemaRowset(GUID rguidSchema);

HRESULT EnumerateProviders ();

HRESULT ExecuteCommand
	(
	IUnknown*	pIUnknown,
	ICommand*	pICommand,
	LPWSTR		wszBuffer,
	IRowset**	ppIRowset_out 
	);

HRESULT GetDataFromRowset
	(
	IRowset*	pIRowset
	);

HRESULT GetColumnsInfo
	(
	IRowset*		pIRowset,
	ULONG* 			pcCol,
	DBCOLUMNINFO**	ppColumnInfo,
	WCHAR**			ppStringsBuffer
	);

HRESULT SetupBindings
	(
	ULONG 			cCol,
	DBCOLUMNINFO*	pColumnInfo,
	DBBINDING*		rgBind_out,
	ULONG*			cBind_out,
    ULONG*          pcMaxRowSize_out
	);
    
HRESULT CreateAccessor
	(
	IRowset*	pIRowset,
	DBBINDING*	rgBind,
	ULONG		cBind,
	HACCESSOR*	phAccessor_out
	);

HRESULT GetData
	(
	IRowset*		pIRowset,
	ULONG   		cMaxRowSize,
    HACCESSOR		hAccessor,
    DBBINDING*	    rgBind,			// needed for pretty printing
    ULONG		    cBind,	    	// for pretty printing
    DBCOLUMNINFO*	pColumnInfo, 	// for pretty printing
    ULONG			cCol,			// for pretty printing		
	HWND			hList,
	DWORD			dwText,
	DWORD			addString
	);

HRESULT CleanupRowset
	(
	IRowset*	pIRowset,
	HACCESSOR 	hAccessor
	);

void DumpRow
	(
    DBBINDING* 	rgBind,
    ULONG		cBind,
    ULONG		cMaxColWidth,
    BYTE* 		pData,
	HWND		hList,
	DWORD		dwText,
	DWORD		addString
    );

HRESULT GetDetailedErrorInfo 
      (
	   HRESULT	hr,
	   IUnknown * pBadObject,                  
	   GUID IID_BadIntereface,        
	   LPSTR	lpStrBuffer
//       char * szErrorDescription_out,
//	   char * szErrorSource_out
	  );

/*
void DumpError
     ( HRESULT hr, 
	   LPSTR lpStrBuffer, 
	   LPSTR lpSource, 
	   LPSTR lpDescription
	  );
*/

void DumpErrorHResult
	( 
	HRESULT hr,
	LPSTR lpStrBuffer
	);

// How to lay out each column in memory.
// Note that bData should be DWORD aligned, since it may contain a DWORD.
struct COLUMNDATA 
	{
	DBSTATUS	wStatus;	// status of column
	DWORD		dwLength;	// length of data (not space allocated)
	BYTE		bData[1];	// data here and beyond
	};


/******************************* End of File ********************************/
