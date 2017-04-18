/*++

Copyright (c) 1996 Intel Corp

Module Name:

    nullpdef.h

Abstract:

    This  file  provides  common  externally  visible  definitions for the null
    provider.

Author:

    Paul Drews (Intel) 01-30-1996

Notes:

    $Revision:   1.1  $

    $Modtime:   05 Apr 1996 12:17:12  $
    
Revision History:

    most-recent-revision-date email-name
        description

    01-30-1996 Paul Drews
        Created
--*/

#ifndef _NULLPDEF_
#define _NULLPDEF_


// Define  the  artificial  "address family" that identifies the null provider.
// This  is  technically  illegal,  since one is supposed to get address family
// identifiers allocated through a clearing house.  But for the purpose of this
// simple  example  it  will  suffice to define one that is some small distance
// past the currently known set.

#define AF_SPECIAL_NULL  (AF_MAX + 5)

#endif  // _NULLPDEF_
