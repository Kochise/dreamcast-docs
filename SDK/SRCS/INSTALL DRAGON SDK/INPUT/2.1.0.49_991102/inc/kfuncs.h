/*++

Copyright (c) 1995-1998 Microsoft Corporation

Module Name: kfuncs.h

++*/

#ifndef __KFUNCS_H__
#define __KFUNCS_H__

#define NUM_SYS_HANDLES  32

#define SYS_HANDLE_BASE	 64
#define SH_WIN32                0
#define SH_CURTHREAD            1
#define SH_CURPROC              2
// #define SH_KWIN32            3       // OBSOLETE

#define SH_LAST_NOTIFY			16	// Last set notified on Thread/Process Termination
#define SH_GDI                  16
#define SH_WMGR                 17
#define SH_INIT                 18
#define SH_COMM                 19      // Communications not "COM"
#define SH_FILESYS_APIS			20      // File system APIS
#define SH_SHELL                21
#define SH_DEVMGR_APIS			22		// File system device manager
#define SH_TAPI					23
#define SH_PATCHER				24
#define SH_IMM					25
#define SH_WNET					26      // WNet APIs for network redirector

#ifdef WINCEOEM
#include <psyscall.h>    // change to include only defines required by OEMs
#endif

#if defined(ARM)
#define PUserKData ((LPBYTE)0xFFFFC800)
#else
#define PUserKData ((LPBYTE)0x00005800)
#endif
#define SYSHANDLE_OFFSET 0x004

#ifdef WINCEOEM
#include <pkfuncs.h>    // change to include only defines required by OEMs
#ifdef WINCEMACRO
#include <mkfuncs.h>
#endif
#endif

#ifndef EventModify
BOOL WINAPI EventModify(HANDLE hEvent, DWORD func);
#endif

#if defined(MIPS)

#if defined(MIPS16SUPPORT) && !defined(NOMIPS16CODE)
#ifdef __cplusplus
extern "C" {
#endif
  void __emit(const unsigned __int32 a);
#ifdef __cplusplus
}
#endif
#pragma intrinsic (__emit)
extern void DebugBreak();
#pragma intrinsic (DebugBreak)
#else
#pragma warning(disable:4052)
extern void __asm(char[], ...);
_inline void DebugBreak() {
	__asm("break 1");
}
#pragma warning(default:4052)
#endif

#elif defined(PPC)

void __emit(unsigned const __int32);
_inline void DebugBreak() {
	__emit(0x0FE00016);	// "twi 31,0,0x16"
}

#elif defined(x86)

_inline void DebugBreak() {
	__asm int 3
}

#elif defined(SHx)

extern void __asm(const char *, ...);
#define DebugBreak() __asm("trapa #1")

#elif defined(ARM)

#if defined(THUMB)
void __emit(const __uint16);
#define DebugBreak() __emit(0xDEFE)
#else
void __emit(unsigned const __int32);
#define DebugBreak() __emit(0xE6000010)
#endif

#else

extern void DebugBreak();

#endif

#define EVENT_PULSE     1
#define EVENT_RESET     2
#define EVENT_SET       3

/*
	@doc BOTH EXTERNAL
	
	@func BOOL | PulseEvent | Provides a single operation that sets (to signaled) the state
	of the specified event object and then resets it (to nonsignaled) after releasing the
	appropriate number of waiting threads.
    @parm HANDLE | hEvent | handle of event object

	@comm Follows the Win32 reference description with the following exception:
*/
_inline BOOL PulseEvent(HANDLE h) {
	return EventModify(h,EVENT_PULSE);
}

/*
	@doc BOTH EXTERNAL
	
	@func BOOL | ResetEvent | Sets the state of the specified event object to nonsignaled.
    @parm HANDLE | hEvent | handle of event object

	@comm Follows the Win32 reference description with the following exception:
*/
_inline BOOL ResetEvent(HANDLE h) {
	return EventModify(h,EVENT_RESET);
}

