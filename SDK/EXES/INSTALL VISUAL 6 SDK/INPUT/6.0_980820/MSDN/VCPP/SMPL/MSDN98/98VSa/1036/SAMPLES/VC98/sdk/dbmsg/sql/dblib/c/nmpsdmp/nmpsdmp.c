// NMPSDMP.C
//
// DBLIB program for using named pipe dump devices for backup and restore data
// from SQL Server 95.This program is an example and shows the usage of named pipe
// dump devices on the client side.
//
//
// The program needs the following arguments (it asks from the user interactively) :
//	Operation	: DUMP/LOAD
//	Servername	: Name of the server to dump from/load into
//	Databasename: Name of the database to be dumped/loaded
//	Stripenum	: How many pipes are to be used for dump/load
//	Dumpname	: Prefix of the files to write/read the dumped/load data (DMP postfix)

#define DBNTWIN32
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <process.h>
#include <sqlfront.h>
#include <sqldb.h>

// definitions
#define MAX_DEVICES			32				// maximum number of stripe devices
#define PIPE_WAIT_TIME		500				// wait time in milliseconds
#define	DBPAGESIZE			2048			// size of physical page dumped

// status values for dump/load threads
#define STAT_SUCCESS		0x0				// default status
#define STAT_ERROR			0x1		  		// error in the current thread
#define STAT_ENDTHREAD		0x2				// the current thread has terminated

// opcode values
#define DUMP_MODE			0x1				// dump mode of operation
#define LOAD_MODE			0x2				// load mode of operation

// this structure is maintained on a global basis among all threads that
// are doing reads/writes from pipe
typedef struct ginfo
{
	char 	servername[30];	// server name
	char 	dbname[30];		// database name			
	char 	dumpname[80];	// dump file prefix
	char	password[30];	// dblogin password of SA
	long	status;			// global status flag for error recovery
	short	opcode;			// operation code
	short	stripenum;		// number of pipe devices to be used
} GINFO;

// this structure contains pipe specific info to be run by different threads
// that read/write data during the stripe dump/load
typedef struct pipeinfo
{
	char	pipename[80];	// Physical name of pipe used for client
	char	spipename[80];	// Physical name of pipe sent to SQL Server
	char	dumpname[80];	// Physical name of the dump file
	short	slot;			// which device slot
	GINFO	*curinfo;		// pointer to global info buffer
	long	status;			// thread local status		
} PIPEINFO;

// Macros
# define NEWARG(i)   	(*(argv[i]) == '-' || *(argv[i]) == '/')
# define BUFALIGN(a)    ( (BYTE *) ( ((long)a + 64) & 0xffffffc0) )


// function prototypes
void parse_parms(int argc, char *argv[], GINFO *curinfo);
void argvalue(int i, int argc, char* argv[], char* out);
int set_up_pipes(GINFO *curinfo, PIPEINFO **pipes);
void close_up_pipes(GINFO *curinfo, PIPEINFO **pipes);
void dump_proc(PIPEINFO	*curpipe);
void load_proc(PIPEINFO	*curpipe);
INT msg_handler(PDBPROCESS,DBINT,INT,INT,LPCSTR,LPCSTR,LPCSTR,DBUSMALLINT);
INT err_handler(PDBPROCESS,INT,INT,INT,LPCSTR,LPCSTR);

