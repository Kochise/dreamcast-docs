/******************************************************************************
 * Name			: VQCALC.C
 * Title		: Vector Quantisation Compression Code
 * Author		: Julian Hodgson, Simon Fenney and Rowland Fraser
 *				  
 * Created		: 17/03/1997 
 *
 * Modified     : 14/7/1999 by Carlos Sarria.
 *
 * Copyright	: 1997 by VideoLogic Limited. All rights reserved.
 *              : No part of this software, either material or conceptual 
 *              : may be copied or distributed, transmitted, transcribed,
 *              : stored in a retrieval system or translated into any 
 *              : human or computer language in any form by any means,
 *              : electronic, mechanical, manual or other-wise, or 
 *              : disclosed to third parties without the express written
 *              : permission of VideoLogic Limited, Unit 8, HomePark
 *              : Industrial Estate, King's Langley, Hertfordshire,
 *              : WD4 8LZ, U.K.
 *
 * Description	: Code for Vector Quantisation Compression of a 2D image.
 *				  
 *
 * Platform		: ANSI (HS4/CLX2 Set 2.24)
 * 
 * Note         : CreateVq() returns a VQ format, which consists of a twelve 
 *                byte header followed by the code book data and finally the 
 *                image data without any padding between the sections.
 *                Only the code book data and the image data have to be uploaded 
 *                in video memory. If you want to use this tool for creating a 
 *                'pure' VQ format, just remove the 12-byte header and re-align to a
 *                32-byte boundary.
 *                This code uses malloc() for allocating memory. It works fine under 
 *                VisualC++ and any other PC compilers, but we have found that its use 
 *                under SH4 compilers is not stable enough. It works as expected in 
 *                most cases, but sometimes the final texture is not aligned correctly
 *                for the hardware (it only happens when creating and loading textures 
 *                on the fly).
 *
 ******************************************************************************/
/******************************************************************************/
/*  INCLUDES                                                                  */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> 
#include <limits.h>

#include "vqcalc.h"
/******************************************************************************/
/*  DEFINES AND TYPEDEFS                                                      */
/******************************************************************************/
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

/*Max number of Quantized Vectors*/
#define MAX_CODES	 256       

/*
// Define our "max image" dimensions. Increase these if necessary.
// Ideally these should be completely dynamic.
*/
#define MAX_X_PIXELS 1024
#define MAX_Y_PIXELS 1024

#ifdef  DEBUG
	extern void myAssert(int, char * File, int line);
	#define ASSERT(X) {myAssert(X, __FILE__, __LINE__);}
#else
	#define ASSERT(X)
#endif
	
/*
// Define whether we do our maths using integer or float.
*/
#if 1
#define MATH_TYPE float
#else
#define MATH_TYPE int
#endif

/*
// set hardware endian
*/
#define LITTLE_ENDIAN 0
#define BIG_ENDIAN 1

#define COUNT_SEARCH 0
#define REJECT_METHOD 0


/*
// Do some reordering of the code book for architectures
// where the page size is small
*/
#define SMALL_PAGE_SIZE 0

/*
// This value terminates the iteration loop if the amount of
// improvement we are getting is too small to be of much use
*/
#define IMPROVEMENT_TOO_SMALL (0.005f)

#define START_DIFFUSION	(0.3f)

#define HARDWARE_PARAMS TRUE 

/*
// From now on, hardwire the dimensions of the vectors. For an
// RGB 2x2 this gives a vector length of 12.   Putting in an alpha
// component will make that 16.
*/
#define PIXEL_BLOCK_SIZE (2)
#define COMPONENTS_PER_PIXEL (4)
#define VECLEN (COMPONENTS_PER_PIXEL * PIXEL_BLOCK_SIZE * PIXEL_BLOCK_SIZE)

/*
// Define the size of the memory PAGEs relative to the size of a code. In
// particular, give how many codes will fit in a page, and the number
// of pages needed to store the max number of codes (round up if necessary)
*/
#define CODES_PER_PAGE (128)
#define MAX_CODEBOOK_PAGES	   ((MAX_CODES + (CODES_PER_PAGE - 1)) / CODES_PER_PAGE)

/*
// Define useful macros
*/
#define NEW(X) 	     	((X *) malloc (sizeof(X)))
#define NEW_ARRAY(X, N) ((X *) malloc (sizeof(X) * (N)))
#define RESIZE_ARRAY(PTR, X, N) (PTR = (X *) realloc (PTR, sizeof(X) * (N)))

#define SQ(X) ((X)*(X))

/* Define how we compute the image/vector score */
#define MEASURE_SMOOTHNESS 0
#define USE_AVERAGE_PER_PIXEL 0

/* Define the method used to throw out poor codes */
#define REJECT_CODES_BASED_ON_USAGE 0

/* Define which one we are using */
#define SEARCH_METHOD NEAREST_NEIGHBOUR_METHOD

/* Also define if we should test the method we have chosen against 
// the brute force solution */
#define CHECK_SEARCH_METHOD (0)

/* Define the Search Function as a macro */
#define FIND_CLOSEST_CODE NearestNeighbourFind
	
typedef struct {
	int			CodeIndex;
	/*this is the '1/2' distance (sort of): */
	MATH_TYPE	CutOffDistance; 
} NeighbourInfoStruct;


#define MAX_NEAREST_NEIGHBOURS (20)

typedef struct {
	int					NumNeighbours;
	NeighbourInfoStruct Neighbs[MAX_NEAREST_NEIGHBOURS];
} CodeNeighbourStruct;

	CodeNeighbourStruct		NearestNeighbours[ MAX_CODES] ;
	int						Repeats[ MAX_CODES] ;

#define GET_NEIGHBOUR_STATS 0

#if   GET_NEIGHBOUR_STATS
	int		NumDistanceCalcs;
	int		TotalSearches;
#endif

typedef int CodeReMapType[MAX_CODES];

typedef struct code_info {
	int code;
	int freq;
} CODE_INFO;


#ifndef UINT8
	typedef unsigned char UINT8;
#endif
#ifndef UINT32
	typedef unsigned long UINT32;
#endif

typedef struct
{
	UINT8 rgb[3];

}PIXEL_STRUCT;

/*
// Internal storage of an image
*/
typedef struct 
{
	int xDim, yDim;
	PIXEL_STRUCT *Pixels;	 
}IMAGE_STRUCT;

typedef struct 
{
    UINT8 *Pixels;
} ALPHA_STRUCT;

/*
// List of indices for the compressed image
*/
typedef struct 
{
	UINT8 *PixelCodes;
	 
}CODE_IMAGE_STRUCT;

/*
// A pixel vector just replaces an  [N][N][Colour_depth] block of
// pixels with a single dimension vector so that it is easier to
// iterate through the dimensions
*/
typedef struct
{
 	MATH_TYPE v[VECLEN];

}MT_PIXEL_VECT;

typedef struct
{
 	UINT8 v[VECLEN];

}BYTE_PIXEL_VECT;

/*
// A CODE Data Structure is used to keep "sets" of pixel vectors.
// It has a rep point, + stats on the max and min vectors it contains 
// etc
*/
typedef struct
{
	MT_PIXEL_VECT mtRepVector; /*The Vector used for this code*/

    /*Values used in computing a new Rep*/
	MT_PIXEL_VECT Sums;
	int		NumMembers;

	MT_PIXEL_VECT mtWorstMatchingVector;

    /* Min Dist to another code */ 
	MATH_TYPE  MinDist;

	MATH_TYPE  WorstDist;
	MATH_TYPE  TotalDist;
	MATH_TYPE  AdjustedScore;

	int 	   ReadOnly;
}CODE_DATA_STRUCT;


/*
// Declare the CodeBook type: The code book is just an
// array of vector data: Each element will eventually become
// a code used to compress
*/
typedef struct
{
	int NumUsedCodes;
	CODE_DATA_STRUCT Codes[MAX_CODES];
} CODE_BOOK_STRUCT;


/*
// Macro to keep the max and min of a set of values
*/
#define UpMaxMin(Val, Min, Max) \
  {if((Val)<(Min)) Min = Val;if((Val)>(Max)) Max = Val;}

/* 
// Define a Vector Format for the image
*/
#define MAX_IMAGE_VECTORS  (MAX_Y_PIXELS * MAX_X_PIXELS / 4)

typedef struct 
{
	int NumVects;
#if 1
	MT_PIXEL_VECT *mtVectors; 
#else
	BYTE_PIXEL_VECT *u8Vectors; 
#endif

}IMAGE_VECTOR_STRUCT;

typedef struct 
{
	int x;
	int y;
} POSITION_STRUCT, *PPOSITION_STRUCT;

typedef struct 
{
	int useage;
	POSITION_STRUCT position[1024];
	CODE_DATA_STRUCT psEntries[16];

} SUB_CODEBOOK_STRUCT, *PSUB_CODEBOOK_STRUCT;

typedef struct 
{
	 int ignore;
	 int order;
	 int used;
} CODEBOOK_ENTRY_INFO_STRUCT, *PCODEBOOK_ENTRY_INFO;


typedef struct
{
	float				gWeighting;
	IMAGE_STRUCT		*pImage;
	ALPHA_STRUCT		*pAlpha;
	IMAGE_VECTOR_STRUCT	*pImageVecs;
	CODE_IMAGE_STRUCT	*pImageCodes;
} MIPMAP_ENTRY;

typedef struct 
{
	int					numMipmapLevels;
	MIPMAP_ENTRY		mipEntry[20];
} MIPMAPS;

enum
{
	CBOptNone, /*really only for debug*/
	CBOptLow,
	CBOptMedium,
	CBOptHigh,
	CBOptVeryHigh,

	CBOptNotSet,

}CodeBookOptimModeEnum;
/*
// Dubious significance of names - could be wrong way around;
// one reverses alpha, one doesn't.
*/
enum __Alpha_Type {
	PVR1,
	PVR2
} Alpha_Type;

/******************************************************************************/
/*  GLOBALS                                                                   */
/******************************************************************************/

void BGRtoRGB( void *p1, int N);

int	 transp = 0;

const float PrecisionClamper[3][4] = { 
	{17.0f,17.0f,17.0f, 17.0f},  /*4444*/
	{ 8.22580645f, 8.22580645f, 8.22580645f, 255.0f}, /*5551*/
	{ 8.22580645f, 4.04761905f, 8.22580645f, 255.0f}  /*565x x not used*/
}; 

#ifdef  DEBUG
 int FullDebug = 0;
#endif

CODE_BOOK_STRUCT	*pCodeBk;
CODE_INFO			*pCodeList;
int					*pCodeFreq;

 int FilterWeights4x4[4][4] = 
	{{1, 2, 2, 1}, 
	 {2, 4, 4, 2},
	 {2, 4, 4, 2},
	 {1, 2, 2, 1}};

 int FilterWeights2x2[4][4] = 
	{{0, 0, 0, 0}, 
	 {0, 1, 1, 0},
	 {0, 1, 1, 0},
	 {0, 0, 0, 0}};

typedef float Mat16x16Type[VECLEN][VECLEN];

	const	CODE_BOOK_STRUCT	*pGlobalSearchedBook;

Mat16x16Type RGBToPerception;
Mat16x16Type PerceptionToRGB;


/* rgb2yiq 111 = 100 correct */

const float RGBtoYIQ[3][3] = 
{{ 0.3f,	 0.59f,		 0.11f},
 { 0.6f,	-0.28f,		-0.32f},
 { 0.21f,	-0.52f,		 0.31f}};

/* yiq2rgb 100 = 111 correct */

const float YIQtoRGB[3][3] = 
{{ 1.0f,	 0.948f,	 0.624f},
 { 1.0f,	-0.276f,	-0.640f},
 { 1.0f,	-1.105f,	 1.730f}};


float YIQWeightings[3] ;

/* s2f 1111 = 2 0 0 0 correct */

const float SpaceToFreq[4][4] =
{{ 0.5f,	 0.5f,		0.5f,		0.5f}, 
 {-0.5f,	-0.5f,		0.5f,		0.5f}, 
 {-0.5f,	 0.5f,	   -0.5f,		0.5f}, 
 {-0.5f,	 0.5f,	    0.5f,	   -0.5f}};

/* this is a scaled transpose of the above = inverse since orthogonal */

/* f2s 2000 = 1111 correct */ 

const float FreqToSpace[4][4] =
{{ 0.5f,	-0.5f,	   -0.5f,	   -0.5f},
 { 0.5f,	-0.5f,	    0.5f,	    0.5f},
 { 0.5f,	 0.5f,	   -0.5f,	    0.5f},
 { 0.5f,	 0.5f,	    0.5f,	   -0.5f}};


float FreqWeightings[4] = {1.0f,   0.8f, 0.8f, 0.8f};



/******************************************************************************/
/*  LOCAL PROTOTYPES                                                          */
/******************************************************************************/
void		highQVq( 	MIPMAPS *pMipmaps, 	CODE_BOOK_STRUCT *pCodeBook,	
							int DoDiffusion, int NumIterations, int nFormat,
							int MaxCodes, float *pFinalErrorVal, float PercentError	);

void	ReOrderCodebook(MIPMAPS *pMipmaps, CODE_BOOK_STRUCT *pCodeBook, 
							 int OptimRecursionDepth);

void	ReOrderCodebookSimple(MIPMAPS *pMipmaps, CODE_BOOK_STRUCT *pCodeBook);

void	GenerateReducedImages(MIPMAPS *pMipmaps, int filtermode );

void	GenerateWholeInitialBook(MIPMAPS *pMipmaps, CODE_BOOK_STRUCT * pBook, int MaxCodes);

void	GetStats(MIPMAPS *pMipmaps,	CODE_BOOK_STRUCT *pBook, float *Error);
 
void	MatrixMatrixMul( Mat16x16Type, const Mat16x16Type , const Mat16x16Type );
void	MatrixVectorMul( MT_PIXEL_VECT *, const Mat16x16Type, const MT_PIXEL_VECT *);
void	SetIdentMatrix( Mat16x16Type );
void	SetZeroMatrix( Mat16x16Type );
void	GenerateMappingMatrices(ColourSpaceModeType , int );

UINT8	add(UINT8 a, int b);
void	Dither( PIXEL_STRUCT *rgb, UINT8 *pAlpha,  int nFormat, int nTranslucent, int xDim, int yDim);
void	Dither4Square( PIXEL_STRUCT *rgb_data, UINT8 *pAlpha, 
							   int nFormat, int nTranslucent, int xDim, int yDim);
void	ConvertBitMapToVectors ( MIPMAPS *pMipmaps);
void	ConvertCodeBookToRGB   ( CODE_BOOK_STRUCT *pBook, int nFormat) ;
void	ConvertCodeBookFromRGB ( CODE_BOOK_STRUCT *pBook ) ;
void	Clamp ( CODE_BOOK_STRUCT * pBook,  int nFormat) ;
void	ReconstructCompressedImage (	MIPMAPS	*pMipmaps,	const	CODE_BOOK_STRUCT * pBook,
												int		ShowPageBreaks);
void	ViewCompressedImage(	MIPMAPS *pMipmaps,	const CODE_BOOK_STRUCT * pBook,
										int		   ShowPageBreaks);

void	ExpSpace( MT_PIXEL_VECT *);
void	UnExpSpace( MT_PIXEL_VECT *);

float	EvaluateScore( CODE_BOOK_STRUCT *pBook) ;
void	SplitWorst ( CODE_BOOK_STRUCT * pBook, int MaxCodes) ;
float	NearestNeighbourFind ( const MT_PIXEL_VECT *pVector, UINT8 * pCodeChosen) ;
void	SetUpNearestNeighbours ( CODE_BOOK_STRUCT * pBook) ;
int		NeighbourCompare ( const void *p1, const void *p2);

#if  		REJECT_CODES_BASED_ON_USAGE
	int		DeleteDeadCodes ( CODE_BOOK_STRUCT *pCodeBook, int	RemoveLowUse, int MaxCodes) ;
#else
	int		DeleteDeadCodes ( CODE_BOOK_STRUCT *pCodeBook, float ErrCutoff, int MaxCodes) ;
#endif

void	WriteShortMem( unsigned char *ucP, int nVal, int nEndian );
void	Deinterleave( int addr, int *x, int *y ) ;

int		CodeCompare( const void *p1, const void *p2);

int		WriteVqfMemory(	void *MemoryOut, int nFormat, MIPMAPS *pMipmaps, 
						CODE_BOOK_STRUCT *pCodeBook,int	nNumCodes,	int bAlphaSense);
						
void	ReMapTextureEncoding(CodeReMapType ReMappingTable, MIPMAPS *pMipmaps,
									   CODE_BOOK_STRUCT *pBook);	
