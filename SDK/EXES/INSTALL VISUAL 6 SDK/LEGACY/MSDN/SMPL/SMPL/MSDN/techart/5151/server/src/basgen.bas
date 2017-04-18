Attribute VB_Name = "basGen"
Option Explicit

' GenEng Public Constants
Public Const scTagOpen = "<!"
Public Const scTagClose = "!>"
Public Const scNotNull = "NOT NULL"
Public Const scIsNull = "NULL"
Public Const scIsFK = "REFERENCES    <!TbName!>(PKId)"
Public Const scMask = "CHECK (<!TbMask!>)"
Public Const scDefault = "DEFAULT <!TbDefault!>"
Public Const scUpdDate = "getdate()"
Public Const scUpdUser = "HOST_NAME()"
Public Const scDomain = ",Descr      varchar(50)  NOT NULL" & vbCrLf & _
                        "     ,Code       char(7)      NOT NULL"
Public Const scMaskChk = "IF NOT (@<!TbMask!>)" & vbCrLf & _
                         "BEGIN" & vbCrLf & _
                         "    RAISERROR('<!TbMaskErr!>',1,2)" & vbCrLf & _
                         "    SELECT -200" & vbCrLf & _
                         "    RETURN -200" & vbCrLf & _
                         "End"

'SQL
Public Const scEntQry = "SELECT AllEntities.* FROM AllEntities WHERE AllEntities.EntPKId = "
Public Const scAttribQry = "SELECT Attribute.PKId FROM Attribute WHERE Attribute.EntityId = "
Public Const scAttribLangQry = "SELECT AttribLang.* FROM AttribLang WHERE AttribLang.AttribPKId = "

Sub main()

End Sub
