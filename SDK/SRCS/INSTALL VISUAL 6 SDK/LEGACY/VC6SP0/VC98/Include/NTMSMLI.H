/*++

  Copyright (c) 1996-1997 Microsoft Corporation
  Copyright (c) 1996-1997 Highground Systems

  Module Name:

	NtmsMli.h

  Abstract:

	This module contains the definitions for the MediaLabelInfo structure. This structure contains
	information that allows NTMS to identify media. This structure must be returned by media label
	libraries.

  Author:

	Kevin Fitzgerald (kfitzgerald@highground.com) 21-04-1997

  Revision History:

--*/

#ifndef _INCL_NTMSMLI_H_
#define _INCL_NTMSMLI_H_

#include <windows.h>

#define NTMSMLI_MAXTYPE     64
#define NTMSMLI_MAXIDSIZE   256
#define NTMSMLI_MAXAPPDESCR 256

typedef struct 
{
	WCHAR	LabelType[NTMSMLI_MAXTYPE] ;
	DWORD	LabelIDSize ;
	BYTE	LabelID[NTMSMLI_MAXIDSIZE] ;
	WCHAR	LabelAppDescr[NTMSMLI_MAXAPPDESCR] ;
} MediaLabelInfo, *pMediaLabelInfo ;

#endif
