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
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "resource.h"
#include "smart.h"


//////////////////////////////////////////////////////////////////////////
//
//	Global Variables
//
LPSTR lpszName = "Smart Alloc" ;

HINSTANCE hInstance ;

METHODSTRUCT methods[4] = { "_fmalloc", AppMalloc, AppMfree, FALSE,
									 "GlobalAlloc",AppGalloc, AppGfree, TRUE,
									 "_fmalloc-DLL", DllMalloc, DllMfree, FALSE,
									 "GlobalAlloc-DLL", DllGalloc, DllGfree, TRUE
								  } ;

///////////////////////////////////////////////////////////////////////						
//
// The environment is not used.  Suppress these functions which use the 
//	environment. _setenvp allocates space with malloc()..
//
void _setargv() {} ;
void _setenvp() {} ;

//
// This is a dummy function used to insure that the calls to 
// GlobalAlloc, GlobalReAlloc, and GlobalFree from the run time library
// are intercepted by the replacement calls in smartdll.dll.
//
void foo()
{
	HGLOBAL hglb = GlobalAlloc(GMEM_MOVEABLE, 10) ;
	GlobalReAlloc(hglb, 1000, GMEM_MOVEABLE) ;
	GlobalFree( hglb ) ;
}

///////////////////////////////////////////////////////////////////////////							 
//
// WinMain
//
int PASCAL WinMain (HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	hInstance = hInst ;

	DialogBox (hInstance, MAKEINTRESOURCE(ID_SMARTALLOC), 
					NULL, (DLGPROC)Smart_OldProc) ;

	return 0L ;
}


/////////////////////////////////////////////////////////////////////////
//
// Message Handlers for Dialog box.
//
BOOL Smart_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	// Initialize Various controls
			int tabs[4] ;
			WORD widthUnits = (LOWORD(GetDialogBaseUnits()) / 4 ) * 2;
			HWND hctl ;
			HFONT hfont ;
			
		// Initialize the ListBox			
			hfont = GetStockObject(SYSTEM_FIXED_FONT) ;
			hctl = GetDlgItem(hwnd,ID_LISTBOX) ;						

			tabs[0] = widthUnits * 14 ;
			tabs[1] = widthUnits * 22 ;
			tabs[2] = widthUnits * 30 ;
			tabs[3] = widthUnits * 46 ;
			
			ListBox_SetTabStops(hctl, 4, tabs) ;			
			SetWindowFont(hctl,hfont, FALSE) ;			


		// Set up the listbox title line
			hctl = GetDlgItem(hwnd, ID_LBTITLE) ;
			ListBox_SetTabStops(hctl, 4, tabs) ;			
			SetWindowFont(hctl,hfont, TRUE) ;			
			ListBox_AddString(hctl,"ADDRESS\tHANDLE\t  SIZE\tMETHOD\tOPTIONS") ;

		// Gray Global Alloc Options
			enableGAOptions(hwnd,FALSE) ;
		

		// Initialize radio buttons
			CheckRadioButton(hwnd, ID_MALLOC, ID_GLOBALALLOC, ID_MALLOC) ;
			CheckRadioButton(hwnd, ID_APPLICATION, ID_DLL, ID_APPLICATION) ;
			CheckRadioButton(hwnd, ID_MOVEABLE, ID_FIXED, ID_MOVEABLE) ;
			
		// Initialize Size and Number Edit Boxes
			SetDlgItemInt(hwnd, ID_AMBLKSIZ, _amblksiz, FALSE) ;
			SetDlgItemInt(hwnd, ID_SIZE, _amblksiz, FALSE) ;
			SetDlgItemInt(hwnd, ID_NUMBER, 1, FALSE) ;
			Edit_LimitText(GetDlgItem(hwnd,ID_AMBLKSIZ), 6) ;
			Edit_LimitText(GetDlgItem(hwnd,ID_SIZE), 6) ;
			Edit_LimitText(GetDlgItem(hwnd,ID_NUMBER), 5) ;

	return TRUE ;
}

void Smart_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch(id)
	{
	//	
	// Push Buttons
	//	
	case ID_ALLOCATE:
		doAlloc(hwnd) ;
		break ;
		
	case ID_FREE:
		doFree(hwnd) ;
		break ;
		
	case ID_HEAPMIN:
		_heapmin() ; 
		break ;
		
	case ID_HELP:
		WinHelp(hwnd,"smart.hlp", HELP_CONTENTS, 0L) ;
		break ;
		
	case ID_CLOSE:
		done(hwnd) ;
		break ;
	
	//			
	// The Using Radio Buttons	
	//
	case ID_MALLOC:
		enableGAOptions(hwnd,FALSE) ;
		break ;
	case ID_GLOBALALLOC:
		enableGAOptions(hwnd,TRUE) ;
		break ;
		
	//		
	// Don't let "listbox" title line get the focus
	//
	case ID_LBTITLE:
		if(codeNotify == LBN_SETFOCUS)
		{
			SetFocus( GetDlgItem(hwnd, ID_LISTBOX) ) ;
		}
		break ;
		
	default:
		break ;
	}
}

