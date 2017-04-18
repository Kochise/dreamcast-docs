/*
 * FRAMER.H
 * Document Objects Framer
 * Definitions of classes, constants, etc.
 * Includes in-line implementation of CHourGlass, CWindow
 *
 * Copyright (c)1995-1997 Microsoft Corporation, All Rights Reserved
 */


#ifndef _FRAMER_H_
#define _FRAMER_H_

#define INC_OLE2
#include <docobj.h>


#include <tchar.h>
#ifdef UNICODE
#include <wchar.h>
#endif

extern "C"
    {
    #include <commdlg.h>
    }


#include "resource.h"


//DeleteInterfaceImp calls 'delete' and NULLs the pointer
#define DeleteInterfaceImp(p)\
            {\
            if (NULL!=p)\
                {\
                delete p;\
                p=NULL;\
                }\
            }


//ReleaseInterface calls 'Release' and NULLs the pointer
#define ReleaseInterface(p)\
            {\
            IUnknown *pt=(IUnknown *)p;\
            p=NULL;\
            if (NULL!=pt)\
                pt->Release();\
            }



class CHourglass;
class CFrame;
class CSite;


/**
 ** CFrame encapsulates a main application window
 **/

//FRAMEWIN.CPP:  Standard window procedure and AboutProc
LRESULT APIENTRY FrameWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT APIENTRY ClientWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL    APIENTRY AboutProc(HWND, UINT, WPARAM, LPARAM);

#define CBFRAMEWNDEXTRA     sizeof(LONG)
#define FRAMEWL_STRUCTURE   0

#define CBCLIENTWNDEXTRA    sizeof(LONG)
#define CLIENTWL_STRUCTURE  0

#define SZCLASSFRAME        TEXT("Frame")
#define SZCLASSCLIENT       TEXT("Client")


//FRAME.CPP:  Frame object that creates a main window

class CFrame : public IOleInPlaceFrame, public IOleCommandTarget
    {
    //Let our window procedure look in our private variables.
    friend LRESULT APIENTRY FrameWndProc(HWND, UINT, WPARAM, LPARAM);
	friend LRESULT APIENTRY ClientWndProc(HWND, UINT, WPARAM, LPARAM);

    protected:
        HINSTANCE       m_hInst;            //Task instance
        HWND            m_hWnd;             //Window handle of the window
        ULONG           m_cRef; 

        HINSTANCE       m_hInstPrev;        //WinMain parameters
        LPTSTR          m_pszCmdLine;
        int             m_nCmdShow;        

        HMENU          *m_phMenu;           //Popup menu handles
        HACCEL          m_hAccel;           //Accelerators
        HWND            m_hWndClient;       //Client area window

        BOOL            m_fInitialized;     //OleInitialize called?
        IStorage       *m_pIStorage;        //Temp file for all needs
        DWORD           m_dwIDCounter;      //For site IDs

        //For menu merging
        HMENU           m_hMenuOrg;         //Original menu
        HMENU           m_hMenuTop;			//Currently shown menu
		HMENU			m_hMenuHelp;		//Special Help menu
		BOOL			m_fUsingOurHelp;	//Help menu in use?
        BOOL			m_fInObjectHelp;	//Object's menu found?
        BOOL            m_fOurMenuShowing;  //Our menu up?		

        //Other object needs
        BOOL            m_fHaveObject;      //For menu enabling
		HWND			m_hWndObj;			//UI Active object

        class CSite    *m_pSite;            //Site holding object        
        BORDERWIDTHS    m_bwIP;             //In-place tool allocations
        BOOL            m_fInContextHelp;   //In context help mode?

        IOleInPlaceActiveObject *m_pIOleIPActiveObject;

    protected:
        BOOL    RegisterAllClasses(void);        
        LRESULT OnCommand(HWND, WPARAM, LPARAM);		
        BOOL    OpenDialog(LPTSTR, UINT);
        BOOL    CreateObject(LPTSTR);
		void	ResizeClientWindow(UINT, UINT, UINT, UINT);

    public:
        CFrame(HINSTANCE, HINSTANCE, LPSTR, int);
        ~CFrame(void);

        inline HINSTANCE Instance(void)
        	{ return m_hInst; }

        inline HWND      Window(void)
        	{ return m_hWnd; }        

        inline HACCEL    Accelerators(void)
        	{ return m_hAccel; }        
		
        BOOL    Init(UINT, int, int, int, int);
        WPARAM  MessageLoop(void);
		void    Close();        

        //Shared IUnknown implementation
        STDMETHODIMP         QueryInterface(REFIID, void **);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

		//IOleInPlaceFrame implementation
        STDMETHODIMP         GetWindow(HWND *);
        STDMETHODIMP         ContextSensitiveHelp(BOOL);
        STDMETHODIMP         GetBorder(LPRECT);
        STDMETHODIMP         RequestBorderSpace(LPCBORDERWIDTHS);
        STDMETHODIMP         SetBorderSpace(LPCBORDERWIDTHS);
        STDMETHODIMP         SetActiveObject(LPOLEINPLACEACTIVEOBJECT
                                 , LPCOLESTR);
        STDMETHODIMP         InsertMenus(HMENU, LPOLEMENUGROUPWIDTHS);
        STDMETHODIMP         SetMenu(HMENU, HOLEMENU, HWND);
        STDMETHODIMP         RemoveMenus(HMENU);
        STDMETHODIMP         SetStatusText(LPCOLESTR);
        STDMETHODIMP         EnableModeless(BOOL);
        STDMETHODIMP         TranslateAccelerator(LPMSG, WORD);

		//IOleCommandTarget
        STDMETHODIMP QueryStatus(const GUID *pguidCmdGroup, ULONG cCmds
            , OLECMD prgCmds[], OLECMDTEXT *pCmdText);
        
        STDMETHODIMP Exec(const GUID *pguidCmdGroup, DWORD nCmdID
            , DWORD nCmdexecopt, VARIANTARG *pvaIn, VARIANTARG *pvaOut);            
    };


typedef CFrame *PCFrame;



/**
 ** CHourglass:  Manages the hourglass and mouse capture
 **/

class CHourglass
    {
    protected:
        HWND            m_hWndCapture;      //Window with capture
        HCURSOR         m_hCur;             //Cursor held.

    public:
        CHourglass(void)
            {
            m_hCur=SetCursor(LoadCursor(NULL, IDC_WAIT));
            m_hWndCapture=NULL;
            return;
            }

        CHourglass(HWND hWnd)
            {
            m_hCur=SetCursor(LoadCursor(NULL, IDC_WAIT));

            if (NULL!=hWnd)
                {
                m_hWndCapture=hWnd;
                SetCapture(hWnd);
                }

            return;
            }

        ~CHourglass(void)
            {
            if (NULL!=m_hWndCapture)
                ReleaseCapture();

            SetCursor(m_hCur);
            return;
            }
    };

typedef CHourglass *PCHourglass;


#include "site.h"

#endif //_FRAMER_H_
