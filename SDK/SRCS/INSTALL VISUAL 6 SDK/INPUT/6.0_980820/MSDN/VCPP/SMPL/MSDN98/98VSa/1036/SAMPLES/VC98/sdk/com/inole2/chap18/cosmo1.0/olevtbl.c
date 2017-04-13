/*
 * OLEVTBL.C
 *
 * Creates or frees the procedure instances for the server, document,
 * and object VTBLs.  There are two functions for each table:  one
 * to initialize the table, the other to free the instances in the table.
 *
 * Copyright(c) Microsoft Corp. 1992-1994 All Rights Reserved
 * Win32 version, January 1994
 */


#ifdef MAKEOLESERVER


#include <windows.h>
#include <ole.h>
#include "cosmo.h"
#include "oleglobl.h"

#ifdef MSC
/*
 * This disables Microsoft VC++ 1.x warnings we get from assigning
 * functions with our app-specific prototypes to the fixed prototypes
 * in the VTBL structures.  The functionality of this application was
 * verified before adding this pragma.
 */
#pragma warning(disable:4028)
#ifndef WIN32
#pragma warning(disable:4113)
#endif
#endif


/*
 * FOLEVtblInitServer
 *
 * Purpose:
 *  Creates procedure instances for all the OLE methods required
 *  by the server library for standard server methods.
 *
 * Parameters:
 *  hInst           HINSTANCE of the application instance.
 *  pvt             LPOLESERVERVTBL to the VTBL to initialize.
 *
 * Return Value:
 *  None
 *
 * Customization:
 *  None required.
 */

BOOL WINAPI FOLEVtblInitServer(HINSTANCE hInst, LPOLESERVERVTBL pvt)
    {
    BOOL        fRet=TRUE;

   #ifdef WIN32
    pvt->Create            =ServerCreate;
    pvt->CreateFromTemplate=ServerCreateFromTemplate;
    pvt->Edit              =ServerEdit;
    pvt->Execute           =ServerExecute;
    pvt->Exit              =ServerExit;
    pvt->Open              =ServerOpen;
    pvt->Release           =ServerRelease;
   #else
    pvt->Create            =(LPVOID)MakeProcInstance(ServerCreate,             hInst);
    pvt->CreateFromTemplate=(LPVOID)MakeProcInstance(ServerCreateFromTemplate, hInst);
    pvt->Edit              =(LPVOID)MakeProcInstance(ServerEdit,               hInst);
    pvt->Execute           =(LPVOID)MakeProcInstance(ServerExecute,            hInst);
    pvt->Exit              =(LPVOID)MakeProcInstance(ServerExit,               hInst);
    pvt->Open              =(LPVOID)MakeProcInstance(ServerOpen,               hInst);
    pvt->Release           =(LPVOID)MakeProcInstance(ServerRelease,            hInst);

    fRet =(NULL!=pvt->Create);
    fRet&=(NULL!=pvt->CreateFromTemplate);
    fRet&=(NULL!=pvt->Edit);
    fRet&=(NULL!=pvt->Execute);
    fRet&=(NULL!=pvt->Exit);
    fRet&=(NULL!=pvt->Open);
    fRet&=(NULL!=pvt->Release);
   #endif

    return fRet;
    }


/*
 * OLEVtblFreeServer
 *
 * Purpose:
 *  Frees all procedure instances in the server VTBL.
 *
 * Parameters:
 *  pvt             LPOLESERVERVTBL to the VTBL to free.
 *
 * Return Value:
 *  none
 *
 * Customization:
 *  None required.
 */

void WINAPI OLEVtblFreeServer(LPOLESERVERVTBL pvt)
    {
   #ifndef WIN32
    FreeProcInstance(pvt->Create);
    FreeProcInstance(pvt->CreateFromTemplate);
    FreeProcInstance(pvt->Edit);
    FreeProcInstance(pvt->Exit);
    FreeProcInstance(pvt->Open);
    FreeProcInstance(pvt->Release);
   #endif

    return;
    }





/*
 * FOLEVtblInitDocument
 *
 * Purpose:
 *  Creates procedure instances for all the OLE methods required
 *  for document methods.
 *
 * Parameters:
 *  hInst           HINSTANCE of the application instance.
 *  pvt             LPOLESERVERDOCVTBL to the VTBL to initialize.
 * 
 * Return Value:
 *  None
 *
 * Customization:
 *  None required.
 */

BOOL WINAPI FOLEVtblInitDocument(HINSTANCE hInst, LPOLESERVERDOCVTBL pvt)
    {
    BOOL        fRet=TRUE;

   #ifdef WIN32
    pvt->Close           =DocClose;
    pvt->GetObject       =DocGetObject;
    pvt->Execute         =DocExecute;
    pvt->Release         =DocRelease;
    pvt->Save            =DocSave;
    pvt->SetColorScheme  =DocSetColorScheme;
    pvt->SetDocDimensions=DocSetDocDimensions;
    pvt->SetHostNames    =DocSetHostNames;
   #else
    pvt->Close           =(LPVOID)MakeProcInstance(DocClose,            hInst);
    pvt->GetObject       =(LPVOID)MakeProcInstance(DocGetObject,        hInst);
    pvt->Execute         =(LPVOID)MakeProcInstance(DocExecute,          hInst);
    pvt->Release         =(LPVOID)MakeProcInstance(DocRelease,          hInst);
    pvt->Save            =(LPVOID)MakeProcInstance(DocSave,             hInst);
    pvt->SetColorScheme  =(LPVOID)MakeProcInstance(DocSetColorScheme,   hInst);
    pvt->SetDocDimensions=(LPVOID)MakeProcInstance(DocSetDocDimensions, hInst);
    pvt->SetHostNames    =(LPVOID)MakeProcInstance(DocSetHostNames,     hInst);

    fRet =(NULL!=pvt->Close);
    fRet&=(NULL!=pvt->GetObject);
    fRet&=(NULL!=pvt->Execute);
    fRet&=(NULL!=pvt->Release);
    fRet&=(NULL!=pvt->Save);
    fRet&=(NULL!=pvt->SetColorScheme);
    fRet&=(NULL!=pvt->SetDocDimensions);
    fRet&=(NULL!=pvt->SetHostNames);
   #endif

    return fRet;
    }




