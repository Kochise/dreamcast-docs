VERSION 5.00
Begin VB.UserControl ShapeLabel 
   BackStyle       =   0  'Transparent
   ClientHeight    =   1575
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   2820
   ClipControls    =   0   'False
   ForwardFocus    =   -1  'True
   PropertyPages   =   "CPShapeL.ctx":0000
   ScaleHeight     =   1575
   ScaleWidth      =   2820
   Begin VB.Label lblCaption 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Légende"
      Height          =   195
      Left            =   840
      TabIndex        =   0
      Top             =   360
      Width           =   555
   End
   Begin VB.Shape shpBack 
      BorderStyle     =   0  'Transparent
      FillColor       =   &H000000FF&
      FillStyle       =   0  'Solid
      Height          =   735
      Left            =   600
      Shape           =   2  'Oval
      Top             =   360
      Width           =   1575
   End
End
Attribute VB_Name = "ShapeLabel"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Ext_KEY = "PropPageWizardRun" ,"Yes"
Option Explicit
' Notes sur le contrôle ShapeLabel:
'
' 1) Ce code a été généré dans sa quasi-totalité par
'    l'Assistant Interface de contrôles ActiveX.
'    Le code ajouté ou modifié à la main est signalé 
'    de manière explicite.
' 2) Il a été affecté la valeur True à la propriété ForwardFocus 
'    de l'objet UserControl. Ainsi, le focus se comporte comme 
'    pour des contrôles Label courants.
'

Const RESIZE_AdjustX As Single = 0.07
Const RESIZE_AdjustY As Single = 0.03

' Stockage pour les valeurs de propriétés. (La plupart
' des valeurs de propriétés de le contrôle ShapeLabel sont
' stockées dans les propriétés de l'objet UserControl ou
' de ses contrôles constitutifs.)
Private m_Alignment As AlignmentConstants

' Déclarations des événements:
Event Click() 'MappingInfo=UserControl,UserControl,-1,Click
Attribute Click.VB_Description = "Se produit lorsque l'utilisateur appuie et relâche un bouton de la souris sur un objet."
Event DblClick() 'MappingInfo=UserControl,UserControl,-1,DblClick
Event MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single) 'MappingInfo=UserControl,UserControl,-1,MouseDown
Attribute MouseDown.VB_Description = "Se produit lorsque l'utilisateur appuie sur le bouton de la souris lorsqu'un objet a le focus."
Event MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single) 'MappingInfo=UserControl,UserControl,-1,MouseMove
Attribute MouseMove.VB_Description = "Se produit lorsque l'utilisateur bouge la souris."
Event MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single) 'MappingInfo=UserControl,UserControl,-1,MouseUp
Attribute MouseUp.VB_Description = "Se produit lorsque l'utilisateur relâche le bouton de la souris, quand un objet a le focus."

' La propriété BackColor a été réaffectée à la main
' à la propriété FillColor du contrôle Shape,
' car c'est ce qui remplit la forme qui apparaît comme 
' l'arrière-plan du contrôle ShapeLabel.
'
Public Property Get BackColor() As OLE_COLOR
Attribute BackColor.VB_Description = "Renvoie/définit la couleur de l'arrière-plan utilisé pour afficher du texte et des graphiques dans un objet."
    BackColor = shpBack.FillColor
End Property

Public Property Let BackColor(ByVal New_BackColor As OLE_COLOR)
    shpBack.FillColor() = New_BackColor
    PropertyChanged "BackColor"
End Property

' La propriété ForeColor est affectée à la propriété
' ForeColor du contrôle Label, car la propriété
' ForeColor du contrôle ShapeLabel doit contrôler
' la couleur de la police. L'arrière-plan du contrôle
' Label est de type Transparent, la propriété
' BackColor a donc peu d'importance.
'
' ATTENTION! NE PAS SUPPRIMER OU MODIFIER LES LIGNES DE COMMENTAIRE SUIVANTES!
' MappingInfo=lblCaption,lblCaption,-1,ForeColor
Public Property Get ForeColor() As OLE_COLOR
Attribute ForeColor.VB_Description = "Renvoie/définit la couleur du premier plan utilisé pour afficher du texte et des graphiques dans un objet."
    ForeColor = lblCaption.ForeColor
End Property

Public Property Let ForeColor(ByVal New_ForeColor As OLE_COLOR)
    lblCaption.ForeColor() = New_ForeColor
    PropertyChanged "ForeColor"
