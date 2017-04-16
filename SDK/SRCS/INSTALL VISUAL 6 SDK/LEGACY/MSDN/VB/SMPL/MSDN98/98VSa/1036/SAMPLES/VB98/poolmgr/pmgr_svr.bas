Attribute VB_Name = "modPoolMngr"
Option Explicit

' Note: Ceci est un exemple simple de gestionnaire de regroupement.
' Pour les besoins de la démonstration, il n'y a pas de recherche
' d'une liste des composants à initialiser. il crée une liste initiale
' avec le composant du projet Interface comme seul membre de la liste.

' L'extension de cette implémentation pour que votre environnement supporte une liste d'objets personnalisée ne devrait pas poser de problème. 
' Le schéma d'allocation peut aussi être plus sophistiqué pour 
' refléter les besoins spécifiques de gestion de votre environnement.

Type ProjectInfoStruc
  Prev As Integer
  Next As Integer
  nFirstSvrNode As Integer
  strProgID As String
  intCurUseCount As Integer
  intMinUseCount As Integer
  intMaxUseCount As Integer
  intCloseDelay As Integer
  bLookAheadCreate As Integer
End Type

Type ServerInstanceStruc
  Prev As Integer
  Next As Integer
  ObjHandle As Object
  DeallocTime As Date
  bInUse As Integer
End Type

Global Const gnINFO_TYPE = 0
Global Const gnINST_TYPE = 1
Global gaPrjInfo() As ProjectInfoStruc
Global gaSvrInst() As ServerInstanceStruc
Global gnFirstPrjNode As Integer
  ' Conventions d'implémentation de la liste chaînée:
  ' - une racine est toujours disponible à l'index mnXXXX_ROOT. 
  ' - quand node.prev = node, ce nœud est alors le premier membre de la liste.
  ' - quand node.next = gnNIL, ce nœud est alors le dernier membre de la liste.
Const mINFO_FREE_ROOT = 0
Const mINST_FREE_ROOT = 0
Global Const gnNIL = -1
Const mnMAX_NODES = 32000

Const mstrINI_POOL_MNGR_FILE_NAME = "poolmngr.ini"
Const mstrINI_POOL_MNGR_KEY = "PoolManager"
Const mstrINI_POOL_SVR_KEY = "PoolSvr"

#If Win32 Then
  Declare Function GetPrivateProfileString Lib "kernel32" Alias "GetPrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Long
  Declare Function WritePrivateProfileString Lib "kernel32" Alias "WritePrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpString As Any, ByVal lplFileName As String) As Long
#Else
  Declare Function GetPrivateProfileString Lib "Kernel" (ByVal Secname1$, ByVal Keynamei$, ByVal Def1$, ByVal Ret1$, ByVal Size1%, ByVal lpFileName$) As Integer
  Declare Function WritePrivateProfileString% Lib "Kernel" (ByVal lpAppName$, ByVal lpKeyName$, ByVal lpString$, ByVal lpFileName$)
#End If

Sub Main()
   frmPoolMngr.Show
End Sub

Sub InitProjectArray()
  Dim strPrjSettings As String
  Dim bDone As Integer
  Dim i As Integer
  Dim j As Integer
  Dim nPrjNode As Integer
  Dim nPrevPrjNode As Integer
  Dim nSvrNode As Integer
  Dim intPtr1  As Integer
  Dim intPtr2  As Integer
  
' Initialise la liste chaînée et définit les références de la racine sur elles-mêmes.
ReDim gaPrjInfo(0) As ProjectInfoStruc              ' Alloue mINFO_FREE_ROOT
gaPrjInfo(mINFO_FREE_ROOT).Prev = mINFO_FREE_ROOT
gaPrjInfo(mINFO_FREE_ROOT).Next = mINFO_FREE_ROOT
ReDim gaSvrInst(0) As ServerInstanceStruc           ' Alloue mINST_FREE_ROOT
gaSvrInst(mINST_FREE_ROOT).Prev = mINST_FREE_ROOT
gaSvrInst(mINST_FREE_ROOT).Next = mINST_FREE_ROOT

