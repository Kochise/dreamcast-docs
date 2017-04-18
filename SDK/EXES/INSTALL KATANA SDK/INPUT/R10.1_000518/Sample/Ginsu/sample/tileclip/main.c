/************************************************************
  Ninja Sample
  COPYRIGHT (C) SEGA ENTERPRISES, LTD.

  タイトル ： 画面分割
  編集履歴 ： 98-08-27 製作開始
************************************************************/

#include <shinobi.h>
#include <njdef.h>
#include <sg_sycbl.h>
#include "ginsu.h"

void main(void)
{
#ifdef __GNUC__
	shinobi_workaround();
#endif
	njSetBorderColor( 0x00000000 );
    njUserInit();
    while (njUserMain() == NJD_USER_CONTINUE) {
        njWaitVSync();
    }
    njUserExit();
}

#define MAX_MATRIX_DEPTH 10
#define MAX_VERTEXES 4000

#define SPECULAR_CYCLE 500
#define SPECULAR_CHANGE_SPEED NJM_DEG_ANG(1.0F)

#define SCREEN_SAVE_TIME 30

extern NJS_CNK_OBJECT object__sphere3_sphere3[];

static NJS_MATRIX *Matrix;
static NJS_VERTEX_BUF *VertexBuffer;

static NJS_LIGHT light;
static NJS_VIEW View;

static NJS_POINT2 p1[2];
static NJS_POINT2 p2[2];
static NJS_POINT2 p3[2];
static NJS_POINT2 p4[2];

static NJS_SCREEN scr1;
static NJS_SCREEN scr2;
static NJS_SCREEN scr3;
static NJS_SCREEN scr4;

/*----------------------------------------------------------------------
           初期化
----------------------------------------------------------------------*/
void njUserInit(void)
{


	
    gsInit();
    
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
	/* 画面のアスペクト比を設定 */
    njSetAspect( 1.0F, 0.91F );
    /* メモリ割り当て */
    Matrix = syMalloc(sizeof(NJS_MATRIX) * MAX_MATRIX_DEPTH);
    VertexBuffer   = syMalloc(sizeof(NJS_VERTEX_BUF) * MAX_VERTEXES);
    /* 背景色の設定 */
    njSetBackColor(ARGB(0, 192, 0, 0), ARGB(0, 0, 192, 0), ARGB(0, 0, 0, 192));
    /* 頂点格納バッファの確保 */
    njInitVertexBuffer(MAX_VERTEXES * 64 / 4, 0, MAX_VERTEXES * 64 / 4, 0, 0);
	njInitPrint( NULL, 0, NJD_TEXFMT_ARGB_1555 );
    /* マトリクススタックの初期化 */
    njInitMatrix(Matrix, MAX_MATRIX_DEPTH, 1);
    /* 3Dシステムの初期化 */
    njInit3D(VertexBuffer, MAX_VERTEXES);
    njControl3D( NJD_CONTROL_3D_CNK_CONSTANT_ATTR );
    /* ビューの初期化 */
    njInitView(&View);
    /* ビューの設定 */
    njSetView(&View);
	/* ライトの設定 */
	njCreateLight(&light, NJD_SPEC_DIR);
	/* 文字色の設定 */
	njPrintColor(0xFFC0C0C0);
	/* 表示位置の調整 */
	njAdjustDisplay(0,8);

	p1[0].x = 0;	/* 0x32 = 0 */
	p1[0].y = 0;	/* 0x32 = 0 */
	p1[1].x = 9;	/* 9x32 = 288 */
	p1[1].y = 6;	/* 6x32 = 192 */

	p2[0].x = 10;	/* 10x32 = 320 */
	p2[0].y = 0;	/* 0x32 = 0 */
	p2[1].x = 19;	/* 19x32 = 608 */
	p2[1].y = 6;	/* 6x32 = 192 */

	p3[0].x = 0;	/* 0x32 = 0 */
	p3[0].y = 7;	/* 7x32 = 224 */
	p3[1].x = 9;	/* 9x32 = 288 */
	p3[1].y = 13;	/* 13x32 = 416 */

	p4[0].x = 10;	/* 10x32 = 320 */
	p4[0].y = 7;	/* 7x32 = 224 */
	p4[1].x = 19;	/* 19x32 = 608 */
	p4[1].y = 13;	/* 13x32 = 416 */

	scr1.dist = 250.f;
	scr1.w = 320.f;
	scr1.h = 240.f;
	scr1.cx = 160.f;
	scr1.cy = 120.f;

	scr2.dist = 250.f;
	scr2.w = 320.f;
	scr2.h = 240.f;
	scr2.cx = 480.f;;
	scr2.cy = 120.f;

	scr3.dist = 250.f;
	scr3.w = 320.f;
	scr3.h = 240.f;
	scr3.cx = 160.f;;
	scr3.cy = 360.f;

	scr4.dist = 250.f;
	scr4.w = 320.f;
	scr4.h = 240.f;
	scr4.cx = 480.f;;
	scr4.cy = 360.f;
}

