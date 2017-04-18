//--------------------------------------------------------------
// common user interface routines
//
//
//--------------------------------------------------------------

#define STRICT
#define _INC_OLE        // WIN32, get ole2 from windows.h
#define CONST_VTABLE

#include <windows.h>
#include <commdlg.h>
#include <dlgs.h>       // commdlg IDs
#include <shellapi.h>
#include <commctrl.h>
#include <windowsx.h>
#include <ole2.h>
#include <shlobj.h>

//
// defclsf.c
//
typedef HRESULT (CALLBACK FAR * LPFNCREATEINSTANCE)(LPUNKNOWN pUnkOuter,
	REFIID riid, LPVOID FAR* ppvObject);

STDAPI SHCreateDefClassObject(REFIID riid, LPVOID FAR* ppv,
			 LPFNCREATEINSTANCE lpfnCI, UINT FAR * pcRefDll,
			 REFIID riidInst);

//
// Helper macro for implemting OLE classes in C
//
#define _IOffset(class, itf)         ((UINT)&(((class *)0)->itf))
#define IToClass(class, itf, pitf)   ((class  *)(((LPSTR)pitf)-_IOffset(class, itf)))
#define IToClassN(class, itf, pitf)  IToClass(class, itf, pitf)

