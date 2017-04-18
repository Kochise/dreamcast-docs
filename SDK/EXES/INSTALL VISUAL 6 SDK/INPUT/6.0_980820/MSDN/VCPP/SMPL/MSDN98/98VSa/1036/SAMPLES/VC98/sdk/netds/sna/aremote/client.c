/*
Copyright (c) 1994, 1993 Microsoft Corporation

Module Name:
    Client.c

Abstract:
    The Client component of Remote. Connects to the remote
    server using named pipes. It sends its stdin to
    the server and output everything from server to
    its stdout.

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
#include <io.h>
#include <string.h>
#include <winappc.h>
#include "appclib.h"
#include "aremote.h"

tpconvid_t EstablishSession(TCHAR *locallu, TCHAR *serverlu, TCHAR *tpname, 
	TCHAR *loctpname, TCHAR *mode_name);
DWORD WINAPI GetServerOut(PVOID *Noarg);
DWORD WINAPI SendServerInp(PVOID *Noarg);
BOOL FilterClientInp(TCHAR *buff, int count);
BOOL Mych(DWORD ctrlT);
VOID SendMyInfo(tpconvid_t tpconv);


HANDLE iothreads[2];
HANDLE MyStdInp;
HANDLE MyStdOut;
tpconvid_t tpconv;


CONSOLE_SCREEN_BUFFER_INFO csbi;

TCHAR   MyEchoStr[30];
BOOL   CmdSent;
DWORD  LinesToSend=LINESTOSEND;

VOID Client(TCHAR *local_lu, TCHAR *server_lu, TCHAR *tp_name, 
	        TCHAR *loc_tp_name, TCHAR *mode_name) {
    DWORD  tid;


    MyStdInp=GetStdHandle(STD_INPUT_HANDLE);
    MyStdOut=GetStdHandle(STD_OUTPUT_HANDLE);

    WRITEF((VBuff,TEXT("**************************************\n")));
    WRITEF((VBuff,TEXT("***********     REMOTE    ************\n")));
    WRITEF((VBuff,TEXT("***********     CLIENT    ************\n")));
    WRITEF((VBuff,TEXT("**************************************\n")));

	tpconv = EstablishSession(local_lu, server_lu, tp_name, loc_tp_name, 
		mode_name);
	if (tpconv == NULL) {
		appcdestroy();
		return;
	}

    SetConsoleCtrlHandler((PHANDLER_ROUTINE)Mych,TRUE);

    // Start Thread For Server --> Client Flow
    if ((iothreads[0]=CreateThread((LPSECURITY_ATTRIBUTES)NULL,     // No security attributes.
            (DWORD)0,                           					// Use same stack size.
            (LPTHREAD_START_ROUTINE)GetServerOut, 					// Thread procedure.
            (LPVOID)NULL,              								// Parameter to pass.
            (DWORD)0,                           					// Run immediately.
            (LPDWORD)&tid))==NULL)              					// Thread identifier.
    {

        Errormsg(TEXT("Could Not Create rwSrv2Cl Thread"));
        return;
    }



    //
    // Start Thread for Client --> Server Flow
    //

    if ((iothreads[1]=CreateThread((LPSECURITY_ATTRIBUTES)NULL,           // No security attributes.
                    (DWORD)0,                           // Use same stack size.
                    (LPTHREAD_START_ROUTINE)SendServerInp, // Thread procedure.
                    (LPVOID)NULL,          // Parameter to pass.
                    (DWORD)0,                           // Run immediately.
                    (LPDWORD)&tid))==NULL)              // Thread identifier.
    {

        Errormsg(TEXT("Could Not Create rwSrv2Cl Thread"));
        return;
    }

    WaitForSingleObject(iothreads[0], INFINITE);

    TerminateThread(iothreads[1],1);

	appcclose(tpconv);
	appcdestroy();

	WRITEF((VBuff,TEXT("*** SESSION OVER ***\n")));
}


DWORD WINAPI GetServerOut(PVOID *Noarg) {
    TCHAR buffin[1024];
    DWORD dread=0,tmp;

	while (appcvalid(tpconv)) {
		dread = appcread(tpconv, (void *) buffin, 1000);
		if (dread > 0) {
			if (!WriteConsole(MyStdOut, buffin, dread/2, &tmp, NULL))
				break;
		}
	}
    return 1;
}

DWORD WINAPI SendServerInp(PVOID *Noarg) {
    TCHAR buff[1000];
    DWORD dread;
    SetLastError(0);

    while(ReadConsole(MyStdInp,buff,999,&dread,NULL)) {
        if (FilterClientInp(buff, dread)) continue;
		appcwrite(tpconv, (void *) buff, dread * sizeof(TCHAR));
    }
    return 0;
}

BOOL FilterClientInp(TCHAR *buff, int count) {
    if (count==0)
        return(TRUE);

    if (buff[0]==2)  //Adhoc screening of ^B so that i386kd/mipskd
        return(TRUE);//do not terminate.

    if (buff[0]==COMMANDCHAR) {
        switch (tolower(buff[1])) {
        	case TEXT('k'):
        	case TEXT('q'):
            	return(FALSE);

        	case TEXT('h'):
            	WRITEF((VBuff,TEXT("%cM : Send Message\n"),COMMANDCHAR));
            	WRITEF((VBuff,TEXT("%cP : Show Popup on Server\n"),COMMANDCHAR));
            	WRITEF((VBuff,TEXT("%cS : Status of Server\n"),COMMANDCHAR));
            	WRITEF((VBuff,TEXT("%cQ : Quit client\n"),COMMANDCHAR));
            	WRITEF((VBuff,TEXT("%cH : This Help\n"),COMMANDCHAR));
            	return(TRUE);

        	default:
	            return(FALSE);
        }

    }
    return(FALSE);
}


BOOL Mych(DWORD ctrlT) {
    TCHAR  c[3];
    DWORD send;

    if (ctrlT==CTRL_C_EVENT) {
		c[0] = 3;
		send = 1;
		appcwrite(tpconv, (void *) c, send);
    }
    if ((ctrlT==CTRL_BREAK_EVENT) ||
        (ctrlT==CTRL_CLOSE_EVENT) ||
        (ctrlT==CTRL_LOGOFF_EVENT) ||
        (ctrlT==CTRL_SHUTDOWN_EVENT)) {
		c[0] = COMMANDCHAR;
		c[1] = TEXT('q');
		send = 2;
		appcwrite(tpconv, (void *) c, send);
    }
    return(TRUE);
}

tpconvid_t EstablishSession(TCHAR *local_lu, TCHAR *server_lu, TCHAR *tp_name, 
                            TCHAR *loc_tp_name, TCHAR *mode_name) {
	TCHAR buf[255];
	tpconvid_t tpconv;

	appcinit();
	WRITEF((VBuff, TEXT("\nClient Connection Information:\n")));
	WRITEF((VBuff, TEXT("  Local LU       = %ws\n"), local_lu));
	WRITEF((VBuff, TEXT("  Server LU      = %ws\n"), server_lu));
	WRITEF((VBuff, TEXT("  Server TP Name = %ws\n"), tp_name));
	WRITEF((VBuff, TEXT("  Client TP Name = %ws\n"), loc_tp_name));
	WRITEF((VBuff, TEXT("  Mode Name      = %ws\n"), mode_name));
	WRITEF((VBuff, TEXT("\n")));
	WRITEF((VBuff, TEXT("Connecting . . . ")));

	// connect to the server
	tpconv = appcconnect(local_lu, server_lu, tp_name, loc_tp_name, mode_name);

	// the server will either send us zero bytes (signifying a valid 
	// connection), or close our connection.  If it is closed then
	// let the client know
	appcread(tpconv, buf, 255);
	if (!appcvalid(tpconv)) {
		WRITEF((VBuff, 
			TEXT("Remote: server doesn't have any available sessions\n")));
		return NULL;
	}
	if (lstrcmp(buf, REMOTE_INIT_MSG) != 0) {
		WRITEF((VBuff, 
			TEXT("Remote: this doesn't seem to be a remote server\n")));
		return NULL;
	}

	WRITEF((VBuff, TEXT("\rConnected        \n\n")));
	SendMyInfo(tpconv);

	return tpconv;
}

VOID SendMyInfo(tpconvid_t tpconv) {
    DWORD  hostlen=HOSTNAMELEN-1;
    DWORD  tmp, BytesToRead;
    SESSION_STARTUPINFO ssi;
    SESSION_STARTREPLY  ssr;
    TCHAR   *buff;

	// fill out the SESSION_STARTUPINFO structure
    ssi.MagicNumber = MAGICNUMBER;
    GetComputerName((TCHAR *) ssi.ClientName, &hostlen);
    ssi.LinesToSend = LinesToSend;
    ssi.Flag = ClientToServerFlag;
	appcwrite(tpconv, (void *) &ssi, sizeof(ssi));

	// receive a SESSION_STARTUPREPLY structure
	appcread(tpconv, (void *) &ssr, sizeof(ssr));

	if (ssr.MagicNumber < MAGICNUMBER) {
		WRITEF((VBuff, TEXT("Warning: this APPC Remote server is older than your client\n")));
	} else if (ssr.MagicNumber > MAGICNUMBER) {
		WRITEF((VBuff, TEXT("Warning: your APPC Remote client is older than the server \n")));
	}

    BytesToRead=MINIMUM(ssr.FileSize,ssi.LinesToSend*CHARS_PER_LINE);
    buff=calloc(BytesToRead+1,sizeof(TCHAR));
    if (buff!=NULL)
    {
        DWORD  bytesread=0;

        bytesread = appcread(tpconv, (void *) buff, BytesToRead*sizeof(TCHAR));

        WriteConsole(MyStdOut,buff,bytesread/sizeof(TCHAR),&tmp,NULL);
        LocalFree(buff);
    }

}
