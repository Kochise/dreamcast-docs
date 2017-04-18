/************************************************************************
**	D B D A O I D . H													*
**																		*
**		History 														*
**		------- 														*
**	09-05-93   	peterdi		Creation 			 						*
**	09-17-93	wolfma		GUID's added								*
**																		*
**	OLE DAO component class id definitions								*
**	DAO has been allocated the GUID::Data1 range of 0x00025eXX			*
**																		*
*************************************************************************
** Copyright (C) 1992 and 1993 by Microsoft Corporation		 			*
**		   All Rights Reserved					 						*
** Information Contained Herein Is Proprietary and Confidential.	 	*
************************************************************************/

/*
	NOTES:

	*	Do not reuse the defunct GUIDs specified at the bottom of this file.

	*	All UNICODE OLE Automation interface IDs must be the same as the ANSI
		interface IDs with exception that Data1 is offset +1.
		(This is so that wide interfaces can be generated automatically)

	*	All UNICODE IID_... names must be the same as the ANSI IID_... name
		with a "W" appended to the end.

	(peterdi)

	*	For versions 3.5, 4.0 and beyond, DAO was assigned a new range of
		GUIDs for our use.  DEFINE-DAOGUID replaces the standard macro
		DEFINE-OLEGUID and applies the DAO base range to the id being
		defined.  DAO 3.5 has reserved 0x00000000 - 0x000000FF.  If more
		are needed they must not conflict with DAO 4.0's range which is
		based at 0x00000100.

	*	Since 3.5 uses a completely different base range I've dispensed
		with the list of defunct GUIDs from previous versions.  The list
		at the bottom of this file is now restriced to only defunct GUIDS
		for the 3.5 version.

	(markbue)


	*	The pre-3.5 GUIDs have been redefined with "30" added to the ID. For example:

			IID_IDAOIndex becomes IID30_IDAOIndex

		This way both the 30 and 3.5 GUIDs can be used at once (see bugs 1214, 1271) jcm 5/96
*/

// Because this file is consumed by an AWK script DO NOT use DEFINE_ OLEGUID or DEFINE_ DAOGUID
// in comments (change to DEFINE-OLEGUID or DEFINE-DAOGUID) - 1/97 jcm


// This is a gross little hack which allows VBA programmers access to context sensative help
// from within SQL strings -- click the help button on SELECT from a SQL string and it will
// jump to the help topic.  This has absolutely nothing to do with DAO and should be removed
// from our code.  But for now, we're hosting this poor little orphan so be nice and don't
// kick it out yet.... [mab June '96]
DEFINE_OLEGUID(LIBID_CJETSQLHELP,		0x00025f01, 0, 0);


// Define a local macro which will build GUIDS in the assigned DAO range.  We cannot
// use the standard DEFINE-OLEGUID macro because it assigns from a different base range
// than what we have been assigned.  [mab 9/27/95]
#define DEFINE_DAOGUID(name, l) \
    DEFINE_GUID(name, l, 0, 0x10, 0x80,0,0,0xAA,0,0x6D,0x2E,0xA4)


// Type library
DEFINE_OLEGUID(LIBID_CDAO,				0x00025e01, 0, 0);
DEFINE_OLEGUID(LIBID_CDAO25,			0x00025e04, 0, 0);

// Old BETA Type library IDs 
DEFINE_DAOGUID(BETA_LIBID_CDAO,				0x00000001);
DEFINE_DAOGUID(BETA_LIBID_CDAO25,			0x00000002);

// StdObject
DEFINE_DAOGUID(IID_IDAOStdObject,		0x0000000A);

// StdCollection
DEFINE_DAOGUID(IID_IDAOStdCollection,	0x0000000C);

