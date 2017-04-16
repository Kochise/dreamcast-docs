//
// standard includes
//
#include <windows.h>	// std windows defs, etc
#include <wininet.h>	// Windows Internet SDK api
#include <stdio.h>
#include <ctype.h>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>



//
// private includes
//
#include "cnetget.h"



//
// default constructor
//
CNetGet::CNetGet()
	{
	// initialize misc. vars
	hInternetSession = (HINTERNET)NULL;

	// reset counters
	iLastKeyword = 0;
	iDefaultFileCount = 1;
	lBytesWrittenToDisk = 0L;
	lURLsReadSuccess = 0L;
	lURLsReadFailure = 0L;
	iLastExtension = 0;

	// set flags
	bQuietMode = FALSE;
	bExtractGraphics = TRUE;
	bExtractBaggage = TRUE;
	bLogging = TRUE;
	bMakeDataFile = FALSE;
	bUniqueFiles = FALSE;
	}



//
// default destructor
//
CNetGet::~CNetGet()
	{
	int n;

	// release array resources
	for (n = 0; n < iLastKeyword; n++)
		{
		delete [] pKeywordArray[iLastKeyword];
		delete [] pElementArray[iLastKeyword];
		}
	for (n = 0; n < iLastExtension; n++)
		{
		delete [] pAcceptableExtensions[n];
		}

	// delete temp file
	if (bMakeDataFile)
		{
		DeleteFile(TEMPFILESPEC);
		}

	return;
	}



//
// routine to add keyword to private keyword table
//
BOOL CNetGet::AddKeyword(LPSTR pKeyword, LPSTR pElement, int iProcessingMode)
	{
	// ensure we don't go out of bounds
	if (iLastKeyword >= MAXKEYWORDS)
		{
		//return failure
		return(FALSE);
		}

	// store incoming keywords and elements
	pKeywordArray[iLastKeyword] = new char [strlen(pKeyword) + 1];
	strcpy(pKeywordArray[iLastKeyword], pKeyword);
	pElementArray[iLastKeyword] = new char [strlen(pElement) + 1];
	strcpy(pElementArray[iLastKeyword], pElement);
	iProcessingArray[iLastKeyword] = iProcessingMode;

	// increment counter
	iLastKeyword++;

	// return success
	return(TRUE);
	}



//
// routine to return last Win32 error
//
DWORD CNetGet::GetLastError()
	{
	return(dwGLE);
	}



//
// routine to clean up internet session
//
void CNetGet::StopInternetSession()
	{
	InternetCloseHandle(hInternetSession);
	return;
	}



//
// routine to start internet session
//
BOOL CNetGet::StartInternetSession(LPSTR pServer)
	{

	// create internet session
	hInternetSession = InternetOpen(
							pServer,
							INTERNET_OPEN_TYPE_PRECONFIG,
							NULL,
							NULL,
							0);

	// if no session then return error code
	if (hInternetSession == NULL)
		{
		dwGLE = GetLastError();
		return(FALSE);
		}

	// else return session handle
	return(TRUE);
	}



