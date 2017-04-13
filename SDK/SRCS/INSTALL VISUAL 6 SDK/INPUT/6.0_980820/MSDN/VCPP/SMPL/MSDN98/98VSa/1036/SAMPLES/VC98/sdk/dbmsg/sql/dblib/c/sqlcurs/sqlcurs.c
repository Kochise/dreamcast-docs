/*************************************************************************

	PROGRAM: SQLCURS - SQL DB-Library cursors sample program
		 Copyright (c), 1995 by Microsoft Corp.

*************************************************************************/


#if defined(DBNTWIN32)
#include <windows.h>
#endif

#include <sqlfront.h>
#include <sqldb.h>	/* DBLIB header files (should always be included    */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#ifndef NULL
#define	    NULL    0
#endif

#define INVALID_VALUE (short)-100

/* Forward declarations of the error handler and message handler. */
int err_handler(DBPROCESS*, int, int, int, char*, char*);
int msg_handler(DBPROCESS*, DBINT, int, int, char*);

void ProcessResults(void);

#define NROWS	    5		/* Number of rows to be scrolled at a time   */


/* Select statement to be used in the cursor case */

char stmt[] = " select au_lname, au_fname, city, state from authors where contract = 1 ";


/* Status array, and results set */

DBINT	    pstat[NROWS];
char	    au_lname[NROWS][41];
char	    au_fname[NROWS][21];
char	    au_city[NROWS][21];
char	    au_state[NROWS][3];
DBINT	    au_citlen[NROWS];
DBINT	    au_statlen[NROWS];
DBINT	    au_fnamlen[NROWS];
char	    *stats[NROWS];
char	    values[250];
short     ScrollOpt;
short     ConcurOpt;
int       ch;

main ()
{
	DBPROCESS *dbproc;	/* allocate a DB-LIB process structure		*/
	LOGINREC  *login;	/* allocate a DB-LIB login structure		*/
	DBCURSOR  *hcursor; /* allocate a DB-LIB cursor structure		*/

	char       Servername[21] = "";
	RETCODE    result_code;
	int     fetch, optype;
	int     nrow;
	char    sfetch[3], soptype[3];
	char    srow[3], stab[31];

	/* Install the user-supplied error-handling	and message-handling
	 * routines. They are defined at the bottom	of this	source file.
	 */
	
	dberrhandle((DBERRHANDLE_PROC)err_handler);
	dbmsghandle((DBMSGHANDLE_PROC)msg_handler);

	/* Get server's computer name */
	printf ("\nEnter Name of SQL Server: ");
	gets (Servername);

	ScrollOpt = INVALID_VALUE;
	do 
	{
		printf ("\nEnter Scroll Option: F)orward  K)eyset  D)ynamic  I)nsensitive: ");
		ch = tolower(_getch());
		switch (ch)
		{
			case 'f': ScrollOpt = CUR_FORWARD; break;
			case 'k': ScrollOpt = CUR_KEYSET;  break;
			case 'd': ScrollOpt = CUR_DYNAMIC; break;
			case 'i': ScrollOpt = CUR_INSENSITIVE; break;
			default:  printf("Invalid character entered."); break;
		}
	} while (ScrollOpt == INVALID_VALUE);

	ConcurOpt = INVALID_VALUE;
	do 
	{
		printf ("\nEnter Concurrency Option: R)ead Only   L)ock CC   O)opt CC   V)al Opt CC: ");
		ch = tolower(_getch());
		switch (ch)
		{
			case 'r': ConcurOpt = CUR_READONLY; break;
			case 'l': ConcurOpt = CUR_LOCKCC;   break;
			case 'o': ConcurOpt = CUR_OPTCC;    break;
			case 'v': ConcurOpt = CUR_OPTCCVAL; break;
			default:  printf("Invalid character entered."); break;
		}
	} while (ConcurOpt == INVALID_VALUE);
	printf("\n");
	login = dblogin();		    /* get login record	from DB-LIB */
	DBSETLUSER (login, (char far *)"sa");     /* set the username	*/
	DBSETLAPP (login, (char far *)"curtest"); /* set the application name */
	DBSETLPWD (login, (char far *)"");	      /* set the SQL Server password */
	DBSETLVERSION(login, DBVER60);

	/* Now attempt to create and initialize a DBPROCESS	structure */
	if((dbproc = dbopen (login, Servername)) == NULL)
	{
		printf ("dbopen failed\n");
		return (1); /* exit program */
	}

	dbuse (dbproc, "pubs");  /* use the "pubs" database */

	/* Open the cursor */
	hcursor = dbcursoropen(dbproc, stmt, ScrollOpt, ConcurOpt, NROWS, pstat);
	if (hcursor == (DBCURSOR *)NULL)
	{
		printf("\ndbcursoropen failed\n");
		return(1);
	}

	/* Bind variables */
	result_code = dbcursorbind(hcursor, 1, NTBSTRINGBIND, 41, NULL, (char *)au_lname);
	if (result_code == FAIL)
	{
		printf("\ndbcursorbind failed, column 1\n");
		return(1);
	}
	result_code = dbcursorbind(hcursor, 2, NTBSTRINGBIND, 21, au_fnamlen, (char *)au_fname);
	if (result_code == FAIL)
	{
		printf("\ndbcursorbind failed, column 2\n");
		return(1);
	}
	result_code = dbcursorbind(hcursor, 3, NTBSTRINGBIND, 21, au_citlen, (char *)au_city);
	if (result_code == FAIL)
	{
		printf("\ndbcursorbind failed, column 3\n");
		return(1);
	}
	
	result_code = dbcursorbind(hcursor, 4, NOBIND, 0, au_statlen, (char *)stats);
	if (result_code == FAIL)
	{
		printf("\ndbcursorbind failed, column 4\n");
		return(1);
	}
	
	/* Begin transaction. Will exit without committing the transaction so that
	** none of the data modifications will actually be committed */
	if ((dbcmd(dbproc, "begin transaction") == FAIL) ||
		(dbsqlexec(dbproc) == FAIL) || (dbresults(dbproc) == FAIL))
	{
		printf("\n BEGIN TRAN failed");
		return(1);
	}

	/* Now fetch and print the rows */
	while (TRUE)
	{
		printf("\n0)Leave  1)First  2)Next  3)Previous  4)Random  5)Relative  6)Last  7)By Value");
		printf("\nEnter fetch value: ");
		fetch = atoi(gets(sfetch));
		if (fetch != 0)
		{
			if ((fetch == FETCH_RANDOM) || (fetch == FETCH_RELATIVE))
			{
				printf("\n Enter row number: ");
				nrow = atoi(gets(srow));
			}
			else
				nrow = 0;

			if (dbcursorfetchex(hcursor, fetch, nrow, NROWS, 0) == FAIL)
				printf("\ndbcursorfetchex() failed\n");

			ProcessResults();
			continue;		/* Fetch again */
		}
	
		/* Do updates */
		while (TRUE)
		{
			printf("\n0)Leave  1)Update  2)Delete  3)Insert  4)Refresh  5)Lock  6)Cursor Fetch");
			printf("\nEnter operation: ");
			optype = atoi(gets(soptype));

			if ((optype == 0) || (optype == 6))		/* Exit condition */
				break;
			
			if (optype > 6)
				continue;

			printf("\nEnter buffer number: ");
			nrow = atoi(gets(srow));
			printf("\nEnter table: ");
			gets(stab);
			printf("\nEnter values: ");
			gets(values);
			if (values == (char *)NULL)
				values[0] = '\0';
			if ((result_code=dbcursor(hcursor, optype, nrow, stab, values)) == FAIL)
				printf("\n dbcursor failed");
			else
				if (optype == CRS_REFRESH)
					ProcessResults();
				else
					printf("\ndbcursor() succeeded");

		} /* Exit dbcursor() loop */
		
		if (optype == 0)
			break;	   /* Close cursor */
	}

	dbcursorclose(hcursor);

	dbexit();
}

