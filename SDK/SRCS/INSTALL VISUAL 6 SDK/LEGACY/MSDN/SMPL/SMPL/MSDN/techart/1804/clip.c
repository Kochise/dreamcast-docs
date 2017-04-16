/*
    clip.c

    Clipboard support

*/

#include "global.h"

//
// Set the state of the edit menu items
//

void InitClipMenu(HMENU hmenuPopup)
{
    POBJECT pO;
    BOOL bSel = FALSE;

    //
    // See if there is anything we have that we might want the
    // user to be able to copy to the clipboard
    //

    pO = gpObjList;
    while (pO) {
        if (pO->bSelected == TRUE) {
            bSel = TRUE;
            break;
        }
        pO = pO->pNext;
    }

    if (bSel) {
        EnableMenuItem(hmenuPopup, IDM_CUT, MF_ENABLED);
        EnableMenuItem(hmenuPopup, IDM_COPY, MF_ENABLED);
        EnableMenuItem(hmenuPopup, IDM_DELETE, MF_ENABLED);
    } else {
        EnableMenuItem(hmenuPopup, IDM_CUT, MF_GRAYED);
        EnableMenuItem(hmenuPopup, IDM_COPY, MF_GRAYED);
        EnableMenuItem(hmenuPopup, IDM_DELETE, MF_GRAYED);
    }

    //
    // See if there is anything in the Clipboard which
    // we are capable of pasting
    //

    if (IsClipboardFormatAvailable(gcfObjectDescriptor)) {
  
        //
        // OLE Object
        //
  
        ModifyMenu(hmenuPopup, IDM_PASTE, MF_BYCOMMAND, IDM_PASTE, "&Paste");
        EnableMenuItem(hmenuPopup, IDM_PASTE, MF_ENABLED);
  
   
    } else {
  
        //
        // Nothing available so gray it out
        //

        ModifyMenu(hmenuPopup, IDM_PASTE, MF_BYCOMMAND, IDM_PASTE, "&Paste");
        EnableMenuItem(hmenuPopup, IDM_PASTE, MF_GRAYED);

    }
}

//
// Process a clipboard command
//

void ClipCommand(HWND hWnd, WPARAM wParam)
{
    LPSTR pData = NULL;
    POBJECT pObj, pCFObj;
    LPDATAOBJECT pDataObj = NULL;
    HRESULT hResult;
    POINT ptOff;
    int w, h;

    switch (wParam) {
    case IDM_COPY:
    case IDM_CUT:

        dprintf2("Cut/Copy");

        //
        // Find the selected object
        // Note: we only support single selection
        // and the menu is only enabled if there is a selection
        //

        pObj = gpObjList;
        while (pObj) {
            if (pObj->bSelected) break;
            pObj = pObj->pNext;
        }
        ASSERT(pObj);

        //
        // Make a snapshot of the object here
        //

        pCFObj = CopyObj(pObj);
        if (!pCFObj) {
            Message(0, "Unable to copy object");
            return;
        }

        //
        // get access to the clipboard
        //

        pDataObj = NULL;
        hResult = OleGetClipboard(&pDataObj); // we don't care what it returns
        if (pDataObj) pDataObj->lpVtbl->Release(pDataObj);

        //
        // Get a pointer to the data object 
        //

        pDataObj = (LPDATAOBJECT) &(pCFObj->ObjIDataObject);

        //
        // Stuff it in the clipboard
        //

        hResult = OleSetClipboard(pDataObj);
        MyTestOleResult(hResult);

        //
        // If the operation was CUT, delete the original object and redraw
        //

        if (wParam == IDM_CUT) {
            DeleteObj(pObj);
            InvalidateRect(ghwndMain, NULL, TRUE);
        }

        break;

    case IDM_DELETE:

        dprintf2("Delete");

        pObj = gpObjList;
        while (pObj) {
            if (pObj->bSelected) break;
            pObj = pObj->pNext;
        }
        ASSERT(pObj);

        //
        // Delete the object and redraw
        //

        DeleteObj(pObj);
        InvalidateRect(ghwndMain, NULL, TRUE);
        break;

    case IDM_PASTE:

        dprintf2("Paste");

        //
        // Get the data object in the clipboard
        //

        pDataObj = NULL;
        hResult = OleGetClipboard(&pDataObj);

        if (!MyTestOleResult(hResult)) {

            dprintf1("failed to get data object from clipboard");
            return;
        }

        //
        // Get the mouse offset vector and the object size
        // We don't need the mouse offset here (it's for d&d)
        //

        GetObjectDescriptorPointAndSize(pDataObj, &ptOff, &w, &h); // in util.c

        //
        // Create an OLE object from the clipboard data
        //

        pObj = CreateObj(gptInsert.x,
                         gptInsert.y,
                         w,
                         h,
                         NULL,
                         pDataObj,
                         NULL,
                         FROM_DATA);

        //
        // Add it to our internal object list
        //

        AppendObj(pObj);
        SelectObj(pObj, TRUE);

        //
        // Draw the final embedded form
        //

        InvalidateRect(hWnd, 
                       &(pObj->rc),
                       TRUE);

        break;

    default:
        break;
    }
}
