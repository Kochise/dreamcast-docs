/*
 * OLE2UI.C
 *
 * Contains initialization routines and miscellaneous API implementations for
 * the OLE 2.0 User Interface Support Library.
 *
 * Copyright (c)1992-1996 Microsoft Corporation, All Right Reserved
 */

#define STRICT  1

#include "olestd.h"
#include "common.h"
#include "utility.h"
#include <commdlg.h>
#include "malspy.h"

OLEDBGDATA

#define WINDLL  1           // make far pointer version of stdargs.h
#include <stdarg.h>

//The instance handle shared amongst all dialogs.
HINSTANCE     ghInst;

// object count, used to support DllCanUnloadNow and OleUICanUnloadNow
DWORD g_dwObjectCount=0;
DWORD g_dwLockCount=0;

//Registered messages for use with all the dialogs, registered in LibMain
UINT        uMsgHelp=0;
UINT        uMsgEndDialog=0;
UINT        uMsgBrowse=0;
UINT        uMsgChangeIcon=0;
UINT        uMsgFileOKString=0;
UINT        uMsgCloseBusyDlg=0;

//Clipboard formats used by PasteSpecial
UINT  cfObjectDescriptor;
UINT  cfLinkSrcDescriptor;
UINT  cfEmbedSource;
UINT  cfEmbeddedObject;
UINT  cfLinkSource;
UINT  cfOwnerLink;
UINT  cfFileName;


// local definition
#define WM_U_UPDATELINK WM_USER



/*
 * OleStdInitialize
 *
 * NOTE: This function should be called by your application before using any of
 *       the functions found in this library.
 *
 * Purpose:
 *   Initializes the OLE UI Library.
 *
 * Parameters:
 *
 *  hInstance       HINSTANCE of the module where the UI library resources
 *                  and Dialog Procedures are contained.  If you are calling
 *                  this function yourself, this should be the instance handle
 *                  of your application.
 *
 *  hPrevInst       HINSTANCE of the previous application instance.
 *                  This is the parameter passed in to your WinMain.  For
 *                  the DLL version, this should always be set to zero (for
 *                  WIN16 DLLs).
 *
 * Return Value:
 *  BOOL            TRUE if initialization was successful.
 *                  FALSE if either the "Magic Number" did not verify, or one of
 *                  the window classes could not be registered.  If the
 *                  "Magic Number" did not verify, then the resources
 *                  in your module are of a different version than the
 *                  ones you compiled with.
 */

STDAPI_(BOOL) OleStdInitialize(HINSTANCE hInstance)
{
   OleDbgOut1("OleStdInitialize called.\r\n");
   ghInst=hInstance;

   // Register Clipboard Formats used by PasteSpecial dialog.
   cfObjectDescriptor = RegisterClipboardFormat(CF_OBJECTDESCRIPTOR);
   cfLinkSrcDescriptor= RegisterClipboardFormat(CF_LINKSRCDESCRIPTOR);
   cfEmbedSource      = RegisterClipboardFormat(CF_EMBEDSOURCE);
   cfEmbeddedObject   = RegisterClipboardFormat(CF_EMBEDDEDOBJECT);
   cfLinkSource       = RegisterClipboardFormat(CF_LINKSOURCE);
   cfOwnerLink        = RegisterClipboardFormat(CF_OWNERLINK);
   cfFileName         = RegisterClipboardFormat(CF_FILENAME);

#ifdef TRACEMEM
   return (InitializeMallocSpy());
#else
   return (TRUE);
#endif
}

STDAPI_(void) OleStdUninitialize(void)
{
#ifdef TRACEMEM
   UninitializeMallocSpy();
#endif
}

/*
 * OleUICanUnloadNow
 *
 * NOTE: if you link to this library and you implement
 *       DllCanUnloadNow, then you must call this routine in your
 *       implementation of DllCanUnloadNow to determine if you can be
 *       unloaded or not.
 *
 * Purpose:
 *   Determines when it is safe to go away
 *   (ie. there are no existing object instances).
 *
 * Return Value:
 *   HRESULT    NOERROR it is safe to go away, S_FALSE this code must stay
 *              loaded.
 *
 * Comments:
 *
 *   If an INPROC server DLL links to the OLESTD library,
 *   then the OleUILockLibrary function should NOT be used.
 *   instead the INPROC server DLL should call OleUICanUnloadNow API from
 *   within its own DllCanUnloadNow function. The idea here is, that if there
 *   are any existing instance of objects created by the OLESTD library
 *   functions (eg. EnumFORMATETC objects created by OleStdEnumFmtEtc_Create)
 *   then, the INPROC server DLL must NOT let itself be unloaded.
 *
 *   An EXE based object using the OLESTD libray need NOT use either the
 *   OleUILockLibrary or OleUICanUnloadNow functions. All objects created
 *   by the OLESTD library will have LRPC proxies and stubs created to
 *   manage remoting method calls. the worst that can happen when the EXE
 *   exits is that any outstanding proxies for unreleased objects will get
 *   RPC_E_SERVERDIED errors; they will not GPFault.
 */

STDAPI OleUICanUnloadNow()
{
  if (g_dwObjectCount == 0) {
   return NOERROR;
  }

  return S_FALSE;
}


