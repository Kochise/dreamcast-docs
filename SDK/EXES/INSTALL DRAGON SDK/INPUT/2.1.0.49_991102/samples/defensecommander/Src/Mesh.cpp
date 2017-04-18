/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    Mesh.cpp

Abstract:

    Mesh management and utility functions. Rendering is handled 
	in RMesh.cpp.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGraphics.h"
#include "DCMesh.h"

struct MeshListItem
{
	MeshListItem *Next;
	HANDLE Mesh;
	TCHAR Name[1];
};

static MeshListItem *MeshList;
static int CurrentMeshID=1; // Should be in range 0-255 since only byte is send across network.

static void ScaleMesh(TSMHeader *Mesh, float Scale)
{
	// Scale vertices.
	int i;
	for (i=0;i<Mesh->VertsCount;i++)
	{
		TSMVertex *V=Mesh->Verts+i;
		V->X*=Scale;
		V->Y*=Scale;
		V->Z*=Scale;
	}

	// Scale bounding radius.
	Mesh->BoundingRadiusCollision*=Scale;
	Mesh->BoundingRadiusView*=Scale;

	// Scale bounding verts.
	for (i=0;i<Mesh->BoundingVertsCount;i++)
	{
		TSMVector *V=Mesh->BoundingVerts+i;
		V->X*=Scale;
		V->Y*=Scale;
		V->Z*=Scale;
	}

	// Scale bounding planes.
	for (i=0;i<Mesh->BoundingPlanesCount;i++)
	{
		TSMPlane *V=Mesh->BoundingPlanes+i;
		V->W*=Scale;
	}

	// Scale coronas.
	for (i=0;i<TSM_NUM_MATERIALS;i++)
	{
		TSMMaterial *Mat=Mesh->Materials + i;
		if ((Mat->Flags & TSM_MFLAG_USED) && (Mat->Flags & TSM_MFLAG_CORONA))
		{
			int Count=((DWORD *)Mat->Indices)[0];
			TSMCorona *Corona=(TSMCorona *)(Mat->Indices+2);
			for (;Count;Count--,Corona++)
			{
				// Fill in vertex structures.
				Corona->Radius*=Scale;
				Corona->CX*=Scale;
				Corona->CY*=Scale;
				Corona->CZ*=Scale;
			}
		}
	}
}

#ifndef DREAMCAST
// Need to adjust vertex normals when flat shading since D3D (PC) uses
// first triangle vertex for color, not last.
void FixupFlatNormals(TSMHeader *Mesh)
{
	for (int i=0;i<TSM_NUM_MATERIALS;i++)
	{
		TSMMaterial *Mat=Mesh->Materials + i;
		if ((Mat->Flags & TSM_MFLAG_USED) && 
			!(Mat->Flags & TSM_MFLAG_SMOOTH) &&
			!(Mat->Flags & TSM_MFLAG_CORONA))
		{
			signed short *Indices=Mat->Indices;

			// Walk indice list, moving third normals 2 vertices back.
			while (*Indices!=0)
			{
				int Count=*(Indices++);

				for (int i=0;i<Count-2;i++)
				{
					Indices[i*2+1]=Indices[(i+2)*2+1];
				}
				Indices+=Count*2;
			}
		}
	}
}
#endif

