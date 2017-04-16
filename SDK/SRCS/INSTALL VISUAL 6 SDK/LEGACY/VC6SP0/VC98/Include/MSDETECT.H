//
// Imported functions from MSDETSTF.DLL
//

extern BOOL  APIENTRY FFileInUse(LPSTR szFile);
extern int   APIENTRY CbGetDateOfFile(LPSTR szFile, LPSTR szBuf, int cbBuf);
extern int   APIENTRY CbGetVersionOfFile(LPSTR szFile, LPSTR szBuf,
				int cbBuf);
extern int   APIENTRY GetExistingFOTFileForTTF(LPSTR szFile, LPSTR szBuf,
				int cbBuf);
extern int   APIENTRY FGetValidDrivesList(LPSTR szSymbol);
extern int   APIENTRY FGetLocalHardDrivesList(LPSTR szSymbol);
extern int   APIENTRY FGetNetworkDrivesList(LPSTR szSymbol);
#ifdef WIN16
extern DWORD APIENTRY LcbTotalDrive(int nDrive);
extern DWORD APIENTRY LcbFreeDrive(int nDrive);
#endif
#ifdef WIN32
extern DWORDLONG  APIENTRY LcbTotalDrive(int nDrive);
extern DWORDLONG  APIENTRY LcbFreeDrive(int nDrive);
#endif
extern DWORD APIENTRY LcbGetSizeOfFile(LPSTR szFile);
extern int   APIENTRY FIsValidDrive(int nDrive);
extern int   APIENTRY FIsLocalHardDrive(int nDrive);
extern int   APIENTRY FIsRemoveDrive(int nDrive);
extern int   APIENTRY FIsRemoteDrive(int nDrive);
extern int   APIENTRY FDirExists(LPSTR szDir);
extern int   APIENTRY FDoesFileExist(LPSTR szFileName, int mode);
extern int   APIENTRY FDoesIniKeyExist(LPSTR szFile, LPSTR szSect,
				LPSTR szKey);
extern int   APIENTRY CbGetIniKeyString(LPSTR szFile, LPSTR szSect,
				LPSTR szKey, LPSTR szBuf, int cbBuf);
#ifndef STF_LITE
extern int   APIENTRY FGetRemovableDrivesList(LPSTR szSymbol);
extern LONG  APIENTRY LGetVersionNthField(LPSTR szVersion, int nField);
extern int   APIENTRY FDoesIniSectionExist(LPSTR szFile, LPSTR szSect);
extern int   APIENTRY WGetDOSMajorVersion(void);
extern int   APIENTRY WGetDOSMinorVersion(void);
extern int   APIENTRY CbGetEnvVariableValue(LPSTR szEnvVar, LPSTR szBuf,
				int cbBuf);
extern int   APIENTRY WGetNumWinApps(void);
extern int   APIENTRY FGetParallelPortsList(LPSTR szSymbol);
extern int   APIENTRY FGetSerialPortsList(LPSTR szSymbol);
extern int   APIENTRY FHas87MathChip(void);
extern int   APIENTRY FHasMonochromeDisplay(void);
extern int   APIENTRY FHasMouseInstalled(void);
extern int   APIENTRY FIsDriverInConfig(LPSTR szDrv);
extern int   APIENTRY WGetConfigSmartdrvSize(void);
extern int   APIENTRY WGetConfigRamdriveSize(void);
extern int   APIENTRY WGetConfigNumBuffers(void);
extern int   APIENTRY WGetConfigNumFiles(void);
extern int   APIENTRY WGetConfigLastDrive(void);
extern int   APIENTRY FGetProcessorType(LPSTR, USHORT, LPSTR, unsigned);
extern int   APIENTRY CbFindTargetOnEnvVar(LPSTR szFile, LPSTR szEnvVar,
				LPSTR szBuf, int cbBuf);
