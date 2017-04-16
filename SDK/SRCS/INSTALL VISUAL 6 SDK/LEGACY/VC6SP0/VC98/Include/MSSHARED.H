#ifndef STF_LITE

extern BOOL SharedFileNeedsCopying;

extern BOOL  FixupWinIniMsappsSection(VOID);

extern BOOL  DoesSharedFileNeedCopying(VOID);

extern INT   WCompareVersion(LPSTR szVer1, LPSTR szVer2);

extern LPSTR FindSharedFileFromPath(LPSTR szField, LPSTR szVersion,
				LPSTR zsBuf, int cbBuf);

extern LPSTR SearchForLocationForSharedFile(LPSTR szRegDbKey,
				LPSTR szWinIniSect, LPSTR szWinIniKey, int iWinIniField,
				LPSTR szDefault, LPSTR szVersion, LPSTR szBuf, int cbBuf);

extern LPSTR HandleSharedFile(LPSTR szInfSection, LPSTR szInfKey,
				LPSTR szSubDir, LPSTR szRegDbKey, LPSTR szWinIniSect,
				LPSTR szWinIniKey, int iWinIniField, LPSTR szBuf, int cbBuf);
#endif  /* !STF_LITE */
