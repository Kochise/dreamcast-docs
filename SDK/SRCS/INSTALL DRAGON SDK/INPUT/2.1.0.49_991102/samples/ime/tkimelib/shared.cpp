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


#include "precomp.hxx"


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
#ifdef KANJI
    if (!AddFontResource (FONTFILENAME)) 
    {
        OutputDebugString(TEXT("Add font resource failed.\n"));
        OutputDebugString(TEXT("Make sure the font file \"msgot.ttf\" is in the image.\r\n"));
        OutputDebugString (TEXT("To do this, type 'set IMGTKIME=1', then run 'makeimg'.\r\n"));
        return FALSE;
    }
#endif


    g_hfontKana = CreateKanaFont (FONTDEFHEIGHT);
    if (!g_hfontKana)
    {
#ifdef KANJI
        RemoveFontResource (FONTFILENAME);
#endif // KANJI
        return FALSE;
    }

    if (!IME_CreateDirectInput(g_hinstApp, g_hwndApp, &g_pdidevice2JoystickApp))
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
    IME_DestroyDirectInput();

    if (g_hfontKana)
        DeleteObject (g_hfontKana);

#ifdef KANJI
    RemoveFontResource (FONTFILENAME);
#endif  // KANJI
}
