/* KallistiOS ##version##

   pvr_prim.c
   (C)2002 Dan Potter

 */

#include <assert.h>
#include <string.h>
#include <dc/pvr.h>
#include "pvr_internal.h"

/*

   Primitive handling

   These functions help you prepare primitives for loading into the
   PVR for scene processing.

*/

CVSID("$Id: pvr_prim.c,v 1.8 2002/09/13 04:38:41 bardtx Exp $");

/* Compile a polygon context into a polygon header */
void pvr_poly_compile(pvr_poly_hdr_t *dst, pvr_poly_cxt_t *src) {
	int	u, v;
	uint32	txr_base;
	
	/* Basically we just take each parameter, clip it, shift it
	   into place, and OR it into the final result. */

	/* The base values for CMD */
	dst->cmd = PVR_CMD_POLYHDR;
	if (src->txr.enable == PVR_TEXTURE_ENABLE)
		dst->cmd |= 8;

	/* Or in the list type, shading type, color and UV formats */
	dst->cmd |= (src->list_type << PVR_TA_CMD_TYPE_SHIFT) & PVR_TA_CMD_TYPE_MASK;
	dst->cmd |= (src->fmt.color << PVR_TA_CMD_CLRFMT_SHIFT) & PVR_TA_CMD_CLRFMT_MASK;
	dst->cmd |= (src->gen.shading << PVR_TA_CMD_SHADE_SHIFT) & PVR_TA_CMD_SHADE_MASK;
	dst->cmd |= (src->fmt.uv << PVR_TA_CMD_UVFMT_SHIFT) & PVR_TA_CMD_UVFMT_MASK;
	dst->cmd |= (src->gen.clip_mode << PVR_TA_CMD_USERCLIP_SHIFT) & PVR_TA_CMD_USERCLIP_MASK;
	dst->cmd |= (src->fmt.modifier << PVR_TA_CMD_MODIFIER_SHIFT) & PVR_TA_CMD_MODIFIER_MASK;
	dst->cmd |= (src->gen.modifier_mode << PVR_TA_CMD_MODIFIERMODE_SHIFT) & PVR_TA_CMD_MODIFIERMODE_MASK;

	/* Polygon mode 1 */
	dst->mode1  = (src->depth.comparison << PVR_TA_PM1_DEPTHCMP_SHIFT) & PVR_TA_PM1_DEPTHCMP_MASK;
	dst->mode1 |= (src->gen.culling << PVR_TA_PM1_CULLING_SHIFT) & PVR_TA_PM1_CULLING_MASK;
	dst->mode1 |= (src->depth.write << PVR_TA_PM1_DEPTHWRITE_SHIFT) & PVR_TA_PM1_DEPTHWRITE_MASK;
	dst->mode1 |= (src->txr.enable << PVR_TA_PM1_TXRENABLE_SHIFT) & PVR_TA_PM1_TXRENABLE_MASK;

	/* Polygon mode 2 */
	dst->mode2  = (src->blend.src << PVR_TA_PM2_SRCBLEND_SHIFT) & PVR_TA_PM2_SRCBLEND_MASK;
	dst->mode2 |= (src->blend.dst << PVR_TA_PM2_DSTBLEND_SHIFT) & PVR_TA_PM2_DSTBLEND_MASK;
	dst->mode2 |= (src->blend.src_enable << PVR_TA_PM2_SRCENABLE_SHIFT) & PVR_TA_PM2_SRCENABLE_MASK;
	dst->mode2 |= (src->blend.dst_enable << PVR_TA_PM2_DSTENABLE_SHIFT) & PVR_TA_PM2_DSTENABLE_MASK;
	dst->mode2 |= (src->gen.fog_type << PVR_TA_PM2_FOG_SHIFT) & PVR_TA_PM2_FOG_MASK;
	dst->mode2 |= (src->gen.color_clamp << PVR_TA_PM2_CLAMP_SHIFT) & PVR_TA_PM2_CLAMP_MASK;
	dst->mode2 |= (src->gen.alpha << PVR_TA_PM2_ALPHA_SHIFT) & PVR_TA_PM2_ALPHA_MASK;

	if (src->txr.enable == PVR_TEXTURE_DISABLE) {
		dst->mode3 = 0;
	} else {
		dst->mode2 |= (src->txr.alpha << PVR_TA_PM2_TXRALPHA_SHIFT) & PVR_TA_PM2_TXRALPHA_MASK;
		dst->mode2 |= (src->txr.uv_flip << PVR_TA_PM2_UVFLIP_SHIFT) & PVR_TA_PM2_UVFLIP_MASK;
		dst->mode2 |= (src->txr.uv_clamp << PVR_TA_PM2_UVCLAMP_SHIFT) & PVR_TA_PM2_UVCLAMP_MASK;
		dst->mode2 |= (src->txr.filter << PVR_TA_PM2_FILTER_SHIFT) & PVR_TA_PM2_FILTER_MASK;
		dst->mode2 |= (src->txr.mipmap_bias << PVR_TA_PM2_MIPBIAS_SHIFT) & PVR_TA_PM2_MIPBIAS_MASK;
		dst->mode2 |= (src->txr.env << PVR_TA_PM2_TXRENV_SHIFT) & PVR_TA_PM2_TXRENV_MASK;

		switch (src->txr.width) {
		case 8:		u = 0; break;
		case 16:	u = 1; break;
		case 32:	u = 2; break;
		case 64:	u = 3; break;
		case 128:	u = 4; break;
		case 256:	u = 5; break;
		case 512:	u = 6; break;
		case 1024:	u = 7; break;
		default:	assert_msg(0, "Invalid texture U size"); u = 0; break;
		}

		switch (src->txr.height) {
		case 8:		v = 0; break;
		case 16:	v = 1; break;
		case 32:	v = 2; break;
		case 64:	v = 3; break;
		case 128:	v = 4; break;
		case 256:	v = 5; break;
		case 512:	v = 6; break;
		case 1024:	v = 7; break;
		default:	assert_msg(0, "Invalid texture V size"); v = 0; break;
		}

		dst->mode2 |= (u << PVR_TA_PM2_USIZE_SHIFT) & PVR_TA_PM2_USIZE_MASK;
		dst->mode2 |= (v << PVR_TA_PM2_VSIZE_SHIFT) & PVR_TA_PM2_VSIZE_MASK;

		/* Polygon mode 3 */
		dst->mode3  = (src->txr.mipmap << PVR_TA_PM3_MIPMAP_SHIFT) & PVR_TA_PM3_MIPMAP_MASK;
		dst->mode3 |= (src->txr.format << PVR_TA_PM3_TXRFMT_SHIFT) & PVR_TA_PM3_TXRFMT_MASK;

		/* Convert the texture address */
		txr_base = (uint32)src->txr.base;
		txr_base = (txr_base & 0x00fffff8) >> 3;
		dst->mode3 |= txr_base;
	}

	/* Dummy values */
	dst->d1 = dst->d2 = dst->d3 = dst->d4 = 0xffffffff;
}

