VERSION 5.00
Begin VB.Form frmGroupsUsers 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Groupes/Utilisateurs"
   ClientHeight    =   5010
   ClientLeft      =   4380
   ClientTop       =   1905
   ClientWidth     =   6480
   HelpContextID   =   2016088
   Icon            =   "GRPSUSRS.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   MinButton       =   0   'False
   ScaleHeight     =   5010
   ScaleWidth      =   6480
   ShowInTaskbar   =   0   'False
   Begin VB.ComboBox cboOwners 
      Height          =   315
      Left            =   4080
      Style           =   2  'Dropdown List
      TabIndex        =   28
      Top             =   2360
      Width           =   2175
   End
   Begin VB.Frame fraPermissions 
      Caption         =   "Autorisations"
      Height          =   1695
      Left            =   3120
      TabIndex        =   16
      Top             =   2760
      Width           =   3135
      Begin VB.CommandButton cmdAssign 
         Caption         =   "&Affecter"
         Height          =   300
         Left            =   120
         MaskColor       =   &H00000000&
         TabIndex        =   25
         Top             =   1280
         Width           =   1400
      End
      Begin VB.CheckBox chkDeleteData 
         Caption         =   "DeleteData"
         Height          =   255
         Left            =   1680
         MaskColor       =   &H00000000&
         TabIndex        =   24
         Top             =   1320
         Width           =   1335
      End
      Begin VB.CheckBox chkInsertData 
         Caption         =   "InsertData"
         Height          =   255
         Left            =   1680
         MaskColor       =   &H00000000&
         TabIndex        =   23
         Top             =   1000
         Width           =   1335
      End
      Begin VB.CheckBox chkUpdateData 
         Caption         =   "UpdateData"
         Height          =   255
         Left            =   1680
         MaskColor       =   &H00000000&
         TabIndex        =   22
         Top             =   680
         Width           =   1335
      End
      Begin VB.CheckBox chkReadData 
         Caption         =   "ReadData"
         Height          =   255
         Left            =   1680
         MaskColor       =   &H00000000&
         TabIndex        =   21
         Top             =   360
         Width           =   1335
      End
      Begin VB.CheckBox chkAdminister 
         Caption         =   "Administer"
         Height          =   255
         Left            =   120
         MaskColor       =   &H00000000&
         TabIndex        =   20
         Top             =   1000
         Width           =   1455
      End
      Begin VB.CheckBox chkModifyDesign 
         Caption         =   "ModifyDesign"
         Height          =   255
         Left            =   120
         MaskColor       =   &H00000000&
         TabIndex        =   19
         Top             =   680
         Width           =   1575
      End
      Begin VB.CheckBox chkReadDesign 
         Caption         =   "ReadDesign"
         Height          =   255
         Left            =   120
         MaskColor       =   &H00000000&
         TabIndex        =   18
         Top             =   360
         Width           =   1455
      End
   End
   Begin VB.OptionButton optGroups 
      Caption         =   "Groupes"
      Height          =   255
      Left            =   1680
      MaskColor       =   &H00000000&
      TabIndex        =   2
      Top             =   120
      Width           =   975
   End
   Begin VB.OptionButton optUsers 
      Caption         =   "Utilisateurs"
      Height          =   255
      Left            =   120
      MaskColor       =   &H00000000&
      TabIndex        =   1
      Top             =   120
      Value           =   -1  'True
      Width           =   1335
   End
   Begin VB.CommandButton cmdClose 
      Cancel          =   -1  'True
      Caption         =   "&Fermer"
      Height          =   375
      Left            =   2400
      MaskColor       =   &H00000000&
      TabIndex        =   0
      Top             =   4560
      Width           =   1335
   End
   Begin VB.ListBox lstTablesQuerys 
      Height          =   1620
      ItemData        =   "GRPSUSRS.frx":030A
      Left            =   3120
      List            =   "GRPSUSRS.frx":030C
      MultiSelect     =   2  'Extended
      TabIndex        =   15
      Top             =   480
      Width           =   3135
   End
   Begin VB.PictureBox picUsers 
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   3975
      Left            =   120
      ScaleHeight     =   3975
      ScaleWidth      =   2805
      TabIndex        =   3
      Top             =   480
      Width           =   2805
      Begin VB.CommandButton cmdPassword 
         Caption         =   "&Définir/Supprimer le mot de passe"
         Height          =   300
         Left            =   15
         MaskColor       =   &H00000000&
         TabIndex        =   26
         Top             =   3615
         Width           =   2640
      End
      Begin VB.ListBox lstUsersGroups 
         Height          =   1035
         ItemData        =   "GRPSUSRS.frx":030E
         Left            =   0
         List            =   "GRPSUSRS.frx":0310
         MultiSelect     =   1  'Simple
         TabIndex        =   12
         Top             =   2400
         Width           =   2655
      End
      Begin VB.CommandButton cmdDeleteUser 
         Caption         =   "&Supprimer"
         Height          =   300
         Left            =   1080
         MaskColor       =   &H00000000&
         TabIndex        =   10
         Top             =   1800
         Width           =   1080
      End
      Begin VB.CommandButton cmdNewUser 
         Caption         =   "&Nouveau"
         Height          =   300
         Left            =   0
         MaskColor       =   &H00000000&
         TabIndex        =   9
         Top             =   1800
         Width           =   1080
      End
      Begin VB.ListBox lstUsers 
         Height          =   1620
         ItemData        =   "GRPSUSRS.frx":0312
         Left            =   0
         List            =   "GRPSUSRS.frx":0314
         TabIndex        =   4
         Top             =   0
         Width           =   2655
      End
      Begin VB.Label lblLabels 
         Caption         =   "Appartenant aux groupes:"
         Height          =   255
         Index           =   1
         Left            =   0
         TabIndex        =   11
         Top             =   2160
         Width           =   2055
      End
   End
   Begin VB.PictureBox picGroups 
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   3615
      Left            =   120
      ScaleHeight     =   3615
      ScaleWidth      =   2205
      TabIndex        =   5
      Top             =   480
      Visible         =   0   'False
      Width           =   2205
      Begin VB.ListBox lstGroupsUsers 
         Height          =   1035
         ItemData        =   "GRPSUSRS.frx":0316
         Left            =   0
         List            =   "GRPSUSRS.frx":0318
         MultiSelect     =   1  'Simple
         TabIndex        =   13
         Top             =   2400
         Width           =   2175
      End
      Begin VB.CommandButton cmdDeleteGroup 
         Caption         =   "&Supprimer"
         Height          =   300
         Left            =   1200
         MaskColor       =   &H00000000&
         TabIndex        =   8
         Top             =   1800
         Width           =   975
      End
      Begin VB.CommandButton cmdNewGroup 
         Caption         =   "&Nouveau"
         Height          =   300
         Left            =   0
         MaskColor       =   &H00000000&
         TabIndex        =   7
         Top             =   1800
         Width           =   975
      End
      Begin VB.ListBox lstGroups 
         Height          =   1620
         ItemData        =   "GRPSUSRS.frx":031A
         Left            =   0
         List            =   "GRPSUSRS.frx":031C
         TabIndex        =   6
         Top             =   0
         Width           =   2175
      End
      Begin VB.Label lblLabels 
         BackColor       =   &H00C0C0C0&
         Caption         =   "Membres:"
         Height          =   255
         Index           =   2
         Left            =   120
         TabIndex        =   14
         Top             =   2160
         Width           =   2055
      End
   End
   Begin VB.Label lblLabels 
      Caption         =   "Propriétaire:"
      Height          =   255
      Index           =   3
      Left            =   3120
      TabIndex        =   27
      Top             =   2400
      Width           =   855
   End
   Begin VB.Label lblLabels 
      Caption         =   "Tables/Requêtes:"
      Height          =   255
      Index           =   0
      Left            =   3120
      TabIndex        =   17
      Top             =   165
      Width           =   2055
   End
   Begin VB.Line Line1 
      BorderWidth     =   3
      X1              =   3000
      X2              =   3000
      Y1              =   120
      Y2              =   4440
   End
