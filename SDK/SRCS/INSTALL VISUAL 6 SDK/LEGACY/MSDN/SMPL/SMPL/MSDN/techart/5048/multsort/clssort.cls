VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "clsSort"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit
Public Event SortComplete(vntSortedData As Variant)

'*************************************************************************
'Asynchronous function call - caches this object and the array to
'be sorted, and then enables a Timer which will fire and do the sorting work
'*************************************************************************
Public Sub Asynchronous_SelectionSort(vntUnsortedData As Variant)

    'Cache the array to be sorted
    g_vntUnsortedData = vntUnsortedData

    'Cache the instance of this object
    Set g_objSort = Me
    
    'Enable the Timer for 100 ms
    'When the Timer fires, the sort work will be done but
    'in the mean time, we return to the client application
    'EnableOneShot is in the modSortHelper module
    EnableOneShot 100

End Sub

'****************************************************************
'Synchronous_SelectionSort - Merely sorts the array, and returns
'when finished
'*****************************************************************
Public Sub Synchronous_SelectionSort(vntUnsortedData As Variant)

'Merely sort the array
SelectionSort vntUnsortedData

End Sub


Friend Sub FireSortComplete(vntSortedData As Variant)
    RaiseEvent SortComplete(vntSortedData)
End Sub
