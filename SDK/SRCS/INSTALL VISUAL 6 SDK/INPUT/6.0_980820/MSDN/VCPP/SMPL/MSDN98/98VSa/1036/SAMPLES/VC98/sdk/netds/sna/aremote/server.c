/*
Copyright (c) 1994, 1993 Microsoft Corporation

Module Name:
    Server.c

Abstract:
    The server component of Remote. It spawns a child process
    and redirects the stdin/stdout/stderr of child to itself.
    Waits for connections from clients - passing the
    output of child process to client and the input from clients
    to child process.

Author:
    Rajivendra Nath (rajnath) 2-Jan-1993

Environment:
    Console App. User mode.

Revision History:
	Alex Wetmore (t-alexwe) 6-Jun-1994
		- converted remote to use APPC with Windows SNA Server instead of named
		  pipes
		- converted to use Unicode
*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include <winappc.h>
#include "appclib.h"
#include "aremote.h"

#define COMMANDFORMAT       TEXT("%c%-15s    [%-15s %d:%d]\n%c")
#define RemoteInfo(prt,flg) {if (!(flg&0x80000000)) prt;}

#define CMDSTRING(OutBuff,InpBuff,Client,sTime) \
        {                                \
            /* int xxlen; */             \
            wsprintf                      \
            (                            \
               &OutBuff[0],COMMANDFORMAT,\
               BEGINMARK,InpBuff,        \
               Client->Name,sTime.wHour, \
               sTime.wMinute,ENDMARK     \
            );                           \
         }

#define BUFFSIZE      1024

SESSION_TYPE ClientList[MAX_SESSION];

HANDLE  ChildStdInp;     //Server Writes to  it
HANDLE  ChildStdOut;     //Server Reads from it
HANDLE  ChildStdErr;     //Server Reads from it

HANDLE  SaveFile;       //File containing all that was
                        //output by child process.
                        //Each connection opens a handle to this file
                        //and is sent through PipeWriteH.

TCHAR   SaveFileName[64]; //Name of above file - all new sessions need
HANDLE  ChldProc;         //Handle to the Child Process
HANDLE  ListenThreadH;    //Handle to the thread listening for connections
                          //from Remote Clients.
extern 	BOOL AutoStarted;		// true if this is an autostarted service

CRITICAL_SECTION	close_crit;	// critical section for closing

HANDLE
ForkChildProcess(          // Creates a new process
    TCHAR *cmd,             // Redirects its stdin,stdout
    PHANDLE in,            // and stderr - returns the
    PHANDLE out,           // corresponding pipe ends. Using currently
    PHANDLE err
    );

DWORD WINAPI
ListenForSession(          //THREAD:Listens for new connections and
    TCHAR* pipe             //spawns of new seesions - Updates the
    );                     //Status in Client DataStructure. Seperate Thread.

//
// threads for dealing with local session (only when non-autostarted)
DWORD WINAPI LocalSession(SESSION_TYPE *cli);
DWORD WINAPI StdoutThread(SESSION_TYPE *cli);
DWORD WINAPI StdinThread(SESSION_TYPE *cli);

BOOL
CreateMySecurityDescriptor(                    //
    PSECURITY_DESCRIPTOR pSecurityDescriptor,  // Creates a security descriptor
    TCHAR *Owner                                // with discretionary access for
    );                                         // access for Owner.


DWORD
NewSession(                //Manages the session with a client.
    SESSION_TYPE* Client
    );

DWORD WINAPI               //2 THREAD:Each reads either
GetChldOutput(             //StdOut or StdErr of child and
    HANDLE rhandle         //writes to SaveFile. Seperate Thread.
    );

DWORD WINAPI
TransferFileToClient(      //X THREADS:Reads the save
    SESSION_TYPE* Client   //file and sendsoutput to a client. Seperate Thread
    );


DWORD WINAPI
GetClientInput(            //Times X THREADS:Gets input from Child pipe
    SESSION_TYPE* Client   //and sends to childs StdIn. Seperate Thread.
    );


BOOL
FilterCommand(             //Filters input from client
    SESSION_TYPE *cl,      //for commands intended for REMOTE
    TCHAR *buff,
    int dread
    );

DWORD WINAPI               // Manages the IO with Remote Client.
RemoteSession(
    SESSION_TYPE* Client
    );

BOOL                       // Ctrl-C handler
SrvCtrlHand(
    DWORD event
    );

VOID                       // @s command to remote
SendStatus(
    tpconvid_t tpconv
    );

DWORD WINAPI               // @p command to remote
ShowPopup(
    TCHAR *mssg
    );

VOID                       // Removes the command begin and end markers
RemoveInpMark(             // from the save file.
    char* Buff,
    DWORD Size
    );

VOID                       // Cleans up the session
CloseClient(               // once it ends.
    SESSION_TYPE *Client
    );
                           // Initialises the Client datastructs
VOID
InitClientList(
    );