i = 0
  While Not bDone
    strPrjSettings = IniStringGet(mstrINI_POOL_SVR_KEY & Format$(i))
    If strPrjSettings = "" Then
      If i = 0 Then
        InitPoolSvrList
      Else
        bDone = True
      End If
    Else
      nPrjNode = NodeGet(gnINFO_TYPE)
      If nPrjNode = gnNIL Then
        bDone = True
      Else
        If i = 0 Then
          gnFirstPrjNode = nPrjNode
          nPrevPrjNode = nPrjNode
        Else
          gaPrjInfo(nPrevPrjNode).Next = nPrjNode
        End If
        gaPrjInfo(nPrjNode).Prev = nPrevPrjNode
        gaPrjInfo(nPrjNode).Next = gnNIL
        gaPrjInfo(nPrjNode).nFirstSvrNode = gnNIL
        gaPrjInfo(nPrjNode).intCurUseCount = 0
        
        ' Parcourt la chaîne d'initialisation et 
        ' initialise la structure d'information du projet.
        intPtr1 = 1
        intPtr2 = InStr(intPtr1, strPrjSettings, ",")
        If intPtr2 > 0 Then gaPrjInfo(nPrjNode).strProgID = Mid$(strPrjSettings, intPtr1, intPtr2 - intPtr1)
        intPtr1 = intPtr2 + 1
        intPtr2 = InStr(intPtr1, strPrjSettings, ",")
        If intPtr2 > 0 Then gaPrjInfo(nPrjNode).intMinUseCount = Val(Mid$(strPrjSettings, intPtr1, intPtr2 - intPtr1))
        intPtr1 = intPtr2 + 1
        intPtr2 = InStr(intPtr1, strPrjSettings, ",")
        If intPtr2 > 0 Then gaPrjInfo(nPrjNode).intMaxUseCount = Val(Mid$(strPrjSettings, intPtr1, intPtr2 - intPtr1))
        intPtr1 = intPtr2 + 1
        intPtr2 = InStr(intPtr1, strPrjSettings, ",")
        If intPtr2 > 0 Then gaPrjInfo(nPrjNode).intCloseDelay = Val(Mid$(strPrjSettings, intPtr1, intPtr2 - intPtr1))
        gaPrjInfo(nPrjNode).bLookAheadCreate = Val(Mid$(strPrjSettings, intPtr2 + 1))
        
        ' Initialise le gestionnaire de regroupement pour minimiser la taille.
        For j = 0 To gaPrjInfo(nPrjNode).intMinUseCount - 1
          nSvrNode = GetNewServerNode(nPrjNode)
          If nSvrNode = gnNIL Then Exit For
          Set gaSvrInst(nSvrNode).ObjHandle = CreateObject(gaPrjInfo(nPrjNode).strProgID)
          gaSvrInst(nSvrNode).bInUse = False
        Next j
        
        i = i + 1
        nPrevPrjNode = nPrjNode
      End If
    End If
  Wend
End Sub

Sub InitPoolSvrList()
  ' Définit une liste initiale d'entrée de composants que le 
  ' gestionnaire de regroupement peut utiliser pour une démonstration.
  Const strINTERFACE_PROG_ID = "InterfaceProj.ServerInterface"
  Const strPASSTHRU_PROG_ID = "PassThruProj.PassThruClass"
  Dim strTmp As String
   
  strTmp = strINTERFACE_PROG_ID & "," & "1,6,60,-1"
  IniStringSet mstrINI_POOL_SVR_KEY & "0", strTmp
  strTmp = strPASSTHRU_PROG_ID & "," & "1,6,60,-1"   'ProgId, MinPoolSize, MaxPoolSize, CloseDelay, LookAheadCreate
  IniStringSet mstrINI_POOL_SVR_KEY & "1", strTmp
End Sub

Sub NodeAppend(rnNodeType As Integer, rnBaseNode As Integer, rnNewNode As Integer)
 ' Ajoute rnNewNode à côté de rnBaseNode.
  If rnNodeType = gnINFO_TYPE Then
    gaPrjInfo(rnNewNode).Next = gaPrjInfo(rnBaseNode).Next
    gaPrjInfo(rnNewNode).Prev = rnBaseNode
    If gaPrjInfo(rnBaseNode).Next <> gnNIL Then
      gaPrjInfo(gaPrjInfo(rnBaseNode).Next).Prev = rnNewNode
    End If
    gaPrjInfo(rnBaseNode).Next = rnNewNode
  
  ElseIf rnNodeType = gnINST_TYPE Then
    gaSvrInst(rnNewNode).Next = gaSvrInst(rnBaseNode).Next
    gaSvrInst(rnNewNode).Prev = rnBaseNode
    If gaSvrInst(rnBaseNode).Next <> gnNIL Then
      gaSvrInst(gaSvrInst(rnBaseNode).Next).Prev = rnNewNode
    End If
    gaSvrInst(rnBaseNode).Next = rnNewNode
  End If
End Sub

