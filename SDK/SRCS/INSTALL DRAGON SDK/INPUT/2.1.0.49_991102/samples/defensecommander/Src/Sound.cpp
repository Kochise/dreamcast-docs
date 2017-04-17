/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    Sound.cpp

Abstract:

    Sound code.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCSound.h"
#include <DSound.h>
#include <string.h> // Need regular string functions for processing WAV files.

struct SoundListItem
{
	SoundListItem *Next;
	LPDIRECTSOUNDBUFFER DSBuffer;
	int SoundID;
	TCHAR Name[1];
};

static LPDIRECTSOUND lpDirectSound; 
static SoundListItem *SoundList=NULL;
static int CurrentSoundID=1;

#define MAX_TMP_SOUNDS 32
static LPDIRECTSOUNDBUFFER TmpSounds[MAX_TMP_SOUNDS];
static int LastTmpSound=0;

WORD GetWord(BYTE *Buffer)
{
	return ((WORD)Buffer[1]<<8) | (WORD)Buffer[0];
}

DWORD GetDword(BYTE *Buffer)
{
	return ((DWORD)Buffer[3]<<24) | ((DWORD)Buffer[2]<<16) | ((DWORD)Buffer[1]<<8) | (DWORD)Buffer[0];
}

BYTE *GetChunk(char *Name, BYTE *Buffer, DWORD Size)
{
	for (DWORD Offset=0;Offset<Size;)
	{
		int ChunkLen=GetDword(Buffer+Offset+4);
		if (ChunkLen<0)
			break;
		
		if (strncmp((char *)Buffer+Offset,Name,4)==0)
			return Buffer+Offset+8;

		Offset+=8 + ((ChunkLen+1) & ~0x01); // Chunks always WORD aligned.
	}
	// Got to end of file so couldn't find chunk.
	return NULL;
}

LPDIRECTSOUNDBUFFER CreateBuffer(DWORD SamplesPerSec, DWORD BytesPerSample, DWORD NumSamples) 
{ 
    PCMWAVEFORMAT pcmwf; 
    DSBUFFERDESC dsbdesc; 
    
	// Set up wave format structure. 
    memset(&pcmwf, 0, sizeof(PCMWAVEFORMAT)); 
    pcmwf.wf.wFormatTag = WAVE_FORMAT_PCM; 
    pcmwf.wf.nChannels = 1; 
    pcmwf.wf.nSamplesPerSec = SamplesPerSec; 
    pcmwf.wf.nBlockAlign = (WORD)BytesPerSample; 
    pcmwf.wf.nAvgBytesPerSec = SamplesPerSec * BytesPerSample; 
    pcmwf.wBitsPerSample = (WORD)BytesPerSample*8;

    // Set up DSBUFFERDESC structure. 
    memset(&dsbdesc, 0, sizeof(DSBUFFERDESC)); // Zero it out. 
    dsbdesc.dwSize = sizeof(DSBUFFERDESC); 
    // Need default controls (pan, volume, frequency). 
    dsbdesc.dwFlags = DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME; 
    // 3-second buffer 
    dsbdesc.dwBufferBytes = (NumSamples*BytesPerSample + 0x1F) & ~0x1F; // Keep blocks multiple of 32 bytes.
    dsbdesc.lpwfxFormat = (LPWAVEFORMATEX)&pcmwf; 
    // Create buffer. 
	LPDIRECTSOUNDBUFFER lpDSB;
    if (SUCCEEDED(lpDirectSound->CreateSoundBuffer(&dsbdesc, &lpDSB, NULL)))
		return lpDSB;
	else
		return NULL;
}

