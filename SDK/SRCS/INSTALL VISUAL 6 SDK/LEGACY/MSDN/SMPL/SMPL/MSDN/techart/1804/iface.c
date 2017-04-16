/*
    iface.c

    OLE interfaces 

    An interface consists of a pointer to a Vtbl.  We can optionally
    make a Vtbl pointer the first element in a structure of our own and pass
    the pointer to that struct instead of the basic Vtbl.  In this way
    we pass a pointer to an 'object' -> a set of method functions (via
    the Vtbl) and some private data.  

    All the interfaces we provide to our own objects have a pointer to the
    object structure itself following the vtbl pointer so we can generally
    get a pointer to our own object from the 'this' pointer supplied
    to a method function by casting the 'this' pointer to the interface
    struct we defined in our own object and then dereferencing the pointer
    back to the object base. A Picture would be nice no?

    Reference counting is implemented on the whole object, not on the
    individual interfaces.  This allows me to use a single AddRef and a 
    single Release function. The original reason for supporting reference
    counts was to provide a convenient way to detect when the clipboard
    was finished with an object we sent it.

    I should point out that this module was very tedious to type out and
    consequently you might be very grateful that I have done it for you :)

*/

#include "global.h"

//
// global data
//

IOleClientSiteVtbl MyClientSiteVtbl;
IAdviseSinkVtbl MyAdviseSinkVtbl;
IDataObjectVtbl MyDataObjectVtbl;
IDropTargetVtbl MyDropTargetVtbl;
IDropSourceVtbl MyDropSourceVtbl;

//
// Generic support for IUnknown methods of our own interfaces.
// This only works because we define each of our own interfaces
// the same way with the same field names and so on.
//

STDMETHODIMP MyObjQueryInterface(LPVOID pThis,
                                  REFIID iid,
                                  LPVOID FAR* ppNew)
{
    POBJECT pObject;

    dprintf2("MyObjQueryInterface");

    *ppNew = NULL;

    //
    // Cast the 'this' pointer and deref to get a pointer to our object struct
    //

    pObject = ((struct _ObjIClientSite FAR *)pThis)->pObject;
    ASSERT(pObject->dwMagic == OBJECT_MAGIC);

    //
    // Test for the interfaces we support in our objects
    //

    if (IsEqualIID(iid, &IID_IOleClientSite)) {

        dprintf3(" ClientSite");
        *ppNew = &(pObject->ObjIClientSite);

    } else if (IsEqualIID(iid, &IID_IAdviseSink)) {

        dprintf3(" AdviseSink");
        *ppNew = &(pObject->ObjIAdviseSink);

    } else if (IsEqualIID(iid, &IID_IDataObject)) {

        dprintf3(" DataObject");
        *ppNew = &(pObject->ObjIDataObject);

    } else {

        dprintf3(" unsupported interface requested");
        return ResultFromScode(E_NOINTERFACE);
    }

    //
    // Increment the reference count on the object since we
    // are returning a valid pointer to one of its interfaces
    //

    ((LPUNKNOWN)(*ppNew))->lpVtbl->AddRef(*ppNew);

    return NOERROR;
}

STDMETHODIMP_(ULONG) MyObjAddRef(LPVOID pThis)
{
    POBJECT pObject;

    pObject = ((struct _ObjIClientSite FAR *)pThis)->pObject;
    ASSERT(pObject->dwMagic == OBJECT_MAGIC);

    (pObject->lRef)++;
    dprintf2("MyObjAddRef --> %ld", pObject->lRef);

    return pObject->lRef;
}

STDMETHODIMP_(ULONG) MyObjRelease(LPVOID pThis)
{
    POBJECT pObject;
    LONG lReturn;

    pObject = ((struct _ObjIClientSite FAR *)pThis)->pObject;
    ASSERT(pObject->dwMagic == OBJECT_MAGIC);

    lReturn = --(pObject->lRef);
    dprintf2("MyObjRelease --> %ld", pObject->lRef);
    ASSERT(pObject->lRef >= 0);

    if (pObject->lRef == 0) {
        dprintf3(" deleting object");
        DeleteObj(pObject);
    }

    return lReturn;
}

