/* SlideShow by Sandeep Singh Bisla. Date Last Modified: 28/02/2000.	 *
 * Program: Add PVR files to SlideList.txt and watch them in a Slide 	 *
 * Show with Dissolve & Zoom Transition, also excepts Stride Format PVRs.*
 * Added timer from 1 to 59 seconds, for each image just add a comma and *
 * number between 1 and 59 to get length of pause in seconds. Default is *
 * 2 seconds if nothing entered. Program uses asynchronous ADX streaming *
 * from text file. Added audio support, first line of program has audio  *
 * field, if the user adds any ADX/WAV/AU/AIFF file it will play (ADX	 *
 * files will loop continuously. E.G. audio: sample.adx. If space after	 *
 * "audio:" is left blank then no audio will play!			             */

//#define  	_STRICT_UNION_
//#define  	_CLX2_
//#define 	_CLX_
#include	<shinobi.h>
#include	<kamui2.h>
#include 	<ac.h>
#include 	<sj.h>
#include 	<cri_adxf.h>
#include 	<cri_adxt.h>
#include 	<sn_fcntl.h>   /* LibCross file types. */
#include 	<usrsnasm.h>   /* LibCross I/O routines*/
#include    "bpAcSetup.h" // using new boiler plate code

#define	VBUFFER_SIZE 	8*3*2000
#define MAXTEXTURES         4096        /* Maximum number of textures to be tracked. */
#define MAXSMALLVQ          0           /* Maximum number of small VQ textures. */

/* new macro stuff - use level 4 */
#define		_KM_USE_VERTEX_MACRO_L5_
#include	"kamuix.h"

/* Kamui2 texture work area, must be aligned to 32-byte boundary. */
#ifdef  __MWERKS__
#pragma align (32);
KMDWORD
#else
#ifdef __GNUC__
KMDWORD __attribute__ ((aligned (32)))
#else
#pragma aligndata32(TextureWorkArea)
KMDWORD
#endif /* __GNUC__ */
#endif /* _MWERKS__ */
TextureWorkArea[MAXTEXTURES * 24 / 4 + MAXSMALLVQ * 76 / 4];

#ifdef  __MWERKS__
#pragma align (4);	/* Return Metrowerks alignment to 4-bytes. */
#endif

/********************************************************************************************/
/* Macros                                                                                   */
/********************************************************************************************/
/* Set up 32-byte aligned malloc() / free() memory management. */
//#define Align32Malloc   (*MallocPtr)
//#define Align32Free     (*FreePtr)
/* Align a pointer to the nearest 32-byte aligned memory address. */
//#define Align32Byte(ADR)        ((((long) ADR) + 0x1F) & 0xFFFFFFE0)

/*	The number of maximum channels	*/
#define	MAX_CH			(2)
/*	The number of maximum CD streams playing at the same time	*/
#define	MAX_CDSTM		(4)
/*	Maximum sampling frequency	*/
#define	MAX_SFREQ		(44100)
/*	Work area size of CD stream play	*/
#define	WKSIZE		(ADXT_CALC_WORK(MAX_CH, 1, MAX_CDSTM, MAX_SFREQ))


/***************************************************************************
 *		Variable Declaration
 ***************************************************************************/

KMVERTEX_05             triangle[4];
KMVERTEX_05             triangle2[4];
KMVERTEXBUFFDESC        vertex_buffer;
KMSTRIPCONTEXT          global_sc[2];
KMSTRIPHEAD				global_sh[2];
KMDWORD					FBarea[24576 + 19456];	/*	FBstruct 4096 Entry (= 4096 * 24 / 4)*/
KMSYSTEMCONFIGSTRUCT	SystemConfig;
KMSURFACEDESC			surface1;				/* surface 1 (front buffer) */
KMSURFACEDESC			surface2;				/* surface 2 (back buffer) */
PKMSURFACEDESC 			psurface[2];			/* array of pointers to surfaces */
PKMDWORD    fileptr;

int 	texnum = 0, j = 0, pausenum = 1, region = 0, texpause[2], first = 1;
float   alpha[2] = {0.0, 0.0}, xlen[2], ylen[2], uset[2], vset[2], xset[2] = {0.0, 0.0},
		yset[2] = {0.0, 0.0}, zset[2] = {0.0, 0.0};
