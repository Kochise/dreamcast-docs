// COPYRIGHT:
//
//   (C) Copyright Microsoft Corp. 1993.  All rights reserved.
//
//   You have a royalty-free right to use, modify, reproduce and
//   distribute the Sample Files (and/or any modified version) in
//   any way you find useful, provided that you agree that
//   Microsoft has no warranty obligations or liability for any
//   Sample Application Files which are modified.


#include "pick_dll.h"  
#include <stdlib.h>

// Internal Message Handlers
// 
LRESULT LOCAL picker_DlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT LOCAL DefDialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL LOCAL picker_OnInitDialog(HWND hwndDlg, HWND hwndFocus, LPARAM lParam);
void LOCAL picker_OnDestroy(HWND hwnd);
void LOCAL picker_OnCommand(HWND hwndDlg, UINT id, HWND hwndCtl, UINT code);
void LOCAL picker_OnLButtonDown( HWND hwnd, BOOL bDouble, int x, int y, UINT keyFlags); 
void LOCAL picker_OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags);

// Internal Function Prototypes
// 
void LOCAL cleanup(HWND hwnd);
void LOCAL setup(HWND hwnd);
void LOCAL invertBorder(HWND hwnd);
void LOCAL invertBorders(HWND hwndDlg, HWND hwndTarget);
void LOCAL popup(HWND hwnd);							
BOOL LOCAL copyStruct(HWND hwnd);
void LOCAL done(HWND hwnd, BOOL bExitFlag);
													 

// Common default dialog procedure
//
LRESULT LOCAL DefDialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    DLGPROC lpfndp = SubclassDialog(hwnd, NULL);
    LRESULT result = DefDlgProc(hwnd, msg, wParam, lParam);
    SubclassDialog(hwnd, lpfndp);
    return result;
}

//This function is marked as an Exported Entry Point since it is
//called by the application.
//
int DLL_EXP Picker_Do(HWND hwndOwner, LP_PICKER_STRUCT lpPicker)
{
	 if (!lpPicker)
		 return FALSE ;

    return  DialogBoxParam(hInst, MAKEINTRESOURCE(IDR_PICKER),		 
									 hwndOwner, Picker_OldDlgProc,
									 (LPARAM)lpPicker);								 
}

// This function is marked as an Entry Point since it is called by
// Windows and is not used directly by the client application.
//
BOOL DLL_ENT Picker_OldDlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    return SetDlgMsgResult(hwndDlg, msg, picker_DlgProc(hwndDlg, msg, wParam, lParam));
}

// Message Handlers

LRESULT LOCAL picker_DlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        HANDLE_MSG(hwndDlg, WM_INITDIALOG, picker_OnInitDialog);
        HANDLE_MSG(hwndDlg, WM_COMMAND, picker_OnCommand);
		  HANDLE_MSG(hwndDlg, WM_MOUSEMOVE,picker_OnMouseMove);
  		  HANDLE_MSG(hwndDlg, WM_LBUTTONDOWN,picker_OnLButtonDown);
    default:
       return DefDialogProc(hwndDlg, msg, wParam, lParam);
    }
}

BOOL LOCAL picker_OnInitDialog(HWND hwndDlg, HWND hwndFocus, LPARAM lParam)
{
	 RECT rectDlg ;
	 NP_GLOBAL_PICKER g = allocMem(hwndDlg,(LP_PICKER_STRUCT)lParam);
	 if (!g)
	 {
		 return FALSE ;
	 }			 
	 g->bPicking = FALSE ;
	 
	 GetWindowRect(hwndDlg, &rectDlg);
	 SetCursorPos(rectDlg.left + (rectDlg.right - rectDlg.left)/4,
					  rectDlg.top + (rectDlg.bottom - rectDlg.top)/4 ) ;
				  
    PostMessage(hwndDlg,WM_COMMAND,IDM_CONTINUE,0L);
	 return TRUE;
}

VOID LOCAL picker_OnCommand(HWND hwndDlg, UINT id, HWND hwndCtl, UINT code)
{
    if ( (id == IDCANCEL && code == BN_CLICKED) ||
		   (id == IDM_CANCEL) )
    {		  		  
        done(hwndDlg, FALSE);
    }
	 else if ( ( id == IDOK && code == BN_CLICKED ) ||
			     ( id == IDM_PICK ) )
	 {		 
		 done(hwndDlg,TRUE);
	 }
	 else if ( id == IDM_CONTINUE )
	 {
		setup(hwndDlg); 
	 }
  }

void LOCAL picker_OnLButtonDown(HWND hwnd, BOOL bDouble, int x, int y, UINT keyFlags)
{
	if (!bDouble)
		cleanup(hwnd);
}

