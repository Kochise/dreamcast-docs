/* ** The example uses the following stored procedure, 
** named "rpctest", which it assumes is located in the 
** user's default database. Before running this example, 
** you must create "rpctest" in your default database.
**
**     create procedure rpctest
**         (@param1 int out,
**          @param2 int out,
**          @param3 int out,
**          @param4 int)
**     as
**     begin
**         select "rpctest is running."
**         select @param1 = 11
**         select @param2 = 22
**         select @param3 = 33
**         select @param1
**
**         return 123
**     end
**
*/

#if defined(DBNTWIN32)
#include <windows.h>
#endif

#include <stdio.h> 
#include <stdlib.h> 
#include <sqlfront.h> 
#include <sqldb.h> 
#define FMTSTR    "%-8.8s %-8.8s %-8.8s %-8.8s\n"
#define FMTSTR1    "%-8.8s %-8.8s %8.8ld %8.8ld\n"

/* Forward declarations of the error handler and message handler routines. */
int err_handler(DBPROCESS*, int, int, int, char*, char*);
int msg_handler(DBPROCESS*, DBINT, int, int, char*, char*, char*, DBUSMALLINT);

void main()
{
	LOGINREC         *login;
	DBPROCESS        *dbproc;
	
	int              i;
	int              numrets;
	DBINT            param1 = 1;
	DBINT            param2 = 2;
	DBINT            param3 = 3;
	DBINT            param4 = 4;
	RETCODE          return_code;

  	/* Initialize private DB Library structures. */
	dbinit();


	/* Install the user-supplied error-handling and message-handling
	 * routines. They are defined at the bottom of this source file.
	 */

	dbmsghandle((DBMSGHANDLE_PROC)msg_handler);
	dberrhandle((DBERRHANDLE_PROC)err_handler);

	/* Allocate and initialize the LOGINREC structure to be used
	 * to open a connection to SQL Server.
	 */

	login = dblogin( );
	DBSETLUSER(login, "user");
	DBSETLPWD(login, "my_passwd");
	DBSETLAPP(login, "rpcexample");
	DBSETLVERSION(login, DBVER60);

	dbproc = dbopen(login, (char *)"my_server");

	/* Make the rpc. */
	if (dbrpcinit(dbproc, "rpctest", (DBSMALLINT)0) == FAIL)
	{
		printf("dbrpcinit failed.\n");
		dbexit();
		exit(ERREXIT);
	}
	if (dbrpcparam(dbproc, "@param1", (BYTE)DBRPCRETURN, SQLINT4, 
		-1, -1, (BYTE *)&param1)
	   == FAIL)
	{
		printf("dbrpcparam failed.\n");
		dbexit();
		exit(ERREXIT);
	}

	if (dbrpcparam(dbproc, "@param2", (BYTE)DBRPCRETURN, SQLINT4, 
		-1, -1, 	(BYTE *)&param2)
	   == FAIL)
	{
		printf("dbrpcparam failed.\n");
		dbexit();
		exit(ERREXIT);
	}

	if (dbrpcparam(dbproc, "@param3", (BYTE)DBRPCRETURN, SQLINT4, 
			-1, -1, (BYTE *)&param3)
	   == FAIL)
	{
		printf("dbrpcparam failed.\n");
		dbexit();
		exit(ERREXIT);
	}

	if (dbrpcparam(dbproc, "@param4", (BYTE)NULL, SQLINT4, 
		-1, -1, (BYTE *)&param4)
	   == FAIL)
	{
		printf("dbrpcparam failed.\n");
		dbexit();
		exit(ERREXIT);
	}

	if (dbrpcsend(dbproc) == FAIL)
	{
		printf("dbrpcsend failed.\n");
		dbexit();
		exit(ERREXIT);
	}

	if (dbsqlok(dbproc) == FAIL)
	{
		printf("dbsqlok failed.\n");
		dbexit();
		exit(ERREXIT);
	}
	while ((return_code = dbresults(dbproc)) != NO_MORE_RESULTS)
	{
		if (return_code == FAIL)
		{
			printf("dbresults failed.\n");
			dbexit();
			exit(ERREXIT);
		}

		/* Print any rows that may have been returned. */
		dbprrow(dbproc);

		/* Examine any return parameters that may have arrived. */

		numrets = dbnumrets(dbproc);
		printf("%d return values received.\n\n", numrets);

		if (numrets != 0)
		{
			printf
			 (FMTSTR, "Name", "Type", "Length", "Value");
			printf
			 (FMTSTR,
				 "------------", "------------",
				 "------------", "------------");

   		for (i = 1; i <= numrets; i++)
 	   	{
		   	printf
			   	(FMTSTR1, dbretname(dbproc, i),
				   dbprtype(dbrettype(dbproc, i)), dbretlen(dbproc, i),
   				*((DBINT *)(dbretdata(dbproc, i))));
	   	}

		}
		if (dbhasretstat(dbproc))
			printf("Return status = %ld\n", dbretstatus(dbproc));
		else
			printf("No return status for this command.\n");
	}
	
	dbexit();
}
int err_handler(dbproc, severity, dberr, oserr, dberrstr, oserrstr)
DBPROCESS       *dbproc;
int             severity;
int             dberr;
int             oserr;
char            *dberrstr;
char            *oserrstr;
{
	if (dberrstr != NULL) 	printf("DB-Library error:\n\t%s\n", dberrstr);

	if (oserr != DBNOERR)
		printf("Operating-system error:\n\t%s\n", oserrstr);
	if ((dbproc == NULL) || (DBDEAD(dbproc)))
		return(INT_EXIT);
	else 
{

	return(INT_CANCEL);
}
}

int msg_handler(dbproc, msgno, msgstate, severity, msgtext,
srvname, procname, line)
DBPROCESS	*dbproc;
DBINT		msgno;
int			msgstate;
int			severity;
char		*msgtext;
char		*srvname;
char		*procname;
DBUSMALLINT	line;

{
	printf ("Msg %ld, Level %d, State %d\n", 
		msgno, severity, msgstate);

	if (srvname !=  NULL)
		printf ("Server '%s', ", srvname);
	if (procname !=  NULL)
		printf ("Procedure '%s', ", procname);
	if (line !=  0)
		printf ("Line %d", line);

	printf("\n\t%s\n", msgtext);

	return(0);
}