End
Attribute VB_Name = "frmGroupsUsers"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'>>>>>>>>>>>>>>>>>>>>>>>>
Const FORMCAPTION = "Groupes/Utilisateurs/Autorisations"
Const Label1 = "Tables/Requêtes:"
Const Label2 = "Appartenant aux groupes:"
Const LABEL3 = "Membres:"
Const LABEL4 = "Propriétaire:"
Const BUTTON1 = "&Nouveau"
Const BUTTON2 = "&Supprimer"
Const BUTTON3 = "&Définir/Supprimer le mot de passe"
Const BUTTON4 = "&Affecter"
Const BUTTON5 = "&Fermer"
Const OPTION1 = "Utilisateurs"
Const OPTION2 = "Groupes"
Const FRAME1 = "Autorisations"
Const MSG1 = "Vous n'êtes pas autorisé à modifier le propriétaire!"
Const MSG2 = "Aucun groupe n'est sélectionné!"
Const MSG3 = "Supprime le groupe?"
Const MSG4 = "Aucun utilisateur n'est sélectionné!"
Const MSG5 = "Supprime l'utilisateur?"
Const MSG6 = "Nouvel groupe"
Const MSG7 = "Nouvel utilisateur"
Const MSG8 = "Supprimer le mot de passe?"
Const MSG9 = "Aucun objet n'est sélectionné!"
'>>>>>>>>>>>>>>>>>>>>>>>>


