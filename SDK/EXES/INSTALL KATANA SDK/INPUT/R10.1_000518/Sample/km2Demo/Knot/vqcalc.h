/******************************************************************************
 * Name			: VQCALC.H
 * Title		: Vector Quantisation Compression Code
 * Author		: Julian Hodgson, Simon Fenney and Rowland Fraser
 *				  
 * Created		: 17/03/1997 
 *
 * Modified     : 14/7/1999 by Carlos Sarria.
 *
 * Copyright	: 1997 by VideoLogic Limited. All rights reserved.
 *				: No part of this software, either material or conceptual 
 *				: may be copied or distributed, transmitted, transcribed,
 *				: stored in a retrieval system or translated into any 
 *				: human or computer language in any form by any means,
 *				: electronic, mechanical, manual or other-wise, or 
 *				: disclosed to third parties without the express written
 *				: permission of VideoLogic Limited, Unit 8, HomePark
 *				: Industrial Estate, King's Langley, Hertfordshire,
 *				: WD4 8LZ, U.K.
 *
 * Description	: Code for Vector Quantisation Compression of a 2D image.
 *				  
 *
 * Platform		: ANSI (HS4/CLX2 Set 2.24)
 ******************************************************************************/

/* Return messages */
#define VQ_OK			0
#define VQ_OUTOFMEMORY	1

/*
// set format
*/
#define	FORMAT_4444 0
#define	FORMAT_1555 1
#define FORMAT_565	2

typedef enum
{
	FreqYIQspace,
	RGBspace

} ColourSpaceModeType;

/******************************************************************************/
/*  THE ONLY EXTERN FUNTION                                                   */
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
							);

/***********************
	DESCRIPTION
 ***********************
InputArrayRGB:

Array of pixels, as in a windows bitmap with bottom right hand corner
first.  Colours go B, G, R.  No padding between lines.
The pixels are unaffected at function return.

InputArrayAlpha:

As above but just one byte of alpha per pixel.

OutputMemory:

The memory where the compressed vqf file will be written;
this must be preallocated.  You can find out how much you need 
by calling the function with this pointer NULL.

nWidth:

The size of the ( square) texture.  Should be one of the possible
sizes, 8 up to 1024 in multiples of 2.

bMipMap:

Do we mipmap the texture?

bAlphaOn:

Are you supplying an alpha to use?

bDither:

Are the images to be dithered?  If so then the colour channels AND the alpha
Channels, if present, are dithered.  Also, all the mipmap levels are dithered if
The mipmaps are being generated.  The pixels are dithered to the colour depth chosen, 
and the error is carried to neighbouring pixels.  The original pixels are not altered, 
however.
This tends to improve the compression of graduated images.

nNumCodes:

Number of codes used; possibles are 16, 32,.., 256, as in the VQGEN
program.  May not all be supported due to efficiency of compression 
ratios.

nColourFormat:

See defines.h for the colour formats, eg 4444, 565, etc...

nNumIterations:

Should be small for the 1024x1024 s! ( Speed).
Otherwise recommend 5 or 10.

bDoFreq:

Whether to do the calculations in frequency space - doesnt make
much difference

fColourWeights:

As in GUI.  Use defalut mostly, 1.0, 1.0, 1.0

fFreqWeights:

Use 1.0, 1.0, 1.0, 1.0. Could experiment.

bAlphaSense:

You can reverse the sense of alpha in the output file.

ColSpace:

Whether to use YIQ space or RGB space;  usually not much difference.

fPercentError:

Stop iterating when the RMS error falls below this percentage.  
Try 0.1

fErrorFound:

The error between the codes chosen and the original image is returned here.  It 
is the average error over all the pixels and over all the channels used, so takes 
into account whether the alpha channel is used.
This should give some idea of how well the codes fit the data, and will correlate 
with the image quality, although it may return different values for different images.



Usage of DLL:
-------------

The Dll should be called twice if you don't know how much memory is needed for the 
output file, once with OutputMemory passed NULL, upon which the function will return 
with the ammount of memory needed.
The second time just pass the pointer for the compressed memory.

Note:
-----

The natural world images often compress better when the images have first been dithered 
to the desired colour depth with error diffusion, using bDither.

VQGen with VqDll.Dll
--------------------

The .dll should go in the same directory as the .exe, or in the windows directory.
The .lib file should be included in the project that calls the Dll.


// END OF FILE
*/
