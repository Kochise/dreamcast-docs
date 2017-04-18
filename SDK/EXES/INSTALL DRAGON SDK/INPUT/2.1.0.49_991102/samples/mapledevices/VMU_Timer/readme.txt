MapleDevices sample program -- VMU_Timer
-----------------------------------------

* Purpose:
This sample demonstrates how to interact with the built-in 
timer on the VMU device. It sets/clears the date, and buzzes 
the timer at different frequencies and volumes based on user-input.

The sample uses various command line parameters to perform
different Timer-related actions.  The commands are:

Note:  The VMU timer hardware does not currently support setting the 
day of the week (i.e., Monday, Tuesday, etc.).  However, the 
structure used does have field reserved for this feature, in 
case it is implemented in the future.  Therefore, this sample
currently always reports the current day-of-week as "Sunday" if 
you set the timer (with "-s") or read the timer (with "-r").

* Required Files\Parameters:
Usage: VMU_Timer <options>
-?  Dump Usage Information
-R  Read Timer.  [port number]
-S  Set Timer.  [port yyyy mm dd hh mm ss].  For example
    "VMU_TIMER -S 0 1998 12 25 13 25 33" sets the timer on port 0 to 
    1:25:33pm, 25 Dec 98
-A  Set the Alarm to the desired volume frequency and then play the 
    sound for 2 seconds. [port alarm# Frequency Volume].  For example 
    "VMU_TIMER -A 0 1 255 255" Plays the lowest frequency sound at 
    the highest volume from alarm #1 on the timer on port 0

* This sample exits automatically after performing the specified 
functionality.
