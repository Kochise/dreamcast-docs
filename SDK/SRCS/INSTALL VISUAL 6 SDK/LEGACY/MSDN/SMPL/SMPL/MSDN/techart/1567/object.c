/*
    object.c

    Object functions

*/

#include "global.h"

//
// Create a new object and its associated OLE object.
// This is a kind of do-all function which was evolved
// from lots of separate chunks of code which is why it's a bit messy.
// It can create a temporary object (for sending to the clipboard),
// an object from clipboard data or an object from file based data.
//

POBJECT CreateObj(int x, int y, int w, int h,
                  LPSTORAGE pStorage, LPDATAOBJECT pDataObj,
                  REFCLSID pClsid,
                  DWORD dwFlags)
{
    POBJECT pObj;
    HRESULT hResult;
    DWORD dwJunk;

    dprintf2("CreateObj");

    //
    // Allocate the memory for the structure
    //

    pObj = (POBJECT) ALLOCATE(sizeof(OBJECT));
    if (!pObj) {
        dprintf1("Out of memory allocating object");
        return NULL;
    }

    //
    // Set the default state of each field
    //

    pObj->dwMagic = OBJECT_MAGIC;
    pObj->lRef = 0;
    pObj->pNext = NULL;
    pObj->pOleObj = NULL;
    pObj->pStorage = NULL;
    pObj->szStorageName[0] = '\0';
    pObj->rc.left = x;
    pObj->rc.top = y;
    pObj->rc.right = x + w;
    pObj->rc.bottom = y + h;
    pObj->bSelected = FALSE;
    pObj->ObjIClientSite.lpVtbl = &MyClientSiteVtbl;
    pObj->ObjIClientSite.pObject = pObj;
    pObj->ObjIAdviseSink.lpVtbl = &MyAdviseSinkVtbl;
    pObj->ObjIAdviseSink.pObject = pObj;
    pObj->ObjIDataObject.lpVtbl = &MyDataObjectVtbl;
    pObj->ObjIDataObject.pObject = pObj;

    if (dwFlags & AS_TEMPORARY) {

        ASSERT(pStorage);  // the source

        //
        // Create a temporary storage object
        //

        hResult = StgCreateDocfile(NULL,
                                   STGM_READWRITE | STGM_SHARE_EXCLUSIVE
                                    | STGM_DIRECT | STGM_CREATE,
                                   NULL,
                                   &(pObj->pStorage));

        if (!MyTestOleResult(hResult)) {
            dprintf1("Failed to create temp. storage");
            DeleteObj(pObj);
            return NULL;
        }

        //
        // Copy the data 
        //

        hResult = pStorage->lpVtbl->CopyTo(pStorage,
                                           NULL,
                                           NULL,
                                           NULL,
                                           pObj->pStorage);
        if (!MyTestOleResult(hResult)) {
            dprintf1("Failed to copy object storage");
            DeleteObj(pObj);
            return NULL;
        }

        //
        // Create the new OLE object
        //

        ASSERT(pClsid);
        hResult = OleCreate(pClsid,
                            &IID_IOleObject,
                            OLERENDER_DRAW,     // let server chose format
                            NULL,               // no specific format
                            NULL,
                            pObj->pStorage,     // storage object
                            (LPVOID)&(pObj->pOleObj));

        if (!MyTestOleResult(hResult)) {
            dprintf1("Failed to create OLE object");
            DeleteObj(pObj);
            return NULL;
        }
    }

    if (dwFlags & FROM_STORAGE) {

        //
        // We use one of the OLE helper functions to perform
        // this particular piece of black magic.
        //
    
        hResult = OleLoad(pStorage,
                          &IID_IOleObject,
                          (LPOLECLIENTSITE)&(pObj->ObjIClientSite),
                          (LPVOID)&(pObj->pOleObj));
    
        if (!MyTestOleResult(hResult)) {
            Message(0, "Failed to load OLE object");
            DeleteObj(pObj);
            return NULL;
        }

        pObj->pStorage = pStorage;
    }

    if ((dwFlags & FROM_CLASSID) || (dwFlags & FROM_DATA)) {

        //
        // Create the storage object
        //

        char szStorageName[32];

        //
        // Invent a name for the storage object and create the storage
        //

        wsprintf(szStorageName, "OBJ%lu", gdwNextObject++);

        hResult = gpStorage->lpVtbl->CreateStorage(gpStorage,
                                              szStorageName,
                                              STGM_READWRITE | STGM_SHARE_EXCLUSIVE
                                               | STGM_DIRECT | STGM_CREATE,
                                              NULL,
                                              NULL,
                                              &(pObj->pStorage));

        if (!MyTestOleResult(hResult)) {
            Message(0, "Failed to create %s storage",
                    (LPSTR) szStorageName);
            DeleteObj(pObj);
            return NULL;
        }


        lstrcpy(pObj->szStorageName, szStorageName);

    }

    if (dwFlags & FROM_CLASSID) {


        hResult = OleCreate(pClsid,
                            &IID_IOleObject,
                            OLERENDER_DRAW,     // let server choose format
                            NULL,               // no specific format
                            (LPOLECLIENTSITE)&(pObj->ObjIClientSite),
                            pObj->pStorage,     // storage object
                            (LPVOID)&(pObj->pOleObj)); // where to put the result

        if (!MyTestOleResult(hResult)) {
            dprintf1("Failed to create OLE Object");
            DeleteObj(pObj);
            return NULL;
        }

    }

    if (dwFlags & FROM_DATA) {

        hResult = OleCreateFromData(pDataObj,
                            &IID_IOleObject,
                            OLERENDER_DRAW,     // let server choose format
                            NULL,               // no specific format
                            (LPOLECLIENTSITE)&(pObj->ObjIClientSite),
                            pObj->pStorage,     // storage object
                            (LPVOID)&(pObj->pOleObj)); // where to put the result

        if (!MyTestOleResult(hResult)) {
            dprintf1("Failed to create OLE Object");
            DeleteObj(pObj);
            return NULL;
        }

    }

    if (!(dwFlags & AS_TEMPORARY)) {

        //
        // Set up the notifications we require
        //

        pObj->pOleObj->lpVtbl->Advise(pObj->pOleObj,
                                      (LPADVISESINK)&(pObj->ObjIAdviseSink),
                                      &dwJunk);

        //
        // Call the hokey API which prevents ref count screw ups.
        //
    
        OleSetContainedObject((LPUNKNOWN)(pObj->pOleObj), TRUE);

        //
        // Set the names we want the host to use
        //

        pObj->pOleObj->lpVtbl->SetHostNames(pObj->pOleObj,
                                            gszAppName,
                                            gachFileName);
    }

    return pObj;
}