End Property

' Pour fonctionner de la même façon que les propriétés
' Enabled des autres contrôles, la propriété Enabled 
' doit présenter un identificateur de procédure correct.
' L'Assistant Interface n'effectue pas cette opération; 
' il faut le faire à la main.
' Utilisez la boîte de dialogue Attributs de procédure,
' accessible à partir du menu Outils, pour définir
' l'identificateur de procédure avec pour valeur Enabled
' pour la propriété Enabled. La Liste ID de la procédure est 
' accessible à partir du bouton Avancés de la boîte de dialogue.
' Sélectionnez Enabled dans la liste Nom pour afficher
' les attributs de la propriété Enabled.
'
' ATTENTION! NE PAS SUPPRIMER OU MODIFIER LES LIGNES DE COMMENTAIRE SUIVANTES!
' MappingInfo=UserControl,UserControl,-1,Enabled
Public Property Get Enabled() As Boolean
Attribute Enabled.VB_Description = "Renvoie/définit une valeur qui determine si un objet peut répondre aux événements générés par l'utilisateur."
Attribute Enabled.VB_UserMemId = -514
    Enabled = UserControl.Enabled
End Property

Public Property Let Enabled(ByVal New_Enabled As Boolean)
    UserControl.Enabled() = New_Enabled
    PropertyChanged "Enabled"
End Property

' ATTENTION! NE PAS SUPPRIMER OU MODIFIER LES LIGNES DE COMMENTAIRE SUIVANTES!
' MappingInfo=lblCaption,lblCaption,-1,Font
Public Property Get Font() As Font
Attribute Font.VB_Description = "Renvoie un objet Font."
Attribute Font.VB_UserMemId = -512
    Set Font = lblCaption.Font
End Property

Public Property Set Font(ByVal New_Font As Font)
    Set lblCaption.Font = New_Font
    PropertyChanged "Font"
    ' Ajout manuel: le changement de police peut demander un
    'ajustement de la position du contrôle Label.
    Call UserControl_Resize
End Property

' Ajout manuel à la propriété d'une des constantes de BorderStyleConstants.
'
' ATTENTION! NE PAS SUPPRIMER OU MODIFIER LES LIGNES DE COMMENTAIRE SUIVANTES!
' MappingInfo=shpBack,shpBack,-1,BorderStyle
Public Property Get BorderStyle() As BorderStyleConstants
Attribute BorderStyle.VB_Description = "Renvoie/définit le style de bordure pour un objet."
    BorderStyle = shpBack.BorderStyle
End Property
Public Property Let BorderStyle(ByVal New_BorderStyle As BorderStyleConstants)
    ' Validation fournie par le contrôle Shape shpBack.
    shpBack.BorderStyle() = New_BorderStyle
    PropertyChanged "BorderStyle"
End Property

' ATTENTION! NE PAS SUPPRIMER OU MODIFIER LES LIGNES DE COMMENTAIRE SUIVANTES!
' MappingInfo=UserControl,UserControl,-1,Refresh
Public Sub Refresh()
Attribute Refresh.VB_Description = "Force le rafraîchissement complet d'un objet."
    UserControl.Refresh
End Sub

' Ceci est un exemple de double affectation.
' Pour que l'événement Click du contrôle ShapeLabel
' agisse correctement, il doit être déclenché lorsque 
' l'utilisateur clique sur l'étiquette, et/ou
' sur le corps du contrôle. L'Assistant Interface
' ne gère pas de code pour une double affectation.
Private Sub lblCaption_Click()
    RaiseEvent Click
End Sub
Private Sub UserControl_Click()
    RaiseEvent Click
End Sub

' Ajout manuel d'une affectation à l'événement
' DblClick du contrôle Label.
Private Sub lblCaption_DblClick()
    RaiseEvent DblClick
End Sub
Private Sub UserControl_DblClick()
    RaiseEvent DblClick
End Sub

' Ajout manuel d'une affectation à l'événement
' MouseDown du contrôle Label.
Private Sub lblCaption_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    ' Voir le commentaire dans lblCaption_MouseMove.
    RaiseEvent MouseDown(Button, Shift, _
        ScaleX(X + lblCaption.Left, vbTwips, vbContainerPosition), _
        ScaleY(Y + lblCaption.Height, vbTwips, vbContainerPosition))
