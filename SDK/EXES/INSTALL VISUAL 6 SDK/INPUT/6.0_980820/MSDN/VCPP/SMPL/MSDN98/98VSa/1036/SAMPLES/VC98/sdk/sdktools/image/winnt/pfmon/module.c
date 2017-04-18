/*++

Copyright (c) 1995-1997  Microsoft Corporation

Module Name:

    module.c

Abstract:

    This module maintains the module (symbol) information for the pfmon application

Author:

    Mark Lucovsky (markl) 27-Jan-1995

Revision History:

--*/

#include "pfmonp.h"

BOOL
AddModule(
    LPDEBUG_EVENT DebugEvent
    )
{
    PMODULE_INFO Module;
    LPVOID BaseAddress;
    HANDLE Handle;

    if ( DebugEvent->dwDebugEventCode == CREATE_PROCESS_DEBUG_EVENT) {
        Handle = DebugEvent->u.CreateProcessInfo.hFile;
        BaseAddress = DebugEvent->u.CreateProcessInfo.lpBaseOfImage;
        }
    else {
        Handle = DebugEvent->u.LoadDll.hFile;
        BaseAddress = DebugEvent->u.LoadDll.lpBaseOfDll;
        }

    Module = FindModuleContainingAddress(BaseAddress);
    if ( Module ) {
        DeleteModule(Module);
        }

    Module = LocalAlloc(LMEM_ZEROINIT, sizeof( *Module ) );

    if (Module == NULL) {
        return FALSE;
        }

    Module->Handle = Handle;
    Module->BaseAddress = BaseAddress;

    if ( !Module->Handle ) {
        LocalFree(Module);
        return FALSE;
        }

    Module->DebugInfo = MapDebugInformation(
                            Module->Handle,
                            NULL,
                            SymbolSearchPath,
                            (DWORD)Module->BaseAddress
                            );

    if ( !Module->DebugInfo ) {
        LocalFree(Module);
        return FALSE;
        }
    Module->VirtualSize = Module->DebugInfo->SizeOfImage;

    SymLoadModule(hProcess,Handle,NULL,NULL,(DWORD)BaseAddress,0);

    InsertTailList( &ModuleListHead, &Module->Entry );

    return TRUE;
}

BOOL
DeleteModule(
    PMODULE_INFO Module
    )
{
    CHAR Line[256];

    if ( Module ) {
        RemoveEntryList(&Module->Entry);

        sprintf(Line,"%16s Caused %6d faults had %6d Soft %6d Hard faulted VA's\n",
            Module->DebugInfo->ImageFileName,
            Module->NumberCausedFaults,
            Module->NumberFaultedSoftVas,
            Module->NumberFaultedHardVas
            );
        if ( !fLogOnly ) {
            fprintf(stdout,"%s",Line);
            }
        if ( LogFile ) {
            fprintf(LogFile,"%s",Line);
            }

        UnmapDebugInformation(Module->DebugInfo);
        LocalFree(Module);
        }

    return TRUE;
}


PMODULE_INFO
FindModuleContainingAddress(
    LPVOID Address
    )
{
    PLIST_ENTRY Next;
    PMODULE_INFO Module;

    Next = ModuleListHead.Flink;
    while ( Next != &ModuleListHead ) {
        Module = CONTAINING_RECORD(Next,MODULE_INFO,Entry);
        if ( Address >= Module->BaseAddress &&
             Address < (LPVOID)((PUCHAR)(Module->BaseAddress)+Module->VirtualSize) ) {
            return Module;
            }
        Next = Next->Flink;
        }
    return NULL;
}

VOID
SetSymbolSearchPath( )
{
    LPSTR lpSymPathEnv, lpAltSymPathEnv, lpSystemRootEnv;
    ULONG cbSymPath;
    DWORD dw;

    cbSymPath = 18;
    if (lpSymPathEnv = getenv("_NT_SYMBOL_PATH")) {
        cbSymPath += strlen(lpSymPathEnv) + 1;
    }
    if (lpAltSymPathEnv = getenv("_NT_ALT_SYMBOL_PATH")) {
        cbSymPath += strlen(lpAltSymPathEnv) + 1;
    }

    if (lpSystemRootEnv = getenv("SystemRoot")) {
        cbSymPath += strlen(lpSystemRootEnv) + 1;
    }

    SymbolSearchPath = LocalAlloc(LMEM_ZEROINIT,cbSymPath);

    if (lpAltSymPathEnv) {
        dw = GetFileAttributes(lpAltSymPathEnv);
        if ( dw != 0xffffffff && dw & FILE_ATTRIBUTE_DIRECTORY ) {
            strcat(SymbolSearchPath,lpAltSymPathEnv);
            strcat(SymbolSearchPath,";");
            }
    }
    if (lpSymPathEnv) {
        dw = GetFileAttributes(lpSymPathEnv);
        if ( dw != 0xffffffff && dw & FILE_ATTRIBUTE_DIRECTORY ) {
            strcat(SymbolSearchPath,lpSymPathEnv);
            strcat(SymbolSearchPath,";");
            }
    }

    if (lpSystemRootEnv) {
        dw = GetFileAttributes(lpSystemRootEnv);
        if ( dw != 0xffffffff && dw & FILE_ATTRIBUTE_DIRECTORY ) {
            strcat(SymbolSearchPath,lpSystemRootEnv);
            strcat(SymbolSearchPath,";");
            }
    }

    strcat(SymbolSearchPath,".;");

}
