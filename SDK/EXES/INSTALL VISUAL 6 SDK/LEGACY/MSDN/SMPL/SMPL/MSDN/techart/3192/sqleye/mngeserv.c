//****************************** Function Header ******************************
//
// Function : MngeServ
//
// Description: Functions to manage the server
//
// Author PeterWil 1994, Microsoft Ltd.
//*****************************************************************************
#define DBNTWIN32

// Standard compiler and SQL header files
#include    <windows.h>
#include    <sqlfront.h>
#include    <srv.h>

// Application specific header files
#include    "mngeserv.h"
#include    "initremo.h"

extern SRV_SERVER *server;

// Stop anyone else from connecting
int ServerSleep(SRV_PROC *srvproc)
{
    // When we get a connection request from a client, we want to
    // call "DoNotInitRemote()" to not make a connection to the remote
    // server.
    if (server) 
        srv_handle(server, (DBINT)SRV_CONNECT, DoNotInitRemote);
    return (SRV_CONTINUE);
}

// Allow new people to connect                                 
int ServerRestart(SRV_PROC *srvproc)
{
    // When we get a connection request from a client, we want to
    // call "InitRemote()" to make a connection to the remote
    // server.
    if (server)
        srv_handle(server, (DBINT)SRV_CONNECT, InitRemote);
    return (SRV_CONTINUE);
}

