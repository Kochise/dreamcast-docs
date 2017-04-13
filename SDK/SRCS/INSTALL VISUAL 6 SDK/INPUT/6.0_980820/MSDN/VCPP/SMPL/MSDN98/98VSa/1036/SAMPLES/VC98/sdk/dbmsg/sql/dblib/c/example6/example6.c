/*	example6.c */
/*
** This example illustrates opening a data file, inserting data
** from the file into a newly created table containing several
** SQL Server datatypes, and updating the table using browse mode
** techniques.
*/

#if defined(DBNTWIN32)
#include <windows.h>
#endif

#include <stdio.h>
#include <sqlfront.h>
#include <sqldb.h>

#define BUFLEN 2048

/* Forward declarations of the error-handling and message-handing
functions. */
int err_handler(DBPROCESS*, int, int, int, char*, char*);
int msg_handler(DBPROCESS*, DBINT, int, int, char*);

main()
{
	LOGINREC	*login;
	DBPROCESS	*q_dbproc;	/* This DBPROCESS is used to
	* query the database.
	*/
	DBPROCESS	*u_dbproc;	/* This DBPROCESS is used to
	* simultaneously update the database.
	*/
	const char  *qualptr;	/* This points to the WHERE clause
	* appropriate for updating q_dbproc's
	* current data row.
	*/
	RETCODE	return_code;
	DBTINYINT	age;
	static char	cmdbuf[BUFLEN];
	FILE	*infile;

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
	DBSETLAPP(login, "example6");
	DBSETLVERSION(login, DBVER60);

	q_dbproc = dbopen(login, "my_server");
	u_dbproc = dbopen(login, "my_server");

	printf("Creating the 'alltypes' table.\n");

	/* Create a table that contains several SQL Server datatypes. */
	dbcmd(q_dbproc,"if exists(select name from sysobjects where name='alltypes') drop table alltypes ");

	dbcmd(q_dbproc,"create table alltypes ");
	dbcmd(q_dbproc,"(age tinyint,");
	dbcmd(q_dbproc,"userid smallint,");
	dbcmd(q_dbproc,"royalty int,");
	dbcmd(q_dbproc,"name char(25),");
	dbcmd(q_dbproc,"title_id varbinary(20),");
	dbcmd(q_dbproc,"us_citizen bit,");
	dbcmd(q_dbproc,"account float,");
	dbcmd(q_dbproc,"title varchar(20),");
	dbcmd(q_dbproc,"manager char(25),");
	dbcmd(q_dbproc,"sales decimal(10,2),");
	dbcmd(q_dbproc,"timestamp)");

	dbcmd(q_dbproc, "create unique index index1 on alltypes(userid)");

	dbsqlexec(q_dbproc);
	while (dbresults(q_dbproc) != NO_MORE_RESULTS)
	continue;

	/* Insert rows of data into the newly created table "alltypes".
	* We will read in the contents of the file and form an
	* INSERT statement.
	*/

	if ((infile=fopen("datafile","r")) == NULL)
	{
		printf("Unable to open file 'datafile'.\n");
		return(STDEXIT);
	}

	printf("Inserting rows into the 'alltypes' table...\n");

	while ((fgets(cmdbuf,BUFLEN,infile)) != NULL)
	{
		dbfcmd(q_dbproc,"insert into alltypes \n");
		dbfcmd(q_dbproc,"values(%s, null) \n",cmdbuf);
	}

	dbsqlexec(q_dbproc);

	/* Process the results of each of the INSERT statements. */

	while ((return_code = dbresults(q_dbproc)) != NO_MORE_RESULTS)
	{
		if (return_code == FAIL)
			printf("One of the insert statements failed.\n");
	}

	/* Using DB-LIBRARY's browse mode facilities, we'll increment
	* the age of every person in the table.
	*/

	printf("Updating rows in the 'alltypes' table...\n");

	dbcmd(q_dbproc,"select * from alltypes for browse");
	dbsqlexec(q_dbproc);

	while ((return_code = dbresults(q_dbproc)) != NO_MORE_RESULTS)
	{
		if (return_code == SUCCEED)
		{
			while (dbnextrow(q_dbproc) != NO_MORE_ROWS)
			{
				age = *((DBTINYINT *)(dbdata(q_dbproc, 1)));
				qualptr = dbqual(q_dbproc, -1, "alltypes");
				dbcmd(u_dbproc, "update alltypes");
				dbfcmd
				(u_dbproc, " set age = %d %s", age+1, qualptr);
				dbsqlexec(u_dbproc);
				dbresults(u_dbproc);
				dbfreequal(qualptr);
			}
		}
	}

	/* Now, we'll look at the updated contents of the table to
	* verify that the ages were properly incremented.
	*/
	printf("Selecting rows from the 'alltypes' table:\n");
	dbcmd(q_dbproc, "select * from alltypes");
	dbsqlexec(q_dbproc);
	dbresults(q_dbproc);
	dbprrow(q_dbproc);

	printf("Dropping 'alltypes' table:\n");
	dbcmd(q_dbproc, "drop table alltypes");
	dbsqlexec(q_dbproc);
	dbresults(q_dbproc);

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
