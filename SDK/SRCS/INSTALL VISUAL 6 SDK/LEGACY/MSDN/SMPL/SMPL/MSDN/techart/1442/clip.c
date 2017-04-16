/*
    clip.c

    Clipboard support

    This does copy and paste operations on the block of data
    addressed by pFileData and dwFileLength.

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
    } else {
        EnableMenuItem(hmenuPopup, IDM_CUT, MF_GRAYED);
        EnableMenuItem(hmenuPopup, IDM_COPY, MF_GRAYED);
    }

    //
    // See if there is anything in the Clipboard which
    // we are capably of pasting
    //

    if ((IsClipboardFormatAvailable(CF_TEXT))
    ||  (IsClipboardFormatAvailable(gcfTextBoxObject))) {

        //
        // native format
        //

        ModifyMenu(hmenuPopup, IDM_PASTE, MF_BYCOMMAND, IDM_PASTE, "&Paste");
        EnableMenuItem(hmenuPopup, IDM_PASTE, MF_ENABLED);

    // else if OLE format....

    } else {

        //
        // Nothing available so gray it out
        //

        ModifyMenu(hmenuPopup, IDM_PASTE, MF_BYCOMMAND, IDM_PASTE, "&Paste");
        EnableMenuItem(hmenuPopup, IDM_PASTE, MF_GRAYED);

    }
}

//
// Create a CF_TEXT Clipboard object from our data
//

static HANDLE CreateCFTEXTObject(POBJECT pObj)
{
    HANDLE hData;
    LPSTR pData = NULL;

    //
    // Allocate the memory block
    //

    hData = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT,
                        pObj->uiSize);
    if (!hData) {
        Message(0,"Out of memory");
        return NULL;
    }

    pData = GlobalLock(hData);
    _fmemcpy(pData, pObj->pInfo, pObj->uiSize);
    GlobalUnlock(hData);
    return hData;
}

//
// Create a CF_TEXTBOXOBJECT Clipboard object from our data
// This is an OBJECT struct with the data packed right after it
//

static HANDLE CreateCFTextBoxObject(POBJECT pObj)
{
    HANDLE hData;
    LPSTR pData = NULL;

    //
    // Allocate the memory block
    //

    hData = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT,
                        pObj->uiSize+sizeof(OBJECT));
    if (!hData) {
        Message(0,"Out of memory");
        return NULL;
    }

    pData = GlobalLock(hData);
    _fmemcpy(pData, pObj, sizeof(OBJECT));
    _fmemcpy(pData+sizeof(OBJECT), pObj->pInfo, pObj->uiSize);
    GlobalUnlock(hData);
    return hData;
}

//
// Process a clipboard command
//

void ClipCommand(HWND hWnd, WPARAM wParam)
{
    HANDLE hData;
    LPSTR pData = NULL;
    UINT uiSize;
    POBJECT pObj, pCFObj;
    UINT uiFmt;

    switch (wParam) {
    case IDM_COPY:
    case IDM_CUT:

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

        OpenClipboard(hWnd);
        EmptyClipboard();

        hData = CreateCFTextBoxObject(pObj);
        if (!hData) {
            Message(0, "Unable to create Herman Clipboard object");
        } else {
            SetClipboardData(gcfTextBoxObject, hData);
            dprintf2("Copied %u bytes", pObj->uiSize);
        }
        hData = CreateCFTEXTObject(pObj);
        if (!hData) {
            Message(0, "Unable to create Text Clipboard object");
        } else {
            SetClipboardData(CF_TEXT, hData);
            dprintf2("Copied %u bytes", pObj->uiSize);
        }
        CloseClipboard();

        //
        // If the operation was CUT, delete the object and redraw
        //

        if (wParam == IDM_CUT) {
            DeleteObj(pObj);
            InvalidateRect(ghwndMain, NULL, TRUE);
        }

        break;

    case IDM_PASTE:

        OpenClipboard(hWnd);

        //
        // See if we can find a clipboard format we like
        // Start with our own private format, then OLE formats
        // then junko formats like CF_TEXT.
        //

        uiFmt = gcfTextBoxObject;
        hData = GetClipboardData(uiFmt);
        if (!hData) {
            uiFmt = CF_TEXT;
            hData = GetClipboardData(uiFmt);
        }

        if (hData) {
            pData = GlobalLock(hData);
        }
        if (pData) {
            pObj = NULL;

            if (uiFmt == gcfTextBoxObject) {

                dprintf3("Using private format");
                pCFObj = (POBJECT) pData;
                pObj = CreateObj(gptInsert.x,
                                 gptInsert.y,
                                 pCFObj->rc.right - pCFObj->rc.left,
                                 pCFObj->rc.bottom - pCFObj->rc.top,
                                 CF_TEXT, // as far as rendering it is concerned
                                 pCFObj->uiSize,
                                 (LPVOID)(((LPSTR)(pCFObj))+sizeof(OBJECT)));

            } else if (uiFmt == CF_TEXT) {

                dprintf3("Using CF_TEXT format");
                uiSize = (UINT) GlobalSize(hData);
                pObj = CreateObj(gptInsert.x,
                                 gptInsert.y,
                                 DEFAULT_OBJ_WIDTH,
                                 DEFAULT_OBJ_HEIGHT,
                                 CF_TEXT,
                                 uiSize,
                                 (LPVOID)pData);
            }

            if (pObj) {
                dprintf2("Pasted %u bytes", pObj->uiSize);
                AppendObj(pObj); // add to top of list
                InvalidateRect(ghwndMain, NULL, TRUE); // repaint
            }
            GlobalUnlock(hData);
        } else {
            Message(0,"Failed to get Clipboard data");
        }

        CloseClipboard();
        break;

    default:
        break;
    }
}