/******************************************************************************/
/*  EXTERNAL FUNCTIONS                                                        */
/******************************************************************************/
int CreateVq(	void*	InputArrayRGB,
										void*	InputArrayAlpha,
										void*	OutputMemory, 
										int		nWidth,
										int		bMipMap,
										int		bAlphaOn,
										int		bDither,
										int		nNumCodes,
										int		nColourFormat,
										int		nNumIterations,
										int		bDoFreq,
										float	fColourWeights[3],
										float	fFreqWeights[4],
										ColourSpaceModeType	ColSpace,
										int		bAlphaSense,
										float	fPercentError,
										float	*fErrorFound
							)
{

	ALPHA_STRUCT		AlphaImage;
	IMAGE_STRUCT		SourceImage;
	CODE_BOOK_STRUCT	CodeBook;
	CODE_BOOK_STRUCT	*pCodeBook;
	MIPMAPS				pMipmaps[1];

	void	*pArrayAlpha = NULL;
	void	*InputRGBCopy = NULL;
	void	*InputAlphaCopy = NULL;

	int		i;
	int		nReturnValue = VQ_OK;


	/* Set global translucency flag */
	transp = bAlphaOn;

	/* Set Colour weigthings */
	for ( i=0; i<3; i++)
		YIQWeightings[i] = fColourWeights[i];
	/* Set Freq weightings */
	for ( i=0; i<4; i++)
		FreqWeightings[i] = fFreqWeights[i];


	pCodeBook = &CodeBook;

	/* Has the App malloced the memory yet? */
	if ( OutputMemory == NULL) {
		
		/* Work out memory needed */
		int nMemoryNeeded = 0;

		/* Header of 12 bytes */
		nMemoryNeeded = 12;
		/* Codes */
		nMemoryNeeded += 8 * nNumCodes;
		/* Indices */
		/* lower mimpmap levels */
		if ( bMipMap) {
			/* Do 1x1 */
			nMemoryNeeded++;
			/* Start loop at 2x2 pix block = 1x1 code */
			for ( i=1; i < nWidth/2; i*=2)
			{
				nMemoryNeeded+= i*i;
			}
		}
		/* top one */
		nMemoryNeeded+= nWidth * nWidth / 4;

		/* Exit function with number of bytes to allocate before coming
		   here again!
		 */
		return nMemoryNeeded;
	}
	/*
	// Assume that OutputMemory points to valid memory for vqf file ( in memory)
	// so BEGIN:
	*/
	/* Make transformation matrices */
	if ( bDoFreq) 
		GenerateMappingMatrices( ColSpace, TRUE);
	else
		GenerateMappingMatrices( ColSpace, FALSE);

	
	if ( bAlphaOn == 0) {
		
		unsigned char *ucPtr;
		/* Allocate memory */
		pArrayAlpha = (unsigned char *)malloc( nWidth * nWidth);
		if ( pArrayAlpha == NULL) {
			nReturnValue = VQ_OUTOFMEMORY;
			goto cleanup_and_exit;
		}
		/* Set to zero */
		ucPtr = pArrayAlpha;
		for ( i=0; i<nWidth*nWidth; i++)
			*ucPtr++ = 0;
		/* Use this memory */
		
	} else
	{
		/* Use given alpah */
		pArrayAlpha = InputArrayAlpha;
	}

	AlphaImage.Pixels = pArrayAlpha ;

	/* Convert BGR to RGB */
	BGRtoRGB( InputArrayRGB, nWidth*nWidth );
	
	SourceImage.Pixels = InputArrayRGB;
	SourceImage.xDim = nWidth;
	SourceImage.yDim = nWidth;

	pMipmaps->mipEntry[0].pImage = &SourceImage;
	pMipmaps->mipEntry[0].pAlpha = &AlphaImage;
		
	/* Generate the mipmap levels if necessary */
	if ( bMipMap ) 
		GenerateReducedImages ( pMipmaps, TRUE);
	else 
		pMipmaps->numMipmapLevels =	1;
		
	if ( bDither) 
	{
		/* Make a copy of original image */
		InputRGBCopy = (unsigned char *)malloc( 3*nWidth*nWidth);
		
		if ( bAlphaOn)
		InputAlphaCopy = (unsigned char *)malloc( nWidth*nWidth);
		
		if ( InputRGBCopy == NULL || ( InputAlphaCopy == NULL && bAlphaOn)) {
			nReturnValue = VQ_OUTOFMEMORY;
			goto cleanup_and_exit;
		}
		
		memcpy( InputRGBCopy, InputArrayRGB, 3*nWidth*nWidth);
		if ( bAlphaOn)
			memcpy( InputAlphaCopy, InputArrayAlpha, nWidth*nWidth);
	
		pMipmaps->mipEntry[0].pImage->Pixels = InputRGBCopy; 
		if ( bAlphaOn)
			pMipmaps->mipEntry[0].pAlpha->Pixels = InputAlphaCopy;

		/* Dither all the levels */
		
		for ( i=0; i<pMipmaps->numMipmapLevels; i++)
					Dither4Square(		pMipmaps->mipEntry[i].pImage->Pixels,
						pMipmaps->mipEntry[i].pAlpha->Pixels,
						nColourFormat,
						bAlphaOn,
						pMipmaps->mipEntry[i].pImage->xDim,
						pMipmaps->mipEntry[i].pImage->yDim
					);
	
	} 


	/* Generate the 16D vectors representing a 2x2 block for the algortihm */
	ConvertBitMapToVectors ( pMipmaps);

	/* Convert back RGB to BGR */
	BGRtoRGB( InputArrayRGB, nWidth*nWidth);

	/* Do the VQ compression */
	highQVq (	pMipmaps,		pCodeBook,	0 , 
				nNumIterations, nColourFormat, nNumCodes, 
				fErrorFound, fPercentError);

	/* Convert the code book back from perception space to RGB clamped space */
	ConvertCodeBookToRGB ( pCodeBook, nColourFormat) ;
	Clamp ( pCodeBook, nColourFormat) ;

	/*
	// Do some reordering of the code book for architectures
	// where the page size is small
	*/
#if SMALL_PAGE_SIZE
	ReOrderCodebookSimple(pMipmaps, pCodeBook);
#endif

	/* Not interested in going back to images; just write vqf file to memory: */
	
	WriteVqfMemory(		OutputMemory, 
						nColourFormat, 
						pMipmaps, 
						pCodeBook,
						nNumCodes,
						bAlphaSense
						);


cleanup_and_exit:
	
	/* Free our temporary alpha array if we made it */
	if ( bAlphaOn == 0) {
		if ( pArrayAlpha)
			free( pArrayAlpha);
	}

	if ( InputRGBCopy)		free ( InputRGBCopy);
	if ( InputAlphaCopy)	free ( InputAlphaCopy);

	return nReturnValue;

}
/******************************************************************************/
/*  LOCAL FUNCTIONS                                                           */
/******************************************************************************/
void BGRtoRGB( void *p1, int N)
{
	int i;
	unsigned char temp, *p;

	p = ( unsigned char*) p1;

	for ( i=0; i<N; i++)
	{
		temp = *p;
		*p = *(p+2);
		p++;
		p++;
		*p++ = temp;
	}
}
/******************************************************************************
 * From			: vq.c
 * Title		: Vector Quantisation Compression Code
 * Author		: Julian Hodgson.
 * Created		: 17/03/1997
 ******************************************************************************/
void highQVq( 	MIPMAPS *pMipmaps, 
				CODE_BOOK_STRUCT *pCodeBook,	
				int DoDiffusion, 
				int NumIterations, 
				int nFormat,
				int MaxCodes,
				float *pFinalErrorVal,
				float PercentError)
{
	float Error=0;
	/*int StartDiffusion = 0;*/
	int KillFactorCount=0;
	int DeletionsDone=0;
	float LastError=0;
	float OverallScore=0;
	IMAGE_VECTOR_STRUCT	*pImageVecs;


	char buffer[50];
	int Iteration=0;
	
	
	pImageVecs = (IMAGE_VECTOR_STRUCT*)pMipmaps->mipEntry[0].pImageVecs;
	
	/* ACTUALLY */
	/* Base all codes on image in one go: */

	GenerateWholeInitialBook( pMipmaps, pCodeBook, MaxCodes);


	SetUpNearestNeighbours(pCodeBook);

	GetStats(pMipmaps, pCodeBook, &Error); 
	OverallScore = EvaluateScore(pCodeBook);

	/*
	// Iterate, doing a General Lloyd Algorithm to find better representative codes
	*/
	LastError = 100000.0f;
	KillFactorCount = 1;
	DeletionsDone = 0;
	for(Iteration = 1; Iteration <= NumIterations; Iteration++)
	{
		

		/*
		// The following defines the method used to chuck-out codes.
		*/
#if   REJECT_CODES_BASED_ON_USAGE
		int KillFactor=0;
		if(pCodeBook->NumUsedCodes==MaxCodes)
		{
		    /*
			// A function that just decays away every iteration
			*/
			KillFactor = 
			    (pImageVecs->NumVects / (((KillFactorCount /2) + 1) * MaxCodes));
			if(KillFactor < 0)
			{
				KillFactor = 0;
			}
			KillFactorCount++;
			KillFactor = 10;

			/*
			// determine what codes we will weed out by their usage. Base this
			// on the iteration count. At first we'll kill off codes that get used
			// less than 20% of the time and then gradually decrease this.
			//
			// Make the last few iterations not kill off any codes.
			*/
			KillFactor = (int)
			  (((float) (NumIterations- Iteration - 2) /
						 (float) (NumIterations - 2) * 0.2f ) 
					     * (float) MaxCodes);
			
			if(KillFactor < 0)
			{
				KillFactor = 0;
			}
		}
		else
		{
			KillFactor = 0;
		}

		/*
		// Kill off the codes which are not contributing (much) to
		// the compression
		*/

		DeletionsDone = DeleteDeadCodes(pCodeBook, KillFactor , MaxCodes);

#else
		/*
		// Dont kill off any used codes until we have the maximum number
		// we are after. Also give it time to settle after killing a code,
		// and also if we are nearing the maximum number of iterations, then
		// don't suddenly make a backwards step!
		*/

		/* DONT KILL ANY CODES */
		
	
		DeletionsDone = DeleteDeadCodes(pCodeBook, 0.0f,
					  MaxCodes);
	

#endif /* REJECT_CODES_BASED_ON_USAGE*/

		/*
		// Split the worst codes
		*/
		SplitWorst(pCodeBook, MaxCodes);




#if   GET_NEIGHBOUR_STATS
		NumDistanceCalcs = 0;
		TotalSearches = 0;
#endif

		/*
		// recompute the nearest neighbour table
		*/
		SetUpNearestNeighbours(pCodeBook);

		/*
		// re-sort the image's vectors into the set of codes
		*/
		if(DoDiffusion)/* && StartDiffusion)*/
		{
			/*Killed the diffusion one for the moment*/
			/*GetStatsWithDiffusion(pMipmaps, pCodeBook, &Error);*/
			printf("No diffusion version at the moment\n");
			GetStats(pMipmaps, pCodeBook, &Error); 
		}
		else
		{
			GetStats(pMipmaps, pCodeBook, &Error); 
		}


		OverallScore = EvaluateScore(pCodeBook);
		
		sprintf( buffer, "%f", sqrt(OverallScore/VECLEN));
		


#if   GET_NEIGHBOUR_STATS
		printf("Av Distance calcs Per Vector :%5.2f\n", 
							(float) NumDistanceCalcs / (float)TotalSearches);
#endif



/*		if((!DeletionsDone) && (fabs(LastError - Error) < IMPROVEMENT_TOO_SMALL))
*/
		if ( ( !DeletionsDone) && ( fabs( 100 * ( LastError - Error) / Error) < PercentError) )
		{
			break;
		}

		LastError = Error;

	}

	printf("Number of codes Used:%d\n", pCodeBook->NumUsedCodes);

	*pFinalErrorVal = Error;
}

 void GenerateWholeInitialBook(MIPMAPS *pMipmaps, 
								CODE_BOOK_STRUCT * pBook, int MaxCodes)
{
	int IxDim=0, IyDim=0;
	int IxBlkSize=0, IyBlkSize=0;
	int i, j, k, ii, jj, index = 0, code_index = 0;

	CODE_DATA_STRUCT Block;
	MT_PIXEL_VECT *pVect;
	IMAGE_STRUCT *pImage;
	ALPHA_STRUCT *pAlpha;

	/* Make sure all codes are initialised as Read Only */
	Block.ReadOnly = FALSE;
	
	IxDim = pMipmaps->mipEntry[0].pImage->xDim / PIXEL_BLOCK_SIZE;
	IyDim = pMipmaps->mipEntry[0].pImage->yDim / PIXEL_BLOCK_SIZE;

	IxBlkSize = ( int) ( IxDim / ( 1 + ( int) sqrt( MaxCodes) )  );
	IyBlkSize = ( int) ( IyDim / ( 1 + ( int) sqrt( MaxCodes) )  );

/* Make sure non-zero ! */
	
	if ( IxBlkSize==0)
		IxBlkSize = 1;
	if ( IyBlkSize==0)
		IyBlkSize = 1;

	/* Set number of used codes to max codes (soon will be) */ 

	pBook->NumUsedCodes = MaxCodes;
	pVect = pMipmaps->mipEntry[0].pImageVecs->mtVectors;

	code_index = 0;

	for ( j = 0; j < IyDim; j += IyBlkSize)
	{

		for ( i = 0; i < IxDim; i += IxBlkSize)
	   	{

		    /* Set Block to zero */

			for ( k = 0; k < VECLEN ; k++)
			{
				Block.Sums.v[k] = (MATH_TYPE) 0;
			}

			/* Collect all image vectors in block */

			for ( jj = 0; jj < IyBlkSize; jj++)
			{
				index = ( j + jj) * IxDim +  i ;

				for ( ii = 0; ii < IxBlkSize; ii++)
				{
					
					for ( k = 0; k < VECLEN; k++)
					{
						Block.Sums.v[k] += pVect[ index].v[k];
					}

					index++ ;
				}

			}


			/* Update Rep Vector etc.. */

			Block.NumMembers = IxBlkSize * IyBlkSize;
			
			for ( k = 0; k < VECLEN; k++)
			{
			
				 Block.mtRepVector.v[k] = ( Block.Sums.v[k] / ( ( MATH_TYPE) Block.NumMembers ));

			}

			pBook->Codes[ code_index] = Block;


			/* If we have filled our code book then exit */

			if ( code_index >= MaxCodes - 1 ) { goto finished; }

			code_index++;

		}

	}

	finished:
;

	/* If mipmaps then put last code as lowest mipmap level - we need a good match! */
	/* Also for 2x2 mipmap level: in total this only reserves 2 codes. */

	if ( pMipmaps->numMipmapLevels != 1) {
		
		code_index = MaxCodes - 1;
		pImage = pMipmaps->mipEntry[ pMipmaps->numMipmapLevels - 1].pImage ;
		pAlpha = pMipmaps->mipEntry[ pMipmaps->numMipmapLevels - 1].pAlpha ;
		
		
		pBook->Codes[ code_index].mtRepVector = 
			pMipmaps->mipEntry[ pMipmaps->numMipmapLevels-1].pImageVecs->mtVectors[0];
		/* Set as READ ONLY */
		pBook->Codes[ code_index].ReadOnly = TRUE;

		code_index = MaxCodes - 2;
		pImage = pMipmaps->mipEntry[ pMipmaps->numMipmapLevels - 2].pImage ;
		pAlpha = pMipmaps->mipEntry[ pMipmaps->numMipmapLevels - 2].pAlpha ;

		pBook->Codes[ code_index].mtRepVector = 
			pMipmaps->mipEntry[ pMipmaps->numMipmapLevels-2].pImageVecs->mtVectors[0];
		/* Set as READ ONLY */
		pBook->Codes[ code_index].ReadOnly = TRUE;

	}

}





/*************************************************
//
// Given the set of rep vectors and the image, this steps
// through all the vectors in the image, assigning them to
// their closest vector. This then gives us stats so we can
// regenerate a new/better code book.
//
*************************************************/


 void GetStats(	MIPMAPS *pMipmaps,
						CODE_BOOK_STRUCT *pBook,
	            		float *Error)
{
	int VecCount=0, i, k, l;
	MATH_TYPE LocalError=0;
	int totalVecs = 0;
	CODE_DATA_STRUCT *pBestCode;
	CODE_IMAGE_STRUCT *pImageCodes;
	IMAGE_VECTOR_STRUCT *pImageVecs;
	UINT8 *pSavedPixelsCode;
	const MT_PIXEL_VECT *pVect;

	/*
	// reset the current stats for all the code vectors
	*/
	pBestCode = pBook->Codes;
	*Error = 0.0f;

	for(k = 0; k < pBook->NumUsedCodes; k ++, pBestCode ++)
	{
		/*
		// reset the max and Mins, and the sum of all vectors etc
		*/
		for(i = 0; i < VECLEN; i++)
		{
			pBestCode->Sums.v[i] = (MATH_TYPE) 0;
		} /*end for i*/

		pBestCode->NumMembers = 0;

		pBestCode->WorstDist = (MATH_TYPE) 0;
		pBestCode->TotalDist = (MATH_TYPE) 0;
	}

	/*
	// Set up the search routine's global code book pointer
	*/
	pGlobalSearchedBook = pBook;

	/*
	// Step through all the image's vectors
	*/	
	for(l = 0; l < pMipmaps->numMipmapLevels; l++)
	{
		pImageVecs = pMipmaps->mipEntry[l].pImageVecs;
		pImageCodes = pMipmaps->mipEntry[l].pImageCodes;
		pVect = pImageVecs->mtVectors;
						
		pSavedPixelsCode = pImageCodes->PixelCodes;

#if  COUNT_SEARCH

		num_brute = brute_tests = num_neighb = neighb_tests = 0;

#endif

		for(VecCount = pImageVecs->NumVects; VecCount!=0; VecCount--, pVect++)
		{
			/*
			// Find the closest, and update its stats. read the previous one.
			*/
			LocalError = FIND_CLOSEST_CODE(pVect, pSavedPixelsCode);

			*Error += LocalError;
			pBestCode = pBook->Codes + *pSavedPixelsCode;

			pSavedPixelsCode++;


			/*
			// Update the statistics
			*/
			for(i = 0; i < VECLEN; i++)
			{
				pBestCode->Sums.v[i] += pVect->v[i];

			}/*end for i*/

			/*
			// Get the worst vector so far that still matches this code
			*/
			if(pBestCode->WorstDist < LocalError)
			{
				pBestCode->WorstDist = LocalError;

				pBestCode->mtWorstMatchingVector = *pVect;
			}

			/*
			// Sum up the total error on this code
			*/
			pBestCode->TotalDist += LocalError;

			pBestCode->NumMembers++;
	
		}/*end for VecCount*/

		totalVecs += pImageVecs->NumVects;
	}/*end for mip-map level*/

#if  COUNT_SEARCH

	printf("%d resorted to brute test, average %f dist calcs\n",
				num_brute, (float) brute_tests / ( (float) num_brute+0.0001));

	printf("%d were found as neigbours, average %f dist calcs\n",
			    num_neighb, (float) neighb_tests / ( (float) num_neighb+0.0001));

#endif

	/*
	// get the RMS of the errors. (Note that the returned
	// error value is already a square)
	*/
	if( transp)
		*Error = (float) sqrt(*Error/((float)(totalVecs * 16)));
	else
		*Error = (float) sqrt(*Error/((float)(totalVecs * 12)));
	 
	/*
	// recompute the rep colour, by taking the average
	*/
	pBestCode = pBook->Codes;
	for(k = 0; k < pBook->NumUsedCodes; k ++, pBestCode ++)
	{
		if(pBestCode->NumMembers)
		{
			/* Skip if READ ONLY CODE */
			if (pBestCode->ReadOnly)
				continue;
			/*
			// Compute the averages
			*/
			for(i = 0; i < VECLEN; i++)
			{
				pBestCode->mtRepVector.v[i] = (MATH_TYPE)
				 ((pBestCode->Sums.v[i] ) / 
										   pBestCode->NumMembers);
			}/*end for i*/
		}/*end if code is used at all*/

	}
}




