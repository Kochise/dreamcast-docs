/*****************************************************************************
  Name : KMTexture.c
  Date : August 1998
  Platform : ANSI compatible
 
  * Description : 
  This file is part of the KAMUI TOOLS library (KMTools.lib) used
  with the SDK demos for PowerVR series 2.

  Set of functions used in texturing.
  

  Copyright : 1998 by VideoLogic Limited. All rights reserved.
******************************************************************************/

#include "KMTools.h"
#include "vqcalc.h"

/************
** Defines **
************/

#define MAKE_565(r,g,b)    (unsigned short)(((unsigned short)(r)<<8)&0xF800 | ((unsigned short)(g)<<3)&0x07E0 | ((unsigned short)(b)>>3)&0x001F)
#define MAKE_4444(a,r,g,b) (unsigned short)(((unsigned short)(a)<<8)&0xF000 | ((unsigned short)(r)<<4)&0x0F00 | ((unsigned short)(g)   )&0x00F0 | ((unsigned short)(b)>>4)&0x000F)
#define MAKE_1555(a,r,g,b) (unsigned short)(((unsigned short)(a)<<8)&0x8000 | ((unsigned short)(r)<<7)&0x7C00 | ((unsigned short)(g)<<2)&0x03E0 | ((unsigned short)(b)>>3)&0x001F)
#define MAKE_8888(a,r,g,b) (unsigned int)(((unsigned int)(a))&0x000000FF | ((unsigned int)(r)<<24)&0xFF000000 | ((unsigned int)(g)<<16)&0x00FF0000 | ((unsigned int)(b)<<8)&0x0000FF00)

/*************
** Typedefs ** 
*************/
/* Internal structure type */
typedef struct Pixel32Type_TAG {
	unsigned char Alpha; 
	unsigned char Red;
	unsigned char Green;
	unsigned char Blue;
} Pixel32Type;

/*************
** Globals  ** 
*************/
DWORD Glob_CurrentMipmappingMethod = MIPMAP_2x2;

/******************
** Local functions ** 
*******************/
KMDWORD LoadTextureInVideoMemory(KMSURFACEDESC *pTexSurfaceDesc, unsigned long *pSourceTex, 
				KMINT32 SizeX, KMINT32 SizeY, KMTEXTURETYPE nTextureType);

							
KMDWORD LoadRectangular(KMSURFACEDESC *pTexSurfaceDesc, unsigned short *p16bitsConverted, unsigned char *pSource, unsigned char *pTransSource, 
								KMINT32 SizeX, KMINT32 SizeY, KMTEXTURETYPE nTextureType);
								
KMDWORD LoadTwiddled(KMSURFACEDESC *pTexSurfaceDesc, unsigned short *p16bitsConverted, unsigned char *pSource, unsigned char *pTransSource, 
								KMINT32 SizeX, KMINT32 SizeY, KMTEXTURETYPE nTextureType);
							
KMDWORD LoadTwiddledMipmap(KMSURFACEDESC *pTexSurfaceDesc, const void *MemPtr, unsigned char *pSource, unsigned char *pTransSource,
								 KMINT32 nSourceSize, KMTEXTURETYPE nTextureType);
								 
KMDWORD LoadPalettised(KMSURFACEDESC *pTexSurfaceDesc, unsigned short *p16bitsConverted, unsigned char *pSource, 
						unsigned char *pTransSource, KMINT32 SizeX, KMINT32 SizeY, KMTEXTURETYPE nTextureType);

KMDWORD LoadPalettisedMipmap(KMSURFACEDESC *pTexSurfaceDesc,  unsigned short *MemPtr, unsigned char *pSource, 
								unsigned char *pTransSource, KMINT32 nSourceSize, KMTEXTURETYPE nTextureType);

KMDWORD LoadVQ(KMSURFACEDESC *pTexSurfaceDesc, unsigned short *p16bitsConverted, unsigned char *pSource, 
				unsigned char *pTransSource, KMINT32 nSourceSize, KMTEXTURETYPE nTextureType, int bMipmap);
						
void CreateNextMipmapLevel2x2(unsigned int *pBitmapData32, int nSourceDim, int bTranslucent, unsigned int *pOutputData32);

void CreateNextMipmapLevel4x4(unsigned int *pBitmapData32, int nSourceDim, int bTranslucent, unsigned int *pOutputData32);

unsigned short CalculateBump (unsigned Height, unsigned Height01, unsigned Height10);

void CreatePalettes(void);

BOOL CreateFourierMipmapLevels	(unsigned char *pBitmapData24, unsigned char *pBitmapTransData24,int nSourceDim, 
							   		unsigned int *pOutputData32, int nOrder);
void MirrorExpandBitmap			(float **Red, float **Green, float **Blue, float **Alpha, 
										unsigned char *pBm, unsigned char *pBmTrans, int nSize);
void ApplyLowPassFilter			(float **data, float *speq, DWORD dwSize, float fCutOff, int nOrder);
float **AllocateSquareMatrix	(long nSize);
void FreeSquareMatrix			(float **ppMatrix, long nSize);
float *AllocateVector			(long nSize);
void FreeVector					(float *pVector, long nSize);
void DFT2D						(float data[], unsigned long nn2, unsigned long nn3, int isign);
void RealFFT2D					(float **data, float *speq, unsigned long nn2, unsigned long nn3, int isign);
int fround						(float fValue);

/*****************************************************************************
 TWIDDLE Table
 The new address of a (x.y) pixel is (TwiddledOffset[x] | TwiddledOffset[y]<<1)
 
 How to build this table:
 
 ========================================
 for (unsigned Shift=0; Shift<10; Shift++)
 {
	unsigned BitCompare=(1<<Shift);
				
	if (Position & BitCompare)
	{
		Offset+=BitCompare<<Shift;
	}
 }
 TwiddledOffset[Position] = Offset;
=========================================
******************************************************************************/							
unsigned int TwiddledOffset[1024] = {
     0,      2,      8,     10,     32,     34,     40,     42,    128,    130,    136,    138,    160,    162,    168,    170,    512,    514,    520,    522,    544,    546,    552,    554,    640,    642,    648,    650,    672,    674,    680,    682, 
  2048,   2050,   2056,   2058,   2080,   2082,   2088,   2090,   2176,   2178,   2184,   2186,   2208,   2210,   2216,   2218,   2560,   2562,   2568,   2570,   2592,   2594,   2600,   2602,   2688,   2690,   2696,   2698,   2720,   2722,   2728,   2730, 
  8192,   8194,   8200,   8202,   8224,   8226,   8232,   8234,   8320,   8322,   8328,   8330,   8352,   8354,   8360,   8362,   8704,   8706,   8712,   8714,   8736,   8738,   8744,   8746,   8832,   8834,   8840,   8842,   8864,   8866,   8872,   8874, 
 10240,  10242,  10248,  10250,  10272,  10274,  10280,  10282,  10368,  10370,  10376,  10378,  10400,  10402,  10408,  10410,  10752,  10754,  10760,  10762,  10784,  10786,  10792,  10794,  10880,  10882,  10888,  10890,  10912,  10914,  10920,  10922, 
 32768,  32770,  32776,  32778,  32800,  32802,  32808,  32810,  32896,  32898,  32904,  32906,  32928,  32930,  32936,  32938,  33280,  33282,  33288,  33290,  33312,  33314,  33320,  33322,  33408,  33410,  33416,  33418,  33440,  33442,  33448,  33450, 
 34816,  34818,  34824,  34826,  34848,  34850,  34856,  34858,  34944,  34946,  34952,  34954,  34976,  34978,  34984,  34986,  35328,  35330,  35336,  35338,  35360,  35362,  35368,  35370,  35456,  35458,  35464,  35466,  35488,  35490,  35496,  35498, 
 40960,  40962,  40968,  40970,  40992,  40994,  41000,  41002,  41088,  41090,  41096,  41098,  41120,  41122,  41128,  41130,  41472,  41474,  41480,  41482,  41504,  41506,  41512,  41514,  41600,  41602,  41608,  41610,  41632,  41634,  41640,  41642, 
 43008,  43010,  43016,  43018,  43040,  43042,  43048,  43050,  43136,  43138,  43144,  43146,  43168,  43170,  43176,  43178,  43520,  43522,  43528,  43530,  43552,  43554,  43560,  43562,  43648,  43650,  43656,  43658,  43680,  43682,  43688,  43690, 
131072, 131074, 131080, 131082, 131104, 131106, 131112, 131114, 131200, 131202, 131208, 131210, 131232, 131234, 131240, 131242, 131584, 131586, 131592, 131594, 131616, 131618, 131624, 131626, 131712, 131714, 131720, 131722, 131744, 131746, 131752, 131754, 
133120, 133122, 133128, 133130, 133152, 133154, 133160, 133162, 133248, 133250, 133256, 133258, 133280, 133282, 133288, 133290, 133632, 133634, 133640, 133642, 133664, 133666, 133672, 133674, 133760, 133762, 133768, 133770, 133792, 133794, 133800, 133802, 
139264, 139266, 139272, 139274, 139296, 139298, 139304, 139306, 139392, 139394, 139400, 139402, 139424, 139426, 139432, 139434, 139776, 139778, 139784, 139786, 139808, 139810, 139816, 139818, 139904, 139906, 139912, 139914, 139936, 139938, 139944, 139946, 
141312, 141314, 141320, 141322, 141344, 141346, 141352, 141354, 141440, 141442, 141448, 141450, 141472, 141474, 141480, 141482, 141824, 141826, 141832, 141834, 141856, 141858, 141864, 141866, 141952, 141954, 141960, 141962, 141984, 141986, 141992, 141994, 
163840, 163842, 163848, 163850, 163872, 163874, 163880, 163882, 163968, 163970, 163976, 163978, 164000, 164002, 164008, 164010, 164352, 164354, 164360, 164362, 164384, 164386, 164392, 164394, 164480, 164482, 164488, 164490, 164512, 164514, 164520, 164522, 
165888, 165890, 165896, 165898, 165920, 165922, 165928, 165930, 166016, 166018, 166024, 166026, 166048, 166050, 166056, 166058, 166400, 166402, 166408, 166410, 166432, 166434, 166440, 166442, 166528, 166530, 166536, 166538, 166560, 166562, 166568, 166570, 
172032, 172034, 172040, 172042, 172064, 172066, 172072, 172074, 172160, 172162, 172168, 172170, 172192, 172194, 172200, 172202, 172544, 172546, 172552, 172554, 172576, 172578, 172584, 172586, 172672, 172674, 172680, 172682, 172704, 172706, 172712, 172714, 
174080, 174082, 174088, 174090, 174112, 174114, 174120, 174122, 174208, 174210, 174216, 174218, 174240, 174242, 174248, 174250, 174592, 174594, 174600, 174602, 174624, 174626, 174632, 174634, 174720, 174722, 174728, 174730, 174752, 174754, 174760, 174762, 
524288, 524290, 524296, 524298, 524320, 524322, 524328, 524330, 524416, 524418, 524424, 524426, 524448, 524450, 524456, 524458, 524800, 524802, 524808, 524810, 524832, 524834, 524840, 524842, 524928, 524930, 524936, 524938, 524960, 524962, 524968, 524970, 
526336, 526338, 526344, 526346, 526368, 526370, 526376, 526378, 526464, 526466, 526472, 526474, 526496, 526498, 526504, 526506, 526848, 526850, 526856, 526858, 526880, 526882, 526888, 526890, 526976, 526978, 526984, 526986, 527008, 527010, 527016, 527018, 
532480, 532482, 532488, 532490, 532512, 532514, 532520, 532522, 532608, 532610, 532616, 532618, 532640, 532642, 532648, 532650, 532992, 532994, 533000, 533002, 533024, 533026, 533032, 533034, 533120, 533122, 533128, 533130, 533152, 533154, 533160, 533162, 
534528, 534530, 534536, 534538, 534560, 534562, 534568, 534570, 534656, 534658, 534664, 534666, 534688, 534690, 534696, 534698, 535040, 535042, 535048, 535050, 535072, 535074, 535080, 535082, 535168, 535170, 535176, 535178, 535200, 535202, 535208, 535210, 
557056, 557058, 557064, 557066, 557088, 557090, 557096, 557098, 557184, 557186, 557192, 557194, 557216, 557218, 557224, 557226, 557568, 557570, 557576, 557578, 557600, 557602, 557608, 557610, 557696, 557698, 557704, 557706, 557728, 557730, 557736, 557738, 
559104, 559106, 559112, 559114, 559136, 559138, 559144, 559146, 559232, 559234, 559240, 559242, 559264, 559266, 559272, 559274, 559616, 559618, 559624, 559626, 559648, 559650, 559656, 559658, 559744, 559746, 559752, 559754, 559776, 559778, 559784, 559786, 
565248, 565250, 565256, 565258, 565280, 565282, 565288, 565290, 565376, 565378, 565384, 565386, 565408, 565410, 565416, 565418, 565760, 565762, 565768, 565770, 565792, 565794, 565800, 565802, 565888, 565890, 565896, 565898, 565920, 565922, 565928, 565930, 
567296, 567298, 567304, 567306, 567328, 567330, 567336, 567338, 567424, 567426, 567432, 567434, 567456, 567458, 567464, 567466, 567808, 567810, 567816, 567818, 567840, 567842, 567848, 567850, 567936, 567938, 567944, 567946, 567968, 567970, 567976, 567978, 
655360, 655362, 655368, 655370, 655392, 655394, 655400, 655402, 655488, 655490, 655496, 655498, 655520, 655522, 655528, 655530, 655872, 655874, 655880, 655882, 655904, 655906, 655912, 655914, 656000, 656002, 656008, 656010, 656032, 656034, 656040, 656042, 
657408, 657410, 657416, 657418, 657440, 657442, 657448, 657450, 657536, 657538, 657544, 657546, 657568, 657570, 657576, 657578, 657920, 657922, 657928, 657930, 657952, 657954, 657960, 657962, 658048, 658050, 658056, 658058, 658080, 658082, 658088, 658090, 
663552, 663554, 663560, 663562, 663584, 663586, 663592, 663594, 663680, 663682, 663688, 663690, 663712, 663714, 663720, 663722, 664064, 664066, 664072, 664074, 664096, 664098, 664104, 664106, 664192, 664194, 664200, 664202, 664224, 664226, 664232, 664234, 
665600, 665602, 665608, 665610, 665632, 665634, 665640, 665642, 665728, 665730, 665736, 665738, 665760, 665762, 665768, 665770, 666112, 666114, 666120, 666122, 666144, 666146, 666152, 666154, 666240, 666242, 666248, 666250, 666272, 666274, 666280, 666282, 
688128, 688130, 688136, 688138, 688160, 688162, 688168, 688170, 688256, 688258, 688264, 688266, 688288, 688290, 688296, 688298, 688640, 688642, 688648, 688650, 688672, 688674, 688680, 688682, 688768, 688770, 688776, 688778, 688800, 688802, 688808, 688810, 
690176, 690178, 690184, 690186, 690208, 690210, 690216, 690218, 690304, 690306, 690312, 690314, 690336, 690338, 690344, 690346, 690688, 690690, 690696, 690698, 690720, 690722, 690728, 690730, 690816, 690818, 690824, 690826, 690848, 690850, 690856, 690858, 
696320, 696322, 696328, 696330, 696352, 696354, 696360, 696362, 696448, 696450, 696456, 696458, 696480, 696482, 696488, 696490, 696832, 696834, 696840, 696842, 696864, 696866, 696872, 696874, 696960, 696962, 696968, 696970, 696992, 696994, 697000, 697002, 
698368, 698370, 698376, 698378, 698400, 698402, 698408, 698410, 698496, 698498, 698504, 698506, 698528, 698530, 698536, 698538, 698880, 698882, 698888, 698890, 698912, 698914, 698920, 698922, 699008, 699010, 699016, 699018, 699040, 699042, 699048, 699050 
};