//
// routine to get URL information and store out to disk
//
int CNetGet::GetURLInformation(LPSTR pURL, LPSTR pOutputDir, LPSTR pOutputSpec)
	{
	HINTERNET hURL;
	LPSTR pBuffer;
	DWORD dwBytesRead;
	DWORD dwBytesWritten;
	HANDLE hOutputFile;
	BOOL bAPIResult;
	char cProtocol[_MAX_PATH];
	char cSubdir[_MAX_PATH];
	char cPath[_MAX_PATH];
	char cFilename[_MAX_PATH];
	char cCompleteURL[_MAX_PATH];
	int n;
	DWORD dwCreationFlag = CREATE_ALWAYS;

	// we need a buffer to read into
	pBuffer = new char [URLBUFFERSIZE];

	// parse URL, creating default output file spec if necessary
	strcpy(cCompleteURL, pURL);
	MyInternetSplitPath(pURL, cCompleteURL, cProtocol, cPath, cSubdir, cFilename);
	MyInternetMakePath(cCompleteURL, cProtocol, cPath, cSubdir, cFilename);
	
	// inform user of where we are
	if (!bQuietMode)
		printf("Getting %s", cCompleteURL);

	// link to Internat information via URL
	hURL = InternetOpenUrl(
			hInternetSession,
			cCompleteURL,
			NULL,
			0,
			0,
			0);

	// if error then clean up and exit
	if (hURL == NULL)
		{
		// store last Win32 error
		dwGLE = GetLastError();

		// get internet failure msg
		dwBytesWritten = URLBUFFERSIZE;
		InternetGetLastResponseInfo(
			&dwBytesRead,
			(LPSTR)pBuffer,
			&dwBytesWritten);

		// release working buffer
		delete [] pBuffer;

		// increment failure count
		lURLsReadFailure++;

		// inform user
		if (!bQuietMode)
			printf(" - failure\n");

		// and return
		return(NG_INVALIDURL);
		}

	// increment URL count
	lURLsReadSuccess++;


	// develop output filespec
	if (bMakeDataFile)
		{
		strcpy(pOutputSpec, TEMPFILESPEC);
		}
	else
		{
		// create relevant subdirectories
		CreateDirectory(pOutputDir, NULL);
		strcpy(pBuffer, pOutputDir);
		strcat(pBuffer, "\\");
		strcat(pBuffer, cPath + 2);
		*(strchr(pBuffer, '/')) = '\0';
		CreateDirectory(pBuffer, NULL);

		// build file spec
		strcpy(pOutputSpec, pBuffer);
		strcat(pOutputSpec, "\\");
		strcat(pOutputSpec, GetDefaultFileSpec(cFilename));
		}

	// set appropriate creation flag
	if (bUniqueFiles)
		{
		dwCreationFlag = CREATE_NEW;
		}

	// create output file
	hOutputFile = CreateFile(
					pOutputSpec,
					GENERIC_READ | GENERIC_WRITE,
					FILE_SHARE_READ | FILE_SHARE_WRITE,
					NULL,
					dwCreationFlag,
					FILE_ATTRIBUTE_NORMAL,
					NULL);
	n = 1;
	while (hOutputFile == INVALID_HANDLE_VALUE && bUniqueFiles)
		{
		sprintf(pBuffer, "%s_%d", pOutputSpec, n++);
		hOutputFile = CreateFile(
						pBuffer,
						GENERIC_READ | GENERIC_WRITE,
						FILE_SHARE_READ | FILE_SHARE_WRITE,
						NULL,
						dwCreationFlag,
						FILE_ATTRIBUTE_NORMAL,
						NULL);
		}

	// read information into buffer
	bAPIResult = TRUE;
	while (bAPIResult)
		{
		bAPIResult = InternetReadFile(
			hURL,
			pBuffer,
			(DWORD)URLBUFFERSIZE,
			&dwBytesRead);

		// if nothng returned then assume EOF
		if (dwBytesRead == 0)
			{
			bAPIResult = FALSE;
			}

		// if not EOF
		if (bAPIResult)
			{
			// write Internet information to file
			bAPIResult = WriteFile(
					hOutputFile,
					pBuffer,
					dwBytesRead,
					&dwBytesWritten,
					NULL);
			lBytesWrittenToDisk += dwBytesWritten;
			}
		}
	
	// close down and release resources
	CloseHandle(hOutputFile);
	InternetCloseHandle(hURL);
	delete [] pBuffer;

	// exit with success code
	if (!bQuietMode)
		printf("\n");
	return(NG_SUCCESS);
	}

	
	
