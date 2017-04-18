/*
 * COCOSMO.H
 * Component Cosmo Chapter 12
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

#define INC_CLASSLIB
#define INC_CONTROLS
#define INC_OLE2
//CHAPTER12MOD
#define CHAPTER12
//CHAPTER12MOD
#include <inole.h>
#include <ipoly10.h>
#include "resource.h"

//COCOSMO.CPP:  Frame object that creates a main window

class CCosmoFrame : public CFrame
    {
    private:
        HBITMAP         m_hBmpLines[5];     //Menu item bitmaps
        UINT            m_uIDCurLine;       //Current line selection
        BOOL            m_fInitialized;     //OleInitialize work?

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

class CPolylineAdviseSink : public IPolylineAdviseSink10
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
        STDMETHODIMP_(void) OnColorChange(void);
        STDMETHODIMP_(void) OnLineStyleChange(void);
    };

typedef CPolylineAdviseSink *PCPolylineAdviseSink;


/*
 * The generic advisory interface.  This object controls it's own
 * lifetime and the document becomes a user of the object with
 * the last reference count.
 */

class CImpIAdviseSink : public IAdviseSink
    {
    protected:
        ULONG               m_cRef;
        LPVOID              m_pObj;
        LPUNKNOWN           m_pUnkOuter;

    public:
        CImpIAdviseSink(LPVOID, LPUNKNOWN);
        ~CImpIAdviseSink(void);

        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP_(void)  OnDataChange(LPFORMATETC, LPSTGMEDIUM);
        STDMETHODIMP_(void)  OnViewChange(DWORD, LONG);
        STDMETHODIMP_(void)  OnRename(LPMONIKER);
        STDMETHODIMP_(void)  OnSave(void);
        STDMETHODIMP_(void)  OnClose(void);
    };

typedef CImpIAdviseSink *PCImpIAdviseSink;




//Constant ID for the window polyline that lives in a document
#define ID_POLYLINE         10

//Stream name to open with IPersistStream[Init]
#define SZSTREAM                    OLETEXT("CONTENTS")


class CCosmoDoc : public CDocument, public IUnknown
    {
    friend class CPolylineAdviseSink;
    friend class CImpIAdviseSink;

    protected:
        UINT                    m_uPrevSize;    //Last WM_SIZE wParam

        IPolyline10            *m_pPL;          //Polyline object
        IPolylineAdviseSink10  *m_pPLAdv;

        IConnectionPoint       *m_pIConnectPt;
        DWORD                   m_dwCookie;     //Connection key
        IStorage               *m_pIStorage;    //Doc storage
        PERSISTPOINTER          m_pp;

        PCImpIAdviseSink        m_pImpIAdviseSink;

        DWORD                   m_dwConn;       //Advisory connection
        ULONG                   m_cRef;         //Document ref count

        //CHAPTER12MOD
        LPDATAOBJECT            m_pIDataClip;   //Clipboard object
        //End CHAPTER12MOD

    protected:
        virtual BOOL     FMessageHook(HWND, UINT, WPARAM, LPARAM
            , LRESULT *);

    public:
        CCosmoDoc(HINSTANCE, PCFrame, PCDocumentAdviseSink);
        virtual ~CCosmoDoc(void);

        //Need a controlling unknown for our interfaces
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        virtual BOOL     Init(PDOCUMENTINIT);
        virtual void     Clear(void);

        virtual UINT     Load(BOOL, LPTSTR);
        virtual UINT     Save(UINT, LPTSTR);

        virtual void     Undo(void);
        virtual BOOL     Clip(HWND, BOOL);

        //CHAPTER12MOD
        //RenderFormat no longer necessary.
        //End CHAPTER12MOD

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