/*************************************************************/
/* The main entry point for the Server End of Remote         */
/*************************************************************/
VOID Server(TCHAR* ChildCmd, TCHAR *tp_name) {
    DWORD  ThreadID ;
    HANDLE WaitH[3], objs[MAX_SESSION];
    DWORD  WaitObj;
    TCHAR  tmpdir[32];
	int    i, active;

    WRITEF((VBuff, TEXT("**************************************\n")));
    WRITEF((VBuff, TEXT("***********     REMOTE    ************\n")));
    WRITEF((VBuff, TEXT("***********     SERVER    ************\n")));
    WRITEF((VBuff, TEXT("**************************************\n")));

    InitClientList();

	appcinit();

	//
	// This critical section is used around close so that only one appcclose
	// is happening at a time.
	//
	InitializeCriticalSection(&close_crit);

    //
    //Start the command as a child process
    //

    ChldProc=ForkChildProcess(ChildCmd,&ChildStdInp,&ChildStdOut,&ChildStdErr);

    //
    //Create a tempfile for storing Child process output.
    //
    {
         DWORD size=sizeof(tmpdir);
         if (
             (GetEnvironmentVariable(TEXT("TMP"),tmpdir,size)==0)&&
             (GetEnvironmentVariable(TEXT("TEMP"),tmpdir,size)==0)
            )
         {
            wsprintf(tmpdir,TEXT("%ws"),TEXT("."));
         }
         if (!GetTempFileName(tmpdir,TEXT("REMOTE"),0,SaveFileName))
            GetTempFileName(TEXT("."),TEXT("REMOTE"),0,SaveFileName);
    }


    if ((SaveFile=CreateFile
                  (
                     (LPCTSTR)SaveFileName,           /* address of name of the file  */
                     GENERIC_READ|GENERIC_WRITE,      /* access (read/write) mode */
                     FILE_SHARE_READ|FILE_SHARE_WRITE,/* share mode   */
                     (LPSECURITY_ATTRIBUTES)NULL,     /* security descriptor  */
                     CREATE_ALWAYS,                   /* how to create    */
                     FILE_ATTRIBUTE_NORMAL,           /* File Attribute */
                     (HANDLE)NULL)
                  )==NULL)
    {
        TerminateProcess(ChldProc,0);
        ErrorExit(TEXT("Could not Create Output File"));
    }


    //
    //Start 2 threads to save the output from stdout and stderr of cmd to savefile.
    //

    if ((WaitH[0]=CreateThread
                  (
                     (LPSECURITY_ATTRIBUTES)NULL,           // No security attributes.
                     (DWORD)0,                              // Use same stack size.
                     (LPTHREAD_START_ROUTINE)GetChldOutput, // Thread procedure.
                     (LPVOID)ChildStdErr,                   // Parameter to pass.
                     (DWORD)0,                              // Run immediately.
                     (LPDWORD)&ThreadID)
                   )==NULL)
    {

        TerminateProcess(ChldProc,0);
        ErrorExit(TEXT("Failed to Create GetGhldOutput#1 Thread"));
    }


    if ((WaitH[1]=CreateThread
                  (
                     (LPSECURITY_ATTRIBUTES)NULL,           // No security attributes.
                     (DWORD)0,                              // Use same stack size.
                     (LPTHREAD_START_ROUTINE)GetChldOutput, // Thread procedure.
                     (LPVOID)ChildStdOut,                   // Parameter to pass.
                     (DWORD)0,                              // Run immediately.
                     (LPDWORD)&ThreadID)
                  )==NULL)
    {

        TerminateProcess(ChldProc,0);
        ErrorExit(TEXT("Failed to Create GetGhldOutput#2 Thread"));
    }


    //
    // Start Thread for local session
	// only run if this is not an autostarted TP
    //
	if (!AutoStarted) {
		ClientList[0].Active = TRUE;
   		if ((ClientList[0].hThread = CreateThread(
   	   			(LPSECURITY_ATTRIBUTES) NULL,   	// No security attributes.
   	   			(DWORD) 0,                      	// Use same stack size.
   	   			(LPTHREAD_START_ROUTINE) LocalSession, 	// Thread procedure.
   	   			(LPVOID) &ClientList[0],            // Parameter to pass.
   	   			(DWORD) 0,                          // Run immediately.
   	   			(LPDWORD) &ThreadID))==NULL) {
   	    	TerminateProcess(ChldProc,0);
   	    	ErrorExit(TEXT("Failed To Create LocalSession Thread"));
   		}
	}

    //
    //Start Thread to listen for new Connections
    //

    if ((ListenThreadH=CreateThread
                       (
                         (LPSECURITY_ATTRIBUTES)NULL,        // No security attributes.
                         (DWORD)0,                           // Use same stack size.
                         (LPTHREAD_START_ROUTINE)ListenForSession, // Thread procedure.
                         (LPVOID)tp_name,                    // Parameter to pass.
                         (DWORD)0,                           // Run immediately.
                         (LPDWORD)&ThreadID)
                       )==NULL)
    {

        TerminateProcess(ChldProc,0);
        ErrorExit(TEXT("Failed To Create ListenForSession Thread"));

    }

    SetConsoleCtrlHandler((PHANDLER_ROUTINE)SrvCtrlHand,TRUE);

    WaitH[2]=ChldProc;

    //
    // Wait until the child process terminates
    // or local IO thread terminates
    // or IO with child process ends
    //

    WaitObj=WaitForMultipleObjects(3,WaitH,FALSE,INFINITE);

    switch (WaitObj-WAIT_OBJECT_0)
    {
        case 0:      // Error Writing to savefile
        case 1:
            TerminateProcess(ChldProc,0);
            break;
        case 2:      // Child Proc Terminated
            break;

        default:     // Out of Some Resource
            WRITEF((VBuff,
				TEXT("Out of Resource Error %d..Terminating\n"),
				GetLastError()));
            break;

    }

    TerminateThread(ListenThreadH,0);

    CloseHandle(ChildStdInp);
    CloseHandle(ChildStdOut);
    CloseHandle(ChildStdErr);

    WRITEF((VBuff,
		TEXT("\nServer: Child process \"%ws\" died, parent exiting...\n"),
		ChildCmd));

    CloseHandle(SaveFile);

	// signal all of the client threads to tell them that they should die
	for (i = 0, active = 0; i < MAX_SESSION; i++) {
		if (ClientList[i].Active) {
			SetEvent(ClientList[i].DoClose);
			objs[active++] = ClientList[i].hThread;
		}
	}

	// Wait for all of the client to die gracefully
	WaitForMultipleObjects(active, objs, TRUE, INFINITE);

    for (i = 0; i < MAX_SESSION; i++) {
	    if (ClientList[i].rSaveFile != INVALID_HANDLE_VALUE)
        	CloseHandle(ClientList[i].rSaveFile);

	    if (ClientList[i].MoreData != NULL)
        	CloseHandle(ClientList[i].MoreData);
	}

    if (!DeleteFile(SaveFileName))
          WRITEF((VBuff,TEXT("Temp File %ws not deleted..\n"),SaveFileName));

	appcdestroy();

    return;
}