Dim mbSettingUser As Integer
Dim mbSettingOwner As Integer
Dim mbSettingPerm As Integer
Dim mbLoading As Integer
Dim mobjCurrObject As Object    ' Sélection en cours de la table ou de la requête.

Private Sub cboOwners_Click()
  On Error GoTo COErr
  
  ' Quitte en cas de définition par du code.
  If mbSettingOwner Then Exit Sub
  
  If (mobjCurrObject.Permissions And dbSecWriteOwner) = dbSecWriteOwner Then
    ' Essaye de le définir.
    mobjCurrObject.Owner = cboOwners.Text
  Else
    MsgBox MSG1, 48
    Exit Sub
  End If
  
  Exit Sub
  
COErr:
  ShowError
End Sub

Private Sub chkAdminister_Click()
  If mbSettingPerm Then Exit Sub
  
  If chkAdminister.Value = vbChecked Then
    ' Les définir tous.
    chkReadDesign.Value = vbChecked
    chkModifyDesign.Value = vbChecked
    chkReadData.Value = vbChecked
    chkUpdateData.Value = vbChecked
    chkInsertData.Value = vbChecked
    chkDeleteData.Value = vbChecked
  End If
End Sub

Private Sub chkDeleteData_Click()
  If mbSettingPerm Then Exit Sub
  
  If chkDeleteData.Value = vbUnchecked Then
    ' Dé-coche si nécessaire
    chkAdminister.Value = vbUnchecked
    chkModifyDesign.Value = vbUnchecked
  Else
    chkReadDesign.Value = vbChecked
    chkReadData.Value = vbChecked
  End If
End Sub

Private Sub chkInsertData_Click()
  If mbSettingPerm Then Exit Sub
  
  If chkInsertData.Value = vbUnchecked Then
    ' Dé-coche si nécessaire
    chkAdminister.Value = vbUnchecked
  Else
    chkReadDesign.Value = vbChecked
    chkReadData.Value = vbChecked
  End If
End Sub

Private Sub chkModifyDesign_Click()
  If mbSettingPerm Then Exit Sub
  
  If chkModifyDesign.Value = vbUnchecked Then
    ' Dé-coche leur Administer
    chkAdminister.Value = vbUnchecked
  Else
    chkReadDesign.Value = vbChecked
    chkReadData.Value = vbChecked
    chkInsertData.Value = vbChecked
    chkDeleteData.Value = vbChecked
  End If
End Sub

Private Sub chkReadData_Click()
  If mbSettingPerm Then Exit Sub
  
  If chkReadData.Value = vbUnchecked Then
    ' dé-coche si nécessaire
    chkAdminister.Value = vbUnchecked
    chkModifyDesign.Value = vbUnchecked
  Else
    chkReadDesign.Value = vbChecked
  End If