// Callback which gets sound names then loads the sounds.
static BOOL LoadSoundCallback(TCHAR *FileName, void *User)
{
	// Read the file into memory.
	DWORD FileSize;
	BYTE *FileBuffer=(BYTE *)ReadFileIntoMemory(SOUND_DIRECTORY,FileName,&FileSize);
	if (!FileBuffer)
		return TRUE;

	// Get file information from wave format.
	// Wave files are in a bunch of chunks.
	// Get RIFF chunk so we can make sure its a WAVE file.
	BYTE *RiffChunk=GetChunk("RIFF",FileBuffer,FileSize);
	if (!RiffChunk || strncmp((char *)RiffChunk,"WAVE",4)!=0)
	{
		DC_WARNING(("WAV file missing RIFF/WAV chunk.\n"));
		DCFree(FileBuffer);
		return TRUE;
	}
	DWORD RiffOffset=RiffChunk-FileBuffer+4;

	// Get format chunk.
	BYTE *FmtChunk=GetChunk("fmt ",FileBuffer + RiffOffset,FileSize - RiffOffset);
	if (!FmtChunk)
	{
		DC_WARNING(("WAV file missing fmt FmtChunk.\n"));
		DCFree(FileBuffer);
		return TRUE;
	}
	if (GetWord(FmtChunk)!=1 || GetWord(FmtChunk+2)!=1) // Check format.
	{
		DC_WARNING(("WAV file is not in PCM format or is not single channel.\n"));
		DCFree(FileBuffer);
		return TRUE;
	}
	DWORD SamplesPerSec=GetDword(FmtChunk+4);
	DWORD BytesPerSample=GetWord(FmtChunk+14)/8;
	DWORD FmtOffset=FmtChunk-FileBuffer+16;

	// Find data offset and length.
	BYTE *DataChunk=GetChunk("data",FileBuffer + FmtOffset,FileSize - FmtOffset);
	if (!DataChunk)
	{
		DC_WARNING(("WAV file missing data chunk.\n"));
		DCFree(FileBuffer);
		return TRUE;
	}
	DWORD NumSamples=GetDword(DataChunk-4) / BytesPerSample; // Num samples based on size of chunk.

	// Have all the info about the sample now, just need to load it.
	// Create a secondary DirectSound buffer.
	LPDIRECTSOUNDBUFFER DSBuffer=CreateBuffer(SamplesPerSec,BytesPerSample,NumSamples);
	if (!DSBuffer)
	{
		DC_WARNING(("Failed to create DirectSound buffer for sound.\n"));
		DCFree(FileBuffer);
		return TRUE;
	}

	// Write sound data into buffer.
	LPVOID lpvAudioPtr1, lpvAudioPtr2;
	DWORD  dwAudioBytes1, dwAudioBytes2;
	if (FAILED(DSBuffer->Lock(0,NumSamples*BytesPerSample,
							  &lpvAudioPtr1,&dwAudioBytes1,
							  &lpvAudioPtr2,&dwAudioBytes2,
							  DSBLOCK_ENTIREBUFFER)))
	{
		DC_WARNING(("Failed to lock DirectSound buffer for sound.\n"));
		DSBuffer->Release();
		DCFree(FileBuffer);
		return TRUE;
	}

	// Copy audio data.
	DWORD *Src,*Dst;
	DWORD Count;
	DWORD SrcCount=NumSamples*BytesPerSample/4;
	for (Src=(DWORD *)DataChunk,Dst=(DWORD *)lpvAudioPtr1,Count=dwAudioBytes1/4;
		 Count && SrcCount;
		 Count--,SrcCount--,Src++,Dst++)
		*Dst=*Src;
	for (;Count;Count--,Dst++) // Pad any leftovers with zeros.
		*Dst=0;
	for (Dst=(DWORD *)lpvAudioPtr2,Count=dwAudioBytes2/4;
		 Count && SrcCount;
		 Count--,SrcCount--,Src++,Dst++)
		*Dst=*Src;
	for (;Count;Count--,Dst++) // Pad any leftovers with zeros.
		*Dst=0;

	// Unlock buffer.
	DSBuffer->Unlock(lpvAudioPtr1, dwAudioBytes1, lpvAudioPtr2, dwAudioBytes2);
	// Release WAV file buffer since we don't need it any more.
	DCFree(FileBuffer);
	
	// Allocate list item.
	int Size=sizeof(SoundListItem)+(lstrlen(FileName)-4)*sizeof(TCHAR);
	SoundListItem *Item=(SoundListItem *)DCMalloc(Size);
	if (!Item)
	{
		DSBuffer->Release();
		return TRUE;
	}
	DCZeroMemory(Item,Size);
	
	// Set list item and add to chain.
	Item->Next=SoundList;
	Item->DSBuffer=DSBuffer;
	Item->SoundID=CurrentSoundID++;
	memcpy(Item->Name,FileName,(lstrlen(FileName)-4)*sizeof(TCHAR));
	Item->Name[lstrlen(FileName)-4]=0;

	SoundList=Item;

	return TRUE;
}

