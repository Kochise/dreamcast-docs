VERSION 1.0 CLASS
BEGIN
  MultiUse = 0   'False
END
Attribute VB_Name = "Customer"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "RVB_UniqueId" ,"3237F8CE00C3"
'A customer in our system identified with a customer id.

Option Base 0

'##ModelId=3237F8CE0132
Private pCustomerId As Variant

'##ModelId=3237F8CE0133
Private pName As Variant

'##ModelId=3237F8CE0134
Private pAddress As Variant

'##ModelId=3237F8CB02DB
Private pStorage As Persistence

'Creates a new customer and returns the customer id
'##ModelId=3237F8CE00C4
Public Function CreateNew(Customer_Name As String, Address As String) As Integer
    On Error GoTo Customer_CreateNew__exception
    Create_New = 0
    Exit Function
Customer_CreateNew__exception:
    Resume Customer_CreateNew__end
Customer_CreateNew__end:
    Exit Function
End Function

'Fetches a customer, from the database, given a customer id.
'##ModelId=3237F8CE00C7
Public Sub Fetch(Id As Integer)
    On Error GoTo Customer_Fetch__exception
    'Set the Article Id query parameter and get the customer
    pStorage.theQueryDef.Parameters!Id = Id
    pStorage.Execute
    If pStorage.RecordsExists Then
        Customer CustomerId:=pStorage.theRecordset!CustomerId, Name:=pStorage.theRecordset!Name, Address:=pStorage.theRecordset!Address
    Else
        Clear
    End If
    Exit Sub
Customer_Fetch__exception:
    Resume Customer_Fetch__end
Customer_Fetch__end:
    Exit Sub
End Sub

'Sets the properties and states for a customer.
'##ModelId=3237F8CE00C9
Public Sub Customer(CustomerId As Variant, Name As Variant, Address As Variant)
    On Error GoTo Customer_Customer__exception
    pCustomerId = CustomerId
    pName = Name
    pAddress = Address
    Exit Sub
Customer_Customer__exception:
    Resume Customer_Customer__end
Customer_Customer__end:
    Exit Sub
End Sub

'Clears the contents of the customer object.
'##ModelId=3237F8CE00FB
Public Sub Clear()
    On Error GoTo Customer_Clear__exception
    pCustomer_Id = 0
    pName = ""
    pAddress = ""
    Exit Sub
Customer_Clear__exception:
    Resume Customer_Clear__end
Customer_Clear__end:
    Exit Sub
End Sub

'##ModelId=3237F8CE00FC
Public Property Get CustomerId() As Variant
    On Error GoTo Customer_CustomerId__exception
    CustomerId = pCustomerId
    Exit Property
Customer_CustomerId__exception:
    Resume Customer_CustomerId__end
Customer_CustomerId__end:
    Exit Property
End Property

'##ModelId=3237F8CE00FD
Public Property Get Name() As Variant
    On Error GoTo Customer_Name__exception
    Name = pName
    Exit Property
Customer_Name__exception:
    Resume Customer_Name__end
Customer_Name__end:
    Exit Property
End Property

'##ModelId=3237F8CE00FE
Public Property Let Name(value As Variant)
    On Error GoTo Customer_Name__exception
    pName = value
    Exit Property
Customer_Name__exception:
    Resume Customer_Name__end
Customer_Name__end:
    Exit Property
End Property

'##ModelId=3237F8CE012D
Public Property Get Address() As Variant
    On Error GoTo Customer_Address__exception
    Address = pAddress
    Exit Property
Customer_Address__exception:
    Resume Customer_Address__end
Customer_Address__end:
    Exit Property
End Property

'##ModelId=3237F8CE012E
Public Property Let Address(value As Variant)
    On Error GoTo Customer_Address__exception
    pAddress = value
    Exit Property
Customer_Address__exception:
    Resume Customer_Address__end
Customer_Address__end:
    Exit Property
End Property

'##ModelId=3237F8CE0130
Private Sub Class_Initialize()
    On Error GoTo Customer_Class_Initialize__exception
    Set pStorage = New Persistence
    pStorage.Connect ("Query_Customer")
    Exit Sub
Customer_Class_Initialize__exception:
    Resume Customer_Class_Initialize__end
Customer_Class_Initialize__end:
    Exit Sub
End Sub

'##ModelId=3237F8CE0131
Private Sub Class_Terminate()
    On Error GoTo Customer_Class_Terminate__exception
    Set pStorage = Nothing
    Exit Sub
Customer_Class_Terminate__exception:
    Resume Customer_Class_Terminate__end
Customer_Class_Terminate__end:
    Exit Sub
End Sub

