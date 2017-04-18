/*
// FILE: 		vqdll.h
//
// DECRIPTION: 	Prototype definitions for vqdll.dll, the dynamic link library
//		for PowerVR VQ texture compression.
//
//		Please use the first function interface: 
//		The second is there only for compatibility with old applications
//
// HISTORY:		Modified 18 November 1999, Simon Fenney
//
//				Created  1998  Julian Hodgson
//
//
//	$Log: vqdll.h,v $
 * Revision 1.5  2000/03/28  15:15:12  sjf
 * Added "grouped VQ" interface function.
 *
 * Revision 1.4  2000/01/10  15:42:29  sjf
 * Added "Vq" to the name of the info function.
 *
 * Revision 1.3  2000/01/10  15:19:11  sjf
 * Added function to return version info at request of Sega Europe.
 *
 * Revision 1.2  2000/01/06  15:18:22  sjf
 * Improved the comments in the file.
 *
//
//
*/


/*
//
//Usage of DLL:
//-------------
//
//The Dll should be called twice if you don't know how much memory is needed for the 
//output file, once with OutputMemory passed NULL, upon which the function will return 
//with the amount of memory needed.
//The second time just pass the pointer for the compressed memory.
//
//
//VQGen (or any other program using this dll) with VqDll.Dll
//--------------------
//
//The .dll should go in the same directory as the .exe, or in the windows directory.
//The .lib file should be included in the project that calls the Dll when the application
//is built.
*/

#ifndef MyDllExport
#define MyDllExport 
#endif

/*
// Define the interface types etc. 
//
// Note for IMG TECH: these MUST be the same as in vqcalc.h
*/
#ifndef VQ_OUTOFMEMORY	


/* Error Return messages */

#define VQ_OUTOFMEMORY	-1
#define VQ_INVALID_SIZE -2
#define VQ_INVALID_PARAMETER -3

/*
// Settings for output format
//
// Transparent formats. 
*/
#define	FORMAT_4444 (0)   /* The BEST mode for quality transparency*/
#define	FORMAT_1555 (1)	  /*This also doubles for the opaque 555 format*/

/*
// Opaque formats
*/
#define	FORMAT_555  (FORMAT_1555)
#define FORMAT_565	(2)   /*Either this of YUV is the best format for Opaque*/

#define FORMAT_YUV	(3)

/*
// for future expansion
*/
//#define FORMAT_BUMP	(4)


typedef enum
{
 	VQNoDither = 0,
	VQSubtleDither,
	VQFullDither
} VQ_DITHER_TYPES;


/*
// Colour space metrics
*/
typedef enum
{
 	VQMetricEqual = 0,	/*equal spacing*/
	VQMetricWeighted,

	/*
	// The following name is for backward compatibility only.
	*/
	VQMetricRGB = VQMetricEqual

} VQ_COLOUR_METRIC;


/*
// The following flag can be ORed with the previous values
// to form a variation on the colour metric. It makes the 
// compressor tolerate greater inaccuracy in high frequency
// changes.
*/
#define VQMETRIC_FREQUENCY_FLAG 0x10
#define VQ_BASE_METRIC_MASK     0x0F


/*
//MIP map modes
*/
typedef enum
{
	VQ_NO_MIPMAP = 0,    /*not recommended - it doesn't look good, and it can cause pagebreaks*/
	VQ_GENERATE_MIPMAP,  /*automatically generate the MIP map from base level*/
	VQ_SUPPLIED_MIPMAP	 /*The user has supplied the MIP map levels. These are assumed
						  *to have been packed from largest level to smallest in the supplied
						  *RGB and optional alpha data*/
}VQ_MIPMAP_MODES;


typedef enum
{
	VQ_GROUP_ALLOW_MIXED,
	VQ_GROUP_NO_MIXED
}VQ_GROUP_MODES;

#define VQ_MIXED_GROUP_ID (255)

#endif







/******************************************************************************/
/*
// Function: 	VqCalc2
//
// Description: DLL version of CreateVq function.
//				Given raw, packed 24 bit RBG data (with optional separate alpha),
//				this routine generates the VQ format as used by PowerVR2.
//
// Inputs:		InputArrayRGB 	Input data as a packed array of bytes
//				InputArrayAlpha	Optional alpha values
//				OutputMemory	Supplied memory for storage of resulting VQ data.
// 								If this is NULL the function ONLY returns the size
//								of output data (in bytes) required for the given
//								parameters.
//
//				bBGROrder		if data is ordered as BGR not RGB
//				nWiddth			Texture width: Only square, power of 2 sizes currently 
//								supported, and these are limited to 8x8 through to 
//								1024x1024
//				ReservedA		Supply as 0
//
//				MipMapMode		See VQ_MIPMAP_MODES
//
//				bAlphaOn		Is alpha data supplied? If not, assumed Alpha == 0xFF
//
//				bIncludeHeader	Optionally prepends the 12byte .VQF file format data. If
//								the data is to go straight into memory OR be massaged 
//								into the PVR file format, you probably don't want the 
//								header data.
//				
//				DitherLevel		Controls error diffusion. Ranges from none, 1/2, and full
//								(see defines above)
//
//				NumCodes		The maximum number of Vector codes to allocate 
//								Note that the routine will round this value up to a 
//								supported power of 2.
//
//				nColourFormat	See Codes above: One of 565, YUV, 4444, or  (1)555
//								565 or YUV probably best for Opaque texures, and
//								4444 best for translucency.
//								
//				bInvertAlpha	Usually set to 0. Flips the supplied Alpha values for
//									old PVR1 input data
//
//				Metric			How to "measure" the distance between colours. 
//								"VQMetricEqual" gives weighting to all RGB&A or YUV 
//								components.
//								"VQMetricWeighted" attempts to tune the result a bit 
//								closer to the eye's behaviour.
//
//								If the VQMETRIC_FREQUENCY_FLAG is also set on this value
//								the function will tolerate greater error in high
//								frequency areas. This sometimes helps because the eye
//								doesn't tend to notice small errors in high frequency
//								data.
//
//				ReservedB		Set it to 0.
//
// Outputs:
//				fErrorFound		returned RMS error per colour channel
//
// Returned Val:
//				IF there is an error, it returns one of the negative "Return messages"
//				listed above.
//
//				IF 	(OutputMemory == NULL), it returns the required size for the
//				output memory
//
//				IF (OutputMemort != NULL), and the function is successful, it returns
//				the number of codes actually used.
*/
/******************************************************************************/

