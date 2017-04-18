VERSION 1.0 CLASS
BEGIN
  MultiUse = 0   'False
END
Attribute VB_Name = "OrderRow"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "RVB_UniqueId" ,"3237F8CE0054"
'The article and quantity as part of an order.

Option Base 0

'##ModelId=3237F8CC0221
Private pArticle As Article

'##ModelId=3237F8CE00C2
Private pQuantity As Variant

'Calculates the sum of this order row.
'##ModelId=3237F8CE0055
Public Property Get Sum() As Currency
    On Error GoTo OrderRow_Sum__exception
    Sum = Quantity * Article.Price
    Exit Property
OrderRow_Sum__exception:
    Resume OrderRow_Sum__end
OrderRow_Sum__end:
    Exit Property
End Property

'Creates an order row and opens a dialog where the end user
'can order articles in quantity.
'##ModelId=3237F8CE0056
Public Function Create() As Boolean
    On Error GoTo OrderRow_Create__exception
    'Open the order row form and edit the new order row.
    dlg_OrderRow.Edit Me
    'Check for quantity
    If Quantity > 0 Then
        'OK clicked with a nonzero quantity
        Create = True
    Else
        'Cancel clicked
        Create = False
    End If
    Exit Function
OrderRow_Create__exception:
    Resume OrderRow_Create__end
OrderRow_Create__end:
    Exit Function
End Function

'Edit an existing orderrow.
'##ModelId=3237F8CE008C
Public Sub Edit()
    On Error GoTo OrderRow_Edit__exception
    Exit Sub
OrderRow_Edit__exception:
    Resume OrderRow_Edit__end
OrderRow_Edit__end:
    Exit Sub
End Sub

'The clear operation resets the state of en orderrow to
'empty.
'##ModelId=3237F8CE008D
Public Sub Clear()
    On Error GoTo OrderRow_Clear__exception
    Exit Sub
OrderRow_Clear__exception:
    Resume OrderRow_Clear__end
OrderRow_Clear__end:
    Exit Sub
End Sub

'##ModelId=3237F8CE008E
Public Property Get Article() As Article
    On Error GoTo OrderRow_Article__exception
    Set Article = pArticle
    Exit Property
OrderRow_Article__exception:
    Resume OrderRow_Article__end
OrderRow_Article__end:
    Exit Property
End Property

'##ModelId=3237F8CE008F
Public Property Set Article(value As Article)
    On Error GoTo OrderRow_Article__exception
    Set pArticle = value
    Exit Property
OrderRow_Article__exception:
    Resume OrderRow_Article__end
OrderRow_Article__end:
    Exit Property
End Property

'##ModelId=3237F8CE0091
Public Property Get Quantity() As Variant
    On Error GoTo OrderRow_Quantity__exception
    Quantity = pQuantity
    Exit Property
OrderRow_Quantity__exception:
    Resume OrderRow_Quantity__end
OrderRow_Quantity__end:
    Exit Property
End Property

'##ModelId=3237F8CE00BE
Public Property Let Quantity(value As Variant)
    On Error GoTo OrderRow_Quantity__exception
    pQuantity = value
    Exit Property
OrderRow_Quantity__exception:
    Resume OrderRow_Quantity__end
OrderRow_Quantity__end:
    Exit Property
End Property

'##ModelId=3237F8CE00C0
Private Sub Class_Initialize()
    On Error GoTo OrderRow_Class_Initialize__exception
    Exit Sub
OrderRow_Class_Initialize__exception:
    Resume OrderRow_Class_Initialize__end
OrderRow_Class_Initialize__end:
    Exit Sub
End Sub

'##ModelId=3237F8CE00C1
Private Sub Class_Terminate()
    On Error GoTo OrderRow_Class_Terminate__exception
    Exit Sub
OrderRow_Class_Terminate__exception:
    Resume OrderRow_Class_Terminate__end
OrderRow_Class_Terminate__end:
    Exit Sub
End Sub

