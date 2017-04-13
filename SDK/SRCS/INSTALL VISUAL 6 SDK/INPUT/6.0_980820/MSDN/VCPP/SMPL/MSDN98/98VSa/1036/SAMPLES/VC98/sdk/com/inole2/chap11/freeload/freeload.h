/*
 * FREELOAD.H
 * Freeloader Chapter 11
 *
 * Class overrides for the FreeLoader application
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _FREELOAD_H_
#define _FREELOAD_H_

#define INC_OLE2
#define INC_CLASSLIB
#define CHAPTER11
#include <inole.h>
#include "resource.h"


//FREELOAD.CPP:  Frame object that creates a main window

class CFreeloaderFrame : public CFrame
    {
    private:
        BOOL             m_fInitialized;    //OleInitialize work?

    protected:
        //Overridable for creating a CClient for this frame
        virtual PCClient CreateCClient(void);
        virtual LRESULT  OnCommand(HWND, WPARAM, LPARAM);

    public:
        CFreeloaderFrame(HINSTANCE, HINSTANCE, LPSTR, int);
        virtual ~CFreeloaderFrame(void);

        virtual BOOL     FInit(PFRAMEINIT);
        virtual void     UpdateMenus(HMENU, UINT);
    };


typedef CFreeloaderFrame *PCFreeloaderFrame;





//CLIENT.CPP

//Override to create CFreeloaderDoc
class CFreeloaderClient : public CClient
    {
    protected:
        //Overridable for creating a new CDocument
        virtual PCDocument  CreateCDocument(void);

    public:
        CFreeloaderClient(HINSTANCE, PCFrame);
        virtual ~CFreeloaderClient(void);
    };


typedef CFreeloaderClient *PCFreeloaderClient;




//DOCUMENT.CPP

//Paint continuation callback for IViewObject::Draw
BOOL CALLBACK ContinuePaint(DWORD);

class CFreeloaderDoc : public CDocument
    {
    protected:
        LPSTORAGE       m_pIStorage;    //Root storage for this doc
        LPUNKNOWN       m_pIUnknown;    //Static visual object.
        DWORD           m_dwConn;       //From IOleCache::Cache
        CLSID           m_clsID;        //Data type

    protected:
        //Centralized cleanup
        void ReleaseObject(void);

        //To catch WM_PAINT
        virtual BOOL    FMessageHook(HWND, UINT, WPARAM, LPARAM
            , LRESULT *);

    public:
        CFreeloaderDoc(HINSTANCE, PCFrame, PCDocumentAdviseSink);
        virtual ~CFreeloaderDoc(void);

        virtual BOOL     FInit(PDOCUMENTINIT);

        virtual UINT     Load(BOOL, LPTSTR);
        virtual UINT     Save(UINT, LPTSTR);

        virtual BOOL     Clip(HWND, BOOL);
        virtual HGLOBAL  RenderFormat(UINT);
        virtual BOOL     FQueryPaste(void);
        virtual BOOL     Paste(HWND);

        virtual BOOL     SizeToGraphic(BOOL);
    };

typedef CFreeloaderDoc *PCFreeloaderDoc;


//For mapping HIMETRIC to pixels.
#define HIMETRIC_PER_INCH       2540

#endif //_FREELOAD_H_
