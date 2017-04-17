MSCHATPR SAMPLES

GENERAL INFO FOR CHAT CONTROL

The MSCHATPR.DLL chat control is a UI-less Active X control. 
You can use any Active X container to host the chat control, 
but for this sample, we are using the HTML control as the 
container for the chat control and htmlsamp.exe as the sample
container for the HTML control. After starting the htmlsamp.exe
sample and connecting to the Internet, go to the sample pages
chat.html or puzzle.html (DC URL = file:/pc/samples/chat.html -
these pages are in your samples hierarchy and they have been 
copied into your release hierarchy for ease in accessing them 
from the sample application. If you make changes to the version
in the samples hierarchy, be sure to copy the files into the
release hierarchy. If you put these files out on the Internet
and access them via http protocol, you do not have to copy them
to the release hierarchy).

These sample HTML pages will also work on the PC version of 
Internet Explorer (4.x or 5.x).

To use the chat control, you need to be connected to the 
Internet (or your Intranet) for the duration of the chat 
session. You may want to make your dialer check for winsock 
traffic rather than just checking for navigation to non-local 
pages as is done in the htmlsamp.exe sample.

You need to have access to a chat server. You may set one up
yourself on your Intranet or on the Internet, or you can test 
using comicsrv1.microsoft.com.

CHAT.HTML

This sample page shows most of the chat control functionality.

- To connect to a chat server: Enter a nickname, real name, 
  and chat server name into the appropriate text boxes. Click 
  Connect. The button name will change to Cancel while 
  connecting. Then the button name will change to Disconnect 
  when logged in.
- To disconnect from the chat server: Click Cancel or 
  Disconnect. The button name will change back to Connect. 
- If you can connect but not logon (duplicate ID): Click Cancel.
  Enter a new nickname. Click Connect.
- To join a chat room: Enter a chat room name. Click Join.
  The button name will change to Leave. The other members in 
  the room will be listed in the listbox on the right side of 
  the page.
- To leave a chat room: Click Leave. The button name will change
  back to Join.
- To send a message to the whole group: Enter text into the 
  message text box (under the chat history). Click Send.
- To send an action to the whole group: Enter action text into
  the message text box. Click Act.
- To send a message to a specific member: Select the member in
  the listbox. Enter text into the message text box. Click
  Whisper.
- To kick a member out of the chat room: Select the member in
  the listbox. Enter reason text into the message text box (or 
  leave it blank). Click Kick. You can only kick members out if 
  you are the host (you started the chat room).
- To change the topic of the chat room: Enter text into the
  topic text box. Click Change Topic. You can only change the
  topic if you are the host.
- To invite a user (who is not already in the chat room) to your
  chat room: Enter the user nickname in the invite text box.
  Click Invite.
- To ban a user from the chat room: Enter the user nickname in
  the ban text box. Click Ban User. You can only ban users if
  you are the host. If the user is already in the chat room,
  you will probably want to kick him out, too. Banning will 
  prevent him from re-entering the chat room.
- To unban a user from the chat room: Enter the user nickname in
  the ban text box. Click Unban User. You can only unban users
  if you are the host.
- To send a private message to a user (who does not have to be
  in your chat room): Enter text into the private message text
  box. Enter the user nickname in the private message to text
  box. Click Send Private Message.
- To change your nickname: Enter new nickname in the change 
  nickname text box. Click Change Nickname.
- To indicate to other users that you are away from your desk:
  Enter the reason for being away (if any) in the away text
  box. Click Set Away. The button name will change to Set Back.
- To indicate to other users that you are back at your desk:
  Click Set Back.
- To search for existing chat rooms on the server: Select For  
  All, By Name, or By Topic. For the last two, enter search text. 
  Click Fetch.
- To search for logged on users: Select For All or By Nickname.
  For the last one, enter search text. Click Fetch.

PUZZLE.HTML

This sample page shows how data can be passed using the chat
control in order to run a game. 