End Sub

Private Sub chkReadDesign_Click()
  If mbSettingPerm Then Exit Sub
  
  If chkReadDesign.Value = vbUnchecked Then
    ' dé-coche tous
    chkAdminister.Value = vbUnchecked
    chkModifyDesign.Value = vbUnchecked
    chkReadData.Value = vbUnchecked
    chkUpdateData.Value = vbUnchecked
    chkInsertData.Value = vbUnchecked
    chkDeleteData.Value = vbUnchecked
  End If
End Sub

Private Sub chkUpdateData_Click()
  If mbSettingPerm Then Exit Sub
  
  If chkUpdateData.Value = vbUnchecked Then
    ' Dé-coche si nécessaire
    chkAdminister.Value = vbUnchecked
    chkModifyDesign.Value = vbUnchecked
  Else
    chkReadDesign.Value = vbChecked
    chkReadData.Value = vbChecked
  End If
End Sub

Private Sub cmdAssign_Click()
  SetPermissions True    ' Pour les affecter
End Sub

Private Sub cmdClose_Click()
  Unload Me
End Sub

Private Sub cmdDeleteGroup_Click()
  On Error GoTo DGErr
  
  Dim i As Integer
    
  If lstGroups.ListIndex < 0 Then
    Beep
    MsgBox MSG2
    Exit Sub
  End If
  If MsgBox(MSG3, vbYesNo + vbQuestion) <> vbYes Then Exit Sub
  
  gwsMainWS.Groups.Delete lstGroups.Text
  i = lstGroups.ListIndex
  lstGroups.RemoveItem i
  lstUsersGroups.RemoveItem i
  If lstGroups.ListCount > 0 Then
    lstGroups.ListIndex = 0
  Else
    ' Il faut désélectionner tous les utilisateurs.
    For i = 0 To lstGroupsUsers.ListCount - 1
      lstGroupsUsers.Selected(i) = False
    Next
  End If
  
  Exit Sub
  
DGErr:
  ShowError
End Sub

Private Sub cmdDeleteUser_Click()
  On Error GoTo DUErr
  
  Dim i As Integer
  
  If lstUsers.ListIndex < 0 Then
    Beep
    MsgBox MSG4
    Exit Sub
  End If
  If MsgBox(MSG5, vbYesNo + vbQuestion) <> vbYes Then Exit Sub
  
  gwsMainWS.Users.Delete lstUsers.Text
  lstUsers.RemoveItem lstUsers.ListIndex
  If lstUsers.ListCount > 0 Then
    lstUsers.ListIndex = 0
  Else
    ' Il faut désélectionner tous les groupes.
    For i = 0 To lstUsersGroups.ListCount - 1
      lstUsersGroups.Selected(i) = False
    Next
  End If
  Exit Sub
  
DUErr:
  ShowError
End Sub

Private Sub cmdNewGroup_Click()
  frmNewUserGroup.UserOrGroup = 1
  frmNewUserGroup.Caption = MSG6
  frmNewUserGroup.Show vbModal
End Sub

Private Sub cmdNewUser_Click()
  frmNewUserGroup.UserOrGroup = 0
  frmNewUserGroup.Caption = MSG7
  frmNewUserGroup.Show vbModal
End Sub

Private Sub cmdPassword_Click()
  On Error GoTo CPErr
  
  If lstUsers.Text = gwsMainWS.UserName Then
    frmNewPassword.Show vbModal
  Else
    If MsgBox(MSG8, vbYesNo + vbQuestion) = vbYes Then
      gwsMainWS.Users(lstUsers.Text).NewPassword vbNullString, vbNullString
    End If
  End If
  
  Exit Sub
  
CPErr:
  ShowError
End Sub

Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
  If KeyCode = vbKeyF1 And Shift = 0 Then
    DisplayTopic 2016088
  End If
End Sub

