#ifndef _PLATUTIL_H_
#define _PLATUTIL_H_

#ifdef __cplusplus
extern "C" {
#endif

void * __cdecl FastMemcpy(void *, const void *, size_t);

BOOL IsDevelopmentStation(VOID);

// The following are the values that GetVideoOutputFormat can return
#define VIDFMT_NTSC_RGB     0x02
#define VIDFMT_NTSC		    0x03
#define VIDFMT_PAL_RGB	    0x12
#define VIDFMT_PAL		    0x13
#define VIDFMT_PAL_M_RGB    0x22
#define VIDFMT_PAL_M        0x23
#define VIDFMT_PAL_N_RGB    0x32
#define VIDFMT_PAL_N        0x33
#define VIDFMT_VGA		    0x40

// The following are how the above values are generated
#define VIDFMT_CONNECTOR_MASK       0x0F
#define VIDFMT_FORMAT_MASK          0xF0

#define VIDFMT_CONNECTOR_VGA        0x00
#define VIDFMT_CONNECTOR_RGB        0x02
#define VIDFMT_CONNECTOR_COMPOSITE  0x03
#define VIDFMT_FORMAT_NTSC          0x00
#define VIDFMT_FORMAT_PAL           0x10
#define VIDFMT_FORMAT_PAL_M         0x20
#define VIDFMT_FORMAT_PAL_N         0x30
#define VIDFMT_FORMAT_VGA           0x40

#define VIDFMT_FORMAT_MAX           VIDFMT_FORMAT_VGA


BYTE GetVideoOutputFormat(VOID);

#define FLASHREG_MICROSOFT  1
#define FLASHREG_OEMRESERV0 2
#define FLASHREG_OEMRESERV1 3
#define FLASHREG_OEMRESERV2 4

typedef int FLASH_REGION;
typedef PBYTE PBYTE60;

BOOL FlashOpen(FLASH_REGION region, LPDWORD lpdwRecords, LPWORD lpwType);
VOID FlashClose(VOID);
BOOL FlashRead(DWORD dwRecord, PBYTE60 pUserBuffer);
BOOL FlashWrite(DWORD dwRecord, PBYTE60 pUserBuffer);

BOOL FlashFormat(WORD type);
#define FORMAT_NORMAL		0
#define FORMAT_PROTECTED	1

VOID FirmwareGetSerialNumber(PBYTE, LPDWORD);
BYTE FirmwareGetMachineType(VOID);

#define MACHINE_TYPE_DREAMCAST 0
#define MACHINE_TYPE_DEVELOPMENT 1

BYTE FirmwareGetCountryCode(VOID);

#define COUNTRY_JAPAN   0
#define COUNTRY_AMERICA 1
#define COUNTRY_EUROPE  2
#define COUNTRY_MAX     COUNTRY_EUROPE

BYTE FirmwareGetLanguageCode(VOID);

#define LANGUAGE_JAPANESE 0
#define LANGUAGE_ENGLISH  1
#define LANGUAGE_GERMAN   2
#define LANGUAGE_FRENCH   3
#define LANGUAGE_SPANISH  4
#define LANGUAGE_ITALIAN  5
#define LANGUAGE_MAX      LANGUAGE_ITALIAN

DWORD FirmwareGetClock(VOID);
BYTE FirmwareGetGMT(VOID);

BYTE FirmwareGetSoundMode(VOID);
#define SOUND_MODE_STEREO   0
#define SOUND_MODE_MONO     1

BYTE FirmwareGetAutoStart(VOID);
#define AUTO_START_ON  0
#define AUTO_START_OFF 1

DWORD FirmwareGetIcon(UINT iconNum, PBYTE pBuffer, LPDWORD lpdwReturned);
#define FIRMWARE_ICON_MAX_ICONNUM 9
#define FIRMWARE_ICON_NO_ERROR 0
#define FIRMWARE_ICON_ERROR_BUFFERSIZE_RETURNED 1
#define FIRMWARE_ICON_ERROR_ICONNUM_TOO_BIG 2
#define FIRMWARE_ICON_GENERAL_ERROR 3

VOID ResetToFirmware(VOID);

VOID SetFirmwareValues(DWORD clock, BYTE gmt, BYTE language, BYTE sound, BYTE autostart);
#define DWORD_DONT_CHANGE 0xFFFFFFFF
#define BYTE_DONT_CHANGE 0xFF

#include <netinfo.h>

#define REG_KEY_NETWORK_INFO    TEXT("Comm")
#define REG_VAL_NETWORK_INFO    TEXT("NetworkInfo")
#define RASENTRY_BASE_NAME      TEXT("ISP")

BOOL
FlashLoadNetworkInfo(
    IN CONST NetworkInfo *pInfo OPTIONAL,
    IN DWORD nLength,
    OUT LPDWORD lpnStatus OPTIONAL
);


// Rom Font stuff
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
#define SYD_BT_FNT_GAIJ_24_OFS   (SYD_BT_FNT_LVL2_24_OFS+SYD_BT_FNT_LVL2_24_SIZE)
#define SYD_BT_FNT_GAIJ_24_SIZE  (0x630)
#define SYD_BT_FNT_VMSICON_OFS   (SYD_BT_FNT_GAIJ_24_OFS+SYD_BT_FNT_GAIJ_24_SIZE)
#define SYD_BT_FNT_VMSICON_SIZE  (129*32*32/8)
#define SYD_BT_FNT_ASCII_12_OFS  (0)
#define SYD_BT_FNT_ASCII_12_SIZE (0)
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
#define SYD_BT_FNT_ICON_WIDTH  (32)
#define SYD_BT_FNT_ICON_HEIGHT (32)
#define SYD_BT_FNT_ICON_SIZE   (SYD_BT_FNT_ICON_WIDTH*SYD_BT_FNT_ICON_HEIGHT/8)

#define SYD_BT_FNTINI    (0)

#define SYD_BT_FNT_SMPH_SUCCESS (0)
#define SYD_BT_FNT_SMPH_FAILURE (-1)


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
#define SYD_BT_FNT_GAIJ_MIN       (0)
#define SYD_BT_FNT_GAIJ_MAX       (21)
#define SYD_BT_FNT_ICON_MIN       (0)
#define SYD_BT_FNT_ICON_MAX       (128)

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

/*** VMU ICON code *****************************************************/
#define SYD_BT_FNT_ICON_UNFMT           (0)   /* UNFORMAT              */
#define SYD_BT_FNT_ICON_HOUR0           (1)   /* HOURGRASS 0           */
#define SYD_BT_FNT_ICON_HOUR1           (2)   /* HOURGRASS 1           */
#define SYD_BT_FNT_ICON_HOUR2           (3)   /* HOURGRASS 2           */
#define SYD_BT_FNT_ICON_HOUR3           (4)   /* HOURGRASS 3           */
#define SYD_BT_FNT_ICON_OFS             (5)   /* designed icon 0       */
#define SYD_BT_FNT_ICON_NUM             (124) /* number of icons       */
#define SYD_BT_FNT_ICON_END             (128) /* designed icon 123     */


typedef struct tag_SYS_BT_FNT_INFO {
	BYTE  width;                     /* Width of a font graphic          */
	BYTE  height;                    /* Height of a font graphic         */
} SYS_BT_FNT_INFO;

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


void
RomFontInitialize(void);
    
void 
RomFontCleanUp();


#define ROM_FONT_NO_ERROR 0
#define ROM_FONT_ERROR_NOT_INITIALIZED 1
#define ROM_FONT_ERROR_BUFFER_TOO_SMALL 2
#define ROM_FONT_ERROR_BUSY 3
    
HRESULT
RomFontGetCharacter(
    SYE_BT_FNT_FONTSET set,
    SHORT code,    
    PBYTE pBuffer,
    DWORD dwBufferSize,
    SYS_BT_FNT_INFO *pInfo);

SHORT 
RomFontSJisToJis( 
    SHORT sjis);

#define SH4PCTL_OREADACCESS		0x0001 // Operand read access
#define SH4PCTL_OWRITEACCESS		0x0002 // Operand write access
#define SH4PCTL_UTLBMISS		0x0003 // UTLB miss
#define SH4PCTL_OCREADMISS		0x0004 // Operand cache read miss
#define SH4PCTL_OCWRITEMISS		0x0005 // Operand cache write miss
#define SH4PCTL_IFETCH			0x0006 // Instruction fetch (/with cache)
#define SH4PCTL_ITLBMISS		0x0007 // Instruction TLB miss
#define SH4PCTL_ICMISS			0x0008 // Instruction cache miss
#define SH4PCTL_OCMISS			0x000f // Operand cache miss (read + write)
#define SH4PCTL_IEXEC			0x0013 // Instruction execution

void MapSh4Stats();
void UnmapSh4Stats();

void StartSh4Stats(WORD wPerf1, WORD wPerf2);
void StopSh4Stats();
void ReadSh4Stats(DWORD *dwHiPerf1, DWORD *dwLoPerf1, DWORD *dwHiPerf2, DWORD *dwLoPerf2);



#ifdef __cplusplus
};
#endif

#endif //_PLATUTIL_H
