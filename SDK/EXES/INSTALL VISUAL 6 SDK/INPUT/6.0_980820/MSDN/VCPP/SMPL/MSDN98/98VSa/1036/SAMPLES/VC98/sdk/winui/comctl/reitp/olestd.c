/*************************************************************************
**
**    OLE 2 Standard Utilities
**
**    olestd.c
**
**    This file contains utilities that are useful for most standard
**        OLE 2.0 compound document type applications.
**
**    (c) Copyright Microsoft Corp. 1992-1997 All Rights Reserved
**
*************************************************************************/

#define NONAMELESSUNION     // use strict ANSI standard (for DVOBJ.H)

#define STRICT  1
#include "olestd.h"
#include <stdlib.h>
#include <ctype.h>
#include <shellapi.h>
#include "common.h"

OLEDBGDATA

static char szAssertMemAlloc[] = "CoGetMalloc failed";
static int IsCloseFormatEtc(FORMATETC FAR* pFetcLeft, FORMATETC FAR* pFetcRight);

//The instance handle shared amongst all dialogs.
HINSTANCE     ghInst;


/* OleStdSwitchDisplayAspect
** -------------------------
**    Switch the currently cached display aspect between DVASPECT_ICON
**    and DVASPECT_CONTENT.
**
**    NOTE: when setting up icon aspect, any currently cached content
**    cache is discarded and any advise connections for content aspect
**    are broken.
**
**    RETURNS:
**      S_OK -- new display aspect setup successfully
**      E_INVALIDARG -- IOleCache interface is NOT supported (this is
**                  required).
**      <other SCODE> -- any SCODE that can be returned by
**                  IOleCache::Cache method.
**      NOTE: if an error occurs then the current display aspect and
**            cache contents unchanged.
*/
STDAPI OleStdSwitchDisplayAspect(
      LPOLEOBJECT             lpOleObj,
      LPDWORD                 lpdwCurAspect,
      DWORD                   dwNewAspect,
      HGLOBAL                 hMetaPict,
      BOOL                    fDeleteOldAspect,
      BOOL                    fSetupViewAdvise,
      LPADVISESINK            lpAdviseSink,
      BOOL FAR*               lpfMustUpdate
)
{
   LPOLECACHE      lpOleCache = NULL;
   LPVIEWOBJECT    lpViewObj = NULL;
   LPENUMSTATDATA  lpEnumStatData = NULL;
   STATDATA        StatData;
   FORMATETC       FmtEtc;
   STGMEDIUM       Medium;
   DWORD           dwAdvf;
   DWORD           dwNewConnection;
   DWORD           dwOldAspect = *lpdwCurAspect;
   HRESULT         hrErr;

   if (lpfMustUpdate)
      *lpfMustUpdate = FALSE;

   lpOleCache = (LPOLECACHE)OleStdQueryInterface(
                              (LPUNKNOWN)lpOleObj,&IID_IOleCache);

   // if IOleCache* is NOT available, do nothing
   if (! lpOleCache)
      return E_INVALIDARG;

   // Setup new cache with the new aspect
   FmtEtc.cfFormat = 0;     // whatever is needed to draw
   FmtEtc.ptd      = NULL;
   FmtEtc.dwAspect = dwNewAspect;
   FmtEtc.lindex   = -1;
   FmtEtc.tymed    = TYMED_NULL;

   /* NOTE: if we are setting up Icon aspect with a custom icon
   **    then we do not want DataAdvise notifications to ever change
   **    the contents of the data cache. thus we set up a NODATA
   **    advise connection. otherwise we set up a standard DataAdvise
   **    connection.
   */
   if (dwNewAspect == DVASPECT_ICON && hMetaPict)
      dwAdvf = ADVF_NODATA;
   else
      dwAdvf = ADVF_PRIMEFIRST;

   OLEDBG_BEGIN2("IOleCache::Cache called\r\n")
   hrErr = lpOleCache->lpVtbl->Cache(
         lpOleCache,
         (LPFORMATETC)&FmtEtc,
         dwAdvf,
         (LPDWORD)&dwNewConnection
   );
   OLEDBG_END2

   if (! SUCCEEDED(hrErr)) {
      OleDbgOutHResult("IOleCache::Cache returned", hrErr);
      OleStdRelease((LPUNKNOWN)lpOleCache);
      return hrErr;
   }

   *lpdwCurAspect = dwNewAspect;

   /* NOTE: if we are setting up Icon aspect with a custom icon,
   **    then stuff the icon into the cache. otherwise the cache must
   **    be forced to be updated. set the *lpfMustUpdate flag to tell
   **    caller to force the object to Run so that the cache will be
   **    updated.
   */
   if (dwNewAspect == DVASPECT_ICON && hMetaPict) {

      FmtEtc.cfFormat = CF_METAFILEPICT;
      FmtEtc.ptd      = NULL;
      FmtEtc.dwAspect = DVASPECT_ICON;
      FmtEtc.lindex   = -1;
      FmtEtc.tymed    = TYMED_MFPICT;

      Medium.tymed            = TYMED_MFPICT;
      Medium.u.hGlobal        = hMetaPict;
      Medium.pUnkForRelease   = NULL;

      OLEDBG_BEGIN2("IOleCache::SetData called\r\n")
      hrErr = lpOleCache->lpVtbl->SetData(
            lpOleCache,
            (LPFORMATETC)&FmtEtc,
            (LPSTGMEDIUM)&Medium,
            FALSE   /* fRelease */
      );
      OLEDBG_END2
   } else {
      if (lpfMustUpdate)
         *lpfMustUpdate = TRUE;
   }

   if (fSetupViewAdvise && lpAdviseSink) {
      /* NOTE: re-establish the ViewAdvise connection */
      lpViewObj = (LPVIEWOBJECT)OleStdQueryInterface(
                              (LPUNKNOWN)lpOleObj,&IID_IViewObject);

      if (lpViewObj) {

         OLEDBG_BEGIN2("IViewObject::SetAdvise called\r\n")
         lpViewObj->lpVtbl->SetAdvise(
               lpViewObj,
               dwNewAspect,
               0,
               lpAdviseSink
         );
         OLEDBG_END2

         OleStdRelease((LPUNKNOWN)lpViewObj);
      }
   }

   /* NOTE: remove any existing caches that are set up for the old
   **    display aspect. It WOULD be possible to retain the caches set
   **    up for the old aspect, but this would increase the storage
   **    space required for the object and possibly require additional
   **    overhead to maintain the unused cachaes. For these reasons the
   **    strategy to delete the previous caches is prefered. if it is a
   **    requirement to quickly switch between Icon and Content
   **    display, then it would be better to keep both aspect caches.
   */

   if (fDeleteOldAspect) {
      OLEDBG_BEGIN2("IOleCache::EnumCache called\r\n")
      hrErr = lpOleCache->lpVtbl->EnumCache(
            lpOleCache,
            (LPENUMSTATDATA FAR*)&lpEnumStatData
      );
      OLEDBG_END2

      while(hrErr == NOERROR) {
         hrErr = lpEnumStatData->lpVtbl->Next(
               lpEnumStatData,
               1,
               (LPSTATDATA)&StatData,
               NULL
         );
         if (hrErr != NOERROR)
            break;              // DONE! no more caches.

         if (StatData.formatetc.dwAspect == dwOldAspect) {

            // Remove previous cache with old aspect
            OLEDBG_BEGIN2("IOleCache::Uncache called\r\n")
            lpOleCache->lpVtbl->Uncache(lpOleCache,StatData.dwConnection);
            OLEDBG_END2
         }
      }

      if (lpEnumStatData) {
         OleStdVerifyRelease(
               (LPUNKNOWN)lpEnumStatData,
               OLESTR ("OleStdSwitchDisplayAspect: Cache enumerator NOT released"));
      }
   }

   if (lpOleCache)
      OleStdRelease((LPUNKNOWN)lpOleCache);

   return NOERROR;
}


