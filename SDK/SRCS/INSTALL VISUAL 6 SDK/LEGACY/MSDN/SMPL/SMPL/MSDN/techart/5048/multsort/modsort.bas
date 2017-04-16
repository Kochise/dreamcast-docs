Attribute VB_Name = "modSortHelper"
Option Explicit

Private Declare Function SetTimer Lib "user32" (ByVal hWnd As Long, ByVal nIDEvent As Long, ByVal uElapse As Long, ByVal lpTimerFunc As Long) As Long
Private Declare Function KillTimer Lib "user32" (ByVal hWnd As Long, ByVal nIDEvent As Long) As Long


Public g_vntUnsortedData As Variant
Public g_objSort As clsSort
Public g_TimerID As Long

Public Sub EnableOneShot(ByVal ulTime As Long)
    g_TimerID = SetTimer(0, 0, ulTime, AddressOf TimerCallback)
End Sub

Public Sub TimerCallback(ByVal hWnd As Long, ByVal uMsg As Long, ByVal idEvent As Long, ByVal dwTime As Long)
    
    'Kill the timer - we do not need it any more
    KillTimer 0, g_TimerID
    
    'Quicksort the Global array
    SelectionSort g_vntUnsortedData
    
    'Raise the event to indicate sort is finished
    g_objSort.FireSortComplete g_vntUnsortedData
    
    'Cleanup and exit
    Set g_objSort = Nothing
    
End Sub

Public Sub SelectionSort(TempArray As Variant)

   Dim MaxVal As Variant
   Dim MaxIndex As Integer
   Dim i, j As Integer
 
      'Step through the elements in the array starting with the
      'last element in the array
      For i = UBound(TempArray) To 1 Step -1
 
          'Set MaxVal to the element in the array and save the
          'index of this element as MaxIndex
          MaxVal = TempArray(i)
          MaxIndex = i
 
          'Loop through the remaining elements to see if any is
          'larger than MaxVal. If it is then set this element
          'to be the new MaxVal.
          For j = 1 To i
              If TempArray(j) > MaxVal Then
                 MaxVal = TempArray(j)
                 MaxIndex = j
              End If
          Next j
 
          'If the index of the largest element is not i, then
          'exchange this element with element i
          If MaxIndex < i Then
              TempArray(MaxIndex) = TempArray(i)
              TempArray(i) = MaxVal
          End If
      Next i
 
 
End Sub
