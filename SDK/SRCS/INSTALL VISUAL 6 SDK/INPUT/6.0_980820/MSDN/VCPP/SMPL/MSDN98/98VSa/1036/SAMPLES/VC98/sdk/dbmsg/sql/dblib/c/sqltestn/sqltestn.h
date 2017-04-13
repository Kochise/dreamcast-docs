/***************************************************************************
	FILE: SQLTESTW.H
	      Copyright (C) 1995, Microsoft Corp.

	PURPOSE: Defines values internal to the dblib test windows app.

	COMMENTS: This file contains all the constant declarations for
		the sqltestc windows application.

***************************************************************************/

#define ID_ABOUTSQL 	100			/* ID for ABOUTSQL box     */
#define AUTHORNAME	201			/* ID for authorname edit  */
						/* control		   */
#define SQL_SERVER	202			/* ID for server edit      */
						/* control		   */
#define MAX_ANAME	30			/* max length for author   */
#define MAX_SERVERNAME	31			/* max length for server   */
#define	IDM_CONNECT	400			/* menu id for connect	   */
#define	IDM_SELECT	401			/* menu id for select	   */
#define WM_DBRESULTS	WM_USER			/* results proc message	   */

/* declare all functions for application here		   */

int PASCAL WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
BOOL SqlTestInit(HANDLE);
BOOL SqlTestProcessResults(HWND);
LONG APIENTRY SqlTestWndProc(HWND, UINT, DWORD, LONG);
LONG APIENTRY AboutSQL(HWND, UINT, DWORD, LONG);
LONG APIENTRY SelectSQL(HWND, UINT, DWORD, LONG);
LONG APIENTRY ConnectSQL(HWND, UINT, DWORD, LONG);
int API dbwinErrorHandler(DBPROCESS *, int, int, int, CHAR *, CHAR *);
int API dbwinMessageHandler(DBPROCESS *, DBINT, INT, INT, CHAR *);
