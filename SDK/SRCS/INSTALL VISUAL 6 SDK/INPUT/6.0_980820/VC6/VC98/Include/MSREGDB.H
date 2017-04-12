#ifndef STF_LITE


#define REG_DB_ENABLED

#ifdef WIN16
#define REG_SZ                1
#define HKEY_CLASSES_ROOT     1
#define ERROR_SUCCESS         0
#endif

#define GRC_API_FAILED        104

extern int   APIENTRY EercErrorHandler(int grc, int fVital, LPSTR sz1,
				LPSTR sz2, LPSTR sz3);


extern BOOL  FInitRegDb(void);

#ifdef WIN16
extern LONG  APIENTRY RegOpenKey(LONG hKey, LPSTR szSubKey, LPSTR phkResult);
extern LONG  APIENTRY RegCreateKey(LONG hKey, LPSTR szSubKey,
				LPSTR phkResult);
extern LONG  APIENTRY RegDeleteKey(LONG hKey, LPSTR szSubKey);
extern LONG  APIENTRY RegCloseKey(LONG hKey);
extern LONG  APIENTRY RegQueryValue(LONG hKey, LPSTR szSubKey, LPSTR szValue,
				LPSTR lpcb);
extern LONG  APIENTRY RegSetValue(LONG hKey, LPSTR szSubKey, LONG dwType,
				LPSTR szValue, LONG cbValue);
extern LONG  APIENTRY RegEnumKey(LONG hKey, LONG dwIndex, LPSTR szBuffer,
				LONG dwBufferSize);
#endif


extern void  CreateRegKey(LPSTR szKey);
extern void  CreateRegKeyValue(LPSTR szKey, LPSTR szValue);
extern void  SetRegKeyValue(LPSTR szKey, LPSTR szValue);
extern void  DeleteRegKey(LPSTR szKey);
extern LPSTR GetRegKeyValue(LPSTR szKey, LPSTR zsBuf, int cbBuf);
extern int   DoesRegKeyExist(LPSTR szKey);


#ifdef WIN32
extern void   CreateRegKeyEx(HKEY hKey, LPCSTR szKey);
extern void   CreateRegKeyValueEx(HKEY hKey, LPCSTR szKey, LPSTR szValueName, DWORD dwType, LPBYTE lpValueData, DWORD dwDataLen);
extern void   SetRegKeyValueEx(HKEY hKey, LPCSTR szKey, LPSTR szValueName, DWORD dwType, LPBYTE szValueData, DWORD dwDataLen);
extern void   DeleteRegKeyEx(HKEY hKey, LPCSTR szKey);
extern LONG   GetRegKeyValueEx(HKEY hKey, LPCSTR szKey, LPSTR szValueName, LPDWORD lpdwType, LPBYTE lpBuf, DWORD cbBuf);
extern int    DoesRegKeyExistEx(HKEY hKey, LPCSTR szKey);
extern BOOL   DeleteAllSubKeys(HKEY hKey, LPCSTR szKey);
#endif
#endif  /* !STF_LITE */