void Smart_OnSysCommand(HWND hwnd, UINT cmd, int x, int y)
{
	if (( cmd & 0xFFF0) == SC_CLOSE)
	{
			done(hwnd) ;
	}
	else	
		FORWARD_WM_SYSCOMMAND(hwnd, cmd, x, y, Smart_DefProc) ;

}

void Smart_OnPaint (HWND hwnd)
{
	if (IsIconic(hwnd))
	{
		PAINTSTRUCT ps ;
		BeginPaint(hwnd, (LPPAINTSTRUCT) &ps) ;
		FORWARD_WM_ICONERASEBKGND(hwnd, ps.hdc, Smart_DefProc) ;
		DrawIcon(ps.hdc, 0,0, LoadIcon(hInstance,"smartIcon"));
		EndPaint( hwnd, (LPPAINTSTRUCT) &ps) ;		
	}
	else
		FORWARD_WM_PAINT(hwnd, Smart_DefProc) ;
		
}

/////////////////////////////////////////////////////////////////////////
//
// Memory Allocation Functions
//
void * AppMalloc(HWND hwnd, DWORD size, UINT options )
{
	// Program is compiled large model to get _fmalloc 
	if( size > _HEAP_MAXREQ )
	{
		MessageBox(hwnd, "Cannot allocate memory block this large.",
					  lpszName,MB_OK | MB_ICONEXCLAMATION ) ;
		MessageBeep(0) ;
		return NULL ;
	}
	else
		return malloc((size_t)size) ;	
}

void * AppGalloc(HWND hwnd, DWORD size, UINT options)
{
	// See Windowsx.h for GlobalAllocPtr
	return GlobalAllocPtr(options,size) ;
}

/////////////////////////////////////////////////////////////////////////
//
// Free Functions
//
void AppMfree(void * ptr) 
{
	free(ptr) ;
}

void AppGfree(void * ptr) 
{
	// See Windowsx.h for GlobalFreePtr Definition
	GlobalFreePtr(ptr) ;
}

/////////////////////////////////////////////////////////////////////////
//
// Internal helper functions
//
void doFree(HWND hwnd)
{
	void * ptrmem ;
	UINT offset ;
	HWND hListBox = GetDlgItem(hwnd, ID_LISTBOX) ;

	// Get Selection
		int index = ListBox_GetCurSel(hListBox) ;
		if (index == LB_ERR)
		{
			MessageBeep(0) ;
			MessageBox(hwnd,"No item selected.",lpszName ,MB_OK | MB_ICONEXCLAMATION ) ;
			return ;
		}
	
	// Get Pointer to Memory Block to delete
		ptrmem = (void *)ListBox_GetItemData(hListBox,index) ;
	// Remove string from Listbox
		ListBox_DeleteString(GetDlgItem(hwnd,ID_LISTBOX), index) ;
	
	// Get index to free function
	// The index is currently stored in the first byte of the allocated
	// memory, but could be stored in the ListBox string
		offset = *((UINT*)ptrmem);
	
	// Free Memory
		(*(methods[offset].freeProc))(ptrmem) ;
	
	// Selection the previous line in the listbox
		ListBox_SetCurSel(hListBox, --index < 0 ? 0 : index) ;
}