/*************************************************
//
// Converts the "total" score into a different metric.
//
*************************************************/

 float EvaluateScore(CODE_BOOK_STRUCT * pBook)
{
	int codeIndex = 0;
	float OverallScore = 0.0f;
	int totalVecs =0;
	CODE_DATA_STRUCT *pCode;

	/*
	// Step through all the codes
	*/
	pCode = pBook->Codes;
	for(codeIndex = 0; codeIndex < pBook->NumUsedCodes; codeIndex ++, pCode++)
	{
		float Score=0;
#if   MEASURE_SMOOTHNESS
		int j;
		int DifferenceSum = 0;
#endif

		/*
		// Initially set Score to be the total distance
		*/
		Score = pCode->TotalDist;

#if   MEASURE_SMOOTHNESS
		for(j = 0; j < VECLEN / 4; j++)
		{
			int min = 255;
			int max = 0;
			
			UpMaxMin(pCode->u8RepVector.v[j], min, max);
			UpMaxMin(pCode->u8RepVector.v[j+4], min, max);
			UpMaxMin(pCode->u8RepVector.v[j+8], min, max);
			UpMaxMin(pCode->u8RepVector.v[j+12], min, max);
			
			DifferenceSum += max-min;
		}
		
		if(DifferenceSum > 30)
		{
			DifferenceSum = 30;
		}
		/*
		// Come up with some sort of weighting metric....
		//
		// Those with very low frequency content will be weighted more highly
		*/
		Score *=  (30*30+4.0) / (DifferenceSum * DifferenceSum + 4.0f);
#endif

#if  USE_AVERAGE_PER_PIXEL
		/*
		// Divide through by the number of members to get the average
		// error per vector for this code
		*/
		OverallScore+= Score;
		Score /= (1.0f + pCode->NumMembers);

#else
		OverallScore+= Score;
#endif

		pCode->AdjustedScore = Score;
		totalVecs+= pCode->NumMembers;

	}/*end for step through codes*/


	/*
	// Compute the overal scene score
	*/
	OverallScore /= totalVecs;


	return OverallScore;
} 


/*************************************************
//
// This function splits the "worst" of the sets into two, and 
// regenerates information
//
*************************************************/



 void SplitWorst(CODE_BOOK_STRUCT * pBook,
						int MaxCodes)
{
	int i=0, codeIndex=0, WorstCodeIndex=0;
	float WorstSize=0;

	CODE_DATA_STRUCT *pCode, *pCodeToSplit;

	/*
	// Loop through finding a new code to split till we either
	// have the maximum number of codes OR we've split all that
	// we can
	*/
	while(pBook->NumUsedCodes < MaxCodes)
	{
		WorstSize = 0.0f;
		pCodeToSplit = NULL; 
		pCode = pBook->Codes;

		WorstCodeIndex = 0;
		/*
		// Find the most suitable code to split.
		*/
		for(codeIndex = 0; codeIndex < pBook->NumUsedCodes; codeIndex ++, pCode++)
		{
			/*
			// If this is worse...
			*/			
			if ( (pCode->AdjustedScore > WorstSize) && (pCode->ReadOnly == FALSE) )
			{
				WorstSize  = pCode->AdjustedScore;
				pCodeToSplit=pCode;
				/* For Debug */
				WorstCodeIndex = codeIndex;
			}

		}/*end for step through codes*/

		/*
		// If nothing is splitable, get out of here
		*/
		if(pCodeToSplit == NULL)
		{
			return;
		}
		/*
		// Else split this one, and then mark it so it won't happen again
		//
		// Ok, "split" the worst set, by moving its rep position to
		// create a new set.
		// Get a pointer to the free code.
		//
		// Mark the Score's as Zero, so that we don't consider them again.
		*/
		pCodeToSplit->AdjustedScore= 0.0f;
		pBook->Codes[pBook->NumUsedCodes].AdjustedScore =0.0f;

		pCode = pBook->Codes + pBook->NumUsedCodes;
		pBook->NumUsedCodes ++;

		/*
		// Produce a new representative by choosing a point closer to the
		// worst matching one.
		*/
		*pCode = *pCodeToSplit;

		for(i = 0; i < VECLEN; i++)
		{

			pCode->mtRepVector = pCodeToSplit->mtWorstMatchingVector;
		
		}/*end for i*/

	}/*end while*/

} 



/*************************************************
//
//SetUpNearestNeighbours
//
*************************************************/
 void SetUpNearestNeighbours( CODE_BOOK_STRUCT * pBook)
{
	int i, j, k, count=0;
	CODE_DATA_STRUCT *pCodeI;
	CODE_DATA_STRUCT *pCodeJ;

	MT_PIXEL_VECT *codeI, *codeJ ;

	CodeNeighbourStruct *pCodesNs;

	ASSERT(pBook->NumUsedCodes > 0);

	/* Set up repeated code table */
	for ( i = 0; i < MAX_CODES; i++)
		Repeats[ i] = 0;

	/*
	// Step though all the codes
	*/
	pCodeI = pBook->Codes;
	pCodesNs = NearestNeighbours;

	for(i = 0; i < pBook->NumUsedCodes; i++, pCodeI++, pCodesNs++)
	{
		NeighbourInfoStruct *pNeighDetails;
		MATH_TYPE Distance=0, WorstDistance=0, MinDistance=0;
		int WorstDistancePos=-1;		/*initialise to stop warnings*/

		codeI	 = & ( pCodeI->mtRepVector);
		/*
		// Initialise this code's neighbour table to be empty
		*/
		pCodesNs->NumNeighbours = 0;

		/*
		// And initialise the worst distance in the set
		*/
		WorstDistance = (MATH_TYPE) -1;

		/*
		// Initialise minimum distance
		// = largest possible seperation
		*/
		MinDistance = (MATH_TYPE) 1048576000.0;

		/*
		// Measure the distance to each of the other codes
		*/
		pCodeJ = pBook->Codes;
		for(j = 0; j < pBook->NumUsedCodes; j++, pCodeJ++)
		{
			if(i == j)
			{
				continue;
			}

			/*
			// measure the distance between the two
			*/
			codeJ	 = & ( pCodeJ->mtRepVector);
			
			{
		
			MATH_TYPE sub1, sub2, sub3, sub4, tmp1, tmp2, tmp3, tmp4;

			sub1 = codeJ->v[0] - codeI->v[0];	
			sub2 = codeJ->v[1] - codeI->v[1];		
			sub3 = codeJ->v[2] - codeI->v[2];		
			sub4 = codeJ->v[3] - codeI->v[3];		
			
			tmp1 = sub1*sub1;
			tmp2 = sub2*sub2;
			tmp3 = sub3*sub3;
			tmp4 = sub4*sub4;

			Distance = tmp1+tmp2+tmp3+tmp4;

			sub1 = codeJ->v[4] - codeI->v[4];		
			sub2 = codeJ->v[5] - codeI->v[5];
			sub3 = codeJ->v[6] - codeI->v[6];		
			sub4 = codeJ->v[7] - codeI->v[7];
			
			tmp1 = sub1*sub1;
			tmp2 = sub2*sub2;
			tmp3 = sub3*sub3;	
			tmp4 = sub4*sub4;		

			Distance += tmp1+tmp2+tmp3+tmp4;
			
			sub1 = codeJ->v[8] - codeI->v[8];		
			sub2 = codeJ->v[9] - codeI->v[9];		
			sub3 = codeJ->v[10] - codeI->v[10];	
			sub4 = codeJ->v[11] - codeI->v[11];	

			tmp1 = sub1*sub1;
			tmp2 = sub2*sub2;
			tmp3 = sub3*sub3;	
			tmp4 = sub4*sub4;		

			Distance += tmp1+tmp2+tmp3+tmp4;

			sub1 = codeJ->v[12] - codeI->v[12];	
			sub2 = codeJ->v[13] - codeI->v[13];	
			sub3 = codeJ->v[14] - codeI->v[14];	
			sub4 = codeJ->v[15] - codeI->v[15];	
			
			tmp1 = sub1*sub1;
			tmp2 = sub2*sub2;
			tmp3 = sub3*sub3;	
			tmp4 = sub4*sub4;		

			Distance += tmp1+tmp2+tmp3+tmp4;
			}

#if  GET_NEIGHBOUR_STATS
			NumDistanceCalcs ++;
#endif

			/*
			// We want the halfway distance, but because we are working with the
			// square of the distance, we need to take a 1/4 not a 1/2
			*/
			Distance /= (MATH_TYPE) 4;

			/* Update MinDistance if necessary */
			if ( Distance < MinDistance) { MinDistance = Distance; }

			if ( Distance == 0.0f)
				if ( i < j)
				{
					/* These two codes are identical so mark one of them down			*/
					/* This is done in such a way ( since i < j) that in the end,		*/
					/* even if there is more than one repeated code, only one code		*/
					/* will not be marked for deletion - the first or last occurence,	*/
					/* I can't remember which.											*/
					Repeats[ i] = 1;
					count++;
				}

			/*
			// if we haven't filled the table, put this one in
			*/
			if(pCodesNs->NumNeighbours < MAX_NEAREST_NEIGHBOURS)
			{
				/*
				// get access to this the next free neighbour slot of this code
				*/
				pNeighDetails = pCodesNs->Neighbs + pCodesNs->NumNeighbours;

				pNeighDetails->CodeIndex = j;
				pNeighDetails->CutOffDistance = Distance;

		 		/*
				// Is this the furthest so far?
				*/
				if(Distance > WorstDistance)
				{
					WorstDistance = Distance;
					WorstDistancePos = pCodesNs->NumNeighbours;
				}

				pCodesNs->NumNeighbours++;
			}
			/*
			// Else see if this is better than what we currently have.
			*/
			else if(Distance < WorstDistance)
			{
				/*
				// Find the neighbour with the worst Distance
				*/
				pNeighDetails = pCodesNs->Neighbs + WorstDistancePos;

				ASSERT(pNeighDetails->CutOffDistance == WorstDistance);

				/*
				// replace the worst one with the new neighbour
				*/
				pNeighDetails->CutOffDistance = Distance;
				pNeighDetails->CodeIndex	  = j;

				/*
				// Now search through the lot and find the new worst distance
				*/
				WorstDistance = 0.0f;
				pNeighDetails = pCodesNs->Neighbs;
				for(k = 0; k < MAX_NEAREST_NEIGHBOURS; k++, pNeighDetails++)
				{
					if(WorstDistance < pNeighDetails->CutOffDistance)
					{
						WorstDistancePos = k;
						WorstDistance = pNeighDetails->CutOffDistance;
					}
				}/*end for k  - stepping through neighbours*/

			}/*end if new neighbour is closer than at least one of the others*/
		}/*end for j : stepping through all the other codes*/

		pCodeI->MinDist = MinDistance;

		/*
		// Now sort the neighbours into increasing order of distance
		*/
		qsort( pCodesNs->Neighbs, 
			   pCodesNs->NumNeighbours, 
			   sizeof(NeighbourInfoStruct),
			   NeighbourCompare);

	}/*end for i - stepping through all the codes */
}




/* ////////////////////////////////////
// Nearest Neighbour find:Given the Vector etc, get
// the closest (within reason) matching
// code.
//
// We start with the previously chosen code, since this is likely
// to be a good starting point, and then see if we can PROVE that this 
// is the best code, by showing that it is closer to this code than any
// of its neighbours.
// If, however, we find that a neighbour is closer, we move to it instead.
// To stop us retesting a code, set up an boolean array of Tested/Untested.
//////////////////////////////////// */

 float NearestNeighbourFind(const MT_PIXEL_VECT *pVector,
										          UINT8 * pCodeChosen)
{
	const CODE_DATA_STRUCT *pBCodeSF, *pTmpCode;

	CodeNeighbourStruct *pCodesNs;
	NeighbourInfoStruct *pNeighDetails;

	const MT_PIXEL_VECT *code;

	int		  BestCodeSoFar=0;
	MATH_TYPE BestDistSoFar=0;
//	MATH_TYPE Distance;
	int i, k;



	 /*These are bit packed to keep cache and setup requirements low*/
	UINT32 AlreadyTested[(MAX_CODES +31) / 32];

	/*
	// Initialise our "tested so far" array
	*/
	for(i = 0; i <  (MAX_CODES + 31) / 32; i++)
	{
		AlreadyTested[i] = 0;
	}/*end for i */

	/*
	// if we have been given an out of range code (which is possible if
	// it hasn't been initialised OR a code has been deleted), reset it
	// back to 0
	*/
	BestCodeSoFar = *pCodeChosen;
	if((BestCodeSoFar < 0) || (BestCodeSoFar >= pGlobalSearchedBook->NumUsedCodes))
	{
		BestCodeSoFar = 0;
	}

	/*
	// mark this code as tested. Well, it soon will be...
	*/
	AlreadyTested[(BestCodeSoFar >> 5)] = 1 << (BestCodeSoFar & 31);

	/*
	// get access to the code book entry and nearest neighbours for this code
	*/
	pBCodeSF = pGlobalSearchedBook->Codes + BestCodeSoFar;
	pCodesNs = NearestNeighbours		  + BestCodeSoFar;

	/*
	// Measure the distance from the vector to the best code so far
	*/
	BestDistSoFar = SQ(pVector->v[0] - pBCodeSF->mtRepVector.v[0]);
	for(k = 1; k < VECLEN; k++)
	{	
		BestDistSoFar += SQ(pVector->v[k] - pBCodeSF->mtRepVector.v[k]);
	}

#if  GET_NEIGHBOUR_STATS
	NumDistanceCalcs ++;
	TotalSearches ++;
#endif

	/*
	// Either try to show that this IS the best code, or move to another code
	// which is better.
	*/
	while(1)
	{
#if  COUNT_SEARCH

		int neighb_count = 0;

#endif

		int NeighbourIsCloser=0;
		int NeighboursAreFurther=0;
		/*
		// Assume for the moment, that no neighbour is closer
		*/
		NeighbourIsCloser = 0;
		NeighboursAreFurther = 0;

		/*
		// Look at all the neighbours that are within the cut-off distance.
		// (All the nearest neighbours whose cut off distance is > than our
		// current distance cannot possibly be closer)
		*/
		pNeighDetails = pCodesNs->Neighbs;
		for(i = 0; i < pCodesNs->NumNeighbours; i++, pNeighDetails++)
		{
			/* If this code is a repeat then mark as tested and continue */
			if ( Repeats[ pNeighDetails->CodeIndex] ) {
				AlreadyTested[(pNeighDetails->CodeIndex >> 5)] |= 
									(1 << (pNeighDetails->CodeIndex & 31));
				continue;
			}

			/*
			// if this neighbour is past the cut off point, then we needn't test the
			// remaining neighbours
			// Note the test MUST be > as we might have had several codes with the
			// same cut off distance but due to the fact we aren't storing all neighbours
			// these might have been lost.
			*/
			if(pNeighDetails->CutOffDistance >  BestDistSoFar)
			{
				NeighboursAreFurther = 1;
#if  COUNT_SEARCH
				num_neighb++;
				neighb_tests+=neighb_count;
#endif
				/*
				// we could actually do a "return" at this point..
				*/
				break;
			}
			/*
			// Else if we have already looked at this code then skip over it
			*/
			else if(AlreadyTested[(pNeighDetails->CodeIndex >> 5)] & 
									(1 <<(pNeighDetails->CodeIndex & 31)))
			{
				continue;
			}

			/*
			// Ok, we are going to test this code, so mark it off the list
			*/
			AlreadyTested[(pNeighDetails->CodeIndex >> 5)] |= 
									(1 << (pNeighDetails->CodeIndex & 31));

			/*
			// Measure the distance from this neighbour to the
			// vector in question using partial sum method
			*/

#if  COUNT_SEARCH

			neighb_count++;

#endif
			pTmpCode = pGlobalSearchedBook->Codes + pNeighDetails->CodeIndex;

			code	 = & ( pTmpCode->mtRepVector);
		
			{
		
			MATH_TYPE sub1, sub2, sub3, sub4, tmp1, tmp2, tmp3, tmp4,  total=0;

			sub1 = pVector->v[0] - code->v[0];	
			sub2 = pVector->v[1] - code->v[1];		
			sub3 = pVector->v[2] - code->v[2];		
			sub4 = pVector->v[3] - code->v[3];		
			
			tmp1 = sub1*sub1;
			tmp2 = sub2*sub2;
			tmp3 = sub3*sub3;
			tmp4 = sub4*sub4;

			total = tmp1+tmp2+tmp3+tmp4;

			if ( total > BestDistSoFar)		continue;
			
			sub1 = pVector->v[4] - code->v[4];		
			sub2 = pVector->v[5] - code->v[5];
			sub3 = pVector->v[6] - code->v[6];		
			sub4 = pVector->v[7] - code->v[7];
			
			tmp1 = sub1*sub1;
			tmp2 = sub2*sub2;
			tmp3 = sub3*sub3;	
			tmp4 = sub4*sub4;		

			total += tmp1+tmp2+tmp3+tmp4;
			
			if ( total > BestDistSoFar)		continue;

			sub1 = pVector->v[8] - code->v[8];		
			sub2 = pVector->v[9] - code->v[9];		
			sub3 = pVector->v[10] - code->v[10];	
			sub4 = pVector->v[11] - code->v[11];	

			tmp1 = sub1*sub1;
			tmp2 = sub2*sub2;
			tmp3 = sub3*sub3;	
			tmp4 = sub4*sub4;		

			total += tmp1+tmp2+tmp3+tmp4;

			if ( total > BestDistSoFar) 	continue;
			
			sub1 = pVector->v[12] - code->v[12];	
			sub2 = pVector->v[13] - code->v[13];	
			sub3 = pVector->v[14] - code->v[14];	
			sub4 = pVector->v[15] - code->v[15];	
			
			tmp1 = sub1*sub1;
			tmp2 = sub2*sub2;
			tmp3 = sub3*sub3;	
			tmp4 = sub4*sub4;		

			total += tmp1+tmp2+tmp3+tmp4;
			
#if  GET_NEIGHBOUR_STATS
NumDistanceCalcs ++;
#endif

			/* if we are closer than our current best so-far, change the best so far */
			if ( total < BestDistSoFar) 
			{
				/* Set new min distance and best code index */
				NeighbourIsCloser = 1;
				BestDistSoFar = total ;
				BestCodeSoFar = pNeighDetails->CodeIndex;
				pBCodeSF = pTmpCode;
				pCodesNs = NearestNeighbours + BestCodeSoFar;
				/* Leave the for loop, don't bother testing the others (well not yet) */
				break;
			}
			} /* end for local variables sub1 etc... */
		
		
	}/*end for i*/

		/*
		// Ok, how did we exit the for loop?
		//
		// if we know all the NEAREST neighbours were further away, then we have found
		// the closest so far
		*/
		if(NeighboursAreFurther)
		{
			break; /*exit the while loop*/
		}
		/*
		// Else if we went through all the nearest neighbours and none were closer
		// than the one we already have, BUT we couldn't prove that all the others
		// are further away, then we just have to try all the other codes. Bugger.
		*/
		else if(!NeighbourIsCloser)
		{

#if  COUNT_SEARCH		   
			num_brute++;
#endif
			for(i = 0; i < pGlobalSearchedBook->NumUsedCodes; i++)
			{
				/*
			    // if we haven't already tested this code, then measure
			    // its distance.
			    */
			    if(! (AlreadyTested[i>> 5] & (1 << (i & 31))))
			    {

			    	pTmpCode = pGlobalSearchedBook->Codes + i;
					code	 = & ( pTmpCode->mtRepVector);
				    /*
					// If smallest cut off distance is greater than
					// BestDistSoFar, don't consider this code
					// as it couldn't be closer!
					*/

					if (pTmpCode->MinDist > BestDistSoFar) { continue;}

#if  COUNT_SEARCH		   
					brute_tests++;
#endif
			{
			
			MATH_TYPE sub1, sub2, sub3, sub4, tmp1, tmp2, tmp3, tmp4, total;
			

			sub1 = pVector->v[0] - code->v[0];	
			sub2 = pVector->v[1] - code->v[1];		
			sub3 = pVector->v[2] - code->v[2];		
			sub4 = pVector->v[3] - code->v[3];		
			
			tmp1 = sub1*sub1;
			tmp2 = sub2*sub2;
			tmp3 = sub3*sub3;
			tmp4 = sub4*sub4;

			total = tmp1+tmp2+tmp3+tmp4;

			if ( total > BestDistSoFar)		continue;
			
			sub1 = pVector->v[4] - code->v[4];		
			sub2 = pVector->v[5] - code->v[5];
			sub3 = pVector->v[6] - code->v[6];		
			sub4 = pVector->v[7] - code->v[7];
			
			tmp1 = sub1*sub1;
			tmp2 = sub2*sub2;
			tmp3 = sub3*sub3;	
			tmp4 = sub4*sub4;		

			total += tmp1+tmp2+tmp3+tmp4;
			
			if ( total > BestDistSoFar)		continue;

			sub1 = pVector->v[8] - code->v[8];		
			sub2 = pVector->v[9] - code->v[9];		
			sub3 = pVector->v[10] - code->v[10];	
			sub4 = pVector->v[11] - code->v[11];	

			tmp1 = sub1*sub1;
			tmp2 = sub2*sub2;
			tmp3 = sub3*sub3;	
			tmp4 = sub4*sub4;		

			total += tmp1+tmp2+tmp3+tmp4;

			if ( total > BestDistSoFar) 	continue;
			
			sub1 = pVector->v[12] - code->v[12];	
			sub2 = pVector->v[13] - code->v[13];	
			sub3 = pVector->v[14] - code->v[14];	
			sub4 = pVector->v[15] - code->v[15];	
			
			tmp1 = sub1*sub1;
			tmp2 = sub2*sub2;
			tmp3 = sub3*sub3;	
			tmp4 = sub4*sub4;		

			total += tmp1+tmp2+tmp3+tmp4;

			
			if ( total < BestDistSoFar) 
			{
				/* Set new min distance and best code index */
				BestDistSoFar = total ;
				BestCodeSoFar = i ;
			}
			} /* end for local variables */


#if  GET_NEIGHBOUR_STATS
					NumDistanceCalcs ++;
#endif

				}/*end if the code hasn't been tested*/
			}/*end for i */

			/*
			// Exit the while loop. We MUST have found the closest now!
			*/
			break;
		}/*end if we had to test all the other codes anyway*/

	}/*end while*/



#if  CHECK_SEARCH_METHOD
	{
		float tmpDist;
		UINT8 tmpClosest;

		tmpDist = BruteForceFind(pVector, &tmpClosest);

		ASSERT(tmpDist == BestDistSoFar);
	}
#endif



	/*
	// When we get here, we have found the best code
	*/
	*pCodeChosen = BestCodeSoFar;
	return  BestDistSoFar;

}

