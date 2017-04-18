/*
    sprite.c

    Sprite specific routines

*/

#include "global.h"

//
// local data
//

PSPRITE pDlgSprite;


//
// Load a sprite
// If no path is given, show a dialog to allow selection of the DIB
//

PSPRITE LoadSprite(LPSTR pszPath, BOOL bRedraw)
{
    PSPRITE pSprite;
    RECT rc;

    dprintf2("LoadSprite()");

    //
    // Allocate memory for the SPRITE info
    //

    pSprite = (PSPRITE) ALLOCATE(sizeof(SPRITE));
    if (!pSprite) {
        dprintf1("No memory for sprite");
        return NULL;
    }

    //
    // Load the DIB image
    //

    pSprite->pDIB = LoadDIB(pszPath);
    if (!pSprite->pDIB) {
        goto $abort;
    }

    pSprite->width = (int) DIB_WIDTH(pSprite->pDIB);
    pSprite->height = (int) DIB_HEIGHT(pSprite->pDIB);
    pSprite->x = 0;
    pSprite->y = 0;
    pSprite->z = 0;
    pSprite->vx = 0;
    pSprite->vy = 0;
    pSprite->bSelectable = TRUE;
    pSprite->pNext = NULL;
    pSprite->pPrev = NULL;
    dprintf4("Sprite is %u by %u", pSprite->width, pSprite->height);

    //
    // Map the color table so that it matches the one in the
    // background DIB
    //

    ASSERT(pdibBkGnd);
    MapDIBColorTable(pSprite->pDIB, pdibBkGnd);

    //
    // get the index and color of the top left pixel
    //

    pSprite->bTopLeft = GetDIBPixelValue(pSprite->pDIB, 0, 0);
    pSprite->rgbTopLeft = GetDIBPixelColor(pSprite->pDIB, 0, 0);
    dprintf4("Sprite top left: %2.2XH, %8.8lXH", 
             pSprite->bTopLeft,
             pSprite->rgbTopLeft);

    //
    // Add it to the sprite list
    //

    if (pSpriteList) {
        pSpriteList->pPrev = pSprite;
        pSprite->pNext = pSpriteList;
    }
    pSpriteList = pSprite;

    //
    // Set the zorder somewhere in the middle
    //

    SetSpriteZOrder(pSprite, 50, NO_UPDATE);

    //
    // Redraw the sprite set
    //

    if (bRedraw != NO_UPDATE) {
        GetSpriteRect(pSprite, &rc);
        Redraw(&rc, UPDATE_SCREEN);
    }

    return pSprite;

$abort:
    if (pSprite) FREE(pSprite);


    return NULL;
}

//
// Delete a sprite
//

void DeleteSprite(PSPRITE pSprite)
{
    PSPRITE pPrev, pNext;

    pPrev = pSprite->pPrev;
    pNext = pSprite->pNext;

    DeleteDIB(pSprite->pDIB);

    if (pPrev) {
        pPrev->pNext = pNext;
    } else {
        pSpriteList = pNext;
    }
    if (pNext) {
        pNext->pPrev = pPrev;
    }

}

//
// Delete the current set of sprites
//

void DeleteSpriteList()
{
    PSPRITE pSprite, pNext;

    pSprite = pSpriteList;
    while (pSprite) {
        pNext = pSprite->pNext;
        DeleteSprite(pSprite);
        pSprite = pNext;
    }
    pSpriteList = NULL;
}

//
// Test for a mouse hit in a non-transparent bit of a sprite.
//

PSPRITE SpriteHitTest(int x, int y)
{
    PSPRITE pSprite;
    int dx, dy;

    pSprite = pSpriteList;
    while (pSprite) {

        //
        // Test if the click is inside the sprite rectangle
        //
    
        if ((x > pSprite->x) 
        && (x < pSprite->x + (int) pSprite->width)
        && (y > pSprite->y)
        && (y < pSprite->y + (int) pSprite->height)) {
    
            dprintf4("Hit is in sprite rect");
    
            //
            // See if this point is transparent by testing to
            // see if the pixel value is the same as the top
            // left corner value.  Note that top left of the
            // image is bottom left in the DIB.
            //
    
            dx = x - pSprite->x;
            dy = y - pSprite->y;
    
            if (GetDIBPixelValue(pSprite->pDIB, dx, dy) 
               != pSprite->bTopLeft) {
                break;
            }
        }

        pSprite = pSprite->pNext;
    }

    return pSprite;
}

//
// get the enclosing rectangle for a sprite
//

void GetSpriteRect(PSPRITE pSprite, LPRECT prcSprite)
{
    prcSprite->left = pSprite->x;
    prcSprite->right = pSprite->x + pSprite->width;
    prcSprite->top = pSprite->y;
    prcSprite->bottom = pSprite->y + pSprite->height;
}


//
// Set a new position for a sprite
//

