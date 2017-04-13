MAPI Routing Client


The Route.Cli sample illustrates two important areas of MAPI:

1. How to use specially defined named properties, known as routing property 
   sets, for storing addressing information when sending messages across 
   different messaging systems.

2. How to use basic MAPI facilities, as an e-mail client might.

Different messaging systems use different address formats. So when a message
crosses a domain boundary, usually passing through a gateway, the addressing
information needs to be translated from the format used by the original domain
to the format used by the new domain. Almost all gateways do this for the
sender and ordinary message recipients. MAPI defines special mechanism for
preserving the addressing information for users who are not on the message
recipient list. Please see "Sending Messages Between Domains" in the MAPI
Online documentation for more information. This sample uses the mechanism to
route a message to a list of people one after another.

The routing client demonstrates the use of routing property sets by
implementing a simple linear route for a message with optional attached
documents. The routing list is stored in the routing property sets, and each
user who receives the message has an opportunity to edit the message and pass
it to the next person in the routing list. Each user may optionally edit the
remainder of the route as well.

The sample routing client also serves as a simple e-mail client. Features
include:

  - Viewing the contents table of any folder in any message store.
  - Sending or reading any message, using the form registered for it.
  - Forcing new mail to be downloaded to the default message store.
  - Deleting mail.

Performance

Recently the routing code of the sample has been revised with
performance considerations in mind. A few simple changes have
significantly improved response time.  If you looked at the source of
the sample before, you might find it very beneficial to compare the old
and new versions.  Here is the list of things that have been changed:

1. Instead of calling GetIDsFromNames and GetProps once for every
recipient on the routing list, now these functions are called only
once for all the recipients on the routing list.

2. Several calls to GetProps have been combined into one. (For example,
function HasAttachment which did a separate GetProps does not exist
any more. Instead the call has been combined with GetProps in function
RT_OnInitDialog).

3. Now the sample uses the MAPI_DEFERRED_ERRORS flag wherever possible.
(In calls such as OpenEntry, OpenProperty, CreateMessage, etc.) In
general, if a method accepts this flag, you should use it unless there
is a very good reason not to.

These simple tips can significantly boost performance of any MAPI
application.