/*************************************************************/
/* Creates the child process and redirects its std.IO handles*/
/*************************************************************/
// these handles should be treated as if they send and receive ANSI, not Unicode
HANDLE
ForkChildProcess(          // Creates a new process
    TCHAR *cmd,             // Redirects its stdin,stdout
    PHANDLE inH,           // and stderr - returns the
    PHANDLE outH,          // corresponding pipe ends.
    PHANDLE errH
    )
{
    SECURITY_ATTRIBUTES lsa;
    STARTUPINFO         si;
    PROCESS_INFORMATION pi;

    HANDLE ChildIn;
    HANDLE ChildOut;
    HANDLE ChildErr;

    lsa.nLength=sizeof(SECURITY_ATTRIBUTES);
    lsa.lpSecurityDescriptor=NULL;
    lsa.bInheritHandle=TRUE;

    //
    //Create Parent_Write to ChildStdIn Pipe
    //

    if (!CreatePipe(&ChildIn,inH,&lsa,0))
        ErrorExit(TEXT("Could Not Create Parent-->Child Pipe"));

    //
    //Create ChildStdOut to Parent_Read pipe
    //

    if (!CreatePipe(outH,&ChildOut,&lsa,0))
        ErrorExit(TEXT("Could Not Create Child-->Parent Pipe"));

    //
    //Create ChildStdOut to Parent_Read pipe
    //

    if (!CreatePipe(errH,&ChildErr,&lsa,0))
        ErrorExit(TEXT("Could Not Create Child-->Parent Pipe"));

    //
    // Lets Redirect Console StdHandles - easy enough
    //


    si.cb=sizeof(STARTUPINFO);
    si.lpReserved=NULL;
    si.lpTitle=NULL;
    si.lpDesktop=NULL;
    si.dwX=si.dwY=si.dwYSize=si.dwXSize=0;
    si.dwFlags=STARTF_USESTDHANDLES;
    si.hStdInput =ChildIn;
    si.hStdOutput=ChildOut;
    si.hStdError =ChildErr;
    si.wShowWindow=SW_SHOW;
    si.lpReserved2=NULL;
    si.cbReserved2=0;

    //
    //Create Child Process
    //

    if (!CreateProcess
         (
            NULL,
            cmd,
            NULL,
            NULL,
            TRUE,
            NORMAL_PRIORITY_CLASS,
            NULL,
            NULL,
            &si,
            &pi)
         )
    {
        if (GetLastError()==2)
            WRITEF((VBuff,TEXT("Executable %ws not found\n"),cmd));
        ErrorExit(TEXT("Could Not Create Child Process"));
    }

    //
    //Close unneccesary Handles and Restore the crt handles
    //

    CloseHandle(ChildIn);
    CloseHandle(ChildOut);
    CloseHandle(ChildErr);

    return(pi.hProcess);
}

/*************************************************************/
/* Listens for sessions from Clients and creates a new thread*/
/* for each client                                           */
/*************************************************************/

DWORD WINAPI ListenForSession(TCHAR* tp_name) {
    int    i;
    DWORD  ThreadID;
	tpconvid_t tpconv;
    HANDLE TokenHandle;
    TOKEN_DEFAULT_DACL DefaultDacl;

	WRITEF((VBuff, TEXT("\nServer: Waiting for clients on TP: %ws\n\n"), tp_name));

    DefaultDacl.DefaultDacl = NULL;

    if (OpenProcessToken
        (
            GetCurrentProcess(),
            TOKEN_ADJUST_DEFAULT,
            &TokenHandle
        ))
    {

        //
        // Remove the default DACL on the token
        //

        SetTokenInformation
        (
            TokenHandle,
            TokenDefaultDacl,
            &DefaultDacl,
            sizeof( TOKEN_DEFAULT_DACL )
        );

    }

    while(TRUE) {
		tpconv = appclisten(tp_name);

        //
        // Look For a Free Slot
		// There is guaranteed to be one or appclisten wouldn't have run.
        //

        for (i = 0; i < MAX_SESSION; i++) {
            //
            // Locate a Free Client block
            //
            if (!ClientList[i].Active) break;
        }

		// check to see if we couldn't find a free session
		if (i == MAX_SESSION) {
			WRITEF((VBuff, TEXT("\nServer: Client tried to connect with all sessions in use\n")));
			appcclose(tpconv);
			continue;
		} else {
			appcwrite(tpconv, REMOTE_INIT_MSG,
				lstrlen(REMOTE_INIT_MSG) * sizeof(TCHAR));
		}

        //
        // Initialize the Client
        //
        ClientList[i].tpconv = tpconv;
        ClientList[i].Active = TRUE;
        ClientList[i].SendOutput = TRUE;
        ClientList[i].CommandRcvd = FALSE;

        //
        //start new thread for this connection
        //

        if((ClientList[i].hThread=CreateThread
            (
                 (LPSECURITY_ATTRIBUTES)NULL,        // No security attributes.
                 (DWORD)0,                           // Use same stack size.
                 (LPTHREAD_START_ROUTINE)RemoteSession, // Thread procedure.
                 (LPVOID)&ClientList[i],             // Parameter to pass.
                 (DWORD)0,                           // Run immediately.
                 (LPDWORD)&ThreadID)
            )==NULL)
        {
            CloseClient(&ClientList[i]);
            continue;
        }

    }
    return(0);
}

