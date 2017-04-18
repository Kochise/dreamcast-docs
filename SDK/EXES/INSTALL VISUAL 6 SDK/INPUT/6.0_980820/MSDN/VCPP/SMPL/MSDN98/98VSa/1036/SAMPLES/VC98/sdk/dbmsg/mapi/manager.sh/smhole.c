/*
 *  S M H O L E . C
 *
 *  Sample mail handling hook OLE storage support for RICHEDIT
 *  Copyright 1992-95 Microsoft Corporation.  All Rights Reserved.
 */

#include "_pch.h"
DEFINE_OLEGUID(IID_IRichEditOleCallback, 0x00020D03, 0, 0);
const REOC_Vtbl vtblREOC =
{
    REOC_QueryInterface,
    REOC_AddRef,
    REOC_Release,
    REOC_GetNewStorage,
    REOC_GetInPlaceContext,
    REOC_ShowContainerUI,
    REOC_QueryInsertObject,
    REOC_DeleteObject,
    REOC_QueryAcceptData,
    REOC_ContextSensitiveHelp,
    REOC_GetClipboardData,
    REOC_GetDragDropEffect,
    REOC_GetContextMenu
};


/*
 *  SMH Object Methods
 *
 *  SMH_QueryInterface      (See OLE IUnknown object methods)
 *  SMH_AddRef              (See OLE IUnknown object methods)
 *  SMH_Release             (See OLE IUnknown object methods)
 *  SMH_InboundMsgHook      Filters inbound messages
 *  SMH_OutboundMsgHook     Filters sent mail messages
 *
 */
STDMETHODIMP
REOC_QueryInterface (LPREOC lpreoc, REFIID lpiid, LPVOID FAR * lppv)
{
    if (!memcmp (lpiid, &IID_IRichEditOleCallback, sizeof(IID)) ||
        !memcmp (lpiid, &IID_IUnknown, sizeof(IID)))
    {
        *lppv = (LPVOID)lpreoc;
        lpreoc->lcInit++;
        return hrSuccess;
    }

    DebugTraceSc (SMH_QueryInterface(), MAPI_E_INTERFACE_NOT_SUPPORTED);
    return ResultFromScode (MAPI_E_INTERFACE_NOT_SUPPORTED);
}

STDMETHODIMP_(ULONG)
REOC_AddRef (LPREOC lpreoc)
{
    return ++lpreoc->lcInit;
}

STDMETHODIMP_(ULONG)
REOC_Release (LPREOC lpreoc)
{
    if (--lpreoc->lcInit)
        return lpreoc->lcInit;

    UlRelease (lpreoc->lpstg);
    (*lpreoc->lpfnFree) (lpreoc);
    return 0;
}

STDMETHODIMP
REOC_GetNewStorage (LPREOC lpreoc, LPSTORAGE FAR * lppstg)
{
    HRESULT hr = hrSuccess;
    LPSTORAGE lpstg = lpreoc->lpstg;

#ifdef  _WIN32
    WCHAR rgch[MAX_PATH];
    wsprintfW (rgch, L"SMHOBJ%08ld", lpreoc->cSub++);
#else
    CHAR rgch[MAX_PATH];
    wsprintf (rgch, "SMHOBJ%08ld", lpreoc->cSub++);
#endif  // WIN16

    if (lpstg)
    {
        lpstg->lpVtbl->CreateStorage (lpstg,
                            rgch,
                            STGM_READWRITE | STGM_TRANSACTED | STGM_SHARE_EXCLUSIVE,
                            0,
                            0,
                            lppstg);
        if (HR_FAILED (hr))
            *lppstg = NULL;
    }
    DebugTraceResult (REOC_GetNewStorage(), hr);
    return hr;
}