// Callback gets mesh names. Loads mesh and adds associated textures.
static BOOL TSMCallback(TCHAR *FileName, void *User)
{
	// Read the file.
	TSMHeader *Mesh=(TSMHeader *)ReadFileIntoMemory(MESH_DIRECTORY,FileName,NULL);
	if (!Mesh)
		return TRUE;

	// Check mesh header version.
	if (Mesh->Version!=TSM_VERSION)
		return TRUE;

	// Fixup pointers and add textures.
	Mesh->BoundingVerts=(TSMVector *)( (int)Mesh->BoundingVerts + (int)Mesh );
	Mesh->BoundingPlanes=(TSMPlane *)( (int)Mesh->BoundingPlanes + (int)Mesh );
	Mesh->Verts=(TSMVertex *)( (int)Mesh->Verts + (int)Mesh );
	Mesh->Normals=(TSMVector *)( (int)Mesh->Normals + (int)Mesh );
	for (int i=0;i<TSM_NUM_MATERIALS;i++)
	{
		TSMMaterial *Mat=Mesh->Materials + i;
		if (Mat->Flags & TSM_MFLAG_USED)
		{
			Mat->Indices=(signed short *)( (int)Mat->Indices + (int)Mesh );

			// Convert texture name from word to whatever TCHAR is.
			TCHAR *TexName=(TCHAR *)Mat->TextureName;
			for (int j=0;j<TSM_TEXTURE_NAME_SIZE;j++)
				TexName[j]=(TCHAR)Mat->TextureName[j];
			TexName[TSM_TEXTURE_NAME_SIZE-1]=0;

			if (TexName[0])
				Mat->TextureHandle=gGraphics.AddTexture(
					ReadImageFileMipmapped,
					TexName,
					TRUE,
					((Mat->Flags & TSM_MFLAG_TRANSLUCENT) && !(Mat->Flags & TSM_MFLAG_CORONA_DIRECTIONAL)) );
			else
				Mat->TextureHandle=NULL;
		}
	}
	
	// Stuff mesh ID in version variable since we won't need it any more.
	Mesh->Version=DC_AS_FLOAT(CurrentMeshID);
	CurrentMeshID++;

	// Scale mesh.
	ScaleMesh(Mesh,(Mesh->Flags & TSM_FLAG_FIRST_PERSON) ? MESH_SCALE*1.5f : MESH_SCALE);

#ifndef DREAMCAST
	// Need to adjust vertex normals when flat shading since D3D (PC) uses
	// first triangle vertex for color, not last.
	FixupFlatNormals(Mesh);
#endif

	// Allocate list item.
	int Size=sizeof(MeshListItem)+(lstrlen(FileName)-4)*sizeof(TCHAR);
	MeshListItem *Item=(MeshListItem *)DCMalloc(Size);
	if (!Item)
	{
		DCFree(Mesh);
		return TRUE;
	}
	DCZeroMemory(Item,Size);
	
	// Set list item and add to chain.
	Item->Next=MeshList;
	Item->Mesh=Mesh;
	memcpy(Item->Name,FileName,(lstrlen(FileName)-4)*sizeof(TCHAR));
	Item->Name[lstrlen(FileName)-4]=0;

	MeshList=Item;

	return TRUE;
}

// Exposed mesh functions.
// Initializes the meshes. Loads all meshes.
BOOL MeshInit(void)
{
	MeshList=NULL;
	CurrentMeshID=1;

	EnumFileNames(MESH_DIRECTORY,TEXT("*.TSM"),TSMCallback,NULL);
	
	return TRUE;
}

void MeshShutdown(void)
{
	// Free all our meshes.
	for (MeshListItem *Item=MeshList,*Next;Item!=NULL;Item=Next)
	{
		// Get next while we still can.
		Next=Item->Next;
		
		// Free mesh.
		DCFree(Item->Mesh);

		// Free list item.
		DCFree(Item);
	}
}

// Adds a user render mesh to the mesh list.
void AddUserRenderMesh(TCHAR *Name,
					   BOOL HaveOpaque, BOOL HaveTranslucent,
					   USER_MESH_RENDER_CALLBACK RenderCallback, 
					   USER_MESH_RADIUS_CALLBACK RadiusCallback, 
					   HANDLE CallbackData)
{
	// Allocate mesh header.
	UserRenderMeshHeader *Mesh=(UserRenderMeshHeader *)DCMalloc(sizeof(UserRenderMeshHeader));
	if (!Mesh)
		return;
	DCZeroMemory(Mesh,sizeof(UserRenderMeshHeader));

	// Fill in mesh header.
	Mesh->Version=DC_AS_FLOAT(CurrentMeshID);
	CurrentMeshID++;

	Mesh->Flags=(HaveOpaque ? TSM_FLAG_HAVE_OPAQUE : 0) |
				(HaveTranslucent ? TSM_FLAG_HAVE_TRANS : 0) |
				TSM_FLAG_USER_RENDER;
	Mesh->RenderCallback=RenderCallback;
	Mesh->RadiusCallback=RadiusCallback;
	Mesh->CallbackUserData=CallbackData;
	
	// Allocate list item.
	int Size=sizeof(MeshListItem)+lstrlen(Name)*sizeof(TCHAR);
	MeshListItem *Item=(MeshListItem *)DCMalloc(Size);
	if (!Item)
	{
		DCFree(Mesh);
		return;
	}
	DCZeroMemory(Item,Size);
	
	// Set list item and add to chain.
	Item->Next=MeshList;
	Item->Mesh=Mesh;
	memcpy(Item->Name,Name,lstrlen(Name)*sizeof(TCHAR));
	Item->Name[lstrlen(Name)]=0;

	MeshList=Item;
}

// Returns the mesh handle associated with the mesh name.
HANDLE GetMeshHandleFromName(TCHAR *Name)
{
	// Walk mesh list looking for name.
	for (MeshListItem *Item=MeshList;Item!=NULL;Item=Item->Next)
	{
		if (lstrcmpi(Name,Item->Name)==0)
			return Item->Mesh;
	}

	return NULL;
}

HANDLE GetMeshHandleFromID(int ID)
{
	// Walk mesh list looking for ID.
	for (MeshListItem *Item=MeshList;Item!=NULL;Item=Item->Next)
	{
		if (DC_AS_INT(((TSMHeader *)(Item->Mesh))->Version)==ID)
			return Item->Mesh;
	}

	return NULL;
}