void SetSpritePosition(PSPRITE pSprite, int x, int y, BOOL bUpdate)
{
    RECT rcOld, rcNew, rcChange;


    dprintf4("SetSpritePosition(%u,%u)", x, y);

    ASSERT(pSprite);

    //
    // Get the current sprite position
    //

    GetSpriteRect(pSprite, &rcOld);

    //
    // Update the position and get the new rectangle
    //

    pSprite->x = x;
    pSprite->y = y;
    GetSpriteRect(pSprite, &rcNew);

    //
    // Update the change rectangle to include the old and the new
    // positions of the sprite
    //

    CopyRect(&rcChange, &rcOld);
    UnionRect(&rcChange, &rcChange, &rcNew);

    //
    // Redraw the changes if required
    //

    if (bUpdate != NO_UPDATE) {
        Redraw(&rcChange, bUpdate);
    }
}

//
// Set a new z position for a sprite
//

void SetSpriteZOrder(PSPRITE pSprite, WORD z, BOOL bUpdate)
{
    RECT rcChange;
    PSPRITE pNew, pLast;

    dprintf4("SetSpriteZOrder(%u)", z);

    ASSERT(pSprite);
    ASSERT(pSpriteList);

    pSprite->z = z;

    //
    // Get the current sprite position
    //

    GetSpriteRect(pSprite, &rcChange);

    //
    // Unlink the sprite from the list
    //

    if (pSprite->pPrev) {
        pSprite->pPrev->pNext = pSprite->pNext;
    } else {
        pSpriteList = pSprite->pNext;
    }
    if (pSprite->pNext) {
        pSprite->pNext->pPrev = pSprite->pPrev;
    }
    pSprite->pNext = pSprite->pPrev = NULL;

    //
    // Walk down the list (from the top (front) until we find
    // a sprite with higher z order or the end of the list
    //

    pNew = pLast = pSpriteList;
    while (pNew) {
        if (pNew->z > pSprite->z) break;
        pLast = pNew;
        pNew = pNew->pNext;
    }

    if (!pNew) {

        //
        // There is no sprite further back than this so put
        // this one on the end
        //

        if (pLast) {
            pLast->pNext = pSprite;
        } else {
            pSpriteList = pSprite;
        }
        pSprite->pPrev = pLast;

    } else {

        //
        // pNew points the the one we want after this one
        // so insert the new sprite before it
        //

        if (pNew->pPrev) {
            pSprite->pNext = pNew;
            pSprite->pPrev = pNew->pPrev;
            pNew->pPrev->pNext = pSprite;
            pNew->pPrev = pSprite;
        } else {
            pSprite->pNext = pNew;
            pSpriteList = pSprite;
            pNew->pPrev = pSprite;
        }

    }

    //
    // Redraw the changes if required
    //

    if (bUpdate != NO_UPDATE) {
        Redraw(&rcChange, bUpdate);
    }
}

//
// Sprite dialog procedure
//

int CALLBACK SpriteDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_INITDIALOG:
        SetDlgItemInt(hDlg, IDDS_X, pDlgSprite->x, TRUE);
        SetDlgItemInt(hDlg, IDDS_Y, pDlgSprite->y, TRUE);
        SetDlgItemInt(hDlg, IDDS_W, pDlgSprite->width, TRUE);
        SetDlgItemInt(hDlg, IDDS_H, pDlgSprite->height, TRUE);
        SetDlgItemInt(hDlg, IDDS_VX, pDlgSprite->vx, TRUE);
        SetDlgItemInt(hDlg, IDDS_VY, pDlgSprite->vy, TRUE);
        SetDlgItemInt(hDlg, IDDS_Z, pDlgSprite->z, TRUE);
        CheckDlgButton(hDlg, IDDS_SEL, pDlgSprite->bSelectable);
        break;

    case WM_COMMAND:
        switch (wParam) {
        case IDOK:
            SetSpritePosition(pDlgSprite,
                              GetDlgItemInt(hDlg, IDDS_X, NULL, TRUE),
                              GetDlgItemInt(hDlg, IDDS_Y, NULL, TRUE),
                              NO_UPDATE);
            pDlgSprite->vx = GetDlgItemInt(hDlg, IDDS_VX, NULL, TRUE);
            pDlgSprite->vy = GetDlgItemInt(hDlg, IDDS_VY, NULL, TRUE);
            SetSpriteZOrder(pDlgSprite, 
                            GetDlgItemInt(hDlg, IDDS_Z, NULL, TRUE),
                            NO_UPDATE);
            pDlgSprite->bSelectable = IsDlgButtonChecked(hDlg, IDDS_SEL);
            Redraw(NULL, UPDATE_SCREEN);
            EndDialog(hDlg, TRUE);
            break;

        case IDCANCEL:
            EndDialog(hDlg, FALSE);
            break;

        default:
            break;
        }
        break;

    default:
        return FALSE; // say we didn't handle it
        break;
    }

    return TRUE; // say we handled it
}

//
// Show the sprite dialog box
//

void SpriteDialog(PSPRITE pSprite)
{
    FARPROC fpDlg;

    pDlgSprite = pSprite;
    fpDlg = MakeProcInstance((FARPROC)SpriteDlgProc, hAppInstance);
    DialogBox(hAppInstance, 
              MAKEINTRESOURCE(IDD_SPRITE), 
              hwndMain,
              (DLGPROC)fpDlg);
    FreeProcInstance(fpDlg);
}

//
// Test is a sprite is selectable
//

BOOL IsSpriteSelectable(PSPRITE pSprite)
{
    return pSprite->bSelectable;
}