extern int   APIENTRY CbFindFileInTree(LPSTR szFile, LPSTR szDir, LPSTR szBuf,
				int cbBuf);
#endif



//
//  Configuration detection wrapper functions
//
extern BOOL  IsDriveValid(LPSTR szDrive);
extern BOOL  IsDriveLocalHard(LPSTR szDrive);
extern BOOL  IsDriveRemovable(LPSTR szDrive);
extern BOOL  IsDriveNetwork(LPSTR szDrive);
extern VOID  GetValidDrivesList(LPSTR szSymbol);
extern VOID  GetLocalHardDrivesList(LPSTR szSymbol);
extern VOID  GetNetworkDrivesList(LPSTR szSymbol);
#ifdef WIN16
extern DWORD GetTotalSpaceForDrive(LPSTR szDrive);
extern DWORD GetFreeSpaceForDrive(LPSTR szDrive);
#endif
#ifdef WIN32
extern DWORDLONG GetTotalSpaceForDrive(LPSTR szDrive);
extern DWORDLONG GetFreeSpaceForDrive(LPSTR szDrive);
#endif
extern BOOL  DoesFileExist(LPSTR szFile, int mode);
extern DWORD GetSizeOfFile(LPSTR szFile);
extern BOOL  DoesDirExist(LPSTR szDir);
extern BOOL  DoesIniKeyExist(LPSTR szFile, LPSTR szSect,
				LPSTR szKey);
extern LPSTR GetIniKeyString(LPSTR szFile, LPSTR szSect, LPSTR szKey,
				LPSTR szBuf, int cbBuf);
extern LPSTR GetDateOfFile(LPSTR szFile, LPSTR szBuf, int cbBuf);
extern INT   GetYearFromDate(LPSTR szDate);
extern INT   GetMonthFromDate(LPSTR szDate);
extern INT   GetDayFromDate(LPSTR szDate);

#ifndef STF_LITE
extern VOID  GetRemovableDrivesList(LPSTR szSymbol);
extern INT   GetTypeFaceNameFromTTF(LPSTR szFile, LPSTR szBuf,
				int cbBuf);

extern LPSTR GetEnvVariableValue(LPSTR szEnvVar, LPSTR szBuf,
				int cbBuf);

extern INT   GetHourFromDate(LPSTR szDate);
extern INT   GetMinuteFromDate(LPSTR szDate);
extern INT   GetSecondFromDate(LPSTR szDate);
extern LPSTR GetVersionOfFile(LPSTR szFile, LPSTR szBuf, int cbBuf);
extern LONG  GetVersionNthField(LPSTR szVersion, int nField);
extern LPSTR FindTargetOnEnvVar(LPSTR szFile, LPSTR szEnvVar,
				LPSTR szBuf, int cbBuf);
extern LPSTR FindFileInTree(LPSTR szFile, LPSTR szDir, LPSTR szBuf,
				int cbBuf);
extern BOOL  DoesIniSectionExist(LPSTR szFile, LPSTR szSect);
extern BOOL  IsDriverInConfig(LPSTR szDrv);
extern INT   GetProcessorType(void);
extern VOID  GetParallelPortsList(LPSTR szSymbol);
extern VOID  GetSerialPortsList(LPSTR szSymbol);
extern BOOL  Has87MathChip(void);
extern BOOL  HasFPPMathChip(void);
extern BOOL  HasMonochromeDisplay(void);
extern BOOL  HasMouseInstalled(void);
extern INT   GetDOSMajorVersion(void);
extern INT   GetDOSMinorVersion(void);
extern INT   GetNumWinApps(void);
extern INT   GetConfigSmartdrvSize(void);
extern INT   GetConfigRamdriveSize(void);
extern INT   GetConfigNumBuffers(void);
extern INT   GetConfigNumFiles(void);
extern LPSTR GetConfigLastDrive(LPSTR szBuf, int cbBuf);
#endif  /* !STF_LITE */