//
// routine to parse URL and extract all 'src' files
//
int CNetGet::ParseURL(LPSTR pURL, LPSTR pOutputDir, LPSTR pInputSpec)
	{
	FILE * hURLListFile;
	LPSTR pURLBuffer;
	LPSTR pFilename;
	LPSTR pPtr;

	// we need working buffers
	pURLBuffer = new char [PAGEBUFFERSIZE];
	pFilename = new char [_MAX_PATH];

	// create URL list output file
	if (bMakeDataFile)
		{
		hURLListFile = fopen(pOutputDir, "at");
		}

	// open parsing file
	ParseOpen(pInputSpec);

	// walk through file
	pPtr = ParseFirstURL(pURL, pURLBuffer, pOutputDir, pFilename);
	while (pPtr)
		{
		// either output URL to list file or get URL contents
		if (bMakeDataFile)
			{
			fprintf(hURLListFile, "%s\n", pURLBuffer);
			lURLsReadSuccess++;
			lBytesWrittenToDisk = 0L;
			}
		else
			{
			// slight delay to insure transfer
			Sleep(1000);

			// get URL information
			GetURLInformation(pURLBuffer, pOutputDir, pFilename);
			}
		// get next URL
		pPtr = ParseNextURL(pURL, pURLBuffer, pOutputDir, pFilename);
		}

	// close parsing file
	ParseClose();

	// close URL list output file if one created
	if (bMakeDataFile)
		{
		fclose(hURLListFile);
		}

	// release working buffers
	delete [] pURLBuffer;
	delete [] pFilename;

	// return with success
	return(0);
	}



//
// routine to extract SRC= elementr from line
//
BOOL CNetGet::LookForTagAndExtractValue(LPSTR pLine)
	{
	LPSTR pBuffer;
	BOOL bResult = FALSE;
	LPSTR pPtr;
	DWORD dwSize;
	int iKeyword;

	// allocate working buffers
	pBuffer = new char [PAGEBUFFERSIZE];
	
	// make copy of input data and standardize into lowercase
	strcpy(pBuffer, pLine);
	strlwr(pBuffer);

	// loop through keyword table, looking for keyword
	for (iKeyword = 0; iKeyword < iLastKeyword && !bResult; iKeyword++)
		{
		// look for keyword 'x'
		pPtr = strstr(pBuffer, pKeywordArray[iKeyword]);

		// if found
		if (pPtr != NULL)
			{
			LPSTR pTag;
			
			// make temporary buffer
			pTag = new char [strlen(pPtr) + 1];

			// copy rest of line
			strcpy(pTag, pPtr);

			// look for end of tag terminator
			pPtr = strchr(pTag, '>');

			// if found
			if (pPtr)
				{
				// terminate line at terminator
				pPtr++;
				*pPtr = '\0';

				// look for this tags element
				pPtr = ExtractTagValue(pTag, pElementArray[iKeyword]);

				// if found
				if (pPtr != NULL)
					{
					// bypass any leading tag chars
					while (*pPtr && strchr(ParamDelimiters, *pPtr))
						pPtr++;

					// copy what is left
					strcpy(pBuffer, pPtr);

					// terminate at any remaining tag chars
					pPtr = strpbrk(pBuffer, ParamSeparators);
					if (pPtr)
						*pPtr = '\0';

					// pass back to user and flag success
					dwSize = PAGEBUFFERSIZE;
					strcpy(pLine, pBuffer);

					// signal success
					bResult = TRUE;

					// do we need to do any processing with this keyword
					switch (iProcessingArray[iKeyword])
						{
						case 0:
						default:
							break;
						case 1:
							if (*pLine == '#')
								{
								bResult = FALSE;
								}
							break;
						}
					}
				}
			// release temporary buffer
			delete [] pTag;
			}
		}

	// release resources and exit
	delete [] pBuffer;
	return(bResult);
	}



