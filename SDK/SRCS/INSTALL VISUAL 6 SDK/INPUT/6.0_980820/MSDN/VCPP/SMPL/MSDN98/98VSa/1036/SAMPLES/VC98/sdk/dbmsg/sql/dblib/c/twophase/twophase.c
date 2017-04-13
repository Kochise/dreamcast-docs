/*	Demo of Two-Phase Commit Service
**
**	This example uses the two-phase commit service
**	to perform a simultaneous update on two servers.
**	In this example, one of the servers participating
**	in the distributed transaction also functions as
**	the commit service.
**
**	In this particular example, the same update is
**	performed on both servers. You can, however, use
**	the commit server to perform completely different
**	updates on each server.
**
*/

#if defined(DBNTWIN32)
#include <windows.h>
#endif

#include <stdio.h>
#include <sqlfront.h>
#include <sqldb.h>

char	cmdbuf[256];
char	xact_string[128];

/* Forward declarations of the error handler and message handler. 
*/
int err_handler(DBPROCESS*, int, int, int, char*, char*);
int msg_handler(DBPROCESS*, DBINT, int, int, char*);
void abortall (DBPROCESS * dbproc_server1, DBPROCESS * dbproc_server2, DBPROCESS * dbproc_commit, DBINT commid);

void main(argv,argc)
int argc;
char *argv[];
{

	DBPROCESS	*dbproc_server1;
	DBPROCESS	*dbproc_server2;
	DBPROCESS	*dbproc_commit;
	LOGINREC	*login;
	DBINT	commid;

	RETCODE	ret_server1;
	RETCODE	ret_server2;

	// set error/msg handlers for this program
	dbmsghandle((DBMSGHANDLE_PROC)msg_handler);
	dberrhandle((DBERRHANDLE_PROC)err_handler);


	/* Open connections with the servers and the commit service. */
	printf("Demo of Two Phase Commit\n");
	login = dblogin();
	DBSETLUSER(login, "user");
	DBSETLPWD(login, "my_passwd");
	DBSETLAPP(login, "example");
	DBSETLVERSION(login, DBVER60);
    
	dbproc_server1 = dbopen (login, "my_server1");
	dbproc_server2 = dbopen (login, "my_server2");
	dbproc_commit = open_commit (login, "my_commitsrv");

	if (dbproc_server1 == NULL ||
		dbproc_server2 == NULL ||
		dbproc_commit	== NULL)
	{
		printf (" Connections failed!\n");
		exit (ERREXIT);
	}

	/* Use the "pubs" database. */
	dbuse(dbproc_server1, "pubs");
	dbuse(dbproc_server2, "pubs");

	/* Start the distributed transaction on the commit service. */
	commid = start_xact(dbproc_commit, "demo", "test", 2);

	/* Build the transaction name. */
	build_xact_string ("test", "my_commitsrv", commid, xact_string);

	/* Build the first command buffer. */
	sprintf(cmdbuf, "BEGIN TRANSACTION %s", xact_string);

	/* Begin the transactions on the different servers. */
	dbcmd(dbproc_server1, cmdbuf);
	dbsqlexec(dbproc_server1);
	dbcmd(dbproc_server2, cmdbuf);
	dbsqlexec(dbproc_server2);

	dbcancel(dbproc_server1);
	dbcancel(dbproc_server2);

	/* Do various updates. */
	sprintf(cmdbuf, " update titles set price = $1.50 where");
	strcat(cmdbuf, " title_id = 'BU1032'");
	dbcmd(dbproc_server1, cmdbuf);
	ret_server1 = dbsqlexec(dbproc_server1);
	dbcmd(dbproc_server2, cmdbuf);
	ret_server2 =dbsqlexec(dbproc_server2);
	if (ret_server1 == FAIL || ret_server2 == FAIL)
	{
		/* Some part of the transaction failed. */
		printf(" Transaction aborted -- dbsqlexec failed\n");
		abortall(dbproc_server1, dbproc_server2, dbproc_commit, commid);
	}

	dbcancel(dbproc_server1);
	dbcancel(dbproc_server2);

	/* Find out if all servers can commit the transaction. */
	sprintf(cmdbuf, "PREPARE TRANSACTION");
	dbcmd(dbproc_server1, cmdbuf);
	dbcmd(dbproc_server2, cmdbuf);
	ret_server1 = dbsqlexec(dbproc_server1);
	ret_server2 = dbsqlexec(dbproc_server2);
	if (ret_server1 == FAIL || ret_server2 == FAIL)
	{
		/* One or both of the servers failed to prepare. */
		printf(" Transaction aborted -- PREPARE failed\n");
		abortall(dbproc_server1, dbproc_server2, dbproc_commit, commid);
	}

	dbcancel(dbproc_server1);
	dbcancel(dbproc_server2);

	/* Commit the transaction. */
	if (commit_xact(dbproc_commit, commid) == FAIL)
	{
		/* The commit server failed to record the commit. */
		printf( " Transaction aborted -- commit_xact failed\n");
		abortall(dbproc_server1, dbproc_server2, dbproc_commit, commid);
		exit(ERREXIT);
	}

	/* The transaction has successfully committed.	Inform the servers. 
*/
	sprintf(cmdbuf, "COMMIT TRANSACTION");
	dbcmd(dbproc_server1, cmdbuf);
	if (dbsqlexec(dbproc_server1) != FAIL)
		remove_xact(dbproc_commit, commid, 1);
	dbcmd(dbproc_server2, cmdbuf);
	if (dbsqlexec(dbproc_server2) != FAIL)
		remove_xact(dbproc_commit, commid, 1);

	/* Close the connection to the commit server. */
	close_commit(dbproc_commit);

	printf( "We made it!\n");
	dbexit();
	exit(STDEXIT);
}