// start of the progam
main(int argc, char *argv[])
{

	RETCODE		retcode;				// DBLIB return code
	LOGINREC 	*loginrec = NULL;		// DBLIB LOGINREC pointer
	DBPROCESS 	*dbproc = NULL;			// DBLIB DBPROC pointer
	GINFO		info;					// to store global info & status
	PIPEINFO	*pipes[MAX_DEVICES];	// array of PIPEINFO pointers
	char		cmd[1024];				// SQL command buffer

   	// scratch variables
  	char		scratch[80];
	int			i;

  	// Initialize
	for (i=0; i<MAX_DEVICES; i++)
		pipes[i] = NULL;

	info.servername[0] = 0;
	info.dbname[0] = 0;
	info.dumpname[0] = 0;
	info.password[0] = 0;
	info.stripenum = 1;
	info.opcode = DUMP_MODE;
	info.status = STAT_SUCCESS;

	// read the user input
	parse_parms(argc, argv, &info);

	// Install the DBLIB handlers
	dberrhandle(err_handler);
	dbmsghandle(msg_handler);

	printf("Logging on to server...\n");

	loginrec = dblogin();
	DBSETLUSER(loginrec, "sa");
	DBSETLPWD(loginrec,"");

	if ((dbproc = dbopen(loginrec, info.servername)) == (DBPROCESS *)NULL)
	{
	  printf("dbopen() failed");
	  info.status |= STAT_ERROR;
	  goto clean_up;
	};

	// Set up the thread(s) for reading/writing the pipe device
	if (!set_up_pipes(&info, pipes))
	{
		info.status |= STAT_ERROR;
		goto clean_up;
	}

	// prepare the command now
	if (info.opcode == DUMP_MODE)
		strcpy(cmd, "dump database ");
	else
		strcpy(cmd, "load database ");
	strcat(cmd, info.dbname);
	if (info.opcode == DUMP_MODE)
		strcat(cmd, " to ");
	else
		strcat(cmd, " from ");
	for (i=0; i < info.stripenum; i++)
	{
		sprintf(scratch, "pipe = '%s'", &pipes[i]->spipename);
		strcat(cmd, scratch);
		if ((i+1) < info.stripenum)
			strcat(cmd, ", ");
	}
	printf("Command : <%s>\n", cmd);

	// this thread will be blocked till the dump/load command is not
	// completed; for changing the behavior to non blocking, use
	// dbsqlsend(), dbdataready() and dbsqlok() instead of dbsqlexec()
	retcode = dbcmd(dbproc, cmd);
    retcode = dbsqlexec(dbproc);

   	if (retcode != SUCCEED)
	{
		printf("dbsqlexec failed\n");
		info.status |= STAT_ERROR;
		goto clean_up;
	}

   	// discard results ; we do not need it
   	while (dbresults(dbproc) == SUCCEED)
    	while (dbnextrow(dbproc) != NO_MORE_ROWS)
			;

	// We are done with all the work ; clean up the resources and exit
	// strictly speaking, cleanup is not necessary for this since we
	// will exit the program (but for implementing this as a procedures
	// would involve cleanup)
clean_up:

	if (dbproc)
   		dbclose(dbproc);
	if (loginrec)
		dbfreelogin(loginrec);

	close_up_pipes(&info, pipes);
	exit(1);
    return(0);
}

// procedure to get all the parameters
void  parse_parms(int argc, char *argv[], GINFO *curinfo)
{
	int     i;
	char    argval[30];

	for (i = 0 ; i < argc; i++)
	{
		if (NEWARG(i))
		{
			switch(*(argv[i] + 1))
			{
				case 'S' : // Servername
					argvalue(i,argc,argv,curinfo->servername);
					break;

				case 'D' : // Databasename
					argvalue(i,argc,argv,curinfo->dbname);
					break;

				case 'P' : // SA password
					argvalue(i,argc,argv,curinfo->password);
					break;

				case 'N' : // Stripe Number
					argvalue(i,argc,argv,argval);
					if ((curinfo->stripenum = (short)atoi(argval)) < 1)
					{
						printf("Invalid value %d for stripe device. Setting to 1\n");
						curinfo->stripenum = 1;
					}
					else if (curinfo->stripenum > MAX_DEVICES)
					{
						printf("Invalid value %d for stripe device. Setting to %d\n",
								MAX_DEVICES);
						curinfo->stripenum = MAX_DEVICES;
					}
					break;

				case 'F' : // Dump file prefix
					argvalue(i,argc,argv,curinfo->dumpname);
					break;

				case 'O' : // Mode of operation
					argvalue(i,argc,argv,argval);
					if ( (!strcmp(argval, "DUMP")) || (!strcmp(argval, "dump")) )
						curinfo->opcode = DUMP_MODE;
					else if ( (!strcmp(argval, "LOAD")) || (!strcmp(argval, "load")) )
						curinfo->opcode = LOAD_MODE;
					else
					{
						printf("Invalid mode %s specified\n", argval);
						exit(1);
					}
					break;

				case '?' : // Help message
					printf("NMPSDMP -Sservername -Ppassword -O{dump | load} -Ddatabasename -Nstripenumber -Fdumpprefix\n");
					exit(1);
					break;

				default:
					printf("Invalid	parameter option : %s\n", *(argv[i] + 1) );
					printf("NMPSDMP -Sservername -Ppassword -O{dump | load} -Ddatabasename -Nstripenumber -Fdumpprefix\n");
					exit(1);
			}
		}
	}
	return;
}

