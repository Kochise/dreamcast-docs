/* KallistiGL for KOS ##version##

   gltex.c
   (c)2001 Dan Potter
*/

#include <GL/gl.h>
#include <GL/glu.h>
#include "glinternal.h"
#include "glmacros.h"

#include <assert.h>
#include <malloc.h>
#include <stdio.h>

CVSID("$Id: gltex.c,v 1.11 2002/09/05 07:36:23 bardtx Exp $");

/* Texture handling */

/* Allocate "texture structures" (really poly context structs) */
void glGenTextures(GLsizei n, GLuint *textures) {
	int i;
	pvr_poly_cxt_t *p;
	for (i=0; i<n; i++) {
		p = (pvr_poly_cxt_t*)malloc(sizeof(pvr_poly_cxt_t));

		/* initial state for this texture object */
		p->txr.env = PVR_TXRENV_MODULATE;
		p->txr.enable = PVR_TEXTURE_ENABLE;
		p->txr.filter = PVR_FILTER_NONE;
		p->txr.alpha = PVR_TXRALPHA_DISABLE;
		p->txr.mipmap = PVR_MIPMAP_DISABLE;
		p->txr.mipmap_bias = PVR_MIPBIAS_NORMAL;
		p->txr.uv_flip = PVR_UVFLIP_NONE;
		p->txr.uv_clamp = PVR_UVCLAMP_NONE;
		p->txr.format = PVR_TXRFMT_NONE;
		p->txr.base = NULL;
		p->txr.width = -1;
		p->txr.height = -1;
		
		textures[i] = (GLuint)p;
	}
}

/*  Delete textures from VRAM */
void glDeleteTextures(GLsizei n, const GLuint *textures) {
	int i;

	for (i=0; i<n; i++) {
		pvr_mem_free(((pvr_poly_cxt_t *)textures[i])->txr.base);
		free((void*)textures[i]);
	}
}

/* Bind a texture */
void glBindTexture(GLenum type, GLuint texture) {
	assert(type == GL_TEXTURE_2D);

	gl_cur_texture = (pvr_poly_cxt_t *)texture;
	gl_pbuf_submitted = GL_FALSE;
}

/* Load a texture from a 2D image */
void glTexImage2D(GLenum target, GLint level,
		GLint internal_fmt,
		GLsizei width, GLsizei height,
		GLint border, GLenum format, GLenum type,
		const GLvoid *pixels) {
	pvr_ptr_t txr;
	
	assert_msg(border == 0 && level == 0, "Borders and levels not supported.");
	assert_msg((internal_fmt & ~1) == (format & ~1), "Pixel conversion not supported.");

	/* Allocate space for it */
	txr = pvr_mem_malloc(width * height * 2);

	/* Load the texture data */
	if ((internal_fmt & 1) != (format & 1))
	 	pvr_txr_load_ex((GLvoid *)pixels, txr, width, height, PVR_TXRLOAD_16BPP);
	else
		pvr_txr_load((GLvoid *)pixels, txr, width * height * 2);
		
	/* Store texture state in context */
	gl_cur_texture->txr.width = width; 
	gl_cur_texture->txr.height =  height;
	gl_cur_texture->txr.format =  internal_fmt;
	gl_cur_texture->txr.base = txr;

	gl_pbuf_submitted = GL_FALSE;
}

/* KOS shortcut function (if you loaded your own texture) */
void glKosTex2D(GLint internal_fmt, GLsizei width, GLsizei height,
		pvr_ptr_t txr_address) {

	/* Store texture state in context */
	gl_cur_texture->txr.width = width; 
	gl_cur_texture->txr.height =  height;
	gl_cur_texture->txr.format =  internal_fmt;
	gl_cur_texture->txr.base = txr_address;

	gl_pbuf_submitted = GL_FALSE;
}

/* Texture environment */
void glTexEnvi(GLenum target, GLenum pname, GLint param) {
	assert(target == GL_TEXTURE_2D);
	assert(pname == GL_TEXTURE_ENV_MODE);

	switch(param) {
	case GL_REPLACE:
		gl_cur_texture->txr.env = PVR_TXRENV_REPLACE;
		break;
	case GL_MODULATE:
		gl_cur_texture->txr.env = PVR_TXRENV_MODULATE;
		break;
	case GL_DECAL:
		gl_cur_texture->txr.env = PVR_TXRENV_DECAL;
		break;
	case GL_MODULATEALPHA:
		gl_cur_texture->txr.env = PVR_TXRENV_MODULATEALPHA;
		break;
	}
	gl_pbuf_submitted = GL_FALSE;
}

/* Texture parameter */
void glTexParameteri(GLenum target, GLenum pname, GLint param) {	
	assert(target == GL_TEXTURE_2D);

	switch(pname) {
		case GL_TEXTURE_FILTER:
			switch(param) {
				case GL_FILTER_NONE:
					gl_cur_texture->txr.filter = PVR_FILTER_NONE;
					break;
				case GL_FILTER_BILINEAR:
					gl_cur_texture->txr.filter = PVR_FILTER_BILINEAR;
					break;
				default:
					assert_msg(0, "Unknown texture filter.");
				break;	
			}
			break;
		case GL_TEXTURE_WRAP_S: /* adjust state of UVCLAMP_U */
			switch(param) {
				case GL_REPEAT:
					if (gl_cur_texture->txr.uv_clamp == PVR_UVCLAMP_UV)
						gl_cur_texture->txr.uv_clamp = PVR_UVCLAMP_V;
					else if (gl_cur_texture->txr.uv_clamp == PVR_UVCLAMP_U)
						gl_cur_texture->txr.uv_clamp = PVR_UVCLAMP_NONE;
					break;
				case GL_CLAMP:
					if (gl_cur_texture->txr.uv_clamp == PVR_UVCLAMP_NONE)
						gl_cur_texture->txr.uv_clamp = PVR_UVCLAMP_U;
					else if (gl_cur_texture->txr.uv_clamp == PVR_UVCLAMP_V)
						gl_cur_texture->txr.uv_clamp = PVR_UVCLAMP_UV;
					break;
				default:
					assert_msg(0, "Unknown texture wrap mode.");
					break;
			}
			break;
		case GL_TEXTURE_WRAP_T: /* adjust state of UVCLAMP_V */
			switch(param) {
				case GL_REPEAT:
					if (gl_cur_texture->txr.uv_clamp == PVR_UVCLAMP_UV)
						gl_cur_texture->txr.uv_clamp = PVR_UVCLAMP_U;
					else if (gl_cur_texture->txr.uv_clamp == PVR_UVCLAMP_V)
						gl_cur_texture->txr.uv_clamp = PVR_UVCLAMP_NONE;
					break;
				case GL_CLAMP:
					if (gl_cur_texture->txr.uv_clamp == PVR_UVCLAMP_NONE)
						gl_cur_texture->txr.uv_clamp = PVR_UVCLAMP_V;
					else if (gl_cur_texture->txr.uv_clamp == PVR_UVCLAMP_U)
						gl_cur_texture->txr.uv_clamp = PVR_UVCLAMP_UV;
					break;
				default:
					assert_msg(0, "Unknown texture wrap mode.");
					break;
			}
			break;
		default:
			assert_msg(0, "Unknown parameter name (pname).");
			break;

	}
	gl_pbuf_submitted = GL_FALSE;
}

