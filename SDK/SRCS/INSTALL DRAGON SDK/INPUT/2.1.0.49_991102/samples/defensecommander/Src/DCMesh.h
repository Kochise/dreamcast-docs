/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    DCMesh.h

Abstract:

    Mesh related functions.

-------------------------------------------------------------------*/

#include "TSMesh.h"

#define MESH_SCALE 6.0f

// Structure to pass to the callback.
struct RMeshCurrentState
{
	DWORD LastFlags;
	HANDLE LastTexture;
	BOOL  Translucent;
	BOOL  RenderFirstPerson;
};

typedef void (*USER_MESH_RENDER_CALLBACK)(HANDLE Data, DCVector *Loc, DCVector*Rot, RMeshCurrentState *CurrState);
typedef float (*USER_MESH_RADIUS_CALLBACK)(HANDLE Data, BOOL ForRender);

// First part of this structure is identical to TSMHeader
struct UserRenderMeshHeader
{
	float		Version;
	DWORD		Flags;

	USER_MESH_RENDER_CALLBACK	RenderCallback;
	USER_MESH_RADIUS_CALLBACK	RadiusCallback;
	HANDLE		CallbackUserData;
};

void AddUserRenderMesh(TCHAR *Name,
					   BOOL HaveOpaque, BOOL HaveTranslucent,
					   USER_MESH_RENDER_CALLBACK RenderCallback, 
					   USER_MESH_RADIUS_CALLBACK RadiusCallback, 
					   HANDLE CallbackData);
