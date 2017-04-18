' This script does not do anything useful other than demonstrate the functions available

HardReset()
SoftReset() 
Call DisplayParameters()
Call LoadSomeBinary()
LoadProgramFile "e:\projects\maketest\hello.elf"
SetBreakpoint "main"
Run()
Dim Running
Running = 1
Do 
	Running	=	IsRunning	
Loop Until Running = 0
Call ReadSomeRegisters()
Call WriteSomeRegisters()
Call ReadSomeMemory()
Call WriteSomeMemory()
Call ReadSomeMemory()
ClearAllBreakpoints
Write( "Script complete." )


Sub WriteSomeRegisters()
	WriteRegister "fr0", 3.14159 
	WriteRegister "r0", "0xabcdef"
	WriteRegister "pc", "main + 0x30"
End Sub

Sub ReadSomeRegisters()
	Write( "Value of pc = " & ReadRegister( "pc" ) )
	Write( "Value of r0 = " & ReadRegister( "r0" ) )
End Sub

Sub LoadSomeBinary()
	LoadBinaryFile "d:\\projects\\codescape\\satmon.bin", "201392128"
	LoadBinaryFile "d:\\projects\\codescape\\satmon.bin", 201392128
	LoadBinaryFile "d:\\projects\\codescape\\satmon.bin", "0xc010000"
	LoadBinaryFile "d:\\projects\\codescape\\satmon.bin", "main" 
End Sub

Sub DisplayParameters()
	NumParams	=	GetParamCount
	Write( "Number of parameters = " & NumParams )
	For i = 1 To NumParams
		Write( "Parameter " & i & " = " & GetParam( i - 1 ) )
	Next
End Sub

Sub ReadSomeMemory()
	Write( "Byte at main = " & ReadByte( "main" ) )
	Write( "Word at main + 4 = " & ReadWord( "main + 4" ) )
	Write( "Long at main + 8 = " & ReadLong( "main + 8" ) ) 
End Sub	   

Sub WriteSomeMemory()
	WriteByte "main", 255
	WriteWord "main + 4", "0xabcd" 
	WriteLong "main + 8", "0xfedcba"
End Sub