/****************************************************************************
 *  Function Name   : KMTextureSetMipmapMethod                            
 *  Inputs          : None                                  
 *  Outputs         : None                                         
 *  Returns         : None                          
 *  Globals Used    : None                                      
 *  Description     : 
 *****************************************************************************/
void KMTextureSetMipmapMethod(DWORD dwMM_Method)
{
	Glob_CurrentMipmappingMethod = dwMM_Method;
}
/****************************************************************************
 *  Function Name   : KMTextureConvertAndLoad                            
 *  Inputs          : pTextureSurfaceDesc, MemPtr, pSource, pTransSource,
 *                     SizeX, SizeY, nTextureType,                                  
 *  Outputs         : None                                         
 *  Returns         : ErrorCode                          
 *  Globals Used    : None                                      
 *  Description     : This function converts from a 888 format to a 16 bits
 *                    format and loads it in memory       
 *  Notes           : MemPtr is a pointer to a zone of free memory, and it's used
 *                    for calculations and temporal data storage.
 *                    Once the texture is uploaded into video memory all this data
 *                    is not needed anymore, so this zone of memory can be reused.
 *****************************************************************************/
KMDWORD KMTextureConvertAndLoad(KMSURFACEDESC *pTexSurfaceDesc, unsigned char *pSource, 
						unsigned char *pTransSource, int SizeX, int SizeY, KMTEXTURETYPE nTextureType)
{
unsigned short 	*p16bitsConverted;
KMDWORD 		ErrorCode;
int    			nFormatType;

	p16bitsConverted = (unsigned short *)syMalloc(SizeX*SizeY*sizeof(short) * 2);

	nFormatType = (int)(nTextureType &0x0000FF00);
	
	switch (nFormatType)
	{
		case KM_TEXTURE_RECTANGLE:
		case KM_TEXTURE_STRIDE:
			 ErrorCode = LoadRectangular(pTexSurfaceDesc, p16bitsConverted, pSource, pTransSource, SizeX, SizeY, nTextureType);
			 break;
	
		case KM_TEXTURE_TWIDDLED_RECTANGLE:
		case KM_TEXTURE_TWIDDLED:
	 		 ErrorCode =  LoadTwiddled(pTexSurfaceDesc, p16bitsConverted, pSource, pTransSource, SizeX, SizeY, nTextureType);
			 break;
		
		case KM_TEXTURE_TWIDDLED_MM:
			 ErrorCode =  LoadTwiddledMipmap(pTexSurfaceDesc, p16bitsConverted, pSource, pTransSource, SizeX, nTextureType);
			 break;
		
		case KM_TEXTURE_PALETTIZE4_MM:
		case KM_TEXTURE_PALETTIZE8_MM:
				 CreatePalettes ();
				 LoadPalettisedMipmap (pTexSurfaceDesc, p16bitsConverted, pSource, pTransSource, SizeX, nTextureType);
				 break;
				 
		case KM_TEXTURE_PALETTIZE4:
		case KM_TEXTURE_PALETTIZE8:
				CreatePalettes ();
				LoadPalettised(pTexSurfaceDesc, p16bitsConverted, pSource, pTransSource, SizeX, SizeY, nTextureType);
				break;
				
		case KM_TEXTURE_VQ:
			 ErrorCode = LoadVQ (pTexSurfaceDesc, p16bitsConverted, pSource, pTransSource, SizeX, nTextureType, FALSE);
			 break;
	
		case KM_TEXTURE_VQ_MM:
			 ErrorCode = LoadVQ (pTexSurfaceDesc, p16bitsConverted, pSource, pTransSource, SizeX, nTextureType, TRUE);
			 break;
			 
		default: return KMSTATUS_INVALID_TEXTURE_TYPE;
	}

	if (ErrorCode != KMSTATUS_SUCCESS) return ErrorCode;
	
	/* Everything's OK */
	return KMSTATUS_SUCCESS;
}
/****************************************************************************
 *  Function Name   : LoadTextureInVideoMemory                            
 *  Inputs          : pTextureSurfaceDesc, MemPtr,SizeX, SizeY, nTextureType,                                  
 *  Outputs         : None                                         
 *  Returns         : ErrorCode                          
 *  Globals Used    : None                                      
 *  Description     : This function loads a texture into video memory.     
 *  Notes           : MemPtr is a pointer to the 16bits texture data already
 *                    converted.
 *****************************************************************************/
KMDWORD LoadTextureInVideoMemory(KMSURFACEDESC *pTexSurfaceDesc, unsigned long *pSourceTex, 
									KMINT32 SizeX, KMINT32 SizeY, KMTEXTURETYPE nTextureType)
{
KMDWORD ErrorCode;

	/* Create texture surface */
	ErrorCode = kmCreateTextureSurface(
		pTexSurfaceDesc,		/* OUT	PKMSURFACEDESC	pSurfaceDesc */
		SizeX,					/*	IN	KMINT32			nWidth */
		SizeY,					/*	IN	KMINT32			nHeightt */
		nTextureType			/*	IN	KMTEXTURETYPE	nTextureType */
	);

	if (ErrorCode != KMSTATUS_SUCCESS) return ErrorCode;


	/* Load and set texture */
	ErrorCode = kmLoadTexture( 
		pTexSurfaceDesc,						/* PKMSURFACEDESC pSurfaceDesc */
		pSourceTex								/* PKMDWORD pTexture */
		);

	if (ErrorCode != KMSTATUS_SUCCESS) return ErrorCode;

	/* Everything's OK */
	return KMSTATUS_SUCCESS;
}
/****************************************************************************
 *  Function Name   : LoadRectangular                            
 *  Inputs          : pTextureSurfaceDesc, p16bitsConverted, pSource, pTransSource,
 *                     SizeX, SizeY, nTextureType,                                  
 *  Outputs         : None                                         
 *  Returns         : ErrorCode                          
 *  Globals Used    : None                                      
 *  Description     : This function converts from a 888 format to a 16 bits
 *                    rectangular or stride format.       
 *  Notes           : p16bitsConverted is a pointer to a zone of free memory, 
 *                    and it's where the converted data will be stored
 *****************************************************************************/
KMDWORD LoadRectangular(KMSURFACEDESC *pTexSurfaceDesc, unsigned short *p16bitsConverted, unsigned char *pSource, 
						unsigned char *pTransSource, KMINT32 SizeX, KMINT32 SizeY, KMTEXTURETYPE nTextureType)
{
register 		i, j;
unsigned short 	nFormatType, nColorType;
unsigned char  	*pCurrentPointer, *pCurrentTransPointer, a, r, b, g;
unsigned 		nCounterConvert = 0;
unsigned short 	Y0, Y1, U, V;
unsigned		Height, Height10, Height01;
KMDWORD 		ErrorCode;


	nFormatType = nTextureType & 0xFF00;
	nColorType  = nTextureType & 0x00FF;
	
	nCounterConvert = 0;
	
	for (j=0; j<SizeY; j++)
	{
		pCurrentPointer = pSource + j*SizeX*3;
		if (pTransSource) pCurrentTransPointer = pTransSource + j*SizeX*3;
		
		for (i=0; i<SizeX; i++)
		{
			if (pTransSource)
			{
				a = *(pCurrentTransPointer); 
				pCurrentTransPointer+=3;
			}
			else
			{
				a = 255;
			}
			b = *(pCurrentPointer++);
			g = *(pCurrentPointer++);
			r = *(pCurrentPointer++);			
			
			switch (nColorType)
			{	
				case KM_TEXTURE_RGB565:
					 *(p16bitsConverted+nCounterConvert++) = MAKE_565 (r, g, b); break;
						 
				case KM_TEXTURE_ARGB4444:
				     *(p16bitsConverted+nCounterConvert++) = MAKE_4444 (a, r, g, b); break;
						     
				case KM_TEXTURE_ARGB1555:
				     *(p16bitsConverted+nCounterConvert++) = MAKE_1555 (a, r, g, b); break;
				     
				case KM_TEXTURE_YUV422:
			     		if(!(i&1)) /* even pixel */
			     		{
			     			Y0= (unsigned)(0.29*r + 0.57*g + 0.14*b);
							U = (unsigned)(128.0f - 0.14*r - 0.29*g + 0.43*b);
						}
			     		else  /* odd pixel */
			     		{
			     			Y1= (unsigned)(0.29*r + 0.57*g + 0.14*b);
							V = (unsigned)(128.0f + 0.36*r - 0.29*g - 0.07*b);
							
							*(p16bitsConverted+nCounterConvert++) = (Y0<<8)|U;
							*(p16bitsConverted+nCounterConvert++) = (Y1<<8)|V;
				  		}
			     		break;
			     		
				case KM_TEXTURE_BUMP:
						Height = r;
						
						if(i<SizeX-1) Height10 = *(pCurrentPointer + 3);
						else          Height10 = *(pCurrentPointer - SizeX*3 + 3); /* Horizontal wrap */
						
						if(j<SizeY-1) 	Height01 = *(pCurrentPointer + SizeX*3);
						else    		Height01 = *(pCurrentPointer - SizeX*3*(SizeY-1)); /* Vertical wrap */
						
						*(p16bitsConverted+nCounterConvert++) = CalculateBump (Height, Height01, Height10);
						break;
			} 
			
		} /* end of i loop */
	} /*  end of j loop */
		
	
	ErrorCode = LoadTextureInVideoMemory(pTexSurfaceDesc, (unsigned long *)p16bitsConverted, SizeX, SizeY, nTextureType);
	
	if (ErrorCode != KMSTATUS_SUCCESS) return ErrorCode;
	
	/* Everything's OK */
	return KMSTATUS_SUCCESS;
}
/****************************************************************************
 *  Function Name   : LoadTwiddled                            
 *  Inputs          : pTextureSurfaceDesc, p16bitsConverted, pSource, pTransSource,
 *                     SizeX, SizeY, nTextureType,                                  
 *  Outputs         : None                                         
 *  Returns         : ErrorCode                          
 *  Globals Used    : None                                      
 *  Description     : This function converts from a 888 format to a 16 bits
 *                    twiddled format.       
 *  Notes           : p16bitsConverted is a pointer to a zone of free memory, 
 *                    and it's where the converted data will be stored
 *****************************************************************************/
KMDWORD LoadTwiddled(KMSURFACEDESC *pTexSurfaceDesc, unsigned short *p16bitsConverted, unsigned char *pSource, 
						unsigned char *pTransSource, KMINT32 SizeX, KMINT32 SizeY, KMTEXTURETYPE nTextureType)
{
register 		i, j;
unsigned short 	nFormatType, nColorType;
unsigned 		nOffset, nPrevOffset, *pOffsetX, *pOffsetY;
unsigned char  	*pCurrentPointer, *pCurrentTransPointer, a, r, b, g;
unsigned 		nCounterConvert = 0, nCounterSource = 0;
unsigned		Height, Height10, Height01;
unsigned short 	Y0, Y1, U, V;
KMDWORD 		ErrorCode;


	nFormatType = nTextureType & 0xFF00;
	nColorType  = nTextureType & 0x00FF;
	
	pOffsetY = TwiddledOffset;
	
	for (j=0; j<SizeY; j++)
	{
		pCurrentPointer = pSource + j*SizeX*3;
		if (pTransSource) pCurrentTransPointer = pTransSource + j*SizeX*3;
		
		pOffsetX = TwiddledOffset;
		
		for (i=0; i<SizeX; i++)
		{
			if (pTransSource)
			{
				a = *(pCurrentTransPointer); 
				pCurrentTransPointer+=3;
			}
			else
			{
				a = 255;
			}
			b = *(pCurrentPointer++);
			g = *(pCurrentPointer++);
			r = *(pCurrentPointer++);			
			
			/* This is the location for a twiddled pixel */
			nOffset = (*pOffsetX|((*pOffsetY)>>1));
			
			switch (nColorType)
			{	
				case KM_TEXTURE_RGB565:
					 *(p16bitsConverted+nOffset) = MAKE_565 (r, g, b); break;
						 
				case KM_TEXTURE_ARGB4444:
				     *(p16bitsConverted+nOffset) = MAKE_4444 (a, r, g, b); break;
						     
				case KM_TEXTURE_ARGB1555:
				     *(p16bitsConverted+nOffset) = MAKE_1555 (a, r, g, b); break;
				     
				case KM_TEXTURE_YUV422:
			     		if(!(i&1)) /* even pixel */
			     		{
			     			Y0= (unsigned)(0.29*r + 0.57*g + 0.14*b);
							U = (unsigned)(128.0f - 0.14*r - 0.29*g + 0.43*b);
							
							nPrevOffset = nOffset;
						}
			     		else  /* odd pixel */
			     		{
			     			Y1= (unsigned)(0.29*r + 0.57*g + 0.14*b);
							V = (unsigned)(128.0f + 0.36*r - 0.29*g - 0.07*b);
							
							*(p16bitsConverted+nPrevOffset) = (Y0<<8)|U;
							*(p16bitsConverted+nOffset) = (Y1<<8)|V;
				  		}
			     		break;
			     		
		     	case KM_TEXTURE_BUMP:
						Height = r;
						
						if(i<SizeX-1) Height10 = *(pCurrentPointer + 3);
						else          Height10 = *(pCurrentPointer - SizeX*3 + 3); /* Horizontal wrap */
						
						if(j<SizeY-1) 	Height01 = *(pCurrentPointer + SizeX*3);
						else    		Height01 = *(pCurrentPointer - SizeX*3*(SizeY-1)); /* Vertical wrap */
						
						*(p16bitsConverted+nOffset++) = CalculateBump (Height, Height01, Height10);
						break;
			} 
			
			pOffsetX++;
			
		} /* end of i loop */
		
		pOffsetY++;
		
	} /*  end of j loop */
		
	ErrorCode = LoadTextureInVideoMemory(pTexSurfaceDesc, (unsigned long *)p16bitsConverted, SizeX, SizeY, nTextureType);
	
	if (ErrorCode != KMSTATUS_SUCCESS) return ErrorCode;
	
	/* Everything's OK */
	return KMSTATUS_SUCCESS;
}
/****************************************************************************
 *  Function Name   : LoadTwiddledMipmap                            
 *  Inputs          : pTextureSurfaceDesc, p16bitsConverted, pSource, pTransSource,
 *                     SizeX, SizeY, nTextureType,                                  
 *  Outputs         : None                                         
 *  Returns         : ErrorCode                          
 *  Globals Used    : None                                      
 *  Description     : This function converts from a 888 format to a 16 bits
 *                    twiddled mipmapped format.       
 *  Notes           : p16bitsConverted is a pointer to a zone of free memory, 
 *                    and it's where the converted data will be stored
 *****************************************************************************/