/*************************************************
//
// Function used to compare neighbours so that we can sort
// them into increasing distance
//
*************************************************/


 int NeighbourCompare(const void *p1, const void *p2)
{
	const NeighbourInfoStruct *pNeigh1 = p1;
	const NeighbourInfoStruct *pNeigh2 = p2;

	/*
	// We use the cut off distance to order these
	*/
	if(pNeigh1->CutOffDistance < pNeigh2->CutOffDistance)
	{
		return -1;
	}
	else if(pNeigh1->CutOffDistance > pNeigh2->CutOffDistance)
	{
		return  1;
	}
	else
	{
		return  0;
	}

}



/*************************************************
//
// This function deletes code that have no matching
// vectors.
//
*************************************************/

#if  REJECT_CODES_BASED_ON_USAGE
 int DeleteDeadCodes(CODE_BOOK_STRUCT * pCodeBook, int RemoveLowUse, int MaxCodes)
#else
 int DeleteDeadCodes(CODE_BOOK_STRUCT * pCodeBook, float ErrCutoff, int MaxCodes)
#endif
{
	int i,j;
	CODE_DATA_STRUCT *pCode1, *pCode2;
	int Summary=0;
	static char buffer[50];

	Summary = 0;
	pCode1 = pCodeBook->Codes;
	for(i = 0; i < pCodeBook->NumUsedCodes; i++, pCode1++)
	{
		/*
		// If this code is unused, delete it, by shifting down all
		// the other codes
		*/
#if  REJECT_METHOD
		if(pCode1->NumMembers <= RemoveLowUse )
#else
		if((pCode1->NumMembers == 0 ) || (ErrCutoff > pCode1->AdjustedScore))
#endif
		{
			Summary ++;

			pCode2 = pCode1;
			for(j = i; j < pCodeBook->NumUsedCodes -1; j++,  pCode2++)
			{
				/*
				// copy the next one to this spot
				*/
				pCode2[0] = pCode2[1];
			}


			/*
			// decrement the number of codes, and move the pointer back
			// to compensate for the pointer addition
			*/
			pCodeBook->NumUsedCodes --;
			pCode1--;
			i--;
		}


	}/*end for i */

	
	if(Summary)
	{
#if  REJECT_CODES_BASED_ON_USAGE
		printf("Deleted  %d Codes with Usage <= %d\n", Summary, RemoveLowUse);
#else
		sprintf( buffer, "%f", ErrCutoff);
#endif
	}
	
	/*
	// Return if we deleted any codes that were actually in use
	*/
#if  REJECT_CODES_BASED_ON_USAGE
	return(RemoveLowUse && Summary);
#else
	return(Summary);
#endif

}
/******************************************************************************
 * From			: vqfmem.c
 * Title		: Vector Quantisation Compression Code
 * Author		: Julian Hodgson.
 * Created		: 17/03/1997
 ******************************************************************************/
int WriteVqfMemory(		void *MemoryOut, 
						int nFormat, 
						MIPMAPS *pMipmaps, 
						CODE_BOOK_STRUCT *pCodeBook,
						int	nNumCodes,
						int bAlphaSense
						)

{
	int			x=0, y=0, addr=0;
	int			i, j, l;
	int			r, g, b, a;
	int			nTemp=0;
	MT_PIXEL_VECT	*psVector;
	int			nHt=0;
	int			nWd=0;
	IMAGE_STRUCT *pImage;
	CODE_IMAGE_STRUCT *pImageCodes;
	int			nEndian=0;
	int			map=0, size=0, code_book_size=0;
	int			code_out=0;
	unsigned char *ucPtr;
	/* Write as if machine is little endian */
	nEndian = LITTLE_ENDIAN;

	ucPtr = ( unsigned char *) MemoryOut;
	/*
	// write the header
	*/

	/* Two chars */
	*ucPtr++ = 'P';
	*ucPtr++ = 'V';
		
	/* map_type */
	switch( nFormat) {
	
	case FORMAT_4444:
		map = 9;
		break;

	case FORMAT_1555:
		if ( transp)
			map = 8;
		else
			map = 6;
		break;

	case FORMAT_565:
		map = 7;
		break;

	default:
		return -3; ;
	}

	if ( pMipmaps->numMipmapLevels != 1)
		map += 64;
	
	*ucPtr++ = map;
	
	/* map_size */
	switch ( pMipmaps->mipEntry[0].pImage->xDim) {
	
	case 32:
		size = 0;
		break;

	case 64:
		size = 1;
		break;

	case 128:
		size = 2;
		break;

	case 256:
		size = 3;
		break;

	case 8:
		size = 4;
		break;

	case 16:
		size = 5;
		break;

	case 512:
		size = 6;
		break;

	case 1024:
		size = 7;
		break;

	default:
		return -1;

	}
	
	/* x-dim */
	*ucPtr++ = size;
	
	/* y-dim - x_dim ( bitwise) but since square, zero for now */
	*ucPtr++ = 0;
	
	switch ( nNumCodes)
	{
		case 8:
			code_book_size = 0;
			break;

		case 16:
			code_book_size = 1;
			break;

		case 32:
			code_book_size = 2;
			break;

		case 64:
			code_book_size = 3;
			break;

		case 128:
			code_book_size = 4;
			break;

		case 256:
			code_book_size = 5;
			break;

		default:
			return -2;
	}

	*ucPtr++ = code_book_size;

	/* Empty part of header */
	for(i = 0; i < 6; i++)
	{
		*ucPtr++ = 0;
	}

	/*
	// write the codebook out 
	*/
	for(i = 0; i < nNumCodes; i++)
	{
		int t;
		
		psVector = &(pCodeBook->Codes[i].mtRepVector);

		t = 0;
		
		while (t < 4)
		{
			MATH_TYPE *v =NULL;
			MATH_TYPE alpha;

			switch (t)
			{

				/*
				// Changed since upside down
				*/
				case 0: v = &psVector->v[0]; break;
				case 1: v = &psVector->v[8]; break;
				case 2: v = &psVector->v[4]; break;
				case 3: v = &psVector->v[12]; break;

			}

			/*
			// Reverse Sense of Alpha Channel iff the platform is PVR2
			*/

			if ( bAlphaSense == PVR2)
				alpha = 255.0f - v[3] ;
			else 
				alpha = v[3] ;

			r = (UINT8) (v[0]/PrecisionClamper[nFormat][0] + 0.5f);
			g = (UINT8) (v[1]/PrecisionClamper[nFormat][1] + 0.5f);
			b = (UINT8) (v[2]/PrecisionClamper[nFormat][2] + 0.5f);
			a = (UINT8) (alpha/PrecisionClamper[nFormat][3] + 0.5f);

			switch (nFormat)
			{
			case FORMAT_4444:
				nTemp = (a << 12) | (r << 8) | (g << 4) | b;
				break;

			case FORMAT_565:
				nTemp = (r << 11) | (g << 5) | b;
				break;

			case FORMAT_1555:
				if (transp)
					nTemp = (a << 15) | (r << 10) | (g << 5) | b;
				else
					/* Full alpha anyway */
					nTemp = 0x8000 | (r << 10) | (g << 5) | b; 
				break;

			default:
				return -3;
			}

			WriteShortMem( ucPtr, nTemp, nEndian );	
			
			// Advance pointer
			ucPtr += 2;

			++t;
		}
	}

	/*
	// Write out indices: The smallest mipmap level goes first - the 1x1 level, then the rest.
	*/	
	for(l = pMipmaps->numMipmapLevels-1; l>=0; l--)
	{ 
		pImage = pMipmaps->mipEntry[l].pImage;
		pImageCodes = pMipmaps->mipEntry[l].pImageCodes;

		nHt = (pImage->yDim)/(PIXEL_BLOCK_SIZE);
		nWd = (pImage->xDim)/(PIXEL_BLOCK_SIZE);

		if(nHt==0 || nWd==0)
		{
			nHt=1;
		  	nWd=1;
		}

		addr = 0;
		for(i = 0; i < nHt; i++)
		{
			for(j = 0; j < nWd; j++)
			{
				Deinterleave( addr, &x, &y );
				/* y = ( nHt - 1) - y; */

				/* Flip Y for crazy Windows DIB format */

				code_out = pImageCodes->PixelCodes[nWd * y + x];
				ASSERT( (nWd * y + x > 0) || (nWd * y + x < nWd*nHt) );
				
				code_out += 256 - nNumCodes;
				ASSERT( ( code_out >= 256 - nNumCodes) && ( code_out <= 255) );

				*ucPtr++ = code_out;  
				
				addr ++;
			}
		}
	}
	

	return 0;

}


/*************************************************
//
// Write out short in big or little endian
//
*************************************************/

void WriteShortMem( unsigned char *ucP, int nVal, int nEndian )
{
	if (nEndian == LITTLE_ENDIAN)
	{
		*ucP++ = ( nVal & 0xff );
		*ucP++ = ( nVal >> 8 );
	}
	else
	{
		*ucP++ = ( nVal >> 8 );
		*ucP++ = ( nVal & 0xff );
	}
}


/*************************************************
//
// Deinterleave
//
*************************************************/

void Deinterleave( int addr, int *x, int *y )
{
	int p;

	*x = 0;
	*y = 0;
	for(p = 0; p < 32; p += 2)
	{
		*y >>= 1;
		*x >>= 1;

		*y = *y | (addr & 1) << 15;
		addr >>= 1;
		*x = *x | (addr & 1) << 15;
		addr >>= 1;
	}
}
/******************************************************************************
 * From			: mipmap.c
 * Title		: Vector Quantisation Compression Code
 * Author		: Rowland Fraser (complete rewrite by Simon Fenney)
 * Created		: 17/03/1997
 * Note         : Function to remap the usage of codes in the texture.
 *******************************************************************************/
 void ReMapTextureEncoding(CodeReMapType ReMappingTable,
									   MIPMAPS *pMipmaps,
									   CODE_BOOK_STRUCT *pBook)
{
int i,j, k;
unsigned char *pThisRow;
CODE_IMAGE_STRUCT *pImageCodes;
CODE_BOOK_STRUCT  TempCodeBook;

	/*
	// Step through the MIP map levels, reassigning the codes according
	// to their new positions
	*/
	for(k = 0; k < pMipmaps->numMipmapLevels; k++)
	{
		int XDim, YDim;

		pImageCodes = pMipmaps->mipEntry[k].pImageCodes;

		XDim = pMipmaps->mipEntry[k].pImage->xDim/2;
		YDim = pMipmaps->mipEntry[k].pImage->yDim/2;

		if ( (XDim ==0) || (YDim ==0)) 
		{
			XDim = 1;
			YDim = 1;
		}
	
		/*
		// Run through the image
		*/
		for(i=0; i< YDim; i++)
		{
			pThisRow = &(pImageCodes->PixelCodes[i * XDim]);
		
			/*
			// Run through codes in the row
			*/ 
			for(j=0; j < XDim; j++)
			{
				/*
				// Map the code to its new location
				*/
				*pThisRow =  (UINT8) ReMappingTable[*pThisRow];
				
				pThisRow++;
			}/*end for j*/
		}/*end for i*/

	}/*end for k (step though MIP map levels)*/

	/*
	// Now rearrange the code book.
	*/
	TempCodeBook.NumUsedCodes = pBook->NumUsedCodes;
	for(i = 0; i < pBook->NumUsedCodes; i++)
	{
	    /*
		// Move the code to it's new position
		*/
		TempCodeBook.Codes[ReMappingTable[i]] = pBook->Codes[i];
	}

	/*
	// Copy the re-arranged table back again
	*/
	memcpy (pBook, &TempCodeBook, sizeof(CODE_BOOK_STRUCT));
}
									   
								 

/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*
// "Game Tree" best code assignment method
*/
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*
// Define the type for storing info on how many times particular
// pairs of codes are adjacent to each other. Note that direction
// is irrelevent, and we don't need to consider when the same code is
// adjancent to itself (since we won't get a page break!). Also since
// A adjacent to B is the same as B adjacent to A, we can always assume
// the numeric value of A is < B.
*/
typedef struct
{
	int CodeA; /* Code A < CodeB */
	int CodeB;
	int Occurences;
	int RemainingScore;
	int PageAssignment; /* =MAX_CODEBOOK_PAGES if A and B in different Parent pages*/
}CodePairStructType;

/*
// Define a macro function for mapping a combination of A,B to a position
// in the array. This mapping was found by solving 3 simulataneous equations.
// it assumes 0 <= A < B <= 255.
// Note MAP(0,1) = 0 and MAP(1,2)= 255 as required. MAP(0,0) is invalid (=-1).
*/
#define MAP_AB_TO_POSITION(A,B) (((A * (511 - A)) >> 1) + ((B - A) - 1))


/*
// Define the array of possible pairs. The size is the index of the last
// element (254,255) plus 1 to get the correct val for a C array declaration.
*/
#define MAX_NUM_CODE_PAIRS (MAP_AB_TO_POSITION(254, 255) + 1)

CodePairStructType CodePairs[MAX_NUM_CODE_PAIRS];


/*
// Define how we have assigned the codes (so far) to pages, and keep track
// of page usage.
*/

 int CurrentPageAssignments[MAX_CODES];
 int BestPageAssignments[MAX_CODES];
 int CodesAssignedForChildren[2];

 int MaxPagesInUse = -1;


/*
// Global parameters for "FindGoodPageAssignment" which are invariant for all
// recursions
*/
 CodePairStructType * pFGPAEndOfCodePairs;
 int FGPAScoreToBeat;
 int FGPAChildPageBase;
 int FGPANumCodesPerPage;