//
// Client site interface method functions
//

STDMETHODIMP ClientSite_QueryInterface(LPOLECLIENTSITE pThis,
                                  REFIID iid,
                                  LPVOID FAR* ppNew)
{
    dprintf2(">ClientSite_QueryInterface");

    return MyObjQueryInterface(pThis, iid, ppNew);
}

STDMETHODIMP_(ULONG) ClientSite_AddRef(LPOLECLIENTSITE pThis)
{
    dprintf2(">ClientSite_AddRef");

    return MyObjAddRef(pThis);
}

STDMETHODIMP_(ULONG) ClientSite_Release(LPOLECLIENTSITE pThis)
{
    dprintf2(">ClientSite_Release");

    return MyObjRelease(pThis);
}

STDMETHODIMP ClientSite_SaveObject(LPOLECLIENTSITE pThis)
{
    POBJECT pObj;
    LPPERSISTSTORAGE pPersist;
    HRESULT hResult;

    dprintf2(">ClientSite_SaveObject");

    pObj = ((struct _ObjIClientSite FAR *)pThis)->pObject;
    ASSERT(pObj->dwMagic == OBJECT_MAGIC);

    //
    // Get a pointer to the OLE objects persistent storage interface
    //

    pPersist = (LPPERSISTSTORAGE) OleStdQueryInterface(
                    (LPUNKNOWN) pObj->pOleObj,
                    &IID_IPersistStorage);

    if (!pPersist) {

        dprintf1("Failed to get IPersistStorage interface");
        return ResultFromScode(E_FAIL);

    }

    //
    // We use one of the OLE helper functions to perform
    // this particular piece of black magic.
    //
    
    hResult = OleSave(pPersist,
                          pObj->pStorage,
                      TRUE);
    
    if (!MyTestOleResult(hResult)) {
        dprintf1("Failed to save OLE object");
        return ResultFromScode(E_FAIL);
    }

    dprintf3(" saved");
    return NOERROR;
}

STDMETHODIMP ClientSite_GetMoniker(LPOLECLIENTSITE pThis,
                              DWORD dwAssign,
                              DWORD dwWhichMoniker,
                              LPMONIKER FAR *ppmk)
{
    dprintf2(">ClientSite_GetMoniker(%lu, %lu)", dwAssign, dwWhichMoniker);
    *ppmk = NULL;

    return ResultFromScode(E_FAIL);
}

STDMETHODIMP ClientSite_GetContainer(LPOLECLIENTSITE pThis,
                                LPOLECONTAINER FAR *ppContainer)
{
    dprintf2(">ClientSite_GetContainer");
    *ppContainer = NULL;

    return ResultFromScode(E_FAIL);
}

STDMETHODIMP ClientSite_ShowObject(LPOLECLIENTSITE pThis)
{
    dprintf2(">ClientSite_ShowObject");

    return NOERROR;
}

STDMETHODIMP ClientSite_OnShowWindow(LPOLECLIENTSITE pThis,
                                BOOL fShow)
{
    POBJECT pObject;

    dprintf2(">ClientSite_OnShowWindow(%u)", fShow);

    //
    // Cast the 'this' pointer and deref to get a pointer to our object struct
    //

    pObject = ((struct _ObjIClientSite FAR *)pThis)->pObject;
    ASSERT(pObject->dwMagic == OBJECT_MAGIC);

    //
    // Set a flag in the object to say if it's currently open in
    // a server window or not.  Redraw it to show it's state as
    // shaded or normal
    //

    pObject->bObjOpenInWindow = fShow;

    //
    // Force a redraw
    //

    InvalidateRect(ghwndMain, &(pObject->rc), TRUE);


    return NOERROR;
}

STDMETHODIMP ClientSite_RequestNewObjectLayout(LPOLECLIENTSITE pThis)
{
    dprintf2(">ClientSite_RequestNewObjectLayout");

    return NOERROR;
}

