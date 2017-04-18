/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    OutputState.cpp

Abstract:

    functions designed to output the state of a
    Keyboard in an easily readible format.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "Keyboard.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++

// Location of the 'No Input' image in the main bitmap
RECT g_rcNoInputBmp = {0, 70, 0 + 66, 70 + 22};

// Location of the 'Type Text' image in the main bitmap
RECT g_rcTypeTextBmp = {0, 98, 86, 121};

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    KeyIsSupported

Description:

    Determines if the passed-in key is one that this sample supports.  
    This sample only supports the alphanumeric keys (A-Z, 0-9).  Lower
    case letters are automatically converted to upper case letters

Arguments:
    
    int         *pnKey  - The key to check.  Upper-cases it if appropriate

Return Value:

    TRUE if supported, FALSE if not supported

-------------------------------------------------------------------*/
BOOL KeyIsSupported(int *pnKey)
{
    if (*pnKey >= 'a' && *pnKey <= 'z')
        *pnKey += ('A' - 'a');

    if (*pnKey >= 'A' && *pnKey <= 'Z')
        return TRUE;

    if (*pnKey >= '0' && *pnKey <= '9')
        return TRUE;

    if (*pnKey == ' ')
        return TRUE;

    return FALSE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    OutputKeyboardState

Description:

    Output the current state of the specified port to the screen.  Use
    the specified port number to determine where on the screen to display
    the information.  If there is no Keyboard on this port, display
    "No Input".

Arguments:
    
    int         iPort       - Port number of the Keyboard to output

    CKeyboard   *pcont      - The Keyboard to output

Return Value:

    None

-------------------------------------------------------------------*/
void 
OutputKeyboardState(int iPort, CKeyboard *pcont)
{
    if (pcont == NULL)
    {
        // There is no Keyboard attached to this port.  Output "No Input" image
        RECT rc = {iPort * 150 + 20, 20, iPort * 150 + 20 + 66, 20 + 22};
        g_pddsBack->Blt(&rc, g_pddsButtons, &g_rcNoInputBmp, DDBLT_WAIT, 0);
    }
    else
    {
        // There is a Keyboard attached to this port.  

        // Output 'Type Text' image
        RECT rc = {iPort * 150 + 20, 20, iPort * 150 + 20 + 86, 20 + 23};
        g_pddsBack->Blt(&rc, g_pddsButtons, &g_rcTypeTextBmp, DDBLT_WAIT, 0);
        
        // Add any newly pressed keys to the text box.
        while (!pcont->m_pqPressedKeys->IsEmpty())
        {
            int iKey;

            pcont->m_pqPressedKeys->Dequeue(&iKey);

            if (iKey == 0x8)    // Backspace key
                g_ptextbox[iPort]->BackSpace();
            else if (KeyIsSupported(&iKey))
                g_ptextbox[iPort]->AddChar(iKey);
        }
    }

    // Output the controller's text box. Only draw cursor if port has a keyboard
    // plugged into it.
    g_ptextbox[iPort]->Output(pcont != NULL);
}

