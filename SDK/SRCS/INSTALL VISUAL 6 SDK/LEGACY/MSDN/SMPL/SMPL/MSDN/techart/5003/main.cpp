#include <windows.h>
#include <stdio.h>

#include "CEncrypt.h"

int main(int argc, char * argv[]);
void Usage();
BOOL IsSwitch(int argc, char * argv[], LPSTR pSwitch, int iMinSwitches, int iMaxSwitches);

int main(int argc, char * argv[])
	{
	CEncrypt Crypt;
	BOOL bResult;
	int iResultCode = 0;

	// check for invalid usage or help request
	if (argc < 2)
		{
		Usage();
		return(0);
		}

	// Was CEncrypt object initialized properly
	if (Crypt.IsFailure())
		{
		if (Crypt.LastError() != NTE_BAD_KEYSET)
			{
			printf("Could not initialize CSP. Aborting...\n");
			return(1);
			}
		}

	// check for encryption request
	if (IsSwitch(argc, argv, "/ENCRYPT", 3, 4))
		{
		bResult = Crypt.EncryptFile(argv[2], argv[3], argv[4]);
		if (bResult == CEncrypt::ENCRYPT_SUCCESS)
			{
			printf("%s encrypted successfully to %s.\n", argv[2], argv[3]);
			}
		else
			{
			printf("Failed encrypting %s.\n", argv[2]);
			iResultCode = 1;
			}
		}

	// check for decryption request
	else if (IsSwitch(argc, argv, "/DECRYPT", 3, 4))
		{
		bResult = Crypt.DecryptFile(argv[2], argv[3], argv[4]);
		if (bResult == CEncrypt::ENCRYPT_SUCCESS)
			{
			printf("%s decrypted successfully to %s.\n", argv[2], argv[3]);
			}
		else
			{
			printf("Failed decrypting %s.\n", argv[2]);
			iResultCode = 1;
			}
		}

	// check for add user request
	else if (IsSwitch(argc, argv, "/ADDUSER", 1, 1))
		{
		bResult = Crypt.AddUser();
		if (bResult == CEncrypt::ENCRYPT_SUCCESS)
			{
			printf("User added successfully.\n");
			}
		else
			{
			printf("Failed adding user.\n");
			iResultCode = 1;
			}
		}

	// check for remove user request
	else if (IsSwitch(argc, argv, "/REMOVEUSER", 1, 1))
		{
		bResult = Crypt.RemoveUser();
		if (bResult == CEncrypt::ENCRYPT_SUCCESS)
			{
			printf("User removed successfully.\n");
			}
		else
			{
			printf("Failed removing user.\n");
			iResultCode = 1;
			}
		}

	// check for CSP statistics request
	else if (IsSwitch(argc, argv, "/CSP", 1, 1))
		{
		Crypt.Statistics();
		}

	// check for file signing request
	else if (IsSwitch(argc, argv, "/SIGN", 3, 4))
		{
		bResult = Crypt.SignFile(argv[2], argv[3], argv[4]);
		if (bResult == CEncrypt::ENCRYPT_SUCCESS)
			{
			printf("File %s signed successfully\n", argv[2]);
			}
		else
			{
			printf("Failed signing %s\n", argv[2]);
			iResultCode = 1;
			}
		}

	// check for signature verification request
	else if (IsSwitch(argc, argv, "/VERIFY", 3, 4))
		{
		bResult = Crypt.VerifyFile(argv[2], argv[3], argv[4]);
		if (bResult == CEncrypt::ENCRYPT_SUCCESS)
			{
			printf("File %s is signed correctly\n", argv[2]);
			}
		else
			{
			printf("File %s is not signed correctly\n", argv[2]);
			iResultCode = 1;
			}
		}

	// unknown switch applied
	else
		{
		Usage();
		iResultCode = 1;
		}

	return(iResultCode);
	}

void Usage()
	{
	puts("Usage: Encrypt ...");
	puts("");
	puts("where ... is one of");
	puts("");
	puts(" /A[DDUSER                        <- to add user to CSP table");
	puts(" /R[EMOVEUSER                     <- to remove user from CSP table");
	puts(" /E[NCRYPT] uf ef [pwd]           <- to encrypt a file");
	puts(" /D[ECRYPT] ef uf [pwd]           <- to decrypt a file");
	puts(" /S[IGN] uf sf [desc]             <- to sign a file");
	puts(" /V[ERIFY] sf uf [desc]           <- to verify a signed file");
	puts(" /C[SP]                           <- to show CSP statistics");
	puts("");
	puts("");
	puts(" and uf   = name of an unencrypted file");
	puts("     ef   = name of an encrypted file");
	puts("     sf   = name of a signed file");
	puts("     pwd  = optional password");
	puts("     desc = optional signature description");
	return;
	}

BOOL IsSwitch(int argc, char * argv[], LPSTR pSwitch, int iMinSwitches, int iMaxSwitches)
	{
	if (strnicmp(argv[1], pSwitch, strlen(argv[1])) == 0)
		{
		argc--;
		if (argc < iMinSwitches)
			{
			printf("Insufficient arguments supplied. Try again with /? for help\n");
			return(FALSE);
			}
		if (argc > iMaxSwitches)
			{
			printf("Excessive arguments supplied. Try again with /? for help\n");
			return(FALSE);
			}
		return(TRUE);
		}
	else
		{
		return(FALSE);
		}
	}
