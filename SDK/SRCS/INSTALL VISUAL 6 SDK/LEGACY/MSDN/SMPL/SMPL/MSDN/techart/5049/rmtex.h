/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. 
 *  All Rights Reserved.
 *
 *  File: resource.h
 *
 ***************************************************************************/

#define MENU_ABOUT                      1
#define MENU_FILE_OPEN                  2
#define MENU_EXIT                       3
#define MENU_STEP                       27
#define MENU_GO                         28
#define MENU_FIRST_DRIVER               80

#define MENU_WRAP_VALS                  98
#define MENU_WRAP_VALS_KILL             99
#define MENU_WRAP_FLAT                  100
#define MENU_WRAP_CYL                   101
#define MENU_WRAP_SPHR                  102
#define MENU_WRAP_CHROME                103

#define IDC_STATIC                     -1

#ifdef __cplusplus
extern "C" {
#endif

void setWrapDefaults(LONG wrapType);

char* OpenNewFile( HWND hwnd, const char *wndTitle );

extern HINSTANCE hInst;
extern HWND win;
extern HWND hwPageVal;
extern int  wrapType;
extern D3DRMIMAGE* texImage;
extern D3DRMBOX box;
extern D3DVALUE minx;    
extern D3DVALUE maxx;
extern D3DVALUE width;
extern D3DVALUE miny;    
extern D3DVALUE maxy;
extern D3DVALUE height;
extern D3DVALUE minz;    
extern D3DVALUE maxz;
extern D3DVALUE depth;

extern BOOL bX;
HWND CreatePropertySheet(HWND);

extern float wOx,wOy,wOz;
extern float wZx,wZy,wZz;
extern float wYx,wYy,wYz;
extern float tOx,tOy;
extern float tSx,tSy;
extern int floatToInt(float f );
extern float intToFloat(int i );
extern char* floatToText(float f);
extern float textToFloat(char* t);
extern char* intToText(int i);
extern int  textToInt(char* t);
extern LPDIRECT3DRMMESH mesh;
extern void setBoxDims(LPD3DRMBOX box);

#ifdef __cplusplus
}
#endif
