#include "stdafx.h"

#include "DBsrvImp.h" //CPPtoDLL: change to include implementation

#ifdef LOCALSERVER
	#include "..\objectexe\dblocal.h"
#endif
#define new DEBUG_NEW

// Database object
HRESULT CDB::Read(short nTable, short nRow, LPWSTR lpszData) {
	EnterCriticalSection(&m_secDB);
  CStringArray *pTable;
  pTable=(CStringArray*) m_arrTables[nTable];
#ifndef UNICODE
	MultiByteToWideChar(CP_ACP, 0, (*pTable)[nRow], -1, lpszData, 80);
#else
  lstrcpy (lpszData, (*pTable)[nRow]);
#endif
	LeaveCriticalSection(&m_secDB);
  return NO_ERROR;
}

HRESULT CDB::Write(short nTable, short nRow, LPCWSTR lpszData) {
	EnterCriticalSection(&m_secDB);
  CStringArray *pTable;
  pTable=(CStringArray*) m_arrTables[nTable];
#ifdef UNICODE
  pTable->SetAtGrow(nRow, lpszData);
#else
	char szData[80];
	WideCharToMultiByte(CP_ACP, 0, lpszData, -1, szData, 80, NULL, NULL);
  pTable->SetAtGrow(nRow, szData);
#endif
	LeaveCriticalSection(&m_secDB);
  return NO_ERROR;
}

HRESULT CDB::Create(short &nTable, LPCWSTR lpszName) {
	EnterCriticalSection(&m_secDB);
  CStringArray *pTable=new CStringArray;
  nTable=m_arrTables.Add(pTable);
#ifdef UNICODE
  m_arrNames.SetAtGrow(nTable, lpszName);
#else
	char szName[80];
	WideCharToMultiByte(CP_ACP, 0, lpszName, -1, szName, 80, NULL, NULL);
  m_arrNames.SetAtGrow(nTable, szName);
#endif
	LeaveCriticalSection(&m_secDB);
  return NO_ERROR;
}

HRESULT CDB::Delete(short nTable) {
	EnterCriticalSection(&m_secDB);
  CStringArray *pTable;
  pTable=(CStringArray*) m_arrTables[nTable];
  delete pTable;
  m_arrTables[nTable]=NULL;
  m_arrNames[nTable]="";
  if (nTable==m_arrTables.GetSize()-1) {
		m_arrTables.RemoveAt(nTable);
		m_arrNames.RemoveAt(nTable);
    }
	LeaveCriticalSection(&m_secDB);
  return NO_ERROR;
}

HRESULT CDB::GetNumTables(short &nNumTables) {
	EnterCriticalSection(&m_secDB);
  nNumTables=m_arrTables.GetSize();
	LeaveCriticalSection(&m_secDB);
	return NOERROR;

}

HRESULT CDB::GetTableName(short nTable, LPWSTR lpszName) {
	EnterCriticalSection(&m_secDB);
#ifndef UNICODE
	MultiByteToWideChar(CP_ACP, 0, m_arrNames[nTable], -1, lpszName, 80);
#else
  lstrcpy(lpszName, m_arrNames[nTable]);
#endif
	LeaveCriticalSection(&m_secDB);
  return NO_ERROR;
}

HRESULT CDB::GetNumRows(short nTable, short &nRows) {
	EnterCriticalSection(&m_secDB);
  CStringArray *pTable;
  pTable=(CStringArray*) m_arrTables[nTable];
	LeaveCriticalSection(&m_secDB);
  return pTable->GetSize();
}

CDB::~CDB() {
	EnterCriticalSection(&m_secDB);
  short nNumTables;
  for (GetNumTables(nNumTables);nNumTables>0; GetNumTables(nNumTables)) {
		Delete(nNumTables-1);
    }
#ifdef LOCALSERVER
	m_pDoc->OnCloseDocument();
	m_pDoc=NULL;
#endif
	LeaveCriticalSection(&m_secDB);
	DeleteCriticalSection(&m_secDB);
}

CDB::CDB() {
	InitializeCriticalSection(&m_secDB);
	m_dwRefCount=0;
#ifdef LOCALSERVER
	((CDBLocalApp*) AfxGetApp())->OnFileNew();
	m_pDoc=((CDBLocalApp*) AfxGetApp())->m_pLastDoc;
#endif
}

HRESULT CDB::QueryInterface(REFIID riid, void** ppObject) {
	if (riid==IID_IUnknown || riid==IID_IDB) {
		*ppObject=(IDB*) this;
		}
	else if (riid==IID_IDBAccess) {
		*ppObject=(IDBAccess*) this;
		}
	else if (riid==IID_IDBManage) {
		*ppObject=(IDBManage*) this;
		}
	else if (riid==IID_IDBInfo) {
		*ppObject=(IDBInfo*) this;
		}
	else {
		return E_NOINTERFACE;
		}
	AddRef();
	return NO_ERROR;
}

ULONG CDB::AddRef() {
	InterlockedIncrement((long*) &g_dwRefCount);
	InterlockedIncrement((long*) &m_dwRefCount);
	return m_dwRefCount;
}

ULONG CDB::Release() {
	ULONG dwRefCount=m_dwRefCount-1;
	ULONG dwGlobalCount=InterlockedDecrement((long*) &g_dwRefCount);
	if (InterlockedDecrement((long*) &m_dwRefCount)==0) {
#ifdef LOCALSERVER
		if (dwGlobalCount==0) {
			AfxGetMainWnd()->PostMessage(WM_CLOSE);
			}
#endif
		delete this;
		return 0;
		}
	return dwRefCount;
}