Private Sub Form_Load()
  On Error GoTo FLErr
  
  Dim grp As Group
  Dim usr As User
  Dim i As Integer

  Me.Caption = FORMCAPTION
  optUsers.Caption = OPTION1
  optGroups.Caption = OPTION2
  fraPermissions.Caption = FRAME1
  cmdNewUser.Caption = BUTTON1
  cmdDeleteUser.Caption = BUTTON2
  cmdNewGroup.Caption = BUTTON1
  cmdDeleteGroup.Caption = BUTTON2
  cmdPassword.Caption = BUTTON3
  cmdAssign.Caption = BUTTON4
  cmdClose.Caption = BUTTON5
  lblLabels(0).Caption = Label1
  lblLabels(1).Caption = Label2
  lblLabels(2).Caption = LABEL3
  lblLabels(3).Caption = LABEL4

  mbLoading = True
  ' Ajoute les groupes et les utilisateurs.
  For Each usr In gwsMainWS.Users
    lstUsers.AddItem usr.Name
    lstGroupsUsers.AddItem usr.Name
    cboOwners.AddItem usr.Name
  Next
  For Each grp In gwsMainWS.Groups
    lstGroups.AddItem grp.Name
    lstUsersGroups.AddItem grp.Name
    cboOwners.AddItem grp.Name
  Next
  ' Définit le premier élément si possible.
  If lstUsers.ListCount > 0 Then
    lstUsers.ListIndex = 0
  End If
  If lstGroups.ListCount > 0 Then
    lstGroups.ListIndex = 0
  End If
  
  ' Remplit les listes d'objets à partir des feuilles de tables.
  GetTableList lstTablesQuerys, True, False, False
  mbLoading = False
  lstTablesQuerys.Selected(0) = True
  Screen.MousePointer = vbDefault
  Exit Sub
  
FLErr:
  mbLoading = False
  ShowError
End Sub

Private Sub lstGroups_Click()
  On Error GoTo GSErr

  Dim i As Integer
  
  mbSettingUser = True
  For i = 0 To lstGroupsUsers.ListCount - 1
    If IsMemberOf(lstGroups.Text, lstGroupsUsers.List(i)) Then
      lstGroupsUsers.Selected(i) = True
    Else
      lstGroupsUsers.Selected(i) = False
    End If
  Next
  mbSettingUser = False
  
  Exit Sub
  
GSErr:
  ShowError
  mbSettingUser = False
End Sub

Private Sub lstGroupsUsers_Click()
  On Error GoTo GUErr
  
  Dim usr As User
  
  If mbSettingUser Then Exit Sub
  
  If lstGroups.ListIndex < 0 Then
    Beep
    MsgBox MSG2
    Exit Sub
  End If
  
  If lstGroupsUsers.Selected(lstGroupsUsers.ListIndex) Then
    ' Ajoute l'utilisateur au groupe.
    Set usr = gwsMainWS.CreateUser(lstGroupsUsers.Text)
    gwsMainWS.Groups(lstGroups.Text).Users.Append usr
    gwsMainWS.Users(lstGroupsUsers.Text).Groups.Refresh
  Else
    ' Retire l'utilisateur du groupe.
    gwsMainWS.Groups(lstGroups.Text).Users.Delete lstGroupsUsers.Text
    gwsMainWS.Users(lstGroupsUsers.Text).Groups.Refresh
  End If
  
  Exit Sub
  
GUErr:
  ShowError
End Sub

Private Sub lstTablesQuerys_Click()
  SetPermissions False
End Sub

Private Sub lstUsers_Click()
  On Error GoTo USErr

  Dim i As Integer
  
  mbSettingUser = True
  For i = 0 To lstUsersGroups.ListCount - 1
    If IsMemberOf(lstUsersGroups.List(i), lstUsers.Text) Then
      lstUsersGroups.Selected(i) = True
    Else
      lstUsersGroups.Selected(i) = False
    End If
  Next
  mbSettingUser = False
  
  ' Affiche les autorisations.
  SetPermissions False
  
  Exit Sub
  
USErr:
  ShowError
  mbSettingUser = False
End Sub

