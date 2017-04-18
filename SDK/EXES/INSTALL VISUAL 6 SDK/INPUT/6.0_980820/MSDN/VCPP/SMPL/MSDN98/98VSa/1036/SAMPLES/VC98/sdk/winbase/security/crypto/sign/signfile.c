/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright 1996-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <wincrypt.h>

static BOOL SignFile(PCHAR szSourceFile, PCHAR szSignatureFile, PCHAR szDescription);

/*****************************************************************************/
void _cdecl main(int argc, char *argv[])
{
    PCHAR szSourceFile	  = NULL;
    PCHAR szSignatureFile = NULL;
    PCHAR szDescription   = NULL;

    // Validate argument count.
    if(argc != 4) {
	printf("USAGE: signfile <source file> <signature file> <description>\n");
	exit(1);
    }

    // Parse arguments.
    szSourceFile    = argv[1];
    szSignatureFile = argv[2];
    szDescription   = argv[3];

    if(!SignFile(szSourceFile, szSignatureFile, szDescription)) {
	printf("Error signing file!\n");
	exit(1);
    }

    exit(0);
}

/*****************************************************************************/
static BOOL SignFile(PCHAR szSourceFile, PCHAR szSignatureFile, PCHAR szDescription)
{
    FILE *hSourceFile	 = NULL;
    FILE *hSignatureFile = NULL;
    INT eof = 0;

    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;

    PBYTE pbSignature = NULL;
    DWORD dwSignatureLen;

    PBYTE pbBuffer    = NULL;
    DWORD dwBufferLen;
    DWORD dwCount;

    // Get handle to the default provider.
    if(!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 0)) {
        printf("Error %x during CryptAcquireContext!\n", GetLastError());
	goto error;
    }

    //
    // Hash source file.
    //

    // Determine number of bytes to hash at once.
    dwBufferLen = 1000;

    // Allocate memory for 'pbBuffer'.
    if((pbBuffer = malloc(dwBufferLen)) == NULL) {
	printf("Out of memory 1!\n");
	goto error;
    }

    // Open source file.
    if((hSourceFile = fopen(szSourceFile,"rb")) == NULL) {
	printf("Error opening source file!\n");
	goto error;
    }

    // Create a hash object.
    if(!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
	printf("Error %x during CryptCreateHash!\n", GetLastError());
	goto error;
    }

    // Hash source file.
    do {
	// Read up to 'dwBufferLen' bytes from source file.
	dwCount = fread(pbBuffer, 1, dwBufferLen, hSourceFile);
	if(ferror(hSourceFile)) {
	    printf("Error reading Plaintext!\n");
	    goto error;
        }
	eof = feof(hSourceFile);

	// Add data to hash object.
	if(!CryptHashData(hHash, pbBuffer, dwCount, 0)) {
	    printf("Error %x during CryptHashData!\n", GetLastError());
	    goto error;
	}
    } while(!feof(hSourceFile));

    // Close source file.
    fclose(hSourceFile);
    hSourceFile = 0;

    // Free 'pbBuffer' memory.
    free(pbBuffer);
    pbBuffer = NULL;


    //
    // Sign hash object.
    //

    // Determine size of signature.
    dwCount = 0;
    if(!CryptSignHash(hHash, AT_SIGNATURE, NULL, 0, NULL, &dwSignatureLen)) {
	printf("Error %x during CryptSignHash 1!\n", GetLastError());
	goto error;
    }

    // Allocate memory for 'pbSignature'.
    if((pbSignature = malloc(dwSignatureLen)) == NULL) {
	printf("Out of memory 2!\n");
	goto error;
    }

    // Sign hash object (with signature key).
    if(!CryptSignHash(hHash, AT_SIGNATURE, szDescription, 0, pbSignature, &dwSignatureLen)) {
	printf("Error %x during CryptSignHash 2!\n", GetLastError());
	goto error;
    }


    //
    // Write signature to signature file.
    //

    // Open signature file.
    if((hSignatureFile = fopen(szSignatureFile,"wb")) == NULL) {
	printf("Error opening signature file!\n");
	goto error;
    }

    // Write signature to signature file.
    fwrite(pbSignature, 1, dwSignatureLen, hSignatureFile);
    if(ferror(hSignatureFile)) {
	printf("Error writing signature!\n");
	goto error;
    }

    // Close signature file.
    fclose(hSignatureFile);
    hSignatureFile = 0;

    // Free 'pbSignature' memory.
    free(pbSignature);
    pbSignature = NULL;


    // Destroy hash object.
    CryptDestroyHash(hHash);
    hHash = 0;

    // Release provider handle.
    CryptReleaseContext(hProv, 0);
    hProv = 0;

    printf("OK\n");

    return TRUE;

    error:

    //
    // Do cleanup
    //

    // Close files.
    if(hSourceFile) fclose(hSourceFile);
    if(hSignatureFile) fclose(hSignatureFile);

    // Free memory.
    if(pbSignature) free(pbSignature);
    if(pbBuffer) free(pbBuffer);

    // Release crypto handles.
    if(hHash) CryptDestroyHash(hHash);
    if(hProv) CryptReleaseContext(hProv, 0);

    return FALSE;
}
