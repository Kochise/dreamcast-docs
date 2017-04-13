
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright 1993 - 1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

/*++

Copyright 1993 - 1997 Microsoft Corporation

Module Name:

    Remote.c

Abstract:

    This module contains the main() entry point for Remote.
    Calls the Server or the Client depending on the first parameter.


Author:

    Rajivendra Nath  2-Jan-1993

Environment:

    Console App. User mode.

Revision History:

--*/


#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "Remote.h"

char   HostName[HOSTNAMELEN];
char*  ChildCmd;
char*  PipeName;
char*  ServerName;
char * DaclNames[ MAX_DACL_NAMES ];
DWORD  DaclNameCount = 0;
char * DaclDenyNames[ MAX_DACL_NAMES ];
DWORD  DaclDenyNameCount = 0 ;
HANDLE MyStdOut;
HANDLE hAttachedProcess = INVALID_HANDLE_VALUE;
HANDLE hAttachedWriteChildStdIn = INVALID_HANDLE_VALUE;
HANDLE hAttachedReadChildStdOut = INVALID_HANDLE_VALUE;

BOOL   IsAdvertise;
DWORD  ClientToServerFlag;
BOOL   bForceTwoPipes;

char* ColorList[]={"black" ,"blue" ,"green" ,"cyan" ,"red" ,"purple" ,"yellow" ,"white",
                   "lblack","lblue","lgreen","lcyan","lred","lpurple","lyellow","lwhite"};

WORD
GetColorNum(
    char* color
    );

VOID
SetColor(
    WORD attr
    );

BOOL
GetNextConnectInfo(
    char** SrvName,
    char** PipeName
    );



CONSOLE_SCREEN_BUFFER_INFO csbiOriginal;