//
// routine to pointer to element parameter, if any
//
LPSTR CNetGet::ExtractTagValue(LPSTR pLine, LPSTR pKeyword)
	{
	LPSTR pBuffer;
	LPSTR pPtr;
	int c;

	// allocate working buffers
	pBuffer = new char [strlen(pLine) + 1];
	
	// get copy of param and standardize (lowercase)
	strcpy(pBuffer, pLine);
	strlwr(pBuffer);

	// look for keyword
	pPtr = strstr(pBuffer, pKeyword);
	while (pPtr)
		{
		// check behind keyword if not at beginning of line
		if (pPtr > pBuffer)
			{
			c = *(pPtr-1);
			// if alphanumeric then not standalone keyword
			if (isalnum(c))
				{
				// find next occurence
				pPtr = strstr(pPtr + 1, pKeyword);
				continue;
				}
			}

		// look at char after keyword
		c = *(pPtr + strlen(pKeyword));

		// if alphanumeric then not standalone keyword
		if (isalnum(c))
			{
			// find next occurence
			pPtr = strstr(pPtr + 1, pKeyword);
			continue;
			}

		// if here then keyword is standalone keyword
		// the format is most often in the form of keyword = value
		// so bypass trailing spaces
		pPtr += strlen(pKeyword);
		while (*pPtr && isspace(*pPtr))
			pPtr++;
		if (*pPtr == '=')
			pPtr++;
		while (*pPtr && isspace(*pPtr))
			pPtr++;
		break;
		}

	// calculate offset into original line
	if (pPtr != NULL)
		{
		pPtr = pLine + (pPtr - pBuffer);
		}

	// release resources and exit
	delete [] pBuffer;
	return(pPtr);
	}



//
// routine to simulate C runtime splitpath
//
// rules
// 1)	a file ALWAYS has an extension
// 2)	from http:, ftp:, gopher:, etc to last / is the URL 'path'
//
// URL									Protocol	path				subdir		file
// http://www.msn.com					http:		//www.msn.com/
// http://www.msn.com/					http:		//www.msn.com/
// http://www.msn.com/abc				http:		//www.msn.com/		abc/
// http://www.msn.com/abc/				http:		//www.msn.com/		abc/
// http://www.msn.com/trio.htm			http:		//www.msn.com/					trio.htm
// http://www.msn.com/abc/trio.htm		http:		//www.msn.com/		abc/		trio.htm
//
void CNetGet::MyInternetSplitPath(LPSTR pURLBase, LPSTR pUserURL, LPSTR pUserProtocol, LPSTR pUserPath, LPSTR pUserSubdir, LPSTR pUserFilename)
	{
	char pURL[_MAX_PATH];
	char pCompleteURL[_MAX_PATH];
	char pProtocol[_MAX_PATH];
	char pPath[_MAX_PATH];
	char pSubdir[_MAX_PATH];
	char pFilename[_MAX_PATH];
	char pBuffer[_MAX_PATH];
	LPSTR pPtr;
	int n;
	DWORD dwSize;

	// set defaults
	strcpy(pProtocol, "");
	strcpy(pPath, "");
	strcpy(pSubdir, "");
	strcpy(pFilename, "");

	// get copy of URL parameter
	dwSize = _MAX_PATH;
	InternetCombineUrl(
		pURLBase,
		pUserURL,
		pCompleteURL,
		&dwSize,
		ICU_DECODE);
	strcpy(pURL, pCompleteURL);

	// strip off protocol if given
	pPtr = strchr(pURL, ':');
	if (pPtr)
		{
		n = pPtr - pURL + 1;
		strncpy(pProtocol, pURL, n);
		*(pProtocol + n) = '\0';
		strcpy(pURL, pCompleteURL + n);
		}

	// find path
	pPtr = pURL;
	if (strncmp(pURL, "//", 2) == 0)
		{
		pPtr = pURL + 2;
		}
	pPtr = strchr(pPtr, '/');
	if (pPtr)
		{
		n = pPtr - pURL + 1;
		strncpy(pPath, pURL, n);
		*(pPath + n) = '\0';
		strcpy(pBuffer, pPtr + 1);
		strcpy(pURL, pBuffer);
		}

	// find subdir
	pPtr = strrchr(pURL, '/');
	if (pPtr)
		{
		strcpy(pSubdir, pURL);
		n = pPtr - pURL + 1;
		*(pSubdir + n) = '\0';
		strcpy(pFilename, pPtr + 1);
		}

	strcpy(pUserProtocol, pProtocol);
	strcpy(pUserPath, pPath);
	strcpy(pUserSubdir, pSubdir);
	strcpy(pUserFilename, pFilename);

	return;
	}