//
// Make a copy of an object
//

POBJECT CopyObj(POBJECT pObj)
{
    POBJECT pNewObj = NULL;
    CLSID clsid;

    dprintf2("CopyObj");

    pObj->pOleObj->lpVtbl->GetUserClassID(pObj->pOleObj, &clsid);
    pNewObj = CreateObj(pObj->rc.left,
                        pObj->rc.top,
                        pObj->rc.right - pObj->rc.left + 1,
                        pObj->rc.bottom - pObj->rc.top + 1,
                        pObj->pStorage,
                        NULL,
                        &clsid,
                        AS_TEMPORARY);

    if (!pNewObj) {
        return NULL;
    }

    return pNewObj;
}

//
// Delete an object
//

void DeleteObj(POBJECT pObj)
{
    dprintf2("DeleteObj");
    if (!pObj) return;

    //
    // Release the OLE object and its storage
    //

    if (pObj->pStorage) {
        dprintf3(" releasing storage");
        pObj->pStorage->lpVtbl->Release(pObj->pStorage);
    }
    if (pObj->pOleObj) {
        dprintf3(" closing OLE object");
        pObj->pOleObj->lpVtbl->Close(pObj->pOleObj, OLECLOSE_NOSAVE);
        dprintf3(" releasing OLE object");
        pObj->pOleObj->lpVtbl->Release(pObj->pOleObj);
    }
    if (pObj->lRef != 0) {
        dprintf1("WARNING: Obj ref count not zero (%lu)", pObj->lRef);
    }
    UnlinkObj(pObj); // remove from the list if it's in there
    FREE(pObj);
}

//
// Render an object
//

