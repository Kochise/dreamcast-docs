/*++

  COPYRIGHT        (C) NEC        Corporation 1997 - 1999

  All rights reserved by NEC Corporation. This program must be
  used solely for the purpose for which it was furnished by NEC
  Corporation. No part of this program may be reproduced or
  disclosed to others, in any form, without the prior written
  permission of NEC Corporation.
  Use of copyright notice does not evidence publication of this
  program.

  Author     :		T.Hirata(NEC Software,Ltd.)
  Module Name:		km2vtx.h

  Abstract:
	Kamui is Low-Level PowerVR Driver.
	'km2vtx.h' defines kamui vertex structures.

  Environment:
	ANSI C Compiler.

  Notes:
	PowerVR2 for Dreamcast Specific Vertex Data structure.

  Revision History:

--*/
#if !defined(__kamui_vertex_h)
#define __kamui_vertex_h

#ifdef __cplusplus
extern "C" {
#endif 


/*++
//	Non-Textured Packed Color(Type0)
//
//		0x00	ParameterControlWord
//		0x04	X
//		0x08	Y
//		0x0C	Z
//		0x10	Reserved 0
//		0x14	Reserved 1
//		0x18	BaseColor
//		0x1C	Reserved 2
--*/
typedef struct tagKMVERTEX0
{
	KMDWORD	ParamControlWord;
	KMFLOAT	fX;
	KMFLOAT	fY;
	union{
		KMFLOAT	fZ;
		KMFLOAT	fInvW;
	}
#if defined(_STRICT_UNION_)
	u
#endif
	;
	/* padding word */
	KMDWORD	Reserved0;
	KMDWORD	Reserved1;
	KMPACKEDARGB	uBaseRGB;
	/* padding word */
	KMDWORD	Reserved2;

} KMVERTEX0,*PKMVERTEX0;

/*++
//	Non-Textured Floating Color(Type1)
//
//		0x00	ParameterControlWord
//		0x04	X
//		0x08	Y
//		0x0C	Z
//		0x10	BaseColor Alpha
//		0x14	BaseColor R
//		0x18	BaseColor G
//		0x1C	BaseColor B
--*/
typedef struct tagKMVERTEX1
{
	KMDWORD	ParamControlWord;
	KMFLOAT	fX;
	KMFLOAT	fY;
	union{
		KMFLOAT	fZ;
		KMFLOAT	fInvW;
	}
#if defined(_STRICT_UNION_)
	u
#endif
	;
	KMFLOAT	fBaseAlpha;
	KMFLOAT	fBaseRed;
	KMFLOAT	fBaseGreen;
	KMFLOAT	fBaseBlue;

}KMVERTEX1,*PKMVERTEX1;

/*++
//	Non-Textured Intensity(Type2)
//		0x00	ParameterControlWord
//		0x04	X
//		0x08	Y
//		0x0C	Z
//		0x10	Reserved 0
//		0x14	Reserved 1
//		0x18	BaseIntensity
//		0x1C	Reserved 2
--*/
typedef struct tagKMVERTEX2
{
	KMDWORD	ParamControlWord;
	KMFLOAT	fX;
	KMFLOAT	fY;
	union{
		KMFLOAT	fZ;
		KMFLOAT	fInvW;
	}
#if defined(_STRICT_UNION_)
	u
#endif
	;
	/* padding word */
	KMDWORD	Reserved0;
	KMDWORD	Reserved1;
	KMFLOAT	fBaseIntensity;
	/* padding word */
	KMDWORD	Reserved2;

}KMVERTEX2,*PKMVERTEX2;

/*++
//	Textured Packed Color(Type3)
//
//		0x00	ParameterControlWord
//		0x04	X
//		0x08	Y
//		0x0C	Z
//		0x10	U
//		0x14	V
//		0x18	BaseColor
//		0x1C	OffsetColor
--*/
typedef struct tagKMVERTEX3
{
	KMDWORD	ParamControlWord;
	KMFLOAT	fX;
	KMFLOAT	fY;
	union{
		KMFLOAT	fZ;
		KMFLOAT	fInvW;
	}
#if defined(_STRICT_UNION_)
	u
#endif
	;
	KMFLOAT	fU;
	KMFLOAT	fV;
	KMPACKEDARGB uBaseRGB;
	KMPACKEDARGB uOffsetRGB;

}KMVERTEX3,*PKMVERTEX3;

/*++
//	Textured Packed Color CompactUV(Type4)
//
//		0x00	ParameterControlWord
//		0x04	X
//		0x08	Y
//		0x0C	Z
//		0x10	U/V
//		0x14	Reserved 0
//		0x18	BaseColor
//		0x1C	OffsetColor
--*/
typedef struct tagKMVERTEX4
{
	KMDWORD	ParamControlWord;
	KMFLOAT	fX;
	KMFLOAT	fY;
	union{
		KMFLOAT	fZ;
		KMFLOAT	fInvW;
	}
#if defined(_STRICT_UNION_)
	u
#endif
	;
	KMDWORD	dwUV;
	/* padding word */
	KMDWORD	Reserved0;
	KMPACKEDARGB uBaseRGB;
	KMPACKEDARGB uOffsetRGB;

}KMVERTEX4,*PKMVERTEX4;

/*++
//	Floating Color(Type5)
//
//		0x00	ParameterControlWord
//		0x04	X
//		0x08	Y
//		0x0C	Z
//		0x10	U
//		0x14	V
//		0x18	Reserved 0
//		0x1C	Reserved 1
//		0x20	BaseColor Alpha
//		0x24	BaseColor R
//		0x28	BaseColor G
//		0x2C	BaseColor B
//		0x30	OffsetColor Alpha
//		0x34	OffsetColor R
//		0x38	OffsetColor G
//		0x3C	OffsetColor B
--*/
typedef struct tagKMVERTEX5
{
	KMDWORD	ParamControlWord;
	KMFLOAT	fX;
	KMFLOAT	fY;
	union{
		KMFLOAT	fZ;
		KMFLOAT	fInvW;
	}
#if defined(_STRICT_UNION_)
	u
#endif
	;
	KMFLOAT	fU;
	KMFLOAT	fV;
	/* padding word */
	KMDWORD	Reserved0;
	KMDWORD	Reserved1;
	KMFLOAT	fBaseAlpha;
	KMFLOAT	fBaseRed;
	KMFLOAT	fBaseGreen;
	KMFLOAT	fBaseBlue;
	KMFLOAT	fOffsetAlpha;
	KMFLOAT	fOffsetRed;
	KMFLOAT	fOffsetGreen;
	KMFLOAT	fOffsetBlue;

}KMVERTEX5,*PKMVERTEX5;

/*++
//	Floating Color CompactUV(Type6)
//
//		0x00	ParameterControlWord
//		0x04	X
//		0x08	Y
//		0x0C	Z
//		0x10	U/V
//		0x14	Reserved 0
//		0x18	Reserved 1
//		0x1C	Reserved 2
//		0x20	BaseColor Alpha
//		0x24	BaseColor R
//		0x28	BaseColor G
//		0x2C	BaseColor B
//		0x30	OffsetColor Alpha
//		0x34	OffsetColor R
//		0x38	OffsetColor G
//		0x3C	OffsetColor B
--*/
typedef struct tagKMVERTEX6
{
	KMDWORD	ParamControlWord;
	KMFLOAT	fX;
	KMFLOAT	fY;
	union{
		KMFLOAT	fZ;
		KMFLOAT	fInvW;
	}
#if defined(_STRICT_UNION_)
	u
#endif
	;
	KMDWORD	dwUV;
	/* padding word */
	KMDWORD	Reserved0;
	KMDWORD	Reserved1;
	KMDWORD	Reserved2;
	KMFLOAT	fBaseAlpha;
	KMFLOAT	fBaseRed;
	KMFLOAT	fBaseGreen;
	KMFLOAT	fBaseBlue;
	KMFLOAT	fOffsetAlpha;
	KMFLOAT	fOffsetRed;
	KMFLOAT	fOffsetGreen;
	KMFLOAT	fOffsetBlue;

}KMVERTEX6,*PKMVERTEX6;

/*++
//	Intensity(Type7)
//
//		0x00	ParameterControlWord
//		0x04	X
//		0x08	Y
//		0x0C	Z
//		0x10	U
//		0x14	V
//		0x18	BaseIntensity
//		0x1C	OffsetIntensity
++*/
typedef struct tagKMVERTEX7
{
	KMDWORD	ParamControlWord;
	KMFLOAT	fX;
	KMFLOAT	fY;
	union{
		KMFLOAT	fZ;
		KMFLOAT	fInvW;
	}
#if defined(_STRICT_UNION_)
	u
#endif
	;
	KMFLOAT	fU;
	KMFLOAT	fV;
	KMFLOAT	fBaseIntensity;
	KMFLOAT	fOffsetIntensity;

}KMVERTEX7,*PKMVERTEX7;

/*++
//	Intensity CompactUV(Type8)
//
//		0x00	ParameterControlWord
//		0x04	X
//		0x08	Y
//		0x0C	Z
//		0x10	U/V
//		0x14	Reserved 0
//		0x18	BaseIntensity
//		0x1C	OffsetIntensity
--*/
typedef struct tagKMVERTEX8
{
	KMDWORD	ParamControlWord;
	KMFLOAT	fX;
	KMFLOAT	fY;
	union{
		KMFLOAT	fZ;
		KMFLOAT	fInvW;
	}
#if defined(_STRICT_UNION_)
	u
#endif
	;
	KMDWORD	dwUV;
	/* padding word */
	KMDWORD	Reserved0;
	KMFLOAT	fBaseIntensity;
	KMFLOAT	fOffsetIntensity;

}KMVERTEX8,*PKMVERTEX8;

/*++
//	Non Textured Packed Color with Two Volumes(Type9)
//
//		0x00	ParameterControlWord
//		0x04	X
//		0x08	Y
//		0x0C	Z
//		0x10	BaseColor 0
//		0x14	BaseColor 1
//		0x18	Reserved 0
//		0x1C	Reserved 1
--*/
typedef struct tagKMVERTEX9
{
	KMDWORD	ParamControlWord;
	KMFLOAT	fX;
	KMFLOAT	fY;
	union{
		KMFLOAT	fZ;
		KMFLOAT	fInvW;
	}
#if defined(_STRICT_UNION_)
	u
#endif
	;
	KMPACKEDARGB uBaseRGB0m;
	KMPACKEDARGB uBaseRGB1m;
	/* padding word */
	KMDWORD	Reserved0;
	KMDWORD	Reserved1;

}KMVERTEX9,*PKMVERTEX9;

/*++
//	Non Textured Intensity with Two Volumes(Type10)
//
//		0x00	ParameterControlWord
//		0x04	X
//		0x08	Y
//		0x0C	Z
//		0x10	BaseIntensity 0
//		0x14	BaseIntensity 1
//		0x18	Reserved 0
//		0x1C	Reserved 1
--*/
typedef struct tagKMVERTEX10
{
	KMDWORD	ParamControlWord;
	KMFLOAT	fX;
	KMFLOAT	fY;
	union{
		KMFLOAT	fZ;
		KMFLOAT	fInvW;
	}
#if defined(_STRICT_UNION_)
	u
#endif
	;
	KMFLOAT	fBaseIntensity0m;
	KMFLOAT	fBaseIntensity1m;
	/* padding word */
	KMDWORD	Reserved0;
	KMDWORD	Reserved1;

}KMVERTEX10,*PKMVERTEX10;

/*++
//	Textured Packed Color Modifier Volume Variant(Type11)
//
//		0x00	ParameterControlWord
//		0x04	X
//		0x08	Y
//		0x0C	Z
//		0x10	U0
//		0x14	V0
//		0x18	BaseColor 0
//		0x1C	OffsetColor 0
//		0x20	U1
//		0x24	V1
//		0x28	BaseColor 1
//		0x2C	OffsetColor 1
//		0x20	Reserved 0
//		0x24	Reserved 1
//		0x28	Reserved 2
//		0x2C	Reserved 3
--*/
typedef struct tagKMVERTEX11
{
	KMDWORD	ParamControlWord;
	KMFLOAT	fX;
	KMFLOAT	fY;
	union{
		KMFLOAT	fZ;
		KMFLOAT	fInvW;
	}
#if defined(_STRICT_UNION_)
	u
#endif
	;

	/* CLX */
	KMFLOAT	fU0m;
	KMFLOAT	fV0m;
	KMPACKEDARGB uBaseRGB0m;
	KMPACKEDARGB uOffsetRGB0m;
	KMFLOAT	fU1m;
	KMFLOAT	fV1m;
	KMPACKEDARGB uBaseRGB1m;
	KMPACKEDARGB uOffsetRGB1m;
	/* padding word */
	KMDWORD	Reserved0;
	KMDWORD	Reserved1;
	KMDWORD	Reserved2;
	KMDWORD	Reserved3;

}KMVERTEX11,*PKMVERTEX11;

/*++
//	Textured Packed Color CompactUV Modifier Volume Variant(Type12)
//
//		0x00	ParameterControlWord
//		0x04	X
//		0x08	Y
//		0x0C	Z
//		0x10	U0/V0
//		0x14	Reserved 0
//		0x18	BaseColor 0
//		0x1C	OffsetColor 0
//		0x20	U1/V1
//		0x24	Reserved 1
//		0x28	BaseColor 1
//		0x2C	OffsetColor 1
//		0x20	Reserved 2
//		0x24	Reserved 3
//		0x28	Reserved 4
//		0x2C	Reserved 5
--*/
typedef struct tagKMVERTEX12
{
	KMDWORD	ParamControlWord;
	KMFLOAT	fX;
	KMFLOAT	fY;
	union{
		KMFLOAT	fZ;
		KMFLOAT	fInvW;
	}
#if defined(_STRICT_UNION_)
	u
#endif
	;

	/* CLX */
	KMDWORD	dwUV0m;
	/* padding word */
	KMDWORD	Reserved0;
	KMPACKEDARGB uBaseRGB0m;
	KMPACKEDARGB uOffsetRGB0m;
	KMDWORD	dwUV1m;
	/* padding word */
	KMDWORD	Reserved1;
	KMPACKEDARGB uBaseRGB1m;
	KMPACKEDARGB uOffsetRGB1m;

	/* padding word */
	KMDWORD	Reserved2;
	KMDWORD	Reserved3;
	KMDWORD	Reserved4;
	KMDWORD	Reserved5;

}KMVERTEX12,*PKMVERTEX12;

/*++
//	Textured Intensity Modifier Volume Variant(Type13)
//
//		0x00	ParameterControlWord
//		0x04	X
//		0x08	Y
//		0x0C	Z
//		0x10	U0
//		0x14	V0
//		0x18	BaseIntensity 0
//		0x1C	OffsetIntensity 0
//		0x20	U1
//		0x24	V1
//		0x28	BaseIntensity 1
//		0x2C	OffsetIntensity 1
//		0x20	Reserved 0
//		0x24	Reserved 1
//		0x28	Reserved 2
//		0x2C	Reserved 3
--*/
typedef struct tagKMVERTEX13
{
	KMDWORD	ParamControlWord;
	KMFLOAT	fX;
	KMFLOAT	fY;
	union{
		KMFLOAT	fZ;
		KMFLOAT	fInvW;
	}
#if defined(_STRICT_UNION_)
	u
#endif
	;
	KMFLOAT	fU0m;
	KMFLOAT	fV0m;
	KMFLOAT	fBaseIntensity0m;
	KMFLOAT	fOffsetIntensity0m;
	KMFLOAT	fU1m;
	KMFLOAT	fV1m;
	KMFLOAT	fBaseIntensity1m;
	KMFLOAT	fOffsetIntensity1m;
	/* padding word */
	KMDWORD	Reserved0;
	KMDWORD	Reserved1;
	KMDWORD	Reserved2;
	KMDWORD	Reserved3;

}KMVERTEX13,*PKMVERTEX13;

/*++
//	Textured Intensity CompactUV Modifier Volume Variant(Type14)
//
//		0x00	ParameterControlWord
//		0x04	X
//		0x08	Y
//		0x0C	Z
//		0x10	U0/V0
//		0x14	Reserved 0
//		0x18	BaseIntensity 0
//		0x1C	OffsetIntensity 0
//		0x20	U1/V1
//		0x24	Reserved 1
//		0x28	BaseIntensity 1
//		0x2C	OffsetIntensity 1
//		0x20	Reserved 2
//		0x24	Reserved 3
//		0x28	Reserved 4
//		0x2C	Reserved 5
--*/
typedef struct tagKMVERTEX14
{
	KMDWORD	ParamControlWord;
	KMFLOAT	fX;
	KMFLOAT	fY;
	union{
		KMFLOAT	fZ;
		KMFLOAT	fInvW;
	}
#if defined(_STRICT_UNION_)
	u
#endif
	;
	KMDWORD	dwUV0m;
	/* padding word */
	KMDWORD	Reserved0;
	KMFLOAT	fBaseIntensity0m;
	KMFLOAT	fOffsetIntensity0m;
	KMDWORD	dwUV1m;
	/* padding word */
	KMDWORD	Reserved1;
	KMFLOAT	fBaseIntensity1m;
	KMFLOAT	fOffsetIntensity1m;
	/* padding word */
	KMDWORD	Reserved2;
	KMDWORD	Reserved3;
	KMDWORD	Reserved4;
	KMDWORD	Reserved5;

}KMVERTEX14,*PKMVERTEX14;

/*++
//	Sprite(Type15)
//
//		0x04	AX
//		0x08	AY
//		0x0C	AZ
//		0x10	BX
//		0x14	BY
//		0x18	BZ
//		0x1C	CX
//		0x20	CY
//		0x24	CZ
//		0x28	DX
//		0x2C	DY
//		0x20	Reserved 0
//		0x24	AU/AV
//		0x28	BU/BV
//		0x2C	CU/CV
--*/
typedef struct tagKMVERTEX15
{
	KMDWORD	ParamControlWord;
	KMFLOAT	fAX;
	KMFLOAT	fAY;
	union{
		KMFLOAT	fAZ;
		KMFLOAT	fAInvW;
	}
#if defined(_STRICT_UNION_)
	uA
#endif
	;
	KMFLOAT	fBX;
	KMFLOAT	fBY;
	union{
		KMFLOAT	fBZ;
		KMFLOAT	fBInvW;
	}
#if defined(_STRICT_UNION_)
	uB
#endif
	;
	KMFLOAT	fCX;
	KMFLOAT	fCY;
	union{
		KMFLOAT	fCZ;
		KMFLOAT	fCInvW;
	}
#if defined(_STRICT_UNION_)
	uC
#endif
	;
	KMFLOAT	fDX;
	KMFLOAT	fDY;
	/* padding word */
	KMDWORD	Reserved0;
	KMDWORD	Reserved1;
	KMDWORD	Reserved2;
	KMDWORD	Reserved3;

}KMVERTEX15,*PKMVERTEX15;

/*++
//	Sprite(Type16)
//
//		0x04	AX
//		0x08	AY
//		0x0C	AZ
//		0x10	BX
//		0x14	BY
//		0x18	BZ
//		0x1C	CX
//		0x20	CY
//		0x24	CZ
//		0x28	DX
//		0x2C	DY
//		0x20	Reserved 0
//		0x24	AU/AV
//		0x28	BU/BV
//		0x2C	CU/CV
--*/
typedef struct tagKMVERTEX16
{
	KMDWORD	ParamControlWord;
	KMFLOAT	fAX;
	KMFLOAT	fAY;
	union{
		KMFLOAT	fAZ;
		KMFLOAT	fAInvW;
	}
#if defined(_STRICT_UNION_)
	uA
#endif
	;
	KMFLOAT	fBX;
	KMFLOAT	fBY;
	union{
		KMFLOAT	fBZ;
		KMFLOAT	fBInvW;
	}
#if defined(_STRICT_UNION_)
	uB
#endif
	;
	KMFLOAT	fCX;
	KMFLOAT	fCY;
	union{
		KMFLOAT	fCZ;
		KMFLOAT	fCInvW;
	}
#if defined(_STRICT_UNION_)
	uC
#endif
	;
	KMFLOAT	fDX;
	KMFLOAT	fDY;
	/* padding word */
	KMDWORD	Reserved0;
	KMDWORD	dwUVA;
	KMDWORD	dwUVB;
	KMDWORD	dwUVC;

}KMVERTEX16,*PKMVERTEX16;

/*++
//	Modifier Volume(Type17)
//
//		0x04	AX
//		0x08	AY
//		0x0C	AZ
//		0x10	BX
//		0x14	BY
//		0x18	BZ
//		0x1C	CX
//		0x20	CY
//		0x24	CZ
//		0x28	Reserved 0
//		0x2C	Reserved 1
//		0x20	Reserved 2
//		0x24	Reserved 3
//		0x28	Reserved 4
//		0x2C	Reserved 5
--*/
typedef struct tagKMVERTEX17
{
	KMDWORD	ParamControlWord;
	KMFLOAT	fAX;
	KMFLOAT	fAY;
	union{
		KMFLOAT	fAZ;
		KMFLOAT	fAInvW;
	}
#if defined(_STRICT_UNION_)
	uA
#endif
	;
	KMFLOAT	fBX;
	KMFLOAT	fBY;
	union{
		KMFLOAT	fBZ;
		KMFLOAT	fBInvW;
	}
#if defined(_STRICT_UNION_)
	uB
#endif
	;
	KMFLOAT	fCX;
	KMFLOAT	fCY;
	union{
		KMFLOAT	fCZ;
		KMFLOAT	fCInvW;
	}
#if defined(_STRICT_UNION_)
	uC
#endif
	;
	/* padding word */
	KMDWORD	Reserved0;
	KMDWORD	Reserved1;
	KMDWORD	Reserved2;
	KMDWORD	Reserved3;
	KMDWORD	Reserved4;
	KMDWORD	Reserved5;

}KMVERTEX17,*PKMVERTEX17;


/*
 * Alias
 */
typedef KMVERTEX0	 KMVERTEX_00,*PKMVERTEX_00;
typedef KMVERTEX1	 KMVERTEX_01,*PKMVERTEX_01;
typedef KMVERTEX2	 KMVERTEX_02,*PKMVERTEX_02;
typedef KMVERTEX3	 KMVERTEX_03,*PKMVERTEX_03;
typedef KMVERTEX4	 KMVERTEX_04,*PKMVERTEX_04;
typedef KMVERTEX5	 KMVERTEX_05,*PKMVERTEX_05;
typedef KMVERTEX6	 KMVERTEX_06,*PKMVERTEX_06;
typedef KMVERTEX7	 KMVERTEX_07,*PKMVERTEX_07;
typedef KMVERTEX8	 KMVERTEX_08,*PKMVERTEX_08;
typedef KMVERTEX9	 KMVERTEX_09,*PKMVERTEX_09;
typedef KMVERTEX10	 KMVERTEX_10,*PKMVERTEX_10;
typedef KMVERTEX11	 KMVERTEX_11,*PKMVERTEX_11;
typedef KMVERTEX12	 KMVERTEX_12,*PKMVERTEX_12;
typedef KMVERTEX13	 KMVERTEX_13,*PKMVERTEX_13;
typedef KMVERTEX14	 KMVERTEX_14,*PKMVERTEX_14;
typedef KMVERTEX15	 KMVERTEX_15,*PKMVERTEX_15;
typedef KMVERTEX16	 KMVERTEX_16,*PKMVERTEX_16;
typedef KMVERTEX17	 KMVERTEX_17,*PKMVERTEX_17;

#ifdef __cplusplus
}
#endif 

#endif /*  __kamui_vertex_h */

