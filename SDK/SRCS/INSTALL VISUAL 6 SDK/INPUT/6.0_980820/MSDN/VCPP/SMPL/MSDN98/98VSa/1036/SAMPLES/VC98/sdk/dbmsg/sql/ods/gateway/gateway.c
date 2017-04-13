// This program is an example of an Open Data Services application. It accepts
// requests from clients and then passes those requests on to an SQL server.
// The results from the SQL server are then sent back to the client.

#include    <stdlib.h>
#include    <stdio.h>
#include    <string.h>
#include    <windows.h>
#include    <sqlfront.h>
#include    <sqldb.h>
#include    <srv.h>

// Globals
//
DBCHAR *SrvrName = "";  // Default remote server name
DBCHAR *RegistryName = "Gateway";   // Default registry name

#define EXIT_OK 0
#define EXIT_ERROR 1

// function prototypes
//
void getargs(int argc, char **argv);

void main(int argc, char **argv);

int SRVAPI init_server(SRV_SERVER *server);

void SRVAPI set_remote_server_name(char *name);

int chk_err(SRV_SERVER *server, SRV_PROC *srvproc, int srverror,
            BYTE severity, BYTE state, int oserrnum, DBCHAR *errtext,
            int errtextlen, DBCHAR *oserrtext, int oserrtextlen);

void main(argc, argv)
int argc;
char *argv[];
{
    SRV_CONFIG *config; // The configuration structure
    SRV_SERVER *server; // The service process
    int exitcode = EXIT_ERROR;

    // Read any command line arguments.
    //
    getargs(argc, argv);

    // Send the name retrieved to the gateway's DLL module
    //
    set_remote_server_name(SrvrName);

    // Allocate a configuration structure that is used to initialize
    // the Open Data Services application
    //
    config = srv_config_alloc();

    // Allow 20 connections at a time.
    //
    srv_config(config, (DBINT)SRV_CONNECTIONS, "100", SRV_NULLTERM);

    // Set the log file.
    //
    srv_config(config, (DBINT)SRV_LOGFILE, "gateway.log", SRV_NULLTERM);

    // The gateway will not convert data source strings in order to allow
    // SQL Server and DB-libraray to coordinate on the codepage as usual.
    //
    srv_config(config, (DBINT)SRV_ANSI_CODEPAGE, "TRUE", SRV_NULLTERM);

    // Install the Open Data Services error handler.
    //
    srv_errhandle(chk_err);

    // Initialize the gateway and save the server handle
    // so it can be used in later functions.
    //
    server = srv_init(config, RegistryName, SRV_NULLTERM);
    if (server == NULL) {
        printf("Unable to initialize Gateway.\n");
        ExitProcess(exitcode);
    }

    // When starting the gateway, initialize the remote server structure.
    // This is done in the init_server() function.
    // All the other event handlers are also defined in the init_server()
    // function.
    //
    srv_handle(server, (DBINT)SRV_START, init_server);

    // Now everything's ready to go with our gateway, so we
    // start it and keep it going until we get a stop request.
    //
    srv_log(server, FALSE, " ", SRV_NULLTERM);  // insert blank line
    srv_log(server, TRUE, "Gateway Starting", SRV_NULLTERM);

    printf("\nGateway Starting\n");

    srv_run(server);

}

// GETARGS
//    Read the command line arguments.
//
// Parameters:
//     argc - int (from "main" entry)
//     argv - pointer to array of char pointers (from "main" entry)
//
// Returns:
//     VOID
//
void getargs(int argc, char *argv[])
{

    int i;
    char *ptr;
    int exitcode = EXIT_ERROR;

    for (i = 1; i < argc; ++i) {
        if (argv[i][0] != '-' && argv[i][0] != '/') {
            printf(
            "Usage: gateway -S<remote server name> [-R<registry key name>]\n");
                
            ExitProcess(exitcode);
        }
        ptr = argv[i];
        switch (ptr[1]) {

        case 'S':
            if (strlen(ptr + 2) > 0) {
                SrvrName = ptr + 2;
            }
            break;

        case 'R':
            if (strlen(ptr + 2) > 0) {
                RegistryName = ptr + 2;
            }
            break;

        default:
            printf(
            "Usage: gateway -S<remote server name> [-R<registry key name>]\n");
                
            ExitProcess(exitcode);
        }
    }
}