//
// Advise sink interface method functions
//

STDMETHODIMP AdviseSink_QueryInterface(LPADVISESINK pThis,
                                  REFIID iid,
                                  LPVOID FAR* ppNew)
{
    dprintf2(">AdviseSink_QueryInterface");

    return (MyObjQueryInterface(pThis, iid, ppNew));
}

STDMETHODIMP_(ULONG) AdviseSink_AddRef(LPADVISESINK pThis)
{
    dprintf2(">AdviseSink_AddRef");

    return MyObjAddRef(pThis);
}

STDMETHODIMP_(ULONG) AdviseSink_Release(LPADVISESINK pThis)
{
    dprintf2(">AdviseSink_Release");

    return MyObjRelease(pThis);
}

STDMETHODIMP_(void) AdviseSink_OnDataChange(LPADVISESINK pThis,
                                     FORMATETC FAR *pFormatEtc,
                                     STGMEDIUM FAR *pStgmed)
{
    dprintf2(">AdviseSink_OnDataChange");
}

STDMETHODIMP_(void) AdviseSink_OnViewChange(LPADVISESINK pThis,
                                     DWORD dwAspect,
                                     LONG lIndex)
{
    POBJECT pObj;

    dprintf2(">AdviseSink_OnViewChange");

    pObj = ((struct _ObjIClientSite FAR *)pThis)->pObject;
    ASSERT(pObj->dwMagic == OBJECT_MAGIC);

    //
    // Mark the document as dirty and repaint the 
    // object area to show the changes
    //

    gfDirty = TRUE;
    InvalidateRect(ghwndMain, &(pObj->rc), TRUE);
}

STDMETHODIMP_(void) AdviseSink_OnRename(LPADVISESINK pThis,
                                     LPMONIKER pMnk)
{
    dprintf2(">AdviseSink_OnRename");
}

STDMETHODIMP_(void) AdviseSink_OnSave(LPADVISESINK pThis)
{
    dprintf2(">AdviseSink_OnSave");
}

STDMETHODIMP_(void) AdviseSink_OnClose(LPADVISESINK pThis)
{
    dprintf2(">AdviseSink_OnClose");
}

//
// Data Object interface method functions
//

STDMETHODIMP DataObject_QueryInterface(LPDATAOBJECT pThis,
                                  REFIID iid,
                                  LPVOID FAR* ppNew)
{
    dprintf2(">DataObject_QueryInterface");

    return (MyObjQueryInterface(pThis, iid, ppNew));
}

STDMETHODIMP_(ULONG) DataObject_AddRef(LPDATAOBJECT pThis)
{
    dprintf2(">DataObject_AddRef");

    return MyObjAddRef(pThis);
}

STDMETHODIMP_(ULONG) DataObject_Release(LPDATAOBJECT pThis)
{
    dprintf2(">DataObject_Release");

    return MyObjRelease(pThis);
}

STDMETHODIMP DataObject_GetData(LPDATAOBJECT pThis,
                                LPFORMATETC pFormat,
                                LPSTGMEDIUM pMedium)
{
    POBJECT pObject;
    LPDATAOBJECT pDataObj;
    HRESULT hResult;

    dprintf2(">DataObject_GetData");

    pObject = ((struct _ObjIClientSite FAR *)pThis)->pObject;
    ASSERT(pObject->dwMagic == OBJECT_MAGIC);

    //
    // see if our OLE object can supply it
    //

    pDataObj = (LPDATAOBJECT)OleStdQueryInterface(
	                (LPUNKNOWN) (pObject->pOleObj),
                    &IID_IDataObject);
    if (pDataObj) {

        hResult = pDataObj->lpVtbl->GetData(pDataObj,
                                            pFormat,
                                            pMedium);
        if (SUCCEEDED(hResult)) {
            dprintf3(" data supplied by OLE object");
            return NOERROR;
        }

    }

    //
    // Might be one for us then
    //

    if (GetObjData(pObject, pFormat, pMedium, FALSE)) {

        return NOERROR;
    }

    dprintf3(" failed");
    return ResultFromScode(DATA_E_FORMATETC);
}

