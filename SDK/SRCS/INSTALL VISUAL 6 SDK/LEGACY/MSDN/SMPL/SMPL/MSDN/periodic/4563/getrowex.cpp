////////////////////////////////////////////////////////////////
// (From MSDEV\DAOSDK\SAMPLES\GETROWS)
// Structure for GetRowsEx
//

// struct to receive one row of Employee data
typedef struct {
   LONG  lEmpId;
   TCHAR *strLastName;
   TCHAR strFirstName[20];
} EMP, *LPEMP;

// Employee table binding 
DAORSETBINDING Bindings[] = 
{
   // { Index Type,  Column,     Type,             Offset,  Size }

   {dbBindIndexINT,  EMP_ID,     dbBindI4,         offsetof(EMP,lEmpId), 
      sizeof(LONG)},
   {dbBindIndexINT,  EMP_LNAME,  dbBindLPSTRING,   offsetof(EMP,strLastName),
      sizeof(TCHAR *)},
   {dbBindIndexINT,  EMP_FNAME,  dbBindSTRING,     offsetof(EMP,strFirstName),
      sizeof(TCHAR) * 20 }
};

////////////////
// Perform C++ GetRowsEx against the Employee table
//
void CGetRowsDlg::DoGetRowsEx() 
{
   LPEMP       pEmpRows = new EMP[MAX_EMP_REC];
   CListBox    *pListBox = (CListBox *)GetDlgItem(IDD_GETROWSLISTEX);
   CString     strLBRow;
   TCHAR       szId[16];
   LONG        lNumRecords;
   LONG        lCount;
   TCHAR       pBuf[MAX_EMP_REC * 15];    // allow average of 15 chars/name

   // Perform GetRows on Employee table
   // This GetRows uses a specific C++ structure
   try {
      lNumRecords = m_cEmpRecordSet.GetRowsEx(pEmpRows, sizeof(EMP),
         &Bindings[0], sizeof(Bindings) / sizeof(DAORSETBINDING),
         pBuf, sizeof(pBuf),
         MAX_EMP_REC); //arbitrarily get MAX_EMP_REC rows

   } catch (CdbException e) {
      // Differentiate between GetRowsEx Errors and other CdbExceptions
      // see defines in DAOGETRW.H
      if( e.m_hr == E_ROWTOOSHORT ||
          e.m_hr == E_BADBINDINFO ||         
          e.m_hr == E_COLUMNUNAVAILABLE ) {
         AfxMessageBox(_T("Error in GetRowsEx call."));
      } else {
         AfxMessageBox(_T("General CdbException"));
      }
      delete [] pEmpRows;
      return;
   }

   // Step through the returned rows 
   for (lCount = 0; lCount < lNumRecords; lCount++) {
      strLBRow.Empty();
      wsprintf(szId, _T("%d,  "), pEmpRows[lCount].lEmpId);
      strLBRow += szId;
      strLBRow += pEmpRows[lCount].strLastName;
      strLBRow += _T(", ");
      strLBRow += (LPCTSTR) pEmpRows[lCount].strFirstName;
      pListBox->AddString(strLBRow);
   }
   delete [] pEmpRows;
}
