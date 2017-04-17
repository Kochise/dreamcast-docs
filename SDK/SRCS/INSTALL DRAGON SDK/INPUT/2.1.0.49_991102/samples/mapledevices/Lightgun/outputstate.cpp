/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    OutputState.cpp

Abstract:

    functions designed to output the state of a
    controller in an easily readible format.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "Lightgun.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++

// Location of the various port status images in the main bitmap
RECT g_rcNoInputBmp = {0, 88, 0 + 66, 88 + 22};
RECT g_rcNotGunBmp  = {0, 132, 0 + 66, 132 + 22};
RECT g_rcShootBmp   = {0, 110, 0 + 66, 110 + 22};

// Location of the various 'splash' images
RECT g_rcSplash[4] = {{0, 0, 44, 44}, {44, 0, 88, 44}, {0, 44, 44, 88}, {44, 44, 88, 88}};

// Size of the splash bitmap
int g_nSplashSize   = 44;

// The port currently being calibrated
#define INVALID_PORT -1
int g_iCalibrationPort = INVALID_PORT;

BOOL g_fDraw[4] = {FALSE, FALSE, FALSE, FALSE};

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
    if (pcont == NULL)
    {
        // There is no controller attached to this port.  Output "No Controller"
        RECT rc = {iPort * 150 + 20, 20, iPort * 150 + 20 + 66, 20 + 22};
        g_pddsBack->Blt(&rc, g_pddsSplash, &g_rcNoInputBmp, DDBLT_WAIT, 0);
    }
    else
    {
        CLightgun *plightgun = pcont->GetLightgun();
        HRESULT hr;

        // There is a controller attached to this port.  If it is a lightgun, then 
        // draw a bitmap at the last location that the user 'fired' at.
        if (plightgun)
        {
            // If the user pressed the 'B' button on this controller, then mark it for calibration
            if (g_iCalibrationPort == INVALID_PORT && pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[g_iBButton]])
            {
                if (pcont->m_curButtonValues[pcont->m_buttonIndices[g_iBButton]] & 0x80)
                {
                    g_iCalibrationPort = iPort; 
                }
            }

            if (g_iCalibrationPort != INVALID_PORT)
            {
                RECT rcDest   = {(640 - g_nSplashSize) / 2, (480 - g_nSplashSize) / 2, 
                                 (640 + g_nSplashSize) / 2, (480 + g_nSplashSize) / 2};
                RECT rcSource = g_rcSplash[g_iCalibrationPort];
                g_pddsBack->Blt(&rcDest, g_pddsSplash, &rcSource, DDBLT_WAIT, 0);
            }

            RECT rc = {iPort * 150 + 20, 20, iPort * 150 + 20 + 66, 20 + 22};
            g_pddsBack->Blt(&rc, g_pddsSplash, &g_rcShootBmp, DDBLT_WAIT, 0);

            // Check to see if the trigger has been pulled; if so, update the current
            // screen coordinates for this port's splash image
            if (pcont->m_rgfButtonStateChanged[pcont->m_buttonIndices[g_iAButton]])
            {
                // The trigger's state has changed.  If it's now 'pulled', then update the position
                if (pcont->m_curButtonValues[pcont->m_buttonIndices[g_iAButton]] & 0x80)
                {
                    // The 'GetPosition' lightgun function runs asychronously with this
                    // sample application.  It flashes the screen white, reads the lightgun position, and
                    // reports it the next frame.  The first time through, it will return immediately without
                    // modifying the passed-in variables; as soon as the lightgun device has determined
                    // the position values, it copies them into the passed-in variables.
                    // If the GetPosition function is called quickly after the last time it was called,
                    // it will block waiting for the first call to determine the lightgun position.  This
                    // can take anywhere from 16 to 32 ms depending on the scanline that the monitor is 
                    // currently on.
                    WaitForSingleObject(plightgun->m_hEvent, 5000);

                    // Get the actual gun position

                    if (g_iCalibrationPort == iPort)
                    {
                        // This will block until the data is retrieved
                        plightgun->m_plgunintf->GetGunPosition(&plightgun->m_lgunpos, NULL);

                        // Now use that data to calibrate the gun
                        plightgun->m_plgunintf->Calibrate(640/2, 480/2, plightgun->m_lgunpos.nX, plightgun->m_lgunpos.nY);
                        g_iCalibrationPort = INVALID_PORT;
                    }
                    else
                    {
                        hr = plightgun->m_plgunintf->GetGunPosition(&plightgun->m_lgunpos, plightgun->m_hEvent);
                        if (hr != LGUN_OK)
                        {
                            SetEvent(plightgun->m_hEvent);
                        }
                    }

                    g_fDraw[iPort] = TRUE;
                }    
            }

            // Draw the splash image.  Don't draw it if trigger hasn't been pulled yet
            if (g_fDraw[iPort] && plightgun->m_lgunpos.nX != LGUN_INVALID_VALUE)
            {
                // Draw the image centered around the current lightgun fired-at spot
                RECT rcDest   = {plightgun->m_lgunpos.nX - g_nSplashSize / 2, plightgun->m_lgunpos.nY - g_nSplashSize / 2, 
                                 plightgun->m_lgunpos.nX + g_nSplashSize / 2, plightgun->m_lgunpos.nY + g_nSplashSize / 2};
                RECT rcSource = g_rcSplash[iPort];
                
                // Check if the destination is completely offscreen
                if (rcDest.left < 639 && rcDest.right > 0 && rcDest.top < 479 && rcDest.bottom > 0)
                {
                    // Clip the RECTs to the screen
                    if (rcDest.left < 0)
                    {
                        rcSource.left -= rcDest.left;
                        rcDest.left = 0;
                    }
                    if (rcDest.top < 0)
                    {
                        rcSource.top -= rcDest.top;
                        rcDest.top = 0;
                    }
                    if (rcDest.right > 639)
                    {
                        rcSource.right = g_rcSplash[iPort].left + g_nSplashSize + (639 - rcDest.right);
                        rcDest.right = 639;
                    }
                    if (rcDest.bottom > 479)
                    {
                        rcSource.bottom = g_rcSplash[iPort].top + g_nSplashSize + (479 - rcDest.bottom);
                        rcDest.bottom = 479;
                    }

                    g_pddsBack->Blt(&rcDest, g_pddsSplash, &rcSource, DDBLT_WAIT, 0);
                }
            }
        }
        else
        {
            // There's a device, but it's not a lightgun.
            RECT rc = {iPort * 150 + 20, 20, iPort * 150 + 20 + 66, 20 + 22};
            g_pddsBack->Blt(&rc, g_pddsSplash, &g_rcNotGunBmp, DDBLT_WAIT, 0);
        }
    }
}

