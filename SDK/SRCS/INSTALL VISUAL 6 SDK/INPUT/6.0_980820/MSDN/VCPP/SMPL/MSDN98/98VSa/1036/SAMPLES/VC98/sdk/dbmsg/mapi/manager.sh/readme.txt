Sample Message Hook


The Manager.Sh sample is a sample spooler message hook provider (SMH32.DLL).
The sample spooler hook is an example of a reasonably clever extension to
MAPI which uses the documented MAPI spooler message hook interfaces to
categorize and archive sent and received mail.

Installation
------------

The sample spooler hook is shipped in source form for 32-bit platforms only.
You must build SMH32.DLL first. For the DLL to build successfully, you must
have an SDK that includes the import libraries for the Windows 95 common
controls installed. For the DLL to run successfully on Windows NT 3.5, the
Windows 95 compatible common controls must be installed. Windows NT 3.51
includes these controls.

After building SMH32.DLL, copy it to the system directory of the target
machine, then use the mergeini utility to merge smh.inf into mapisvc.inf.

For example:

    copy smh32.dll c:\windows\system
    mergeini.exe -m .\smh.inf
	
Start the control panel and start the Mail and Fax applet. Select "Add..."
on the Services page of Profile Properties and double-click Sample Mail
Handler.

Configuration
-------------

The sample message hook has a three-page property sheet interface for
interactive configuration, which is accessible through service provider
logon, through the ServiceEntry call, and through the
IMAPIStatus::SettingsDialog method.

When you first add the sample message hook to the profile configuration,
you will need to log off the profile if you are already logged in, and
then log in again before the change will take effect.

General Page
------------

Incoming mail -- Use the "Enable filtering of inbound messages" checkbox
to start inbound/outbound mail "filter"ing. Use the "Add unread messages
folder to hierarchy" checkbox to create a search folder containing all
unread messages for easier access.

Sent mail -- Use the "Archive sent mail into monthly subfolders" checkbox
to instruct the hook processor to categorize sent mail by date and to use
and create subfolders based on the month of submission to contain these
messages. Use the "Archive sent mail monthly folders by year" checkbox to
further organize the archives by year (e.g. sent mail\year\month folder
hierarchy).

Deleted mail -- Use the "Archive deleted mail into monthly subfolders"
checkbox to instruct the hook processor to categorize deleted mail by date
and to use and create subfolders based on the month of creation to contain
these messages. Use the "Archive deleted mail monthly folders by year"
checkbox to further organize the archives by year
(e.g. deleted mail\year\month folder hierarchy).

Filters Page
------------

This page displays a listbox containing all the filters/actions which have
been defined for this profile. The sample hook processor traverses this
list from top to bottom in determining the disposition of a newly
sent/received message. The first rule that "fires" will be the only one
which is applied to the message in question.

To add a filter rule, use the "New" button. To change a rule, select it
and use the "Edit" button. To delete a rule, select it and use the "Delete"
button. To arrange the ordering of rules, select the rule whose position in
the list needs changing and use the up/down arrow buttons to make the
appropriate change.

When you select "New" or "Edit", the filter description dialog will be
presented to you. In this dialog you should enter a display name for the
filter rule that can be used for the listbox, select one of the filtering
criteria (self-explanatory). Enter the appropriate string in "Value contains"
(in the case of recipients, the filter compares both the display name and
the email address), the display name (as shown in the left-hand pane of the
Exchange mail client) of the target store in the "Target Store" field, and
the display name (again as shown in the Exchange mail client) of the folder
to which you want mail matching this filter rule to be copied in the "Target
Folder" field. The hook provider will create folders if need be; to specify
folders in a hierarchy, use a backslash character (e.g. My Mail\Clever
Sayings). To get the negative effect (ie this rule fires for a message not
matching the criteria), set the "Filter messages that do not match this
criteria" checkbox. To disable a filter without deleting it, you set the
"Discontinue the filtering of messages matching this criteria" checkbox. To
choose archiving options for the filter (like in the Sent Mail / Deleted Mail
option above) you may set the appropriate checkboxes for the rule.

Exclusions Page
---------------

This page displays a listbox containing all the message classes for which
filtering is disabled. The sample hook processor traverses this list from top
to bottom in determining whether it should filter a newly sent/received
message. If any message class matches, rules processing will not occur for
that message.

To add a message class, use the New button. To delete a rule, select it and
use the Delete button. To arrange the ordering of rules, select the rule
whose position in the list needs changing and use the up/down arrow buttons
to make the appropriate change.

Known Problems
--------------

Some of the sample hook's features will not work if you use a tightly-coupled
store and transport as your default message store. The archiving of sent and
received mail will not work, because the hook entry points are never called
when the message store server receives mail. Other features, such as archiving
of deleted messages and auto-reply, will work normally.

The hook only can be built on/for 32-bit platforms (this is a limitation of
the sample provider, not of the hook interface itself). The Unread Messages
folder doesn't always seem to be accessable from the Exchange client. The
"Filter messages that do not match this criteria" checkbox doesn't always
seem to work.
