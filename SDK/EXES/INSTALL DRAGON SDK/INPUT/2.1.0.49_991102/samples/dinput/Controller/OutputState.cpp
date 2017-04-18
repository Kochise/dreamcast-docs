/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    OutputState.cpp

Abstract:

    Sample-specific functions designed to output the state of a
    controller in an easily readible format.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "Controller.hpp"

// ++++ Structres +++++++++++++++++++++++++++++++++++++++++++++
typedef struct tagButtonInfo {
    int   nXDest, nYDest;
    RECT rcUp;
    RECT rcDown;
} typeButtonInfo;   // Contains source and dest info for button output

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
typeButtonInfo g_btninfo[] = {
    { 0,   0, { 22,   0,  44,  22}, { 0,   0,  22,  22}},  // A
    {30,   0, { 22,  22,  44,  44}, { 0,  22,  22,  44}},  // B
    {60,   0, { 22,  44,  44,  66}, { 0,  44,  22,  66}},  // C
    { 0,  30, {  0, 110,  66, 132}, { 0,  88,  66, 110}},  // Start
    { 0,  60, {110,   0, 132,  22}, {88,   0, 110,  22}},  // LA
    {30,  60, {110,  22, 132,  44}, {88,  22, 110,  44}},  // RA
    {60,  60, {110,  66, 132,  88}, {88,  66, 110,  88}},  // DA
    {90,  60, {110,  44, 132,  66}, {88,  44, 110,  66}},  // UA
    { 0,  90, { 66,   0,  88,  22}, {44,   0,  66,  22}},  // X
    {30,  90, { 66,  22,  88,  44}, {44,  22,  66,  44}},  // Y
    {60,  90, { 66,  44,  88,  66}, {44,  44,  66,  66}},  // Z
    {90,   0, { 22,  88,  44, 110}, { 0,  88,  22, 110}},  // D
    { 0, 120, {110,  88, 132, 110}, {88,  88, 110, 110}},  // LB
    {30, 120, {110, 110, 132, 132}, {88, 110, 110, 132}},  // RB
    {60, 120, {110, 154, 132, 176}, {88, 154, 110, 176}},  // DB
    {90, 120, {110, 132, 132, 154}, {88, 132, 110, 154}},  // UB
    { 0, 150, {  0, 198, 110, 220}, { 0, 198, 110, 220}},  // RTrigger
    { 0, 180, {  0, 176, 110, 198}, { 0, 176, 110, 198}},  // LTrigger
    { 0, 0,   {  0,   0,   0,   0}, { 0,   0,   0,   0}},  // An3 (Same as X range - never used)
    { 0, 0,   {  0,   0,   0,   0}, { 0,   0,   0,   0}},  // An4 (Same as Y range - never used)
    { 0, 270, {  0, 264, 110, 286}, { 0, 264, 110, 286}},  // An5
    { 0, 300, {  0, 286, 110, 308}, { 0, 286, 110, 308}},  // An6
};

// Location of the 'No Input' image in the main bitmap
RECT g_rcNoInputBmp = {0, 132, 0 + 66, 132 + 22};

// Location of the axes images in the main bitmap
RECT g_rcXAxisBmp   = {0, 220, 110, 220 + 22};
RECT g_rcYAxisBmp   = {0, 242, 110, 242 + 22};

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    OutputButtonState

Description:

    Output the current state of the specified button to the screen.  Use
    the specified port number to determine where on the screen to display
    the information.  This function handles both digital buttons and analog
    buttons (ie Triggers).

Arguments:
    
    int     iPort    - Port number of the controller to output

    int     iButton  - Index of the button whose state we're outputting.

    int     nState   - Current state of the button

Return Value:

    None

