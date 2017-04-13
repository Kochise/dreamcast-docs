Attribute VB_Name = "basVB4SMS32"
Option Explicit
'//****************************************************************************
'//
'//  Copyright (c) 1996, Microsoft Corporation
'//
'//  File:  VB4SMS32.BAS
'//
'//  History:
'//
'//      Gary Fuehrer, SEA   3/5/96      Created.
'//
'//****************************************************************************
'
'The Declare statements that used to appear in this module are no longer
'necessary because they are now declared in the type library.  Use the
'Object Browser to view these declarations (see the View menu).  However,
'Because of some "features" of VB4, some of the declarations in the
'type library can not be used and must be overridden with a Declare statement.
'Only the functions for which this is the case appear here.

'Because of yet another "feature" of VB4, some of the functions also needed a
'VB function wrapper.  These VB wrappers appear in this module as well.
'
'

'// ====================================================================
'//      Version number API.
'// ====================================================================
'
'  See also the Object Browser for declarations in the type library.
'
'
'// ====================================================================
'//      Engine APIs.
'// ====================================================================
'
   Declare Function SmsDescribeFolderU& Lib "vb4sms32.olb" Alias "SmsDescribeFolderVB" (tObjectity As BASETYPE, ByVal dwTag As Long, pFolderInfo() As FOLDER_INFO)
'
   Declare Function SmsEnumContainers& Lib "vb4sms32.olb" Alias "SmsEnumContainersVB" (ContainerInfos() As FOLDER_INFO, pCount As Long)
'
   Declare Function SmsEnumFolders& Lib "vb4sms32.olb" Alias "SmsEnumFoldersVB" (FolderInfos() As FOLDER_INFO, pCount As Long)
'
   Declare Function SmsEnumFilters& Lib "vb4sms32.olb" Alias "SmsEnumFiltersVB" (FilterInfos() As FILTER_INFO, pCount As Long)
'
'  See also the Object Browser for declarations in the type library.
'
'
'// ====================================================================
'//      Connection APIs.
'// ====================================================================
'
   Declare Function SmsDataSourceConnect& Lib "vb4sms32.olb" Alias "SmsDataSourceConnectVB" (pDataSource As SQL_CONNECT_PARAMS, phConn As Long)
'
'  See also the Object Browser for declarations in the type library.
'
'
'// ====================================================================
'//      Container APIS.
'// ====================================================================
'
   Declare Function SmsPopulate& Lib "vb4sms32.olb" Alias "SmsPopulateVB" (ByVal hContainer As Long, ByVal dwOptions As Long, pNotify As Any)
'
'  See also the Object Browser for declarations in the type library.
'
'
'// ====================================================================
'//  Folder (collection) APIs.
'//  A collection contains other things, that is it can have embedded
'//  collections and it can also have properties (scalars).
'// ====================================================================
'
'  See also the Object Browser for declarations in the type library.
'
'
'// ====================================================================
'//  Scalar APIs.
'// ====================================================================
'
   Declare Function SmsGetNextScalarU& Lib "vb4sms32.olb" Alias "SmsGetNextScalarVB" (ByVal hFolder As Long, pScalar() As SCALAR)
'
   Declare Function SmsGetScalarByNameU& Lib "vb4sms32.olb" Alias "SmsGetScalarByNameVB" (ByVal hFolder As Long, ByVal pszName As String, pScalar() As SCALAR)
'
   Declare Function SmsSetScalarU& Lib "vb4sms32.olb" Alias "SmsSetScalarVB" (ByVal hFolder As Long, pScalar() As SCALAR)
'
'  See also the Object Browser for declarations in the type library.
'
'
'// ====================================================================
'//  FilterContainer APIs
'// ====================================================================
'
'  See also the Object Browser for declarations in the type library.
'
'
'// ====================================================================
'//  Filter APIs
'// ====================================================================
'
   Declare Function SmsGetToken& Lib "vb4sms32.olb" Alias "SmsGetTokenVB" (ByVal hObject As Long, ByVal iIndex As Long, pTokenInfo As TOKEN)
'
   Declare Function SmsAddToken& Lib "vb4sms32.olb" Alias "SmsAddTokenVB" (ByVal hObject As Long, opAndOr As ANDOR, pTokenInfo As TOKEN, ByVal iIndex As Long)
'
   Declare Function SmsEnumObjects& Lib "vb4sms32.olb" Alias "SmsEnumObjectsVB" (ByVal hConnection As Long, ByVal pszObjectType As String, pPredecessors() As String, ByVAl CtPredecessors As Long, pObjects() As OBJDESCRIPTOR, pCtObjects As Long)
'
'  See also the Object Browser for declarations in the type library.


Function SmsDescribeFolder&(tObjectity As BASETYPE, ByVal dwTag As Long, pFolderInfo As FOLDER_INFO)
    Dim FolderInfos(0) As FOLDER_INFO
    Dim lRet&

    lRet& = SmsDescribeFolderU&(tObjectity, dwTag, FolderInfos)
    If (lRet& = SMS_OK) Then pFolderInfo = FolderInfos(0)

    SmsDescribeFolder& = lRet&
End Function
Function SmsGetNextScalar&(ByVal hFolder As Long, pScalar As SCALAR)
    Dim Scalars(0) As SCALAR
    Dim lRet&

    lRet& = SmsGetNextScalarU&(hFolder, Scalars)
    If (lRet& = SMS_OK) Then pScalar = Scalars(0)

    SmsGetNextScalar& = lRet&
End Function
Function SmsGetScalarByName&(ByVal hFolder As Long, ByVal pszName As String, pScalar As SCALAR)
    Dim Scalars(0) As SCALAR
    Dim lRet&

    lRet& = SmsGetScalarByNameU&(hFolder, pszName, Scalars)
    If (lRet& = SMS_OK) Then pScalar = Scalars(0)

    SmsGetScalarByName& = lRet&
End Function

Function SmsSetScalar&(ByVal hFolder As Long, pScalar As SCALAR)
    Dim Scalars(0) As SCALAR

    Scalars(0) = pScalar
    SmsSetScalar& = SmsSetScalarU&(hFolder, Scalars)
End Function

