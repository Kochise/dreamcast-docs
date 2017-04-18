/*
Copyright (c) 1994, 1993 Microsoft Corporation

Module Name:
    Remote.c

Abstract:
    This module contains the main() entry point for Remote.
    Calls the Server or the Client depending on the first parameter.

Author:
    Rajivendra Nath (rajnath) 2-Jan-1993

Environment:
    Console App. User mode.

Revision History:
	Alex Wetmore (t-alexwe) 6-Jun-1994
		- converted remote to use APPC with Windows SNA Server instead of named
		  pipes
*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <winappc.h>
#include "appclib.h"
#include "aremote.h"

TCHAR   HostName[HOSTNAMELEN];
TCHAR   *ChildCmd;
TCHAR   *TPName = TEXT("AREMOTE");
TCHAR   *locTPName = TEXT("AREMOTC");
TCHAR   *LocalLU = TEXT("AREMOTE");
TCHAR   *ServerLU;
TCHAR   *mode_name = TEXT("#INTER");
HANDLE MyOutHandle;
BOOL   IsAdvertise=TRUE;
DWORD  ClientToServerFlag;
BOOL   AutoStarted;


TCHAR	ChildCmdBuffer[1024];

TCHAR* ColorList[]={TEXT("black") ,TEXT("blue") ,TEXT("green") ,TEXT("cyan") ,TEXT("red") ,TEXT("purple") ,TEXT("yellow") ,TEXT("white"),
                   TEXT("lblack"),TEXT("lblue"),TEXT("lgreen"),TEXT("lcyan"),TEXT("lred"),TEXT("lpurple"),TEXT("lyellow"),TEXT("lwhite")};

int __cdecl main(void);

WORD GetColorNum(TCHAR* color);
VOID SetColor(WORD attr);

CONSOLE_SCREEN_BUFFER_INFO csbiOriginal;

/*************************************************************/
VOID ErrorExit(TCHAR *str) {
    WRITEF((VBuff,TEXT("Error-%d:%s\n"),GetLastError(),str));
    ExitProcess(1);
}
/*************************************************************/
DWORD ReadFixBytes(HANDLE hRead, TCHAR*  Buffer, DWORD  ToRead,
    DWORD  TimeOut) {   //ignore timeout for timebeing
    DWORD xyzBytesRead=0;
    DWORD xyzBytesToRead=ToRead;
    TCHAR* xyzbuff=Buffer;

    while(xyzBytesToRead!=0)
    {
        if (!ReadFile(hRead,xyzbuff,xyzBytesToRead,&xyzBytesRead,NULL))
        {
            return(xyzBytesToRead);
        }

        xyzBytesToRead-=xyzBytesRead;
        xyzbuff+=xyzBytesRead;
    }
    return(0);

}
/*************************************************************/
VOID DisplayClientHlp() {
    WRITEF((VBuff,TEXT("\n   To Start the CLIENT end of AREMOTE\n")));
    WRITEF((VBuff,TEXT("   ---------------------------------\n")));
    WRITEF((VBuff,TEXT("   Syntax : AREMOTE /C <ServerLU> [/T <TPName>] [/P <TPName>] [/L <LocalLU>]\n")));
    WRITEF((VBuff,TEXT("                                  [/N <# lines>] [/M <Modename>]\n")));
	WRITEF((VBuff,TEXT("                                  [/F <Color>] [/B <Color>]\n")));
    WRITEF((VBuff,TEXT("\n")));

    WRITEF((VBuff,TEXT("   <ServerLU>      SNA LU for connecting to Server\n")));

	WRITEF((VBuff,TEXT("   [/T <TPName>]   TP name that server is using (default is \"%s\")\n"), TPName));
	WRITEF((VBuff,TEXT("   [/P <TPName>]   TP name that client is using (default is \"%s\")\n"), locTPName));
	WRITEF((VBuff,TEXT("   [/M <Modename>] The mode by which the Local LU and Server LU are partnered\n")));
	WRITEF((VBuff,TEXT("                   (defaults to \"%s\")\n"), mode_name));
	WRITEF((VBuff,TEXT("   [/L <LocalLU>]  LU name for local TP to use (default is \"%s\")\n"), LocalLU));
    WRITEF((VBuff,TEXT("   [/N <# lines>]  Number of Lines to Get.\n")));
    WRITEF((VBuff,TEXT("   [/F <color>]    Foreground color eg blue, red, etc.\n")));
    WRITEF((VBuff,TEXT("   [/B <color>]    Background color eg blue, lwhite,etc.\n")));
    WRITEF((VBuff,TEXT("\n")));
    WRITEF((VBuff,TEXT("   Example: aremote /C serverlu\n")));
    WRITEF((VBuff,TEXT("\n")));
    WRITEF((VBuff,TEXT("   To Exit: %cQ (Leaves the Remote Server Running)\n"), COMMANDCHAR));
    WRITEF((VBuff,TEXT("\n")));
}
/*************************************************************/

