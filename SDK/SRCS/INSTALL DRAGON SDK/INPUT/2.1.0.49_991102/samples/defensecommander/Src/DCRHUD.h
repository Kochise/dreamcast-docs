/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    DCRHUD.h

Abstract:

    HUD rendering stuff.

-------------------------------------------------------------------*/


struct HUDInfo
{
	int CurrentFire; // 0-Normal, 1-Seeker, 2-Explosive, 3-Rapid.
	int FireCount;
	int SmartBombCount;
	float Energy; // Range 0-1.
	int MissileTargetStatus; // 0-No target, 1-Have target, 2-Target locked.
	DCVector MissileTarget; // Location of targeted entity.
};