main(
    int    argc,
    char** argv
    )
{
    WORD  RunType;              // Server or Client end of Remote
    DWORD len=HOSTNAMELEN;
    int   i, FirstArg;

    char  sTitle[120];          // New Title
    char  orgTitle[100];        // Old Title
    BOOL  bPromptForArgs=FALSE; // Is /P option
    WORD  wAttrib;              // Console Attributes
    int   privacy;              // Allows exposing or hidng sessions to remote /q
    BOOL  Deny ;

    GetComputerName((LPTSTR)HostName,&len);

    MyStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (GetConsoleScreenBufferInfo(MyStdOut,&csbiOriginal)) {

        wAttrib = csbiOriginal.wAttributes;
        GetConsoleTitle(orgTitle,sizeof(orgTitle));

    } else {

        //
        // either stdout is a pipe, or it wasn't opened for
        // GENERIC_READ along with GENERIC_WRITE, in which
        // case our color manipulations will work so we need
        // to pick default colors.
        //

        wAttrib = FOREGROUND_GREEN |
                  FOREGROUND_INTENSITY;

        orgTitle[0] = 0;
    }

    privacy = PRIVACY_DEFAULT;



    //
    // Parameter Processing
    //
    // For Server:
    // Remote /S <Executable>  <PipeName> [Optional Params]
    //
    // For Client:
    // Remote /C <Server Name> <PipeName> [Optional Params]
    // or
    // Remote /P
    // This will loop continously prompting for different
    // Servers and Pipename


    if ((argc<2)||((argv[1][0]!='/')&&(argv[1][0]!='-')))
    {

        DisplayServerHlp();
        DisplayClientHlp();
        return(1);
    }

    switch(argv[1][1])
    {
    case 'c':
    case 'C':

        //
        // Is Client End of Remote
        //

        if ((argc<4)||((argv[1][0]!='/')&&(argv[1][0]!='-')))
        {

            DisplayServerHlp();
            DisplayClientHlp();
            return(1);
        }

        ServerName=argv[2];
        PipeName=argv[3];
        FirstArg=4;
        RunType=RUNTYPE_CLIENT;
        break;


    case 'q':
    case 'Q':

        //
        //  Query for possible conexions
        //


        if ((argc != 3)||((argv[1][0]!='/')&&(argv[1][0]!='-')))
        {

            DisplayServerHlp();
            DisplayClientHlp();
            return(1);
        }

        QueryRemotePipes(argv[2]);  //  Send ServerName as a param
        return(0);


    case 'p':
    case 'P':

        //
        // Is Client End of Remote
        //

        bPromptForArgs=TRUE;
        RunType=RUNTYPE_CLIENT;
        FirstArg=2;
        break;


    case 's':
    case 'S':
        //
        // Is Server End of Remote
        //
        if ((argc<4)||((argv[1][0]!='/')&&(argv[1][0]!='-')))
        {

            DisplayServerHlp();
            DisplayClientHlp();
            return(1);
        }

        ChildCmd=argv[2];
        PipeName=argv[3];
        FirstArg=4;

        RunType=REMOTE_SERVER;
        break;


    case 'a':
    case 'A':
        //
        // Is Server End of Remote Attaching to existing process.
        //
        if ((argc<7)||((argv[1][0]!='/')&&(argv[1][0]!='-')))
        {

            DisplayServerHlp();
            DisplayClientHlp();
            return(1);
        }

        hAttachedProcess = (HANDLE) atoi(argv[2]);
        hAttachedWriteChildStdIn = (HANDLE) atoi(argv[3]);
        hAttachedReadChildStdOut = (HANDLE) atoi(argv[4]);
        ChildCmd=argv[5]; // for display only
        PipeName=argv[6];
        FirstArg=7;

        RunType = REMOTE_SERVER;
        privacy = PRIVACY_VISIBLE;  // presumably ntsd/*kd
        break;


    default:
        DisplayServerHlp();
        DisplayClientHlp();
        return(1);
    }

    if (RunType==REMOTE_SERVER)
    {
        //
        // Base Name of Executable
        // For setting the title
        //

        char *tcmd=ChildCmd;

        while ((*tcmd!=' ')    &&(*tcmd!=0))   tcmd++;
        while ((tcmd!=ChildCmd)&&(*tcmd!='\\'))tcmd--;
        if (*tcmd=='\\') tcmd++;
        sprintf(sTitle,"%-s  [Remote /C %s %s]",tcmd,HostName,PipeName);
    }

    //
    //Process Common (Optional) Parameters
    //

    for (i=FirstArg;i<argc;i++)
    {

        if ((argv[i][0]!='/')&&(argv[i][0]!='-'))
        {
            printf("Invalid parameter %s:Ignoring\n",argv[i]);
            continue;
        }

        switch(argv[i][1])
        {
        case 'l':    // Only Valid for client End
        case 'L':    // Max Number of Lines to recieve from Server
            i++;
            if (i>=argc)
            {
                printf("Incomplete Param %s..Ignoring\n",argv[i-1]);
                break;
            }
            LinesToSend=(DWORD)atoi(argv[i])+1;
            break;

        case 't':    // Title to be set instead of the default
        case 'T':
            i++;
            if (i>=argc)
            {
                printf("Incomplete Param %s..Ignoring\n",argv[i-1]);
                break;
            }
            sprintf(sTitle,"%s",argv[i]);
            break;

        case 'b':    // Background color
        case 'B':
            i++;
            if (i>=argc)
            {
                printf("Incomplete Param %s..Ignoring\n",argv[i-1]);
                break;
            }
            {
                WORD col=GetColorNum(argv[i]);
                if (col!=0xffff)
                {
                    wAttrib=col<<4|(wAttrib&0x000f);
                }
                break;
            }

        case 'f':    // Foreground color
        case 'F':
            i++;
            if (i>=argc)
            {
                printf("Incomplete Param %s..Ignoring\n",argv[i-1]);
                break;
            }
            {
                WORD col=GetColorNum(argv[i]);
                if (col!=0xffff)
                {
                    wAttrib=col|(wAttrib&0x00f0);
                }
                break;
            }

        case 'v':
        case 'V':
            privacy = PRIVACY_VISIBLE;
            break;

        case '-':
            if( (argv[i][2] == 'v')
                || (argv[i][2] == 'V'))
                privacy = PRIVACY_NOT_VISIBLE;
            else
                printf("Unknown Parameter=%s %s\n",argv[i-1],argv[i]);
            break;

        case 'q':
        case 'Q':
            ClientToServerFlag|=0x80000000;
            break;

        case 'u':
        case 'U':
            if ( (argv[i][2] == 'd') ||
                 (argv[i][2] == 'D' ) )
            {
                Deny = TRUE ;
            }
            else
            {
                Deny = FALSE ;
            }

            i++ ;

            if ( i >= argc )
            {
                printf( "Incomplete Param %s..Ignoring\n", argv[i-1] );
                break;
            }

            if ( Deny )
            {
                if (DaclDenyNameCount == MAX_DACL_NAMES )
                {
                    printf("Too many names specified (max %d).  Ignoring user %s\n",
                            MAX_DACL_NAMES, argv[i] );

                    break;
                }

                DaclDenyNames[ DaclDenyNameCount++ ] = argv[i];

            }
            else
            {
                if (DaclNameCount == MAX_DACL_NAMES )
                {
                    printf("Too many names specified (max %d).  Ignoring user %s\n",
                            MAX_DACL_NAMES, argv[i] );

                    break;
                }

                DaclNames[ DaclNameCount++ ] = argv[i];

            }

            break;

        case '2':
            bForceTwoPipes = TRUE;
            break;

        default:
            printf("Unknown Parameter=%s %s\n",argv[i-1],argv[i]);
            break;

        }

    }

    //
    //Now Set various Parameters
    //

    //
    //Colors
    //

    SetColor(wAttrib);

    if (RunType==RUNTYPE_CLIENT)
    {
        BOOL done=FALSE;
        BOOL gotinfo;

        //
        // Set Client end defaults and start client
        //

        while(!done)
        {
            if (!bPromptForArgs ||
                (gotinfo = GetNextConnectInfo(&ServerName,&PipeName))
               )
            {
                sprintf(sTitle,"Remote /C %s %s",ServerName,PipeName);
                SetConsoleTitle(sTitle);

                //
                // Start Client (Client.C)
                //
                Client(ServerName,PipeName);
            }
            done = !bPromptForArgs || !gotinfo;
        }
    }

    if (RunType==REMOTE_SERVER)
    {
        if (privacy == PRIVACY_VISIBLE ||
             (privacy == PRIVACY_DEFAULT && IsKdString(ChildCmd))) {

            sprintf(sTitle, "%s visible", sTitle);
            IsAdvertise = TRUE;
        }

        SetConsoleTitle(sTitle);

        i = OverlappedServer(ChildCmd, PipeName);
    }

    //
    //Reset Colors
    //
    SetColor(csbiOriginal.wAttributes);
    SetConsoleTitle(orgTitle);

    return i;
}

