//////////////////
// Create new document
//
BOOL CDAOEMPDoc::OnNewDocument()
{
   if (!COleDocument::OnNewDocument())
      return FALSE;
   
   if(!ConnectToDatabase()) {
      m_bConnected = FALSE;
      return FALSE;
   }
   m_bConnected = TRUE;
   return TRUE;
}

////////////////
// When the document is created, connect to the database and open the
// Employee recordset.
//
BOOL CDAOEMPDoc::ConnectToDatabase()
{
   // Ask the user for the name of the EMPLOYEE database
   CFileDialog cOpenFile( TRUE,
      _T("MDB"), 
      _T("employee.mdb"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
      (_T("Access Files (*.mdb) | *.mdb ||")));

   // Get the location of database (assume it's the Employee example)
   cOpenFile.DoModal();

   //Open the database and the recordset
   try {
      // NOTE: Using default collection rather than Workspaces.Items
      m_cEmpDatabase = m_cDBEngine.OpenDatabase(cOpenFile.m_ofn.lpstrFile);
      m_cEmpRecordSet = m_cEmpDatabase.OpenRecordset(_T("Employees"));

   } catch (CdbException e) {
      CdbLastOLEError exError;
      TCHAR szBuf[256];

      wsprintf(szBuf, _T("Error %d : %s\n"), DBERR(e.m_hr), 
         (LPCTSTR) exError.GetDescription());
      AfxMessageBox(szBuf);
      return (FALSE);
   }
   return TRUE;;
}
