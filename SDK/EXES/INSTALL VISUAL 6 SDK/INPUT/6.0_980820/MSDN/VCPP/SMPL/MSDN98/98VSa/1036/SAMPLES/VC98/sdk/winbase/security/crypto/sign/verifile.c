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

static BOOL VerifyFile(PCHAR szSourceFile, PCHAR szSignatureFile, PCHAR szDescription);

/*****************************************************************************/
void _cdecl main(int argc, char *argv[])
{
    PCHAR szSourceFile	  = NULL;
    PCHAR szSignatureFile = NULL;
    PCHAR szDescription  = NULL;

    // Validate argument count.
    if(argc != 4) {
	printf("USAGE: signfile <source file> <signature file> <description>\n");
	exit(1);
    }

    // Parse arguments.
    szSourceFile    = argv[1];
    szSignatureFile = argv[2];
    szDescription   = argv[3];

    if(!VerifyFile(szSourceFile, szSignatureFile, szDescription)) {
	printf("Error verifying file!\n");
	exit(1);
    }

    exit(0);
}

/*****************************************************************************/
static BOOL VerifyFile(PCHAR szSourceFile, PCHAR szSignatureFile, PCHAR szDescription)
{
    FILE *hSourceFile	 = NULL;
    FILE *hSignatureFile = NULL;
    INT eof = 0;

    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    HCRYPTKEY hSigPublicKey = 0;

    PBYTE pbSignature = NULL;
    DWORD dwSignatureLen;

    PBYTE pbBuffer = NULL;
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
    // Read in signature file.
    //

    // Determine size of signature.
    dwSignatureLen = 0;
    if(!CryptSignHash(hHash, AT_SIGNATURE, NULL, 0, NULL, &dwSignatureLen)) {
	printf("Error %x during CryptSignHash!\n", GetLastError());
	goto error;
    }

    // Allocate memory for 'pbSignature'.
    if((pbSignature = malloc(dwSignatureLen)) == NULL) {
	printf("Out of memory 2!\n");
	goto error;
    }

    // Open signature file.
    if((hSignatureFile = fopen(szSignatureFile,"rb")) == NULL) {
	printf("Error opening signature file!\n");
	goto error;
    }

    // Read signature data.
    dwCount = fread(pbSignature, 1, dwSignatureLen, hSignatureFile);
    if(ferror(hSignatureFile)) {
	printf("Error reading signature!\n");
	goto error;
    }

    // Close signature file.
    fclose(hSignatureFile);
    hSignatureFile = 0;


    //
    // Verify signature.
    //

    // Get handle to signature key.
    if(!CryptGetUserKey(hProv, AT_SIGNATURE, &hSigPublicKey)) {
	printf("Error %x during CryptGetUserKey!\n", GetLastError());
	goto error;
    }

    // Verify signature.
    if(!CryptVerifySignature(hHash, pbSignature, dwSignatureLen, hSigPublicKey, szDescription, 0)) {
	if(GetLastError() == NTE_BAD_SIGNATURE) {
	    printf("Signature did not match!\n");
	} else {
	    printf("Error %x during CryptVerifySignature!\n", GetLastError());
	}
	goto error;
    }

    // Release signature key.
    CryptDestroyKey(hSigPublicKey);
    hSigPublicKey = 0;

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
    if(hSigPublicKey) CryptDestroyKey(hSigPublicKey);
    if(hProv) CryptReleaseContext(hProv, 0);

    return FALSE;
}
