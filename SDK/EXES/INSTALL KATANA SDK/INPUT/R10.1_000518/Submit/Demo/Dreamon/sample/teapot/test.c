/*===========================================================
    Ninja Sample modified to be DreamScene/Ginsu compliant
	T. Szirtes / Sega Europe 

    COPYRIGHT (C) SEGA ENTERPRISES,LTD.

    Teapot Sample

    1998.7.23
	modified 1999.25.5 to support SDK8 new Ginsu version
  ===========================================================*/

/* Comment this out if you are not using SDK8-SOE (Shinobi 1.42) */
#define		USING_SDK8

/* Include Files */
#include <Shinobi.h>
#include <nindows.h>
#include "..\..\lib\ginsu.h"
#include "sndutls.h"

extern Uint16 T009[];

#define OBJECT  object_tea_Teapot1_Teapot1
extern NJS_OBJECT OBJECT[];

NJS_TEXNAME texname[1];
NJS_TEXLIST tlist1 = {texname,1};
NJS_TEXINFO info;

extern NJS_MATRIX   matrix[8];
extern NJS_VERTEX_BUF   vbuf[4096];

NJS_TEXMEMLIST  tex[10];

NJS_VIEW    view;
NJS_LIGHT   light;

Sint32  xx,yy,zz = 0;

Uint32 count = 0;

void Count(void)
{
    count++;

}

Sint8 	*buffer;
int		newcdda;
char	*basepath;
int		autodemo	=	0;


char		buf[256];


void UserInit(void)
{
	
    njSetBorderColor( 0 ) ;

 
	switch( syCblCheckCable() ) 
	{
	case SYE_CBL_CABLE_VGA :
		sbInitSystem(NJD_RESOLUTION_VGA, NJD_FRAMEBUFFER_MODE_RGB565, 1);
		break;    
	default:
	    sbInitSystem( NJD_RESOLUTION_640x480_PALNI, NJD_FRAMEBUFFER_MODE_RGB565, 1 );
		break;
	}
							

	/* CALL GINSU INIT AFTER SHINOBI INTIALIZATION */
    gsInit();

	gsGetUserData	(buf, 8);

    /* CHANGE DIRECTORY USING NEW BATH PATH */
	basepath=gsGetBasePath();
#ifndef	USING_SDK8
	gdFsChangeDir(basepath);		// Only needed for below SDK8
#endif	

	/* load files */
	SoundInitialize( "MANATEE.DRV", "STREAM.MLT" );
	sdGddaSetVol( 127, 127 );
    sdGddaSetPan( 0x40, -( 0x80 - 0x40 ) );

	newcdda	=	gsGDDALogicalToPhysical	(4);
#ifndef USING_SDK8
    gdFsDaPlay( newcdda, newcdda, 0 );
#else
	gdFsDaPlay( 4, 4, 0 );			// translation automatic with SDK8
#endif

// Check for AUTODEMO mode
	if (strcmp("-auto",gsGetArgV(1))==0) autodemo=1;


    njInitVertexBuffer( 800000, 0, 200000, 0 ,0);
    njInitPrint(NULL, 0, 0);
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

    njSetBackColor(0x00000000,0x00000000,0x000000FF);

    njSetVSyncFunction(Count);
    njPrintSize(16);
        
}



Sint32 njUserMain(void)
{
    njClearMatrix();
    njTranslate( NULL, 0.f, 0.f, -12.f );
    njRotateXYZ( NULL, xx,yy,zz );
    njDrawObject( OBJECT );
    
    xx += 257;
    yy += 179;
    zz += 193;

	njPrintC(NJM_LOCATION(2,3),"DREAMSCENE COMPATIBLE");
#ifndef USING_SDK8
	njPrintC(NJM_LOCATION(2,4),"PATH = ");
	njPrintC(NJM_LOCATION(2,5),"CDDA = ");
	njPrintC(NJM_LOCATION(9,4),basepath);
	njPrintD(NJM_LOCATION(9,5),newcdda,2);
#else
	njPrintC(NJM_LOCATION(2,4),"PATH = AUTOMATIC : ");
	njPrintC(NJM_LOCATION(2,5),"CDDA = AUTOMATIC : ");
	njPrintC(NJM_LOCATION(21,4),basepath);
	njPrintD(NJM_LOCATION(21,5),newcdda,2);
#endif
	njPrintC(NJM_LOCATION(2,6),gsGetArgV(1));
	njPrintC(NJM_LOCATION(2,8),buf);
	if (autodemo==1) njPrintC(NJM_LOCATION(10,6),"AUTODEMO");
    
    sdSysServer();

    return nwExecute();
}


void main(void)
{
	UserInit();

	/* CALL GINSU EXECUTE IN MAIN LOOP, CHECK FOR EXIT CONDITION */
	while (gsExec()!=GS_FORCE_APP_EXIT) 
	{
		if (njUserMain() < 0) break;
		njWaitVSync();
	}

    nwExitSystem();
    njExitPrint();
    njExitTexture();
    sbExitSystem();
	
    /* GINSU EXIT IS CALLED AS VERY LAST FUNCTION CALL */
    gsExit();
}
