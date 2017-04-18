/*
 * OLEGLOBL.H
 *
 * Definitions an other globals specific to the OLE code.
 *
 * Copyright(c) Microsoft Corp. 1992-1994 All Rights Reserved
 * Win32 version, January 1994
 */

#ifdef MAKEOLESERVER

#ifndef CCHPATHMAX
#define CCHPATHMAX          256
#endif

#ifndef CCHFILENAME
#define CCHFILENAMEMAX      15
#endif


typedef LPOLESERVER    FAR *LPLPOLESERVER;
typedef LPOLESERVERDOC FAR *LPLPOLESERVERDOC;
typedef LPOLEOBJECT    FAR *LPLPOLEOBJECT;

typedef LPVOID (WINAPI *LPVOIDPROC) (LPOLEOBJECT, LPSTR);


typedef struct
    {
    LPOLEOBJECTVTBL     pvtbl;          //Standard
    BOOL                fRelease;       //Flag to watch if we need to wait
    LPOLECLIENT         pClient;        //Necessary for notifications
    HLOCAL              hMem;           //Memory handle to this structure
    } COSMOOBJECT;


typedef COSMOOBJECT FAR *LPCOSMOOBJECT;
#define CBCOSMOOBJECT sizeof(COSMOOBJECT)


typedef struct
    {
    LPOLESERVERDOCVTBL  pvtbl;          //Standard
    LHSERVERDOC         lh;             //Required by OleRegisterServerDoc
    BOOL                fRelease;       //Flag to watch if we need to wait
    ATOM                aObject;        //Name of the document's object
    ATOM                aClient;        //Name of the connected client
    HLOCAL              hMem;           //Memory handle to this structure
    LPCOSMOOBJECT       pObj;           //Last object we allocated
    } COSMODOC;


typedef COSMODOC FAR *LPCOSMODOC;
#define CBCOSMODOC sizeof(COSMODOC)


typedef struct
    {
    LPOLESERVERVTBL     pvtbl;          //Standard
    LHSERVER            lh;             //Required by OleRegisterServer
    BOOL                fRelease;       //Flag to watch if we need to wait
    BOOL                fEmbed;         //TRUE if we're embedding only
    BOOL                fLink;          //TRUE if we're linking only
    UINT                nCmdShow;       //OLE-modified window show command
    HWND                hWnd;           //Main application window
    HLOCAL              hMem;           //Memory handle to this structure
    LPCOSMODOC          pDoc;           //Last document we allocated
    } COSMOSERVER;

typedef COSMOSERVER FAR *LPCOSMOSERVER;
#define CBCOSMOSERVER sizeof(COSMOSERVER)


/*
 * Single data structure holding any OLE-specific global variables.
 */

typedef struct
    {
    LPCOSMOSERVER       pSvr;

    OLESERVERVTBL       vtblSvr;
    OLESERVERDOCVTBL    vtblDoc;
    OLEOBJECTVTBL       vtblObj;

    UINT                cfNative;
    UINT                cfOwnerLink;
    UINT                cfObjectLink;
    } XOLEGLOBALS;

typedef XOLEGLOBALS FAR *LPXOLEGLOBALS;
#define CBXOLEGLOBALS sizeof(XOLEGLOBALS)


//The single global
extern LPXOLEGLOBALS pOLE;


/*
 * STDTARGETDEVICE structure for ObjSetTargetDevice.
 */


typedef struct
    {
    //Offsets are pointers into the data field.
    UINT    deviceNameOffset;   //szDeviceName
    UINT    driverNameOffset;   //szDriverName
    UINT    portNameOffset;     //szPortName
    UINT    extDevModeOffset;   //DEVMODE structure
    UINT    extDevModeSize;     //Size of the DEVMOCE struct, for versioning.
    UINT    environmentOffset;  //Current MS-DOS environment, in a string
    UINT    environmentSize;    //Length of environment string.
    BYTE    data[];
    } STDTARGETDEVICE;

typedef STDTARGETDEVICE FAR * LPSTDTARGETDEVICE;
#define CBSTDTARGETDEVICE sizeof(STDTARGETDEVICE)






/*
 * Function prototypes for OLE-Specific functions.
 */



//OLECLIP.C
BOOL      WINAPI FOLECopyNative(LPXOLEGLOBALS);
BOOL      WINAPI FOLECopyLink(LPXOLEGLOBALS, BOOL, LPSTR);
HGLOBAL   WINAPI HLinkConstruct(LPSTR, LPSTR, LPSTR);


//OLEDOC.C
LPCOSMODOC  WINAPI PDocumentAllocate(LPOLESERVERDOCVTBL);   //Helper
void        WINAPI DocumentClean(LPCOSMODOC);               //Helper

