/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


#ifndef __EXTENSIONS_H
#define __EXTENSIONS_H

#include "Imports.h"

BOOL InitExtensions();
BOOL ActivateExtensions(int iForceMode = 0);
void EndExtensions();
bool GetExtensionsInited();
bool GetExtensionsActive();
int  GetExtensionsErr();

extern CString g_sRegUserName;


// exported extensions
CFancyTabCtrl *NewWTTabCtrl();
void SetWTTabCtrlColors(CFancyTabCtrl *pCtrl, COLORREF clrReg, COLORREF clrSel);
void WTTabCtrlSetFlags(CFancyTabCtrl *pCtrl, int flags);
bool WTTabCtrlIsGroupSection(CFancyTabCtrl *pCtrl, POINT pt);
void WTTabCtrlSetTabOverlay(CFancyTabCtrl *pCtrl, int iTab, HICON hIcon, 
                            bool bAutoDelete);
void WTTabCtrlRefresh(CFancyTabCtrl *pCtrl);
int WTTabCtrlGetGroupInfo(CFancyTabCtrl *pCtrl, int *pInfo);


#endif  // __EXTENSIONS_H