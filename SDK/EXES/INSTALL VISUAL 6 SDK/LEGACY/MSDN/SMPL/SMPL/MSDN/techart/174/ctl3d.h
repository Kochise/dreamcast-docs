/*-----------------------------------------------------------------------
|	CTL3D.DLL
|	
|	Adds 3d effects to Windows controls
|
|	See ctl3d.doc for info
|		
-----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif


BOOL FAR PASCAL Ctl3dSubclassDlg(HWND, WORD);
WORD FAR PASCAL Ctl3dGetVer(void);
BOOL FAR PASCAL Ctl3dEnabled(void);
HBRUSH FAR PASCAL Ctl3dCtlColor(HDC, LONG);	// ARCHAIC, use Ctl3dCtlColorEx
HBRUSH FAR PASCAL Ctl3dCtlColorEx(UINT wm, WPARAM wParam, LPARAM lParam);
BOOL FAR PASCAL Ctl3dColorChange(void);
BOOL FAR PASCAL Ctl3dSubclassCtl(HWND);
LONG FAR PASCAL Ctl3dDlgFramePaint(HWND, UINT, WPARAM, LPARAM);

BOOL FAR PASCAL Ctl3dAutoSubclass(HANDLE);

BOOL FAR PASCAL Ctl3dRegister(HANDLE);
BOOL FAR PASCAL Ctl3dUnregister(HANDLE);

/* Ctl3dSubclassDlg3d flags */
#define CTL3D_BUTTONS		0x0001
#define CTL3D_LISTBOXES		0x0002		
#define CTL3D_EDITS			0x0004	
#define CTL3D_COMBOS			0x0008		
#define CTL3D_STATICTEXTS	0x0010		
#define CTL3D_STATICFRAMES	0x0020

#define CTL3D_ALL				0xffff

#define WM_DLGBORDER (WM_USER+3567)
/* WM_DLGBORDER *(int FAR *)lParam return codes */
#define CTL3D_NOBORDER		0
#define CTL3D_BORDER			1

#define WM_DLGSUBCLASS (WM_USER+3568)
/* WM_DLGSUBCLASS *(int FAR *)lParam return codes */
#define CTL3D_NOSUBCLASS	0
#define CTL3D_SUBCLASS		1


#ifdef __cplusplus
}
#endif
