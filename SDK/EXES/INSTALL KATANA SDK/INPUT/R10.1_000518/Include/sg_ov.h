/*
 *  Overlay Library
 *  Copyright (c) 1998 SEGA
 *  
 *      Overlay
 *
 *  Module  : Library Header File
 *  File    : sg_ov.h
 *  Create  : 1998-02-20
 *  Modify  : 1998-05-12
 *  Version : 0.41
 *  Note    :
 */
#ifndef _SG_OV_H_
#define _SG_OV_H_

#include	<sg_xpt.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*	Version No.	*/
#define	OVD_VER					"1.00"

/*  ƒ‰ƒCƒuƒ‰ƒŠ‚Ìƒo[ƒWƒ‡ƒ"(Ver.1.00)		*/
#define	OVD_VERSION_NO			(0x01)		/*  ƒo[ƒWƒ‡ƒ""Ô†				*/
#define	OVD_REVISION_NO			(0x00)		/*  ƒŠƒrƒWƒ‡ƒ""Ô†				*/

/*	Universally Unique Identifier	*/
#ifndef UUID_DEFINED
#define UUID_DEFINED
typedef struct _UUID
{
    Uint32	Data1;
    Uint16	Data2;
    Uint16	Data3;
    Uint8	Data4[8];
} UUID;
typedef UUID Uuid;
#endif

/*	ƒ‰ƒCƒuƒ‰ƒŠID‚Ì'è‹`		*/
#define OVD_LID { \
	0xba7e0a00, 0xbda9, 0x11d1, 0x8a, 0xeb, 0x00, 0x60, 0x08, 0x95, 0x62, 0x5f\
}\

/*	ƒGƒ‰[ƒR[ƒh	*/
typedef enum {
	OVE_ERR_OK				= 0,		/*  ³íI—¹					*/
	OVE_ERR_INVALID_FORMAT	= -1,		/*  •s³‚ÈƒtƒH[ƒ}ƒbƒg			*/
	OVE_ERR_INVALID_LIB_ID	= -2,		/*  •s³‚Èƒ‰ƒCƒuƒ‰ƒŠID			*/
	OVE_ERR_INVALID_LIB_HDL	= -3		/*  •s³‚Èƒ‰ƒCƒuƒ‰ƒŠƒnƒ"ƒhƒ‹	*/
} OVE_ERR;


/*	ƒ‰ƒCƒuƒ‰ƒŠƒnƒ"ƒhƒ‹	*/
typedef struct {
	struct _ov_lif	*lif;			/*	ƒ‰ƒCƒuƒ‰ƒŠƒCƒ"ƒ^ƒtƒF[ƒX			*/
	Uint8			ver;			/*	ƒo[ƒWƒ‡ƒ""Ô†						*/
	Uint8			revi;			/*	ƒŠƒrƒWƒ‡ƒ""Ô†						*/
	Sint16			rsv1;			/*	—\–ñ 1								*/
	Sint32			rsv2;			/*	—\–ñ 2								*/
	Sint32			rsv3;			/*	—\–ñ 3								*/
	UUID    		lid;			/*	ƒ‰ƒCƒuƒ‰ƒŠID						*/
} OVS_LIB_OBJ;
typedef OVS_LIB_OBJ *OVLIB;

/*	Šeƒ‰ƒCƒuƒ‰ƒŠ‚ª•K‚¸ì¬‚·‚éƒ‰ƒCƒuƒ‰ƒŠƒCƒ"ƒ^ƒtƒF[ƒXŠÖ"  				*/
typedef struct _ov_lif {
	void (*QueryInterface)();		/*		for COM compatibility			*/
	void (*AddRef)();				/*		for COM compatibility			*/
	void (*Release)();				/*		for COM compatibility			*/
	void (*Init)(OVLIB ovl);		/*		‰Šú‰»							*/
	void (*Finish)(OVLIB ovl);		/*		I—¹ˆ—						*/
	void (*Exec)(OVLIB ovl);		/*		Às							*/
} OVS_LIB_IF;
typedef OVS_LIB_IF *OVLIB_IF;

/***
*		Àsƒ‚ƒWƒ…[ƒ‹‚Ì‚½‚ß‚ÌŠÖ"
***/

/*	Àsƒ‚ƒWƒ…[ƒ‹ƒnƒ"ƒhƒ‹	*/
typedef struct {
	Sint32	rsv[8];
	OVS_LIB_OBJ libobj[1];
} OVS_MDL_OBJ;
typedef OVS_MDL_OBJ *OVMDL;

/***
*			ƒ‰ƒCƒuƒ‰ƒŠ"à•"‚Ì‚½‚ß‚Ì'è‹`
***/

