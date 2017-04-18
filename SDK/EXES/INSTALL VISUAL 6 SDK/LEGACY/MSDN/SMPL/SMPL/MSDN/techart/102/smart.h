#ifndef __SMART__

#define EXPORTED __export 

#define ARRAYSIZE 4

typedef void* (*ALLOCPROC)(HWND, DWORD, UINT ) ;

typedef void (*FREEPROC)(void*) ;

typedef struct tagALLOCSTRUCT{
	DWORD dwSize;
	UINT number ;
	UINT offset ;
	BOOL bNeedOptions ;
	UINT options ;
	LPSTR lpszOptions ;
	void * memory ;
} ALLOCSTRUCT;

typedef struct tagMETHODSTRUCT{
	LPSTR name ;
	ALLOCPROC allocProc ;
	FREEPROC freeProc ;
	BOOL useOptions ;
} METHODSTRUCT ;

//////////////////////////////////////////////////////////////////////////
//
//	Prototypes
//
BOOL CALLBACK EXPORTED Smart_OldProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT Smart_DlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT Smart_DefProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam);

//
// Message handlers
//
BOOL Smart_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam); 
void Smart_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void Smart_OnPaint(HWND hwnd) ;
void Smart_OnSysCommand(HWND hwnd, UINT cmd, int x, int y) ;

//
//Allocation/ Free functions
//
void* AppMalloc(HWND hwnd, DWORD size, UINT options);
void* EXPORTED DllMalloc(HWND hwnd, DWORD size, UINT options);
void*	AppGalloc(HWND hwnd, DWORD size, UINT options);
void* EXPORTED DllGalloc(HWND hwnd, DWORD size, UINT options);

void AppMfree(void * ptr) ;
void EXPORTED DllMfree(void * ptr) ;
void AppGfree(void * ptr) ;
void EXPORTED DllGfree(void * ptr) ;

//
// Internal functions
//
void doAlloc(HWND hwnd);
void doFree(HWND hwnd) ;
void addToListBox(HWND hListBox, ALLOCSTRUCT * alloc) ;
void enableGAOptions(HWND hdlg, BOOL bGray);
void done(HWND hdlg);

#define __SMART__
#endif


