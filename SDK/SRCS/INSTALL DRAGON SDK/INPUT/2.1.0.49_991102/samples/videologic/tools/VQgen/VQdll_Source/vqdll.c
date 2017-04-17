#include <windows.h>

#include "vqcalc.h"


#define MyDllExport    __declspec( dllexport )
#include "Vqdll.h"


int WINAPI DllMain ( HINSTANCE hInstance, DWORD fdwReason, PVOID pvReserved)
{
	return TRUE;
}

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
							)
{
		/* 
		 * Very important: CreateVQ() generates a info header of 12 bytes
		 * preceding the VQ data.
		 * To upload in video memory a VQ file created with this function,
		 * this header has to be removed.
		 */
		return
		CreateVq(	InputArrayRGB,
					InputArrayAlpha,
					OutputMemory, 
					nWidth,
					bMipMap,
					bAlphaOn,
					bDither,
					nNumCodes,
					nColourFormat,
					nNumIterations,
					bDoFreq,
					fColourWeights,
					fFreqWeights,
					ColSpace,
					bAlphaSense,
					fPercentError,
					fErrorFound
							);

}


