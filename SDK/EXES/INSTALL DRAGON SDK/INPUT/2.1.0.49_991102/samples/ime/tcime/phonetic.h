/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    katakana.h

Abstract:

    This file contains definitions of katakana characters.

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/

#ifndef _PHONETIC_H
#define _PHONETIC_H

#include "display.h"


//      ROMAJI              PHONETIC UNICODE VALUE
//      ------------        ----------------------
#define PHON_B              0x3105
#define PHON_P              0x3106
#define PHON_M              0x3107
#define PHON_F              0x3108
#define PHON_D              0x3109
#define PHON_T              0x310a
#define PHON_N              0x310b
#define PHON_L              0x310c
#define PHON_G              0x310d
#define PHON_K              0x310e
#define PHON_H              0x310f
#define PHON_J              0x3110
#define PHON_Q              0x3111
#define PHON_X              0x3112
#define PHON_ZHI            0x3113
#define PHON_CHI            0x3114
#define PHON_SHI            0x3115
#define PHON_RI             0x3116
#define PHON_ZI             0x3117
#define PHON_CI             0x3118
#define PHON_SI             0x3119
#define PHON_A              0x311a
#define PHON_O              0x311b
#define PHON_E              0x311c
#define PHON_IE             0x311d
#define PHON_AI             0x311e
#define PHON_EI             0x311f
#define PHON_AO             0x3120
#define PHON_OU             0x3121
#define PHON_AN             0x3122
#define PHON_EN             0x3123
#define PHON_ANG            0x3124
#define PHON_ENG            0x3125
#define PHON_ER             0x3126
#define PHON_YI             0x3127
#define PHON_WU             0x3128
#define PHON_YU             0x3129
#define PHON_TONE0          0x02d9
#define PHON_TONE2          0x02ca
#define PHON_TONE3          0x02c7
#define PHON_TONE4          0x02cb

// regular katakana
#define FIRST_PHONETIC      0x3105
#define LAST_PHONETIC       0x3129


extern SOFTKEY  g_rgskPhonetic[];
extern WORD     g_cPhoneticKeys;

#endif  // _KATAKANA_H
