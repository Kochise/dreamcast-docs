/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    imeui.cxx

Abstract:

    This file contains functions which manage the Input Method Editor (IME)
    user interface window.

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#include "precomp.hpp"


TCHAR               g_szKanji[MAX_KANJI+1];        // string for kana-kanji translation
TCHAR               g_szHiragana[256];             // string for kana-kanji translation
unsigned short		g_iKeyTop = 0;				   // the top displayed row of the scrolling
												   // kanji selection window	


#include "inputkwnd.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IMECreate

Description:

    This function initializes the contents of the IME, creates the direct 
    input for the IME, creates the kanji selection window, and renders the
    IME window.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
IMECreate
    (
    void
    )
{
    // create the direct input but don't acquire it
    if (!CreateDirectInput(g_hinstApp, g_hwndApp, &g_pdidevice2JoystickIME)) 
    {
        // this is not an error; maybe the joystick is unplugged.  the IME will
        // continuously try to find a joystick.
    }

    // create the kanji window
    if (!KWNDCreate ())
    {
        return 0;
    }

    if (!EditBoxRender ())
    {
        return(FALSE);
    }

    return(TRUE);

} // IMECreate


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IMEProcessVirtualKey

Description:

    This function processes a virtual key message.

Return Value:
    none.

-------------------------------------------------------------------*/
void 
IMEProcessVirtualKey
    (
    TCHAR       wcKey,
    BOOL        fCtrlKeyPressed
    )
{
    UINT        ch;
    UINT        dummy;

    // DEBUGMSG(1, (TEXT("PIME sample received vkcode=%x\r\n"), wcKey));
    switch (wcKey)
    {
        case VK_LEFT:
            // DEBUGMSG(1, (TEXT("Editbox window received VK_LEFT.\r\n")));
            if (fCtrlKeyPressed)
                break;
            if (g_caretpos > 0)
                g_caretpos--;
            EditBoxRender();
            break;

        case VK_RIGHT:
            if (fCtrlKeyPressed)
                break;
            if (g_caretpos < _tcslen(g_wszConverted))
                g_caretpos++;
            EditBoxRender();
            break;

        case VK_END:
            g_caretpos = _tcslen(g_wszConverted);
            EditBoxRender();
            break;

        case VK_HOME:
            g_caretpos = 0;
            EditBoxRender();
            break;

		case VK_ESCAPE:
  			PostQuitMessage(0);
			break;

        case VK_NOCONVERT:
            // Post a return key.
			ch = ' ';
            PostKeybdMessage((HWND) -1, VK_RETURN, KeyStateDownFlag, 0, &dummy, &ch);
            break;      

        case VK_CONVERT:
            // Post a spacebar.
			ch = ' ';
            PostKeybdMessage((HWND) -1, VK_SPACE, KeyStateDownFlag, 1, &dummy, &ch);
            break;      

        case VK_BACK:
            // delete the last character inserted into the IME (LIFO)
            if (g_caretpos > 0)
            {
                memmove (&g_wszConverted[g_caretpos - 1], &g_wszConverted[g_caretpos], 
                    (_tcslen(g_wszConverted) - g_caretpos + 1) * sizeof(TCHAR));
                g_caretpos--;
                EditBoxRender();
            }
            break;

        case VK_DELETE:
            // delete the last character inserted into the IME (LIFO)
            DEBUGMSG(1, (TEXT("Received VK_BACK")));
            if (g_caretpos < _tcslen(g_wszConverted))
            {
                memmove (&g_wszConverted[g_caretpos], &g_wszConverted[g_caretpos + 1], 
                    (_tcslen(g_wszConverted) - g_caretpos) * sizeof(TCHAR));
                EditBoxRender();
            }
            break;

		case VK_DBE_SBCSCHAR:
            g_pkeybdstateCurrent->keyboard = KATAKANA;
			g_pkeybdstateCurrent->fHalfWidth = TRUE;
			break;

		case VK_DBE_DBCSCHAR:
            g_pkeybdstateCurrent->keyboard = KATAKANA;
			g_pkeybdstateCurrent->fHalfWidth = FALSE;
			break;

		case VK_DBE_HIRAGANA:
            //OutputDebugString(TEXT("H"));
			g_pkeybdstateCurrent->keyboard = HIRAGANA;
			break;

		case VK_DBE_KATAKANA:
            //OutputDebugString(TEXT("K"));
			g_pkeybdstateCurrent->keyboard = KATAKANA;
			break;

		case VK_DBE_NOROMAN:
            //OutputDebugString(TEXT("N"));
			g_pkeybdstateCurrent->fRKCOn = FALSE;
			break;	

		case VK_DBE_ROMAN:
            //OutputDebugString(TEXT("R"));
			g_pkeybdstateCurrent->fRKCOn = TRUE;
			break;	

        case VK_CAPITAL:
            if (g_fHardwareKeyboardPresent)
            {
                if (!g_pkeybdstateCurrent->fIMEOn || g_pkeybdstateCurrent->keyboard == ROMANJI)
                    g_pkeybdstateCurrent->fCapsOn = GetKeyState(VK_CAPITAL) & 0x01;
            }
            else
                g_pkeybdstateCurrent->fCapsOn = !g_pkeybdstateCurrent->fCapsOn;

            break;

//        case VK_LWIN:
//        case VK_RWIN:
//            // Pop open the symbols list.
//            g_xSWNDCursor = 0;
//            g_ySWNDCursor = 0;
//            g_iSWNDFocus = 0;
//            SWNDRender(0);
//            g_bSWNDactive = TRUE;
//            break;

        default:
            break;
    }

} // IMEProcessVirtualKey


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    DakutenValid