VOID DisplayServerHlp() {
    WRITEF((VBuff,TEXT("\n   To Start the SERVER end of AREMOTE\n")));
    WRITEF((VBuff,TEXT("   ---------------------------------\n")));
    WRITEF((VBuff,TEXT("   Syntax : AREMOTE /S \"<Cmd>\" [/T <TPName>] [/F <color>] [/B <color>]\n")));
    WRITEF((VBuff,TEXT("\n")));

    WRITEF((VBuff,TEXT("   \"<Cmd>\"         A Text-Mode program that you want to control\n")));
    WRITEF((VBuff,TEXT("                   from another computer.\n")));

	WRITEF((VBuff,TEXT("   [/T <TPName>]   TP name that server is using (default is \"%s\")\n"), TPName));
    WRITEF((VBuff,TEXT("   [/F <color>]    Foreground color eg blue, red, etc.\n")));
    WRITEF((VBuff,TEXT("   [/B <color>]    Background color eg blue, lwhite, etc.\n")));

    WRITEF((VBuff,TEXT("\n")));
    WRITEF((VBuff,TEXT("   Example: aremote /S \"cmd\"\n")));
    WRITEF((VBuff,TEXT("\n")));
    WRITEF((VBuff,TEXT("   To Exit: %cK from Client\n"), COMMANDCHAR));
    WRITEF((VBuff,TEXT("\n")));

}

WORD GetColorNum(TCHAR *color) {
    int i;

    _wcslwr(color);
    for (i=0;i<16;i++)
    {
        if (lstrcmp(ColorList[i],color)==0)
        {
            return(i);
        }
    }
    return 0xffff;
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
    	MyOutHandle,attr,csbiOriginal.dwSize.
    	X*csbiOriginal.dwSize.Y,origin,&dwrite
    );
    SetConsoleTextAttribute(MyOutHandle,attr);
}

/*************************************************************/
VOID
Errormsg(
    TCHAR* str
    )
{
    WRITEF((VBuff,TEXT("Error (%d) - %s\n"),GetLastError(),str));
}

/*************************************************************/

/*
 * this main procedure gets called by the appropriate main depending on
 * if AREMOTE is setup as a service or not.
 */
