This readme has the instructions to install the Exchange Techdesk Active Messaging
application and the techdesk outlook form.  If you have any problems, feel free
to email me at thomriz@microsoft.com.

You need to have at least IIS 3.0 with Active Server Pages installed and the
Adventure Works demo site that comes with ASPs,NT 4.0 with SP2 and 
Exchange 5.0 RC1 or better with the Active Server Components installed.
To test to see if you have adventure works, try http://yourservername/advworks.

Instructions:

1) Create in IIS Internet Service Manager a virtual directory pointing
to c:\techdesk and name it techdesk.  Make sure that you check that you have
give execute permissions in the techdesk virtual directory (you will get HTTP
Error 501 if you do not do this)

Also, make sure that you uncheck "Allow Anonymous" in the Internet Service
Manager under the WWW service.

2) Using Outlook, connect to your Exchange Server and import the techdesk.fdm
into a public folder under All public Folders.  This will require
you to
1) Create the Techdesk folder (it is case-sensitive) in your public folders tree
2) Right-click on the Techdesk folder and go to properties
3) under the forms tab, select manage
4) Then select install and a dialog will appear
5) Make sure you can see all the file types (select all files at the bottom)
6) Select the techdesk.fdm
7) hit cancel, close, apply, ok
8) Now, you should see a new Techdesk request on the Task menu (if
you created the default item to be task items)
)
  The form needs to be in the root of All Public Folders since the code only recurses the root
folders of the public folders.  You can easily rewrite the code to recurse
subfolders by checking to see if the folder you currently are viewing
has a folders collection below it.

3a) In the Outlook form, there is a button "Update System Info"
to read in a subset of SMS information from an Access DB.  You will need 
to have Access 97 (or something that installs DAO 3.5, VB 5.0 is your best
bet)  installed on the machine in order for this button to
work.  If you do not have Access 97 installed, just don't click on the button :)

4) Open the logon.inc file.  There is one item that must be customized.  Find in default.asp and posthelp.asp
the line:

bstrServer = "tomexdemo"

Change the name in quotes to the name of your Exchange server.

5) You are going to need to create views on
the folder titled Techdesk, From and Status.  Select the Techdesk public
folder you have created and Below is a breakdown of
the columns (in order) and the group by for each view:

Make sure you right-click on the Techdesk folder and go under properties
and select "Automatically generate Microsoft Exchange Views" so that is it on.

Techdesk				
----------				
Columns - Flag, From User, Subject, Received
Group By - None

From
-----
Columns - Flag, Subject, Received
Group By - From User (ascending)

Status
-------
Columns - From User, Subject, Received
Group By - Flag (Ascending)

To find the columns you need to look into the user-defined fields in the
drop-down box or field chooser for the From User and Flag fields since
they are custom MAPI properties.  Make sure that you do not use the Frequently
Used Fields "From" instead of the custom "From User".  Subject and Received
are just the Messages' subject and received fields.  You can get these from
the frequently-used field drop-down box.  These views are used to browse
the trouble tickets from a web browser. 

6) Make sure you fill in the Directory information for the users in the Exchange
Administrator.  (Dept, phone, Company, Office, etc) or you will get a MAPI_E_NOT_FOUND error.

6a) There is an access database named smsdata.mdb.  Make sure that whatever
alias you use to logon to the techdesk is contained in the tables of the access
database.  You can modify the default 3 tables in the access database by
deleting the reference to johnfre or thomriz and replacing them with your logon
Exchange alias.  Also, to work from the web, you need to create a system DSN
in the ODBC manager named Techdesk that points to the access database.  Make
sure that you do this or you will get a script error when you read a techdesk
ticket.

7) You're ready to go!  Connect using your browser to
http://yourservername/techdesk