// argument reading routine for parse_parms()
void argvalue(
    int   i,                           // parameter number
    int   argc,                        // #args
    char* argv[],                      // arglist
    char* out                          // receives parm 'i'
){
	if( *(argv[i]+2) )
		strcpy(out, argv[i]+2);
	else
	{
		if( i+1<argc && !( NEWARG(i+1) ) )
            strcpy(out, argv[i+1]);
	}
}

// procedure to setup all the threads for reading pipes
//
// return : 1 if success
//			0 otherwise
int set_up_pipes(GINFO *curinfo, PIPEINFO **pipes)
{
	
	int		i;
	PIPEINFO	*curpipe;
	char		pipebuf[30];

	// for every device
	for (i=0; i < curinfo->stripenum; i++)
	{
		// allocate for the current pipe
		if ((curpipe = malloc(sizeof(PIPEINFO))) == NULL)
			return 0;
		curpipe->slot = i;
		curpipe->curinfo = curinfo;
		curpipe->status = STAT_SUCCESS;

		// prepare the pipe name
		strcpy(curpipe->pipename, "\\\\");
		strcpy(curpipe->spipename, "\\\\");
		if (curinfo->servername[0])
			strcat(curpipe->pipename, curinfo->servername);
		else
			strcat(curpipe->pipename, ".");
		strcat(curpipe->spipename, ".");
		strcat(curpipe->pipename, "\\pipe\\");
		strcat(curpipe->spipename, "\\pipe\\");
		sprintf(pipebuf, "sqldmpld%d", i);
		strcat(curpipe->pipename, pipebuf);
		strcat(curpipe->spipename, pipebuf);

		// prepare the dump file name
		sprintf(curpipe->dumpname, "%s%d.dmp", curinfo->dumpname, i);

		// now start the thread for this device
		pipes[i] = curpipe;
		if (curinfo->opcode == DUMP_MODE)
		{
			if (!(_beginthread(dump_proc, 0, (LPVOID)curpipe)))
			{
				printf("beginthread failed for slot %d\n", i);
				return 0;
			}
		}
		else
		{
			if (!(_beginthread(load_proc, 0, (LPVOID)curpipe)))
			{
				printf("beginthread failed for slot %d\n", i);
				return 0;
			}
		}
	}

	// started all the threads
	return 1;
}

// procedure to close all the threads for reading/writing pipes
//
// return : nothing
//
void close_up_pipes(GINFO *curinfo, PIPEINFO **pipes)
{
	int			i;
	PIPEINFO	*curpipe;

	// check if we need to clean up
	if (!curinfo->stripenum)
		return;

	// for every open device
	for (i=0; i < curinfo->stripenum; i++)
	{
		if (!(curpipe = pipes[i]))
			continue;

		// wait for the thread to close itself
		while (!(curpipe->status & STAT_ENDTHREAD))
			SleepEx(10, TRUE);			

		// free the allocated memory
		free(curpipe);
	}
}

// DUMP_PROC
// 	This procedure does the opening and reading of dumped data sent
//	by the SQL Server. Each thread invoked with this routine services
//	one named pipe (instance) connection; for simplicity we are creating
//	separate named pipes for each stripe number.
//				
//	For dump process, the thread opens the pipe created by SQL Server
// 	and connects to it. Then keeps reading data and writing it
//	out to the dumpfile till the SQL Server is done.