/*************************************************************************/
/*************************************************************************/


 void FindGoodPageAssignment( CodePairStructType * pCodePair,

								  int PartialScoreSoFar,
								  int RecursionsRemaining,
								  int CodesInChild0,
								  int CodesInChild1)
{
	int i;
	int CodeA, CodeB;


	/*
	// Loop through all the pairs in which both codes have already
	// been assigned. 
	*/
	while( (pCodePair != pFGPAEndOfCodePairs) && 
		   (CurrentPageAssignments[pCodePair->CodeA] >= 0) && 
		   (CurrentPageAssignments[pCodePair->CodeB] >= 0) )
	{
		/*
		// If they have been assigned to different pages, then increase our
		// score
		*/
		if( CurrentPageAssignments[pCodePair->CodeA] != 
			CurrentPageAssignments[pCodePair->CodeB])
		{
			PartialScoreSoFar += pCodePair->Occurences;

			/*
			// if we are already worse off than our best-so-far, give up!
			*/
			if( PartialScoreSoFar >= FGPAScoreToBeat )
			{
				#ifdef  DEBUG
				if(FullDebug) 
				{
					printf("Exiting: PS=%d ScoreToBeat=%d\n", 
									 PartialScoreSoFar, 
									 FGPAScoreToBeat);
				}
				#endif
				return;
			}
		}
		pCodePair++;
	} /*end while*/

	/*
	// have we finished recursion OR reached the end of the pairs?
	*/
	if((RecursionsRemaining == 0) || (pCodePair == pFGPAEndOfCodePairs))
	{
		int SearchLimit=0;

		#ifdef  DEBUG
		if(FullDebug) 
		{
			static const char NY[2][3]={"No", "Yes"};

			printf("\tRecursions Remaining: %d .  At pair list end: %s\n", 
							   RecursionsRemaining,
							   NY[pCodePair == pFGPAEndOfCodePairs]);

			printf("\tPartial Score: %d .  ScoreTB:%d\n", 
							   PartialScoreSoFar,
							   FGPAScoreToBeat);

			printf("\tChild 0:%d Child 1:%d\n", 
								 CodesInChild0, CodesInChild1);
		}
		#endif

		/*
		// Evaluate the remaining code pairs - look properly at the first
		// SearchLimit of them, then just estimate the rest.
		*/
		SearchLimit = 10;
		while((pCodePair != pFGPAEndOfCodePairs) && SearchLimit)
		{

			/*
			// if these codes haven't been assigned to the same
			// page, then sum up the potential page breaks
			*/
			if( CurrentPageAssignments[pCodePair->CodeA] != 
					CurrentPageAssignments[pCodePair->CodeB])
			{
				PartialScoreSoFar += pCodePair->Occurences;

				/*
				// if we are already over our best so far, then
				// give up. It isn't going to get better!
				*/
				if(PartialScoreSoFar >= FGPAScoreToBeat)
				{
					#ifdef  DEBUG
					if(FullDebug) 
					{
						printf("RecRem:Exiting: PS=%d ScoreToBeat=%d\n", 
										  PartialScoreSoFar, 
										  FGPAScoreToBeat);
					}
					#endif
					return;
				}
			}/*end if codes' pages are different*/

			/*
			// Move to the next code pair
			*/
			pCodePair ++;
			SearchLimit --;

		}/*end while*/

		/*
		// If we exited early, then add on an estimate of how much is left
		*/
		if(pCodePair != pFGPAEndOfCodePairs)
		{
			PartialScoreSoFar+= pCodePair->RemainingScore;
		}

		/*
		// if we have beaten the best so far, then update the saved values
		*/
		if(PartialScoreSoFar < FGPAScoreToBeat)
		{
			int DebugCount = 0;
#ifdef  DEBUG
			if(FullDebug)
			{
				printf("Score Now: %d\n", PartialScoreSoFar);
			}
#endif
			FGPAScoreToBeat = PartialScoreSoFar;
			for(i = 0; i < MAX_CODES; i++)
			{
				BestPageAssignments[i] = CurrentPageAssignments[i];

				if( (CurrentPageAssignments[i] == FGPAChildPageBase) || 
					(CurrentPageAssignments[i] == FGPAChildPageBase + 1))
				{
					DebugCount++;
				}
			}/*end for i*/

			CodesAssignedForChildren[0] = CodesInChild0;
			CodesAssignedForChildren[1] = CodesInChild1;

			ASSERT(DebugCount == (CodesInChild0 + CodesInChild1));
		}
		/*
		// All done. Back on out.
		*/
		return;
	}
	/*
	// Else try assigning the codes to pages.
	*/
	else
	{
		int CodeToAssign=0;

		CodeA = pCodePair->CodeA;
		CodeB = pCodePair->CodeB;

		RecursionsRemaining	--;

		/*
		// We are assigning one more code, so reduce the partial score. This
		// should make sure the algorithm is encouraged to assign codes!
		*/
		PartialScoreSoFar--;

		/*
		//Decide which code we should assign
		// 
		// if A already assigned, then do B.
		*/
		if(CurrentPageAssignments[CodeA] >= 0)
		{
			/*
			// We can assume B has not been assigned a page since we have already
			// looped through all the pairs that have both codes assigned.
			*/
			ASSERT(CurrentPageAssignments[CodeB] < 0);
			CodeToAssign = CodeB;
		}
		else
		{
			CodeToAssign = CodeA;
		}
		/*
		// There are only two possible cases...
		//
		// Try assigning  first to child Page 0...
		*/
		if(CodesInChild0 < FGPANumCodesPerPage)
		{
			CurrentPageAssignments[CodeToAssign] = FGPAChildPageBase + 0;
		
			FindGoodPageAssignment(pCodePair,
							  PartialScoreSoFar,
							  RecursionsRemaining,
							  CodesInChild0 + 1,
							  CodesInChild1);
		}
		/*
		// ... and then child Page 1
		*/
		if(CodesInChild1 < FGPANumCodesPerPage)
		{
			CurrentPageAssignments[CodeToAssign] = FGPAChildPageBase + 1;
		
			FindGoodPageAssignment(pCodePair,
							  PartialScoreSoFar,
							  RecursionsRemaining,
							  CodesInChild0,
							  CodesInChild1 + 1);
		}
		
		/*
		// Clear out the assignment we made.
		*/
		CurrentPageAssignments[CodeToAssign] = -1 -CodeToAssign;

	}/*end decision if we have come to end of recursion etc*/
}/*end function*/



/*****************************************************************************/
/*****************************************************************************/
/*
// We need to be able to sort the code pair table. Use standard Quick sort function.
// This needs a comparison function... This is set to give decreasing order.
*/
 int PairCompare(const void *p1, const void *p2)
{
	const CodePairStructType *Pair1 = p1;
	const CodePairStructType *Pair2 = p2;

	/*
	// if the codes of the two pairs ALL belong to the same class, then
	// order them in decreasing order of of occurence.
	*/
	if(Pair1->PageAssignment == Pair2->PageAssignment)
	{
		return( Pair2->Occurences - Pair1->Occurences );
	}
	/*
	// Else order them by the pair assignments. This way, any pair that
	// has codes in different parent pages will be sorted toward the end
	// of the list, and hence discarded.
	*/
	else
	{
		return( Pair1->PageAssignment - Pair2->PageAssignment );
	}
}

/*****************************************************************************/
/*****************************************************************************/


/*
// Function to count the number of pairs of adjacent codes in an image.
*/
 void CountCodePairs( MIPMAPS *pMipmaps, 
							    int *pTotalPotentialBreaks,
								int *pNaivePotentialBreaks )
{
	int i,j,k;
	int PreviousCode=0;
	int CodeBelow=0;
	int ThisCode=0;
#ifdef  DEBUG
	int CodePairoffset = 0;
#endif
	CodePairStructType *pCodePair;

	CODE_IMAGE_STRUCT *pImageCodes;

	unsigned char *pThisRow, *pNextRow;

	/*
	// Ininitialise the table of code pairs
	*/
	pCodePair = CodePairs;
	for(i = 0; i < 255; i++)
	{
		for(j = i+1; j < 256; j++)
		{
			/*
			// Initialise this code
			*/
			pCodePair->CodeA = i;
			pCodePair->CodeB = j;
			pCodePair->Occurences = 0;
			/* all codes initially belong to the same "root" Page*/
			pCodePair->PageAssignment = 0;
			/*
			// Move to the next position
			*/
			pCodePair++;

			/*
			// Debug Checks
			*/
			#ifdef  DEBUG
				ASSERT(CodePairoffset == MAP_AB_TO_POSITION(i,j));
				CodePairoffset++;
			#endif
		}/*end for j*/
	}/*end for i*/


	*pTotalPotentialBreaks = 0;

	/*
	// Now run through the image counting the occurences
	*/
	for(k = 0; k < pMipmaps->numMipmapLevels; k++)
	{
		int XDim, YDim;

		pImageCodes = pMipmaps->mipEntry[k].pImageCodes;

		XDim = pMipmaps->mipEntry[k].pImage->xDim/2;
		YDim = pMipmaps->mipEntry[k].pImage->yDim/2;
		
		/*
		// Add on potential breaks for this MIP map level
		*/
		*pTotalPotentialBreaks += 2 * XDim * YDim - XDim - YDim;

		/*
		// Run through all but the last row of the image
		*/
		for(i=0; i< YDim - 1; i++)
		{
			pThisRow = & pImageCodes->PixelCodes[i * XDim];
			pNextRow = pThisRow + XDim;

			/*
			// Do the first code of the row specially since it doesn't have a predecessor
			*/
			ThisCode = *pThisRow;
			CodeBelow= *pNextRow;

			/*
			// Count this vertical pair
			*/
			if(ThisCode == CodeBelow)
			{
			  /*Do nothing*/
			}
			else if(ThisCode < CodeBelow)
			{
				CodePairs[ MAP_AB_TO_POSITION(ThisCode, CodeBelow)].Occurences++;
			}
			else
			{
				CodePairs[ MAP_AB_TO_POSITION(CodeBelow, ThisCode)].Occurences++;
			}

			PreviousCode = ThisCode;
			pThisRow++;
			pNextRow++;
			/*
			// Run through all other codes in the row
			*/ 
			for(j=1; j < XDim; j++)
			{
				ThisCode = *pThisRow;
				CodeBelow= *pNextRow;

				/*
				// Look at the horizontal pair
				*/
				if(PreviousCode == ThisCode)
			    {
			      /*Do nothing*/
			    }
				else if(PreviousCode < ThisCode)
				{
					CodePairs[ MAP_AB_TO_POSITION(PreviousCode, ThisCode)].Occurences++;
				}
				else
				{
					CodePairs[ MAP_AB_TO_POSITION(ThisCode, PreviousCode)].Occurences++;
				}

				/*
				// Do the vertical pairing
				*/
			    if(ThisCode == CodeBelow)
			    {
			      /*Do nothing*/
			    }
			    else if(ThisCode < CodeBelow)
			    {
			    	CodePairs[ MAP_AB_TO_POSITION(ThisCode, CodeBelow)].Occurences++;
			    }
			    else
			    {
			    	CodePairs[ MAP_AB_TO_POSITION(CodeBelow, ThisCode)].Occurences++;
			    }

				/*
				// Move to next spot
				*/
				PreviousCode = ThisCode;
				pThisRow++;
				pNextRow++;

			}/*end for j*/
		}/*end for i*/

		/*
		// Do the last row of the image
		*/
		pThisRow = & pImageCodes->PixelCodes[i * XDim];

		/*
		// Do the first code of the row specially since it doesn't have a predecessor
		*/
		PreviousCode = *pThisRow;

		pThisRow++;
		/*
		// Run through all other codes in the row
		*/ 
		for(j=1; j< XDim; j++)
		{
			ThisCode = *pThisRow;
		
			/*
			// Look at the horizontal pair
			*/
			if(PreviousCode == ThisCode)
		    {
		      /*Do nothing*/
		    }
			else if(PreviousCode < ThisCode)
			{
				CodePairs[ MAP_AB_TO_POSITION(PreviousCode, ThisCode)].Occurences++;
			}
			else
			{
				CodePairs[ MAP_AB_TO_POSITION(ThisCode, PreviousCode)].Occurences++;
			}
		
			/*
			// Move to next spot
			*/
			PreviousCode = ThisCode;
			pThisRow++;
		}/*end for j*/

	}/*end for k (step though MIP map levels)*/


	/*
	// Count the potential breaks we get using the naiive encoding
	*/
	*pNaivePotentialBreaks = 0;

	pCodePair = CodePairs;
	for(i = 0; i < 255; i++)
	{
		for(j = i+1; j < 256; j++)
		{
		    /*
			// NOTE the following test ONLY works if CODES_PER_PAGE is a 
			// power of 2.
			*/
			if((i ^ j) & (~(CODES_PER_PAGE - 1)))
			{
				*pNaivePotentialBreaks += pCodePair->Occurences;
			}
			pCodePair++;
		}/*end for j*/
	}/*end for i*/
	

	/*
	// Sort the code pairs into decreasing order of occurence
	*/
	qsort( CodePairs, 
		   MAX_NUM_CODE_PAIRS, 
		   sizeof(CodePairStructType), 
		   PairCompare);



}
/******************************************************************
 ******************************************************************/

int GlobalUniquePageBase;
void  AssignCodesToChildPages(CodePairStructType* pStartCodePairs, 
							  CodePairStructType* pEndOfCodePairs,
							  int PageBase,
							  int PageSize,
							  int SearchDepth)
{
	int i;
	int NumCodesInPage=0;
	CodePairStructType* pTmpPair;
	CodePairStructType* pTmpPair2;
	CodePairStructType* pTmpPair3;
	int SumSoFar=0;

	int NumCodesYetToAssign=0;


#ifdef  DEBUG
	FullDebug = 0;
#endif


	/*
	// Find all the codes which have been assigned to the page base,
	// and set them to be unassigned. We then assign them to either
	// Page (2*PageBase)  OR Page (2*PageBase +1), using the game
	// tree method to select the assignment.
	*/
	NumCodesInPage = 0;
	for(i = 0; i < MAX_CODES; i++)
	{
		if(BestPageAssignments[i] == PageBase)
		{
			/*make the codes page unassigned and unique*/
			CurrentPageAssignments[i] = -i - 1; 
			NumCodesInPage ++;
		}
		else
		{
			CurrentPageAssignments[i] = BestPageAssignments[i];
		}
	}

	/*
	// If the number of codes in the page doesn't exceed a page's limit
	// then our work here is done.
	*/
	if(NumCodesInPage <= CODES_PER_PAGE)
	{
		return;
	}

	/*
	// Increment the Unique Page base (by 2 since we always create 2 children).
	*/
	GlobalUniquePageBase+= 2;

	/*
	// grab the unique page base and remember it
	*/
	PageBase = GlobalUniquePageBase;




	/*
	// Now we may as well assign the first pairs first code to the
	// first of the two children because it HAS to go in one of them!
	*/
	CurrentPageAssignments[pStartCodePairs[0].CodeA] = PageBase;
	CodesAssignedForChildren[0] = 1;
	CodesAssignedForChildren[1] = 0;

	/*
	// Loop through the pairs. When we encounter one that has not had either of
	// its two codes assigned, then use the "game tree" method of trying to
	// assign the codes optimally.
	*/
	FGPAScoreToBeat     = INT_MAX;
	pFGPAEndOfCodePairs = pEndOfCodePairs;
	FGPAChildPageBase   = PageBase;
	FGPANumCodesPerPage = PageSize / 2;


	NumCodesYetToAssign = NumCodesInPage;

	while(NumCodesYetToAssign)
	{
		int PreviousYetToAssign = NumCodesYetToAssign;

		/*
		// Assign another batch of codes.
		*/
		FindGoodPageAssignment( pStartCodePairs,
								/*
								//set the initial score to equal the number of codes we
								// have yet to assign. That way the algorithm is 
								// encouraged to assign more codes :)
								*/
								NumCodesYetToAssign, 
							    SearchDepth, /*recursion remaining*/
								CodesAssignedForChildren[0],
								CodesAssignedForChildren[1]);
		printf(".");
		fflush(stdout);
		
		NumCodesYetToAssign	= NumCodesInPage - 
						  (CodesAssignedForChildren[0] + CodesAssignedForChildren[1]);


		/*
		// If we couldn't improve, then  there are some "Orphaned" codes in this set.
		// Just assign them arbitrarily to the two children, and exit the loop.
		*/
		if(PreviousYetToAssign == NumCodesYetToAssign)
		{
			for(i = 0; i < MAX_CODES; i++)
			{
				if((BestPageAssignments[i] < 0) && (BestPageAssignments[i]!=(-INT_MAX)))
				{
					/*
					// if Child 0 has a free space, add it there
					*/
					if(CodesAssignedForChildren[0] < FGPANumCodesPerPage)
					{
						BestPageAssignments[i] = PageBase;
						CodesAssignedForChildren[0]++;
					}
					/*
					// else assign to Child 1
					*/
					else
					{
						ASSERT(CodesAssignedForChildren[1] < FGPANumCodesPerPage);

						BestPageAssignments[i] = PageBase + 1;
						CodesAssignedForChildren[1]++;
					}
				}/*end if code unassigned*/
			}/*end for stepping through the codes*/
			
			break;
		}/*end if we couldn't assign pages this time*/

		/*
		// Copy over the assignements made so far
		*/
		for(i = 0; i < MAX_CODES; i++)
		{
			CurrentPageAssignments[i] = BestPageAssignments[i];
		}
	}


	/*
	// We should now have assigned the codes to one of the two child pages.
	// Run through all the code pairs marking them as either having both codes
	// belonging to the same pair, or not.
	*/
	for(pTmpPair = pStartCodePairs;  pTmpPair < pEndOfCodePairs; pTmpPair++)
	{
		int CodeAsPage=0, CodeBsPage=0;
		
		CodeAsPage = BestPageAssignments[pTmpPair->CodeA];
		CodeBsPage = BestPageAssignments[pTmpPair->CodeB];

		if(CodeAsPage == CodeBsPage)
		{
			pTmpPair->PageAssignment = CodeAsPage;
		}
		else
		{
			pTmpPair->PageAssignment = INT_MAX; /*this forces it to the bottom*/
		}
	}/*end for*/

	/*
	// Sort these so that pairs with codes assigned to the same page are put
	// together (and in decreasing order of occurence) and those with different
	// pages are put at the end.
	*/
	qsort( pStartCodePairs, 
		   pEndOfCodePairs - pStartCodePairs,
		   sizeof(CodePairStructType), 
		   PairCompare);

	/*
	// Find all the pairs assigned to the first page
	*/
	for(pTmpPair = pStartCodePairs;  pTmpPair < pEndOfCodePairs; pTmpPair++)
	{
		if(pTmpPair->PageAssignment != PageBase)
		{
			break;
		}
	}

	/*
	// Find all the codes assigned to the second page.
	*/
	pTmpPair2 = pTmpPair;
	for(pTmpPair2 = pTmpPair;  pTmpPair2 < pEndOfCodePairs; pTmpPair2++)
	{
		if(pTmpPair2->PageAssignment != PageBase+1)
		{
			break;
		}
	}


	/*
	// Run through each of these sets. from back to front, computing
	// an upper bound on score. This should reduce the amount of work
	// we have to do (by doing approximations)
	//
	// Do the first set..
	*/
	SumSoFar= 0;
	for(pTmpPair3 =  pTmpPair - 1; pTmpPair3 >= pStartCodePairs; pTmpPair3 --)
	{
		SumSoFar += pTmpPair3->Occurences;
		pTmpPair3->RemainingScore = SumSoFar;
	}

	/*
	// and the second set...
	*/
	SumSoFar= 0;
	for(pTmpPair3 =  pTmpPair2 - 1; pTmpPair3 >= pTmpPair; pTmpPair3 --)
	{
		SumSoFar += pTmpPair3->Occurences;
		pTmpPair3->RemainingScore = SumSoFar;
	}
	
	/*
	// Recursively assign the two sets to each of their own children
	*/
	AssignCodesToChildPages(pStartCodePairs, 
							pTmpPair,
							PageBase,
							PageSize / 2,
							SearchDepth + 2);

	AssignCodesToChildPages(pTmpPair,
							pTmpPair2,
							PageBase + 1,
							PageSize / 2,
							SearchDepth + 2); /*WAS +1*/
}


/******************************************************************
 *
 *
 *
 ******************************************************************/
