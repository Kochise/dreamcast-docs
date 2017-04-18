/*	example3.c */
/*
** This example selects some information from the "pubs" database.
** It illustrates binding of both aggregate and compute results.
**
** Note that this example only work if the "pubs" database exists
** on your SQL Server.
*/

#if defined(DBNTWIN32)
#include <windows.h>
#endif

#include <stdio.h>
#include <sqlfront.h>
#include <sqldb.h>

#define PLEN 4
#define DATEPRINT 26
#define MONEYPRINT 12

/* Forward declarations of the error handler and message handler.
*/
int	err_handler();
int	msg_handler();

main(argc,argv)
int	argc;
char	*argv[];
{
	LOGINREC	*login;
	DBPROCESS	*dbproc;

	/* Declare the datatypes for the columns in the table "titles". */
	DBINT	pcount;
	DBINT	sales;
	DBINT	salesavg;
	DBINT	sumsale;
	DBCHAR	date[DATEPRINT+1];
	DBCHAR	price[MONEYPRINT+1];
	DBCHAR	priceavg[MONEYPRINT+1];
	DBCHAR	pubid[PLEN+1];
	RETCODE	result_code; /* to hold the results of dbresults(). */
	STATUS	row_code;	/* to hold the results of dbnextrow(). */

        dbinit();		/* initialize dblib */


	/* Install the user-supplied error-handling and message-handling
	* functions. They are defined at the bottom of this source file.
	*/
	dbmsghandle((DBMSGHANDLE_PROC)msg_handler);
	dberrhandle((DBERRHANDLE_PROC)err_handler);

	/* Set up the login information. */

	login = dblogin();
	DBSETLUSER(login, "user");
	DBSETLPWD(login, "my_passwd");
	DBSETLAPP(login, "example3");
	DBSETLVERSION(login, DBVER60);

	dbproc = dbopen(login, "my_server");

	/* Send a "use database" command. */
	dbuse(dbproc,"pubs");

	/* Put the SQL statement into the command buffer. */
	dbcmd(dbproc, "select pub_id, pubdate, price, avg(price), ytd_sales,");
	dbcmd(dbproc, " avg(ytd_sales), sum(ytd_sales) from titles");
        dbcmd(dbproc, " group by pub_id, pubdate, price, ytd_sales");
	dbcmd(dbproc, " order by pub_id");
	dbcmd(dbproc, " compute count(pub_id) by pub_id");

	/* Send the command buffer to SQL Server for execution. */
	dbsqlexec(dbproc);

	/*
	** Using the aggregates "sum" and "avg" with the COMPUTE clause
	** necessitates special handling when binding the results. Since each
	** aggregate creates a new column, this is accounted for in the bind.
	** Notice that avg(price) is the fourth column in the select list
	** and is also specified as the fourth column in the dbbind() function.
	**
	** The COMPUTE clause creates a compute row, which requires a
	** special bind function called dbaltbind().
	*/

	while ((result_code = dbresults(dbproc)) != NO_MORE_RESULTS)
	{
		if (result_code == SUCCEED)
		{
			dbbind(dbproc,1,NTBSTRINGBIND, (DBINT) 0,pubid);
			dbbind(dbproc,2,NTBSTRINGBIND, (DBINT) 0,date);
			dbbind(dbproc,3,NTBSTRINGBIND, (DBINT) 0,price);
			dbbind(dbproc,4,NTBSTRINGBIND, (DBINT) 0,priceavg);
			dbbind(dbproc,5,INTBIND, (DBINT) 0, (BYTE *) &sales);
			dbbind(dbproc,6,INTBIND, (DBINT) 0, (BYTE *) &salesavg);
			dbbind(dbproc,7,INTBIND, (DBINT) 0, (BYTE *) &sumsale);

			/* dbaltbind() binds compute columns. */
			dbaltbind(dbproc,1,1,INTBIND,(DBINT) 0,(BYTE *)&pcount);

			printf("\nAccounts:\n");
			printf("---------\n\n");
			printf
			("%-5s	%-19s	%-6s	%-10s	%-5s	%-10s	%-10s\n\n",
			"pubid", "date", "price", "avg(price)",
			"sales", "avg(sales)", "sum(sales)");

			/*
			** Print out each result row, using different statements
			** depending on whether the row is a regular row or a
			** compute row.
			*/

			while ((row_code = dbnextrow(dbproc)) != NO_MORE_ROWS)
			{
				if (row_code == REG_ROW)
				{
					printf
				("%5s	%19s	%6s	%10s	%5ld	%10ld	%10ld\n",
				pubid, date, price, priceavg, sales,
				salesavg, sumsale);
				}
				else
				printf("title count:	%ld\n\n",pcount);
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


