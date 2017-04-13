/*
 * PATRON.H
 * Patron Chapter 12
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
#define INC_OLE2
//CHAPTER12MOD
#define INC_OLEUI
#define CHAPTER12
//End CHAPTER12MOD
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

        //CHAPTER12MOD
        //For locking DATATRAN.DLL class factory
        LPCLASSFACTORY  m_pIClassDataTran;
        //End CHAPTER12MOD

    protected:
        //Overridable for creating a CPatronClient
        virtual PCClient    CreateCClient(void);

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
    protected:
        LONG            m_lVer;         //Loaded data version
        PCPages         m_pPG;          //Pages window in us

        LPSTORAGE       m_pIStorage;    //Root storage for document

        //CHAPTER12MOD
        BOOL            m_fPrintSetup;
        //End CHAPTER12MOD

    protected:
        virtual BOOL    FMessageHook(HWND, UINT, WPARAM, LPARAM
            , LRESULT *);

        //CHAPTER12MOD
        BOOL            FQueryPasteFromData(LPDATAOBJECT
                            , LPFORMATETC, PTENANTTYPE);
        BOOL            PasteFromData(LPDATAOBJECT, LPFORMATETC
                            , TENANTTYPE, PPATRONOBJECT, DWORD);
        //End CHAPTER12MOD

    public:
        CPatronDoc(HINSTANCE, PCFrame, PCDocumentAdviseSink);
        virtual ~CPatronDoc(void);

        virtual BOOL    Init(PDOCUMENTINIT);
        virtual void    Clear(void);

        //CHAPTER12MOD
        virtual BOOL    FDirtyGet(void);
        virtual void    Delete(void);
        virtual BOOL    FQueryPrinterSetup(void);
        virtual BOOL    FQueryObjectSelected(HMENU);
        //End CHAPTER12MOD

        virtual UINT    Load(BOOL, LPTSTR);
        virtual UINT    Save(UINT, LPTSTR);

        virtual BOOL    Print(HWND);
        virtual UINT    PrinterSetup(HWND, BOOL);

        //CHAPTER12MOD
        virtual BOOL    Clip(HWND, BOOL);
        virtual BOOL    FQueryPaste(void);
        virtual BOOL    Paste(HWND);
        virtual BOOL    PasteSpecial(HWND);
        //End CHAPTER12MOD

        virtual UINT    NewPage(void);
        virtual UINT    DeletePage(void);
        virtual UINT    NextPage(void);
        virtual UINT    PreviousPage(void);
        virtual UINT    FirstPage(void);
        virtual UINT    LastPage(void);
    };

typedef CPatronDoc *PCPatronDoc;

//Hook for Print Dialog to hide Setup... button
UINT CALLBACK PrintDlgHook(HWND, UINT, WPARAM, LPARAM);


#endif //_PATRON_H_
