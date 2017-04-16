In order to run the Hotel example, you must first run the RoomMgr.exe
server to allow it to register itself.  If you are using Remote Automation,
this will need to be done on the server and the RoomMgr must be
configured at each client via the Remote Automation Connection
Manager that comes with Visual Basic 4 Enterprise Edition.

Once the RoomMgr has registered itself, it can either be left
running, or it will be automatically started whenever the first
Register.exe client attaches to it.

To fully understand the value of the interaction model in this
example, you should run multiple Register.exe clients and note
how changing the status on any given room is automatically
reflected across all other running clients simultaneously.
