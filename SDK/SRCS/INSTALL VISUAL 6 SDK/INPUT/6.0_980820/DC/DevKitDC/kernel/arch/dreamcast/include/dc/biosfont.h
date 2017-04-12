/* KallistiOS 1.1.6

   dc/biosfont.h
   (c)2000-2001 Dan Potter

   $Id: biosfont.h,v 1.2 2002/01/05 07:33:51 bardtx Exp $

*/

#ifndef __DC_BIOSFONT_H
#define __DC_BIOSFONT_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

void *bfont_find_char(int ch);
void bfont_draw(uint16 *buffer, int bufwidth, int opaque, int c);
void bfont_draw_str(uint16 *buffer, int width, int opaque, char *str);

__END_DECLS

#endif	/* __DC_BIOSFONT_H */

