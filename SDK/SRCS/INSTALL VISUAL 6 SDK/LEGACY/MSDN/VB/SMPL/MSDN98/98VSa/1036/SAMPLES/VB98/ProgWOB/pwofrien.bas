Attribute VB_Name = "modFriends"
Option Explicit
' Constantes pour les fonctions de débogage.
Global Const DEBUGTOKEN_DebugID = 1
Global Const DEBUGTOKEN_ClassName = 2

' Type défini par l'utilisateur, dont se sert
'   l'exemple pour illusté le type Friend.
Public Type udtDEMO
    intA As Integer
    lngB As Long
    strC As String
End Type

' La fonction timeGetTime est utilisé par
' ----------- l'exemple Implements, et par le
'   code de débogage de la durée de vie de
'   l'objet dans ce module.
Declare Function timeGetTime Lib "winmm.dll" () As Long

' Stockage pour la collection globale
'   pour la durée de vie des objets de débogage.
'   Utilisé par les procédures DebugInit,
'   DebugTerm et DebugShow (ci-dessous).
Private mcolDebug As New Collection

'         PROCÉDURES DE DÉBOGAGE
'
' DebugInit
' DebugTerm
' DebugShow
'
' Tous les objets implémentent l'interface
'   IDebug et la gèrent en appelant la fonction
'   DebugInit(Me) dans leurs événements
'   Initialize, et la procédure DebugTerm Me dans
'   leurs événements Terminate. Vous pouvez
'   utiliser la fonction DebugShow dans la fenêtre Exécution
'   pour lister un objet actif, tous les
'   objets actifs, ou tous les objets d'une classe.
'
' Tous les objets de ce projet sont
'   définis pour utiliser ces fonctions.
'
' -------------------------------------
' La fonction DebugInit est appelée par chaque objet,
' ---------     dans son événement Initialize.
'   DebugInit ajoute une chaîne de débogage pour
'   l'objet de la collection globale, et
'   renvoie un DebugID unique pour l'objet.
'   La méthode peut afficher en option la
'   chaîne de débogage dans la fenêtre Exécution
'   (la valeur par défaut est True).
'
Public Function DebugInit(ByVal obj As Object, _
        Optional ByVal ShowImmediate As Boolean = True) As Long
    Dim lngDebugID As Long
    Dim strDebug As String
    
    ' Obtient un numéro d'identificateur unique.
    lngDebugID = GetDebugID
    ' La chaîne de débogage de chaque
    '   objet affiche le DebugID, le
    '   nom de classe de l'objet, et l'heure
    '   de début (exprimée en secondes depuis
    '   que le premier objet de débogage a été
    '   créé, sous forme de valeur de type Double,
    '   les millisecondes étant affichées sous
    '   forme décimale).
    strDebug = lngDebugID & " " _
        & TypeName(obj) _
        & " (créé à " & DebugTime & ")"
    '
    ' Ajoute la chaîne à la collection,
    '   en utilisant l'identificateur unique comme une clé.
    mcolDebug.Add strDebug, CStr(lngDebugID)
    '
    ' L'option par défaut est d'afficher la chaîne
    '   de débogage dans la fenêtre Exécution.
    If ShowImmediate Then Debug.Print strDebug
    '
    ' Renvoie le DebugID. L'objet doit
    '   le stocker comme une partie de
    '   l'implémentation de IDebug.
    DebugInit = lngDebugID
End Function

' La procédure DebugTerm est appelé par chaque objet,
' ---------     dans son événement Terminate.
'   La procédure DebugTerm supprime la chaîne de débogage
'   de l'objet de la collection globale,
'   et affiche en option (la valeur par défaut
'   est True) la chaîne de débogage dans
'   la fenêtre Exécution.
'
Public Sub DebugTerm(ByVal obj As Object, _
        Optional ByVal ShowImmediate As Boolean = True)
    
    Dim idbg As IDebug
    
    On Error Resume Next
    '
    ' Obtient une référence à l'interface
    '   IDebug de l'objet.
    Set idbg = obj
    If Err.Number <> 0 Then
        MsgBox TypeName(obj) & " n'implémente pas IDebug; impossible d'enregistrer la fin.", , "DebugTerm"
        Exit Sub
    End If
    '
    ' La valeur par défaut est d'afficher la
    '   chaîne de débogage dans la Fenêtre Exécution.
    If ShowImmediate Then Debug.Print _
        mcolDebug(CStr(idbg.DebugID)) _
        & " (Terminé à " & DebugTime & ")"
    '
    ' Supprime la chaîne de la collection.
    ' 
    mcolDebug.Remove CStr(idbg.DebugID)
