/*
 *
 *		SofdecF/X Sample for Kamui2 (Textured movie)
 *
 */

/***************************************************************************
 *      インクルードファイル
 *      Include file
 ***************************************************************************/

#include	<string.h>
#include	"shinobi.h"

#define		_STRICT_UNION_		/* for kamui2.h */
#include	"kamui2.h"

#include	"sg_mw.h"
#include	"usr.h"


/***************************************************************************
 *      定数マクロ
 *      MACRO CONSTANT
 ***************************************************************************/

/***************************************************************************
 *      処理マクロ
 *      Process MACRO
 ***************************************************************************/

/*	フラグON/OFFの反転		*/
/*	Turn over flag(ON/OFF)	*/
#define NOT_FLAG(flag)		(((flag) == OFF) ? ON : OFF)

#define	RGBA(r, g, b, a)	\
		((KMUINT32) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b)))

//	The resolution of this movie is 320 x 240
#define	U_MV	(320.0f/512.0f)
#define	V_MV	(240.0f/256.0f)

/***************************************************************************
 *      変数定義
 *		Variable Declaration
 ***************************************************************************/

/*	アプリケーション構造体											*/
/*	Application structure											*/
typedef struct {
	Sint32	term_flag;					//	Application terminate flag
	Sint32	disp_flag;					//	Display information flag
	Sint32	pause;						//	Pause flag
	Sint32	trnsfrm_flag;				//	Transform flag
	char	*fname;						//	File name
	MWPLY	ply;						//	Player
	Sint32 frame;						//	frame counter
	KMVERTEX_03	Vertices[4];			//	Vertex
	KMSTRIPCONTEXT StripContext;		// Strip Context
	KMSTRIPHEAD StripHead;				// Strip Head
	KMVERTEXBUFFDESC *VertexBufferDesc;	//	Vertex buffer
	MWS_PLY_CPRM_SFD cprm;				//	Create parameter
} AP_OBJ, *AP;

/*	アプリケーションオブジェクト									*/
/*	Application Object												*/
AP_OBJ ap_obj = {
	OFF,						//	Execute App.
	OFF,						//	Display Info.
	OFF,						//	not puase
//	OFF,						//	not transform
	ON,
	"SAMPLE.SFD",				//	File name
	NULL,						//	Player
	0,							//	frame
	{
		/* ParamControlWord             X,      Y,    Z,    U,    V,   Base Color,  Offset Color */
		{ KM_VERTEXPARAM_NORMAL,     320.0f, 479.0f, 0.5f, 0.0f, V_MV, RGBA(255, 255, 255, 255), 0 },
		{ KM_VERTEXPARAM_NORMAL,       0.0f, 240.0f, 0.5f, 0.0f, 0.0f, RGBA(255, 255, 255, 255), 0 },
		{ KM_VERTEXPARAM_NORMAL,     639.0f, 240.0f, 0.5f, U_MV, V_MV, RGBA(255, 255, 255, 255), 0 },
		{ KM_VERTEXPARAM_ENDOFSTRIP, 320.0f,   0.0f, 0.5f, U_MV, 0.0f, RGBA(255, 255, 255, 255), 0 }
	}
};

/***************************************************************************
 *      関数定義
 *      Function Declaration
 ***************************************************************************/

/***
 *			ミドルウェアの再生
 *			Playing middleware
 ***/

/*	ミドルウェアのエラー発生時に起動する関数			*/
/*	Callback function when an error occur in middleware	*/
void ap_mw_err_func(void *obj, char *errmsg)
{
	AP ap=(AP)obj;

	for (;;);
}

/*	ミドルウェアの初期化				*/
/*	Initialize Middleware				*/
void ApInitMw(AP ap,
		Sint32 mod, Sint32 frm, Sint32 cnt, Sint32 ltncy, void *vtxbuf)
{
	MWS_PLY_INIT_SFD	iprm;

	memset(&iprm, 0, sizeof(iprm));	/*	予約メンバのゼロ設定			*/
									/*	initialize reserved member		*/
	iprm.mode		= mod;			/*	Resolution, NTSC, PAL, VGA		*/
	iprm.frame		= frm;			/*	RGB565, ARGB8888				*/
	iprm.count		= cnt;			/*	Game period by the V-Sync count */
	iprm.latency	= ltncy;		/*	Latency (2V or 3V)				*/
#ifdef NINJA1
	mwPlyInitSofdec(&iprm);
#else
	mwPlyInitSfdFx(&iprm);
	mwPlySetVertexBuffer(vtxbuf);
#endif
	mwPlyEntryErrFunc(ap_mw_err_func, ap);
}

/*	ミドルウェアの終了					*/
/*	Finalize Middleware					*/
void ApFinishMw(AP ap)
{
#ifdef	NINJA1
	mwPlyFinishSofdec();
#else
	mwPlyFinishSfdFx();
#endif
}