/*************************************************************/
/* Creates a security descriptor with the discrtionry access */
/* for the account specified in the /U switch  if any        */
/*************************************************************/

BOOL
CreateMySecurityDescriptor(
    PSECURITY_DESCRIPTOR pSecurityDescriptor,
    TCHAR *Owner
    )
{
    PSID pOwnerSid;
    PACL pAcl;
    BOOL Ret=FALSE;

    //
    // Initialize the Security Descriptor struct.
    //


    InitializeSecurityDescriptor
    (
        pSecurityDescriptor,
        SECURITY_DESCRIPTOR_REVISION
    );

    if (Owner==NULL)
    {
        //
        // No security required.
        //

        SetSecurityDescriptorDacl
        (
               pSecurityDescriptor,
               TRUE,
               NULL,
               FALSE
        );

        return TRUE;
    }

    {
        //
        // Get the SID for the account/Group
        //

        DWORD len1=1024,len2=1024;
        TCHAR RefDomain[1024];
        SID_NAME_USE snu=0;        //don't care

        if ((pOwnerSid=(PSID)LocalAlloc(LMEM_FIXED, len1))==NULL)
            return FALSE;


        Ret=
        LookupAccountName
        (
            NULL,
            Owner,
            pOwnerSid,
            &len1,
            RefDomain,
            &len2,
            &snu
        );

        if (!Ret)
        {
            LocalFree(pOwnerSid);
            return FALSE;
        }

    }

    {

        //
        // Create the access control list with access for
        // the SID obtained above.
        //

        DWORD aclsize=sizeof(ACL)+
                      sizeof(ACCESS_ALLOWED_ACE)+
                      GetLengthSid(pOwnerSid)-
                      sizeof(DWORD);

        if ((pAcl=(PACL)LocalAlloc(LMEM_FIXED,aclsize))==NULL)
        {
            LocalFree(pOwnerSid);
            return FALSE;
        }

        //
        // Initialize the acl buffer
        //

        Ret=
        InitializeAcl
        (
            pAcl,
            aclsize,
            ACL_REVISION
        );

        if (!Ret)
        {
            LocalFree(pOwnerSid);
            LocalFree(pAcl);
            return FALSE;
        }

        //
        // Add the sid to the access allowed part in ACL
        //

        Ret=
        AddAccessAllowedAce
        (
            pAcl,
            ACL_REVISION,
            GENERIC_ALL,
            pOwnerSid
        );

        if (!Ret)
        {
            LocalFree(pOwnerSid);
            LocalFree(pAcl);
            return FALSE;
        }
    }

    //
    // Add the created ACL to the discreationary control list
    //

    Ret=
    SetSecurityDescriptorDacl
    (
        pSecurityDescriptor,
        TRUE,
        pAcl,
        FALSE
    );

    if (!Ret)
    {
        LocalFree(pOwnerSid);
        LocalFree(pAcl);
        return FALSE;
    }
    return TRUE;
}

/*************************************************************/
/* Manages the Session with a Client - Creates a thread for  */
/* Inputs from the client and a thread for sending outputs to*/
/* the client. Could have just as easily done with 1 thread  */
/* using Asyn IO.                                            */
/*************************************************************/
DWORD WINAPI RemoteSession(SESSION_TYPE         *MyClient) {
    SESSION_STARTUPINFO  ssi;
    DWORD                tmp;
    SESSION_STARTREPLY   ssr;
    SYSTEMTIME           st;

    GetLocalTime(&st);
    memset((TCHAR *)&ssi,0,sizeof(ssi));

    //
    // Open a new handle to the save file ...
    // contains the saved output from the child process
    // and the commands already given to it.
    //

    if ((MyClient->rSaveFile=CreateFile
        (
            SaveFileName,
            GENERIC_READ|GENERIC_WRITE,
            FILE_SHARE_READ|FILE_SHARE_WRITE,
            NULL,OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,NULL)
        )==NULL)

    {
        CloseClient(MyClient);
        return(1);
    }

    //
    // Exchange Remote Information with Client.
    //
	appcread(MyClient->tpconv, (void *) &ssi, sizeof(ssi));
	wcscpy(MyClient->Name, ssi.ClientName);
	MyClient->Name[15] = 0;

	ssr.FileSize = GetFileSize(MyClient->rSaveFile, &tmp);
	ssr.MagicNumber = MAGICNUMBER;

	appcwrite(MyClient->tpconv, (void *) &ssr, sizeof(ssr));

    /* Lines  */
    if (ssi.LinesToSend!=-1)
    {
        long  PosFromEnd=ssi.LinesToSend*CHARS_PER_LINE;
        DWORD BytesToSend=MINIMUM((DWORD)PosFromEnd,ssr.FileSize);
        DWORD BytesRead, usize;
        char *abuff=(char *)LocalAlloc(LMEM_FIXED,(BytesToSend+1)*sizeof(char));
        TCHAR *ubuff=(TCHAR *)LocalAlloc(0, (BytesToSend+1)*sizeof(TCHAR));

        if (ssr.FileSize > (DWORD)PosFromEnd)
        {
            SetFilePointer(
                            MyClient->rSaveFile,
                            -PosFromEnd,
                            (PLONG)NULL,
                            FILE_END
                          );
        }

        if (abuff!=NULL && ubuff!=NULL)
        {
            if (!ReadFile(MyClient->rSaveFile,abuff,BytesToSend,&BytesRead,NULL))
            {
                CloseClient(MyClient);
                return(1);
            }

            // Don't want the markers to be part of the output display
            // at the client end.
            RemoveInpMark(abuff, BytesRead);

			// convert to wbs
			usize = mbstowcs(ubuff, abuff, BytesRead);

			appcwrite(MyClient->tpconv, (void *) ubuff, usize * sizeof(TCHAR));
        }
        LocalFree(abuff);
		LocalFree(ubuff);

    }

    RemoteInfo(WRITEF((VBuff, TEXT("\nServer: Connected To %ws [%02d:%02d]\n"),MyClient->Name,st.wHour,st.wMinute)),ssi.Flag);

    //
    // Start off the new session.
    //
    NewSession(MyClient);

    RemoteInfo(WRITEF((VBuff, TEXT("\nServer: Disconnected From %ws [%02d:%02d]\n"),MyClient->Name,st.wHour,st.wMinute)),ssi.Flag);

	LocalFree(MyClient->tpconv);

    return(0);
}

