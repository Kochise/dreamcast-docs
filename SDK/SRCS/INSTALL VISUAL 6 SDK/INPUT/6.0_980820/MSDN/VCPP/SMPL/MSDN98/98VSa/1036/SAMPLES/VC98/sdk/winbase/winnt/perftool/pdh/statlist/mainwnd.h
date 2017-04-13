// data type and constant definitions used by mainwnd.c
#include <pdh.h>

typedef struct _CounterInfoBlock {
    struct _CounterInfoBlock *pNext;
    TCHAR   szCounterPath[MAX_PATH];
    HCOUNTER    hCounter;
    PPDH_RAW_COUNTER    pCounterArray;
    DWORD       dwFirstIndex;
    DWORD       dwNextIndex;
    DWORD       dwLastIndex;
    PDH_STATISTICS  pdhCurrentStats;
    double      dLastValue;
} CIB, *PCIB;

// global functions found in mainwnd.c
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
