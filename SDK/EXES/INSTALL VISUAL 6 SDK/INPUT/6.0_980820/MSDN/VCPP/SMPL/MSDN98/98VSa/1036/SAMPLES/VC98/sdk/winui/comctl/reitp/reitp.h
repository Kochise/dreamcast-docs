/* =========================================================================

File: Reitp.h
Function: Header file for Reitp.c. Exports the DoOpen() and PrintREDoc()
	functions so the Mac version can support the required OpenDoc and Print
	Apple Events.

============================================================================ */

typedef struct _redoc
{
	HWND hwndRE;
	HWND hwndParent;
	DWORD dwFormat;
	BOOL fReadOnly;
	BOOL fWysiwyg;
	BOOL fWrap;
	BOOL fUpdateEditMenu;
	WPARAM scf;
	HMENU hmenuVerbs;
	LPRICHEDITOLE preole;
	struct _itpcall * pitpcall;
	LPSTORAGE pstg;
	ULONG cItem;
	PRINTDLG pd;
	HDC hdcTarget;
	HWND hwndFormatBar;
	FINDREPLACE *pfr;
	TCHAR szFile[256];
	TCHAR szTitle[32];
} REDOC;


LRESULT DoOpen(REDOC *predoc, LPSTR  szFile, LPSTR  szTitle, BOOL  fInsert);

VOID PrintREDoc(REDOC *predoc);