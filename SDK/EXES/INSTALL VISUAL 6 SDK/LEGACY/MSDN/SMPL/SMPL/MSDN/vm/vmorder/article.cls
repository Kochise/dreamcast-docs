VERSION 1.0 CLASS
BEGIN
  MultiUse = 0   'False
END
Attribute VB_Name = "Article"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "RVB_UniqueId" ,"3237F8CD024E"
'An article in stock, uniquely identified by an article
'number.

Option Base 0

'A unique article identifier. Also the article number used
'for identifying articles in stock.
'##ModelId=3237F8CD032E
Private pArticleId As Variant

'The name of the article. The name must not be unique but should describe the article.
'##ModelId=3237F8CD032F
Private pName As Variant

'The number of articles currently in stock.
'##ModelId=3237F8CD0330
Private pQuantity As Variant

'The price paid by a customer when ordering an item of the
'article.
'##ModelId=3237F8CD035C
Private pPrice As Variant

'The time for a producer to deliver backlogged items.
'##ModelId=3237F8CD035D
Private pDeliveryTime As Variant

'The number of items reserved for unfilled orders.
'##ModelId=3237F8CD035E
Private pBacklog As Variant

'A descriptive text of the article and its characteristics.
'##ModelId=3237F8CD0398
Private pDescription As Variant

'##ModelId=3237F8CB02D2
Private pStorage As Persistence

'##ModelId=3237F8CD0280
Public Sub Article(Id As Variant, Backlog As Variant, Delivery_Time As Variant, Description As Variant, Name As Variant, Price As Variant, Quantity As Variant)
    On Error GoTo Article_Article__exception
    pArticle_Id = Id
    pBacklog = Backlog
    pDeliveryTime = DeliveryTime
    pDescription = Description
    pName = Name
    pPrice = Price
    pQuantity = Quantity
    Exit Sub
Article_Article__exception:
    Resume Article_Article__end
Article_Article__end:
    Exit Sub
End Sub

'Fetches the article referenced article from the database.
'##ModelId=3237F8CD0288
Public Sub Fetch(Id As Variant)
    On Error GoTo Article_Fetch__exception
    Exit Sub
Article_Fetch__exception:
    Resume Article_Fetch__end
Article_Fetch__end:
    Exit Sub
End Sub

'A unique article identifier. Also the article number used
'for identifying articles in stock.
'##ModelId=3237F8CD028A
Public Property Get ArticleId() As Variant
    On Error GoTo Article_ArticleId__exception
    ArticleId = pArticleId
    Exit Property
Article_ArticleId__exception:
    Resume Article_ArticleId__end
Article_ArticleId__end:
    Exit Property
End Property

'A unique article identifier. Also the article number used for identifying articles in stock.
'##ModelId=3237F8CD028B
Public Property Let ArticleId(value As Variant)
    On Error GoTo Article_ArticleId__exception
    Let pArticleId = value
    Exit Property
Article_ArticleId__exception:
    Resume Article_ArticleId__end
Article_ArticleId__end:
    Exit Property
End Property

'The name of the article. The name must not be unique but
'should describe the article.
'##ModelId=3237F8CD02BC
Public Property Get Name() As Variant
    On Error GoTo Article_Name__exception
    Name = pName
    Exit Property
Article_Name__exception:
    Resume Article_Name__end
Article_Name__end:
    Exit Property
End Property

'The name of the article. The name must not be unique but should describe the article.
'##ModelId=3237F8CD02BD
Public Property Let Name(value As Variant)
    On Error GoTo Article_Name__exception
    Let pName = value
    Exit Property
Article_Name__exception:
    Resume Article_Name__end
Article_Name__end:
    Exit Property
End Property

'The number of articles currently in stock.
'##ModelId=3237F8CD02BF
Public Property Get Quantity() As Variant
    On Error GoTo Article_Quantity__exception
    Quantity = pQuantity
    Exit Property
Article_Quantity__exception:
    Resume Article_Quantity__end
Article_Quantity__end:
    Exit Property
End Property

'The number of articles currently in stock.
'##ModelId=3237F8CD02C0
Public Property Let Quantity(value As Variant)
    On Error GoTo Article_Quantity__exception
    Let pQuantity = value
    Exit Property
Article_Quantity__exception:
    Resume Article_Quantity__end
Article_Quantity__end:
    Exit Property
End Property

'The price paid by a customer when ordering an item of the
'article.
'##ModelId=3237F8CD02C2
Public Property Get Price() As Variant
    On Error GoTo Article_Price__exception
    Price = pPrice
    Exit Property
Article_Price__exception:
    Resume Article_Price__end
Article_Price__end:
    Exit Property
End Property

'The price paid by a customer when ordering an item of the
'article.
'##ModelId=3237F8CD02C3
Public Property Let Price(value As Variant)
    On Error GoTo Article_Price__exception
    Let pPrice = value
    Exit Property
Article_Price__exception:
    Resume Article_Price__end
Article_Price__end:
    Exit Property
End Property

'The time for a producer to deliver backlogged items.
'##ModelId=3237F8CD02EF
Public Property Get DeliveryTime() As Variant
    On Error GoTo Article_DeliveryTime__exception
    DeliveryTime = pDeliveryTime
    Exit Property
Article_DeliveryTime__exception:
    Resume Article_DeliveryTime__end
Article_DeliveryTime__end:
    Exit Property
End Property

'The time for a producer to deliver backlogged items.
'##ModelId=3237F8CD02F0
Public Property Let DeliveryTime(value As Variant)
    On Error GoTo Article_DeliveryTime__exception
    Let pDeliveryTime = value
    Exit Property
Article_DeliveryTime__exception:
    Resume Article_DeliveryTime__end
Article_DeliveryTime__end:
    Exit Property
End Property

'The number of items reserved for unfilled orders.
'##ModelId=3237F8CD02F2
Public Property Get Backlog() As Variant
    On Error GoTo Article_Backlog__exception
    Backlog = pBacklog
    Exit Property
Article_Backlog__exception:
    Resume Article_Backlog__end
Article_Backlog__end:
    Exit Property
End Property

'The number of items reserved for unfilled orders.
'##ModelId=3237F8CD02F3
Public Property Let Backlog(value As Variant)
    On Error GoTo Article_Backlog__exception
    Let pBacklog = value
    Exit Property
Article_Backlog__exception:
    Resume Article_Backlog__end
Article_Backlog__end:
    Exit Property
End Property

'A descriptive text of the article and its characteristics.
'##ModelId=3237F8CD02F5
Public Property Get Description() As Variant
    On Error GoTo Article_Description__exception
    Description = pDescription
    Exit Property
Article_Description__exception:
    Resume Article_Description__end
Article_Description__end:
    Exit Property
End Property

'A descriptive text of the article and its characteristics.
'##ModelId=3237F8CD032A
Public Property Let Description(value As Variant)
    On Error GoTo Article_Description__exception
    Let pDescription = value
    Exit Property
Article_Description__exception:
    Resume Article_Description__end
Article_Description__end:
    Exit Property
End Property

'##ModelId=3237F8CD032C
Private Sub Class_Initialize()
    On Error GoTo Article_Class_Initialize__exception
    Exit Sub
Article_Class_Initialize__exception:
    Resume Article_Class_Initialize__end
Article_Class_Initialize__end:
    Exit Sub
End Sub

'##ModelId=3237F8CD032D
Private Sub Class_Terminate()
    On Error GoTo Article_Class_Terminate__exception
    Exit Sub
Article_Class_Terminate__exception:
    Resume Article_Class_Terminate__end
Article_Class_Terminate__end:
    Exit Sub
End Sub

