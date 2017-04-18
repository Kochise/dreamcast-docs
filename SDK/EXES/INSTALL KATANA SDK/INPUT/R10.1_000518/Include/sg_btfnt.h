/*======================================================================
 *      sg_byFnt.h -- Font data
 *      Copyright(c) SEGA ENTERPRISES, LTD., 1998
 *      Ver.0.51(1998-07-09) Written by SEKI Masahiro
 *      Ver.0.60(1998-08-24) Added Shift JIS interface by SEKI Masahiro
 *======================================================================*/
#ifndef _SG_BTFNT_H_
#define _SG_BTFNT_H_

#define INCLUDE_VMS_ICON (1)

/*** Boot ROM Access interface ******************************************/
/*
 * each offset and each size in Boot ROM Font
 */
#define SYD_BT_FNT_ASCII_24_OFS  (0)
#define SYD_BT_FNT_ASCII_24_SIZE (96*12*24/8)
#define SYD_BT_FNT_WEST_24_OFS   (SYD_BT_FNT_ASCII_24_OFS+SYD_BT_FNT_ASCII_24_SIZE)
#define SYD_BT_FNT_WEST_24_SIZE  (96*12*24/8)
#define SYD_BT_FNT_JISX_24_OFS   (SYD_BT_FNT_WEST_24_OFS+SYD_BT_FNT_WEST_24_SIZE)
#define SYD_BT_FNT_JISX_24_SIZE  (96*12*24/8)
#define SYD_BT_FNT_KANA_24_OFS   (SYD_BT_FNT_JISX_24_OFS+SYD_BT_FNT_JISX_24_SIZE)
#define SYD_BT_FNT_KANA_24_SIZE  (47376)
#define SYD_BT_FNT_LVL1_24_OFS   (SYD_BT_FNT_KANA_24_OFS+SYD_BT_FNT_KANA_24_SIZE)
#define SYD_BT_FNT_LVL1_24_SIZE  (216576)
#define SYD_BT_FNT_LVL2_24_OFS   (SYD_BT_FNT_LVL1_24_OFS+SYD_BT_FNT_LVL1_24_SIZE)
#define SYD_BT_FNT_LVL2_24_SIZE  (244080)
#if INCLUDE_VMS_ICON /* 19980824 */
#define SYD_BT_FNT_GAIJ_24_OFS   (SYD_BT_FNT_LVL2_24_OFS+SYD_BT_FNT_LVL2_24_SIZE)
#define SYD_BT_FNT_GAIJ_24_SIZE  (0x630)
#define SYD_BT_FNT_VMSICON_OFS   (SYD_BT_FNT_GAIJ_24_OFS+SYD_BT_FNT_GAIJ_24_SIZE)
#define SYD_BT_FNT_VMSICON_SIZE  (129*32*32/8)
#define SYD_BT_FNT_ASCII_12_OFS  (0)
#define SYD_BT_FNT_ASCII_12_SIZE (0)
#else
#define SYD_BT_FNT_ASCII_12_OFS  (SYD_BT_FNT_LVL2_24_OFS+SYD_BT_FNT_LVL2_24_SIZE)
#define SYD_BT_FNT_ASCII_12_SIZE (1728)
#define SYD_BT_FNT_GAIJ_24_OFS   (SYD_BT_FNT_ASCII_12_OFS+SYD_BT_FNT_ASCII_12_SIZE)
#define SYD_BT_FNT_GAIJ_24_SIZE  (56*24*24/8)
#define SYD_BT_FNT_VMSICON_OFS   (0)
#define SYD_BT_FNT_VMSICON_SIZE  (0)
#endif /* 19980824 */
/*
 * pixels of font
 */
#define SYD_BT_FNT_24_WIDTH_HAN (12)
#define SYD_BT_FNT_24_WIDTH_ZEN (24)
#define SYD_BT_FNT_24_HEIGHT    (24)
#define SYD_BT_FNT_12_WIDTH     (0)
#define SYD_BT_FNT_12_HEIGHT    (0)
#define SYD_BT_FNT_24_SIZE_HAN  (SYD_BT_FNT_24_WIDTH_HAN * SYD_BT_FNT_24_HEIGHT / 8)
#define SYD_BT_FNT_24_SIZE_ZEN  (SYD_BT_FNT_24_WIDTH_ZEN * SYD_BT_FNT_24_HEIGHT / 8)
#define SYD_BT_FNT_12_SIZE      (SYD_BT_FNT_12_WIDTH * SYD_BT_FNT_12_HEIGHT / 8)
#if INCLUDE_VMS_ICON /* 19980824 */
#define SYD_BT_FNT_ICON_WIDTH  (32)
#define SYD_BT_FNT_ICON_HEIGHT (32)
#define SYD_BT_FNT_ICON_SIZE   (SYD_BT_FNT_ICON_WIDTH*SYD_BT_FNT_ICON_HEIGHT/8)
#endif /* 19980824 */