KMDWORD LoadTwiddledMipmap(KMSURFACEDESC *pTexSurfaceDesc, const void *MemPtr, unsigned char *pSource, unsigned char *pTransSource,
								 KMINT32 nSourceSize, KMTEXTURETYPE nTextureType)
{
register 		i, j, k;
unsigned 		*p32BitsData, *p32BitsMem, nStart32bits = 0, rgb;
unsigned  		uCont = 0, nCurrentLevelSize, nOffset, nPrevOffset, *pOffsetX, *pOffsetY;
unsigned short 	nFormatType, nColorType, *p16bitsConverted;
unsigned char  	*pCurrentPointer, *pCurrentTransPointer, a, r, b, g;
unsigned 		uMimapLevelOffset[] = {	0x00000,0x00001,0x00005,0x00015,0x00055,0x00155,0x00555,0x01555,0x05555,0x15555,0x55555	};
unsigned 		Size[] = { 1,2,4,8,16,32,64,128,256,512,1024 };
unsigned		Height, Height10, Height01;
unsigned 		Y0, Y1, U, V;
KMDWORD 		ErrorCode;
KMDWORD 		bIsTrans = FALSE;

	nFormatType = nTextureType & 0xFF00;
	nColorType  = nTextureType & 0x00FF;
	
	if (pTransSource && (nColorType==KM_TEXTURE_ARGB4444 || nColorType==KM_TEXTURE_ARGB1555))
	{
		 bIsTrans = TRUE;
	}
	else
	{
		bIsTrans = FALSE;
		pTransSource = NULL;
	}
	
	pCurrentPointer = pSource;
	pCurrentTransPointer = pTransSource;
	
	for (i=0; i<=10; i++)
	{
		 if (Size[i] == nSourceSize) nStart32bits = uMimapLevelOffset[i+1];
    }

	   
	/* Start of memory for storing the higher mipmap level in a 32 bits format */ 
	p32BitsMem = (unsigned *) syMalloc (nStart32bits * sizeof(unsigned));
	if (p32BitsMem == NULL) return KMSTATUS_NOT_ENOUGH_MEMORY;
	
	p32BitsData = p32BitsMem + nStart32bits  - (nSourceSize*nSourceSize);
	
	uCont = 0;
	/* Convert to a 32bit format adding the alpha chanel (if possible)*/
	if (bIsTrans)
	{
		for(i=nSourceSize*nSourceSize; i!=0; i--)
		{
			b   = *(pCurrentPointer++);
			g   = *(pCurrentPointer++);
			r   = *(pCurrentPointer++);
			a   = *(pCurrentTransPointer + uCont);
		
			*(p32BitsData++) = MAKE_8888(a,r,g,b);
		
			uCont+=3;		
		}
	}
	else /* No alpha chanel */
	{
		for(i=nSourceSize*nSourceSize; i!=0; i--)
		{
			b   = *(pCurrentPointer++);
			g   = *(pCurrentPointer++);
			r   = *(pCurrentPointer++);
			
			*(p32BitsData++) = MAKE_8888(255,r,g,b);
		}
	}


	p32BitsData = p32BitsMem;
	
	/* Create mipmap levels */
	switch(Glob_CurrentMipmappingMethod)
	{
		default:
		case MIPMAP_2x2:
			for (i=10; i>0; i--)
			{	
				if (Size[i] <= nSourceSize)
				{
				  CreateNextMipmapLevel2x2((unsigned int *)p32BitsData+uMimapLevelOffset[i], Size[i],
				  							bIsTrans,  (unsigned int *)p32BitsData+uMimapLevelOffset[i-1]);
			    }
			}
			break;
		
		case MIPMAP_4x4:
			for (i=10; i>0; i--)
			{	
				if (Size[i] <= nSourceSize)
				{
			  		CreateNextMipmapLevel4x4((unsigned int *)p32BitsData+uMimapLevelOffset[i], Size[i],
			  							bIsTrans,  (unsigned int *)p32BitsData+uMimapLevelOffset[i-1]);
			    }
			}
			break;
			
		case MIPMAP_FOURIER1:
			CreateFourierMipmapLevels(pSource, pTransSource, nSourceSize, p32BitsData, 0);
			break;
	
		case MIPMAP_FOURIER2:
			CreateFourierMipmapLevels(pSource, pTransSource, nSourceSize, p32BitsData, 4);
			break;
			
		case MIPMAP_FOURIER3:
			CreateFourierMipmapLevels(pSource, pTransSource, nSourceSize, p32BitsData, 8);
			break;	
	}
	
	
	
	/* Twiddle */
	p16bitsConverted = (unsigned short *)MemPtr + 1;
	p32BitsData      = p32BitsMem;
	
	for (k=0; k<=10; k++)
	{
		if (Size[k] <= nSourceSize)
		{
		   nCurrentLevelSize = Size[k];
		   
		   pOffsetY = TwiddledOffset;
  	  		  
		  for (j=0; j<nCurrentLevelSize; j++)
		  {
		  	    pOffsetX = TwiddledOffset;
		  		
			   for (i=0; i<nCurrentLevelSize; i++)
			   {
		   		rgb = *(p32BitsData++);
			
				a = rgb;
				r = rgb>>24;
				g = rgb>>16;
				b = rgb>>8;			
				
				/* This is the location for a twiddled pixel */
				nOffset = (*pOffsetX|((*pOffsetY)>>1));
	 
				switch (nColorType)
				{	
					case KM_TEXTURE_RGB565:
				 		*(p16bitsConverted+nOffset) = MAKE_565 (r, g, b); break;
						 
					case KM_TEXTURE_ARGB4444:
			     		*(p16bitsConverted+nOffset) = MAKE_4444 (a, r, g, b); break;
						     
					case KM_TEXTURE_ARGB1555:
			     	 	*(p16bitsConverted+nOffset) = MAKE_1555 (a, r, g, b); break;
			     	 
			     	case KM_TEXTURE_YUV422:
			     		if(!(i&1)) /* Even pixel */
			     		{
			     			Y0= (unsigned)(0.29*r + 0.57*g + 0.14*b);
							U= (unsigned)(128.0f - 0.14*r - 0.29*g + 0.43*b);
							
							nPrevOffset = nOffset;
			     		}
			     		else /* Odd pixel */
			     		{
			     			Y1= (unsigned)(0.29*r + 0.57*g + 0.14*b);
							V=  (unsigned)(128.0f + 0.36*r - 0.29*g - 0.07*b);
							
							*(p16bitsConverted+nPrevOffset) = (Y0<<8)|U;
							*(p16bitsConverted+nOffset)     = (Y1<<8)|V;
			     		}
			     		break;			     	 
			     		
			     	 case KM_TEXTURE_BUMP:
						Height = r;
						
						if(i<nCurrentLevelSize-1) Height10 = (*(p32BitsData + 1))>>24;
						else          Height10 = (*(p32BitsData - 1))>>24; /* Horizontal clamp */
						
						if(j<nCurrentLevelSize-1) 	Height01 = (*(p32BitsData + nCurrentLevelSize))>>24;
						else    		Height01 = (*(p32BitsData - nCurrentLevelSize))>>24; /* Vertical clamp */
						
						*(p16bitsConverted+nOffset++) = CalculateBump (Height, Height01, Height10);
						break;
				} 
				
				pOffsetX++;
			 }
			 
			 pOffsetY++;
		   }
		   
		   /* Next level start */
		   p16bitsConverted += (nCurrentLevelSize*nCurrentLevelSize);
	    }
	}
	
	
	/* Upload in video memory */
	ErrorCode = LoadTextureInVideoMemory(pTexSurfaceDesc, (unsigned long *)MemPtr, nSourceSize, nSourceSize, nTextureType);
	
	syFree (p32BitsMem);
	
	if (ErrorCode != KMSTATUS_SUCCESS) return ErrorCode;
			
	/* Everything's OK */
	return KMSTATUS_SUCCESS;
}
/****************************************************************************
 *  Function Name   : LoadPalettised                            
 *  Inputs          : pTextureSurfaceDesc, p16bitsConverted, pSource, pTransSource,
 *                     SizeX, SizeY, nTextureType,                                  
 *  Outputs         : None                                         
 *  Returns         : ErrorCode                          
 *  Globals Used    : None                                      
 *  Description     : This function converts from a 888 format to a 16 bits
 *                    palettised format.  
 *                    The 888 format is converted to a 332 format for 8bits and
 *                    to a 121 format for 4bits.     
 *  Notes           : p16bitsConverted is a pointer to a zone of free memory, 
 *                    and it's where the converted data will be stored
 *****************************************************************************/
KMDWORD LoadPalettised(KMSURFACEDESC *pTexSurfaceDesc, unsigned short *p16bitsConverted, unsigned char *pSource, 
						unsigned char *pTransSource, KMINT32 SizeX, KMINT32 SizeY, KMTEXTURETYPE nTextureType)
{
register 		i, j, k, l;
unsigned short 	nFormatType, nColorType;
unsigned char  	*pCurrentPointer, *pCurrentTransPointer, a[4], r[4], b[4], g[4];
unsigned  		nOffset, *pOffsetX, *pOffsetY, BlockCont = 0;
KMDWORD 		ErrorCode;


	nFormatType = nTextureType & 0xFF00;
	nColorType  = nTextureType & 0x00FF;
	
	pOffsetY = TwiddledOffset;
	
	for (j=0; j<SizeY; j+=2)
	{
		pOffsetX = TwiddledOffset; 
		 
		for (i=0; i<SizeX; i+=2)
		{
			
			BlockCont = 0;
			
			/* Read a 4 pixel block in one go
			 *	  ---
			 *   |0|2|
			 *    ---
			 *   |1|3|
			 *    ---
			 */
			for (l=0; l<2; l++)
			{
				for (k=0; k<2; k++)
				{
					if (pTransSource)
					{
						a[BlockCont] = *(pTransSource+(j+k)*SizeX*3+(i+l)*3+0);
					}
					else
					{
						a[BlockCont] = 255;
					}
					
					/* Well, I know it can be optimised... */
					b[BlockCont] = *(pSource+(j+k)*SizeX*3+(i+l)*3+0);
					g[BlockCont] = *(pSource+(j+k)*SizeX*3+(i+l)*3+1);
					r[BlockCont] = *(pSource+(j+k)*SizeX*3+(i+l)*3+2);
					
					BlockCont++;			
				}
			}
			
				
			switch (nColorType)
			{	
				case KM_TEXTURE_ARGB4444:
				case KM_TEXTURE_ARGB1555:
					/* Index 0 is full translucent */
					if(a[0]<128) r[0]=g[0]=b[0]=0;
					if(a[1]<128) r[1]=g[1]=b[1]=0;
					if(a[2]<128) r[2]=g[2]=b[2]=0;
					if(a[3]<128) r[3]=g[3]=b[3]=0;
					
				case KM_TEXTURE_RGB565:
				
					 if(nFormatType == KM_TEXTURE_PALETTIZE4)
					 {
					 	/* This is the location for a twiddled pixel */
						nOffset = (*pOffsetX|((*pOffsetY)>>1));
						
						/* four 4bits indexes stored as b3b2b1b0 short */
					 	*(p16bitsConverted+nOffset) = 
					 	((r[3]&0x80)<<8 | (g[3]&0xC0)<<7 | (b[3]&0x80)<<5 |
					 	 (r[2]&0x80)<<4 | (g[2]&0xC0)<<3 | (b[2]&0x80)<<1 |
					 	 (r[1]&0x80)>>0 | (g[1]&0xC0)>>1 | (b[1]&0x80)>>3 |
					 	 (r[0]&0x80)>>4 | (g[0]&0xC0)>>5 | (b[0]&0x80)>>7 );
					 	break;
					 }
					 else if(nFormatType == KM_TEXTURE_PALETTIZE8)
					 {
					 	/* four 8bits indexes stored as b1b0 and b3b2 shorts */
						nOffset = (((*pOffsetX)>>1) | *pOffsetY);
						
					  	*(p16bitsConverted+nOffset)= 					 	
					 	((r[1]&0xE0)<<8 | (g[1]&0xE0)<<5 | (b[1]&0xC0)<<2 |
					 	(r[0]&0xE0)>>0 | (g[0]&0xE0)>>3 | (b[0]&0xC0)>>6 );
					 	
					 	
					 	pOffsetX++;
						nOffset = (((*pOffsetX)>>1) | *pOffsetY);
					 	
					 	*(p16bitsConverted+nOffset)= 					 	
					 	((r[3]&0xE0)<<8 | (g[3]&0xE0)<<5 | (b[3]&0xC0)<<2 |
					 	(r[2]&0xE0)>>0 | (g[2]&0xE0)>>3 | (b[2]&0xC0)>>6 );
					 	 
					 	break;		
					 }
						 
				
				     break;
				
			} 
			
			pOffsetX++;
		} /* end of i loop */
		
		pOffsetY++;
	} /*  end of j loop */
		
	
	ErrorCode = LoadTextureInVideoMemory(pTexSurfaceDesc, (unsigned long *)p16bitsConverted, SizeX, SizeY, nTextureType);
	
	if (ErrorCode != KMSTATUS_SUCCESS) return ErrorCode;
	
	/* Everything's OK */
	return KMSTATUS_SUCCESS;
}
/****************************************************************************
 *  Function Name   : LoadTwiddledMipmap                            
 *  Inputs          : pTextureSurfaceDesc, p16bitsConverted, pSource, pTransSource,
 *                     SizeX, SizeY, nTextureType,                                  
 *  Outputs         : None                                         
 *  Returns         : ErrorCode                          
 *  Globals Used    : None                                      
 *  Description     : This function converts from a 888 format to a 16 bits
 *                    mipmapped paletised format. 
 *                    The 888 format is converted to a 332 format for 8bits and
 *                    to a 121 format for 4bits.
 *  Notes           : p16bitsConverted is a pointer to a zone of free memory, 
 *                    and it's where the converted data will be stored
 *****************************************************************************/
