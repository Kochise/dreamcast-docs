if( GetParamCount() == 1 )
{
	HardReset();
	ClearAllBreakpoints();
	if( LoadBinary( GetParam( 0 ), "0x0c010000" ) )
	{
		SetBreakpoint( "0xac000000" );
		WriteRegister( "pc", "0x0c010000" );
		Run();
		Write( "Waiting for operation to complete..." );
		while( IsRunning() )
		{
			;
		}
		var result = ReadLong( "0x0c00000c" );
		if( ( result & 0xffff0000 ) == 0x00010000 )
		{
			Write( "Succeeded" )
		}
		else
		{
			Write( "Failed: Error code = " + result );
		}
	}
	else
	{
		Write( "Could not load file " + GetParam( 0 ) );

	}
}
else
{
	Write( "Error:- You must supply the name of the boot rom file." );
}
