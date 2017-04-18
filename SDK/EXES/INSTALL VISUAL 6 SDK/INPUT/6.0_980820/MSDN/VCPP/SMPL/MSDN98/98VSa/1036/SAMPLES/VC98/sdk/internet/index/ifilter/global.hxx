//+-------------------------------------------------------------------------
//
//  Copyright 1992 - 1997 Microsoft Corporation
//
//  File:       global.hxx
//
//  Contents:   Global defines
//
//--------------------------------------------------------------------------

#if !defined( __GLOBAL_HXX__ )
#define __GLOBAL_HXX__

#include <debug.hxx>
#include <except.hxx>

DECLARE_DEBUG(html);

#if DBG == 1

#define htmlDebugOut( x ) htmlInlineDebugOut x

#else  // DBG == 0

#define htmlDebugOut( x )

#endif // DBG

//
// Memory allocator that calls the default allocator and then throws on
// allocation failure
//

enum HtmlNew {
    onDefault = 0x1e,   // Just to force a different operator new signature
};

#define newk(Tag, pCounter)     new(onDefault)

inline void * _CRTAPI1 operator new( size_t size, enum HtmlNew on )
{
    void *pMemory = ::new char[size];

    if ( pMemory == 0 )
        throw( CException( E_OUTOFMEMORY ) );

    return pMemory;
}

#endif   // __GLOBAL_HXX__

