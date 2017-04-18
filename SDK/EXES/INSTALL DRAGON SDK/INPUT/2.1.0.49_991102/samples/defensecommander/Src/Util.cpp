/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    Util.cpp

Abstract:

    General utility functions such as memory allocation and file IO.

-------------------------------------------------------------------*/

#include "DC.h"

TCHAR *DirectoryNames[]=
{
#ifdef DREAMCAST
	TEXT("\\CD-ROM\\Art"),
	TEXT("\\CD-ROM\\Art\\Images"),
	TEXT("\\CD-ROM\\Art\\Meshes"),
	TEXT("\\CD-ROM\\Art\\Sounds")
#else
	TEXT("Art"),
	TEXT("Art\\Images"),
	TEXT("Art\\Meshes"),
	TEXT("Art\\Sounds")
#endif
};

// Allocates a block of memory.
void *DCMalloc(size_t Size)
{
	return malloc(Size);
}

// Frees a block of memory allocated with DCMalloc.
void DCFree(void *Ptr)
{
	free(Ptr);
}

void *DCMalloc32(size_t Size)
{
	void *Mem=(BYTE *)malloc(Size+31+4);
	int RetI=((int)(Mem)+31+4) & ~0x1F;
	void **Ret=(void **)RetI;
	Ret[-1]=Mem;
	
	return (void *)Ret;
}

void DCFree32(void *Ptr)
{
	void *Mem=((void **)Ptr)[-1];

	free(Mem);
}

// Redefine new and delete.
void* operator new(size_t Size)
{
	return ::DCMalloc(Size); 
}

void* operator new[](size_t Size)
{
	return ::DCMalloc(Size);
}

void operator delete(void* Ptr)
{
	::DCFree(Ptr);
}

void operator delete[](void* Ptr)
{
	::DCFree(Ptr);
}

