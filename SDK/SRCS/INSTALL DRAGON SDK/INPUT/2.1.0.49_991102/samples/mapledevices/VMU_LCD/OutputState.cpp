/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    OutputState.cpp

Abstract:

    Functions designed to output the state of all VMU's currently
    attached to controllers that are plugged in.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "VMU_LCD.hpp"

// ++++ Local Variables +++++++++++++++++++++++++++++++++++++++++++++

// Various image locations in the main bitmap
RECT g_rcNoInputBmp = {0,  0, 66, 22};
RECT g_rcNoVMUBmp   = {0, 22, 66, 44};
RECT g_rcDrawingBmp = {0, 44, 66, 66};
RECT g_rcPenUpBmp   = {0, 66, 66, 88};
RECT g_rcPenDownBmp = {0, 88, 66, 110};

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    OutputVMUState

Description:

    Output the contents of the VMU's LCD screen onto the monitor so
    that the user can verify that they match.

Arguments:

    int         iPort       - Port number of the controller to output

    CLCD        *plcd       - The LCD display to draw to the monitor

Return Value:

    None

-------------------------------------------------------------------*/
void
OutputVMUState(int iPort, CLCD *plcd)
{
    int     iX, iY;
    DDBLTFX ddbltfx;
    int     nBlockWidth  = 150 / g_uiStdLCDXPixels;
    int     nBlockHeight = 150 / g_uiStdLCDYPixels;
    RECT    rc;

    for (iY = 0; iY < (int)g_uiStdLCDYPixels; iY++)
        for (iX = 0; iX < (int)g_uiStdLCDXPixels; iX++)
        {
            // Plot Pixel (iX, iY) on screen
            rc.left   = iPort * 150 + iX * nBlockWidth;
            rc.top    = 80 + iY * nBlockHeight;
            rc.right  = rc.left + nBlockWidth - 2;
            rc.bottom = rc.top + nBlockHeight - 2;
            memset(&ddbltfx,0,sizeof(DDBLTFX));
            ddbltfx.dwSize = sizeof(DDBLTFX);
            if (iX == plcd->m_nCurX && iY == plcd->m_nCurY)
                ddbltfx.dwFillColor = 0xF800;       // Red
            else
            {
                if (plcd->GetBit(iX, iY))
                    ddbltfx.dwFillColor = 0xFF00;   // Yellow
                else
                    ddbltfx.dwFillColor = 0x00FF;   // Blue
            }
            g_pddsBack->Blt(&rc, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
        }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    UpdateLCDDisplay

Description:

    Updates the contents of the LCD's display based on the user's input
    via the LCD's controller.

Arguments:

    CController *pcont      - The controller to output

Return Value:

    TRUE if LCD still plugged in; FALSE if it's been removed.

-------------------------------------------------------------------*/
BOOL
UpdateLCDDisplay(CController *pcont)
{
    BOOL fLCDPluggedIn = TRUE;
    CLCD *plcd = pcont->GetLCD();

    // Check to see if any state changes have occurred in the controller's buttons
    // that we care about.  If so, handle them.  Note that this doesn't support
    // repeating buttons.
    if (pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[g_iUAButton]])
    {
        // The state of the 'Up' button has changed.  Is it now pressed?  If so, move and draw
        if (pcont->m_curButtonValues[pcont->m_buttonIndices[g_iUAButton]] & 0x80)
            fLCDPluggedIn = plcd->LCDCommand(ecmdUp);
    }

    if (pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[g_iDAButton]])
    {
        // The state of the 'Down' button has changed.  Is it now pressed?  If so, move and draw
        if (pcont->m_curButtonValues[pcont->m_buttonIndices[g_iDAButton]] & 0x80)
            fLCDPluggedIn = plcd->LCDCommand(ecmdDown);
    }

    if (pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[g_iLAButton]])
    {
        // The state of the 'Left' button has changed.  Is it now pressed?  If so, move and draw
        if (pcont->m_curButtonValues[pcont->m_buttonIndices[g_iLAButton]] & 0x80)
            fLCDPluggedIn = plcd->LCDCommand(ecmdLeft);
    }

    if (pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[g_iRAButton]])
    {
        // The state of the 'Right' button has changed.  Is it now pressed?  If so, move and draw
        if (pcont->m_curButtonValues[pcont->m_buttonIndices[g_iRAButton]] & 0x80)
            fLCDPluggedIn = plcd->LCDCommand(ecmdRight);
    }

    if (pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[g_iAButton]])
    {
        // The state of the 'A' button has changed.  Is it now pressed?  If so, clear the LCD
        if (pcont->m_curButtonValues[pcont->m_buttonIndices[g_iAButton]] & 0x80)
            fLCDPluggedIn = plcd->LCDCommand(ecmdClear);
    }

    if (pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[g_iBButton]])
    {
        // The state of the 'B' button has changed.  Set Pen Up/Down state
        if (pcont->m_curButtonValues[pcont->m_buttonIndices[g_iBButton]] & 0x80)
            fLCDPluggedIn = plcd->LCDCommand(ecmdPenUp);
        else
            fLCDPluggedIn = plcd->LCDCommand(ecmdPenDown);
    }

    // Update the contents of the LCD device itself
    if (plcd->m_fNeedRedraw)
    {
        plcd->m_fNeedRedraw = FALSE;
        fLCDPluggedIn = plcd->LCDCommand(ecmdRedraw);
    }

    // Check if the LCD is still plugged in
    if (!fLCDPluggedIn)
    {
        // the LCD must have been removed from the controller.  Update accordingly
        pcont->SetLCD(NULL);
        return FALSE;
    }

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    OutputControllerState