//
// LocalSession: creates a session for use by the local terminal
//
// argument is ignored
//
DWORD WINAPI LocalSession(SESSION_TYPE *cli) {
	BOOL		done = FALSE;
	HANDLE		rthread, wthread;
	DWORD		tid;
    SYSTEMTIME  st;

    GetLocalTime(&st);

	cli->Active = TRUE;
	cli->tpconv = NULL;
	cli->SendOutput = TRUE;
	lstrcpy(cli->Name, TEXT("Local"));

    if ((cli->rSaveFile=CreateFile(SaveFileName,
            GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL))==NULL) {
		cli->Active = FALSE;
        return 0;
    }

    cli->MoreData = CreateEvent(
        (LPSECURITY_ATTRIBUTES) NULL, /* address of security attributes	*/
        FALSE,                	      /* flag for manual-reset event	*/
        TRUE,	                      /* flag for initial state			*/
        NULL	                      /* address of event-object name	*/
    );

	cli->DoClose = CreateEvent(
		(LPSECURITY_ATTRIBUTES) NULL,	// no security on event
		FALSE,							// auto reset event mode
		FALSE,							// initially false
		NULL);							// unnamed object

    WRITEF((VBuff, TEXT("\nServer: Connected To %ws [%02d:%02d]\n"),cli->Name,st.wHour,st.wMinute));

	if ((wthread = CreateThread(NULL,				// no security attributes
			0,										// use same stack size
			(LPTHREAD_START_ROUTINE) StdinThread,	// function to run
			cli,									// pass client info
			0,										// run now
			&tid)) == NULL) {						// return thread id
		ExitThread(0);
	}

	if ((rthread = CreateThread(NULL,				// no security attributes
			0,										// use same stack size
			(LPTHREAD_START_ROUTINE) StdoutThread,	// function to run
			cli,									// pass client info
			0,										// run now
			&tid)) == NULL) {						// return thread id
		ExitThread(0);
	}
	
	WaitForSingleObject(cli->DoClose, INFINITE);

	TerminateThread(rthread, 0);
	TerminateThread(wthread, 0);

	cli->Active = FALSE;
	CloseHandle(cli->DoClose);
	CloseHandle(cli->MoreData);
	CloseHandle(cli->rSaveFile);
	CloseHandle(stdin);
	CloseHandle(stdout);

    WRITEF((VBuff, TEXT("\nServer: Disconnected From %ws [%02d:%02d]\n"),cli->Name,st.wHour,st.wMinute));

	return 0;
}

DWORD WINAPI StdinThread(SESSION_TYPE *cli) {
	HANDLE	Stdin;
	TCHAR	ubuf[BUFFSIZE];
	char	abuf[BUFFSIZE];
	DWORD	tmp, dread, asize;

	Stdin = GetStdHandle(STD_INPUT_HANDLE);
	// read a command from the user into a buffer (it will be in Unicode)
	while (ReadConsole(Stdin, ubuf, BUFFSIZE - 1, &dread, NULL)) {
		cli->CommandRcvd = TRUE;
		ubuf[dread] = 0;
		// see if it is a valid command
		if (!FilterCommand(cli, ubuf, dread)) {
			// convert the buffer from Unicode to ANSI
			asize = wcstombs(abuf, ubuf, BUFFSIZE);

			// write the buffer to the child's pipe
			if (!WriteFile(ChildStdInp, abuf, asize, &tmp, NULL))
				ExitThread(0);
		}
	}
	return 0;
}

DWORD WINAPI StdoutThread(SESSION_TYPE *cli) {
	HANDLE	Stdout;
	char	abuffin[BUFFSIZE];
    TCHAR   buffin[BUFFSIZE], buffout[BUFFSIZE], cmdbuff[BUFFSIZE];
    DWORD  	aread, dread=0, dwrite=0, tmp, cmdP = 0, i;
    BOOL   	incmd=FALSE;
    TCHAR   MyEchoStr[30];

    wsprintf(MyEchoStr,TEXT("[%-15s"),cli->Name);

    Stdout = GetStdHandle(STD_OUTPUT_HANDLE);

	// read a buffer from an ansi file (the buffer will be ANSI)
    while (ReadFile(cli->rSaveFile, abuffin, BUFFSIZE-1, &aread, NULL)) {
        if (aread == 0) {
			// wait for more data to arrive and loop again
			WaitForSingleObject(cli->MoreData, INFINITE);
			continue;
		}

		abuffin[aread] = 0;
		dread = mbstowcs(buffin, abuffin, BUFFSIZE);

        dwrite=0;

        //
        // This is all to insure that the commands entered
        // by clients are not echoed back to them.
        // A Beginmark and an Endmark is placed around commands
        // sent to the child process from some client.
        //

        for (i = 0; i < dread; i++) {
            if (incmd) {
                if ((buffin[i] == ENDMARK) || (cmdP == BUFFSIZE - 1)) {
                    incmd = FALSE;
                    cmdbuff[cmdP] = 0;
                    if ((wcsstr(cmdbuff, MyEchoStr) == NULL) ||
                        (!cli->CommandRcvd)) {
						WriteConsole(Stdout, cmdbuff, dread, &tmp, NULL);
                    }
                    cmdP=0;
                } else {
                    cmdbuff[cmdP++] = buffin[i];
                }
            } else {
                if (buffin[i] == BEGINMARK) {
                    if (dwrite != 0) {
						WriteConsole(Stdout, buffout, dread, &tmp, NULL);
                        dwrite = 0;
                    }
                    incmd = TRUE;
                    continue;
                } else {
                    buffout[dwrite++] = buffin[i];
                }
            }
        }

        if (dwrite != 0) {
			WriteConsole(Stdout, buffout, dread, &tmp, NULL);
        }
    }

	return 0;
}

