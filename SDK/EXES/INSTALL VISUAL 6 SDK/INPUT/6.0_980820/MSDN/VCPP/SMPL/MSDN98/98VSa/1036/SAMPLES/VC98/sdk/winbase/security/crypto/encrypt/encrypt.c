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

#ifdef USE_BLOCK_CIPHER
    // defines for RC2 block cipher
    #define ENCRYPT_ALGORITHM	CALG_RC2
    #define ENCRYPT_BLOCK_SIZE	8
#else
    // defines for RC4 stream cipher
    #define ENCRYPT_ALGORITHM	CALG_RC4
    #define ENCRYPT_BLOCK_SIZE	1
#endif

static BOOL CAPIEncryptFile(PCHAR szSource, PCHAR szDestination, PCHAR szPassword);

/*****************************************************************************/
void _cdecl main(int argc, char *argv[])
{
    PCHAR szSource	= NULL;
    PCHAR szDestination = NULL;
    PCHAR szPassword	= NULL;

    // Validate argument count.
    if(argc != 3 && argc != 4) {
	printf("USAGE: encrypt <source file> <dest file> [ <password> ]\n");
	exit(1);
    }

    // Parse arguments.
    szSource	   = argv[1];
    szDestination  = argv[2];
    if(argc == 4) {
	szPassword = argv[3];
    }

    if(!CAPIEncryptFile(szSource, szDestination, szPassword)) {
	printf("Error encrypting file!\n");
	exit(1);
    }

    exit(0);
}

/*****************************************************************************/
static BOOL CAPIEncryptFile(PCHAR szSource, PCHAR szDestination, PCHAR szPassword)
{
    FILE *hSource      = NULL;
    FILE *hDestination = NULL;
    INT eof = 0;

    HCRYPTPROV hProv   = 0;
    HCRYPTKEY hKey     = 0;
    HCRYPTKEY hXchgKey = 0;
    HCRYPTHASH hHash   = 0;

    PBYTE pbKeyBlob = NULL;
    DWORD dwKeyBlobLen;

    PBYTE pbBuffer = NULL;
    DWORD dwBlockLen;
    DWORD dwBufferLen;
    DWORD dwCount;

    BOOL status = FALSE;

    // Open source file.
    if((hSource = fopen(szSource,"rb")) == NULL) {
	printf("Error opening Plaintext file!\n");
        goto done;
    }

    // Open destination file.
    if((hDestination = fopen(szDestination,"wb")) == NULL) {
	printf("Error opening Ciphertext file!\n");
        goto done;
    }

    // Get handle to the default provider.
    if(!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 0)) {
        printf("Error %x during CryptAcquireContext!\n", GetLastError());
        goto done;
    }

    if(szPassword == NULL) {
	// Encrypt the file with a random session key.

	// Create a random session key.
	if(!CryptGenKey(hProv, ENCRYPT_ALGORITHM, CRYPT_EXPORTABLE, &hKey)) {
	    printf("Error %x during CryptGenKey!\n", GetLastError());
	    goto done;
	}

	// Get handle to key exchange public key.
	if(!CryptGetUserKey(hProv, AT_KEYEXCHANGE, &hXchgKey)) {
	    printf("Error %x during CryptGetUserKey!\n", GetLastError());
	    goto done;
	}

	// Determine size of the key blob and allocate memory.
	if(!CryptExportKey(hKey, hXchgKey, SIMPLEBLOB, 0, NULL, &dwKeyBlobLen)) {
	    printf("Error %x computing blob length!\n", GetLastError());
	    goto done;
	}
	if((pbKeyBlob = malloc(dwKeyBlobLen)) == NULL) {
	    printf("Out of memory!\n");
	    goto done;
	}

	// Export session key into a simple key blob.
	if(!CryptExportKey(hKey, hXchgKey, SIMPLEBLOB, 0, pbKeyBlob, &dwKeyBlobLen)) {
	    printf("Error %x during CryptExportKey!\n", GetLastError());
	    goto done;
	}

	// Release key exchange key handle.
	CryptDestroyKey(hXchgKey);
	hXchgKey = 0;

	// Write size of key blob to destination file.
	fwrite(&dwKeyBlobLen, sizeof(DWORD), 1, hDestination);
	if(ferror(hDestination)) {
	    printf("Error writing header!\n");
	    goto done;
	}

	// Write key blob to destination file.
	fwrite(pbKeyBlob, 1, dwKeyBlobLen, hDestination);
	if(ferror(hDestination)) {
	    printf("Error writing header!\n");
	    goto done;
	}

    } else {
	// Encrypt the file with a session key derived from a password.

	// Create a hash object.
	if(!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
	    printf("Error %x during CryptCreateHash!\n", GetLastError());
	    goto done;
	}

	// Hash in the password data.
	if(!CryptHashData(hHash, szPassword, strlen(szPassword), 0)) {
	    printf("Error %x during CryptHashData!\n", GetLastError());
	    goto done;
	}

	// Derive a session key from the hash object.
	if(!CryptDeriveKey(hProv, ENCRYPT_ALGORITHM, hHash, 0, &hKey)) {
	    printf("Error %x during CryptDeriveKey!\n", GetLastError());
	    goto done;
	}

	// Destroy the hash object.
	CryptDestroyHash(hHash);
	hHash = 0;
    }

    // Determine number of bytes to encrypt at a time. This must be a multiple
    // of ENCRYPT_BLOCK_SIZE.
    dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE;

    // Determine the block size. If a block cipher is used this must have
    // room for an extra block.
    if(ENCRYPT_BLOCK_SIZE > 1) {
	dwBufferLen = dwBlockLen + ENCRYPT_BLOCK_SIZE;
    } else {
	dwBufferLen = dwBlockLen;
    }

    // Allocate memory.
    if((pbBuffer = malloc(dwBufferLen)) == NULL) {
	printf("Out of memory!\n");
	goto done;
    }

    // Encrypt source file and write to Source file.
    do {
	// Read up to 'dwBlockLen' bytes from source file.
	dwCount = fread(pbBuffer, 1, dwBlockLen, hSource);
	if(ferror(hSource)) {
	    printf("Error reading Plaintext!\n");
            goto done;
        }
	eof = feof(hSource);

        // Encrypt data
	if(!CryptEncrypt(hKey, 0, eof, 0, pbBuffer, &dwCount, dwBufferLen)) {
            printf("bytes required:%d\n",dwCount);
            printf("Error %x during CryptEncrypt!\n", GetLastError());
            goto done;
        }

	// Write data to destination file.
	fwrite(pbBuffer, 1, dwCount, hDestination);
	if(ferror(hDestination)) {
	    printf("Error writing Ciphertext!\n");
            goto done;
        }
    } while(!feof(hSource));

    status = TRUE;

    printf("OK\n");

    done:

    // Close files.
    if(hSource) fclose(hSource);
    if(hDestination) fclose(hDestination);

    // Free memory.
    if(pbKeyBlob) free(pbKeyBlob);
    if(pbBuffer) free(pbBuffer);

    // Destroy session key.
    if(hKey) CryptDestroyKey(hKey);

    // Release key exchange key handle.
    if(hXchgKey) CryptDestroyKey(hXchgKey);

    // Destroy hash object.
    if(hHash) CryptDestroyHash(hHash);

    // Release provider handle.
    if(hProv) CryptReleaseContext(hProv, 0);

    return(status);
}
