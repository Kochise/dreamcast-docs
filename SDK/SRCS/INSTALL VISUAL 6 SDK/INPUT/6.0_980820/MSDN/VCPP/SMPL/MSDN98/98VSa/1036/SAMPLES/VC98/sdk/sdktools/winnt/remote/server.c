
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1992-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

/*++

Module Name:

    Server.c

Abstract:

    The server component of Remote. It spawns a child process
    and redirects the stdin/stdout/stderr of child to itself.
    Waits for connections from clients - passing the
    output of child process to client and the input from clients
    to child process.

Author:

    Rajivendra Nath (rajnath) 2-Jan-1992

Environment:

    Console App. User mode.

Revision History:

--*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include "Remote.h"

#define MAX_SESSION   10

#define COMMANDFORMAT       "%c%-15s    [%-15s %d:%d]\n%c"
#define LOCALNAME           "Local"
#define LOCALCLIENT(x)      (strcmp((char *)(x->Name),LOCALNAME)==0)
#define RemoteInfo(prt,flg) {if (!(flg&&0x80000000)) prt;}

#define CMDSTRING(OutBuff,InpBuff,Client,sTime) \
        {                                \
            /* int xxlen; */             \
            sprintf                      \
            (                            \
               &OutBuff[0],COMMANDFORMAT,\
               BEGINMARK,InpBuff,        \
               Client->Name,sTime.wHour, \
               sTime.wMinute,ENDMARK     \
            );                           \
         }                               \

#define BUFFSIZE      256

SESSION_TYPE ClientList[MAX_SESSION];

HANDLE  ChildStdInp;     //Server Writes to  it
HANDLE  ChildStdOut;     //Server Reads from it
HANDLE  ChildStdErr;     //Server Reads from it

HANDLE  SaveFile;       //File containing all that was
                        //output by child process.
                        //Each connection opens a handle to this file
                        //and is sent through PipeWriteH.

char    SaveFileName[64]; //Name of above file - all new sessions need
HANDLE  ChldProc;         //Handle to the Child Process
HANDLE  ListenThreadH;    //Handle to the thread listening for connections
                          //from Remote Clients.

char    *UserName;        // User/Group who can connect to this server.
                          // Obtained from /U option. If NULL all access.

HANDLE
ForkChildProcess(          // Creates a new process
    char *cmd,             // Redirects its stdin,stdout
    PHANDLE in,            // and stderr - returns the
    PHANDLE out,           // corresponding pipe ends. Using currently
    PHANDLE err
    );

HANDLE
OldForkChildProcess(       //Same as above except different
    char *cmd,             //method for redirection. Not Used.
    PHANDLE in,
    PHANDLE out,
    PHANDLE err
    );

DWORD
ListenForSession(          //THREAD:Listens for new connections and
    char* pipe             //spawns of new seesions - Updates the
    );                     //Status in Client DataStructure. Seperate Thread.

BOOL
CreateMySecurityDescriptor(                    //
    PSECURITY_DESCRIPTOR pSecurityDescriptor,  // Creates a security descriptor
    char *Owner                                // with discretionary access for
    );                                         // access for Owner.


DWORD
NewSession(                //Manages the session with a client.
    SESSION_TYPE* Client
    );

DWORD                      //2 THREAD:Each reads either
GetChldOutput(             //StdOut or StdErr of child and
    HANDLE rhandle         //writes to SaveFile. Seperate Thread.
    );

DWORD
TransferFileToClient(      //X THREADS:Reads the save
    SESSION_TYPE* Client   //file and sendsoutput to a client. Seperate Thread
    );


DWORD
GetClientInput(            //Times X THREADS:Gets input from Child pipe
    SESSION_TYPE* Client   //and sends to childs StdIn. Seperate Thread.
    );


BOOL
FilterCommand(             //Filters input from client
    SESSION_TYPE *cl,      //for commands intended for REMOTE
    char *buff,
    int dread
    );

DWORD                      // Manages the IO with user
LocalSession(              // For the remote server. Seperate Thread.
    PVOID noarg
    );

DWORD                      // Manages the IO with Remote Client.
RemoteSession(
    SESSION_TYPE* Client
    );

BOOL                       // Ctrl-C handler
SrvCtrlHand(
    DWORD event
    );

VOID                       // @s command to remote
SendStatus(
    HANDLE hClientPipe
    );