DWORD NewSession(SESSION_TYPE* MyClient) {
    DWORD 	ThreadId;
    HANDLE  rThread, wThread;

    MyClient->MoreData = CreateEvent(
        (LPSECURITY_ATTRIBUTES) NULL, /* address of security attributes	*/
        FALSE,                	      /* flag for manual-reset event	*/
        TRUE,	                      /* flag for initial state			*/
        NULL	                      /* address of event-object name	*/
    );

	MyClient->DoClose = CreateEvent(
		(LPSECURITY_ATTRIBUTES) NULL,	// no security on event
		FALSE,							// flag for manual-reset event
		FALSE,							// initially false
		NULL);							// unnamed object

    if ((rThread = CreateThread(
            (LPSECURITY_ATTRIBUTES) NULL,         // No security attributes.
            (DWORD) 0,                            // Use same stack size.
            (LPTHREAD_START_ROUTINE) GetClientInput,
            (LPVOID) MyClient,                    // Parameter to pass.
            (DWORD) 0,                            // Run immediately.
            (LPDWORD) &ThreadId))==NULL) {
        return(GetLastError());
    }


    if ((wThread=CreateThread(
            (LPSECURITY_ATTRIBUTES) NULL,        // No security attributes.
            (DWORD) 0,                           // Use same stack size.
            (LPTHREAD_START_ROUTINE) TransferFileToClient,
            (LPVOID) MyClient,                   // Parameter to pass.
            (DWORD) 0,                           // Run immediately.
            (LPDWORD) &ThreadId))==NULL) {
        CloseHandle(rThread);
        return(GetLastError());
    }

	// Wait for the input thread to terminate.  when it does the session is
	// over.
    ThreadId = WaitForSingleObject(wThread, INFINITE);

	CloseClient(MyClient);

	ThreadId = WaitForSingleObject(rThread, INFINITE);

	// close the thread handles
    CloseHandle(rThread);
    CloseHandle(wThread);

    return 0;
}

/*************************************************************/
/* Saves the output from the child process into the savefile */
/* All the remote client thread and local client thread      */
/* open a seperate handle to this and output its content     */
/* sequentially.                                             */
/*************************************************************/
DWORD WINAPI GetChldOutput(HANDLE readH) {
    TCHAR  	buff[BUFFSIZE];
    DWORD 	dread;
    DWORD 	tmp;
	int		i;


    while (ReadFile(readH,buff,BUFFSIZE-1,&dread,NULL)) {
        buff[dread]=TEXT('\0');

        if (!WriteFile(SaveFile,buff,dread,&tmp,NULL))
            return(1);

        //
        // Signal Reader Thread that more data is available
        //
        for (i=0;i<MAX_SESSION;i++)
			if (ClientList[i].Active) SetEvent(ClientList[i].MoreData);
    }
    return 1;
}

/*************************************************************/
/* A thread for each client connection and one for local IO  */
/* Reads the contents of Save file and sends it to client for*/
/* display.                                                  */
/*************************************************************/
DWORD WINAPI TransferFileToClient(SESSION_TYPE *MyClient) {
    TCHAR   buffin[BUFFSIZE], buffout[BUFFSIZE], cmdbuff[BUFFSIZE];
	char	abuffin[BUFFSIZE];
    DWORD  	dread=0,dwrite=0,aread;
    BOOL   	incmd=FALSE;
    DWORD  	cmdP=0;
    DWORD  	i;
    TCHAR   	MyEchoStr[30];
	HANDLE	objs[2];
	DWORD 	which;

    wsprintf(MyEchoStr,TEXT("[%-15s"),MyClient->Name);

    while (ReadFile(MyClient->rSaveFile, abuffin, BUFFSIZE-1, &aread, NULL)) {
        if (aread == 0) {
            //
            // Event is set by GetChldOutput() func. to signal
            // More data is available in save file.
            //
			objs[0] = MyClient->MoreData;
			objs[1] = MyClient->DoClose;

			// wait for moredata or a close request
			which = WaitForMultipleObjects(2, objs, FALSE, INFINITE);
			which = which - WAIT_OBJECT_0;

            if (which == 0) {
				// there is more data waiting
				continue;
			} else {
				// they want us to close
				return 0;
			}
        }

		dread = mbstowcs(buffin, abuffin, aread);

        dwrite=0;

        //
        // This is all to insure that the commands entered
        // by clients are not echoed back to them.
        // A Beginmark and an Endmark is placed around commands
        // sent to the child process from some client.
        //

        for (i = 0; i < dread; i++) {
            if (incmd) {
                if ((buffin[i] == ENDMARK) || (cmdP == BUFFSIZE - 1)) {
                    incmd = FALSE;
                    cmdbuff[cmdP] = 0;
                    if ((wcsstr(cmdbuff, MyEchoStr) == NULL) ||
                        (!MyClient->CommandRcvd)) {
						appcwrite(MyClient->tpconv, (void *) cmdbuff,
							cmdP * sizeof(TCHAR));
                    }
                    cmdP=0;
                } else {
                    cmdbuff[cmdP++] = buffin[i];
                }
            } else {
                if (buffin[i] == BEGINMARK) {
                    if (dwrite != 0) {
						appcwrite(MyClient->tpconv, (void *) buffout,
							dwrite * sizeof(TCHAR));
                        dwrite = 0;
                    }
                    incmd = TRUE;
                    continue;
                } else {
                    buffout[dwrite++] = buffin[i];
                }
            }
        }

        if (dwrite != 0) {
			appcwrite(MyClient->tpconv, (void *) buffout,
				dwrite * sizeof(TCHAR));
        }
    }
    return 0;
}

