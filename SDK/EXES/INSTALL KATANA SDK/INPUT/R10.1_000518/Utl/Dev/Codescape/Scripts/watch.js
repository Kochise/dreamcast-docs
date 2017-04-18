BPTYPE_WATCH=1;
BPSCRIPT_JSCRIPT	=	1;
BPLOCMASKLOW20 =	5;						//	Mask low 20 bits
triggerCount	=	10;						//	Hit break 10 times before triggering

RemoveBreakpoint( 0 );						//	Remove any previous breakpoint
breakID = CreateBreakpoint( BPTYPE_WATCH, 0 );							//	Create a watch breakpoint
SetBreakpointLocationMask( breakID, BPLOCMASKLOW20 );					//	Mask low 20 bits
SetBreakpointCondition( breakID, "", 0, triggerCount, false, false );	//	Set the trigger count
SetBreakpointLog( breakID,  "\"PC=0x%x\",pc", true );					//	Set to log PC when break occurs
SetBreakpointScript( breakID, "watch.js", BPSCRIPT_JSCRIPT, "", false );	//	Reset this breakpoint
Run();																	//	Start running