// Creatable Classes
DEFINE_DAOGUID(CLSID_CDAODBEngine,		0x00000100);
DEFINE_DAOGUID(CLSID_CDAOPrivDBEngine,	0x00000101);
DEFINE_DAOGUID(CLSID_CDAOConnection,	0x00000102);
DEFINE_DAOGUID(CLSID_CDAOTableDef,		0x00000103);
DEFINE_DAOGUID(CLSID_CDAOField, 		0x00000104);
DEFINE_DAOGUID(CLSID_CDAOIndex, 		0x00000105);
DEFINE_DAOGUID(CLSID_CDAOGroup, 		0x00000106);
DEFINE_DAOGUID(CLSID_CDAOUser,			0x00000107);
DEFINE_DAOGUID(CLSID_CDAOQueryDef,		0x00000108);
DEFINE_DAOGUID(CLSID_CDAORelation,		0x00000109);

//DAO3.5 creatable objects
DEFINE_DAOGUID(CLSID35_CDAODBEngine,		0x00000010);
DEFINE_DAOGUID(CLSID35_CDAOPrivDBEngine,	0x00000011);
DEFINE_DAOGUID(CLSID35_CDAOConnection,	0x00000012);
DEFINE_DAOGUID(CLSID35_CDAOTableDef,		0x00000013);
DEFINE_DAOGUID(CLSID35_CDAOField, 		0x00000014);
DEFINE_DAOGUID(CLSID35_CDAOIndex, 		0x00000015);
DEFINE_DAOGUID(CLSID35_CDAOGroup, 		0x00000016);
DEFINE_DAOGUID(CLSID35_CDAOUser,			0x00000017);
DEFINE_DAOGUID(CLSID35_CDAOQueryDef,		0x00000018);
DEFINE_DAOGUID(CLSID35_CDAORelation,		0x00000019);

/*	Do not currently support creating these CDAO objects
 * CLSID_CDAOWorkspace
 * CLSID_CDAODatabase
 * CLSID_CDAORecordset
 * CLSID_CDAOParameter
 * CLSID_CDAOProperty
 * CLSID_CDAOContainer
 * CLSID_CDAODocument
 */

// DBEngine
DEFINE_DAOGUID(IID_IDAODBEngine,		0x00000020);
DEFINE_DAOGUID(IID_IDAODBEngineW,		0x00000021);

// Error
DEFINE_DAOGUID(IID_IDAOError,			0x00000022);
DEFINE_DAOGUID(IID_IDAOErrorW,			0x00000023);
DEFINE_DAOGUID(IID_IDAOErrors,			0x00000024);
DEFINE_DAOGUID(IID_IDAOErrorsW,			0x00000025);

// Property
DEFINE_DAOGUID(IID_IDAOProperty,		0x00000026);
DEFINE_DAOGUID(IID_IDAOPropertyW,		0x00000027);
DEFINE_DAOGUID(IID_IDAOProperties,		0x00000028);
DEFINE_DAOGUID(IID_IDAOPropertiesW,		0x00000029);

// Recordset
DEFINE_DAOGUID(IID_IDAORecordset,		0x00000030);
DEFINE_DAOGUID(IID_IDAORecordsetW,		0x00000031);
DEFINE_DAOGUID(IID_IDAORecordsets,		0x00000032);
DEFINE_DAOGUID(IID_IDAORecordsetsW,		0x00000033);
DEFINE_OLEGUID(IID_ICDAORecordset,		0x00025e31, 0, 0);	//same as it was in 3.0
//DEFINE-DAOGUID(IID_ICDAORecordset,		0x000000C0);
//DEFINE-DAOGUID(IID_ICRDORecordset,		0x000000C1);

// Workspace
DEFINE_DAOGUID(IID_IDAOWorkspace,		0x00000038);
DEFINE_DAOGUID(IID_IDAOWorkspaceW,		0x00000039);
DEFINE_DAOGUID(IID_IDAOWorkspaces,		0x0000003A);
DEFINE_DAOGUID(IID_IDAOWorkspacesW,		0x0000003B);

// Connection
DEFINE_DAOGUID(IID_IDAOConnection,		0x00000040);
DEFINE_DAOGUID(IID_IDAOConnectionW,		0x00000041);
DEFINE_DAOGUID(IID_IDAOConnections,		0x00000042);
DEFINE_DAOGUID(IID_IDAOConnectionsW,	0x00000043);

