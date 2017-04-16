// COPYRIGHT:
//
//   (C) Copyright Microsoft Corp. 1993.  All rights reserved.
//
//   You have a royalty-free right to use, modify, reproduce and
//   distribute the Sample Files (and/or any modified version) in
//   any way you find useful, provided that you agree that
//   Microsoft has no warranty obligations or liability for any
//   Sample Application Files which are modified.
//
/*
    dde.c

    This module handles all the DDE support not provided by stddde.c

*/

#include "ddeexec.h"
#include <stdlib.h>

//
// DDE variables
//

static DWORD dwDDEInst = 0;         // DDE Instance value

//
// Format lists
//

WORD MyFormats[] = {
    CF_TEXT,
    NULL};

//
// Local functions
//

HDDEDATA SysHelpRequest(UINT wFmt, HSZ hszTopic, HSZ hszItem);


//
// Startup our DDE services
//

void SetupDDE(HINSTANCE hInstance)
{
    //
    // Do the basic initialization
    //

    InitializeDDE(hInstance,
                  SZ_SERVICENAME,
                  &dwDDEInst, 
                  NULL,
                  CBF_FAIL_EXECUTES);

    //
    // Add each system/item pair we support
    //

    AddDDEItem(SZDDESYS_TOPIC, 
               SZDDESYS_ITEM_HELP,
               MyFormats,
               SysHelpRequest,
               NULL);

    //
    // Add each topic/item pair we support
    //





    //
    // Add any topics for Execute connections
    //

    AddDDETopic(SZ_DRAWRECT,
                NULL,
                NULL,
                NULL);

    //
    // Add the commands for this execute set
    //

    AddDDEExecCmd(SZ_DRAWRECT,  "Ellipse",  EllipseFn,  4,  4);
    AddDDEExecCmd(SZ_DRAWRECT,  "Rectangle",RectangleFn,4,  4);
    AddDDEExecCmd(SZ_DRAWRECT,  "Line",     LineFn,     4,  4);
    AddDDEExecCmd(SZ_DRAWRECT,  "Erase",    EraseFn,    0,  1);
    AddDDEExecCmd(SZ_DRAWRECT,  "Pen",      PenFn,      1,  1);
    AddDDEExecCmd(SZ_DRAWRECT,  "Brush",    BrushFn,    1,  1);
    AddDDEExecCmd(SZ_DRAWRECT,  "Text",     TextFn,     3,  3);

}

//
// Return a string in CF_TEXT format
//

HDDEDATA MakeCFText(UINT wFmt, LPSTR lpszStr, HSZ hszItem)
{
    if (wFmt != CF_TEXT) return NULL;

    return DdeCreateDataHandle(dwDDEInst,
                               lpszStr,
                               lstrlen(lpszStr)+1,
                               0,
                               hszItem,
                               CF_TEXT,
                               NULL);
}

//
// Return the Help info
//

HDDEDATA SysHelpRequest(UINT wFmt, HSZ hszTopic, HSZ hszItem)
{
    static char sz[] = "DDE Help for the DDE Execute Service.";

    return MakeCFText(wFmt, sz, hszItem);
}