//
// routine to examine command line switch for specified switch
//
int CNetGet::IsCommandLineSwitchSet(int argc, char * argv[], int iSwitch)
	{
	int n;
	int iResult = 0;
	BOOL bSwitchState;

	// loop through switches
	for (n = 1; n < argc; n++)
		{
		// determine switch state
		switch (argv[n][0])
			{
			case '-':
				bSwitchState = FALSE;
				break;
			case '+':
				bSwitchState = TRUE;
				break;
			case '/':
				bSwitchState = TRUE;
				break;
			default:
				continue;
			}
		if (strchr(argv[n], tolower(iSwitch)) || strchr(argv[n], toupper(iSwitch)))
			{
			iResult = (bSwitchState) ? n : n * -1;
			break;
			}
		}

	// return result of scan
	return(iResult);
	}



//
// routine to set flag and return old value
//
BOOL CNetGet::Set_UniqueFiles(BOOL bValue)
	{
	BOOL bOldValue;
	bOldValue = bUniqueFiles;
	bUniqueFiles = bValue;
	return(bOldValue);
	}



//
// routine to set flag and return old value
//
BOOL CNetGet::Set_PromptMode(BOOL bValue)
	{
	BOOL bOldValue;
	bOldValue = bPromptMode;
	bPromptMode = bValue;
	return(bOldValue);
	}



//
// routine to set flag and return old value
//
BOOL CNetGet::Set_ExtractGraphics(BOOL bValue)
	{
	BOOL bOldValue;
	bOldValue = bExtractGraphics;
	bExtractGraphics = bValue;
	return(bOldValue);
	}



//
// routine to set flag and return old value
//
BOOL CNetGet::Set_ExtractBaggage(BOOL bValue)
	{
	BOOL bOldValue;

	bOldValue = bExtractBaggage;
	bExtractBaggage = bValue;
	return(bOldValue);
	}



//
// routine to set flag and return old value
//
BOOL CNetGet::Set_QuietMode(BOOL bValue)
	{
	BOOL bOldValue;

	bOldValue = bQuietMode;
	bQuietMode = bValue;
	return(bOldValue);
	}



//
// routine to set flag and return old value
//
BOOL CNetGet::Set_Logging(BOOL bValue)
	{
	BOOL bOldValue;

	bOldValue = bLogging;
	bLogging = bValue;
	return(bOldValue);
	}



//
// routine to set flag and return old value
//
BOOL CNetGet::Set_MakeDataFile(BOOL bValue)
	{
	BOOL bOldValue;

	bOldValue = bMakeDataFile;
	bMakeDataFile = bValue;
	return(bOldValue);
	}



// routine routine to simulate C runtime makepath
//
// rules:
//	1) the path ALWAYS end with a /
//	2) the subdir ALWAYS end with a /
//
LPSTR CNetGet::MyInternetMakePath(LPSTR pCompleteURL, LPSTR pUserProtocol, LPSTR pUserPath, LPSTR pUserSubdir, LPSTR pUserFilename)
	{

	// if no protocol specified then use default HTTP:
	if (strlen(pUserProtocol) == 0)
		{
		strcpy(pCompleteURL, "HTTP:");
		}
	else
		{
		strcpy(pCompleteURL, pUserProtocol);
		}

	// if path does not start with // then append //
	if (strncmp(pUserPath, "//", 2))
		{
		strcat(pCompleteURL, "//");
		}

	// put the rest together
	strcat(pCompleteURL, pUserPath);
	strcat(pCompleteURL, pUserSubdir);
	strcat(pCompleteURL, pUserFilename);

	// return pointer to buffer
	return(pCompleteURL);
	}



//
// routine to read keyword file
//
int CNetGet::ReadKeyFile(LPSTR pKeyFile)
	{
	FILE * hFile;
	int iKeyCount = 0;
	char cKeyword[32];
	char cElement[32];
	int iProcessingMode;
	LPSTR pBuffer;
	LPSTR pPtr;

	// get working buffer
	pBuffer = new char[256];

	// open keyword file
	hFile = fopen(pKeyFile, "rt");

	// if open
	if (hFile != NULL)
		{

		// get line and loop through file
		pPtr = fgets(pBuffer, 256, hFile);
		while (pPtr != NULL)
			{
			// break into componenets
			pPtr = strtok(pBuffer, ";");
			strcpy(cKeyword, pPtr);
			strcat(cKeyword, " ");
			pPtr = strtok(NULL, ";");
			strcpy(cElement, pPtr);
			pPtr = strtok(NULL, ";");
			iProcessingMode = atoi(pPtr);

			// add to keyword table
			AddKeyword(cKeyword, cElement, iProcessingMode);

			// get next line in file
			pPtr = fgets(pBuffer, 256, hFile);
			}
		}

	// close file, release working buffer
	fclose(hFile);
	delete [] pBuffer;

	// return keyword count
	return(iKeyCount);
	}