OLESTATUS WINAPI DocClose(LPCOSMODOC);
OLESTATUS WINAPI DocGetObject(LPCOSMODOC, OLE_LPCSTR, LPLPOLEOBJECT, LPOLECLIENT);
OLESTATUS WINAPI DocExecute(LPCOSMODOC, HGLOBAL);
OLESTATUS WINAPI DocRelease(LPCOSMODOC);
OLESTATUS WINAPI DocSave(LPCOSMODOC);
OLESTATUS WINAPI DocSetColorScheme(LPCOSMODOC, OLE_CONST LOGPALETTE FAR *);
OLESTATUS WINAPI DocSetDocDimensions(LPCOSMODOC, OLE_CONST RECT FAR *);
OLESTATUS WINAPI DocSetHostNames(LPCOSMODOC, OLE_LPCSTR, OLE_LPCSTR);


//OLEEXIT.C
BOOL WINAPI FOLEExit(LPXOLEGLOBALS);


//OLEFILE.C
LPCOSMODOC WINAPI PDocRevokeAndCreate(LPXOLEGLOBALS);


//OLEINIT.C
BOOL      WINAPI FOLEInstanceInit(LPXOLEGLOBALS, HINSTANCE, LPSTR, LPSTR FAR *, UINT);


//OLEMISC.C
void      WINAPI MenuEmbeddingSet(HWND, LPSTR, BOOL);
void      WINAPI OLEClientNotify(LPCOSMOOBJECT, UINT);
BOOL      WINAPI FOLEReleaseWait(BOOL FAR *, LONG);



//OLEOBJ.C
LPCOSMOOBJECT WINAPI PObjectAllocate(LPOLEOBJECTVTBL);

LPVOID        WINAPI ObjQueryProtocol(LPCOSMOOBJECT, OLE_LPCSTR);
OLESTATUS     WINAPI ObjRelease(LPCOSMOOBJECT);
OLESTATUS     WINAPI ObjShow(LPCOSMOOBJECT, BOOL);
OLESTATUS     WINAPI ObjDoVerb(LPCOSMOOBJECT, UINT, BOOL, BOOL);
OLESTATUS     WINAPI ObjGetData(LPCOSMOOBJECT, OLECLIPFORMAT, HGLOBAL FAR *);
OLESTATUS     WINAPI ObjSetData(LPCOSMOOBJECT, OLECLIPFORMAT, HGLOBAL);
OLESTATUS     WINAPI ObjSetTargetDevice(LPCOSMOOBJECT, HGLOBAL);
OLESTATUS     WINAPI ObjSetBounds(LPCOSMOOBJECT, OLE_CONST RECT FAR *);
OLECLIPFORMAT WINAPI ObjEnumFormats(LPCOSMOOBJECT, OLECLIPFORMAT);
OLESTATUS     WINAPI ObjSetColorScheme(LPCOSMOOBJECT, OLE_CONST LOGPALETTE FAR *);


//OLESVR.C
LPCOSMOSERVER WINAPI PServerAllocate(LPOLESERVERVTBL);

OLESTATUS WINAPI ServerCreate(LPCOSMOSERVER, LHSERVERDOC, OLE_LPCSTR, OLE_LPCSTR, LPLPOLESERVERDOC);
OLESTATUS WINAPI ServerCreateFromTemplate(LPCOSMOSERVER, LHSERVERDOC, OLE_LPCSTR, OLE_LPCSTR, OLE_LPCSTR, LPLPOLESERVERDOC);
OLESTATUS WINAPI ServerEdit(LPCOSMOSERVER, LHSERVERDOC, OLE_LPCSTR, OLE_LPCSTR, LPLPOLESERVERDOC);
OLESTATUS WINAPI ServerExecute(LPCOSMOSERVER, HGLOBAL);
OLESTATUS WINAPI ServerExit(LPCOSMOSERVER);
OLESTATUS WINAPI ServerOpen(LPCOSMOSERVER, LHSERVERDOC, OLE_LPCSTR, LPLPOLESERVERDOC);
OLESTATUS WINAPI ServerRelease(LPCOSMOSERVER);


//OLEVTBL.C
BOOL      WINAPI FOLEVtblInitServer(HINSTANCE,   LPOLESERVERVTBL);
BOOL      WINAPI FOLEVtblInitDocument(HINSTANCE, LPOLESERVERDOCVTBL);
BOOL      WINAPI FOLEVtblInitObject(HINSTANCE,   LPOLEOBJECTVTBL);

void      WINAPI OLEVtblFreeServer(LPOLESERVERVTBL);
void      WINAPI OLEVtblFreeDocument(LPOLESERVERDOCVTBL);
void      WINAPI OLEVtblFreeObject(LPOLEOBJECTVTBL);


#endif //MAKEOLESERVER
