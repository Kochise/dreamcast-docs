/***********************************************************************
 *
 *  PRECOMP.H
 *
 *
 *  Copyright 1995 Microsoft Corporation.  All Rights Reserved.
 *
 ***********************************************************************/

#define         STRICT  1

#include        <windows.h>
#include        <windowsx.h>
#include        <ole2.h>
#include        <mapix.h>
#include        <mapiform.h>
#include        <mapidbg.h>
#include        <mapiutil.h>
#include        <exchform.h>
#include        <pdkver.h>
#include        <strstrea.h>
#include        "resource.h"

#include        "viewntfr.h"
#include        "lasterr.h"

#include        "guid.h"

#define ASSERT(a)       Assert(a)

extern char g_szFormName[];
extern char g_szWindowCaption[];
extern char g_szSendWinClass[];
extern char g_szReadWinClass[];



//
// CClassFactory
//

class CClassFactory : public IClassFactory
{
public:
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR * ppvObj);
    STDMETHOD_(ULONG,AddRef)  (THIS);
    STDMETHOD_(ULONG,Release) (THIS);
    STDMETHOD (CreateInstance) (LPUNKNOWN pUnkOuter, REFIID riid,
                                LPVOID FAR* ppvObject);
    STDMETHOD (LockServer) (BOOL fLock);

    CClassFactory(void);
    ~CClassFactory(void);

    void FAR PASCAL ObjDestroyedCallback ();

public:
    static HWND ms_hWndMain;    // Main window handle

protected:
    ULONG m_cRef;               // Count of references
    static ULONG ms_cObjs;      // Count of active objects
    static ULONG ms_cLocks;     // Count of active locks
};

#include        "formbase.h"

