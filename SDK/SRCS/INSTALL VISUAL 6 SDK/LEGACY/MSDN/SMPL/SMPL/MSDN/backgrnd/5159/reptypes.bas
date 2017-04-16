Attribute VB_Name = "RepTypes"
Option Explicit

'<Public>--------------------------------------------------------
Public CLSID_RepositoryObject       As Variant

'---- Repository Type Infomation Model Object IDs; assigned in InitRepository()

'---- classes
Public OBJID_ClassDef               As Variant
Public OBJID_InterfaceDef           As Variant
Public OBJID_CollectionDef          As Variant
Public OBJID_MethodDef              As Variant
Public OBJID_PropertyDef            As Variant
Public OBJID_RelationshipDef        As Variant
Public OBJID_ReposTypeLib           As Variant
Public OBJID_ReposRoot              As Variant

'---- interfaces
Public OBJID_IUnknown               As Variant
Public OBJID_IDispatch              As Variant
Public OBJID_IReposDispatch         As Variant
Public OBJID_IReposTypeInfo         As Variant
Public OBJID_IClassDef              As Variant
Public OBJID_IInterfaceDef          As Variant
Public OBJID_IInterfaceMember       As Variant
Public OBJID_IPropertyDef           As Variant
Public OBJID_ICollectionDef         As Variant
Public OBJID_IRepositoryItem        As Variant
Public OBJID_IRepositoryObject      As Variant
Public OBJID_IRelationship          As Variant
Public OBJID_IAnnotationalProps     As Variant
Public OBJID_ISummaryInfo           As Variant
Public OBJID_INamedObject           As Variant
Public OBJID_IManageReposTypeLib    As Variant
Public OBJID_IReposTypeLib          As Variant
Public OBJID_IReposRoot             As Variant

'---- relationships
Public OBJID_RClassImplIface                As Variant
Public OBJID_RIfaceInheritsFromIface        As Variant
Public OBJID_RIfaceHasMembers               As Variant
Public OBJID_RColContainsItems              As Variant
Public OBJID_RContainerContextForReposTLBs  As Variant
Public OBJID_RReposTLBScopeForReposTypeInfo As Variant

'---- collections
Public OBJID_Ifaces                 As Variant
Public OBJID_Classes                As Variant
Public OBJID_Ancestor               As Variant
Public OBJID_Descendants            As Variant
Public OBJID_Members                As Variant
Public OBJID_Iface                  As Variant
Public OBJID_CollectionItem         As Variant
Public OBJID_Collection             As Variant
Public OBJID_ReposTypeLibs          As Variant
Public OBJID_ReposTLBContexts       As Variant
Public OBJID_ReposTypeInfos         As Variant
Public OBJID_ReposTypeLibScopes     As Variant

'---- instances of above
Public OBJID_ReposRootObj           As Variant
Public OBJID_ReposTIM               As Variant

Public OBJID_NULL                   As Variant

'---- SubItems in ListView
Public Const subTypeName            As Integer = 1
Public Const subValue               As Integer = 2

'----- data sources
Public Const repAccessDataSource    As Integer = 1
Public Const repODBCDataSource      As Integer = 2
'</Public>-------------------------------------------------------

 

Function InitGuid(a As Byte, b As Byte, c As Byte, d As Byte, _
    e As Byte, f As Byte, g As Byte, h As Byte, _
    i As Byte, j As Byte, k As Byte, l As Byte, _
    m As Byte, n As Byte, o As Byte, p As Byte) As Variant
    
    Dim Guid(0 To 15) As Byte
    
    Guid(0) = a
    Guid(1) = b
    Guid(2) = c
    Guid(3) = d
    Guid(4) = e
    Guid(5) = f
    Guid(6) = g
    Guid(7) = h
    Guid(8) = i
    Guid(9) = j
    Guid(10) = k
    Guid(11) = l
    Guid(12) = m
    Guid(13) = n
    Guid(14) = o
    Guid(15) = p
    
    InitGuid = Guid
End Function

Private Sub Define_OBJID(ByRef ID As Variant, Uniquifier As Long, Base() As Long)
    Base(4) = Uniquifier
    ID = Base
End Sub