void ReOrderCodebook(MIPMAPS *pMipmaps, CODE_BOOK_STRUCT *pBook, int InitialSearchDepth)
{
	int i , j;
	int InitialParentSize=0;
	CodePairStructType *pEndOfCodePairs, *pTempCodePair;
	int PageBase=0;
	int Score=0, Total=0;
	int TotalPotentialBreaks=0, NaivePageBreaks=0;

	int	SumSoFar=0;

	CodeReMapType ReMappingTable;



	/*
	// Run through the entire image, counting the occurences of adjacent
	// code pairs. Sort these into decreasing order.
	*/
	CountCodePairs(pMipmaps, &TotalPotentialBreaks, &NaivePageBreaks);

	/*
	// Find the last code pair (+ 1)
	*/
	pEndOfCodePairs = CodePairs;
	/*
	// Find the number of pairs used
	*/
	for(i = 0; i < MAX_NUM_CODE_PAIRS; i++)
	{
		if(pEndOfCodePairs->Occurences == 0)
		{
			break;
		}
		
		pEndOfCodePairs ++;
	}


	/*
	// Compute upper bounds on remaining code page breaks....
	//
	//
	// Starting from the back and working forward, sum up upper bounds on
	// the weightings
	*/
	SumSoFar= 0;
	for(pTempCodePair = pEndOfCodePairs - 1; pTempCodePair >= CodePairs; pTempCodePair--)
	{
		SumSoFar += pTempCodePair->Occurences;
		pTempCodePair->RemainingScore = SumSoFar;
	}


	/*
	// Initialise the Current code page assignments. At the moment,
    // all are assigned to the "Root Mega Parent" page.
	*/
	for(i = 0; i < pBook->NumUsedCodes; i++)
	{
		CurrentPageAssignments[i] = 0;
		BestPageAssignments[i] = 0;
	}
	/*
	// kill off the unused ones
	*/
	for(/*nil*/; i < MAX_CODES; i++)
	{
		CurrentPageAssignments[i] = -INT_MAX;
		BestPageAssignments[i] = -INT_MAX;
	}

	/*
	// Compute how many pages we require
	*/
	MaxPagesInUse = (pBook->NumUsedCodes + (CODES_PER_PAGE - 1)) / CODES_PER_PAGE;

	/*
	// Compute the size of the Initial root parent page: it has to be a power of
	// 2 times CODES_PER_PAGE, and for efficiency, only just large enough to
	// hold all the codes.
	*/
	InitialParentSize = CODES_PER_PAGE;
	while(InitialParentSize < pBook->NumUsedCodes)
	{
		InitialParentSize *= 2;
		/*To keep execution time down, decrease this for large code sets*/
		InitialSearchDepth -= 1; 
	}

	/*
	// Make sure InitialSearchDepth is sensible
	*/
	if(InitialSearchDepth <= 0)
	{
		InitialSearchDepth = 1;
	}

	/*
	// Recursively split the mega page
	*/
	GlobalUniquePageBase = 0;
	AssignCodesToChildPages( CodePairs, 
							 pEndOfCodePairs, 
							 GlobalUniquePageBase,
							 InitialParentSize,
							 InitialSearchDepth);

	printf(".\n");
	/*
	// Now we just need to renumber all the pages.
	// Start by negating all the assignments made and making them unique by
	// subtracting a further 1.
	*/
	for(i = 0; i < pBook->NumUsedCodes; i++)
	{
		BestPageAssignments[i] = -1 - BestPageAssignments[i];
	}


	PageBase = 0;
	/*
	// Run through all the codes and each time we find one that hasn't been
	// re-assigned, do so
	*/
	for(i = 0; i < pBook->NumUsedCodes; i++)
	{
	    /*
		// has this code page not been re-assigned?
		*/
		if(BestPageAssignments[i] < 0)
		{
		    /*
			// Then find all codes assigned to the same page and
			// redo them
			*/
			for(j = i+1; j < pBook->NumUsedCodes; j++)
			{
				if(BestPageAssignments[j] == BestPageAssignments[i])
				{
					BestPageAssignments[j] = PageBase;
				}
			}/*end for j*/

			BestPageAssignments[i] = PageBase;
			PageBase ++;
		}/*end if page not renumbered*/
	}/*end for i*/



	/*
	// Compute the final score. It should just be the sum of all
	// pairs which aren't in the same page
	*/
	Score = 0;
	Total = 0;

	for(pTempCodePair = CodePairs; pTempCodePair!= pEndOfCodePairs; pTempCodePair++)
	{
		if(pTempCodePair->PageAssignment == INT_MAX)
		{
			Score += pTempCodePair->Occurences;
		}
		Total += pTempCodePair->Occurences;
	}/*end for*/


	/*
	// Give approximate breaks in original encoding. (Note +1 is to
	// stop any possible div by zero).
	*/
	/*
	 *printf("Total Vector to Vector  = %d%%\n", 
	 *			 (NaivePageBreaks * 100) / (TotalPotentialBreaks + 1),
	 *			 NaivePageBreaks, TotalPotentialBreaks);
	*/
	printf("Page Break Cost of initial encoding = %d%%\n", 
				 (NaivePageBreaks * 100) / (TotalPotentialBreaks + 1));

	printf("Page Break Cost of New encoding = %d%% (%d, %d, %d)\n", 
				 (Score * 100) / (TotalPotentialBreaks + 1),
				 Score, Total, TotalPotentialBreaks);


	/*
	// generate a remapping table. This table indicates the new position of
	// each code.
	*/
	
	for(i = 0; i < 	MaxPagesInUse; i++)
	{
		int NewCodePosition;
		NewCodePosition = i * CODES_PER_PAGE;

		/*
		// Find all codes assigned to this page.
		*/
		for(j = 0; j < MAX_CODES; j++)
		{
			if(BestPageAssignments[j] == i)
			{
				ReMappingTable[j] = NewCodePosition;
				NewCodePosition++;
			}
		}/*end for j*/
	}/*end for i*/


	/*
	// rearrange the codes according to our code page optimisation
	*/
	ReMapTextureEncoding(ReMappingTable, pMipmaps, pBook);

}




/****************************************************************
/ This Function just orders the code book with respect to its usage
/ in the image, for rendering optimisation on Arc
*****************************************************************/



void ReOrderCodebookSimple(MIPMAPS *pMipmaps, CODE_BOOK_STRUCT *pCodeBook)
{
	int i;

	CodeReMapType ReMappingTable, InverseReMappingTable;

	/*
	// Fill table with identity mapping
	*/

	for ( i=0; i<MAX_CODES; i++)
		ReMappingTable[i] = i;

	/* Global for CodeCompare */
	pCodeBk = pCodeBook;



	/*
	// Sort the table according to the number of images per code
	*/
	qsort(&ReMappingTable, pCodeBook->NumUsedCodes, sizeof(int), CodeCompare);

	/*
	// We want the inverse of this function
	*/

 	for ( i=0; i<MAX_CODES; i++)
		InverseReMappingTable[ReMappingTable[i]] = i;

	/*
	// rearrange the codes according to our code page optimisation
	*/
	ReMapTextureEncoding(InverseReMappingTable, pMipmaps, pCodeBook);

	/*
	// Done!
	*/

			
}

int CodeCompare( const void *p1, const void *p2)
{
	const int *a1 = p1;
	const int *a2 = p2;

	if ( pCodeBk->Codes[*a1].NumMembers < pCodeBk->Codes[*a2].NumMembers)	
		return 1;
	else if  ( pCodeBk->Codes[*a1].NumMembers == pCodeBk->Codes[*a2].NumMembers)	
		return 0;
	else		
		return -1;

}


 int CodeCompareMip( const void *p1, const void *p2)
{
	const int *a1 = p1;
	const int *a2 = p2;

	if ( pCodeList[*a1].freq < pCodeList[*a2].freq)		
		return 1;
	else if ( pCodeList[*a1].freq == pCodeList[*a2].freq)		
		return 0;
	else		
		return -1;
}


 int CompareFinal( const void *p1, const void *p2)
{
	const int *a1 = p1;
	const int *a2 = p2;

	if ( pCodeFreq[*a1] < pCodeFreq[*a2])  
		return 1;
	else if ( pCodeFreq[*a1] == pCodeFreq[*a2]) 
		return 0;
	else								   
		return -1;
}


	
void ReOrderCodebookSimplest(MIPMAPS *pMipmaps, CODE_BOOK_STRUCT *pCodeBook)
{
	int Score=0, i, l;
	CodeReMapType ReMappingTable, InverseReMappingTable;
	int NumUsedCodes[MAX_CODES];
	int NumLevels=0;
	int NumVects=0;

	CODE_IMAGE_STRUCT *pImageCodes;

	NumLevels = pMipmaps->numMipmapLevels;

	/* 
	// If Mipmap off then just reorder simply 
	*/

	if ( NumLevels == 1) {
		ReOrderCodebookSimple( pMipmaps, pCodeBook);
		return;
	}

	for ( i=0; i<MAX_CODES; i++)
		NumUsedCodes[i] = 0;

	for ( l=0; l<NumLevels; l++) {

		Score = 1 << l;
		pImageCodes = pMipmaps->mipEntry[l].pImageCodes;
		
		NumVects = pMipmaps->mipEntry[l].pImageVecs->NumVects;

		for ( i=0; i<NumVects; i++) 
			NumUsedCodes[ pImageCodes->PixelCodes[i] ]+= Score;
			
	}

	for ( i=0; i<MAX_CODES; i++)
		ReMappingTable[i] = i;

	pCodeFreq = (int *) &NumUsedCodes;

	qsort( &ReMappingTable, pCodeBook->NumUsedCodes, sizeof(int), CompareFinal);

	/*
	// We want the inverse of this function
	*/

	for ( i=0; i<MAX_CODES; i++)
		InverseReMappingTable[ReMappingTable[i]] = i;

	/*
	// rearrange the codes according to our code page optimisation
	*/
	ReMapTextureEncoding(InverseReMappingTable, pMipmaps, pCodeBook);



}
/******************************************************************************
 * From			: convert.c
 * Title		: Vector Quantisation Compression Code
 * Author		: Julian Hodgson.
 * Created		: 17/03/1997
 ******************************************************************************/
void ConvertBitMapToVectors ( MIPMAPS *pMipmaps)
{
	int i, j, l, index=0;
	int xPos=0, yPos=0;
	int VecsMaxX=0, VecsMaxY=0;
	int VectCount=0;
	int normalMipmapLevels=0;

	MT_PIXEL_VECT *pVect;

	IMAGE_STRUCT *pImage;
	ALPHA_STRUCT *pAlpha = NULL; /*initialise to stop compiler warnings*/
	IMAGE_VECTOR_STRUCT	*pImageVecs;

	/*
	// Find the number of MIP-levels that converted to 2*2 codes
	// ie not the single pixel special case
	*/
	normalMipmapLevels = pMipmaps->numMipmapLevels;
	if(normalMipmapLevels>1)
  		normalMipmapLevels--;

  	for(l = 0; l < normalMipmapLevels; l++)
	{
		pImage = pMipmaps->mipEntry[l].pImage;
		pAlpha = pMipmaps->mipEntry[l].pAlpha;

		/*
		// Get the dimensions of the Image Vector Structure
		*/
		VecsMaxX = 	(pImage->xDim + PIXEL_BLOCK_SIZE -1) / PIXEL_BLOCK_SIZE;
		VecsMaxY = 	(pImage->yDim + PIXEL_BLOCK_SIZE -1) / PIXEL_BLOCK_SIZE;
		
		pMipmaps->mipEntry[l].pImageVecs = NEW(IMAGE_VECTOR_STRUCT);

		if( pMipmaps->mipEntry[l].pImageVecs == NULL)
		{
			printf("Out of memory\n");
			return;/*exit(1);*/
		}

		pImageVecs = pMipmaps->mipEntry[l].pImageVecs;
		pImageVecs->NumVects = VecsMaxX*VecsMaxY;
		pImageVecs->mtVectors = 
		      (MT_PIXEL_VECT *) malloc( sizeof(MT_PIXEL_VECT) * pImageVecs->NumVects );

		if( pImageVecs->mtVectors == NULL)
		{
			printf("Out of memory\n");
			return;/*exit(-99);*/
		}

		pVect = pImageVecs->mtVectors;

		VectCount = 0;

		for(yPos = 0; yPos < VecsMaxY; yPos++)
		{
			int yLower = yPos * PIXEL_BLOCK_SIZE; 
		
			for(xPos = 0; xPos < VecsMaxX; xPos++)
			{
				int k =0;
				int xLower= xPos * PIXEL_BLOCK_SIZE;
				/*
				// Re-arrange the NxN pixels
				*/
				for(i = yLower; i < yLower + PIXEL_BLOCK_SIZE; i++)
				{
					index = i * VecsMaxX * 2 + xLower;

					for(j = xLower; j < xLower + PIXEL_BLOCK_SIZE; j++)
					{
						/* index = i*VecsMaxX*2+j */

						pVect->v[k]   = (UINT8) pImage->Pixels[index].rgb[0];
						pVect->v[k+1] = (UINT8) pImage->Pixels[index].rgb[1];
						pVect->v[k+2] = (UINT8) pImage->Pixels[index].rgb[2];
						pVect->v[k+3] = (UINT8) pAlpha->Pixels[index];

						k+=(VECLEN/4);

						index ++;
					}
				}

				/*
				// Convert the RGB representation of the vector into
				// the "visual perception" space
				*/
				

				MatrixVectorMul(pVect,  RGBToPerception, pVect);


				/*
				// Move on to the next vector
				*/
				pVect++;
				VectCount ++;

			}/*end for xPos*/ 
		
		}/*end for yPos*/ 

		/*
		// Allocate image code space
		*/
		pMipmaps->mipEntry[l].pImageCodes =
			(CODE_IMAGE_STRUCT *) malloc( sizeof(CODE_IMAGE_STRUCT) );
		if( pMipmaps->mipEntry[l].pImageCodes == NULL)
		{
			printf("Out of memory\n");
			return;/*exit(-99);*/
		}
		pMipmaps->mipEntry[l].pImageCodes->PixelCodes = 
			(unsigned char *) malloc( sizeof(unsigned char) * pImageVecs->NumVects);

		if( pMipmaps->mipEntry[l].pImageCodes->PixelCodes == NULL)
		{
			printf("Out of memory\n");
			return;/*exit(-99);*/
		}
	}
	
	/* 
	// Convert single pixel MIP-map to 4 texels 
	*/
	if(pMipmaps->numMipmapLevels>1)
	{	
		pImage = pMipmaps->mipEntry[l].pImage;
		
		pMipmaps->mipEntry[l].pImageVecs = (IMAGE_VECTOR_STRUCT *) malloc( sizeof(IMAGE_VECTOR_STRUCT) );
		if( pMipmaps->mipEntry[l].pImageVecs == NULL)
		{
			printf("Out of memory\n");
			return;/*exit(-99);*/
		}

		pImageVecs = pMipmaps->mipEntry[l].pImageVecs;
		pImageVecs->NumVects = 1;
		pImageVecs->mtVectors = (MT_PIXEL_VECT *) malloc( sizeof(MT_PIXEL_VECT) );
		if( pImageVecs->mtVectors == NULL)
		{
			return;/*exit(-99);*/
		}

		pVect = pImageVecs->mtVectors;

		for(i = 0; i < 4; i++)
		{
				pVect->v[i*4  ] = (unsigned char) pImage->Pixels[0].rgb[0];
				pVect->v[i*4+1] = (unsigned char) pImage->Pixels[0].rgb[1];
				pVect->v[i*4+2] = (unsigned char) pImage->Pixels[0].rgb[2];
				pVect->v[i*4+3] = (unsigned char) pAlpha->Pixels[0];
		}
		
		/* Convert to preception space */
		MatrixVectorMul(pVect,  RGBToPerception, pVect);

		/*
		// Allocate image code space
		*/
		pMipmaps->mipEntry[l].pImageCodes =
			(CODE_IMAGE_STRUCT *) malloc( sizeof(CODE_IMAGE_STRUCT) );
		if( pMipmaps->mipEntry[l].pImageCodes == NULL)
		{
			printf("Out of memory\n");
			return;/*exit(1);*/
		}
		pMipmaps->mipEntry[l].pImageCodes->PixelCodes = 
			(unsigned char *) malloc( sizeof(unsigned char) );

		if( pMipmaps->mipEntry[l].pImageCodes->PixelCodes == NULL)
		{
			printf("Out of memory\n");
			return;/*exit(-99);*/
		}

	}
}

/********************************************************
*
*  Converts Code book from RGB space
*
*********************************************************/


void ConvertCodeBookFromRGB(CODE_BOOK_STRUCT * pBook)
{
	int k;
	CODE_DATA_STRUCT *pCode;
	/*
	// Map each vector back to perception space
	*/
	pCode = pBook->Codes;
	for(k = 0; k < pBook->NumUsedCodes; k ++, pCode ++)
	{
		/*
		// Do the mapping
		*/
		MatrixVectorMul(&pCode->mtRepVector, RGBToPerception, &pCode->mtRepVector);

		
		
	}
}


/********************************************************
*
*  Converts Code book to RGB space
*
*********************************************************/

void ConvertCodeBookToRGB(CODE_BOOK_STRUCT * pBook, 
												  int nFormat)
{
	int k, j;
	CODE_DATA_STRUCT *pCode;

	ASSERT((nFormat == FORMAT_4444) || (nFormat == FORMAT_1555) || (nFormat == FORMAT_565));
	
	/*
	// Map each vector back to RGB
	*/
	pCode = pBook->Codes;
	for(k = 0; k < pBook->NumUsedCodes; k ++, pCode ++)
	{
		/*
		// Do the mapping
		*/
		MatrixVectorMul(&pCode->mtRepVector, PerceptionToRGB, &pCode->mtRepVector);


		/*
		// Clamp the components to the required range
		*/
		for(j = 0; j < VECLEN; j++)
		{
			float PrecisionClamp = PrecisionClamper[nFormat][j&3];

			/*
			// This rounds the colour component to the nearest representable
			// value (i think)- atually we could do better, but it takes a bit
			// of messing about.
			*/

			pCode->mtRepVector.v[j] = PrecisionClamp *
		    (int)(pCode->mtRepVector.v[j] / PrecisionClamp + 0.5f);

			if(pCode->mtRepVector.v[j] < 0.0f)
			{
				pCode->mtRepVector.v[j] = 0.0f;
			}
			else if(pCode->mtRepVector.v[j] > 255.0f)
			{
				pCode->mtRepVector.v[j] = 255.0f;
			}

		}/*for j*/
	}
}




