/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    DCRender.h

Abstract:

   Stuff for rendering scene. 

-------------------------------------------------------------------*/

struct RenderClass
{
	// Useful frame specific stuff.
	struct FrameStruct
	{
		float FrameTime;
		DCVector ViewLoc,ViewRot;
		BOOL IsObserverMode;
		BOOL IsTimePaused;
		DCVector ViewVecX,ViewVecY,ViewVecZ;
		DCMatrix16 ProjectionMatrix,ViewMatrix,InvViewMatrix;
		float ZNear,ZFar;

		struct FirstPersonStruct
		{
			HANDLE Mesh;
			DCVector Loc,Rot;
		} FirstPerson;
	} Frame;

	HANDLE GridTexture;
};

extern RenderClass gRender;

