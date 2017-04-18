Sub SetDate()
	dim db as database, rs as Recordset
   dim vBkmk as variant
   on error goto lblErrorHndlr
   set db = OpenDatabase("employees.mdb")
   set rs = db.OpenRecordset("employees", dbOpenDynaset)
   vBkmk = rs.bookmark
   rs.FindFirst "[Hire Date] < #10/10/1990#"
   do while rs.nomatch = False
     rs.edit
     rs![Hire Date] = #10/10/1990#
     rs.update
     rs.FindFirst "[Hire Date] < #10/10/1990#"
   loop
   rs.bookmark = vBkmk
   rs.Close
   db.Close
lblQuit:
   exit sub
lblErrorHndlr:
   if (dbengine.errors.count <> 0) then
     msgbox dbengine.Errors(0).Description
   else
     msgbox "Unexpected Error"
   endif
   resume lblQuit
end sub