// TableDef
DEFINE_DAOGUID(IID_IDAOTableDef,		0x00000048);
DEFINE_DAOGUID(IID_IDAOTableDefW,		0x00000049);
DEFINE_DAOGUID(IID_IDAOTableDefs,		0x0000004A);
DEFINE_DAOGUID(IID_IDAOTableDefsW,		0x0000004B);

// Field
DEFINE_DAOGUID(IID_IDAOField,			0x00000050);
DEFINE_DAOGUID(IID_IDAOFieldW,			0x00000051);
DEFINE_DAOGUID(IID_IDAOFields,			0x00000052);
DEFINE_DAOGUID(IID_IDAOFieldsW,			0x00000053);

// Index
DEFINE_DAOGUID(IID_IDAOIndex,			0x00000058);
DEFINE_DAOGUID(IID_IDAOIndexW,			0x00000059);
DEFINE_DAOGUID(IID_IDAOIndexes,			0x0000005A);
DEFINE_DAOGUID(IID_IDAOIndexesW,		0x0000005B);
//UNDONE:  Can we get rid of this?  The Index Fields problem should
// be able to go away since 3.5 doesn't support 2.x syntaxes.
DEFINE_DAOGUID(IID_IDAOIndexFields,		0x0000005C);
DEFINE_DAOGUID(IID_IDAOIndexFieldsW,	0x0000005D);

// Group
DEFINE_DAOGUID(IID_IDAOGroup,			0x00000060);
DEFINE_DAOGUID(IID_IDAOGroupW,			0x00000061);
DEFINE_DAOGUID(IID_IDAOGroups,			0x00000062);
DEFINE_DAOGUID(IID_IDAOGroupsW,			0x00000063);

// User
DEFINE_DAOGUID(IID_IDAOUser,			0x00000068);
DEFINE_DAOGUID(IID_IDAOUserW,			0x00000069);
DEFINE_DAOGUID(IID_IDAOUsers,			0x0000006A);
DEFINE_DAOGUID(IID_IDAOUsersW,			0x0000006B);

// Database
DEFINE_DAOGUID(IID_IDAODatabase,		0x00000070);
DEFINE_DAOGUID(IID_IDAODatabaseW,		0x00000071);
DEFINE_DAOGUID(IID_IDAODatabases,		0x00000072);
DEFINE_DAOGUID(IID_IDAODatabasesW,		0x00000073);

// QueryDef
DEFINE_DAOGUID(IID_IDAOQueryDef,		0x00000078);
DEFINE_DAOGUID(IID_IDAOQueryDefW,		0x00000079);
DEFINE_DAOGUID(IID_IDAOQueryDefs,		0x0000007A);
DEFINE_DAOGUID(IID_IDAOQueryDefsW,		0x0000007B);

// Parameter
DEFINE_DAOGUID(IID_IDAOParameter,		0x00000080);
DEFINE_DAOGUID(IID_IDAOParameterW,		0x00000081);
DEFINE_DAOGUID(IID_IDAOParameters,		0x00000082);
DEFINE_DAOGUID(IID_IDAOParametersW,		0x00000083);

// Relation
DEFINE_DAOGUID(IID_IDAORelation,		0x00000088);
DEFINE_DAOGUID(IID_IDAORelationW,		0x00000089);
DEFINE_DAOGUID(IID_IDAORelations,		0x0000008A);
DEFINE_DAOGUID(IID_IDAORelationsW,		0x0000008B);

// Container
DEFINE_DAOGUID(IID_IDAOContainer,		0x00000090);
DEFINE_DAOGUID(IID_IDAOContainerW,		0x00000091);
DEFINE_DAOGUID(IID_IDAOContainers,		0x00000092);
DEFINE_DAOGUID(IID_IDAOContainersW,		0x00000093);