DWORD                      // @p command to remote
ShowPopup(
    char *mssg
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
VOID
Server(                    
    char* ChildCmd,
    char* PipeName
    )
{
    DWORD  ThreadID ;
    HANDLE WaitH[3];
    DWORD  WaitObj;
    char   tmpdir[32];

    WRITEF((VBuff,"**************************************\n"));
    WRITEF((VBuff,"***********     REMOTE    ************\n"));
    WRITEF((VBuff,"***********     SERVER    ************\n"));
    WRITEF((VBuff,"**************************************\n"));
    WRITEF((VBuff,"To Connect: Remote /C %s %s\n\n",HostName,PipeName));

    InitClientList();

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
             (GetEnvironmentVariable("TMP" ,tmpdir,size)==0)&&
             (GetEnvironmentVariable("TEMP",tmpdir,size)==0)
            )
         {
            sprintf(tmpdir,"%s",".");
         }
         if (!GetTempFileName(tmpdir,"REMOTE",0,SaveFileName))
            GetTempFileName(".","REMOTE",0,SaveFileName);
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
        ErrorExit("Could not Create Output File");
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
        ErrorExit("Failed to Create GetGhldOutput#1 Thread");
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
        ErrorExit("Failed to Create GetGhldOutput#2 Thread");
    }


    //
    //Start Thread to listen for new Connections
    //

    if ((ListenThreadH=CreateThread
                       (
                         (LPSECURITY_ATTRIBUTES)NULL,        // No security attributes.
                         (DWORD)0,                           // Use same stack size.
                         (LPTHREAD_START_ROUTINE)ListenForSession, // Thread procedure.
                         (LPVOID)PipeName,                   // Parameter to pass.
                         (DWORD)0,                           // Run immediately.
                         (LPDWORD)&ThreadID)
                       )==NULL)
    {

        TerminateProcess(ChldProc,0);
        ErrorExit("Failed To Create ListenForSession Thread");

    }

    //
    //Start Local Thread
    //

    if ((ClientList[0].hThread=CreateThread
                               (
                                    (LPSECURITY_ATTRIBUTES)NULL,        // No security attributes.
                                    (DWORD)0,                           // Use same stack size.
                                    (LPTHREAD_START_ROUTINE)LocalSession, // Thread procedure.
                                    (LPVOID)NULL,                       // Parameter to pass.
                                    (DWORD)0,                           // Run immediately.
                                    (LPDWORD)&ThreadID)
                               )==NULL)
    {

        TerminateProcess(ChldProc,0);
        ErrorExit("Failed To Create ListenForSession Thread");

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
            printf("Out of Resource Error %d..Terminating\n",GetLastError());
            break;

    }

    TerminateThread(ListenThreadH,0);

    CloseHandle(ChildStdInp);
    CloseHandle(ChildStdOut);
    CloseHandle(ChildStdErr);

    WRITEF((VBuff,"\nRemote:Parent exiting. Child(%s) dead..\n",ChildCmd));

    CloseHandle(SaveFile);

    {
        int i;
        for (i=0;i<MAX_SESSION;i++)
            CloseClient(&ClientList[i]);
    }

    if (!DeleteFile(SaveFileName))
          WRITEF((VBuff,"Temp File %s not deleted..\n",SaveFileName));

    return;
}
/*************************************************************/
/* Creates the child process and redirects its std.IO handles*/
/*************************************************************/
HANDLE
ForkChildProcess(          // Creates a new process
    char *cmd,             // Redirects its stdin,stdout
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
        ErrorExit("Could Not Create Parent-->Child Pipe");

    //
    //Create ChildStdOut to Parent_Read pipe
    //

    if (!CreatePipe(outH,&ChildOut,&lsa,0))
        ErrorExit("Could Not Create Child-->Parent Pipe");

    //
    //Create ChildStdOut to Parent_Read pipe
    //

    if (!CreatePipe(errH,&ChildErr,&lsa,0))
        ErrorExit("Could Not Create Child-->Parent Pipe");

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
            WRITEF((VBuff,"Executable %s not found\n",cmd));
        ErrorExit("Could Not Create Child Process");
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
/* Same as above but uses different method of IO redir.      */
/* Not used now                                              */
/*************************************************************/
HANDLE
OldForkChildProcess(
    char *cmd,
    PHANDLE inH,
    PHANDLE outH,
    PHANDLE errH
    )
{
    SECURITY_ATTRIBUTES lsa;
    STARTUPINFO         si;
    PROCESS_INFORMATION pi;

    HANDLE OldStdIn =GetStdHandle(STD_INPUT_HANDLE);
    HANDLE OldStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE OldStdErr=GetStdHandle(STD_ERROR_HANDLE);

    HANDLE ChildStdIn;
    HANDLE ChildStdOut;
    HANDLE ChildStdErr;

    lsa.nLength=sizeof(SECURITY_ATTRIBUTES);
    lsa.lpSecurityDescriptor=NULL;
    lsa.bInheritHandle=TRUE;

    //Create Parent_Write to ChildStdIn Pipe
    if (!CreatePipe(&ChildStdIn,inH,&lsa,0))
        ErrorExit("Could Not Create Parent-->Child Pipe");

    //Create ChildStdOut to Parent_Read pipe
    if (!CreatePipe(outH,&ChildStdOut,&lsa,0))
        ErrorExit("Could Not Create Child-->Parent Pipe");

    //Create ChildStdOut to Parent_Read pipe
    if (!CreatePipe(errH,&ChildStdErr,&lsa,0))
        ErrorExit("Could Not Create Child-->Parent Pipe");

    //Make ChildStdIn and Out as standard handles and get it inherited by child
    if (!SetStdHandle(STD_INPUT_HANDLE,ChildStdIn))
        ErrorExit("Could not change StdIn");

    if (!SetStdHandle(STD_OUTPUT_HANDLE,ChildStdOut))
        ErrorExit("Could Not change StdOut");

    if (!SetStdHandle(STD_ERROR_HANDLE,ChildStdErr))
        ErrorExit("Could Not change StdErr");

    si.cb=sizeof(STARTUPINFO);
    si.lpReserved=NULL;
    si.lpTitle=NULL;
    si.lpDesktop=NULL;
    si.dwX=si.dwY=si.dwYSize=si.dwXSize=si.dwFlags=0L;
    si.wShowWindow=SW_SHOW;
    si.lpReserved2=NULL;
    si.cbReserved2=0;

    //Create Child Process
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
        ErrorExit("Could Not Create Child Process");
    }

    //reset StdIn StdOut
    if (!SetStdHandle(STD_INPUT_HANDLE,OldStdIn))
    {
        TerminateProcess(pi.hProcess,1);
        ErrorExit("Could not RESET StdIn");
    }

    if (!SetStdHandle(STD_OUTPUT_HANDLE,OldStdOut))
    {
        TerminateProcess(pi.hProcess,1);
        ErrorExit("Could not RESET StdIn");
    }

    if (!SetStdHandle(STD_ERROR_HANDLE,OldStdErr))
    {
        TerminateProcess(pi.hProcess,1);
        ErrorExit("Could not RESET StdIn");
    }

    //Close unneccesary Handles
    CloseHandle(ChildStdIn);
    CloseHandle(ChildStdOut);
    CloseHandle(ChildStdErr);

    return(pi.hProcess);
}

