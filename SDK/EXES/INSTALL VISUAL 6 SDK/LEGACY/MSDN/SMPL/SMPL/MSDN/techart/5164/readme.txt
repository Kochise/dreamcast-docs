The following is the readme for the Exchange Event Service Expense
Report Sample.  As with all samples, the usual disclaimers apply.

The Expense Report demo shows how a corporation or developer could build a workflow
process using the Exchange Event Service included with Exchange
Server 5.5.  The workflow starts in a browser where the user enters in
their email id and server.  They are authenticated and can now submit
or check the status of their expense reports.  Once a report is submitted
if the value is > 5000, the report is routed automatically to the
user's manager.  If the manager doesn't approve the report in 15 minutes
the report is automatically rerouted to the manager's manager.  This
keeps happening until there are no more managers to route to.



System requirements:

NT 4.0 with Service Pack 3, Exchange 5.5 RC1 or better, Outlook 8.03 (included with Exchange 5.5),IIS 3.0 with Active
Server Pages.  

Setup:

1) Create a folder called expense on your harddrive.  Unzip the 
expense.zip file into this folder.

2) In the Internet Service Manager for IIS, under the WWW Service and then
under directories, click Add.  In the directory box, point to the folder
where you unzipped the files (ie. c:\expense), and for the virtual root
alias type expense.  Make sure that you click "Execute" at the bottom
to allow the Active Server Pages to execute in the virtual directory. Hit
ok and then ok again.

3) Using a mail client, create the public folder called "Expense Reports".  This
folder must be a root folder under "All Public Folders".  This code will not search subfolders for the Expense Reports folder

4) In the Exchange Administrator, make sure you have event scripting setup correctly.
To do this, go under the Folders container and then system folders.
There should be a EventsRoot and then EventConfig_YOURSERVERNAME. Dbl click on it and click on client
permissions.  Give your NT account at least Author permissions (these are the accounts that are
allowed to save scripts).

5) Close the dialog box and click on Folders, Public Folders and then the Expense Reports
public folder.  Click on the File menu and then properties.  Under the advanced tab, unselect
"Hide from Address Book" (This sample emails the expense report into the folder, there is code in the ASPs that allow you to post it in, but they are commented out.  If you want you can modify
the code so it does a post)  Exit the dialog box.

6) For the recipients you want to use in the workflow, make sure you fill out their
directory information especially MANAGER in the Exchange administrator.  If you do not do
this, the expense report will not route anywhere and the application
will return an error.  

7) In your Outlook 8.03 client, select the Expense Reports
public folder, right click and select Properties.  You should not see an Agent tab in
the properties.  Select the Agent tab and select the Server at the bottom to run the agent
on.  Then, click on New, call the agent whatever you like and select the "A scheduled event occurs" and "A new item is posted into the folder".  Click on schedule and change  the "Every 1 hour" to 0 hours and 15 minutes and then click ok.  Click on the Edit script button and do a select all.  Open the included expense.txt and paste the entire document in the editor. Change "localhost" in the script code to the name of your IIS server. Click on File/Save and exit.  Click ok and then ok and you're set!  There is some debugging
code in the script that you can turn on.

8) Again in the properties settings for the public folder, make sure
that under the permissions tab, you give permissions to everyone that
is working with the folder especially create items and edit items (change permissions for the person submitting
and approving, etc)  If you don't, the sample will not work.

9) Fire up IE and point it to http://YOURSERVERNAME/expense/ and you should be ready to go.
Submit an expense report for under 5000 and make sure that it automatically gets approved
by the agent.  Next, submit an expense report for 10000 and make sure it gets routed to your
manager (15 minutes later).  Note, the expense report HTML form can't handle decimal point numbers
or very large numbers so don't enter things like 10.35 or 10000000.  You'll get a vbscript error.

One final note, for approval the sample uses Localhost as the name of the web server, if you
are planning to run the ASPs on a separate web server, you need to edit the expense.txt script to reflect
this.

9) Enjoy!  