/*
 * CLASSLIB.H
 * Sample Code Class Libraries
 *
 * Master include file for our own Class Library containing:
 *  CStringTable    Class that manages a stringtable.
 *  CHourglass      Class to manage the hourglass.
 *
 *  CWindow         Basic window class for most other classes in here
 *  CToolBar        Wrapper for a toolbar control
 *  CStatusLine     Wrapper for a status lib control
 *
 *  CFrame          Frame window
 *  CClient         Client window with a uniform interface for
 *                  MDI and SDI frames.
 *  CDocument       Document window, also with a uniform interface
 *                  for MDI and SDI.
 *
 *  CDocumentAdviseSink Object implemented in the frame that the
 *                      document notifies of important events.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _CLASSLIB_H_
#define _CLASSLIB_H_

#include <book1632.h>

//Get default resource definitions
#include "classres.h"


class CStringTable;
class CHourglass;
class CToolBar;
class CStatusLine;
class CWindow;
class CFrame;
class CClient;
class CDocument;
class CDocumentAdviseSink;
class CHatchWin;


/**
 ** CStringTable providing string table management for anyone.
 **/

class CStringTable
    {
    protected:
        HINSTANCE       m_hInst;
        UINT            m_idsMin;
        UINT            m_idsMax;
        USHORT          m_cStrings;
        LPTSTR          m_pszStrings;
        LPTSTR         *m_ppszTable;

    public:
        CStringTable(HINSTANCE);
        ~CStringTable(void);

        BOOL Init(UINT, UINT);

        //Function to resolve an ID into a string pointer.
        const LPTSTR operator [](const UINT) const;
    };


typedef CStringTable *PCStringTable;

/*
 * Typical classes that initialize a stringtable should have an m_pST
 * member, then they can use this macro conveniently.
 */

#define PSZ(i) ((*m_pST)[i])
#define CCHSTRINGMAX            256


/**
 ** CHourglass:  Manages the hourglass and mouse capture
 **/

class CHourglass
    {
    protected:
        HWND            m_hWndCapture;      //Window with capture
        HCURSOR         m_hCur;             //Cursor held.

    public:
        CHourglass(void);
        CHourglass(HWND);
        ~CHourglass(void);
    };

typedef CHourglass *PCHourglass;



/**
 ** CWindow:  Our basic window class.
 **/

class CWindow
    {
    protected:
        HINSTANCE   m_hInst;            //Task instance
        HWND        m_hWnd;             //Window handle of the window

    public:
        //Standard Class Functions
        CWindow(HINSTANCE);
        ~CWindow(void);

        //Just returns members.  No need to modify
        HWND        Window(void);
        HINSTANCE   Instance(void);
    };


typedef CWindow * PCWindow;




/**
 ** CToolBar encapculates a toolbar control
 **/

#include <bttncur.h>
#include <gizmobar.h>


class CToolBar : public CWindow
    {
    protected:
        UINT            m_cyBar;

    public:
        CToolBar(HINSTANCE);
        ~CToolBar(void);

        BOOL   Init(HWND, UINT, UINT);

        //Window message wrappers
        void   OnSize(HWND);
        void   FontSet(HFONT, BOOL);
        HFONT  FontGet(void);
        void   Enable(BOOL);

        //ToolBar function wrappers
        HWND   HwndAssociateSet(HWND);
        HWND   HwndAssociateGet(void);

        BOOL   Add(UINT, UINT, UINT, UINT, UINT, LPTSTR, HBITMAP
                   , UINT, UINT);
        BOOL   Remove(UINT);

        LONG   SendMessage(UINT, UINT, WPARAM, LPARAM);

        BOOL   Show(UINT, BOOL);
        BOOL   Enable(UINT, BOOL);
        BOOL   Check(UINT, BOOL);
        UINT   FocusSet(UINT);
        BOOL   Exist(UINT);

        int    TypeGet(UINT);

        DWORD  DataSet(UINT, DWORD);
        DWORD  DataGet(UINT);
        BOOL   NotifySet(UINT, BOOL);
        BOOL   NotifyGet(UINT);

        int    TextGet(UINT, LPTSTR, UINT);
        void   TextSet(UINT, LPTSTR);
        UINT   IntGet(UINT, BOOL *, BOOL);
        void   IntSet(UINT, int, BOOL);
    };


typedef CToolBar *PCToolBar;





/**
 ** CStatusLine encapsulates a status line control.
 **/