KMDWORD LoadPalettisedMipmap(KMSURFACEDESC *pTexSurfaceDesc,  unsigned short *MemPtr, unsigned char *pSource,
							 unsigned char *pTransSource, KMINT32 nSourceSize, KMTEXTURETYPE nTextureType)
{
int     		i, j, k, l, m;
unsigned 		*p32BitsData, *p32BitsMem, nStart32bits = 0, rgb;
unsigned  		uCont = 0, nCurrentLevelSize, nOffset, nPrevOffset, *pOffsetX, *pOffsetY;
int			 	nFormatType, nColorType;
unsigned short	*p16bitsConverted;
unsigned char  	*pCurrentPointer, *pCurrentTransPointer;
unsigned 		uMimapLevelOffset[] = {	0x00000,0x00001,0x00005,0x00015,0x00055,0x00155,0x00555,0x01555,0x05555,0x15555,0x55555	};
unsigned 		Size[] = { 1,2,4,8,16,32,64,128,256,512,1024 };
unsigned char	a[4], r[4], b[4], g[4];
unsigned  		BlockCont = 0;
KMDWORD 		ErrorCode;
KMDWORD 		bIsTrans = FALSE;

	nFormatType = (int)(nTextureType & 0x00000FF00);
	nColorType  = (int)(nTextureType & 0x0000000FF);
	
	if (pTransSource && (nColorType==KM_TEXTURE_ARGB4444 || nColorType==KM_TEXTURE_ARGB1555))
	{
		 bIsTrans = TRUE;
	}
	else
	{
		bIsTrans = FALSE;
		pTransSource = NULL;
	}	
	
	pCurrentPointer = pSource;
	pCurrentTransPointer = pTransSource;
	

	
	for (i=0; i<=10; i++)
	{
		 if (Size[i] == nSourceSize) nStart32bits = uMimapLevelOffset[i+1];
    }

	   
	/* Start of memory for storing the higher mipmap level in a 32 bits format */ 
	p32BitsMem = (unsigned *) syMalloc (nStart32bits * sizeof(unsigned));
	if (p32BitsMem == NULL) return KMSTATUS_NOT_ENOUGH_MEMORY;
	
	p32BitsData = p32BitsMem + nStart32bits  - (nSourceSize*nSourceSize);
	
	uCont = 0;
	/* Convert to a 32bit format adding the alpha chanel (if possible)*/
	if (bIsTrans)
	{
		for(i=nSourceSize*nSourceSize; i!=0; i--)
		{
			b[0]   = *(pCurrentPointer++);
			g[0]   = *(pCurrentPointer++);
			r[0]   = *(pCurrentPointer++);
			a[0]   = *(pCurrentTransPointer + uCont);
		
			*(p32BitsData++) = MAKE_8888(a[0],r[0],g[0],b[0]);
		
			uCont+=3;		
		}
	}
	else /* No alpha chanel */
	{
		for(i=nSourceSize*nSourceSize; i!=0; i--)
		{
			b[0]   = *(pCurrentPointer++);
			g[0]   = *(pCurrentPointer++);
			r[0]   = *(pCurrentPointer++);
			
			*(p32BitsData++) = MAKE_8888(255,r[0],g[0],b[0]);
		}
	}


	p32BitsData = p32BitsMem;
	
	/* Create mipmap levels */
	switch(Glob_CurrentMipmappingMethod)
	{
		default:
		case MIPMAP_2x2:
			for (i=10; i>0; i--)
			{	
				if (Size[i] <= nSourceSize)
				{
				  CreateNextMipmapLevel2x2((unsigned int *)p32BitsData+uMimapLevelOffset[i], Size[i],
				  							bIsTrans,  (unsigned int *)p32BitsData+uMimapLevelOffset[i-1]);
			    }
			}
			break;
		
		case MIPMAP_4x4:
			for (i=10; i>0; i--)
			{	
				if (Size[i] <= nSourceSize)
				{
			  		CreateNextMipmapLevel4x4((unsigned int *)p32BitsData+uMimapLevelOffset[i], Size[i],
			  							bIsTrans,  (unsigned int *)p32BitsData+uMimapLevelOffset[i-1]);
			    }
			}
			break;
			
		case MIPMAP_FOURIER1:
			CreateFourierMipmapLevels(pSource, pTransSource, nSourceSize, p32BitsData, 0);
			break;
	
		case MIPMAP_FOURIER2:
			CreateFourierMipmapLevels(pSource, pTransSource, nSourceSize, p32BitsData, 4);
			break;
			
		case MIPMAP_FOURIER3:
			CreateFourierMipmapLevels(pSource, pTransSource, nSourceSize, p32BitsData, 8);
			break;	
	}

	/* Pointer to aligned data (to be filled) */
	if(nFormatType == 0x000600) p16bitsConverted = (unsigned short *)MemPtr + 1; /*KM_TEXTURE_PALETTIZE4*/
	else 		 				p16bitsConverted = (unsigned short *)MemPtr + 2; /*KM_TEXTURE_PALETTIZE8*/
	
	/* Pointer to argb colors */
	p32BitsData      = p32BitsMem;
	
	/* Level by level from the smaller one (1x1) to the bigest one */
	for (m=0; m<=10; m++)
	{
		if (Size[m] <= nSourceSize)
		{
		   nCurrentLevelSize = Size[m];
		   
		   pOffsetY = TwiddledOffset;
	
		  for (j=0; j<nCurrentLevelSize; j+=2)
		  {
			pOffsetX = TwiddledOffset; 
		 
			for (i=0; i<nCurrentLevelSize; i+=2)
			{
			
				BlockCont = 0;
				
				/* Read a 4 pixel block in one go
				 *	  ---
				 *   |0|2|
				 *    ---
				 *   |1|3|
				 *    ---
				 */

				for (l=0; l<2; l++)
				{
					for (k=0; k<2; k++)
					{
						rgb = *(p32BitsData+(j+k)*nCurrentLevelSize+(i+l));
		
						if (bIsTrans)
						{
							a[BlockCont] = rgb;
						}
						else
						{
							a[BlockCont] = 255;
						}
					
						r[BlockCont] = (rgb>>24);
						g[BlockCont] = (rgb>>16);
						b[BlockCont] = (rgb>>8);
					
						BlockCont++;			
					}
				}

		       switch ((int)nColorType)
				  {	
					case KM_TEXTURE_ARGB4444:
					case KM_TEXTURE_ARGB1555:
						/* Index 0 is full translucent */
						if(a[0]<128) r[0]=g[0]=b[0]=0;
						if(a[1]<128) r[1]=g[1]=b[1]=0;
						if(a[2]<128) r[2]=g[2]=b[2]=0;
						if(a[3]<128) r[3]=g[3]=b[3]=0;
					
					case KM_TEXTURE_RGB565:
					
					 	if(nFormatType == 0x000600) /* KM_TEXTURE_PALETTIZE4 */
					 	{
					 		/* This is the location for a twiddled pixel */
							nOffset = (*pOffsetX|((*pOffsetY)>>1));
						
							/* four 4bits indexes stored as b3b2b1b0 short */
							*(p16bitsConverted+nOffset) = 
							((r[3]&0x80)<<8 | (g[3]&0xC0)<<7 | (b[3]&0x80)<<5 |
					 		 (r[2]&0x80)<<4 | (g[2]&0xC0)<<3 | (b[2]&0x80)<<1 |
					 		 (r[1]&0x80)>>0 | (g[1]&0xC0)>>1 | (b[1]&0x80)>>3 |
					 		 (r[0]&0x80)>>4 | (g[0]&0xC0)>>5 | (b[0]&0x80)>>7 );
					  	}
					 	else  /* KM_TEXTURE_PALETTIZE8 */
					 	{
					 		nOffset = (((*pOffsetX)>>1) | *pOffsetY);
							
							/* four 8bits indexes stored as b1b0 and b3b2 shorts */
					  		*(p16bitsConverted+nOffset)=  				 	
					 		((r[1]&0xE0)<<8 | (g[1]&0xE0)<<5 | (b[1]&0xC0)<<2 |
					 		(r[0]&0xE0)>>0 | (g[0]&0xE0)>>3 | (b[0]&0xC0)>>6 );
					 	
					 	
					 		pOffsetX++;
							nOffset = (((*pOffsetX)>>1) | *pOffsetY);
					 	
					 		*(p16bitsConverted+nOffset)= 					 	
					 		((r[3]&0xE0)<<8 | (g[3]&0xE0)<<5 | (b[3]&0xC0)<<2 |
					 		(r[2]&0xE0)>>0 | (g[2]&0xE0)>>3 | (b[2]&0xC0)>>6 );
					 	}
					 					
				  	} 
					pOffsetX++;
				} /* end of i loop */
		
			pOffsetY++;
			} /*  end of j loop */
		   
		  /* Next level start */
		 if(nFormatType == 0x000600) p16bitsConverted += (nCurrentLevelSize*nCurrentLevelSize)/4; /*KM_TEXTURE_PALETTIZE4*/ 
		 else 				         p16bitsConverted += (nCurrentLevelSize*nCurrentLevelSize)/2; /*KM_TEXTURE_PALETTIZE8 */
		 
		 p32BitsData += (nCurrentLevelSize*nCurrentLevelSize);
	    }
	}

	/* Upload in video memory */
	ErrorCode = LoadTextureInVideoMemory(pTexSurfaceDesc, (unsigned long *)MemPtr, nSourceSize, nSourceSize, nTextureType);
	
	syFree (p32BitsMem);
	
	if (ErrorCode != KMSTATUS_SUCCESS) return ErrorCode;
			
	/* Everything's OK */
	return KMSTATUS_SUCCESS;
}
/****************************************************************************
 *  Function Name   : LoadTwiddledMipmap                            
 *  Inputs          : pTextureSurfaceDesc, p16bitsConverted, pSource, pTransSource,
 *                     SizeX, SizeY, nTextureType,                                  
 *  Outputs         : None                                         
 *  Returns         : ErrorCode                          
 *  Globals Used    : None                                      
 *  Description     : This function converts from a 888 format to a 16 bits
 *                    twiddled mipmapped format.       
 *  Notes           : p16bitsConverted is a pointer to a zone of free memory, 
 *                    and it's where the converted data will be stored
 *****************************************************************************/
KMDWORD LoadVQ(KMSURFACEDESC *pTexSurfaceDesc, unsigned short *p16bitsConverted, unsigned char *pSource, unsigned char *pTransSource,
								 KMINT32 nSourceSize, KMTEXTURETYPE nTextureType, int bMipmap)
{
int		i;
int     nColourType;
int 	ErrorValue;	
float	fErrorFound;
float 	fColourWeights[3] = { 1.0f, 1.0f, 1.0f};
float	fFreqWeights[4]   = { 1.0f, 1.0f, 1.0f, 1.0f};
unsigned char *p8BitsAlphaChannel;
	
	
	 switch (nTextureType & 0x00FF)
	 {
	 	default:
	 	case KM_TEXTURE_RGB565: 	nColourType = FORMAT_565; break;
	 	case KM_TEXTURE_ARGB4444: 	nColourType = FORMAT_4444; break;
	 	case KM_TEXTURE_ARGB1555: 	nColourType = FORMAT_1555; break;
	 };
	 
	if (nColourType == FORMAT_565)
	{
		 pTransSource = NULL;
	}
	
	p8BitsAlphaChannel = NULL;
	
	/* convert the alpha source from 24bits to 8bits */
	if(pTransSource)
	{
		p8BitsAlphaChannel = (unsigned char *) syMalloc (nSourceSize * nSourceSize * sizeof(char));
		
		for (i=0; i<nSourceSize*nSourceSize; i++)
		{
			p8BitsAlphaChannel[i] = *(pTransSource+i*3);
		}
	}
	
	ErrorValue = CreateVq(
	 					(void *) pSource, 			/* RGB Source (24bits format)*/
						(void *) p8BitsAlphaChannel,/* Alpha Source (8 bits format)*/
						(void *) (p16bitsConverted),/* 16bits Output */
						nSourceSize,				/* Size (must be a square) */
						bMipmap, 					/* Mipmap */
						(pTransSource)?TRUE:FALSE, 	/* Translucent channel */
						TRUE, 						/* Dither */
						256, 						/* Num Codes */
						nColourType, 				/* Colour format */
						5, 							/* Num Iterartions */
						TRUE, 						/* Do Freq */
						fColourWeights, 			/* Colour weights */
						fFreqWeights, 				/* Frequency weights */
						FreqYIQspace,				/* Colour Space (FreqYIQspace=0 or RGBspace=1) */
						0, 							/* Alpha sense */
						0.1f, 						/* Percent of error */
						&fErrorFound ); 			/* Error found */
						
	/* Important Note: CreateVQ generates a info header of 12 bytes (6 shorts).*/
	ErrorValue = LoadTextureInVideoMemory(pTexSurfaceDesc, (unsigned long *)(p16bitsConverted+6), 
					nSourceSize, nSourceSize, nTextureType);
					
	if(p8BitsAlphaChannel) syFree(p8BitsAlphaChannel);
	
	return ErrorValue;
}

/****************************************************************************
 *  Function Name   : CalculateBump                            
 *  Inputs          : Height, Height01, Height10                                 
 *  Outputs         : None                                         
 *  Returns         : R/S angles already packed in a WORD.                          
 *  Globals Used    : None                                      
 *  Description     : This inline function convert three Heights (current, right and 
 *                    bottom values)in a bumpmap angle.       
 *****************************************************************************/
