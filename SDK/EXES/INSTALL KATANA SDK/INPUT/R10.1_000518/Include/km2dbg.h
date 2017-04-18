/*++

  COPYRIGHT        (C) NEC        Corporation 1999

  All rights reserved by NEC Corporation. This program must be
  used solely for the purpose for which it was furnished by NEC
  Corporation. No part of this program may be reproduced or
  disclosed to others, in any form, without the prior written
  permission of NEC Corporation.
  Use of copyright notice does not evidence publication of this
  program.

  Author     :		T.Hirata(NEC Software,Ltd.)
  Module Name:		km2dbg.h

  Abstract:
	register assert() callback function.

  Environment:
	SHC Compiler.

  Notes:

  Revision History:
	1999/03/11	Create New.

--*/
#if !defined(__KM2DBG_H__)
#define	__KM2DBG_H__

KMSTATUS KMAPI
kmSetAssertCallback(
        IN  PKMCALLBACKFUNC pCallback
	);

#endif