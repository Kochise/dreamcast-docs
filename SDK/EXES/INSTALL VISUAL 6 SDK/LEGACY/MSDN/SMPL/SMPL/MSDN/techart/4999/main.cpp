#include <stdio.h>

#include "cNetGet.h"

// function declarations
int main(int argc, char * argv[]);
BOOL ProcessOnePage(LPSTR pURL, LPSTR pOutputSpec);
int ProcessDataFile(LPSTR pDatafile, LPSTR pOutputSpec);
BOOL Initialize(int argc, char * argv[]);
void Usage();

CNetGet NG;

// main processing loop
int main(int argc, char * argv[])
	{
	BOOL bDataFileSpecified = FALSE;
	LPSTR pURL;
	LPSTR pOutputSpec;
	int n;

	// if insufficient arguments then display usage
	if (argc < 2)
		{
		Usage();
		return(0);
		}

	// start internet session, display msg if error
	if (!NG.StartInternetSession())
		{
		printf("Unable to start Internet session. GetLastError() returned %ld. Aborting.../n", NG.GetLastError());
		return(1);
		}

	// initialize since connected now
	Initialize(argc, argv);

	// look for -l switch to specify whether or not to log errors and statistics
	if (NG.IsCommandLineSwitchSet(argc, argv, 'd') != 0)
		{
		bDataFileSpecified = TRUE;
		}

	// acquire working buffers
	pURL = new char [_MAX_PATH + 1];
	pOutputSpec = new char [_MAX_PATH + 1];

	// store arguments
	for (n = 1; n < argc; n++)
		{
		if (isalnum(argv[n][0]))
			{
			strcpy(pURL, argv[n]);
			strcpy(pOutputSpec, argv[n + 1]);
			break;
			}
		}

	// get page, and parse page if no error
	if (bDataFileSpecified)
		{
		ProcessDataFile(pURL, pOutputSpec);
		}
	else
		{
		ProcessOnePage(pURL, pOutputSpec);
		}

	// terminate internet session
	NG.StopInternetSession();
	NG.ShowStatistics();

	// release working buffers
	delete [] pURL;
	delete [] pOutputSpec;

	// exit
	return(0);
	}



//
//
//
int ProcessDataFile(LPSTR pDatafile, LPSTR pOutputSpec)
	{
	LPSTR pURL;
	LPSTR pPtr;
	FILE * hFile;
	int iCount = 0;

	// get working buffer
	pURL = new char [_MAX_PATH + 1];

	// open data file
	hFile = fopen(pDatafile, "rt");

	// while data t process
	while (!feof(hFile))
		{
		// if we can read some data
		if (fgets(pURL, _MAX_PATH, hFile) > 0)
			{
			// and it is not a commented out line
			if (*pURL != ';')
				{
				// strip off newline
				pPtr = strchr(pURL, '\n');
				if (pPtr)
					{
					*pPtr = '\0';
					}
				// if not a blank line
				if (strlen(pURL) > 0)
					{
					// then process this URL
					ProcessOnePage(pURL, pOutputSpec);
					iCount++;
					}
				}
			}
		else
			{
			break;
			}
		}

	// close data file
	fclose(hFile);

	// return count of URLs processed
	return(iCount);
	}



//
//
//
BOOL ProcessOnePage(LPSTR pURL, LPSTR pOutputDir)
	{
	char cOutputSpec[_MAX_PATH];
	char cCompleteURL[_MAX_PATH];

	// normalize user URL if need be
	NG.NormalizeURL(pURL, cCompleteURL);

	BOOL bResult = TRUE;
	if (NG.GetURLInformation(cCompleteURL, pOutputDir, cOutputSpec) == CNetGet::NG_SUCCESS)
		{
		NG.ParseURL(cCompleteURL, pOutputDir, cOutputSpec);
		}
	else
		{
		printf("Unable to get URL %s\n. GetLastError() returned %ld. Ending...\n", pURL, NG.GetLastError());
		bResult = FALSE;
		}
	return(bResult);
	}



//
//
//
BOOL Initialize(int argc, char * argv[])
	{
	BOOL bFlag;
	char cDrive[_MAX_DRIVE];
	char cDir[_MAX_DIR];
	char cDataFile[_MAX_PATH];

	// look for -p switch to prompt for default file names
	bFlag = FALSE;
	if (NG.IsCommandLineSwitchSet(argc, argv, 'p') != 0)
		{
		bFlag = TRUE;
		}
	NG.Set_PromptMode(bFlag);

	// look for -q switch to specify whether or not to be quiet
	bFlag = FALSE;
	if (NG.IsCommandLineSwitchSet(argc, argv, 'q') != 0)
		{
		bFlag = TRUE;
		}
	NG.Set_QuietMode(bFlag);

	// look for -u switch to specify whether or not to overwrite duplicate files
	bFlag = FALSE;
	if (NG.IsCommandLineSwitchSet(argc, argv, 'u') != 0)
		{
		bFlag = TRUE;
		}
	NG.Set_UniqueFiles(bFlag);

	// look for -m switch to specify whether or not to make a data file from URLs found
	bFlag = FALSE;
	if (NG.IsCommandLineSwitchSet(argc, argv, 'm') != 0)
		{
		bFlag = TRUE;
		}
	NG.Set_MakeDataFile(bFlag);

	// look for -e switch to specify whether or not to extract graphics
	bFlag = FALSE;
	if (NG.IsCommandLineSwitchSet(argc, argv, 'e') != 0)
		{
		bFlag = TRUE;
		}
	NG.Set_ExtractBaggage(bFlag);

	// look for -b switch to specify whether or not to extract 'baggage' files
	bFlag = FALSE;
	if (NG.IsCommandLineSwitchSet(argc, argv, 'b') != 0)
		{
		bFlag = TRUE;
		}
	NG.Set_ExtractBaggage(bFlag);

	// look for -l switch to specify whether or not to log errors and statistics
	bFlag = FALSE;
	if (NG.IsCommandLineSwitchSet(argc, argv, 'l') != 0)
		{
		bFlag = TRUE;
		}
	NG.Set_Logging(bFlag);

	// create array of tags to look for
	_splitpath(argv[0], cDrive, cDir, NULL, NULL);
	_makepath(cDataFile, cDrive, cDir, "NETGET", ".KYS");
	NG.ReadKeyFile(cDataFile);

	// create array of acceptable extensions to look for
	_splitpath(argv[0], cDrive, cDir, NULL, NULL);
	_makepath(cDataFile, cDrive, cDir, "NETGET", ".EXT");
	NG.ReadExtensionFile(cDataFile);

	return(TRUE);
	}



//
// routine to display help
//
void Usage()
	{
	puts("Usage: NetGet [switches] URL|datafile dir|file [");
	puts("");
	puts("where switches can be any combinations of the following:");
	puts("      -e  - extracts only graphics files");
	puts("      -d  - use datafile containing list of URLs, instead of URL");
	puts("      -l  - log errors and statistics");
	puts("      -m  - create datafile from URL contents");
	puts("      -b  - extract baggage(links) also");
	puts("      -q  - run in quiet mode");
	puts("      -p  - prompt for default file names");
	puts("      -u  - make unique files, does not overwrite duplicates");
	puts("      Note: Combining certain switches may not have the desired effect.");
	puts("      e.g. the -m and -d are mutually exclusive");
	puts("");
	puts("      URL|datafile is either a URL to download or the name of a file");
	puts("                    containing a list of crlf delimited URLs to download");
	puts("");
	puts("      dir|file     is either the name of the directory to store the");
	puts("                   contents in; or the name of the output file to store");
	puts("                   the results of the -m switch");
	}
