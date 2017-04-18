Attribute VB_Name = "modMain"
Option Explicit

Public oRequestBroker As Broker

Sub Main()
    
    'Simulated Request Broker
    'Set oRequestBroker = CreateObject("RequestBroker.Broker")
    Set oRequestBroker = New Broker
    
    Load frmReporter
    frmReporter.Show

End Sub

