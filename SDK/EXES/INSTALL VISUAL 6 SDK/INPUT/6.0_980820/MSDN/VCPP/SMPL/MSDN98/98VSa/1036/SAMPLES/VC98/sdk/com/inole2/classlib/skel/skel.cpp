/*
 * SKEL.CPP
 * CLASSLIB Skeleton
 *
 * Skeleton application using CLASSLIB which only needs a WinMain
 * and a number of standard resources.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include <windows.h>
#include <classlib.h>


/*
 * WinMain
 *
 * Purpose:
 *  Main entry point of application.  Should register the app class
 *  if a previous instance has not done so and do any other one-time
 *  initializations.
 */

int PASCAL WinMain (HINSTANCE hInst, HINSTANCE hPrev
    , LPSTR pszCmdLine, int nCmdShow)
    {
    PCFrame         pFR;
    FRAMEINIT       fi;
    WPARAM          wRet;

    //Attempt to allocate and initialize the application
    pFR=new CFrame(hInst, hPrev, pszCmdLine, nCmdShow);

    if (NULL==pFR)
        return 0;

    fi.idsMin=IDS_STANDARDFRAMEMIN;
    fi.idsMax=IDS_STANDARDFRAMEMAX;
    fi.idsStatMin=IDS_STANDARDSTATMESSAGEMIN;
    fi.idsStatMax=IDS_STANDARDSTATMESSAGEMAX;
    fi.idStatMenuMin=ID_MENUFILE;
    fi.idStatMenuMax=ID_MENUHELP;
    fi.iPosWindowMenu=WINDOW_MENU;
    fi.cMenus=CMENUS;

    fi.x=CW_USEDEFAULT;
    fi.y=CW_USEDEFAULT;
    fi.cx=CW_USEDEFAULT;
    fi.cy=CW_USEDEFAULT;

    //If we can initialize pFR, start chugging messages
    if (pFR->Init(&fi))
        wRet=pFR->MessageLoop();

    delete pFR;
    return wRet;
    }
