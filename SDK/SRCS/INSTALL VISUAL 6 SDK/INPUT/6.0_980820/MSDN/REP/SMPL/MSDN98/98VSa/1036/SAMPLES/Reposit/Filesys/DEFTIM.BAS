Attribute VB_Name = "V2FilesysTIM"
' ------------------------------------------------------------------------
'               Copyright (C) 1998 Microsoft Corporation
'
' You have a royalty-free right to use, modify, and reproduce
' the Sample Application Files (and/or any modified version) in any way
' you find useful, provided that you agree that Microsoft has no warranty,
' obligations or liability for any Sample Application Files.
' ------------------------------------------------------------------------

' ------------------------------------------------------------------------
' This sample project creates the "Files and Directories" tool information
' model in the repository. The model is attached to the repository root via
' the RootDirs collection. After the model is stored in the repository, it
' is populated with a single directory (C:\), and a single file (test.txt).
'
' The model contains two classes: CDir and CFile.
'
' The CDir class implements two interfaces: IDir (default) and IDirItem
' The CFile class implements two interfaces: IFile and IDirItem (default)
'
' IDir supports the property: ChildCount (LONG)
' IDirItem supports the properties: ModDate (LONG), Name (string)
' IFile supports the property: Size (LONG)
'
' IDir has a relationship called "IDir-contains-IDirItem" to IDirItem.
' The corresponding origin collection (at IDir) is called "Children".
' The corresponding destination collection (at IDirItem) is called "Parents".
' The "Children" collection is unique naming.
'
' All of the routines for this project are either contained in this file, or
' in repeng.bas, which is located in the "include" directory.
' ------------------------------------------------------------------------
Declare Function GetWindowsDirectory Lib "kernel32" Alias "GetWindowsDirectoryA" (ByVal lpBuffer As String, ByVal nSize As Long) As Long

' ------------------------------------------------------------------------
' Module-level definitions used for this sample program.
'
' TLBID_FilesAndDirs holds the GUID that gets assigned to the repository
' type library that represents the "Files and Directories" information model.
' The various IID_xxx variants are the interface identifiers that get assigned
' to the three interfaces that are defined by the information model.  The
' OBJID_xxx variants are the object identifiers for the class definition
' objects that are created for the CDir and CFile classes.
' ------------------------------------------------------------------------
Dim TLBID_FilesAndDirs As Variant
Dim IID_IDir As Variant
Dim IID_IDirItem As Variant
Dim IID_IFile As Variant

Dim OBJID_CDir As Variant
Dim OBJID_CFile As Variant

'Constants for use with version merge
Public Const PRIMARY = 1
Public Const SECONDARY = 2

'Variable to keep track of set of actions performed so far
Public gPrevActions As String


' ------------------------------------------------------------------------
' The Main procedure just calls subroutines to initialize repository
' variables, open a connection to the repository, create the model,
' and populate the model with a minimal amount of instance data.
' ------------------------------------------------------------------------
Sub Main()

' Repos is the object that maintains the connection to the repository.
' Root is the object that represents the root of the repository.
Dim Repos As New Repository
Dim Root As RepositoryObject

' Initialize some Repository constants for VB. See repeng.bas to see what
' goes on in this routine.
Call InitRepository

' Find the path to the Windows directory.
Dim WinDir As String
Dim WDLen As Integer
Dim Temp As String * 200
WDLen = GetWindowsDirectory(Temp, 200)
WinDir = Left(Temp, WDLen)
gPrevActions = ""

'==================================================================
'                   Create the Repository
'==================================================================
' For JET, the database file is assumed to be c:\temp\repostry.mdb.
' If one already exists, it will be deleted and a new one created in
' its place.
Dim db_path As String
db_path = "c:\temp\repostry.mdb"
If Dir(db_path) <> "" Then
    Kill db_path
End If
Debug.Print "Creating the repository ..."
Set Root = Repos.Create("DBQ=" & db_path)

' Creation of a repository on SQL Server is done through the
' following statement.
'Set Root = Repos.Create("SERVER=<server name>;DATABASE=<database name>")

'==================================================================
'                   Create the Information Model
'==================================================================
' Initialize the GUIDs for the typelib and interface identifiers.
Call InitSample

' Create the Files and Directories tool information model.  This subroutine
' has logic to handle the case where the information model has already been
' defined.
Debug.Print "Creating the information model ..."
Call CreateTIM(Repos, Root)

On Error GoTo Last:

