/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright 1996-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <windows.h>
#include <wincrypt.h>

/*****************************************************************************/
void _cdecl main(int argc, char *argv[])
{
    HCRYPTPROV hProv = 0;
    BYTE *ptr = NULL;
    DWORD i;
    ALG_ID aiAlgid;
    DWORD dwBits;
    DWORD dwNameLen;
    CHAR szName[100];	      // Often allocated dynamically.
    BYTE pbData[1000];	      // Often allocated dynamically.
    DWORD dwDataLen;
    DWORD dwFlags;
    CHAR *pszAlgType = NULL;

    // Get handle to the default provider.
    if(!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 0)) {
        printf("Error %x during CryptAcquireContext!\n", GetLastError());
        goto done;
    }

    // Enumerate the supported algorithms.
    for(i=0 ; ; i++) {
	// Set the CRYPT_FIRST flag the first time through the loop.
	if(i == 0) {
	    dwFlags = CRYPT_FIRST;
	} else {
	    dwFlags = 0;
	}

	// Retrieve information about an algorithm.
	dwDataLen = 1000;
	if(!CryptGetProvParam(hProv, PP_ENUMALGS, pbData, &dwDataLen, 0)) {
	    if(GetLastError() == ERROR_NO_MORE_ITEMS) {
		// Exit the loop.
		break;
	    } else {
		printf("Error %x reading algorithm!\n", GetLastError());
		return;
	    }
	}

	// Extract algorithm information from 'pbData' buffer.
	ptr = pbData;
	aiAlgid = *(ALG_ID *)ptr;
	ptr += sizeof(ALG_ID);
	dwBits = *(DWORD *)ptr;
	ptr += sizeof(DWORD);
	dwNameLen = *(DWORD *)ptr;
	ptr += sizeof(DWORD);
	strncpy(szName, ptr,dwNameLen);

	// Determine algorithm type.
	switch(GET_ALG_CLASS(aiAlgid)) {
	    case ALG_CLASS_DATA_ENCRYPT: pszAlgType = "Encrypt  ";
					 break;
	    case ALG_CLASS_HASH:	 pszAlgType = "Hash     ";
					 break;
	    case ALG_CLASS_KEY_EXCHANGE: pszAlgType = "Exchange ";
					 break;
	    case ALG_CLASS_SIGNATURE:	 pszAlgType = "Signature";
					 break;
	    default:			 pszAlgType = "Unknown  ";
	}

	// Print information about algorithm.
	printf("Name:%-14s Type:%s  Bits:%-4d Algid:%8.8xh\n",
	    szName, pszAlgType, dwBits, aiAlgid
	);
    }

    done:

    // Release CSP handle.
    if(hProv) CryptReleaseContext(hProv,0);
}
