//      Copyright (c) 1995-1998 Microsoft Corporation
//      @doc    EXTERNAL

/*      @module keybd.h       |

Non Win32 defines and structs for WinCE keyboard.

*/
#ifndef __KEYBD_H__
#define __KEYBD_H__

#ifdef __cplusplus
extern "C" {
#endif


/*		@doc    EXTERNAL DRIVERS
		@type   KEY_STATE_FLAGS | Flags for keyboard events and shift state.

@comm These flags perform a number of functions:

@comm The low order bits are used to keep track of a key state.  This
allows using 256 UINT8's for the key state array just like windows does
already.

@comm The upper bits keep track of shift state on a per key basis.  Since
we are not maintaining a complete key state array for each task, this
gives us some extra info fairly cheaply.

@comm The KeyStateDownFlag does double duty internal to the driver to
identify key up or key down events.

@comm KeyShiftDeadFlag is set by the <f KeybdDriverVKeyToUnicode> function
to signify that the character generated is a dead character.

@comm KeyShiftNoCharacterFlag is set by the <f KeybdDriverVKeyToUnicode>
function to signify that there is no valid character to generate for the
given virtual key event.  This may be the case on a key up event or a key
which only changes the shift state.

@comm The control, alt, shift and capital flags are set by the <f
KeybdDriverVKeyToUnicode> function to encapsulate the shift state when the
character was generated.

@xref
	<tab><f KeybdDriverVKeyToUnicode><nl>
	<tab><f KeybdEventCallback><nl>

*/
typedef UINT32  KEY_STATE_FLAGS;

#define KeyStateToggledFlag			0x0001	//	Key is toggled.
#define KeyStateGetAsyncDownFlag	0x0002	//	Key went down since last GetAsyncKey call.
#define KeyStateReserved4			0x0004
#define KeyStateReserved8			0x0008
#define KeyStateReserved10			0x0010
#define KeyStateReserved20			0x0020
#define KeyStatePrevDownFlag		0x0040	//	Key was previously down.
#define KeyStateDownFlag			0x0080	//	Key is currently down.

#define KeyStateKeyEventFlag		0x80000000	//	Internal
#define KeyShiftAnyCtrlFlag			0x40000000  //  L or R control is down.
#define KeyShiftAnyShiftFlag		0x20000000  //  L or R shift is down.
#define KeyShiftAnyAltFlag			0x10000000  //  L or R alt is down.
#define KeyShiftCapitalFlag			0x08000000  //  VK_CAPITAL is toggled.
#define KeyShiftLeftCtrlFlag		0x04000000  //  L control is down.
#define KeyShiftLeftShiftFlag		0x02000000  //  L shift is down.
#define KeyShiftLeftAltFlag			0x01000000  //  L alt is down.
#define KeyShiftLeftWinFlag			0x00800000  //  L Win key is down.
#define KeyShiftRightCtrlFlag		0x00400000  //  R control is down.
#define KeyShiftRightShiftFlag		0x00200000  //  R shift is down.
#define KeyShiftRightAltFlag		0x00100000  //  R alt is down.
#define KeyShiftRightWinFlag		0x00080000  //  R Win key is down.
#define KeyShiftReserved40000		0x00040000  //  Reserved.
#define KeyShiftDeadFlag			0x00020000  //  Corresponding char is dead char.
#define KeyShiftNoCharacterFlag		0x00010000  //  No corresponding char.

#define	KeyShiftLanguageFlag1		0x00008000  //  Use for language specific shifts.
#define KeyShiftKeybdEventFlag		0x00004000	//	Not for external use.

#define KeyShiftUseVKNullFlag		0x00002000  //  Not for external use.
#define KeyShiftNumLockFlag			0x00001000  //  NumLock toggled state.
#define KeyShiftReserved800			0x00000800  //  Reserved.
#define KeyShiftReserved400			0x00000400  //  Reserved.
#define KeyShiftReserved200			0x00000200  //  Reserved.
#define KeyShiftReserved100			0x00000100  //  Reserved.

// Japanese keyboard
#define	KeyShiftKanaFlag			KeyShiftLanguageFlag1  //  Kana lock is toggled.


#define KeyStateIsDown(Flags)           (Flags&KeyStateDownFlag)
#define KeyStateIsPrevDown(Flags)       (Flags&KeyStatePrevDownFlag)
#define KeyStateIsToggled(Flags)        (Flags&KeyStateToggledFlag)
#define KeyStateIsDownTransition(Flags) ( KeyStateIsDown(Flags) && !KeyStateIsPrevDown(Flags) )


#define COUNT_VKEYS     256


/*		@doc    EXTERNAL DRIVERS
		@type   KEY_STATE       | Array of virtual key states.

*/
typedef UINT8   KEY_STATE[COUNT_VKEYS];




//
// KeyboardDriverGetDeviceInfo query capability definitions
//


/*		@doc	EXTERNAL DRIVERS
		@const	ULONG | KBDI_VKEY_TO_UNICODE_INFO_ID |

Id for <f KeybdDriverGetInfo> to get Unicode conversion info.

@xref
	<tab><f KeybdDriverGetInfo><nl>
	<tab><t KBDI_VKEY_TO_UNICODE_INFO><nl>
	<tab><f KeybdDriverVKeyToUnicode>

*/
#define KBDI_VKEY_TO_UNICODE_INFO_ID	0


/*      @doc    EXTERNAL DRIVERS KEYBD_DRIVER
		@struct	KBDI_VKEY_TO_UNICODE_INFO |

Info required to set up for Unicode conversion.

@xref
	<tab><f KeybdDriverGetInfo><nl>
	<tab><c KBDI_VKEY_TO_UNICODE_INFO_ID><nl>
	<tab><f KeybdDriverVKeyToUnicode><nl>
	<tab><t TO_UNICODE_STATE>

@comm cbToUnicodeState is the number of bytes necessary to store the
driver specific state which is required to generate characters from a
virtual key.  For example, a French keyboard driver may need to remember
that an accent key was previously pressed in order to decide on a specific
Unicode character to generate for a virtual key.  This value may be 0 if
no other state besides <t KEY_STATE> is required to generate characters,
e.g., English keyboard drivers.

@comm cMaxToUnicodeCharacters is the maximum number of characters that may
be generated by a call to KeybdDriverVKeyToUnicode.  For example, if a
user presses the '^' key and then the 'b' key, a French keyboard driver
would generate the two characters, '^' 'b', when the second key is
pressed.  Note that this is not the count of bytes required to store the
characters, it is just the number of characters.

*/
struct KBDI_VKEY_TO_UNICODE_INFO
	{
	UINT32  cbToUnicodeState;				// @FIELD 	Count of bytes required
											//			for state info for Unicode
											//			character generation.
	UINT32  cMaxToUnicodeCharacters;		// @FIELD	Maximum number of characters
											//			generated for a single virtual key.
	};




/*		@doc	EXTERNAL DRIVERS
		@const	ULONG | KBDI_AUTOREPEAT_INFO_ID |

Id for <f KeybdDriverGetInfo> to get keyboard auto-repeat info.

@xref
	<tab><f KeybdDriverGetInfo><nl>
	<tab><t KBDI_AUTOREPEAT_INFO><nl>
	<tab><c KBDI_AUTOREPEAT_SELECTIONS_INFO_ID>

*/
#define KBDI_AUTOREPEAT_INFO_ID	1



/*      @doc    EXTERNAL DRIVERS
		@struct	KBDI_AUTOREPEAT_INFO |

Info about the keyboard autorepeat capabilities and settings.

@xref
	<tab><f KeybdDriverGetInfo><nl>
	<tab><c KBDI_AUTOREPEAT_INFO_ID><nl>
	<tab><c KBDI_AUTOREPEAT_SELECTIONS_INFO_ID>

@comm cInitialDelaysSelectable gives the number of initial delays which
may be set.  Query again using <c KBDI_AUTOREPEAT_SELECTIONS_INFO_ID> to
get the actual values available.

@comm cRepeatRatesSelectable is similar to cInitialDelaysSelectable except
that it gives the number of repeat rates available.

*/

struct KBDI_AUTOREPEAT_INFO
	{
	INT32	CurrentInitialDelay;		// @FIELD	Current initial delay in milliseconds.
	INT32	CurrentRepeatRate;			// @FIELD	Current repeat rate in keys per second.
	INT32	cInitialDelaysSelectable;	// @FIELD	Number of initial delays selectable.
	INT32	cRepeatRatesSelectable;		// @FIELD	Number of repeat rates supported.
	};


/*		@doc	EXTERNAL DRIVERS
		@const	ULONG | KBDI_AUTOREPEAT_SELECTIONS_INFO_ID |

Id for <f KeybdDriverGetInfo> to get keyboard auto-repeat selections info.

@xref
	<tab><f KeybdDriverGetInfo><nl>
	<tab><c KBDI_AUTOREPEAT_INFO_ID><nl>
	<tab><t KBDI_AUTOREPEAT_INFO><nl>

@comm When <f KeybdDriverGetInfo> is called with this value, the lpOutput
parameter should be a pointer to an array of INT32's to hold the selection
info.  The initial delays will be put at the beginning of the array
followed by the repeat rate selections.  The number of initial delay
values is determined by calling <f KeybdDriverGetInfo> using <c
KBDI_AUTOREPEAT_INFO_ID> and looking at the returned
cInitialDelaysSelectable field.  If this value is -1, there will be two
(2) values, the min and max and the initial delay may be set to any value
in this range.  This value may be 0 if the initial delay is not settable.
Similarly, if cRepeatRatesSelectable is 0, there will be no repeat rate
information.  If it is -1, there will be two (2) values, the min and max.

Initial delay values are in milliseconds.  Repeat rates are in keys per
second.

*/
#define KBDI_AUTOREPEAT_SELECTIONS_INFO_ID	2

// INTERNATIONAL
#define KBDI_KEYBOARD_STATUS_ID 3


#define KBDI_KEYBOARD_PRESENT	0x0001	
#define KBDI_KEYBOARD_ENABLED	0x0002
#define KBDI_KEYBOARD_ENTER_ESC	0x0004
#define KBDI_KEYBOARD_ALPHA_NUM	0x0008


// INTERNATIONAL

#ifdef __cplusplus
}
#endif



#endif


