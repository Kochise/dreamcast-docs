VERSION 5.00
Begin VB.Form frmHello 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Serveur Bonjour"
   ClientHeight    =   1110
   ClientLeft      =   3150
   ClientTop       =   2325
   ClientWidth     =   2820
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   1110
   ScaleWidth      =   2820
End
Attribute VB_Name = "frmHello"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_TemplateDerived = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Load()
' Note1: les deux segments de code suivants illustrent deux options
' pour l'instanciation d'un objet par un client.
' La première option utilise une liaison précoce et nécessite que
' "HelloProj" soit référencé à partir de la boîte de dialogue Références du menu Projet.
' La seconde option utilise une liaison tardive et requiert une
' instruction supplémentaire pour créer l'objet. La liaison précoce
' est plus rapide que la liaison tardive. La liaison tardive
' offre cependant une plus grande flexibilité pour décider en cours d'exécution quels sont les objets à utiliser.

' Note2: ce code source du client est présent dans le projet afin de
' faciliter le débogage. Ce code peut être utilisé dans ce projet
' (serveur) afin de vérifier la syntaxe et les fonctionnalités.
' Il peut être collé dans un projet (client) séparé et utilisé *sans* ' changements pour accéder au serveur depuis un exécutable externe.
' Le fait que la création d'objet est identique pour des projets internes ou externes peut grandement faciliter les tests et le partage de code source.

' Option de liaison précoce.
' Dim objNew As New HelloProj.HelloClass
' MsgBox objNew.SayHello
' Set objNew = Nothing

' Option de liaison tardive.
' Dim objNew As Object
' Set objNew = CreateObject("HelloProj.HelloClass")
' MsgBox objNew.SayHello
' Set objNew = Nothing
End Sub