- To connect: Log on and join a chat room as with CHAT.HTML.
- To send a message to the whole group: Enter text into the 
  message text box. Click Send.
- To invite a user (who is not already in the chat room) to
  your chat room: Click Invite. Enter the user's nickname.
  Click OK.
- To start the game: Click Start Game. Enter a phrase for the
  other members to guess. Click OK. The person who starts the 
  game will be the host of the game. This person does not have
  to be the host of the chat room.

While the game is being played, the game host does not need to
do anything. The PUZZLE.HTML page will handle prompting each
member when it is his turn to guess a letter.

If a member joins the game after it has already started, he 
will be treated as a spectator. When the current game is over,
he can then be a host or player for the next game.

If the host leaves before the game is over, the game will be
immediately terminated.

If all the players leave before the game is over, the game will
be immediately terminated.

NOTES - ARRAYS

The original chat control was created for Internet Explorer on
the PC, and it was assumed that web developers would be using
VBScript (or at least have access to VBScript). Some of the 
methods on the chat control require VB arrays (safe arrays) 
which cannot be created in JScript. To assist you in creating
these arrays, we have supplied a VBArray object with the chat
control (see CHAT.HTML on how to use it). It converts JScript
strings (with embedded nulls to separate items) to string 
VBArrays and vice versa. This is useful for setting up and
parsing recipients of messages. If you need something more
complex for your application, create your own Active X control
that will handle the arrays for you.

NOTES - TYPELIB

To see all of the available methods and properties on the chat
control, use a typelib viewer on the MSCHATPR.DLL.

NOTES - IMAGE

If you plan on using chat a lot in your application, you should
put MSCHATPR.DLL in your image.

NOTES - REGISTRY

Make sure you have the chat registry entries in your gemini.reg
file:

[HKEY_CLASSES_ROOT\MsChatPr.MsChatPr]
@="MsChatPr Class"
[HKEY_CLASSES_ROOT\MsChatPr.MsChatPr\CLSID]
@="{039397C0-46DF-11D0-99CB-00C04FD64497}"
[HKEY_CLASSES_ROOT\CLSID\{039397C0-46DF-11D0-99CB-00C04FD64497}\InprocServer32]
@="mschatpr.dll"
[HKEY_CLASSES_ROOT\CLSID\{039397C0-46DF-11D0-99CB-00C04FD64497}\TypeLib]
@="{9FE8A900-96AC-11CF-9086-00AA006C3FBC}"
[HKEY_CLASSES_ROOT\TypeLib\{9FE8A900-96AC-11CF-9086-00AA006C3FBC}\2.0\0]
@="mschatpr.dll"
[HKEY_CLASSES_ROOT\CLSID\{039397C0-46DF-11D0-99CB-00C04FD64497}\MiscStatus\1]
@="132497"

[HKEY_CLASSES_ROOT\MsChatPr.VBArray]
@="VBArray Class"
[HKEY_CLASSES_ROOT\MsChatPr.VBArray\CLSID]
@="{A37AA2D0-97A5-11d3-B16A-0008C76BE5B9}"
[HKEY_CLASSES_ROOT\CLSID\{A37AA2D0-97A5-11d3-B16A-0008C76BE5B9}\InprocServer32]
@="mschatpr.dll"
[HKEY_CLASSES_ROOT\CLSID\{A37AA2D0-97A5-11d3-B16A-0008C76BE5B9}\TypeLib]
@="{9FE8A900-96AC-11CF-9086-00AA006C3FBC}"

IF COUNTRY=JAPAN !
[HKEY_CURRENT_USER\Software\Microsoft\Internet Explorer\Chat Control]
"CharSet"=dword:0
ENDIF

IF COUNTRY=JAPAN
[HKEY_CURRENT_USER\Software\Microsoft\Internet Explorer\Chat Control]
"CharSet"=dword:80
ENDIF

