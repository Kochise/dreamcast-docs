/*
 * OLEMISC.C
 *
 * Functions without another approprate home:
 *  MenuEmbeddingSet
 *  OLEClientNotify
 *  FOLEReleaseWait
 *
 * Copyright(c) Microsoft Corp. 1992-1994 All Rights Reserved
 * Win32 version, January 1994
 */

#ifdef MAKEOLESERVER

#include <windows.h>
#include <ole.h>
#include "cosmo.h"
#include "oleglobl.h"



/*
 * MenuEmbeddingSet
 *
 * Purpose:
 *  Modifies the main menu of the application to change "Save" to "Update"
 *  and to change "Exit" to "Exit & return to xx."  Alternately, this
 *  function can change the menus back to the original state, reverting
 *  "Update" to "Save" and setting the Exit item back to plain "Exit."
 *
 * Parameters:
 *  hWnd            HWND of the window with the menu.
 *  pszClient       LPSTR to the client name.
 *  fOLE            BOOL indiciating if we are to set for OLE or to normal.
 *                  If setting to normal, pszClient can be NULL.
 *
 * Return Value:
 *  None.
 *
 */

void WINAPI MenuEmbeddingSet(HWND hWnd, LPSTR pszClient, BOOL fOLE)
    {
    HMENU       hMenu;
    char        szTemp[130];
    LPSTR       pszT;

    hMenu=GetMenu(pGlob->hWnd);

    //Change the File/Save menu to File/Update <client> or vice-versa
    if (fOLE)
        wsprintf(szTemp, rgpsz[IDS_UPDATE], pszClient);
    else
        lstrcpy(szTemp, rgpsz[IDS_SAVE]);

    ModifyMenu(hMenu, IDM_FILESAVE, MF_STRING, IDM_FILESAVE, szTemp);


    //Change the File/Save As menu to File/Save Copy As or vice-versa.
    pszT=(fOLE) ? rgpsz[IDS_SAVECOPYAS] : rgpsz[IDS_SAVEAS];
    ModifyMenu(hMenu, IDM_FILESAVEAS, MF_STRING, IDM_FILESAVEAS, pszT);


    //Change "Exit" to "Exit & return to xx" or vice-versa.
    if (fOLE)
        wsprintf(szTemp, rgpsz[IDS_EXITANDRETURN], pszClient);
    else
        lstrcpy(szTemp, rgpsz[IDS_EXIT]);

    ModifyMenu(hMenu, IDM_FILEEXIT, MF_STRING, IDM_FILEEXIT, szTemp);
    return;
    }






/*
 * OLEClientNotify
 *
 * Purpose:
 *  Performs a direct function call to the single callback in the
 *  client that is communicating with this server application.
 *  This is the only point where there is direct communication
 *  between the two applciations.
 *
 * Parameters:
 *  pObj            LPCOSMOOBJECT that contains a pClient pointer to an
 *                  LPOLECLIENT that holds a pointer to the OLECLIENTVTBL
 *                  that holds a pointer to the CallBack function.
 *  iMsg            UINT, message to send, such as OLE_CLOSED.
 *
 * Return Value:
 *  None.
 */

void WINAPI OLEClientNotify(LPCOSMOOBJECT pObj, UINT iMsg)
    {
    LPOLECLIENT     pClient;
    LPOLECLIENTVTBL pvt;

    if (NULL==pObj)
        return;

    pClient=pObj->pClient;

    if (NULL==pClient)
        return;

    pvt=pClient->lpvtbl;

    if (NULL==pvt)
        return;

    (pvt->CallBack)(pClient, iMsg, (LPOLEOBJECT)pObj);
    return;
    }






/*
 * FOLEReleaseWait
 *
 * Purpose:
 *  Enters a Peek/Translate/Dispatch message loop to process all messages
 *  to the application until a release flag has been sent.  The application
 *  calls this routine whenever it is required to wait until conversations
 *  for OLE have terminated.
 *
 *  Some of the messages processed may be DDE messages (for OLE 1.x) that
 *  are eventually passed to OLESVR which eventually calls the ServerRelease
 *  function (see OLESVR.C).  ServerRelease modifies a BOOL flag indicating
 *  that the server is released.
 *
 *  Therefore we can watch a particular memory location (*pf)
 *  and only exit when that flag is set.
 *
 * Parameters:
 *  pf              BOOL FAR * to the flag to wait on.
 *  lhSvr           LONG for the OLE server
 *
 * Return Value:
 *  BOOL            Contents of *pf.
 *
 */

BOOL WINAPI FOLEReleaseWait(BOOL FAR *pf, LONG lhSvr)
    {
    MSG        msg;

    *pf=FALSE;

    while (FALSE==*pf)
        {
        /*
         * We use PeekMessage here to make a point about power
         * management and ROM Windows--GetMessage, when there's
         * no more messages, will correctly let the system go into
         * a low-power idle state.  PeekMessage by itself will not.
         * If you do background processing in a PeekMessage loop like
         * this, and there's no background processing to be done,
         * then you MUST call WaitMessage to duplicate the idle
         * state like GetMessage.
         */

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
            /*
             * We will not see WM_QUIT in the middle of the
             * application since this application MUST call
             * PostQuitMessage to get it in the queue.  Therefore we
             * don't even worry about it.
             */

            TranslateMessage (&msg);
            DispatchMessage (&msg);
            }
        else
            {
            /*
             * If the application has some background processing
             * to do, it should perform a piece of it here.  Otherwise
             * you MUST call WaitMessage or you'll screw up ROM-Windows
             * power-management.
             */

            WaitMessage();
            }
        }

    return *pf;
    }





#endif //MAKEOLESERVER