Function NodeGet(rnNodeType As Integer) As Integer
 ' Retourne un nouveau nœud immédiatement après la racine (ROOT).
  NodeGet = gnNIL
  
  If rnNodeType = gnINFO_TYPE Then
    If gaPrjInfo(mINFO_FREE_ROOT).Next = mINFO_FREE_ROOT Then
      If Not NodeGrowLinkedList(gnINFO_TYPE, 2) Then Exit Function
    End If
    NodeGet = gaPrjInfo(mINFO_FREE_ROOT).Next
    gaPrjInfo(mINFO_FREE_ROOT).Next = gaPrjInfo(gaPrjInfo(mINFO_FREE_ROOT).Next).Next
    gaPrjInfo(gaPrjInfo(mINFO_FREE_ROOT).Next).Prev = mINFO_FREE_ROOT
  
  ElseIf rnNodeType = gnINST_TYPE Then
    If gaSvrInst(mINST_FREE_ROOT).Next = mINST_FREE_ROOT Then
      If Not NodeGrowLinkedList(gnINST_TYPE, 8) Then Exit Function
    End If
    NodeGet = gaSvrInst(mINST_FREE_ROOT).Next
    gaSvrInst(mINST_FREE_ROOT).Next = gaSvrInst(gaSvrInst(mINST_FREE_ROOT).Next).Next
    gaSvrInst(gaSvrInst(mINST_FREE_ROOT).Next).Prev = mINST_FREE_ROOT
  End If
End Function

Sub CloseOpenServers()
  Dim nPrjNode As Integer
  Dim nSvrNode As Integer
  On Error GoTo cosErr

  nPrjNode = gnFirstPrjNode
  While nPrjNode <> gnNIL
    nSvrNode = gaPrjInfo(nPrjNode).nFirstSvrNode
    While nSvrNode <> gnNIL
      Set gaSvrInst(nSvrNode).ObjHandle = Nothing
      nSvrNode = gaSvrInst(nSvrNode).Next
    Wend
    nPrjNode = gaPrjInfo(nPrjNode).Next
  Wend
GoTo cosExit

cosErr:
  DisplayError
  Resume cosExit

cosExit:
End Sub
Sub DisplayError()
  #If gbDEBUG2 Then
    MsgBox Error$
  #End If
End Sub
Function GetNewServerNode(rnProjNode As Integer) As Integer
  ' Obtient un nouveau nœud de composant et initialise ses références.
  Dim nSvrNode As Integer
  On Error GoTo gnsnErr
    
  nSvrNode = NodeGet(gnINST_TYPE)
  GetNewServerNode = nSvrNode
  If nSvrNode = gnNIL Then Exit Function    ' Doit donner une erreur.
      
  gaSvrInst(nSvrNode).Prev = nSvrNode
  gaSvrInst(nSvrNode).Next = gaPrjInfo(rnProjNode).nFirstSvrNode
  If gaPrjInfo(rnProjNode).nFirstSvrNode <> gnNIL Then
    gaSvrInst(gaPrjInfo(rnProjNode).nFirstSvrNode).Prev = nSvrNode
  End If
  gaPrjInfo(rnProjNode).nFirstSvrNode = nSvrNode
  GoTo gnsnExit

gnsnErr:
  DisplayError
  Resume gnsnExit

gnsnExit:
End Function
Function NodeGrowLinkedList(rnNodeType As Integer, rnIncrease As Integer) As Integer
  Dim i As Integer
  Dim nLast As Integer
  Dim nFirst As Integer
  On Error GoTo gllErr

  NodeGrowLinkedList = False
  If rnIncrease < 1 Then Exit Function
  If rnNodeType = gnINFO_TYPE Then
    nLast = UBound(gaPrjInfo)
    If nLast + rnIncrease < mnMAX_NODES Then ReDim Preserve gaPrjInfo(nLast + rnIncrease)
      
    nFirst = nLast + 1
    gaPrjInfo(gaPrjInfo(mINFO_FREE_ROOT).Next).Prev = nLast + rnIncrease
    gaPrjInfo(nLast + rnIncrease).Next = gaPrjInfo(mINFO_FREE_ROOT).Next
    gaPrjInfo(mINFO_FREE_ROOT).Next = nFirst
    gaPrjInfo(nFirst).Prev = mINFO_FREE_ROOT

    gaPrjInfo(nFirst).Next = nFirst + 1
    For i = nFirst + 1 To nLast + rnIncrease - 1
      gaPrjInfo(i).Prev = i - 1
      gaPrjInfo(i).Next = i + 1
    Next i
    gaPrjInfo(i).Prev = i - 1
  Else
    nLast = UBound(gaSvrInst)
    If nLast + rnIncrease < mnMAX_NODES Then ReDim Preserve gaSvrInst(nLast + rnIncrease)
    
    nFirst = nLast + 1
    gaSvrInst(gaSvrInst(mINST_FREE_ROOT).Next).Prev = nLast + rnIncrease
    gaSvrInst(nLast + rnIncrease).Next = gaSvrInst(mINST_FREE_ROOT).Next
    gaSvrInst(mINST_FREE_ROOT).Next = nFirst
    gaSvrInst(nFirst).Prev = mINST_FREE_ROOT

    gaSvrInst(nFirst).Next = nFirst + 1
    For i = nFirst + 1 To nLast + rnIncrease - 1
      gaSvrInst(i).Prev = i - 1
      gaSvrInst(i).Next = i + 1
    Next i
    gaSvrInst(i).Prev = i - 1
  End If
  NodeGrowLinkedList = True
  GoTo gllExit

