/****************************************************************************

	PROGRAM: SqlTestn.c
	Copyright (C) 1995-1997 Microsoft Corp.

	PURPOSE: SqlTest sample Windows applications

	FUNCTIONS:

	WinMain() - calls initialization function, processes message loop
	SqlTestInit() - initializes window data and registers window
	SqlTestWndProc() - processes messages
	AboutSQL() - processes messages for "About" dialog box
	SelectSQL() - processes input of author name
	ConnectSQL() - processes input of server name and connects to server

	COMMENTS:

	WIN32 can have several copies of your application running at the
	same time.  The variable hInst keeps track of which instance this
	application is so that processing will be to the correct window.

	You only need to initialize the application once.  After it is
	initialized, all other copies of the application will use the same
	window class, and do not need to be separately initialized.

****************************************************************************/

#include "windows.h"      /* required for all NT Windows applications*/
#include "stdio.h"
#define DBNTWIN32         /* needed to define environment 	    */
#include "sqlfront.h"     /* standard dblib include file	    */
#include "sqldb.h"        /* standard dblib include file	    */
#include "sqltestn.h"     /* specific to this program		    */

PDBPROCESS dbproc = (PDBPROCESS)NULL;
	              /* dbprocess pointer for dblib connection*/
HINSTANCE hInst;    /* current instance			    */
HWND ghWnd;      /* global window handle for handlers    */
HWND errhWnd;    /* global window handle for current error*/

/****************************************************************************

	FUNCTION: WinMain(HANDLE, HANDLE, LPSTR, int)

	PURPOSE: calls initialization function, processes message loop

	COMMENTS:

	This will initialize the window class if it is the first time this
	application is run.  It then creates the window, and processes the
	message loop until a PostQuitMessage is received.  It exits the
	application by returning the value passed by the PostQuitMessage.

****************************************************************************/

int PASCAL WinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow)
HINSTANCE hInstance;			     /* current instance	     */
HINSTANCE hPrevInstance;			     /* previous instance	     */
LPSTR lpCmdLine;			     /* command line		     */
int nCmdShow;				     /* show-window type (open/icon) */
{
	HWND hWnd;				     /* window handle		     */
	MSG msg;				     /* message			     */


	if (!hPrevInstance)			/* Has application been initialized? */
		if (!SqlTestInit(hInstance))
			return (0);		/* Exits if unable to initialize     */

	hInst = hInstance;			/* Saves the current instance	     */

	hWnd = CreateWindow("SQL Test",               /* window class	     */
		"SQL Server Sample Windows NT Application", /* window name	     */
		WS_OVERLAPPEDWINDOW|WS_VISIBLE,            /* window style	     */
		CW_USEDEFAULT,                             /* x position		     */
		CW_USEDEFAULT,                             /* y position		     */
		CW_USEDEFAULT,                             /* width		     */
		CW_USEDEFAULT,                             /* height		     */
		NULL,                                      /* parent handle	     */
		NULL,                                      /* menu or child ID	     */
		hInstance,                                 /* instance		     */
		NULL);                                     /* additional info	     */

	if (!hWnd)					  /* Was the window created? */
		return (0);

	ghWnd = hWnd;				  /* set global handle	     */
	errhWnd = hWnd;

	ShowWindow(hWnd, SW_SHOW); /* Shows the window        */
	UpdateWindow(hWnd);        /* Sends WM_PAINT message  */

	while (GetMessage(&msg, /* message structure */
				NULL,		      /* handle of window receiving the message */
				0,             /* lowest message to examine */
				0))            /* highest message to examine	*/
	{
		TranslateMessage(&msg);	   /* Translates virtual key codes	     */
		DispatchMessage(&msg);	   /* Dispatches message to window	     */
	}
	return (msg.wParam);	   /* Returns the value from PostQuitMessage */
}


/****************************************************************************

	FUNCTION: SqlTestInit(HANDLE)

	PURPOSE: Initializes window data and registers window class

	COMMENTS:

	Sets up a structure to register the window class.  Structure includes
	such information as what function will process messages, what cursor
	and icon to use, etc.

****************************************************************************/