#include <stastrip.h>


class CStatusLine : public CWindow
    {
    protected:
        UINT        m_cy;           //Control height

    public:
        CStatusLine(HINSTANCE);
        ~CStatusLine(void);

        BOOL  Init(HWND, UINT, UINT);

        void  OnSize(HWND);
        void  MessageSet(LPTSTR);
        UINT  MessageGet(LPTSTR, UINT);
        UINT  MessageGetLength(void);
        void  FontSet(HFONT, BOOL);
        HFONT FontGet(void);
        void  Enable(BOOL);

        BOOL  MessageMap(HWND, HINSTANCE, UINT, UINT, UINT, UINT
                  , UINT, UINT, UINT, UINT, UINT);
        void  MenuSelect(WPARAM, LPARAM);
        void  MessageDisplay(UINT);
    };

typedef CStatusLine *PCStatusLine;





/**
 ** CFrame encapsulates a main application window
 **/

//FRAMEWIN.CPP:  Standard window procedure and AboutProc
LRESULT APIENTRY FrameWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL    APIENTRY AboutProc(HWND, UINT, WPARAM, LPARAM);

#define CBFRAMEWNDEXTRA     sizeof(LONG)
#define FRAMEWL_STRUCTURE   0


/*
 * Structure containing resource ranges for initialization of
 * a CFrame object through its Init member.
 */

typedef struct tagFRAMEINIT
    {
    UINT    idsMin;         //Stringtable start and end
    UINT    idsMax;

    UINT    idsStatMin;     //StatStrip stringtable start and end
    UINT    idsStatMax;

    UINT    idStatMenuMin;  //Start and end IDs for StatStrip
    UINT    idStatMenuMax;  //popup menu IDs

    UINT    iPosWindowMenu; //Position of the Window menu (MDI init)
    UINT    cMenus;         //Number of popup menus we have.

    int     x;              //Window positioning.
    int     y;
    int     cx;
    int     cy;
    } FRAMEINIT, *PFRAMEINIT;



//FRAME.CPP:  Frame object that creates a main window

class CFrame : public CWindow
    {
    //Let our window procedure look in our private variables.
    friend LRESULT APIENTRY FrameWndProc(HWND, UINT, WPARAM, LPARAM);
    friend class CDocumentAdviseSink;

    protected:
        HINSTANCE       m_hInstPrev;        //WinMain parameters
        LPTSTR          m_pszCmdLine;
        int             m_nCmdShow;

        LPTSTR         *m_ppszCmdArgs;      //Command line arguments
        UINT            m_cCmdArgs;
        BOOL            m_fCmdsParsed;      //Been parsed yet?

        BOOL            m_fInit;            //Initializing or closing
        BOOL            m_fSizing;          //Inside WM_SIZE
        BOOL            m_fClosing;         //In WM_CLOSE

        BOOL            m_fLastEnable;      //Toolbar enable state
        BOOL            m_fLastPaste;

        HMENU          *m_phMenu;           //Popup menu handles
        HMENU           m_hMenuWindow;      //"Window" menu

        HACCEL          m_hAccel;           //Accelerators
        HBITMAP         m_hBmp;             //Toolbar images
        UINT            m_cyBar;            //Toolbar height
        UINT            m_dxB;              //Toolbar button sizes
        UINT            m_dyB;

        PCToolBar       m_pTB;              //Toolbar
        PCStatusLine    m_pSL;              //Status line

        PCStringTable   m_pST;              //Stringtable.
        CClient        *m_pCL;              //SDI/MDI client window

    protected:
        virtual BOOL     ParseCommandLine(void);
        virtual CClient *CreateCClient(void);

        virtual BOOL     RegisterAllClasses(void);
        virtual BOOL     PreShowInit(void);
        virtual void     OpenInitialFiles(void);
        virtual UINT     CreateToolbar(void);

        virtual BOOL     FMessageHook(HWND, UINT, WPARAM, LPARAM
                             , LRESULT *);
        virtual LRESULT  OnCommand(HWND, WPARAM, LPARAM);
        virtual void     OnDocumentDataChange(CDocument *);
        virtual void     OnDocumentActivate(CDocument *);

        virtual BOOL     SaveOpenDialog(LPTSTR, UINT, UINT, BOOL
                             , UINT *);
        virtual UINT     ReplaceCharWithNull(LPTSTR, int);
        virtual LPTSTR   PszWhiteSpaceScan(LPTSTR, BOOL);

    public:
        CFrame(HINSTANCE, HINSTANCE, LPSTR, int);
        virtual ~CFrame(void);

        virtual BOOL     Init(PFRAMEINIT);

        virtual WPARAM   MessageLoop(void);
        virtual BOOL     AskAndSave(LPTSTR);
        virtual void     UpdateMenus(HMENU, UINT);
        virtual void     UpdateToolbar(void);
        virtual void     WindowTitleSet(CDocument *, BOOL);

        virtual PCStatusLine inline StatusLine(void);
    };


