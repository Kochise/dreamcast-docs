/*	example2.c */
/*
** This example opens a data file, inserts data from the file
** into a newly created table containing several of the
** SQL Server datatypes, and binds and prints the results.
** You must have a file named datafile and CREATE DATABASE
** permission in your login database.  Also you must have enough room
** in your default device to create a new database (minimum 2Mb).
*/

#if defined(DBNTWIN32)
#include <windows.h>
#endif

#include <stdio.h>
#include <sqlfront.h>
#include <sqldb.h>

#define BUFLEN	2048
#define HEXLEN	510
#define PLEN	25
#define SALESLEN 11

/* Forward declarations of the error handler and message handler functions.
*/
int err_handler(DBPROCESS*, int, int, int, char*, char*);
int msg_handler(DBPROCESS*, DBINT, int, int, char*);

main(argc,argv)
int	argc;
char	*argv[];
{

	LOGINREC	*login;
	DBPROCESS	*dbproc;
	RETCODE	return_code;

	DBTINYINT	age;
	DBSMALLINT	userid;
	DBINT	royalty;
	DBCHAR	name[PLEN+1];
	DBBINARY	title_id[PLEN+1];
	DBBIT	us_citizen;
	DBFLT8	account;
	DBCHAR	title[PLEN+1];	/* string	*/
	DBCHAR	manager[PLEN+1];	/* ntbstring */
	DBCHAR	id_buffer[HEXLEN+1];
	DBCHAR   sales_buffer[SALESLEN+1];
	DBDECIMAL sales;

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
	DBSETLAPP(login, "example2");
	DBSETLVERSION(login, DBVER60);

	dbproc = dbopen(login, "my_server");
	printf("Creating the 'test' database.\n");
	dbcmd(dbproc,"create database test ");
	dbsqlexec(dbproc);
	dbresults(dbproc);
	dbuse(dbproc,"test");
	printf("Creating the 'alltypes' table.\n");

	/* Create a table that contains several SQL Server datatypes. */
	dbcmd(dbproc,"create table alltypes ");
	dbcmd(dbproc,"(age tinyint,");
	dbcmd(dbproc,"userid smallint,");
	dbcmd(dbproc,"royalty int,");
	dbcmd(dbproc,"name char(25),");
	dbcmd(dbproc,"title_id varbinary(20),");
	dbcmd(dbproc,"us_citizen bit,");
	dbcmd(dbproc,"account float,");
	dbcmd(dbproc,"title varchar(20),");
	dbcmd(dbproc,"manager char(25),");
	dbcmd(dbproc,"sales decimal(10,2))");
	dbsqlexec(dbproc);
	dbresults(dbproc);

	/* Insert rows of data into the newly created table "alltypes".
	* We will read in the contents of the file and form an
	* INSERT statement.
	*/

	if ((infile=fopen("datafile","r")) == NULL)
	{
		printf("Unable to open file 'datafile'.\n");
		return(STDEXIT);
	}

	printf("Inserting rows into the 'alltypes' table.\n");

	while ((fgets(cmdbuf,BUFLEN,infile)) != NULL)
	{
		dbfcmd(dbproc,"insert into alltypes \n");
		dbfcmd(dbproc,"values(%s) \n",cmdbuf);
	}
	dbsqlexec(dbproc);

	/* Process the results of each of the INSERT statements. */
	while ((return_code = dbresults(dbproc)) != NO_MORE_RESULTS)
	{
		if (return_code == FAIL)
			printf("One of the insert statements failed.\n");
	}
	printf("Selecting rows from the 'alltypes' table:\n");
	dbcmd(dbproc,"select * from alltypes");
	dbsqlexec(dbproc);

	/* Initialize the DBDECIMAL structure so binding and conversions will use defaults */
	sales.precision = 0;
	sales.scale = 0;

	while ((return_code = dbresults(dbproc)) != NO_MORE_RESULTS)
	{
		if (return_code == SUCCEED)
		{
			dbbind(dbproc,1,TINYBIND, (DBINT) 0,(BYTE *) &age);
			dbbind(dbproc,2,SMALLBIND, (DBINT) 0,(BYTE *) &userid);
			dbbind(dbproc,3,INTBIND, (DBINT) 0,(BYTE *) &royalty);
			dbbind(dbproc,4,CHARBIND, (DBINT) 0,name);
			dbbind(dbproc,5,BINARYBIND, (DBINT) 0,title_id);
			dbbind(dbproc,6,BITBIND, (DBINT) 0,(BYTE *) &us_citizen);
			dbbind(dbproc,7,FLT8BIND, (DBINT) 0,(BYTE *) &account);
			dbbind(dbproc,8,STRINGBIND, (DBINT) 0,title);
			dbbind(dbproc,9,NTBSTRINGBIND, (DBINT) 0,manager);
			dbbind(dbproc,10,DECIMALBIND, (DBINT) 0, (BYTE *)&sales);

			/*
			** Initialize null terminator in "name" array,
			** since CHARBIND does not add one.
			*/
			name[PLEN] = '\0';

			while (dbnextrow(dbproc) != NO_MORE_ROWS)
			{
				dbconvert (dbproc, SQLBINARY, title_id, dbdatlen(dbproc, 5), SQLCHAR, id_buffer, (DBINT)-1);
				dbconvert (dbproc, SQLDECIMAL, (BYTE *)&sales, sizeof(DBDECIMAL), SQLCHAR, sales_buffer, (DBINT)-1);

				printf
				("%d	%d	%ld	%s	0x%s\n",
				age, userid, royalty, name, id_buffer);
				printf
				("%d	%8.2f	%s	%s %s\n",
				us_citizen, account, title, manager, sales_buffer);
				
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