MyDllExport int VqCalc2(void*	InputArrayRGB,
						void*	InputArrayAlpha,
						void*	OutputMemory,

						int		bBGROrder,
						int		nWidth,
						int		ReservedA,

			VQ_MIPMAP_MODES		MipMapMode,
						int		bAlphaOn,
						int		bIncludeHeader,

			VQ_DITHER_TYPES		DitherLevel,

						int		nNumCodes,
						int		nColourFormat,
						int		bInvertAlpha,

						int 	Metric, /*a VQ_COLOUR_METRIC value optionally ored with	frequency flag*/
						int 	ReservedB,
						float	*fErrorFound);



/******************************************************************************/
/*
// Function: 	VqCalcGrouped
//
// Description: DLL version of CreateVqGrouped function.
//
//		This is very similar to the VqCalc2, except that it doesn't handle alpha.
//		Instead, it allows the user to specify an unsigned 8bit "group" value per pixel.
//		Code book entries will then be arranged according to their group.
//		
//		The group value is treated as another "colour component" except that it is
//		weighted *much* higher than, say, R,G, or B.
//		
//		If, for a given code book, there are pixels from more than one group, two possible
//		actions can happen, depending on the parameter "GroupMode"
//		
//		if GroupMode == VQ_GROUP_ALLOW_MIXED, then any code with mixed pixels will
//		automatically be put in "255", which can be considered to be the "Mixed" group.
//		
//		if GroupMode == VQ_GROUP_NO_MIXED, then the system finds the highest occuring group
//		in the codebooks pixels. In the event of a tie, the least valued group id is used.
//			Example 1: Pixels in groups 5,1,4,5 => code book given group 5
//			Example 2  					5,5,4,4 => code book is assigned group 4
//		
//		
//		To determine which codes are in which groups, use "GroupCounts". The codes
//		are arranged in their groups from smallest used group ID to highest. This array
//		returns how many are in each group.
//		
//		**************************************
//		***SPECIAL CASE FOR MIP MAPPED YUV ***
//		**************************************
//		As with all the VQcalc routines, the 1x1 level of a YUV texture uses a 565 format.
//		This map is always given it's own unique code which is stored at (nNumCodes-1) code.
//		In effect, it  is also considered to be in its own unique group. If you sum up the
//		values in GroupCounts, you will also see that it is not included (since there isn't
//		a spare ID left)
//
//
//
// Inputs:		See VqCalc2 for most parameters.
//
//
// Outputs:
//				fErrorFound		returned RMS error per colour channel
//				
//				GroupCounts		Reports how many code book entries are in each group. Codes
//								with the same group are arranged contiguously, from the smallest
//								group id, to the largest.
//
// Returned Val: As for VqCalc2
//
*/
/******************************************************************************/

MyDllExport int VqCalcGrouped(const void*	InputArrayRGB,
						      const void*	InputArrayGroupInfo,
						         	void*	OutputMemory, 

						int		BGROrder,
						int		nWidth,
						int		Reserved1,
			VQ_MIPMAP_MODES		MipMapMode,

						int		IncludeHeader,

			VQ_DITHER_TYPES		DitherLevel,
				
						int		nNumCodes,
						int		nColourFormat,
										
			VQ_GROUP_MODES		GroupMode, /*see VQ_GROUP_MODES */

						int 	Metric,

						int 	Reserved2,

						int		GroupCounts[256],/*the number of codes in each group,  
												  NOTE group 255 is always the "Mixed pixel" group.*/

						float	*fErrorFound);


/******************************************************************************/
/*
// Function: 	VqGetVersionInfoString
//
// Description: Simply returns the version of the DLL in a user supplied string.
//				Added at the request of Sega Europe.
//
//	Example:
//			VqGetVersionInfoString( szBuffer, "FileVersion" );
*/
/******************************************************************************/

MyDllExport void VqGetVersionInfoString( char* pszVersionInfoString, const char* pszKey );





/*
// The OBSOLETE function interface. ***ONLY*** for backward compatibility
*/
MyDllExport int VqCalc(	void*	InputArrayRGB,
								void*	InputArrayAlpha,
								void*	OutputMemory, 
								int		nWidth,
								int		bMipMap,
								int		bAlphaOn,
								int		bDither,
								int		nNumCodes,
								int		nColourFormat,
								int		WeightMode,
								int		DummyB,
								float	DummyC[3],
								float	DummyD[4],
								int		DummyE,
								int		bInvertAlpha,
								float	DummyF,
								float	*fErrorFound);





/*
// END OF FILE
*/ 
