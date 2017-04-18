#include <shinobi.h>
#include <kamui2.h>
#include <kmutil.h>
#include <sg_sycbl.h>
#include <sg_sytmr.h>
#include <sg_gd.h>

#include "model.h"
#define MAX_TEX_NUM 200

int nCurrentTex = 0;

KMSURFACEDESC Texture[MAX_TEX_NUM];

/*
 *		Read PVR File From GD
 *
 */
PKMDWORD LoadFmGDFS(char *filename)
{
	PKMDWORD pReadBuffer;
	char ReadFileName[50];
	GDFS	gdfs;
	Sint32 	size;
	Sint32 	ret;

	sprintf(ReadFileName,"%s.pvr", filename);
	
	gdfs = gdFsOpen(ReadFileName, NULL);
	if (gdfs == NULL) return NULL;

	gdFsGetFileSize(gdfs, &size);
	size = gdFsCalcSctSize(size);

	pReadBuffer = syMalloc(size * 2048);
	if (pReadBuffer == NULL)
	{
		gdFsClose(gdfs);
		return NULL;
	}

	ret = gdFsRead(gdfs, size, pReadBuffer);

	/* close handle */
	gdFsClose(gdfs);

	if(ret != GDD_ERR_OK)
	{
		syFree(pReadBuffer);
		return NULL;
	}

	return pReadBuffer;
}

/*
 *		Create Texture Sufrace and Load
 *
 */
int LoadTextureList(
						PKG_TEXLIST pTexList	/* Load Texture List */
)
{
	PKG_TEXNAME 	pTexName;
	KMDWORD			nLoop, NumTextures;
	PKMDWORD		pBuffer, pTexture;
	PKG_TEXHEADER	pHeader;
	KMSTATUS 		status;
	PKMSURFACEDESC	pTexSurface;

	pTexName  = pTexList->textures;
	NumTextures = (KMDWORD)pTexList->nbTexture;

	for(nLoop = 0; nLoop < NumTextures; nLoop++)
	{
		pTexture = pBuffer = LoadFmGDFS(pTexName->filename);
		if (pBuffer == NULL) break;

		while (*pBuffer != 0x54525650) pBuffer++; /* Search 'PVRT' Chunk Header*/
		pHeader = (PKG_TEXHEADER)pBuffer;
		pBuffer += (0x10 / sizeof(KMDWORD));

		status = kmCreateTextureSurface(
								&Texture[nCurrentTex], 
								(KMINT32)pHeader->nWidth,
								(KMINT32)pHeader->nHeight,
								(KMINT32)pHeader->nTextureType
							   );

		status = kmLoadTexture(
								&Texture[nCurrentTex],
								pBuffer
							   );
		syFree(pTexture);
		pTexName++;
		nCurrentTex++;
	}
}
