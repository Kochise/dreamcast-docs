/*	example4.c */
/*
** This example accesses the data within each row without using dbbind()
** and illustrates the use of row buffering.
**
** It runs a query, saves all of the returned rows (up to a maximum
** of 100) using DB-LIBRARY row buffering, and allows the user to
** examine data rows at random.
*/

#if defined(DBNTWIN32)
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sqlfront.h>
#include <sqldb.h>

DBPROCESS	*dbproc;	/* Our connection with SQL Server. */
LOGINREC	*login;	/* Our login information. */

#define TYPELEN 2
#define DATELEN 25

/* Forward declarations of the error handler and message handler.
*/
int err_handler(DBPROCESS*, int, int, int, char*, char*);
int msg_handler(DBPROCESS*, DBINT, int, int, char*);

main(argc, argv)
int	argc;
char	*argv[];
{
	/* Here are the variables which will be used to store the
	* data being examined.
	*/
	DBCHAR	name[MAXNAME+1];	/* MAXNAME is defined in
	* "sqldb.h" as the maximum
	* length for names of database
	* objects, such as tables,
	* columns, and procedures.
	*/
	DBCHAR	type[TYPELEN+1];
	DBINT	id;

	DBCHAR	datebuf[64];
	DBINT	len;
	char	numstring[32];
	int	quitflag = 0;
	RETCODE	row_code;
	DBINT	rownum;

        dbinit();		/* initialize dblib */

	/* Install the user-supplied error-handling and message-handling
	* functions. They are defined at the bottom of this source file.
	*/
	dbmsghandle((DBMSGHANDLE_PROC)msg_handler);
	dberrhandle((DBERRHANDLE_PROC)err_handler);

	/*
	** Get a LOGINREC structure and fill it with the necessary
	** login information.
	*/

	login = dblogin();
	DBSETLUSER (login, "user");
	DBSETLPWD(login, "my_passwd");
	DBSETLAPP(login, "example4");
	DBSETLVERSION(login, DBVER60);

	dbproc = dbopen(login, "my_server");
	dbcmd(dbproc, "select name, type, id, crdate from sysobjects");
	dbcmd(dbproc, " where type = 'S'");

	/*
        ** Set row buffering to 100 rows, via dbsetopt().
	** Note that this parameter must be passed as an ASCII string.
	*/

	dbsetopt(dbproc, DBBUFFER, "100");
	dbsqlexec(dbproc);
	if (dbresults(dbproc) == SUCCEED)
	{
		/* Read all of the rows into DB-LIBRARY's buffer */
		while ((row_code = dbnextrow(dbproc)) != NO_MORE_ROWS)
		{
			/* If DB-LIBRARY's row buffer is full, throw
			* away the oldest row to allow the newest
			* row to be read in.
			*/
			if (row_code == BUF_FULL)
				dbclrbuf(dbproc, (DBINT) 1);
		}

		/* Print out the column headers. */

		puts("NAME                 TYPE DATE                   ID");
		puts("-------------------- ---- ---------------------- ----");


		/* Let the user view any row in the table. */

		printf("Type the number of the row you want to see.\n");
		printf("The first row is number 1.\n");
		printf("Asking for row 0 will terminate the program.\n");

		while (quitflag == 0)
		{
			printf("Row number: ");
			gets(numstring);
			rownum = atoi(numstring);

		if (rownum == 0)
			quitflag = 1;
		else
		{
			/* Print out the requested row. */
			if (dbgetrow(dbproc, rownum) == NO_MORE_ROWS)
				printf
				("That row is not in the table.\n");
			else
			{
				/* Copy variable-length character data
				* (colname).
					*/

				strncpy
				(name, (DBCHAR *)dbdata(dbproc, 1),
				(len = dbdatlen(dbproc, 1)));

				/* String needs terminating null. */

				name[len] = '\0';

				/* Copy fixed-length character data. */

				strncpy
				(type, (DBCHAR *)dbdata(dbproc, 2),
				(len = dbdatlen(dbproc, 2)));
				type[len] = '\0';

				/* Copy integer data. */
				id = *((DBINT *)dbdata(dbproc, 3));

				/* Convert datetime data to a printable
				* string.
				*/

				dbconvert(dbproc, SQLDATETIME, (dbdata(dbproc, 4)),
				(DBINT)-1, SQLCHAR, datebuf, (DBINT)-1);


				printf("%-20s %-4s %-22s %-4ld \n",
				name, type, datebuf, id);
				}
			}
		}
	}

	dbexit();
	return(STDEXIT);
}

int err_handler(dbproc, severity, dberr, oserr, dberrstr, oserrstr)
DBPROCESS	*dbproc;
int	severity;
int	dberr;
int	oserr;
char	*dberrstr;
char	*oserrstr;
{
    printf("DB-LIBRARY error:\n\t%s\n", dberrstr);

	if (oserr != DBNOERR)
		printf("Operating-system error:\n\t%s\n", oserrstr);

	if ((dbproc == NULL) || (DBDEAD(dbproc)))
		return(INT_EXIT);

	return(INT_CANCEL);
}

int msg_handler(dbproc, msgno, msgstate, severity, msgtext)
DBPROCESS	*dbproc;
DBINT	msgno;
int	msgstate;
int	severity;
char	*msgtext;
{
	printf
	("SQL Server message %ld, state %d, severity %d:\n\t%s\n",
	msgno, msgstate, severity, msgtext);
	return(0);
}

