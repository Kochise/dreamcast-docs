/********************************************************************************************/
/* CONFIDENTIAL AND PROPRIETARY:                                                            */
/*      Copyright 1999, Sega of America.  All rights reserved.                              */
/*      This sample source code is provided for demonstration purposes only.                */
/*      Use and distribution of Sega proprietary material is governed by                    */
/*      developer licensing agreement.                                                      */
/********************************************************************************************/

/********************************************************************************************/
/* Name:     MSLSTL.c                                                                       */
/* Title:    MSL/STL C++ example                                                            */
/* Author:   David Rudolph/Joe Votour                                                       */
/* Created:  January 19, 2000                                                               */
/*                                                                                          */
/* Version:  1.0                                                                            */
/* Platform: Dreamcast | Set5.24                                                            */
/*                                                                                          */
/* Description:                                                                             */
/*  This program demonstrates how to use the MSL and STL (Standard Template                 */
/*  Libraries) that come with the MetroWerks and GNU compilers.                             */
/*  This sample is not supported under the SHC (Hitachi) compiler, since it does            */
/*  not include the necessary libraries to use STL.                                         */
/*                                                                                          */
/* History:                                                                                 */
/*  01/19/00 - First release version                                                        */
/********************************************************************************************/


/********************************************************************************************/
/* Since MetroWerks and GNU use different filenames for some of their STL headers, we need  */
/* to differentiate between them.                                                           */
/********************************************************************************************/

#ifdef __MWERKS__
	#include <algorithm.h>
#endif

#ifdef __GNUC__
    #include <algorithm>
#endif

/********************************************************************************************/
/* And now the standard stuff...                                                            */
/********************************************************************************************/

#include <shinobi.h>
#include <ninja.h>
#include <assert.h>
#include <string.h>

class CTest
{
public:

	//Constructor
	CTest(int nNumArray = 10);

	//Destructor
	~CTest();

    int Add(int x=4, int y=7);

private:

	int* m_IntArray;
	int  m_nNumArray;
    int  m_nTest;
};

CTest::CTest(int nNum)
{

	m_IntArray = NULL;

    m_IntArray = new int[nNum] ;
    m_nNumArray = nNum;

	for (int i = 0; i < nNum; i++)
	{
		m_IntArray[nNum] = i;
	}

    m_nTest = 123;
}

CTest::~CTest()
{
	if(m_IntArray != NULL)
	{
		delete [] m_IntArray;

		m_IntArray = NULL;
	}
}

int CTest::Add(int x, int y)
{
	return (x+y);
}


/********************************************************************************************/
/* This program is very simple.  It will create a string containing "Mark Twain" and then   */
/* use the reverse function to reverse the string ("niawT kraM")                            */
/********************************************************************************************/

CTest bob;

int main()
{
	char string1[] = "Mark Twain";
    int N1, result, *alloc_test;

#ifdef __GNUC__
    shinobi_workaround();
#endif

	/* Check the cable for NTSC/PAL or VGA.. works properly for SCART. */
	switch (syCblCheck())
	{
		/* Initialize the display device and set the frame buffer based on the video mode. */
		case SYE_CBL_NTSC:  /* U.S./North America NTSC (60Hz) and Brazil PAL-M (60Hz). */
			sbInitSystem (NJD_RESOLUTION_640x480_NTSCNI, NJD_FRAMEBUFFER_MODE_RGB565, 1);
			break;
		case SYE_CBL_PAL:   /* Europe PAL (50Hz) and Argentina PAL-N (50Hz). */
			sbInitSystem (NJD_RESOLUTION_640x544_PALNI, NJD_FRAMEBUFFER_MODE_RGB565, 1);
			break;
		case SYE_CBL_VGA:   /* Standard VGA. */
			sbInitSystem (NJD_RESOLUTION_VGA, NJD_FRAMEBUFFER_MODE_RGB565, 1);
			break;
		default:
			syBtExit();     /* Unknown video type, return to Dreamcast BootROM. */
	}

    result = bob.Add();

    N1 = strlen (string1);

    alloc_test = (int *) syMalloc (1024);

	reverse(&string1[0], &string1[N1]);

    while (1)
        result++;
}