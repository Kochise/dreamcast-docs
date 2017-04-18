/*
    object.c

    Object functions

*/

#include "global.h"

//
// Create a new object
//

POBJECT CreateObj(int x, int y, int w, int h, 
                  UINT uiType, UINT uiSize, LPVOID pData)
{
    POBJECT pObj;

    pObj = (POBJECT) ALLOCATE(sizeof(OBJECT) + uiSize);
    if (!pObj) {
        dprintf1("Out of memory allocating object");
        return NULL;
    }

    pObj->pNext = NULL;
    pObj->rc.left = x;
    pObj->rc.top = y;
    pObj->rc.right = x + w;
    pObj->rc.bottom = y + h;
    pObj->bSelected = FALSE;
    pObj->uiSize = uiSize;
    pObj->pInfo = (((LPBYTE)pObj) + sizeof(OBJECT));
    pObj->uiType = uiType;
    _fmemcpy(pObj->pInfo, pData, uiSize);

    return pObj;
}

//
// Delete an object
//

void DeleteObj(POBJECT pObj)
{
    if (!pObj) return;

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
    RECT rc;

    //
    // Put a border round it so we can see where it is
    // If it's selected, make the border red
    //

    if (pObj->bSelected) {
        hpenRed = CreatePen(PS_SOLID, 2, RGB(255,0,0));
        hpenOld = SelectObject(hDC, hpenRed);
    }

    Rectangle(hDC, 
              pObj->rc.left, pObj->rc.top,
              pObj->rc.right, pObj->rc.bottom);

    if (hpenOld) SelectObject(hDC, hpenOld);
    if (hpenRed) DeleteObject(hpenRed);

    switch (pObj->uiType) {
    case CF_TEXT:
        rc = pObj->rc;
        InflateRect(&rc, -1, -1);
        DrawText(hDC, 
                 (LPSTR)(pObj->pInfo), 
                 -1,
                 &rc,
                 DT_WORDBREAK);
        break;

    default:
        dprintf1("Unsupported CF");
        break;
    }
}

//
// Process the edit menu insert object command
//

void InsertObjCmd(HWND hWnd)
{
    char szFileName[_MAX_PATH];
    static char *szInsertObjFilter = "Text Files (*.txt)\0*.txt\0"
                                     "\0";
    FILE *fp;
    char buf[1024];
    POBJECT pObj;

    //
    // Just for now, we'll try to open a text file
    // and pull the info from that.
    //

    szFileName[0] = '\0';
    if (!PromptForFileName(hWnd, 
                           ghAppInstance, 
                           szFileName,
                           sizeof(szFileName), 
                           "Insert Object", 
                           szInsertObjFilter,
                           "txt",
                           PFFN_OPENFILE | PFFN_UPPERCASE)) {
        return;
    }

    //
    // Open the file and read the first line of text from it
    //

    fp = fopen(szFileName, "r");
    fgets(buf, sizeof(buf)-1, fp);
    fclose(fp);
    if (buf[lstrlen(buf)-1] == '\n') {
        buf[lstrlen(buf)-1] = '\0';
    }

    //
    // Create a new object to hold the info
    //

    pObj = CreateObj(gptInsert.x,
                     gptInsert.y,
                     DEFAULT_OBJ_WIDTH,
                     DEFAULT_OBJ_HEIGHT,
                     CF_TEXT,
                     lstrlen(buf)+1,
                     buf);
    if (!pObj) {
        dprintf1("Failed to create new object");
        return;
    }

    //
    // Add it to the list
    //

    AppendObj(pObj);

    //
    // Repaint to show it
    //

    InvalidateRect(hWnd, NULL, TRUE); // BUGBUG use clip rect here

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
