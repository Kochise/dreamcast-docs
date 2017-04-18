#ifndef _INC_CLIENT
#define _INC_CLIENT

BOOL GLOBAL Client_Initialize(APP* papp);
void GLOBAL Client_Terminate(APP* papp);

LRESULT ENTRY Client_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

HWND GLOBAL Client_CreateWindow(HWND hwndParent, int x, int y, int cx, int cy);

void GLOBAL Client_OnDestroy(HWND hwnd);

BOOL GLOBAL Client_OnEraseBkgnd(HWND hwnd, HDC hdc);

BOOL GLOBAL Client_OnQueryEndSession(HWND hwnd);
void GLOBAL Client_OnEndSession(HWND hwnd, BOOL fEnding);

#endif  // !_INC_CLIENT
