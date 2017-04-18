/***************************************************************************\
* Function : SendAll
*
* Description : SendAll dialog proc.
*
/***************************************************************************/
#define DBNTWIN32

// Standard compiler/sql server supplied header files
#include <windows.h>
#include <stdlib.h>
#include <sqlfront.h>
#include <sqldb.h>
#include <srv.h>

// Application specific header files
#include "sqleye.h"
#include "dialogs.h"

// Declare the handle to protect the linked list of remote structures
extern HANDLE    LinkedList_SEM;

extern HWND ghwndMain;

#define MAXMSG 256
#define MAXSEV 2

int WINAPI SendAll(HWND hDlg,UINT message,DWORD wParam,LONG lParam)
{
    REMOTE_DBMS * Head;
    static char szSeverity[MAXSEV+2];
    static char szMsgText[MAXMSG+1];


    switch (message)
    {
        case WM_INITDIALOG:
            // Set the server and regkey values
            SendDlgItemMessage(hDlg,IDD_SEVERITY, EM_LIMITTEXT, (DWORD)MAXSEV,(LONG)0);
            SendDlgItemMessage(hDlg,IDD_SEVERITY, EM_REPLACESEL,(DWORD)0,(LONG)szSeverity);
            SendDlgItemMessage(hDlg,IDD_MESSAGE,  EM_LIMITTEXT, (DWORD)MAXMSG,(LONG)0);
            SendDlgItemMessage(hDlg,IDD_MESSAGE,  EM_REPLACESEL,(DWORD)0,(LONG)szMsgText);
            return TRUE;

        case WM_COMMAND:
        switch (LOWORD(wParam))
        {
            case IDOK:
                // Retrieve the data
                strcpy(szMsgText, "");
                GetDlgItemText(hDlg, IDD_MESSAGE, szMsgText, MAXMSG);
                strcat(szMsgText, "\0");
                strcpy(szSeverity, "");
                GetDlgItemText(hDlg, IDD_SEVERITY, szSeverity, MAXMSG);
                strcat(szSeverity, "\0");
                EndDialog(hDlg, wParam);

                // send the message
                // START OF CRITICAL SECTION
                WaitForSingleObject(LinkedList_SEM, (DWORD)SRV_INDEFINITE_WAIT);
                // get the head of the list
                Head = (REMOTE_DBMS *)GetWindowLong(ghwndMain, GWL_USERDATA);
                // use the srvproc
                while (Head != NULL)
                {
                    if ( srv_sendmsg(
                        Head->srvproc,
                        SRV_MSG_INFO,
                        0,
                        (DBTINYINT)atoi(szSeverity),
                        0,
                        NULL,
                        0,
                        0,
                        szMsgText,
                        SRV_NULLTERM) != SUCCEED)
                        MSGBOX("Failed to send message");
                    Head = (REMOTE_DBMS *)Head->Next;
                }
                // release the list
                // END OF CRITICAL SECTION
                ReleaseSemaphore(LinkedList_SEM, 1, NULL);
                MSGBOX("Message sent");
            break;

            case IDCANCEL:
                EndDialog(hDlg, wParam);
            break;
        }
    }

    return FALSE;
}  

