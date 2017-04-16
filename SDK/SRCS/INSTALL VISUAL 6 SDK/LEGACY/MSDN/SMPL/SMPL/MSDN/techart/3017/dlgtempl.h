/*
    Copyright 1993 Microsoft Corporation. All Right reserved.
    Written By: J.Seghers 1993  
    History:
        7/94    P.Oka   Ported to WIN32 and Macintosh
        8/19/94 NigelT  Cleaned up for Win32 only
*/
/////////////////////////////////////////////////////////////////////////////
// Dialog Template parsing class and structures

#ifndef __DLGTEMPL_H__
#define __DLGTEMPL_H__

struct ControlData;
struct DialogBoxHeader;

const USER_TYPE = 0x0000;
const CTRL_TYPE = 0x0080;
const BUTTON_TYPE = CTRL_TYPE + 0;
const EDIT_TYPE = CTRL_TYPE + 1;
const STATIC_TYPE  = CTRL_TYPE + 2;
const LISTBOX_TYPE = CTRL_TYPE + 3;
const SCROLLBAR_TYPE = CTRL_TYPE + 4;
const COMBOBOX_TYPE = CTRL_TYPE + 5;


class CDlgTemplate : public CObject
{
public:
    CDlgTemplate(UINT iddTemplate);
    ~CDlgTemplate();
    
    LPCSTR  GetCtlClass();
    UINT    GetCtlID();
    DWORD   GetCtlStyle();
    LPCSTR  GetCtlText();
    void   GetCtlRect(LPRECT lpRect);
    BYTE   GetCtlType();
    BYTE   GetCtlCount();
    void   GetDlgRect(LPRECT lpRect);
    void   ConvertDluToPixel(LPRECT lpRect);

    
    BOOL NextControl();

protected:
    void   GetDLUBaseUnits();

    ControlData*        m_pCurrentControl;
    int                 m_nCurControl;
    DialogBoxHeader*    m_pDialogHeader;
    HGLOBAL             m_hTemplate;
    int                 m_cxBase, m_cyBase;     // DLU Base Units      

    // Storage for converted unicode strings
    CString             m_strCtlClass;
    CString             m_strCtlText;
};  

    #pragma pack(1) // These are resource file formats and must be byte packed
    struct DialogBoxHeader {
        DWORD lStyle;
        DWORD dwExtendedStyle;
        WORD  bNumberOfItems;
        WORD  x;
        WORD  y;
        WORD  cx;
        WORD  cy;
        LPCSTR GetMenuName();
        LPCSTR GetClassName();
        LPCSTR GetCaption();
        WORD   GetPointSize();
        LPCSTR GetFaceName();

        ControlData* GetFirstControl();

    //    char  szMenuName[];  // 0x0000 OR 0xFFFF, 0x???? OR Unicode sz
    //    char  szClassName[]; // 0x0000 OR 0xFFFF, 0x???? OR Unicode sz
    //    char  szCaption[];   // 0x0000 OR Unicode sz
    //    WORD  wPointSize;    /* only if DS_SETFONT */
    //    char  szFaceName[];  /* only if DS_SETFONT */
    };

    struct ControlData
    {
        DWORD lStyle;
        DWORD dwExtendedStyle;
        WORD  x;
        WORD  y;
        WORD  cx;
        WORD  cy;
        WORD  wID;

        ControlData* GetNextControl();
        LPCSTR GetClass();
        LPCSTR GetText();
    //    union
    //    {
    //        DWORD class;     // 0xffff , 0x????  
    //        char szClass[];  // otherwise Unicode sz
    //    } ClassID;
    //    char szText[];
    };

    #pragma pack()      // return to default packing

#endif //__DLGTEMPL_H_
