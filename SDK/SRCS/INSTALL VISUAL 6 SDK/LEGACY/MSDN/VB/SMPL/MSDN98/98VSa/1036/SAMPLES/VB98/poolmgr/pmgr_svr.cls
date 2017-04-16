VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "PoolMngrClass"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Public Function objGetProjInstance(rstrProgID As String, rnProjID As Integer) As Object
' Note: Cette procédure présume que la classe PoolMngrClass a été créée avec la
' propriété Instancing ayant la valeur MultiUse et n'est pas réentrante! Retourne une référence à un
' objet Automation pour le projet requis. Retourne rnProjID < 0 si aucune instance
' n'est disponible ou s'il y a une erreur.
Dim nPrjNode As Integer
Dim nSvrNode As Integer
Dim bFoundFree As Integer
Dim nFirstFree As Integer
On Error GoTo gciError

rnProjID = -1
nPrjNode = gnFirstPrjNode

While nPrjNode <> gnNIL And rnProjID < 0
  If gaPrjInfo(nPrjNode).strProgID = rstrProgID Then
    If gaPrjInfo(nPrjNode).intCurUseCount >= gaPrjInfo(nPrjNode).intMaxUseCount Then Exit Function
    nSvrNode = gaPrjInfo(nPrjNode).nFirstSvrNode
    bFoundFree = False
    While nSvrNode <> gnNIL And Not bFoundFree
      If gaSvrInst(nSvrNode).bInUse Then
        nSvrNode = gaSvrInst(nSvrNode).Next
      Else
        bFoundFree = True
      End If
    Wend
      
    If Not bFoundFree Then
      nSvrNode = GetNewServerNode(nPrjNode)
      If nSvrNode = gnNIL Then Exit Function
      Set gaSvrInst(nSvrNode).ObjHandle = CreateObject(rstrProgID)
    End If
      
    Set objGetProjInstance = gaSvrInst(nSvrNode).ObjHandle
    gaSvrInst(nSvrNode).DeallocTime = "12/31/9999"
    gaSvrInst(nSvrNode).bInUse = True
    gaPrjInfo(nPrjNode).intCurUseCount = gaPrjInfo(nPrjNode).intCurUseCount + 1
    rnProjID = nSvrNode
    
    If gaPrjInfo(nPrjNode).bLookAheadCreate And _
          gaPrjInfo(nPrjNode).intCurUseCount < gaPrjInfo(nPrjNode).intMaxUseCount Then
      ' Enregistre nPrjNode et définit un délai d'attente.
    End If
  Else
    nPrjNode = gaPrjInfo(nPrjNode).Next
  End If
Wend

  If rnProjID < 0 Then
  ' objGetClassInstance = Nothing <<Provoque une erreur! Que pouvez-vous renvoyer?
  End If
GoTo gciExit

gciError:
'  objGetClassInstance = Nothing <<Provoque une erreur! Que pouvez-vous renvoyer?
  Resume gciExit
  
gciExit:
End Function
Public Function ReturnProjInstance(ByVal rstrProgID As String, rnSvrNode As Integer) As Integer
' Note: Cette procédure présume que la classe a été créée avec la propriété Instancing
' ayant la valeur MultiUse et n'est pas réentrante. Renvoie False en cas d'erreur.
Dim nPrjNode As Integer
Dim bDone As Integer
On Error GoTo rpiError

ReturnProjInstance = False
If rnSvrNode < 0 Then Exit Function
If Not gaSvrInst(rnSvrNode).bInUse Then Exit Function
nPrjNode = gnFirstPrjNode

While nPrjNode <> gnNIL And Not bDone
  If gaPrjInfo(nPrjNode).strProgID = rstrProgID Then
    gaPrjInfo(nPrjNode).intCurUseCount = gaPrjInfo(nPrjNode).intCurUseCount - 1
    If gaPrjInfo(nPrjNode).intCurUseCount >= gaPrjInfo(nPrjNode).intMinUseCount Then
      If gaPrjInfo(nPrjNode).intCloseDelay > 0 Then
        ' Enregistre nPrjNode et définit un délai d'attente et supprime le noeud plus tard.
        gaSvrInst(rnSvrNode).DeallocTime = Now
      Else
        Set gaSvrInst(rnSvrNode).ObjHandle = Nothing
        If gaPrjInfo(nPrjNode).nFirstSvrNode = rnSvrNode Then
          gaPrjInfo(nPrjNode).nFirstSvrNode = gaSvrInst(gaPrjInfo(nPrjNode).nFirstSvrNode).Next
        End If
        NodeRemove gnINST_TYPE, rnSvrNode
      End If
      bDone = True
    Else
      gaSvrInst(rnSvrNode).bInUse = False
    End If
    ReturnProjInstance = True
  End If
  nPrjNode = gaPrjInfo(nPrjNode).Next
Wend
GoTo rpiExit

rpiError:
Resume rpiExit

rpiExit:
End Function

