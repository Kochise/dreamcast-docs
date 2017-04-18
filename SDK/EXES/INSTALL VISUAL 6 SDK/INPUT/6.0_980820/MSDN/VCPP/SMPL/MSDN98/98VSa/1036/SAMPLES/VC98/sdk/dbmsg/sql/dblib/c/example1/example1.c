/*	example1.c */
/*
**	This example illustrates how to send two queries to
**	SQL Server in a command batch.	It binds each set
**	of results and prints the rows.
**
*/

#if defined(DBNTWIN32)
#include <windows.h>
#endif

#include <stdio.h>
#include <sqlfront.h>
#include <sqldb.h>

#define DATELEN	26
#define TYPELEN	2

/* Forward declarations of the error handler and message handler.
*/
int err_handler(DBPROCESS*, int, int, int, char*, char*);
int msg_handler(DBPROCESS*, DBINT, int, int, char*);

main(argc, argv)
int	argc;
char	*argv[];
{
	DBPROCESS	*dbproc;	/* Our connection with SQL Server. */
	LOGINREC	*login;	/* Our login information. */

	/* These are the variables used to store the returning data. */

	DBCHAR	crdate[DATELEN+1];
	DBINT	id;
	DBCHAR	name[MAXNAME+1];	/* MAXNAME is defined in
	* "sqldb.h" as the maximum
	* length for names of database
	* objects, such as tables,
	* columns, and procedures.
	*/
	DBCHAR	type[TYPELEN+1];
	RETCODE	result_code;

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
	DBSETLUSER(login, "user");
	DBSETLPWD(login, "my_passwd");
	DBSETLAPP(login, "example1");
	DBSETLVERSION(login, DBVER60);

	/*
	** Get a DBPROCESS structure for communicating with SQL Server.
	*/

	dbproc = dbopen(login, "my_server");

	/*
	** We are going to retrieve some information from a table
	** named "sysobjects", regarding names of system tables and
	** stored procedures.
	** We will submit two queries.	The first finds all the rows
	** that describe system tables.	The second finds all the rows
	** that describe stored procedures.	The program will only look
	** at the first 10 rows that describe stored procedures.
	*/

	/* First, put the commands into the command buffer. */

	dbcmd(dbproc, "select name, type, id, crdate from sysobjects");
	dbcmd(dbproc, " where type = 'S' ");
	dbcmd(dbproc, "select name, type, id, crdate from sysobjects");
	dbcmd(dbproc, " where type = 'P' ");

	/*
	** SQL Server processes the command batch in the following
	** order:
	**
	** 1)	It checks for syntax errors (i.e., "use database pubs"
	**		is syntactically incorrect; it should be "use pubs").
	** 2)	The second check is a semantic check (i.e., "select * from
	**		titels" is incorrect because the spelling should be
	**		"titles".)
	** 3) The third check occurs in the actual execution phase. This
	**	check involves issues like permissions or memory problems.
	**
	** In the execution phase, dbsqlexec() and dbresults() can return
	** the value "SUCCEED", which means there are more commands in the
	** batch to process and that command was successful. A value
	** of "FAIL" means that the query failed but there may be more
	** commands in the batch to process. A value of "NO_MORE_RESULTS"
	** means that there are no more commands in the batch to process.
	** Therefore, the programmer must check the return values after
	** dbsqlexec() and dbresults(), as illustrated below.
	**
	*/

	/* Send the commands to SQL Server and start execution. */
	dbsqlexec(dbproc);

	/* Process each command until there are no more. */

	while ((result_code = dbresults(dbproc)) != NO_MORE_RESULTS)
	{
		if (result_code == SUCCEED)
		{
			/* Bind program variables. */

			dbbind(dbproc, 1, NTBSTRINGBIND, (DBINT) 0, name);
			dbbind(dbproc, 2, NTBSTRINGBIND, (DBINT) 0, type);
			dbbind(dbproc, 3, INTBIND, (DBINT) 0, (BYTE *) &id);
			dbbind(dbproc, 4, NTBSTRINGBIND, (DBINT) 0, crdate);

			/* Print appropriate header for the type of
			* data coming back.
			*/

			printf("\n %s Objects: \n\n",
			DBCURCMD(dbproc) == 1 ? "System Table": "Procedure");

			/* Now print the rows. */

			while (dbnextrow(dbproc) != NO_MORE_ROWS)
			{
				/*
				** If this is the 2nd command and
				** 10th row, flush the rest of the
				** rows for that command.
				*/

				if ((DBCURCMD(dbproc) == 2)
				&& (DBCURROW(dbproc) > 10))
							    	continue;

				printf
				("%s %s %ld %s\n", name, type, id, crdate);
			}
		}
	}


	/* Close our connection and exit the program. */

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


