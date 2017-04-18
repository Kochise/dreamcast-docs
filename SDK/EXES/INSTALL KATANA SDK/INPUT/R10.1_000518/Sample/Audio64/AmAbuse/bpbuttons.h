//-----------------------------------------------------------------------------
//
//	FILE:		bpbuttons.h
//
//	DESC:		Boilerplate for miscellaneous definitions
//
//	HISTORY:	2000.01.xx	Reworked samples/boilerplates for R10 release.
//
//-----------------------------------------------------------------------------
//	COPYRIGHT (C) SEGA OF AMERICA DREAMCAST, INC. 1998, 1999, 2000
//	All rights reserved.
//
//	Information and source code samples contained herein are provided "as-is",
//	without representations or warranties, and are subject to change without
//	notice.
//
//	SEGA OF AMERICA DREAMCAST, INC. cannot support modifications or derivative
//	works created from the sample source code provided. Developers may use,
//	reproduce, and modify portions or entire sections of the sample source
//	code for the purposes of creating Dreamcast applications.
//
//	Sample source code contained herein may not be appropriate for use under
//	all circumstances. Please consult Developer documentation provided along
//	with your Dreamcast unit for additional information and suggestions.
//-----------------------------------------------------------------------------

#if !defined(_BPBUTTONS_H_)
#define _BPBUTTONS_H_

#include <sg_pad.h>

//	screen coordinates
#define BASE_X								2
#define BASE_Y								6
#define INFO_0_X							BASE_X
#define INFO_0_Y							BASE_Y
#define INFO_1_X							BASE_X
#define INFO_1_Y							BASE_Y+2
#define INFO_2_X							BASE_X
#define INFO_2_Y							BASE_Y+4
#define INFO_3_X							BASE_X
#define INFO_3_Y							BASE_Y+6
#define INFO_4_X							BASE_X
#define INFO_4_Y							BASE_Y+8
#define INFO_5_X							BASE_X
#define INFO_5_Y							BASE_Y+10
#define INFO_6_X							BASE_X
#define INFO_6_Y							BASE_Y+12
#define INFO_7_X							BASE_X
#define INFO_7_Y							BASE_Y+14
#define INFO_8_X							BASE_X
#define INFO_8_Y							BASE_Y+16
#define INFO_9_X							BASE_X
#define INFO_9_Y							BASE_Y+18

//	controller masks
#define PAD_X_BUTTON						PDD_DEV_SUPPORT_TX
#define PAD_Y_BUTTON						PDD_DEV_SUPPORT_TY
#define PAD_A_BUTTON						PDD_DEV_SUPPORT_TA
#define PAD_B_BUTTON						PDD_DEV_SUPPORT_TB
#define PAD_START_BUTTON					PDD_DEV_SUPPORT_ST
#define PAD_MOVE_LEFT						PDD_DEV_SUPPORT_KL
#define PAD_MOVE_RIGHT						PDD_DEV_SUPPORT_KR
#define PAD_MOVE_UP							PDD_DEV_SUPPORT_KU
#define PAD_MOVE_DOWN						PDD_DEV_SUPPORT_KD
#define PAD_R_TRIGGER						PDD_DEV_SUPPORT_AR
#define PAD_L_TRIGGER						PDD_DEV_SUPPORT_AL
#define PAD_SOFTRESET						(PAD_A_BUTTON \
											| PAD_B_BUTTON \
											| PAD_X_BUTTON \
											| PAD_Y_BUTTON \
											| PAD_START_BUTTON)

#endif	//	_BPBUTTONS_H_