STDMETHODIMP
REOC_GetInPlaceContext (LPREOC lpreoc,
   LPOLEINPLACEFRAME FAR * lppipframe,
   LPOLEINPLACEUIWINDOW FAR * lppipuiDoc,
   LPOLEINPLACEFRAMEINFO lpipfinfo)
{
    return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP
REOC_ShowContainerUI (LPREOC lpreoc, BOOL fShow)
{
    return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP
REOC_QueryInsertObject (LPREOC lpreoc, LPCLSID pclsid, LPSTORAGE pstg, LONG cp)
{
    return hrSuccess;
}

STDMETHODIMP
REOC_DeleteObject (LPREOC lpreoc, LPOLEOBJECT lpoleobj)
{
    return hrSuccess;
}

STDMETHODIMP
REOC_QueryAcceptData (LPREOC lpreoc,
    LPDATAOBJECT lpdataobj,
    CLIPFORMAT FAR * lpcfFormat,
    DWORD reco,
    BOOL fReally,
    HGLOBAL hMetaPict)
{
    return hrSuccess;
}

STDMETHODIMP
REOC_ContextSensitiveHelp (LPREOC lpreoc, BOOL fEnterMode)
{
    return hrSuccess;
}

STDMETHODIMP
REOC_GetClipboardData (LPREOC lpreoc,
    CHARRANGE FAR * lpchrg,
    DWORD reco,
    LPDATAOBJECT FAR * lppdataobj)
{
    return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP
REOC_GetDragDropEffect (LPREOC lpreoc,
    BOOL fDrag,
    DWORD grfKeyState,
    LPDWORD lpdwEffect)
{
    return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP
REOC_GetContextMenu (LPREOC lpreoc,
    WORD seltype,
    LPOLEOBJECT lpoleobj,
    CHARRANGE FAR * lpchrg,
    HMENU FAR * lphmenu)
{
    if (lpreoc->lpfb && (*lphmenu = CreatePopupMenu()))
    {
        AppendMenu (*lphmenu, MF_ENABLED | MF_STRING, ID_Bullet, "Bullet Paragraph");
        AppendMenu (*lphmenu, MF_SEPARATOR, 0, NULL);
        AppendMenu (*lphmenu, MF_ENABLED | MF_STRING, ID_Indent, "Increase Indent");
        AppendMenu (*lphmenu, MF_ENABLED | MF_STRING, ID_Collapse, "Decrease Indent");
        AppendMenu (*lphmenu, MF_SEPARATOR, 0, NULL);
        AppendMenu (*lphmenu, MF_ENABLED | MF_STRING, ID_Left, "Align Left");
        AppendMenu (*lphmenu, MF_ENABLED | MF_STRING, ID_Center, "Align Center");
        AppendMenu (*lphmenu, MF_ENABLED | MF_STRING, ID_Right, "Align Right");
        if (lpreoc->lpfb->pf.wNumbering == PFN_BULLET)
            CheckMenuItem (*lphmenu, ID_Bullet, MF_BYCOMMAND | MF_CHECKED);
        if (lpreoc->lpfb->pf.dxStartIndent > 1440)
            EnableMenuItem (*lphmenu, ID_Indent, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
        if (!lpreoc->lpfb->pf.dxStartIndent)
            EnableMenuItem (*lphmenu, ID_Collapse, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
        return hrSuccess;
    }
    return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP_(SCODE)
ScNewRicheditCallback (LPFORMATBAR lpfb,
    LPALLOCATEBUFFER lpfnAlloc,
    LPALLOCATEMORE lpfnAllocMore,
    LPFREEBUFFER lpfnFree,
    LPREOC FAR * lppreoc)
{
    SCODE sc;
    LPREOC lpreoc = NULL;

    if (!FAILED (sc = (*lpfnAlloc) (sizeof(REOC), &lpreoc)))
    {
        memset (lpreoc, 0, sizeof (REOC));
        lpreoc->lpVtbl = (REOC_Vtbl FAR *)&vtblREOC;
        lpreoc->lcInit = 1;
        lpreoc->cSub = 0;
        lpreoc->lpfnAlloc = lpfnAlloc;
        lpreoc->lpfnAllocMore = lpfnAllocMore;
        lpreoc->lpfnFree = lpfnFree;
        lpreoc->lpfb = lpfb;

        sc = GetScode (StgCreateDocfile (NULL,
                                STGM_READWRITE           |
                                    STGM_TRANSACTED      |
                                    STGM_DELETEONRELEASE |
                                    STGM_SHARE_EXCLUSIVE,
                                0,
                                &lpreoc->lpstg));
        if (FAILED (sc))
        {
            (*lpfnFree) (lpreoc);
            lpreoc = NULL;
        }
    }

    *lppreoc = lpreoc;

    DebugTraceSc (ScNewRicheditCallback(), sc);
    return sc;
}