/*
	@doc BOTH EXTERNAL
	
	@func BOOL | SetEvent | Sets the state of the specified event object to signaled.
    @parm HANDLE | hEvent | handle of event object

	@comm Follows the Win32 reference description with the following exception:
*/
_inline BOOL SetEvent(HANDLE h) {
	return EventModify(h,EVENT_SET);
}

/*
	@doc BOTH EXTERNAL
	@func HANDLE | CreateEvent | Creates a named or unnamed event object.
    @parm LPSECURITY_ATTRIBUTES | lpEventAttributes | address of security attributes (<p must be NULL>).
    @parm BOOL | bManualReset | flag for manual-reset event
    @parm BOOL | bInitialState | flag for initial state
    @parm LPTSTR | lpName | address of event-object name (<p must be NULL>)
	@comm Follows the Win32 reference description with these restrictions:
	Only default security attributes are available and existing object names are not supported.
	The <p lpEventAttributes> and <p lpName> parameters must be set to NULL.

*/

/*
	@doc BOTH EXTERNAL
	@func VOID | Sleep | Suspends the execution of the current thread for a specified interval.
    @parm DWORD | cMilliseconds | sleep time in milliseconds
	@comm Follows the Win32 reference description without restrictions or modifications.
*/

/*
	@doc BOTH EXTERNAL
	@func DWORD | WaitForSingleObject | Returns when the specified object is in the
	signaled state or when the time-out interval elapses.
    @parm HANDLE | hObject | <p See restrictions below> Handle of object to wait for
    @parm DWORD | dwTimeout | time-out interval in milliseconds
	@comm Follows the Win32 reference description without restriction
*/

/*
	@doc BOTH EXTERNAL
	@func DWORD | WaitForMultipleObjects | Returns when one of the specified objects is in the
	signaled state or when the time-out interval elapses.
	@parm DWORD | cObjects | number of objects to wait on, must be less than MAXIMUM_WAIT_OBJECTS
    @parm const HANDLE* | lphObjects | array of handles to wait on
    @parm BOOL | fWaitAll | must be FALSE
    @parm DWORD | dwTimeout | time-out interval in milliseconds
	@comm Follows the Win32 reference description with these restrictions:
		bWaitAll must be FALSE
*/

/*
	@doc BOTH EXTERNAL
	@func DWORD | SuspendThread | Suspends the specified thread.
    @parm HANDLE | hThread | handle to the thread
	@comm Follows the Win32 reference description without restrictions or modifications.
*/

/*
	@doc BOTH EXTERNAL
	@func DWORD | ResumeThread | Decrements a thread's suspend count. When the suspend count
			is decremented to zero, the execution of the thread is resumed.
    @parm HANDLE | hThread | identifies thread to restart
	@comm Follows the Win32 reference description without restrictions or modifications.
*/

/*
	@doc BOTH EXTERNAL
	@func BOOL | SetThreadPriority | Sets the priority value for the specified thread.
	This value, together with the priority class of the thread's process, determines
	the thread's base priority level.
	@comm Follows the Win32 reference description without restrictions or modifications.
*/

/*
	@doc BOTH EXTERNAL
	@func int | GetThreadPriority | Returns the priority value for the specified thread.
    @parm HANDLE | hThread | handle to thread
	@comm Follows the Win32 reference description without restrictions or modifications.
*/


/*
	@doc BOTH EXTERNAL
	@func DWORD | GetLastError | Returns the calling thread's last-error code value.
	@comm Follows the Win32 reference description without restrictions or modifications.
*/

/*
	@doc BOTH EXTERNAL
	@func VOID | SetLastError | Sets the last-error code for the calling thread.
    @parm DWORD | fdwError | per-thread error code
	@comm Follows the Win32 reference description without restrictions or modifications.
*/

/*
	@doc BOTH EXTERNAL
	@func BOOL | GetExitCodeThread | Retrieves the termination status of the specified thread.
    @parm HANDLE | hThread | handle to the thread
    @parm LPDWORD |lpdwExitCode | address to receive termination status
	@comm Follows the Win32 reference description without restrictions or modifications.
*/

