/*
 * COCOSMO.H
 * Component Cosmo Chapter 8
 *
 * Single include file that pulls in everything needed for other
 * source files in the Cosmo application.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _COCOSMO_H_
#define _COCOSMO_H_

//CHAPTER8MOD
#define INC_CLASSLIB
#define INC_CONTROLS
#define INC_OLE2
#define CHAPTER8
#include <inole.h>
#include <ipoly8.h>
#include "resource.h"
//End CHAPTER8MOD

//COCOSMO.CPP:  Frame object that creates a main window

class CCosmoFrame : public CFrame
    {
    private:
        HBITMAP         m_hBmpLines[5];     //Menu item bitmaps
        UINT            m_uIDCurLine;       //Current line selection
        BOOL            m_fInitialized;     //CoInitialize work?

    protected:
        //Overridable for creating a CClient for this frame
        virtual PCClient  CreateCClient(void);

        virtual BOOL      RegisterAllClasses(void);
        virtual BOOL      PreShowInit(void);
        virtual UINT      CreateToolbar(void);

        virtual LRESULT   OnCommand(HWND, WPARAM, LPARAM);
        virtual void      OnDocumentDataChange(PCDocument);
        virtual void      OnDocumentActivate(PCDocument);

        //New for this class
        virtual void      CreateLineMenu(void);

    public:
        CCosmoFrame(HINSTANCE, HINSTANCE, LPSTR, int);
        virtual ~CCosmoFrame(void);

        //Overrides
        virtual BOOL      Init(PFRAMEINIT);
        virtual void      UpdateMenus(HMENU, UINT);
        virtual void      UpdateToolbar(void);

        //New for this class
        virtual void      CheckLineSelection(UINT);
    };


typedef CCosmoFrame *PCCosmoFrame;





//CLIENT.CPP

/*
 * The only reason we have a derived class here is to override
 * CreateCDocument so we can create our own type as well as
 * overriding NewDocument to perform one other piece of work once
 * the document's been created.
 */

class CCosmoClient : public CClient
    {
    protected:
        //Overridable for creating a new CDocument
        virtual PCDocument CreateCDocument(void);

    public:
        CCosmoClient(HINSTANCE, PCFrame);
        virtual ~CCosmoClient(void);

        virtual PCDocument NewDocument(BOOL);
    };


typedef CCosmoClient *PCCosmoClient;




//DOCUMENT.CPP

class CCosmoDoc;
typedef CCosmoDoc *PCCosmoDoc;

class CPolylineAdviseSink : public IPolylineAdviseSink8
    {
    private:
        PCCosmoDoc  m_pDoc;         //Backpointer to document
        ULONG       m_cRef;

    public:
        CPolylineAdviseSink(PCCosmoDoc);
        ~CPolylineAdviseSink(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //Advise members.
        STDMETHODIMP_(void) OnPointChange(void);
        STDMETHODIMP_(void) OnSizeChange(void);
        STDMETHODIMP_(void) OnDataChange(void);
        STDMETHODIMP_(void) OnColorChange(void);
        STDMETHODIMP_(void) OnLineStyleChange(void);
    };

typedef CPolylineAdviseSink *PCPolylineAdviseSink;



//Constant ID for the window polyline that lives in a document
#define ID_POLYLINE         10

//CHAPTER8MOD
//Stream name to open with IPersistStream[Init]
#define SZSTREAM                    OLETEXT("CONTENTS")
//End CHAPTER8MOD


class CCosmoDoc : public CDocument
    {
    friend class CPolylineAdviseSink;

    protected:
        UINT                    m_uPrevSize;    //Last WM_SIZE wParam

        //CHAPTER8MOD
        IPolyline8             *m_pPL;          //Polyline object
        IPolylineAdviseSink8   *m_pPLAdv;
        //End CHAPTER8MOD

        IConnectionPoint       *m_pIConnectPt;
        DWORD                   m_dwCookie;     //Connection key

        //CHAPTER8MOD
        IStorage               *m_pIStorage;    //Doc storage
        PERSISTPOINTER          m_pp;
        //End CHAPTER8MOD

    protected:
        virtual BOOL     FMessageHook(HWND, UINT, WPARAM, LPARAM
            , LRESULT *);

    public:
        CCosmoDoc(HINSTANCE, PCFrame, PCDocumentAdviseSink);
        virtual ~CCosmoDoc(void);

        virtual BOOL     Init(PDOCUMENTINIT);

        virtual void     Clear(void);

        virtual UINT     Load(BOOL, LPTSTR);
        virtual UINT     Save(UINT, LPTSTR);

        virtual void     Undo(void);
        virtual BOOL     Clip(HWND, BOOL);
        virtual HGLOBAL  RenderFormat(UINT);
        virtual BOOL     FQueryPaste(void);
        virtual BOOL     Paste(HWND);

        virtual COLORREF ColorSet(UINT, COLORREF);
        virtual COLORREF ColorGet(UINT);

        virtual UINT     LineStyleSet(UINT);
        virtual UINT     LineStyleGet(void);
    };

typedef CCosmoDoc *PCCosmoDoc;


//These color indices wrap the polyline definitions
#define DOCCOLOR_BACKGROUND             POLYLINECOLOR_BACKGROUND
#define DOCCOLOR_LINE                   POLYLINECOLOR_LINE



#endif //_COCOSMO_H_
