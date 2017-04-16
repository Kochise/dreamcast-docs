#include <windows.h>
#include <stdlib.h>
#include "w32pen.h"

void PASCAL HandlePopupMenu(HWND hwnd, POINT point)
{
    HMENU hMenu;
    HMENU hMenuTrackPopup;

    /* Get the menu for the pop-up menu from the resource file. */


    hMenu = LoadMenu(hInst, "HITMENU");
    if (!hMenu)
        return;

    /*
     * Get the first menu in the pop-up menu to use in the call
     * to TrackPopupMenu. This could also have been created by
     * using CreatePopupMenu and then added by using InsertMenu
     * or AppendMenu.
     */

    hMenuTrackPopup = GetSubMenu(hMenu, 0);

    /*
     * Convert the mouse point to screen coordinates, because that

     * is what TrackPopup expects.
     */

    ClientToScreen(hwnd, (LPPOINT)&point);

    /* Draw and track the "floating" pop-up menu. */

    TrackPopupMenu(hMenuTrackPopup, 0, point.x, point.y, 0, hwnd, NULL);

    DestroyMenu(hMenu);
}
