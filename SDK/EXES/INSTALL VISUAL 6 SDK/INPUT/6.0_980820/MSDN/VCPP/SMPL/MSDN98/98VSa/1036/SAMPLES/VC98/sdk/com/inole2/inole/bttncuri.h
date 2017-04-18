/*
 * BTTNCURI.H
 * Buttons & Cursors
 *
 * Private include file for the Button Images and Cursors DLL.
 *
 * Copyright (c)1992-1995 Microsoft Corporation, All Right Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */

#ifndef _BTTNCURI_H_
#define _BTTNCURI_H_


#ifdef __cplusplus
extern "C"
    {
#endif

//Function prototypes.

//BTTNCUR.C
BOOL     ToolButtonInit(HINSTANCE);
void     ToolButtonFree(void);
HBRUSH   HBrushDitherCreate(COLORREF, COLORREF);
void     DrawBlankButton(HDC, int, int, int, int, BOOL, COLORREF *);

void     PatB(HDC, int, int, int, int, COLORREF);
void     MaskCreate(UINT, int, int, int, int, int, int, UINT);


//CURSORS.C
void        CursorsCache(HINSTANCE);
void        CursorsFree(void);


#define ROP_DSPDxax  0x00E20746
#define ROP_PSDPxax  0x00B8074A


/*
 * Color indices into an array of standard hard-coded black, white,
 * and gray colors.
 */

#define STDCOLOR_BLACK      0
#define STDCOLOR_DKGRAY     1
#define STDCOLOR_LTGRAY     2
#define STDCOLOR_WHITE      3

/*
 * Color indices into an array of system colors, matching those in
 * the hard-coded array for the colors they replace.
 */

#define SYSCOLOR_TEXT       0
#define SYSCOLOR_SHADOW     1
#define SYSCOLOR_FACE       2
#define SYSCOLOR_HILIGHT    3


/*
 * Button types, used internally to distinguish command buttons from
 * attribute buttons to enforce three-state or six-state
 * possibilities.  Command buttons can only have three states (up,
 * mouse down, disabled) while attribute buttons add (down, down
 * disabled, and indeterminate).
 */

#define BUTTONTYPE_COMMAND      0
#define BUTTONTYPE_ATTRIBUTE    1


#ifdef __cplusplus
    }
#endif

#endif //_BTTNCURI_H_
