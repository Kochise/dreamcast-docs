VERSION 4.00
Begin VB.MDIForm frmMain 
   BackColor       =   &H00808000&
   Caption         =   "Reporter"
   ClientHeight    =   3435
   ClientLeft      =   2910
   ClientTop       =   9480
   ClientWidth     =   3960
   Height          =   3840
   Icon            =   "frmMain.frx":0000
   Left            =   2850
   LinkTopic       =   "MDIForm1"
   Top             =   9135
   Width           =   4080
End
Attribute VB_Name = "frmMain"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

Private Sub MDIForm_Load()

    'On Load we create the Request Broker object
    Set oRequestBroker = CreateObject("RequestBroker.clsRequestBroker")
    
    'Load the Request form and allow it to show itself when it is done initializing
    Load frmRequest

End Sub