Description:

    Output the current state of the specified port to the screen.  If
    there is a controller attached to the port, and a VMU attached to
    the controller, then output the current contents of the LCD display
    on the VMU.

Arguments:

    int         iPort       - Port number of the controller to output

    CController *pcont      - The controller to output

Return Value:

    None

-------------------------------------------------------------------*/
void
OutputControllerState(int iPort, CController *pcont)
{
    RECT rcStatus    = {iPort * 150 + 40, 20, iPort * 150 + 40 + 66, 20 + 22};
    RECT rcPenStatus = {iPort * 150 + 40, 50, iPort * 150 + 40 + 66, 50 + 22};

    if (pcont == NULL)
    {
        // There is no controller attached to this port.  Display "No Input"
        g_pddsBack->Blt(&rcStatus, g_pddsSprites, &g_rcNoInputBmp, DDBLT_WAIT, 0);
    }
    else
    {
        // There is a controller attached to this port.  Check if there is an LCD
        // device attached to the controller.
        CLCD *plcd = pcont->GetLCD();
        if (!plcd)
        {
            // No VMU Attached to this controller.  Display "No VMS"
            g_pddsBack->Blt(&rcStatus, g_pddsSprites, &g_rcNoVMUBmp, DDBLT_WAIT, 0);
        }
        else
        {
            // There is an LCD device attached to the controller on this port.
            BOOL fLCDPluggedIn;

            // Update the contents of the LCD's display based on the user's input. 
            // This function also checks to see if the LCD has been removed since the
            // last screen refresh
            fLCDPluggedIn = UpdateLCDDisplay(pcont);
            if (!fLCDPluggedIn)
                return;

            // Display 'Drawing' on the screen
            g_pddsBack->Blt(&rcStatus, g_pddsSprites, &g_rcDrawingBmp, DDBLT_WAIT, 0);

            // Display the appropriate Pen state image
            if (plcd->m_fPenDown)
                g_pddsBack->Blt(&rcPenStatus, g_pddsSprites, &g_rcPenDownBmp, DDBLT_WAIT, 0);
            else
                g_pddsBack->Blt(&rcPenStatus, g_pddsSprites, &g_rcPenUpBmp, DDBLT_WAIT, 0);

            // Output the LCD's contents to the screen so that the user can verify them
            OutputVMUState(iPort, plcd);
        }
    }
}
