/*****************************************************************************
 *
 *  DMDFM.c
 *
 *  Copyright (c) 1996 Microsoft Corporation.  All Rights Reserved.
 *
 *
 *****************************************************************************/

#include <windows.h>
#include "dmdfm.h"

/*****************************************************************************
 *
 *          Macros
 *
 *****************************************************************************/

#define     INTERNAL        NTAPI
#define     EXTERNAL        NTAPI
#define     INLINE          __inline

#define hresLe(le) MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, (USHORT)(le))

/*
 *  Arithmetic on pointers.
 */
#define pvSubPvCb(pv, cb) ((LPVOID)((PBYTE)pv - (cb)))
#define pvAddPvCb(pv, cb) ((LPVOID)((PBYTE)pv + (cb)))
#define cbSubPvPv(p1, p2) ((PBYTE)(p1) - (PBYTE)(p2))

/*
 * limp - logical implication.  True unless the first is nonzero and
 * the second is zero.
 */
#define fLimpFF(f1, f2) (!(f1) || (f2))

/*****************************************************************************
 *
 *  @doc    INTERNAL
 *
 *  @func   DWORD | DetachRegion |
 *
 *          Detach a region of memory from the underlying storage medium.
 *
 *  @parm   LPVOID | lpvAddress |
 *
 *          The base address of the region.
 *
 *  @parm   DWORD | cb |
 *
 *          Number of bytes.
 *
 *****************************************************************************/

HRESULT INTERNAL
DetachRegion(LPVOID lpvAddress, DWORD cb)
{
    HRESULT hres;
    static DWORD dwPageSize;
    LPVOID lpvEnd;                  /* One past last byte we care about */

    /*
     *  Get the system page size if we haven't yet.  Note that not all
     *  architectures use the same page size.
     */
    if (dwPageSize == 0) {
        SYSTEM_INFO si;
        GetSystemInfo(&si);
        dwPageSize = si.dwPageSize;
    }

    /*
     *  Note that VirtualQuery automatically rounds lpvAddress down to
     *  the nearest page, so we don't have to.  and the way we walk memory,
     *  we don't need to round the ending address up either.
     */

    lpvEnd = pvAddPvCb(lpvAddress, cb);

    while (lpvAddress < lpvEnd) {
        MEMORY_BASIC_INFORMATION mbi;
        DWORD cbRc = VirtualQuery(lpvAddress, &mbi, sizeof(mbi));
        if (cbRc == sizeof(mbi)) {
            LPVOID lpvRgnEnd = pvAddPvCb(mbi.BaseAddress, mbi.RegionSize);

            /*
             *  Don't overdo it.
             */
            if (lpvRgnEnd > lpvEnd) {
                lpvRgnEnd = lpvEnd;
            }

            /*
             *  Do it only for committed memory.
             */
            if (mbi.State == MEM_COMMIT) {

                /*
                 *  None of the memory should be guarded or PAGE_NOACCESS.
                 *  If it is, then it means that the app has been playing
                 *  evil virtual memory games and we should not mess with it.
                 */
                if (!(mbi.Protect & PAGE_GUARD) &&
                    mbi.Protect != PAGE_NOACCESS) {

                    BOOL fRestore;  /* Do we need to restore original perms? */
                    DWORD dw;       /* Scratch */

                    /*
                     *  If the page is copy-on-write, then DON'T CHANGE IT
                     *  TO PLAIN READ/WRITE!  Otherwise, we end up screwing
                     *  with the *original* bytes, and oh no that's horrible.
                     *
                     *  What's more, DON'T CHANGE IT BACK TO COPY-ON-WRITE
                     *  when we're done, because we will have written to it
                     *  and thereby changed its protection to plain write.
                     */
                    if (mbi.Protect != PAGE_WRITECOPY &&
                        mbi.Protect != PAGE_EXECUTE_WRITECOPY) {
                        /*
                         *  Note that we use PAGE_EXECUTE_READWRITE.
                         *  Otherwise, we will GPF any threads
                         *  that happen to be inside the page (if this
                         *  is a code page).
                         */
                        if (VirtualProtect(mbi.BaseAddress,
                                           cbSubPvPv(lpvRgnEnd,
                                                     mbi.BaseAddress),
                                           PAGE_EXECUTE_READWRITE, &dw)) {
                            if (dw == mbi.Protect) { /* Still kosher */
                            } else {
                                /*
                                 * Somebody else is messing with the
                                 * page permissions at the same time.
                                 * Try to undo what we did, and then
                                 * GET OUT NOW!  DO NOT PASS GO,
                                 * DO NOT COLLECT $200!
                                 */
                                VirtualProtect(mbi.BaseAddress,
                                               cbSubPvPv(lpvRgnEnd,
                                                         mbi.BaseAddress),
                                               dw, &dw);

                                hres = E_UNEXPECTED;
                                goto done;
                            }
                        } else {
                            hres = hresLe(GetLastError());
                            goto done;
                        }
                        fRestore = TRUE;
                    } else {
                        fRestore = FALSE;
                    }

                    /*
                     *  Touch every page in the region.
                     */
                    for (lpvAddress = mbi.BaseAddress; lpvAddress < lpvRgnEnd;
                         lpvAddress = pvAddPvCb(lpvAddress, dwPageSize)) {
                        volatile DWORD *pdw = lpvAddress;
                        *pdw = *pdw;
                    }

                    /*
                     *  Restore the original permissions.
                     */
                    if (fLimpFF(fRestore,
                                VirtualProtect(mbi.BaseAddress,
                                       cbSubPvPv(lpvRgnEnd, mbi.BaseAddress),
                                       mbi.Protect, &dw))) {
                    } else {
                        /* Ouch!  What could've happened? */
                        hres = hresLe(GetLastError());
                        goto done;
                    }

                }
                lpvAddress = lpvRgnEnd;

            }

        } else {
            hres = E_UNEXPECTED;
            goto done;
        }
    }

done:;
    return hres;
} // DetachRegion()