/* OleStdQueryInterface
** --------------------
**    Returns the desired interface pointer if exposed by the given object.
**    Returns NULL if the interface is not available.
**    eg.:
**      lpDataObj = OleStdQueryInterface(lpOleObj, &IID_DataObject);
*/
STDAPI_(LPUNKNOWN) OleStdQueryInterface(LPUNKNOWN lpUnk, REFIID riid)
{
   LPUNKNOWN lpInterface;
   HRESULT hrErr;

   hrErr = lpUnk->lpVtbl->QueryInterface(
         lpUnk,
         riid,
         (LPVOID FAR*)&lpInterface
   );

   if (hrErr == NOERROR)
      return lpInterface;
   else
      return NULL;
}


/* OleStdFreeString
** ----------------
**    Free a string that was allocated with the currently active
**    IMalloc* allocator.
**
**    if the caller has the current IMalloc* handy, then it can be
**    passed as a argument, otherwise this function will retrieve the
**    active allocator and use it.
*/
STDAPI_(void) OleStdFreeString(LPOLESTR lpsz, LPMALLOC lpMalloc)
{
   BOOL fMustRelease = FALSE;

   if (! lpMalloc) {
      if (CoGetMalloc(MEMCTX_TASK, &lpMalloc) != NOERROR)
         return;
      fMustRelease = TRUE;
   }

   lpMalloc->lpVtbl->Free(lpMalloc, lpsz);

   if (fMustRelease)
      lpMalloc->lpVtbl->Release(lpMalloc);
}


