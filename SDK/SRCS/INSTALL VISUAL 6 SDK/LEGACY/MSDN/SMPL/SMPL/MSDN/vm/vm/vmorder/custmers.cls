VERSION 1.0 CLASS
BEGIN
  MultiUse = 0   'False
END
Attribute VB_Name = "Customers"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "RVB_UniqueId" ,"3237F8CE0135"
'A set of items restored from the database.
'Customers objects are based on a database table or dynaset
'and a stored query definition:
'"PARAMETERS...; SELECT * FROM ... WHERE ... "

Option Base 0

'##ModelId=3237F8CB02D8
Private pStorage As Persistence

'Returns the an item from the set.
'Index syntax.
' <nothing> = Returns the current item
' Number = Returns the item indexed by number.   Range:
'1..Count.
'##ModelId=3237F8CE0168
Public Function Item(Optional index As Variant) As Customer
    On Error GoTo Customers_Item__exception
    If Not IsMissing(index) Then
        pStorage.theRecordset.AbsolutePosition = index - 1
    End If
    'Allocate and return the current object
    Dim New_Customer As New Customer
    New_Customer.Customer CustomerId:=pStorage.theRecordset!Customer_Id, Name:=pStorage.theRecordset!Name, Address:=pStorage.theRecordset!Address
    Set Item = New_Customer
    Exit Function
Customers_Item__exception:
    Resume Customers_Item__end
Customers_Item__end:
    Exit Function
End Function

'Returns the number of items in the set.
'##ModelId=3237F8CE016A
Public Property Get Count() As Long
    On Error GoTo Customers_Count__exception
    If pStorage.RecordsExists Then
        pStorage.theRecordset.MoveLast
        Count = pStorage.theRecordset.RecordCount
    Else
        Count = 0
    End If
    Exit Property
Customers_Count__exception:
    Resume Customers_Count__end
Customers_Count__end:
    Exit Property
End Property

'Sets the criterion for fetching a set of items.
'##ModelId=3237F8CE016B
Public Sub Fetch(Optional Id As Variant, Optional Name As Variant)
    On Error GoTo Customers_Fetch__exception
    'Set the Customer_Id query parameter
    If Not IsMissing(Id) Then
        pStorage.theQueryDef.Parameters!Id = Id
    Else
        pStorage.theQueryDef.Parameters!Id = "*"
    End If
    'Set the Name query parameter
    If Not IsMissing(Name) Then
        pStorage.theQueryDef.Parameters!Name = Name
    Else
        pStorage.theQueryDef.Parameters!Name = "*"
    End If
    pStorage.Execute
    Exit Sub
Customers_Fetch__exception:
    Resume Customers_Fetch__end
Customers_Fetch__end:
    Exit Sub
End Sub

'Returns the previous item from the set.
'##ModelId=3237F8CE019C
Public Function MovePrevious() As Customer
    On Error GoTo Customers_MovePrevious__exception
    If pStorage.RecordsExists Then
        'Move to the previous item in the recordset
        pStorage.theRecordset.MovePrevious
        'Return the current customer by calling the Item method
        Set MovePrevious = Item
    End If
    Exit Function
Customers_MovePrevious__exception:
    Resume Customers_MovePrevious__end
Customers_MovePrevious__end:
    Exit Function
End Function

'Returns the next item from the set.
'##ModelId=3237F8CE019D
Public Function MoveNext() As Customer
    On Error GoTo Customers_MoveNext__exception
    If pStorage.RecordsExists And Not pStorage.theRecordset.EOF Then
        'Move to the next item in the recordset
        pStorage.theRecordset.MoveNext
        'Return the current customer by calling the Item method
        Set MoveNext = Item
    End If
    Exit Function
Customers_MoveNext__exception:
    Resume Customers_MoveNext__end
Customers_MoveNext__end:
    Exit Function
End Function

'Returns the first item from the set.
'##ModelId=3237F8CE019E
Public Function MoveFirst() As Customer
    On Error GoTo Customers_MoveFirst__exception
    If pStorage.RecordsExists Then
        'Move to the first item in the recordset
        pStorage.theRecordset.MoveFirst
        'Return the current customer by calling the Item method
        Set MoveFirst = Item
    End If
    Exit Function
Customers_MoveFirst__exception:
    Resume Customers_MoveFirst__end
Customers_MoveFirst__end:
    Exit Function
End Function

'Returns true when the last customer is indexed.
'##ModelId=3237F8CE019F
Public Function Last() As Boolean
    On Error GoTo Customers_Last__exception
    If pStorage.RecordsExists Then
        Last = pStorage.theRecordset.EOF
    Else
        Last = True
    End If
    Exit Function
Customers_Last__exception:
    Resume Customers_Last__end
Customers_Last__end:
    Exit Function
End Function

'##ModelId=3237F8CE01A0
Private Sub Class_Initialize()
    On Error GoTo Customers_Class_Initialize__exception
    'Setup the persistence object
    Set pStorage = New Persistence
    pStorage.Connect ("Query_Customers")
    Exit Sub
Customers_Class_Initialize__exception:
    Resume Customers_Class_Initialize__end
Customers_Class_Initialize__end:
    Exit Sub
End Sub

'##ModelId=3237F8CE01A1
Private Sub Class_Terminate()
    On Error GoTo Customers_Class_Terminate__exception
    Set pStorage = Nothing
    Exit Sub
Customers_Class_Terminate__exception:
    Resume Customers_Class_Terminate__end
Customers_Class_Terminate__end:
    Exit Sub
End Sub