typedef CFrame *PCFrame;


//Other Miscellaneous CFrame definitions

//ToolBar and StatStrip IDs used in this frame
#define ID_GIZMOBAR         11
#define ID_STATSTRIP        12

//Classname
#define SZCLASSFRAME        TEXT("Frame")





/**
 ** CClient encapsulates an MDI or SDI client window
 **/

//Forward reference
class CDocumentAdviseSink;
typedef CDocumentAdviseSink *PCDocumentAdviseSink;


//CLIENT.CPP
LRESULT APIENTRY SDIClientWndProc(HWND, UINT, WPARAM, LPARAM);

#define CBCLIENTWNDEXTRA    sizeof(LONG)
#define CLIENTWL_HWNDDOC    0


class CClient : public CWindow
    {
    friend LRESULT APIENTRY SDIClientWndProc(HWND, UINT, WPARAM
        , LPARAM);

    protected:
        PCFrame         m_pFR;          //Frame window information
        UINT            m_cDoc;         //Count of open documents
        CDocument *     m_pDocLast;     //Last created document

        HWND            m_hListDocs;    //List of documents

        //This is created to send notifications to the frame
        PCDocumentAdviseSink m_pAdv;

    private:
        //This non-overridable sets m_pDocLast
        CDocument         * CreateDoc(void);

    protected:
        //Overridable for creating a new CDocument
        virtual CDocument * CreateCDocument(void);

    public:
        CClient(HINSTANCE, PCFrame);
        virtual ~CClient(void);

        PCFrame                 Frame(void);
        UINT                    DocumentCount(void);
        HWND                    DocumentList(void);

        virtual BOOL            Init(HMENU, LPRECT);

        virtual BOOL            TranslateAccelerator(LPMSG);
        virtual LRESULT         DefaultFrameProc(HWND, UINT, WPARAM
                                    , LPARAM);
        virtual void            OnWindowCommand(UINT, UINT);
        virtual void            OnSize(UINT, UINT, UINT, UINT);

        virtual CDocument *     NewDocument(BOOL);
        virtual CDocument *     ActiveDocument(void);
        virtual BOOL            ShowDocument(CDocument *, BOOL);
        virtual BOOL            SDIVerify(void);
        virtual UINT            CloseDocument(CDocument *);
        virtual BOOL            QueryCloseAllDocuments(BOOL, BOOL);
        virtual BOOL            FCleanVerify(CDocument *);
    };


typedef CClient *PCClient;


//Other Miscellaneous CFrame definitions

//Document window identifiers
#define ID_DOCUMENT         999     //Internal ID for all documents
#define ID_MDICHILDMIN      1000    //Starting point for MDI doc IDs

#define SZCLASSSDICLIENT    TEXT("SDIClient")




/**
 ** CDocument encapsulates an MDI or SDI child window
 **/


//DOCWIN.CPP
LRESULT APIENTRY DocumentWndProc(HWND, UINT, WPARAM, LPARAM);


//DOCUMENT.CPP
//File-related string lengths.
#define CCHPATHMAX          256
#define CCHFILENAMEMAX      15


//Window extra bytes and offsets
#define CBDOCUMENTWNDEXTRA  sizeof(LONG)
#define DOCWL_STRUCTURE     0


//Error codes from Load and Save functions
#define DOCERR_NONE                     0
#define DOCERR_NOFILE                   1
#define DOCERR_COULDNOTOPEN             2
#define DOCERR_READFAILURE              3
#define DOCERR_UNSUPPORTEDVERSION       4
#define DOCERR_WRITEFAILURE             5
#define DOCERR_CANCELLED                6
#define DOCERR_STDMAX                   6




/*
 * Structure containing resource ranges and other data for
 * initialization of a CDocument object through its Init member.
 */

typedef struct tagDOCUMENTINIT
    {
    UINT        idsMin;    //Stringtable start and end
    UINT        idsMax;
    HWND        hWndDoc;   //HWND of this document, created in client
    } DOCUMENTINIT, *PDOCUMENTINIT;