STDMETHODIMP DataObject_GetDataHere(LPDATAOBJECT pThis,
                                LPFORMATETC pFormat,
                                LPSTGMEDIUM pMedium)
{
    POBJECT pObject;
    LPDATAOBJECT pDataObj;
    HRESULT hResult;

    dprintf2(">DataObject_GetDataHere");

    pObject = ((struct _ObjIClientSite FAR *)pThis)->pObject;
    ASSERT(pObject->dwMagic == OBJECT_MAGIC);

    //
    // see if our OLE object can supply it
    //

    pDataObj = (LPDATAOBJECT)OleStdQueryInterface(
	                (LPUNKNOWN) (pObject->pOleObj),
                    &IID_IDataObject);
    if (pDataObj) {

        hResult = pDataObj->lpVtbl->GetDataHere(pDataObj,
                                            pFormat,
                                            pMedium);
        if (SUCCEEDED(hResult)) {
            dprintf3(" data supplied by OLE object");
            return NOERROR;
        }
    }

    //
    // Might be one for us then
    //

    if (GetObjData(pObject, pFormat, pMedium, TRUE)) {

        return NOERROR;
    }

    dprintf3(" failed");
    return ResultFromScode(DATA_E_FORMATETC);
}

STDMETHODIMP DataObject_QueryGetData(LPDATAOBJECT pThis,
                                LPFORMATETC pFormat)
{
    POBJECT pObject;

    dprintf2(">DataObject_QueryGetData");

    pObject = ((struct _ObjIClientSite FAR *)pThis)->pObject;
    ASSERT(pObject->dwMagic == OBJECT_MAGIC);

    if (!IsValidDataFormat(pObject, pFormat)) {

        dprintf3(" unsupported format");
        return ResultFromScode(DATA_E_FORMATETC);
    }

    return NOERROR;
}

STDMETHODIMP DataObject_GetCanonicalFormatEtc(LPDATAOBJECT pThis,
                                LPFORMATETC pInFormat,
                                LPFORMATETC pOutFormat)
{
    dprintf2(">DataObject_GetCanonicalFormatEtc");

    return ResultFromScode(E_FAIL);
}

STDMETHODIMP DataObject_SetData(LPDATAOBJECT pThis,
                                LPFORMATETC pFormat,
                                LPSTGMEDIUM pMedium,
                                BOOL fRelease)
{
    dprintf2(">DataObject_SetData");

    return ResultFromScode(E_FAIL);
}

STDMETHODIMP DataObject_EnumFormatEtc(LPDATAOBJECT pThis,
                                DWORD dwDirection,
                                LPENUMFORMATETC FAR *ppForm)
{
    dprintf2(">DataObject_EnumFormatEtc");

    if (dwDirection != DATADIR_GET) {
        return ResultFromScode(E_FAIL);
    }

    //
    // Cal a helper in ole2ui to do the work
    //

    *ppForm = OleStdEnumFmtEtc_Create(giSingleObjGetFmts,
                                      gSingleObjGetFmts);
    return NOERROR;
}

STDMETHODIMP DataObject_DAdvise(LPDATAOBJECT pThis,
                                LPFORMATETC pFormat,
                                DWORD advf,
                                LPADVISESINK pAdvSink,
                                DWORD FAR *pConnect)
{
    dprintf2(">DataObject_DAdvise");

    return ResultFromScode(E_FAIL);
}

STDMETHODIMP DataObject_DUnadvise(LPDATAOBJECT pThis,
                                DWORD dwConnect)
{
    dprintf2(">DataObject_DUnadvise");

    return ResultFromScode(E_FAIL);
}

STDMETHODIMP DataObject_EnumDAdvise(LPDATAOBJECT pThis,
                                LPENUMSTATDATA FAR *pAdvise)
{
    dprintf2(">DataObject_DEnumAdvise");

    return ResultFromScode(E_FAIL);
}

