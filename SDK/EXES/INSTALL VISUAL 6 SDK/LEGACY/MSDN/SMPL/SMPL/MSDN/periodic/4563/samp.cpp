void SetDate(void)
{
	CdbDBEngine dben;
	CdbDatabase db;
	CdbRecordset rs;
	CdbBookmark bk;
	COleDateTime dt;
	try {
		db = dben[0L].OpenDatabase(_T("employees.mdb"));
		rs = db.OpenRecordset(_T("employees"));
		bk = rs.GetBookmark();
		rs.FindFirst(_T("[Hire Date] < #10/10/1990#"));
		while (rs.GetNoMatch() == FALSE) {
			rs.Edit();
			rs.SetValue(_T("[Hire Date]"), COleDateTime(1990, 10, 10, 0, 0, 0));
			rs.Update();
			rs.FindFirst(_T("[Hire Date] < #10/10/1990#"));
		}
		rs.SetBookmark(bk);
		rs.Close();
		db.Close();

	} catch(CdbException e) {
		if (dben.Errors.GetCount() != 0)
			MessageBox(NULL, dben.Errors[0L].GetDescription(), NULL, 0);
		else
			MessageBox(NULL, _T("Unexpected Error"), NULL, 0);
	}
}