void RenderObj(HDC hDC, POBJECT pObj)
{
    HPEN hpenRed = NULL;
    HPEN hpenOld = NULL;
    LPOLEOBJECT pOleObj;
    LPVIEWOBJECT pViewObj;
    HRESULT hrErr = NOERROR;
    RECTL rclHim;

    //
    // If it's selected, draw a red border around it
    //

    if (pObj->bSelected) {
        hpenRed = CreatePen(PS_SOLID, 2, RGB(255,0,0));
        hpenOld = SelectObject(hDC, hpenRed);

        Rectangle(hDC, 
                  pObj->rc.left-1, pObj->rc.top-1,
                  pObj->rc.right+2, pObj->rc.bottom+2);

        SelectObject(hDC, hpenOld);
        DeleteObject(hpenRed);
    }

    pOleObj = pObj->pOleObj;

    //
    // Get a pointer to the IViewObject interface which all
    // objects are supposed to support.  
    //

    pViewObj = (LPVIEWOBJECT)OleStdQueryInterface(
	                (LPUNKNOWN) pOleObj,
                    &IID_IViewObject);
    ASSERT(pViewObj); // should always support this

    //
    // define the bounding rect
    //

    rclHim.top = pObj->rc.top;
    rclHim.left = pObj->rc.left;
    rclHim.bottom = pObj->rc.bottom;
    rclHim.right = pObj->rc.right;

    //
    // Invoke the Draw method
    //

    hrErr = pViewObj->lpVtbl->Draw(pViewObj, 
            DVASPECT_CONTENT, // draw content (for now)
            -1,
            NULL,
            NULL,
            NULL,
            hDC,
            &rclHim,
            &rclHim,
            NULL,
            0);
    
    //
    // If the object is open in a window, then shade the area
    // to make it obvious
    // 

    if (pObj->bObjOpenInWindow) {
        OleUIDrawShading(&(pObj->rc),
                         hDC,
                         OLEUI_SHADE_FULLRECT,
                         0);
    }

}

//
// Process the edit menu insert object command
//

void InsertObjCmd(HWND hWnd)
{
    OLEUIINSERTOBJECT io;
    char szFile[OLEUI_CCHPATHMAX];
    UINT uiRet;
    POBJECT pObj;

    dprintf2("InsertOleObj");

    //
    // Fill the info struct with zeroes and
    // fill in any fields we might need to.  Mostly this is
    // a case of copying the example source code.
    //

    _fmemset(&io, 0, sizeof(io));
    io.cbStruct = sizeof(io);
    io.dwFlags = IOF_SELECTCREATENEW | IOF_SHOWHELP;
    io.hWndOwner = hWnd;
    szFile[0] = '\0';
    io.lpszFile = szFile;
    io.cchFile = sizeof(szFile);

    //
    // Show the dialog
    //

    uiRet = OleUIInsertObject(&io);
    if (uiRet != OLEUI_OK) {
        if (uiRet != OLEUI_CANCEL) {
            Message(0, "Failed to invoke dialog. Err: %u", uiRet);
        }
        return;
    }

    //
    // Now we get to create an OLE object.  Oh joy, oh rapture
    // a *real* API call. I can hardly wait. It's only taken 4 days
    // to get this far.
    //

    dprintf3(" io.dwFlags = %8.8lXH", io.dwFlags);

    //
    // To make life a lot simpler here, we will begin by only
    // suporting requests to create a new embedded object.
    //

    if (io.dwFlags & IOF_SELECTCREATEFROMFILE) {
        Message(0, "File creation not supported yet");
        return;
    }

    if (io.dwFlags & IOF_CHECKLINK) {
        Message(0, "Linking to objects is not supported yet");
        return;
    }

    ASSERT(io.dwFlags & IOF_SELECTCREATENEW); // should only be this case left

    //
    // At this point, the book says to allocate the storage object,
    // initialize the container site and then call the appropriate
    // OLE fuction to create the object.
    // Lots of tricky stuff here. We'll try to get some form of render
    // cache that will allow us to have the image of the object drawn with
    // out having to launch the server app.  We use OLERENDER_DRAW to
    // allow the server to select the render format.
    //

    ASSERT(gpStorage);

    //
    // Create one of our own objects
    //

    pObj = CreateObj(gptInsert.x,
                     gptInsert.y,
                     DEFAULT_OBJ_WIDTH,
                     DEFAULT_OBJ_HEIGHT,
                     NULL,
                     NULL,
                     &(io.clsid),
                     FROM_CLASSID);

    if (!pObj) {
        dprintf1("Failed to create new list object");
        return;
    }

    //
    // Add it to the list
    //

    AppendObj(pObj);

    //
    // Invoke the server to allow the user to set the contents etc.
    //

    ActivateObj(pObj);

    //
    // Show the final embedded form
    //

    InvalidateRect(hWnd, &(pObj->rc), TRUE);
}