unsigned short CalculateBump (unsigned Height, unsigned Height01, unsigned Height10)
{
unsigned char *pSource;
int rows, cols;
int u,v,u1,v1, u2, v2;			
unsigned char h, hv1, hv2, hu1, hu2, h10, h01;
double dH01,dH10;		
unsigned char RAng,SAng;	

	/* Check for special case first */
	if(( Height == Height01 ) && ( Height == Height10 ))
	{
		/* Height map is flat here */
		return 0xFF00;	
	}

	else
	{
		/* Derive the delta Heights */
		dH01 = ((double)Height - (double)Height01)/32.0; 
		dH10 = ((double)Height - (double)Height10)/32.0;
				
		RAng = (unsigned char)(int)(atan2(dH01,dH10)*128.0/3.14159);	
		SAng = (unsigned char)(int)(atan2(1.0,sqrt(dH01*dH01+dH10*dH10))*255.0*2.0/3.14159);
		
		return (((unsigned short)SAng)<<8) | ((unsigned short)RAng);
	}
}

/****************************************************************************
 *  Function Name   : CreatePalettes                            
 *  Inputs          : None                               
 *  Outputs         : None                                         
 *  Returns         :                           
 *  Globals Used    :                                       
 *  Description     : Create two palettes, one of 256 entries for 8bits palettised
 *                    and another one of 16 entries for 4bits paslettised.
 *                    These palettes are the same for all the palettised textures.
 *                    The 8bits format is a 332 palette and the 4bits one is a 121.      
 *****************************************************************************/
void CreatePalettes (void)
{
register i;
KMPALETTEDATA*	pPaletteTable;
int DataOffset=0;
	
	/* Allocate palett table 32bits aligned */
	pPaletteTable = (KMPALETTEDATA *)syMalloc(sizeof(KMPALETTEDATA));
	
	/* Set palette type */
	kmSetPaletteMode (KM_PALETTE_16BPP_ARGB1555);
	
	/* Fill up the banks */
	
	/* for Bank 0 : 8bits */
	for(i = 0; i<256; i++) 
	{
		pPaletteTable->dwPaletteData[DataOffset++] = (KMDWORD)MAKE_1555((i==0)?0x00:0xFF,(i<<0),(i<<3),(i<<6));
	}
		
	/* for Bank 16 : 4bits */
	for(i = 0; i<16; i++)
	{
		pPaletteTable->dwPaletteData[DataOffset++] = (KMDWORD)MAKE_1555((i==0)?0x00:0xFF,(i<<4),(i<<5),(i<<7));
	}
	
	kmSetPaletteData(pPaletteTable);
	
	syFree(pPaletteTable);
}
/*****************************************************************************
 *     MIPMAPPING 
 *****************************************************************************/
/*****************************************************************************
 * Function Name  : CreateNextMipmapLevel2x2
 * Inputs		  : *pBitmapData32, nSourceDim, bTranslucent
 * Output		  : *pOutputData32
 * Returns		  : Nothing
 * Description    : Create next mipmap level from *pBitmapData32.
 *					The next mipmap is computed using a 2x2 algorithm.
 *					Four pixels in the source surface define one pixel
 *					in the destination surface.
 *					For alpha textures, the four pixels channels are weighted
 *					with their opacity values (Alpha).
 *
 *****************************************************************************/
void CreateNextMipmapLevel2x2(unsigned int *pBitmapData32, int nSourceDim, int bTranslucent, unsigned int *pOutputData32)
{
Pixel32Type		Pixel1, Pixel2, Pixel3, Pixel4;
Pixel32Type		*pSourcePixel, *pDestPixel;
int				Alpha;
int				nDestDim=nSourceDim>>1;
int				i, j;
float			fInvA;
			
	/* Get destination pointer */
	pDestPixel=(Pixel32Type *)pOutputData32;
	
	/* For each line of destination surface */
	for (i=0; i<nDestDim; i++)
	{
		/* Get pointer to every two lines in source data */
		pSourcePixel=(Pixel32Type *)(pBitmapData32+2*i*nSourceDim);
		
		/* Translucent mipmapping is a special case : treat it separately */
		if (bTranslucent)
		{
			/* For each column of destination surface */
			for (j=0; j<nDestDim; j++)
			{
				/* Get four pixels */
				Pixel1=*pSourcePixel;
				Pixel2=*(pSourcePixel+1);
				Pixel3=*(pSourcePixel+nSourceDim);
				Pixel4=*(pSourcePixel+nSourceDim+1);

				/* Total alpha value */
				Alpha = Pixel1.Alpha + Pixel2.Alpha + Pixel3.Alpha + Pixel4.Alpha;
				
				/* That's to avoid a division by zero */
				if (!Alpha)
				{
					pDestPixel->Red =  (Pixel1.Red   + Pixel2.Red   + Pixel3.Red   + Pixel4.Red)  >>2;
					pDestPixel->Green =(Pixel1.Green + Pixel2.Green + Pixel3.Green + Pixel4.Green)>>2;
					pDestPixel->Blue = (Pixel1.Blue  + Pixel2.Blue  + Pixel3.Blue  + Pixel4.Blue) >>2;
					pDestPixel->Alpha =0;
				}
				else
				{
					/* Get alpha-weighted colors */
					fInvA=1.0f/Alpha;
					pDestPixel->Red = (int)( (Pixel1.Red*Pixel1.Alpha   + Pixel2.Red*Pixel2.Alpha   + Pixel3.Red*Pixel3.Alpha   + Pixel4.Red*Pixel4.Alpha)   * fInvA );
					pDestPixel->Green=(int)( (Pixel1.Green*Pixel1.Alpha + Pixel2.Green*Pixel2.Alpha + Pixel3.Green*Pixel3.Alpha + Pixel4.Green*Pixel4.Alpha) * fInvA );
					pDestPixel->Blue =(int)( (Pixel1.Blue*Pixel1.Alpha  + Pixel2.Blue*Pixel2.Alpha  + Pixel3.Blue*Pixel3.Alpha  + Pixel4.Blue*Pixel4.Alpha)  * fInvA );
					pDestPixel->Alpha=Alpha>>2;
				}

				/* Increase pointers */
				pSourcePixel+=2; pDestPixel++; 
			}
		}
		else
		{
			/* Opaque mipmapping */

			/* For each column of destination surface */
			for (j=0; j<nDestDim; j++)
			{
				/* Get four pixels */
				Pixel1=*pSourcePixel;
				Pixel2=*(pSourcePixel+1);
				Pixel3=*(pSourcePixel+nSourceDim);
				Pixel4=*(pSourcePixel+nSourceDim+1);

				/* Compute averaged Red, Green and Blue channels */
				pDestPixel->Red =  (Pixel1.Red   + Pixel2.Red   + Pixel3.Red   + Pixel4.Red)  >>2;
				pDestPixel->Green= (Pixel1.Green + Pixel2.Green + Pixel3.Green + Pixel4.Green)>>2;
				pDestPixel->Blue = (Pixel1.Blue  + Pixel2.Blue  + Pixel3.Blue  + Pixel4.Blue) >>2;
				
				/* Increase pointers */
				pSourcePixel+=2; pDestPixel++; 
			}
		}
	}
}
/*****************************************************************************
 * Function Name  : CreateNextMipmapLevel4x4
 * Inputs		  : *pBitmapData32, nSourceDim, bTranslucent
 * Output		  : *pOutputData32
 * Returns		  : Nothing
 * Description    : Create next mipmap level from *pBitmapData32..
 *					The next mipmap is computed using a 4x4 algorith.
 *					
 *					The filter used looks like :
 *
 *						     COLUMN
 *						  W   X   Y   Z
 *						-----------------
 *					A	| 1 | 2 | 2 | 1 |
 *						-----------------
 *					B	| 2 | 4 | 4 | 2 |
 *		ROW				-----------------
 *					C	| 2 | 4 | 4 | 2 |
 *						-----------------
 *					D	| 1 | 2 | 2 | 1 |
 *						-----------------
 *
 *		Basically 16 pixels are used in a weighted sum to produce a single
 *		pixel. The pixels with the "4" weights are the ones originally
 *		used to produce the half-size polygons.
 *
 *
 *		When doing the next 1/2 size pixel to the right, Columns Y and Z must
 *		be re-used as columns W & X. The weightings are chosen so that the X &
 *		Y weightings are 2x the W & Z ones. This allows us to sum up Y and Z
 *		columns using the weightings (1,2,2,1) and then optionally multiply by
 *		2 to generate the (2,4,4,2) columns.
 *
 *		IE in summary, each column only needs to be computed once as we generate
 *		a row of pixels of the 1/2 size map.
 *
 *****************************************************************************/
