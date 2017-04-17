/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    DCCollide.h

Abstract:

    Collision functions.

-------------------------------------------------------------------*/

void HandleObserverCollision(DCVector *NewLocation, DCVector *OriginalLocation);
float GetTerrainHeight(float X, float Z); // This is actually in RTerrain.cpp.
float GetDangerHeight(float X, float Z); // This is actually in RTerrain.cpp.
float GetDangerAngle(float X, float Z, float DirX, float DirZ); // This is actually in RTerrain.cpp.
BOOL IsPointInSphere(DCVector *Point, DCVector *SphereCenter, float SphereRadius);
BOOL IsSphereInSphere(DCVector *Sphere1Center, float Sphere1Radius,
					  DCVector *Sphere2Center, float Sphere2Radius);
BOOL IsPointInMeshHull(DCVector *Point, HANDLE Mesh, DCVector *Loc, DCVector *Rot);
BOOL IsMovingPointInMeshHull(DCVector *Point, DCVector *Mov, HANDLE Mesh, DCVector *Loc, DCVector *Rot);
BOOL IsMeshHullInMeshHull(HANDLE Mesh1, DCVector *Loc1, DCVector *Rot1,
						  HANDLE Mesh2, DCVector *Loc2, DCVector *Rot2);