-------------------------------------------------------------------*/
void
OutputButtonState(int iPort, int iButton, int nState)
{
    RECT rc;
    typeButtonInfo *pbiCur = &g_btninfo[iButton];
    int nWidth;

    rc.left = pbiCur->nXDest + iPort * 150 + 20;
    rc.top  = pbiCur->nYDest + 20;

    if (iButton == g_iLTrigButton || iButton == g_iRTrigButton ||
        iButton == g_iAn5Button   || iButton == g_iAn6Button)
    {
        DDBLTFX ddbltfx;

        // It's an Trigger button.
        rc.right  = rc.left + (pbiCur->rcDown.right  - pbiCur->rcDown.left);
        rc.bottom = rc.top  + (pbiCur->rcDown.bottom - pbiCur->rcDown.top);
        g_pddsBack->Blt(&rc, g_pddsButtons, &pbiCur->rcDown, DDBLT_WAIT, 0);

        // Now fill in an area to show how far the trigger is pulled
        nWidth = (int)((float)nState * 81.0f / 255.0f);// Trigger button bitmap interior width = 81 pixels

        rc.left += 3;
        rc.top  += 3;
        rc.right = rc.left + nWidth + 1;
        rc.bottom = rc.top + 16;

        memset(&ddbltfx,0,sizeof(DDBLTFX));
        ddbltfx.dwSize = sizeof(DDBLTFX);
        ddbltfx.dwFillColor = 0xff00ff00;
        g_pddsBack->Blt(&rc, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);

    }
    else
    {
        // It's a normal button
        if (nState & 0x80)
        {
            rc.right  = rc.left + (pbiCur->rcDown.right - pbiCur->rcDown.left);
            rc.bottom = rc.top  + (pbiCur->rcDown.bottom - pbiCur->rcDown.top);
            g_pddsBack->Blt(&rc, g_pddsButtons, &pbiCur->rcDown, DDBLT_WAIT, 0);
        }
        else
        {
            rc.right  = rc.left + (pbiCur->rcUp.right - pbiCur->rcUp.left);
            rc.bottom = rc.top  + (pbiCur->rcUp.bottom - pbiCur->rcUp.top);
            g_pddsBack->Blt(&rc, g_pddsButtons, &pbiCur->rcUp, DDBLT_WAIT, 0);
        }
    }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    OutputControllerState

Description:

    Output the current state of the specified port to the screen.  Use
    the specified port number to determine where on the screen to display
    the information.  If there is no controller on this port, display
    "No Controller".  This function is sample-specific, otherwise it would
    be better placed as a member function of CController...

Arguments:
    
    int         iPort       - Port number of the controller to output

    CController *pcont      - The controller to output

Return Value:

    None

-------------------------------------------------------------------*/
void
OutputAxisState(int iPort, eAxis eaxis, int iLoc, int nState)
{
    RECT rc;
    int nWidth;
    DDBLTFX ddbltfx;

    rc.left   = iPort * 150 + 20;
    rc.top    = 230 + iLoc * 30;
    rc.right  = rc.left + 110;
    rc.bottom = rc.top  + 22;
    switch (eaxis) {
    case eXAxis:
        g_pddsBack->Blt(&rc, g_pddsButtons, &g_rcXAxisBmp, DDBLT_WAIT, 0);
        break;

    case eYAxis:
        g_pddsBack->Blt(&rc, g_pddsButtons, &g_rcYAxisBmp, DDBLT_WAIT, 0);
        break;
    }

    // Now fill in an area to show the current axis state.
    nWidth = (int)((float)nState * 81.0f / 255.0f);

    rc.left += 3;
    rc.top  += 3;
    rc.right = rc.left + nWidth + 1;
    rc.bottom = rc.top + 16;

    memset(&ddbltfx,0,sizeof(DDBLTFX));
    ddbltfx.dwSize = sizeof(DDBLTFX);
    ddbltfx.dwFillColor = 0x00ff00ff;
    g_pddsBack->Blt(&rc, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    OutputControllerState

Description:

    Output the current state of the specified port to the screen.  Use
    the specified port number to determine where on the screen to display
    the information.  If there are no controller on this port, display
    "No Controller".  This function is sample-specific, otherwise it would
    be better placed as a member function of CController...

Arguments:
    
    int         iPort       - Port number of the controller to output

    CController *pcont      - The controller to output

Return Value:

    None

-------------------------------------------------------------------*/
void 
OutputControllerState(int iPort, CController *pcont)
{
    unsigned int iButton, iAxis;

    if (pcont == NULL)
    {
        // There is no controller attached to this port.  Output "No Controller"
        RECT rc = {iPort * 150 + 20, 20, iPort * 150 + 20 + 66, 20 + 22};
        g_pddsBack->Blt(&rc, g_pddsButtons, &g_rcNoInputBmp, DDBLT_WAIT, 0);
    }
    else
    {
        // There is a controller attached to this port.  Output it's button and axis states.
        
        // First, output each of the buttons.  
        for (iButton = 0; iButton < g_nMaxButtons; iButton++)
        {
            if (pcont->m_buttonIndices[iButton] != g_iInvalid)
            {
                // This button exists!  Output it on screen
                OutputButtonState(iPort, iButton, pcont->m_curButtonValues[pcont->m_buttonIndices[iButton]]);
            }
        }
        
        // Next, output each of the axes
        int iLoc = 0;
        for (iAxis = 0; iAxis < g_nMaxAxes; iAxis++)
        {
            if (pcont->m_axisIndices[iAxis].iAxis != g_iInvalid)
            {
                // This button exists!  Output it on screen
                OutputAxisState(iPort, pcont->m_axisIndices[iAxis].eaxis, iLoc++, pcont->m_curAxisValues[pcont->m_axisIndices[iAxis].iAxis]);
            }
        }
    }
}