/*	アプリケーション開始処理	*/
/*	Start application		*/
void ApStart(AP ap)
{
	MWS_PLY_CPRM_SFD		*cprm=&ap->cprm;

	/*	ハンドルの生成	*/
	/*	Create handle	*/
	memset(cprm, 0, sizeof(MWS_PLY_CPRM_SFD));
	memset(cprm, 0, sizeof(MWS_PLY_CPRM_SFD));
	cprm->compo_mode	= MWD_PLY_COMPO_OPEQ;
	cprm->ftype			= MWD_PLY_FTYPE_SFD;
	cprm->dtype			= MWD_PLY_DTYPE_AUTO;
	cprm->max_bps		= 450*1024*8;
	cprm->max_width		= 352;
	cprm->max_height	= 240;
	cprm->nfrm_pool_wk	= 6;
	cprm->wksize	= mwPlyCalcWorkCprmSfd(cprm);
	cprm->work = syMalloc(cprm->wksize);
	if ((ap->ply = mwPlyCreateSofdec(cprm)) == NULL)
		for (;;) ;
	mwPlySetVideoSw(ap->ply, 0);		//	Back ground movie is OFF
}

/*	アプリケーション停止処理	*/
/*	Stop application		*/
void ApStop(AP ap)
{
	mwPlyStop(ap->ply);					/*	再生停止 					*/
										/*	Stop to play middleware		*/
	mwPlyDestroy(ap->ply);				/*	ハンドル消去				*/
										/*	Destroy handle				*/
	ap->ply = NULL;
	syFree(ap->cprm.work);				/*	作業領域の開放				*/
										/*	Release work area			*/
	ap->cprm.work = NULL;
}

/*	情報の表示			*/
/*	Display infomation	*/
void ap_disp_info(AP ap)
{
	Sint32	time, tunit, hh, mm, ss, ff;

	mwPlyGetTime(ap->ply, &time, &tunit);
	UsrSfcnt2time(tunit, time, &hh, &mm, &ss, &ff);
	UsrPrintf(0, 0, "File: %s  Time:%02d:%02d:%02d.%02d", 
							ap->fname, hh, mm, ss, ff);
}

/*	動画の再生					*/
/*	Playing the animation file	*/
Sint32 ApExec(AP ap)
{
	MWPLY					ply=ap->ply;
	MWE_PLY_STAT			stat;
	const PDS_PERIPHERAL	*per;
	MWS_PLY_MVFRM			frm;

	per = pdGetPeripheral(PDD_PORT_A0);
	if (per->press & PDD_DGT_ST) {
		ap->pause = NOT_FLAG(ap->pause);
		mwPlyPause(ply, ap->pause);		/*	一時停止解除			*/
										/*	Release pause status	*/
	}
	if (per->press & PDD_DGT_TA)
		ap->disp_flag = NOT_FLAG(ap->disp_flag);
	if (per->press & PDD_DGT_TB)
		return FALSE;
	if (per->press & PDD_DGT_TX)
		mwPlySetVideoSw(ply, NOT_FLAG(mwPlyGetVideoSw(ply)));
	if (per->press & PDD_DGT_TY)
		ap->trnsfrm_flag = NOT_FLAG(ap->trnsfrm_flag);

	/*	Checking status												*/
	stat = mwPlyGetStat(ply);
	if ((stat == MWE_PLY_STAT_STOP) || (stat == MWE_PLY_STAT_PLAYEND)) {
		/*	The sofdec library has a small bug.								*/
		/*	So you have to call mwPlyStop() to erase the previous frame.	*/
		/*	If you don't call mwPlyStop(), the last frame of previous movie */
		/*	will display when the next movie start 						 	*/
		mwPlyStop(ap->ply);
		mwPlyStartFname(ap->ply, ap->fname);
	}
	if (stat == MWE_PLY_STAT_ERROR )
		return FALSE;
	if ( ap->disp_flag == ON )
		ap_disp_info(ap);

	/*	動画サーフェスの設定				*/
	/*	Set movie surface 					*/
	if ( mwPlyGetMvFrm(ply, &frm) == 1 ) {
		//	Set the movie surface
		ap->StripContext.ImageControl[KM_IMAGE_PARAM1].pTextureSurfaceDesc = frm.srf;
		/* Generate Strip Head */
		kmGenerateStripHead03( &ap->StripHead, &ap->StripContext );

		kmStartStrip(ap->VertexBufferDesc, &ap->StripHead);
		/* Send 4 vertex data */
		kmSetVertex(ap->VertexBufferDesc,
				&ap->Vertices[0], KM_VERTEXTYPE_03, sizeof(KMVERTEX_03));
		kmSetVertex(ap->VertexBufferDesc,
				&ap->Vertices[1], KM_VERTEXTYPE_03, sizeof(KMVERTEX_03));
		kmSetVertex(ap->VertexBufferDesc,
				&ap->Vertices[2], KM_VERTEXTYPE_03, sizeof(KMVERTEX_03));
		kmSetVertex(ap->VertexBufferDesc,
				&ap->Vertices[3], KM_VERTEXTYPE_03, sizeof(KMVERTEX_03));
		kmEndStrip(ap->VertexBufferDesc );

		if ( ap->trnsfrm_flag ) {
			ap->frame++;
			ap->Vertices[1].fY = ( 64 - abs(ap->frame - 64)) * 5.0f - 5.0f;
			ap->Vertices[2].fY = 645.0f - ( 64 - abs(ap->frame - 64)) * 5.0f;
			if( ap->frame >= 128 )
				ap->frame = 0;
		}
	}

	return TRUE;
}

