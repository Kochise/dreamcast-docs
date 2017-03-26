/* KallistiOS ##version##

   os/abi/video.h
   (c)2000-2001 Dan Potter

   $Id: video.h,v 1.1 2003/02/27 03:46:31 bardtx Exp $

*/

#ifndef __OS_ABI_VIDEO_H
#define __OS_ABI_VIDEO_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <os/process.h>
#include <dc/video.h>
#include <dc/biosfont.h>

typedef struct {
	service_abi_t	hdr;		/* Header info */

	int		(*check_cable)();
	void		(*set_mode)(int ct, int vid_mode, int pixel_mode);
	void		(*set_start)(uint32 start);
	void		(*border_color)(int r, int g, int b);
	void		(*clear)(int r, int g, int b);
	void		(*empty)();
	void		(*waitvbl)();
	uint32		padding0[16-7];

	uint32		*vram_l;
	uint16		*vram_s;
	uint32		padding1[16-2];

	void*		(*bfont_find_char)(int ch);
	void		(*bfont_draw)(uint16 *buffer, int bufwidth, int opaque, int c);
	void		(*bfont_draw_str)(uint16 *buffer, int width, int opaque, char *str);
} abi_video_t;

__END_DECLS

#endif	/* __OS_ABI_VIDEO_H */

