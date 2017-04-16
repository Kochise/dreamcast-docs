void getword(char *word, char *line, char stop);
char *makeword(char *line, char stop);
char *fmakeword(FILE *f, char stop, int *len);
char x2c(char *what);
void unescape_url(char *url);
void plustospace(char *str);
void GetModuleFilePath(char *pszPath);
BOOL GetHTTPServerPath(char *pszPath);
int  GetNameValuePairs(entry* entries);
void WriteNameValuePairsToFile(HANDLE hTempFile, entry *entries, int m, LPSTR FileToSpawn, long *lTimeOut);
void WriteEnvToFile(HANDLE hTempInFile, char *env[]);
void SpawnNewProcess(LPSTR ServerPath, LPSTR szCommandLine, 
					 STARTUPINFO *si, PROCESS_INFORMATION *pi, 
					 long lTimeOut, HANDLE hTempOutFile);
void WriteFileToSTDOUT(LPSTR szFN);
void ErrMsg(LPSTR ErrMsg, int nAction, int nErrCode);




