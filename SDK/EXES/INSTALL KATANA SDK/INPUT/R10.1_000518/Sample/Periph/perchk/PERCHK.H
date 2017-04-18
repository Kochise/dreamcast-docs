/********************************************************************
 *  Shinobi Library Sample
 *  Copyright (c) 1998 SEGA
 *
 *  Library : Controller Library
 *  Module  : Controller distinction
 *  File    : perchk.c
 *  Date    : 1999-01-21
 *  Version : 1.00
 *  Note    :
 ********************************************************************/

#ifndef _PERCHK_H_
#define _PERCHK_H_

#include <shinobi.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* ä÷êî CheckController()ÇÕÅAà»â∫ÇÃenumílÇï‘Ç∑ÅB */

enum {
	PER_NONE,
	PER_CONTROLLER,
	PER_STICK,
	PER_RACING,
	PER_GUN,
	PER_KEYBOARD,
	PER_FISHING,
	PER_UNKNOWN
};


extern Sint32 CheckController(Uint32 port);


#endif /* _PERCHK_H_ */
