/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    ENTurretSwivel.cpp

Abstract:

	Entity "AI" - turret swivel.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGame.h"

class EntityTurretSwivel : EntityBase
{
	void ServerTick(float FrameDeltaTime);
	HANDLE GetMesh(BOOL ForRender);
};

// Manufacture function.
EntityBase *ManufactureEntityTurretSwivel()
{
	void *Entity=new(EntityTurretSwivel);
	
	return (EntityBase *)Entity;
}

void EntityTurretSwivel::ServerTick(float FrameDeltaTime)
{
	// If not in observer mode get position from viewer direction.
	if (!gGame.IsObserverMode())
	{
		DCVector ViewLoc,ViewRot;
		gGame.GetViewerCoords(&ViewLoc,&ViewRot);
		gGame.SetEntityPosition(this,&Loc,&DCVector(0,ViewRot.Y,0));
	}
}

HANDLE EntityTurretSwivel::GetMesh(BOOL ForRender)
{
	// Don't return mesh unless we are in observer mode.
	return (gGame.IsObserverMode() || !ForRender) ? Mesh : NULL;
}