static 	Uint32 framecounter = 0;
static char text[256] = {"a"};
SJCK	 	ck, ck2;			// Stream Joint Chunks
ADXF 		adxf, adxf2;		// global ADX File handles
SJ		 	sj;					// Stream Joint
char        *buf;
PKMDWORD   	textureptr;
char work[WKSIZE]; 			   	// Work area
ADXT adxt; 						// ADXT handle


void myVblankFunc(void)
{
	framecounter++;		//this will count vblanks for us, we can use it as a timer
}

/*------------------------------------------------------------*/
/*  Function Name   : PALExtCallbackFunc                      */
/*  Inputs          : pCallbackArguments                      */
/*  Outputs         : None                                    */
/*  Returns         : None                                    */
/*  Globals Used    :                                         */
/*  Description     : PAL mode callback (set the height ratio)*/
/*------------------------------------------------------------*/
VOID STATIC	PALExtCallbackFunc(PVOID pCallbackArguments)
{
PKMPALEXTINFO	pInfo;

	pInfo = (PKMPALEXTINFO)pCallbackArguments;
	pInfo->nPALExtMode = KM_PALEXT_HEIGHT_RATIO_1_133;	   //for PAL extended mode
	return;
}


void	InitStripContext03(	PKMSTRIPCONTEXT pStripContext,PKMSTRIPHEAD	pStripHead, PKMSURFACEDESC tex, int sel)
{
	memset( pStripContext, 0, sizeof(global_sc[sel]));
	pStripContext->nSize = sizeof(KMSTRIPCONTEXT);
	pStripContext->StripControl.nListType		= KM_TRANS_POLYGON;
	pStripContext->StripControl.nUserClipMode  	= KM_USERCLIP_DISABLE;
	pStripContext->StripControl.nShadowMode		= KM_NORMAL_POLYGON;
	pStripContext->StripControl.bOffset			= KM_FALSE;
	pStripContext->StripControl.bGouraud		= KM_TRUE;
	pStripContext->ObjectControl.nDepthCompare	= KM_GREATER;
	pStripContext->ObjectControl.nCullingMode  	= KM_CULLSMALL;
	pStripContext->ObjectControl.bZWriteDisable	= KM_FALSE;
	pStripContext->ObjectControl.bDCalcControl 	= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nSRCBlendingMode	= KM_SRCALPHA;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nDSTBlendingMode	= KM_INVSRCALPHA;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bSRCSelect			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bDSTSelect			= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFogMode			= KM_NOFOG;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bColorClamp		= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bUseAlpha			= KM_TRUE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bIgnoreTextureAlpha= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFlipUV			= KM_NOFLIP;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nClampUV			= KM_NOCLAMP;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nFilterMode		= KM_BILINEAR;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].bSuperSampleMode	= KM_FALSE;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].dwMipmapAdjust		= KM_MIPMAP_D_ADJUST_1_00;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].nTextureShadingMode= KM_MODULATE_ALPHA;
	pStripContext->ImageControl[KM_IMAGE_PARAM1].pTextureSurfaceDesc= tex;
	kmGenerateStripHead05( pStripHead,pStripContext );
}

/**************************************************************
 *      void InitSystem (void)
 *
 *      Initialize display, buffers and clipping
 **************************************************************/