void dump_proc(PIPEINFO	*curpipe)
{
	GINFO		*curinfo = curpipe->curinfo;
	HANDLE		hpipe = NULL;
	HANDLE		hfile = NULL;
	BYTE		*buf_start = NULL;
	BYTE		*buf_ptr;
	DWORD		bufsize, cbread, cbwritten, mode;
	DWORD		errcode = 0;
	DWORD		offl, offh;

	// Open the pipe
	while (1)
	{

		// check the global flag
		if (curinfo->status & STAT_ERROR)
			goto dump_proc_cleanup;

		hpipe = CreateFile(curpipe->pipename,
				GENERIC_READ | GENERIC_WRITE, 0, NULL,
				OPEN_EXISTING, FILE_FLAG_WRITE_THROUGH, NULL);

		// break if handle is valid
		if (hpipe != INVALID_HANDLE_VALUE)
			break;
		
		// check the pipe state
		errcode = GetLastError();
		if (errcode == ERROR_FILE_NOT_FOUND)
		{
			// SQL Server has not yet created the pipe; wait
			SleepEx(PIPE_WAIT_TIME, TRUE);
			continue;
		}
		else if (errcode != ERROR_PIPE_BUSY)
		{
			printf("Error in %s : %d\n", "CreateFile", errcode);
			curpipe->status |= STAT_ERROR;
			goto dump_proc_cleanup;
		}

		// Wait for sometime if pipe is busy
		if (!WaitNamedPipe(curpipe->pipename, PIPE_WAIT_TIME))
		{
			printf("Error in %s : %d\n", "WaitNamedPipe", GetLastError());
			curpipe->status |= STAT_ERROR;
			goto dump_proc_cleanup;
		}
	}
	
	printf("dump thread : %d : connected to server\n", curpipe->slot);
								
	// get the buffer size
	if ((!GetNamedPipeInfo(hpipe, NULL, NULL, &bufsize, NULL)) || (bufsize == 0))
	{
		printf("Error in %s : %d\n", "GetNamedPipeInfo", GetLastError());
		curpipe->status |= STAT_ERROR;
		goto dump_proc_cleanup;
	}

	// Align the buffer size to database pagesize if necessary
	if (bufsize % DBPAGESIZE)
		bufsize = ((bufsize / DBPAGESIZE) - 1) * DBPAGESIZE;
	//printf("dump thread : %d : buffer size %d \n", curpipe->slot, bufsize);

	// allocate the buffer for reading incoming data and align it
	if ((buf_start = malloc(bufsize + 64)) == NULL)
	{
		printf("malloc failed\n");
		curpipe->status |= STAT_ERROR;
		goto dump_proc_cleanup;
	}
	buf_ptr = BUFALIGN(buf_start);

	// Set the pipe mode to message read mode 
	mode = PIPE_READMODE_MESSAGE;
	if (!SetNamedPipeHandleState(hpipe, &mode, NULL, NULL))
	{
		printf("Error in %s : %d\n", "SetNamedPipeHandleState", GetLastError());
		curpipe->status |= STAT_ERROR;
		goto dump_proc_cleanup;
	}

	// open the dump file ; if it exists then overwrite it
	// otherwise open a new file
	hfile = CreateFile(curpipe->dumpname,
            GENERIC_READ | GENERIC_WRITE, 0, NULL,
            CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (hfile == INVALID_HANDLE_VALUE)
	{
		printf("Error in %s : %d\n", "CreateFile", GetLastError());
		curpipe->status |= STAT_ERROR;
		goto dump_proc_cleanup;
	}

	// set the file pointer to start of file
	offh = 0;
	if ((offl = SetFilePointer(hfile, 0, &offh, FILE_BEGIN)) == -1)
	{
		printf("Error in %s : %d\n", "SetFilePointer", GetLastError());
		curpipe->status |= STAT_ERROR;
		goto dump_proc_cleanup;
	}

	// now we are all set to read from the pipe; keep reading till the pipe is
	// closed.
	while (1)
	{
		// check the global flag
		if (curinfo->status & STAT_ERROR)
			goto dump_proc_cleanup;

		if (!ReadFile(hpipe, buf_ptr, bufsize, &cbread, NULL))
		{
			// Are we done reading
			if ((errcode = GetLastError()) == ERROR_BROKEN_PIPE)
				break;
			if (errcode != ERROR_MORE_DATA)
			{
				printf("Error in %s : %d\n", "ReadFile", errcode);
				curpipe->status |= STAT_ERROR;
				goto dump_proc_cleanup;
			}
		}
		//printf("dump thread : %d : read %d bytes\n", curpipe->slot, cbread);
		if (!WriteFile(hfile, buf_ptr, cbread, &cbwritten, NULL))
		{
			printf("Error in %s : %d\n", "WriteFile", GetLastError());
			curpipe->status |= STAT_ERROR;
			goto dump_proc_cleanup;
		}
	}

dump_proc_cleanup:

	// release the resources
	if (buf_start)
		free(buf_start);
	if (hfile)
	{
		FlushFileBuffers(hfile);
		CloseHandle(hfile);
	}
	if (hpipe)
		CloseHandle(hpipe);

	// set the status flags
	curpipe->status |= STAT_ENDTHREAD;
	if (curpipe->status & STAT_ERROR)
		curinfo->status |= STAT_ERROR;

	return;
}

// LOAD_PROC
// 	This procedure does the opening and writing of dumped data sent
//	to the SQL Server. Each thread invoked with this routine services
//	one named pipe (instance) connection; we are create
//	separate named pipes for each stripe number.
//				
//	For load process, the thread opens the pipe created by SQL Server
// 	and connects to it. Then keeps reading data from the dumpfile till end
//  and writes to the pipe; Finally closes the pipe when done.

void load_proc(PIPEINFO	*curpipe)
{
	GINFO		*curinfo = curpipe->curinfo;
	HANDLE		hpipe = NULL;
	HANDLE		hfile = NULL;
	BYTE		*buf_start = NULL;
	BYTE		*buf_ptr;
	DWORD		bufsize, cbread, cbwritten, mode;
	DWORD		errcode = 0;
	DWORD		offl, offh;

	// Open the pipe
	while (1)
	{

		// check the global flag
		if (curinfo->status & STAT_ERROR)
			goto load_proc_cleanup;

		hpipe = CreateFile(curpipe->pipename,
				GENERIC_READ | GENERIC_WRITE, 0, NULL,
				OPEN_EXISTING, FILE_FLAG_WRITE_THROUGH, NULL);

		// break if handle is valid
		if (hpipe != INVALID_HANDLE_VALUE)
			break;
		
		// check the pipe state
		errcode = GetLastError();
		if (errcode == ERROR_FILE_NOT_FOUND)
		{
			// SQL Server has not yet created the pipe; wait
			SleepEx(PIPE_WAIT_TIME, TRUE);
			continue;
		}
		else if (errcode != ERROR_PIPE_BUSY)
		{
			printf("Error in %s : %d\n", "CreateFile", errcode);
			curpipe->status |= STAT_ERROR;
			goto load_proc_cleanup;
		}

		// Wait for sometime if pipe is busy
		if (!WaitNamedPipe(curpipe->pipename, PIPE_WAIT_TIME))
		{
			printf("Error in %s : %d\n", "WaitNamedPipe", GetLastError());
			curpipe->status |= STAT_ERROR;
			goto load_proc_cleanup;
		}
	}

	printf("load thread : %d : connected to server\n", curpipe->slot);
								
	// get the buffer size
	if ((!GetNamedPipeInfo(hpipe, NULL, NULL, &bufsize, NULL)) || (bufsize == 0))
	{
		printf("Error in %s : %d\n", "GetNamedPipeInfo", GetLastError());
		curpipe->status |= STAT_ERROR;
		goto load_proc_cleanup;
	}

	// Align the buffer size to database pagesize if necessary
	if (bufsize % DBPAGESIZE)
		bufsize = ((bufsize / DBPAGESIZE) - 1) * DBPAGESIZE;
	//printf("load thread : %d : buffer size %d \n", curpipe->slot, bufsize);

	// allocate the buffer for reading incoming data and align it
	if ((buf_start = malloc(bufsize + 64)) == NULL)
	{
		printf("malloc failed\n");
		curpipe->status |= STAT_ERROR;
		goto load_proc_cleanup;
	}
	buf_ptr = BUFALIGN(buf_start);

	// Set the pipe mode to message read mode 
	mode = PIPE_READMODE_MESSAGE;
	if (!SetNamedPipeHandleState(hpipe, &mode, NULL, NULL))
	{
		printf("Error in %s : %d\n", "SetNamedPipeHandleState", GetLastError());
		curpipe->status |= STAT_ERROR;
		goto load_proc_cleanup;
	}

	// open the dump file ; it should exist
	hfile = CreateFile(curpipe->dumpname,
            GENERIC_READ | GENERIC_WRITE, 0, NULL,
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hfile == INVALID_HANDLE_VALUE)
	{
		printf("Error in %s : %d\n", "CreateFile", GetLastError());
		curpipe->status |= STAT_ERROR;
		goto load_proc_cleanup;
	}

	// set the file pointer to start of file
	offh = 0;
	if ((offl = SetFilePointer(hfile, 0, &offh, FILE_BEGIN)) == -1)
	{
		printf("Error in %s : %d\n", "SetFilePointer", GetLastError());
		curpipe->status |= STAT_ERROR;
		goto load_proc_cleanup;
	}

	//
	// Read the first page and write it to the pipe
	//
	if ((!ReadFile(hfile, buf_ptr, DBPAGESIZE, &cbread, NULL)) || 
			(cbread != DBPAGESIZE))
	{
		printf("Error in %s : %d\n", "ReadFile", GetLastError());
		curpipe->status |= STAT_ERROR;
		goto load_proc_cleanup;
	}
	if (!WriteFile(hpipe, buf_ptr, DBPAGESIZE, &cbwritten, NULL))
	{
		printf("Error in %s : %d\n", "WriteFile", errcode);
		curpipe->status |= STAT_ERROR;
		goto load_proc_cleanup;
	}
	//printf("load thread : %d : wrote %d bytes\n", curpipe->slot, cbwritten);

	// now we are all set to read from the dumpfile; keep reading till we reach
	// the end of dumpfile
	while (1)
	{
		// check the global flag
		if (curinfo->status & STAT_ERROR)
			goto load_proc_cleanup;

		// read from the dump file
		if (!ReadFile(hfile, buf_ptr, bufsize, &cbread, NULL))
		{
			// check if we are done reading
			if ((errcode = GetLastError()) == ERROR_HANDLE_EOF)
				break;

			printf("Error in %s : %d\n", "ReadFile", GetLastError());
			curpipe->status |= STAT_ERROR;
			goto load_proc_cleanup;
		}

		// Done reading the dump file
		if (cbread == 0)
			break;

		// write to the pipe
		if (!WriteFile(hpipe, buf_ptr, cbread, &cbwritten, NULL))
		{
			printf("Error in %s : %d\n", "WriteFile", GetLastError());
			curpipe->status |= STAT_ERROR;
			goto load_proc_cleanup;
		}
		//printf("load thread : %d : wrote %d bytes\n", curpipe->slot, cbwritten);
	}

load_proc_cleanup:

	// release the resources
	if (buf_start)
		free(buf_start);
	if (hfile)
		CloseHandle(hfile);
	if (hpipe)
	{
		FlushFileBuffers(hpipe);
		CloseHandle(hpipe);
	}

	// set the status flags
	curpipe->status |= STAT_ENDTHREAD;
	if (curpipe->status & STAT_ERROR)
		curinfo->status |= STAT_ERROR;

	return;
}


INT msg_handler(dbproc,msgno,msgstate, severity, msgtext,server,proc,line)
PDBPROCESS	 dbproc;
DBINT		 msgno;
INT	 msgstate;
INT	 severity;
LPCSTR		msgtext;
LPCSTR	server;
LPCSTR	proc;
DBUSMALLINT line;
{
   if (severity)
      printf("\nDB-LIB message: %s \n", msgtext);
   return (0);
};

INT err_handler(dbproc,	severity, herrno, oserr, dberrstr, oserrstr)
PDBPROCESS	 dbproc;
INT	    severity;		
INT		 herrno;
INT		 oserr;			
LPCSTR	 dberrstr;
LPCSTR	 oserrstr;
{
	if (severity)
      printf("\nDB-LIBRARY error: %s \n", dberrstr);
    return (INT_CANCEL);
};