int remote_main(int argc, TCHAR **argv) {
    WORD  RunType;              // Server or Client end of Remote
    DWORD len=HOSTNAMELEN-1;
    int   i;

    TCHAR  sTitle[100];          // New Title
    TCHAR  orgTitle[100];        // Old Title
    BOOL  bSetAttrib=FALSE;     // Change Console Attributes
    WORD  wAttrib;              // Console Attributes
	char  abuff[1024];		// temporary ansi buffer

    GetComputerName((LPTSTR)HostName,&len);

    MyOutHandle=GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(MyOutHandle,&csbiOriginal);

    // Parameter Processing
    //
    // For Server:
    // Remote /S <Executable> [Optional Params]
	//
	// For AutoStarted TP:
	// Remote /A <Executable> [Optional Params]
	//   - this case is handled in main()
    //
    // For Client:
    // Remote /C <Server LU> [Optional Params]

    if ((argc < 2)||((argv[1][0] != TEXT('/'))&&(argv[1][0] != TEXT('-')))) {
        DisplayServerHlp();
        DisplayClientHlp();
		WRITEF((VBuff, TEXT("\nFor server help only: aremote /s")));
		WRITEF((VBuff, TEXT("\nFor client help only: aremote /c")));
        return(1);
    }

    switch(tolower(argv[1][1])) {
    	case TEXT('c'):
        	// Is Client End of Remote
        	if ((argc < 3) || ((argv[1][0] != TEXT('/')) && (argv[1][0] != TEXT('-')))) {
            	DisplayClientHlp();
            	return 1;
        	}

			ServerLU = _wcsupr(argv[2]);

	        RunType=REMOTE_CLIENT;
        	break;

    	case TEXT('s'):
	        // Is Server End of Remote
        	if ((argc < 3) || ((argv[1][0] != TEXT('/')) && (argv[1][0] != TEXT('-')))) {
            	DisplayServerHlp();
            	return 1;
        	}

        	ChildCmd = argv[2];

        	RunType = REMOTE_SERVER;
        	break;

    	default:
        	DisplayServerHlp();
        	DisplayClientHlp();
			WRITEF((VBuff, TEXT("\nFor server help only: aremote /s")));
			WRITEF((VBuff, TEXT("\nFor client help only: aremote /c")));
		 	return(1);
    }

    //
    // Save Existing Values
    //

    //
    //Colors /f   <ForeGround> /b <BackGround>
    //

    wAttrib = csbiOriginal.wAttributes;

    GetConsoleTitle(orgTitle,sizeof(orgTitle));

    if (RunType == REMOTE_SERVER) {
    	//
    	// Base Name of Executable
    	// For setting the title
    	//

        TCHAR *tcmd=ChildCmd;

        while ((*tcmd!=TEXT(' '))    &&(*tcmd!=0))   tcmd++;
        while ((tcmd!=ChildCmd)&&(*tcmd!=TEXT('\\')))tcmd--;

        wsprintf(sTitle,TEXT("%8.8s [Remote /C %s %s]"),tcmd,HostName,TPName);
    }

    //
    //Process Common (Optional) Parameters
    //

    for (i = 3; i < argc; i++) {

        if ((argv[i][0] != TEXT('/')) && (argv[i][0] != TEXT('-'))) {
            WRITEF((VBuff,TEXT("Invalid parameter %s:Ignoring\n"),argv[i]));
            continue;
        }

        switch(tolower(argv[i][1])) {
        	case TEXT('n'):   // Only Valid for client End, max number of lines to get from server
            	i++;
            	if (i >= argc) {
                	WRITEF((VBuff,TEXT("Incomplete Param %s..Ignoring\n"),argv[i-1]));
                	break;
            	}
				wcstombs(abuff, argv[i], 1024);
            	LinesToSend=(DWORD)atoi(abuff)+1;
            	break;

			case TEXT('l'):	// name of LU for client to use
				i++;
				if (i >= argc) {
                	WRITEF((VBuff,TEXT("Incomplete Param %s..Ignoring\n"),argv[i-1]));
                	break;
            	}
				LocalLU = _wcsupr(argv[i]);
				break;
        	
			case TEXT('m'):	// name of LU-LU connection mode
				i++;
				if (i >= argc) {
                	WRITEF((VBuff,TEXT("Incomplete Param %s..Ignoring\n"),argv[i-1]));
                	break;
            	}
				mode_name = _wcsupr(argv[i]);
				break;
        	
			case TEXT('t'):	// name of tp
				i++;
				if (i >= argc) {
                	WRITEF((VBuff,TEXT("Incomplete Param %s..Ignoring\n"),argv[i-1]));
                	break;
            	}
				TPName = _wcsupr(argv[i]);
				break;
        	
   			case TEXT('p'):	// name of tp
				i++;
				if (i >= argc) {
                	WRITEF((VBuff,TEXT("Incomplete Param %s..Ignoring\n"),argv[i-1]));
                	break;
            	}
				locTPName = _wcsupr(argv[i]);
				break;
        	
        	case TEXT('b'):   // Background color
        	    i++;
	            if (i >= argc) {
	                WRITEF((VBuff,TEXT("Incomplete Param %s..Ignoring\n"),argv[i-1]));
                	break;
            	}
            	{
                	WORD col = GetColorNum(argv[i]);
                	if (col != 0xffff) {
                    	bSetAttrib = TRUE;
                    	wAttrib = col << 4 | (wAttrib & 0x000f);
                	}
                	break;
            	}

        	case TEXT('f'):   // Foreground color
            	i++;
            	if (i>=argc) {
                	WRITEF((VBuff,TEXT("Incomplete Param %s..Ignoring\n"),argv[i-1]));
                	break;
            	}
            	{
	                WORD col = GetColorNum(argv[i]);
                	if (col != 0xffff) {
                    bSetAttrib = TRUE;
                    wAttrib = col | (wAttrib & 0x00f0);
                }
                break;
            }

        	case TEXT('q'):
            	IsAdvertise = FALSE;
            	ClientToServerFlag |= 0x80000000;
            	break;

        	default:
            	WRITEF((VBuff,TEXT("Unknown Parameter=%s %s\n"),argv[i-1],argv[i]));
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

    if (RunType==REMOTE_CLIENT) {
        // Start Client (Client.C)
        Client(LocalLU, ServerLU, TPName, locTPName, mode_name);
    }

    if (RunType==REMOTE_SERVER) {
        // Start Server (Server.C)
        Server(ChildCmd, TPName);
    }

    //
    //Reset Colors
    //
    SetColor(csbiOriginal.wAttributes);

    ExitProcess(0);

	return	0;		// satisfy the ppc compiler; statement never reached
}

/*****************************************************************************/
/* The following code makes this TP invokable as an NT service. There are 3  */
/* routines.                                                                 */
/*                                                                           */
/* 1. main. This is the entry point for the process, it sets up a service    */
/*          table entry and then calls StartServiceCtrlDispatcher. This call */
/*          doesn't return, but uses the thread which called it as a         */
/*          control dispatcher for all the services implemented by this      */
/*          process (in this case, just the TP itself).                      */
/*                                                                           */
/* 2. ServiceMain. This is the main entry point for the service itself, the  */
/*          service control dispatcher creates a thread to start at this     */
/*          routine. It must register a service control handler for the      */
/*          service which will be called by the control dispatcher when it   */
/*          has control instructions for the service. It then informs the    */
/*          service control manager that the service is running and finally  */
/*          calls the start of the TP itself. This routine should not return */
/*          until the service is ready to die.                               */
/*                                                                           */
/* 3. ControlHandler. This routine is called by the control dispatcher when  */
/*          it has instructions for the service. We do not respond to any    */
/*          of the instructions as this service should be transitory and not */
/*          actually run for more than a few seconds so we don't need to do  */
/*          anything with the STOP or SHUTDOWN requests.                     */
/*          Note that we MUST call SetServiceStatus, even if the status      */
/*          hasn't changed.                                                  */
/*****************************************************************************/

VOID WINAPI ServiceMain(DWORD dwNumServiceArgs, LPTSTR * lpServiceArgs);
VOID WINAPI ControlHandler(DWORD dwControl);
SERVICE_STATUS_HANDLE stat_hand;
SERVICE_STATUS servstat;

int __cdecl main(void) {
	SERVICE_TABLE_ENTRY stab[2];
	int 	argc, i;
	TCHAR 	*argv[50];
	TCHAR	cmdline[1024];

	// read the command line and break it out into argc/argv.  We have to do
	// this because the standard command line passed into main isn't in Unicode
	lstrcpy(cmdline, GetCommandLine());
	i = 0; argc = 0;
	argv[argc] = &(cmdline[i]);
	while (cmdline[i] != 0) {
		if (cmdline[i] == TEXT(' ')) {
			cmdline[i++] = 0;
			argv[++argc] = &(cmdline[i]);
		}
		i++;
	}
	argc++;

	if ((argc >= 3) &&
	    (tolower(argv[1][1]) == TEXT('a')) &&
	    ((argv[1][0] == TEXT('/')) || (argv[1][0] == TEXT('-')))) {

		AutoStarted = TRUE;

		//
		// hack to fix NET START AREMOTE bug. Since we're not autostarted
		// by an SNA Server component we have no control over the service
		// cmd line.  Therefore we copy out the 3rd parameter passed to the
		// service process and use it if and only there are less than 3 params
		// passed to StartService
		//
		lstrcpy( ChildCmdBuffer, argv[2] );

		//
		//
		// This is being run as a service
		//
		//
		// Start the control dispatcher. This call gives the SCManager this
		// thread for the entire period that this service is running, so that
		// it can call us back with service controls. It will spawn a new
		// thread to run the service itself, starting at entrypoint ServiceMain
		//
		stab[0].lpServiceName = TEXT("AREMOTE\0");
		stab[0].lpServiceProc = (LPSERVICE_MAIN_FUNCTION) ServiceMain;

		stab[1].lpServiceName = NULL;
		stab[1].lpServiceProc = NULL;

		if (!StartServiceCtrlDispatcher(stab)) {
			WRITEF((VBuff, TEXT("Remote: This was run as an service\n\n")));
			WRITEF((VBuff, TEXT("For command line usage type \"Remote\"\n")));
		}
	} else {
		//
		// This is being run as a user-invoked program
		//
		AutoStarted = FALSE;
		remote_main(argc, argv);
	}

	return 0;
}


/*****************************************************************************/
/* This routine is the entry-point for the service itself the service        */
/* control dispatcher creates a thread to start here when we issue           */
/* StartServiceControlDispatcher.                                            */
/*                                                                           */
/* Inputs:  number of arguments to services, array of strings.               */
/*                                                                           */
/* Outputs: none                                                             */
/*                                                                           */
/*****************************************************************************/
VOID WINAPI ServiceMain(DWORD argc, LPTSTR *argv) {
	DWORD rc;

	stat_hand = RegisterServiceCtrlHandler(TEXT("AREMOTE\0"),
		(LPHANDLER_FUNCTION) ControlHandler);

	if (stat_hand == (SERVICE_STATUS_HANDLE)NULL) {
		rc = GetLastError();
		DebugBreak();
	}

	/*************************************************************************/
	/* Let the SCManager know that we are running.                           */
	/*************************************************************************/
	servstat.dwServiceType              = SERVICE_WIN32;
	servstat.dwCurrentState             = SERVICE_RUNNING;
	servstat.dwControlsAccepted			= SERVICE_ACCEPT_STOP |
											SERVICE_ACCEPT_SHUTDOWN;
	servstat.dwWin32ExitCode            = NO_ERROR;
	servstat.dwServiceSpecificExitCode  = NO_ERROR;
	servstat.dwCheckPoint               = 0;
	servstat.dwWaitHint                 = 0;

	rc = SetServiceStatus(stat_hand, &servstat);

	if (!rc) {
		rc = GetLastError();
		DebugBreak();
	}

	{
		int new_argc = 3;
		TCHAR *new_argv[3];

		new_argv[0] = argv[0];
		new_argv[1] = (TCHAR *) LocalAlloc(0, 16);
		lstrcpy(new_argv[1], TEXT("/s"));

		if ( argc < 3 )
		{
			//
			// hack to fix NET START AREMOTE bug. Since we're not autostarted
			// by an SNA Server component we have no control over the service
			// cmd line.  Therefore we copy out the 3rd parameter passed to the
			// service process and use it if and only there are less than 3 params
			// passed to StartService
			//
			new_argv[2] = ChildCmdBuffer;
		}
		else
		{
			new_argv[2] = argv[2];
		}


		remote_main(new_argc, (TCHAR **) new_argv);

		LocalFree(new_argv[1]);
	}
}

/***************************************************************************/
/* This routine is the callback from the SCManager to handle specific      */
/* service control requests. It MUST call SetServiceStatus before it       */
/* returns, regardless of whether the status has changed.                  */
/*                                                                         */
/* Inputs: service control requested                                       */
/*                                                                         */
/* Outputs: none                                                           */
/*                                                                         */
/***************************************************************************/
VOID WINAPI ControlHandler(DWORD dwControl) {
	DWORD rc;

	switch (dwControl) {
		case SERVICE_CONTROL_STOP :
			servstat.dwCurrentState = SERVICE_STOP_PENDING;
			servstat.dwWaitHint     = 24000;
			break;

		case SERVICE_CONTROL_PAUSE :
		case SERVICE_CONTROL_CONTINUE :
		case SERVICE_CONTROL_INTERROGATE :
			servstat.dwWaitHint     = 0;
			break;

		case SERVICE_CONTROL_SHUTDOWN:
			servstat.dwCurrentState = SERVICE_STOP_PENDING;
			servstat.dwWaitHint     = 10000;
			break;
	}

	rc=SetServiceStatus(stat_hand, &servstat);
	if (!rc) {
		rc=GetLastError();
	}
}
