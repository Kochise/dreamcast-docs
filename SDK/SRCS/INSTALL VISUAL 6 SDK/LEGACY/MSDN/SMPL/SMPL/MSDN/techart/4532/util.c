#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include "global.h"
#include "util.h"

void getword(char *word, char *line, char stop) {
    int x = 0,y;

    for(x=0;((line[x]) && (line[x] != stop));x++)
        word[x] = line[x];

    word[x] = '\0';
    if(line[x]) ++x;
    y=0;

    while(line[y++] = line[x++]);
}

char *makeword(char *line, char stop) {
    int x = 0,y;
    char *word = (char *) malloc(sizeof(char) * (strlen(line) + 1));

    for(x=0;((line[x]) && (line[x] != stop));x++)
        word[x] = line[x];

    word[x] = '\0';
    if(line[x]) ++x;
    y=0;

    while(line[y++] = line[x++]);
    return word;
}

char *fmakeword(FILE *f, char stop, int *cl) {
    int wsize;
    char *word;
    int ll;

    wsize = 102400;
    ll=0;
    word = (char *) malloc(sizeof(char) * (wsize + 1));

    while(1) {
        word[ll] = (char)fgetc(f);
        if(ll==wsize) {
            word[ll+1] = '\0';
            wsize+=102400;
            word = (char *)realloc(word,sizeof(char)*(wsize+1));
        }
        --(*cl);
        if((word[ll] == stop) || (feof(f)) || (!(*cl))) {
            if(word[ll] != stop) ll++;
            word[ll] = '\0';
            return word;
        }
        ++ll;
    }
}

char x2c(char *what) {
    register char digit;

    digit = (what[0] >= 'A' ? ((what[0] & 0xdf) - 'A')+10 : (what[0] - '0'));
    digit *= 16;
    digit += (what[1] >= 'A' ? ((what[1] & 0xdf) - 'A')+10 : (what[1] - '0'));
    return(digit);
}

void unescape_url(char *url) {
    register int x,y;

    for(x=0,y=0;url[y];++x,++y) {
        if((url[x] = url[y]) == '%') {
            url[x] = x2c(&url[y+1]);
            y+=2;
        }
    }
    url[x] = '\0';
}

void plustospace(char *str) {
    register int x;

    for(x=0;str[x];x++) if(str[x] == '+') str[x] = ' ';
}

int rind(char *s, char c) {
    register int x;
    for(x=strlen(s) - 1;x != -1; x--)
        if(s[x] == c) return x;
    return -1;
}

int getline(char *s, int n, FILE *f) {
    register int i=0;

    while(1) {
        s[i] = (char)fgetc(f);

        if(s[i] == CR)
            s[i] = fgetc(f);

        if((s[i] == 0x4) || (s[i] == LF) || (i == (n-1))) {
            s[i] = '\0';
            return (feof(f) ? 1 : 0);
        }
        ++i;
    }
}

void send_fd(FILE *f, FILE *fd)
{
    int num_chars=0;
    char c;

    while (1) {
        c = fgetc(f);
        if(feof(f))
            return;
        fputc(c,fd);
    }
}

void GetModuleFilePath(char *pszPath)
{
	char TempFileName[MAX_PATH];
	char *pTempFileName;
	char *pTempPath;
	int ch = '\\';
	int nLen;
	int i;

	pTempFileName = TempFileName;

	GetModuleFileName(NULL, TempFileName, MAX_PATH);

	pTempPath = strrchr(TempFileName, ch);
	nLen = strlen(TempFileName) - strlen(pTempPath) + 1;

	for (i = 0;i < nLen;i++) {
		*pszPath++ = *pTempFileName++;
	}
}


BOOL GetHTTPServerPath(char *pszPath)
{
	BOOL bRet = FALSE;

    // Read the current state from the registry
    // Try opening the registry key:
    // HKEY_CURRENT_USER\Control Panel\<AppName>
    HKEY hparams;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
    				 "SYSTEM\\CurrentControlSet\\Services\\HTTPS\\Parameters",
            		 0,
            		 KEY_QUERY_VALUE,
            		 &hparams) == ERROR_SUCCESS) {
	
   		DWORD dwType = 0;
  		DWORD dwSize = MAX_PATH;
    	if (RegQueryValueEx(hparams,
    		        	"Directory",
                        NULL,
                        &dwType,
                        pszPath,
                        &dwSize)== ERROR_SUCCESS)  {
			bRet = TRUE;
		}

		RegCloseKey(hparams);
	}
	return(bRet);
}

