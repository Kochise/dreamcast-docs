IE sample DLL -- MAILTO Sample Pluggable Protocol Handler
---------------------------------------------------------------

* Purpose:
This sample demonstrates how to create a very simple pluggable 
protocol handler to handle the mailto protocol. Since the
sample browser does not have a mail client, mailto links cannot
be used. This handler parses the mailto URL to extract the 
recipient and subject information, then sends those parameters 
to a web page that is specified in the registry. This web page
is then responsible for permitting the user to enter a mail 
message and send it.

The registry entries for the web page that handles creating the
mail and that supplies the sender (from) information can be set
at image building time (as in this sample) or can be set at run time.
In your browser shell, you may have the user log on when he starts
the browser, and you determine a web page and sender from that
information.

* Used by:
The html control.

* Registry entries:
[HKEY_CLASSES_ROOT\PROTOCOLS\Handler\mailto]
@="MailTo Protocol"
"CLSID"="{40B4BA40-C477-11d3-B16F-0008C76BE5B9}"
[HKEY_CLASSES_ROOT\CLSID\{40B4BA40-C477-11d3-B16F-0008C76BE5B9}]
@="MailTo Protocol"
[HKEY_CLASSES_ROOT\CLSID\{40B4BA40-C477-11d3-B16F-0008C76BE5B9}\InprocServer32]
@="mailto.dll"
"ThreadingModel"="Apartment"
[HKEY_CURRENT_USER\Software\Microsoft\Internet Explorer\Dreamcast Mailto]
"Redirect Site"="http://www.yoursite.com/createmailmail.asp"
"Mail From"="defaultuser@yoursite.com"

* Sample Web Pages:
The sample server pages are designed to work in IIS with ASP and CDO.
You can use a different Internet server type and/or scripting system,
but you will need to consult your documentation on how to send mail from
within your particular setup.

createmail.asp: This file is the page to which the user would be routed 
when he clicks on a mailto link. It provides a form with various fields
pre-filled (data from the mailto link). When the Send button is clicked,
the data from the fields is posted to sendmail.asp.

sendmail.asp: This file is the page that does the actual mail sending. It
builds the CDONTS.NewMail object (you must have your server set up 
correctly), populates the mail data, sends the message, and displays a
confirmation page.

mailtotest.html: This file is a test page for the mailto protocol. It is
a simple page that contains various mailto links.

* Additional resources
You can check out the following MSDN articles for more information
on how to use CDONTS and how to set up your mail server on IIS.

HOWTO: Use CDONTS to Collect and Mail Information From a User
http://support.microsoft.com/support/kb/articles/Q186/2/04.ASP

Sending Email via ASP and CDO for NT Server
http://msdn.microsoft.com/library/periodic/period99/asp9951.htm