'--------------------------------------------------------------------
'<Purpose> initializes variables to map to internal Repository IDs
'--------------------------------------------------------------------
Sub InitRepository()
    Dim ObjID(0 To 4) As Long
    
    CLSID_RepositoryObject = InitGuid(&HFB, &H70, &H22, &H6E, &H99, &HF7, &HCF, &H11, &H92, &H27, 0, &HAA, 0, &HA1, &HEB, &H95)
    
    '---- Set up the guid portion of the object IDs.
    ObjID(0) = &H90591B0C
    ObjID(1) = &H11CF24F7
    ObjID(2) = &HAA000A92
    ObjID(3) = &H95EBA100

    Call Define_OBJID(OBJID_ClassDef, 0, ObjID)
    Call Define_OBJID(OBJID_InterfaceDef, 1, ObjID)
    Call Define_OBJID(OBJID_CollectionDef, 2, ObjID)
    Call Define_OBJID(OBJID_MethodDef, 3, ObjID)
    Call Define_OBJID(OBJID_PropertyDef, 4, ObjID)
    Call Define_OBJID(OBJID_RelationshipDef, 5, ObjID)
    Call Define_OBJID(OBJID_ReposTypeLib, 6, ObjID)
    Call Define_OBJID(OBJID_ReposRoot, 7, ObjID)
    
    Call Define_OBJID(OBJID_IUnknown, 8, ObjID)
    Call Define_OBJID(OBJID_IDispatch, 9, ObjID)
    Call Define_OBJID(OBJID_IReposDispatch, 10, ObjID)
    Call Define_OBJID(OBJID_IReposTypeInfo, 11, ObjID)
    Call Define_OBJID(OBJID_IClassDef, 12, ObjID)
    Call Define_OBJID(OBJID_IInterfaceDef, 13, ObjID)
    Call Define_OBJID(OBJID_IInterfaceMember, 14, ObjID)
    Call Define_OBJID(OBJID_IPropertyDef, 15, ObjID)
    Call Define_OBJID(OBJID_ICollectionDef, 16, ObjID)
    Call Define_OBJID(OBJID_IRepositoryItem, 17, ObjID)
    Call Define_OBJID(OBJID_IRepositoryObject, 18, ObjID)
    Call Define_OBJID(OBJID_IRelationship, 19, ObjID)
    Call Define_OBJID(OBJID_IAnnotationalProps, 20, ObjID)
    Call Define_OBJID(OBJID_ISummaryInfo, 21, ObjID)
    Call Define_OBJID(OBJID_INamedObject, 22, ObjID)
    Call Define_OBJID(OBJID_IManageReposTypeLib, 23, ObjID)
    Call Define_OBJID(OBJID_IReposTypeLib, 24, ObjID)
    Call Define_OBJID(OBJID_IReposRoot, 25, ObjID)
    
    Call Define_OBJID(OBJID_RClassImplIface, 26, ObjID)
    Call Define_OBJID(OBJID_RIfaceInheritsFromIface, 27, ObjID)
    Call Define_OBJID(OBJID_RIfaceHasMembers, 28, ObjID)
    Call Define_OBJID(OBJID_RColContainsItems, 29, ObjID)
    Call Define_OBJID(OBJID_RContainerContextForReposTLBs, 30, ObjID)
    Call Define_OBJID(OBJID_RReposTLBScopeForReposTypeInfo, 31, ObjID)
    
    Call Define_OBJID(OBJID_Ifaces, 32, ObjID)
    Call Define_OBJID(OBJID_Classes, 33, ObjID)
    Call Define_OBJID(OBJID_Ancestor, 34, ObjID)
    Call Define_OBJID(OBJID_Descendants, 35, ObjID)
    Call Define_OBJID(OBJID_Members, 36, ObjID)
    Call Define_OBJID(OBJID_Iface, 37, ObjID)
    Call Define_OBJID(OBJID_CollectionItem, 38, ObjID)
    Call Define_OBJID(OBJID_Collection, 39, ObjID)
    Call Define_OBJID(OBJID_ReposTypeLibs, 40, ObjID)
    Call Define_OBJID(OBJID_ReposTLBContexts, 41, ObjID)
    Call Define_OBJID(OBJID_ReposTypeInfos, 42, ObjID)
    Call Define_OBJID(OBJID_ReposTypeLibScopes, 43, ObjID)
    
    Call Define_OBJID(OBJID_ReposRootObj, 44, ObjID)
    Call Define_OBJID(OBJID_ReposTIM, 45, ObjID)
    
    Call Define_OBJID(OBJID_NULL, &HFFFFFFFF, ObjID)
    
End Sub

'----------------------------------------------------------------
'<Purpose> checks to see if an object is a property def
'----------------------------------------------------------------
Public Function IsPropertyDef(ThisObject As Variant) As Boolean
    Dim i           As Integer
    Dim Lower       As Integer
    Dim Upper       As Integer
    Dim PropDef     As Variant
    
    '---- cache array boundaries for speed
    Lower = LBound(ThisObject)
    Upper = UBound(ThisObject)
    
    '---- everything must compare
    PropDef = OBJID_PropertyDef
    For i = Lower To Upper
        If (ThisObject(i) <> PropDef(i)) Then
            IsPropertyDef = False
            Exit Function
        End If
    Next
    IsPropertyDef = True
      
End Function

'----------------------------------------------------------------
'<Purpose> returns a key based on the ObjectID
'----------------------------------------------------------------
Public Function ObjectKey(ThisObject As Variant) As String
    Dim i           As Integer
    Dim Lower       As Integer
    Dim Upper       As Integer
    Dim Temp        As String
    Static Counter  As Long
    
    On Error GoTo BadObject
    '---- cache array boundaries for speed
    Lower = LBound(ThisObject.ObjectID)
    Upper = UBound(ThisObject.ObjectID)
    
    '---- assemble ID
    Temp = CStr(ThisObject.ObjectID(Lower))
    For i = Lower + 1 To Upper
        Temp = Temp & "." & CStr(ThisObject.ObjectID(i))
    Next
    Temp = "K" & Temp
    
    ObjectKey = Temp
    On Error GoTo 0
    Exit Function
    
BadObject:
    On Error GoTo 0
    Counter = Counter + 1
    ObjectKey = "K" & Counter

End Function



