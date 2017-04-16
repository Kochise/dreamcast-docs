VERSION 5.00
Begin VB.UserControl UCObjectSafety 
   BackColor       =   &H00C00000&
   BorderStyle     =   1  'Fixed Single
   ClientHeight    =   525
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4170
   EditAtDesignTime=   -1  'True
   FillColor       =   &H00C00000&
   ForeColor       =   &H00C00000&
   ScaleHeight     =   525
   ScaleWidth      =   4170
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BorderStyle     =   1  'Fixed Single
      Caption         =   "IObjectSafety Interface Sample Control"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   300
      Left            =   120
      TabIndex        =   0
      Top             =   90
      Width           =   3900
   End
End
Attribute VB_Name = "UCObjectSafety"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
' ------------------------------------------------------------------------
' Copyright © 1997 Microsoft Corporation. Tous droits réservés.
' Vous disposez d'un droit accordé à titre gratuit d'utiliser, modifier, reproduire et ' distribuer, de quelque manière que ce soit,
' des extraits de Fichiers d'Applications Exemples. ' Vous reconnaissez être informé et vous acceptez que Microsoft exclut toute garantie,
' obligation ' ou responsabilité relatives à l'exercice du droit gratuit qui vous est accordé ci-dessus.
'-------------------------------------------------------------------------
Option Explicit
Implements IObjectSafety

Private m_Safety                As Boolean
Private m_fMakeSafeForScripting As Boolean

'------------------------------------------------------------
Private Sub IObjectSafety_GetInterfaceSafetyOptions(ByVal riid As Long, pdwSupportedOptions As Long, pdwEnabledOptions As Long)
'------------------------------------------------------------
    Dim IID         As String                           ' Chaîne de l'ID de l'interface
'------------------------------------------------------------
    ' Définit les fonctionnalités sécurisées de l'objet pris en charge...
    pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER Or INTERFACESAFE_FOR_UNTRUSTED_DATA
                          
    IID = GetIIDFromPTR(riid)                           ' Extrait la chaîne de l'ID de l'interface depuis le pointeur
    
    Select Case IID                                     ' Détermine l'interface qui demande les paramètres
    Case IID_IDispatch                                  ' Interface IDispatch.
        ' si ce contrôle est sécurisé pour initialisation _
          l'indicateur INTERFACESAFE_FOR_UNTRUSTED_DATA est alors dénifi
        pdwEnabledOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA    ' définit l'indicateur de fonctionnalité activé
        Exit Sub                                                ' quitte et l'opération a réussi
    Case IID_IPersistStorage, IID_IPersistStream, IID_IPersistPropertyBag
        ' si ce contrôle est sécurisé pour le traitement de script ou s'il peut être sécurisé pour_
        ' le traitement de script l'indicateur INTERFACESAFE_FOR_UNTRUSTED_CALLER est alors défini
        pdwEnabledOptions = pdwEnabledOptions Or INTERFACESAFE_FOR_UNTRUSTED_CALLER     ' Définit l'indicateur de fonctionnalité activé
        Exit Sub                                        ' Opération réussie
    Case Else                                           ' Interface inconnue demandée.
        Err.Raise E_NOINTERFACE                         ' Options sécurisées demandées pour l'interface ne sont pas prises en charge.
    End Select
        
    Err.Raise E_FAIL                                    ' Le paramètre sécurisé pour l'interface n'est pas pris en charge
'------------------------------------------------------------
End Sub
'------------------------------------------------------------

'------------------------------------------------------------
Private Sub IObjectSafety_SetInterfaceSafetyOptions(ByVal riid As Long, ByVal dwOptionsSetMask As Long, ByVal dwEnabledOptions As Long)
'------------------------------------------------------------
    Dim fSettings   As Long                             ' Indicateur de paramètres sécurisés
    Dim IID         As String                           ' Chaîne de l'ID de l'interface
'------------------------------------------------------------
    fSettings = (dwEnabledOptions And dwOptionsSetMask) ' Obtient l'indicateur des paramètres sécurisés
    IID = GetIIDFromPTR(riid)                           ' Obtient la chaîne de l'ID de l'interface depuis le pointeur
    
    Select Case IID                                     ' Détermine l'interface qui demande les paramètres
    Case IID_IDispatch                                  ' Interface IDispatch.
        ' ************************************************************
        ' Si ce contrôle n'est pas ou ne peut pas être sécurisé pour le traitement de script,
        ' la ligne de code suivante est mise en commentaire pour renvoyer E_FAIL
        ' ************************************************************
        ' Err.Raise E_FAIL                              ' Renvoie une erreur si le contrôle n'est pas sécurisé pour le traitement de script.
        
        If (fSettings = INTERFACESAFE_FOR_UNTRUSTED_CALLER) Then
        ' Si ce contrôle n'est pas considéré comme sécurisé pour le traitement de script, _
          il peut cependant être sécurisé pour le traitement de script en désactivant ses _
          fonctionnalités non sécurisées.  Utilise cet indicateur pour indiquer que le contrôle requis doit être _
          sécurisé pour le traitement de script.
            m_fMakeSafeForScripting = True              ' Configure sur True, le contrôle doit être sécurisé pour le traitement de script.
            Exit Sub                                    ' opération réussie
        End If
    Case IID_IPersistStorage, IID_IPersistStream, IID_IPersistPropertyBag
        ' ************************************************************
        ' Si ce contrôle n'est jamais sécurisé pour l'initialisation,
        ' l'interface IObjectSafety ne devrait pas être ajoutée.
        ' ************************************************************
        If (fSettings = INTERFACESAFE_FOR_UNTRUSTED_DATA) Then
            ' Si ce contrôle est toujours sécurisé pour l'initialisation
            Exit Sub                                    ' Opération réussie
        End If
    Case Else                                           ' Interface requise inconnue.
        Err.Raise E_NOINTERFACE                         ' Options sécurisées requises pour l'interface ne sont pas prises en charge.
    End Select
    
    Err.Raise E_FAIL                                    ' L'option sécurisée pour une interface n'est pas prise en charge