End Sub

' La procédure DebugShow affiche la ou les chaînes
' ---------     de débogage pour toute la liste
'   des objets actifs, pour tous les objets actifs
'   d'une classe, ou pour un objet particulier.
'   Appellez la procédure DebugShow à partir de la fenêtre
'   Exécution sans argument (affiche tout),
'   avec un nom de classe (affiche toute la classe),
'   avec une référence d'objet (affiche cet
'   objet), ou le DebugID d'un objet
'   (affiche cet objet).
'
Public Sub DebugShow(Optional ByVal What As Variant)
    Dim vnt As Variant
    Dim idbg As IDebug
    
    On Error GoTo NoShow
    ' Si aucun argument n'est fourni, affiche
    '   tous les objets actifs. (Il peut être
    '   utile d'avoir un deuxième paramètre optionnel
    '   FileName qui vous permettrait
    '   de les enregistrer vers un fichier, où même
    '   dans le Presse-papiers.)
    If IsMissing(What) Then
        What = "<Tout>"
        For Each vnt In mcolDebug
            Debug.Print vnt
        Next
    '
    ' Si un objet est fourni, utilise son
    '   DebugID pour rechercher sa chaîne de
    '   débogage.
    ElseIf IsObject(What) Then
        On Error Resume Next
        '
        ' Obtient une référence à l'interface
        '   IDebug de l'objet.
Set idbg = What
        If Err.Number <> 0 Then
            MsgBox TypeName(What) & " n'implémente pas IDebug; impossible d'afficher l'enregistrement du débogage.", , "DebugShow"
            Exit Sub
        End If
        '
        Debug.Print mcolDebug(CStr(idbg.DebugID))
    '
    ' Si un nombre est fourni, considère qu'il s'agit
    '   du DebugID et l'utilise pour rechercher la chaîne.
    ' 
    ElseIf IsNumeric(What) Then
        Debug.Print mcolDebug(CStr(What))
    '
    ' Si ce n'est pas un nombre, considère qu'il
    '   s'agit d'une chaîne contenant le nom de
    '   la classe; affiche tous les objets avec
    '   le nom de la classe.
    Else
        For Each vnt In mcolDebug
            If What = GetDebugToken(vnt, DEBUGTOKEN_ClassName) Then
                Debug.Print vnt
            End If
        Next
    End If
    Exit Sub
    
NoShow:
    If IsObject(What) Then
        MsgBox "Impossible d'afficher des informations. Est-ce que cet objet a été défini pour le débogage?", , "DebugShow"
    Else
        MsgBox "Impossible d'afficher des informations pour " _
            & What & ". Est-ce que cet objet a été défini pour le débogage?", , "DebugShow"
    End If
End Sub

' La fonction GetDebugString renvoie une chaîne
' --------------    de l'objet depuis la collection
'   globale.
'
Public Function GetDebugString(ByVal obj As Object) As String
    Dim idbg As IDebug
    
    On Error Resume Next
    '
    ' Obtient une référence à l'interface
    '   IDebug de l'objet.
    Set idbg = obj
    GetDebugString = mcolDebug(CStr(idbg.DebugID))
End Function

' La fonction GetDebugID est utilisée pour affecter à chaque objet
' ----------    un numéro d'identificateur unique, à
'   des fins de débogage.
Public Function GetDebugID() As Long
    Static lngLastID As Long
    lngLastID = lngLastID + 1
    GetDebugID = lngLastID
End Function

' La fonction GetDebugToken analyse la chaîne de débogage
' -------------     pour un objet et
'   renvoie le jeton demandé. Les jetons
'   sont séparés par des espaces simples.
'   (1) DebugID
'   (2) Nom de la classe
'
' Il existe d'autres jetons, mais ils n'ont
'   pas le bon type.
'
Public Function GetDebugToken( _
        ByVal DebugString As String, _
        ByVal TokenNumber As Integer) As String

    Dim inx1 As Long
    Dim inx2 As Long
    Dim ct As Integer
    
    If TokenNumber <= 0 Then
        Err.Raise vbObjectError + 1060, , _
            "Mauvais numéro de jeton dans la fonction GetDebugToken"
    Else
        inx2 = 1
        For ct = 1 To TokenNumber
            inx1 = inx2
            inx2 = InStr(inx1, DebugString, " ")
            If inx2 = 0 Then Exit For
        Next
        If inx2 = 0 Then
            GetDebugToken = ""
        Else
            GetDebugToken = Mid$(DebugString, inx1 + 1, inx2 - inx1)
        End If
    End If
End Function
        
' La fonction DebugTime utilise l'API timeGetTime
' ---------     pour compter les millisecondes
'   écoulées depuis le démarrage de l'ordinateur.
'   Ce nombre est converti en une valeur de type Double
'   contenant le nombre de secondes depuis la création
'   du premier objet de débogage (s,mmm), en utilisant
'   comme heure de base la première instance où cette
'   fonction a été appelée. Avec cette fonction, les
'   valeurs d'heure sont plus faciles à utiliser qu'un
'   nombre brut exprimé en millisecondes, comptées depuis
'   le dernier démarrage de la machine, dans la mesure où
'   (1) il peut s'agir d'un nombre très long, et (2) qu'il
'   peut être négatif, comme cela est expliqué plus loin.
'
Public Function DebugTime() As Double
    Static timeBase As Double
    Dim timeCurrent As Double
    
    If timeBase = 0 Then
        ' Initialise l'heure de base. La boucle
        '   tient compte du fait que l'heure
        '   renvoyée par la fonction timeGetTime
        '   peut repasser par zéro, si l'ordinateur
        '   reste allumé suffisamment longtemps.
        Do While timeBase = 0
            timeBase = timeGetTime
        Loop
        '
        ' La valeur renvoyée par la fonction timeGetTime
        '   peut être négative (reportez-vous à la note
        '   ci-dessous) si l'ordinateur est resté
        '   longtemps allumé.
        '   Correct pour cela.
        If timeBase < 0 Then
            timeBase = timeBase + 4294967296#
        End If
    End If
    '
    timeCurrent = timeGetTime
    '
    ' Correct pour la valeur négative,
    '   si nécessaire.
    If timeCurrent < 0 Then
        timeCurrent = timeCurrent + 4294967296#
    End If
    '
    ' Gère le cas où la fonction timeGetTime
    '   repasse par zéro.
    If timeCurrent < timeBase Then
        DebugTime = (timeCurrent + 4294967296# - timeBase) / 1000#
    Else
        DebugTime = (timeCurrent - timeBase) / 1000#
    End If
End Function
' -------- Fonction timeGetTime --------
' Les millisecondes écoulées depuis le dernier
'   démarrage sont exprimées sous forme d'un
'   entier binaire de 4 octets non signé, ce
'   qui signifie qu'il peut être plus long que
'   la valeur de type Long supportée.
'   Lorsqu'il passe le plus grand nombre positif
'   géré par une valeur de type Long (soit 2147483647),
'   Visual Basic considère que le nombre a "fait
'   le tour" et le transforme en nombre négatif.
'   Si cela se produit, l'incrémentation se poursuit
'   jusqu'à atteindre le plus grand nombre négatif
'   géré par la valeur de type Long, jusqu'à zéro,
'   et ainsi de suite.

' Cela créé un modèle en 'dents de scie',
'   et fonctionne assez bien pour les
'   différences d'heures (ce que la fonction
'   DebugTime calcule), sauf au moment critique
'   où la remise à zéro se produit.
'
' La fonction DebugTime résout ce problème
'   en plaçant le nombre dans un conteneur
'   plus large, de type Double. Si le
'   nombre est négatif, il peut être converti
'   dans le nombre qu'il aurait dû être
'   en lui ajoutant 4294967296.
