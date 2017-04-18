////////////////////////////////////////////////////////////////////
// PIDL.h: interface for the CPIDL class.
//

#ifndef __PIDL_H
#define __PIDL_H

#include <shlobj.h>

class CPIDL
{
public:
    LPITEMIDLIST  m_pidl;

// == Construction/Destruction == //

    // Empty object
    CPIDL() : m_pidl(NULL) {}

    // Copy constructor
    CPIDL(const CPIDL& cpidl) : m_pidl(NULL) { Set(cpidl); }

    // From path (szPath relevant to the folder psf) - see Set()
    CPIDL(LPCSTR szPath, LPSHELLFOLDER psf = m_sfDesktop) : 
        m_pidl(NULL) { Set(szPath, psf); }

    // Construct from an ITEMIDLIST pointer - does NOT copy the
    // ITEMIDLIST data (use MakeCopyOf() for that)
    CPIDL(LPITEMIDLIST pidl) : m_pidl(pidl) {}

    // destructor
    virtual ~CPIDL();


// == Assignment == //

    // All of the assignment operators *free* the current list.
    // If you we to set a new item list without freeing the old one,
    // you have to set m_pidl to NULL before assigning.

    // Make a copy of cpidl's list data
    HRESULT Set(const CPIDL& cpidl);

    // Set by path: szPath relative to the folder psf.  Uses
    // the desktop by default, so you can use regular path strings
    // like "c:\windows"
    HRESULT Set(LPCSTR szPath, LPSHELLFOLDER psf = m_sfDesktop);

    // Points the CPIDL to an existing item list: does *not* 
    // copy the actual data - just the pointer.  To make a copy of 
    // the data, use MakeCopyOf()
    HRESULT Set(LPITEMIDLIST pidl);

// == Special Assignments == //

    // Takes a pointer to an existing item list and makes a new
    // copy of the list data.
    HRESULT MakeCopyOf(LPITEMIDLIST pidl);

    // An absolute PIDL is a PIDL with the desktop as a root.  Use
    // this function to create an absolute PIDL of any other pidl
    // rooted at the folder pointed by psf.
    HRESULT MakeAbsPIDLOf(LPSHELLFOLDER psf, LPITEMIDLIST pidl);


// == Item Access == //

    // Returns a pointer to the first item in the list
    LPSHITEMID GetFirstItemID() const 
        { return (LPSHITEMID)m_pidl; }

    // Points to the next item in the list
    void GetNextItemID(LPSHITEMID& pid) const 
        { (LPBYTE &)pid += pid->cb; }


// == General Operations == //

    // Frees the memory used by the item id list
    void Free();

    // Counts the amount memory needed to store the id list
    UINT GetSize() const;

    // A pidl points to a name-space object such as a file or 
    // folder, such as "c:\windows\system\kernel32.dll"
    // This function will split the pidl into two pidls:
    // 1. the pidl of the object's direct parent
    // 2. the pidl of the object, relative to it's parent
    // Example: for the above file
    // parent - is set to the pidl of "c:\windows\system"
    // obj    - is set to the pidl of "kernel" (relative to parent)
    void Split(CPIDL& parent, CPIDL& obj) const;

    // Concatenation using the + operator
    CPIDL operator + (CPIDL& pidl) const;

    // Concatenation - faster version using references
    static void Concat(const CPIDL &a, const CPIDL& b, 
        CPIDL& result);  // (result = a+b)


// == Shell Name-space Access Helper Functions == //

    // IShellFolder->GetUIObjectOf works only for 1 item pidls (i.e.
    // objects that are direct descendants of the folder).
    // This following function allows you to retrieve a UI object of
    // any pidl rooted at the folder psf.
    // Example:
    // psf -> IShellFolder of "c:\windows",
    // pidl -> pidl of "system\kernel32.dll" (relative to psf)
    // 1) Will *not* work psf->GetUIObjectOf(pidl, ... )
    // 2) Will work: pidl.GetUIObjectOf(..., psf)
    HRESULT GetUIObjectOf(REFIID riid, LPVOID *ppvOut, 
        HWND hWnd = NULL, LPSHELLFOLDER psf = m_sfDesktop);

    // Helper function: Given an STRRET structure, will ensure that
    // the returned string is moved to the cStr field.  
    // For use after functions like IShellFolder->GetDisplayNameOf()
    // Note: memory used the OLE strings is automatically freed.
    void ExtractCStr(STRRET& strRet) const;


// == Conversion Operators == //

    operator LPITEMIDLIST&  () { return m_pidl; }
    operator LPITEMIDLIST * () { return &m_pidl; }
    operator LPCITEMIDLIST  () const { return m_pidl; }
    operator LPCITEMIDLIST* () const 
        { return (LPCITEMIDLIST *)&m_pidl; }

protected:

    static LPSHELLFOLDER    m_sfDesktop;    // desktop object
    static LPMALLOC         m_pAllocator;   // system allocator

    // allocate memory for the pidl using the system allocator
    void AllocMem(int iAllocSize);

    // initializer (used for automatic initialization)
    static struct pidl_initializer {
        pidl_initializer();
        ~pidl_initializer();
    } m_initializer;
    friend struct pidl_initializer;
};

#endif  // __PIDL_H
