/*****************************************************************************
  Name : KMMisc.c
  Date : August 1998
  Platform : ANSI compatible
 
  * Description : 
  This file is part of the KAMUI TOOLS library (KMTools.lib) used
  with the SDK demos for PowerVR series 2.

  Set of functions for Kamui. 

  Copyright : 1998 by VideoLogic Limited. All rights reserved.
******************************************************************************/
#include "KMTools.h"

/* the random number generator's state variable*/
static KMDWORD RandomNumber=0; 


/*---------------------------------------------------------------------------*
 *  Function Name   :  KMMiscRand()                                                 
 *  Inputs          :                                                     
 *  Outputs         :                                                   
 *  Returns         :                                                   
 *  Globals Used    :                                                   
 *  Description     : A portable L.C.G. random number generator taken from
 *				  Numerical Recipies. It does assume the unsigned 32bit mul
 *				  does behave correctly. ie returns the bottom 32bits of a
 *				  64Bit result. With a seed of 0, the next few numbers should
 *				  be 0x3C6EF35F, 0x47502932, 0xD1CCF6E9, and 0xAAF95334.
 *				  INTERNALLY! To make it easier to use, we mask off the top
 *				  bit so that we can return it as a positive signed integer.
 *---------------------------------------------------------------------------*/
long KMMiscRand(void)
{
	const long TOPBIT = 0x80000000L;

	RandomNumber=1664525UL*RandomNumber + 1013904223UL;

	return(RandomNumber & ~TOPBIT);
}
/*---------------------------------------------------------------------------*
 *  Function Name   :  KMMiscSeedRand()                                                 
 *  Inputs          :                                                     
 *  Outputs         :                                                   
 *  Returns         :                                                   
 *  Globals Used    :                                                   
 *  Description     : Seeds the random number generator. It can take any value
 *---------------------------------------------------------------------------*/
void KMMiscSeedRand(unsigned long Seed)
{	
	RandomNumber=Seed;
}