// Document
DEFINE_DAOGUID(IID_IDAODocument,		0x00000098);
DEFINE_DAOGUID(IID_IDAODocumentW,		0x00000099);
DEFINE_DAOGUID(IID_IDAODocuments,		0x0000009A);
DEFINE_DAOGUID(IID_IDAODocumentsW,		0x0000009B);

// Collections (how are these used?  mab 9/27/95)
DEFINE_DAOGUID(IID_IDAOCollection,		0x000000A0);
DEFINE_DAOGUID(IID_IDAODynaCollection,	0x000000A2);

// Connection points (how are these used?  mab 9/27/95)
DEFINE_DAOGUID(IID_IDAOQueryCP,			0x000000B0);	// Connection point
DEFINE_DAOGUID(IID_IDAOQueryAS,			0x000000B2);	// Advise sink interface

// A few private interfaces, mostly for use by Access.
DEFINE_DAOGUID(IID_ICDAOJETDBEngine,	0x000000A0);	//Access uses this.
DEFINE_DAOGUID(IID_ICDAOJETError,		0x000000A1);
DEFINE_DAOGUID(IID_ICDAOJETRecordset,	0x000000A2);
DEFINE_DAOGUID(IID_ICDAOJETWorkspace,	0x000000A3);
DEFINE_DAOGUID(IID_ICDAOJETField,		0x000000A4);
DEFINE_DAOGUID(IID_ICDAOJETDatabase,	0x000000A5);

//UNDONE:  These are defunct interfaces, not supported by DAO 3.4, so
// we should remove them completely.  For now, I'll just give them very
// large GUIDS in our assigned range.  [mab 9/27/95]

// Snapshot
DEFINE_DAOGUID(IID_IDAOSnapshot,		0x000000FD);

// Table
DEFINE_DAOGUID(IID_IDAOTable,			0x000000FE);

// Dynaset
DEFINE_DAOGUID(IID_IDAODynaset,			0x000000FF);

/**************************************
* Disconnect Interfaces
*
*	TODO:  Need confirmation from Dave Stutz
*/
DEFINE_GUID(IID_IDisconnect,	0xB196B288,0xBAB4,0x101A,0xB6,0x9C,0x00,0xAA,0x00,0x34,0x1D,0x07);
DEFINE_GUID(IID_IDisconnectAll,	0xB196B289,0xBAB4,0x101A,0xB6,0x9C,0x00,0xAA,0x00,0x34,0x1D,0x07);

/**************************************
* Data Source Control Interfaces
*
*	TODO:  Need to get these from VB!
*/
//UNDONE:  ? Why do we need to get these from vb?  They should
// be getting them from us shouldn't they?  I'll comment out the
// old GUIDs here but I'm changing them to the new range. [mab 9/27/95]
//DEFINE-OLEGUID(IID_IDSCAdviseSink,		0x00025EFEL, 0, 0);
//DEFINE-OLEGUID(IID_IDSCConnectionPoint,	0x00025EFFL, 0, 0);
DEFINE_DAOGUID(IID_IDSCAdviseSink,		0x000000E0);
DEFINE_DAOGUID(IID_IDSCConnectionPoint,	0x000000E2);

// Database connection points
DEFINE_DAOGUID(IID_IDBAdviseSink,		0x000000E8);
DEFINE_DAOGUID(IID_IDBConnectionPoint,	0x000000EA);

/* Defunct GUIDS!!!! Do not reuse!!!!
 * DAO versions 2.5 and 3.0 used DEFINE_OLEGUID to create guids in the
 * standard Microsoft OLE range.  We now have own private range and use
 * DEFINE-DAOGUID to generate them.  Rather list explicitly all the old
 * GUIDS for 2.5 and 3.0 we will simply declare that all GUIDS generated
 * by the standard DEFINE_OLEGUID with a Data1 value in the range of
 * 0x00025EF00 through 0x00025EFFF are hereby defunct.
 *
 * Listed below will be only the guids which have been retired from the
 * DEFINE-DAOGUID range.  [mab 9/27/95]
 */

// <There are no defunct guids yet.  Remeber to remove this comment when
// you do retire some guids!>



