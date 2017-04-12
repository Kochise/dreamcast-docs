// ------------------------------------------------------------------------
// Copyright (c) 1998 by Microsoft Corporation, All Rights Reserved
// 
// This software is provided as is without warranty of any kind.  The entire
// risk as to the results and performance of this software is assumed by the user.
// Microsoft disclaims all warranties, either express or implied, including but
// not limited, the implied warranties of merchantability, fitness for a
// particular purpose, title and noninfringement, with respect to this software.
// ------------------------------------------------------------------------
//*****************************************************************************
// REPERR.H
//
// This file contains the errors that any Repository method may return.  Each
// error has rich error text that can be retrieved using the Repository error
// queue.  See the documentation for more details.
//
// Copyright (c) 1995-1998 by Microsoft Corporation, All Rights Reserved
//*****************************************************************************
#ifndef __REPERR_H__
#define __REPERR_H__

#ifndef EMAKEHR
#define SMAKEHR(val)			MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_ITF, val)
#define EMAKEHR(val)			MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, val)
#endif

//**** Generic errors.
#define EREP_BADPARAMS			EMAKEHR(0x1000)		// One or more parameters were invalid.
#define EREP_BADNAME			EMAKEHR(0x1001)		// The name ""%s"" has a syntax error, is a reserved word or is too long.
#define EREP_BADDRIVER			EMAKEHR(0x1002)		// The ODBC driver (version %s) installed on this computer is too old, and is incompatible with Microsoft Repository.
#define EREP_BADERROR			EMAKEHR(0x1003)		// Internal error (%s: %d).
#define EREP_BUFFER_OVERFLOW	EMAKEHR(0x1004)		// An error occurred while building an SQL statement. Reduce the number of changed properties or repository objects in the operation (%s: %d).

//**** ODBC errors 
#define EREP_NOROWSFOUND		EMAKEHR(0x1011)		// No data was found for the statement.
#define EREP_ODBC_CERROR		EMAKEHR(0x1012)		// Generic ODBC error.
#define EREP_ODBC_MDBNOTFOUND	EMAKEHR(0x1013)		// The database '%s' was not found.
#define EREP_NEED_DATA			EMAKEHR(0x1014)		// The statement needs data at run-time.
#define EREP_ODBC_UNKNOWNDRIVER	EMAKEHR(0x1015)		// Unknown driver type.
#define EREP_ODBC_CREATEFAILED	EMAKEHR(0x1016)		// An error occurred while creating %s.
#define EREP_ODBC_WARNINGS		SMAKEHR(0x1017)		// Warnings were issued by ODBC driver.  Check the
													//	error queue for the error text.
#define EREP_STILL_EXECUTING	EMAKEHR(0x1018)		// The statement is still executing. 
#define EREP_ODBC_NOTCAPABLE	EMAKEHR(0x1019)		// The odbc driver is not capable of doing the operation. 

//**** Database errors
#define	EREP_DB_EXISTS			EMAKEHR(0x1030)		// The database %s already exists.
#define EREP_DB_NOTCONNECTED	EMAKEHR(0x1031)		// Must be connected before doing this operation.
#define EREP_DB_ALREADYCONNECTED EMAKEHR(0x1032)	// Database already connected.
#define EREP_DB_DBMSONETHREAD	EMAKEHR(0x1033)		// The underlying database is single threaded.  Only thread 0x%08x can access this object.
#define EREP_DB_CORRUPT			EMAKEHR(0x1034)		// The database has consistancy errors.
#define EREP_DB_NOSCHEMA		EMAKEHR(0x1035)		// The repository schema is not installed.
#define EREP_DB_DBMSOLD			EMAKEHR(0x1036)		// DBMS is too old for the Repository.
#define EREP_DB_READONLY		EMAKEHR(0x1037)		// DBMS is read only and cannot be changed.
#define EREP_DB_INCOMPATIBLEVERSION	EMAKEHR(0x1038)	// Incompatible repository database version.

//**** Transaction errors
#define EREP_TXN_NOTXNACTIVE	EMAKEHR(0x1041)		// Cannot Commit/Abort when no transaction active.
#define EREP_TXN_AUTOABORT		EMAKEHR(0x1042)		// User started transaction wasn't committed or
													//   rolled back before final shutdown.