Private Function IsMemberOf(rsGrp As String, rsUsr As String) As Integer
  Dim usr As User
  Dim grp As Group
  Dim i As Integer
  
  Set usr = gwsMainWS.Users(rsUsr)
  
  For Each grp In usr.Groups
    If grp.Name = rsGrp Then
      IsMemberOf = True
      Exit Function
    End If
  Next
  IsMemberOf = False
End Function

Private Sub lstUsersGroups_Click()
  On Error GoTo UGErr
  
  Dim grp As Group
  
  If mbSettingUser Then Exit Sub
  
  If lstUsers.ListIndex < 0 Then
    Beep
    MsgBox MSG4
    Exit Sub
  End If
  
  If lstUsersGroups.Selected(lstUsersGroups.ListIndex) Then
    ' Ajoute le groupe à l'utilisateur.
    Set grp = gwsMainWS.CreateGroup(lstUsersGroups.Text)
    gwsMainWS.Users(lstUsers.Text).Groups.Append grp
    gwsMainWS.Groups(lstUsersGroups.Text).Users.Refresh
  Else
    ' Retire le groupe de l'utilisateur.
    gwsMainWS.Users(lstUsers.Text).Groups.Delete lstUsersGroups.Text
    gwsMainWS.Groups(lstUsersGroups.Text).Users.Refresh
  End If
  
  Exit Sub
  
UGErr:
  ShowError
End Sub

Private Sub optGroups_Click()
  picUsers.Visible = False
  picGroups.Visible = True
End Sub

Private Sub optUsers_Click()
  picGroups.Visible = False
  picUsers.Visible = True
End Sub

