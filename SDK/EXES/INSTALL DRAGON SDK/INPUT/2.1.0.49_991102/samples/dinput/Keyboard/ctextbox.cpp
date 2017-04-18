/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    CTextBox.cpp

Abstract:

    A simple text box class implementation to demonstrate how to
    store and output keyboard text entry.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "Keyboard.hpp"

const int g_nLetterWidth  = 14;
const int g_nLetterHeight = 14;
const int g_nXPadding     = 0;
const int g_nYPadding     = 0;

RECT g_rcCursor = {56, 56, 70, 70};
const int  g_cCursorFlashDelay = 500;   // Flash every 500 ms.

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    OutputKey

Description:

    Output the specified key at the specified location on the screen.
    This function doesn't do any form of clipping.

Arguments:
    
    int         nX       - X Location to draw at

    int         nY       - Y Location to draw at
    
    int         iKey     - The actual key to output

Return Value:

    None

-------------------------------------------------------------------*/
void
OutputKey(int nX, int nY, int iKey)
{
    RECT rc, rcKey;

    rc.left   = nX;
    rc.top    = nY;
    rc.right  = rc.left + 14;
    rc.bottom = rc.top  + 14;        

    // Note: Several of the 'magic numbers' below are specific to the 
    // bitmap used to store the letters' images.
    if (iKey >= 'A' && iKey <= 'Z')
    {
        rcKey.left = ((iKey - 'A') % 8 ) * g_nLetterWidth;
        rcKey.top = ((iKey - 'A')/ 8) * g_nLetterHeight;
        rcKey.right = rcKey.left + g_nLetterWidth;
        rcKey.bottom = rcKey.top + g_nLetterHeight;
    }
    else    // '0' - '9'
    {
        rcKey.left = (((iKey - '0') % 8 + 2) * g_nLetterWidth)%112;
        rcKey.top = ((iKey -'0'+2)/ 8) * g_nLetterHeight + 42;
        rcKey.right = rcKey.left + g_nLetterWidth;
        rcKey.bottom = rcKey.top + g_nLetterHeight;
    }

    g_pddsBack->Blt(&rc, g_pddsButtons, &rcKey, DDBLT_WAIT, 0);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CTextBox::CTextBox

Description:

    CTextBox constructor function

Arguments:
    
    int         nX          - X Location of the textbox

    int         nY          - Y Location of the textbox

    int         nW          - Width of the textbox

    int         nH          - Height of the textbox

Return Value:

    None

-------------------------------------------------------------------*/
CTextBox::CTextBox(int nX, int nY, int nW, int nH)
{
    m_nX = nX;
    m_nY = nY;
    m_nW = nW;
    m_nH = nH;
    
    m_nCharWidth = m_nW / (g_nLetterWidth + g_nXPadding);

    m_iChar = 0;
    m_fDrawCursor = FALSE;
    m_nLastCursorFlash = GetTickCount();

    // Calculate maximum number of characters in this textbox
    m_iMaxChars = m_nCharWidth * m_nH/(g_nLetterHeight + g_nYPadding)-1;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CTextBox::AddChar

Description:

    Adds the specified character to the textbox

Arguments:
    
    char        ch  - The character to add to the textbox

Return Value:

    None

-------------------------------------------------------------------*/
void
CTextBox::AddChar(char ch)
{
    if (m_iChar < m_iMaxChars)
        m_rgText[m_iChar++] = ch;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CTextBox::BackSpace

Description:

    Delete the front most character from the textbox

Arguments:
    
    None

Return Value:

    None

-------------------------------------------------------------------*/
void
CTextBox::BackSpace()
{
    m_iChar = max(0,m_iChar-1);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CTextBox::Output

Description:

    Output the contents of the textbox to the screen.

Arguments:
    
    BOOL        fActive     -- If true, the cursor is drawn

Return Value:

    None

-------------------------------------------------------------------*/
void
CTextBox::Output(BOOL fActive)
{
    int nCurTime;

    for (int i = 0;i < m_iChar; i++)
    {
        int nX = m_nX + (g_nLetterWidth + g_nXPadding) * (i%m_nCharWidth);
        int nY = m_nY + i/m_nCharWidth * (g_nLetterHeight + g_nYPadding);

        if (m_rgText[i] != ' ')
            OutputKey(nX, nY, m_rgText[i]);
    }

    if (fActive)
    {
        // Draw a flashing cursor at the current location
        nCurTime = GetTickCount();

        if (nCurTime - m_nLastCursorFlash > g_cCursorFlashDelay)
        {
            m_nLastCursorFlash = nCurTime;
            m_fDrawCursor = !m_fDrawCursor;
        }

        if (m_fDrawCursor)
        {
            RECT rc; 
        
            rc.left   = m_nX + (g_nLetterWidth + g_nXPadding) * (m_iChar%m_nCharWidth);
            rc.top    = m_nY + m_iChar/m_nCharWidth * (g_nLetterHeight + g_nYPadding);
            rc.right  = rc.left + g_nLetterWidth;
            rc.bottom = rc.top  + g_nLetterHeight;

            g_pddsBack->Blt(&rc, g_pddsButtons, &g_rcCursor, DDBLT_WAIT, 0);
        }
    }
}
