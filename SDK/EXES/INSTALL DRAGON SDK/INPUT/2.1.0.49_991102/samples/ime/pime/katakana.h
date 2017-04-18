/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    katakana.h

Abstract:

    This file contains definitions of katakana characters.

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/

#ifndef _KATAKANA_H
#define _KATAKANA_H

#include "kanji.h"
#include "symbols.h"
#include "romanji.h"
#include "display.h"


//      ROMAJI              KATAKANA UNICODE VALUE
//      ------------        ----------------------
#define KATAKANA_A_HH       0x30a1
#define KATAKANA_A          0x30a2
#define KATAKANA_I_HH       0x30a3
#define KATAKANA_I          0x30a4
#define KATAKANA_U_HH       0x30a5
#define KATAKANA_U          0x30a6
#define KATAKANA_E_HH       0x30a7
#define KATAKANA_E          0x30a8
#define KATAKANA_O_HH       0x30a9
#define KATAKANA_O          0x30aa
#define KATAKANA_KA         0x30ab
#define KATAKANA_KA_DK      0x30ac
#define KATAKANA_KI         0x30ad
#define KATAKANA_KI_DK      0x30ae
#define KATAKANA_KU         0x30af
#define KATAKANA_KU_DK      0x30b0
#define KATAKANA_KE         0x30b1
#define KATAKANA_KE_DK      0x30b2
#define KATAKANA_KO         0x30b3
#define KATAKANA_KO_DK      0x30b4
#define KATAKANA_SA         0x30b5
#define KATAKANA_SA_DK      0x30b6
#define KATAKANA_SHI        0x30b7
#define KATAKANA_SHI_DK     0x30b8
#define KATAKANA_SU         0x30b9
#define KATAKANA_SU_DK      0x30ba
#define KATAKANA_SE         0x30bb
#define KATAKANA_SE_DK      0x30bc
#define KATAKANA_SO         0x30bd
#define KATAKANA_SO_DK      0x30be
#define KATAKANA_TA         0x30bf
#define KATAKANA_TA_DK      0x30c0
#define KATAKANA_CHI        0x30c1
#define KATAKANA_CHI_DK     0x30c2
#define KATAKANA_TSU_HH     0x30c3
#define KATAKANA_TSU        0x30c4
#define KATAKANA_TSU_DK     0x30c5
#define KATAKANA_TE         0x30c6
#define KATAKANA_TE_DK      0x30c7
#define KATAKANA_TO         0x30c8
#define KATAKANA_TO_DK      0x30c9
#define KATAKANA_NA         0x30ca
#define KATAKANA_NI         0x30cb
#define KATAKANA_NU         0x30cc
#define KATAKANA_NE         0x30cd
#define KATAKANA_NO         0x30ce
#define KATAKANA_HA         0x30cf
#define KATAKANA_HA_DK      0x30d0
#define KATAKANA_HA_HK      0x30d1
#define KATAKANA_HI         0x30d2
#define KATAKANA_HI_DK      0x30d3
#define KATAKANA_HI_HK      0x30d4
#define KATAKANA_HU         0x30d5
#define KATAKANA_HU_DK      0x30d6
#define KATAKANA_HU_HK      0x30d7
#define KATAKANA_HE         0x30d8
#define KATAKANA_HE_DK      0x30d9
#define KATAKANA_HE_HK      0x30da
#define KATAKANA_HO         0x30db
#define KATAKANA_HO_DK      0x30dc
#define KATAKANA_HO_HK      0x30dd
#define KATAKANA_MA         0x30de
#define KATAKANA_MI         0x30df
#define KATAKANA_MU         0x30e0
#define KATAKANA_ME         0x30e1
#define KATAKANA_MO         0x30e2
#define KATAKANA_YA_HH      0x30e3
#define KATAKANA_YA         0x30e4
#define KATAKANA_YU_HH      0x30e5
#define KATAKANA_YU         0x30e6
#define KATAKANA_YO_HH      0x30e7
#define KATAKANA_YO         0x30e8
#define KATAKANA_RA         0x30e9
#define KATAKANA_RI         0x30ea
#define KATAKANA_RU         0x30eb
#define KATAKANA_RE         0x30ec
#define KATAKANA_RO         0x30ed
#define KATAKANA_WA_HH      0x30ee
#define KATAKANA_WA         0x30ef
#define KATAKANA_UNKNOWN1   0x30f0
#define KATAKANA_UNKNOWN2   0x30f1
#define KATAKANA_WO         0x30f2
#define KATAKANA_NN         0x30f3
#define KATAKANA_U_DK       0x30f4
#define KATAKANA_KA_HH      0x30f5
#define KATAKANA_KE_HH      0x30f6