/*	ƒNƒŠƒeƒBƒJƒ‹ƒZƒNƒVƒ‡ƒ"	*/
typedef Sint32 OV_CS;

/*	ƒ‰ƒCƒuƒ‰ƒŠŠÇ—ƒe[ƒuƒ‹‚Ö‚Ìƒ|ƒCƒ"ƒ^‚ÌƒAƒhƒŒƒX	*/
#define	OVD_LIBTBL_ADR_PTR	(0x8C00FFF0)
/*	ƒ‰ƒCƒuƒ‰ƒŠŠÇ—ƒe[ƒuƒ‹‚ÌÅ'å"o˜^"‚Ö‚ÌƒAƒhƒŒƒX	*/
#define	OVD_LIBTBL_ADR_MAX	(0x8C00FFF4)
/*	ƒ‰ƒCƒuƒ‰ƒŠŠÇ—ƒe[ƒuƒ‹‚ÌƒAƒhƒŒƒX	*/
#define	OVD_DEF_LIBTBL_ADR	(0x8C00FC00)

/*	ƒ‰ƒCƒuƒ‰ƒŠŠÇ—ƒe[ƒuƒ‹‚ÌÅ'å"o˜^"	*/
#define	OVD_DEF_LIBTBL_MAX	(120)

/*	ƒ‰ƒCƒuƒ‰ƒŠŠÇ—ƒe[ƒuƒ‹	*/
typedef struct {
	Sint32	nlib;				/* "o˜^‚³‚ê‚Ä‚¢‚éƒ‰ƒCƒuƒ‰ƒŠ"				*/
	Sint32	rsv1;				/* —\–ñ‚P									*/
	struct {
		OVLIB	lib;			/* ƒ‰ƒCƒuƒ‰ƒŠƒnƒ"ƒhƒ‹						*/
		Sint32	ref;			/* QÆƒJƒEƒ"ƒ^								*/
	} entry[1];
} OVS_LIBTBL;

/***
*		ŠÖ"éŒ¾
***/

/*	ƒ‰ƒCƒuƒ‰ƒŠƒnƒ"ƒhƒ‹‚Ìæ"¾												*/
OVLIB ovLibOpen(UUID *lid);
/*	ƒ‰ƒCƒuƒ‰ƒŠƒnƒ"ƒhƒ‹‚ÌŠJ•ú												*/
void ovLibClose(UUID *lid);
/*	ƒ‚ƒWƒ…[ƒ‹ƒtƒ@ƒCƒ‹‚Ì"Ç‚İ‚İ											*/
OVE_ERR ovMdlEntryTbl(OVMDL ovmdl);
/*	ƒ‚ƒWƒ…[ƒ‹ƒtƒ@ƒCƒ‹‚ÌŠJ•ú												*/
OVE_ERR ovMdlDeleteTbl(OVMDL ovmdl);
/*  Àsƒ‚ƒWƒ…[ƒ‹‚ÌÀs													*/
Sint32 ovMdlExec(OVMDL ovmdl);

/*  ƒ‰ƒCƒuƒ‰ƒŠƒCƒ"ƒ^ƒtƒF[ƒX‚Ìæ"¾											*/
OVLIB_IF ovLibGetLibIf(OVLIB lib);
/*  ƒ‰ƒCƒuƒ‰ƒŠ‚Ìƒo[ƒWƒ‡ƒ"‚Ìæ"¾											*/
void ovLibGetVersion(OVLIB lib, Uint8 *ver, Uint8 *revi);
/*  ƒ‰ƒCƒuƒ‰ƒŠID‚Ìæ"¾														*/
UUID *ovLibGetUuid(OVLIB lib);

/*  ƒ‰ƒCƒuƒ‰ƒŠŠÇ—ƒ‰ƒCƒuƒ‰ƒŠ‚Ì‰Šú‰» ('Êíg—p‚µ‚È‚¢j						*/
void ovInit(void *ovltbl, Sint32 nlib);
/*  ƒ‰ƒCƒuƒ‰ƒŠŠÇ—ƒ‰ƒCƒuƒ‰ƒŠ‚ÌI—¹ˆ— ('Êíg—p‚µ‚È‚¢j					*/
void ovFinish(void);
/*	ƒ‰ƒCƒuƒ‰ƒŠƒnƒ"ƒhƒ‹‚Ì"o˜^												*/
OVE_ERR ovLibEntryTbl(OVLIB lib);
/*	ƒ‰ƒCƒuƒ‰ƒŠƒnƒ"ƒhƒ‹‚Ìíœ												*/
OVE_ERR ovLibDeleteTbl(OVLIB lib);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif     /*  _SG_OV_H_	*/