//
// Drop target interface method functions
//

STDMETHODIMP DropTarget_QueryInterface(LPDROPTARGET pThis,
                                  REFIID iid,
                                  LPVOID FAR* ppNew)
{
    PMYDOCINFO pDocInfo;

    dprintf2(">DropTarget_QueryInterface");

    *ppNew = NULL;

    //
    // Cast the 'this' pointer and deref to get a pointer to our object struct
    //

    pDocInfo = ((struct _DocIDropTarget FAR *)pThis)->pDocInfo;

    //
    // Test for the interfaces we support in our doc objects
    //

    if (IsEqualIID(iid, &IID_IDropTarget)) {

        dprintf3(" DropTarget");
        *ppNew = &(pDocInfo->DocIDropTarget);

    } else {

        dprintf3(" unsupported interface requested");
        return ResultFromScode(E_NOINTERFACE);
    }

    //
    // Increment the reference count on the object since we
    // are returning a valid pointer to one of its interfaces
    //

    ((LPUNKNOWN)(*ppNew))->lpVtbl->AddRef(*ppNew);

    return NOERROR;
}

STDMETHODIMP_(ULONG) DropTarget_AddRef(LPDROPTARGET pThis)
{
    PMYDOCINFO pDocInfo;

    dprintf2(">DropTarget_AddRef");
    pDocInfo = ((struct _DocIDropTarget FAR *)pThis)->pDocInfo;
    (pDocInfo->lRef)++;
    dprintf2("MyDocAddRef --> %ld", pDocInfo->lRef);

    return pDocInfo->lRef;
}

STDMETHODIMP_(ULONG) DropTarget_Release(LPDROPTARGET pThis)
{
    PMYDOCINFO pDocInfo;
    LONG lReturn;

    dprintf2(">DropTarget_Release");
    pDocInfo = ((struct _DocIDropTarget FAR *)pThis)->pDocInfo;
    lReturn = --(pDocInfo->lRef);
    dprintf2("MyDocRelease --> %ld", pDocInfo->lRef);

    if (pDocInfo->lRef == 0) {
        dprintf3(" doc object ref count = 0");
    }

    return lReturn;
}

STDMETHODIMP DropTarget_DragEnter(LPDROPTARGET pThis,
                                  LPDATAOBJECT pData,
                                  DWORD dwKeyState,
                                  POINTL pt,
                                  LPDWORD pdwEffect)
{
    PMYDOCINFO pDocInfo;
    POINT ptMouse;

    dprintf2(">DropTarget_DragEnter(%ld,%ld)", pt.x, pt.y);

    //
    // Get a pointer to our doc info struct
    //

    pDocInfo = ((struct _DocIDropTarget FAR *)pThis)->pDocInfo;

    //
    // We just assume we can accept the object.  You could interrogate
    // through pData to see if this is reasonable to do or not which
    // would be better.
    //
    
    if (dwKeyState & MK_CONTROL) {
        *pdwEffect = DROPEFFECT_COPY;   // copy if Ctrl is down
    } else {
        *pdwEffect = DROPEFFECT_MOVE;   // else it's a move
    }
    
    //
    // Get the mouse position in our client area
    //

    pDocInfo->ptlPrev = pt;
    ptMouse.x = (int) pt.x;
    ptMouse.y = (int) pt.y;
    ScreenToClient(ghwndMain, &ptMouse); // in util.c

    //
    // Set the drag feedback rectangle size to the size of the 
    // object and draw the rectangle
    //

    GetObjectDescriptorPointAndSize(pData,
                                    &(pDocInfo->ptMouseOffset),
                                    &(pDocInfo->iWidth),
                                    &(pDocInfo->iHeight));

    pDocInfo->rcDrag.top = ptMouse.y - pDocInfo->ptMouseOffset.y;
    pDocInfo->rcDrag.left = ptMouse.x - pDocInfo->ptMouseOffset.x;
    pDocInfo->rcDrag.bottom = pDocInfo->rcDrag.top
                              + pDocInfo->iHeight;
    pDocInfo->rcDrag.right = pDocInfo->rcDrag.left
                             + pDocInfo->iWidth;
    DrawBand(ghwndMain, &(pDocInfo->rcDrag));

    return ResultFromScode(S_OK);
}