/* Call Release on the object that is expected to go away.
**      if the refcnt of the object did no go to 0 then give a debug message.
*/
STDAPI_(ULONG) OleStdVerifyRelease(LPUNKNOWN lpUnk, LPOLESTR lpszMsg)
{
   ULONG cRef;
   char  lpszAnsiMsg[256];

   W2A (lpszMsg, lpszAnsiMsg, 256);
   cRef = lpUnk->lpVtbl->Release(lpUnk);

#if defined( _DEBUG )
   if (cRef != 0) {
      char szBuf[80];
      if (lpszMsg)
         MessageBox(NULL, lpszAnsiMsg, NULL, MB_ICONEXCLAMATION | MB_OK);
      wsprintf(
            /*(LPSTR)*/szBuf,
            "refcnt (%ld) != 0 after object (0x%lx) release\n",
            cRef,
            lpUnk
      );
      if (lpszMsg)
         OleDbgOut1(lpszAnsiMsg);
      OleDbgOut1(/*(LPSTR)*/szBuf);
      OleDbgAssertSz(cRef == 0, /*(LPSTR)*/szBuf);
   } else {
      char szBuf[80];
      wsprintf(
            /*(LPSTR)*/szBuf,
            "refcnt = 0 after object (0x%lx) release\n", lpUnk
      );
      OleDbgOut4(/*(LPSTR)*/szBuf);
   }
#endif
   return cRef;
}


/* Call Release on the object that is NOT necessarily expected to go away.
*/
STDAPI_(ULONG) OleStdRelease(LPUNKNOWN lpUnk)
{
   ULONG cRef;

   cRef = lpUnk->lpVtbl->Release(lpUnk);

#if defined( _DEBUG )
   {
      char szBuf[80];
      wsprintf(
            /*(LPSTR)*/szBuf,
            "refcnt = %ld after object (0x%lx) release\n",
            cRef,
            lpUnk
      );
      OleDbgOut4(/*(LPSTR)*/szBuf);
   }
#endif
   return cRef;
}


/*************************************************************************
** OleStdCreateRootStorage
**    create a root level Storage given a filename that is compatible
**    to be used by a top-level OLE container. if the filename
**    specifies an existing file, then an error is returned.
**    the root storage (Docfile) that is created by this function
**    is suitable to be used to create child storages for embedings.
**    (CreateChildStorage can be used to create child storages.)
**    NOTE: the root-level storage is opened in transacted mode.
*************************************************************************/

STDAPI_(LPSTORAGE) OleStdCreateRootStorage(LPOLESTR lpszStgName, DWORD grfMode)
{
   HRESULT hr;
   DWORD grfCreateMode = STGM_READWRITE | STGM_TRANSACTED;
   DWORD reserved = 0;
   LPSTORAGE lpRootStg;
   char szMsg[64];

   // if temp file is being created, enable delete-on-release
   if (! lpszStgName)
      grfCreateMode |= STGM_DELETEONRELEASE;

   hr = StgCreateDocfile(
         lpszStgName,
         grfMode | grfCreateMode,
         reserved,
         (LPSTORAGE FAR*)&lpRootStg
      );

   if (hr == NOERROR)
      return lpRootStg;               // existing file successfully opened

   OleDbgOutHResult("StgCreateDocfile returned", hr);

   if (0 == LoadString(ghInst, (UINT)IDS_OLESTDNOCREATEFILE, /*(LPSTR)*/szMsg, 64))
     return NULL;

   MessageBox(NULL, /*(LPSTR)*/szMsg, NULL,MB_ICONEXCLAMATION | MB_OK);
   return NULL;
}


/*
** OleStdCreateChildStorage
**    create a child Storage inside the given lpStg that is compatible
**    to be used by an embedded OLE object. the return value from this
**    function can be passed to OleCreateXXX functions.
**    NOTE: the child storage is opened in transacted mode.
*/
STDAPI_(LPSTORAGE) OleStdCreateChildStorage(LPSTORAGE lpStg, LPOLESTR lpszStgName)
{
   if (lpStg != NULL) {
      LPSTORAGE lpChildStg;
      DWORD grfMode = (STGM_READWRITE | STGM_TRANSACTED |
            STGM_SHARE_EXCLUSIVE);
      DWORD reserved = 0;

      HRESULT hrErr = lpStg->lpVtbl->CreateStorage(
            lpStg,
            lpszStgName,
            grfMode,
            reserved,
            reserved,
            (LPSTORAGE FAR*)&lpChildStg
         );

      if (hrErr == NOERROR)
         return lpChildStg;

      OleDbgOutHResult("lpStg->lpVtbl->CreateStorage returned", hrErr);
   }
   return NULL;
}

HRESULT HrGetClassFileA(LPCSTR szFilenameA, CLSID * pclsid)
{
    WCHAR lpszFilenameW[MAX_PATH];
    HRESULT hr;

    A2W (szFilenameA, lpszFilenameW, MAX_PATH);

    hr = GetClassFile(lpszFilenameW, pclsid);

    return hr;
}