/*
	@doc BOTH EXTERNAL
	@func HANDLE | GetCurrentThread | Returns a pseudohandle for the current thread.
	@comm Follows the Win32 reference description without restrictions or modifications.
*/

_inline HANDLE GetCurrentThread(void) {
	return ((HANDLE)(SH_CURTHREAD+SYS_HANDLE_BASE));
}

/*
	@doc BOTH EXTERNAL
	@func HANDLE | GetCurrentProcess | Returns a pseudohandle for the current process.
	@comm Follows the Win32 reference description without restrictions or modifications.
*/

_inline HANDLE GetCurrentProcess(void) {
	return ((HANDLE)(SH_CURPROC+SYS_HANDLE_BASE));
}

_inline DWORD GetCurrentThreadId(void) {
	return ((DWORD)(((HANDLE *)(PUserKData+SYSHANDLE_OFFSET))[SH_CURTHREAD]));
}

_inline DWORD GetCurrentProcessId(void) {
	return ((DWORD)(((HANDLE *)(PUserKData+SYSHANDLE_OFFSET))[SH_CURPROC]));
}

#define TLS_FUNCALLOC   0
#define TLS_FUNCFREE    1

#ifndef TlsCall
DWORD WINAPI TlsCall(DWORD p1, DWORD p2);
#endif

/*
	@doc BOTH EXTERNAL
	@func DWORD | TlsAlloc | Allocates a thread local storage (TLS) index. Any thread
		of the process can subsequently use this index to store and retrieve values that
		are local to the thread.
	@comm Follows the Win32 reference description without restrictions or modifications.
*/

_inline DWORD WINAPI TlsAlloc(void) {
	return TlsCall(TLS_FUNCALLOC, 0);
}

/*
	@doc BOTH EXTERNAL
	@func BOOL | TlsFree | Releases a thread local storage (TLS) index, making it available
		for reuse.
    @parm DWORD | dwTlsIndex | TLS index to free
	@comm Follows the Win32 reference description without restrictions or modifications.
*/
_inline BOOL WINAPI TlsFree(DWORD dwTlsIndex) {
	return TlsCall(TLS_FUNCFREE, dwTlsIndex);
}

#define VERIFY_READ_FLAG    0
#define VERIFY_EXECUTE_FLAG 0
#define VERIFY_WRITE_FLAG   1
#define VERIFY_KERNEL_OK    2

/*
	@doc BOTH EXTERNAL
	@func BOOL | IsBadReadPtr | Verifies that the calling process
		has read access to the specified range of memory.
    @parm CONST VOID | *lpvPtr | address of memory block
    @parm UINT | cbBytes | size of block
	@comm Follows the Win32 reference description without restrictions or modifications.
*/

/*
	@doc BOTH EXTERNAL
	@func BOOL | IsBadWritePtr | Verifies that the calling process has write access
		to the specified range of memory.
    @parm LPVOID | lpvPtr | address of memory block
    @parm UINT | cbBytes | size of block
	@comm Follows the Win32 reference description without restrictions or modifications.
*/

/*
	@doc BOTH EXTERNAL
	@func LPVOID | VirtualAlloc | Reserves or commits a region of pages in the virtual
		address space of the calling process. Memory allocated by this function is automatically
		initialized to zero.
    @parm LPVOID | lpvAddress | address of region to reserve or commit
    @parm DWORD | cbSize | size of region
    @parm DWORD | fdwAllocationType | type of allocation
    @parm DWORD | fdwProtect | type of access protection
	@comm Follows the Win32 reference description without restrictions or modifications.
*/

/*
	@doc BOTH EXTERNAL
	@func BOOL | VirtualFree | Releases or decommits (or both) a region of pages
	within the virtual address space of the calling process.
    @parm LPVOID | lpvAddress | address of region of committed pages
    @parm DWORD | cbSize | size of region
    @parm DWORD | fdwFreeType | type of free operation
	@comm Follows the Win32 reference description without restrictions or modifications.
*/

