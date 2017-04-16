// COPYRIGHT:
//
//   (C) Copyright Microsoft Corp. 1993.  All rights reserved.
//
//   You have a royalty-free right to use, modify, reproduce and
//   distribute the Sample Files (and/or any modified version) in
//   any way you find useful, provided that you agree that
//   Microsoft has no warranty obligations or liability for any
//   Sample Application Files which are modified.
//
/*
    This module contains all the DDE Execute functions
    supported by this server.

    Drawing functions are:

    Pen(RED|BLUE|GREEN|BLACK|WHITE|YELLOW|CYAN|MAGENTA)
    Brush(RED|BLUE|GREEN|BLACK|WHITE|YELLOW|CYAN|MAGENTA)
    Line(left,top,right,bottom)
    Ellipse(left,top,right,bottom)
    Rectangle(left,top,right,bottom)
    Erase()
    Text(x,y,text)

*/

#include "ddeexec.h"

//
// local data 
//

static HPEN hpenCurrent;
static HBRUSH hbrCurrent;
static HPEN hpenOld;
static HBRUSH hbrOld;
static COLORREF rgbBrush;
static COLORREF rgbPen;

//
// local functions
//

static BOOL GetRectangle(LPSTR pszError, UINT uiErrorSize, UINT uiNargs, LPSTR FAR *ppArgs, LPRECT pRect);
static BOOL GetColor(LPSTR pszError, UINT uiErrorSize, UINT uiNargs, LPSTR FAR *ppArgs, COLORREF *pColor);
static void SetTools(HDC hDC);
static void RestoreTools(HDC hDC);
static void SetPenColor(COLORREF rgb);
static void SetBrushColor(COLORREF rgb);

//
// Pen(color)
//

BOOL FAR PenFn(PDDETOPICINFO pTopic,
				 LPSTR pszResult,
				 UINT uiResultSize,
				 UINT uiNargs,
				 LPSTR FAR *ppArgs)
{
    COLORREF color;

    Status("Pen: %s", ppArgs[0]);

    if (!GetColor(pszResult, uiResultSize, uiNargs, ppArgs, &color)) {
        return FALSE;
    }

    SetPenColor(color);

    return TRUE;
}

//
// Brush(color)
//

BOOL FAR BrushFn(PDDETOPICINFO pTopic,
				 LPSTR pszResult,
				 UINT uiResultSize,
				 UINT uiNargs,
				 LPSTR FAR *ppArgs)
{
    COLORREF color;

    Status("Brush: %s", ppArgs[0]);

    if (!GetColor(pszResult, uiResultSize, uiNargs, ppArgs, &color)) {
        return FALSE;
    }

    SetBrushColor(color);

    return TRUE;
}

//
// Ellipse(left,top,right,bottom)
//

BOOL FAR EllipseFn(PDDETOPICINFO pTopic,
				 LPSTR pszResult,
				 UINT uiResultSize,
				 UINT uiNargs,
				 LPSTR FAR *ppArgs)
{
    HDC hDC;
    RECT rc;

    //
    // Get the co-ordinates
    //

    if (!GetRectangle(pszResult, uiResultSize, uiNargs, ppArgs, &rc)) {
        return FALSE;
    }

    Status("Ellipse(%d,%d,%d,%d)", rc.left, rc.top, rc.right, rc.bottom);

    hDC = GetDC(hwndMain);

    SetTools(hDC);
    Ellipse(hDC, rc.left, rc.top, rc.right, rc.bottom);
    RestoreTools(hDC);

    ReleaseDC(hwndMain, hDC);

    return TRUE;
}

//
// Rectangle(left,top,right,bottom)
//

BOOL FAR RectangleFn(PDDETOPICINFO pTopic,
				 LPSTR pszResult,
				 UINT uiResultSize,
				 UINT uiNargs,
				 LPSTR FAR *ppArgs)
{
    HDC hDC;
    RECT rc;

    //
    // Get the co-ordinates
    //

    if (!GetRectangle(pszResult, uiResultSize, uiNargs, ppArgs, &rc)) {
        return FALSE;
    }

    Status("Rectangle(%d,%d,%d,%d)", rc.left, rc.top, rc.right, rc.bottom);

    hDC = GetDC(hwndMain);

    SetTools(hDC);
    Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom);
    RestoreTools(hDC);

    ReleaseDC(hwndMain, hDC);

    return TRUE;
}

//
// Line(left,top,right,bottom)
//

BOOL FAR LineFn(PDDETOPICINFO pTopic,
				 LPSTR pszResult,
				 UINT uiResultSize,
				 UINT uiNargs,
				 LPSTR FAR *ppArgs)
{
    HDC hDC;
    RECT rc;

    //
    // Get the co-ordinates
    //

    if (!GetRectangle(pszResult, uiResultSize, uiNargs, ppArgs, &rc)) {
        return FALSE;
    }

    Status("Line(%d,%d,%d,%d)", rc.left, rc.top, rc.right, rc.bottom);

    hDC = GetDC(hwndMain);

    SetTools(hDC);
    MoveTo(hDC, rc.left, rc.top);
    LineTo(hDC, rc.right, rc.bottom);
    RestoreTools(hDC);

    ReleaseDC(hwndMain, hDC);

    return TRUE;
}

//
// Erase()
//