End Sub
Private Sub UserControl_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    ' Voir le commentaire dans UserConrol_MouseMove.
    RaiseEvent MouseDown(Button, Shift, _
        ScaleX(X, vbTwips, vbContainerPosition), _
        ScaleY(Y, vbTwips, vbContainerPosition))
End Sub

' Ajout manuel d'une affectation à l'événement
' MouseMove du contrôle Label.
'
Private Sub lblCaption_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    ' La position de la souris (X, Y) doit être convertie
    ' en coordonnées du conteneur. Puisque cela est lié au 
    ' contrôle Label, il doit d'abord être converti en 
    ' coordonnées de l'objet UserControl, en ajoutant les valeurs 
    ' lblCaption.Top et .Left. Ces valeurs peuvent être ajoutées 
    ' car la valeur de la propriété ScaleMode de l'objet UserControl 
    ' est en Twips, la même unité que pour les coordonnées du 
    ' contrôle Label. Si ce n'est pas le cas, une autre conversion 
    ' sera demandée.
    '
    RaiseEvent MouseMove(Button, Shift, _
        ScaleX(X + lblCaption.Left, vbTwips, vbContainerPosition), _
        ScaleY(Y + lblCaption.Height, vbTwips, vbContainerPosition))
End Sub
Private Sub UserControl_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    ' La position de la souris (X, Y) doit être convertie
    ' en coordonnées du conteneur (qui peuvent être exprimées,
    ' par exemple, en pixels).
    '
    ' Nous pourrions procéder d'une manière plus générale
    ' en remplaçant vbTwips par UserControl.ScaleMode.
    ' Cela fonctionnerait toujours, même après avoir changé
    ' la propriété ScaleMode. Cependant, cela signifie deux
    ' appels de méthodes au lieu de deux constantes.
    ' Dans le cas où l'événement MouseMove peut être aussi 
    ' rapide que possible, la constante vbTwips est utilisée
    ' ici. (Bien entendu, si vous changez la propriété ScaleMode 
    ' au moment de l'exécution, vous devez utiliser
    ' UserControl.ScaleMode au lieu de vbTwips!)
    '
    RaiseEvent MouseMove(Button, Shift, _
        ScaleX(X, vbTwips, vbContainerPosition), _
        ScaleY(Y, vbTwips, vbContainerPosition))
End Sub

' Ajout manuel d'une affectation à l'événement
' MouseUp du contrôle Label
'.
Private Sub lblCaption_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    ' Voir le commentaire dans lblCaption_MouseMove.
    RaiseEvent MouseUp(Button, Shift, _
        ScaleX(X + lblCaption.Left, vbTwips, vbContainerPosition), _
        ScaleY(Y + lblCaption.Height, vbTwips, vbContainerPosition))
End Sub
Private Sub UserControl_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    ' Voir le commentaire dans UserControl_MouseMove.
    RaiseEvent MouseUp(Button, Shift, _
        ScaleX(X, vbTwips, vbContainerPosition), _
        ScaleY(Y, vbTwips, vbContainerPosition))
End Sub

' Ajout manuel à la propriété d'une des constantes AlignmentConstants.
'
' ATTENTION! NE PAS SUPPRIMER OU MODIFIER LES LIGNES DE COMMENTAIRE SUIVANTES!
' MappingInfo=lblCaption,lblCaption,-1,Alignment
Public Property Get Alignment() As AlignmentConstants
Attribute Alignment.VB_Description = "Renvoie/définit l'alignement des contrôles CheckBox ou OptionButton, ou du texte d'un contrôle."
    Alignment = m_Alignment
End Property

Public Property Let Alignment(ByVal New_Alignment As AlignmentConstants)
    ' L'alignement n'est pas stocké dans la propriété d'un
    ' contrôle constitutif; nous devons donc fournir notre
    ' propre code de validation.
    Select Case New_Alignment
        Case vbCenter
        Case vbLeftJustify
        Case vbRightJustify
        Case Else
            ' Valeur de propriété non valide.
            Err.Raise 380
    ' Si vous vous arrêtez ici lors de l'exécution du contrôle
    ' ShapeLabel, cliquez avec le bouton droit de la souris 
    ' dans la fenêtre Code, cliquez sur Activer dans le menu
    ' contextuel, puis sur Arrêt sur les erreurs non gérées.
    ' Vous pouvez alors appuyer sur F5 pour continuer l'exécution
    ' de l'exemple.
    End Select
    m_Alignment = New_Alignment
    PropertyChanged "Alignment"
    ' Le changement de l'alignement peut affecter les positions
    ' des contrôles constitutifs.
    Call UserControl_Resize
