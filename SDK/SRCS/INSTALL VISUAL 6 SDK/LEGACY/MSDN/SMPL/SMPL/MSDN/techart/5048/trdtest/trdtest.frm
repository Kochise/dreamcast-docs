VERSION 5.00
Begin VB.Form frmThreadTest 
   Caption         =   "Form1"
   ClientHeight    =   2655
   ClientLeft      =   3480
   ClientTop       =   4005
   ClientWidth     =   4560
   LinkTopic       =   "Form1"
   ScaleHeight     =   2655
   ScaleWidth      =   4560
   Begin VB.CommandButton Command2 
      Caption         =   "Synchronously Sort 4 Arrays"
      Height          =   615
      Left            =   480
      TabIndex        =   1
      Top             =   600
      Width           =   3615
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Asynchronously Sort 4 Arrays"
      Height          =   615
      Left            =   480
      TabIndex        =   0
      Top             =   1560
      Width           =   3615
   End
End
Attribute VB_Name = "frmThreadTest"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private Const MAXTHREADS As Long = 4
Private Const NUMTRIALS As Long = 3

Private WithEvents objSort1 As clsSort
Attribute objSort1.VB_VarHelpID = -1
Private WithEvents objSort2 As clsSort
Attribute objSort2.VB_VarHelpID = -1
Private WithEvents objSort3 As clsSort
Attribute objSort3.VB_VarHelpID = -1
Private WithEvents objSort4 As clsSort
Attribute objSort4.VB_VarHelpID = -1
Private Const MAXRAND As Long = 1000
Private Const LOGFILE As String = "c:\Log.txt"

Private ulRandom1(1 To MAXRAND) As Long
Private ulRandom2(1 To MAXRAND) As Long
Private ulRandom3(1 To MAXRAND) As Long
Private ulRandom4(1 To MAXRAND) As Long
Private vntArray(1 To MAXTHREADS) As Variant

Private ulNumberArraysSorted As Long

Private dwTimeBefore As Long
Private dwTimeAfter As Long
Private dwTimeElapsed(1 To NUMTRIALS) As Long
Private Declare Function GetTickCount Lib "kernel32" () As Long
Private ulNumberOfTrial As Long
Private iFileNumber As Integer


'****************************************************
'This calls the asynchronous function to sort the
'arrays asynchronously. The start time is gained
'before th ecalls, and the finish time is retrieved
'in the CheckIfFinished subroutine, which is called in the
'events that are fired when the arrays have been sorted
'*******************************************************
Private Sub Command1_Click()


Dim ulCounter As Long

    'Setup the arrays with random data
    SetupData
    
    'Create the objects from the server
    Set objSort1 = New clsSort
    Set objSort2 = New clsSort
    Set objSort3 = New clsSort
    Set objSort4 = New clsSort
    
    'Reinitialize this variable=0
    ulNumberArraysSorted = 0
    
    'Start to measure time taken
    dwTimeBefore = GetTickCount()
    
    'Make each asynchronous call
    objSort1.Asynchronous_SelectionSort (vntArray(1))
    objSort2.Asynchronous_SelectionSort (vntArray(2))
    objSort3.Asynchronous_SelectionSort (vntArray(3))
    objSort4.Asynchronous_SelectionSort (vntArray(4))

    'Finish time in CheckIfFinished call

End Sub

'*****************************************
'Sets up the array with random data
'*****************************************
Private Sub SetupData()
    
    Dim i As Long
    Dim f As Single
    
    For i = MAXRAND To 1 Step -1
        Randomize
        f = Rnd()
        ulRandom1(i) = f * MAXRAND
        ulRandom2(i) = 2 * f * MAXRAND
        ulRandom3(i) = 3 * f * MAXRAND
        ulRandom4(i) = 4 * f * MAXRAND
    Next i
    
    vntArray(1) = ulRandom1
    vntArray(2) = ulRandom2
    vntArray(3) = ulRandom3
    vntArray(4) = ulRandom4
    
End Sub


Private Sub CheckIfFinished()

ulNumberArraysSorted = ulNumberArraysSorted + 1

'If this is the MAXTHREADS time we have called this function
'then we have finished sorting MAXTHREADS number of arrays
'and we can keep the time it took in dwTimeElapsed(ulNumberOfTrial)
If (ulNumberArraysSorted = MAXTHREADS) Then
    
    'Stop the clock
    dwTimeAfter = GetTickCount()
    
    frmThreadTest.MousePointer = vbHourglass
    
    If (ulNumberOfTrial < NUMTRIALS) Then
        ulNumberOfTrial = ulNumberOfTrial + 1
        dwTimeElapsed(ulNumberOfTrial) = dwTimeAfter - dwTimeBefore
    End If
    
    If (ulNumberOfTrial < NUMTRIALS) Then
        'Repeat trial - i.e. sort 4 more arrays again
        Command1_Click
    Else
        'Write out the results - we have finished NUMTRIALS of this test
        WriteToLog "Asynchronous"
        frmThreadTest.MousePointer = vbArrow
    End If
End If

End Sub

Private Sub objSort1_SortComplete(vntSortedData As Variant)
    vntArray(1) = vntSortedData
    CheckIfFinished
End Sub

Private Sub objSort2_SortComplete(vntSortedData As Variant)
    vntArray(2) = vntSortedData
    CheckIfFinished
End Sub

Private Sub objSort3_SortComplete(vntSortedData As Variant)
    vntArray(3) = vntSortedData
    CheckIfFinished
End Sub

Private Sub objSort4_SortComplete(vntSortedData As Variant)
    vntArray(4) = vntSortedData
    CheckIfFinished
End Sub


'*****************************************************
'This merely calls the synchronous SelectionSort 4 times,
'and the time to complete all 4 function calls is kept
'*********************************************************
Private Sub Command2_Click()

Dim ulCounter As Long

frmThreadTest.MousePointer = vbHourglass

    For ulCounter = 1 To NUMTRIALS

    'Setup the arrays with random data
    SetupData
    
    'Create the objects from the server
    Set objSort1 = New clsSort

    'Start to measure time taken
    dwTimeBefore = GetTickCount()
    
    'Make each synchronous call
    objSort1.Synchronous_SelectionSort (vntArray(1))
    objSort1.Synchronous_SelectionSort (vntArray(2))
    objSort1.Synchronous_SelectionSort (vntArray(3))
    objSort1.Synchronous_SelectionSort (vntArray(4))

    'Get the Finish Time
    dwTimeAfter = GetTickCount()
    
    dwTimeElapsed(ulCounter) = dwTimeAfter - dwTimeBefore
    
    Next ulCounter
 
'Write out the results
WriteToLog "Synchronous"
frmThreadTest.MousePointer = vbArrow
    
    
End Sub


'*****************************************************
'Standard function used to write the results out to a Text
'file
'*****************************************************
Private Sub WriteToLog(ByVal strDescription As String)

Dim ulCounter As Long

        iFileNumber = FreeFile
        Open LOGFILE For Output As iFileNumber
        
        Print #iFileNumber, strDescription
        
        For ulCounter = 1 To NUMTRIALS
            Print #iFileNumber, dwTimeElapsed(ulCounter)
        Next ulCounter
        
        Close (iFileNumber)
        MsgBox "Finished"
End Sub