//
// routine to open parsing file
//
BOOL CNetGet::ParseOpen(LPSTR pInputFile)
	{
	// open input file
	hParseFile = fopen(pInputFile, "rt");

	// return status code
	if (hParseFile == (FILE *)-1)
		{
		return(FALSE);
		}
	else
		{
		return(TRUE);
		}
	}



//
// routine to parse first URL from data file
//
LPSTR CNetGet::ParseFirstURL(LPSTR pBaseURL, LPSTR pURLOutputBuffer, LPSTR pOutputDir, LPSTR pFilename)
	{
	return(ParseNextURL(pBaseURL, pURLOutputBuffer, pOutputDir, pFilename));
	}



//
// routine to parse next URL from data file
//
LPSTR CNetGet::ParseNextURL(LPSTR pBaseURL, LPSTR pURLOutputBuffer, LPSTR pOutputDir, LPSTR pFilename)
	{
	LPSTR pBuffer;
	LPSTR pFileSpec;
	LPSTR pURLBuffer;
	LPSTR pEOF;
	char cProtocol[_MAX_PATH];
	char cSubdir[_MAX_PATH];
	char cPath[_MAX_PATH];
	char cFilename[_MAX_PATH];

	// we need Buffers to play with
	pBuffer = new char [PAGEBUFFERSIZE];
	pURLBuffer = new char [PAGEBUFFERSIZE];
	pFileSpec = new char [_MAX_PATH + 1];

	// get a line from HTML file
	pEOF = fgets(pBuffer, PAGEBUFFERSIZE, hParseFile);

	// loop through file
	while (pEOF != NULL)
		{
		// strip newline
		pEOF = strchr(pBuffer, '\n');
		if (pEOF != NULL)
			*pEOF = '\0';

		// is there a desired element on this line
		if (LookForTagAndExtractValue(pBuffer))
			{
			// if so then parse and get URL for it
			MyInternetSplitPath(pBaseURL, pBuffer, cProtocol, cPath, cSubdir, cFilename);
			MyInternetMakePath(pURLBuffer, cProtocol, cPath, cSubdir, cFilename);

			// should we ignore this extension
			if (AcceptExtension(cFilename))
				{
				// send URL back
				strcpy(pURLOutputBuffer, pURLBuffer);
				strcpy(pFilename, cFilename);
				pEOF = pURLOutputBuffer;
				break;
				}
			}
		pEOF = fgets(pBuffer, PAGEBUFFERSIZE, hParseFile);
		}

	// close down and release resources
	delete [] pURLBuffer;
	delete [] pBuffer;
	delete [] pFileSpec;

	// return with success
	return(pEOF);
	}



//
// routine to close parse file
//
BOOL CNetGet::ParseClose()
	{
	// close input file
	fclose(hParseFile);

	return(TRUE);
	}



//
// routine to show statistics
//
void CNetGet::ShowStatistics()
	{
	if (bQuietMode)
		return;

	printf("\n# of URLs read: %ld\n", lURLsReadSuccess + lURLsReadFailure);
	printf("  successful  : %ld\n", lURLsReadSuccess);
	printf("  failed      : %ld\n", lURLsReadFailure);
	printf("\nTotal bytes written to disk: %ld\n", lBytesWrittenToDisk);
	return;
	}