/* Function to abort the distributed transaction. */

void abortall( dbproc_server1, dbproc_server2, dbproc_commit, commid )
DBPROCESS	*dbproc_server1;
DBPROCESS	*dbproc_server2;
DBPROCESS	*dbproc_commit;
DBINT	commid;
{
	/* Some part of the transaction failed. */

	/* Inform the commit server of the failure. */
	abort_xact(dbproc_commit, commid);

	/* Roll back the transactions on the different servers. */
	sprintf(cmdbuf, "ROLLBACK TRANSACTION");
	dbcmd(dbproc_server1, cmdbuf);
	if (dbsqlexec(dbproc_server1) != FAIL)
		remove_xact(dbproc_commit, commid, 1);
	dbcmd(dbproc_server2, cmdbuf);
	if (dbsqlexec(dbproc_server2) != FAIL)
		remove_xact(dbproc_commit, commid, 1);

	dbexit();
	exit(ERREXIT);
}
/* Message and error handling functions. */
int msg_handler(dbproc,msgno,msgstate, severity, msgtext)
DBPROCESS	*dbproc;
DBINT	msgno;
int	msgstate;
int	severity;
char	*msgtext;
{
	/*	Msg 5701 is just a USE DATABASE message, so skip it.	*/
	if (msgno == 5701)
		return (0);
	/*	Print any severity 0 message as is, without extra stuff.	*/
	if (severity == 0)
	{
		printf ("%s\n",msgtext);
		return (0);
	}

	printf("SQL Server message %ld, severity %d:\n\t%s\n",
		msgno, severity, msgtext);

	if (severity >>= 16)
	{
		printf("Program Terminated! Fatal SQL Server error.\n");
		exit(ERREXIT);
	}
	return (0);
}

int err_handler(dbproc, severity, dberr, oserr, dberrstr, oserrstr)
DBPROCESS	*dbproc;
int	severity;
int	dberr;
int	oserr;
char	*dberrstr;
char	*oserrstr;
{
	if ((dbproc == NULL) || (DBDEAD(dbproc)))
		return (INT_EXIT);
	else
	{
		printf ("DB-LIBRARY error: \n\t%s\n", dberrstr);

		if (oserr != DBNOERR)
			printf ("Operating system error:\n\t%s\n", oserrstr);
	}
	return (INT_CANCEL);
}
