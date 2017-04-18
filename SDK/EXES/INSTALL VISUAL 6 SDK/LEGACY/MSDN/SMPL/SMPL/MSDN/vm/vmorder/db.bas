Attribute VB_Name = "Db"
Attribute VB_Ext_KEY = "RVB_UniqueId" ,"3237F8CE0352"
'Stores the tables:
'tbl_customer
'tbl_article
'tbl_order
'tbl_order_row

Option Base 0

'##ModelId=3237F8CB0304
Public OrderSys_Db As Database

'Opens the named database and returns a boolean success
'value.
'##ModelId=3237F8CE0353
Public Function Db_Open(database_name As String) As Integer
    On Error GoTo Db_Db_Open__exception
    Set OrderSys_Db = Workspaces(0).OpenDatabase(App.Path & "\ordersys.mdb")
    Db_Open = True
    Exit Function
    Exit Function
Db_Db_Open__exception:
    Resume Db_Db_Open__end
Db_Db_Open__end:
    Exit Function
End Function

'##ModelId=3237F8CE0355
Public Function Db_Table_Article() As Recordset
    On Error GoTo Db_Db_Table_Article__exception
    Set Db_Table_Article = OrderSys_Db.OpenRecordset("tbl_article", dbOpenDynaset)
    Exit Function
Db_Db_Table_Article__exception:
    Resume Db_Db_Table_Article__end
Db_Db_Table_Article__end:
    Exit Function
End Function

'##ModelId=3237F8CE0356
Public Function Db_Table_Orderrow() As Recordset
    On Error GoTo Db_Db_Table_Orderrow__exception
    Exit Function
Db_Db_Table_Orderrow__exception:
    Resume Db_Db_Table_Orderrow__end
Db_Db_Table_Orderrow__end:
    Exit Function
End Function

'##ModelId=3237F8CE0357
Public Function Db_Table_Order() As Recordset
    On Error GoTo Db_Db_Table_Order__exception
    Exit Function
Db_Db_Table_Order__exception:
    Resume Db_Db_Table_Order__end
Db_Db_Table_Order__end:
    Exit Function
End Function

'##ModelId=3237F8CE0358
Public Function Db_Table_Customer() As Recordset
    On Error GoTo Db_Db_Table_Customer__exception
    Set Db_Table_Customer = OrderSys_Db.OpenRecordset("tbl_customer", dbOpenDynaset)
    Exit Function
Db_Db_Table_Customer__exception:
    Resume Db_Db_Table_Customer__end
Db_Db_Table_Customer__end:
    Exit Function
End Function

