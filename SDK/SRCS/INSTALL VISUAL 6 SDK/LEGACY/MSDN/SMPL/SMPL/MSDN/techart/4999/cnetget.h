#ifndef __CNETGET__
#define __CNETGET__

#include <windows.h>
#include <wininet.h>

// list of possible characters which start a tag's value
#define ParamDelimiters "<>\" "

// list of possible characters which terminate a tag's value
#define ParamSeparators  "<>\" #,?&"

// buffer sizes
#define URLBUFFERSIZE 65535
#define PAGEBUFFERSIZE 8192
#define LINESIZE 1024
#define MAXKEYWORDS 16



//
// default file parts
//
#define DEFAULT_NAME "DEFAULT"
#define DEFAULT_EXT "HTML"
#define TEMPFILESPEC "$NETGET$.$$$"



//
// class definition
//
class CNetGet
	{
	public:
		// enumerations
		enum
			{
			NG_SUCCESS = 0,
			NG_BADCONNECTION,
			NG_INVALIDURL
			};

		// member functions
		CNetGet();
		~CNetGet();
		
		BOOL StartInternetSession(LPSTR pServer = "Microsoft Internet Explorer");
		void StopInternetSession();
		
		int GetURLInformation(LPSTR pURL, LPSTR pOutputDir, LPSTR pOutputSpec);
		int ParseURL(LPSTR pURL, LPSTR pOutputDir, LPSTR pInputSpec);
		int IsCommandLineSwitchSet(int argc, char * argv[], int iSwitch);

		DWORD GetLastError();
		BOOL AddKeyword(LPSTR pKeyword, LPSTR pElement, int iProcessingMode);
		BOOL ReadExtensionFile(LPSTR pDataFile);
		
		BOOL Set_ExtractGraphics(BOOL bValue);
		BOOL Set_ExtractBaggage(BOOL bValue);
		BOOL Set_Logging(BOOL bValue);
		BOOL Set_MakeDataFile(BOOL bValue);
		BOOL Set_QuietMode(BOOL bValue);
		BOOL Set_PromptMode(BOOL bValue);
		BOOL Set_UniqueFiles(BOOL bValue);
		BOOL Set_RewriteReferences(BOOL bValue);

		int ReadKeyFile(LPSTR pKeyFile);
		BOOL ParseOpen(LPSTR pInputFile);
		LPSTR ParseFirstURL(LPSTR pBaseURL, LPSTR pURLOutputBuffer, LPSTR pOutputDir, LPSTR pFilename);
		LPSTR ParseNextURL(LPSTR pBaseURL, LPSTR pURLOutputBuffer, LPSTR pOutputDir, LPSTR pFilename);
		LPSTR NormalizeURL(LPSTR pURL, LPSTR pReturnBuffer);
		BOOL ParseClose();
		void ShowStatistics();

	protected:
		// tables and arrays
		LPSTR pAcceptableExtensions[MAXKEYWORDS];
		LPSTR pKeywordArray[MAXKEYWORDS];
		LPSTR pElementArray[MAXKEYWORDS];
		int iProcessingArray[MAXKEYWORDS];

		// misc
		long lBytesWrittenToDisk;
		long lURLsReadSuccess;
		long lURLsReadFailure;
		int iLastKeyword;
		int iLastExtension;
		int iDefaultFileCount;
		DWORD dwGLE;
		HINTERNET hInternetSession;
		FILE * hParseFile;

		// flags
		BOOL bQuietMode;
		BOOL bExtractGraphics;
		BOOL bExtractBaggage;
		BOOL bLogging;
		BOOL bMakeDataFile;
		BOOL bPromptMode;
		BOOL bUniqueFiles;

		// member functions
		BOOL LookForTagAndExtractValue(LPSTR pLine);
		LPSTR ExtractTagValue(LPSTR pLine, LPSTR pKeyword);
		void MyInternetSplitPath(LPSTR pURLBase, LPSTR pUserURL, LPSTR pUserProtocol, LPSTR pUserPath, LPSTR pUsersubdir, LPSTR pUserFilename);
		LPSTR MyInternetMakePath(LPSTR pCompleteURL, LPSTR pUserProtocol, LPSTR pUserPath, LPSTR pUsersubdir, LPSTR pUserFilename);
		BOOL AcceptExtension(LPSTR pFilename);
		LPSTR GetDefaultFileSpec(LPSTR pFilename);
	};

#endif // #ifndef __CNETGET__
