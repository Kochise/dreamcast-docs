
#include <kos.h>
#include <dc\sound\sound.h>
#include <stdio.h>
#include <string.h>
#include "ads.h"
#include "aica_cmd_iface.h"


/*
 * some good values for block size and count
 */
#define BLOCK_SIZE  8192
#define BLOCK_COUNT 20

/*
 * ads wave data format
 */
#define ADS_FORMAT_PCM_BIG		 0
#define ADS_FORMAT_PCM_LITTLE	 1
#define ADS_FORMAT_ADPCM		16

/* Global Header info */
static unsigned int SampleRate;
static unsigned int Channels;
static int sfx_lastchan = 2;
static unsigned int Format;
typedef struct
{
	uint32  Data;
	uint8 * pData;
	uint32  pos;
} SoundChunk;

/*
 * module level variables
 */
static SoundChunk       waveBlocks[BLOCK_COUNT];
static volatile int     waveFreeBlockCount;
static int              waveCurrentBlock;

static void allocateBlocks(int size, int count)
{
    int i;
    for(i = 0; i < count; i++)
	{
        waveBlocks[i].Data = snd_mem_malloc(size);
		waveBlocks[i].pData = (uint8 *)malloc(size);
        waveBlocks[i].pos  = 0;  
    } 
   
}

static void PlaySoundChunk(int idx)
{
	int i;
	uint8 * p;
	AICA_CMDSTR_CHANNEL(tmp, cmd, chan);
	
	 
	if(Channels-1) // stereo
	{
		p=waveBlocks[idx].pData;
		
		for(i=0;i<8;i++)
		{
			
			spu_memload(waveBlocks[idx].Data+(i*512), p,512);
			p=p+512;
			spu_memload(waveBlocks[idx].Data+4096+(i*512), p,512);
			p=p+512;
		}
		spu_memload(waveBlocks[idx].Data,waveBlocks[idx].pData,BLOCK_SIZE);
		// Play Left sample
		cmd->cmd = AICA_CMD_CHAN;
		cmd->timestamp = 0;
		cmd->size = AICA_CMDSTR_CHANNEL_SIZE;
		cmd->cmd_id = sfx_lastchan;
		chan->cmd = AICA_CH_CMD_START;
		chan->base = waveBlocks[idx].Data;
		chan->type = AICA_SM_16BIT;
		chan->length = BLOCK_SIZE/4;
		chan->loop = 0;
		chan->loopstart = 0;
		chan->loopend = chan->length;
		chan->freq = SampleRate;
		chan->vol = 1000;
		chan->pan = 0;

		snd_sh4_to_aica_stop();
		snd_sh4_to_aica(tmp, cmd->size);

		sfx_lastchan++;
		if (sfx_lastchan >= 64)
			sfx_lastchan = 2;
		
		// Play Right sample
		cmd->cmd_id = sfx_lastchan;
		chan->base = waveBlocks[idx].Data + BLOCK_SIZE/4;
		chan->pan = 255;
		snd_sh4_to_aica(tmp, cmd->size);
		snd_sh4_to_aica_start();
		
		sfx_lastchan++;
		if (sfx_lastchan >= 64)
			sfx_lastchan = 2;
	}
	else // mono
	{
		//snd_sh4_to_aica_stop();
		spu_memload(waveBlocks[idx].Data,waveBlocks[idx].pData,BLOCK_SIZE);
		cmd->cmd = AICA_CMD_CHAN;
		cmd->timestamp = 0;
		cmd->size = AICA_CMDSTR_CHANNEL_SIZE;
		cmd->cmd_id = sfx_lastchan;
		chan->cmd = AICA_CH_CMD_START;
		chan->base = waveBlocks[idx].Data;
		chan->type = AICA_SM_16BIT;
		chan->length = BLOCK_SIZE/2;
		chan->loop = 0;
		chan->loopstart = 0;
		chan->loopend = chan->length;
		chan->freq = SampleRate;
		chan->vol = 1000;
		chan->pan = 127;
		snd_sh4_to_aica(tmp, cmd->size);
	
		sfx_lastchan++;
		if (sfx_lastchan >= 64)
			sfx_lastchan = 2;
	}
	

}


int ADS_Open(unsigned char * _adsHeader)
{
    unsigned int * pval;

    if(strncmp(_adsHeader,"SShd",4)!=0) /* not an ads stream */
		return 0;

	/* check ADS format ... */
	Format =*(unsigned int *)( _adsHeader + 8) ;
	
	if(Format!= ADS_FORMAT_PCM_LITTLE)
		return 0;

    /*
     * initialise the module variables
     */ 
	snd_init();
    allocateBlocks(BLOCK_SIZE, BLOCK_COUNT);
    waveFreeBlockCount = BLOCK_COUNT;
    waveCurrentBlock   = 0;
	sfx_lastchan = 2;
    
 
    /*
     * set up the Global setting.
     */
	
    SampleRate		= *(unsigned int *)(_adsHeader + 12);  /* sample rate */
    Channels       =  *(unsigned int *)(_adsHeader + 16);  /* channels    */

	printf("ADS Plugin init : %dHz %s %s\n",SampleRate,(Channels-1)? "stereo" : "mono",(Format==1)? "PCM" : "ADPCM");
 
	return 1;
    
}

void ADS_Close()
{
    int i;
    /*
     * unload any blocks 
     */
    for(i = 0; i < BLOCK_COUNT; i++) 
	{
		snd_mem_free(waveBlocks[i].Data);
		free(waveBlocks[i].pData);
	}
		
    
	snd_shutdown();	
    
    
}

void ADS_Write(unsigned char * data, int size)
{
    SoundChunk* current;
    int remain;

    current = &waveBlocks[waveCurrentBlock];
  
    while(size > 0)
	{
 
        if(size < (int)(BLOCK_SIZE - current->pos)) 
		{
			memcpy(current->pData + current->pos, data, size);
            current->pos += size;
            break;
        }
		

        remain = BLOCK_SIZE - current->pos;
		memcpy(current->pData + current->pos, data, remain);
        size -= remain;
        data += remain;

		PlaySoundChunk(waveCurrentBlock);

        /*
         * point to the next block
         */
        waveCurrentBlock++;
        waveCurrentBlock %= BLOCK_COUNT;

        current = &waveBlocks[waveCurrentBlock];
        current->pos = 0;
	
    }
	
}


