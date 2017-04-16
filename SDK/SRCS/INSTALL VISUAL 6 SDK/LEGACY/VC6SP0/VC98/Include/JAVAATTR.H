#ifndef _JAVAATTR_H_
#define _JAVAATTR_H_

// -----------------------------------------------------------------------
// JavaAttr.h  -- TypeLib Custom Properties for Java
//
// Copyright (c) 1996-1997 Microsoft Corporation.  All Rights Reserved.	
// -----------------------------------------------------------------------  
//
// Usage:
//  In IDL or ODL source,
//  #include <JavaAttr.h>
//
//  Within the attributes section of a coclass, write
//      JAVACLASS("class name")    and/or
//      PROGID("progid name")

//======================================================================================
// Attribute GUIDs
//======================================================================================
#define		TLBATTR_JAVACLASS	06f90aa0-3f00-11d0-987d-00a0c90aebd9
#define		TLBATTR_PROGID		06f90aa1-3f00-11d0-987d-00a0c90aebd9

//======================================================================================
// Attribute MACROs
//======================================================================================

#define JAVACLASS(str)			custom(TLBATTR_JAVACLASS,str)
#define PROGID(str)			custom(TLBATTR_PROGID,str)


#endif _JAVAATTR_H_