/* Create a colored polygon context with parameters similar to
   the old "ta" function `ta_poly_hdr_col' */
void pvr_poly_cxt_col(pvr_poly_cxt_t *dst, pvr_list_t list) {
	int alpha;

	/* Start off blank */
	memset(dst, 0, sizeof(pvr_poly_cxt_t));

	/* Fill in a few values */
	dst->list_type = list;
	alpha = list > PVR_LIST_OP_MOD;
	dst->fmt.color = PVR_CLRFMT_ARGBPACKED;
	dst->fmt.uv = PVR_UVFMT_32BIT;
	dst->gen.shading = PVR_SHADE_GOURAUD;
	dst->depth.comparison = PVR_DEPTHCMP_GREATER;
	dst->depth.write = PVR_DEPTHWRITE_ENABLE;
	dst->gen.culling = PVR_CULLING_CCW;
	dst->txr.enable = PVR_TEXTURE_DISABLE;
	if (!alpha) {
		dst->gen.alpha = PVR_ALPHA_DISABLE;
		dst->blend.src = PVR_BLEND_ONE;
		dst->blend.dst = PVR_BLEND_ZERO;
	} else {
		dst->gen.alpha = PVR_ALPHA_ENABLE;
		dst->blend.src = PVR_BLEND_SRCALPHA;
		dst->blend.dst = PVR_BLEND_INVSRCALPHA;
	}
	dst->blend.src_enable = PVR_BLEND_DISABLE;
	dst->blend.dst_enable = PVR_BLEND_DISABLE;
	dst->gen.fog_type = PVR_FOG_DISABLE;
	dst->gen.color_clamp = PVR_CLRCLAMP_DISABLE;
}

/* Create a textured polygon context with parameters similar to
   the old "ta" function `ta_poly_hdr_txr' */
void pvr_poly_cxt_txr(pvr_poly_cxt_t *dst, pvr_list_t list,
		int textureformat, int tw, int th, pvr_ptr_t textureaddr,
		int filtering) {
	int alpha;
	
	/* Start off blank */
	memset(dst, 0, sizeof(pvr_poly_cxt_t));

	/* Fill in a few values */
	dst->list_type = list;
	alpha = list > PVR_LIST_OP_MOD;
	dst->fmt.color = PVR_CLRFMT_ARGBPACKED;
	dst->fmt.uv = PVR_UVFMT_32BIT;
	dst->gen.shading = PVR_SHADE_GOURAUD;
	dst->depth.comparison = PVR_DEPTHCMP_GREATER;
	dst->depth.write = PVR_DEPTHWRITE_ENABLE;
	dst->gen.culling = PVR_CULLING_CCW;
	dst->txr.enable = PVR_TEXTURE_ENABLE;
	if (!alpha) {
		dst->gen.alpha = PVR_ALPHA_DISABLE;
		dst->txr.alpha = PVR_TXRALPHA_ENABLE;
		dst->blend.src = PVR_BLEND_ONE;
		dst->blend.dst = PVR_BLEND_ZERO;
		dst->txr.env = PVR_TXRENV_MODULATE;
	} else {
		dst->gen.alpha = PVR_ALPHA_ENABLE;
		dst->txr.alpha = PVR_TXRALPHA_ENABLE;
		dst->blend.src = PVR_BLEND_SRCALPHA;
		dst->blend.dst = PVR_BLEND_INVSRCALPHA;
		dst->txr.env = PVR_TXRENV_MODULATEALPHA;
	}
	dst->blend.src_enable = PVR_BLEND_DISABLE;
	dst->blend.dst_enable = PVR_BLEND_DISABLE;
	dst->gen.fog_type = PVR_FOG_DISABLE;
	dst->gen.color_clamp = PVR_CLRCLAMP_DISABLE;
	dst->txr.uv_flip = PVR_UVFLIP_NONE;
	dst->txr.uv_clamp = PVR_UVCLAMP_NONE;
	dst->txr.filter = filtering;
	dst->txr.mipmap_bias = PVR_MIPBIAS_NORMAL;
	dst->txr.width = tw;
	dst->txr.height = th;
	dst->txr.base = textureaddr;
	dst->txr.format = textureformat;
}