STDMETHODIMP DropTarget_DragOver(LPDROPTARGET pThis,
                                 DWORD dwKeyState,
                                 POINTL pt,
                                 LPDWORD pdwEffect)
{
    PMYDOCINFO pDocInfo;
    POINT ptMouse;

    dprintf2(">DropTarget_DragOver(%ld,%ld)", pt.x, pt.y);

    //
    // Get a pointer to our doc info struct
    //

    pDocInfo = ((struct _DocIDropTarget FAR *)pThis)->pDocInfo;

    //
    // We just assume we can accept the object.  You could interrogate
    // through pData to see if this is reasonable to do or not which
    // would be better.
    //
    
    if (dwKeyState & MK_CONTROL) {
        *pdwEffect = DROPEFFECT_COPY;   // copy if Ctrl is down
    } else {
        *pdwEffect = DROPEFFECT_MOVE;   // else it's a move
    }

    //
    // See if the mouse position has changed since last time
    // and if it has, redraw the feedback rectangle
    //

    if ((pt.x != pDocInfo->ptlPrev.x) 
    || (pt.y != pDocInfo->ptlPrev.y)) {

        pDocInfo->ptlPrev = pt;

        //
        // Erase the feedback rectangle
        //
    
        DrawBand(ghwndMain, &(pDocInfo->rcDrag));
    
        //
        // Get the mouse position in our client area
        //
    
        ptMouse.x = (int) pt.x;
        ptMouse.y = (int) pt.y;
        ScreenToClient(ghwndMain, &ptMouse); // in util.c
    
        //
        // Calculate the new feedback rectangle position
        //
    
        pDocInfo->rcDrag.top = ptMouse.y - pDocInfo->ptMouseOffset.y;
        pDocInfo->rcDrag.left = ptMouse.x - pDocInfo->ptMouseOffset.x;
        pDocInfo->rcDrag.bottom = pDocInfo->rcDrag.top
                                  + pDocInfo->iHeight;
        pDocInfo->rcDrag.right = pDocInfo->rcDrag.left
                                 + pDocInfo->iWidth;
    
        //
        // Draw the new position
        //
    
        DrawBand(ghwndMain, &(pDocInfo->rcDrag));

    }

    return ResultFromScode(S_OK);
}

STDMETHODIMP DropTarget_DragLeave(LPDROPTARGET pThis)
{
    PMYDOCINFO pDocInfo;

    dprintf2(">DropTarget_DragLeave");

    //
    // Get a pointer to our doc info struct
    //

    pDocInfo = ((struct _DocIDropTarget FAR *)pThis)->pDocInfo;

    //
    // Erase the feedback rectangle
    //

    DrawBand(ghwndMain, &(pDocInfo->rcDrag));

    return ResultFromScode(S_OK);
}