void InitSystem( void )
{
	KMSTATUS    	ks;
	KMPACKEDARGB 	border;
	int				interruptmask;
	Uint32			chainvblank;

  /* Check the cable for NTSC/PAL or VGA.. works properly for SCART. */
    switch (syCblCheck())
	{
        /* Initialize the display device and set the frame buffer based on the video mode. */
        case SYE_CBL_NTSC:  /* U.S./North America NTSC (60Hz) and Brazil PAL-M (60Hz). */
            sbInitSystem (KM_DSPMODE_NTSCNI640x480, KM_DSPBPP_RGB565, 1);
			region = 60;  //for vblank timer, this must be 60 as NTSC supports 60 fps
            break;
        case SYE_CBL_PAL:   /* Europe PAL (50Hz) and Argentina PAL-N (50Hz).*/
            sbInitSystem (KM_DSPMODE_PALNI640x480EXT, KM_DSPBPP_RGB565, 1);
			/*	Change the PAL height ratio */
			kmSetPALEXTCallback(PALExtCallbackFunc,NULL);
			kmSetDisplayMode (KM_DSPMODE_PALNI640x480EXT, KM_DSPBPP_RGB565, TRUE, FALSE);
			// region = 50;  //for vblank timer, this must be 50 as PAL supports 50 fps
			region = 60; // For PAL Extended Mode
            break;
        case SYE_CBL_VGA:   /* Standard VGA. */
            sbInitSystem (KM_DSPMODE_VGA, KM_DSPBPP_RGB565, 1);
			region = 60;
            break;
        default:
            syBtExit();     /* Unknown video type, return to Dreamcast BootROM. */
	}

   	border.dwPacked	=	0x00000000;
	kmSetBorderColor(border);
	psurface[0]			=	&surface1;
	psurface[1]			=	&surface2;
	/* generate vertex buffer */
	interruptmask = get_imask();
	set_imask(15);  /* Disable all interrupts. */
	chainvblank = syChainAddHandler (0x0900, myVblankFunc, 0x58, NULL); //add our vBlank function to the handler
	set_imask(interruptmask);
	SystemConfig.dwSize					=	sizeof(KMSYSTEMCONFIGSTRUCT);
	SystemConfig.flags					=	KM_CONFIGFLAG_ENABLE_CLEAR_FRAMEBUFFER;
	/* for Frame buffer */
	SystemConfig.ppSurfaceDescArray		=	&psurface[0];		/* Array of SurfaceDesc	pointer	*/
	SystemConfig.fb.nNumOfFrameBuffer	=	2;			/* Number Of Frame Buffer		*/
	/* for Texture Memory */
	SystemConfig.nTextureMemorySize		=	0x100000*4;	/* Texture 2MB					*/
	SystemConfig.nNumOfTextureStruct	=	4096;
	SystemConfig.nNumOfSmallVQStruct	=	1024;
	SystemConfig.pTextureWork			=	&FBarea[0];
	/* for Vertex buffer */
	SystemConfig.pBufferDesc			=	&vertex_buffer;	/* pointer to VERTEXBUFFDESC */
	SystemConfig.nNumOfVertexBank		=	2;
 	SystemConfig.pVertexBuffer	=(PKMDWORD)(((KMDWORD)  syMalloc(2*sizeof(KMDWORD)*VBUFFER_SIZE) & 0x0FFFFFFFUL) | 0xA0000000);
	SystemConfig.nVertexBufferSize		=	2*sizeof(KMDWORD)*VBUFFER_SIZE;	/* 2MB						*/
	SystemConfig.nPassDepth			=	1;
	SystemConfig.Pass[0].dwRegionArrayFlag = KM_PASSINFO_AUTOSORT;
	SystemConfig.Pass[0].fBufferSize[0] =  30.0f;
	SystemConfig.Pass[0].fBufferSize[1] =   0.0f;
	SystemConfig.Pass[0].fBufferSize[2] =  70.0f;
	SystemConfig.Pass[0].fBufferSize[3] =   0.0f;
	SystemConfig.Pass[0].fBufferSize[4] =   0.0f;
	kmSetSystemConfiguration( &SystemConfig );
}

void	sound_init()
{
	if ( bpAcSetup(AC_DRIVER_DA, KTFALSE, NULL)==KTFALSE ) // using boiler plate
		for (;;);
	acSetTransferMode(AC_TRANSFER_DMA);					   // DMA transfers supported under R10
}


void QuitSystem(void)
{
 	syFree	(SystemConfig.pVertexBuffer);
	ADXT_Destroy(adxt);	// audio destruction
	ADXF_Close(adxf);	// text file closing
	ADXT_Finish();		// Close ADX library
	sbExitSystem();
}


/*	Load data to memory	usinng GDFS, used only for Audio Driver */
void *LoadFile(char *fname, long *len)
{
	GDFS gdfs;
	long fsize, nsct;
	void *dat=NULL;

	if ( (gdfs=gdFsOpen(fname, NULL)) == NULL ) {
		return NULL;
	}
	gdFsGetFileSize(gdfs, &fsize);
	nsct = (fsize+2047)/2048;
	if ( (dat=syMalloc(nsct*2048)) != NULL ) {
		gdFsRead(gdfs, nsct, dat);
	}
	gdFsClose(gdfs);
	if ( len != NULL )
		*len = fsize;

	return dat;
}

int firstlinelength=0;

