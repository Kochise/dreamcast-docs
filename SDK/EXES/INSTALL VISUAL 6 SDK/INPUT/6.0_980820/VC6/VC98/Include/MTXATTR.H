#ifndef _MTXATTR_H_
#define _MTXATTR_H_

// -----------------------------------------------------------------------
// mtxattr.h  -- Microsoft Transaction Server Custom Properties			
//																		
// This file is the IDL include for Microsoft Transaction Server		
// custom typelib properties.											
//																		
// Microsoft Transaction Server 2.0										
// Copyright (c) 1996-1997 Microsoft Corporation.  All Rights Reserved.	
// -----------------------------------------------------------------------  

//======================================================================================
// Component attributes
//======================================================================================
#define		TLBATTR_TRANS_REQUIRED	17093CC5-9BD2-11cf-AA4F-304BF89C0001
#define		TLBATTR_TRANS_NOTSUPP	17093CC6-9BD2-11cf-AA4F-304BF89C0001
#define		TLBATTR_TRANS_REQNEW	17093CC7-9BD2-11cf-AA4F-304BF89C0001
#define		TLBATTR_TRANS_SUPPORTED	17093CC8-9BD2-11cf-AA4F-304BF89C0001

//======================================================================================
// Component attribute MACROS
//======================================================================================

#define TRANSACTION_REQUIRED		custom(TLBATTR_TRANS_REQUIRED,0)
#define TRANSACTION_SUPPORTED		custom(TLBATTR_TRANS_SUPPORTED,0)
#define TRANSACTION_NOT_SUPPORTED	custom(TLBATTR_TRANS_NOTSUPP,0)
#define TRANSACTION_REQUIRES_NEW	custom(TLBATTR_TRANS_REQNEW,0)


#endif _MTXATTR_H_
