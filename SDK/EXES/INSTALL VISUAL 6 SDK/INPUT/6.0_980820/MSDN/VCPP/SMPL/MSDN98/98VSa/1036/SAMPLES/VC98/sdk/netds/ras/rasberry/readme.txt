RASberry - A demonstation of the RAS API set.

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1993-1995  Microsoft Corporation.  All Rights Reserved.


PURPOSE:
    To demonstrate the Remote Access Service (RAS) API set.  RASberry
    allows the user to enumerate current RAS connections, display the
    status of a selected connection, dial entries from the default
    phone book, and hang up a active connection.

RAS APIs USED:
    RasDial
    RasEnumConnections
    RasEnumEntries
    RasGetConnectStatus
    RasGetErrorString
    RasHangUp

COMMENTS:
    This sample may be built as a 16 or 32 bit application.  The default
    is 32 bits.  To build a 16 bit version, define MAK16 on the build
    command line.

    32 BIT SPECIFICS:
    - Before the application exits, it should insure that the RAS state
      machine has been reset if there has been a hang up.  This may be 
      done by calling Sleep(3000).  See documentation on RasHangUp for 
      more information.

    - The 32 bit RasDial API can either function syncronously or
      asyncronously.  This sample demonstrates the asyncronous ability.
      The asyncronous RasDial call requires a callback function to
      receive a notification of a change of state in the connection
      process.  The function is not associated with a window or message
      queue.  To provide a single source for both Win32 and Win16 
      applications, the RasDialFunc in RASbeery, just posts a message
      to a window, and the window's message handle takes the 
      appropriate action. 


    16 BIT SPECIFICS:
    - The RasDial API is only asyncronous for Win16.  RasDial sends
      a WM_RASDIALEVENT message to the window specified in the call to
      RasDial.  An application may perform any tasks during the handling
      of this message, but it should not call EndDialog().  If it is 
      desired that the window be closed, a shut down message should be
      posted to the window as in this sample.


MODULE MAP:
    RASberry- Implements message handlers for the main window.  Maintains
              the list of current RAS connections.
    StatDlg - Displays the status of a connection selected from the main
              application window.
    PhbkDlg - Displays contents of default phone book and allow the user
              to dail an entry.
    AuthDlg - Obtains authentication information from user before making
              a connection.
    DialDlg - Displays the states of the RAS connection during the initial
              connection phase.
    RasUtil - Utilities used by modules listed above.
    Dispatch- Message dispatching routines
    WinMain - Calls initialization functions and processes the message loop
    Init    - Performs application and instance specific initialization
    About   - Defines a standard about dialog box.
    Misc    - Defines the applications specific commands not related to
                a specific module.
