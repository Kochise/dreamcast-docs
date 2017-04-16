//=======================================
// PSAPI Working Set Demo - Matt Pietrek 1996
// Microsoft Systems Journal, November 1996
// FILE: PSAPIHELPER.CPP
//=======================================
#include <windows.h>
#pragma hdrstop
#include "psapi.h"
#include "PSAPIhelper.h"

BOOL GetModuleNameAndSectionInfo(
        HANDLE  hProcess,
        PVOID   p,
        PSTR    pszModuleName,
        DWORD   cbModuleName,
        PSTR    pszSectionName,
        DWORD   cbSectionName,
        PDWORD  puSectionNum )
{

    MEMORY_BASIC_INFORMATION mbi;

    if ( !VirtualQueryEx( hProcess, p, &mbi, sizeof(mbi)) )
        return FALSE;

    PVOID hModule = mbi.AllocationBase;

    DWORD cbRead;       
    IMAGE_DOS_HEADER dosHdr;

    if ( !ReadProcessMemory(hProcess, hModule,
                            &dosHdr, sizeof(dosHdr), &cbRead) )
        return FALSE;

    if ( IMAGE_DOS_SIGNATURE != dosHdr.e_magic )
        return FALSE;

    if ( dosHdr.e_lfarlc < 0x40 )
        return FALSE;

    DWORD peHdrOffs = (DWORD)hModule + dosHdr.e_lfanew;

    IMAGE_NT_HEADERS ntHdr;

    if ( !ReadProcessMemory(hProcess, (PVOID)peHdrOffs,
                            &ntHdr, sizeof(ntHdr), &cbRead ) )
        return FALSE;

    if ( IMAGE_NT_SIGNATURE != ntHdr.Signature )
        return FALSE;

    PVOID sectionHdrOffs = (PVOID)(
                    peHdrOffs
                    + FIELD_OFFSET( IMAGE_NT_HEADERS, OptionalHeader )
                    + ntHdr.FileHeader.SizeOfOptionalHeader );

    #define MAX_SECTIONS 128

    IMAGE_SECTION_HEADER sections[ MAX_SECTIONS ];
    PIMAGE_SECTION_HEADER pSection;

    DWORD cSections = min( ntHdr.FileHeader.NumberOfSections, MAX_SECTIONS );

    if ( !ReadProcessMemory(hProcess,
                            sectionHdrOffs,
                            &sections,
                            cSections * IMAGE_SIZEOF_SECTION_HEADER,
                            &cbRead) )
        return FALSE;

    // Get the module name now, since we can't assume that we'll find
    // a section name/index later.  For instance, the RVA might be somewhere
    // in the NT header page, rather than in a code/data section.
    GetModuleBaseName(  hProcess, hModule,
                        pszModuleName, cbModuleName );
    
    pszSectionName[0] = 0;  // Set to void values in case we bail out of the
    *puSectionNum = 0;      // loop below without finding a section.

    DWORD rva = (DWORD)p - (DWORD)hModule;

    pSection = (PIMAGE_SECTION_HEADER)&sections;

    for ( DWORD i = 0; i < cSections; i++, pSection++ )
    {
        DWORD endRVA = pSection->VirtualAddress
                + max(pSection->SizeOfRawData, pSection->Misc.VirtualSize);

        if ( pSection->VirtualAddress > rva )   // Is this section's RVA
            break;                              // past the RVA we're after?

        if ( (rva >= pSection->VirtualAddress) && (rva <= endRVA ) )
        {
            lstrcpyn( pszSectionName, (PSTR)pSection->Name,
                       min(IMAGE_SIZEOF_SHORT_NAME+1, cbSectionName) );
            *puSectionNum = i+1;
            return TRUE;
        }
    }

    return TRUE;
}