void CreateNextMipmapLevel4x4(unsigned int *pBitmapData32, int nSourceDim, int bTranslucent, 
							  unsigned int *pOutputData32)
{
	int						i, j;
	Pixel32Type				*lp8b;
	Pixel32Type				*lpSrcPointerPL, *lpSrcPointer, *lpSrcPointerNL, *lpSrcPointerLL;
	Pixel32Type				CW[4], CX[4], CY[4], CZ[4];
	Pixel32Type				*ColumnW=CW, *ColumnX=CX, *ColumnY=CY, *ColumnZ=CZ;
	Pixel32Type				*Dummy;
	DWORD					Red, Green, Blue, Alpha=255;
	float					fInvAlpha;
	int						nSourceHeight, nSourceWidth;
	int						nDestHeight, nDestWidth;

	/* Set up some variables */
	nSourceHeight=nSourceDim;
	nSourceWidth=nSourceDim;
	nDestHeight=nSourceHeight/2;
	nDestWidth=nSourceWidth/2;
	
	/* For each line of destination surface */
	for (i=0; i<nDestHeight; i++)
	{
		/* Compute source and destination pointers */
		lpSrcPointer=(Pixel32Type *)(pBitmapData32 + i*2*nSourceWidth);
		lpSrcPointerNL=(Pixel32Type *)(lpSrcPointer + nSourceWidth);
		lp8b=(Pixel32Type *)(pOutputData32 + i*nDestWidth);

		/* If first line then previous line pointer is the same as current line pointer */
		if (i==0) lpSrcPointerPL=lpSrcPointer;
			else lpSrcPointerPL=lpSrcPointer - nSourceWidth;

		/* If last line then last line pointer is the same as next line pointer */
		if (i==(nDestHeight-1)) lpSrcPointerLL=lpSrcPointerNL;
			else lpSrcPointerLL=lpSrcPointerNL + nSourceWidth;

		/* Initialise column Y and Z */
		ColumnZ[0] = *lpSrcPointerPL;
		ColumnZ[1] = *lpSrcPointer;
		ColumnZ[2] = *lpSrcPointerNL;
		ColumnZ[3] = *lpSrcPointerLL;
		memcpy(ColumnY, ColumnZ, 4*sizeof(Pixel32Type));

		/* For each column of destination surface */
		for (j=0; j<nDestWidth; j++)
		{
			/********************
			** Get all columns **
			********************/

			/* Column W and X are columns Y and Z from previous pixel */
			/* Swap pointers */
			Dummy=ColumnW; ColumnW=ColumnY; ColumnY=Dummy;
			Dummy=ColumnX; ColumnX=ColumnZ; ColumnZ=Dummy;

			/* Special case if end of column */
			if (j==(nDestWidth-1)) 
			{
				/* Get column Y */
				ColumnY[0] = *(lpSrcPointerPL + 1);
				ColumnY[1] = *(lpSrcPointer   + 1); 
				ColumnY[2] = *(lpSrcPointerNL + 1);
				ColumnY[3] = *(lpSrcPointerLL + 1); 

				/* Column Z is equal to column Y */
				memcpy(ColumnZ, ColumnY, 4*sizeof(Pixel32Type));
			}
			else
			{
				/* Get column Y */
				ColumnY[0] = *(lpSrcPointerPL + 1);
				ColumnY[1] = *(lpSrcPointer   + 1); 
				ColumnY[2] = *(lpSrcPointerNL + 1);
				ColumnY[3] = *(lpSrcPointerLL + 1); 
				
				/* Get column Z */
				ColumnZ[0] = *(lpSrcPointerPL + 2);
				ColumnZ[1] = *(lpSrcPointer   + 2); 
				ColumnZ[2] = *(lpSrcPointerNL + 2);
				ColumnZ[3] = *(lpSrcPointerLL + 2); 
			}

			/* If translucent information, also take Alpha channel */
			if (bTranslucent)
			{
				/* Compute Alpha */
				Alpha= ColumnW[0].Alpha + 2*ColumnX[0].Alpha + 2*ColumnY[0].Alpha +   ColumnZ[0].Alpha +
					 2*ColumnW[1].Alpha + 4*ColumnX[1].Alpha + 4*ColumnY[1].Alpha + 2*ColumnZ[1].Alpha +
					 2*ColumnW[2].Alpha + 4*ColumnX[2].Alpha + 4*ColumnY[2].Alpha + 2*ColumnZ[2].Alpha +
				       ColumnW[3].Alpha + 2*ColumnX[3].Alpha + 2*ColumnY[3].Alpha +   ColumnZ[3].Alpha;

				/* If alpha is 0, then do not use it in weighting operation */
				if (!Alpha)
				{
					/* Compute resulting color */
					Red=   ColumnW[0].Red + 2*ColumnX[0].Red + 2*ColumnY[0].Red +   ColumnZ[0].Red +
						 2*ColumnW[1].Red + 4*ColumnX[1].Red + 4*ColumnY[1].Red + 2*ColumnZ[1].Red +
						 2*ColumnW[2].Red + 4*ColumnX[2].Red + 4*ColumnY[2].Red + 2*ColumnZ[2].Red +
						   ColumnW[3].Red + 2*ColumnX[3].Red + 2*ColumnY[3].Red +   ColumnZ[3].Red;
					Green= ColumnW[0].Green + 2*ColumnX[0].Green + 2*ColumnY[0].Green +   ColumnZ[0].Green +
						 2*ColumnW[1].Green + 4*ColumnX[1].Green + 4*ColumnY[1].Green + 2*ColumnZ[1].Green +
						 2*ColumnW[2].Green + 4*ColumnX[2].Green + 4*ColumnY[2].Green + 2*ColumnZ[2].Green +
						   ColumnW[3].Green + 2*ColumnX[3].Green + 2*ColumnY[3].Green +   ColumnZ[3].Green;
					Blue=  ColumnW[0].Blue + 2*ColumnX[0].Blue + 2*ColumnY[0].Blue +   ColumnZ[0].Blue +
						 2*ColumnW[1].Blue + 4*ColumnX[1].Blue + 4*ColumnY[1].Blue + 2*ColumnZ[1].Blue +
						 2*ColumnW[2].Blue + 4*ColumnX[2].Blue + 4*ColumnY[2].Blue + 2*ColumnZ[2].Blue +
						   ColumnW[3].Blue + 2*ColumnX[3].Blue + 2*ColumnY[3].Blue +   ColumnZ[3].Blue;

					/* Divide each color channels by total weight */
					//Red = (int)((((float)Red) / 36.0f) + 0.5f);
					//Green = (int)((((float)Green) / 36.0f) + 0.5f);
					//Blue = (int)((((float)Blue) / 36.0f) + 0.5f);					
					
					Red   *= (1.0f / 36.0f);
					Green *= (1.0f / 36.0f);
					Blue  *= (1.0f / 36.0f);
				}
				else
				{
					/* Compute resulting color with alpha */
					Red=   ColumnW[0].Alpha*ColumnW[0].Red + 2*ColumnX[0].Alpha*ColumnX[0].Red + 2*ColumnY[0].Alpha*ColumnY[0].Red + ColumnZ[0].Alpha*ColumnZ[0].Red +
						 2*ColumnW[1].Alpha*ColumnW[1].Red + 4*ColumnX[1].Alpha*ColumnX[1].Red + 4*ColumnY[1].Alpha*ColumnY[1].Red + 2*ColumnZ[1].Alpha*ColumnZ[1].Red +
						 2*ColumnW[2].Alpha*ColumnW[2].Red + 4*ColumnX[2].Alpha*ColumnX[2].Red + 4*ColumnY[2].Alpha*ColumnY[2].Red + 2*ColumnZ[2].Alpha*ColumnZ[2].Red +
						   ColumnW[3].Alpha*ColumnW[3].Red + 2*ColumnX[3].Alpha*ColumnX[3].Red + 2*ColumnY[3].Alpha*ColumnY[3].Red + ColumnZ[3].Alpha*ColumnZ[3].Red;
					Green= ColumnW[0].Alpha*ColumnW[0].Green + 2*ColumnX[0].Alpha*ColumnX[0].Green + 2*ColumnY[0].Alpha*ColumnY[0].Green + ColumnZ[0].Alpha*ColumnZ[0].Green +
						 2*ColumnW[1].Alpha*ColumnW[1].Green + 4*ColumnX[1].Alpha*ColumnX[1].Green + 4*ColumnY[1].Alpha*ColumnY[1].Green + 2*ColumnZ[1].Alpha*ColumnZ[1].Green +
						 2*ColumnW[2].Alpha*ColumnW[2].Green + 4*ColumnX[2].Alpha*ColumnX[2].Green + 4*ColumnY[2].Alpha*ColumnY[2].Green + 2*ColumnZ[2].Alpha*ColumnZ[2].Green +
						   ColumnW[3].Alpha*ColumnW[3].Green + 2*ColumnX[3].Alpha*ColumnX[3].Green + 2*ColumnY[3].Alpha*ColumnY[3].Green + ColumnZ[3].Alpha*ColumnZ[3].Green;
					Blue=  ColumnW[0].Alpha*ColumnW[0].Blue + 2*ColumnX[0].Alpha*ColumnX[0].Blue + 2*ColumnY[0].Alpha*ColumnY[0].Blue + ColumnZ[0].Alpha*ColumnZ[0].Blue +
						 2*ColumnW[1].Alpha*ColumnW[1].Blue + 4*ColumnX[1].Alpha*ColumnX[1].Blue + 4*ColumnY[1].Alpha*ColumnY[1].Blue + 2*ColumnZ[1].Alpha*ColumnZ[1].Blue +
						 2*ColumnW[2].Alpha*ColumnW[2].Blue + 4*ColumnX[2].Alpha*ColumnX[2].Blue + 4*ColumnY[2].Alpha*ColumnY[2].Blue + 2*ColumnZ[2].Alpha*ColumnZ[2].Blue +
						   ColumnW[3].Alpha*ColumnW[3].Blue + 2*ColumnX[3].Alpha*ColumnX[3].Blue + 2*ColumnY[3].Alpha*ColumnY[3].Blue + ColumnZ[3].Alpha*ColumnZ[3].Blue;

					/* Compute 1 over alpha */
					fInvAlpha = 1.0f / Alpha;
					
					/* Divide each color channel by total alpha weight */
					Red	  *= fInvAlpha;
					Green *= fInvAlpha;
					Blue  *= fInvAlpha;
					Alpha *= (1.0f / 36.0f);
				}
			}
			else
			{
				/* Opaque case */
				/* Compute resulting color */
				Red=   ColumnW[0].Red + 2*ColumnX[0].Red + 2*ColumnY[0].Red +   ColumnZ[0].Red +
					 2*ColumnW[1].Red + 4*ColumnX[1].Red + 4*ColumnY[1].Red + 2*ColumnZ[1].Red +
					 2*ColumnW[2].Red + 4*ColumnX[2].Red + 4*ColumnY[2].Red + 2*ColumnZ[2].Red +
					   ColumnW[3].Red + 2*ColumnX[3].Red + 2*ColumnY[3].Red +   ColumnZ[3].Red;
				Green= ColumnW[0].Green + 2*ColumnX[0].Green + 2*ColumnY[0].Green +   ColumnZ[0].Green +
					 2*ColumnW[1].Green + 4*ColumnX[1].Green + 4*ColumnY[1].Green + 2*ColumnZ[1].Green +
					 2*ColumnW[2].Green + 4*ColumnX[2].Green + 4*ColumnY[2].Green + 2*ColumnZ[2].Green +
					   ColumnW[3].Green + 2*ColumnX[3].Green + 2*ColumnY[3].Green +   ColumnZ[3].Green;
				Blue=  ColumnW[0].Blue + 2*ColumnX[0].Blue + 2*ColumnY[0].Blue +   ColumnZ[0].Blue +
					 2*ColumnW[1].Blue + 4*ColumnX[1].Blue + 4*ColumnY[1].Blue + 2*ColumnZ[1].Blue +
					 2*ColumnW[2].Blue + 4*ColumnX[2].Blue + 4*ColumnY[2].Blue + 2*ColumnZ[2].Blue +
					   ColumnW[3].Blue + 2*ColumnX[3].Blue + 2*ColumnY[3].Blue +   ColumnZ[3].Blue;




					/* Divide each color channels by total weight */
					//Red = (int)((((float)Red) / 36.0f) + 0.5f);
					//Green = (int)((((float)Green) / 36.0f) + 0.5f);
					//Blue = (int)((((float)Blue) / 36.0f) + 0.5f);
					
				/* Divide each color channel by total weight */
				Red   *= (1.0f / 36.0f);
				Green *= (1.0f / 36.0f);
				Blue  *= (1.0f / 36.0f);
			}

			/* Write resulting color */
			lp8b->Blue=Blue;
			lp8b->Green=Green;
			lp8b->Red=Red;
			lp8b->Alpha=Alpha;
			lp8b++;

			/* Increase source pointers */
			lpSrcPointerPL += 2;
			lpSrcPointer   += 2;
			lpSrcPointerNL += 2;
			lpSrcPointerLL += 2;
		}
	}
}
/*******************************************************************************
 * Function Name  : CreateFourierMipmapLevels
 * Input		  : lpDD4, lpDev3, *pBm, *pBmTrans, int nOrder
 * Input/Output	  : lpDDSSystemMemorySurface
 * Returns		  : TRUE or FALSE
 * Global Used    : None
 * Description    : Create all mipmap levels of an image pointed to by pBm
 *					and store them in texture surfaces attached to the passed
 *					texture surface.
 *					The texture surface must have been created with the
 *					DDSCAPS_TEXTURE, DDSCAPS_MIPMAP, and DDSCAPS_COMPLEX caps.
 *					Width and Height must have been specified at surface
 *					creation.
 *					Texture must be square and a power of 2.
 *******************************************************************************/
