/*
 *  Shinobi Library
 *  Copyright (c) 1998 SEGA
 *
 *       Hardware
 *
 *  Module  : Library Header File
 *  File    : sg_pad.h
 *  Create  : 1998-04-20
 *  Modify  : 1998-08-28
 *  Version : 1.01
 *  Note    :
 */

#ifndef _SG_SYHW_H_
#define _SG_SYHW_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sg_xpt.h>

void syHwInit(void);
void syHwInit2(void);
void syHwFinish(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SG_SYHW_H_ */
