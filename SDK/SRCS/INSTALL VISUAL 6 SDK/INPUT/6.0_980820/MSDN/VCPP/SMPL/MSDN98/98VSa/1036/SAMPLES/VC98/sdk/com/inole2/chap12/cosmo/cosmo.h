/*
 * COSMO.H
 * Cosmo Chapter 12
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


#ifndef _COSMO_H_
#define _COSMO_H_

#define INC_CLASSLIB
//CHAPTER12MOD
#define CHAPTER12
//End CHAPTER12MOD
#include <inole.h>
#include "resource.h"

//Get the editor window information.
#include "polyline.h"



//COSMO.CPP:  Frame object that creates a main window

class CCosmoFrame : public CFrame
    {
    private:
        HBITMAP         m_hBmpLines[5];     //Menu item bitmaps
        UINT            m_uIDCurLine;       //Current line selection
        BOOL            m_fInitialized;     //Did OleInitalize work?

        //CHAPTER12MOD
        //For locking DATATRAN.DLL class factory
        LPCLASSFACTORY  m_pIClassDataTran;
        //End CHAPTER12MOD

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

//Constant ID for the window polyline that lives in a document
#define ID_POLYLINE         10


class CCosmoDoc : public CDocument
    {
    friend class CPolylineAdviseSink;

    protected:
        UINT                    m_uPrevSize;    //Last WM_SIZE wParam
        LONG                    m_lVer;         //Loaded Polyline ver

        PCPolyline              m_pPL;          //Polyline window here
        PCPolylineAdviseSink    m_pPLAdv;       //Advises from Polyline

    protected:
        virtual BOOL     FMessageHook(HWND, UINT, WPARAM, LPARAM
            , LRESULT *);

        //CHAPTER12MOD
        virtual BOOL     FQueryPasteFromData(LPDATAOBJECT);
        virtual BOOL     PasteFromData(LPDATAOBJECT);
        //End CHAPTER12MOD

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



#endif //_COSMO_H_