/*************************************************************/
/* Commands from the clients are sent to the child process   */
/* and also saved in the SaveFile with Begin and End markers */
/* around them to seperate them from the output from child   */
/* process.                                                  */
/*************************************************************/
DWORD WINAPI GetClientInput(SESSION_TYPE *MyClient) {
    TCHAR ubuff[BUFFSIZE];
	char  abuff[BUFFSIZE];
    DWORD tmp,uread,aread;

	while (TRUE) {
    	uread = appcread(MyClient->tpconv, (void *) ubuff, BUFFSIZE) /
			sizeof(TCHAR);
		if (!appcvalid(MyClient->tpconv)) break;

        MyClient->CommandRcvd = TRUE;

        if (FilterCommand(MyClient, ubuff, uread)) continue;

		aread = wcstombs(abuff, ubuff, uread);

        if (!WriteFile(ChildStdInp, abuff, aread, &tmp, NULL)) ExitThread(0);
    }

    return(1);
}

/*************************************************************/
/* If a client command is intended for the Remote server -   */
/* those beginning with COMMANDCHAR (are not intended        */
/* for the child process) - they are executed here           */
/* and the output sent to the client.                        */
/*************************************************************/
BOOL FilterCommand(SESSION_TYPE *cl, TCHAR *buff, int dread) {
    SYSTEMTIME st;
    TCHAR       inp_buff[4096];
    TCHAR       tmpchar;
    TCHAR       ch[3];
    DWORD      tmp;
    int        len;
    DWORD      ThreadID; //Useless

    if (dread==0)
        return(FALSE);

    buff[dread]=0;

    GetLocalTime(&st);

    if (buff[0]==COMMANDCHAR) {
        switch(tolower(buff[1])) {
            case TEXT('o'):
                cl->SendOutput=!cl->SendOutput;
                break;

            case TEXT('k'):
                TerminateProcess(ChldProc,1);
                break;

			case TEXT('q'):
				SetEvent(cl->DoClose);
				break;

            case TEXT('s'):
                SendStatus(cl->tpconv);
                break;

            case TEXT('p'):
				if (cl->tpconv == NULL) break;
				{
 					//Free it in called Proc	
					TCHAR *mssg=(TCHAR *)LocalAlloc(0, 4096*sizeof(TCHAR));
   	             	TCHAR  *ack=TEXT("Server: Popup Shown..\n");

                    if (mssg==NULL)
                        break;

                    wsprintf(mssg,TEXT("From %ws [%d:%d]\n\n%ws\n"),cl->Name,st.wHour,st.wMinute,&buff[2]);
                    CreateThread(
                          (LPSECURITY_ATTRIBUTES)NULL,         // No security attributes.
                          (DWORD)0,              // Use same stack size.
                          (LPTHREAD_START_ROUTINE)ShowPopup, // Thread procedure.
                          (LPVOID)mssg,          // Parameter to pass.
                          (DWORD)0,              // Run immediately.
                          (LPDWORD)&ThreadID
                         );
					appcwrite(cl->tpconv, (void *) ack, lstrlen(ack) *
						sizeof(TCHAR));
                    break;
                 }

            case TEXT('m'):
                buff[dread-2]=0;
                CMDSTRING(inp_buff,buff,cl,st);
                len=lstrlen(inp_buff);
                WriteFile(SaveFile,inp_buff,len,&tmp,NULL);
                break;

            case TEXT('@'):
                buff[dread-2]=0;
                CMDSTRING(inp_buff,&buff[1],cl,st);
                len=lstrlen(inp_buff);
                WriteFile(SaveFile,inp_buff,len,&tmp,NULL);
                //
                // Remove the first @ sign
                //
                MoveMemory(buff,&buff[1],dread-1);
                buff[dread-1]=TEXT(' ');
                return(FALSE); //Send it it to the chile process
                break;


            default :
				if (cl->tpconv == NULL) break;
                lstrcpy(inp_buff, TEXT("** Unknown Command **\n"));
				appcwrite(cl->tpconv, (void *) inp_buff,
					lstrlen(inp_buff) * sizeof(TCHAR));

            case TEXT('h'):
				if (cl->tpconv != NULL) {
	                wsprintf(inp_buff,TEXT("%cM: To Send Message\n"),COMMANDCHAR);
					appcwrite(cl->tpconv, (void *) inp_buff, lstrlen(inp_buff) * sizeof(TCHAR));
   		            wsprintf(inp_buff,TEXT("%cP: To Generate popup\n"),COMMANDCHAR);
					appcwrite(cl->tpconv, (void *) inp_buff, lstrlen(inp_buff) * sizeof(TCHAR));
   		            wsprintf(inp_buff,TEXT("%cK: To kill the server\n"),COMMANDCHAR);
					appcwrite(cl->tpconv, (void *) inp_buff, lstrlen(inp_buff) * sizeof(TCHAR));
   		            wsprintf(inp_buff,TEXT("%cH: This Help\n"),COMMANDCHAR);
					appcwrite(cl->tpconv, (void *) inp_buff, lstrlen(inp_buff) * sizeof(TCHAR));
				}
                break;
        }
        return(TRUE);
    }


    if ((buff[0]<26)) {
        BOOL ret=FALSE;

        wsprintf(ch,TEXT("^%c"),buff[0]+64);
//        CMDSTRING(inp_buff,ch,cl,st);
        len=lstrlen(inp_buff);

        if (buff[0]==CTRLC)
        {
            cl->CommandRcvd=FALSE;
            GenerateConsoleCtrlEvent(CTRL_C_EVENT,0);
            ret=TRUE; //Already sent to child
        }

        WriteFile(SaveFile,inp_buff,len,&tmp,NULL);
        return(ret); //FALSE:send it to child StdIn
    }

    tmpchar=buff[dread-2]; //must be 13;but just incase
    buff[dread-2]=0;
//    CMDSTRING(inp_buff,buff,cl,st);
    buff[dread-2]=tmpchar;
    len=lstrlen(inp_buff);
    WriteFile(SaveFile,inp_buff,len,&tmp,NULL);
    return(FALSE);
}