/*************************************************************/
VOID
ErrorExit(
    char* str
    )
{
    extern PSZ pszPipeName;
    DWORD dwErr;

    dwErr = GetLastError();

    printf("REMOTE error %d: %s\n", dwErr, str);

    #if DBG
    {
        char szMsg[1024];

        sprintf(szMsg, "REMOTE error %d: %s\n", dwErr, str);
        OutputDebugString(szMsg);

        if (pszPipeName) {               // ad-hoc:  if server
            if (IsDebuggerPresent()) {
                DebugBreak();
            }
        }
    }
    #endif

    exit(1);
}

/*************************************************************/
VOID
DisplayClientHlp()
{
    printf("\n"
           "   To Start the CLIENT end of REMOTE\n"
           "   ---------------------------------\n"
           "   Syntax : REMOTE /C <ServerName> <Unique Id> [Param]\n"
           "   Example: REMOTE /C %s imbroglio\n"
           "            This would connect to a server session on %s with Id\n"
           "            \"imbroglio\" if there is a REMOTE /S <\"Cmd\"> imbroglio\n"
           "            running on %s.\n\n"
           "   To Exit: %cQ (Leaves the Remote Server Running)\n"
           "   [Param]: /L <# of Lines to Get>\n"
           "   [Param]: /F <Foreground color eg blue, lred..>\n"
           "   [Param]: /B <Background color eg cyan, lwhite..>\n"
           "\n"
           "   To Query the visible sessions on a server\n"
           "   -----------------------------------------\n"
           "   Syntax:  REMOTE /Q %s\n"
           "            This would retrieve the available <Unique Id>s\n"
           "            visible connections on the computer named %s.\n"
           "\n",
           HostName, HostName, HostName, COMMANDCHAR, HostName, HostName);
}
/*************************************************************/

VOID
DisplayServerHlp()
{
    printf("\n"
           "   To Start the SERVER end of REMOTE\n"
           "   ---------------------------------\n"
           "   Syntax : REMOTE /S <\"Cmd\">     <Unique Id> [Param]\n"
           "   Example: REMOTE /S \"i386kd -v\" imbroglio\n"
           "            To interact with this \"Cmd\" from some other machine,\n"
           "            start the client end using:  REMOTE /C %s imbroglio\n\n"
           "   To Exit: %cK \n"
           "   [Param]: /F  <Foreground color eg yellow, black..>\n"
           "   [Param]: /B  <Background color eg lblue, white..>\n"
           "   [Param]: /U  username or groupname\n"
           "                specifies which users or groups may connect\n"
           "                may be specified more than once, e.g\n"
           "                /U user1 /U group2 /U user2\n"
           "   [Param]: /UD username or groupname\n"
           "                specifically denies access to that user or group\n"
           "   [Param]: /V  Makes this session visible to remote /Q\n"
           "   [Param]: /-V Hides this session from remote /q (invisible)\n"
           "                By default, if \"Cmd\" looks like a debugger,\n"
           "                the session is visible, otherwise not\n"
           "\n",
           HostName, COMMANDCHAR);
}

WORD
GetColorNum(
    char *color
    )
{
    int i;

    _strlwr(color);
    for (i=0;i<16;i++)
    {
        if (strcmp(ColorList[i],color)==0)
        {
            return(i);
        }
    }
    return ((WORD)atoi(color));
}