BOOL CreateFourierMipmapLevels(unsigned char *pBitmapData24, unsigned char *pBitmapTransData24,int nSourceDim, 
							   unsigned int *pOutputData32, int nOrder)
{
	int						hres;
	DWORD					dwMirrorSize, dwTextureSize, dwMipmapSize;
	DWORD					dwOffsetRE, dwOffsetIM;
	DWORD					i, ii1, j;
	BYTE					r, g, b, a;
	BYTE					R, G, B, A;
	BYTE					LeftR, LeftG, LeftB, LeftA; 
	BYTE					RightR, RightG, RightB, RightA;
	unsigned int 			*lp32b;
	int						nNumberOfMipmapLevels, nMipmap, nMode;
	float					fScaleFactor, fRedChannel, fGreenChannel, fBlueChannel, fAlphaChannel=-1.0f;
	float					**dataRed, **dataGreen, **dataBlue, **dataAlpha=NULL;
	float					*speqRed, *speqGreen, *speqBlue, *speqAlpha;
	float					**MipmapdataRed, **MipmapdataGreen, **MipmapdataBlue, **MipmapdataAlpha;
	float					*MipmapspeqRed, *MipmapspeqGreen, *MipmapspeqBlue, *MipmapspeqAlpha;
	char					pszString[200];
	unsigned 				uMimapLevelOffset[] = {	0x00000,0x00001,0x00005,0x00015,0x00055,0x00155,0x00555,
													0x01555,0x05555,0x15555,0x55555	};
	
	/* Get texture size and its wrap-around equivalent */
	dwTextureSize=nSourceDim;
	dwMirrorSize=2*dwTextureSize;

	/* Check texture dimensions */
	if (dwTextureSize>2048)
	{
		return FALSE;
	}

	/* Find out how many mipmap levels have to be created.
	   It depends on the texture size. At the same time,
	   check that texture size is a power of 2 */
	switch(dwTextureSize)
	{
		case 2048 :	nNumberOfMipmapLevels=11; break;
		case 1024 :	nNumberOfMipmapLevels=10; break;
		case 512 :	nNumberOfMipmapLevels=9; break;
		case 256:	nNumberOfMipmapLevels=8; break;
		case 128:	nNumberOfMipmapLevels=7; break;
		case 64:	nNumberOfMipmapLevels=6; break;
		case 32:	nNumberOfMipmapLevels=5; break;
		case 16:	nNumberOfMipmapLevels=4; break;
		case 8:		nNumberOfMipmapLevels=3; break;
		case 4:		nNumberOfMipmapLevels=2; break;
		case 2:		nNumberOfMipmapLevels=1; break;
		case 1:		return FALSE; break;
		default :	return FALSE;
	}


	/***************************************************
	** Allocate memory each channel's frequency space **
	***************************************************/
	dataRed=AllocateSquareMatrix(dwMirrorSize);
	speqRed=AllocateVector(2*dwMirrorSize);
	dataGreen=AllocateSquareMatrix(dwMirrorSize);
	speqGreen=AllocateVector(2*dwMirrorSize);
	dataBlue=AllocateSquareMatrix(dwMirrorSize);
	speqBlue=AllocateVector(2*dwMirrorSize);
	if (pBitmapTransData24)
	{
		dataAlpha=AllocateSquareMatrix(dwMirrorSize);
		speqAlpha=AllocateVector(2*dwMirrorSize);
	}

	/****************************
	** Expand data into mirror **
	****************************/
	MirrorExpandBitmap(dataRed, dataGreen, dataBlue, pBitmapTransData24 ? dataAlpha : NULL, 
					   pBitmapData24, pBitmapTransData24, nSourceDim);

	/***************************
	** Fast Fourier Transform **
	***************************/
	/* Apply FFT to get frequency space of each color channel */
	RealFFT2D(dataRed,		speqRed,	dwMirrorSize, dwMirrorSize, 1);
	RealFFT2D(dataGreen,	speqGreen,	dwMirrorSize, dwMirrorSize, 1);
	RealFFT2D(dataBlue,		speqBlue,	dwMirrorSize, dwMirrorSize, 1);
	if (pBitmapTransData24)
	{
		RealFFT2D(dataAlpha, speqAlpha,	dwMirrorSize, dwMirrorSize, 1);
	}

	/*******************************
	** Initialise mipmap creation **
	*******************************/
	dwMipmapSize=dwTextureSize;

	/* Compute amount to multiply output of inverse Fourier with */
	fScaleFactor=1.0f/(dwMirrorSize*dwMirrorSize/2);

	/*************************
	** Mipmap creation loop **
	*************************/
	for (nMipmap=nNumberOfMipmapLevels-1; nMipmap>0; nMipmap--)
	{
		/* Compute new mipmap level size */
		dwMipmapSize = 1<<nMipmap;

		
		/*************************************************
		** Allocate memory for mipmap spectrum and data **
		*************************************************/
		MipmapdataRed=AllocateSquareMatrix(2*dwMipmapSize);
		MipmapspeqRed=AllocateVector(2*(2*dwMipmapSize));
		MipmapdataGreen=AllocateSquareMatrix(2*dwMipmapSize);
		MipmapspeqGreen=AllocateVector(2*(2*dwMipmapSize));
		MipmapdataBlue=AllocateSquareMatrix(2*dwMipmapSize);
		MipmapspeqBlue=AllocateVector(2*(2*dwMipmapSize));
		if (pBitmapTransData24)
		{
			MipmapdataAlpha=AllocateSquareMatrix(2*dwMipmapSize);
			MipmapspeqAlpha=AllocateVector(2*(2*dwMipmapSize));
		}
	
			
		/************************************************
		** Copy lower frequencies into mipmap spectrum **
		************************************************/
		/* For each row */
		for (i=1; i<=dwMipmapSize; i++)
		{
			/* For each column of each row */
			for (j=1; j<=dwMipmapSize; j++)
			{
				/* Compute real and imaginary part offsets */
				dwOffsetRE=(j<<1)-1;
				dwOffsetIM=j<<1;
				
				/* Copy frequencies */
				MipmapdataRed[i][dwOffsetRE] =	dataRed[i][dwOffsetRE];
				MipmapdataRed[i][dwOffsetIM] =	dataRed[i][dwOffsetIM];
				MipmapdataGreen[i][dwOffsetRE]= dataGreen[i][dwOffsetRE];
				MipmapdataGreen[i][dwOffsetIM]=	dataGreen[i][dwOffsetIM];
				MipmapdataBlue[i][dwOffsetRE] =	dataBlue[i][dwOffsetRE];
				MipmapdataBlue[i][dwOffsetIM]=	dataBlue[i][dwOffsetIM];
				if (pBitmapTransData24)
				{
					MipmapdataAlpha[i][dwOffsetRE] = dataAlpha[i][dwOffsetRE];
					MipmapdataAlpha[i][dwOffsetIM] = dataAlpha[i][dwOffsetIM];
				}
			}
			/* Last value of j(dwMipmapSize+1) is in speq */
			MipmapspeqRed[(i<<1)-1]=	speqRed[(i<<1)-1];
			MipmapspeqRed[(i<<1)]=		speqRed[(i<<1)];
			MipmapspeqGreen[(i<<1)-1]=	speqGreen[(i<<1)-1];
			MipmapspeqGreen[(i<<1)]=	speqGreen[(i<<1)];
			MipmapspeqBlue[(i<<1)-1]=	speqBlue[(i<<1)-1];
			MipmapspeqBlue[(i<<1)]=		speqBlue[(i<<1)];
			if (pBitmapTransData24)
			{
				MipmapspeqAlpha[(i<<1)-1]=	speqAlpha[(i<<1)-1];
				MipmapspeqAlpha[(i<<1)]=	speqAlpha[(i<<1)];
			}
		}
		/* For each row */
		for (i=dwMipmapSize+1, ii1=dwMirrorSize-dwMipmapSize+1; i<=2*dwMipmapSize; i++, ii1++)
		{
			/* For each column of each row */
			for (j=1; j<=dwMipmapSize; j++)
			{
				/* Compute real and imaginary part offsets */
				dwOffsetRE=(j<<1)-1;
				dwOffsetIM=(j<<1);

				/* Copy frequencies */
				MipmapdataRed[i][dwOffsetRE] =	dataRed[ii1][dwOffsetRE];
				MipmapdataRed[i][dwOffsetIM]=	dataRed[ii1][dwOffsetIM];
				MipmapdataGreen[i][dwOffsetRE]= dataGreen[ii1][dwOffsetRE];
				MipmapdataGreen[i][dwOffsetIM]=	dataGreen[ii1][dwOffsetIM];
				MipmapdataBlue[i][dwOffsetRE] =	dataBlue[ii1][dwOffsetRE];
				MipmapdataBlue[i][dwOffsetIM]=	dataBlue[ii1][dwOffsetIM];
				if (pBitmapTransData24)
				{
					MipmapdataAlpha[i][dwOffsetRE]=	dataAlpha[ii1][dwOffsetRE];
					MipmapdataAlpha[i][dwOffsetIM]=	dataAlpha[ii1][dwOffsetIM];
				}
			}
			/* Last value of j(dwMipmapSize+1) is in speq */
			MipmapspeqRed[(i<<1)-1]=	speqRed[(ii1<<1)-1];
			MipmapspeqRed[(i<<1)]=		speqRed[(ii1<<1)];
			MipmapspeqGreen[(i<<1)-1]=	speqGreen[(ii1<<1)-1];
			MipmapspeqGreen[(i<<1)]=	speqGreen[(ii1<<1)];
			MipmapspeqBlue[(i<<1)-1]=	speqBlue[(ii1<<1)-1];
			MipmapspeqBlue[(i<<1)]=		speqBlue[(ii1<<1)];
			if (pBitmapTransData24)
			{
				MipmapspeqAlpha[(i<<1)-1]=	speqAlpha[(ii1<<1)-1];
				MipmapspeqAlpha[(i<<1)]=	speqAlpha[(ii1<<1)];
			}
		}

		/********************************************************************
		** Apply a butterworth low-pass filter to new range of frequencies **
		********************************************************************/
		if (nOrder) 
		{
			ApplyLowPassFilter(MipmapdataRed,	MipmapspeqRed,		2*dwMipmapSize, 0.5f, nOrder);
			ApplyLowPassFilter(MipmapdataGreen, MipmapspeqGreen,	2*dwMipmapSize, 0.5f, nOrder);
			ApplyLowPassFilter(MipmapdataBlue,	MipmapspeqBlue,		2*dwMipmapSize, 0.5f, nOrder);
			if (pBitmapTransData24)
			{
				ApplyLowPassFilter(MipmapdataAlpha,	MipmapspeqAlpha, 2*dwMipmapSize, 0.5f, nOrder);
			}
		}

		/****************
		** Inverse FFT **
		****************/
		RealFFT2D(MipmapdataRed,	MipmapspeqRed,		2*dwMipmapSize, 2*dwMipmapSize, -1);
		RealFFT2D(MipmapdataGreen,	MipmapspeqGreen,	2*dwMipmapSize, 2*dwMipmapSize, -1);
		RealFFT2D(MipmapdataBlue,	MipmapspeqBlue,		2*dwMipmapSize, 2*dwMipmapSize, -1);
		if (pBitmapTransData24)
		{
			RealFFT2D(MipmapdataAlpha,	MipmapspeqAlpha, 2*dwMipmapSize, 2*dwMipmapSize, -1);
		}

		/****************************
		** Mipmap creation        **
		****************************/
		
			
	    /* Loop through y values from bottom to top */
		for (i=dwMipmapSize; i>0; i--)
		{
			/* Calculate pointers corresponding to surface format 16bits */
			lp32b = pOutputData32 + uMimapLevelOffset[nMipmap] + dwMipmapSize*(i-0);
			
			/* Look through x values from right to left */
			for (j=1; j<=(int)dwMipmapSize; j++)
			{ 
				/* Get R, G, B values (always 8-bit each, as the bitmap is 24-bit) */
				fRedChannel=	MipmapdataRed[(dwMipmapSize>>1) + i][(dwMipmapSize>>1) + j]*fScaleFactor;
				fGreenChannel=	MipmapdataGreen[(dwMipmapSize>>1) + i][(dwMipmapSize>>1) + j]*fScaleFactor;
				fBlueChannel=	MipmapdataBlue[(dwMipmapSize>>1) + i][(dwMipmapSize>>1) + j]*fScaleFactor;
				if (pBitmapTransData24)
				{
					fAlphaChannel=MipmapdataAlpha[(dwMipmapSize>>1) + i][(dwMipmapSize>>1) + j]*fScaleFactor;
				}

				/* Write each color channel float value into a byte (0-255) */
				if (fRedChannel<0.0f) R=0;
					else if (fRedChannel>255.0f) R=255;
						else R=fround(fRedChannel);
				if (fGreenChannel<0.0) G=0;
					else if (fGreenChannel>255.0) G=255;
						else G=fround(fGreenChannel);
				if (fBlueChannel<0.0) B=0;
					else if (fBlueChannel>255.0) B=255;
						else B=fround(fBlueChannel);
				if (fAlphaChannel<0.0) A=0;
					else if (fAlphaChannel>255.0) A=255;
						else A=fround(fAlphaChannel);

				/* Which surface format ? */
				/* 16 Bits Translucent */
				if(pBitmapTransData24)
				{
					*(lp32b--) = MAKE_8888(A,R,G,B);
				}
				/* 16 Bits Opaque */
				else
				{
					*(lp32b--) = MAKE_8888(0xFF,R,G,B); 
				}
		
			}
		}

		/***********************
		** Free mipmap memory **
		***********************/
		if (pBitmapTransData24)
		{
			FreeVector(MipmapspeqAlpha, 2*(2*dwMipmapSize));
			FreeSquareMatrix(MipmapdataAlpha, 2*dwMipmapSize);
		}
		FreeVector(MipmapspeqBlue, 2*(2*dwMipmapSize));
		FreeSquareMatrix(MipmapdataBlue, 2*dwMipmapSize);
		FreeVector(MipmapspeqGreen, 2*(2*dwMipmapSize));
		FreeSquareMatrix(MipmapdataGreen, 2*dwMipmapSize);
		FreeVector(MipmapspeqRed, 2*(2*dwMipmapSize));
		FreeSquareMatrix(MipmapdataRed, 2*dwMipmapSize);
	}

	/***************************************
	** Free memory used for spectrum data **
	***************************************/
	if (pBitmapTransData24)
	{
		FreeVector(speqAlpha, 2*dwMirrorSize);
		FreeSquareMatrix(dataAlpha, dwMirrorSize);
	}
	FreeVector(speqBlue, 2*dwMirrorSize);
	FreeSquareMatrix(dataBlue, dwMirrorSize);
	FreeVector(speqGreen, 2*dwMirrorSize);
	FreeSquareMatrix(dataGreen, dwMirrorSize);
	FreeVector(speqRed, 2*dwMirrorSize);
	FreeSquareMatrix(dataRed, dwMirrorSize);
	
	/* No problem occured */
	return TRUE;
}
/*******************************************************************************
 * Function Name  : MirrorExpandBitmap
 * Input		  : *pBm, *pBmTrans
 * Output		  : **Red, **Green, **Blue, **Alpha
 * Returns		  : TRUE or FALSE
 * Global Used    : None
 * Description    : Expand a bitmap into a wrap-around format. Each channel data
 *					is stored in the corresponding array (**Red, **Green, **Blue,
 *					**Alpha).
 *					if hTranslucentBitmap exists then the ALPHA channel is expanded
 *					as well.
 *					Texture must be square and a power of 2.
 *******************************************************************************/
void MirrorExpandBitmap(float **Red, float **Green, float **Blue, float **Alpha, 
						unsigned char *pBm, unsigned char *pBmTrans, int nSize)
{
	DWORD	dwSize, dwTextureSize, dwHalfTextureSize;
	DWORD	i, j;
	DWORD	y;
	BYTE	*lpByte, *lpByteTrans, R, G, B, A;

	/* Get dimensions */
	dwTextureSize=nSize;
	dwSize=2*dwTextureSize;
	dwHalfTextureSize=dwTextureSize/2;


	/**************************
	** Read data from bitmap **
	**************************/
	if (pBmTrans)
	{
		/* Translucent case */

		/* Loop through y values from bottom to top */
		for (i=1; i<=dwTextureSize; i++)
		{
			lpByte=((unsigned char *)pBm+(i)*dwTextureSize*3+dwTextureSize*3+2);
			lpByteTrans=((unsigned char *)pBmTrans+(i)*dwTextureSize*3+dwTextureSize*3+2);
			
						
			/* Look through x values from right to left */
			for (j=1; j<=(int)dwTextureSize; j++)
			{ 
				/* Get R, G, B values (always 8-bit each, as the bitmap is 24-bit) */
				R = *lpByte--;
				G = *lpByte--;
				B = *lpByte--;
				A = *lpByteTrans;
				lpByteTrans-=3;

				// Central data
				Red[(i + dwHalfTextureSize)][dwHalfTextureSize + j]=R;
				Green[(i + dwHalfTextureSize)][dwHalfTextureSize + j]=G;
				Blue[(i + dwHalfTextureSize)][dwHalfTextureSize + j]=B;
				Alpha[(i + dwHalfTextureSize)][dwHalfTextureSize + j]=A;
				

				// Separate texture in two halves in x
				if (j<=dwHalfTextureSize)
				{
					// Left central data
					Red[(i + dwHalfTextureSize)][dwHalfTextureSize - j + 1]=R;
					Green[(i + dwHalfTextureSize)][dwHalfTextureSize - j + 1]=G;
					Blue[(i + dwHalfTextureSize)][dwHalfTextureSize - j + 1]=B;
					Alpha[(i + dwHalfTextureSize)][dwHalfTextureSize - j + 1]=A;
				}
				else
				{
					// Right central data
					Red[(i + dwHalfTextureSize)][dwSize + dwHalfTextureSize - j + 1]=R;
					Green[(i + dwHalfTextureSize)][dwSize + dwHalfTextureSize - j + 1]=G;
					Blue[(i + dwHalfTextureSize)][dwSize + dwHalfTextureSize - j + 1]=B;
					Alpha[(i + dwHalfTextureSize)][dwSize + dwHalfTextureSize - j + 1]=A;
				}
				
				// Separate texture in two halves in y
				if (i<=dwHalfTextureSize)
				{
					// Compute y offset
					y=(dwHalfTextureSize - i + 1);
					
					// Top central data
					Red[y][dwHalfTextureSize + j]=R;
					Green[y][dwHalfTextureSize + j]=G;
					Blue[y][dwHalfTextureSize + j]=B;
					Alpha[y][dwHalfTextureSize + j]=A;

					if (j<=dwHalfTextureSize)
					{
						// Corner
						Red[y][dwHalfTextureSize - j + 1]=R;
						Green[y][dwHalfTextureSize - j + 1]=G;
						Blue[y][dwHalfTextureSize - j + 1]=B;
						Alpha[y][dwHalfTextureSize - j + 1]=A;
					}
					else
					{
						// Corner
						Red[y][dwSize + dwHalfTextureSize - j + 1]=R;
						Green[y][dwSize + dwHalfTextureSize - j + 1]=G;
						Blue[y][dwSize + dwHalfTextureSize - j + 1]=B;
						Alpha[y][dwSize + dwHalfTextureSize - j + 1]=A;
					}
				}
				else
				{
					// Compute y offset
					y=(dwSize + dwHalfTextureSize - i + 1);
					
					// Bottom central data
					Red[y][dwHalfTextureSize + j]=R;
					Green[y][dwHalfTextureSize + j]=G;
					Blue[y][dwHalfTextureSize + j]=B;
					Alpha[y][dwHalfTextureSize + j]=A;
					
					if (j<=dwHalfTextureSize)
					{
						// Corner
						Red[y][dwHalfTextureSize - j + 1]=R;
						Green[y][dwHalfTextureSize - j + 1]=G;
						Blue[y][dwHalfTextureSize - j + 1]=B;
						Alpha[y][dwHalfTextureSize - j + 1]=A;
					}
					else
					{
						// Corner
						Red[y][dwSize + dwHalfTextureSize - j + 1]=R;
						Green[y][dwSize + dwHalfTextureSize - j + 1]=G;
						Blue[y][dwSize + dwHalfTextureSize - j + 1]=B;
						Alpha[y][dwSize + dwHalfTextureSize - j + 1]=B;
					}
				}
			}
		}
	}
	else
	{
		/* Opaque case */

		/* Loop through y values from bottom to top */
		for (i=1; i<=dwTextureSize; i++)
		{
			lpByte=((unsigned char *)pBm+(i)*dwTextureSize*3+dwTextureSize*3+2);
			
			/* Look through x values from right to left */
			for (j=1; j<=(int)dwTextureSize; j++)
			{ 
				/* Get R, G, B values (always 8-bit each, as the bitmap is 24-bit) */
				R = *lpByte--;
				G = *lpByte--;
				B = *lpByte--;

				// Central data
				Red[(i + dwHalfTextureSize)][dwHalfTextureSize + j]=R;
				Green[(i + dwHalfTextureSize)][dwHalfTextureSize + j]=G;
				Blue[(i + dwHalfTextureSize)][dwHalfTextureSize + j]=B;
				

				// Separate texture in two halves in x
				if (j<=dwHalfTextureSize)
				{
					// Left central data
					Red[(i + dwHalfTextureSize)][dwHalfTextureSize - j + 1]=R;
					Green[(i + dwHalfTextureSize)][dwHalfTextureSize - j + 1]=G;
					Blue[(i + dwHalfTextureSize)][dwHalfTextureSize - j + 1]=B;
				}
				else
				{
					// Right central data
					Red[(i + dwHalfTextureSize)][dwSize + dwHalfTextureSize - j + 1]=R;
					Green[(i + dwHalfTextureSize)][dwSize + dwHalfTextureSize - j + 1]=G;
					Blue[(i + dwHalfTextureSize)][dwSize + dwHalfTextureSize - j + 1]=B;
				}
				
				// Separate texture in two halves in y
				if (i<=dwHalfTextureSize)
				{
					// Compute y offset
					y=(dwHalfTextureSize - i + 1);
					
					// Top central data
					Red[y][dwHalfTextureSize + j]=R;
					Green[y][dwHalfTextureSize + j]=G;
					Blue[y][dwHalfTextureSize + j]=B;

					if (j<=dwHalfTextureSize)
					{
						// Corner
						Red[y][dwHalfTextureSize - j + 1]=R;
						Green[y][dwHalfTextureSize - j + 1]=G;
						Blue[y][dwHalfTextureSize - j + 1]=B;
					}
					else
					{
						// Corner
						Red[y][dwSize + dwHalfTextureSize - j + 1]=R;
						Green[y][dwSize + dwHalfTextureSize - j + 1]=G;
						Blue[y][dwSize + dwHalfTextureSize - j + 1]=B;
					}
				}
				else
				{
					// Compute y offset
					y=(dwSize + dwHalfTextureSize - i + 1);
					
					// Bottom central data
					Red[y][dwHalfTextureSize + j]=R;
					Green[y][dwHalfTextureSize + j]=G;
					Blue[y][dwHalfTextureSize + j]=B;
					
					if (j<=dwHalfTextureSize)
					{
						// Corner
						Red[y][dwHalfTextureSize - j + 1]=R;
						Green[y][dwHalfTextureSize - j + 1]=G;
						Blue[y][dwHalfTextureSize - j + 1]=B;
					}
					else
					{
						// Corner
						Red[y][dwSize + dwHalfTextureSize - j + 1]=R;
						Green[y][dwSize + dwHalfTextureSize - j + 1]=G;
						Blue[y][dwSize + dwHalfTextureSize - j + 1]=B;
					}
				}
			}
		}
	}
}