/*
 * OLEVtblFreeDocument
 *
 * Purpose:
 *  Frees all procedure instances in the document VTBL.
 *
 * Parameters:
 *  pvt             LPOLESERVERDOCVTBL to the VTBL to free.
 *
 * Return Value:
 *  none
 *
 * Customization:
 *  None required.
 */

void WINAPI OLEVtblFreeDocument(LPOLESERVERDOCVTBL pvt)
    {
   #ifndef WIN32
    FreeProcInstance(pvt->Close);
    FreeProcInstance(pvt->GetObject);
    FreeProcInstance(pvt->Release);
    FreeProcInstance(pvt->Save);
    FreeProcInstance(pvt->SetColorScheme);
    FreeProcInstance(pvt->SetDocDimensions);
    FreeProcInstance(pvt->SetHostNames);
   #endif

    return;
    }





/*
 * FOLEVtblInitObject
 *
 * Purpose:
 *  Creates procedure instances for all the OLE methods required
 *  for object methods.
 *
 * Parameters:
 *  hInst           HINSTANCE of the application instance.
 *  pvt             LPOLEOBJECTVTBL to free.
 * 
 * Return Value:
 *  None
 *
 * Customization:
 *  Your application might not use global variables for srvrvtbl,
 *  docvtbl, and objvtbl.
 */

BOOL WINAPI FOLEVtblInitObject(HINSTANCE hInst, LPOLEOBJECTVTBL pvt)
    {
    BOOL        fRet=TRUE;

    /*
     * Local variables are used here just to make this one assignment
     * more readable since it requires some typecasting to compile clean
     * at warning level 3.
     */
   #ifdef WIN32
    pvt->QueryProtocol  =ObjQueryProtocol;
    pvt->DoVerb         =ObjDoVerb;
    pvt->EnumFormats    =ObjEnumFormats;
    pvt->GetData        =ObjGetData;
    pvt->Release        =ObjRelease;
    pvt->SetBounds      =ObjSetBounds;
    pvt->SetColorScheme =ObjSetColorScheme;
    pvt->SetData        =ObjSetData;
    pvt->SetTargetDevice=ObjSetTargetDevice;
    pvt->Show           =ObjShow;
   #else
    pvt->QueryProtocol  =(LPVOID)MakeProcInstance((FARPROC)ObjQueryProtocol, hInst);;
    pvt->DoVerb         =(LPVOID)MakeProcInstance(ObjDoVerb, hInst);
    pvt->EnumFormats    =(LPVOID)MakeProcInstance(ObjEnumFormats, hInst);
    pvt->GetData        =(LPVOID)MakeProcInstance(ObjGetData, hInst);
    pvt->Release        =(LPVOID)MakeProcInstance(ObjRelease, hInst);
    pvt->SetBounds      =(LPVOID)MakeProcInstance(ObjSetBounds, hInst);
    pvt->SetColorScheme =(LPVOID)MakeProcInstance(ObjSetColorScheme, hInst);
    pvt->SetData        =(LPVOID)MakeProcInstance(ObjSetData, hInst);
    pvt->SetTargetDevice=(LPVOID)MakeProcInstance(ObjSetTargetDevice, hInst);
    pvt->Show           =(LPVOID)MakeProcInstance(ObjShow, hInst);

    fRet =(NULL!=pvt->QueryProtocol);
    fRet&=(NULL!=pvt->DoVerb);
    fRet&=(NULL!=pvt->EnumFormats);
    fRet&=(NULL!=pvt->GetData);
    fRet&=(NULL!=pvt->Release);
    fRet&=(NULL!=pvt->SetBounds);
    fRet =(NULL!=pvt->SetColorScheme);
    fRet&=(NULL!=pvt->SetData);
    fRet&=(NULL!=pvt->SetTargetDevice);
    fRet&=(NULL!=pvt->Show);
   #endif

    return fRet;    //TRUE by default in Win32
    }





/*
 * OLEVtblFreeObject
 *
 * Purpose:
 *  Frees all procedure instances in the object VTBL.
 *
 * Parameters:
 *  pvt             LPOLEOBJECTVTBL to the VTBL to free.
 *
 * Return Value:
 *  none
 *
 * Customization:
 *  None required.
 */

void WINAPI OLEVtblFreeObject(LPOLEOBJECTVTBL pvt)
    {
   #ifndef WIN32
    FreeProcInstance(pvt->DoVerb);
    FreeProcInstance(pvt->EnumFormats);
    FreeProcInstance(pvt->GetData);
    FreeProcInstance((FARPROC)pvt->QueryProtocol);
    FreeProcInstance(pvt->Release);
    FreeProcInstance(pvt->SetBounds);
    FreeProcInstance(pvt->SetColorScheme);
    FreeProcInstance(pvt->SetData);
    FreeProcInstance(pvt->SetTargetDevice);
    FreeProcInstance(pvt->Show);
   #endif

    return;
    }



#endif //MAKEOLESERVER