#define KATAKANA_WO_HW      0xff66
#define KATAKANA_A_HHHW     0xff67
#define KATAKANA_I_HHHW     0xff68
#define KATAKANA_U_HHHW     0xff69
#define KATAKANA_E_HHHW     0xff6a
#define KATAKANA_O_HHHW     0xff6b
#define KATAKANA_YA_HHHW    0xff6c
#define KATAKANA_YU_HHHW    0xff6d
#define KATAKANA_YO_HHHW    0xff6e
#define KATAKANA_TSU_HHHW   0xff6f
#define KATAKANA_UNKNOWN3   0xff70
#define KATAKANA_A_HW       0xff71
#define KATAKANA_I_HW       0xff72
#define KATAKANA_U_HW       0xff73
#define KATAKANA_E_HW       0xff74
#define KATAKANA_O_HW       0xff75
#define KATAKANA_KA_HW      0xff76
#define KATAKANA_KI_HW      0xff77
#define KATAKANA_KU_HW      0xff78
#define KATAKANA_KE_HW      0xff79
#define KATAKANA_KO_HW      0xff7a
#define KATAKANA_SA_HW      0xff7b
#define KATAKANA_SHI_HW     0xff7c
#define KATAKANA_SU_HW      0xff7d
#define KATAKANA_SE_HW      0xff7e
#define KATAKANA_SO_HW      0xff7f
#define KATAKANA_TA_HW      0xff80
#define KATAKANA_CHI_HW     0xff81
#define KATAKANA_TSU_HW     0xff82
#define KATAKANA_TE_HW      0xff83
#define KATAKANA_TO_HW      0xff84
#define KATAKANA_NA_HW      0xff85
#define KATAKANA_NI_HW      0xff86
#define KATAKANA_NU_HW      0xff87
#define KATAKANA_NE_HW      0xff88
#define KATAKANA_NO_HW      0xff89
#define KATAKANA_HA_HW      0xff8a
#define KATAKANA_HI_HW      0xff8b
#define KATAKANA_HU_HW      0xff8c
#define KATAKANA_HE_HW      0xff8d
#define KATAKANA_HO_HW      0xff8e
#define KATAKANA_MA_HW      0xff8f
#define KATAKANA_MI_HW      0xff90
#define KATAKANA_MU_HW      0xff91
#define KATAKANA_ME_HW      0xff92
#define KATAKANA_MO_HW      0xff93
#define KATAKANA_YA_HW      0xff94
#define KATAKANA_YU_HW      0xff95
#define KATAKANA_YO_HW      0xff96
#define KATAKANA_RA_HW      0xff97
#define KATAKANA_RI_HW      0xff98
#define KATAKANA_RU_HW      0xff99
#define KATAKANA_RE_HW      0xff9a
#define KATAKANA_RO_HW      0xff9b
#define KATAKANA_WA_HW      0xff9c
#define KATAKANA_NN_HW      0xff9d

#define KATAKANA_SWITCH     0x3042

// regular katakana
#define FIRST_KATAKANA      0x30a1
#define LAST_KATAKANA       0x30f6

// half-width katakana
#define FIRST_HW_KATAKANA   0xff66
#define LAST_HW_KATAKANA    0xff9f

// half-width, half-height katakana
#define FIRST_HHHW_KATAKANA 0xff67
#define LAST_HHHW_KATAKANA  0xff70

typedef struct _KATAKANA_MAP
{
    TCHAR   wcHalfHeight;
    TCHAR   wcHalfWidth;
    TCHAR   wcHalfWidthHalfHeight;
    TCHAR   wcDakuten;
    TCHAR   wcHandakuten;
} KATAKANA_MAP;

extern SOFTKEY g_rgskKatakana[];
extern WORD g_cKatakanaKeys;
extern KATAKANA_MAP g_rgKatakanaMap[];

#endif  // _KATAKANA_H
