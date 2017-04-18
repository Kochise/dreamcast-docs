/*
 * PATRON.H
 * Patron Chapter 20
 *
 * Single include file that pulls in everything needed for other
 * source files in the application.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _PATRON_H_
#define _PATRON_H_

#define INC_CLASSLIB
#define INC_OLEUI
//CHAPTER20MOD
#define CHAPTER20
//End CHAPTER20MOD
#include <inole.h>
#include "resource.h"

//Get editor window information
#include "pages.h"


/*
 * UINT value such that adding one produces zero.  Portable to Win32.
 * This is used to represent a non-existent zero-based UINT value
 */
#define NOVALUE                     ((UINT)-1)


//PATRON.CPP:  Frame object that creates a main window

class CPatronFrame : public CFrame
    {
    private:
        BOOL            m_fInitialized;     //OleInitialize worked
        LPCLASSFACTORY  m_pIClassDataTran;  //For locking.

    protected:
        //Overridable for creating a CPatronClient
        virtual PCClient    CreateCClient(void);

        virtual BOOL        FMessageHook(HWND, UINT, WPARAM, LPARAM
                                , LRESULT *);
        virtual BOOL        RegisterAllClasses(void);
        virtual UINT        CreateToolbar(void);
        virtual LRESULT     OnCommand(HWND, WPARAM, LPARAM);

    public:
        CPatronFrame(HINSTANCE, HINSTANCE, LPSTR, int);
        virtual ~CPatronFrame(void);

        //Overrides
        virtual BOOL        Init(PFRAMEINIT);

        virtual void        UpdateMenus(HMENU, UINT);
        virtual void        UpdateToolbar(void);

    };


typedef CPatronFrame *PCPatronFrame;





//CLIENT.CPP

/*
 * The only reason we have a derived class here is to override
 * CreateCDocument so we can create our own type as well as
 * overriding NewDocument to perform one other piece of work once
 * the document's been created.
 */

class CPatronClient : public CClient
    {
    protected:
        //Overridable for creating a new CDocument
        virtual PCDocument CreateCDocument(void);

    public:
        CPatronClient(HINSTANCE, PCFrame);
        virtual ~CPatronClient(void);
    };


typedef CPatronClient *PCPatronClient;




//DOCUMENT.CPP

//Constant ID for the pages window that lives in a document window
#define ID_PAGES            723


class CPatronDoc : public CDocument
    {
    //These need access to FQueryPasteFromData, PasteFromData
    friend class CDropTarget;
    friend class CDropSource;

    protected:
        LONG            m_lVer;         //Loaded data version
        PCPages         m_pPG;          //Pages window in us
        LPSTORAGE       m_pIStorage;    //Root storage for document
        BOOL            m_fPrintSetup;

        class CDropTarget *m_pDropTarget;   //Registered target

        UINT            m_cfEmbeddedObject; //Clipboard formats
        UINT            m_cfObjectDescriptor;
        //CHAPTER20MOD
        UINT            m_cfLinkSource;
        UINT            m_cfLinkSrcDescriptor;
        BOOL            m_fShowTypes;       //Show Objects active?
        //End CHAPTER20MOD

    protected:
        virtual BOOL    FMessageHook(HWND, UINT, WPARAM, LPARAM
            , LRESULT *);

        BOOL            FQueryPasteFromData(LPDATAOBJECT
                            , LPFORMATETC, PTENANTTYPE);
        //CHAPTER20MOD
        BOOL            FQueryPasteLinkFromData(LPDATAOBJECT
                            , LPFORMATETC, PTENANTTYPE);
        //End CHAPTER20MOD
        BOOL            PasteFromData(LPDATAOBJECT, LPFORMATETC
                            , TENANTTYPE, PPATRONOBJECT, DWORD
                            , BOOL);

    public:
        CPatronDoc(HINSTANCE, PCFrame, PCDocumentAdviseSink);
        virtual ~CPatronDoc(void);

        virtual BOOL    Init(PDOCUMENTINIT);
        virtual void    Clear(void);

        virtual BOOL    FDirtyGet(void);
        virtual void    Delete(void);
        virtual BOOL    FQueryPrinterSetup(void);
        virtual BOOL    FQueryObjectSelected(HMENU);

        virtual UINT    Load(BOOL, LPTSTR);
        virtual UINT    Save(UINT, LPTSTR);

        virtual BOOL    Print(HWND);
        virtual UINT    PrinterSetup(HWND, BOOL);

        virtual BOOL    Clip(HWND, BOOL);
        virtual BOOL    FQueryPaste(void);
        virtual BOOL    Paste(HWND);
        virtual BOOL    PasteSpecial(HWND);

        //CHAPTER20MOD
        virtual BOOL    FQueryEnableEditLinks(void);
        virtual BOOL    EditLinks(HWND);
        virtual BOOL    ShowOrQueryObjectTypes(BOOL, BOOL);
        //End CHAPTER20MOD

        virtual UINT    NewPage(void);
        virtual UINT    DeletePage(void);
        virtual UINT    NextPage(void);
        virtual UINT    PreviousPage(void);
        virtual UINT    FirstPage(void);
        virtual UINT    LastPage(void);

        virtual void    Rename(LPTSTR);
        virtual BOOL    InsertObject(HWND);
        virtual void    ActivateObject(LONG);
        virtual BOOL    ConvertObject(HWND);
    };

typedef CPatronDoc *PCPatronDoc;

//Hook for Print Dialog to hide Setup... button
UINT CALLBACK PrintDlgHook(HWND, UINT, WPARAM, LPARAM);


//Drag-drop objects we need in the document

class CDropTarget : public IDropTarget
    {
    protected:
        ULONG               m_cRef;
        PCPatronDoc         m_pDoc;

        LPDATAOBJECT        m_pIDataObject;  //From DragEnter
        BOOL                m_fPendingRepaint;
        POINTL              m_ptPick;        //Pick-up offsets
        POINTL              m_ptLast;        //Last drag point
        SIZEL               m_szl;           //Object size
        BOOL                m_fFeedback;     //Draw feedback?
        FORMATETC           m_fe;            //Real dropping format

    public:
        CDropTarget(PCPatronDoc);
        ~CDropTarget(void);

        //IDropTarget interface members
        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP DragEnter(LPDATAOBJECT, DWORD, POINTL,LPDWORD);
        STDMETHODIMP DragOver(DWORD, POINTL, LPDWORD);
        STDMETHODIMP DragLeave(void);
        STDMETHODIMP Drop(LPDATAOBJECT, DWORD, POINTL, LPDWORD);
    };


typedef CDropTarget *PCDropTarget;


class CDropSource : public IDropSource
    {
    protected:
        ULONG               m_cRef;

    public:
        CDropSource(void);
        ~CDropSource(void);

        //IDropSource interface members
        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP QueryContinueDrag(BOOL, DWORD);
        STDMETHODIMP GiveFeedback(DWORD);
    };

typedef CDropSource *PCDropSource;


#endif //_PATRON_H_
