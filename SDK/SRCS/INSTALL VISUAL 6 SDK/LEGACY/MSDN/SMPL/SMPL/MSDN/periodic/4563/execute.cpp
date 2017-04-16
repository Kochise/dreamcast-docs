////////////////
// When the Execute button is pressed, run through the selected methods 
// and perform each, reporting an approximate execution time and listing
// the first field returned (only if it's a string or numeric)
//
void CDAOReadDlg::OnExecute() 
{
	DWORD			dwStart, dwEnd;
	DWORD			dwDuration;
	LONG			lIndex;
	COleVariant		dbVar;
	CListBox		*pList = ((CListBox *)(GetDlgItem(IDC_ROWSLIST)));

	// Update the parameters
	if (!UpdateData(TRUE))
		return;

	// This could take a while, 
	CWaitCursor wait;

	// Clear the list
	pList->ResetContent();


	// Following is a series of database table retrieves using variations
	// on the Recordset object. This isn't a great programming example,
	// but it shows each method clearly.
	
	// Execute each the requested read methods, recording a time for each
	try {
		// Open the database
		(GetDlgItem(IDC_DATABASENAME))->GetWindowText(m_strDatabase);
		m_dbDatabase = m_dbEngine.OpenDatabase( m_strDatabase,
			m_bExclusive, m_bReadOnly, m_strConnect);

		// Run through the selected methods, recording each time
		
		if (m_bOpenRecordset) {
			// Recordset as a Table
			if (m_bTable) {
				CdbRecordset RSetTable; 
				pList->AddString(_T("Recordset/Table"));
				pList->AddString(_T("=========================="));

				dwStart = timeGetTime();
		
				// Open recordset on a table
				try {
					RSetTable = 
						m_dbDatabase.OpenRecordset(m_strTableQuery, dbOpenTable);
				} catch(CdbException dbError) {

					// If the object was not found, assume it was something 
					// not openable as a "table"
					//
					if(dbError.m_hr != E_DAO_ObjectNotFound)
						throw dbError;
				}

				// Check that recordset was created
				if (RSetTable.Exists()) {

					// Get requested number of records
					for (lIndex = 0L; 
						!RSetTable.GetEOF() && lIndex < m_lNumRows; lIndex++) {

						// Get the first returned column
						dbVar = RSetTable.GetField(0L);
						AddFieldToList(lIndex, &dbVar);
			
						RSetTable.MoveNext();
					}
	
					// Report the estimated execute time (in milliseconds)
					dwEnd = timeGetTime();
					dwDuration = dwEnd - dwStart;
					DisplayQueryTime(IDC_TABLETIME, IDC_UNITTABLE, dwDuration);
				} else {
					(GetDlgItem(IDC_TABLETIME))->SetWindowText(_T("ERROR"));
				}
			}

			// Recordset as a Dynaset
			if(m_bDynaSet) {
				CdbRecordset RSetDyna; 
				pList->AddString(_T("Recordset/Dynaset"));
				pList->AddString(_T("=========================="));

				dwStart = timeGetTime();
		
				// Open recordset on as a Dynaset
				RSetDyna =
					m_dbDatabase.OpenRecordset(m_strTableQuery, dbOpenDynaset);

				// Check that recordset was created
				if (RSetDyna.Exists()) {

					// Get requested number of records
					for (lIndex = 0L; 
						!RSetDyna.GetEOF() && lIndex < m_lNumRows; lIndex++) {

						// Get the first returned column
						dbVar = RSetDyna.GetField(0L);
						AddFieldToList(lIndex, &dbVar);
						RSetDyna.MoveNext();
					}
	
					// Report the estimated execution time (in milliseconds)
					dwEnd = timeGetTime();
					dwDuration = dwEnd - dwStart;
					DisplayQueryTime(IDC_DYNASETTIME, IDC_UNITDYNA, dwDuration);

				} else {
					(GetDlgItem(IDC_DYNASETTIME))->SetWindowText(_T("ERROR"));
				}
			}

			// Recordset as a Dynaset with caching
			if(m_bDynaSet && m_bDynaSetCache) {
				CdbRecordset	RSetDynaCache; 
				CdbBookmark		DynaSetBookmark;

				pList->AddString(_T("Recordset/Dynaset cached"));
				pList->AddString(_T("=========================="));

				dwStart = timeGetTime();
		
				// Open recordset on as a Dynaset
				RSetDynaCache = 
					m_dbDatabase.OpenRecordset(m_strTableQuery, dbOpenDynaset);
				
				// Check that recordset was created
				if (RSetDynaCache.Exists()) {

					// Set the cache size to value supplied by user.
					RSetDynaCache.SetCacheSize(m_lCacheSize);
					RSetDynaCache.FillCache(); 
					
					// Get requested number of records
					for (lIndex = 0L; 
						!RSetDynaCache.GetEOF() && lIndex < m_lNumRows; lIndex++) {

						// Get the first returned column
						dbVar = RSetDynaCache.GetField(0L);
						AddFieldToList(lIndex, &dbVar);
						RSetDynaCache.MoveNext();

						//Watch for cache run-out
						if (lIndex % m_lCacheSize) {	
							DynaSetBookmark = RSetDynaCache.GetBookmark();
							RSetDynaCache.SetCacheStart(DynaSetBookmark);
							RSetDynaCache.FillCache(); 
						}
					}
	
					// Report the estimated execute time (in milliseconds)
					dwEnd = timeGetTime();
					dwDuration = dwEnd - dwStart;
					DisplayQueryTime(IDC_CACHETIME, IDC_UNITCACHE, dwDuration);
				} else {
					(GetDlgItem(IDC_CACHETIME))->SetWindowText(_T("ERROR"));
				}
			}			

			// Recordset as a Snapshot
			if(m_bSnapshot) {
				// Bidirectional Snapshot
				CdbRecordset RSetSnap; 
				pList->AddString(_T("Recordset/Snapshot"));
				pList->AddString(_T("=========================="));

				dwStart = timeGetTime();
		
				// Open recordset on as a Snapshot
				RSetSnap =
					m_dbDatabase.OpenRecordset(m_strTableQuery, dbOpenSnapshot);

				// Check that recordset was created
				if (RSetSnap.Exists()) {

					// Get requested number of records
					for (lIndex = 0L; 
						!RSetSnap.GetEOF() && lIndex < m_lNumRows; lIndex++) {
						// Get the first returned column
						dbVar = RSetSnap.GetField(0L);
						AddFieldToList(lIndex, &dbVar);
						RSetSnap.MoveNext();
					}
	
					// Report the estimated execute time (in milliseconds)
					dwEnd = timeGetTime();
					dwDuration = dwEnd - dwStart;
					DisplayQueryTime(IDC_SNAPSHOTTIME, IDC_UNITSNAP, dwDuration);

				} else {
					(GetDlgItem(IDC_SNAPSHOTTIME))->SetWindowText(_T("ERROR"));
				}

				// Forward Only snapshot
				CdbRecordset RSetSnapForward; 
				pList->AddString(_T("Recordset/Snapshot forward only"));
				pList->AddString(_T("=========================="));

				dwStart = timeGetTime();
		
				// Open recordset on as a Forward only Snapshot
				RSetSnapForward =  m_dbDatabase.OpenRecordset(m_strTableQuery, 
					dbOpenSnapshot, dbForwardOnly);

				// Check that recordset was created
				if (RSetSnapForward.Exists()) {
					// Get requested number of records
					for (lIndex = 0L; 
						!RSetSnapForward.GetEOF() && lIndex < m_lNumRows; lIndex++){

						// Get the first returned column
						dbVar = RSetSnapForward.GetField(0L);
						AddFieldToList(lIndex, &dbVar);
						RSetSnapForward.MoveNext();
					}
	
					// Report the estimated execute time (in milliseconds)
					dwEnd = timeGetTime();
					dwDuration = dwEnd - dwStart;
					DisplayQueryTime(IDC_FORWARDTIME, IDC_UNITSNAPF, dwDuration);
				} else {
					(GetDlgItem(IDC_FORWARDTIME))->SetWindowText(_T("ERROR"));
				}

			}

			// Getrows
			if (m_bGetRows) {
				CdbRecordset	RSetGetRows; 
				COleVariant		cRows; // Returned rows (in SafeArray)
				LONG				lActual;
				LONG				lGetRowsIndex[2];

				pList->AddString(_T("GetRows"));
				pList->AddString(_T("=========================="));

				dwStart = timeGetTime();
		
				// Open recordset on as a Forward only Snapshot
				RSetGetRows = m_dbDatabase.OpenRecordset(m_strTableQuery, 
					dbOpenSnapshot, dbForwardOnly);

				// Check that recordset was created
				if (RSetGetRows.Exists()) {
					cRows = RSetGetRows.GetRows(m_lNumRows); // get requested rows

					// Find out how many records were actually retrieved
					SafeArrayGetUBound(cRows.parray, 1, &lActual);
					if(lActual > m_lNumRows)
						lActual = m_lNumRows;

 					lGetRowsIndex[0] = 0L;

					for (lGetRowsIndex[1] = 0; 
						lGetRowsIndex[1] < lActual; lGetRowsIndex[1]++) {
			
						// Use OLE safe array function to access fields
						SafeArrayGetElement(cRows.parray,&lGetRowsIndex[0],&dbVar);
						AddFieldToList(lGetRowsIndex[1], &dbVar);
					}
	
					// Report the estimated execute time (in milliseconds)
					dwEnd = timeGetTime();
					dwDuration = dwEnd - dwStart;
					DisplayQueryTime(IDC_GETROWSTIME, IDC_UNITGETROWS, dwDuration);

				} else {
					(GetDlgItem(IDC_GETROWSTIME))->SetWindowText(_T("ERROR"));
				}
			}							
		}

		// Disconnect the database

	} catch (CdbException dbError) {
		CdbLastOLEError exError;
		TCHAR szBuf[256];

		wsprintf(szBuf, _T("Error %d : %s\n"), DBERR(dbError.m_hr), 
			(LPCTSTR) exError.GetDescription());
		AfxMessageBox(szBuf);
	}
}
