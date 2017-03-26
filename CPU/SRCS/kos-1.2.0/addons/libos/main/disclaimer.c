/* KallistiOS 1.2.0

   disclaimer.c
   (c)2001 Dan Potter

*/

/* If you make a CD bootable image, you'll want to enable a disclaimer such
   as this one to tell the users that this program was not made or endorsed
   by Sega. You can consider this a required practice as far as making
   hobbyist productions goes. If you are only using this for yourself or
   you are just developing, then there's no point of course. Just make sure
   it's enable somewhere before you distribute a bootable image. */

#include <kos/thread.h>
#include <dc/ta.h>
#include <dc/biosfont.h>

CVSID("$Id: disclaimer.c,v 1.2 2002/01/06 00:40:33 bardtx Exp $");


/* Builds a little disclaimer texture (easier than doing a bunch of font
   polygons) */
static uint32 disc_txr;
static void disc_texture() {
	uint16	*txrtmp;
	int	i, x, y = (480 - 9*24)/2;
	char	*msg[] = {
"This program is a hobbyist production",
"and was not actually produced by or",
"under license from Sega",
"Enterprises(tm). It was produced",
"using the KallistiOS operating system",
"from Cryptic Allusion. For more",
"information, please visit",
"",
"http://dcdev.allusion.net/"
	};

	/* Allocate texture space */
	disc_txr = ta_txr_allocate(512*512*2);
	txrtmp = (uint16*)ta_txr_map(disc_txr);

	/* Draw a message into it */
	for (i=0; i<9; i++) {
		x = 256 - (strlen(msg[i]) * 12)/2;
		bfont_draw_str(txrtmp + y*512+x, 512, 0, msg[i]);
		y += 25;
	}
}

static void disc_display(float fade) {
	vertex_ot_t	v;
	poly_hdr_t	hdr;

	if (fade < 0.0f) fade = 0.0f;

	ta_poly_hdr_txr(&hdr, TA_OPAQUE, TA_RGB565, 512, 512, disc_txr, TA_NO_FILTER);
	ta_commit_poly_hdr(&hdr);

	/* - -
	   + - */
	v.flags = TA_VERTEX_NORMAL;
	v.x = 64.0f;
	v.y = 480.0f;
	v.z = 1.0f;
	v.u = 0.0f; v.v = 480.0f/512.0f;
	v.a = 1.0f; v.r = v.g = v.b = fade;
	v.oa = v.or = v.og = v.ob = 0.0f;
	ta_commit_vertex(&v, sizeof(v));

	/* + -
	   - - */
	v.y = 0.0f;
	v.v = 0.0f;
	ta_commit_vertex(&v, sizeof(v));

	/* - -
	   - + */
	v.x = 640.0f - 64.0f;
	v.y = 480.0f;
	v.u = 1.0f; v.v = 480.0f / 512.0f;
	ta_commit_vertex(&v, sizeof(v));

	/* - +
	   - - */
	v.flags = TA_VERTEX_EOL;
	v.y = 0.0f;
	v.v = 0.0f;
	ta_commit_vertex(&v, sizeof(v));
}

static void disc_blank() {
	poly_hdr_t	hdr;

	ta_poly_hdr_col(&hdr, TA_TRANSLUCENT);
	ta_commit_poly_hdr(&hdr);
}

void disclaimer() {
	float f;
	
	/* Setup the texture */
	disc_texture();

	/* Fade in the disclaimer */
	for (f=0.0f; f<1.0f; f+=0.01f) {
		ta_begin_render();
		disc_display(f);
		ta_commit_eol();
		disc_blank();
		ta_commit_eol();
		ta_finish_frame();
	}

	/* Pause */
	for (f=0.0f; f<360.0f; f+=1.0f) {
		ta_begin_render();
		disc_display(1.0f);
		ta_commit_eol();
		disc_blank();
		ta_commit_eol();
		ta_finish_frame();
	}

	/* Fade out the disclaimer */
	for (f=1.0f; f>=-0.03f; f-=0.01f) {
		ta_begin_render();
		disc_display(f);
		ta_commit_eol();
		disc_blank();
		ta_commit_eol();
		ta_finish_frame();
	}

	/* Free up the texture RAM */
	ta_txr_release_all();
}