// Type library
DEFINE_OLEGUID(LIBID30_CDAO,				0x00025e01, 0, 0);
DEFINE_OLEGUID(LIBID30_CDAO25,			0x00025e04, 0, 0);

// StdObject
DEFINE_OLEGUID(IID30_IDAOStdObject,		0x00025e02, 0, 0);

// StdCollection
DEFINE_OLEGUID(IID30_IDAOStdCollection,	0x00025e03, 0, 0);

/*
	NOTES:

	* Two sets of CLSIDs exist for the DBEngine object.
	* DBEngine and DBEngine30.  The 30 extension means
	* that this engine should load the 3.0 typelibrary
	* from the registry.  Otherwise, load the 2.5/3.0
	* compatability type library

	(daxh)
*/

// DBEngine
DEFINE_OLEGUID(CLSID30_CDAODBEngine,		0x00025e15, 0, 0);
DEFINE_OLEGUID(IID30_IDAODBEngine,		0x00025e16, 0, 0);
DEFINE_OLEGUID(IID30_IDAODBEngineW,		0x00025e17, 0, 0);
DEFINE_OLEGUID(IID30_ICDAOJETDBEngine,	0x00025e18, 0, 0);
DEFINE_OLEGUID(CLSID30_CDAOPrivDBEngine,	0x00025e19, 0, 0);

// Error
DEFINE_OLEGUID(IID30_IDAOError,			0x00025e1d, 0, 0);
DEFINE_OLEGUID(IID30_IDAOErrorW,			0x00025e1e, 0, 0);
DEFINE_OLEGUID(IID30_IDAOErrors,			0x00025e1f, 0, 0);
DEFINE_OLEGUID(IID30_IDAOErrorsW,			0x00025e20, 0, 0);
DEFINE_OLEGUID(IID30_ICDAOJETError,		0x00025e21, 0, 0);	//used by Access, goes away post 3.0

// Property
DEFINE_OLEGUID(IID30_IDAOProperty,		0x00025e25, 0, 0);
DEFINE_OLEGUID(IID30_IDAOPropertyW,		0x00025e26, 0, 0);
DEFINE_OLEGUID(IID30_IDAOProperties,		0x00025e27, 0, 0);
DEFINE_OLEGUID(IID30_IDAOPropertiesW,		0x00025e28, 0, 0);

// Recordset
DEFINE_OLEGUID(IID30_IDAORecordset,		0x00025e2d, 0, 0);
DEFINE_OLEGUID(IID30_IDAORecordsetW,		0x00025e2e, 0, 0);
DEFINE_OLEGUID(IID30_IDAORecordsets,		0x00025e2f, 0, 0);
DEFINE_OLEGUID(IID30_IDAORecordsetsW,		0x00025e30, 0, 0);
DEFINE_OLEGUID(IID30_ICDAORecordset,		0x00025e31, 0, 0);	//NOTE: No change for 3.1 or 3.5
DEFINE_OLEGUID(IID30_ICDAOJETRecordset,	0x00025e32, 0, 0);

// Snapshot
DEFINE_OLEGUID(IID30_IDAOSnapshot,		0x00025e33, 0, 0);

// Table
DEFINE_OLEGUID(IID30_IDAOTable,			0x00025e34, 0, 0);

// Dynaset
DEFINE_OLEGUID(IID30_IDAODynaset,			0x00025e35, 0, 0);

// Workspace
DEFINE_OLEGUID(IID30_IDAOWorkspace,		0x00025e3a, 0, 0);
DEFINE_OLEGUID(IID30_IDAOWorkspaceW,		0x00025e3b, 0, 0);
DEFINE_OLEGUID(IID30_IDAOWorkspaces,		0x00025e3c, 0, 0);
DEFINE_OLEGUID(IID30_IDAOWorkspacesW,		0x00025e3d, 0, 0);
DEFINE_OLEGUID(IID30_ICDAOJETWorkspace,	0x00025e3e, 0, 0);