void doAlloc(HWND hwnd)
{
		ALLOCSTRUCT alloc ;
		char szBuff[10] ;
		char * szstop ;
		UINT i ;
		HCURSOR hcurSave ;
		
		// Set the _amblksiz variable
			BOOL Translated ;
			UINT ret ;
			ret = GetDlgItemInt( hwnd, ID_AMBLKSIZ, &Translated, FALSE ) ;
			if (Translated)
				_amblksiz = ret ;
			
			
			
		// Determine which method to use
			alloc.offset = (IsDlgButtonChecked(hwnd,ID_MALLOC) ? 0 : 1 )
							+ (IsDlgButtonChecked(hwnd,ID_APPLICATION) ? 0 : 2 );
				
		// Do we need to get options
			if (IsDlgButtonChecked(hwnd,ID_GLOBALALLOC))
			{
				alloc.bNeedOptions = TRUE ;
				if( IsDlgButtonChecked(hwnd,ID_DDESHARE) )
				{
					alloc.options = GMEM_SHARE | GMEM_MOVEABLE;
					alloc.lpszOptions = "SHARE" ;
				}
				else if( IsDlgButtonChecked(hwnd, ID_FIXED) )
				{
					alloc.options = GMEM_FIXED ;
					alloc.lpszOptions = "FIXED" ;
				}
				else
				{
					alloc.options = GMEM_MOVEABLE ;
					alloc.lpszOptions = "MOVEABLE" ;
				}
			}
			else
				alloc.bNeedOptions = FALSE ;
		
		// Get Size of memory to allocate
			Edit_GetText(GetDlgItem(hwnd,ID_SIZE),szBuff,10) ;
			alloc.dwSize = strtoul(szBuff,&szstop,10) ;
		
		// Get number of blocks of dwSize to allocate
			Edit_GetText(GetDlgItem(hwnd,ID_NUMBER),szBuff,10) ;
			alloc.number = atoi(szBuff) ;		
			
			
		//
		// Allocate
		//
			hcurSave = SetCursor(LoadCursor(NULL, IDC_WAIT)) ;
		
			SetWindowRedraw(GetDlgItem(hwnd,ID_LISTBOX), FALSE) ;
			
			for (i = 0 ; i < alloc.number ; i++ )
			{
				alloc.memory = (*(methods[alloc.offset].allocProc))(hwnd,alloc.dwSize,alloc.options) ;
				if( alloc.memory == NULL )
				{
					MessageBeep(0) ;
					MessageBox(hwnd, "Error trying to allocate block.", lpszName,
									MB_OK | MB_ICONEXCLAMATION ) ;
				}
				else
				{
					*((UINT*)alloc.memory) = alloc.offset ;
					addToListBox(GetDlgItem(hwnd,ID_LISTBOX),&alloc) ;
				}
			}
		
			SetWindowRedraw(GetDlgItem(hwnd,ID_LISTBOX), TRUE) ;
			
			SetCursor(hcurSave) ;			
		
}

void addToListBox(HWND hListBox, ALLOCSTRUCT * alloc) 
{
	char szBuff[100] ;
	int index ;

	
	sprintf(szBuff,"%09Fp\t%04x\t%6ld\t%s\t%s", alloc->memory,
						 SELECTOROF(alloc->memory),
						 alloc->dwSize,
						 methods[alloc->offset].name,
						 (alloc->bNeedOptions) ? alloc->lpszOptions : "");
											 
	index = ListBox_AddString(hListBox, szBuff) ;
	
	// Put the Pointer to memory in the data value
		ListBox_SetItemData(hListBox, index, alloc->memory) ;	

	// Select Top item if nothing currently selected in listbox
		if ( ListBox_GetCurSel(hListBox) == LB_ERR)
		{
			ListBox_SetCurSel(hListBox,  0) ;
		}
}

void enableGAOptions(HWND hdlg, BOOL bGray)
{
	EnableWindow(GetDlgItem(hdlg,ID_OPTIONSGROUP),bGray) ;
	EnableWindow(GetDlgItem(hdlg,ID_MOVEABLE),bGray) ;
	EnableWindow(GetDlgItem(hdlg,ID_DDESHARE),bGray) ;
	EnableWindow(GetDlgItem(hdlg,ID_FIXED),bGray) ;
}

void done(HWND hdlg)
{
	EndDialog(hdlg, TRUE) ;
}

/////////////////////////////////////////////////////////////////////////
//
// Simplified Dialog Handling as discribed in the file WINDOWSX.TXT included
// in the Windows 3.1 SDK.
//
static BOOL fDefDlgEx = FALSE;

BOOL CALLBACK EXPORTED Smart_OldProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	CheckDefDlgRecursion(&fDefDlgEx);
	return SetDlgMsgResult (hwndDlg, msg, 
									Smart_DlgProc(hwndDlg, msg, wParam, lParam));
}

LRESULT Smart_DefProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefDlgProcEx(hwndDlg, msg, wParam, lParam, &fDefDlgEx);
}

LRESULT Smart_DlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{ 
	HANDLE_MSG(hwndDlg, WM_INITDIALOG, Smart_OnInitDialog);
	HANDLE_MSG(hwndDlg, WM_COMMAND, Smart_OnCommand);
	HANDLE_MSG(hwndDlg, WM_SYSCOMMAND, Smart_OnSysCommand);
	HANDLE_MSG(hwndDlg, WM_PAINT, Smart_OnPaint) ;	

	default:
	    return Smart_DefProc(hwndDlg, msg, wParam, lParam);
	}
}