int GetNameValuePairs(entry *entries, LPSTR FileToSpawn)
{
    int x,m=0;
    int cl;
    char *pccl;

    if(!strcmp(getenv("REQUEST_METHOD"),"GET")) {
		pccl = getenv("QUERY_STRING");
    	if(pccl == NULL) {
	        printf("No query information to decode.\n");
			return 0;
    	}
	    for(x=0;pccl[0] != '\0';x++, entries++) {
    	    m=x;
			entries->val = makeword(pccl, '&');
        	plustospace(entries->val);
        	unescape_url(entries->val);
			entries->name = makeword(entries->val, '=');
			//capture the name of the app to be spawned
			if (!strcmp(_strupr(entries->name), "SPAWN"))
				strcpy(FileToSpawn, entries->val);
    	}
	}

	//if using POST method, grab the name/value pairs from the post
    if(!strcmp(getenv("REQUEST_METHOD"),"POST")) {

	    if(strcmp(getenv("CONTENT_TYPE"),"application/x-www-form-urlencoded")) {
    	    printf("This script can only be used to decode form results. \n");
			return 0;
	    }

    	cl = atoi(getenv("CONTENT_LENGTH"));

    	for(x=0;cl && (!feof(stdin));x++, entries++) {
        	m=x;
        	entries->val = fmakeword(stdin,'&',&cl);
        	plustospace(entries->val);
        	unescape_url(entries->val);
        	entries->name = makeword(entries->val,'=');
			//capture the name of the app to be spawned
			if (!strcmp(_strupr(entries->name), "SPAWN"))
				strcpy(FileToSpawn, entries->val);
	   	}
 	}

	return (m);
}


void WriteNameValuePairsToFile(HANDLE hTempFile, entry *entries, 
							   int m, LPSTR FileToSpawn, long *lTimeOut)
{
	int x;
	char line[MAX_PATH];
	DWORD cbBytesWritten;
	char *szNameValueHdr = "[NameValuePairs]\r\n";

	//write the name/value pairs to the INFILE
	WriteFile(hTempFile, szNameValueHdr, strlen(szNameValueHdr), &cbBytesWritten, NULL);

    for(x=0; x <= m; x++, entries++)
	{
		strupr(entries->val);

		if (!strcmp(_strupr(entries->name), "TIMEOUT"))  
			  *lTimeOut = atol(entries->val);
		
		//format the line
		sprintf(line, "%s,%s%c%c",entries->name, entries->val, 13, 10);
		
 		if (!WriteFile(hTempFile, (LPCVOID)&line, strlen(line), &cbBytesWritten, NULL))
		  OutputDebugString("write failed\n");
   	}
}

void WriteEnvToFile(HANDLE hTempInFile, char *env[])
{
	int i = 0;
	char line[MAX_PATH];
	DWORD cbBytesWritten;
	char *szEnv = "[Environment]\r\n";

	WriteFile(hTempInFile, szEnv, strlen(szEnv), &cbBytesWritten, NULL);

	while (env[i]) {
		sprintf(line, "%s%c%c",env[i], 13, 10);
 		WriteFile(hTempInFile, (LPCVOID)&line, strlen(line), &cbBytesWritten, NULL);
        i++;
    }
}


