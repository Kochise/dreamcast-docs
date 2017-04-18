/*
    Ninja Sample

    COPYRIGHT (C) SEGA ENTERSRISES,LTD.

    F40 Sample for SET5

    1999.01.20
*/
#include <Shinobi.h>
#include <Nindows.h>
#include "ginsu.h"

#define OBJECT  object_F40_GTE_sh_null1_1_null1_1
#define TEXLIST texlist_F40_GTE_sh_null1_1

extern  NJS_OBJECT  OBJECT[];
extern NJS_TEXLIST TEXLIST[];

/* テクスチャの設定 */
/* setting of texture */
NJS_TEXMEMLIST  tex[100];

extern NJS_MATRIX   matrix[32];
extern NJS_VERTEX_BUF   vbuf[4096];

NJS_VIEW    view;
NJS_LIGHT   light;

Sint32  xx = 0,yy = 0,zz = 0;

void njUserInit(void)
{
    gsInit();

    /*
        njInitSystemの変わりにsbInitSystemを実行する。
        詳しくは、sbinit.cをご覧ください

    */
    /*
       Executing "sbInitSystem" in a change of "njInitSystem".
       (reference with sbinit.c in detail)
    */
    njSetBorderColor( 0 ) ;
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

    gdFsChangeDir(gsGetBasePath());
    
	/*
        Securing work buffer of texture. 
        So far, in texture of F40, it was secured 0x40800 byte that was the size 
        that could load it without MIPMAP of 1024x128 of the greatest size.
        But it was changed to can load it by setting of 0x800 unit more than 0x800.
        It does not take the time that the greatest size was used for loads.
    */

    njInitTextureBuffer((Sint8*)vbuf,0x800*100);
    njInitVertexBuffer( 900000, 0, 200000, 0 ,0);
    njInitPrint(NULL,0,0);

    njInitMatrix( matrix, 32 , 0);
    njInit3D( vbuf, 4096 );
    njInitView( &view );
    njCreateLight( &light, NJD_SPEC_DIR );
    njSetLightIntensity( &light, 0.5f, 2.0f, 0.5f );
    njSetView( &view );

    njInitTexture( tex,100);

    /*
        NINDOWS初期化 SET4から引数にポートを設定する

    */
    /*
        NINDOWS initialization
        Establishing a port in an argument (than SET 4)
    */
    nwInitSystem(100,NJD_PORT_A0);

    /*
        テクスチャはDG WorkShopのカレントディレクトリに
        置いてください
    */
    /*
        Put texture with baing current directory of DG WorkShop
    */
    njLoadTexture( TEXLIST );
    njSetTexture( TEXLIST );

    njControl3D( NJD_CONTROL_3D_CONSTANT_ATTR|NJD_CONTROL_3D_NO_CLIP_CHECK );
    njSetConstantAttr( 0xffffffff, NJD_FILTER_BILINEAR);

    njClipZ( -2.0f, -100.f );
    njSetAspect( 1.0f, 1.0f );

    njSetBackColor(0x00000000,0x00000000,0x000000FF);
    njPrintSize(16);
}

Sint32 njUserMain(void)
{
    njClearMatrix();
    njTranslate( NULL, 1.f, 0.f, -7.f );
    njRotateXYZ( NULL, xx,yy,zz );
    njSimpleDrawObject(OBJECT);

    njPrintC(NJM_LOCATION(2,3),"TEST SET5 .. F40");

    yy += 173;
    xx = -6000;

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