void LOCAL picker_OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
	HWND hwndTarget ;
	POINT p;
	NP_GLOBAL_PICKER g = getMem(hwnd);
	
	if (!g->bPicking)
		return ;
	
	p.x = x ;
	p.y = y ;
	ClientToScreen(hwnd,&p);
	
	hwndTarget = WindowFromPoint(p);

	//Only change the text if the Window changes and it is not this task.
	if ( ( hwndTarget != g->picker.hwnd ) &&
			( GetWindowTask(hwndTarget) != GetWindowTask(hwnd) ) )
	{
		HINSTANCE hinstTarget ;
		
		GetClassName(hwndTarget,g->picker.szClassname,CLASSNAMESIZE);
		SetDlgItemText(hwnd,CTL_CLASSNAME,g->picker.szClassname);
		
		hinstTarget = GetWindowInstance(hwndTarget);
		GetModuleFileName(hinstTarget,g->picker.szPathname,PATHNAMESIZE);

		_splitpath(g->picker.szPathname,g->szJunk,g->szJunk,g->picker.szFilename,g->szJunk);
		SetDlgItemText(hwnd,CTL_APPNAME,g->picker.szFilename);				
		
		if (GetWindowText(hwndTarget, g->picker.szCaption,CAPTIONSIZE))
		{
			SetDlgItemText(hwnd,CTL_CAPTION,g->picker.szCaption);
		}
		else
		{
			SetDlgItemText(hwnd,CTL_CAPTION,"");
		}
		
		invertBorders(hwnd,hwndTarget);

		g->picker.hwnd = hwndTarget ;
	}
}

// Internal Functions

 VOID LOCAL setup(HWND hwndDlg)
 {
 	NP_GLOBAL_PICKER g = getMem(hwndDlg);
	HCURSOR hcursor ;
	
	 if (g->bPicking)
		 return ;

	 g->picker.hwnd = NULL ;
	 
	 hcursor = LoadCursor(NULL, IDC_CROSS) ;
	 SetCursor(hcursor);

	 SetCapture(hwndDlg) ;	 
	 g->bPicking = TRUE ;
 }
 
 VOID LOCAL cleanup(HWND hwndDlg)
 {
  	NP_GLOBAL_PICKER g = getMem(hwndDlg);
	 HCURSOR hcursor ;
	 //Only clean up if we need to
	 if (!g->bPicking)
		 return ;

	 invertBorder(g->picker.hwnd);
	 
 	 hcursor = LoadCursor(NULL, IDC_ARROW) ;
	 SetCursor(hcursor);

	 ReleaseCapture();
	 g->bPicking = FALSE ;
	 popup(hwndDlg);
 }
 
 void LOCAL invertBorders(HWND hwndDlg, HWND hwndTarget)
 {
 	NP_GLOBAL_PICKER g = getMem(hwndDlg);
	 invertBorder(g->picker.hwnd);
	 invertBorder(hwndTarget);
 }
 
 void LOCAL invertBorder(HWND hwnd)
{
	HDC hdc ;
	HPEN hOldPen ;
	HPEN hPen ;
	HBRUSH hOldBrush ;
	HBRUSH hBrush ;
	int oldROP2 ;
	RECT rect ;
	
	if (!IsWindow(hwnd))
		return ;
	
	GetClientRect(hwnd, &rect);
   
	hdc = GetDC(hwnd);
	
	oldROP2 = SetROP2(hdc, R2_NOT);
	hPen = CreatePen(PS_SOLID,6,RGB(0,0,0));
	hOldPen = SelectPen(hdc,hPen);
	hBrush = GetStockBrush(HOLLOW_BRUSH);
	hOldBrush = SelectBrush(hdc, hBrush);
	
	Rectangle(hdc, rect.left, rect.top,	rect.right, rect.bottom);
	
	SetROP2(hdc, oldROP2);
	SelectBrush(hdc,hOldBrush);
	SelectPen(hdc,hOldPen);
	DeletePen(hPen);
	ReleaseDC(hwnd, hdc);  
}
 
BOOL LOCAL copyStruct(HWND hwnd)
{
	NP_GLOBAL_PICKER g = getMem(hwnd);
	if (g->picker.hwnd != NULL)
		*(g->lpPicker) = g->picker ;
	return (BOOL)g->picker.hwnd;
}

void LOCAL popup(HWND hwnd)
{
	HMENU hFloatingPopup = CreatePopupMenu();
	POINT p ;
	
	GetCursorPos(&p);	
		
	// Only display the Popup menu if we are outside our window
	if ( GetWindowTask(WindowFromPoint(p)) != GetWindowTask(hwnd) )
	{	
		AppendMenu( hFloatingPopup, MF_ENABLED, IDM_PICK,"Pick" );
		AppendMenu( hFloatingPopup, MF_ENABLED, IDM_CONTINUE,"Continue");
		AppendMenu( hFloatingPopup, MF_ENABLED, IDM_CANCEL,"Cancel");
		TrackPopupMenu( hFloatingPopup,TPM_CENTERALIGN,p.x,p.y,
							 NULL,hwnd,(LPVOID)NULL);
	}	
	DestroyMenu(hFloatingPopup);
}


void LOCAL done(HWND hwnd, BOOL bExitFlag)
{
	// TRUE - Means an okay exit
	// FALSE - Means the user canceled.
	if (bExitFlag)
	{
		bExitFlag = copyStruct(hwnd);
	}
	freeMem(hwnd);
	EndDialog(hwnd,bExitFlag);
}