gllErr:
  DisplayError
  Resume gllExit

gllExit:
End Function

Sub NodeRemove(rnNodeType As Integer, nRemoveNode As Integer)
 ' Extrait un nœud suivant d'un frère.
  If rnNodeType = gnINFO_TYPE Then
    gaPrjInfo(gaPrjInfo(nRemoveNode).Prev).Next = gaPrjInfo(nRemoveNode).Next
    If gaPrjInfo(nRemoveNode).Next <> gnNIL Then
      gaPrjInfo(gaPrjInfo(nRemoveNode).Next).Prev = gaPrjInfo(nRemoveNode).Prev
    End If
  ElseIf rnNodeType = gnINST_TYPE Then
    gaSvrInst(gaSvrInst(nRemoveNode).Prev).Next = gaSvrInst(nRemoveNode).Next
    If gaSvrInst(nRemoveNode).Next <> gnNIL Then
      gaSvrInst(gaSvrInst(nRemoveNode).Next).Prev = gaSvrInst(nRemoveNode).Prev
    End If
  Else
    Exit Sub
  End If
  NodeReturn rnNodeType, nRemoveNode
End Sub

Sub NodeReturn(rnNodeType As Integer, nReturnNode As Integer)
 ' Insère nReturnNode immédiatement après la racine (ROOT).
  If rnNodeType = gnINFO_TYPE Then
    gaPrjInfo(nReturnNode).Next = gaPrjInfo(mINFO_FREE_ROOT).Next
    gaPrjInfo(gaPrjInfo(mINFO_FREE_ROOT).Next).Prev = nReturnNode
    gaPrjInfo(mINFO_FREE_ROOT).Next = nReturnNode
    gaPrjInfo(nReturnNode).Prev = mINFO_FREE_ROOT
  ElseIf rnNodeType = gnINST_TYPE Then
    gaSvrInst(nReturnNode).Next = gaSvrInst(mINST_FREE_ROOT).Next
    gaSvrInst(gaSvrInst(mINST_FREE_ROOT).Next).Prev = nReturnNode
    gaSvrInst(mINST_FREE_ROOT).Next = nReturnNode
    gaSvrInst(nReturnNode).Prev = mINST_FREE_ROOT
  End If
End Sub

Function IniStringGet(KeyString As String) As String
Dim strIniBuffer As String * 255
On Error GoTo gisErr

  #If Win32 Then
    Dim lRetLen As Long
    lRetLen = GetPrivateProfileString(mstrINI_POOL_MNGR_KEY, KeyString, "", strIniBuffer, 255, mstrINI_POOL_MNGR_FILE_NAME)
    If lRetLen > 0 Then IniStringGet = Left$(strIniBuffer, lRetLen)
  #Else
    Dim nRetLen As Integer
    nRetLen = GetPrivateProfileString(mstrINI_POOL_MNGR_KEY, KeyString, "", strIniBuffer, 255, mstrINI_POOL_MNGR_FILE_NAME)
    If nRetLen > 0 Then IniStringGet = Left$(strIniBuffer, nRetLen)
  #End If

  GoTo gisExit

gisErr:
  DisplayError
  Resume gisExit

gisExit:
End Function

Sub IniStringSet(KeyString As String, ValString As String)
  Dim sIniGroupKey As String
  On Error GoTo sisErr

  #If Win32 Then
  Dim lTmp As Long
  lTmp = WritePrivateProfileString(mstrINI_POOL_MNGR_KEY, KeyString, ValString, mstrINI_POOL_MNGR_FILE_NAME)
  #Else
  Dim ntmp As Integer
  ntmp = WritePrivateProfileString(mstrINI_POOL_MNGR_KEY, KeyString, ValString, mstrINI_POOL_MNGR_FILE_NAME)
  #End If
  GoTo sisExit

sisErr:
  DisplayError
  Resume sisExit

sisExit:
End Sub