End Property

' Le type (OLE_COLOR) pour la propriété BorderColor doit être
' ajouté manuellement.
'
' ATTENTION! NE PAS SUPPRIMER OU MODIFIER LES LIGNES DE COMMENTAIRE SUIVANTES!
' MappingInfo=shpBack,shpBack,-1,BorderColor
Public Property Get BorderColor() As OLE_COLOR
Attribute BorderColor.VB_Description = "Renvoie/définit la couleur de la bordure d'un objet."
    BorderColor = shpBack.BorderColor
End Property

Public Property Let BorderColor(ByVal New_BorderColor As OLE_COLOR)
    shpBack.BorderColor() = New_BorderColor
    PropertyChanged "BorderColor"
End Property

' ATTENTION! NE PAS SUPPRIMER OU MODIFIER LES LIGNES DE COMMENTAIRE SUIVANTES!
' MappingInfo=shpBack,shpBack,-1,BorderWidth
Public Property Get BorderWidth() As Integer
Attribute BorderWidth.VB_Description = "Renvoie ou définit la largeur d'une bordure d'un contrôle."
    BorderWidth = shpBack.BorderWidth
End Property

Public Property Let BorderWidth(ByVal New_BorderWidth As Integer)
    shpBack.BorderWidth() = New_BorderWidth
    PropertyChanged "BorderWidth"
End Property

' ATTENTION! NE PAS SUPPRIMER OU MODIFIER LES LIGNES DE COMMENTAIRE SUIVANTES!
' MappingInfo=lblCaption,lblCaption,-1,Caption
Public Property Get Caption() As String
Attribute Caption.VB_Description = "Renvoie/définit le texte affiché dans la barre de titre ou sous l'icône d'un objet."
    Caption = lblCaption.Caption
End Property

Public Property Let Caption(ByVal New_Caption As String)
    lblCaption.Caption() = New_Caption
    PropertyChanged "Caption"
    ' Ajout manuel: le changement de légende peut demander
    ' un ajustement de la position du contrôle Label. 
    Call UserControl_Resize
End Property

' ATTENTION! NE PAS SUPPRIMER OU MODIFIER LES LIGNES DE COMMENTAIRE SUIVANTES!
' MappingInfo=UserControl,UserControl,-1,hDC
Public Property Get hDC() As Long
Attribute hDC.VB_Description = "Renvoie un descripteur (à partir de Microsoft Windows) de contexte de périphérique de l'objet."
    hDC = UserControl.hDC
End Property

' ATTENTION! NE PAS SUPPRIMER OU MODIFIER LES LIGNES DE COMMENTAIRE SUIVANTES!
' MappingInfo=UserControl,UserControl,-1,hWnd
Public Property Get hWnd() As Long
Attribute hWnd.VB_Description = "Renvoie un descripteur (à partir de Microsoft Windows) d'une fenêtre de l'objet."
    hWnd = UserControl.hWnd
End Property

' ATTENTION! NE PAS SUPPRIMER OU MODIFIER LES LIGNES DE COMMENTAIRE SUIVANTES!
' MappingInfo=UserControl,UserControl,-1,MouseIcon
Public Property Get MouseIcon() As Picture
Attribute MouseIcon.VB_Description = "Définit une icône de souris personnalisée."
    Set MouseIcon = UserControl.MouseIcon
End Property

Public Property Set MouseIcon(ByVal New_MouseIcon As Picture)
    Set UserControl.MouseIcon = New_MouseIcon
    PropertyChanged "MouseIcon"
End Property

' Ajout manuel à la propriété d'une des constantes MousePointerConstants.
'
' ATTENTION! NE PAS SUPPRIMER OU MODIFIER LES LIGNES DE COMMENTAIRE SUIVANTES!
' MappingInfo=UserControl,UserControl,-1,MousePointer
Public Property Get MousePointer() As MousePointerConstants
Attribute MousePointer.VB_Description = "Renvoie/définit le type de pointeur de la souris affiché lorsque celui-ci est déplacé sur les éléments de l'objet."
    MousePointer = UserControl.MousePointer
End Property

Public Property Let MousePointer(ByVal New_MousePointer As MousePointerConstants)
    ' Validation fournie par l'objet UserControl.
    UserControl.MousePointer() = New_MousePointer
    PropertyChanged "MousePointer"