Private Sub SetPermissions(rbAssign As Integer)
  On Error GoTo SPErr
  
  Dim lPermissions As Long
  Dim lPermissions2 As Long
  Dim bUncommon As Integer    ' Indicateur à sélections multiples pour des autorisations communes.
  Dim nCnt As Integer         ' Nombre des objets sélectionnés.
  Dim sUserGroup As String
  Dim sObject As String
  Dim i As Integer
  
  mbSettingPerm = True
  
  If rbAssign Then
    ' Détermine les autorisations définies et les unir (Or)
    If chkReadDesign.Value = vbUnchecked Then
      lPermissions = 0
    Else
      If chkAdminister.Value = vbChecked Then
        ' Les définir toutes
        lPermissions = dbSecFullAccess Or _
                       dbSecReadDef Or _
                       dbSecWriteDef Or _
                       dbSecRetrieveData Or _
                       dbSecReplaceData Or _
                       dbSecInsertData Or _
                       dbSecDeleteData
      Else
        ' Les définir une par une
        lPermissions = dbSecReadDef
        If chkModifyDesign.Value = vbChecked Then
          lPermissions = lPermissions Or dbSecWriteDef
        End If
        If chkReadData.Value = vbChecked Then
          lPermissions = lPermissions Or dbSecRetrieveData
        End If
        If chkUpdateData.Value = vbChecked Then
          lPermissions = lPermissions Or dbSecReplaceData
        End If
        If chkInsertData.Value = vbChecked Then
          lPermissions = lPermissions Or dbSecInsertData
        End If
        If chkDeleteData.Value = vbChecked Then
          lPermissions = lPermissions Or dbSecDeleteData
        End If
      End If
    End If
  End If
  
  ' Détermine s'il s'agit d'un utilisateur ou d'un groupe.
  If optUsers.Value Then
    ' Utilisateurs.
    sUserGroup = lstUsers.Text
  Else
    ' Groupes.
    sUserGroup = lstGroups.Text
  End If
  
  ' Définit ou lit les autorisations.
  If lstTablesQuerys.ListIndex = -1 Then
    If mbLoading = False Then   ' Ne provoque pas d'erreur au chargement de la feuille
      Beep
      MsgBox MSG9
    End If
    Exit Sub
  End If
  
  ' Parcoure la liste des objets et traiter les objets sélectionnés.
  For i = 0 To lstTablesQuerys.ListCount - 1
    If lstTablesQuerys.Selected(i) Then
      nCnt = nCnt + 1
      If lstTablesQuerys.ListIndex = 0 Then
        ' Doit être <Nouvel objet>
        gdbCurrentDB.Containers("Tables").UserName = sUserGroup
        If rbAssign = False Then
          lPermissions = gdbCurrentDB.Containers("Tables").Permissions
        Else
          gdbCurrentDB.Containers("Tables").Permissions = lPermissions
        End If
        ShowOwner gdbCurrentDB.Containers("Tables")
        Set mobjCurrObject = gdbCurrentDB.Containers("Tables")
      Else
        sObject = StripConnect(lstTablesQuerys.List(i))
        ' Une table ou une requête a été sélectionnée.
        gdbCurrentDB.Containers("Tables").Documents(sObject).UserName = sUserGroup
        If rbAssign = False Then
          lPermissions = gdbCurrentDB.Containers("Tables").Documents(sObject).Permissions
        Else
          gdbCurrentDB.Containers("Tables").Documents(sObject).Permissions = lPermissions
        End If
        ShowOwner gdbCurrentDB.Containers("Tables").Documents(sObject)
        Set mobjCurrObject = gdbCurrentDB.Containers("Tables").Documents(sObject)
      End If
      If nCnt > 1 Then
        ' Si supérieurs à 1, ils doivent correspondre; sinon, l'indicateur doit être défini.
        If lPermissions <> lPermissions2 Then
          bUncommon = True
        End If
      End If
      ' Le stocker pour la prochaine fois au moyen de
      lPermissions2 = lPermissions
    End If
  Next
  
  If rbAssign = False Then
    If bUncommon Then
      ' Absence de correspondance: il faut les mettre en grisé.
      chkReadDesign.Value = 2
      chkModifyDesign.Value = 2
      chkAdminister.Value = 2
      chkReadData.Value = 2
      chkUpdateData.Value = 2
      chkInsertData.Value = 2
      chkDeleteData.Value = 2
    Else
      ' Il n'y en a qu'un ou ils sont tous identiques:
      ' il faut définir de façon appropriée.
      If (lPermissions And dbSecReadDef) = dbSecReadDef Then
        chkReadDesign.Value = vbChecked
      Else
        chkReadDesign.Value = vbUnchecked
      End If
      If (lPermissions And dbSecWriteDef) = dbSecWriteDef Then
        chkModifyDesign.Value = vbChecked
      Else
        chkModifyDesign.Value = vbUnchecked
      End If
      If (lPermissions And dbSecFullAccess) = dbSecFullAccess Then
        chkAdminister.Value = vbChecked
      Else
        chkAdminister.Value = vbUnchecked
      End If
      If (lPermissions And dbSecRetrieveData) = dbSecRetrieveData Then
        chkReadData.Value = vbChecked
      Else
        chkReadData.Value = vbUnchecked
      End If
      If (lPermissions And dbSecReplaceData) = dbSecReplaceData Then
        chkUpdateData.Value = vbChecked
      Else
        chkUpdateData.Value = vbUnchecked
      End If
      If (lPermissions And dbSecInsertData) = dbSecInsertData Then
        chkInsertData.Value = vbChecked
      Else
        chkInsertData.Value = vbUnchecked
      End If
      If (lPermissions And dbSecDeleteData) = dbSecDeleteData Then
        chkDeleteData.Value = vbChecked
      Else
        chkDeleteData.Value = vbUnchecked
      End If
    End If
  End If
  
  mbSettingPerm = False
  Exit Sub
  
SPErr:
  mbSettingPerm = False
  ShowError
End Sub

Private Sub ShowOwner(vObj As Object)
  On Error GoTo SOErr
  
  Dim i As Integer
  
  For i = 0 To cboOwners.ListCount - 1
    If cboOwners.List(i) = vObj.Owner Then
      mbSettingOwner = True
      cboOwners.ListIndex = i
      mbSettingOwner = False
      Exit For
    End If
  Next

  Exit Sub
  
SOErr:
  mbSettingOwner = True
  cboOwners.ListIndex = -1
  mbSettingOwner = False
  ShowError
End Sub
