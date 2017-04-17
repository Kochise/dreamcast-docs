/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    shared.cxx

Abstract:

    This file contains the destroy function for resources which are
    shared by the sepearate libraries.

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#include "precomp.hpp"


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CreateKanaFont

Description:

    Creates the kana font.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
HFONT
CreateKanaFont
    (
    LONG lFontHeight
    )
{
    LOGFONT             lf;

    memset (&lf, 0, sizeof(lf));
    lf.lfHeight = lFontHeight;
    lf.lfCharSet = DEFAULT_CHARSET;
    lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
    lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    lf.lfQuality = DEFAULT_QUALITY;
    lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
    _tcscpy (lf.lfFaceName, FONTFACENAME);

    return CreateFontIndirect (&lf);

} // CreateKanaFont


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CreateSharedResources

Description:

Return Value:
    
    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL
CreateSharedResources 
    (
    void
    )
{
    if (!AddFontResource (FONTFILENAME)) 
    {
        OutputDebugString(TEXT("TKIME: ERROR: Add font resource for \"msgot.ttf\" failed.\n"));
        OutputDebugString(TEXT("TKIME: To fix this, use the Configuration Tool to turn on the \"Tankanji IME\"\r\n"));
        OutputDebugString(TEXT("TKIME: and \"Japanese font\", and then rebuild the image.  \r\n\r\n"));
        OutputDebugString(TEXT("TKIME: Alternatively, from the WinCE command window, type \"set IMGTKIME=1\", \r\n"));
        OutputDebugString(TEXT("TKIME: and then run \"makeimg\".\r\n"));
        return FALSE;
    }

    g_hfontKana = CreateKanaFont(FONTDEFHEIGHT);
    if (!g_hfontKana) {
        RemoveFontResource (FONTFILENAME);
        return FALSE;
    }

    if (!CreateDirectInput(g_hinstApp, g_hwndApp, &g_pdidevice2JoystickApp))
        return FALSE;

    return TRUE;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    DestroySharedResources

Description:

    Destroys the kana font and the global direct input interface.

Return Value:
    
    None.

-------------------------------------------------------------------*/
void
DestroySharedResources
    (
    void
    )
{
    DestroyDirectInput();

    if (g_hfontKana)
        DeleteObject (g_hfontKana);

    RemoveFontResource (FONTFILENAME);
}