#define EREP_TXN_TOOMANY		EMAKEHR(0x1043)		// Too many transactions running.
#define EREP_TXN_TIMEOUT		EMAKEHR(0x1044)		// Operation timed out.
#define EREP_TXN_NODATA			EMAKEHR(0x1045)		// There is no data for the option.
#define EREP_TXN_NOSETINTXN		EMAKEHR(0x1046)		// Can't set options while in txn.
#define EREP_TXN_OBJABORTED		EMAKEHR(0x1047)		// The cached copy of an object is invalid due to a failed transaction or a deletion (IntID: %s). To update your copy, release and reload the object.
#define EREP_TXN_COLABORTED		EMAKEHR(0x1048)		// Collection was valid but has been aborted or deleted.

//**** Repository level errors.
#define EREP_REPOS_CACHEFULL	EMAKEHR(0x1070)		// The cache is full.
#define EREP_REPOS_NONEXTDISPID	EMAKEHR(0x1071)		// No available dispid value left.

//**** Relationship errors.
#define EREP_RELSHIP_EXISTS		EMAKEHR(0x1100)		// The relationship already exists.
#define EREP_RELSHIP_INVALID_PAIR EMAKEHR(0x1101)	// the relship doesn't have a valid role pair
#define EREP_RELSHIP_NOTFOUND	EMAKEHR(0x1102)		// Relship wasn't found.
													//  with an existing one.  Dupe name for example.
#define EREP_RELSHIP_ORGONLY	EMAKEHR(0x1105)		// Cannot update a sequenced relationship collection
													//  from the target.
#define EREP_RELSHIP_OUTOFDATE	EMAKEHR(0x1106)		// The collection is out of date compared to the DBMS.
#define EREP_RELSHIP_INVALIDFLAGS EMAKEHR(0x1107)	// The combination of role flags is invalid.
#define EREP_RELSHIP_NAMEINVALID EMAKEHR(0x1108)	// The relationship name ""%s"" is invalid for the collection.  A name is required for a naming collection, but is not allowed on a non-naming collection.
#define EREP_RELSHIP_DUPENAME	EMAKEHR(0x1109)		// The relationship name ""%s"" is already used in the collection, and the collection requires all names to be unique.
#define EREP_RELSHIP_NONNAMINGCOL EMAKEHR(0x1110)	// Cannot perform this operation on a non-naming collection.

//**** Class Type errors
#define EREP_TYPE_TABLEMISMATCH	EMAKEHR(0x1120)		// Table exists, but no IntID field.
#define EREP_TYPE_COLMISMATCH	EMAKEHR(0x1121)		// Class specific column type alter mismatch.
#define EREP_TYPE_NOTNULLABLE	EMAKEHR(0x1122)		// The column is not nullable.   
#define EREP_TYPE_MULTIDEFIFACES EMAKEHR(0x1123)	// More than one default interface on a class.
#define EREP_TYPE_INVERTEDNOTALLOWED EMAKEHR(0x1124)// Inverted properties not allowed on this iface.
#define EREP_TYPE_INVALIDSCALE	EMAKEHR(0x1125)		// Invalid SQL scale.
#define EREP_TYPE_BADTABLENAME	EMAKEHR(0x1126)		// The specified table name ""%s"" is an invalid table name.

//**** Lock errors
#define EREP_LOCK_TIMEOUT		EMAKEHR(0x1200)		// Lock timed out.

//**** Query errors
#define EREP_QRY_BADCOLUMNS		EMAKEHR(0x1250)		// Ad-hoc query missing IntID column, has too many columns,
													//   or is otherwise unsuitable for execution.

//**** Object and version errors
#define EREP_OBJ_NOTINITIALIZED	EMAKEHR(0x1300)		// Object not initialized.
#define EREP_OBJ_NOTFOUND		EMAKEHR(0x1301)		// Object not found.
#define EREP_OBJ_NONAMINGRELSHIP EMAKEHR(0x1302)	// No naming relationships.
#define EREP_OBJ_EXISTS			EMAKEHR(0x1303)		// Object already exists.
#define EREP_VERSION_NOTFOUND	EMAKEHR(0x1304)		// Version not found

//**** Property errors.
#define EREP_PROP_MISMATCH		EMAKEHR(0x1400)		// Data type mismatch, for example setting annotational 
													//  props with other than string data type.