void GetAllMeshes(void (*Callback)(TCHAR *Name, HANDLE Mesh))
{
	for (MeshListItem *Item=MeshList;Item!=NULL;Item=Item->Next)
	{
		Callback(Item->Name,Item->Mesh);
	}
}

int GetMeshID(HANDLE Mesh)
{
	if (Mesh)
		return DC_AS_INT(((TSMHeader *)Mesh)->Version);
	else
		return 0;
}

void SetMeshID(HANDLE Mesh, int ID)
{
	if (Mesh)
		((TSMHeader *)Mesh)->Version=DC_AS_FLOAT(ID);
}

// Gets the bounding radius of the mesh.
float GetMeshBoundingRadius(HANDLE Mesh, BOOL ForRender)
{
	if (Mesh)
	{
		if (((TSMHeader *)Mesh)->Flags & TSM_FLAG_USER_RENDER)
		{
			return ((UserRenderMeshHeader *)Mesh)->RadiusCallback(((UserRenderMeshHeader *)Mesh)->CallbackUserData, ForRender);
		}
		else
		{
			if (ForRender)
				return ((TSMHeader *)Mesh)->BoundingRadiusView;
			else
				return ((TSMHeader *)Mesh)->BoundingRadiusCollision;
		}
	}
	else
	{
		return 0.0f;
	}
}

// Gets the lowest point of the mesh.
DCVector GetMeshBoundingLowPoint(HANDLE Mesh, DCVector *Loc, DCVector *Rot)
{
	// Handle when Mesh is NULL.
	if (!Mesh)
		return *Loc;

	// If a user render mesh we must get radius from user funcion.
	if (((TSMHeader *)Mesh)->Flags & TSM_FLAG_USER_RENDER)
	{
		float R=((UserRenderMeshHeader *)Mesh)->RadiusCallback(((UserRenderMeshHeader *)Mesh)->CallbackUserData, FALSE);
		return DCVector(Loc->X,Loc->Y-R,Loc->Z);
	}

	// Create transformation matrix.
	DCMatrix16 M;
	gGraphics.MatrixIdentity();
	gGraphics.MatrixRotateZ(Rot->Z);
	gGraphics.MatrixRotateX(Rot->X);
	gGraphics.MatrixRotateY(Rot->Y);
	gGraphics.MatrixTranslate(Loc->X,Loc->Y,Loc->Z);
	gGraphics.MatrixGet(&M);

	DCVector Min;
	for (int i=0;i<((TSMHeader *)Mesh)->BoundingVertsCount;i++)
	{
		TSMVector *V=((TSMHeader *)Mesh)->BoundingVerts + i;
		
		float X=M.m11*V->X + M.m21*V->Y + M.m31*V->Z + M.m41;
		float Y=M.m12*V->X + M.m22*V->Y + M.m32*V->Z + M.m42;
		float Z=M.m13*V->X + M.m23*V->Y + M.m33*V->Z + M.m43;
	
		if (i==0 || Y<Min.Y)
		{
			Min=DCVector(X,Y,Z);
		}
	}
	
	return Min;
}

// Gets the highest point of the mesh.
DCVector GetMeshBoundingHighPoint(HANDLE Mesh, DCVector *Loc, DCVector *Rot)
{
	// Handle when Mesh is NULL.
	if (!Mesh)
		return *Loc;

	// If a user render mesh we must get radius from user funcion.
	if (((TSMHeader *)Mesh)->Flags & TSM_FLAG_USER_RENDER)
	{
		float R=((UserRenderMeshHeader *)Mesh)->RadiusCallback(((UserRenderMeshHeader *)Mesh)->CallbackUserData, FALSE);
		return DCVector(Loc->X,Loc->Y+R,Loc->Z);
	}

	// Create transformation matrix.
	DCMatrix16 M;
	gGraphics.MatrixIdentity();
	gGraphics.MatrixRotateZ(Rot->Z);
	gGraphics.MatrixRotateX(Rot->X);
	gGraphics.MatrixRotateY(Rot->Y);
	gGraphics.MatrixTranslate(Loc->X,Loc->Y,Loc->Z);
	gGraphics.MatrixGet(&M);

	DCVector Max;
	for (int i=0;i<((TSMHeader *)Mesh)->BoundingVertsCount;i++)
	{
		TSMVector *V=((TSMHeader *)Mesh)->BoundingVerts + i;
		
		float X=M.m11*V->X + M.m21*V->Y + M.m31*V->Z + M.m41;
		float Y=M.m12*V->X + M.m22*V->Y + M.m32*V->Z + M.m42;
		float Z=M.m13*V->X + M.m23*V->Y + M.m33*V->Z + M.m43;
	
		if (i==0 || Y>Max.Y)
		{
			Max=DCVector(X,Y,Z);
		}
	}
	
	return Max;
}