// Connection (new to 3.1)
DEFINE_OLEGUID(CLSID30_CDAOConnection,	0x00025eb1, 0, 0);
DEFINE_OLEGUID(IID30_IDAOConnection,		0x00025eb2, 0, 0);
DEFINE_OLEGUID(IID30_IDAOConnectionW,		0x00025eb3, 0, 0);
DEFINE_OLEGUID(IID30_IDAOConnections,		0x00025eb4, 0, 0);
DEFINE_OLEGUID(IID30_IDAOConnectionsW,	0x00025eb5, 0, 0);

// TableDef
DEFINE_OLEGUID(CLSID30_CDAOTableDef,		0x00025e43, 0, 0);
DEFINE_OLEGUID(IID30_IDAOTableDef,		0x00025e44, 0, 0);
DEFINE_OLEGUID(IID30_IDAOTableDefW,		0x00025e45, 0, 0);
DEFINE_OLEGUID(IID30_IDAOTableDefs,		0x00025e46, 0, 0);
DEFINE_OLEGUID(IID30_IDAOTableDefsW,		0x00025e47, 0, 0);

// Field
DEFINE_OLEGUID(CLSID30_CDAOField, 		0x00025e4c, 0, 0);
DEFINE_OLEGUID(IID30_IDAOField,			0x00025e4d, 0, 0);
DEFINE_OLEGUID(IID30_IDAOFieldW,			0x00025e4e, 0, 0);
DEFINE_OLEGUID(IID30_IDAOFields,			0x00025e4f, 0, 0);
DEFINE_OLEGUID(IID30_IDAOFieldsW,			0x00025e50, 0, 0);
//DEFINE-OLEGUID(IID30_ICDAOJETField,		0x00025e51, 0, 0);	//used by Access, goes away post 3.0
DEFINE_OLEGUID(IID30_ICDAOJETField,		0x00025e49, 0, 0);	//used by Access, goes away post 3.0

// Index
DEFINE_OLEGUID(CLSID30_CDAOIndex, 		0x00025e55, 0, 0);
DEFINE_OLEGUID(IID30_IDAOIndex,			0x00025e56, 0, 0);
DEFINE_OLEGUID(IID30_IDAOIndexW,			0x00025ed7, 0, 0);
DEFINE_OLEGUID(IID30_IDAOIndexes,			0x00025e58, 0, 0);
DEFINE_OLEGUID(IID30_IDAOIndexesW,		0x00025e59, 0, 0);
DEFINE_OLEGUID(IID30_IDAOIndexFields,		0x00025e5a, 0, 0);
DEFINE_OLEGUID(IID30_IDAOIndexFieldsW,	0x00025e5b, 0, 0);

// Group
DEFINE_OLEGUID(CLSID30_CDAOGroup, 		0x00025e5f, 0, 0);
DEFINE_OLEGUID(IID30_IDAOGroup,			0x00025e60, 0, 0);
DEFINE_OLEGUID(IID30_IDAOGroupW,			0x00025e61, 0, 0);
DEFINE_OLEGUID(IID30_IDAOGroups,			0x00025e62, 0, 0);
DEFINE_OLEGUID(IID30_IDAOGroupsW,			0x00025e63, 0, 0);

// User
DEFINE_OLEGUID(CLSID30_CDAOUser,			0x00025e68, 0, 0);
DEFINE_OLEGUID(IID30_IDAOUser,			0x00025e69, 0, 0);
DEFINE_OLEGUID(IID30_IDAOUserW,			0x00025e6a, 0, 0);
DEFINE_OLEGUID(IID30_IDAOUsers,			0x00025e6b, 0, 0);
DEFINE_OLEGUID(IID30_IDAOUsersW,			0x00025e6c, 0, 0);

// Database
DEFINE_OLEGUID(IID30_IDAODatabase,		0x00025e71, 0, 0);
DEFINE_OLEGUID(IID30_IDAODatabaseW,		0x00025e72, 0, 0);
DEFINE_OLEGUID(IID30_IDAODatabases,		0x00025e73, 0, 0);
DEFINE_OLEGUID(IID30_IDAODatabasesW,		0x00025e74, 0, 0);
DEFINE_OLEGUID(IID30_ICDAOJETDatabase,	0x00025e75, 0, 0);

