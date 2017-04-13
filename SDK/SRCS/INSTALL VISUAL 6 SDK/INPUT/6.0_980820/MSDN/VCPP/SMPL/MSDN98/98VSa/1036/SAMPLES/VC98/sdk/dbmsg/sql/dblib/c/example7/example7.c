/*	example7.c */
/*
** This example illustrates the use of browse mode functions to
** determine the source of result columns from ad hoc queries.
*/

#if defined(DBNTWIN32)
#include <windows.h>
#endif

#include <stdio.h>
#include <sqlfront.h>
#include <sqldb.h>

void	examine_results();
BOOL send_command();

/* Forward declarations of the error-handling and message-handling
functions. */
int err_handler(DBPROCESS*, int, int, int, char*, char*);
int msg_handler(DBPROCESS*, DBINT, int, int, char*);

main()
{
	LOGINREC	*login;
	DBPROCESS	*dbproc;

	int	command_count = 0;
	RETCODE	retcode;

        dbinit();		/* initialize dblib */

	/* Install the user-supplied error-handling and message-handling
	* functions. They are defined at the bottom of this source file.
	*/
	dbmsghandle((DBMSGHANDLE_PROC)msg_handler);
	dberrhandle((DBERRHANDLE_PROC)err_handler);

	/* Allocate and initialize the LOGINREC structure to be used
	* to open a connection to SQL Server.
	*/

	login = dblogin();
	DBSETLUSER(login, "user");
	DBSETLPWD(login, "my_passwd");
	DBSETLAPP(login, "example7");
	DBSETLVERSION(login, DBVER60);

	dbproc = dbopen(login, "my_server");

	/* Allow the user to type in a series of queries. This program
	* is terminated by the word "quit" appearing at the
	* beginning of the line.
	*/
	while (1)
	{
		// Send a user-generated query to SQL Server.
		// Exit if user typed in quit.

		if (!send_command(dbproc))
			break;

		/* Now, examine the results of any queries the user has
		* typed in.
		*/

		command_count = 1;
		while ((retcode = dbresults(dbproc)) != NO_MORE_RESULTS)
		{
			command_count++ ;
			if (retcode == FAIL)
				printf("Command %d failed.\n", command_count);
			else
			{
				if (!(DBCMDROW(dbproc)))
					printf
				("Command %d returned no rows.\n",
				command_count);
				else
				{
				/* This is a command that can return
				* rows. Let's take a closer look at it.
				*/
				printf("Command %d:\n", command_count);
				examine_results(dbproc);

				/* Throw away all data rows. */
				dbcanquery(dbproc);
				}
			}
		}
	}

	return(STDEXIT);
}

void examine_results(dbproc)
DBPROCESS	*dbproc;
{
	int	colcount;
	int	colnum;
	char	fullsource[128];
	const char *sourcecolname;
	int	tabcount;
	const char *tabname;
	int	tabnum;

	/* Determine which tables were used to generate the query results.*/

	tabcount = dbtabcount(dbproc);
	printf
	("The following tables were used to generate these query results:\n");

	for (tabnum = 1; tabnum <= tabcount; tabnum++)
	{
	if ((tabname = dbtabname(dbproc, tabnum)) != NULL)
		printf
		("\t%s (%s)\n", tabname,
		(dbtabbrowse(dbproc, tabnum)
		? "browsable" : "not browsable"));
	}

	/* Determine which tables were used to generate each result column.*/

	colcount = dbnumcols(dbproc);
	printf("Here are the columns of the target list and their sources:\n");

	printf
	("\t%-20s	%-30s	%s\n\n",
	"Result column:", "Source:", "Browsable?");
	for (colnum = 1; colnum <= colcount; colnum++)
	{
	tabname = dbtabsource(dbproc, colnum, NULL);
	sourcecolname = dbcolsource(dbproc, colnum);

	if (tabname == NULL)
		strcpy(fullsource, "(result of expression)");
	else
		sprintf(fullsource, "%s.%s", tabname, sourcecolname);

	printf
	("\t%-20s	%-30s	%s\n",
	dbcolname(dbproc, colnum),
	fullsource,
	(dbcolbrowse(dbproc, colnum) ? "yes" : "no"));
	}
}


BOOL send_command(dbproc)
DBPROCESS	*dbproc;
{

	static char	cmdbuf[2048];

	/* Allow the user to type in an ad hoc query. This query
	* is terminated by the word "go" appearing at the
	* beginning of the line.
	*
	* If the user types the word "quit" at the beginning of a line,
	* we'll quit the program.
	*/
	printf("Enter SQL query (or 'quit'):\n");

	while (1)
	{
		printf("> ");
		gets(cmdbuf);

		if (strcmp(cmdbuf, "go") == 0)
		{
			dbsqlexec(dbproc);
			break;
		}
		else if (strcmp(cmdbuf, "quit") == 0)
		{
			return FALSE;
		}
		else
		{
			/* Keep reading SQL commands. */
			dbcmd(dbproc, cmdbuf);
		}
	}

	return TRUE;
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


