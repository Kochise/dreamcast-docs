/*
 * PAGES.H
 * Patron Chapter 1
 *
 * Definitions and function prototypes for the Pages window control.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _PAGES_H_
#define _PAGES_H_

//Versioning.
#define VERSIONMAJOR                2
#define VERSIONMINOR                0
#define VERSIONCURRENT              0x00020000

//Classname
#define SZCLASSPAGES                TEXT("pages")

#define HIMETRIC_PER_INCH           2540
#define LOMETRIC_PER_INCH           254
#define LOMETRIC_BORDER             60          //Border around page


//Window extra bytes and offsets
#define CBPAGESWNDEXTRA             (sizeof(LONG))
#define PAGEWL_STRUCTURE            0


/*
 * Page class describing an individual page and what things it
 * contains.
 *
 * A DWORD is used to identify this page as the name of the storage
 * is the string form of this ID.  If we added a page every second,
 * it would take 136 years to overrun this counter, so we can
 * get away with saving it persistently.  I hope this software is
 * obsolete by then.
 */

class CPage
    {
    private:
        DWORD       m_dwID;             //Persistent identifier

    public:
        CPage(DWORD);
        ~CPage(void);

        DWORD           GetID(void);
    };

typedef CPage *PCPage;



//PRINT.CPP
BOOL    APIENTRY AbortProc(HDC, int);
BOOL    APIENTRY PrintDlgProc(HWND, UINT, WPARAM, LPARAM);


//PAGEWIN.CPP
LRESULT APIENTRY PagesWndProc(HWND, UINT, WPARAM, LPARAM);
void             RectConvertMappings(LPRECT, HDC, BOOL);


class CPages : public CWindow
    {
    friend LRESULT APIENTRY PagesWndProc(HWND, UINT, WPARAM, LPARAM);
    friend BOOL    APIENTRY PrintDlgProc(HWND, UINT, WPARAM, LPARAM);

    private:
        UINT        m_iPageCur;             //Current page
        UINT        m_cPages;               //Number of pages

        HWND        m_hWndPageList;         //Listbox with page list
        HFONT       m_hFont;                //Page font
        BOOL        m_fSystemFont;          //m_hFont system object?

        UINT        m_cx;                   //Page size in LOMETRIC
        UINT        m_cy;

        UINT        m_xMarginLeft;          //Unusable margins,
        UINT        m_xMarginRight;         //in LOMETRIC
        UINT        m_yMarginTop;
        UINT        m_yMarginBottom;

        UINT        m_xPos;                 //Viewport scroll pos,
        UINT        m_yPos;                 //both in *PIXELS*

        DWORD       m_dwIDNext;             //Next ID for a page.

        HGLOBAL     m_hDevMode;             //Current DevMode config

        TCHAR       m_szDriver[CCHDEVICENAME];
        TCHAR       m_szDevice[CCHDEVICENAME];
        TCHAR       m_szPort[CCHDEVICENAME];

    private:
        void        Draw(HDC, BOOL, BOOL);
        void        UpdateScrollRanges(void);
        BOOL        ConfigureForDevice(void);
        BOOL        PageGet(UINT, PCPage *, BOOL);
        BOOL        PageAdd(UINT, DWORD, BOOL);

    public:
        CPages(HINSTANCE);
        ~CPages(void);

        BOOL        Init(HWND, LPRECT, DWORD, UINT, LPVOID);

        void        New(void);
        BOOL        Print(HDC, LPTSTR, DWORD, UINT, UINT, UINT);

        void        RectGet(LPRECT);
        void        RectSet(LPRECT, BOOL);
        void        SizeGet(LPRECT);
        void        SizeSet(LPRECT, BOOL);

        PCPage      ActivePage(void);
        UINT        PageInsert(UINT);
        UINT        PageDelete(UINT);
        UINT        CurPageGet(void);
        UINT        CurPageSet(UINT);
        UINT        NumPagesGet(void);

        BOOL        DevModeSet(HGLOBAL, HGLOBAL);
        HGLOBAL     DevModeGet(void);
    };

typedef CPages *PCPages;


#endif  //_PAGES_H_
