VERSION 4.00
Begin VB.Form Form1 
   Caption         =   "Graph OLE Server Demo"
   ClientHeight    =   150
   ClientLeft      =   1140
   ClientTop       =   1515
   ClientWidth     =   3480
   Height          =   555
   Left            =   1080
   LinkTopic       =   "Form1"
   ScaleHeight     =   150
   ScaleWidth      =   3480
   Top             =   1170
   Width           =   3600
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Dim ThisGraph As Object 'Graph.Application
Private Sub Form_Load()
MyData = "Cats" & vbTab & 20 & vbCr & "Dogs" & vbTab & "13" & vbCr & "Horses" & vbTab & "4"
Clipboard.SetText MyData
Set ThisGraph = CreateObject("MSGraph.Application")
ThisGraph.Visible = True
SendKeys "%VD", True
SendKeys "%EP", True
ThisGraph.Chart.HasTitle = True
ThisGraph.Chart.ChartTitle.Caption = "Favorite Pets"
ThisGraph.Chart.AutoFormat Gallery:=xlColumn, Format:=2
bEnd Sub
