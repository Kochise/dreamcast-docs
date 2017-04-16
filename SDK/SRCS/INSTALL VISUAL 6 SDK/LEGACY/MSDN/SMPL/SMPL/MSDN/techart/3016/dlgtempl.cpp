/*
    Copyright 1993 Microsoft Corporation. All Right reserved.
    Written By: J.Seghers 1993  
    History:
        7/94    P.Oka   Ported to WIN32 and Macintosh
        8/19/94 NigelT  Cleaned up for Win32 only
*/
//
// This file contains Dialog Template Parsing classes
//
#include "stdafx.h"
#include "dlgtempl.h"

// Strings in dialog templates use UNICODE format.
// Undefine lstrlen to prepare for redefinition
#ifdef lstrlen
#undef lstrlen
#endif
// Use wide char format for string length function
#define lstrlen lstrlenW

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTemplate


CDlgTemplate::CDlgTemplate(UINT iddTemplate)
{
    HRSRC hRsrc = ::FindResource(AfxGetResourceHandle(),
                            MAKEINTRESOURCE(iddTemplate), RT_DIALOG);
    m_hTemplate = ::LoadResource(AfxGetResourceHandle(), hRsrc);
    ASSERT(m_hTemplate != NULL);
    m_pDialogHeader = (DialogBoxHeader*) ::LockResource(m_hTemplate);
    ASSERT(m_pDialogHeader != NULL);
    m_pCurrentControl = m_pDialogHeader->GetFirstControl();
    m_nCurControl = 0;
    GetDLUBaseUnits();
    
}

CDlgTemplate::~CDlgTemplate()
{
    ::FreeResource(m_hTemplate);
}

BYTE CDlgTemplate::GetCtlCount()
{
    return (BYTE) m_pDialogHeader->bNumberOfItems;
}