'------------------------------------------------------------
End Sub
'------------------------------------------------------------

'------------------------------------------------------------
Public Property Get Safe() As Boolean
'------------------------------------------------------------
' Cette propriété est considérée comme sécurisée pour le traitement de script _
  et peut être utilisée en toute sécurité par un conteneur d'hôte.
'------------------------------------------------------------
    MsgBox "Appel de la méthode:: Property Get Safe"
    Safe = m_Safety                                     ' Renvoie la valeur de données booléenne
'------------------------------------------------------------
End Property
'------------------------------------------------------------

'------------------------------------------------------------
Public Property Let Safe(ByVal IsSafe As Boolean)
'------------------------------------------------------------
' Cette propriété est considérée comme sécurisée pour le traitement de script _
  et peut être utilisée en toute sécurité par un conteneur d'hôte.
'------------------------------------------------------------
    MsgBox "Appel de la méthode:: Property Let Safe"
    m_Safety = IsSafe                                   ' Définit la valeur de données booléenne
'------------------------------------------------------------
End Property
'------------------------------------------------------------

'------------------------------------------------------------
Public Property Get UnSafe() As Boolean
' ------------------------------------------------------------
'  Cette propriété n'est pas sécurisée pour le traitement de script
'  mais elle peut être requise pour sécuriser
'  par le conteneur d'hôte.  Si cette propriété doit être sécurisée
'  cette fonction doit alors être désactivée losqu'elle est appelée.
' ------------------------------------------------------------
    If m_fMakeSafeForScripting Then                     ' Objet requis doit-il être sécurisé ?
        Err.Raise E_FAIL                                ' Erreur renvoyée : cette propriété n'est pas sécurisée.
        Exit Property                                   ' Sortie
    Else
        MsgBox "Appel de la méthode:: Property Get UnSafe"
        UnSafe = m_Safety                                 ' Renvoie la valeur de données booléenne
    End If
'------------------------------------------------------------
End Property
'------------------------------------------------------------

'------------------------------------------------------------
Public Property Let UnSafe(ByVal IsSafe As Boolean)
' ------------------------------------------------------------
'  Cette propriété n'est pas sécurisée pour le traitement de script
'  elle peut cependant être requise pour sécuriser
'  par le conteneur d'hôte.  Si cette propriété doit être sécurisée
'  cette fonction doit alors être désactivée losqu'elle est appelée.
' ------------------------------------------------------------
    If m_fMakeSafeForScripting Then                     ' Objet requis doit-il être sécurisé ?
        Err.Raise E_FAIL                                ' Erreur renvoyée : cette propriété n'est pas sécurisée.
        Exit Property                                   ' Sortie
    Else
        MsgBox "Appel de la méthode:: Property Let UnSafe"
        m_Safety = IsSafe                               ' Renvoie la valeur de données booléenne
    End If
'------------------------------------------------------------
End Property
'------------------------------------------------------------

'------------------------------------------------------------
Public Function ASafeFunctionToCall(ByVal lparm As Long) As Long
' ------------------------------------------------------------
'  Cette fonstion est considérée comme sécurisée pour le traitement de script
'  elle peut cependant être appelée en toute sécurité pour le traitement de script.
' ------------------------------------------------------------
    MsgBox "Appel de la méthode:: Function ASafeFunctionToCall"
    ASafeFunctionToCall = 1                             ' Renvoie une valeur
'------------------------------------------------------------
End Function
'------------------------------------------------------------

'------------------------------------------------------------
Public Function AnUnSafeFunction(ByVal badparm As Long) As Long
' ------------------------------------------------------------
'  Cette fonction n'est pas considérée comme sécurisée pour le traitement de script
'  et ne doit en aucun cas être appelée pour le traitement de script.  Le cas échéant, une erreur d'exécution sera renvoyée
'  pour désactiver cette fonction.
' ------------------------------------------------------------
    If m_fMakeSafeForScripting Then                     ' Contrôle requis doit-il être sécurisé ?
        Err.Raise E_FAIL                                ' Erreur renvoyée : cette fonction n'est pas sécurisée.
        Exit Function                                   ' Renvoie
    Else
        MsgBox "Appel de la méthode:: Function AnUnSafeFunction"
        AnUnSafeFunction = 32                           ' Renvoie une valeur
    End If
' ------------------------------------------------------------
 End Function
' ------------------------------------------------------------