char* LoadLine (int val)		//function to load one line of text from text file
{
	int 		i=0, txtlen=0,j=0,k=0,l=0,comma=0,comma2=0,atoitemp=0,wait=0,fileblocks=1;
	char 		sound[20], video[20];

	if (val == 1)
		return text;
	if (first == 1)
	{
	    adxf = ADXF_Open("slidelist.txt", NULL);   			// open our text file, create a handle
		fileblocks = ADXF_GetFsizeSct(adxf);				// find the length in Sectors
		buf = syMalloc( (2048 * fileblocks)+2048);			// allocate memory
		sj = SJRBF_Create(buf,fileblocks * 2048, 2048);		// create a Stream Joint (Ring Buffer)
		memset(text, 0, sizeof(text));
		ADXF_ReadSj32(adxf, 50, sj);						// Start Reading our file into a Stream Joint
		while (ADXF_GetStat(adxf) != ADXF_STAT_READEND);	// Read until we reach the end of the file
	}

	//	Read-out data from Stream Joint
	SJ_GetChunk(sj, SJ_LIN_DATA, 255, &ck);			// Get a 255 byte chunk of stream joint (streaming to application now)

	if ( ck.data[i] == '\n' || ck.data[i] == '\r' || ck.data[i] == '\0' ) //see if the first thing is not a char
	{																	  // if not then start list again (looping)
 		ADXF_Stop(adxf);  //stop the file
		SJ_Reset(sj);	  // reset the Stream Joint
		ADXF_Seek(adxf, 0, ADXF_SEEK_SET);	//Seek to start of text file (0)
		ADXF_ReadSj32(adxf, 50, sj);		//start reading again (streaming)
		while (ADXF_GetStat(adxf) != ADXF_STAT_READEND);
		SJ_GetChunk(sj, SJ_LIN_DATA,firstlinelength, &ck);	//Get the first chunk of the file again but only upto end of line (less functions)
		SJ_PutChunk(sj, SJ_LIN_FREE, &ck);	   // return that chunk as it is just sound and video data
		SJ_GetChunk(sj, SJ_LIN_DATA, 255, &ck);	//Get a normal chunk again so we can go back to normal looping
	}

	//	Search paragraph code
	for (i=0; i<ck.len; i++) //lets search thorugh our 255 byte chunk
	{
		if ( ck.data[i] == '\n' || ck.data[i] == '\r' || ck.data[i] == '\0' ) //stop if we hit the end of the line
			break;
	}
	if ( i == ck.len ) // if we hit the end of the chunk then there was no text
		txtlen = 0;
	else
		txtlen = i+2;  // otherwise our text length is where we are plus 2
					   // (to get over the chars representing end of line etc.)
	if (first == 1)	   // if this is our first line in the text file , the handling is different
	{
	   firstlinelength = txtlen;
	   first = 0;
	   sound[l] = '\0';
   	   for (i=6;i<txtlen;i++)
	   {
	      if ((ck.data[i] != ' ') && (comma2 == 0))
		  {
		  	sound[l] = ck.data[i]; //store the data after the word "audio:"
			l++;
		  }
		  if (ck.data[i] == ',')   //finish storing when we hit the comma
		  {
		   	comma2 = 1;
		  	sound[l-1] = '\0';	   // some clean up
		  	if (sound[0] != '\0')
		  		playADX(sound);	   // Lets Play some audio using the ADX Playback function
		  	l=0;
		   	i++;
		    break;
		  }
	   }

  	   if (comma2 == 1)			   // if we've reached our comma
	   {
	   	 video[l] = '\0';
		 for (j=i+7;j<txtlen;j++)
		 {
		 	if (ck.data[j] != ' ' && ck.data[j] != '\n'&& ck.data[j] != '\r' )
		 	{
		 		video[l] = ck.data[j];					//store all after "video:"
		 		l++;
		 	}
		 }
		 if (ck.data[l] == '\n'|| ck.data[l] == '\r' )  // if this is the end of the line
		 {
		 	video[l-1] = '\0';							// set the char to NULL
		 }
	   }
	   if (video[0] != '\0')	   // we can use this to access a playback video function
	   	 playSofdec(video);
	}

	texpause[pausenum] = 0; //this will be our length of pause, we reset this here

	for (j=0; j < txtlen; j++)	 //now lets loop through the text up to the length of the line
	{
	   if (ck.data[j] != ' ' && comma == 0)  //if we don't hit a blank space or comma flag other than 0
	   	 text[k] = ck.data[j];			  // we store the char to make up our file name
	   else
		 k--;							  //otherwise we go back if it's not what we want
	   if (ck.data[j] == ',')	   			  //if we hit a comma
	   {
	   	 text[k] = '\0';		   			  // make the last char a NULL char so we have our filename in an array
		 comma = 1;	   		  			  // set comma flag to 1
	   }
  	   if (comma == 1)	   					  // do the next bit if our comma flag has been set
	   {
	   	 if (ck.data[j] != ' ' && ck.data[j] != ',')					//if not a blank space or comma
		 {
		 	if (atoi(&ck.data[j]) < 1 || atoi(&ck.data[j]) > 59)	// is the integer stored between 1 and 59?,
				texpause[pausenum] = 0;								// if not make it zero.
			else
			{
			 	texpause[pausenum] = atoi(&ck.data[j]);			//otherwise lets store the pause time
				comma = 2;										//set our comma flag to 2, we're done
				break;
			}
  	  	 }
	   }

	   if (ck.data[j] == '\n'|| ck.data[j] == '\r' )	   				// \n  = new line, \r = carriage return
	   {
	   	 text[k] = '\0';	   	   //make sure anything else after our line is NULL
	   }
  	   k++;
	}
	pausenum ^= 1;					   // swap the number between 0 and 1. So we store 2 values
	text[txtlen] = 0;
	SJ_SplitChunk(&ck, txtlen, &ck ,&ck2); // Split our 255 byte chunk by text length, we want to use ck2 again
	SJ_PutChunk(sj, SJ_LIN_FREE, &ck);	   // ck is the text line we took so we put it on free line so Stream Joint knows we used it
	SJ_UngetChunk(sj, SJ_LIN_DATA, &ck2);  // lets put back the rest of the 255 bytes we didn't use into the Stream Joint
	return text;
}

