#include <windows.h>
#include <windowsx.h>
#include <commdlg.h>
#include <string.h>
#include <memory.h>
#include "app.h"

#include "font.hxx"
//+--------------------------------------------------------
// Class:       CFont
//
// Purpose:     Abstract a font
//
// History:     22-Jan-1993     asmusf  created
//----------------------------------------------------------
CFont::CFont(HFONT hfont)
{
    _hfont = hfont;
    _fDel = FALSE;       // owned elsewhere
}

CFont::CFont(TCHAR *szFace, int iHeight, BOOL fBold, BOOL fItalic, BOOL fUnder)
{
    LOGFONT lf;
    _fDel = FALSE;      // not initialized
 
    memset(&lf,0,sizeof (LOGFONT));
    // rude but effective: truncate
    if( lstrlen( szFace ) > sizeof(lf.lfFaceName) )
    {
        szFace[sizeof(lf.lfFaceName)] = 0;
    }
    lstrcpy(lf.lfFaceName, szFace);

    lf.lfHeight = iHeight * 20;         // twips internal, points in API
    
    if( fBold )
    {
        lf.lfWeight = FW_BOLD;
    }
    lf.lfItalic = fItalic;
    lf.lfUnderline = fUnder;
    Create(lf);
}

BOOL CFont::Create(LOGFONT &lf)
{
    if( _fDel )   
    {
        DeleteObject(_hfont);
        _fDel = FALSE;
    }
    if( _hfont = CreateFontIndirect(&lf) )
    {
        _fDel = TRUE;
        return TRUE;
    }
    return FALSE;
}
                                           
CFont::~CFont()
{
    if( _fDel )
    {
        DeleteObject(_hfont);
    }
}

BOOL CFont::Update(int iHeight, BOOL fBold)
{
    LOGFONT lf;
    GetObject(_hfont, sizeof(LOGFONT), &lf);
    lf.lfWeight = (fBold ? FW_BOLD : FW_NORMAL );

    lf.lfHeight = iHeight * 20;         // twips internal, points in API


    return Create(lf);
}


BOOL CFont::Choose(HWND hwnd)
{
    CHOOSEFONT cf ;
    LOGFONT lf ;

    GetObject(_hfont, sizeof(LOGFONT), &lf);


    // match from TWIPS to LOGPIXELS used in common Dialog
    CScreenCanvas canvas(NULL);
    lf.lfHeight = MulDiv(lf.lfHeight,GetDeviceCaps(canvas, LOGPIXELSY),INCH1);  
    
    lf.lfCharSet = ANSI_CHARSET;

    cf.lStructSize      = sizeof (CHOOSEFONT) ;
    cf.hwndOwner        = hwnd ;
    cf.hDC              = NULL ;
    cf.lpLogFont        = &lf ;
    cf.iPointSize       = 0 ;
    cf.Flags            = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS
                                                 | CF_EFFECTS ;
    cf.rgbColors        = 0L ;
    cf.lCustData        = 0L ;
    cf.lpfnHook         = NULL ;
    cf.lpTemplateName   = NULL ;
    cf.hInstance        = NULL ;
    cf.lpszStyle        = NULL ;
    cf.nFontType        = 0 ;               // Returned from ChooseFont
    cf.nSizeMin         = 0 ;
    cf.nSizeMax         = 0 ;

    if( !ChooseFont (&cf) )
    {
        return FALSE;
    }
//    MessageBox( hwnd, lf.lfFaceName, TEXT("Font Chosen"), MB_OK );
    
    // adjust back to using TWIPS
    lf.lfHeight = MulDiv(lf.lfHeight,INCH1,GetDeviceCaps(canvas, LOGPIXELSY));  
    lf.lfWidth=0;               // font mapper knows best
    
    // create the font   
    return Create(lf);
}