#define EREP_PROP_SETINVALID	EMAKEHR(0x1401)		// Cannot set collections.
#define SREP_PROP_TRUNCATION	SMAKEHR(0x1402)		// Property column is not big enough to hold the data.
#define EREP_PROP_CANTSETREPTIM	EMAKEHR(0x1403)		// Can't set property on repository TIM objects.
#define EREP_PROP_READONLY		EMAKEHR(0x1404)		// Property is read only.
#define EREP_PROP_NOTEXISTS		EMAKEHR(0x1405)		// Property does not exist.

//**** TIM errors.
#define EREP_TIM_INVALIDFLAGS   EMAKEHR(0x1500)		// Invalid Combination of Collection Flags.
#define	EREP_TIM_FLAGSDEST		EMAKEHR(0x1501)		// Collection Flags cannot be set of Destination Collection.
#define EREP_TIM_RELTYPEINVALID EMAKEHR(0x1502)	    // The type of a Relationship Definition object for a collection is wrong.
#define EREP_TIM_CTYPEINVALID	EMAKEHR(0x1503)		// Invalid Ctype chosen for property.
#define EREP_TIM_TOOMANYCOLS	EMAKEHR(0x1504)		// Too many Collections per RelationshipDef Object (One origin (Dest.) per Relship).
#define EREP_TIM_SQLTYPEINVALID	EMAKEHR(0x1505)		// Invalid SQL type chosen for property.

// +++++++++++++++++++++++   V2  Errors  +++++++++++++++++++++++++++++++++++++++++++++++++++
//**** Version Management errors.
#define EREP_VM_CANTSETFROZEN	EMAKEHR(0x1600)		// Can't set a property on a frozen version.
#define EREP_VM_MERGETOFROZEN	EMAKEHR(0x1601)		// Can't merge into a frozen version.
#define EREP_VM_MERGEFROMUNFROZEN EMAKEHR(0x1602)	// Can't merge into with an unfrozen secondary version.
#define EREP_VM_UNFROZENVERSION	EMAKEHR(0x1603)
#define EREP_VM_FROZENVERSION	EMAKEHR(0x1604)		// The operation can't be performed on a frozen version.
#define EREP_VM_CHECKEDOUTVERSION	EMAKEHR(0x1605)	// The operation can't be performed on a checked out version.
#define EREP_VM_DUPBRANCHID		EMAKEHR(0x1606)		// A duplicate branch ID was generated for this object.
#define EREP_VM_SUCCESSOREXISTS	EMAKEHR(0x1607)		// A successor of the version exists and hence cannot be deleted.
//****  Relship Version errors (V2)
#define EREP_REL_ORGFROZEN		EMAKEHR(0x1700)		// The origin version is frozen so this operation is invalid.
#define EREP_REL_ORGCLONE		EMAKEHR(0x1701)		// The relship can be cloned only by a version of the origin obj.
#define EREP_REL_NONSEQONLY		EMAKEHR(0x1702)		// This operation cannot be performed on a sequenced relship.
#define EREP_REL_ORGPIN			EMAKEHR(0x1703)		// Can't Pin/UnPin an origin Version.
#define EREP_REL_NOTPINNED		EMAKEHR(0x1704)		// The user is attempting to un-pin an non-pinned relationship.

//**** Workspace errors.
#define EREP_WKS_ITEMEXISTS		EMAKEHR(0x1800)		// The item already exists in the workspace.
#define EREP_WKS_ITEMNOTEXISTS	EMAKEHR(0x1801)		// The item doesn't exist in the workspace.
#define EREP_NOTWORKSPACEITEM	EMAKEHR(0x1802)		// This is not a workspace item.
#define	EREP_ITEMNOTCHECKEDOUT	EMAKEHR(0x1803)		// Operation performed on an un-checked out item.

//**** Version collection errors.
#define EREP_VCOL_VERSIONNOTMEMBER	EMAKEHR(0x1900)	// This version is not a member of this version collection.
#define EREP_VCOL_INVALIDOP		EMAKEHR(0x1901)		// Invalid operation performed on this collection.

//**** Relationship/Target Object collection errors.
#define EREP_COL_NOTSEQUENCED	EMAKEHR(0x1950)		// This operation cannot be performed on a non-sequenced collection.

#endif // __REPERR_H__
