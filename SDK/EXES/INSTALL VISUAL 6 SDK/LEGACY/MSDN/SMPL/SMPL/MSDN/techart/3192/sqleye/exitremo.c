//****************************** Function Header ******************************
//
// Function : ExitRemote
//
// Description: Closes client connection
//
// Author PeterWil 1994, Microsoft Ltd.
//*****************************************************************************
#define     DBNTWIN32

// Standard compiler and SQL header files
#include    <windows.h>
#include    <sqlfront.h>
#include    <sqldb.h>
#include    <srv.h>
#include    <stdio.h>
#include    <stdlib.h>

// Application specific header files
#include    "sqleye.h"
#include    "exitremo.h"
#include    "rowstuff.h"

extern LOG Log;
extern HWND ghwndMain;
extern BOOL bAutoTile;
extern BOOL bGhosts;

// Declare the handle to protect the linked list of remote structures
extern HANDLE    LinkedList_SEM;

#pragma check_stack( off )  // turn off stack checking


int ExitRemote(SRV_PROC  *srvproc)
{
    REMOTE_DBMS  *remote;
    char *plog_buffer;
    PCLIENTINFO pMDI;
    REMOTE_DBMS *Head;
    BOOL        bListOk = TRUE;

    remote = (REMOTE_DBMS *)srv_getuserdata(srvproc);

    // Is there a REMOTE_DBMS structure to clean-up?
    if (remote != (REMOTE_DBMS *)NULL)
    {
        // get mutualy exclusive access to the list
        // START OF CRITICAL SECTION
        WaitForSingleObject(LinkedList_SEM, (DWORD)SRV_INDEFINITE_WAIT);
        // get the head of the list
        Head = (REMOTE_DBMS *)GetWindowLong(ghwndMain, GWL_USERDATA);
        // if the head is the one we want
        if ( Head == remote) 
        {    
            // take it out of the linked list
            SetWindowLong(ghwndMain, GWL_USERDATA, (LONG)remote->Next);
        } else {
            while ( Head->Next != remote && Head->Next != NULL)
                Head = Head->Next;
            if ( Head->Next == remote)
                // take it out of the list
                Head->Next = ((REMOTE_DBMS*)Head->Next)->Next;
            else
                // It wasn't in the list !!
                // I don't want a message box inside the critical section
                bListOk = FALSE;
        }
        // release the list
        // END OF CRITICAL SECTION
        ReleaseSemaphore(LinkedList_SEM, 1, NULL);

        // can now display the message if necessary
        if (!bListOk) MSGBOX("Couldn't find the remote structure in the linked list");

        // Is there a login structure ?
        if (remote->login)
            dbfreelogin(remote->login);
        // Is there a live dbproc ?
        if (remote->dbproc != (DBPROCESS *)NULL)
            dbclose(remote->dbproc);

        // Close MDI window(s)
        // Note we don't need to clear the memory as 
        // the window is responsible for clearing out it's own data
        if (Log.MDI)
        {
            if (pMDI = LocalLock(remote->hMDI))
            {
                // This flag is also used by WM_CLOSE to indicate
                // that it can close at will
                pMDI->iIconType = IDM_GHOST_ICON;

                if (!bGhosts)
                {
                    // Need to unlock it before I can close it
                    LocalUnlock(remote->hMDI);
                    // get rid of the window if no ghosts
                    SendMessage(pMDI->hwnd, WM_CLOSE, 0, 0);
                } else {
                    // display the new icon
                    InvalidateRect(pMDI->hwnd,NULL,TRUE); 
                    // Needed to keep it locked until I've Invliadated the Rect
                    LocalUnlock(remote->hMDI);
                }
            } else ERRBOX("Error closing MDI window");
        }
 
        if (Log.FILE_Connections)
        {
            plog_buffer = (char *)malloc(
                strlen("ConClosed: Client ID: ") +
                strlen(srv_pfield(srvproc, SRV_SPID, (int *)NULL)) + 1);
            sprintf(plog_buffer,
               "ConClosed: Client ID: %s",
               srv_pfield(srvproc, SRV_SPID, (int *)NULL));
            srv_log(SRV_GETSERVER(srvproc), Log.FILE_Timing, plog_buffer, SRV_NULLTERM);
            free(plog_buffer);
        }

        // Free the memory
        srv_free(remote);
    } 
        
    // Tile if necessary
    if (bAutoTile) PostMessage(ghwndMain,WM_COMMAND,IDM_TILE,0L);

    return(SRV_CONTINUE);
}

#pragma check_stack()   // set stack checking to its default setting

