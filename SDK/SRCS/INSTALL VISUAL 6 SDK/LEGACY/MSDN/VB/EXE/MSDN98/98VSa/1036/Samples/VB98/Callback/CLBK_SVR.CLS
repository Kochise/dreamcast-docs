VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CbServerClass"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

' Cet exemple montre l'utilisation du pointeur d'un objet ActiveX passé à un composant ActiveX
' externe (et optionnellement distant). Le composant ActiveX appelle ensuite à intervalles réguliers
' une méthode sur ce pointeur de l'objet, ce qui a pour effet d'envoyer des rappels au client
' depuis le composant. Cela peut constituer un modèle d'application plus performant que le regroupement
' effectué par une application client pour rechercher le statut d'un composant. Bien que cet exemple
' ne renvoie au client que l'heure, il peut aussi facilement renvoyer des données, des informations
' ou toute autre indication dont le client a besoin. L'avantage de cette procédure est que le composant
' effectue toutes les tâches en observant les données dont le client peut avoir besoin, ce qui permet
' au client de faire autre chose et de n'être interrompu que lorsque le composant a quelque chose qui
' l'intéresse.

' Note 1: Dans ce scénario, le client crée un objet interne. Il crée ensuite une instance du composant
' distant et passe un pointeur de l'objet à son objet interne. Le composant se fixe sur l'objet
' du client, et l'alimente de temps en temps. À un moment donné, le client décide de se déconnecter
' (DropObjectReference) et le composant effectue certaines tâches de nettoyage en attendant que
' le client affecte la valeur Nothing à sa référence au composant. Étant donné que le composant
' a une feuille visible (les composants n'ont en général aucun affichage visible sauf
' pour les informations de débogage), il la décharge à ce moment de sorte que l'instance
' sera fermée par le composant ActiveX lorsque le client affecte la valeur Nothing à la référence.

' Note 2: Étant donné que le client a créé à la fois l'instance à son objet interne et l'instance
' au composant, il est important que ce soit le client qui ferme ces deux instances en leur
' affectant la valeur Nothing. Des erreurs ActiveX se produiront si le composant tente d'affecter
' la valeur Nothing à la référence du client.

' Note 3: Cette application a été développée très rapidement et ne doit pas être prise à la
' lettre si l'on veut créer de bons composants. Par exemple, un bon composant ne devrait avoir AUCUN
' appel aux boîtes de message hors d'un mode de débogage: si un composant en production a affiché
' un message pour l'utilisateur, il risque de se passer un bon moment avant que quelqu'un ne clique
' sur le bouton OK de la machine serveur.

' Note 4: Les propriétés de classe suivantes sont de première importance pour le comportement
' de l'application:

' "Instancing = Creatable SingleUse" oblige le composant ActiveX à créer une nouvelle instance
' physique de la classe pour chaque client. Cela fournit un modèle de programmation simple pour
' la création de chemins d'exécution parallèles sur le serveur NT, mais demande une importante
' quantité de mémoire à allouer à chaque client. Littéralement, SingleUse signifie que le
' composant n'est utilisé que par un seul client à la fois. Un modèle d'exécution plus efficace
' peut être obtenu avec "Instancing = MultiUse". Cela oblige le composant ActiveX à créer
' seulement une instance du composant pour le premier client, tous les autres clients auront
' un pointeur vers l'instance initiale lorsqu'ils effectuent leurs créations. Ce modèle est
' plus efficace du point de vue de la mémoire, mais le composant ActiveX n'autorisera
' qu'un seul client à la fois à utiliser l'instance de la classe, ce qui peut déboucher sur
' le blocage du client si la tâche de la classe est plus longue que l'intervalle de demande
' moyenne des clients. L'utilisation d'un regroupement de composants SingleUse peut être un bon
' compromis entre ces deux options d'implémentation. Dans ce cas, 100 clients peuvent avoir
' accès à un regroupement de 10 instances de classes. Reportez-vous à l'exemple Gestionnaire de
' regroupements (Poolmngr) pour plus d'informations sur ce scénario.


' "Public = True" permet aux applications externes d'accéder à cette classe en passant par le
' composant ActiveX.
' "Name = Stuff" est utilisé comme le nom de classe dans la deuxième partie du paramètre progID.
' Le client référence ce paramètre pour dire au composant ActiveX quel objet il veut faire démarrer.

' Note 5: Il est très important de définir le nom du projet dans la boîte de dialogue
' Propriétés du projet accessible à partir de la commande Propriétés du <Projet> du menu Projet.
' Il est utilisé par le client pour définir le nom de projet dans le paramètre progID.
' Après la création d'un composant EXE ActiveX, le fichier EXE doit être exécuté une fois pour
' enregistrer les informations de types ActiveX dans la base de registres du système.
' Après l'avoir exécuté une fois, fermez le composant manuellement: tout semble prêt pour que
' votre application client appelle le composant par l'intermédiaire du contrôle ActiveX.

' Note 6: Chaque fois que vous créez un nouvel exe de votre composant, VB générera
' un nouveau ID unique pour chacune de ses classes. Étant donné que cet ID doit correspondre
' à l'ID qui est enregistré dans la base de registres de la machine du client, la modification
' constante de l'ID risque de transformer le travail simultané du client et du composant en
' une véritable corvée. Pour contourner ce problème, allez dans la boîte de dialogue
' Propriétés du projet, accessible à partir de la commande Propriétés du <Projet> du menu Projet
' en cliquant sur l'onglet Composant et sur la zone Compatibilité des versions; le bouton Sélection
' permet de sélectionner une instance précédente du fichier exe du composant. Chaque fois que VB
' recrée le fichier exe du composant, il prendra le ou les paramètres classID de la précédente version.
' Il fera également une autre vérification pour tenter de s'assurer que vous avez maintenu
' la compatibilité avec les versions précédentes.

Private Sub Class_Terminate()
'  Debug.Print "CbServerProj.CbServerClass est terminé"
End Sub
Private Sub Class_Initialize()
'  Debug.Print "CbServerProj.CbServerClass est initialisé"
End Sub

Public Function AddObjectReference(Caller As Object) As Boolean
  On Error GoTo AddObjectReferenceError
  
  Set gObjRef = Caller
  frmMain.Timer1.Enabled = True
  AddObjectReference = True
  gbConnected = True
  Exit Function

AddObjectReferenceError:
  #If DEBUG_ON Then
  MsgBox Error$, vbOKOnly + vbExclamation, "Erreur - AddObjectReference" & Str$(Err)
  #End If
  AddObjectReference = False
  Exit Function
End Function

Public Function DropObjectReference(Caller As Object) As Boolean
Dim iCounter As Integer
On Error GoTo DropObjReferenceError

  If gObjRef Is Caller Then
    gbConnected = False
    frmMain.Timer1.Enabled = False
    Unload frmMain
    DropObjectReference = True
  Else
'    Debug.Print "Appelant différent de ObjRef. Impossible de quitter."
    DropObjectReference = False
  End If
Exit Function

DropObjReferenceError:
  #If DEBUG_ON Then
  MsgBox Error$, vbOKOnly + vbExclamation, "Erreur - DropObjectReference" & Str$(Err)
  #End If
  DropObjectReference = False
  Exit Function

End Function

Public Function SetInterval(iInterval As Integer) As Boolean
    
    On Error GoTo SetIntervalError
    frmMain.Timer1.Interval = (iInterval * 1000)
    frmMain.lblInterval.Caption = Format$(iInterval)
    SetInterval = True
    Exit Function
    
SetIntervalError:
    SetInterval = False
    Exit Function
    
End Function
