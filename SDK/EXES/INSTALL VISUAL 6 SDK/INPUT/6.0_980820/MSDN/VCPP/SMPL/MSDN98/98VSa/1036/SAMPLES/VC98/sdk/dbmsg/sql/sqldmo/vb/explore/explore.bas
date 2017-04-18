Attribute VB_Name = "basExplore"
Option Explicit

' Global constants
Public oSQLServer As SQLOLE.SQLServer
Public oCurrentOne As Object
Public oCurrentTwo As Object
Public oCurrentThree As Object
Public oCurrentFour As Object

Public NL As String
Sub GetCollection(oObject As Object, strCollection As String, oCollection() As Object)
    Select Case strCollection
    
    ' SQLServer
    Case "Databases"
        Set oCollection(0) = oObject.Databases
    Case "Devices"
        Set oCollection(0) = oObject.Devices
    Case "Languages"
        Set oCollection(0) = oObject.Languages
    Case "Logins"
        Set oCollection(0) = oObject.Logins
    Case "RemoteServers"
        Set oCollection(0) = oObject.RemoteServers
    Case "Alerts"
        Set oCollection(0) = oObject.Alerts
    Case "Operators"
        Set oCollection(0) = oObject.Operators
    
    ' Database
    Case "Defaults"
        Set oCollection(0) = oObject.Defaults
    Case "Groups"
        Set oCollection(0) = oObject.Groups
    Case "Rules"
        Set oCollection(0) = oObject.Rules
    Case "StoredProcedures"
        Set oCollection(0) = oObject.StoredProcedures
    Case "SystemDataTypes"
        Set oCollection(0) = oObject.SystemDatatypes
    Case "Tables"
        Set oCollection(0) = oObject.Tables
    Case "UserDefinedDataTypes"
        Set oCollection(0) = oObject.UserDefinedDatatypes
    Case "Users"
        Set oCollection(0) = oObject.Users
    Case "Views"
        Set oCollection(0) = oObject.Views
    Case "Publications"
        Set oCollection(0) = oObject.Publications
    Case "Articles"
        Set oCollection(0) = oObject.Articles
    Case "Subscriptions"
        Set oCollection(0) = oObject.Subscriptions
    
    ' RemoteServer
    Case "RemoteLogins"
        Set oCollection(0) = oObject.RemoteLogins

    ' Table
    Case "Columns"
        Set oCollection(0) = oObject.Columns
    Case "Indexes"
        Set oCollection(0) = oObject.Indexes
    Case "Triggers"
        Set oCollection(0) = oObject.Triggers
    Case "Keys"
        Set oCollection(0) = oObject.Keys
    Case "Checks"
        Set oCollection(0) = oObject.Checks

    End Select
    
End Sub


