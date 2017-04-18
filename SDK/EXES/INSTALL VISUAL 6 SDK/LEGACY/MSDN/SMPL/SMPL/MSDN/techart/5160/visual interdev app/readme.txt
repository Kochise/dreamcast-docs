Installing the Visual InterDev Application
------------------------------------------

1.  On your Web server, copy the entire "\server components" directory 
    to a local drive on your Web server (do NOT copy the folder into the 
    IIS published "\inetpub\wwwroot" directory). Goto the Web server and run reg.bat from 
    within this newly created folder to register the components. 

2.  From your authoring workstation, start Visual InterDev and create a blank Web project 
    using the New Web Project Wizard. Name the site "Billing" or other suitable name.

3.  Now simply drag and drop the three content files in the \contents 
    folder (billing_information.htm, process.asp, and shipping.gif) into your InterDev 
    project, or insert them using the insert files command.  This will publish them into 
    your Web server project.

4.  Now simply browse http://your_server_name/billing/billing_information.htm in MS Internet 
    Explorer or Netscape Navigator running on any platform. You can right click on the file
    from Visual InterDev to quickly run the application in any installed browser.

5.  Enter the appropriate information in the HTML form to test the functionality provided by 
    the Visual Basic server components that contain the business logic for the application.



