//	Note: this does not do anything useful it just demonstrates the current script commands and how they can be called

function WriteSomeRegisters()
{
	WriteRegister( "fr0", 3.14159 ); 
	WriteRegister( "r0", "0xabcdef" );
	WriteRegister( "pc", "main + 0x30" );
}

function ReadSomeRegisters()
{
	Write( "Value of pc = " + ReadRegister( "pc" ) )
	Write( "Value of r0 = " + ReadRegister( "r0" ) )
}

function LoadSomeBinary()
{
	LoadBinaryFile( "d:\\projects\\codescape\\satmon.bin", "201392128" );
	LoadBinaryFile( "d:\\projects\\codescape\\satmon.bin", 201392128 );
	LoadBinaryFile( "d:\\projects\\codescape\\satmon.bin", "0xc010000" );
	LoadBinaryFile( "d:\\projects\\codescape\\satmon.bin", "main" );
}

function DisplayParameters()
{
	NumParams	=	GetParamCount()
	Write( "Number of parameters = " + NumParams );
	for( i = 0; i < NumParams; i++ )
	{
		Write( "Parameter " + i + " = " + GetParam( i - 1 ) )
	}
}

function ReadSomeMemory()
{
	Write( "Byte at main = " + ReadByte( "main" ) );
	Write( "Word at main + 4 = " + ReadWord( "main + 4" ) );
	Write( "Long at main + 8 = " + ReadLong( "main + 8" ) ); 
}

function WriteSomeMemory()
{
	WriteByte( "main", 255 );
	WriteWord( "main + 4", "0xabcd" );
	WriteLong( "main + 8", "0xfedcba" );
}


HardReset();
SoftReset(); 
DisplayParameters();
LoadSomeBinary();
LoadProgramFile( "e:\\projects\\maketest\\hello.elf" );
SetBreakpoint( "main" );
Run();
while( IsRunning() != 0 ) 
{	
	;
}
ReadSomeRegisters();
WriteSomeRegisters();
ReadSomeMemory();
WriteSomeMemory();
ReadSomeMemory();
ClearAllBreakpoints();
Write( "Script complete." );
