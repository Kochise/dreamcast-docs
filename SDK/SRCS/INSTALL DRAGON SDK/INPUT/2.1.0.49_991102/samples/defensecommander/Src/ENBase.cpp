/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    ENBase.cpp

Abstract:

    Entity "AI" - base class code.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGame.h"
#include "DCEnergy.h"

// Manufacture function.
EntityBase *ManufactureEntityBase()
{
	return new(EntityBase);
}

void EntityBase::Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2)
{
	// Save data.
	Mesh=InMesh;
	Loc=*InLoc;
	Rot=*InRot;
	User1=InUser1;
	User2=InUser2;
	// Init references (to none).
	RefList=NULL;
}

void EntityBase::Shutdown()
{
	// Zero all references to this entity.
	for (ReferenceClass *Item=RefList,*Next;Item;Item=Next)
	{
		// Get next item while we can.
		Next=Item->Next;
		// Zero reference.
		*(Item->Ref)=NULL;
		// Release memory for item.
		DCFree(Item);
	}
}

void EntityBase::AddRef(EntityBase **Ref)
{
	if (Ref)
	{
		ReferenceClass *NewClass;

		NewClass=(ReferenceClass *)DCMalloc(sizeof(ReferenceClass));
		if (!NewClass)
		{
			// If no memory, zero the reference now since we
			// won't be able to do it later.
			*Ref=NULL;
		}
		else
		{
			NewClass->Ref=Ref;
			NewClass->Next=RefList;
			RefList=NewClass;
		}
	}
}

void EntityBase::RemoveRef(EntityBase **Ref)
{
	for (ReferenceClass *Item=RefList,*Prev=NULL;Item;)
	{
		// See if reference matches.
		if (Item->Ref==Ref)
		{
			// Get next while we still have it.
			ReferenceClass *Next=Item->Next;

			// Remove item from list.
			if (Prev)
				Prev->Next=Item->Next;
			else
				RefList=Item->Next;
			
			// Release memory for item.
			DCFree(Item);
			
			// Move on to next.
			Item=Next;
		}
		else
		{
			// Move on to next item.
			Prev=Item;
			Item=Item->Next;
		}
	}
}

void EntityBase::SetPosition(DCVector *InLoc,DCVector *InRot)
{
	Loc=*InLoc;
	Rot=*InRot;
}

void EntityBase::GetPosition(DCVector *OutLoc,DCVector *OutRot)
{
	*OutLoc=Loc;
	*OutRot=Rot;
}

void EntityBase::GetVelocity(DCVector *OutVel)
{
	*OutVel=DCVector(0,0,0);
}

HANDLE EntityBase::GetMesh(BOOL ForRender)
{
	return Mesh;
}

void EntityBase::ServerTick(float FrameDeltaTime)
{
}

void EntityBase::ClientTick(float FrameDeltaTime)
{
}

BOOL EntityBase::Touch(CollisionInfo *Info)
{
	return FALSE;
}

void EntityBase::Killed(void)
{
}

float EntityBase::GetDamage()
{
	// We can't really have things flying through each other, so for things that don't have
	// their own handlers we'll make sure they destroy anything that touches them.
	return INFINITE_DAMAGE;
}

void *EntityBase::Message(void *Message)
{
	return NULL;
}