' Many of the objects that are associated with the repository expose multiple
' interfaces.  One of those interfaces is designated the default interface.
' This is the interface that you get by default when you access an object.
' In this sample, you will see several places where alternate interfaces
' are referenced.  The Root("IReposRoot").RootDirs.xxx syntax a few lines
' further down is an example of this.  The Root object was declared as a
' RepositoryObject.  The default interface for RepositoryObject is the
' IRepositoryObject interface, which inherits base characteristics from the
' IRepositoryItem interface.  The default member of the IRepositoryItem
' interface is the Interface property.  This property provides access to any
' interface that the object exposes, given the name or interface identifier
' of the desired interface.  In this case, RootDirs is a collection that has
' been attached to the IReposRoot interface of the Root object.
Dim ADir As RepositoryObjectVersion
Dim AFile As RepositoryObjectVersion
Dim ARel As Relationship

'**********************************************************************'
'**********************************************************************'
''''''              VERSION  MANAGEMENT  INTERFACES               ''''''
'**********************************************************************'
'**********************************************************************'

' Now that we have made sure that the information model has no instance
' data, we can create the token instance data (one directory and one file).
Repos.Transaction.Begin

' First create an instance of the CDir class.  This is the "C:\" object.
' This creates the first version of the CDir class
Debug.Print "Creating directory object ADir ..."
Set ADir = Repos.CreateObject(OBJID_CDir)       'Create 0th ver of ADir
Call SetDirProps(ADir, 1, 1000, "DirA Ver1")    'Set props on ADir

