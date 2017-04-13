BELLHOP.EXE
-----------

Bellhop is a DirectPlay sample that demonstrates how to write a lobby client
application using the DirectPlay API.

Note: MSVC may include older versions of the DirectX header files and
libraries.  This sample requires DirectX 5.  In order to avoid compile
errors, make sure the path to the DirectX 5 header files and libraries are
listed BEFORE the MSVC header files and libraries through the
Tools -> Options -> Directories menu.

To use the Bellhop application, a DirectPlay lobby server must be running on
a computer on the network.

Lobby Server Setup
------------------
The lobby server application is called LSERVER.EXE and can be found in the
\sdk\bin folder.  Double click on this application to start it.

To initialize the lobby server in its default mode, click on the "Server"
menu. Choose "Start" to start the lobby server.  The lobby server will create
several default top-level groups to start with. Users will only be allowed
to create sub-groups within the top-level groups, staging areas, or shortcuts
to staging areas.

By choosing "Test Mode" in the "Server" menu before clicking "Start", the
lobby server will be in test mode.  No default top-level groups will be
created. Users are free to create any group hierarchy they want to any depth.

By choosing "Secure Mode" in the "Server" menu before clicking "Start", the
lobby will require clients to login to the lobby server but only if the lobby
server is being run on Windows NT 4.0 as described in the DirectPlay readme.

The lobby server will then ask which service provider to use - all clients
connecting to the server will need to select this same service provider.
Provide a name for the lobby server session.

Bellhop
-------
Bellhop is used by people trying to find other people to play games with. By
launching Bellhop and connecting to the lobby server, you can navigate
through the "rooms" (represented by a door icon) on the lobby server to
find other people whom you can chat with.  You can create or join "staging
areas" (represented by the triangle icon) to launch DirectPlay lobby aware
games.

Starting Bellhop:

After launching bellhop, you will be asked to select a "lobby provider".  A
lobby provider is a DLL installed on your system that is used by DirectPlay
to communicate with a particular lobby server.  A sample lobby provider is
installed as part of the SDK.  Other lobby server developers will need to
create and install their own lobby providers in order for Bellhop to work
with them.  Choose "Lobby Connection for DirectPlay"

You will then be presented with a dialog asking you to select a service
provider. The sample lobby server and lobby provider are capable of operating
over any network supported by DirectPlay which is why you are presented with
this choice.  Select an appropriate service provider (like TCP/IP) and click
OK.

As usual with TCP/IP, you will be prompted for the address of the lobby
server.  You may leave it blank to try to find it on your local network or
you can enter the computer name or its IP address.  When the lobby server
name is displayed, join it.

Using Bellhop:

To move your player from doorway to doorway, double-click on the doorway you
wish to enter.  You can also drag and drop the icon representing your player
on top of the doorway.
 
There is optional support for allowing players in multiple rooms
simultaneously. To enable it, uncomment the code in the CreatePlayer section
of CGroupTree and rebuild.  For every player created, a player is added to
the root of the tree control. You can enter simultaneous rooms by dragging the
player icon from the top level onto a doorway.

You can only see the contents of rooms that you are a member of.  Once you
leave a room, all the doorways and players in that room will disappear.

Context menus are enabled throughout the tree control. Right clicking on a
player or group will present you with the options available for that specific
item. If you right click on the background of the tree control, you can
select refresh to re-enumerate all the groups and players your player is
aware of.

To create a staging area, right click on the folder which you want to create
it in.  Select "CreateGroupInGroup".  In this dialog, you can create either a
sub-folder or a staging area. If you choose to create a staging area, you
will need to select which game to play from the listbox (only registered
lobby-aware applications are listed) and which connection to launch the game
on. Optionally, you can specify a password for the session and the maximum
number of players.

If you want to join a staging area, you can right click on the icon and
select "GetGroupConnectionSettings" which shows you properties of the staging
area. You can modify these settings using "SetGroupConnectionSettings".

To start a game from a staging area, right click on the staging area icon and
select "StartSession".  This will launch the application on the machines of
all the people in the staging area and connect them together in a session.

If you move into the staging area after the session has started, you may
select "StartSession" to join the session in progress. If the session is in
progress, the icon will change from a green triangle to a red and black
triangle. 

You can create a shortcut to a room by drag dropping one doorway on top of
another.  The icon will appear as a doorway surrounded by a magic portal.

You can change the name of local groups or players by selecting
SetGroupName\SetPlayerName from the appropriate context menu or by single
clicking on the text of the item within the tree control.

Spectators are essentially the same as a regular player within the lobby. 
