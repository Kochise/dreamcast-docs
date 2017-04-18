VERSION 5.00
Begin {90290CCD-F27D-11D0-8031-00C04FB6C701} EventBub 
   ClientHeight    =   6975
   ClientLeft      =   1815
   ClientTop       =   1545
   ClientWidth     =   7425
   _ExtentX        =   13097
   _ExtentY        =   12303
   SourceFile      =   "EventBub.htm"
   BuildFile       =   "EventBub.htm"
   BuildMode       =   0
   TypeLibCookie   =   780
   AsyncLoad       =   0   'False
   id              =   "DHTMLPage1"
   ShowBorder      =   -1  'True
   ShowDetail      =   -1  'True
   AbsPos          =   0   'False
End
Attribute VB_Name = "EventBub"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Private Function EventArea_onclick() As Boolean
' Se la trasmissione gerarchica degli eventi è attivata
' e l'utente fa clic sul pulsante, questa routine di eventi
' verrà generata dopo la routine "TheButton_onclick". Il codice
' di questa routine modifica il colore dello sfondo dell'intera
' pagina impostandolo su  "wheat".
    Document.bgColor = "wheat"
End Function

Private Sub HTMLPage_Load()
' Imposta durante il caricamento il valore del pulsante di
' opzione in modo da disattivare la trasmissione gerarchica
' degli eventi.
    bubble.Checked = False
    nobubble.Checked = True
    
End Sub

Private Function TheButton_onclick() As Boolean
' Determina se la trasmissione gerarchica degli eventi è attivata
' o meno. La prima operazione eseguita è la modifica del colore del pulsante
' stesso. Se la trasmissione gerarchica degli eventi è attivata,
' l'evento viene trasmesso fino al tag DIV EventArea. In caso contrario,
' la trasmissione viene interrotta.
    If bubble.Checked = True Then
        TheButton.Style.backgroundColor = "slateblue"
    ElseIf nobubble.Checked = True Then
        TheButton.Style.backgroundColor = "slateblue"
        'Annulla la trasmissione gerarchica:
        Document.parentWindow.event.cancelBubble = True
    End If
End Function

Private Sub TheButton_onmouseout()
' Ripristina i colori del documento sui valori originali
' quando viene generato l'evento onmouseout. È pertanto possibile
' ripetere l'effetto al clic successivo.
    TheButton.Style.backgroundColor = "buttonface"
    Document.bgColor = "white"
End Sub
