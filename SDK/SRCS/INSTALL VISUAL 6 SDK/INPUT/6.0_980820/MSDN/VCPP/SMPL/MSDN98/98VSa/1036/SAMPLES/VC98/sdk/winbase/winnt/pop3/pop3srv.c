
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1992-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

//+---------------------------------------------------------------------------
//
//  File:       pop3svr.c
//
//  Contents:
//
//  Classes:
//
//  Functions:
//
//----------------------------------------------------------------------------

#include "pop3srvp.h"
#pragma hdrstop


BOOL    fService = TRUE;
BOOL    fTestMode = FALSE;

//
// This table is the service dispatch table.  It lists the services in
// this process by name, and the entry point to invoke to start them.  This
// example has but one service, but this could be extended to include, for
// instance, an SMTP server.  Be sure to have the prototype for your entry
// point in a global header file, so that you don't get a compiler complaint.
//
SERVICE_TABLE_ENTRY Pop3SrvTable[] = {
            {APPLICATION_NAME, Pop3SrvMain},
            {NULL, NULL } };



//+---------------------------------------------------------------------------
//
//  Function:   DoArgs
//
//  Synopsis:   This parses the process's start arguments, basically just to
//              see if we have a -noservice flag so that we don't talk to the
//              service controller.
//
//  Arguments:  [argc] --
//              [argv] --
//
//  History:    1-09-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
void
DoArgs(
    int argc,
    char * argv[])
{
    int i;
    char * arg;

    for (i = 1; i < argc ; i++)
    {
        arg = argv[i];

        if (*arg == '-')
        {
            //
            // Ooo, an option.
            //
            if (_stricmp(arg, "-noservice") == 0)
            {
                fService = FALSE;
                continue;
            }
            if (_stricmp(arg, "-testmode") == 0)
            {
                fTestMode = TRUE;
                continue;
            }
        }
    }
}

//+---------------------------------------------------------------------------
//
//  Function:   DoServiceController
//
//  Synopsis:   This calls into the service controller, and is never heard
//              from again.
//
//  Arguments:  (none)
//
//  Requires:
//
//  Returns:
//
//  History:    1-09-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
void
DoServiceController(void)
{
    StartServiceCtrlDispatcher(Pop3SrvTable);
}



//+---------------------------------------------------------------------------
//
//  Function:   main
//
//  Synopsis:   Process entry point.  Unless we're told to start without
//              the service controller, we quickly wait for a service start
//              command.
//
//  Arguments:  [argc] --
//              [argv] --
//
//  Requires:
//
//  Returns:
//
//  History:    1-09-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
void
main (int argc, char *argv[])
{

    //
    // Initialize the debug support, by reading our debug level from the
    // registry.
    //
    InitDebugSupport();

    //
    // Parse the arguments
    //
    DoArgs(argc, argv);

    //
    // If we're a service, go to the service controller, otherwise start
    // the service immediately.
    //
    if (fService)
    {
        DoServiceController();
    }
    else
    {
        Pop3SrvMain(argc, NULL);
    }

}