/*
	@doc BOTH EXTERNAL
	@func BOOL | VirtualProtect | Changes the access protection on a region of committed
		pages in the virtual address space of the calling process. This function differs
		from VirtualProtectEx, which changes the access protection of any process.
    @parm LPVOID | lpvAddress | address of region of committed pages
    @parm DWORD | cbSize | size of the region
    @parm DWORD | fdwNewProtect | desired access protection
    @parm PDWORD | pfdwOldProtect | address of variable to get old protection
	@comm Follows the Win32 reference description without restrictions or modifications.
*/

/*
	@doc BOTH EXTERNAL
	@func DWORD | VirtualQuery | Information about a range of pages in the virtual
		address space of the calling process.
    @parm LPCVOID | lpvAddress | address of region
    @parm MEMORY_BASIC_INFORMATION | pmbiBuffer | address of information buffer
    @parm DWORD | cbLength | size of buffer
	@comm Follows the Win32 reference description without restrictions or modifications.
*/

/*
	@doc BOTH EXTERNAL
	@func HINSTANCE | LoadLibrary | Maps the specified executable module into the address
		space of the calling process.
    @parm LPTSTR | lpszLibFile | address of filename of executable module
	@comm Follows the Win32 reference description without restrictions or modifications.
*/

/*
	@doc BOTH EXTERNAL
	
	@func BOOL | FreeLibrary | Decrements the reference count of the loaded dynamic-link
		library (DLL) module
    @parm HMODULE |hLibModule | handle of loaded library module
	@comm Follows the Win32 reference description without restrictions or modifications.
	@devnote Follows the Win32 reference description without restrictions or modifications
*/

/*
	@doc BOTH EXTERNAL
	@func FARPROC | GetProcAddress | Returns the address of the specified exported dynamic-link
		library (DLL) function.
    @parm HMODULE | hModule | handle to DLL module
    @parm LPSTR | lpszProc | name of function
	@comm Follows the Win32 reference description without restrictions or modifications.
*/

/*
	@doc BOTH EXTERNAL
	@func HRSRC | FindResource | Determines the location of a resource with the specified
		type and name in the specified module.
    @parm HMODULE |hModule | resource-module handle
    @parm LPTSTR | lpName | address of resource name
    @parm LPTSTR | lpType | address of resource type
	@comm Follows the Win32 reference description with the exception that we don't support
		the resource id 0 (ie: FindResource(h,0,t) will not work as expected).
*/

/*
	@doc BOTH EXTERNAL
	@func HGLOBAL| LoadResource | Loads the specified resource into global memory.
    @parm HINSTANCE | hModule | resource-module handle
    @parm HRSRC | hResInfo | resource handle
	@comm Follows the Win32 reference description without restrictions or modifications.
*/

/*
	@doc BOTH EXTERNAL
	@func LPVOID| LockResource | Locks a loaded resource
    @parm HGLOBAL | hGlob | Locked resource's handle
	@comm Follows the Win32 reference description without restrictions or modifications.
*/

_inline LPVOID LockResource(HGLOBAL hResData) {
	return ((LPVOID)hResData);
}

/*
	@doc BOTH EXTERNAL
	@func DWORD | GetTickCount | Retrieves the number of milliseconds that have
		elapsed since Windows was started.
	@comm Follows the Win32 reference description without restrictions or modifications.
*/

/*
	@doc BOTH EXTERNAL
	@func VOID | OutputDebugString| Sends a string to the debugger for the current application.
    @parm LPTSTR | lpszOutputString | address of string to be displayed
	@comm Follows the Win32 reference description with these restrictions:
	@comm Supports only the Unicode version of this function.
*/

/*
	@doc BOTH EXTERNAL
	@func VOID | GetSystemInfo | Returns information about the current system.
    @parm LPSYSTEM_INFO | lpSystemInfo | address of system information structure
	@comm Follows the Win32 reference description without restrictions or modifications.
*/

#endif

