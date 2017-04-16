//cgispawn.h
char *szError = "The server was unable to start the process %s<p>\r\n";
char szNoProcess[MAX_PATH];
char TempInFile[MAX_PATH];
char TempOutFile[MAX_PATH];
char ModuleFilePath[MAX_PATH];
char ServerPath[MAX_PATH];
char temppath[MAX_PATH];
char FileToSpawn[MAX_PATH];
char line[80];
HANDLE hTempInFile;
HANDLE hTempOutFile;
DWORD cbBytesWritten;
DWORD dw ;
entry entries[MAX_ENTRIES];
int x,m=0;
char szCommandLine[MAX_PATH];
PROCESS_INFORMATION pi;
STARTUPINFO si;
int i = 0;
long lTimeOut;

void getword(char *word, char *line, char stop);
char *makeword(char *line, char stop);
char *fmakeword(FILE *f, char stop, int *len);
char x2c(char *what);
void unescape_url(char *url);
void plustospace(char *str);
void GetModuleFilePath(char *pszPath);
BOOL GetHTTPServerPath(char *pszPath);
int GetNameValuePairs(entry* entries, LPSTR FileToSpawn);
void WriteNameValuePairsToFile(HANDLE hTempFile, entry *entries, int m, LPSTR FileToSpawn, long *lTimeOut);
void WriteEnvToFile(HANDLE hTempInFile, char *env[]);
void SpawnNewProcess(LPSTR ServerPath, LPSTR szCommandLine, 
					 STARTUPINFO *si, PROCESS_INFORMATION *pi, 
					 long lTimeOut, HANDLE hTempOutFile);
void WriteFileToSTDOUT(LPSTR szFN);
BOOL IsRegisteredApp(LPSTR AppName);
void ErrMsg(LPSTR ErrMsg, int nAction, int nErrCode);
