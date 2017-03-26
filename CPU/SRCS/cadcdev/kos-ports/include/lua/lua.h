/* KallistiOS ##version##

   lua.h
   Copyright (C)2002,2003 Dan Potter

   $Id: lua.h,v 1.1 2003/02/27 03:46:29 bardtx Exp $
*/

#ifndef __LUA_LUA_H
#define __LUA_LUA_H

#include <sys/cdefs.h>
__BEGIN_DECLS

/* Just include the stuff from the Lua tree */
#include "../../lua/include/lua.h"
#include "../../lua/include/lauxlib.h"
// #include "../../lua/include/luadebug.h"
#include "../../lua/include/lualib.h"

/* And our fputs shim */
void luaB_set_fputs(void (* fputs_target)(const char *));

__END_DECLS

#endif	/* __LUA_LUA_H */