//
// routine to read extensons file
//
int CNetGet::ReadExtensionFile(LPSTR pKeyFile)
	{
	FILE * hFile;
	LPSTR pBuffer;
	LPSTR pPtr;

	// get working buffer
	pBuffer = new char[256];

	// open keyword file
	hFile = fopen(pKeyFile, "rt");

	// if open
	if (hFile != NULL)
		{

		// get line and loop through file
		pPtr = fgets(pBuffer, 256, hFile);
		while (pPtr != NULL)
			{
			// strip newline
			pPtr = strchr(pBuffer, '\n');
			if (pPtr)
				{
				*pPtr = '\0';
				}

			// store result in array
			pAcceptableExtensions[iLastExtension] = new char [strlen(pBuffer)];
			strcpy(pAcceptableExtensions[iLastExtension], pBuffer);
			iLastExtension++;

			// get next line in file
			pPtr = fgets(pBuffer, 256, hFile);
			}
		}

	// close file, release working buffer
	fclose(hFile);
	delete [] pBuffer;

	// return keyword count
	return(iLastExtension);
	}



//
// routine to determine if we should ignore the specified file
//
BOOL CNetGet::AcceptExtension(LPSTR pFilename)
	{
	int i;
	BOOL bResult = FALSE;
	char cExt[_MAX_PATH];
	LPSTR pPtr;

	// get copy of filespec
	strcpy(cExt, pFilename);

	// look for last '.'
	pPtr = strrchr(cExt, '.');

	// if one found
	if (pPtr)
		{
		// move to start of extension
		pPtr++;

		// scan through table looking for match
		for (i = 0; i < iLastExtension; i++)
			{
				// if match found then signal user and exit loop
				if (stricmp(pPtr, pAcceptableExtensions[i]) == 0)
					{
					bResult = TRUE;
					break;
					}
			}
		}

	// return result
	return(bResult);
	}



//
// simple routine to normalize URL
//
LPSTR CNetGet::NormalizeURL(LPSTR pURL, LPSTR pReturnBuffer)
	{
	BOOL bHasProtocal = FALSE;

	// URL must start with http:, ftp:, gopher: if not then start with http:
	if (strnicmp(pURL, "HTTP:", 5) == 0)
		bHasProtocal = TRUE;

	if (strnicmp(pURL, "FTP:", 4) == 0)
		bHasProtocal = TRUE;

	if  (strnicmp(pURL, "GOPHER:", 7) == 0)
		bHasProtocal = TRUE;

	// if no protocal then add default
	if (!bHasProtocal)
		{
		// add default protcal
		strcpy(pReturnBuffer, "HTTP:");
		// if not even leading // then add that too
		if (strncmp(pURL, "//", 2))
			{
			strcat(pReturnBuffer, "//");
			}
		// add pURL
		strcat(pReturnBuffer, pURL);
		// is last char a /
		if (strrchr(pURL, '/') != pURL + strlen(pURL))
			strcat(pReturnBuffer, "/");
		}
	else
		{
		strcpy(pReturnBuffer, pURL);
		}

	return(pReturnBuffer);
	}



//
// routine to generate or ask user for default file spec
//
LPSTR CNetGet::GetDefaultFileSpec(LPSTR pFilename)
	{
	char cFilename[_MAX_PATH];

	strcpy(cFilename, pFilename);

	// if we got passed a blank name
	if (strlen(pFilename) == 0)
		{
		// if prompting user then do so
		if (bPromptMode && !bQuietMode)
			{
			printf("\a\nDefault filename required: [Enter=%s.%s] ", DEFAULT_NAME, DEFAULT_EXT);
			gets(cFilename);
			// if blank line then use default filespec
			if (strlen(cFilename) == 0)
				{
				sprintf(cFilename, "%s.%s", DEFAULT_NAME, DEFAULT_EXT);
				}
			}
		else
			// if not prompting user
			{
			// use name appropriate for default name counter
			if (iDefaultFileCount == 0)
				{
				sprintf(cFilename, "%s.%s", DEFAULT_NAME, DEFAULT_EXT);
				}
			else
				{
				sprintf(cFilename, "%s_%d.%s", DEFAULT_NAME, iDefaultFileCount, DEFAULT_EXT);
				}
			// increment counter
			iDefaultFileCount++;
			}
		}

	// pass back new name to user
	strcpy(pFilename, cFilename);
	return(pFilename);
	}