/*****************************************************************************
 *
 *  @doc    INTERNAL
 *
 *  @func   DWORD | GetSectionType |
 *
 *          Determine the <c DMDFM_*PAGES> flag that applies to this
 *          section.
 *
 *  @parm   const IMAGE_SECTION_HEADER * | pish |
 *
 *          The section in question.
 *
 *  @parm   const IMAGE_NT_HEADERS * | pnth |
 *
 *          The PE header that describes the enclosing file.
 *
 *  @returns
 *
 *          A <c DMDFM_*PAGES> value.
 *
 *****************************************************************************/

DWORD INLINE
GetSectionType(const IMAGE_SECTION_HEADER *pish,
               const IMAGE_NT_HEADERS *pnth)
{
    DWORD flType;

    /*
     *  If section is marked executable, then it's a code
     *  section.
     */
    if (pish->Characteristics & IMAGE_SCN_MEM_EXECUTE) {
        flType = DMDFM_CODEPAGES;
    } else

    /*
     *  If section is the start of the resource table, then
     *  it's a resource section.
     */
    if (pnth->OptionalHeader.DataDirectory[
                IMAGE_DIRECTORY_ENTRY_RESOURCE].VirtualAddress ==
        pish->VirtualAddress) {
        flType = DMDFM_RESPAGES;
    } else

    /*
     *  If section is discardable, then it's a fixup section.
     */
    if (pish->Characteristics & IMAGE_SCN_MEM_DISCARDABLE) {
        flType = DMDFM_OTHERPAGES;
    } else

    /*
     *  If section is writeable, then it's a read/write page.
     *  (Even if it's not readable.)
     */
    if (pish->Characteristics & IMAGE_SCN_MEM_WRITE) {
        flType = DMDFM_RWPAGES;
    } else

    /*
     *  If section is readable, then it's a read-only page.
     *  (We filtered out "write" above.)
     */
    if (pish->Characteristics & IMAGE_SCN_MEM_READ) {
        flType = DMDFM_ROPAGES;
    } else

    /*
     *  Yow, this is a really weird section.  Call it "Other".
     */
    if (1) {
        flType = DMDFM_OTHERPAGES;
    }

    return flType;
}