#define SYD_BT_FNTINI    (0)

#define SYD_BT_FNT_SMPH_SUCCESS (0)
#define SYD_BT_FNT_SMPH_FAILURE (-1)

extern void *syBtFntGet( Uint32 num );
extern Sint32 syBtFntChkSmph( void );
extern void syBtFntClrSmph( void );


/*** Shift JIS code interface *******************************************/
/*
 * ascii code information and SJIS code information
 */
#define SYD_BT_FNT_CODE_ASCII_MIN (0x0020)
#define SYD_BT_FNT_CODE_ASCII_MAX (0x007f)
#define SYD_BT_FNT_CODE_8BIT_MIN  (0x00a0)
#define SYD_BT_FNT_CODE_8BIT_MAX  (0x00ff)
#define SYD_BT_FNT_CODE_KANA_MIN  (0x8140)
#define SYD_BT_FNT_CODE_KANA_MAX  (0x8396)
#define SYD_BT_FNT_CODE_LVL1_MIN  (0x889f)
#define SYD_BT_FNT_CODE_LVL1_MAX  (0x9872)
#define SYD_BT_FNT_CODE_LVL2_MIN  (0x989f)
#define SYD_BT_FNT_CODE_LVL2_MAX  (0xeaa4)
#define SYD_BT_FNT_JIS_SPACE      (0x2121)
#define SYD_BT_FNT_SJIS_SPACE     (0x8140)
#define SYD_BT_FNT_ASCII_SPACE    (0x20)
#define SYD_BT_FNT_SJIS_GETA      (0x81ac)
#if 1 /* 19980828 */
#define SYD_BT_FNT_GAIJ_MIN       (0)
#define SYD_BT_FNT_GAIJ_MAX       (21)
#define SYD_BT_FNT_ICON_MIN       (0)
#define SYD_BT_FNT_ICON_MAX       (128)
#endif /* 19980828 */

#define SYD_BT_FNT_FIRSTINDEX_LVL1 ((0x0030-0x0021)*((0x007e)-0x0021+1)+(0x0021-0x0021))
#define SYD_BT_FNT_FIRSTINDEX_LVL2 ((0x0050-0x0021)*((0x007e)-0x0021+1)+(0x0021-0x0021))

/*** GAIJ code *********************************************************/
#define SYD_BT_FNT_CODE_GAIJ_COPY       (0)   /* COPY RIGHT (C)        */
#define SYD_BT_FNT_CODE_GAIJ_REG        (1)   /* REGISTRATION (R)      */
#define SYD_BT_FNT_CODE_GAIJ_TRADE      (2)   /* TRADE MARK            */
#define SYD_BT_FNT_CODE_GAIJ_S_UP       (3)   /* DIGITAL UP            */
#define SYD_BT_FNT_CODE_GAIJ_S_DN       (4)   /* DIGITAL DOWN          */
#define SYD_BT_FNT_CODE_GAIJ_S_LE       (5)   /* DIGITAL LEFT          */
#define SYD_BT_FNT_CODE_GAIJ_S_RI       (6)   /* DIGITAL RIGHT         */
#define SYD_BT_FNT_CODE_GAIJ_S_RU       (7)   /* DIGITAL RIGHT UP      */
#define SYD_BT_FNT_CODE_GAIJ_S_RD       (8)   /* DIGITAL RIGHT DOWN    */
#define SYD_BT_FNT_CODE_GAIJ_S_LD       (9)   /* DIGITAL LEFT DOWN     */
#define SYD_BT_FNT_CODE_GAIJ_S_LU       (10)  /* DIGITAL LEFT UP       */
#define SYD_BT_FNT_CODE_GAIJ_TA         (11)  /* TRIGGER A             */
#define SYD_BT_FNT_CODE_GAIJ_TB         (12)  /* TRIGGER B             */
#define SYD_BT_FNT_CODE_GAIJ_TC         (13)  /* TRIGGER C             */
#define SYD_BT_FNT_CODE_GAIJ_TD         (14)  /* TRIGGER D             */
#define SYD_BT_FNT_CODE_GAIJ_TX         (15)  /* TRIGGER X             */
#define SYD_BT_FNT_CODE_GAIJ_TY         (16)  /* TRIGGER Y             */
#define SYD_BT_FNT_CODE_GAIJ_TZ         (17)  /* TRIGGER Z             */
#define SYD_BT_FNT_CODE_GAIJ_TL         (18)  /* TRIGGER L             */
#define SYD_BT_FNT_CODE_GAIJ_TR         (19)  /* TRIGGER R             */
#define SYD_BT_FNT_CODE_GAIJ_TS         (20)  /* TRIGGER START         */
#define SYD_BT_FNT_CODE_GAIJ_S1         (21)  /* SPECIAL 1             */
#define SYD_BT_FNT_CODE_GAIJ_S2         (22)  /* SPECIAL 2             */

