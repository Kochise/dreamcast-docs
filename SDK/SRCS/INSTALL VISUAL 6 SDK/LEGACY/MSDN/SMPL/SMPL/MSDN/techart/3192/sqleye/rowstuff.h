BOOL CheckBuffers(PCLIENTINFO pInfo);
BOOL ClearBuffers(PCLIENTINFO pInfo);
BOOL AddRow(HANDLE hInfo, char *szBuf, COLORREF color);
BOOL AddHeader(HANDLE hInfo, DBPROCESS *dbproc, COLORREF color);
BOOL AddResultRow(HANDLE hInfo, DBPROCESS *dbproc, COLORREF color);
RETCODE ConstructHeader(DBPROCESS *dbproc, LPSTR *pszHeader, char * szTheTime);
RETCODE ConstructRow(DBPROCESS *dbproc, LPSTR *pszDataVals, char * szTheTime);
int DetermineRowSize(DBPROCESS *dbproc,int iCol);
int GetConvertedLength(int SQLType, int Length, DBPROCESS * dbproc);
