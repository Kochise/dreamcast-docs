/*-----------------------------------------------------------------------
|   Draw3d - Routines to help add 3D effects to Windows
-----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

// Index Color Table
// WARNING: change mpicvSysColors if you change the icv order
typedef int ICV;
#define ICVBTNHILITE   0
#define ICVBTNFACE     1
#define ICVBTNSHADOW   2
#define ICVBRUSHMAX    3

#define ICVBTNTEXT     3
#define ICVWINDOW      4
#define ICVWINDOWTEXT  5
#define ICVGRAYTEXT    6
#define ICVWINDOWFRAME 7
#define ICVMAX         8

  
// DrawRec3d flags
#define DR3LEFT  0x0001
#define DR3TOP   0x0002
#define DR3RIGHT 0x0004
#define DR3BOT   0x0008
#define DR3HACKBOTRIGHT 0x1000  // code size is more important than aesthetics
#define DR3ALL    0x000f

typedef WORD DR3;     

// isomorphic to windows RECT
typedef struct
    {
    int xLeft;
    int yTop;
    int xRight;
    int yBot;
    } RC;
 
BOOL   FAR PASCAL Draw3dEnabled(void);
HBRUSH FAR PASCAL Draw3dCtlColor(UINT wm, WPARAM wParam, LPARAM lParam);
BOOL   FAR PASCAL Draw3dColorChange(void);

BOOL   FAR PASCAL Draw3dRegister(void);
BOOL   FAR PASCAL Draw3dUnregister(void); 

VOID Draw3dRec(HDC hdc, RC FAR *lprc, ICV icvUpperLeft, ICV icvLowerRight, DR3 rdr3);
VOID Draw3dInsetRect(HDC hdc, RC FAR *prc, DR3 dr3);

#ifdef __cplusplus
}
#endif