// Reads an image file from disk. This function will allocate the necessary
// memory for the data. 
BOOL ReadImageFile(TCHAR *FileName, int *Width, int *Height, BOOL *Alpha, DWORD **Data)
{
	// Make filename.
	TCHAR Name[0x200];
	lstrcpy(Name,DirectoryNames[IMAGE_DIRECTORY]);
	lstrcat(Name,TEXT("\\"));
	lstrcat(Name,FileName);
	lstrcat(Name,TEXT(".bmp"));

	// Open input file.
	HANDLE f;
	f=CreateFile(Name,
				 GENERIC_READ,
				 FILE_SHARE_READ,
				 NULL,
				 OPEN_EXISTING,
				 FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
				 NULL);
	if (f==INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	
	// Read file headers.
	BITMAPFILEHEADER FileHeader;
	BITMAPINFOHEADER InfoHeader;
	DWORD BytesRead;

	if (!ReadFile(f,&FileHeader,sizeof(BITMAPFILEHEADER),&BytesRead,NULL) ||
		!ReadFile(f,&InfoHeader,sizeof(BITMAPINFOHEADER),&BytesRead,NULL))
	{
		DC_ERROR(("Error reading from file %s.\n",FileName));
		CloseHandle(f);
		return FALSE;
	}
	
	// Get stuff we need from headers.
	*Width=InfoHeader.biWidth;
	*Height=InfoHeader.biHeight;
	*Alpha=FALSE;
 
	// Allocate memory for image.
	*Data=(DWORD *)DCMalloc(*Width * *Height * sizeof(DWORD));
	if (!*Data)
	{
		DC_ERROR(("Could allocate memory for %s (%ix%i).\n",
				  FileName,*Width,*Height));
		CloseHandle(f);
		return FALSE;
	}

	// Seek to pixel data.
	SetFilePointer(f,FileHeader.bfOffBits,NULL,FILE_BEGIN);

	// Read data in blocks.
#define BLOCK_SIZE (65536)
	BYTE *Buffer=(BYTE *)DCMalloc32(BLOCK_SIZE*3);
	if (!Buffer)
	{
		CloseHandle(f);
		return FALSE;
	}
	BYTE *Dst=(BYTE *)*Data;
	int PixelsToRead=*Width * *Height;

	while (PixelsToRead)
	{
		// Get pixel count for this loop iteration and adjust PixelsToRead.
		int Count=(PixelsToRead>=BLOCK_SIZE) ? BLOCK_SIZE : PixelsToRead;
		PixelsToRead-=Count;

		// Read a block of data.
		if (!ReadFile(f,Buffer,Count*3,&BytesRead,NULL))
		{
			DC_ERROR(("Error reading from file %s.\n",FileName));
			DCFree(*Data);
			CloseHandle(f);
			return FALSE;
		}
		// Convert 24 bit data to 32 bit.
		for (BYTE *Src=Buffer;Count;Count--)
		{
			// Read source components.
			Dst[0]=Src[0];
			Dst[1]=Src[1];
			Dst[2]=Src[2];
			Dst[3]=0xFF;
			Src+=3;
			Dst+=4;
		}
	}
	DCFree32(Buffer);
#undef BLOCK_SIZE

	// File is read so close and return.
	CloseHandle(f);
	return TRUE;
}

// Sees if a file exists by trying the open it for reading.
BOOL DoesFileExist(FileDirectory Dir, TCHAR *FileName)
{
	// Figure out path name.
	TCHAR Name[0x200];
	lstrcpy(Name,DirectoryNames[Dir]);
	lstrcat(Name,TEXT("\\"));
	lstrcat(Name,FileName);

	// Open input file.
	HANDLE f;
	f=CreateFile(Name,
				 GENERIC_READ,
				 FILE_SHARE_READ,
				 NULL,
				 OPEN_EXISTING,
				 FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
				 NULL);
	if (f==INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	CloseHandle(f);
	return TRUE;
}

// Gets file length.
DWORD GetFileSize(FileDirectory Dir, TCHAR *FileName)
{
	// Figure out path name.
	TCHAR Name[0x200];
	lstrcpy(Name,DirectoryNames[Dir]);
	lstrcat(Name,TEXT("\\"));
	lstrcat(Name,FileName);

	// Open input file.
	HANDLE f;
	f=CreateFile(Name,
				 GENERIC_READ,
				 FILE_SHARE_READ,
				 NULL,
				 OPEN_EXISTING,
				 FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
				 NULL);
	if (f==INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	// Get file size.
	DWORD Size=GetFileSize(f,NULL);

	CloseHandle(f);
	
	return Size;
}

// Loads a string resource, allocates a buffer and returns the string in it.
TCHAR *LoadTextString(int StringId)
{
	TCHAR Buffer[1024];
    int SLen;
	TCHAR *Ret;

	// Load string.
	SLen=LoadString(gHInstance, StringId, Buffer, 1024);
	// Allocate memory.
	Ret=(TCHAR *)DCMalloc((SLen+1)*sizeof(TCHAR));
	if (!Ret)
		return TEXT("ERROR: Couldn't load string.\n");
	// Copy string.
	DCCopyMemory(Ret,Buffer,SLen*sizeof(TCHAR));
	Ret[SLen]=0;

	// return string.
	return Ret;
}

// Searches the specified directory for matching filenames.
void EnumFileNames(FileDirectory Dir, TCHAR *FileName, BOOL (*Callback)(TCHAR *, void *),void *User)
{
	// Figure out path name.
	TCHAR Path[0x200];
	lstrcpy(Path,DirectoryNames[Dir]);
	lstrcat(Path,TEXT("\\"));
	lstrcat(Path,FileName);

	// Find the first file.
	WIN32_FIND_DATA FD;
	HANDLE FindHandle=FindFirstFile(Path,&FD);
	if (!FindHandle)
		return;

	// Find the rest of the files.
	for (;;)
	{
		// Call the callback function.
		if (!Callback(FD.cFileName,User))
			break;

		// Get next file.
		if (!FindNextFile(FindHandle,&FD))
			break;
	}

	// Close the find handle.
	FindClose(FindHandle);
}	

// Allocates memory and reads the specified file into memory.
void *ReadFileIntoMemory(FileDirectory Dir, TCHAR *FileName, DWORD *RetFileSize)
{
	// Figure out path name.
	TCHAR Name[0x200];
	lstrcpy(Name,DirectoryNames[Dir]);
	lstrcat(Name,TEXT("\\"));
	lstrcat(Name,FileName);
	
	// Open input file.
	HANDLE f;
	f=CreateFile(Name,
				 GENERIC_READ,
				 FILE_SHARE_READ,
				 NULL,
				 OPEN_EXISTING,
				 FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
				 NULL);
	if (f==INVALID_HANDLE_VALUE)
	{
		return NULL;
	}

	// Get file size.
	DWORD FileSize=GetFileSize(f,NULL);

	// Allocate memory.
	void *Buffer=DCMalloc(FileSize);
	if (!Buffer)
	{
		DC_ERROR(("Could allocate memory for %s.\n",
				  FileName));
		CloseHandle(f);
		return NULL;
	}

	// Allocate a 32 byte aligned buffer to read into.
	// This is required for best performance on Dreamcast.
	void *LocalBuffer=DCMalloc32(FileSize);
	if (!LocalBuffer)
	{
		DC_ERROR(("Could allocate local memory for %s.\n",
				  FileName));
		DCFree(Buffer);
		CloseHandle(f);
		return NULL;
	}

	// Read file data.
	DWORD BytesRead;
	if (!ReadFile(f,LocalBuffer,FileSize,&BytesRead,NULL))
	{
		DC_ERROR(("Error reading from file %s.\n",FileName));
		DCFree32(LocalBuffer);
		DCFree(Buffer);
		CloseHandle(f);
		return FALSE;
	}

	// Copy from local buffer.
	DCCopyMemory(Buffer,LocalBuffer,FileSize);

	// Free local buffer.
	DCFree32(LocalBuffer);

	// Close file.
	CloseHandle(f);

	// Set file size and return.
	if (RetFileSize)
		*RetFileSize=FileSize;
	return Buffer;
}

#ifdef DREAMCAST // Not necessary for Dreamcast.
void WriteImageFile(TCHAR *FileName, int Width, int Height, BOOL Alpha, DWORD *Data, TCHAR *TargetDir)
{
}

HANDLE OpenFileForWrite(TCHAR *FileName, TCHAR *TargetDir)
{
	return NULL;
}

void WriteToFile(HANDLE File, void *Data, int Size)
{
}

void CloseOpenFile(HANDLE File)
{
}
#else // DREAMCAST

// Writes an image file to disk.
void WriteImageFile(TCHAR *FileName, int Width, int Height, BOOL Alpha, DWORD *Data, TCHAR *TargetDir)
{
	// Read file headers.
	BITMAPFILEHEADER FileHeader;
	BITMAPINFOHEADER InfoHeader;
	TCHAR Name[0x200];
	HANDLE f;
	DWORD BytesRead;

	// Read file headers from a file we know exists.
	lstrcpy(Name,DirectoryNames[IMAGE_DIRECTORY]);
	lstrcat(Name,TEXT("\\"));
	lstrcat(Name,TEXT("IntroPC"));
	lstrcat(Name,TEXT(".bmp"));

	// Open input file.
	f=CreateFile(Name,
				 GENERIC_READ,
				 FILE_SHARE_READ,
				 NULL,
				 OPEN_EXISTING,
				 FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
				 NULL);
	if (f==INVALID_HANDLE_VALUE)
	{
		return;
	}
	
	// Read file headers.
	if (!ReadFile(f,&FileHeader,sizeof(BITMAPFILEHEADER),&BytesRead,NULL) ||
		!ReadFile(f,&InfoHeader,sizeof(BITMAPINFOHEADER),&BytesRead,NULL))
	{
		DC_ERROR(("Error reading from file %s.\n",FileName));
		CloseHandle(f);
		return;
	}

	// Set stuff we need to in headers.
	InfoHeader.biWidth=Width;
	InfoHeader.biHeight=Height;
	FileHeader.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);

	// Set target dir to default if not specified.
	if (!TargetDir)
		TargetDir=DirectoryNames[IMAGE_DIRECTORY];

	// Make dest filename.
	lstrcpy(Name,TargetDir);
	lstrcat(Name,TEXT("\\"));
	lstrcat(Name,FileName);
	lstrcat(Name,TEXT(".bmp"));

	// Open output file.
	f=CreateFile(Name,
				 GENERIC_WRITE,
				 0,
				 NULL,
				 CREATE_ALWAYS,
				 FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
				 NULL);
	if (f==INVALID_HANDLE_VALUE)
	{
		return;
	}
	
	// Write file headers.
	DWORD BytesWritten;
	WriteFile(f,&FileHeader,sizeof(BITMAPFILEHEADER),&BytesWritten,NULL);
	WriteFile(f,&InfoHeader,sizeof(BITMAPINFOHEADER),&BytesWritten,NULL);

	// Write data in blocks.
#define BLOCK_SIZE 512
	BYTE Buffer[BLOCK_SIZE*3];
	BYTE *Src=(BYTE *)Data;
	int PixelsToWrite=Width * Height;

	while (PixelsToWrite)
	{
		// Get pixel count for this loop iteration and adjust PixelsToRead.
		int Count=(PixelsToWrite>=BLOCK_SIZE) ? BLOCK_SIZE : PixelsToWrite;
		int CountSave=Count;
		PixelsToWrite-=Count;

		// Convert 24 bit data to 32 bit.
		for (BYTE *Dst=Buffer;Count;Count--)
		{
			// Read source components.
			Dst[0]=Src[0];
			Dst[1]=Src[1];
			Dst[2]=Src[2];
			Dst+=3;
			Src+=4;
		}
		// Read a block of data.
		WriteFile(f,Buffer,CountSave*3,&BytesWritten,NULL);
	}
#undef BLOCK_SIZE

	// File is written so close and return.
	CloseHandle(f);
	return;
}

HANDLE OpenFileForWrite(TCHAR *FileName, TCHAR *TargetDir)
{
	TCHAR Name[0x200];
	HANDLE f;

	// Make dest filename.
	lstrcpy(Name,TargetDir ? TargetDir : TEXT("."));
	lstrcat(Name,TEXT("\\"));
	lstrcat(Name,FileName);

	// Open output file.
	f=CreateFile(Name,
				 GENERIC_WRITE,
				 0,
				 NULL,
				 CREATE_ALWAYS,
				 FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
				 NULL);
	if (f==INVALID_HANDLE_VALUE)
	{
		return NULL;
	}
	return f;
}

void WriteToFile(HANDLE File, void *Data, int Size)
{
	DWORD BytesWritten;
	WriteFile(File,Data,Size,&BytesWritten,NULL);
}

void CloseOpenFile(HANDLE File)
{
	// File is written so close and return.
	CloseHandle(File);
}

#endif // DREAMCAST