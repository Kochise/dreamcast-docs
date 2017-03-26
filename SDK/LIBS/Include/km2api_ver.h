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
  Module Name:		km2api_ver.h

  Abstract:
	KAMUI = Kamui is abstruction model that is ultimate interface for PowerVR.
	'km2api_ver.h' define Version API.

  Environment:
	ANSI C Compiler.

  Notes:
	define Kamui's version api proto-types.

  Revision History:

--*/

#if !defined(__kamui2_version_api_h__)
#define __kamui2_version_api_h__
/*++
kmGetVersionInfo

proto type:
	KMSTATUS
	kmGetVersionInfo(
			PKMVERSIONINFO pVersionInfo
		);

Description:
	ライブラリのバージョン情報を取得します。
	バージョン情報構造体の内容については別途構造体一覧をご覧ください。

Arguments:
	OUT	pVersionInfo		あらかじめ確保しておいたKMVERSIONINFO構造体へのポインタを示します。

Result:
	KMSTATUS_SUCCESS		成功

--*/

KMSTATUS KMAPI
kmGetVersionInfo(
		PKMVERSIONINFO pVersionInfo
	);
#endif