/***
 *		メイン処理
 *		MAIN
 ***/

/*	GDファイルシステムのエラー発生時に起動する関数			*/
/*	Callback function when an error occur in GD file system	*/
void ApGdErrFunc(void *obj, Sint32 errcode)
{
	AP ap=(AP)obj;
	if (errcode == GDD_ERR_TRAYOPEND || errcode == GDD_ERR_UNITATTENT)
		ap->term_flag = ON;			/*	アプリケーションの終了		*/
									/*	Terminate application		*/
}

/*	ユーザがV-SYNC割り込みに登録する関数	*/
/*	Callback function when V-sync interrupt	*/
void ApVsyncFunc(void)
{
	UsrCheckDoorOpen();
}

/*	3D ライブラリの初期化										*/
/*	Initialize 3D Library										*/
void ApInit3D(AP ap)
{
	/* Initialize Strip context */
	ap->StripContext.nSize = sizeof(KMSTRIPCONTEXT);
	kmInitStripContext(
		KM_STRIPCONTEXT_SYS_GOURAUD | KM_OPAQUE_POLYGON, &ap->StripContext );
}

/*	3D ライブラリの終了					*/
/*	Finalize 3D Library					*/
void ApFinish3D(AP ap)
{
}

void main(void)
{
	AP ap=&ap_obj;
	void *vtxbuf;
	Sint32 mode, frame, count, latency;
	Bool ret;

#ifdef __GNUC__
	shinobi_workaround();
#endif

	/*	ミドルウェアのためのシステム初期化 (sbInitSystemの前に置く)	*/
	/*	Initialize system for middleware(call before sbInitSystem)	*/
	mwPlyPreInitSofdec();

	/*	忍ライブラリとビデオの初期化								*/
	/*	Initialize SHINOBI & Video Sysytem							*/
	vtxbuf = UsrInitVideo(&mode, &frame, &count, &latency);
	ap->VertexBufferDesc = (KMVERTEXBUFFDESC *)vtxbuf;

	/*	GDファイルシステムエラーコールバック関数の登録				*/
	/*	Entry callback function of GD file system error				*/
	gdFsEntryErrFuncAll((void *)ApGdErrFunc, ap);

	/*	サウンドシステムの初期化									*/
	/*	Initialize sound system										*/
	UsrInitSound();

	/*	V-Sync 割り込み処理の登録									*/
	/*	Register V-Sync interrupt func								*/
	UsrSetVsyncFunc((void (*)(void))ApVsyncFunc);

	/*	3D ライブラリの初期化										*/
	/*	Initialize 3D Library										*/
	ApInit3D(ap);

	/*	ミドルウェアライブラリ初期化								*/
	/*	Initialize middleware										*/
	ApInitMw(ap, mode, frame, count, latency, vtxbuf);

	/*	Frame Work	*/
	while ( ap->term_flag == OFF ) {
		ApStart(ap);
		while (1) {
			mwPlyExecTexSvr();			/*	Load Texture To V-RAM			*/
			UsrBeginDraw();
			mwPlyExecDrawSvr();			/*	Draw polygons 					*/
			ret = ApExec(ap);
			UsrEndDraw();
			if ( ret == FALSE || ap->term_flag == ON )
				break;
			UsrWaitVBlank();
		}
		ApStop(ap);
	}
	/*	アプリケーション終了処理	*/
	/*	Finalize application		*/
	ApFinish3D(ap);			/*	3D ライブラリの終了					*/
							/*	Finalize 3D Library					*/
	ApFinishMw(ap);			/*	ミドルウェアの終了					*/
							/*	Finalize Middleware					*/
	sbExitSystem();			/*	忍ライブラリの終了処理				*/
							/*	Finalize SHINOBI					*/
	syBtExit();				/*	シンプルプレイヤへジャンプ			*/
							/*	Jump to Simple player				*/
}

/* End of file */
