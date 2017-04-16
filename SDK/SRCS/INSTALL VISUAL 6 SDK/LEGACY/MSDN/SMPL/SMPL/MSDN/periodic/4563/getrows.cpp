////////////////////////////////////////////////////////////////
// (From DAO GETROWS sample)
// Perform standard GetRows against the Employee table
//
void CGetRowsDlg::DoGetRows() 
{
   COleVariant    cRows;
   COleVariant    varField;
   CString        strLBRow;
   TCHAR          szId[16];
   LONG           lNumRecords;
   LONG           lIndex[2];
   HRESULT        hResult;
   CListBox       *pListBox = (CListBox *)GetDlgItem(IDD_GETROWSLIST);

   // Perform GetRows on Employee table
   // This GetRows uses VARIANTS
   // Arbitrarily get MAX_EMP_REC rows
   cRows = m_cEmpRecordSet.GetRows(MAX_EMP_REC); 

   // Find out how many records were actually retrieved
   // (NOTE: SafeArrays are 1-based)
   //
   SafeArrayGetUBound(cRows.parray, 2, &lNumRecords);

   // Clear the listbox
   pListBox->ResetContent();
   
   for (lIndex[1] = 0; lIndex[1] <= lNumRecords; lIndex[1]++) {
      strLBRow.Empty();    // Clear the string

      lIndex[0] = EMP_ID;  // Employee ID
         
      // Use OLE safe array function to access fields
      hResult = SafeArrayGetElement(cRows.parray, &lIndex[0], &varField);

      // Watch out for bum variants
      if(FAILED(hResult))
         break;

      if(varField.vt == VT_I4) {    // Gotta be a long 
         wsprintf(szId, _T("%d,  "), varField.iVal);
      } else {
         lstrcpy(szId, _T("Unexpected Data Type"));
      }

      strLBRow += (LPCTSTR)szId;

      // Get last name
      lIndex[0] = EMP_LNAME;
      SafeArrayGetElement(cRows.parray, &lIndex[0], &varField);
      strLBRow += (LPCTSTR)varField.bstrVal;

      // Get first name
      strLBRow += _T(", ");
      lIndex[0] = EMP_FNAME;
      SafeArrayGetElement(cRows.parray, &lIndex[0], &varField);
      strLBRow += (LPCTSTR)varField.bstrVal;

      pListBox->AddString(strLBRow);
   }
}
