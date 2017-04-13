/*
 * PAGES.H
 * Patron Chapter 7
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
 * contains, managing an IStorage for us.
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
        //CHAPTER7MOD
        LPSTORAGE   m_pIStorage;        //Substorage for this page
        //End CHAPTER7MOD

    public:
        CPage(DWORD);
        ~CPage(void);

        DWORD       GetID(void);
        //CHAPTER7MOD
        BOOL        Open(LPSTORAGE);
        void        Close(BOOL);
        BOOL        Update(void);
        void        Destroy(LPSTORAGE);
        UINT        GetStorageName(LPOLESTR);
        //End CHAPTER7MOD
    };

typedef CPage *PCPage;



//CHAPTER7MOD

/*
 * Structures to save with the document describing the device
 * configuration and pages that we have. This is followed by
 * a list of DWORD IDs for the individual pages.  Note that
 * the strings use TCHAR as a matter of convenience, meaning
 * that non-Unicode files and Unicode files will be incompatible.
 * The same goes for the DEVMODE structure that we store here.
 * If this were a real application that had both types of
 * binaries, then this would be important, but not for this sample.
 */

typedef struct tagDEVICECONFIG
    {
    DWORD       cb;                         //Size of structure
    TCHAR       szDriver[CCHDEVICENAME];
    TCHAR       szDevice[CCHDEVICENAME];
    TCHAR       szPort[CCHDEVICENAME];
    DWORD       cbDevMode;                  //Size of actual DEVMODE
    DEVMODE     dm;                         //Variable
    } DEVICECONFIG, *PDEVICECONFIG;

//Offset to cbDevMode
#define CBSEEKOFFSETCBDEVMODE  (sizeof(DWORD)   \
                               +(3*CCHDEVICENAME*sizeof(TCHAR)))

typedef struct tagPAGELIST
    {
    DWORD       cPages;
    DWORD       iPageCur;
    DWORD       dwIDNext;
    } PAGELIST, *PPAGELIST;

//End CHAPTER7MOD


//PRINT.CPP
BOOL    APIENTRY PrintDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL    APIENTRY AbortProc(HDC, int);


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

        //CHAPTER7MOD
        LPSTORAGE   m_pIStorage;            //Root storage

        //m_hDevMode, m_szDriver, m_szDevice, m_szPort removed
        //End CHAPTER7MOD

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

        //CHAPTER7MOD
        BOOL        StorageSet(LPSTORAGE, BOOL, BOOL);
        BOOL        StorageUpdate(BOOL);
        //End CHAPTER7MOD

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


//CHAPTER7MOD
//Fixed names of streams in the Pages IStorage
#define SZSTREAMPAGELIST        OLETEXT("Page List")
#define SZSTREAMDEVICECONFIG    OLETEXT("Device Configuration")
//End CHAPTER7MOD


#endif  //_PAGES_H_