void Clamp(CODE_BOOK_STRUCT * pBook,  int nFormat)
{
	int k, j;
	CODE_DATA_STRUCT *pCode;

	ASSERT((nFormat == FORMAT_4444) || (nFormat == FORMAT_1555) || (nFormat == FORMAT_565));
	
	/*
	// Map each vector back to RGB
	*/
	pCode = pBook->Codes;
	for(k = 0; k < pBook->NumUsedCodes; k ++, pCode ++)
	{

		/*
		// Clamp the components to the required range
		*/
		for(j = 0; j < VECLEN; j++)
		{
			float PrecisionClamp = PrecisionClamper[nFormat][j&3];

			/*
			// This rounds the colour component to the nearest representable
			// value (i think)- atually we could do better, but it takes a bit
			// of messing about.
			*/

			pCode->mtRepVector.v[j] =  PrecisionClamp *
		   (int)(pCode->mtRepVector.v[j] / PrecisionClamp + 0.5f);

			if(pCode->mtRepVector.v[j] < 0.0f)
			{
				pCode->mtRepVector.v[j] = 0.0f;
			}
			else if(pCode->mtRepVector.v[j] > 255.0f)
			{
				pCode->mtRepVector.v[j] = 255.0f;
			}

		}/*for j*/
	}
}

void ReconstructCompressedImage(	MIPMAPS *pMipmaps,
										const CODE_BOOK_STRUCT * pBook,
										int		   ShowPageBreaks)
{
	int yPos=0, xPos=0, i, j, l;
	int VecsMaxX=0, VecsMaxY=0;
	CODE_IMAGE_STRUCT *pImageCodes;
	IMAGE_STRUCT *pImage;
	ALPHA_STRUCT *pAlpha;
	const CODE_DATA_STRUCT *pBestCode;

	const unsigned char *pCodeIndex;
	
	int bannana=0;
	/*
	// Step through all the MIP-map levels except the last one
	*/

	/* No explanation will be given: well allright: miss out 1x1, but watch for non-mipmap case*/
	bannana = pMipmaps->numMipmapLevels-1;
	if (bannana==0)
		bannana++;

	for(l = 0; l < bannana; l++)
	{
		pImageCodes = pMipmaps->mipEntry[l].pImageCodes;
		pImage = pMipmaps->mipEntry[l].pImage; 
		pAlpha = pMipmaps->mipEntry[l].pAlpha;

	 	VecsMaxX = 	(pImage->xDim + PIXEL_BLOCK_SIZE -1) / PIXEL_BLOCK_SIZE;
		VecsMaxY = 	(pImage->yDim + PIXEL_BLOCK_SIZE -1) / PIXEL_BLOCK_SIZE;

		/*
		// Step through all the image's codes
		*/
		pCodeIndex =  pImageCodes->PixelCodes;

		for(yPos = 0; yPos < VecsMaxY; yPos++)
		{
			int yLower = yPos * PIXEL_BLOCK_SIZE; 

			for(xPos = 0; xPos < VecsMaxX; xPos++)
			{
				int k =0;
				int xLower= xPos * PIXEL_BLOCK_SIZE;

				/*
				// Get the closest
				*/
				pBestCode = pBook->Codes + *pCodeIndex;	


				if(!ShowPageBreaks)
				{

					/*
					// Store this vector in the appropriate place in the
					// image
					*/
					for(i = yLower; i < yLower + PIXEL_BLOCK_SIZE; i++)
					{
						for(j = xLower; j < xLower + PIXEL_BLOCK_SIZE; j++)
						{
							pImage->Pixels[i*VecsMaxX*2+j].rgb[0] = ( unsigned char)
								pBestCode->mtRepVector.v[k];
							pImage->Pixels[i*VecsMaxX*2+j].rgb[1] = ( unsigned char)
								pBestCode->mtRepVector.v[k+1];
							pImage->Pixels[i*VecsMaxX*2+j].rgb[2] = ( unsigned char)
								pBestCode->mtRepVector.v[k+2];
							pAlpha->Pixels[i*VecsMaxX*2+j] =  ( unsigned char)
								pBestCode->mtRepVector.v[k+3];

							k+=(VECLEN/4);
						}
					}/*end for i*/
				}
				/*
				// Else we want to show page break occurences
				// "White" will mean all four neighbours give a break, while black
				// will mean none of them do. 1 to 3 will give the various values of
				// grey.
				*/
				else
				{
					int NumBreaks = 0;
					int ThisCodesPage = (*pCodeIndex) / CODES_PER_PAGE;
					int Temp=0;
					
					/* 
					// look at the neighbours. For simplicity, assume wrap around
					//
					// Look at the one to the left
					*/
					Temp = *(pImageCodes->PixelCodes + (VecsMaxX * yPos) + 
						   (xPos + VecsMaxX -1) % VecsMaxX ) / CODES_PER_PAGE;
					if(Temp != ThisCodesPage)
					{
						NumBreaks++;
					}
					/*
					// And the one to the right
					*/
					Temp = *(pImageCodes->PixelCodes + (VecsMaxX * yPos) + 
						   (xPos + 1) % VecsMaxX ) / CODES_PER_PAGE;
					if(Temp != ThisCodesPage)
					{
						NumBreaks++;
					}

					/*
					// The one above
					*/
					Temp = *(pImageCodes->PixelCodes + 
						   (VecsMaxX * ((yPos + VecsMaxY -1) % VecsMaxY)) + 
						    xPos) / CODES_PER_PAGE;
					if(Temp != ThisCodesPage)
					{
						NumBreaks++;
					}

					/*
					// And The one above
					*/
					Temp = *(pImageCodes->PixelCodes + 
						   (VecsMaxX * ((yPos + 1) % VecsMaxY)) + 
						   xPos) / CODES_PER_PAGE;
					if(Temp != ThisCodesPage)
					{
						NumBreaks++;
					}

					/*
					// Colour it all in
					*/
					for(i = yLower; i < yLower + PIXEL_BLOCK_SIZE; i++)
					{
						for(j = xLower; j < xLower + PIXEL_BLOCK_SIZE; j++)
						{
							static const UINT8 BC[5][3] =
							{{ 0,0,0},
							 { 0,0, 128},
							 { 128, 0, 128},
							 { 255, 0, 0},
							 {255, 255, 0}};

							pImage->Pixels[i*VecsMaxX*2+j].rgb[0] = BC[NumBreaks][0];
							pImage->Pixels[i*VecsMaxX*2+j].rgb[1] = BC[NumBreaks][1];
							pImage->Pixels[i*VecsMaxX*2+j].rgb[2] = BC[NumBreaks][2];
							pAlpha->Pixels[i*VecsMaxX*2+j] =  0; /*Who cares*/

							k+=(VECLEN/4);
						}
						}/*end for i*/

				}
				
				pCodeIndex++;

			}/*end for x*/
		}/*end for y*/
	}/*end for l*/

	/* Do 1x1 mipmap level: taken from 0,0 pixel in 2x2 vector: */
		if ( pMipmaps->numMipmapLevels == 1)
			return;
	
		pImageCodes = pMipmaps->mipEntry[l].pImageCodes;
		pImage = pMipmaps->mipEntry[l].pImage; 
		pAlpha = pMipmaps->mipEntry[l].pAlpha;

		pCodeIndex =  pImageCodes->PixelCodes;
		pBestCode = pBook->Codes + *pCodeIndex;	
		
		pImage->Pixels[0].rgb[0] = ( unsigned char) pBestCode->mtRepVector.v[0];
		pImage->Pixels[0].rgb[1] = ( unsigned char) pBestCode->mtRepVector.v[1];
		pImage->Pixels[0].rgb[2] = ( unsigned char) pBestCode->mtRepVector.v[2];

		pAlpha->Pixels[0] =  ( unsigned char) pBestCode->mtRepVector.v[3];

}




void ViewCompressedImage(	MIPMAPS *pMipmaps,
										const CODE_BOOK_STRUCT * pBook,
										int		   ShowPageBreaks)
{
	int yPos=0, xPos=0, i, j, l;
	int VecsMaxX=0, VecsMaxY=0;
	CODE_IMAGE_STRUCT *pImageCodes;
	IMAGE_STRUCT *pImage;
	ALPHA_STRUCT *pAlpha;
	const CODE_DATA_STRUCT *pBestCode;

	const unsigned char *pCodeIndex;

	/*
	// Step through all the MIP-map levels
	*/

	l = 0;

		pImageCodes = pMipmaps->mipEntry[l].pImageCodes;
		pImage = pMipmaps->mipEntry[l].pImage; 
		pAlpha = pMipmaps->mipEntry[l].pAlpha;

	 	VecsMaxX = 	(pImage->xDim + PIXEL_BLOCK_SIZE -1) / PIXEL_BLOCK_SIZE;
		VecsMaxY = 	(pImage->yDim + PIXEL_BLOCK_SIZE -1) / PIXEL_BLOCK_SIZE;

		/*
		// Step through all the image's codes
		*/
		pCodeIndex =  pImageCodes->PixelCodes;

		for(yPos = 0; yPos < VecsMaxY; yPos++)
		{
			int yLower = yPos * PIXEL_BLOCK_SIZE; 

			for(xPos = 0; xPos < VecsMaxX; xPos++)
			{
				int k =0;
				int xLower= xPos * PIXEL_BLOCK_SIZE;

				/*
				// Get the closest
				*/
				pBestCode = pBook->Codes + *pCodeIndex;	



					/*
					// Store this vector in the appropriate place in the
					// image
					*/
					for(i = yLower; i < yLower + PIXEL_BLOCK_SIZE; i++)
					{
						for(j = xLower; j < xLower + PIXEL_BLOCK_SIZE; j++)
						{
							pImage->Pixels[i*VecsMaxX*2+j].rgb[0] = ( unsigned char)
								pBestCode->mtRepVector.v[k];
							pImage->Pixels[i*VecsMaxX*2+j].rgb[1] = ( unsigned char)
								pBestCode->mtRepVector.v[k+1];
							pImage->Pixels[i*VecsMaxX*2+j].rgb[2] = ( unsigned char)
								pBestCode->mtRepVector.v[k+2];
							pAlpha->Pixels[i*VecsMaxX*2+j] =  ( unsigned char)
								pBestCode->mtRepVector.v[k+3];

							k+=(VECLEN/4);
						}
					}/*end for i*/

	
				
				pCodeIndex++;

			}/*end for x*/
		}/*end for y*/

}
/******************************************************************************
 * From			: mipmap.c
 * Title		: Vector Quantisation Compression Code
 * Author		: Simon Fenney.
 * Created		: 17/03/1997
 ******************************************************************************/
void GenerateReducedImages( MIPMAPS *pMipmaps, int Use4x4 )
{
	int i, j; 
	int l = 0;
	IMAGE_STRUCT *pImage, *pBigImage;
	ALPHA_STRUCT *pAlpha, *pBigAlpha;

	int FilK[4][4];
	int divisor=0;
	int rounding=0;

	/*
	// Set up the filter kernel
	*/
	for(i=0; i< 4; i++)
	{
		for(j=0; j < 4; j++)
		{
			if(Use4x4)
			{
				FilK[i][j]	= FilterWeights4x4[i][j];
			}
			else
			{
				FilK[i][j]	= FilterWeights2x2[i][j];
			}
		}
	}/*for i*/
	/*
	// Work out the divisor and averager
	*/
	divisor = 0;

	for(i=0; i< 4; i++)
	{
		for(j=0; j < 4; j++)
		{
			divisor+= FilK[i][j]; 
		}
	}
	rounding = divisor / 2;

	/* Use this to multiply after doing shift rights */
	divisor = (int) ( 2048.0f / divisor + 0.5f);



	while( pMipmaps->mipEntry[l].pImage->xDim > 0)
	{
		pBigImage = pMipmaps->mipEntry[l].pImage;
		pBigAlpha = pMipmaps->mipEntry[l].pAlpha;
		l++;
		
		/*
		// Allocate new space for new MIP-map level
		*/
		
		/*
		// Allocate image space
		*/
		pMipmaps->mipEntry[l].pImage = (IMAGE_STRUCT *) malloc( sizeof(IMAGE_STRUCT) );
		if( pMipmaps->mipEntry[l].pImage == NULL)
		{
			printf("Out of memory\n");
			return;/*exit(-99);*/
		}
		pImage = pMipmaps->mipEntry[l].pImage;
		
		pImage->xDim = pBigImage->xDim/2; 	
		pImage->yDim = pBigImage->yDim/2;
		 	
		pImage->Pixels = 
			(PIXEL_STRUCT *) malloc( sizeof(PIXEL_STRUCT) * pImage->xDim * pImage->yDim);
		if( pImage->Pixels == NULL)
		{
			printf("Out of memory\n");
			return;/*exit(-99);*/
		}

		/*
		// Allocate alpha space
		*/
		pMipmaps->mipEntry[l].pAlpha = (ALPHA_STRUCT *) malloc( sizeof(ALPHA_STRUCT) );
		if( pMipmaps->mipEntry[l].pAlpha == NULL)
		{
			printf("Out of memory\n");
			return;/*exit(-99);*/
		}
		pAlpha = pMipmaps->mipEntry[l].pAlpha;
	 	
		pAlpha->Pixels = 
			(unsigned char *) malloc( sizeof(PIXEL_STRUCT) * pImage->xDim * pImage->yDim);
		if( pAlpha->Pixels == NULL)
		{
			printf("Out of memory\n");
			return;/*exit(-99);*/
		}



		for(i = 0; i < pImage->yDim; i++)
		{
			for(j = 0; j < pImage->xDim; j++)
			{
				int KerX=0, KerY=0;
				int xyPos=0, yPos=0;
				int RGBSum[3]={0,0,0};
				int AlphaSum=0;
				int col=0;


				AlphaSum = rounding;
				for(col = 0; col <3; col ++)
				{
					RGBSum[col] = rounding;
				}
				
				/*
				// Apply the filter to generate the current pixel
				*/
				for(KerY = 0; KerY < 4; KerY++)
				{
					/*
					// Compute the Src Y position
					*/
					yPos =((i * 2 + pBigImage->yDim + KerY - 1) % pBigImage->yDim) * pBigImage->xDim;

					for(KerX = 0; KerX < 4; KerX++)
					{
						/*
						// Compute the combined XY position
						*/
						xyPos = ((j * 2 + pBigImage->xDim + KerX - 1) % pBigImage->xDim) + yPos;


						/*
						// Do RGB
						*/
						for(col = 0; col <3; col ++)
						{
							RGBSum[col] += FilK[KerY][KerX] * 
								(int) pBigImage->Pixels[xyPos].rgb[col];
						}
						/*
						// Do alpha
						*/
						AlphaSum += FilK[KerY][KerX] * (int) pBigAlpha->Pixels[xyPos];

					}/*end for KerX*/

				}/*end for KerY*/

				/*
				// Produce the final result
				*/
				for(col = 0; col <3; col ++)
				{				
		  			pImage->Pixels[i*pImage->xDim + j].rgb[col] = 
		  				(unsigned char) ((RGBSum[col] * divisor) >> 11);
				}


				pAlpha->Pixels[i*pImage->xDim + j] = 
						(unsigned char) ((AlphaSum * divisor) >> 11);
	 		
	 		
			}/*end for j*/
	  	}/*end for i*/

	}
	pMipmaps->numMipmapLevels = l;				
}
UINT8 add(UINT8 a, int b)
{
	b = a+b;
	if (b<0) { b = 0;}
	if (b>255) { b = 255;}

	return (UINT8) b;
}
/******************************************************************************
 * From			: dither.c
 * Title		: Vector Quantisation Compression Code
 * Author		: Julian Hodgson.
 * Created		: 17/03/1997
 ******************************************************************************/
void	  Dither( PIXEL_STRUCT *rgb, UINT8 *pAlpha, 
				  int nFormat, int nTranslucent, int xDim, int yDim)
{
	int j, count=0, index=0;
	PIXEL_STRUCT current_pix;
	PIXEL_STRUCT *Pix_Ptr;
	UINT8 current_alph=0;
	
	/* Prevent compiler warnings */

	typedef struct pix{ int rgb[3]; }PIX_INT;

	PIX_INT	 error_pix;
	int error_alph;

	error_alph = 0;

 
	for ( j = 0; j < yDim; j++)
	{
		index = j*xDim - 1;
		
		count = xDim;

		while (count>0)
		{
			count--;
			index ++;

			ASSERT(index<xDim*yDim);
			
			current_pix = rgb[index];
			
			Pix_Ptr = &(rgb[index]);
			
			if ( nTranslucent) {
				current_alph = pAlpha[index];	
			}

			/* 1) Scale down, round to nearest int.
			// 2) Scale back, round to nearest UINT8 (unsigned char).
			*/

			Pix_Ptr->rgb[0] = ( unsigned char) (
				0.5f + PrecisionClamper[nFormat][0] *
				(int)(current_pix.rgb[0] / PrecisionClamper[nFormat][0] + 0.5f)
			);

			Pix_Ptr->rgb[1] = ( unsigned char) (
				0.5f + PrecisionClamper[nFormat][1] *
				(int)(current_pix.rgb[1] / PrecisionClamper[nFormat][1] + 0.5f)
			);

			Pix_Ptr->rgb[2] = ( unsigned char) (
				0.5f + PrecisionClamper[nFormat][2] *
				(int)(current_pix.rgb[2] / PrecisionClamper[nFormat][2] + 0.5f)
			);

			if (nTranslucent) {
			   pAlpha[index] = ( unsigned char) (
					0.5f + PrecisionClamper[nFormat][3] *
					(int)(current_alph / PrecisionClamper[nFormat][3] + 0.5f)
				);
			}

			/* Find error as int - could be negative */ 
			

			error_pix.rgb[0] = Pix_Ptr->rgb[0] - current_pix.rgb[0];
   			error_pix.rgb[1] = Pix_Ptr->rgb[1] - current_pix.rgb[1];
			error_pix.rgb[2] = Pix_Ptr->rgb[2] - current_pix.rgb[2]; 

			if (nTranslucent) {
			   error_alph = pAlpha[index] - current_alph ;
			   }

			/* Diffuse error: 
			// at the minute just to the next pixel
			// (in the direction of sense) and not for
			// last in row
			*/

			if (count) {

			   index ++;
				ASSERT(index<xDim*yDim);			
			   Pix_Ptr = &rgb[index];

			   Pix_Ptr->rgb[0] = add(Pix_Ptr->rgb[0], error_pix.rgb[0]);
			   Pix_Ptr->rgb[1] = add(Pix_Ptr->rgb[1], error_pix.rgb[1]);
			   Pix_Ptr->rgb[2] = add(Pix_Ptr->rgb[2], error_pix.rgb[2]);
   				  
			   if (nTranslucent) { 
				  pAlpha[index] = add(pAlpha[index],error_alph);
			   }

			   index --;
			}
		} /* end for while */
	} /* end for j */

}


