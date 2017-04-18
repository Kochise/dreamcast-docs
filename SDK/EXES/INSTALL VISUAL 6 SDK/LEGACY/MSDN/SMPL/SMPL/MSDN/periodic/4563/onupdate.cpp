void CDAOEMPView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
   CDAOEMPDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   try {
		// Employee number/ID
      m_nEmpNum = 
         VTOLONG(pDoc->m_cEmpRecordSet.Fields[EMP_EMPLOYEE_ID].GetValue());
      
      // Convert the variant strings into CStrings
      VarToCStr(&m_strFirstName, 
         &pDoc->m_cEmpRecordSet.Fields[EMP_FIRST_NAME].GetValue());
      VarToCStr(&m_strHomePhone, 
         &pDoc->m_cEmpRecordSet.Fields[EMP_HOME_PHONE].GetValue());
      VarToCStr(&m_strLastName,  
         &pDoc->m_cEmpRecordSet.Fields[EMP_LAST_NAME].GetValue());
      VarToCStr(&m_strNotes,     
         &pDoc->m_cEmpRecordSet.Fields[EMP_NOTES].GetValue());

      // Hire date is a COleDateTime 
      m_HireDate = pDoc->m_cEmpRecordSet.Fields[EMP_HIRE_DATE].GetValue();

   } catch (CdbException e) {
      CdbLastOLEError exError;
      TCHAR szBuf[256];

      wsprintf(szBuf, _T("Error %d : %s\n"), 
         DBERR(e.m_hr), (LPCTSTR) exError.GetDescription());
      AfxMessageBox(szBuf);
   }
   UpdateData(FALSE);   // Invoke DDX (copy member data to form controls)
   Invalidate();        // Tell Windows to repaint
}