/*************************************************************/
VOID SendStatus(tpconvid_t tpconv) {
    TCHAR  buff[1024];
    int   i;
    TCHAR  *env=(TCHAR *)GetEnvironmentStrings();
    DWORD ver=GetVersion();

	if (tpconv == NULL) return;

    wsprintf(buff,TEXT("Command = %ws\n"), ChildCmd);
	appcwrite(tpconv, (void *) buff, lstrlen(buff) * sizeof(TCHAR));

    wsprintf(buff,TEXT("Build = %d \n"),((WORD *)&ver)[1]);
	appcwrite(tpconv, (void *) buff, lstrlen(buff) * sizeof(TCHAR));

    for (i=1;i<MAX_SESSION;i++)
    {
        if (ClientList[i].Active)
        {
            wsprintf(buff,TEXT("ACTIVE SESSION=%ws\n"),ClientList[i].Name);
			appcwrite(tpconv, (void *) buff, lstrlen(buff) * sizeof(TCHAR));
        }
    }

    wsprintf(buff,TEXT("====================\n"));
	appcwrite(tpconv, (void *) buff, lstrlen(buff) * sizeof(TCHAR));

    wsprintf(buff,TEXT("ENVIRONMENT VARIABLES\n"));
	appcwrite(tpconv, (void *) buff, lstrlen(buff) * sizeof(TCHAR));

    wsprintf(buff,TEXT("====================\n"));
	appcwrite(tpconv, (void *) buff, lstrlen(buff) * sizeof(TCHAR));


    __try {
        while (*env!=0)
        {
            wsprintf(buff,TEXT("%ws\n"),env);
			appcwrite(tpconv, (void *) buff, lstrlen(buff) * sizeof(TCHAR));

            while(*(env++)!=0);
        }
    } __except(EXCEPTION_EXECUTE_HANDLER) {
        wsprintf(buff,TEXT("Exception Generated Getting Environment Block\n"),env);
		appcwrite(tpconv, (void *) buff, lstrlen(buff) * sizeof(TCHAR));
    }

    wsprintf(buff,TEXT("====================\n"));
	appcwrite(tpconv, (void *) buff, lstrlen(buff) * sizeof(TCHAR));
    return;
}

/*************************************************************/
DWORD WINAPI
ShowPopup(
    TCHAR *mssg
    )
{
    MessageBox(GetActiveWindow(),mssg,TEXT("***REMOTE***"),MB_OK|MB_SETFOREGROUND);
    LocalFree(mssg);
    return(0);
}
/*************************************************************/
BOOL SrvCtrlHand(
    DWORD event
    )
{
    if (event==CTRL_BREAK_EVENT)
    {
        TerminateProcess(ChldProc,1);
    }
    return(TRUE);
}
/*************************************************************/

VOID CloseClient(SESSION_TYPE *Client) {
	EnterCriticalSection(&close_crit);

	appcclose(Client->tpconv);

    if (Client->rSaveFile != INVALID_HANDLE_VALUE) {
        CloseHandle(Client->rSaveFile);
        Client->rSaveFile = INVALID_HANDLE_VALUE;
    }

    if (Client->MoreData != NULL) {
        CloseHandle(Client->MoreData);
        Client->MoreData = NULL;
    }

	Client->Active=FALSE; //Keep it last else synch problem.

	LeaveCriticalSection(&close_crit);

    return;
}

VOID InitClientList(VOID) {
    int i;
    for (i=0;i<MAX_SESSION;i++)
    {
        ZeroMemory(ClientList[i].Name,HOSTNAMELEN);
		ClientList[i].tpconv = NULL;
        ClientList[i].rSaveFile = INVALID_HANDLE_VALUE;
        ClientList[i].MoreData = NULL;
        ClientList[i].Active = FALSE;
        ClientList[i].CommandRcvd = FALSE;
        ClientList[i].SendOutput = FALSE;
        ClientList[i].hThread = NULL;
    }
    return;
}



VOID RemoveInpMark(char* Buff, DWORD Size) {
    DWORD i;
    for (i=0;i<Size;i++)
    {
        switch (Buff[i])
        {
        case BEGINMARK:
            Buff[i]=' ';
            break;

        case ENDMARK:
            if (i<2)
            {
                Buff[i]= ' ';
            }
            else
            {
                Buff[i]  =Buff[i-1];
                Buff[i-1]=Buff[i-2];
                Buff[i-2]=' ';
            }
            break;

        default:
           break;
       }
    }
}
