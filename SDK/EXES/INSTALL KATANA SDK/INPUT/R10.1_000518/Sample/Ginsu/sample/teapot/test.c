/*
    Ninja Sample

    COPYRIGHT (C) SEGA ENTERSRISES,LTD.

    Teapot Sample

    1998.7.23
*/

#include <shinobi.h>
#include <nindows.h>
#include <sg_sycbl.h>

#include "ginsu.h"

extern Uint16 T009[];

#define	OBJECT	object_tea_Teapot1_Teapot1
extern NJS_OBJECT OBJECT[];

NJS_TEXNAME	texname[1];
NJS_TEXLIST	tlist1 = {texname,1};
NJS_TEXINFO	info;

extern NJS_MATRIX	matrix[8];
extern NJS_VERTEX_BUF	vbuf[4096];

NJS_TEXMEMLIST	tex[10];

NJS_VIEW	view;
NJS_LIGHT	light;

Sint32	xx,yy,zz = 0;

Uint32 count = 0;

void Count(void)
{
	count++;

}


void njUserInit(void)
{
    gsInit();
    
	njSetBorderColor( 0x00000000 );
	
   switch (syCblCheck())
	{
        /* Initialize the display device and set the frame buffer based on the video mode. */
        case SYE_CBL_NTSC:  /* U.S./North America NTSC (60Hz) and Brazil PAL-M (60Hz). */
            sbInitSystem (NJD_RESOLUTION_640x480_NTSCNI, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        case SYE_CBL_PAL:   /* Europe PAL (50Hz) and Argentina PAL-N (50Hz). */
            sbInitSystem (NJD_RESOLUTION_640x544_PALNI, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        case SYE_CBL_VGA:   /* Standard VGA. */
            sbInitSystem (NJD_RESOLUTION_VGA, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        default:
            syBtExit();     /* Unknown video type, return to Dreamcast BootROM. */
	}
    
	njInitVertexBuffer( 800000, 0, 100000, 0, 0 );
	njInitPrint( NULL, 0, NJD_TEXFMT_ARGB_1555 );
	njInitMatrix( matrix, 8 , 0);
	njInit3D( vbuf, 4096 );
	njInitView( &view );
	njCreateLight( &light, NJD_PHONG_DIR );
	njSetLightIntensity( &light, 1.5f, 1.0f, 0.7f );
	njSetLightAngle( &light, NJM_RAD_ANG(NJD_PI / 30.f), NJM_RAD_ANG(NJD_PI / 4.f) );
	njSetLightDirection( &light, 0, 0.707f, -0.707f );
	njSetView( &view );

	njInitTexture( tex, 10 );
	nwInitSystem(10,NJD_PORT_A0);
	njSetTextureInfo(&info,T009,NJD_TEXFMT_RGB_565|NJD_TEXFMT_TWIDDLED,128,128);
	njSetTextureName(&texname[0],&info,0,NJD_TEXATTR_TYPE_MEMORY|NJD_TEXATTR_GLOBALINDEX);
	njLoadTexture( &tlist1 );
	njSetTexture( &tlist1 );

	njControl3D( NJD_CONTROL_3D_CONSTANT_ATTR );
	njSetConstantAttr( 0xffffffff, NJD_FLAG_USE_TEXTURE | NJD_FLAG_USE_ENV|NJD_FILTER_BILINEAR);

	njSetBackColor(0xFF000000,0x000FF000,0x000000FF);

	njSetVSyncFunction(Count);
}

Sint32 njUserMain(void)
{

	njClearMatrix();
	njTranslate(NULL, 0.f, 0.f, -12.f ); /* Hitachi */
	njRotateXYZ(NULL, xx,yy,zz ); /* Hitachi */
	njDrawObject( OBJECT );

        xx += 257*1;
        yy += 179*2;
        zz += 193*3;

	njPrintD(NJM_LOCATION(0,1),count,8);

    if (gsExec())
        return -1;  /* force ninja exit */
    
	return nwExecute();
}

void njUserExit(void)
{
    
	nwExitSystem();
	njExitPrint();
	njExitTexture();
    
	sbExitSystem();
    
    gsExit();
}