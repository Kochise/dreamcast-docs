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
  Module Name:		km2api.h

  Abstract:
	KAMUI = Kamui is abstruction model that is ultimate interface for PowerVR.
	'km2api.h' include prototype for kamui2 function.

  Environment:
	ANSI C Compiler.

  Notes:
	define Kamui's api proto-types.

  Revision History:

--*/

#if !defined(__kamui_api_h)
#define __kamui_api_h

#ifdef __cplusplus
extern "C" {
#endif 

#include "km2api_ver.h"
#include "km2api_dev.h"
#include "km2api_cfg.h"
#include "km2api_misc.h"
#include "km2api_pass.h"
#include "km2api_render.h"
#include "km2api_clb.h"
#include "km2api_tex.h"
#include "km2vtxapi.h"

#define kmRegisterDefaultStripContext(a,b) 	kmRegisterStripContext(b,a)

#ifdef __cplusplus
}
#endif 

#endif