BOOL SqlTestInit(hInstance)
HANDLE hInstance;			       /* current instance	     */
{
	HANDLE hMemory;			       /* handle to allocated memory */
	PWNDCLASS pWndClass;		       /* structure pointer	     */
	BOOL bSuccess;			       /* RegisterClass() result     */

	hMemory = LocalAlloc(LPTR, sizeof(WNDCLASS));
	pWndClass = (PWNDCLASS)hMemory;

	pWndClass->style = 0; /*CS_HREDRAW | CS_VREDRAW; */
	pWndClass->lpfnWndProc = (WNDPROC)SqlTestWndProc;
	pWndClass->hInstance = hInstance;
	pWndClass->hIcon = LoadIcon(hInstance, "SQLITEST");
	pWndClass->hCursor = LoadCursor(NULL, IDC_ARROW);
	pWndClass->hbrBackground = GetStockObject(WHITE_BRUSH);
	pWndClass->lpszMenuName = (LPSTR)"SQLTest";
	pWndClass->lpszClassName = (LPSTR)"SQL Test";

	bSuccess = RegisterClass(pWndClass);

	LocalFree(hMemory);				    /* Returns it to NT */
	return (bSuccess);		 /* Returns result of registering the window */
}

/****************************************************************************

	FUNCTION: SqlTestWndProc(HWND, unsigned, WORD, LONG)

	PURPOSE:  Processes messages

	MESSAGES:

	WM_SYSCOMMAND - system menu (About dialog box)
	WM_CREATE     - create window
	WM_DESTROY    - destroy window
	WM_COMMAND    - application menus (Connect and Select dialog boxes

	COMMENTS:

	To process the ID_ABOUTSQL message. Call Dialog
	box which will create the box according to the information in your
	SqlTest.rc file and turn control over to the About() function.	When
	it returns, free the intance address.
	This same action will take place for the two menu items Connect and
	Select.

****************************************************************************/