class CDocument : public CWindow
    {
    friend LRESULT APIENTRY DocumentWndProc(HWND, UINT, WPARAM
        , LPARAM);

    protected:
        PCFrame         m_pFR;                //Back pointer
        UINT            m_cf;                 //Clipboard format
        BOOL            m_fDirty;             //Is file dirty?
        BOOL            m_fNoDirty;           //Don't touch dirty flag
        BOOL            m_fNoSize;            //Prevent sizing
        BOOL            m_fFileKnown;         //File/Save allowed?
        TCHAR           m_szFile[CCHPATHMAX]; //Filename for Save

        PCStringTable   m_pST;                //Document strings

        /*
         * If someone above us wants information, they'll
         * give us this object.
         */
        PCDocumentAdviseSink m_pAdv;

    protected:
        virtual BOOL     FMessageHook(HWND, UINT, WPARAM, LPARAM
                             , LRESULT *);

    public:
        CDocument(HINSTANCE, PCFrame, PCDocumentAdviseSink);
        virtual ~CDocument(void);

        virtual BOOL     Init(PDOCUMENTINIT);

        virtual BOOL     FDirtySet(BOOL);
        virtual BOOL     FDirtyGet(void);
        virtual void     Clear(void);

        virtual UINT     Load(BOOL, LPTSTR);
        virtual UINT     Save(UINT, LPTSTR);
        virtual void     ErrorMessage(UINT);

        virtual BOOL     Clip(HWND, BOOL);
        virtual HGLOBAL  RenderFormat(UINT);
        virtual BOOL     FQueryPaste(void);
        virtual BOOL     Paste(HWND);
        virtual void     Undo(void);

        virtual BOOL     FQuerySave(void);
        virtual void     Rename(LPTSTR);
        virtual UINT     FilenameGet(LPTSTR, UINT);
        virtual PCFrame  FrameGet(void);
    };

typedef CDocument *PCDocument;


//Classname for documents, not localized
#define SZCLASSDOCUMENT     TEXT("document")


//Macro that isolates us from MDI or SDI Def procs
#ifdef MDI
#define DEFDOCUMENTPROC     DefMDIChildProc
#else
#define DEFDOCUMENTPROC     DefWindowProc
#endif


//Message to get PCDocument from hWnd
#define DOCM_PDOCUMENT      (WM_USER+0)


/**
 ** CDocumentAdviseSink through which a document notifies the
 ** frame or important events.
 **/

class CDocumentAdviseSink
    {
    protected:
        LPVOID      m_pv;               //Customizable structure

    public:
        CDocumentAdviseSink(LPVOID);

        virtual void OnDataChange(PCDocument);
        virtual void OnCloseRequest(PCDocument);
        virtual void OnSizeChange(PCDocument, LPRECT);
        virtual void OnCaptionChange(PCDocument);
        virtual void OnActivate(PCDocument);
    };


/**
 ** CHatchWin when used as a parent window creates a thin
 ** hatch border around the child window.
 **/

BOOL HatchWindowRegister(HINSTANCE);

//Classname
#define SZCLASSHATCHWIN                 TEXT("hatchwin")

//Window extra bytes and offsets
#define CBHATCHWNDEXTRA                 (sizeof(LONG))
#define HWWL_STRUCTURE                  0

//Notification codes for WM_COMMAND messages
#define HWN_BORDERDOUBLECLICKED         1

//Width of the border
#define HATCHWIN_BORDERWIDTHDEFAULT     4

class CHatchWin : public CWindow
    {
    friend LRESULT APIENTRY HatchWndProc(HWND, UINT, WPARAM, LPARAM);

    public:
        int         m_dBorder;
        int         m_dBorderOrg;
        UINT        m_uID;
        HWND        m_hWndKid;
        HWND        m_hWndAssociate;
        RECT        m_rcPos;
        RECT        m_rcClip;

    public:
        CHatchWin(HINSTANCE);
        ~CHatchWin(void);

        BOOL        Init(HWND, UINT, HWND);

        HWND        HwndAssociateSet(HWND);
        HWND        HwndAssociateGet(void);

        void        RectsSet(LPRECT, LPRECT);
        void        ChildSet(HWND);
        void        ShowHatch(BOOL);
    };

typedef CHatchWin *PCHatchWin;



#endif //_CLASSLIB_H_
