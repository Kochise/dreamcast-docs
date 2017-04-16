#ifndef _DBSERVER_INCLUDE
#define _DBSERVER_INCLUDE

typedef long HRESULT;

class IDB {
  // Interfaces
  public:
	  	// Interface for data access
		virtual HRESULT Read(short nTable, short nRow, LPTSTR lpszData) =0;
		virtual HRESULT Write(short nTable, short nRow, LPCTSTR lpszData) =0;

		// Interface for database management
		virtual HRESULT Create(short &nTable, LPCTSTR lpszName) =0;
		virtual HRESULT Delete(short nTable) =0;

		// Interface for database information
		virtual HRESULT GetNumTables(short &nNumTables) =0;
		virtual HRESULT GetTableName(short nTable, LPTSTR lpszName) =0;
		virtual HRESULT GetNumRows(short nTable, short &nRows) =0;
};

HRESULT CreateDB(IDB** ppObj);

#endif