/*******************************************************************************
 * Function Name  : ApplyLowPassFilter
 * Input		  : dwSize, fCutOff, nOrder
 * Input/Output   : **dataRed, **dataGreen, **dataBlue, 
 *					*speqRed, *speqGreen, *speqBlue
 * Returns		  : Nothing
 * Global Used    : None
 * Description    : Apply a low-pass filter to a frequency spectrum.
 *					- dwSize is the length of each dimension of the passed data.
 *					- fCutOff is the cut-off frequency after which frequencies
 *					will be attenuated. Must be positive and between 0.0 and 0.5.
 *					- nOrder is the order of the filter. The higher nOrder 
 *					is, the	sharper the slope of the filter will be. Too much 
 *					attenuation	of higher frequencies can cause "ringing" artefacts 
 *					on some	images. nOrder should be an even number between 2 and 20.
 *					Filter used is of the form : 
 *							
 *						F =	1.0 - ( (f1*f1+f2*f2)**(nOrder/2) ) / (fCutOff**nOrder)
 *
 *******************************************************************************/
void ApplyLowPassFilter(float **data, float *speq, DWORD dwSize, float fCutOff, int nOrder)
{
	DWORD	i, j;
	DWORD	dwOffsetRE, dwOffsetIM;
	float	f, f1, f2;
	float	fFilter;
	float	fOneOverDenominator;
	int		nHalfOrder;

		
	/* Check if parameters are valid */
	if (fCutOff<=0.0f || !data || !speq)
	{
		return;
	}

	/* If order is smaller than 2, then do not perform any filtering and return */
	if (nOrder<2)
	{
		return;
	}

	/* Prevent user to use a too large value for nPower */
	if (nOrder>20)
	{
		nOrder=20;
	}

	/* Compute nHalfOrder (used with (f1*f1+f2*f2) since this term is already a power of 2) */
	nHalfOrder=nOrder/2;

	/* Compute fDenominator */
	fOneOverDenominator=1.0/pow(fCutOff, nOrder);

	/* For each row of spectrum */
	for (i=1; i<=dwSize; i++)
	{
		/* Compute frequency at this row */
		if (i<=((dwSize/2)+1))
		{
			f1=(i-1)/(float)dwSize;
		}
		else
		{
			f1=(dwSize-i+1)/(float)dwSize;
		}

		/* For each column of each row */
		for (j=1; j<=(dwSize/2); j++)
		{
			/* Compute real and imaginary offsets */
			dwOffsetRE=(j<<1)-1;
			dwOffsetIM=j<<1;
			
			/* Compute frequency at this column */
			f2=(j-1)/(float)dwSize;

			/* Compute filter, function of both frequencies */
			f=f1*f1+f2*f2;
			fFilter=1.0 - fOneOverDenominator * pow(f, nHalfOrder);
			if (fFilter<0.0) fFilter=0.0;
			
			/* Multiply real and imaginary parts with filter */
			data[i][dwOffsetRE]*=fFilter;	
			data[i][dwOffsetIM]*=fFilter;
		}

		/* j = (dwSize/2)+1 is in speq */
		speq[(i<<1)-1]*=fFilter;
		speq[i<<1]*=fFilter;
	}
}


/*******************************************************************************
 * Function Name  : AllocateSquareMatrix
 * Input		  : nSize
 * Global Used    : None
 * Returns		  : **float
 * Description    : Allocate a square matrix M[1..nSize][1..nSize]
 *******************************************************************************/
float **AllocateSquareMatrix(long nSize)
{
	long	i;
	float	**ppMatrix;

	ppMatrix=(float **)syMalloc(((nSize+1)*sizeof(float *)));
	ppMatrix[1]=(float *)syMalloc(((nSize*nSize+1)*sizeof(float)));
	
	for (i=2; i<=nSize; i++)
	{
		ppMatrix[i]=ppMatrix[i-1]+nSize;
	}

	return ppMatrix;
}

/*******************************************************************************
 * Function Name  : FreeSquareMatrix
 * Input		  : **m, nSize
 * Global Used    : None
 * Returns		  : Nothing
 * Description    : Frees a matrix allocated with AllocateSquareMatrix().
 *******************************************************************************/
void FreeSquareMatrix(float **ppMatrix, long nSize)
{
	syFree((char  *)ppMatrix[1]);
	syFree((char  *)ppMatrix);
}


/*******************************************************************************
 * Function Name  : AllocateVector
 * Input		  : nSize
 * Global Used    : None
 * Returns		  : *float
 * Description    : Allocate a vector V[1..nSize].
 *******************************************************************************/
float *AllocateVector(long nSize)
{
	float	*pVector;

	pVector=(float *)syMalloc((nSize+1)*sizeof(float));
	
	return pVector;
}

/*******************************************************************************
 * Function Name  : FreeVector
 * Input		  : *v, nSize
 * Global Used    : None
 * Returns		  : Nothing
 * Description    : Frees a vector allocated with AllocateVector().
 *******************************************************************************/
void FreeVector(float *pVector, long nSize)
{
	syFree((char  *)pVector);
}


/*******************************************************************************
 * Function Name  : DFT2D
 * Input		  : data[], nn2, nn3, isign
 * Global Used    : None
 * Description    : For isign==1, replaces data by its two-dimensional discrete 
 *					Fourier	transform.
 *					For isign==-1, data is replaced by its inverse transform 
 *					scaled by the product of the lengths of the two dimensions.
 *******************************************************************************/
void DFT2D(float data[], unsigned long nn2, unsigned long nn3, int isign)
{
#define SWAPVALUE(a, b)	tempr=(a); (a)=(b); (b)=tempr
	int idim;
	unsigned long	i1, i2, i3, i2rev, i3rev, ip1, ip2, ip3, ifp1, ifp2;
	unsigned long	ibit, k1, k2, n, nprev, nrem, ntot;
	float			tempi, tempr;
	double			theta, wi, wpi, wpr, wr, wtemp;
	unsigned long	nn[3];

	nn[1]=nn2;
	nn[2]=nn3;

	for (ntot=1, idim=1; idim<=2; idim++)
	{
		ntot*=nn[idim];
	}
	nprev=1;

	for(idim=2; idim>=1; idim--)
	{
		n=nn[idim];
		nrem=ntot/(n*nprev);
		ip1=nprev<<1;
		ip2=ip1*n;
		ip3=ip2*nrem;
		i2rev=1;
		for (i2=1; i2<=ip2; i2+=ip1)
		{
			if (i2<i2rev)
			{
				for (i1=i2; i1<=i2+ip1-2; i1+=2)
				{
					for (i3=i1; i3<=ip3; i3+=ip2)
					{
						i3rev=i2rev+i3-i2;
						SWAPVALUE(data[i3], data[i3rev]);
						SWAPVALUE(data[i3+1], data[i3rev+1]);
					}
				}
			}
			ibit=ip2>>1;
			while (ibit>=ip1 && i2rev>ibit)
			{
				i2rev-=ibit;
				ibit>>=1;
			}
			i2rev+=ibit;
		}

		ifp1=ip1;
		while (ifp1<ip2)
		{
			ifp2=ifp1<<1;
			theta=isign*6.28318530717959/(ifp2/ip1);
			wtemp=sin(0.5*theta);
			wpr=-2.0*wtemp*wtemp;
			wpi=sin(theta);
			wr=1.0;
			wi=0.0;
			for (i3=1; i3<=ifp1; i3+=ip1)
			{
				for (i1=i3; i1<=i3+ip1-2; i1+=2)
				{
					for (i2=i1; i2<=ip3; i2+=ifp2)
					{
						k1=i2;
						k2=k1+ifp1;
						tempr=(float)wr*data[k2]-(float)wi*data[k2+1];
						tempi=(float)wr*data[k2+1]+(float)wi*data[k2];
						data[k2]=data[k1]-tempr;
						data[k2+1]=data[k1+1]-tempi;
						data[k1]+=tempr;
						data[k1+1]+=tempi;
					}
				}
				wr=(wtemp=wr)*wpr-wi*wpi+wr;
				wi=wi*wpr+wtemp*wpi+wi;
			}
			ifp1=ifp2;
		}
		nprev*=n;
	}
}


/*******************************************************************************
 * Function Name  : RealFFT2D
 * Input		  : *speq (for isign==-1), nn2, nn3, isign
 * Input/Output   : **data
 * Output		  : *speq (for isign==1)
 * Global Used    : None
 * Description    : For isign==1, this function performs the Fourier transform 
 *					of a real 2D array. The resulting spectrum is returned as 
 *					two COMPLEX arrays.
 *					If isign==-1, the INVERSE Fourier transform is performed
 *					on the two COMPLEX arrays and the resulting REAL data is
 *					returned in **data, scaled by nn2*nn3/2.
 *******************************************************************************/
void RealFFT2D(float **data, float *speq, unsigned long nn2, unsigned long nn3, int isign)
{
	unsigned long	i2, i3, j2, j3, nn[3], ii3;
	double			theta, wi, wpi, wpr, wr, wtemp;
	float			c1, c2, h1r, h1i, h2r, h2i;
	
	if (1+&data[nn2][nn3]-&data[1][1] != (float)nn2*nn3)
	{
		return;
	}
	
	c1=0.5;
	c2=-0.5f*isign;
	theta=isign*(6.28318530717959/nn3);
	wtemp=sin(0.5*theta);
	wpr=-2.0*wtemp*wtemp;
	wpi=sin(theta);
	nn[1]=nn2;
	nn[2]=nn3>>1;

	if (isign==1)
	{
		DFT2D(&data[1][1]-1, nn[1], nn[2], isign);
		for (i2=1, j2=0; i2<=nn2; i2++)
		{
			speq[++j2]=data[i2][1];
			speq[++j2]=data[i2][2];
		}
	}

	wr=1.0;
	wi=0.0;

	for (ii3=1, i3=1; i3<=(nn3>>2)+1; i3++, ii3+=2)
	{
		for (i2=1; i2<=nn2; i2++)
		{
			if (i3==1)
			{
				j2=(i2!=1 ? ((nn2-i2)<<1)+3 : 1);
				h1r=c1*(data[i2][1]+speq[j2]);
				h1i=c1*(data[i2][2]-speq[j2+1]);
				h2i=c2*(data[i2][1]-speq[j2]);
				h2r=-c2*(data[i2][2]+speq[j2+1]);
				data[i2][1]=h1r+h2r;
				data[i2][2]=h1i+h2i;
				speq[j2]=h1r-h2r;
				speq[j2+1]=h2i-h1i;
			}
			else
			{
				j2=(i2!=1 ? nn2-i2+2 : 1);
				j3=nn3+3-(i3<<1);
				h1r=c1*(data[i2][ii3]+data[j2][j3]);
				h1i=c1*(data[i2][ii3+1]-data[j2][j3+1]);
				h2i=c2*(data[i2][ii3]-data[j2][j3]);
				h2r=-c2*(data[i2][ii3+1]+data[j2][j3+1]);
				data[i2][ii3]=h1r+wr*h2r-wi*h2i;
				data[i2][ii3+1]=h1i+wr*h2i+wi*h2r;
				data[j2][j3]=h1r-wr*h2r+wi*h2i;
				data[j2][j3+1]=-h1i+wr*h2i+wi*h2r;
			}
		}
		wr=(wtemp=wr)*wpr-wi*wpi+wr;
		wi=wi*wpr+wtemp*wpi+wi;
	}
	
	if (isign==-1)
	{
		DFT2D(&data[1][1]-1, nn[1], nn[2], isign);
	}
}


/*******************************************************************************
 * Function Name  : fround
 * Input		  : fValue
 * Returns		  : int
 * Global Used    : None
 * Description    : Returns the closest integer value to the float input.
 *******************************************************************************/
int fround(float fValue)
{
	/* Positive case */
	if (fValue>=0)
	{
		if ((fValue-floor(fValue))>0.5f)
		{
			return ((int)fValue+1);
		}
		else
		{
			return ((int)(fValue));
		}	
	}
	else
	{
		/* Negative case */
		if ((fValue-floor(fValue))>0.5f)
		{
			return ((int)fValue);
		}
		else
		{
			return ((int)(fValue-1));
		}
	}
}

