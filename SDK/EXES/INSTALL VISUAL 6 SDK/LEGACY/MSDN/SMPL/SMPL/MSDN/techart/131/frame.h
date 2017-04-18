#ifndef _INC_FRAME
#define _INC_FRAME

// Frame message handler declarations

//-------------------------------------------------------------------------
// UNPACKED FUNCTIONS BELOW
#pragma pack(2)	// Use default packing

typedef struct tagFRAME
{
    HWND hwnd;
    HWND hwndClient;
} FRAME;

typedef FRAME NEAR * PTRFRAME;
#pragma pack()	//Revert to packing specified on command line
//--------------------------------------------------------------

LRESULT ENTRY Frame_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL GLOBAL Frame_Initialize(APP* papp);
void GLOBAL Frame_Terminate(APP* papp);

HWND GLOBAL Frame_CreateWindow( LPCSTR lpszText,
										 int x, int y, int cx, int cy, HINSTANCE hinst);

#endif  // !_INC_FRAME