STDMETHODIMP DropTarget_Drop(LPDROPTARGET pThis,
                             LPDATAOBJECT pData,
                             DWORD dwKeyState,
                             POINTL pt,
                             LPDWORD pdwEffect)
{
    POBJECT pObj;
    POINT ptOff, ptMouse;
    int w, h;


    dprintf2(">DropTarget_Drop");

    //
    // Start by being pesimistic
    //

    *pdwEffect = DROPEFFECT_NONE;

    //
    // Get the mouse position in our client area
    //

    ptMouse.x = (int) pt.x;
    ptMouse.y = (int) pt.y;
    ScreenToClient(ghwndMain, &ptMouse); // in util.c

    //
    // Get the mouse offset vector and the object size
    //

    GetObjectDescriptorPointAndSize(pData, &ptOff, &w, &h); // in util.c

    //
    // Create an OLE object from the source data
    //

    pObj = CreateObj(ptMouse.x - ptOff.x,
                     ptMouse.y - ptOff.y,
                     w,
                     h,
                     NULL,
                     pData,
                     NULL,
                     FROM_DATA);

    //
    // Add it to our internal object list and make it the 
    // currently selected object
    //

    AppendObj(pObj);
    SelectObj(pObj, TRUE);

    //
    // Draw the final embedded form
    //

    InvalidateRect(ghwndMain,
                   &(pObj->rc),
                   TRUE);


    //
    // Determine the effect of the drop
    //

    if (dwKeyState & MK_CONTROL) {
        *pdwEffect = DROPEFFECT_COPY;   // copy if Ctrl is down
    } else {
        *pdwEffect = DROPEFFECT_MOVE;   // else it's a move
    }

    return ResultFromScode(S_OK);
}

//
// Drop source interface method functions
//

STDMETHODIMP DropSource_QueryInterface(LPDROPSOURCE pThis,
                                  REFIID iid,
                                  LPVOID FAR* ppNew)
{
    PMYDOCINFO pDocInfo;

    dprintf2(">DropSource_QueryInterface");

    *ppNew = NULL;

    //
    // Cast the 'this' pointer and deref to get a pointer to our object struct
    //

    pDocInfo = ((struct _DocIDropSource FAR *)pThis)->pDocInfo;

    //
    // Test for the interfaces we support in our doc objects
    //

    if (IsEqualIID(iid, &IID_IDropSource)) {

        dprintf3(" DropSource");
        *ppNew = &(pDocInfo->DocIDropSource);

    } else {

        dprintf3(" unsupported interface requested");
        return ResultFromScode(E_NOINTERFACE);
    }

    //
    // Increment the reference count on the object since we
    // are returning a valid pointer to one of its interfaces
    //

    ((LPUNKNOWN)(*ppNew))->lpVtbl->AddRef(*ppNew);

    return NOERROR;
}

STDMETHODIMP_(ULONG) DropSource_AddRef(LPDROPSOURCE pThis)
{
    PMYDOCINFO pDocInfo;

    dprintf2(">DropSource_AddRef");
    pDocInfo = ((struct _DocIDropSource FAR *)pThis)->pDocInfo;
    (pDocInfo->lRef)++;
    dprintf2("MyDocAddRef --> %ld", pDocInfo->lRef);

    return pDocInfo->lRef;
}

STDMETHODIMP_(ULONG) DropSource_Release(LPDROPSOURCE pThis)
{
    PMYDOCINFO pDocInfo;
    LONG lReturn;

    dprintf2(">DropSource_Release");
    pDocInfo = ((struct _DocIDropSource FAR *)pThis)->pDocInfo;
    lReturn = --(pDocInfo->lRef);
    dprintf2("MyDocRelease --> %ld", pDocInfo->lRef);

    if (pDocInfo->lRef == 0) {
        dprintf3(" doc object ref count = 0");
    }

    return lReturn;
}

STDMETHODIMP DropSource_QueryContinueDrag(LPDROPSOURCE pThis,
                                          BOOL fEscapePressed,
                                          DWORD dwKeyState)
{
    //
    // If ESC key has been pressed just cancel
    //

    if (fEscapePressed) return ResultFromScode(DRAGDROP_S_CANCEL);

    //
    // If mouse left button is up, do the drop
    //

    if (!(dwKeyState & MK_LBUTTON)) {
        return ResultFromScode(DRAGDROP_S_DROP);
    }

    return NOERROR; // carry on
}

STDMETHODIMP DropSource_GiveFeedback(LPDROPSOURCE pThis,
                                     DWORD dwEffect)
{
    return ResultFromScode(DRAGDROP_S_USEDEFAULTCURSORS);
}

//
// Initialize the vtbls of the interfaces we support
//

