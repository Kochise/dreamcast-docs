////////////////
// Update the current record
//
void CDAOEMPDoc::UpdateEmpRec(long m_nEmpNum, LPCTSTR lpszFirstName, 
   LPCTSTR lpszHomePhone, LPCTSTR lpszLastName, 
   LPCTSTR lpszNotes, DATE HireDate)
{
   // Convert the date to a dbVariant
   COleVariant cdbHireDate;
   cdbHireDate.date = HireDate;
   cdbHireDate.vt = VT_DATE;

   try {
      // The recordset must be in edit mode
      if(m_cEmpRecordSet.GetEditMode() == dbEditNone)
         m_cEmpRecordSet.Edit();

      m_cEmpRecordSet.SetField(EMP_FIRST_NAME, 
         COleVariant(lpszFirstName, VT_BSTRT));
      m_cEmpRecordSet.SetField(EMP_HOME_PHONE, 
         COleVariant(lpszHomePhone, VT_BSTRT));
      m_cEmpRecordSet.SetField(EMP_LAST_NAME, 
         COleVariant(lpszLastName, VT_BSTRT));
      m_cEmpRecordSet.SetField(EMP_NOTES, 
         COleVariant(lpszNotes, VT_BSTRT));
      m_cEmpRecordSet.SetField(EMP_HIRE_DATE, cdbHireDate);

      // Commit the changes
      m_cEmpRecordSet.Update();

      // Return to the edited record
      CdbBookmark cBookmark = m_cEmpRecordSet.GetLastModified();
      m_cEmpRecordSet.SetBookmark(cBookmark);

   } catch (CdbException e) {
      CdbLastOLEError exError;
      TCHAR szBuf[256];

      wsprintf(szBuf, _T("Error 0x%lx : %s\n"), e.m_hr, 
         (LPCTSTR)exError.GetDescription());
      AfxMessageBox(szBuf);
   }
}