LONG APIENTRY SqlTestWndProc(hWnd, message, wParam, lParam)
HWND hWnd;				  /* window handle		     */
UINT message;	        		  /* type of message		     */
DWORD wParam;				  /* additional information	     */
LONG lParam;				  /* additional information	     */
{
					  /* functions 			     */
	HMENU hMenu;			  /* handle to the System menu	     */

	switch (message)
	{
		case WM_SYSCOMMAND:		/* message: command from system menu */
			if (wParam == ID_ABOUTSQL)
			{
				DialogBox(hInst,		 /* current instance	     */
					(LPTSTR)"ABOUTSQL",		 /* resource to use	     */
					hWnd,			 /* parent handle	     */
					(DLGPROC) AboutSQL);		 /* About() instance address */

				break;
			}
			else			    /* Lets NT process it	     */
				return (DefWindowProc(hWnd, message, wParam, lParam));

		case WM_CREATE:			    /* message: window being created */

			/* Get the handle of the System menu */
			hMenu = GetSystemMenu(hWnd, FALSE);

			/* Add a separator to the menu */
			AppendMenu(hMenu,			      /* menu handle	     */
				MF_SEPARATOR,				      /* menu item to change */
				0,				      /* new menu item	     */
				0);				      /* menu identifier     */

			/* Add new menu item to the System menu */
      	AppendMenu(hMenu,			      /* menu handle	     */
				MF_STRING,				      /* menu item to change */
				ID_ABOUTSQL,			      /* menu identifier     */
				"A&bout SQL Test...");		      /* new menu item	     */

			dbinit();                                 /* initialize dblib    */
	
			/* Now make the message and error    */
			/* Install the handler into dblib */	
			dberrhandle((DBERRHANDLE_PROC)dbwinErrorHandler);
			dbmsghandle((DBMSGHANDLE_PROC)dbwinMessageHandler);
			break;
	
		case WM_COMMAND :			/* menu selections generate */
				
			/* the WM_COMMAND message   */	
			switch(wParam)			/* menu in WORD parameter   */
			{
				case IDM_CONNECT :		/* connect to server	    */
					DialogBox(hInst,		/* current instance	     */
						"CONNECT",	 	/* resource to use	     */
						hWnd,			/* parent handle	     */
						(DLGPROC) ConnectSQL); 	/* ConnectSQL() instance address */

					break;
	
				case IDM_SELECT :		/* select an author	    */

					DialogBox(hInst,		 /* current instance	     */
						"SELECT",		 /* resource to use	     */
						hWnd,			 /* parent handle	     */
						(DLGPROC) SelectSQL);		 /* About() instance address */

					break;
			}
			break;
	
		case WM_DBRESULTS :			/* a select has been issued */
			SqlTestProcessResults(hWnd);	/* process results	    */
			break;

		case WM_DESTROY:		  /* message: window being destroyed */
			dbexit();			  /* free any active dbprocesses     */
			PostQuitMessage(0);
			break;

		default:			  /* Passes it on if unproccessed    */
			return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	
	return (0L);
}


/****************************************************************************

	FUNCTION: AboutSQL(HWND, unsigned, WORD, LONG)

	PURPOSE:  Processes messages for "AboutSQL" dialog box

	MESSAGES:

	WM_INITDIALOG - initialize dialog box
	WM_COMMAND    - Input received

	COMMENTS:

	No initialization is needed for this particular dialog box, but TRUE
	must be returned to NT.

	Wait for user to click on "Ok" button, then close the dialog box.

****************************************************************************/

LONG APIENTRY AboutSQL(hDlg, message, wParam, lParam)
HWND hDlg;
UINT message;
DWORD wParam;
LONG lParam;
{
	switch (message)
	{
		case WM_INITDIALOG:		   /* message: initialize dialog box */
			return (TRUE);

		case WM_COMMAND:		      /* message: received a command */
			if (wParam == IDOK)
			{	      /* "OK" box selected?	     */
				EndDialog(hDlg, 0);	      /* Exits the dialog box	     */
				return (TRUE);
			}
			break;
	}
	return (FALSE);			      /* Didn't process a message    */
}
/****************************************************************************

	FUNCTION: SelectSQL(HWND, unsigned, WORD, LONG)

	PURPOSE:  Processes messages for "SelectSQL" dialog box

	MESSAGES:

	WM_INITDIALOG - initialize dialog box
	WM_COMMAND    - Input received

	COMMENTS:

	No initialization is needed for this particular dialog box, but TRUE
	must be returned to NT.
	
	Let user input into edit control the name of an author (the select
	IS case sensitive).  When user presses OK, format the select statement
	then send it to the server and execute it via dbsqlexec(). If the
	dbsqlexec() SUCCEED's post a WM_DBRESULTS message so the results
	may be retrieved and processed.

	Wait for user to click on "Ok" button, then close the dialog box.

****************************************************************************/

LONG APIENTRY SelectSQL(hDlg, message, wParam, lParam)
HWND hDlg;
UINT message;
DWORD wParam;
LONG lParam;
{
	char szSelectAuthor[41];		  /* string for authors name	    */
	char szServerMess[45];		  /* string for server response	    */
	char szAName[40];			  /* format string for author	    */
	switch (message)
	{
		case WM_INITDIALOG:		   /* message: initialize dialog box */
			SendDlgItemMessage(hDlg,       /* limit input to 40 characters   */
				AUTHORNAME,EM_LIMITTEXT,40,0L);
			return (TRUE);

		case WM_COMMAND:		      /* message: received a command */
			errhWnd = hDlg;
			switch(wParam)
			{
				case IDOK :		      /* "OK" box selected?	     */
					*szSelectAuthor = '\0';   /* Null author		     */
					GetDlgItemText(hDlg,AUTHORNAME, (LPSTR)szSelectAuthor, MAX_ANAME);
					if(dbproc == (PDBPROCESS)NULL) /* if not a valid process*/
					{
						/* No server to query		*/
						MessageBox(hDlg,
							"No SQL Server Connected to Query",
							"SQL Test",MB_ICONHAND | MB_OK);
					}
					else
						if(*szSelectAuthor != '\0') /* if a name exists */
						{
							DBLOCKLIB();		/* lock down the library */
							/* format the select statement */
							dbcmd(dbproc,
								(LPSTR)"select au_id, au_lname,"
								"au_fname, phone, address, city, state, zip");
							dbcmd(dbproc, (LPSTR)" from authors");
							dbcmd(dbproc, (LPSTR)" where au_lname = ");
							sprintf(szAName,"'%s'",szSelectAuthor);
							dbcmd(dbproc,(LPSTR)szAName);
							if (dbsqlexec(dbproc) == FAIL)
							{
								sprintf(szServerMess,	/* error, not in db */
									"%s not found in database pubs",
									szSelectAuthor);
								MessageBox(hDlg,
									(LPSTR)szServerMess,(LPSTR)"SQL Test",
									MB_ICONHAND | MB_OK);
							}
							else	/* query SUCCEEDed so 			*/
							{	/* post message to process results	*/
								PostMessage(GetParent(hDlg),WM_DBRESULTS,0,0L);
							}
							DBUNLOCKLIB();		/* unlock library	*/
						}
					EndDialog(hDlg, 0);	      /* Exits the dialog box	     */
					return (TRUE);
					break;
		
				case IDCANCEL :
					EndDialog(hDlg, 0);	      /* cancelled select */
					return(TRUE);
					break;
			}
	break;
	}
	
	return (FALSE); /* Didn't process a message    */
}
/****************************************************************************

	FUNCTION: ConnectSQL(HWND, unsigned, WORD, LONG)

	PURPOSE:  Processes messages for "Connect" dialog box

	MESSAGES:

	WM_INITDIALOG - initialize dialog box
	WM_COMMAND    - Input received

	COMMENTS:

	No initialization is needed for this particular dialog box, but TRUE
	must be returned to NT.

	Wait for user to click on "Ok" button, then close the dialog box.

****************************************************************************/

LONG APIENTRY ConnectSQL(hDlg, message, wParam, lParam)
HWND hDlg;
UINT message;
DWORD wParam;
LONG lParam;
{
	char szSQLServer[31];
	static PLOGINREC LoginRec;

	*szSQLServer = '\0';
	switch (message)
	{
		case WM_INITDIALOG:		   /* message: initialize dialog box*/
			SendDlgItemMessage(hDlg,       /* limit input to 30 characters  */
				SQL_SERVER,EM_LIMITTEXT,30,0L);
			return (TRUE);

		case WM_COMMAND:		      /* message: received a command*/
			errhWnd = hDlg;
			switch(wParam)
			{
				case IDOK :		      /* "OK" box selected?	    */
					GetDlgItemText(hDlg,SQL_SERVER,
						(LPSTR)szSQLServer,
						MAX_SERVERNAME); /* get Server name */
					if(*szSQLServer != '\0') /* was something input	    */
					{
						DBLOCKLIB();		/* lock down library	    */
						if (dbproc != (PDBPROCESS)NULL) /* if an active     */
							/* process close it */
							dbclose(dbproc);
						if ((LoginRec = dblogin()) != (PLOGINREC)NULL) /* get loginrec */
						{
							DBSETLUSER(LoginRec,(char far *)"sa"); /* set user  */
							DBSETLVERSION(LoginRec,DBVER60);

							/* now open the connection to server */
							if((dbproc = dbopen(LoginRec,(LPSTR)szSQLServer))
								== (PDBPROCESS)NULL)
							{
								/* if NULL couldn't connect	*/
								dbfreelogin(LoginRec);
							}
							else /* got connect so use the pubs database */
							{
								dbuse(dbproc,(LPSTR)"pubs");
								dbfreelogin(LoginRec);
							}
						}
						else /* memory allocation problem */
							MessageBox(hDlg, "Could not allocate Login Record","System Error", MB_ICONHAND | MB_OK);
						DBUNLOCKLIB(); /* done unlock library	*/
					}
					EndDialog(hDlg, 0);	      /* Exits the dialog box	     */
					return (TRUE);
					break;
				
				case IDCANCEL :
					EndDialog(hDlg, 0);
					return(TRUE);
					break;
		
			}
	break;
	}
	
	return (FALSE); /* Didn't process a message */
}

/****************************************************************************

	FUNCTION: CheckForScroll(HWND, int, int, int)

	PURPOSE:  Check if next output line will be out of client area

	PARAMETERS:
	hWnd - Handle to the window.
	CurrentPosition - Current y coordinate for the line of
		text just written to the client area.
	Spacing - The height of the line (including the space
		separating lines) of the text just written.
	Length - The length of the line just written in device units.

	RETURN:	Returns the Y coordinate for the next line of text.

	COMMENTS:

	Will determine if the next line of text will be out of the client
	area.  If so will scroll the window for the next line.  Also validates
	the current line of text so that a WM_PAINT will not clear it.

****************************************************************************/
int CheckForScroll(hWnd,CurrentPosition,Spacing, Length)
HWND hWnd;
int CurrentPosition;
int Spacing;
int Length;
{
	RECT rect;				/* RECT structure for validation */
	rect.top = CurrentPosition; 	/* top of last line of text	 */
	rect.bottom = CurrentPosition+Spacing+1; /* bottom of last line	 */
	rect.left = 1;			/* left most column of line	 */
	rect.right = Length+1;		/* right most column of line	 */
	ValidateRect(hWnd,(LPRECT)&rect);   /* validate line so that it is   */
	
	/* not blanked on next paint	 */
		
	GetClientRect(hWnd,(LPRECT)&rect);	/* get rect for current client   */
	if(CurrentPosition + (Spacing*2) > rect.bottom) /* will line fit	 */
	{
		/* if not scroll window and 	 */
		/* update client window		 */
		ScrollWindow(hWnd,0,-(Spacing+1),NULL,NULL);
		UpdateWindow(hWnd);
		return(CurrentPosition);
	}
	
	return(CurrentPosition+Spacing);
}

/****************************************************************************

	FUNCTION: SQLTestProcessResults(HWND)

	PURPOSE:  If a valid dbprocess is present process all results from pending
		select statement, output each field to client area.  Whenever
		a new line is written to client area it is checked to see if
		the client area needs to be scrolled.

	PARAMETERS: hWnd - Handle to the window.

	RETURN:	Returns the Y coordinate for the next line of text.

	COMMENTS:
	This function will bind the fields in the select statement
	to local variables, format an output string then
	write that string to the client area via TextOut.
	It is called by the main message processing loop
	SQLTestWndProc via the message WM_DBRESULTS.

****************************************************************************/
BOOL SqlTestProcessResults(hWnd)
HWND hWnd;
{
	HDC hDC;				/* display context		 */
	TEXTMETRIC tm;			/* text metric structure	 */
	char szId[12];			/* Author ID for binding	 */
	char szLastName[41];		/* Author last name for binding	 */
	char szFirstName[21];		/* Author first name for binding */
	char szPhone[13];			/* Author phone for binding	 */
	char szAddress[41];			/* Author address for binding	 */
	char szCity[21];			/* Author city for binding	 */
	char szState[3];			/* Author state for binding	 */
	char szZip[6];			/* Author zipcode for binding	 */
	char szOutputString[81];		/* general output string	 */
	RETCODE result_code;		/* results code from dbresults	 */
	int Y;				/* Y coordinate for text output  */
	int Spacing;			/* Spacing between lines	 */
	errhWnd = hWnd;

	hDC = GetDC(hWnd);			/* get display context		 */
	GetTextMetrics(hDC, (LPTEXTMETRIC)&tm); /* get font info		 */
	Spacing = tm.tmExternalLeading + tm.tmHeight; /* set up spacing	 */
	Y = 1;				/* start at line 1		 */
	
	if(dbproc == (PDBPROCESS)NULL)	/* if process null, no results	 */
	{
		ReleaseDC(hWnd,hDC);		/* free resources and return	 */
		return(TRUE);
	}
	
	SendMessage(hWnd,WM_ERASEBKGND,(DWORD)hDC,0L); /* always erase background	 */
	UpdateWindow(hWnd);			/* force painting of window	 */
	DBLOCKLIB();			/* lock down library		 */

	/* get all results from the query*/
	while(((result_code = dbresults(dbproc)) != NO_MORE_RESULTS) && result_code != FAIL)
	{
		if(result_code == SUCCEED)	/* if results ready		 */
		{
			/* Bind all data of interest	 */
			dbbind(dbproc,1,NTBSTRINGBIND, 12L, (LPSTR)szId);
			dbbind(dbproc,2,NTBSTRINGBIND, 41L, (LPSTR)szLastName);
			dbbind(dbproc,3,NTBSTRINGBIND, 21L, (LPSTR)szFirstName);
			dbbind(dbproc,4,NTBSTRINGBIND, 13L, (LPSTR)szPhone);
			dbbind(dbproc,5,NTBSTRINGBIND, 41L, (LPSTR)szAddress);
			dbbind(dbproc,6,NTBSTRINGBIND, 21L, (LPSTR)szCity);
			dbbind(dbproc,7,NTBSTRINGBIND, 3L, (LPSTR)szState);
			dbbind(dbproc,8,NTBSTRINGBIND, 6L, (LPSTR)szZip);
			while(dbnextrow(dbproc) != NO_MORE_ROWS) /* get all rows	 */
			{
				/* here we format each field and write it to client */
				/* area checking to see if the client area needs to */
				/* be scrolled after each line is written	    */
				sprintf(szOutputString,"Author ID: %s",szId);
				TextOut(hDC,1,Y,szOutputString,strlen(szOutputString));
				Y = CheckForScroll(hWnd,Y,Spacing,strlen(szOutputString) * tm.tmMaxCharWidth);

				sprintf(szOutputString,"Last Name: %s",szLastName);
				TextOut(hDC,1,Y,szOutputString,strlen(szOutputString));
				Y = CheckForScroll(hWnd,Y,Spacing,strlen(szOutputString) * tm.tmMaxCharWidth);

				sprintf(szOutputString,"Address:   %s",szAddress);
				TextOut(hDC,1,Y,szOutputString,strlen(szOutputString));
				Y = CheckForScroll(hWnd,Y,Spacing,strlen(szOutputString) * tm.tmMaxCharWidth);

				sprintf(szOutputString,"City:      %s",szCity);
				TextOut(hDC,1,Y,szOutputString,strlen(szOutputString));
				Y = CheckForScroll(hWnd,Y,Spacing,strlen(szOutputString) * tm.tmMaxCharWidth);

				sprintf(szOutputString,"State:     %s",szState);
				TextOut(hDC,1,Y,szOutputString,strlen(szOutputString));
				Y = CheckForScroll(hWnd,Y,Spacing,strlen(szOutputString) * tm.tmMaxCharWidth);

				sprintf(szOutputString,"ZipCode:   %s",szZip);
				TextOut(hDC,1,Y,szOutputString,strlen(szOutputString));
				Y = CheckForScroll(hWnd,Y,Spacing,strlen(szOutputString) * tm.tmMaxCharWidth);

				sprintf(szOutputString,"Telephone: %s",szPhone);
				TextOut(hDC,1,Y,szOutputString,strlen(szOutputString));
				Y = CheckForScroll(hWnd,Y,Spacing,strlen(szOutputString) * tm.tmMaxCharWidth);

				Y = CheckForScroll(hWnd,Y,Spacing,0); /* add extra line     */
				/* after each results */
			}
		}
	}

	DBUNLOCKLIB();				/* unlock library	   */
	ReleaseDC(hWnd,hDC);			/* free resource	   */
	return(TRUE);
}

/****************************************************************************

	FUNCTION: dbwinMessageHandler(PDBPROCESS, DBINT, DBSMALLINT, DBSMALLINT,
		LPSTR)

	PURPOSE:  When the Data Server returns a message to dblib this function
		will be called to process that message.  This function is
		installed into dblib via MakeProcInstance.  It must be declared
		as a FAR cdecl function, not as a FAR PASCAL function, unlike
		other call back routines, as dblib conducts all of it's calls
		in the cdecl fashion.  You must return 0 to dblib.

	RETURN: Return 0

	COMMENTS:

****************************************************************************/

int API dbwinMessageHandler(dbproc, msgno, msgstate, severity, msgtext)
DBPROCESS        *dbproc;
DBINT            msgno;
INT              msgstate;
INT              severity;
CHAR             *msgtext;
{
	MessageBox(errhWnd,msgtext,(LPSTR)"SQL DataServer Message",MB_OK);
	return(0);
}

/****************************************************************************

	FUNCTION: dbwinErrorHandler(PDBPROCESS, int, int, int, LPSTR, LPSTR)

	PURPOSE: When dblib returns an error message to the application this
		function will be called to process that error.  This function is
		installed into dblib via MakeProcInstance.  It must be declared
		as a FAR cdecl function, not as a FAR PASCAL function, unlike
		other call back routines, as dblib conducts all of it's calls
		in the cdecl fashion.  You must return either INT_CANCEL,
		INT_CONTINUE, or INT_EXIT to dblib.

	RETURN: Return continuation code.

	COMMENTS:

****************************************************************************/

int API dbwinErrorHandler(dbproc, severity, errno, oserr, dberrstr, oserrstr)
PDBPROCESS dbproc;
int severity;
int errno;
int oserr;
LPSTR dberrstr;
LPSTR oserrstr;
{
	MessageBox(errhWnd,dberrstr,(LPSTR)"DB-LIBRARY error",MB_ICONHAND | MB_OK);

	if (oserr != DBNOERR)	/* os error	*/
		MessageBox(errhWnd,oserrstr,(LPSTR)"Operating-System error",MB_ICONHAND | MB_OK);

	return(INT_CANCEL);	/* cancel command */
}
