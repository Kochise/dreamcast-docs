VERSION 1.0 CLASS
BEGIN
  MultiUse = 0   'False
END
Attribute VB_Name = "Articles"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "RVB_UniqueId" ,"3237F8CD0399"
'A set of articles restored from the article database.
'Articles objects are based on the database table
'"tbl_article" and the "query_articles" stored query
'definition:
'"PARAMETERS [ArticleId] TEXT, [Name] TEXT; SELECT * FROM
'tbl_article WHERE article_id LIKE [ArticleId] AND name"

Option Base 0

'##ModelId=3237F8CB02D5
Private pStorage As Persistence

'Returns the an article from the set.
'Index syntax.
' <nothing> = Returns the current article
' Number = Returns the article indexed by number.  Range:
'1..Count
'##ModelId=3237F8CD039A
Public Function Item(Optional index As Variant) As Article
    On Error GoTo Articles_Item__exception
    'Move to the indexed position
    'Note: Item is indexed 1..Count, Recordset is indexed 0..Count-1
    If Not IsMissing(index) Then
        pStorage.theRecordset.AbsolutePosition = index - 1
    End If
    'Allocate and return the current article object
    Set Item = New Article
    Item.Article Id:=pStorage.theRecordset!Article_Id, Backlog:=pStorage.theRecordset!Backlog, Delivery_Time:=pStorage.theRecordset!Delivery_Time, Description:=pStorage.theRecordset!Description, Name:=pStorage.theRecordset!Name, Price:=pStorage.theRecordset!Price, Quantity:=pStorage.theRecordset!Quantity
    Exit Function
Articles_Item__exception:
    Resume Articles_Item__end
Articles_Item__end:
    Exit Function
End Function

'Returns the number of items in the set.
'##ModelId=3237F8CD039C
Public Property Get Count() As Long
    On Error GoTo Articles_Count__exception
    If pStorage.RecordsExists Then
        pStorage.theRecordset.MoveLast
        Count = pStorage.theRecordset.RecordCount
    Else
        Count = 0
    End If
    Exit Property
Articles_Count__exception:
    Resume Articles_Count__end
Articles_Count__end:
    Exit Property
End Property

'Sets the criterion for fetching a set of articles.
'Id Syntax:
'  ignore or "*" for all.
'  "100-*" for all articles in the "100" group.
'Name Syntax:
'  ignore or  "*" for all.
'  "S*" for all articles starting with "S".
'##ModelId=3237F8CD039D
Public Sub Fetch(Optional Id As Variant, Optional Name As Variant)
    On Error GoTo Articles_Fetch__exception
    'Set the Article Id query parameter
    If Not IsMissing(Id) Then
        pStorage.theQueryDef.Parameters!ArticleId = Id
    Else
        pStorage.theQueryDef.Parameters!ArticleId = "*"
    End If
    'Set the Name query parameter
    If Not IsMissing(Name) Then
        pStorage.theQueryDef.Parameters!Name = Name
    Else
        pStorage.theQueryDef.Parameters!Name = "*"
    End If
    pStorage.Execute
    Exit Sub
Articles_Fetch__exception:
    Resume Articles_Fetch__end
Articles_Fetch__end:
    Exit Sub
End Sub

'Returns the previous article from the set.
'##ModelId=3237F8CD03A0
Public Function MovePrevious() As Article
    On Error GoTo Articles_MovePrevious__exception
    If pStorage.RecordsExists Then
        'Move to the previous item in the recordset
        pStorage.theRecordset.MovePrevious
        'Return the current article by calling the Item method
        Set MovePrevious = Item
    End If
    Exit Function
Articles_MovePrevious__exception:
    Resume Articles_MovePrevious__end
Articles_MovePrevious__end:
    Exit Function
End Function

'Returns the next article from the set.
'##ModelId=3237F8CD03A1
Public Function MoveNext() As Article
    On Error GoTo Articles_MoveNext__exception
    If pStorage.RecordsExists And Not pStorage.theRecordset.EOF Then
        'Move to the next item in the recordset
        pStorage.theRecordset.MoveNext
        'Return the current article by calling the Item method
        Set MoveNext = Item
    End If
    Exit Function
Articles_MoveNext__exception:
    Resume Articles_MoveNext__end
Articles_MoveNext__end:
    Exit Function
End Function

'Returns the first article from the set.
'##ModelId=3237F8CD03CA
Public Function MoveFirst() As Article
    On Error GoTo Articles_MoveFirst__exception
    If pStorage.RecordsExists Then
        'Move to the first item in the recordset
        pStorage.theRecordset.MoveFirst
        'Return the current article by calling the Item method
        Set MoveFirst = Item
    End If
    Exit Function
Articles_MoveFirst__exception:
    Resume Articles_MoveFirst__end
Articles_MoveFirst__end:
    Exit Function
End Function

'##ModelId=3237F8CD03CB
Private Sub Class_Initialize()
    On Error GoTo Articles_Class_Initialize__exception
    'Setup the persistence object
    Set pStorage = New Persistence
    pStorage.Connect ("Query_Articles")
    Exit Sub
Articles_Class_Initialize__exception:
    Resume Articles_Class_Initialize__end
Articles_Class_Initialize__end:
    Exit Sub
End Sub

'##ModelId=3237F8CD03CC
Private Sub Class_Terminate()
    On Error GoTo Articles_Class_Terminate__exception
    Set pStorage = Nothing
    Exit Sub
Articles_Class_Terminate__exception:
    Resume Articles_Class_Terminate__end
Articles_Class_Terminate__end:
    Exit Sub
End Sub

