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
  Module Name:		km2api_pass.h

  Abstract:
	KAMUI = Kamui is abstruction model that is ultimate interface for PowerVR.
	'km2api_pass.h' define scene and pass API.

  Environment:
	ANSI C Compiler.

  Notes:
	It defines a scene from kmBeginScene until kmEndScene.
	It defines a pass from kmBeginPass until kmEndPass.
	scene can contain a maximum of 8 pass.
	kmRender of kmRenderTexture must be among kmEndScene from kmBeginScene();

  Revision History:

--*/

#if !defined(__kamui2_scene_api_h__)
#define __kamui2_scene_api_h__

/*++
kmBeginScene

proto type:

	KMSTATUS 
	kmBeginScene(
			IN  PKMSYSTEMCONFIGSTRUCT   pSystemConfigStruct
		)

Description:

Arguments:

Result:
	KMSTATUS_SUCCESS		ê¨å˜

--*/
KMSTATUS  KMAPI
kmBeginScene(
		IN  PKMSYSTEMCONFIGSTRUCT   pSystemConfigStruct
	);

/*++
kmEndScene

proto type:

	KMSTATUS 
	kmEndScene(
			IN  PKMSYSTEMCONFIGSTRUCT   pSystemConfigStruct
		)

Description:

Arguments:

Result:
	KMSTATUS_SUCCESS		ê¨å˜

--*/
KMSTATUS  KMAPI
kmEndScene(
		IN  PKMSYSTEMCONFIGSTRUCT   pSystemConfigStruct
	);

/*++
kmBeginPass

proto type:

	KMSTATUS 
	kmBeginPass(
			IN OUT  PKMVERTEXBUFFDESC   pVertexBuffDesc
		)

Description:

Arguments:

Result:
	KMSTATUS_SUCCESS		ê¨å˜

--*/
KMSTATUS  KMAPI
kmBeginPass(		
		IN OUT  PKMVERTEXBUFFDESC   pVertexBuffDesc
	);

/*++
kmEndPass

proto type:

	KMSTATUS 
	kmEndPass(
			IN OUT  PKMVERTEXBUFFDESC   pVertexBuffDesc
		)

Description:

Arguments:

Result:
	KMSTATUS_SUCCESS		ê¨å˜

--*/
KMSTATUS  KMAPI
kmEndPass(		
		IN OUT  PKMVERTEXBUFFDESC   pVertexBuffDesc
	);

/*++
kmContinuePass

proto type:

	KMSTATUS 
	kmContinuePass(
			IN OUT  PKMVERTEXBUFFDESC   pVertexBuffDesc
		)

Description:

Arguments:

Result:
	KMSTATUS_SUCCESS		ê¨å˜

--*/
KMSTATUS  KMAPI
kmContinuePass(		
		IN OUT  PKMVERTEXBUFFDESC   pVertexBuffDesc
	);
#endif
