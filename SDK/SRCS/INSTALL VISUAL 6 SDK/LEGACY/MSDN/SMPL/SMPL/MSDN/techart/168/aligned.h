/*
 * Menu identifiers.
 */

#define IDM_ALIGNMENTLEFT1    100
#define IDM_ALIGNMENTCENTER1  101
#define IDM_ALIGNMENTRIGHT1   102

#define IDM_EXIT              105

#define IDM_ALIGNMENTLEFT2    200
#define IDM_ALIGNMENTCENTER2  201
#define IDM_ALIGNMENTRIGHT2   202



/*
 * Function prototypes.
 */

HANDLE   HLoadAppStrings(void);
long	 FAR PASCAL EditAlignWndProc(HWND, UINT, WPARAM, LPARAM);
