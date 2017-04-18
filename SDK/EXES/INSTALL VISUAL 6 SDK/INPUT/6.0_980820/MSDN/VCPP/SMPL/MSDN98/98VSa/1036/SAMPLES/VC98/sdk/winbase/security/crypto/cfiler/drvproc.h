// DRVPROC.H

#ifndef DRVPROC_INCLUDED
#define DRVPROC_INCLUDED

#include <wincrypt.h>

BOOL    		RunListBoxItem      	(LPCINFO, INT);
BOOL    		ExecuteFileAction   	(LPSINFO);
BOOL    		FillSelectDlg       	(HWND, LPSINFO);
BOOL    		DoFileIO            	(HWND, LPSINFO);
VOID    		UpdateFileLB        	(HWND);
BOOL    		HandleIOError       	(HWND, DWORD, LPTSTR, LPTSTR);
LRESULT WINAPI 	DrvWndProc   			(HWND, UINT, WPARAM, LPARAM);
LRESULT WINAPI 	VersionProc  			(HWND, UINT, WPARAM, LPARAM);
LRESULT WINAPI 	SelectProc   			(HWND, UINT, WPARAM, LPARAM);
LRESULT WINAPI 	RenameProc   			(HWND, UINT, WPARAM, LPARAM);
LRESULT WINAPI 	MkDirProc    			(HWND, UINT, WPARAM, LPARAM);
LRESULT WINAPI 	TextWndProc  			(HWND, UINT, WPARAM, LPARAM);
VOID APIENTRY 	HandleSelectionState	(LPDRAWITEMSTRUCT);
VOID APIENTRY 	DrawEntireItem			(LPDRAWITEMSTRUCT);
VOID APIENTRY 	DrawItem				(LPDRAWITEMSTRUCT);

#endif