/*** VMS ICON code *****************************************************/
#define SYD_BT_FNT_ICON_UNFMT           (0)   /* UNFORMAT              */
#define SYD_BT_FNT_ICON_HOUR0           (1)   /* HOURGRASS 0           */
#define SYD_BT_FNT_ICON_HOUR1           (2)   /* HOURGRASS 1           */
#define SYD_BT_FNT_ICON_HOUR2           (3)   /* HOURGRASS 2           */
#define SYD_BT_FNT_ICON_HOUR3           (4)   /* HOURGRASS 3           */
#define SYD_BT_FNT_ICON_OFS             (5)   /* designed icon 0       */
#define SYD_BT_FNT_ICON_NUM             (124) /* number of icons       */
#define SYD_BT_FNT_ICON_END             (128) /* designed icon 123     */


#if 1 /* 19980824 */
typedef struct tag_SYS_BT_FNT_INFO {
	Uint8  width;                     /* Width of a font graphic          */
	Uint8  height;                    /* Height of a font graphic         */
} SYS_BT_FNT_INFO;

#if INCLUDE_VMS_ICON
typedef enum {
	SYE_BT_FNT_FONTSET_WESTERN_24,              /* ISO 8859-1 12x24      */
	SYE_BT_FNT_FONTSET_JP_JIS_24,               /* JIS X 0201 12x24      */
	SYE_BT_FNT_FONTSET_JP_KANA_24,              /* Shift JIS 24x24       */
	SYE_BT_FNT_FONTSET_JP_LVL1_24,              /* Shift JIS 24x24       */
	SYE_BT_FNT_FONTSET_JP_LVL2_24,              /* Shift JIS 24x24       */
	SYE_BT_FNT_FONTSET_JP_GAIJ_24,              /* SEGA specific font    */
	SYE_BT_FNT_FONTSET_VMSICON,                 /* VMS ICONS             */
	SYE_BT_FNT_FONTSET_END,
	SYE_BT_FNT_FONTSET_JP_ASCII_12,             /* Shift JIS 24x24       */
	SYE_BT_FNT_FONTSET_JP_ASCII_JP_12           /* ASCII yen, overline   */
} SYE_BT_FNT_FONTSET;
#else
typedef enum {
	SYE_BT_FNT_FONTSET_WESTERN_24,              /* ISO 8859-1 12x24      */
	SYE_BT_FNT_FONTSET_JP_JIS_24,               /* JIS X 0201 12x24      */
	SYE_BT_FNT_FONTSET_JP_KANA_24,              /* Shift JIS 24x24       */
	SYE_BT_FNT_FONTSET_JP_LVL1_24,              /* Shift JIS 24x24       */
	SYE_BT_FNT_FONTSET_JP_LVL2_24,              /* Shift JIS 24x24       */
	SYE_BT_FNT_FONTSET_JP_ASCII_12,             /* Shift JIS 24x24       */
	SYE_BT_FNT_FONTSET_JP_ASCII_JP_12,          /* ASCII yen, overline   */
	SYE_BT_FNT_FONTSET_JP_GAIJ_24,              /* SEGA specific font    */
	SYE_BT_FNT_FONTSET_END,
	SYE_BT_FNT_FONTSET_VMSICON                  /* VMS ICONS             */
} SYE_BT_FNT_FONTSET;
#endif /* INCLUDE_VMS_ICON */
#endif /* 19980824 */

#if 1 /* 19980824 */
/*** Basic functions *****************************************************/
Uint32 syBtFntGetAddr( SYE_BT_FNT_FONTSET set, Sint16 code );
void syBtFntGetInfo( SYE_BT_FNT_FONTSET set, Sint16 code, SYS_BT_FNT_INFO *info );
/*** Utility functions ***************************************************/
Sint16 syBtFntSjis2Jis( Sint16 sjis );
#endif /* 19980824 */

#endif /* _SG_BTFNT_H_ */