BOOL InitInterfaces()
{
    //
    // Client site interface
    //

    MyClientSiteVtbl.QueryInterface = ClientSite_QueryInterface;
    MyClientSiteVtbl.AddRef = ClientSite_AddRef;
    MyClientSiteVtbl.Release = ClientSite_Release;

    MyClientSiteVtbl.SaveObject = ClientSite_SaveObject;
    MyClientSiteVtbl.GetMoniker = ClientSite_GetMoniker;
    MyClientSiteVtbl.GetContainer = ClientSite_GetContainer;
    MyClientSiteVtbl.ShowObject = ClientSite_ShowObject;
    MyClientSiteVtbl.OnShowWindow = ClientSite_OnShowWindow;
    MyClientSiteVtbl.RequestNewObjectLayout = ClientSite_RequestNewObjectLayout;

    //
    // Advise sink interface
    //

    MyAdviseSinkVtbl.QueryInterface = AdviseSink_QueryInterface;
    MyAdviseSinkVtbl.AddRef = AdviseSink_AddRef;
    MyAdviseSinkVtbl.Release = AdviseSink_Release;

    MyAdviseSinkVtbl.OnDataChange = AdviseSink_OnDataChange;
    MyAdviseSinkVtbl.OnViewChange = AdviseSink_OnViewChange;
    MyAdviseSinkVtbl.OnRename = AdviseSink_OnRename;
    MyAdviseSinkVtbl.OnSave = AdviseSink_OnSave;
    MyAdviseSinkVtbl.OnClose = AdviseSink_OnClose;

    //
    // Data object interface
    //

    MyDataObjectVtbl.QueryInterface = DataObject_QueryInterface;
    MyDataObjectVtbl.AddRef = DataObject_AddRef;
    MyDataObjectVtbl.Release = DataObject_Release;

    MyDataObjectVtbl.GetData = DataObject_GetData;
    MyDataObjectVtbl.GetDataHere = DataObject_GetDataHere;
    MyDataObjectVtbl.QueryGetData = DataObject_QueryGetData;
    MyDataObjectVtbl.GetCanonicalFormatEtc = DataObject_GetCanonicalFormatEtc;
    MyDataObjectVtbl.SetData = DataObject_SetData;
    MyDataObjectVtbl.EnumFormatEtc = DataObject_EnumFormatEtc;
    MyDataObjectVtbl.DAdvise = DataObject_DAdvise;
    MyDataObjectVtbl.DUnadvise = DataObject_DUnadvise;
    MyDataObjectVtbl.EnumDAdvise = DataObject_EnumDAdvise;

    //
    // Drop target interface
    //

    MyDropTargetVtbl.QueryInterface = DropTarget_QueryInterface;
    MyDropTargetVtbl.AddRef = DropTarget_AddRef;
    MyDropTargetVtbl.Release = DropTarget_Release;

    MyDropTargetVtbl.DragEnter = DropTarget_DragEnter;
    MyDropTargetVtbl.DragOver = DropTarget_DragOver;
    MyDropTargetVtbl.DragLeave = DropTarget_DragLeave;
    MyDropTargetVtbl.Drop = DropTarget_Drop;

    MyDropSourceVtbl.QueryInterface = DropSource_QueryInterface;
    MyDropSourceVtbl.AddRef = DropSource_AddRef;
    MyDropSourceVtbl.Release = DropSource_Release;

    MyDropSourceVtbl.QueryContinueDrag = DropSource_QueryContinueDrag;
    MyDropSourceVtbl.GiveFeedback = DropSource_GiveFeedback;

    //
    // Set up the various pointers and so on in the DOCINFO
    // object which is global
    //

    gDocInfo.lRef = 1;
    gDocInfo.DocIDropTarget.lpVtbl = &MyDropTargetVtbl;
    gDocInfo.DocIDropTarget.pDocInfo = &gDocInfo;
    gDocInfo.DocIDropSource.lpVtbl = &MyDropSourceVtbl;
    gDocInfo.DocIDropSource.pDocInfo = &gDocInfo;


    return TRUE;
}
