/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    Collide.cpp

Abstract:

	Collision handling code. 

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCWorld.h"
#include "DCCollide.h"
#include "DCGame.h"

// In RTerrain.cpp.
float GetTerrainHeight(float X, float Z);

// Handles observer collision with an entity in the world.
void ObserverCallback(HANDLE Mesh, DCVector *Loc, DCVector *Rot, void *User)
{
#define MIN_R (R+(DCW_BASE_ZNEAR*2))

	DCVector *NewLocation=(DCVector *)User;

	DCVector Diff=*NewLocation - *Loc;
	float Dist=Diff.FastLength();
	float R=GetMeshBoundingRadius(Mesh, FALSE);

	if (R>0 && Dist<MIN_R)
	{
		// Too close to object so push observer back.
		if (Dist==0.0f)
		{
			// In same spot so no direction to push in. Just push up.
			NewLocation->Y+=MIN_R;
		}
		else
		{
			*NewLocation=*Loc + (Diff*(MIN_R/Dist));
		}
	}
}

// Forces observer position to be within its movement limits.
// If location is outside limits, will move it back inside.
void HandleObserverCollision(DCVector *NewLocation, DCVector *OriginalLocation)
{
#ifdef _DEBUG
	// Allow the observer to go anywhere in debug build.
	return;
#endif

	// First, make sure not intersecting with any objects.
//	gGame.GetCollisionEntityMeshes(COLLISION_BADDIE,ObserverCallback,NewLocation,FALSE);
//	gGame.GetCollisionEntityMeshes(COLLISION_GOODIE,ObserverCallback,NewLocation,FALSE);
	gGame.GetAllEntityMeshes(ObserverCallback,NewLocation,FALSE);

	// Limit distance from center of world.
	float R=(float)sqrt(NewLocation->X*NewLocation->X + NewLocation->Z*NewLocation->Z);
	if (R > DCW_OBSERVER_MAX_RADIUS)
	{
		NewLocation->X*=DCW_OBSERVER_MAX_RADIUS/R;
		NewLocation->Z*=DCW_OBSERVER_MAX_RADIUS/R;
	}

	// Limit how low we can go.
	if (NewLocation->Y<DCW_OBSERVER_HEIGHT_MIN)
		NewLocation->Y=DCW_OBSERVER_HEIGHT_MIN;

	// Limit how high we can go. Max height is curved.
	float SphereY=(DCW_OBSERVER_HEIGHT_CENTER_MAX*DCW_OBSERVER_HEIGHT_CENTER_MAX -
				   DCW_OBSERVER_HEIGHT_OUTER_MAX*DCW_OBSERVER_HEIGHT_OUTER_MAX -
				   DCW_OBSERVER_MAX_RADIUS*DCW_OBSERVER_MAX_RADIUS)/
				  (2*(DCW_OBSERVER_HEIGHT_CENTER_MAX-DCW_OBSERVER_HEIGHT_OUTER_MAX));
	float SphereR=DCW_OBSERVER_HEIGHT_CENTER_MAX-SphereY;
	float YMax=(float)sqrt(SphereR*SphereR - R*R) + SphereY;
	if (NewLocation->Y > YMax)
		NewLocation->Y = YMax;

	// Stop us from getting under the terrain.
	float TerrainHeight=GetTerrainHeight(NewLocation->X,NewLocation->Z) +
						DCW_OBSERVER_HEIGHT_ABOVE_TERRAIN;
	if (NewLocation->Y < TerrainHeight)
		NewLocation->Y = TerrainHeight;

	// One thing to note here. It is possible to travel over a mountain peak and get
	// above DCW_OBSERVER_HEIGHT_MAX. We could prevent it by going back to
	// OriginalLocation but we don't since this isn't a huge problem and getting stuck
	// behind mountains would be annonying.
}

// Returns TRUE if the point is inside the sphere.
BOOL IsPointInSphere(DCVector *Point, DCVector *SphereCenter, float SphereRadius)
{
	if (Point->DistSquared(*SphereCenter) <= SphereRadius*SphereRadius)
		return TRUE;
	else
		return FALSE;
}

