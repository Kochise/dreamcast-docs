/*++

Copyright (c) 1997-1998  Microsoft Corporation

Module Name: tlhelp32.h

Purpose: Toolhelp include file for Windows

--*/

#ifndef __TOOLHELP32_H__
#define __TOOLHELP32_H__

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

#define TH32CS_SNAPHEAPLIST 0x00000001
#define TH32CS_SNAPPROCESS  0x00000002
#define TH32CS_SNAPTHREAD   0x00000004
#define TH32CS_SNAPMODULE   0x00000008
#define TH32CS_SNAPALL	    (TH32CS_SNAPHEAPLIST | TH32CS_SNAPPROCESS | TH32CS_SNAPTHREAD | TH32CS_SNAPMODULE)
#define TH32CS_GETALLMODS	0x80000000

HANDLE WINAPI CreateToolhelp32Snapshot(DWORD dwFlags, DWORD th32ProcessID);
BOOL WINAPI CloseToolhelp32Snapshot(HANDLE hSnapshot);

typedef struct tagHEAPLIST32 {
    DWORD  dwSize;
    DWORD  th32ProcessID;
    DWORD  th32HeapID;
    DWORD  dwFlags;
} HEAPLIST32, *PHEAPLIST32, *LPHEAPLIST32;

#define HF32_DEFAULT		1  // process's default heap

BOOL WINAPI Heap32ListFirst(HANDLE hSnapshot, LPHEAPLIST32 lphl);
BOOL WINAPI Heap32ListNext(HANDLE hSnapshot, LPHEAPLIST32 lphl);

typedef struct tagHEAPENTRY32 {
    DWORD  dwSize;
    HANDLE hHandle;
    DWORD  dwAddress;
    DWORD  dwBlockSize;
    DWORD  dwFlags;
    DWORD  dwLockCount;
    DWORD  dwResvd;
    DWORD  th32ProcessID;
    DWORD  th32HeapID;
} HEAPENTRY32, *PHEAPENTRY32, *LPHEAPENTRY32;

#define LF32_FIXED    0x00000001
#define LF32_FREE     0x00000002
#define LF32_MOVEABLE 0x00000004
#define LF32_DECOMMIT 0x00000008
#define LF32_BIGBLOCK 0x00000010

BOOL WINAPI Heap32First(HANDLE hSnapshot, LPHEAPENTRY32 lphe, DWORD th32ProcessID, DWORD th32HeapID);
BOOL WINAPI Heap32Next(HANDLE hSnapshot, LPHEAPENTRY32 lphe);

BOOL WINAPI Toolhelp32ReadProcessMemory(DWORD th32ProcessID, LPCVOID lpBaseAddress, LPVOID lpBuffer,
	DWORD cbRead, LPDWORD lpNumberOfBytesRead);

typedef struct tagPROCESSENTRY32 {
    DWORD   dwSize;
    DWORD   cntUsage;
    DWORD   th32ProcessID;
    DWORD   th32DefaultHeapID;
    DWORD   th32ModuleID;
    DWORD   cntThreads;
    DWORD   th32ParentProcessID;
    LONG    pcPriClassBase;
    DWORD   dwFlags;
    TCHAR   szExeFile[MAX_PATH];
    DWORD	th32MemoryBase;
    DWORD	th32AccessKey;
} PROCESSENTRY32, *PPROCESSENTRY32, *LPPROCESSENTRY32;

BOOL WINAPI Process32First(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);
BOOL WINAPI Process32Next(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);

typedef struct tagTHREADENTRY32 {
    DWORD   dwSize;
    DWORD   cntUsage;
    DWORD   th32ThreadID;
    DWORD   th32OwnerProcessID;
    LONG    tpBasePri;
    LONG    tpDeltaPri;
    DWORD   dwFlags;
    DWORD	th32AccessKey;
    DWORD	th32CurrentProcessID;
} THREADENTRY32, *PTHREADENTRY32, *LPTHREADENTRY32;

BOOL WINAPI Thread32First(HANDLE hSnapshot, LPTHREADENTRY32 lpte);
BOOL WINAPI Thread32Next(HANDLE hSnapshot, LPTHREADENTRY32 lpte);

typedef struct tagMODULEENTRY32 {
    DWORD   dwSize;
    DWORD   th32ModuleID;
    DWORD   th32ProcessID;
    DWORD   GlblcntUsage;
    DWORD   ProccntUsage;
    BYTE   *modBaseAddr;
    DWORD   modBaseSize;
    HMODULE hModule;
    TCHAR   szModule[MAX_PATH];
    TCHAR   szExePath[MAX_PATH];
    DWORD	dwFlags;
} MODULEENTRY32, *PMODULEENTRY32, *LPMODULEENTRY32;

BOOL WINAPI Module32First(HANDLE hSnapshot, LPMODULEENTRY32 lpme);
BOOL WINAPI Module32Next(HANDLE hSnapshot, LPMODULEENTRY32 lpme);

#ifdef __cplusplus
}
#endif

#endif // __TOOLHELP32_H__

