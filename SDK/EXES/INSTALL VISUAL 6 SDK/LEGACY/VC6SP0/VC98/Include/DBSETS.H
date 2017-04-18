/***********************************************************************
**      D B S E T S . H                                                *
**                                                                     *
************************************************************************
** Copyright (C) 1996 by Microsoft Corporation                         *
**                 All Rights Reserved                                 *
************************************************************************/
/*

        DBSETS.H

        Database recordset class definitions for Microsoft Guide



*/



#ifndef _DBSETS_H_
#define _DBSETS_H_

#include "mstv.h"

#ifdef DBSETS_STATIC
#undef COMMMSTVEXPORT
#define COMMMSTVEXPORT
#endif

/*

The following classes provide an encapsulation of the dbDAO classes that
offers a simplified interface to the database tables.

CDatabaseConnection and CDatabaseRecordset are the root classes from
which individual Recordset classes are derived.

A Recordset class provides a means to open a recordset, fetch, update,
insert, and delete records, and close the recordset.  The records
produced are of the object type associated with the table.  The
Recordset object itself may be repeatedly opened and closed without
the need for deleting and re-instantiating a new object.

For example, the Episode table is accessed using the CEpisodeRecordset class.
It is opened with a where clause parameter that specifies the set of records.
Getting a record produces a CEpisode object, on a one-to-one basis.  The user
is responsible for deleting the object, and appropriate manipulation of the
object is done using the CEpisode methods.

Only the current record of an open recordset may be updated or deleted.

It is important to note that recordsets are opened by the Jet database engine
as either a Dynaset or Snapshot.  A Dynaset is essentially a list of pointers
to the records in the table.  Data is read from the database only when the
record is actually fetched.  A Snapshot reads all records in the set into a
RAM cache.  Large sets will cause caching to disk and subsequent poorer
performance.  Recordsets will be opened as Dynasets unless the optional lType
parameter specifies otherwise.

The record count is not defined on opening a recordset.  Calling
GetRecordCount requires "moving to the last record", which may be slow for
larger recordsets.  Recordsets generated with an ORDER BY clause appear to
correctly set the initial record count.


*/

COMMMSTVEXPORT void __stdcall SetJet ( CdbDBEngine* pEngine, CdbWorkspace* pWorkspace, CdbDatabase* pDatabase ); 
COMMMSTVEXPORT CdbDatabase * __stdcall GetDatabase(VOID);
COMMMSTVEXPORT BOOL __stdcall GetDatabaseConnected(VOID);


class COMMMSTVEXPORT CDatabaseConnection
{

//  This class provides the root encapsulation of the Jet engine and
//  the EPG database.


public:


	BOOL	StartEngine( const CString &csViewer, const CString &csPassword,
											 const CString &systemFile);
	BOOL    ConnectToDatabase( const CString &csViewer, const CString &csPassword,
							 const CString &systemFile, const CString &databaseFile, CString csWorkspaceName = "");

    BOOL    DisconnectFromDatabase( VOID);

    BOOL    CompactDatabase( VOID);

	CString  GetWorkspaceName( VOID);

	LPUNKNOWN GetWorkspaceUnknown( VOID);

protected:

	VOID    HandleDBException( CdbException* pException, LPCTSTR SourceOfException);

	BOOL 	RepairDB( const CString &databaseFile );

	BOOL	DataBaseInNeedOfRepair();
};





    enum // FindType is one of
    {   dbFindFirst = 1,
        dbFindLast,
        dbFindNext,
        dbFindPrevious
    };



class COMMMSTVEXPORT CDatabaseRecordset : public CDatabaseConnection
{

// This class provides the root encapsulation for recordset manipulation


// lType is one of: dbOpenSnapshot or default dbOpenDynaset
                
 
public:
                CDatabaseRecordset(VOID);
               ~CDatabaseRecordset(VOID);

		virtual BOOL    OpenRecordset( LPCTSTR WhereBy, LONG lType=-1);

        BOOL    OpenRecordsetQueryDef( LPCTSTR QueryName, LONG lType=-1);

        virtual VOID    CloseRecordset( VOID);

        CString GetQueryPrefix( VOID);

        LONG    GetRecordCount( VOID);

        VOID*   GetRecord( LONG RecordNumber);

        BOOL    GotoRecord( LONG RecordNumber);

        LONG    FindRecord( LONG FindType, LPCTSTR Criteria);

        BOOL    InsertRecord( VOID* cRecordsetObject);

        BOOL    UpdateRecord( VOID* cRecordsetObject);

        BOOL    DeleteRecord( VOID);

		void OpenIndexed(int iKeyID, int nOpenType,
										LPCTSTR lpszSQL, int nOptions);
		void SeekAddRS(CObject &coo);
		void UpdateRS(CObject &coo);
		void StartUpdateRS(CObject &coo);
		void EndUpdateRS();

		void Edit(void);
		void Update(void);
		void MoveFirst(void);
		void MovePrevious(void);
		void MoveNext(void);
		void MoveLast(void);
		BOOL GetEOF(void);

		COleVariant GetField(LPCTSTR pstrIndex);
		LONG GetLongField(LPCTSTR pstrIndex);
		COleVariant GetField(LONG lIndex);
		VOID SetField(LPCTSTR pstrIndex, COleVariant cov);
		ULONG GetFieldSize(LPCTSTR pstrIndex);

                // implemented by child recordset

virtual CString GetTableName( VOID) = 0;



protected:      // implemented by child recordset

virtual BOOLEAN Seek(LPCTSTR lpszComparison, CObject &coo);

virtual VOID*   GetRecordsetObject( VOID) = 0;

virtual BOOL    SetRecordsetObject( VOID* cRecordsetObject) = 0;



protected:          // accessed by child recordset

    CdbRecordset    m_cRecordset;


protected:

    time_t          m_ConnectTime;

    LONG            m_lRecordCount;
    LONG            m_lRecordNumber;
    BOOL            m_bRecordsetOpen;

};


#define AFX_RFX_LONG_PSEUDO_NULL (0x4a4d4120L)	// from afxdb.h


// Conversion macros - Variant

// These macros are used by the GetRecordsetObject routines to convert the
// Variant returned by dbdao to the local data type.
// Note there is no checking for nulls or incorrect data type,
// therefore use these macros at your own risk!

#define VAR2BOOL(v)           (v).bVal
#define VAR2BYTE(v)           (v).bVal
#define VAR2SHORT(v)          (v).iVal
#define VAR2LONG(v)           (v).lVal
#define VAR2FLOAT(v)          (v).fltVal
#define VAR2DOUBLE(v)         (v).dblVal
#define VAR2DATE(v)           (v)
#define VAR2CURRENCY(v)       (v)
#define VAR2CSTR(v)  (LPCTSTR)(v).bstrVal

// These macros are used in SetRecordsetObject routines to convert the local
// data type to COleVariant for dbdao

#define BOOL2OLEVAR(a)      COleVariant((BYTE)(a))
#define BYTE2OLEVAR(a)      COleVariant((a))
#define SHORT2OLEVAR(a)     COleVariant((a))
#define LONG2OLEVAR(a)      COleVariant((a))
#define FLOAT2OLEVAR(a)     COleVariant((a))
#define DOUBLE2OLEVAR(a)    COleVariant((a))
#define DATE2OLEVAR(a)      COleVariant((a))
#define CURRENCY2OLEVAR(a)  COleVariant((a))
#define CSTR2OLEVAR(a)      COleVariant((LPCTSTR)(a),VT_BSTRT)

#endif