playADX(char* audio)
{
	/*	Create ADXT handle	*/
	if ( (adxt=ADXT_Create(2, work, WKSIZE)) == NULL )
		return;
	/*	Set recovery mode(BGM:REPLYA,Speech:STOP) 		*/
	ADXT_SetAutoRcvr(adxt, ADXT_RMODE_REPLAY);
	/*	Start to play	*/
	//	ADXT_StartFname(adxt, audio);
	ADXT_SetReloadSct(adxt, 25);		/* set reload interval (in Sectors) */
	ADXT_Pause(adxt, ON);               /* Start Pause to avoid skipping on first load  */
	ADXT_EntryFname(adxt, audio);		// pass our audio file to the Seamless Loop function
	ADXT_SetSeamlessLp(adxt, 1);		// Set our Seamless Loop ON
	ADXT_StartSeamless(adxt);			// Start our loop
}


playSofdec(char* movie)
{
// Not Implemented but here Sofdec implementation code can be added
// this will mean data/audio and video can be streamed

}


int LoadTexture (char* filename, PKMSURFACEDESC texsurfacedesc, int setonce)
{
	long        	fileblocks2=1;
  	KMTEXTURETYPE	ntexturetype;
	int 			filecheck=0, i=0,wait=0;
	float 			ratio=0.0f;

  	if (setonce != 1)
  	{
	  if (!(adxf2 = ADXF_Open(filename, NULL))) 	 	    // use ADX to load a pvr texture, given from LoadLine()
			return 0;
	  fileblocks2 = ADXF_GetFsizeSct(adxf2);			    // find the length in Sectors
	  textureptr = (PKMDWORD)syMalloc((fileblocks2 * 2048)+2048);	// Lets allocate memory to the texture
	  ADXF_ReadNw32(adxf2, 500, textureptr);						//start reading again, max. of 500 sectors
	  while (ADXF_GetStat(adxf2) != ADXF_STAT_READEND);
	  ADXF_Close(adxf2);									// close file once loaded
 	}
    for (;;)
  	{
  		if (textureptr[i]==0x54525650)	//this is the letters "PVRT"
		{
			ntexturetype	= textureptr[i+2]; //lets get the Texture type
			if ((ntexturetype & 0xFF00) == KM_TEXTURE_STRIDE) 			// it the type is a Stride texture
	 		{
			 	xlen[texnum] =GetNearestPow2(textureptr[i+3]&0xffff);	//lets get the width of texture
			 	ylen[texnum] = GetNearestPow2((textureptr[i+3]>>16)&0xffff); //height of texture
			 	// we need to use the function GetNearestPow2 - Get next power of 2
			 	// up from the width or height as STRIDE requires this for display
				uset[texnum] = (textureptr[i+3]&0xffff)/xlen[texnum]; // find the u of the texture
				vset[texnum] = ((textureptr[i+3]>>16)&0xffff)/ylen[texnum]; //find the v of the texture
				break;
			 }
			else
			{
			  	xlen[texnum] =  (textureptr[i+3]&0xffff);	 //3 up from start of pvr file
				ylen[texnum] = ((textureptr[i+3]>>16)&0xffff);
				uset[texnum] = 1.0f;		   	// don't need a u ratio if the texture isn't a stride
				vset[texnum] = 1.0f;		    // don't need a v ratio if the texture isn't a stride
				break;
	   		}
	    }
   i++;
   }

   // Create a texture surface.
   kmCreateTextureSurface (texsurfacedesc, xlen[texnum], ylen[texnum],
   ntexturetype);

   /* Transfer texture from system mem to video mem using a DMA transfer. */
   kmLoadTexture (texsurfacedesc, textureptr + (16 / sizeof(KMDWORD)) + i);

   if ((ntexturetype & 0xFF00) == KM_TEXTURE_STRIDE) //if the texture is Stride
		kmSetStrideWidth(textureptr[i+3]&0xffff);	  //we need to implememnt this function for width
   else
   {
   	 if (xlen[texnum] > 640)				   //this alters the width and height of texture if greater than 640 or 480
	 {
	  	ratio = (xlen[texnum])/(ylen[texnum]);
		xlen[texnum] = 640;
		ylen[texnum] = xlen[texnum]/ratio;
	 }
	 if (ylen[texnum] > 480)
	 {
		ratio = (ylen[texnum])/(xlen[texnum]);
		ylen[texnum] = 480;
		xlen[texnum] = (ylen[texnum])/ratio;
	 }
   }
   xset[texnum] = xlen[texnum]*(uset[texnum]/2);
   yset[texnum] = ylen[texnum]*(vset[texnum]/2);
   texnum ^= 1;
   syFree(textureptr); //free our memory for the texture file
   return 2;
}