VOID
SetColor(
    WORD attr
    )
{
    COORD  origin={0,0};
    DWORD  dwrite;
    FillConsoleOutputAttribute
    (
        MyStdOut,attr,csbiOriginal.dwSize.
        X*csbiOriginal.dwSize.Y,origin,&dwrite
    );
    SetConsoleTextAttribute(MyStdOut,attr);
}

BOOL
GetNextConnectInfo(
    char** SrvName,
    char** PipeName
    )
{
    char *s;
    static char szServerName[64];
    static char szPipeName[32];

    try
    {
        ZeroMemory(szServerName,64);
        ZeroMemory(szPipeName,32);
        SetConsoleTitle("Remote - Prompting for next Connection");
        printf("Debugger machine (server): ");
        fflush(stdout);

        if (((*SrvName=gets(szServerName))==NULL)||
             (strlen(szServerName)==0))
        {
            return(FALSE);
        }

        if (szServerName[0] == COMMANDCHAR &&
            (szServerName[1] == 'q' || szServerName[1] == 'Q')
           )
        {
            return(FALSE);
        }

        if (s = strchr( szServerName, ' ' )) {
            *s++ = '\0';
            while (*s == ' ') {
                s += 1;
            }
            *PipeName=strcpy(szPipeName, s);
            printf(szPipeName);
            fflush(stdout);
        }
        if (strlen(szPipeName) == 0) {
            printf("Target machine (pipe)    : ");
            fflush(stdout);
            if ((*PipeName=gets(szPipeName))==NULL)
            {
                return(FALSE);
            }
        }

        if (s = strchr(szPipeName, ' ')) {
            *s++ = '\0';
        }

        if (szPipeName[0] == COMMANDCHAR &&
            (szPipeName[1] == 'q' || szPipeName[1] == 'Q')
           )
        {
            return(FALSE);
        }
        printf("\n\n");
    }

    except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(FALSE);  // Ignore exceptions
    }
    return(TRUE);
}


/*************************************************************/

VOID
Errormsg(
    char* str
    )
{
    printf("Error (%d) - %s\n",GetLastError(),str);
}

/*************************************************************/

BOOL
IsKdString(
    char* string
    )
{

    char* start;

    //
    // some heuristic for uninvented yet platforms
    // if the first word has "kd" in it ok
    //

    if(    ((start = strstr(string, "kd")) != NULL)
        || ((start = strstr(string, "dbg")) != NULL)
        || ((start = strstr(string, "remoteds")) != NULL)
        || ((start = strstr(string, "ntsd")) != NULL)
        || ((start = strstr(string, "cdb")) != NULL) )
    {
        // is it in the first word?
        while(--start > string)
        {
            if((*start == ' ') || (*start == '\t'))
            {
                while(--start > string)
                    if((*start != '\t') || (*start != ' '))
                        return(FALSE);
            }
        }
        return TRUE;
    }
    return(FALSE);
}


//
// WriteFileSynch is a synchronous WriteFile for overlapped
// file handles.  As a special case, two-pipe client operation
// sets fAsyncPipe FALSE and this routine then passes NULL
// for lpOverlapped.
//

BOOL
FASTCALL
WriteFileSynch(
    HANDLE  hFile,
    LPVOID  lpBuffer,
    DWORD   cbWrite,
    LPDWORD lpNumberOfBytesWritten,
    DWORD   dwFileOffset,
    LPOVERLAPPED lpO
    )
{
    BOOL Success;


    lpO->OffsetHigh = 0;
    lpO->Offset = dwFileOffset;

    Success =
        WriteFile(
            hFile,
            lpBuffer,
            cbWrite,
            lpNumberOfBytesWritten,
            fAsyncPipe ? lpO : NULL
            );

    if ( ! Success ) {

        if (ERROR_IO_PENDING == GetLastError()) {

            Success =
                GetOverlappedResult(
                    hFile,
                    lpO,
                    lpNumberOfBytesWritten,
                    TRUE
                    );
        }
    }

    return Success;
}


BOOL
FASTCALL
ReadFileSynch(
    HANDLE  hFile,
    LPVOID  lpBuffer,
    DWORD   cbRead,
    LPDWORD lpNumberOfBytesRead,
    DWORD   dwFileOffset,
    LPOVERLAPPED lpO
    )
{
    BOOL Success;

    lpO->OffsetHigh = 0;
    lpO->Offset = dwFileOffset;

    Success =
        ReadFile(
            hFile,
            lpBuffer,
            cbRead,
            lpNumberOfBytesRead,
            fAsyncPipe ? lpO : NULL
            );

    if ( ! Success ) {

        if (ERROR_IO_PENDING == GetLastError()) {

            Success =
                GetOverlappedResult(
                    hFile,
                    lpO,
                    lpNumberOfBytesRead,
                    TRUE
                    );
        }
    }

    return Success;
}
