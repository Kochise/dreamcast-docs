// prototypes; exported functions

#define VQ_OK			0
#define VQ_OUTOFMEMORY	-1

MyDllExport int VqCalc(	void*	InputArrayRGB,
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
 