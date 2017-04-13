Readme.txt for CSTEXT

1. Purpose

This sample application shows how to accept keyboard input and display it to the screen, so that complex scripts such as Arabic, Hebrew, and Thai are displayed correctly. See the guidelines in section 4 below.

2. How to run the sample 

   1. Compile the sample as described in section 5 below
   2. Execute the executable cstext.exe, by one of the standard methods.
   3. Type a few characters, switch the keyboard to another language, type more characters. 
   4. Click on the Edit menu and choose "Use Edit Control".
   5. Type characters, swith keyboards, type again.
   6. In the edit control right click to see options for
	-entering Unicode control characters, 
	- switching keyboard layout, 
	- etc. 
	
3. System Requirements

This program will run on any version of Windows 95 or Windows NT 4.0 and beyond. However, to see the effect of displaying text in two different ways, it is best used on a platform that supports complex script, such as Arabic, Hebrew, or Thai Windows 95 or Windows NT. 
	
4. What's the point?

This sample shows the proper use of Win32 messages, APIs, and controls to process keyboard input and display the text so that complex scripts are displayed correctly. Follow these guidelines to process complex scripts correctly.

4.1  Use Unicode as your character encoding if the target platform is Windows NT.

4.2  Use an edit control if possible, since the edit control will handle all processing of complex script for you, including input, display, cut and paste, input of Unicode control characters, etc.

4.3 Use ExtTextOut to display all of the text at once. Displaying text character by character as it is entered will result in improper display of context sensitive text. To see this, invoke this application, switch the keyboard to Thai or Arabic and type. Note that the top row is displayed incorrectly, one character at a time. The second row is correct.

4.4 Don't cache character widths; use GetTextExtentExPoint.
Applications that cache character widths implicitly assume that characters always have the same width. As a result, they may measure line lengths of complex scripts incorrectly, because the width of a character depends on the surrounding characters. The text extent functions, such as GetTextExtentPointEx, have been extended to work correctly with complex scripts on platforms that support those scripts.

5. How to build the sample 

To build this sample, set up the SDK environment as for other samples. Then, simply copy all files in this directory to a clean subdirectory and type nmake at the command prompt.

If the sample is to be run on Windows 95 or Windows 98, be sure to comment out the DEFINES=
line in the makefile. That is, it should appears as follows:

#DEFINES=UNICODE

To enter Unicode control characters, compile as a Unicode application and run on Windows NT. To do this, make sure that the following line

DEFINES=-DUNICODE

is enabled in the makefile, i.e., it is not commented out by a "#" sign.