// Returns true if the spheres intersect.
BOOL IsSphereInSphere(DCVector *Sphere1Center, float Sphere1Radius,
					  DCVector *Sphere2Center, float Sphere2Radius)
{
	float R=Sphere1Radius+Sphere2Radius;
	if (Sphere1Center->DistSquared(*Sphere2Center) <= R*R)
		return TRUE;
	else
		return FALSE;
}

// Returns true if the point is inside the mesh hull.
BOOL IsPointInMeshHull(DCVector *Point, HANDLE Mesh, DCVector *Loc, DCVector *Rot)
{
	float R=GetMeshBoundingRadius(Mesh, FALSE);

	if (Point->DistSquared(*Loc) <= R*R)
		return TRUE;
	else
		return FALSE;
}

// Returns true if the line segment is inside the mesh hull.
BOOL IsMovingPointInMeshHull(DCVector *Point, DCVector *Mov, HANDLE Mesh, DCVector *Loc, DCVector *Rot)
{
	// Get bounding radius of hull.
	float R=GetMeshBoundingRadius(Mesh, FALSE);

	if (Mov->X==0 && Mov->Y==0 && Mov->Z==0)
	{
		// Special case where point is not moving. Just to simple
		// point in sphere test.
		if (Point->DistSquared(*Loc) <= R*R)
			return TRUE;
		else
			return FALSE;
	}

	// First do quick radius check.
	float MovLen2=Mov->X*Mov->X + Mov->Y*Mov->Y + Mov->Z*Mov->Z;
	float TotalR=FastSqrt(MovLen2) + R;
	if (Point->DistSquared(*Loc) > TotalR*TotalR)
		return FALSE;
	
	// Intersection of bounding spheres so good chance of intersection.
	// Next see if line of motion intersects with mesh hull. This will
	// reject most cases where we don't have an intersection.
	// Calculate distance squared from line of motion to center of hull.
	DCVector VPH=*Loc - *Point;
	DCVector Cross=VPH ^ *Mov;
	float D2=(Cross.X*Cross.X + Cross.Y*Cross.Y + Cross.Z*Cross.Z) / MovLen2;
	float R2=R*R;
	if (D2 <= R2)
	{
#if 1
		// If we got here, good enough to intersection.
		return TRUE;
#else
		// Line intersects with sphere so we just have to make sure
		// intersection is between our end points.
		// We do this by using plane perpendicular to line segment and 
		// through hull center. We then calculate relative distances of
		// end points to plane and make sure they have different signs.
		// Already have vector (Mov).
		// Need W component of plane.
		float W=-(Mov->X*Loc->X + Mov->Y*Loc->Y + Mov->Z*Loc->Z);
		// Calculate end points.
		DCVector End1=*Point + *Mov;
		DCVector End2=*Point - *Mov;
		// Calculate relative distances.
		float D1=End1.X*Mov->X + End1.Y*Mov->Y + End1.Z*Mov->Z + W;
		float D2=End2.X*Mov->X + End2.Y*Mov->Y + End2.Z*Mov->Z + W;
		if (D1*D2<=0)
			return TRUE;
		// Even if nearest point is not between end points, it is still
		// possible for line segment to be in sphere. Check for this by
		// checking if either end point is in sphere.
		if (End1.DistSquared(*Loc) <= R2)
			return TRUE;
		if (End2.DistSquared(*Loc) <= R2)
			return TRUE;
#endif
	}
	return FALSE;
}

// Returns true if the mesh hulls intersect.
BOOL IsMeshHullInMeshHull(HANDLE Mesh1, DCVector *Loc1, DCVector *Rot1,
						  HANDLE Mesh2, DCVector *Loc2, DCVector *Rot2)
{
	float R=GetMeshBoundingRadius(Mesh1, FALSE)+GetMeshBoundingRadius(Mesh2, FALSE);

	if (Loc1->DistSquared(*Loc2) <= R*R)
		return TRUE;
	else
		return FALSE;
}
