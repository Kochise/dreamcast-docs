#if defined(_X86_)
#define STACKPTR(Context)  (Context.Esp)
#endif

#if defined(_MIPS_)
#define STACKPTR(Context)  (Context.IntSp)
#endif

#if defined(_ALPHA_)
#define STACKPTR(Context)  (Context.IntSp)
#endif

#if !defined(STACKPTR)
#error Module contains CPU-specific code; modify and re-compile.
#endif

typedef struct
{ DWORD (WINAPI *fnGetModuleFileName)(HMODULE, LPTSTR,DWORD);
  HINSTANCE dwInstance;
  char chPathName[_MAX_PATH];
} THREADFNSTRUCT;


PVOID AllocProcessMemory (HANDLE hProcess, DWORD dwNumBytes);
BOOL FreeProcessMemory (HANDLE hProcess, PVOID pvMem);

