/**
 **
 **	reitp.r
 **
 **	mrc resource script
 **
 **/

#include "mrc\types.r"
include "wlm.rsc";
#include "ftab.r"
//#include "ole2ui.r"


// Include afxrc-generated resources.

#ifdef DEBUG
include "dbugitm.res";
#endif
include "richedit.res";
include "reitp.res";

// Our WLM hello application bundle - just the application icon.

resource 'BNDL' (128)
{
	'CAPO',	// signature
	0,		// version id
	{
		'ICN#',
		{
			0, 128;
		};
		'FREF',
		{
			0, 128;
		};
	};
};

// our application icon

resource 'ICN#' (128)
{
	{
	$"00000000"
	$"00000000"
	$"20007f80"
	$"2409ffe0"
	$"06bbccf0"
	$"09bb0c30"
	$"21230c30"
	$"240b0c30"
	$"0cbb0c30"
	$"09bb0c30"
	$"21233f30"
	$"240bfff0"
	$"0cbbccf0"
	$"09bb0c30"
	$"21230c30"
	$"240b0c30"
	$"0cbb0c30"
	$"09bb0c30"
	$"21233f30"
	$"240bfff0"
	$"0cbbc0f0"
	$"09bb0030"
	$"01200000"
	$"00000000"
	$"00000000"
	$"00000000"
	$"04508aa0"
	$"0450daa0"
	$"0550aaa0"
	$"05508800"
	$"06de8aa0"
	$"00000000";

	$"00000000"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"7ffffffe"
	$"00000000"
	};
};


resource 'SIZE' (-1)
{
	dontSaveScreen,
	acceptSuspendResumeEvents,	// we do our own clipboard conversions when switched in and out
	enableOptionSwitch,
	canBackground,				// we can background; we don't currently, but our sleep value
							// guarantees we don't hog the Mac while we are in the background
	multiFinderAware,			// this says we do our own activate/deactivate; don't fake us out
	backgroundAndForeground,		// this is definitely not a background-only application!
	dontGetFrontClicks,			// change this is if you want "do first click" behavior like the Finder
	ignoreChildDiedEvents,		// essentially, I'm not a debugger (sub-launching)
	is32BitCompatible,			// this app can be run in 32-bit address space
	isHighLevelEventAware,
	localAndRemoteHLEvents,
	notStationeryAware,
	dontUseTextEditServices,
	reserved,
	reserved,
	reserved,
	800 * 1024,
	600 * 1024	
};