// QueryDef
DEFINE_OLEGUID(CLSID30_CDAOQueryDef,		0x00025e7a, 0, 0);
DEFINE_OLEGUID(IID30_IDAOQueryDef,		0x00025e7b, 0, 0);
DEFINE_OLEGUID(IID30_IDAOQueryDefW,		0x00025e7c, 0, 0);
DEFINE_OLEGUID(IID30_IDAOQueryDefs,		0x00025e7d, 0, 0);
DEFINE_OLEGUID(IID30_IDAOQueryDefsW,		0x00025e7e, 0, 0);

// Parameter
DEFINE_OLEGUID(IID30_IDAOParameter,		0x00025e83, 0, 0);
DEFINE_OLEGUID(IID30_IDAOParameterW,		0x00025e84, 0, 0);
DEFINE_OLEGUID(IID30_IDAOParameters,		0x00025e85, 0, 0);
DEFINE_OLEGUID(IID30_IDAOParametersW,		0x00025e86, 0, 0);

// Relation
DEFINE_OLEGUID(CLSID30_CDAORelation,		0x00025e8b, 0, 0);
DEFINE_OLEGUID(IID30_IDAORelation,		0x00025e8c, 0, 0);
DEFINE_OLEGUID(IID30_IDAORelationW,		0x00025e8d, 0, 0);
DEFINE_OLEGUID(IID30_IDAORelations,		0x00025e8e, 0, 0);
DEFINE_OLEGUID(IID30_IDAORelationsW,		0x00025e8f, 0, 0);

// Container
DEFINE_OLEGUID(IID30_IDAOContainer,		0x00025e94, 0, 0);
DEFINE_OLEGUID(IID30_IDAOContainerW,		0x00025e95, 0, 0);
DEFINE_OLEGUID(IID30_IDAOContainers,		0x00025e96, 0, 0);
DEFINE_OLEGUID(IID30_IDAOContainersW,		0x00025e97, 0, 0);

// Document
DEFINE_OLEGUID(IID30_IDAODocument,		0x00025e9c, 0, 0);
DEFINE_OLEGUID(IID30_IDAODocumentW,		0x00025e9d, 0, 0);
DEFINE_OLEGUID(IID30_IDAODocuments,		0x00025e9e, 0, 0);
DEFINE_OLEGUID(IID30_IDAODocumentsW,		0x00025e9f, 0, 0);

// Collections
DEFINE_OLEGUID(IID30_IDAOCollection,		0x00025ea4, 0, 0);
DEFINE_OLEGUID(IID30_IDAODynaCollection,	0x00025ea5, 0, 0);

// Connection points
DEFINE_OLEGUID(IID30_IDAOQueryCP,			0x00025eaa, 0, 0);	// Connection point
DEFINE_OLEGUID(IID30_IDAOQueryAS,			0x00025eab, 0, 0);	// Advise sink interface

/**************************************
* Disconnect Interfaces
*
*	TODO:  Need confirmation from Dave Stutz
*/
DEFINE_GUID(IID30_IDisconnect,	0xB196B288,0xBAB4,0x101A,0xB6,0x9C,0x00,0xAA,0x00,0x34,0x1D,0x07);
DEFINE_GUID(IID30_IDisconnectAll,	0xB196B289,0xBAB4,0x101A,0xB6,0x9C,0x00,0xAA,0x00,0x34,0x1D,0x07);

/**************************************
* Data Source Control Interfaces
*
*	TODO:  Need to get these from VB!
*/
DEFINE_OLEGUID(IID30_IDSCAdviseSink,		0x00025EFEL, 0, 0);
DEFINE_OLEGUID(IID30_IDSCConnectionPoint,	0x00025EFFL, 0, 0);

