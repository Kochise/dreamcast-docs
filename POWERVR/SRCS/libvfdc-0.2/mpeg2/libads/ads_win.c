#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <string.h>
#include "ads.h"

/*
 * some good values for block size and count
 */
#define BLOCK_SIZE  8192
#define BLOCK_COUNT 20


/*
 * function prototypes
 */ 
static void CALLBACK waveOutProc(HWAVEOUT, UINT, DWORD, DWORD, DWORD);
static WAVEHDR* allocateBlocks(int size, int count);
static void freeBlocks(WAVEHDR* blockArray);
static void writeAudio(HWAVEOUT hWaveOut, LPSTR data, int size);

/*
 * module level variables
 */
static CRITICAL_SECTION waveCriticalSection;
static WAVEHDR*         waveBlocks;
static HWAVEOUT			hWaveOut;				/* Audio device handle */
static volatile int     waveFreeBlockCount;
static WAVEFORMATEX		wfx;
static int              waveCurrentBlock;

int ADS_Open(unsigned char * _adsHeader)
{
    unsigned int * pval;

    if(strncmp(_adsHeader,"SShd",4)!=0) /* not an ads stream */
		return 0;

	/* check ADS format ... */
	pval = _adsHeader + 8 ;
	
	if((*pval)!= ADS_FORMAT_PCM_LITTLE)
		return 0;

    /*
     * initialise the module variables
     */ 
    waveBlocks         = allocateBlocks(BLOCK_SIZE, BLOCK_COUNT);
    waveFreeBlockCount = BLOCK_COUNT;
    waveCurrentBlock   = 0;
    
    InitializeCriticalSection(&waveCriticalSection);

    /*
     * set up the WAVEFORMATEX structure.
     */
	
    wfx.nSamplesPerSec  = *(unsigned int *)(_adsHeader + 12);  /* sample rate */
    wfx.wBitsPerSample  = 16;     /* sample size */
    wfx.nChannels       = *(unsigned int *)(_adsHeader + 16);      /* channels    */
    wfx.cbSize          = 0;      /* size of _extra_ info */
    wfx.wFormatTag      = WAVE_FORMAT_PCM;
    wfx.nBlockAlign     = (wfx.wBitsPerSample * wfx.nChannels) >> 3;
    wfx.nAvgBytesPerSec = wfx.nBlockAlign * wfx.nSamplesPerSec;

    /*
     * try to open the default wave device. WAVE_MAPPER is
     * a constant defined in mmsystem.h, it always points to the
     * default wave device on the system (some people have 2 or
     * more sound cards).
     */
    if(waveOutOpen(
        &hWaveOut, 
        WAVE_MAPPER, 
        &wfx, 
        (DWORD_PTR)waveOutProc, 
        (DWORD_PTR)&waveFreeBlockCount, 
        CALLBACK_FUNCTION
    ) != MMSYSERR_NOERROR) 
	{
        return 0;
    }


	return 1;
    
}

void ADS_Close()
{
    int i;
    /*
     * wait for all blocks to complete
     */
    while(waveFreeBlockCount < BLOCK_COUNT)
        Sleep(10);

    /*
     * unprepare any blocks that are still prepared
     */
    for(i = 0; i < waveFreeBlockCount; i++) 
        if(waveBlocks[i].dwFlags & WHDR_PREPARED)
            waveOutUnprepareHeader(hWaveOut, &waveBlocks[i], sizeof(WAVEHDR));

    
    DeleteCriticalSection(&waveCriticalSection);
    freeBlocks(waveBlocks);
    waveOutClose(hWaveOut);
    
    
}

void ADS_Write(unsigned char * data, int size)
{
    WAVEHDR* current;
    int remain;

    current = &waveBlocks[waveCurrentBlock];
    
    while(size > 0) {
        /* 
         * first make sure the header we're going to use is unprepared
         */
        if(current->dwFlags & WHDR_PREPARED) 
            waveOutUnprepareHeader(hWaveOut, current, sizeof(WAVEHDR));

        if(size < (int)(BLOCK_SIZE - current->dwUser)) {
            memcpy(current->lpData + current->dwUser, data, size);
            current->dwUser += size;
            break;
        }

        remain = BLOCK_SIZE - current->dwUser;
        memcpy(current->lpData + current->dwUser, data, remain);
        size -= remain;
        data += remain;
        current->dwBufferLength = BLOCK_SIZE;
       
        waveOutPrepareHeader(hWaveOut, current, sizeof(WAVEHDR));
        waveOutWrite(hWaveOut, current, sizeof(WAVEHDR));
        
        EnterCriticalSection(&waveCriticalSection);
        waveFreeBlockCount--;
        LeaveCriticalSection(&waveCriticalSection);
        
        /*
         * wait for a block to become free
         */
        while(!waveFreeBlockCount)
            Sleep(10);

        /*
         * point to the next block
         */
        waveCurrentBlock++;
        waveCurrentBlock %= BLOCK_COUNT;

        current = &waveBlocks[waveCurrentBlock];
        current->dwUser = 0;
    }
}

static WAVEHDR* allocateBlocks(int size, int count)
{
    unsigned char* buffer;
    int i;
    WAVEHDR* blocks;
    DWORD totalBufferSize = (size + sizeof(WAVEHDR)) * count;
    
    /*
     * allocate memory for the entire set in one go
     */
    if((buffer = HeapAlloc(
        GetProcessHeap(), 
        HEAP_ZERO_MEMORY, 
        totalBufferSize
    )) == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        ExitProcess(1);
    }

    /*
     * and set up the pointers to each bit
     */
    blocks = (WAVEHDR*)buffer;
    buffer += sizeof(WAVEHDR) * count;
    for(i = 0; i < count; i++) {
        blocks[i].dwBufferLength = size;
        blocks[i].lpData = buffer;
        buffer += size;
    }
    
    return blocks;
}

static void freeBlocks(WAVEHDR* blockArray)
{
    /* 
     * and this is why allocateBlocks works the way it does
     */ 
    HeapFree(GetProcessHeap(), 0, blockArray);
}

static void CALLBACK waveOutProc(
    HWAVEOUT hWaveOut, 
    UINT uMsg, 
    DWORD dwInstance,  
    DWORD dwParam1,    
    DWORD dwParam2     
)
{
    int* freeBlockCounter = (int*)dwInstance;
    /*
     * ignore calls that occur due to openining and closing the
     * device.
     */
    if(uMsg != WOM_DONE)
        return;

    EnterCriticalSection(&waveCriticalSection);
    (*freeBlockCounter)++;
    LeaveCriticalSection(&waveCriticalSection);
}