/*----------------------------------------------------------------------
         メイン
----------------------------------------------------------------------*/
Sint32 njUserMain(void)
{
    NJS_PERIPHERAL *padinfo;
	
	static Angle rotateAng = NJM_DEG_ANG(0.0F);/* 回転角度用変数 */

    /* スクリーン座標の変更 */
	njSetScreen(&scr1);
	/* エリア１の内部に描画します */
	njUserClipping(NJD_CLIP_INSIDE, p1);
    /* シェーディングの設定 */
    njSetConstantAttr( 0xFFFFFFFF, NJD_FST_FL);
    /* サンプル名の表示 */
    njPrintC(NJM_LOCATION(4, 4), "Ninja Sample TILECLIP");
    /* マトリックススタックのクリア */
    njClearMatrix();
    /* 平行移動 */
    njTranslate(NULL, 0.F, 0.0F, -25.0F);
    /* X,Y,Z 軸の順番に回転 */
    njRotateXYZ(NULL, rotateAng, rotateAng, rotateAng);
    /* オブジェクトの描画 */
    njCnkDrawObject(object__sphere3_sphere3 );

    /* スクリーン座標の変更 */
	njSetScreen(&scr2);
	/*エリア２の 内部に描画します */
	njUserClipping(NJD_CLIP_INSIDE, p2);
    /* シェーディングの設定 */
    njSetConstantAttr( ~NJD_FST_FL, 0);
    /* マトリックススタックのクリア */
    njClearMatrix();
    /* 平行移動 */
    njTranslate(NULL, 0.0F, 0.0F, -25.0F);
    /* X,Y,Z 軸の順番に回転 */
    njRotateXYZ(NULL, rotateAng, rotateAng, rotateAng);
    /* オブジェクトの描画 */
    njCnkDrawObject(object__sphere3_sphere3 );

    /* スクリーン座標の変更 */
	njSetScreen(&scr3);
	/* エリア３の内部に描画します */
	njUserClipping(NJD_CLIP_INSIDE, p3);
    /* シェーディングの設定 */
    njSetConstantAttr( ~NJD_FST_FL, 0);
    /* マトリックススタックのクリア */
    njClearMatrix();
    /* 平行移動 */
    njTranslate(NULL, 0.0F, 0.0F, -25.0F);
    /* X,Y,Z 軸の順番に回転 */
    njRotateXYZ(NULL, rotateAng, rotateAng, rotateAng);
    /* オブジェクトの描画 */
    njCnkDrawObject(object__sphere3_sphere3 );

    /* スクリーン座標の変更 */
	njSetScreen(&scr4);
	/* エリア４の内部に描画します */
	njUserClipping(NJD_CLIP_INSIDE, p4);
    /* シェーディングの設定 */
    njSetConstantAttr( 0xFFFFFFFF, NJD_FST_FL);
    /* マトリックススタックのクリア */
    njClearMatrix();
    /* 平行移動 */
    njTranslate(NULL, 0.0F, 0.0F, -25.0F);
    /* X,Y,Z 軸の順番に回転 */
    njRotateXYZ(NULL, rotateAng, rotateAng, rotateAng);
    /* オブジェクトの描画 */
    njCnkDrawObject(object__sphere3_sphere3 );
	/* クリッピングを中止します */
	njUserClipping(NJD_CLIP_DISABLE, p4);

    rotateAng += SPECULAR_CHANGE_SPEED;

	/* Read controller info for an exit */
	padinfo = njGetPeripheral(NJD_PORT_A0);

	if(padinfo->press & NJD_DGT_TA)
	{
		return -1;
	}

	if(gsExec())
	{
		return -1; /* force and exit */
	}

    return NJD_USER_CONTINUE;
}

/*----------------------------------------------------------------------
         終了処理
----------------------------------------------------------------------*/
void njUserExit(void)
{
    /* メモリの開放 */
    syFree(Matrix);
    syFree(VertexBuffer);
    /* システムの終了 */
    njExitPrint();
    sbExitSystem();

	gsExit();
}