//
// Test for a hit in an object
// We want the last one that hits in the list since this
// is the one most in front
//

POBJECT HitTestObj(int x, int y)
{
    POBJECT pObj, pHitObj = NULL;
    POINT pt;

    pt.x = x;
    pt.y = y;
    pObj = gpObjList;
    while (pObj) {
        if (PtInRect(&(pObj->rc), pt)) {
            pHitObj = pObj;
        }
        pObj = pObj->pNext;
    }

    return pHitObj;
}

//
// Select an object
//

void SelectObj(POBJECT pObj, BOOL bDesel)
{
    POBJECT pO;

    pO = gpObjList;
    while (pO) {
        if (pO == pObj) {
            pO->bSelected = TRUE;
        } else {
            if (bDesel) {
                pO->bSelected = FALSE;
            }
        }
        pO = pO->pNext;
    }
}

//
// Bring an object to the top of the display (bottom of list)
//

void BringObjToTop(POBJECT pObj)
{
    //
    // Remove it from the list
    //

    UnlinkObj(pObj);

    //
    // Add it to the end of the list
    //

    AppendObj(pObj);
}

//
// Append an object to the end of the list
//

void AppendObj(POBJECT pObj)
{
    POBJECT pO;

    gfDirty = TRUE;
    if (!gpObjList) {
        gpObjList = pObj;
        return;
    }

    pO = gpObjList;
    while (pO->pNext) pO = pO->pNext;
    pO->pNext = pObj;
}

//
// Unlink an object from the list
//

void UnlinkObj(POBJECT pObj)
{
    POBJECT pPrev, pO;

    gfDirty = TRUE;
    pO = gpObjList;
    pPrev = NULL;

    while (pO) {
        if (pO == pObj) {
            if (pPrev) {
                pPrev->pNext = pO->pNext;
            } else {
                gpObjList = pO->pNext;
            }
            pObj->pNext = NULL;
            break;
        }
        pPrev = pO;
        pO = pO->pNext;
    }

}

//
// test for a hit in the size border
//

UINT SizeBorderHitTestObj(int x, int y)
{
    POBJECT pObj;

    pObj = HitTestObj(x, y);
    if (!pObj) return SB_HIT_NONE;

    if (!pObj->bSelected) return SB_HIT_NONE;

    if ((x > pObj->rc.left) && (x < pObj->rc.left + SB_WIDTH)) return SB_HIT_LEFT;
    if ((x < pObj->rc.right) && (x > pObj->rc.right - SB_WIDTH)) return SB_HIT_RIGHT;

    if ((y > pObj->rc.top) && (y < pObj->rc.top + SB_WIDTH)) return SB_HIT_TOP;
    if ((y < pObj->rc.bottom) && (y > pObj->rc.bottom - SB_WIDTH)) return SB_HIT_BOTTOM;

    return SB_HIT_NONE;
}

//
// Activate an object
//

BOOL ActivateObj(POBJECT pObj)
{
    HRESULT hResult;


    dprintf2("ActivateObj");

    //
    // Invoke the server to allow the user to set the contents etc.
    //

    ASSERT(pObj);
    ASSERT(pObj->pOleObj);


    hResult = pObj->pOleObj->lpVtbl->DoVerb(pObj->pOleObj,
                                      OLEIVERB_OPEN,
                                      NULL,
                                      (LPOLECLIENTSITE)&(pObj->ObjIClientSite),
                                      0,
                                      ghwndMain, // parent window
                                      &(pObj->rc));
    if (!MyTestOleResult(hResult)) {
        dprintf1("Failed to execute DoVerb (%8.8lXH)",
                 GetScode(hResult));
        return FALSE;
    }

    return TRUE;
}

//
// Get data for an object.  Note that if bHere is TRUE, the 
// storage has already been allocated.
//