BOOL InitSound(HWND Window)
{
	lpDirectSound=NULL;
	SoundList=NULL;
	CurrentSoundID=1;
	
	for (int i=0;i<MAX_TMP_SOUNDS;i++)
		TmpSounds[i]=NULL;
	LastTmpSound=0;
	
	if (SUCCEEDED(DirectSoundCreate(NULL, &lpDirectSound, NULL)))
	{
		if (SUCCEEDED(lpDirectSound->SetCooperativeLevel(Window, DSSCL_EXCLUSIVE)))
		{
			return TRUE;
		}
	}

	// We could return an error here but its probably better to just continue on without sound.
	DC_WARNING(("Failed to initialize DirectSound.\n"));
	return TRUE;
}

void ShutdownSound(HWND Window)
{
	// Unload sounds if not already done so..
	UnloadSounds();

	// Release DirectSound.
	if (lpDirectSound)
	{
		lpDirectSound->SetCooperativeLevel(Window, DSSCL_NORMAL);
		lpDirectSound->Release();
		lpDirectSound=NULL;
	}
}

BOOL LoadSounds()
{
	// Load sounds
	EnumFileNames(SOUND_DIRECTORY,TEXT("*.WAV"),LoadSoundCallback,NULL);
	return TRUE;
}

void UnloadSounds()
{
	// Unload sounds.
	SoundListItem *Item, *Next;
	for (Item=SoundList;Item!=NULL;Item=Next)
	{
		Next=Item->Next;
		Item->DSBuffer->Release();
		DCFree(Item);
	}
	SoundList=NULL;
}

HANDLE GetSoundHandleFromName(TCHAR *Name)
{
	// Walk list looking for name.
	for (SoundListItem *Item=SoundList;Item!=NULL;Item=Item->Next)
	{
		if (lstrcmpi(Name,Item->Name)==0)
			return Item;
	}

	return NULL;
}

void GetAllSoundIDs(void (*Callback)(TCHAR *Name, int SoundID))
{
	for (SoundListItem *Item=SoundList;Item!=NULL;Item=Item->Next)
	{
		Callback(Item->Name,Item->SoundID);
	}
}

int GetSoundID(HANDLE Sound)
{
	return (Sound) ? ((SoundListItem *)Sound)->SoundID : 0;
}

void SetSoundID(HANDLE Sound, int ID)
{
	if (Sound)
		((SoundListItem *)Sound)->SoundID=ID;
}

HANDLE GetSoundHandleFromID(int ID)
{
	// Walk Sound list looking for ID.
	for (SoundListItem *Item=SoundList;Item!=NULL;Item=Item->Next)
	{
		if (Item->SoundID==ID)
			return Item;
	}

	return NULL;
}

static inline DWORD LinearToLog(float Vol)
{
	if (Vol >= 1.0f)
		return 0;

	DWORD Ret=(DWORD)((100.0f*20.0f)*(float)log10(Vol));
	return __max(DSBVOLUME_MIN,Ret);
}

void PlaySound(HANDLE Sound, float Volume)
{
	if (Sound)
	{
		SoundListItem *S=(SoundListItem *)Sound;
		
		DWORD Status;
		if (SUCCEEDED(S->DSBuffer->GetStatus(&Status)))
		{
			if (Status & DSBSTATUS_PLAYING)
			{
				// Allocate a tmp sound.
				for (int Count=MAX_TMP_SOUNDS;Count;Count--)
				{
					if (TmpSounds[LastTmpSound]==NULL)
						break;
					LastTmpSound++;
					if (LastTmpSound>=MAX_TMP_SOUNDS)
						LastTmpSound=0;
				}
				if (Count)
				{
					// Have a tmp sound so make a copy of permanent sound and play it.
					if (SUCCEEDED(lpDirectSound->DuplicateSoundBuffer(S->DSBuffer,
																	  &TmpSounds[LastTmpSound])))
					{
						TmpSounds[LastTmpSound]->SetVolume(LinearToLog(Volume));
						TmpSounds[LastTmpSound]->Play(0,0,0);
					}
				}
			}
			else
			{
				S->DSBuffer->SetVolume(LinearToLog(Volume));
				S->DSBuffer->Play(0,0,0);
			}
		}
	}
}

void TickSound(void)
{
	// Walk tmp sound list, looking for sounds which are no longer playing.
	for (int i=0;i<MAX_TMP_SOUNDS;i++)
	{
		if (TmpSounds[i])
		{
			DWORD Status;
			if (SUCCEEDED(TmpSounds[i]->GetStatus(&Status)))
			{
				if (!(Status & DSBSTATUS_PLAYING))
				{
					TmpSounds[i]->Release();
					TmpSounds[i]=NULL;
				}
			}
		}
	}
}
