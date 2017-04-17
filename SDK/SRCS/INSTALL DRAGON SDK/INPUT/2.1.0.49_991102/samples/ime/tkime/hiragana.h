
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    hiragana.h

Abstract:

    This file contains definitions of hiragana characters.

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/
#ifndef _HIRAGANA_H
#define _HIRAGANA_H

#include "kanji.h"
#include "symbols.h"
#include "romanji.h"
#include "display.h"


//      ROMAJI              HIRAGANA UNICODE VALUE
//      ------------        ----------------------
#define HIRAGANA_A_HH       0x3041
#define HIRAGANA_A          0x3042
#define HIRAGANA_I_HH       0x3043
#define HIRAGANA_I          0x3044
#define HIRAGANA_U_HH       0x3045
#define HIRAGANA_U          0x3046
#define HIRAGANA_E_HH       0x3047
#define HIRAGANA_E          0x3048
#define HIRAGANA_O_HH       0x3049
#define HIRAGANA_O          0x304a
#define HIRAGANA_KA         0x304b
#define HIRAGANA_KA_DK      0x304c
#define HIRAGANA_KI         0x304d
#define HIRAGANA_KI_DK      0x304e
#define HIRAGANA_KU         0x304f
#define HIRAGANA_KU_DK      0x3050
#define HIRAGANA_KE         0x3051
#define HIRAGANA_KE_DK      0x3052
#define HIRAGANA_KO         0x3053
#define HIRAGANA_KO_DK      0x3054
#define HIRAGANA_SA         0x3055
#define HIRAGANA_SA_DK      0x3056
#define HIRAGANA_SHI        0x3057
#define HIRAGANA_SHI_DK     0x3058
#define HIRAGANA_SU         0x3059
#define HIRAGANA_SU_DK      0x305a
#define HIRAGANA_SE         0x305b
#define HIRAGANA_SE_DK      0x305c
#define HIRAGANA_SO         0x305d
#define HIRAGANA_SO_DK      0x305e
#define HIRAGANA_TA         0x305f
#define HIRAGANA_TA_DK      0x3060
#define HIRAGANA_CHI        0x3061
#define HIRAGANA_CHI_DK     0x3062
#define HIRAGANA_TSU_HH     0x3063
#define HIRAGANA_TSU        0x3064
#define HIRAGANA_TSU_DK     0x3065
#define HIRAGANA_TE         0x3066
#define HIRAGANA_TE_DK      0x3067
#define HIRAGANA_TO         0x3068
#define HIRAGANA_TO_DK      0x3069
#define HIRAGANA_NA         0x306a
#define HIRAGANA_NI         0x306b
#define HIRAGANA_NU         0x306c
#define HIRAGANA_NE         0x306d
#define HIRAGANA_NO         0x306e
#define HIRAGANA_HA         0x306f
#define HIRAGANA_HA_DK      0x3070
#define HIRAGANA_HA_HK      0x3071
#define HIRAGANA_HI         0x3072
#define HIRAGANA_HI_DK      0x3073
#define HIRAGANA_HI_HK      0x3074
#define HIRAGANA_HU         0x3075
#define HIRAGANA_HU_DK      0x3076
#define HIRAGANA_HU_HK      0x3077
#define HIRAGANA_HE         0x3078
#define HIRAGANA_HE_DK      0x3079
#define HIRAGANA_HE_HK      0x307a
#define HIRAGANA_HO         0x307b
#define HIRAGANA_HO_DK      0x307c
#define HIRAGANA_HO_HK      0x307d
#define HIRAGANA_MA         0x307e
#define HIRAGANA_MI         0x307f
#define HIRAGANA_MU         0x3080
#define HIRAGANA_ME         0x3081
#define HIRAGANA_MO         0x3082
#define HIRAGANA_YA_HH      0x3083
#define HIRAGANA_YA         0x3084
#define HIRAGANA_YU_HH      0x3085
#define HIRAGANA_YU         0x3086
#define HIRAGANA_YO_HH      0x3087
#define HIRAGANA_YO         0x3088
#define HIRAGANA_RA         0x3089
#define HIRAGANA_RI         0x308a
#define HIRAGANA_RU         0x308b
#define HIRAGANA_RE         0x308c
#define HIRAGANA_RO         0x308d
#define HIRAGANA_WA_HH      0x308e
#define HIRAGANA_WA         0x308f
#define HIRAGANA_UNKNOWN1   0x3090
#define HIRAGANA_UNKNOWN2   0x3091
#define HIRAGANA_WO         0x3092
#define HIRAGANA_NN         0x3093


#define HIRAGANA_SWITCH 0x30a2

#define FIRST_HIRAGANA      0x3041
#define LAST_HIRAGANA       0x3093


typedef struct _HIRAGANA_MAP
{
    TCHAR   wcHalfHeight;
    TCHAR   wcDakuten;
    TCHAR   wcHandakuten;
} HIRAGANA_MAP;

extern SOFTKEY g_rgskHiragana[];
extern WORD g_cHiraganaKeys;
extern HIRAGANA_MAP g_rgHiraganaMap[];

#endif  // _HIRAGANA_H