BOOL GetObjData(POBJECT pObj, LPFORMATETC pFmt, LPSTGMEDIUM pMed, BOOL bHere)
{
    HGLOBAL hGlobal;
    LPSTR pData = NULL;
    POINTL pointl;
    HRESULT hResult;
    LPSTR pRet;

#ifdef DEBUG
    {
        char buf[256];
        if (pFmt->cfFormat >= CF_PRIVATEFIRST) {
            GetClipboardFormatName(pFmt->cfFormat, buf, sizeof(buf));
        } else {
            wsprintf(buf, "%4.4XH", pFmt->cfFormat);
        }
        dprintf2("GetObjData(%s)", (LPSTR)buf);
    }
#endif // DEBUG

    if (!bHere) {

        //
        // Set the default return param state
        //

        pMed->tymed = NULL;
        pMed->hGlobal = NULL;
        pMed->pUnkForRelease = NULL; // all punks should be locked up for life
    }

    //
    // See which format is being requested
    //

    if (pFmt->cfFormat == CF_TEXT) {

        //
        // See if it can be returned in some way we can handle
        //

        if (!(pFmt->tymed & TYMED_HGLOBAL)) {

            dprintf1("Can't return CF_TEXT in wierd format");
            return FALSE;
        }

        //
        // Since the object didn't respond to the request for text data
        // we should supply some sort of description here.  We can
        // ask the object for its user type name.
        //

        if (!bHere) {
            hGlobal = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT | GMEM_SHARE,
                                  1024); // nice big chunk
            if (!hGlobal) {
                Message(0, "Out of memory");
                return FALSE;
            }
        } else {
            hGlobal = pMed->hGlobal;
        }

        pData = GlobalLock(hGlobal);
        if (pData) {

            hResult = pObj->pOleObj->lpVtbl->GetUserType(pObj->pOleObj,
                                                         USERCLASSTYPE_FULL,
                                                         &pRet);
            if (!MyTestOleResult(hResult)) {

                dprintf1("Failed to get object user type");
                lstrcpy(pData, "Some OLE thing");

            } else {

                dprintf3(" User type: %s", pRet);
                lstrcpy(pData, pRet);

            }

            GlobalUnlock(hGlobal);

        } else {

            dprintf1("failed to lock hGlobal");

        }

        if (!bHere) {
            pMed->tymed = TYMED_HGLOBAL;
            pMed->hGlobal = hGlobal;
        }

        dprintf3(" returned CF_TEXT in hGlobal");
        return TRUE;

    } else if (pFmt->cfFormat == gcfObjectDescriptor) {

        //
        // See if it can be returned in some way we can handle
        //

        if (!(pFmt->tymed & TYMED_HGLOBAL)) {

            dprintf1("Can't return Object Descriptor in wierd format");
            return FALSE;
        }

        //
        // And now some magic from the olestd.c module in ole2ui
        // which will create an obejct descriptor for us.  Note that
        // we use NULL for the name which (apparently) results in the
        // object supplying that for us.
        //

        pointl.x = pointl.y = 0;

        if (!bHere) {

            //
            // Allocate memory for the return data and fill it in.
            //

            hGlobal = OleStdGetObjectDescriptorDataFromOleObject(pObj->pOleObj,
                                                             NULL,
                                                             DVASPECT_CONTENT,
                                                             pointl);
            if (!hGlobal) {
                dprintf3(" failed to get Object Descriptor from OLE object");
                return FALSE;
            }

        } else {

            //
            // The caller is providing the memory.  We can't handle
            // this because I can't find a suitable helper function
            // and I'm too lazy to do the work.  As it turns out
            // this isn't a problem
            //

            dprintf1("can't do 'here'");
            return FALSE;
        }

        if (!bHere) {
            pMed->tymed = TYMED_HGLOBAL;
            pMed->hGlobal = hGlobal;
        }

        dprintf3(" returned Object Descriptor in hGlobal");
        return TRUE;

    } else if (pFmt->cfFormat == gcfEmbeddedObject) {

        //
        // See if it can be returned in some way we can handle
        //

        if (!(pFmt->tymed & TYMED_ISTORAGE)) {

            dprintf1("Can't return Embedded Object in wierd format");
            return FALSE;
        }

        if (!bHere) {

            dprintf1("Arrgh, I don't want to create an ISTORAGE!");
            return FALSE;

        } else {

            //
            // Copy the istorage
            //

            hResult = pObj->pStorage->lpVtbl->CopyTo(pObj->pStorage,
                                                     NULL,
                                                     NULL,
                                                     NULL,
                                                     pMed->pstg);
            if (!MyTestOleResult(hResult)) return FALSE;

            dprintf3(" returned Embedded Object in ISTORAGE");
            return TRUE;
        }
    }

    dprintf3(" some unknown format");
    return FALSE;
}
