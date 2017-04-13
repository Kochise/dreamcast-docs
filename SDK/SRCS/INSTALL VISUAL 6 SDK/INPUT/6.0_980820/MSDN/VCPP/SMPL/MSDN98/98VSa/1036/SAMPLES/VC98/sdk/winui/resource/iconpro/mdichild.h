/****************************************************************************\
*			 
*     FILE:     MDIChild.H
*
*     PURPOSE:  IconPro Project MDI Child Window handling header file
*
*     COMMENTS: One CHILDWINDOWDATA struct defined below is attached
*               to each MDI child window. It stores information about
*               the listbox, the locations of drawing objects, and the
*               icon resource associated with each window.
*
*     Copyright 1995 - 1997 Microsoft Corp.
*
*
* History:
*                July '95 - Created
*
\****************************************************************************/


/****************************************************************************/
// local #defines

// The ID for the listbox child window
#define ID_FORMAT_BOX		102       
/****************************************************************************/


/****************************************************************************/
// Local structs

// This struct is used to hold the data associated with an MDI window
typedef struct 
{
	HWND			hWndFormatListBox;        // Window Handle for listbox
	LPICONRESOURCE	lpIR;                     // pointer to icon resource
	RECT			BoxRect;                  // ListBox Window Rect
	RECT			DrawingRect;              // Overall rect to draw in
	RECT			BlackRect, BlackTextRect; // for black bkgrnd & text
	RECT			WhiteRect, WhiteTextRect; // for white bkgrnd & text
	RECT			XORRect, XORTextRect;     // for XOR mask & text
	RECT			ANDRect, ANDTextRect;     // for AND mask & text
	RECT			XORImageRect;             // in which to draw OR mask
} CHILDWINDOWDATA, *LPCHILDWINDOWDATA;
/****************************************************************************/



/****************************************************************************/
// Exported function prototypes
LRESULT CALLBACK IconChildWndProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
/****************************************************************************/