/*************************************************************/
/* Listens for sessions from Clients and creates a new thread*/
/* for each client                                           */
/*************************************************************/

DWORD
ListenForSession(
   char* pipename
   )
{
    int    i;
    DWORD  ThreadID;
    HANDLE PipeH[2];
    SECURITY_DESCRIPTOR SecurityDescriptor;
    HANDLE TokenHandle;
    TOKEN_DEFAULT_DACL DefaultDacl;
    SECURITY_ATTRIBUTES lsa;

    char   fullnameIn[BUFFSIZE];
    char   fullnameOut[BUFFSIZE];

    sprintf(fullnameIn,SERVER_READ_PIPE  ,".",pipename);
    sprintf(fullnameOut,SERVER_WRITE_PIPE,".",pipename);


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


    if (CreateMySecurityDescriptor(&SecurityDescriptor,UserName)==FALSE)
    {
        Errormsg("Remote:Could not set security for user");
    }

    lsa.nLength=sizeof(SECURITY_ATTRIBUTES);
    lsa.lpSecurityDescriptor=&SecurityDescriptor;
    lsa.bInheritHandle=TRUE;

    while(TRUE)
    {
        //
        // Create New pipe instances for each connection
        //

        PipeH[0]=CreateNamedPipe
                 (
                    fullnameIn ,
                    PIPE_ACCESS_INBOUND ,
                    PIPE_TYPE_BYTE,
                    PIPE_UNLIMITED_INSTANCES,
                    0,0,0,&lsa
                 );

        PipeH[1]=CreateNamedPipe
                 (
                    fullnameOut,
                    PIPE_ACCESS_OUTBOUND,
                    PIPE_TYPE_BYTE,
                    PIPE_UNLIMITED_INSTANCES,
                    0,0,0,&lsa
                 );

        if (!ConnectNamedPipe(PipeH[0],NULL))
        {
            if (GetLastError()!=ERROR_PIPE_CONNECTED)
            {
                CloseHandle(PipeH[0]);
                CloseHandle(PipeH[1]);
                continue;
            }

        }

        if (!ConnectNamedPipe(PipeH[1],NULL))
        {
            if (GetLastError()!=ERROR_PIPE_CONNECTED)
            {
                CloseHandle(PipeH[0]);
                CloseHandle(PipeH[1]);
                continue;
            }
        }

        //
        //Look For a Free Slot & if not- then terminate connection
        //

        for (i=1;i<MAX_SESSION;i++)
        {
            //
            // Locate a Free Client block
            //
            if (!ClientList[i].Active)
                break;
        }

        if (i<MAX_SESSION)
        {
            //
            // Initialize the Client
            //
            ClientList[i].PipeReadH=PipeH[0];
            ClientList[i].PipeWriteH=PipeH[1];
            ClientList[i].Active=TRUE;
            ClientList[i].SendOutput=TRUE;
            ClientList[i].CommandRcvd=FALSE;

        }
        else
        {
            WRITEF((VBuff,"Remote:Closing New Session - No more slots\n"));
            CloseHandle(PipeH[0]);
            CloseHandle(PipeH[1]);
            continue;
        }

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
    char *Owner
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
        char RefDomain[1024];
        SID_NAME_USE snu=0;        //don't care

        if ((pOwnerSid=(PSID)calloc(len1,1))==NULL)
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
            free(pOwnerSid);
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

        if ((pAcl=(PACL)calloc(1,aclsize))==NULL)
        {
            free(pOwnerSid);
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
            free(pOwnerSid);
            free(pAcl);
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
            free(pOwnerSid);
            free(pAcl);
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
        free(pOwnerSid);
        free(pAcl);
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
DWORD
RemoteSession(
    SESSION_TYPE         *MyClient
    )
{
    DWORD                ReadCnt;
    SESSION_STARTUPINFO  ssi;
    char                 *headerbuff;
    char                 msg[BUFFSIZE];
    DWORD                tmp;
    SESSION_STARTREPLY   ssr;
    SYSTEMTIME           st;

    GetLocalTime(&st);
    memset((char *)&ssi,0,sizeof(ssi));

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

    {

        DWORD reply=0;

        ReadFixBytes(MyClient->PipeReadH,(char *)MyClient->Name,HOSTNAMELEN-1,0);

        //
        //Last four Bytes contains a code
        //

        memcpy((char *)&reply,(char *)&(MyClient->Name[11]),4);

        if (reply!=MAGICNUMBER)
        {
            //
            // Unknown client
            //
            CloseClient(MyClient);
            return(1);
        }

        ssr.MagicNumber=MAGICNUMBER;
        ssr.Size=sizeof(ssr);
        ssr.FileSize=GetFileSize( MyClient->rSaveFile, &tmp );

        WriteFile(MyClient->PipeWriteH,(char *)&ssr,sizeof(ssr),&tmp,NULL);
    }

    if (ReadFixBytes(MyClient->PipeReadH,(char *)&(ssi.Size),sizeof(ssi.Size),0)!=0)
    {
        CloseClient(MyClient);
        return(1);
    }

    if (ssi.Size>1024)      //Sanity Check
    {
        sprintf(msg,"%s","Server:Unknown Header..Terminating session\n");
        WriteFile(MyClient->PipeWriteH,msg,strlen(msg),&tmp,NULL);
        CloseClient(MyClient);
        return(1);
    }

    if ((headerbuff=(char *)calloc(ssi.Size,1))==NULL)
    {
        sprintf(msg,"%s","Server:Not Enough Memory..Terminating session\n");
        WriteFile(MyClient->PipeWriteH,msg,strlen(msg),&tmp,NULL);
        CloseClient(MyClient);
        return(1);
    }

    ReadCnt=ssi.Size-sizeof(ssi.Size);
    if (ReadFixBytes(MyClient->PipeReadH,(char *)headerbuff,ReadCnt,0)!=0)
    {
        CloseClient(MyClient);
        return(1);
    }

    memcpy((char *)&ssi+sizeof(ssi.Size),headerbuff,sizeof(ssi)-sizeof(ssi.Size));
    free(headerbuff);

    /* Version  */
    if (ssi.Version!=VERSION)
    {
         sprintf(msg,"Remote Warning:Server Version=%d Client Version=%d\n",VERSION,ssi.Version);
         WriteFile(MyClient->PipeWriteH,msg,strlen(msg),&tmp,NULL);

    }

    /* Name  */
    {
        memcpy(MyClient->Name,ssi.ClientName,15);
        MyClient->Name[14]=0;

    }

    /* Lines  */
    if (ssi.LinesToSend!=-1)
    {
        long  PosFromEnd=ssi.LinesToSend*CHARS_PER_LINE;
        DWORD BytesToSend=MINIMUM((DWORD)PosFromEnd,ssr.FileSize);
        DWORD BytesRead;
        char  *buff=(char *)calloc(BytesToSend+1,1);

        if (ssr.FileSize > (DWORD)PosFromEnd)
        {
            SetFilePointer(
                            MyClient->rSaveFile,
                            -PosFromEnd,
                            (PLONG)NULL,
                            FILE_END
                          );
        }

        if (buff!=NULL)
        {
            if (!ReadFile(MyClient->rSaveFile,buff,BytesToSend,&BytesRead,NULL))
            {
                CloseClient(MyClient);
                return(1);
            }

            //
            // Don't want the markers to be part of the output display
            // at the client end.
            //
            RemoveInpMark(buff,BytesRead);
            if (!WriteFile(MyClient->PipeWriteH,buff,BytesRead,&tmp,NULL))
            {
                CloseClient(MyClient);
                return(1);
            }
        }
        free(buff);

    }

    RemoteInfo(printf("\n**Remote:Connected To %s [%02d:%02d]\n",MyClient->Name,st.wHour,st.wMinute),ssi.Flag);

    //
    // Start off the new session.
    //
    NewSession(MyClient);

    RemoteInfo(printf("\n**Remote:Disconnected From %s [%02d:%02d]\n",MyClient->Name,st.wHour,st.wMinute),ssi.Flag);
    CloseClient(MyClient);
    return(0);
}
/*************************************************************/
DWORD
NewSession(
    SESSION_TYPE* MyClient
    )
{
    DWORD        ThreadId;
    HANDLE       rwThread[3];

    MyClient->MoreData=CreateEvent
    (
        (LPSECURITY_ATTRIBUTES) NULL,/* address of security attributes	*/
        FALSE,                	     /* flag for manual-reset event	*/
        TRUE,	                     /* flag for initial state	*/
        NULL	                     /* address of event-object name	*/
    );

    if ((rwThread[0]=CreateThread
         (
            (LPSECURITY_ATTRIBUTES)NULL,         // No security attributes.
            (DWORD)0,                            // Use same stack size.
            (LPTHREAD_START_ROUTINE)GetClientInput, // Thread procedure.
            (LPVOID)MyClient,                    // Parameter to pass.
            (DWORD)0,                            // Run immediately.
            (LPDWORD)&ThreadId)
         )==NULL)
    {
        return(GetLastError());
    }


    if ((rwThread[1]=CreateThread
         (
            (LPSECURITY_ATTRIBUTES)NULL,        // No security attributes.
            (DWORD)0,                           // Use same stack size.
            (LPTHREAD_START_ROUTINE)TransferFileToClient, // Thread procedure.
            (LPVOID)MyClient,                    // Parameter to pass.
            (DWORD)0,                           // Run immediately.
            (LPDWORD)&ThreadId)
         )==NULL)
    {
        CloseHandle(rwThread[0]);
        return(GetLastError());
    }

    rwThread[2]=ChldProc;

    //
    // Wait for either the Input or Output thread
    // to terminate and then close the session.
    //

    WaitForMultipleObjects(3, rwThread,FALSE, INFINITE);

    TerminateThread(rwThread[0],1);
    TerminateThread(rwThread[1],1);

    CloseHandle(rwThread[0]);
    CloseHandle(rwThread[0]);

    return(0);
}

/*************************************************************/
/* Saves the output from the child process into the savefile */
/* All the remote client thread and local client thread      */
/* open a seperate handle to this and output its content     */
/* sequentially.                                             */
/*************************************************************/
DWORD
GetChldOutput(
    HANDLE readH
    )
{
    char  buff[BUFFSIZE];
    DWORD dread;
    DWORD tmp;


    while(ReadFile(readH,buff,BUFFSIZE-1,&dread,NULL))
    {
        buff[dread]='\0';

        if (!WriteFile(SaveFile,buff,dread,&tmp,NULL))
        {
            return(1);
        }

        //
        // Signal Reader Thread that more data is available
        //
        {
            int i;
            for (i=0;i<MAX_SESSION;i++)
            {
                if (ClientList[i].Active)
                {
                    SetEvent(ClientList[i].MoreData);
                }
            }
        }
    }
    return(1);
}
/*************************************************************/
/* A thread for each client connection and one for local IO  */
/* Reads the contents of Save file and sends it to client for*/
/* display.                                                  */
/*************************************************************/
DWORD
TransferFileToClient(
    SESSION_TYPE *MyClient
    )
{

    char   buffin[BUFFSIZE],buffout[BUFFSIZE],cmdbuff[BUFFSIZE];
    DWORD  tmp;
    DWORD  dread=0,dwrite=0;
    BOOL   incmd=FALSE;
    DWORD  cmdP=0;
    DWORD  i;
    char   MyEchoStr[30];

    sprintf(MyEchoStr,"[%-15s",MyClient->Name);

    while(ReadFile(MyClient->rSaveFile,buffin,BUFFSIZE-1,&dread,NULL))
    {
        if (dread==0)
        {
            //
            // Event is set by GetChldOutput() func. to signal
            // More data is available in save file.
            //
            WaitForSingleObject(MyClient->MoreData,INFINITE);
            continue;
        }
        dwrite=0;

        //
        // This is all to insure that the commands entered
        // by clients are not echoed back to them.
        // A Beginmark and an Endmark is placed around commands
        // sent to the child process from some client.
        //

        for(i=0;i<dread;i++)
        {
            if (incmd)
            {
                if ((buffin[i]==ENDMARK)||(cmdP==BUFFSIZE-1))
                {
                    incmd=FALSE;
                    cmdbuff[cmdP]=0;
                    if ((strstr(cmdbuff,MyEchoStr)==NULL)||
                        (!MyClient->CommandRcvd))
                    {
                        if (!WriteFile(
                            MyClient->PipeWriteH,
                            cmdbuff,cmdP,&tmp,NULL))
                        {
                            return(1);
                        }
                    }
                    cmdP=0;
                }
                else
                {
                    cmdbuff[cmdP++]=buffin[i];
                }
            }
            else
            {

                if (buffin[i]==BEGINMARK)
                {
                    if (dwrite!=0)
                    {
                        if (!WriteFile(
                            MyClient->PipeWriteH,
                            buffout,dwrite,&tmp,NULL))
                        {
                            return(1);
                        }
                        dwrite=0;
                    }
                    incmd=TRUE;
                    continue;
                }
                else
                {
                    buffout[dwrite++]=buffin[i];
                }
            }
        }

        if (dwrite!=0)
        {
            if (!WriteFile(
                MyClient->PipeWriteH,
                buffout,dwrite,&tmp,NULL))
            {
                return(0);
            }
        }
    }
    return(1);
}

/*************************************************************/
/* Commands from the clients are sent to the child process   */
/* and also saved in the SaveFile with Begin and End markers */
/* around them to seperate them from the output from child   */
/* process.                                                  */
/*************************************************************/
DWORD
GetClientInput(
    SESSION_TYPE *MyClient
    )
{
    char buff[BUFFSIZE];
    DWORD tmp,dread;

    while(ReadFile(MyClient->PipeReadH,buff,BUFFSIZE,&dread,NULL))
    {
        buff[dread]=0;
        MyClient->CommandRcvd=TRUE;

        if (FilterCommand(MyClient,buff,dread))
            continue;


        if (!WriteFile(ChildStdInp,buff,dread,&tmp,NULL))
        {
            ExitThread(0);
        }
    }
    return(1);
}

/*************************************************************/
/* If a client command is intended for the Remote server -   */
/* those beginning with COMMANDCHAR (are not intended        */
/* for the child process) - they are executed here           */
/* and the output sent to the client.                        */
/*************************************************************/
BOOL
FilterCommand(
    SESSION_TYPE *cl,
    char *buff,
    int dread
    )
{
    SYSTEMTIME st;
    char       inp_buff[4096];
    char       tmpchar;
    char       ch[3];
    DWORD      tmp;
    int        len;
    DWORD      ThreadID; //Useless

    if (dread==0)
        return(FALSE);

    buff[dread]=0;

    GetLocalTime(&st);


    if (buff[0]==COMMANDCHAR)
    {
        switch(buff[1])
        {
            case 'o':
            case 'O':
                cl->SendOutput=!cl->SendOutput;
                break;

            case 'k':
            case 'K':
                TerminateProcess(ChldProc,1);
                break;

            case 's':
            case 'S':
                 SendStatus(cl->PipeWriteH);
                 break;

            case 'p':
            case 'P':
                {
                    char  *mssg=(char *)calloc(4096,1); //Free it in called Proc
                    char  *ack="Remote:Popup Shown..\n";

                    if (mssg==NULL)
                        break;

                    sprintf(mssg,"From %s [%d:%d]\n\n%s\n",cl->Name,st.wHour,st.wMinute,&buff[2]);
                    CreateThread(
                          (LPSECURITY_ATTRIBUTES)NULL,         // No security attributes.
                          (DWORD)0,              // Use same stack size.
                          (LPTHREAD_START_ROUTINE)ShowPopup, // Thread procedure.
                          (LPVOID)mssg,          // Parameter to pass.
                          (DWORD)0,              // Run immediately.
                          (LPDWORD)&ThreadID
                         );
                    WriteFile(cl->PipeWriteH,ack,strlen(ack),&tmp,NULL);
                    break;
                 }

            case 'm':
            case 'M':
                buff[dread-2]=0;
                CMDSTRING(inp_buff,buff,cl,st);
                len=strlen(inp_buff);
                WriteFile(SaveFile,inp_buff,len,&tmp,NULL);
                break;

            case '@':
                buff[dread-2]=0;
                CMDSTRING(inp_buff,&buff[1],cl,st);
                len=strlen(inp_buff);
                WriteFile(SaveFile,inp_buff,len,&tmp,NULL);
                //
                // Remove the first @ sign
                //
                MoveMemory(buff,&buff[1],dread-1);
                buff[dread-1]=' ';
                return(FALSE); //Send it it to the chile process
                break;


            default :
                sprintf(inp_buff,"%s","** Unknown Command **\n");
                WriteFile(cl->PipeWriteH,inp_buff,strlen(inp_buff),&tmp,NULL);

            case 'h':
            case 'H':
                 sprintf(inp_buff,"%cM: To Send Message\n",COMMANDCHAR);
                 WriteFile(cl->PipeWriteH,inp_buff,strlen(inp_buff),&tmp,NULL);
                 sprintf(inp_buff,"%cP: To Generate popup\n",COMMANDCHAR);
                 WriteFile(cl->PipeWriteH,inp_buff,strlen(inp_buff),&tmp,NULL);
                 sprintf(inp_buff,"%cK: To kill the server\n",COMMANDCHAR);
                 WriteFile(cl->PipeWriteH,inp_buff,strlen(inp_buff),&tmp,NULL);
                 sprintf(inp_buff,"%cH: This Help\n",COMMANDCHAR);
                 WriteFile(cl->PipeWriteH,inp_buff,strlen(inp_buff),&tmp,NULL);
                 break;
        }
        return(TRUE);
    }


    if ((buff[0]<26))
    {
        BOOL ret=FALSE;

        sprintf(ch,"^%c",buff[0]+64);
        CMDSTRING(inp_buff,ch,cl,st);
        len=strlen(inp_buff);

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
    CMDSTRING(inp_buff,buff,cl,st);
    buff[dread-2]=tmpchar;
    len=strlen(inp_buff);
    WriteFile(SaveFile,inp_buff,len,&tmp,NULL);
    return(FALSE);
}
/*************************************************************/
VOID
SendStatus(
    HANDLE hClientPipe
    )
{
    char  buff[1024];
    int   i;
    DWORD tmp;
    char  *env=(char *)GetEnvironmentStrings();
    DWORD ver=GetVersion();

    sprintf(buff,"Command = %s\n",ChildCmd);
    WriteFile(hClientPipe,buff,strlen(buff),&tmp,NULL);

    sprintf(buff,"Server = %s PIPE=%s\n",HostName,PipeName);
    WriteFile(hClientPipe,buff,strlen(buff),&tmp,NULL);

    sprintf(buff,"Build = %d \n",((WORD *)&ver)[1]);
    WriteFile(hClientPipe,buff,strlen(buff),&tmp,NULL);

    for (i=1;i<MAX_SESSION;i++)
    {
        if (ClientList[i].Active)
        {
            sprintf(buff,"ACTIVE SESSION=%s\n",ClientList[i].Name);
            WriteFile(hClientPipe,buff,strlen(buff),&tmp,NULL);
        }
    }

    sprintf(buff,"====================\n",Server,PipeName);
    WriteFile(hClientPipe,buff,strlen(buff),&tmp,NULL);

    sprintf(buff,"ENVIRONMENT VARIABLES\n",Server,PipeName);
    WriteFile(hClientPipe,buff,strlen(buff),&tmp,NULL);

    sprintf(buff,"====================\n",Server,PipeName);
    WriteFile(hClientPipe,buff,strlen(buff),&tmp,NULL);


    try
    {
        while (*env!=0)
        {
            sprintf(buff,"%s\n",env);
            WriteFile(hClientPipe,buff,strlen(buff),&tmp,NULL);

            while(*(env++)!=0);
        }
    }
    except(EXCEPTION_EXECUTE_HANDLER)
    {
        sprintf(buff,"Exception Generated Getting Environment Block\n",env);
        WriteFile(hClientPipe,buff,strlen(buff),&tmp,NULL);

    }

    sprintf(buff,"====================\n",Server,PipeName);
    WriteFile(hClientPipe,buff,strlen(buff),&tmp,NULL);
    return;
}
/*************************************************************/
DWORD
ShowPopup(
    char *mssg
    )
{
    MessageBox(GetActiveWindow(),mssg,"***REMOTE***",MB_OK|MB_SETFOREGROUND);
    free(mssg);
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

DWORD   LocalSession(PVOID noarg)
{
    //Local is ClientList[0]
    char *name=(char *)ClientList[0].Name;

    strcpy(name,LOCALNAME);
    if ((ClientList[0].rSaveFile=CreateFile(SaveFileName,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL))==NULL)
    {
        WRITEF((VBuff,"Remote:Cannot open ReadHandle to Savefile:%d\n",GetLastError()));
        ClientList[0].Active=FALSE;
        return(1);

    }

    ClientList[0].PipeReadH=GetStdHandle(STD_INPUT_HANDLE);
    ClientList[0].PipeWriteH=GetStdHandle(STD_OUTPUT_HANDLE);
    ClientList[0].SendOutput=TRUE;
    ClientList[0].Active=TRUE;
    NewSession(&ClientList[0]);
    CloseClient(&ClientList[0]);
    return(0);
}

VOID
CloseClient(
    SESSION_TYPE *Client
    )
{
    ZeroMemory(Client->Name,HOSTNAMELEN);

    if (Client->PipeReadH!=INVALID_HANDLE_VALUE)
    {
        CloseHandle(Client->PipeReadH);
        Client->PipeReadH=INVALID_HANDLE_VALUE;
    }

    if (Client->PipeWriteH!=INVALID_HANDLE_VALUE)
    {
        CloseHandle(Client->PipeWriteH);
        Client->PipeWriteH=INVALID_HANDLE_VALUE;
    }

    if (Client->rSaveFile!=INVALID_HANDLE_VALUE)
    {
        CloseHandle(Client->rSaveFile);
        Client->rSaveFile=INVALID_HANDLE_VALUE;
    }
    if (Client->MoreData!=NULL)
    {
        CloseHandle(Client->MoreData);
        Client->MoreData=NULL;
    }

    Client->Active=FALSE; //Keep it last else synch problem.
    return;
}

VOID
InitClientList(
    )
{
    int i;
    for (i=0;i<MAX_SESSION;i++)
    {
        ZeroMemory(ClientList[i].Name,HOSTNAMELEN);
        ClientList[i].PipeReadH=INVALID_HANDLE_VALUE;
        ClientList[i].PipeWriteH=INVALID_HANDLE_VALUE;
        ClientList[i].rSaveFile=INVALID_HANDLE_VALUE;
        ClientList[i].MoreData=NULL;
        ClientList[i].Active=FALSE;
        ClientList[i].CommandRcvd=FALSE;
        ClientList[i].SendOutput=FALSE;
        ClientList[i].hThread=NULL;
    }
    return;
}



VOID
RemoveInpMark(
    char* Buff,
    DWORD Size
    )

{
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
