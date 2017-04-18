VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "IRepository"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

'-----------------------------------------------------
'<Name>     IRepository
'<Purpose>  Contains all repository procedures
'-----------------------------------------------------

'<Private>--------------------------------------------
Private BeenHere            As Boolean
Private KeyCounter          As Integer
Private ThisTree            As TreeView
Private WorkingNode         As Node
Private ThisRepository      As Repository
'</Private>-------------------------------------------

'-----------------------------------------------------
'<Purpose> Opens the Repository and start its' enumeration
'-----------------------------------------------------
Public Sub EnumRepository(ThisTreeControl As TreeView)
    Dim RepositoryRoot As RepositoryObject

    '---- cache the tree control
    Set ThisTree = ThisTreeControl
    
    '------------------------------------------------
    ' initialize repository object definition variables
    ' this function can be found in 'RepEng.bas' which
    ' ships with the repository
    '------------------------------------------------
    Call InitRepository
    
    '------------------------------------------------
    ' open the repository; When no arguments are included
    ' in the Open method, the default repository is opened
    '------------------------------------------------
    Set RepositoryRoot = ThisRepository.Open()
    
    '---- add a node that represents the repository root
    Set WorkingNode = ThisTree.Nodes.Add(, , "Root", "Repository Root", 2)
    
    '------------------------------------------------
    ' Enumerate the root interfaces. This will start
    ' a chain of enumerations of the entire Repository:
    ' Interfaces --> enumerates object members
    ' Members --> enumerates relationships
    ' Relationships --> enumerates interfaces
    '------------------------------------------------
    Call EnumInterfaces(RepositoryRoot, "Root")
    
End Sub

'-----------------------------------------------------------------
'<Purpose> enumerates all the interfaces to the RepNodes collection
'-----------------------------------------------------------------
Private Sub EnumInterfaces(ThisObject As RepositoryObject, ParentKey As String)
    Dim ObjectType          As ClassDef
    Dim ObjectInterface     As Object
    Dim TheseInterfaces     As Object
    Dim InstanceInterface   As RepositoryObject
    Dim TheseMembers        As Object
    Dim NodeKey             As String
    
    '---- get the definitions of the implemented interface.
    Set ObjectType = ThisRepository.Object(ThisObject.Type)
    Set TheseInterfaces = ObjectType.Interfaces
    
    For Each InstanceInterface In TheseInterfaces
                
        '---- create a new key
        KeyCounter = KeyCounter + 1
        NodeKey = "I" & KeyCounter
        
        '---- add the node to the TreeView
        Set WorkingNode = ThisTree.Nodes.Add(ParentKey, tvwChild, _
                            NodeKey, InstanceInterface.Name, 4)
        
        '---- this example only loops once
        If (Not BeenHere) Then
            '---- get the interface object
            Set ObjectInterface = ThisObject(InstanceInterface.Name)
            '---- enumerate all of the members of the interface
            Set TheseMembers = InstanceInterface("IInterfaceDef").Members
            Call EnumMembers(TheseMembers, ObjectInterface, NodeKey)
        End If
    Next
    
    BeenHere = True
    
End Sub

Private Sub Class_Initialize()
    Set ThisRepository = New Repository
End Sub

Private Sub Class_Terminate()
    Set ThisRepository = Nothing
End Sub

'--------------------------------------------------------------------
'<Purpose> enumerates all the members and adds object members to the RepNodes collection
'<Note> a member is a collection, property, or method on an inteface
'--------------------------------------------------------------------
Private Sub EnumMembers(TheseMembers As Object, ObjectInterface As Object, _
                          ParentKey As String)
    Dim IsOrigin            As Boolean
    Dim NodeKey             As String
    Dim InstanceMember      As RepositoryObject
    Dim TheseRelationships  As Object
    
    '---- enumerate the relationship collections on the interface
    For Each InstanceMember In TheseMembers
        
        '---- Check if the ThisMember is a property def or collection def.
        If (Not IsPropertyDef(InstanceMember.Type)) Then
        
            '---- create a new key
            KeyCounter = KeyCounter + 1
            NodeKey = "M" & KeyCounter
            
            '---- add the node to the TreeView
            Set WorkingNode = ThisTree.Nodes.Add(ParentKey, tvwChild, _
                                NodeKey, InstanceMember.Name, 4)
        
            '---- test to see if it is an origin
            IsOrigin = (InstanceMember("ICollectionDef").IsOrigin <> 0)
            
            '---- don't show relationships back to origin
            If IsOrigin Then
                '---- create the relationships collection, and enumerate it
                Set TheseRelationships = _
                  ObjectInterface.Properties(InstanceMember.Name).Value
                Call EnumRelationships(TheseRelationships, NodeKey)
            End If
        
        
        End If
    Next
    
End Sub

'-----------------------------------------------------------------
'<Purpose> enumerates all the objects attached to the
' relationships into the RepNodes collection
'-----------------------------------------------------------------
Private Sub EnumRelationships(TheseRelationships As IRelationshipCol, ParentKey As String)
    Dim NodeKey                 As String
    Dim InstanceRelationship    As Relationship
    Dim TargetObject            As RepositoryObject
    
    '---- Enumerate the relationships in this collection for the object.
    For Each InstanceRelationship In TheseRelationships
                
        '---- cache the target object, this is what will be displayed
        Set TargetObject = InstanceRelationship.Target
        
        '---- add properties here
        If (Not IsPropertyDef(InstanceRelationship.Type)) Then
                
            '---- create a new key
            KeyCounter = KeyCounter + 1
            NodeKey = "R" & KeyCounter
            
            '---- add the node to the TreeView
            Set WorkingNode = ThisTree.Nodes.Add(ParentKey, tvwChild, _
                                NodeKey, TargetObject.Name, 4)
            
            '----------------------------------------------
            ' now enumerate the interfaces on the target of
            ' this relationship, starting the loop again
            '----------------------------------------------
            Call EnumInterfaces(TargetObject, NodeKey)
        End If
    Next
    
End Sub