int GetNearestPow2( int v )
{
    int bit = 1;
    while( bit < v ) bit <<= 1;
    return bit;
}

int zoomTrans(int select) 		  //our zoom and alha blending transition
{
	int complete[2] = {0,0};

	if (zset[select] <= 0)
	{
		xset[select] = 0;
		yset[select] = 0;
	}

	if (zset[select^1] > 0)
	{
		xset[select^1] -= ((xlen[select^1] * uset[select^1])/20.f)/2;
		yset[select^1] -= ((ylen[select^1] * vset[select^1])/20.f)/2;
		zset[select^1] -= 1.f;
	}

	if (zset[select] < 20)
	{
  		xset[select] += ((xlen[select] * uset[select])/20.f)/2;
  		yset[select] += ((ylen[select] * vset[select])/20.f)/2;
  	 	zset[select] += 1.f;
	}

	if (zset[select] >= 20 && zset[select^1] <= 0)
	{
		zset[select] = 20.f;
		zset[select^1] = 0.f;

		if (alpha[select] >= 1 && alpha[select^1] <= 0)
		{
			alpha[select] = 1;
			alpha[select^1] = 0;
			complete[select] = 1;
		}
	}

	if (alpha[select^1] > 0)
		alpha[select^1] -= 0.05f;

	if (alpha[select] < 1)
		alpha[select] += 0.05f;

	return complete[select];
}

void usr_adx_err_func(void *obj, char *msg)
{
	/*
	 *	This function call when error occur in ADX library.
	 *	Error message is put into 'msg' variable.
	 *	'msg' house R5 register. You can look error message in address of
	 *	R5 register.
	 *	You cannot call Ninja function because this function is called
	 *	from V-Int.
	 *	You must change this to no operation function when you release
	 *	the application.
	 */

	for (;;);	   /*Delete when you release application.	*/
}


