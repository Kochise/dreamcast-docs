Attribute VB_Name = "Module1"
' DSBROWSE
' This is a simple browser for Active Directory which demonstrates
' the use of the basic Active Directory Automation interfaces from
' VB. Browsing starts automatically at the Namespaces
' Collection Object. The user can expand the browser tree
' to any level desired. The properties option allows viewing
' of the current Active Directory object's properties, while the Set
' button allows changing property values.

Option Explicit

Public currentADsObj As IADs
Public currentADsObjCont As IADsContainer
Public currentADsObjSchema   As IADs
Public currentNewObj   As IADs
Public strPath As String
Public bStartup As Boolean
Public errstring As String
Public ERRNUMB As Long
Public bAbort As Boolean
Public Sub enumerate_path(ByVal Node As Node)
'
'Name: enumerate_path
'Input: Node As Node
'Desc: Does the actual enumerating of input node.
'   All child object are enumerated and placed under
'   the input node as children.
'Return: none
'
    
    '
    ' Set Error handler
    '
    On Error GoTo ErrorHandler
    
    Dim st As Variant
    Dim nodX As Node    ' Create variable.
    Dim ChildNode As Node    ' Create variable.
    Dim I As Integer    ' Create a counter variable.
    Dim Container As IADsContainer
    Dim Class As IADsClass
    Dim Child As IADs
    Dim classobj As IADsClass
    Dim tempClass As String
    
    bAbort = False
    '
    ' Get the object selected
    '
    Set currentADsObj = GetObject(strPath)
    frmBrwsTree.txtName.Caption = currentADsObj.Name
    frmBrwsTree.txtPath.Caption = currentADsObj.ADsPath
    On Error Resume Next
    '
    ' Set the node if not passed into this sub as the current
    ' node we are working on (for the collection coming up).
    '
    If Node Is Nothing Then
       Set Node = frmBrwsTree.TreeView1.Nodes.Item(currentADsObj.ADsPath)
       Node.Sorted = True
    End If

    On Error GoTo ErrorHandler
    
    If frmBrwsTree.TreeView1.Nodes.Count = 0 Then
        '
        ' This means we are enumerating the namespaces container
        ' No nodes expanded yet,
        '
        tempClass = SetClass(currentADsObj.Class)
        Set nodX = frmBrwsTree.TreeView1.Nodes.Add(, , currentADsObj.ADsPath, _
            currentADsObj.Name, tempClass)
        nodX.Sorted = True
        '
        'Get namespace IDs
        '
        Set Container = currentADsObj
        For Each Child In Container
            tempClass = SetClass(Child.Class)
            Set Node = frmBrwsTree.TreeView1.Nodes.Add(nodX, tvwChild, _
                Child.ADsPath, Child.Name, tempClass)
            Node.Sorted = True
            '
            ' If the child is a container, then add a temporary nod
            ' to show that it can be expanded later.
            '
            Set ChildNode = frmBrwsTree.TreeView1.Nodes.Add(Node, _
                tvwChild, Child.ADsPath & "/Dummy", "Dummy", tempClass)
            ChildNode.Sorted = True
        Next Child
        bStartup = True 'disable expand processing
        frmBrwsTree.TreeView1.Nodes(1).Expanded = True
        bStartup = False
        Set Node = Nothing
    
    Else
    
        Set Container = Nothing
        Node.Sorted = True
        '
        ' Now, see if it's a container and if so, enumerate
        ' all objects below it.
        '
        On Error Resume Next
    
        Set Container = currentADsObj
        If Err = 0 Then
            For Each Child In Container
                If Child Is Nothing Then Exit For
                Err = 0
                I = I + 1
                '
                ' Every 80 objects we check for user input
                '
                If I = 80 Then
                    DoEvents
                    If bAbort Then GoTo quitloop
                    I = 0
                End If
                tempClass = SetClass(Child.Class) 'Gets the image
                If tempClass = "" Then tempClass = "Dummy"
               
                Set nodX = frmBrwsTree.TreeView1.Nodes.Add(Node, tvwChild, _
                    Child.ADsPath, Child.Name, tempClass)
                nodX.Sorted = True
                '
                ' If New node is a container then add temporary child node
                '
                If IsContainer(Child) Then
                      
                    Set ChildNode = frmBrwsTree.TreeView1.Nodes.Add(nodX, _
                        tvwChild, Child.ADsPath & "Dummy", "Dummy", tempClass)
                    ChildNode.Sorted = True
                End If
skip:
           Next Child
        End If
        
quitloop:
        Set currentADsObj = Nothing
skip2:
    End If
    GoTo finish
    
ErrorHandler:
    
        errstring = "Had an error:" & Err.Number
        ERRNUMB = Err.Number
        MsgBox errstring
        Resume Next

finish:

End Sub
Public Function SetClass(classString As String) As String
'Name: SetClass
'Input: classString As String
'Desc: Used to determine what classname is
'   used for the imagelist
'Return: SetClass As String

    SetClass = "img" & classString
    
    '
    ' Evaluate input class to set image to all classes
    '
    Select Case classString
    
    Case "Computer"
    Case "NameSpace"
    Case "Namespaces"
    Case "User"
    Case "Domain"
    Case "Service"
    Case "Group"
    Case "PrintQueue"
    Case "FileShare"
    Case "Organization"
    Case "Country"
    Case "Organizational Unit"
        SetClass = "imgOrganization"
    ' Here we set all others
    Case Else
        SetClass = "imgDefault"
    End Select

End Function

Public Function IsContainer(objADS As IADs) As Boolean
'
' This Function returns True or False depending on whether the
' object referred to by objADs is a container or not
'
    Dim Cont As IADsContainer
    
    On Error Resume Next
    
    Set Cont = objADS
    If Err Then
        IsContainer = False
    Else
        IsContainer = True
    End If
End Function