// Database connection points
DEFINE_OLEGUID(IID30_IDBAdviseSink,		0x00025EFCL, 0, 0);
DEFINE_OLEGUID(IID30_IDBConnectionPoint,	0x00025EFDL, 0, 0);

/* Defunct GUIDS!!!! Do not reuse!!!!
*(LIBID_CDAO,    0x00025e00, 0, 0);
*(CLSID_CDAODBEngine,  0x00025e11, 0, 0);
*/

/*	Do not currently support creating these CDAO objects
*(CLSID_CDAOWorkspace,  0x00025exx, 0, 0);
*(CLSID_CDAODatabase,  0x00025exx, 0, 0);
*(CLSID_CDAORecordset,  0x00025exx, 0, 0);
*(CLSID_CDAOParameter,  0x00025exx, 0, 0);
*(CLSID_CDAOProperty,  0x00025exx, 0, 0);
*(CLSID_CDAOContainer,  0x00025exx, 0, 0);
*(CLSID_CDAODocument,  0x00025exx, 0, 0);
*/

/* OLD ids
*(CLSID_CDAODBEngineConfig,0x00025e10, 0, 0);
*(IID_IDAODBEngineConfig, 0x00025e30, 0, 0);
*(IID_DDAODBEngineConfig, 0x00025e50, 0, 0);
*/

/* Dispinterfaces no longer used
*(IID_DDAODynaset,   0x00025e66, 0, 0);
*(IID_DDAOTable,   0x00025e64, 0, 0);
*(IID_DDAOSnapshot,  0x00025e65, 0, 0);
*(IID_DDAORecordsets,  0x00025e6b, 0, 0);
*(IID_DDAORecordset,   0x00025e56, 0, 0);
*(IID_DDAOProperties,  0x00025e75, 0, 0);
*(IID_DDAOProperty,  0x00025e5d, 0, 0);
*(IID_DDAOErrors,   0x00025e63, 0, 0);
*(IID_DDAOError,   0x00025e62, 0, 0);
*(IID_DDAODBEngine,  0x00025e51, 0, 0);
*(IID_DDAOWorkspace,   0x00025e52, 0, 0);
*(IID_DDAODatabase,  0x00025e53, 0, 0);
*(IID_DDAOTableDef,  0x00025e54, 0, 0);
*(IID_DDAOQueryDef,  0x00025e55, 0, 0);
*(IID_DDAOField,    0x00025e57, 0, 0);
*(IID_DDAOIndex,    0x00025e58, 0, 0);
*(IID_DDAOParameter,   0x00025e59, 0, 0);
*(IID_DDAOUser,   0x00025e5a, 0, 0);
*(IID_DDAOGroup,    0x00025e5b, 0, 0);
*(IID_DDAORelation,  0x00025e5c, 0, 0);
*(IID_DDAOContainer,   0x00025e5e, 0, 0);
*(IID_DDAODocument,  0x00025e5f, 0, 0);
*(IID_DDAOCollection,  0x00025e60, 0, 0);
*(IID_DDAODynaCollection, 0x00025e61, 0, 0);
*(IID_DDAOWorkspaces,  0x00025e67, 0, 0);
*(IID_DDAODatabases,  0x00025e68, 0, 0);
*(IID_DDAOTableDefs,  0x00025e69, 0, 0);
*(IID_DDAOQueryDefs,  0x00025e6a, 0, 0);
*(IID_DDAOFields,   0x00025e6c, 0, 0);
*(IID_DDAOIndexFields,  0x00025e6d, 0, 0);
*(IID_DDAOIndexes,   0x00025e6e, 0, 0);
*(IID_DDAOParameters,  0x00025e6f, 0, 0);
*(IID_DDAOUsers,   0x00025e70, 0, 0);
*(IID_DDAOGroups,   0x00025e71, 0, 0);
*(IID_DDAORelations,  0x00025e72, 0, 0);
*(IID_DDAOContainers,  0x00025e73, 0, 0);
*(IID_DDAODocuments,  0x00025e74, 0, 0);
*/