End Property

' Ajout manuel à la propriété d'une des constantes de ShapeConstants.
'
' ATTENTION! NE PAS SUPPRIMER OU MODIFIER LES LIGNES DE COMMENTAIRE SUIVANTES!
' MappingInfo=shpBack,shpBack,-1,Shape
Public Property Get Shape() As ShapeConstants
Attribute Shape.VB_Description = "Renvoie/définit une valeur indiquant l'apparence d'un contrôle."
    Shape = shpBack.Shape
End Property

Public Property Let Shape(ByVal New_Shape As ShapeConstants)
    ' Validation fournie par le contrôle Shape shpBack.
    shpBack.Shape() = New_Shape
    PropertyChanged "Shape"
End Property

' Charge les valeurs de propriétés depuis le lieu de stockage.
Private Sub UserControl_ReadProperties(PropBag As PropertyBag)

    shpBack.BackColor = PropBag.ReadProperty("BackColor", &H80000005)
    lblCaption.ForeColor = PropBag.ReadProperty("ForeColor", &H80000012)
    UserControl.Enabled = PropBag.ReadProperty("Enabled", True)
    Set Font = PropBag.ReadProperty("Font", Ambient.Font)
    shpBack.BorderStyle = PropBag.ReadProperty("BorderStyle", 0)
    m_Alignment = PropBag.ReadProperty("Alignment", 2)
    shpBack.BorderColor = PropBag.ReadProperty("BorderColor", -2147483640)
    shpBack.BorderWidth = PropBag.ReadProperty("BorderWidth", 1)
    lblCaption.Caption = PropBag.ReadProperty("Caption", "Légende")
    Set MouseIcon = PropBag.ReadProperty("MouseIcon", Nothing)
    UserControl.MousePointer = PropBag.ReadProperty("MousePointer", 0)
    shpBack.Shape = PropBag.ReadProperty("Shape", 2)
End Sub

Private Sub UserControl_Resize()
    Dim sngCaptionTop As Single
    Dim sngCaptionLeft As Single
    
    ' Le contrôle Shape fournissant l'arrière-plan
    ' d'un contrôle ShapeLabel est redimensionné
    ' pour couvrir la totalité du contrôle.
    shpBack.Move 0, 0, ScaleWidth, ScaleHeight
    ' Le contrôle Label affichant la légende du contrôle
    ' ShapeLabel est disposé en fonction de la valeur
    ' de la propriété Alignment.
    Select Case Alignment
        Case vbCenter
            sngCaptionLeft = (ScaleWidth - lblCaption.Width) / 2
        Case vbLeftJustify
            sngCaptionLeft = RESIZE_AdjustX * ScaleWidth
        Case vbRightJustify
            sngCaptionLeft = ScaleWidth - lblCaption.Width - RESIZE_AdjustX * ScaleWidth
    End Select
    ' Une propriété VerticalAlignment fonctionnerait
    ' de manière semblable; elle aurait besoin de sa
    ' propre instruction Enum.
    sngCaptionTop = (ScaleHeight - lblCaption.Height) / 2 - RESIZE_AdjustY * ScaleHeight
    '
    lblCaption.Move sngCaptionLeft, sngCaptionTop
End Sub

' Écrit les valeurs de propriétés dans l'emplacement de stockage.
Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
    Call PropBag.WriteProperty("BackColor", shpBack.BackColor, &H80000005)
    Call PropBag.WriteProperty("ForeColor", lblCaption.ForeColor, &H80000012)
    Call PropBag.WriteProperty("Enabled", UserControl.Enabled, True)
    Call PropBag.WriteProperty("Font", Font, Ambient.Font)
    Call PropBag.WriteProperty("BorderStyle", shpBack.BorderStyle, 0)
    Call PropBag.WriteProperty("Alignment", m_Alignment, 2)
    Call PropBag.WriteProperty("BorderColor", shpBack.BorderColor, -2147483640)
    Call PropBag.WriteProperty("BorderWidth", shpBack.BorderWidth, 1)
    Call PropBag.WriteProperty("Caption", lblCaption.Caption, "Légende")
    Call PropBag.WriteProperty("MouseIcon", MouseIcon, Nothing)
    Call PropBag.WriteProperty("MousePointer", UserControl.MousePointer, 0)
    Call PropBag.WriteProperty("Shape", shpBack.Shape, 2)
End Sub

