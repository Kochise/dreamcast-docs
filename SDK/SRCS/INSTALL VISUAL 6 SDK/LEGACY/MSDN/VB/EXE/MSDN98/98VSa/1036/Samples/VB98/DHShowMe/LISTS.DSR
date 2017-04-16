VERSION 5.00
Begin {90290CCD-F27D-11D0-8031-00C04FB6C701} Lists 
   ClientHeight    =   6975
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   7425
   _ExtentX        =   13097
   _ExtentY        =   12303
   SourceFile      =   "Lists.htm"
   BuildFile       =   "Lists.htm"
   BuildMode       =   0
   TypeLibCookie   =   340
   AsyncLoad       =   0   'False
   id              =   "DHTMLPage4"
   ShowBorder      =   0   'False
   ShowDetail      =   0   'False
   AbsPos          =   0   'False
End
Attribute VB_Name = "Lists"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Private Function AddtolList_onclick() As Boolean
    Dim e As HTMLOptionElement
    Set e = Document.createElement("OPTION")
    e.Text = TextField1.Value
    e.Value = "ListItemValue"
    List1.Options.Add e
    TextField1.Value = ""
    
End Function
