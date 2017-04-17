/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    DC.h

Abstract:

    Main header for Defense Commander.

-------------------------------------------------------------------*/

#include <windows.h>
#ifdef DREAMCAST
#include <FloatMathLib.h>
#include "CE\\resource.h"
#else
#include <math.h>
#include "resource.h"
#endif
#include "DCDebug.h"
#include "DC3DMath.h"
#include "DCTimer.h"
#include "DCNoise.h"

typedef __int64 QWORD;

// Defines for directories.
enum FileDirectory
{
	ROOT_DIRECTORY=0,
	IMAGE_DIRECTORY,
	MESH_DIRECTORY,
	SOUND_DIRECTORY
};

#define ADD_TO_LINKED_LIST(HEADER,ITEM,PPREVIOUS,PNEXT) \
{ \
	if (HEADER) \
		HEADER->PPREVIOUS=ITEM; \
	ITEM->PNEXT=HEADER; \
	ITEM->PPREVIOUS=NULL; \
	HEADER=ITEM; \
}

#define REMOVE_FROM_LINKED_LIST(HEADER,ITEM,PPREVIOUS,PNEXT) \
{ \
	if (ITEM->PNEXT) \
		ITEM->PNEXT->PPREVIOUS=ITEM->PPREVIOUS; \
	if (ITEM->PPREVIOUS) \
		ITEM->PPREVIOUS->PNEXT=ITEM->PNEXT; \
	else \
		HEADER=ITEM->PNEXT; \
}

struct DCRect
{
	int X1,Y1,X2,Y2;
};

#define DC_AS_INT(val) ( *((int *)&(val)) )
#define DC_AS_DWORD(val) ( *((DWORD *)&(val)) )
#define DC_AS_FLOAT(val) ( *((float *)&(val)) )

#ifdef DEFINE_GLOBALS
#define DCGLOBAL
#else
#define DCGLOBAL extern
#endif

// Globals
DCGLOBAL BOOL gAppPaused;
DCGLOBAL BOOL gAppExit;
DCGLOBAL BOOL gHighDetail;
DCGLOBAL BOOL gHighTextureDetail;
DCGLOBAL BOOL gDisplayStats;
DCGLOBAL BOOL gCreateFishEyeView;

// Windows specific globals.
DCGLOBAL HINSTANCE gHInstance;

// Function prototypes.
// Error.cpp
#define NO_ERROR_MESSAGE -1
void SetErrorMessage(int Message);
int GetLastErrorMessage(void);

// Mesh.cpp. Exposed mesh functions.
BOOL MeshInit(void);
void MeshShutdown(void);
HANDLE GetMeshHandleFromName(TCHAR *Name);
void GetAllMeshes(void (*Callback)(TCHAR *Name, HANDLE Mesh));
float GetMeshBoundingRadius(HANDLE Mesh, BOOL ForRender);
DCVector GetMeshBoundingLowPoint(HANDLE Mesh, DCVector *Loc, DCVector *Rot);
DCVector GetMeshBoundingHighPoint(HANDLE Mesh, DCVector *Loc, DCVector *Rot);
int GetMeshID(HANDLE Mesh);
void SetMeshID(HANDLE Mesh, int ID);
HANDLE GetMeshHandleFromID(int ID);

// MiscPC/DC.cpp
void DisplayErrorMessage(int MessageId,...);

// TexRead.cpp.
BOOL ReadImageFileMipmappedScaleDown32x32(HANDLE FileName, int *Width, int *Height, DWORD *Flags, DWORD **Data);
BOOL ReadImageFileMipmapped(HANDLE FileName, int *Width, int *Height, DWORD *Flags, DWORD **Data);
BOOL ReadImageFileNotMipmapped(HANDLE FileName, int *Width, int *Height, DWORD *Flags, DWORD **Data);
BOOL ReadImageFileIntensityToAlphaMipmapped(HANDLE FileName, int *Width, int *Height, DWORD *Flags, DWORD **Data);
BOOL ReadImageFileIntensityToAlphaNotMipmapped(HANDLE FileName, int *Width, int *Height, DWORD *Flags, DWORD **Data);
BOOL ReadImageFilePlusAlphaMipmapped(HANDLE FileName, int *Width, int *Height, DWORD *Flags, DWORD **Data);
BOOL ReadImageFilePlusAlphaNotMipmapped(HANDLE FileName, int *Width, int *Height, DWORD *Flags, DWORD **Data);

// Util.cpp
void *DCMalloc(size_t Size);
void DCFree(void *Ptr);
void *DCMalloc32(size_t Size);
void DCFree32(void *Ptr);
#define DCSafeFree(Ptr) { if (Ptr) { DCFree(Ptr); Ptr=NULL; } }
#define DCSafeFree32(Ptr) { if (Ptr) { DCFree32(Ptr); Ptr=NULL; } }
#define DCZeroMemory(Dst,Size) { memset(Dst,0,Size); }
#define DCCopyMemory(Dst,Src,Size) { memcpy(Dst,Src,Size); }
BOOL ReadImageFile(TCHAR *FileName,int *Width, int *Height, int *Alpha, DWORD **Data);
void WriteImageFile(TCHAR *FileName, int Width, int Height, int Alpha, DWORD *Data, TCHAR *TargetDir=NULL);
BOOL DoesFileExist(FileDirectory Dir, TCHAR *FileName);
DWORD GetFileSize(FileDirectory Dir, TCHAR *FileName);
TCHAR *LoadTextString(int StringId);
void EnumFileNames(FileDirectory Dir, TCHAR *FileName, BOOL (*Callback)(TCHAR *, void *),void *User);
void *ReadFileIntoMemory(FileDirectory Dir, TCHAR *FileName, DWORD *FileSize);
HANDLE OpenFileForWrite(TCHAR *FileName, TCHAR *TargetDir);
void WriteToFile(HANDLE File, void *Data, int Size);
void CloseOpenFile(HANDLE File);
