Attribute VB_Name = "basGlobal"
'=======================================================================
'Company:       Microsoft© Corporation
'Date   :       14 October 1997
'Project:       HelpDesk
'Module :       BAS module global to all HelpDesk servers
'Synopsis :     This BAS module is has all the constants which would be used
'               in all Servers written in HelpDesk project.
'=======================================================================

Option Explicit

'=======================================================================
Public Const scSpace = " "
Public Const scSpaceCommaSpace = " , "
Public Const scSQ = "'"
'=======================================================================

'=======================================================================
'This enumeration represents the different array offsets that can be used
'in array manipulation throughout HelpDesk

Public Enum enumArrayOffsets
    icZeroDim = 0
    icOneDim = 1
    icTwoDim = 2
    icThreeDim = 3
    icFourDim = 4
    icFiveDim = 5
    icSixDim = 6
End Enum
'=======================================================================