int main(void)
{
    KMSTATUS           ks;
	KMSURFACEDESC      texture[2] = {0,0};
	int 			   timeUp[2] = {0,0}, load[2] = {0,0}, complete[2] = {0,0}, select1 = 0, i = 0, loadval=0;
    char               TmpString[40];

	texpause  [0] = 59;
	texpause  [1] = 59;
	framecounter = 0;

	/*	Prepare sound library		*/
   	InitSystem();
	sound_init();
  	ADXT_Init();  //Initilaise ADX library
  /*  Entry ADX error callback function   */
    ADXT_EntryErrFunc(usr_adx_err_func, NULL);

	LoadLine(0); // set up audio/viideo in 1st line of script file

	while(TRUE)
 	{
	if (load[select1] == 0)	   // load a texture
		{
			if (timeUp[select1] == 1) 	// if this is not our first texture then free the memory for the last one
				kmFreeTexture(&texture[select1]);
			if ((loadval = LoadTexture(LoadLine(loadval), &texture[select1], loadval)) == 0) // load our texture based on what is in text file
			   	debug_write (SNASM_STDOUT, "Texture Loading Failed, Check Texture", 38);
			if (texpause[select1] == 0)
				texpause[select1] = 2;
		    sprintf (TmpString, "  Texpause: %d", texpause[select1]);
	    	debug_write (SNASM_STDOUT, TmpString, strlen (TmpString));
			InitStripContext03(&global_sc[select1],&global_sh[select1], &texture[select1], select1);
		   	if (loadval != 1)
				load[select1] = 2;	   		// set our load complete flag
			timeUp[select1] = 1;	 	// set first time texture flag
			ADXT_Pause(adxt, OFF);      // Pause Off, finish loading of first twexture before we play audio
		}

		if (complete[select1] == 1)	   //if transition is complete
		{
			load[select1] = 1;
		    if (framecounter >= (region * texpause[select1])) //set the pause for the image depending what is specified in text file
			{
				complete[select1] = 0;	//reset our flags so we change to a second texture
				select1 ^= 1;
				load[select1] = 0;		//reset our load flags, we can now start loading alternate texture
				load[select1^1] = 1;	//one texture wil be displayed while other loads
			}
		}

		if (load[select1] == 2)		   //if loading has finished
		{
			complete[select1] =  zoomTrans(select1); //do a transition
			framecounter = 0;						 //set the vBlank framecounter to zero
		}

   		/* main loop */
		kmBeginScene(&SystemConfig);
		kmBeginPass(&vertex_buffer);
		/* new macro l3 to set a triangle down */
	  	kmxxGetCurrentPtr(&vertex_buffer);

		for(i=0;i<=1;i++)
		{
			if (alpha[i] > 0.f)
			{
				kmxxStartStrip(&vertex_buffer,&global_sh[i]);

				kmxxSetVertex_5( KM_VERTEXPARAM_NORMAL,
						   (320.0f-xset[i]), (240.0f-yset[i]), zset[i],
							0.0f, 0.0f, alpha[i], 1.0f, 1.f, 1.0f,
							0.0f, 0.0f, 0.0f, 0.0f)

				kmxxSetVertex_5( KM_VERTEXPARAM_NORMAL,
							(320.0f-xset[i]), (240.0f+yset[i]),	zset[i],
							0.0f, vset[i], alpha[i], 1.0f, 1.f, 1.0f,
							0.0f, 0.0f, 0.0f, 0.0f)

				kmxxSetVertex_5( KM_VERTEXPARAM_NORMAL,
							(320.0f+xset[i]), (240.0f-yset[i]),zset[i],
							uset[i], 0.0f, alpha[i], 1.0f, 1.f, 1.0f,
							0.0f, 0.0f, 0.0f, 0.0f)

		  	  	kmxxSetVertex_5( KM_VERTEXPARAM_ENDOFSTRIP,
							(320.0f+xset[i]), (240.0f+yset[i]),zset[i],
							uset[i], vset[i], alpha[i], 1.0f, 1.f, 1.0f,
							0.0f, 0.0f, 0.0f, 0.0f)
			}
		}

		kmxxReleaseCurrentPtr(&vertex_buffer);
  	  	kmEndPass(&vertex_buffer);
	   	/* go away and render */
   	    kmRender(KM_RENDER_FLIP);
   		kmEndScene(&SystemConfig);
		/* must call this straight after flip frame buffer */
 		pdExecPeripheralServer();
   	}

    ks = kmDiscardVertexBuffer(&vertex_buffer);
	kmFreeTexture(&texture[0]);
	kmFreeTexture(&texture[1]);
	kmFreeTexture(psurface[0]);
	kmFreeTexture(psurface[1]);
	QuitSystem();
}