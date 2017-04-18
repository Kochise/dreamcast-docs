#ifndef _ZU_H_
#define _ZU_H_
//
// Zusammen include file
//
#include <windows.h>
#include <windowsx.h>

#include "resource.h"
#include "app.h"
#include "frame.h"
#include "client.h"
#include "picker.h"

void GLOBAL zu_calcScreenPos(LPPOINT lpPos, LPPOINT lpSize );
BOOL GLOBAL zu_OnCreate(HWND hwnd, CREATESTRUCT FAR* lpCreateStruct);
void GLOBAL zu_OnHScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos); 
void GLOBAL zu_OnVScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos); 
void GLOBAL zu_OnPaint(HWND hwnd);
void GLOBAL zu_OnCommand(HWND hwnd, int id, HWND hwndCtl, 
											UINT codeNotify);


#endif										