void SpawnNewProcess(LPSTR ServerPath, LPSTR szCommandLine, 
					 STARTUPINFO *si, PROCESS_INFORMATION *pi, 
					 long lTimeOut, LPSTR TempOutFile)
{

	char *szError = "The server was unable to start the process or it timed out%s<p>\r\n";
	char szNoProcess[MAX_PATH];
	DWORD cbBytesWritten;
	DWORD dwWFSO;
	HANDLE hTempOutFile;


	//prepare the startupinfo structure
	si->cb = sizeof(STARTUPINFO);
    si->lpReserved = NULL;
    si->lpDesktop = NULL;
    si->lpTitle = NULL;
    si->dwFlags = 0;
    si->cbReserved2 = 0;
    si->lpReserved2 = NULL;

	//call the specified application and wait for it to signal completion (or timeout)
	if (CreateProcess(ServerPath, szCommandLine, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS,
		NULL, NULL, si, pi))  {

			UINT uiExitCode = 0;

			dwWFSO = WaitForSingleObject(pi->hProcess, 
										(lTimeOut > 0) ? (DWORD)lTimeOut : DEFTIMEOUT);

			if (dwWFSO == WAIT_FAILED) {
			  	dwWFSO = GetLastError();
			}

			if (dwWFSO == WAIT_TIMEOUT)	{

				hTempOutFile = CreateFile(TempOutFile, GENERIC_READ | GENERIC_WRITE, 0, NULL, 
											OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );
				sprintf(szNoProcess, szError, ServerPath);
				WriteFile(hTempOutFile, szNoProcess, strlen(szNoProcess), &cbBytesWritten, NULL);
				CloseHandle(hTempOutFile);
				TerminateProcess(pi->hProcess, uiExitCode);
			}
		}
}		
	
void WriteFileToSTDOUT(LPSTR szFN)
{
	char inBuffer;
	char *poutBuffer = NULL;
	char *ptemp = NULL;
	DWORD nBytesRead;
	BOOL bResult = FALSE;
	HANDLE hTempOutFile;
	BOOL fEOF = FALSE;

	poutBuffer = (char *)malloc(2 * MAX_PATH);

	if (poutBuffer) {

		ptemp = poutBuffer;

		hTempOutFile = CreateFile(szFN, GENERIC_READ, 0, NULL, OPEN_EXISTING, 
	    	       FILE_ATTRIBUTE_NORMAL, 0 );
	
		while (!fEOF)
		{
			bResult = ReadFile(hTempOutFile, &inBuffer, 1, &nBytesRead, NULL);
			// check for eof
			if (bResult &&  nBytesRead == 0) {
				fEOF = TRUE;
			}
			if (!fEOF) {
				if (inBuffer != LF) {
					*ptemp++ = inBuffer;
				}
				else {
					*ptemp++ = inBuffer;
					*ptemp = '\0';
					//send to stdout
					printf("%s", poutBuffer);
					//reset ptr for next line of input
			    	ptemp = poutBuffer;

				}
			}
  		}
		CloseHandle(hTempOutFile);

	  	free(poutBuffer);
	}

}	

BOOL IsRegisteredApp(LPSTR AppName)
{
	LONG lRet;
	HKEY hvalapps;
	char lpszSubKeyName[MAX_PATH];
	DWORD dwIndex = 0;
	BOOL bRet = FALSE;
	DWORD cchValue = MAX_PATH;

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
    				 "SOFTWARE\\cgispawn",
            		 0,
            		 KEY_READ,
            		 &hvalapps) == ERROR_SUCCESS) {

		lRet = RegEnumValue(hvalapps, dwIndex++, (LPSTR)&lpszSubKeyName, (LPDWORD)&cchValue,
							NULL, NULL, NULL, NULL);
		if (strstr(_strupr(AppName), _strupr(lpszSubKeyName))) {
			bRet = TRUE;
		}
		else {
			do {
				cchValue = MAX_PATH;
				lRet = RegEnumValue(hvalapps, dwIndex++, (LPSTR)&lpszSubKeyName, (LPDWORD)&cchValue,
									NULL, NULL, NULL, NULL);
				if (strstr(_strupr(AppName), _strupr(lpszSubKeyName))) {
					bRet = TRUE;
				}
			 
			} while (lRet != ERROR_NO_MORE_ITEMS &&  bRet == FALSE);
		}
		RegCloseKey(hvalapps);
	}
	return (bRet);
}

void ErrMsg(LPSTR ErrMsg, int nAction, int nErrCode)
{
	printf(ErrMsg);
	if (nAction == ERR_EXIT)  {
	  exit(nErrCode);
	}
}