void ProcessResults()
{
	int i, len;

	printf(" Row       First Name                 Last Name                City       State\n");
	printf("----- -------------------- ------------------------------ --------------- -----\n");
	for (i = 0 ; i < NROWS ; i++)
	{	/* Process results */
		if(pstat[i] & FTC_SUCCEED)
		{
			len = 0;
			if (au_statlen[i] != 0) /* This is a NOBIND type */
			{
				len = min(2, (SHORT)au_statlen[i]);
				memcpy(au_state[i], stats[i], len);
			}
			au_state[i][len] = '\0';
  			printf("%5d %-20s %-30s %-15s %-2s\n",i+1,au_fname[i],au_lname[i],au_city[i],au_state[i]);
		}
		else
			if (pstat[i] &  FTC_MISSING)
				printf("\n Row no. %d is missing", i+1);

		/*
		
		The following code could be used if dbcursorfetch()
		was used instead of dbcursorfetchex().

		if (pstat[i] & FTC_ENDOFRESULTS)
		{
			printf("\n End of results");
			break;
		}
		if (pstat[i] & FTC_ENDOFKEYSET)
		{
			printf("\nEnd of keyset");
			break;
		}
		*/

	}
	return;
}

int err_handler(dbproc,	severity, dberr, oserr,	dberrstr, oserrstr)
DBPROCESS *dbproc;
int		 severity;
int		 dberr;
int		 oserr;
char	    *dberrstr;
char	    *oserrstr;
{
	printf("DB-LIBRARY error:\n\t%s\n", dberrstr);

	if (oserr != DBNOERR)
		printf("Operating-system error:\n\t%s\n", oserrstr);

	if ((dbproc == NULL) ||	(DBDEAD(dbproc)))
		return(INT_EXIT);
	else
	{
		return(INT_CANCEL);
	}
}

int msg_handler(dbproc,	msgno, msgstate, severity, msgtext)
DBPROCESS *dbproc;
DBINT		 msgno;
int		 msgstate;
int		 severity;
char	    *msgtext;
{
	printf("SQL Server message %ld, state %d, severity %d:\n\t%s\n",
		msgno,	msgstate, severity, msgtext);
	return(0);
}