/*****************************************************************************
 *
 *  @doc    EXTERNAL
 *
 *  @func   HRESULT | DetachFromMedium |
 *
 *          Dissociate a file or portions of it from the underlying
 *          storage medium, such as a floppy disk or CD-ROM.
 *          The file or portions of it will be loaded
 *          into memory (and the swap file as necessary).
 *
 *          Once a section of the file has been detached from the
 *          storage medium, it cannot be re-attached.
 *
 *  @parm   HINSTANCE | hinst |
 *
 *          The instance handle of the module that should be detached
 *          from the underlying storage medium.
 *
 *  @parm   DWORD | dwFlags |
 *
 *          Flags describing the parts of the file which should be
 *          detached and the conditions under which the detaching
 *          should be performed.
 *
 *          The first class of flags describe the conditions
 *          under which the disassociation should be made.  It may be
 *          one or more of the following flags:
 *
 *          <c DMDFM_IFREMOVABLE>: Detach if the storage medium is
 *          removable.  BUGBUG -- distinguish between floppies and
 *          other storage media (jazz, zip?).
 *
 *          <c DMDFM_IFFIXED>:  Detach if the storage medium is
 *          non-removable, such as a hard drive.
 *
 *          <c DMDFM_IFNETWORK>:  Detach if the storage medium is
 *          a network drive.
 *
 *          <c DMDFM_IFCDROM>:  Detach if the storage medium is
 *          a CD-ROM.
 *
 *          <c DMDFM_IFRAMDRIVE>: Detach if the storage medium is
 *          a RAM drive.  (Probably not a good idea.)
 *
 *          <c DMDFM_ALWAYS>: Always detach, regardless of the
 *          storage medium.
 *
 *          The second class of flags describes the portions of the
 *          file that should be detached.  It may be one or more
 *          of the following flags:
 *
 *          <c DMDFM_CODEPAGES>: Detach code pages.
 *
 *          <c DMDFM_ROPAGES>: Detach read-only data pages.  This
 *          does not include resources or fixup tables.
 *
 *          <c DMDFM_RWPAGES>: Detach read-write data pages.
 *
 *          <c DMDFM_RESPAGES>: Detach resource pages.
 *
 *          <c DMDFM_OTHERPAGES>: Detach page types that are not covered
 *          by the other page types.
 *
 *          <c DMDFM_ALLPAGES>: Detach the entire file.
 *
 *          Note that only the original attributes of the pages in the
 *          module are consulted.  For example, if an application has
 *          converted a read-only page to a read-write page, it will
 *          not be converted by <c DMDF_RWPAGES>; you must still use
 *          <c DMDF_ROPAGES> to detach the page.
 *
 *          If a page falls into more than one of the above categories,
 *          its category is selected according to the following rules:
 *
 *  @returns
 *          Returns a COM error code.  The following error codes are
 *          intended to be illustrative and not necessarily comprehensive.
 *
 *          <c DM_OK> = <c S_OK>: The operation completed successfully.
 *
 *          <c DM_NOEFFECT>: The file storage medium did not meet the
 *          criteria, so no action was taken.
 *
 *          <c DMERR_OUTOFMEMORY>:  Insufficient memory to complete the
 *          operation.
 *
 *          <c DMERR_INVALIDARG>: One or more of the parameters was
 *          not valid.
 *
 *****************************************************************************/

STDMETHODIMP
DetachFromMedium(HINSTANCE hinst, DWORD fl)
{
    HRESULT hres;
    TCHAR tszMedium[8];

    /*
     *  Do not mess with DLLs loaded into shared memory.
     *
     *  Three characters (and a trailing null) are enough to build
     *  the root directory.
     */
    if ((int)hinst > 0 && (GetModuleFileName(hinst, tszMedium, 4))) {
        DWORD flType;

        if ((fl & DMDFM_ALWAYS) == DMDFM_ALWAYS) {
            flType = DMDFM_IFNETWORK;   /* Yeah, whatever */
        } else if (tszMedium[0] == TEXT('\\')) {
            flType = DMDFM_IFNETWORK;
        } else {
            tszMedium[3] = TEXT('\0');
            flType = 1 << (GetDriveType(tszMedium) - DRIVE_REMOVABLE);
            flType &= DMDFM_ALWAYS;
        }

        if (fl & flType) {
            const IMAGE_DOS_HEADER *pidh = hinst;
            const IMAGE_NT_HEADERS *pnth = pvAddPvCb(pidh, pidh->e_lfanew);
            UINT iish;

            /*
             *  The module header is considered an "other" page.
             */
            if (fl & DMDFM_OTHERPAGES) {
                hres = DetachRegion(hinst, pnth->OptionalHeader.SizeOfHeaders);
                if (FAILED(hres)) {
                    goto done;
                }
            }

            /*
             *  Now walk through the list of sections.
             */
            for (iish = 0; iish < pnth->FileHeader.NumberOfSections; iish++) {
                const IMAGE_SECTION_HEADER *pish =
                                        IMAGE_FIRST_SECTION(pnth) + iish;


                /*
                 *  If the section type is one we should detach, do it.
                 */
                if (fl & GetSectionType(pish, pnth)) {
                    hres = DetachRegion(pvAddPvCb(hinst, pish->VirtualAddress),
                                        pish->Misc.VirtualSize);
                    if (FAILED(hres)) {
                        goto done;
                    }
                }
            }

        } else {
            hres = DM_NOEFFECT;
        }
    } else {
        hres = E_INVALIDARG;
    }

done:;
    return hres;
}
