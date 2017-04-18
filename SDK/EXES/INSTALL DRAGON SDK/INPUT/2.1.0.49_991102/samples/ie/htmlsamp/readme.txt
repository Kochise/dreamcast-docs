IE sample program -- HTMLSamp
-----------------------------------------

* Purpose:

This sample shows how to incorporate an HTML control into your game. This is actually two samples
in one. #define GAME_SAMPLE to see the control embedded in a game. Do not #define GAME_SAMPLE to
see a full screen "mini-browser."

To navigate through the sample, move the joystick so the "cursor" is over various "windows":
  Over the Game Board:
    To select different cells in the game board, use the + bar on the controller.
    To "fire" on a cell, use the A button on the controller.
  Over the HTML Control:
    To select different elements on the page, use the + bar on the controller.
    To scroll around in the document, hold Right Trigger and use the + bar on the controller.
    To go to a link, select the linnk using the + bar, and use the A button on the controller.
    To enter a URL, use the Left Trigger on the controller.
  Over the Tool Bar:
    To select different elements in the tool bar, use the + bar on the controller. 
    To activate a command in the tool bar, use the A button on the controller.

See the comments in the code for detailed explanation on how to use the HTML control.

* Required Files\Syntax:
tkimelib.lib
reshelp.dll

* To exit this sample, press X on the controller.


* MACROMEDIA FLASH NOTES

You can get the Macromedia Flash control from Macromedia or Sega; it is not included in this 
Dreamcast SDK available from Microsoft.

This sample has code showing how to register, set up, and use the Flash control. You will need to
#define USE_FLASH to include this support. You will probably also want to not #define GAME_SAMPLE
so you can better see the Flash control. The sample code within the USE_FLASH defines was 
supplied by Macromedia; please contact them if you have any questions. Also, see readme2.txt for
additional information direct from Macromedia.

* MACROMEDIA FKASH LICENSING PROGRAM

If you wish to obtain the Macromedia Flash Control, please go to 
    http://www.macromedia.com/support/shockwave/info/licensing 
to review the licensing terms and download the Macromedia Flash Enabled logos as well as the 
latest Flash Player for Sega Dreamcast bits.

Developers can include the Flash Player for free, provided you agree to put a MM Flash Enabled 
logo in your product and on the web page that promotes the title. Please review the license on 
the Macromedia site for further guidelines and restrictions.