////////////////////////////////////////////////////////////////////////////////////
BYTE CDlgTemplate::GetCtlType()
{
    LPCSTR lpszClass =  m_pCurrentControl->GetClass();

    LPWORD lptstr = (LPWORD) lpszClass;
    // Win32 uses a word for control type
    if ((*lptstr == 0xffff) && (* (lptstr + 1) & 0x0080))  
    {
        // Return a BYTE for compatability of WIN16 code.
        return LOBYTE(*(lptstr + 1));
    }                            
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////    
LPCSTR CDlgTemplate::GetCtlClass()
{
    // Need to convert string to ANSI for WIN32
    LPWORD lpwszCtlClass = (LPWORD) m_pCurrentControl->GetClass();
    INT nBuffSz;

    if (nBuffSz = WideCharToMultiByte(CP_ACP, NULL, lpwszCtlClass, 
            -1, NULL, 0, NULL, NULL))
    {
        LPSTR lpszCtlClass = m_strCtlClass.GetBufferSetLength(nBuffSz + 1);
        ASSERT(lpszCtlClass != NULL);

        VERIFY(WideCharToMultiByte(CP_ACP, NULL, lpwszCtlClass, 
            -1, lpszCtlClass, nBuffSz+1, NULL, NULL));
        return lpszCtlClass;
    }
    return NULL;
}

UINT   CDlgTemplate::GetCtlID()
{
    return m_pCurrentControl->wID;
}

DWORD  CDlgTemplate::GetCtlStyle()
{
    return m_pCurrentControl->lStyle;
}

LPCSTR CDlgTemplate::GetCtlText()
{
    // REVIEW: Need to convert string to ANSI for WIN32
    // Need to convert string to ANSI for WIN32
    LPWORD lpwszText =  (LPWORD) m_pCurrentControl->GetText();
    INT nBuffSz;

    if (nBuffSz = WideCharToMultiByte(CP_ACP, NULL, lpwszText, 
            -1, NULL, 0, NULL, NULL))
    {
        LPSTR lpszCtlText = m_strCtlText.GetBufferSetLength(nBuffSz + 1);
        ASSERT(lpszCtlText != NULL);

        VERIFY(WideCharToMultiByte(CP_ACP, NULL, lpwszText, 
            -1, lpszCtlText, nBuffSz+1, NULL, NULL));
        return lpszCtlText;
    }
    return NULL;
      
}

void   CDlgTemplate::GetCtlRect(LPRECT lpRect)
{
    lpRect->left   = m_pCurrentControl->x;
    lpRect->right  = lpRect->left + m_pCurrentControl->cx;
    lpRect->top    = m_pCurrentControl->y;
    lpRect->bottom = lpRect->top + m_pCurrentControl->cy;
    ConvertDluToPixel(lpRect);
}

void CDlgTemplate::GetDlgRect(LPRECT lpRect)
{
    lpRect->left   = m_pDialogHeader->x;
    lpRect->right  = lpRect->left + m_pDialogHeader->cx;
    lpRect->top    = m_pDialogHeader->y;
    lpRect->bottom = lpRect->top + m_pDialogHeader->cy;
    ConvertDluToPixel(lpRect);
}

void CDlgTemplate::ConvertDluToPixel(LPRECT lpRect)
{
    lpRect->left   = (lpRect->left * m_cxBase) / 4;
    lpRect->right  = (lpRect->right * m_cxBase) / 4;
    lpRect->top    = (lpRect->top * m_cyBase) / 8;
    lpRect->bottom = (lpRect->bottom * m_cyBase) / 8;
}

    
BOOL CDlgTemplate::NextControl()
{
    m_pCurrentControl = m_pCurrentControl->GetNextControl();
    return (++m_nCurControl < m_pDialogHeader->bNumberOfItems);
        
}

void CDlgTemplate::GetDLUBaseUnits()
{
    HDC hDC = ::GetDC(NULL);
    int nWeight;
    
    // Round up to get better results (NigelT)
    // Note that this is still wrong for Lucida Console 8pt
    // for some unknown reason.
    int nHeight = (m_pDialogHeader->GetPointSize() *
                     ::GetDeviceCaps(hDC, LOGPIXELSY) + 36) / 72;
    TRACE("Font size: %d pt. Height: %d pixels", 
          m_pDialogHeader->GetPointSize(), nHeight);
    CFont font;

    nWeight = FW_BOLD; // All dialogs use bold fonts (NigelT)
    font.CreateFont(-nHeight, 0, 0, 0, nWeight, 0, 0, 0, 0, 0, 0, 0, 0,
                            m_pDialogHeader->GetFaceName());

    HGDIOBJ hOldFont = ::SelectObject(hDC, font.m_hObject);
    
    TEXTMETRIC tm;
    ::GetTextMetrics(hDC, &tm);
    m_cyBase = tm.tmHeight;

    TRACE("Font pitch and family: %4.4XH", tm.tmPitchAndFamily);
    if (tm.tmPitchAndFamily & 0x01)
    {
        // Proportional font
        TRACE("Dlg has prop font");
        char szAveCharWidth[52];        // array to hold A-Z,a-z
    
        for (int i = 0; i < 26; i++)
        {
            szAveCharWidth[i] = (char)(i + 'a');
            szAveCharWidth[i + 26] = (char)(i + 'A');
        }
        SIZE sizeExtent;
        ::GetTextExtentPoint(hDC, szAveCharWidth, 52, &sizeExtent);
        m_cxBase = (sizeExtent.cx + 26) / 52;
    }
    else
    {
        TRACE("Dlg has fixed pitch font");
        m_cxBase = tm.tmAveCharWidth;
    }
    TRACE("Dlg base units: %d x %d", m_cxBase, m_cyBase);
    ::SelectObject(hDC, hOldFont);
    ::ReleaseDC(NULL, hDC);
}

LPCSTR DialogBoxHeader::GetMenuName()
{
    return (LPCSTR)(this + 1);  // Menu Name is right after header
}

LPCSTR DialogBoxHeader::GetClassName()
{
    LPCSTR lpszName = GetMenuName();

    // Use a pointer to a WORD for convience    
    LPWORD lpw = (LPWORD) lpszName;
    
    if (*lpw == 0x0000)
    {   // No Menu
        // Advance ptr past Menu Atom
        lpw += 1;
    }
    else if (*lpw == 0xffff)
    {   // Menu exists w/resource ID                    
        // Advance ptr past Menu Atom
        // and resource ID 
        lpw += 2;
    }
    else
    {   // Menu name is a Unicode string         
        // Advance ptr past unicode string
        lpw += lstrlen(lpw) + 1;
    }
    lpszName = (LPCSTR) lpw;

    return lpszName;
}

LPCSTR DialogBoxHeader::GetCaption()
{
    LPCSTR lpszCaption = GetClassName();

    // Use a pointer to a WORD for convience
    LPWORD lpw = (LPWORD) lpszCaption;

    if (*lpw == 0x0000)
    {   // No Caption
        // Advance ptr past Caption Atom
        lpw += 1;
    }
    else if (*lpw == 0xffff)
    {   // Captions Exists w/resource ID                    
        // Advance ptr past Caption Atom & Resource ID
        lpw += 2;
    }
    else
    {   // Caption is a Unicode String         
        // Advance ptr past unicode string
        lpw += lstrlen(lpw) + 1;
    }
    lpszCaption = (LPCSTR) lpw;

    return lpszCaption;
}

WORD DialogBoxHeader::GetPointSize()
{
    if (lStyle & DS_SETFONT)
    {
        LPCSTR lpszCaption = GetCaption();

        // Use a pointer to a WORD for convience
        LPWORD lpw = (LPWORD) lpszCaption;
        // Advance past Caption string
        lpw += lstrlen(lpw) + 1;

        lpszCaption = (LPCSTR) lpw;
    
        return *(LPWORD)lpszCaption;
    }
    // Default is 10 Point 
    return 10;
}

LPCSTR DialogBoxHeader::GetFaceName()
{
    if (lStyle & DS_SETFONT)
    {
        LPCSTR lpszCaption = GetCaption();
        // Use a pointer to a WORD for convience
        LPWORD lpw = (LPWORD) lpszCaption; 
        // Advance past Caption String & Point Size
        lpw += lstrlen(lpw) + 2;
        lpszCaption = (LPCTSTR) lpw;
        return lpszCaption;
    }
    // Default is system font
    return "System";
}

    
ControlData* DialogBoxHeader::GetFirstControl()
{
    LPCSTR lpszLastString;
    if (lStyle & DS_SETFONT)
        lpszLastString = GetFaceName();
    else
        lpszLastString = GetCaption();
    
    // Use a pointer to a WORD for convience
    LPWORD lpw = (LPWORD) lpszLastString;
    // Advance past Font Name or Caption
    lpw += lstrlen(lpw) + 1;

    LPWORD lpwStart = (LPWORD) this;
    UINT wCount = lpw - lpwStart;
    // if we are not on a DWORD Aligned the add
    // a word for padding
    if (wCount % 2)
    {
        lpw++;
    }

    lpszLastString = (LPCSTR) lpw;

    return (ControlData*) lpszLastString;
}

/////////////////////////////////////////////////////////////////////////////
// ControlData class

ControlData* ControlData::GetNextControl()
{
    LPCSTR lpEnd = GetText();

    // Use a pointer to a WORD for convience
    LPWORD lpw = (LPWORD) lpEnd;
    if (*lpw ==  0xffff)
    {   // Text uses resource ID
        // Advance ptr past resource ID 
        lpw += 2;
    }
    else
    {   // Text uses unicode string
        // Advance past unicode string
        lpw += lstrlen(lpw) + 1;
    }
    // Advance past extra WORD
    lpw += *lpw + 1;
        
    LPWORD lpwStart = (LPWORD) this;
    UINT wCount = lpw - lpwStart;
    // if we are not on a DWORD Aligned the add
    // a word for padding
    if (wCount % 2)
    {
        lpw++;
    }
    
    lpEnd = (LPCSTR) lpw;

    return (ControlData*) lpEnd;
}

LPCSTR ControlData::GetClass()
{
    return (LPCSTR)(this + 1);  // Class Name is right after struct
}

LPCSTR ControlData::GetText()    
{
    LPCSTR lpszText = GetClass();
    // Use a pointer to a WORD for convience

    LPWORD lpw = (LPWORD) lpszText;
    if (*lpw == 0xffff) 
    {
        lpw += 2;
    }
    else
    {
        lpw += lstrlen(lpw) + 1;
    }
    lpszText = (LPCSTR) lpw;
    return lpszText;
}



//#define DEBUGGING_CODE_FOR_DLGTEMPLATE_CLASS

#ifdef DEBUGGING_CODE_FOR_DLGTEMPLATE_CLASS
char *lpszClassNames[] = 
{
    "Button", 
    "Edit", 
    "Static", 
    "List box",
    "Scroll bar", 
    "Combo box"
}; 

void ReadDialogTemplate(UINT iddTemplate)
{
    CDlgTemplate dlgTemp(iddTemplate);
    
    CRect rect;
    do
    {
        LPCSTR lpszClass = dlgTemp.GetCtlClass();
        if (*lpszClass & 0x80)
            lpszClass = lpszClassNames[*lpszClass & 0x7f];
            
        UINT nID = dlgTemp.GetCtlID();
        DWORD dwStyle = dlgTemp.GetCtlStyle();
        LPCSTR lpszText = dlgTemp.GetCtlText();
        
        dlgTemp.GetCtlRect(&rect);
        TRACE("%04x %08lx %20s (%3d, %3d) %3dx%3d %s\n",
                 nID, dwStyle, lpszClass,
                 rect.left, rect.top, rect.Width(), rect.Height(),
                 lpszText);
    } while (dlgTemp.NextControl());
}

#endif  // #ifdef DEBUGGING_CODE_FOR_DLGTEMPLATE_CLASS