/**************************************************
//
// Dither image using Floyd-Steinberg Error
// diffusion method.
//
***************************************************/
/*
// Diffuses error over four squares:   o-1
// 	   				        		  /|\
//									 2 3 4
//
// 1: 7/16, 2: 3/16, 3: 5/16, 4: 1/16
*/



void	  Dither4Square( PIXEL_STRUCT *rgb_data, UINT8 *pAlpha, 
				  int nFormat, int nTranslucent, int xDim, int yDim)
{
	/* nTranslucent = 1 means do alpha channel */

	int j, count=0, index=0;
	int NumPixels=0;

	PIXEL_STRUCT current_pix;
	PIXEL_STRUCT *Pix_Ptr;

	UINT8 current_alph;

	MATH_TYPE sixteenth = 1.0f / 16.0f;

	unsigned char first_col, final_row=1;   

	/* Errors may be negative so use integers */

	typedef struct pix{ int rgb[3]; }PIX_INT;

	PIX_INT	 error_pix, erpix_1, erpix_2, erpix_3, erpix_4;
	int error_alph=0, eralp_1=0, eralp_2=0, eralp_3=0, eralp_4=0;

	/* Prevent compiler warnings */

	error_alph = eralp_1 = eralp_2 = eralp_3 = eralp_4 = 0;

	NumPixels = xDim * yDim;
	/*
	// we will dither alternatively from left to right 
	// then right to left - it's better that way
	*/ 

	for ( j = 0; j < yDim; j++)
	{
		index = j*xDim;

		index--;
		
		count = xDim;
		first_col = 0;
		if (j==yDim-1) { final_row=0;}	

		while (count>0)
		{
			count--;
			index ++;
			ASSERT( index < NumPixels);
			current_pix = rgb_data[index];
			Pix_Ptr = &rgb_data[index];
			
			if ( nTranslucent) {
				current_alph = pAlpha[index];			
			}

			/* 1) Scale down, round to nearest int.
			// 2) Scale back, round to nearest int.
			*/

			Pix_Ptr->rgb[0] = ( unsigned char) (
				0.5f + PrecisionClamper[nFormat][0] *
				(int)(current_pix.rgb[0] / PrecisionClamper[nFormat][0] + 0.5f)
			);

			Pix_Ptr->rgb[1] = ( unsigned char) (
				0.5f + PrecisionClamper[nFormat][1] *
				(int)(current_pix.rgb[1] / PrecisionClamper[nFormat][1] + 0.5f)
			);

			Pix_Ptr->rgb[2] = ( unsigned char) (
				0.5f + PrecisionClamper[nFormat][2] *
				(int)(current_pix.rgb[2] / PrecisionClamper[nFormat][2] + 0.5f)
			);

			if (nTranslucent) {
			   pAlpha[index] = ( unsigned char) (
					0.5f + PrecisionClamper[nFormat][3] *
					(int)(current_alph / PrecisionClamper[nFormat][3] + 0.5f)
					);
			}

			/* Find error (as unsigned char) */ 
			
			error_pix.rgb[0] = current_pix.rgb[0] - Pix_Ptr->rgb[0];
   			error_pix.rgb[1] = current_pix.rgb[1] - Pix_Ptr->rgb[1];
			error_pix.rgb[2] = current_pix.rgb[2] - Pix_Ptr->rgb[2];

			if (nTranslucent) {
			   error_alph = current_alph - pAlpha[index];
			   }

			/* Divide error in Floyd-Steinberg ratios.
			// Notice that the last error is defined as
			// the remains of the other pieces so nothing
			// will be lost.
			// The errors are defined - see function header note.
			*/

			/* Using floor since the numbers may be negative */
			
			erpix_1.rgb[0] = (8 + 7 * error_pix.rgb[0]) >> 4;
			erpix_1.rgb[1] = (8 + 7 * error_pix.rgb[1]) >> 4;
			erpix_1.rgb[2] = (8 + 7 * error_pix.rgb[2]) >> 4;

			erpix_2.rgb[0] = (8 + 3 * error_pix.rgb[0]) >> 4;
			erpix_2.rgb[1] = (8 + 3 * error_pix.rgb[1]) >> 4;
			erpix_2.rgb[2] = (8 + 3 * error_pix.rgb[2]) >> 4;

			erpix_3.rgb[0] = (8 + 5 * error_pix.rgb[0]) >> 4;
			erpix_3.rgb[1] = (8 + 5 * error_pix.rgb[1]) >> 4;
			erpix_3.rgb[2] = (8 + 5 * error_pix.rgb[2]) >> 4;

			erpix_4.rgb[0] = error_pix.rgb[0] - erpix_1.rgb[0]
						   - erpix_2.rgb[0] - erpix_3.rgb[0];
			erpix_4.rgb[1] = error_pix.rgb[1] - erpix_1.rgb[1]
						   - erpix_2.rgb[1] - erpix_3.rgb[1];
			erpix_4.rgb[2] = error_pix.rgb[2] - erpix_1.rgb[2]
						   - erpix_2.rgb[2] - erpix_3.rgb[2];

			if (nTranslucent) {
			   eralp_1 = (8 + 7 * error_alph) >> 4;
			   eralp_2 = (8 + 3 * error_alph) >> 4;
			   eralp_3 = (8 + 5 * error_alph) >> 4;
			   eralp_4 = error_alph - eralp_1 - eralp_2 - eralp_3;
			}


			/*  
			// Diffuse error
			*/

			if (!final_row)
			{				   
			   /* Final row */
			   
			   if (count)
			   {
				  /* Not final pixel */
				  /* Do one! */

				  index ++;

				  ASSERT( index < NumPixels);

				  Pix_Ptr = &rgb_data[index];

				  Pix_Ptr->rgb[0] = add(Pix_Ptr->rgb[0], erpix_1.rgb[0]);
				  Pix_Ptr->rgb[1] = add(Pix_Ptr->rgb[1], erpix_1.rgb[1]);
				  Pix_Ptr->rgb[2] = add(Pix_Ptr->rgb[2], erpix_1.rgb[2]);	
	  
				  if (nTranslucent) 
				  {
				  pAlpha[index] = add(pAlpha[index],eralp_1);
				  }
	
				  /* Reset index */

				  index --;

			   }
			} 
			else if (!count)
			{
			   /* Last col */
			   /* Do 3, 2  */

			   index += xDim;

			   ASSERT( index < NumPixels);

			   Pix_Ptr = &rgb_data[index];

			   Pix_Ptr->rgb[0] = add(Pix_Ptr->rgb[0], erpix_3.rgb[0]);
			   Pix_Ptr->rgb[1] = add(Pix_Ptr->rgb[1], erpix_3.rgb[1]);
			   Pix_Ptr->rgb[2] = add(Pix_Ptr->rgb[2], erpix_3.rgb[2]);	
	  
			   if (nTranslucent) 
			   {
			   pAlpha[index] = add(pAlpha[index],eralp_3);
			   }

			   index --;

			   Pix_Ptr = &rgb_data[index];

			   Pix_Ptr->rgb[0] = add(Pix_Ptr->rgb[0], erpix_2.rgb[0]);
			   Pix_Ptr->rgb[1] = add(Pix_Ptr->rgb[1], erpix_2.rgb[1]);
			   Pix_Ptr->rgb[2] = add(Pix_Ptr->rgb[2], erpix_2.rgb[2]);	
	  
			   if (nTranslucent) 
			   {
			   pAlpha[index] = add(pAlpha[index],eralp_2);
			   }
			   
			   /* Reset index */

			   index ++;
			   index -= xDim;

			} 
			else
			{
			   /* Either generic case or first col */

			   if (first_col)
			   {
				  /* Not first col */
				  /* Do 2	       */

				  index += xDim;
				  index --;

				  ASSERT( index < NumPixels);

				  Pix_Ptr = &rgb_data[index];

				  Pix_Ptr->rgb[0] = add(Pix_Ptr->rgb[0], erpix_2.rgb[0]);
				  Pix_Ptr->rgb[1] = add(Pix_Ptr->rgb[1], erpix_2.rgb[1]);
				  Pix_Ptr->rgb[2] = add(Pix_Ptr->rgb[2], erpix_2.rgb[2]);	
	  
				  if (nTranslucent) 
				  {
				  pAlpha[index] = add(pAlpha[index],eralp_2);
				  }
	
				  /* Reset index */

				  index ++;
				  index -= xDim;

			   }

			   /* Do 3, 4, 1 */

			   index += xDim;
			   
			   Pix_Ptr = &rgb_data[index];

			   Pix_Ptr->rgb[0] = add(Pix_Ptr->rgb[0], erpix_3.rgb[0]);
			   Pix_Ptr->rgb[1] = add(Pix_Ptr->rgb[1], erpix_3.rgb[1]);
			   Pix_Ptr->rgb[2] = add(Pix_Ptr->rgb[2], erpix_3.rgb[2]);	
	  
			   if (nTranslucent) 
			   {
			   pAlpha[index] = add(pAlpha[index],eralp_3);
			   }

			   index ++;
	
			   Pix_Ptr = &rgb_data[index];

			   Pix_Ptr->rgb[0] = add(Pix_Ptr->rgb[0], erpix_4.rgb[0]);
			   Pix_Ptr->rgb[1] = add(Pix_Ptr->rgb[1], erpix_4.rgb[1]);
			   Pix_Ptr->rgb[2] = add(Pix_Ptr->rgb[2], erpix_4.rgb[2]);	
	  
			   if (nTranslucent) 
			   {
			   pAlpha[index] = add(pAlpha[index],eralp_4);
			   }

			   index ++;
			   index -= xDim;

			   Pix_Ptr = &rgb_data[index];

			   Pix_Ptr->rgb[0] = add(Pix_Ptr->rgb[0], erpix_1.rgb[0]);
			   Pix_Ptr->rgb[1] = add(Pix_Ptr->rgb[1], erpix_1.rgb[1]);
			   Pix_Ptr->rgb[2] = add(Pix_Ptr->rgb[2], erpix_1.rgb[2]);	
	  
			   if (nTranslucent) 
			   {
			   pAlpha[index] = add(pAlpha[index],eralp_1);
			   }

			   /* Reset index */

			   index --;
			   index --;

			}

		first_col = 1; 

		} /* end for while */
	} /* end for j */

}
/******************************************************************************
 * From			: matrix.c
 * Title		: Vector Quantisation Compression Code
 * Author		: Simon Fenney.
 * Created		: 17/03/1997
 ******************************************************************************/
void MatrixMatrixMul( Mat16x16Type Result, 
					   const Mat16x16Type mA, 
					   const Mat16x16Type mB)
{
	Mat16x16Type TempMat;
	float fTemp=0;
	int i,j,k;

	for(i=0; i < VECLEN; i++)
	{
		for(j=0; j < VECLEN; j++)
		{
			fTemp = 0.0f;

			/*
			// Hopefully the compiler will unwind this loop
			*/
			for(k=0; k < VECLEN; k++)
			{
				fTemp+= mA[i][k] * mB[k][j];
			}
			TempMat[i][j] = fTemp;
		}
	}/*end for i*/


	/*
	// Copy the temporary matrix over
	*/
	memcpy(Result, TempMat, sizeof(Mat16x16Type));

}/*end matrix matrix mul*/

/****************/
/****************/
/****************/

/*
// Multiply a matrix by vector to give another matrix
*/
void MatrixVectorMul( MT_PIXEL_VECT *pResult, 
							 const Mat16x16Type Mat,
							 const MT_PIXEL_VECT *pVec)
{
	float fTemp=0;
	int i,j;

	MT_PIXEL_VECT Src;


	/*
	// Copy the source matrix just in case source and destination
	// are the same
	*/
	Src = *pVec;

	/*
	// Do the multiplication
	*/
	for(i=0; i < VECLEN; i++)
	{
		fTemp = 0.0f;

		/*
		// Hopefully the compiler will unwind this loop
		*/
		for(j=0; j < VECLEN; j++)
		{
			fTemp+= Mat[i][j] * Src.v[j];
		}
		pResult->v[i] = fTemp;
	}/*end for i*/

}/*end matrix matrix mul*/

/****************/
/****************/
/****************/

void SetIdentMatrix( Mat16x16Type Result)
{
	int i,j;

	for(i=0; i < VECLEN; i++)
	{
		for(j=0; j < VECLEN; j++)
		{
			if(i==j)
			{
				Result[i][j] = 1.0f;
			}
			else
			{
				Result[i][j] = 0.0f;
			}
		}
	}/*end for i*/
}/*end matrix matrix mul*/

/****************/
/****************/
/****************/

void SetZeroMatrix( Mat16x16Type Result)
{
	int i,j;

	for(i=0; i < VECLEN; i++)
	{
		for(j=0; j < VECLEN; j++)
		{
			Result[i][j] = 0.0f;
		}
	}/*end for i*/
}/*end matrix matrix mul*/



void GenerateMappingMatrices(ColourSpaceModeType ColSpace, int DoFreq)
{
	int i,j, k;
	
	Mat16x16Type ScratchMatrix;

	/*
	// Initialise the mappings to be identities
	*/
	SetIdentMatrix(RGBToPerception);
	SetIdentMatrix(PerceptionToRGB);


	if( ColSpace == FreqYIQspace)
	{
	

	/*
	// Set up the RGB to YIQ mapping first.
	//
	// Basically the RGBtoYIQ mini matrix gets applied down the
	// main diagonal
	*/
	for(k = 0; k < VECLEN; k+=4)
	{
		for(i = 0; i < 3; i++)
		{
			for(j = 0; j < 3; j++)
			{
				RGBToPerception[i+k][j+k] = 
						RGBtoYIQ[i][j];			  
			}/*end for j*/
		}
	}/*end for k*/

	/*
	// Do the same for the YIQ to RGB
	*/
	for(k = 0; k < VECLEN; k+=4)
	{
		for(i = 0; i < 3; i++)
		{
			for(j = 0; j < 3; j++)
			{
				PerceptionToRGB[i+k][j+k] = 
							YIQtoRGB[i][j];			  
			}/*end for j*/
		}
	}/*end for k*/

#ifdef  DEBUG
	/*
	// Check that we get an identity matrix
	*/
	MatrixMatrixMul(ScratchMatrix, PerceptionToRGB, RGBToPerception);
	for(i = 0; i < VECLEN; i++)
	{
		for(j = 0; j < VECLEN; j++)
		{
			if(i==j)
			{
				ASSERT(fabs(ScratchMatrix[i][j] - 1.0f) < 0.001f);
			}
			else
			{
				ASSERT(fabs(ScratchMatrix[i][j]) < 0.001f);
			}
		}
	}/*end for k*/
		   
#endif

	/*
	// Weight these based on how well we can see each
	// of the YIQ components. I've taken this from
	// Foley and van Dam... It says how much bandwidth 
	// is given to them in the TV industry
	//
	// Please note: I'm doing this in a completely brain-dead
	// fashion to make the coding easier!
	*/
	SetIdentMatrix(ScratchMatrix);
	for(k = 0; k < VECLEN; k+=4)
	{
		for(i = 0; i < 3; i++)
		{
			ScratchMatrix[k+i][k+i] = YIQWeightings[i];
		}
	}/*end for k*/


	/*
	// Apply to the RGBtoP matrix
	*/
	MatrixMatrixMul(RGBToPerception, ScratchMatrix, RGBToPerception);

	/*
	// Keep building the inverse mapping
	*/
	for(k = 0; k < VECLEN; k+=4)
	{
		for(i = 0; i < 3; i++)
		{
			ScratchMatrix[k+i][k+i] = 1.0f / YIQWeightings[i];
		}
	}/*end for k*/

	/*
	// Apply to the P to RGB matrix. Note that the order is different!
	*/
	MatrixMatrixMul(PerceptionToRGB, PerceptionToRGB, ScratchMatrix);

#ifdef  DEBUG
	/*
	// Check that we get an identity matrix
	*/
	MatrixMatrixMul(ScratchMatrix, PerceptionToRGB, RGBToPerception);
	for(i = 0; i < VECLEN; i++)
	{
		for(j = 0; j < VECLEN; j++)
		{
			if(i==j)
			{
				ASSERT(fabs(ScratchMatrix[i][j] - 1.0f) < 0.001f);
			}
			else
			{
				ASSERT(fabs(ScratchMatrix[i][j]) < 0.001f);
			}
		}
	}/*end for k*/
		   
#endif

} /* End for if RGBspace */


/* Do Freq-Space business ! */

if ( DoFreq) {
	/*
	// Create the spatial to frequency domain matrix
	*/
	SetZeroMatrix(ScratchMatrix);
	for(k = 0; k < 4; k++)
	{
		for(i = 0; i < 4; i++)
		{
			for(j = 0; j < 4; j++)
			{
				ScratchMatrix[i*4 + k][j*4 + k] = 
					 SpaceToFreq[i][j];
			}/*end for j*/
		}
	}/*end for k*/
	MatrixMatrixMul(RGBToPerception, ScratchMatrix, RGBToPerception);
		
	/*
	// Create the spatial to frequency domain matrix
	*/
	SetZeroMatrix(ScratchMatrix);
	for(k = 0; k < 4; k++)
	{
		for(i = 0; i < 4; i++)
		{
			for(j = 0; j < 4; j++)
			{
				ScratchMatrix[i*4 + k][j*4 + k] = 
					 FreqToSpace[i][j];
			}/*end for j*/
		}
	}/*end for k*/
	MatrixMatrixMul(PerceptionToRGB, PerceptionToRGB, ScratchMatrix);




	/*
	// Weight these based on how well we percieve the frequencies?
	*/
	SetZeroMatrix(ScratchMatrix);
	for(k = 0; k < 4; k++)
	{
		for(i = 0; i < 4; i++)
		{
			ScratchMatrix[4*k+i][4*k+i] = FreqWeightings[k];
		}
	}/*end for k*/
	MatrixMatrixMul(RGBToPerception, ScratchMatrix, RGBToPerception);


	for(k = 0; k < 4; k++)
	{
		for(i = 0; i < 4; i++)
		{
			ScratchMatrix[4*k+i][4*k+i] = 1.0f / FreqWeightings[k];
		}
	}/*end for k*/
	MatrixMatrixMul(PerceptionToRGB, PerceptionToRGB, ScratchMatrix);




#ifdef  DEBUG
	/*
	// Check that we get an identity matrix
	*/
	MatrixMatrixMul(ScratchMatrix, PerceptionToRGB, RGBToPerception);
	for(i = 0; i < VECLEN; i++)
	{
		for(j = 0; j < VECLEN; j++)
		{
			if(i==j)
			{
				ASSERT(fabs(ScratchMatrix[i][j] - 1.0f) < 0.001f);
			}
			else
			{
				ASSERT(fabs(ScratchMatrix[i][j]) < 0.001f);
			}
		}
	}/*end for k*/
		   
#endif

	} /* end for if DoFreq */

	return;
}

/*
// End of file
*/