Description:

    This function determines whether a character can have a dakuten.

Return Value:

    TRUE if the character can have a dakuten, FALSE otherwise.

-------------------------------------------------------------------*/
TCHAR DakutenValid (TCHAR wcKey)
{
    WORD i;

    if ((wcKey >= FIRST_HIRAGANA) && (wcKey <= LAST_HIRAGANA))

        return (g_rgHiraganaMap[wcKey - FIRST_HIRAGANA].wcDakuten);

    else if ((wcKey >= FIRST_KATAKANA) && (wcKey <= LAST_KATAKANA))

        return (g_rgKatakanaMap[wcKey - FIRST_KATAKANA].wcDakuten);

    else if ((wcKey >= FIRST_HW_KATAKANA) && (wcKey <= LAST_HW_KATAKANA))
    {
        // is this a hiragana characters?
        for (i = 0; i <= LAST_KATAKANA - FIRST_KATAKANA; i++)
        {
            // find out if this is a half-width katakana character
            if (g_rgKatakanaMap[i].wcHalfWidth == wcKey)
                return (g_rgKatakanaMap[i].wcDakuten);
        }   
    }

    return 0;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    HandakutenValid

Description:

    This function determines whether a character can have a handakuten.

Return Value:

    TRUE if the character can have a handakuten, FALSE otherwise.

-------------------------------------------------------------------*/
TCHAR HandakutenValid(TCHAR wcKey)
{
    WORD i;

    if ((wcKey >= FIRST_HIRAGANA) && (wcKey <= LAST_HIRAGANA))

        return (g_rgHiraganaMap[wcKey - FIRST_HIRAGANA].wcHandakuten);

    else if ((wcKey >= FIRST_KATAKANA) && (wcKey <= LAST_KATAKANA))

        return (g_rgKatakanaMap[wcKey - FIRST_KATAKANA].wcHandakuten);

    else if ((wcKey >= FIRST_HW_KATAKANA) && (wcKey <= LAST_HW_KATAKANA))
    {
        // is this a hiragana characters?
        for (i = 0; i <= LAST_KATAKANA - FIRST_KATAKANA; i++)
        {
            // find out if this is a half-width katakana character
            if (g_rgKatakanaMap[i].wcHalfWidth == wcKey)
                return (g_rgKatakanaMap[i].wcHandakuten);
        }   
    }

    return 0;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IsHiragana

Description:

    This function determines whether a string contains only Hiragana,
    dakuten and handakuten characters.

Return Value:

    TRUE if this is a Hiragana string, FALSE otherwise.

-------------------------------------------------------------------*/
BOOL
IsHiragana(TCHAR *szIn)
{
    WORD i = 0;

    // check for empty string
    if (*szIn == '\0') return FALSE;

    while (szIn[i] != '\0') 
    {
        if ((szIn[i] < FIRST_HIRAGANA || szIn[i] > LAST_HIRAGANA)   &&
            (szIn[i] != SYMBOLS_HANDAKUTEN)                         &&
            (szIn[i] != SYMBOLS_DAKUTEN))
        {
            return FALSE;
        }

        i++;
    }

    return TRUE;  // it's Hiragana
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IsKana

Description:

    This function determines whether a string contains only Hiragana,
    Katakana, dakuten and handakuten characters.

Return Value:

    TRUE if this is a pure kana string, FALSE otherwise.

-------------------------------------------------------------------*/
BOOL
IsKana
    (
    TCHAR           *szIn
    )
{
    WORD i = 0;

    // check for empty string
    if (*szIn == '\0') return FALSE;

    while (szIn[i] != '\0') 
    {
        if ((szIn[i] < FIRST_HIRAGANA ||  szIn[i] > LAST_HIRAGANA)          &&
            (szIn[i] < FIRST_KATAKANA ||  szIn[i] > LAST_KATAKANA)          &&
            (szIn[i] < FIRST_HW_KATAKANA || szIn[i] > LAST_HW_KATAKANA)     &&
            (szIn[i] < FIRST_HHHW_KATAKANA || szIn[i] > LAST_HHHW_KATAKANA) &&
            (szIn[i] != SYMBOLS_HANDAKUTEN)                                 &&
            (szIn[i] != SYMBOLS_DAKUTEN))                                
        {
            return FALSE;
        }

        i++;
    }

    return TRUE;  // it's kana.
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IsKatakana

Description:

    This function determines whether a string contains only Katakana,
    dakuten and handakuten characters.

Return Value:

    TRUE if this is a Katakana string, FALSE otherwise.

-------------------------------------------------------------------*/
BOOL
IsKatakana(TCHAR *szIn)
{
    WORD i = 0;

    // check for empty string
    if (*szIn == '\0') return FALSE;

    while (szIn[i] != '\0') 
    {
        if ((szIn[i] < FIRST_KATAKANA || szIn[i] > LAST_KATAKANA)           &&
            (szIn[i] < FIRST_HW_KATAKANA || szIn[i] > LAST_HW_KATAKANA)     &&
            (szIn[i] < FIRST_HHHW_KATAKANA || szIn[i] > LAST_HHHW_KATAKANA) &&
            (szIn[i] != SYMBOLS_HANDAKUTEN)                                 &&
            (szIn[i] != SYMBOLS_DAKUTEN))
        {
            return FALSE;
        }

        i++;
    }

    return TRUE;  // it's Katakana
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    ConvertToHiragana

Description:

Return Value:

    None.

-------------------------------------------------------------------*/
void
ConvertToHiragana
    (
    TCHAR*          szInput,
    TCHAR*          szHiragana
    )
{
    TCHAR           chInput;
    WORD            i;

    do
    {   
        chInput = *szInput;

        if ((chInput >= FIRST_KATAKANA) && (chInput <= LAST_KATAKANA))
            *szHiragana = chInput - 0x60;

        else if (((chInput >= FIRST_HW_KATAKANA) && (chInput <= LAST_HW_KATAKANA)) ||
                 ((chInput >= FIRST_HHHW_KATAKANA) && (chInput <= LAST_HHHW_KATAKANA)))
        {
            if (chInput == SYMBOLS_HW_DAKUTEN)
                *szHiragana = SYMBOLS_DAKUTEN;
            else if (chInput == SYMBOLS_HW_HANDAKUTEN)
                *szHiragana = SYMBOLS_HANDAKUTEN;
            else {
                *szHiragana = chInput;
                for (i = 0 ; i <= LAST_KATAKANA - FIRST_KATAKANA ; i++)
                {
                    if ((g_rgKatakanaMap[i].wcHalfWidth == chInput) ||
                        (g_rgKatakanaMap[i].wcHalfWidthHalfHeight == chInput)) {

                        if (*(szInput + 1) && *(szInput + 1) == SYMBOLS_HW_DAKUTEN &&
                            g_rgKatakanaMap[i].wcDakuten) {
                            *szHiragana = g_rgKatakanaMap[i].wcDakuten - FIRST_KATAKANA + FIRST_HIRAGANA;
                            szInput++;
                        } else if (*(szInput + 1) && *(szInput + 1) == SYMBOLS_HW_HANDAKUTEN &&
                                   g_rgKatakanaMap[i].wcHandakuten) {
                            *szHiragana = g_rgKatakanaMap[i].wcHandakuten - FIRST_KATAKANA + FIRST_HIRAGANA;
                            szInput++;
                        } else {
                            *szHiragana = i + FIRST_KATAKANA - 0x60;
                        }
                        break;
                    }
                }
            }
        }
        else
            *szHiragana = chInput;

        szInput++;
        szHiragana++;

    } while (chInput);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IMEDestroy

Description:

    This function cleans up the IME.
Return Value:

    none

-------------------------------------------------------------------*/
void
IMEDestroy
    (
    void
    )
{
    // destroy the kanji window
    KWNDDestroy();  

    // Release the IME joystick
    if (g_pdidevice2JoystickIME)
    {
        g_pdidevice2JoystickIME->Unacquire ();
        g_pdidevice2JoystickIME->Release ();
        g_pdidevice2JoystickIME = NULL;
    }

} // IMEDestroy


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IMEUpdate

Description:

    This function re-renders the IME.

Return Value:

    none

-------------------------------------------------------------------*/
void
IMEUpdate
    (
    void
    )
{
    static BOOL bLastActive = g_bKWNDactive;
    
    // if the KWND shifted to active or to not active, then reset the iKeyTop to 0
    if (g_bKWNDactive != bLastActive)
    {
        // g_iKeyTop = 0;
        if (bLastActive == TRUE) {
            EditBoxRender();   // render the cleared IME
        } else {
            KWNDRender(g_iKeyTop);
        }
        bLastActive = g_bKWNDactive; 
    }

    if (g_bKWNDactive)
    {
        KWNDReadDirectInputDevices(&g_iKeyTop);
    }

} // IMEUpdate


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IMEBlt

Description:

    This function blits the IME to the back buffer.

Return Value:

    none

-------------------------------------------------------------------*/
void IMEBlt(LPDIRECTDRAWSURFACE lpDDSBack)
{
    if (g_bKWNDactive)
    {
        KWNDBlt(lpDDSBack);
    }
}
