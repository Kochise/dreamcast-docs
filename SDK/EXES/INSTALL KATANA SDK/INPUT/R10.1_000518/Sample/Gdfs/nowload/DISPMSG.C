#include <shinobi.h>

extern const Uint16 pal_NowLoading[];
extern const Uint8 cg_NowLoading[];

static NJS_TEXINFO texinfo[1];
static NJS_TEXNAME texname[1];
static NJS_TEXLIST texlist[1];

static void DrawRect(Sint32 x, Sint32 y, Sint32 w, Sint32 h, Uint32 gidx);

static void blt_pal4(Uint16* buf, Sint32 width, Sint32 height,
								Uint16* pal, Uint8* cg, Sint32 w, Sint32 h)
{
	Sint32 i, j;

	for (i = 0; i < h; i++) {
		for (j = 0; j < w >> 1; j++, cg++) {
			*buf++ = pal[(*cg >> 4) & 0x0f];
			*buf++ = pal[(*cg >> 0) & 0x0f];
		}
		buf += width - w;
	}
}

void DispLoadingMessage(Sint32 x, Sint32 y)
{
	Uint16* texbuf;
	Uint16* top;

	top = texbuf = syMalloc(256 * 32 * 2 * 2);
	texbuf += 2;

	blt_pal4(texbuf, 256, 32, pal_NowLoading, cg_NowLoading, 256, 32);

	njSetTextureInfo(texinfo, texbuf,
		NJD_TEXFMT_ARGB_4444 | NJD_TEXFMT_RECTANGLE, 256, 32);
	njSetTextureName(texname, texinfo, (Uint32)texbuf,
		NJD_TEXATTR_TYPE_MEMORY | NJD_TEXATTR_GLOBALINDEX);

	texlist->textures = texname;
	texlist->nbTexture = 1;

	njLoadTexture(texlist);
	syFree(top);


	DrawRect(x, y, 256, 32, (Uint32)texbuf);
	njWaitVSync();
	DrawRect(x, y, 256, 32, (Uint32)texbuf);
	njWaitVSync();
	DrawRect(x, y, 256, 32, (Uint32)texbuf);
	njWaitVSync();
}

static void DrawRect(Sint32 x, Sint32 y, Sint32 w, Sint32 h, Uint32 gidx)
{
	Sint32 i;
	NJS_TEXTURE_VTX vtx[4];

	for (i = 0; i < 4; i++) {
		vtx[i].col = 0xffffffff;
		vtx[i].z   = 4.f;
	}

	vtx[0].x = x;
	vtx[0].y = y;
	vtx[2].x = x + w;
	vtx[2].y = y;
	vtx[3].x = x + w;
	vtx[3].y = y + h;
	vtx[1].x = x;
	vtx[1].y = y + h;

	vtx[0].u = 0.f;
	vtx[0].v = 0.f;
	vtx[1].u = 0.f;
	vtx[1].v = 1.f;
	vtx[2].u = 1.f;
	vtx[2].v = 0.f;
	vtx[3].u = 1.f;
	vtx[3].v = 1.f;

	njDrawTexture(vtx, 4, gidx, TRUE);
}

/******************************* end of file *******************************/