' Add the CDir version to the Root's RootDir collection. We can get to the
' IReposRoot interface either by name or OBJID
Call Root.Interface(OBJID_IReposRoot).RootDirs.Add(ADir, "C:\")
Repos.Transaction.Commit                        'Commit the transaction

' Next create an instance of the CFile class. This is the "test.txt" object.
Dim ARelCol As IRelationshipCol                 'Note declaration
Repos.Transaction.Begin
Debug.Print "Creating file version AFile ..."
Set AFile = Repos.CreateObject(OBJID_CFile)     'Create 0th ver of AFile
Call SetFileProps(AFile, 1111, 1111, "FileA Ver1") 'Set props on AFile
AFile.FreezeVersion                             'Freeze ver 0 of file
Call ADir("IDir").Children.Add(AFile, "Dir-to-AFile") ' Add ver to tgt obj col
Repos.Transaction.Commit                        'Commit the transaction

' Obtain the relationship instance "Dir-to-AFile"
Set ARelCol = ADir("IDir").Children             'Rel'ship col interface
Set ARel = ARelCol.item("Dir-to-AFile")         'Get rel'ship out of it

' Create the next version of AFile, set properties on it, and
' add it to the target version collection of the relationship "Dir-to-AFile"
Repos.Transaction.Begin
Dim AFile2 As RepositoryObjectVersion
Debug.Print "Creating file version AFile2 ..."
Set AFile2 = AFile.CreateVersion                'Create new Ver of file
Call SetFileProps(AFile2, 2222, 1111, "FileA Ver2") 'Set props on AFile2
ARel.TargetVersions.Add AFile2                  'Add ver to dst ver col
Repos.Transaction.Commit                        'Transaction commit

' Create another version of the file object, set properties on it, and
' add it to the target version collection of the relationship "Dir-to-AFile"
Repos.Transaction.Begin
Dim AFile3 As RepositoryObjectVersion
Debug.Print "Creating file version AFile3 ..."
Set AFile3 = AFile.CreateVersion                'Create a new Br of the file
Call SetFileProps(AFile3, 3333, 3333, "FileA Ver3") 'Set props on AFile3
ARel.TargetVersions.Add AFile3                  'Include AFile3 in rel'ship
AFile3.FreezeVersion                            'Freeze AFile3
Repos.Transaction.Commit                        'Transaction commit

' Now that several versions of the file object have been created, we can
' merge version 3 into version 2. Version 3 is the SECONDARY version in the
' following merge
Repos.Transaction.Begin
Debug.Print "Merging file versions ..."
AFile2.MergeVersion AFile3, SECONDARY          'Primary is AFile2
Repos.Transaction.Commit                        'Transaction commit

'==================================================================
'                   Version graph navigation APIs
'==================================================================
Dim ObjVerCol As VersionCol
Dim SuccVerCol As VersionCol
Dim PredVerCol As VersionCol
Dim DstVerCol As VersionCol
Dim AFileTmp As RepositoryObjectVersion

Dim SuccVerCount As Long
Dim PredVerCount As Long
Dim DstVerCount As Long

Set ObjVerCol = AFile.ObjectVersions
Set SuccVerCol = AFile2.SuccessorVersions
Set PredVerCol = AFile2.PredecessorVersions
Set DstVerCol = ARel.TargetVersions
Set AFileTmp = AFile2.PredecessorCreationVersion 'Creation predecessor

'Print version information
Debug.Print "Printing out version information ..."
PrintVersionInfo AFile
PrintVersionInfo AFile2
PrintVersionInfo AFile3
PrintVersionInfo AFileTmp

' Iterate through the object versions collection
Dim i As Integer
Dim Ver As RepositoryObjectVersion
Dim ObjVerCount As Long
PrintVerColInfo AFile.ObjectVersions

'**********************************************************************'
'**********************************************************************'
''''''              IREPOSITORY2  INTERFACE  INHERITANCE          ''''''
'**********************************************************************'
'**********************************************************************'
Dim ARepos As IRepository2
Dim ObjID As Variant
Dim ExtVID As Variant
Dim IntVID As Variant

Set ARepos = AFile.Repository                   'Get the repos from version
Set AFileTmp = ARepos.version(AFile2.VersionID) 'Get ver from (ext) VersionID
ExtVID = AFile2.VersionID                       'Ext VersionID of AFile2
IntVID = ARepos.VersionIDToInternalID(ExtVID)   'Int VersionID of AFile2
Set AFileTmp = ARepos.version(IntVID)           'Materialize version

IntVID = AFile2.VersionInternalID               'Int VersionID of AFile2
ExtVID = ARepos.InternalIDToVersionID(IntVID)   'Int VersionID of AFile2
Set AFileTmp = ARepos.version(ExtVID)           'Materialize version

ObjID = AFile2.ObjectID
Set AFileTmp = ARepos.object(ObjID)             'Get ver from objID
                                                'Resolves to last created one
Set AFileTmp = ARepos.object(AFile2.InternalID) 'Get ver from INTID
                                                'Resolves to last created one

 
'**********************************************************************'
'**********************************************************************'
''''''                     VERSIONED  RELATIONSHIP                ''''''
'**********************************************************************'
'**********************************************************************'
' Iterate through the "Children" collection of ADir. Each "item" call
' resolves the relationship to the last created version
Repos.Transaction.Begin
For i = 1 To ADir("IDir").Children.Count
    PrintVersionInfo ADir("IDir").Children.item(i)
    Next i
Repos.Transaction.Commit
    
'Enumerator on relationship collection
Dim Child As RepositoryObjectVersion
For Each Child In ADir("IDir").Children
    Debug.Print Child("IDirItem").Name
    Next

'**********************************************************************'
'**********************************************************************'
''''''                       WORKSPACE  INTERFACE                 ''''''
'**********************************************************************'
'**********************************************************************'
Dim AWks As Workspace
Dim WksRepos As IRepository2
Dim WksVer As IRepositoryObjectVersion
Dim WksDir As IRepositoryObjectVersion
Dim WksFile As IRepositoryObjectVersion
Dim ItemDir As IWorkspaceItem
Dim ItemFile As IWorkspaceItem

'Create a new workspace
Repos.Transaction.Begin
Debug.Print "Creating workspace ..."
Set AWks = Repos.CreateObject(OBJID_Workspace)
Set WksRepos = AWks

'Naming on workspace
Set WksVer = AWks
'WksVer.Name = "Workspace 1"

' Add ADir and AFile2 to the workspace
Set WksDir = AWks.Contents.Add(ADir)
Set WksFile = AWks.Contents.Add(AFile2)
Repos.Transaction.Commit
    
' Target version collection is workspace scoped
Dim TgtVer As RepositoryObjectVersion
Set TgtVer = WksDir("IDir").Children.item(1)    'Should return AFile2, not
PrintVersionInfo TgtVer                         'the last created one
    
' Check out a version to the workspace for modification
Repos.Transaction.Begin
If WksFile.IsFrozen = False Then
    Set ItemFile = WksFile
    Debug.Print "Checking out AFile2 for modification ..."
    ItemFile.Checkout
    End If

' Modify the checked out version
WksFile("IDirItem").ModDate = 9797
Repos.Transaction.Commit

' Check in the changes
Repos.Transaction.Begin
Debug.Print "Checking in AFile2 after modification ..."
ItemFile.Checkin
Repos.Transaction.Commit

'Enumerate the Contents collection of the workspace
Debug.Print "Printing out workspace contents ..."
For Each Ver In AWks.Contents
    Debug.Print Ver("IDirItem").Name, Ver("IDirItem").ModDate
    Next

' End of the code
MsgBox "Over!", vbOKOnly, "V2FileSys"
Unload frm_DirStatus
Unload frm_Status
Exit Sub

Last:
End Sub
Sub SetDirProps(Dir As RepositoryObjectVersion, ChildCount As Long, ModDate As Long, Name As String)
    Dir("IDir").ChildCount = ChildCount          'Set property
    Dir("IDirItem").ModDate = ModDate            'Set property
    Dir("IDirItem").Name = Name                  'Set property
End Sub
Sub SetFileProps(File As RepositoryObjectVersion, Size As Long, ModDate As Long, Name As String)
    File("IFile").Size = Size                    'Set property
    File("IDirItem").ModDate = ModDate           'Set property
    File("IDirItem").Name = Name                 'Set property
End Sub
Sub PrintVersionInfo(V As RepositoryObjectVersion)
    Debug.Print "Printing information for version name ..." + V("IDirItem").Name
    Debug.Print "PredecessorCount = ", V.PredecessorVersions.Count
    Debug.Print "SuccessorCount   = ", V.SuccessorVersions.Count
End Sub
Sub PrintVerColInfo(VCol As VersionCol)
    Dim Ver As RepositoryObjectVersion
    For Each Ver In VCol
        PrintVersionInfo Ver
        Next
End Sub
Sub PrintSuccessorGraph(version As Object)
Dim item As Object

PrintVersionInfo version

For Each item In version.SuccessorVersions
    PrintSuccessorGraph item
Next

End Sub
Sub PrintPredecessorGraph(version As Object)
Dim item As Object

PrintVersionInfo version

For Each item In version.PredecessorVersions
    PrintPredecessorGraph item
Next

End Sub
' ------------------------------------------------------------------------
' This subroutine initialize the repository type library and interface
' identifiers that are assigned to this information model.  Since all classes
' and interfaces in a tool information model are also automation objects, they
' must be identifiable by unique identifiers.
' ------------------------------------------------------------------------
Sub InitSample()

' See the repeng.bas file to see what goes on in the InitGuid function.
TLBID_FilesAndDirs = InitGuid(&HE0, &H1D, &H4C, &HD2, &HB9, &H9B, &HCF, &H11, &H92, &H15, 0, &HAA, 0, &HA1, &HEB, &H95)
IID_IDir = InitGuid(&HE1, &H1D, &H4C, &HD2, &HB9, &H9B, &HCF, &H11, &H92, &H15, 0, &HAA, 0, &HA1, &HEB, &H95)
IID_IDirItem = InitGuid(&HE2, &H1D, &H4C, &HD2, &HB9, &H9B, &HCF, &H11, &H92, &H15, 0, &HAA, 0, &HA1, &HEB, &H95)
IID_IFile = InitGuid(&HE3, &H1D, &H4C, &HD2, &HB9, &H9B, &HCF, &H11, &H92, &H15, 0, &HAA, 0, &HA1, &HEB, &H95)

End Sub

' ------------------------------------------------------------------------
' This subroutine creates the "Files and Directories tool information model.
'
' The model contains two classes: CDir and CFile.
'
' The CDir class implements two interfaces: IDir and IDirItem
' The CFile class implements two interfaces: IFile and IDirItem
' ------------------------------------------------------------------------
Sub CreateTIM(Repos As Repository, Root As RepositoryObject)

' Declare various objects and variants that we will use to create the
' information model.  The CLSID_xxx variants are class identifier GUIDs.
' The objects are the various "definition" objects that define the new
' information model in the repository.  Each one of these types of objects
' are also RepositoryObject objects.
Dim ReposObj As RepositoryObject
Dim TypeLib As ReposTypeLib
Dim CLSID_CDir As Variant
Dim CLSID_CFile As Variant
Dim CDir As ClassDef
Dim CFile As ClassDef
Dim IDir As InterfaceDef
Dim IDirItem As InterfaceDef
Dim IFile As InterfaceDef
Dim IRoot As InterfaceDef
Dim RelshipDef As RelationshipDef
Dim ColDef As CollectionDef
Dim IReposVersion As InterfaceDef

' Attempt to access the repository type library object that represents the
' "Files and Directories" information model.  If an error occurs, this means
' the information model has not been defined, so jump to the error handler
' to define the model. (This is really the "normal" case).  Otherwise, if the
' access attempt succeeds, the information model already exists, so just put
' out a debug print message and skip creating the information model.
On Error GoTo DoCreateTim
Set TypeLib = Root("IManageReposTypeLib").ReposTypelibs("Files and Directories")
Debug.Print "TIM already loaded..."
On Error GoTo 0

' Set the object identifiers for the CDir and CFile class definition objects
' for the calling routine.
OBJID_CDir = TypeLib.ReposTypeInfos("CDir").ObjectID
OBJID_CFile = TypeLib.ReposTypeInfos("CFile").ObjectID

Exit Sub

' ------------------------------------------------------------------------
' Error handler that creates the "Files and Directories tool information model.
' ------------------------------------------------------------------------
DoCreateTim:

On Error GoTo 0

' Start a transaction.
Repos.Transaction.Begin

' Create a Repository Type Library.
Set TypeLib = Root("IManageReposTypeLib").CreateTypeLib(OBJID_NULL, "Files and Directories", TLBID_FilesAndDirs)

'Create class identifiers for CDir and CFile class definitions
CLSID_CDir = InitGuid(&HAE, &H7B, &H15, &H82, &H3C, &HD1, &H11, &HD0, &HAB, &HD5, 0, &HAA, 0, &HA1, &H4D, &H34)
CLSID_CFile = InitGuid(&HAE, &H7B, &H15, &H83, &H3C, &HD1, &H11, &HD0, &HAB, &HD5, 0, &HAA, 0, &HA1, &H4D, &H34)

' Create a Directory class definition.
Set CDir = TypeLib.CreateClassDef(OBJID_NULL, "CDir", CLSID_CDir)

' Attach IRepositoryObjectVersion interface to CDir class
Set IReposVersion = Repos.object(OBJID_IRepositoryObjectVersion)
Call CDir.AddInterface(IReposVersion)

' Create a Directory interface definition.
Set IDir = CDir.CreateInterfaceDef(OBJID_NULL, "IDir", IID_IDir, Nothing, "Default")

' Create a "Count of Children" property definition.
Call IDir.CreatePropertyDef(OBJID_NULL, "ChildCount", 100, SQL_C_ULONG)

' Create a Directory Item interface definition.
Set IDirItem = CDir.CreateInterfaceDef(OBJID_NULL, "IDirItem", IID_IDirItem)

' Create a Modification Date property definition.
Call IDirItem.CreatePropertyDef(OBJID_NULL, "ModDate", 101, SQL_C_ULONG)

' Create a DirItem version property definition.
Call IDirItem.CreatePropertyDef(OBJID_NULL, "Name", 102, SQL_C_CHAR)

' Create a File class.
Set CFile = TypeLib.CreateClassDef(OBJID_NULL, "CFile", CLSID_CFile)

' Attach IRepositoryObjectVersion interface to CFile class
Call CFile.AddInterface(IReposVersion)

' Create a File interface definition.
Set IFile = CFile.CreateInterfaceDef(OBJID_NULL, "IFile", IID_IFile)

' Attach the Directory Item interface.
Call CFile.AddInterface(IDirItem, "Default")

' Create a File Size property definition.
Call IFile.CreatePropertyDef(OBJID_NULL, "Size", 103, SQL_C_ULONG)

' Define the IDir-contains-IDirItem relationship.
Set RelshipDef = TypeLib.CreateRelationshipDef(OBJID_NULL, "IDir_Contains_IDirItem")

' Create the origin collection for this relationship and attach it to the IDir
' interface.
Call IDir.CreateRelationshipColDef(OBJID_NULL, "Children", 104, True, COLLECTION_NAMING + COLLECTION_UNIQUENAMING, RelshipDef)

' Create the destination collection for this relationship and attach it to the IDirItem
' interface.
Set ColDef = IDirItem.CreateRelationshipColDef(OBJID_NULL, "Parents", 105, False, 0, RelshipDef)

' Set the minimum cardinality for the destination collection. Note: setting the
' properties of a newly created definition object should always be done as a part
' of the transaction that creates the definition object.  Some validity checking and
' various other internal repository engine operations are deferred until the commit.
ColDef.MinCount = 1

' Define the IRoot-contains-IDir relationship.
Set RelshipDef = TypeLib.CreateRelationshipDef(OBJID_NULL, "IRoot_Contains_IDir")

' Create the origin collection and attach it to the IReposRoot interface.
Set IRoot = Repos.object(OBJID_IReposRoot)
Call IRoot.CreateRelationshipColDef(OBJID_NULL, "RootDirs", 106, True, COLLECTION_NAMING + COLLECTION_UNIQUENAMING, RelshipDef)

' Create the destination collection and attach it to the IDir interface.
Set ColDef = IDir.CreateRelationshipColDef(OBJID_NULL, "Roots", 107, False, 0, RelshipDef)

' Set up the object identifiers of the two new classes for the calling routine.
Set ReposObj = CDir
OBJID_CDir = ReposObj.ObjectID
Set ReposObj = CFile
OBJID_CFile = ReposObj.ObjectID

' Commit the transaction.
Repos.Transaction.Commit
End Sub