BOOL FAR EraseFn(PDDETOPICINFO pTopic,
				 LPSTR pszResult,
				 UINT uiResultSize,
				 UINT uiNargs,
				 LPSTR FAR *ppArgs)
{

    Status("Erase()");

    SetPenColor(RGB(0,0,0));
    SetBrushColor(RGB(255,255,255));
    InvalidateRect(hwndMain, NULL, TRUE);

    return TRUE;
}

//
// Text(left,top,text)
//

BOOL FAR TextFn(PDDETOPICINFO pTopic,
				 LPSTR pszResult,
				 UINT uiResultSize,
				 UINT uiNargs,
				 LPSTR FAR *ppArgs)
{
    HDC hDC;
    int x, y;
    char buf[32];

    //
    // Get the co-ordinates
    //

    _fstrncpy(buf, ppArgs[0], sizeof(buf)-1);
    x = atoi(buf);
    _fstrncpy(buf, ppArgs[1], sizeof(buf)-1);
    y = atoi(buf);

    hDC = GetDC(hwndMain);

    SetTools(hDC);
    TextOut(hDC, x, y, ppArgs[2], _fstrlen(ppArgs[2]));
    RestoreTools(hDC);

    ReleaseDC(hwndMain, hDC);

    Status("Text(%d,%d,%s)", x, y, ppArgs[2]);

    return TRUE;
}

//
// Get rectangle co-ordinates
//

static BOOL GetRectangle(LPSTR pszError,
				 UINT uiErrorSize,
				 UINT uiNargs,
				 LPSTR FAR *ppArgs,
				 LPRECT pRect)
{
    char buf[32];

    if (uiNargs != 4) {
        _fstrncpy(pszError,
                  "Need 4 args",
                  uiErrorSize-1);
        return FALSE;
    }

    _fstrncpy(buf, ppArgs[0], sizeof(buf)-1);
    pRect->left = atoi(buf);

    _fstrncpy(buf, ppArgs[1], sizeof(buf)-1);
    pRect->top = atoi(buf);

    _fstrncpy(buf, ppArgs[2], sizeof(buf)-1);
    pRect->right = atoi(buf);

    _fstrncpy(buf, ppArgs[3], sizeof(buf)-1);
    pRect->bottom = atoi(buf);

    return TRUE;
}

//
// Select the drawing tools to use
//

static void SetTools(HDC hDC)
{
    if (!hpenCurrent) {
        rgbPen = RGB(0,0,0);
        hpenCurrent = CreatePen(PS_SOLID, 1, rgbPen);
    }
    hpenOld = SelectObject(hDC, hpenCurrent);
    SetTextColor(hDC, rgbPen);

    if (!hbrCurrent) {
        rgbBrush = RGB(128,128,128);
        hbrCurrent = CreateSolidBrush(rgbBrush);
    }
    hbrOld = SelectObject(hDC, hbrCurrent);
    SetBkColor(hDC, rgbBrush);
}

//
// Restore the tools
//

static void RestoreTools(HDC hDC)
{
    SelectObject(hDC, hpenOld);
    SelectObject(hDC, hbrOld);
}

//
// Get a color argument
//

static BOOL GetColor(LPSTR pszError,
				 UINT uiErrorSize,
				 UINT uiNargs,
				 LPSTR FAR *ppArgs,
				 COLORREF *pColor)
{
    if (uiNargs != 1) {
        Status("Invalid number of args");
        _fstrncpy(pszError,
                  "Need 1 args",
                  uiErrorSize-1);
        return FALSE;
    }

    if (_fstricmp(ppArgs[0], "RED") == 0) {
        *pColor = RGB(255,0,0);
    } else if (_fstricmp(ppArgs[0], "GREEN") == 0) {
        *pColor = RGB(0,255,0);
    } else if (_fstricmp(ppArgs[0], "BLUE") == 0) {
        *pColor = RGB(0,0,255);
    } else if (_fstricmp(ppArgs[0], "BLACK") == 0) {
        *pColor = RGB(0,0,0);
    } else if (_fstricmp(ppArgs[0], "WHITE") == 0) {
        *pColor = RGB(255,255,255);
    } else if (_fstricmp(ppArgs[0], "GRAY") == 0) {
        *pColor = RGB(127,127,127);
    } else if (_fstricmp(ppArgs[0], "CYAN") == 0) {
        *pColor = RGB(0,255,255);
    } else if (_fstricmp(ppArgs[0], "YELLOW") == 0) {
        *pColor = RGB(255,255,0);
    } else if (_fstricmp(ppArgs[0], "MAGENTA") == 0) {
        *pColor = RGB(255,0,255);
    } else {
        Status("Invalid color");
        _fstrncpy(pszError,
                  "Invalid color",
                  uiErrorSize-1);
        return FALSE;
    }

    return TRUE;
}

//
// Set the current pen
//

static void SetPenColor(COLORREF color)
{
    if (hpenCurrent) {
        DeleteObject(hpenCurrent);
    }
    hpenCurrent = CreatePen(PS_SOLID, 1, color);
    rgbPen = color;
}

//
// Set the current brush
//

static void SetBrushColor(COLORREF color)
{
    if (hbrCurrent) {
        DeleteObject(hbrCurrent);
    }
    hbrCurrent = CreateSolidBrush(color);
    rgbBrush = color;
}
