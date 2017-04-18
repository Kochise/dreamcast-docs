/********************************************************************
 *  Shinobi Library Sample
 *  Copyright (c) 1998 SEGA
 *
 *  Library : Ninja
 *  Module  : Debug print
 *  File    : dbgcons.h
 *  Date    : 1999-05-27
 *  Version : 1.00
 *  Note    : This file provides a simple console interface with
 *            njDebugPrint().
 ********************************************************************/

#ifndef _DBGCONS_H_
#define _DBGCONS_H_

#include <shinobi.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


void ConInit(Sint32 x, Sint32 y, Sint32 w, Sint32 h, void* buf);
void ConExit(void);
void ConPrint(const char* str);
void ConPrintf(const char* fmt, ...);
void ConSetPos(Sint32 x, Sint32 y);
void ConGetPos(Sint32* x, Sint32* y);
void ConMain(void);
void ConCls(void);
void ConDispCuror(void);
void ConEraseCursor(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DBGCONS_H_ */
