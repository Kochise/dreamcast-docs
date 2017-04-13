
Sample: container browser
=========================

This program implements a browser for SMS objects, it illustrates
possible uses of the following SMS APIs:
    SmsEnumContainers
    SmsEnumFilters
    SmsDataSourceConnect
    SmsDataSourceDisconnect
    SmsOpenContainer
    SmsPopulate
    SmsCloseContainer
    SmsGetNextFolder
    SmsCloseFolder
    SmsRewind
    SmsGetFolderID
    SmsGetFolderType
    SmsGetScalarCount
    SmsGetFolderCount
    SmsEnumFolderTypes
    SmsGetNextScalar
    SmsCreateFilter
    SmsAddToken
    SmsGetAllFilters.
    SmsGetFilterType
    SmsGetToken
    SmsGetTokenCount
    SmsCloseFilter

Using the EnumContainers and EnumFilters APIs the program discovers
what containers and filters have been registered with the API engine.
The resulting strings are used to populate the containers and
filters listboxes.

After establishing a connection to the appropriate datasource, the user
selects a container to examine. When the "Done" button, in the select
container section of the dialogue, is pressed the "Select" and "Done"
buttons in the Filters section are enabled. At this point the user
should select and configure filters (explanations further down).
Multiple filters may be selected for the container. Pressing the "Done"
button in this section enables the "View container" button at the
lower part of the dialogue.

The "View container" button brings up the "The container" dialogue.
This dialogue displays the container type (eg "Package container"), the
number of folders contained in the container, and a list of these
folders. The user then selects a folder and views it ("View folder"
button). The "Done" button dismisses this dialogue and returns to the
main doalogue. In this case all the user can do is terminate the
browser, or restart by pressing the "Connect" button.

Viewing folders:
View a folder from the container display brings up a dialogue titled
"View of folder: <the folder's name>". This dialogue has two sections,
folder details, and a sub-folders listbox. The folder details section
displays the folder's ID, type, count of scalars in the folder, count
of sub-folders in the folder, and the number of sub-folder types that
the folder can contain. Refer to the smsapi.h header file, or supplied
help file, for the precise meaning and use of sub-folder type count.
If there are any scalars in the folder the "View scalars" button will
be enabled. Pressing this brings up a dialogue displaying the scalars and
and their values.
The sub-folder list displays the names of any sub-folders. Again, if
there are any sub-folders the "View sub-folder" button will be enabled.
Pressing this will cause the dialogue contents to be replaced with the
details of the selected folder.

Configuring filters:
There are currently 8 filters available:
    site, machine, group, job, architecure, package, attribute, and
        sitelimit.
After selecting a filter the user must configure it in order for it to
be applied to the container, this is done in the "Configure filter"
dialogue.
Filters are composed of one or more tokens, the dialogue allows the
setting of tokens into the specified filter.
There are, currently, two forms of APIs for inserting tokens into
filters, Add{And|Or}Token3 and Add{And|Or}Token4. The former version is
used by all filters with the exception of Machine filters.
If the dialogue detects that it is processing a Machine filter, then an
additional edit control is enabled. For all other filters it is disabled.
Machine filters need to be able to specify a group class, an attribute
name, an operator, and a value. Other filters do not need the group
class field.
The usage of the three common fields differs considerably among filters,
indeed, some filters do not even need all three parameters to be filled
in.

    Site filter
    -----------
Possible values for the name field are: RootSite, and SiteByCode.
They inform the container what site folders it should contain.
If no site filter is applied then the site container will contain
one folder for each site in the datasource.
If RootSite is specified, then no other parameters are needed, and the
container will only contain a folder for the root site.
If SiteByCode is specified, then the Value field must contain the three
letter site code for the requested site. Mixing of a RootSite with
SiteByCode tokens makes no sense. (You have asked for only the root site
and then additional sites.) In this case the RootSite token will take
precedence and the other tokens will be discarded.
It is possible, and perfectly sensible, to set multiple SiteByCode
tokens. In this case the container will be populated with one folder for
each of the requested sites. However, in this case the tokens must be
ORed into the filter. To say that you want the boolean product of site
ABC and site DEF makes no sense since no site can possibly have to
site codes.


    Group filter
    -----------
This filter allows you to select the groupclasses that will be included
for any machines that you wish to browse. As such it is only relevant
for a container that includes machines within its hierarchy, eg site
container, machine container.
Configure this filter as follows:

Name field: must say "GroupClass"
GroupClass field: a valid groupclass name such as
        "MICROSOFT|IDENTIFICATION|1.0".
Operator combobox: select the "is" operator. It's the only one allowed.

It is possible to OR multiple tokens together. For instance, selecting
(OR) a token for MICROSOFT|IDENTIFICATION|1.0 group, select (OR) a
token for MICROSOFT|NETCARD|1.0 group. When viewing the parent machine
folder there will be two sub-folders, one for each of these groups.
Note: some groupclasses have multiple instances, eg MICROSOFT|ENVIRONMENT|1.0.
In this case there will be as many machine group sub-folders as there
are instances of this group.
As in site filters, ANDing tokens together makes no sense.


    Job filter
    -----------
Three options exist for filtering jobs: by job ID, by job type, and
by job status. In all three cases the name and value fields are used.
The operation field, currently, is not.
To set tokens, enter one of the strings "JobType", "JobID", or "JobStatus"
in the name field.
For JobType tokens the value should be one of the following (again as
a literal string):
    "Install"           - for workstation install jobs.
    "Server"            - for server share jobs.
    "Remove package"    - for remove package jobs.
    "System"            - for NAD transfer, site, and minijobs.

For retrieving jobs by their ID, you should type "JobID" in the name
field, and the (eight character) job name in the value field.

For retrieving jobs by their status, type "JobStatus" in the name field.
The value field should contain one of the following string values:
    "Pending"
    "Active"
    "Cancelled"
    "Complete"
    "Failed"
    "Active failed"

Job tokens can be combined together inside a filter. For instance, the
tokens: JobType = Install OR JobID = "ABC00123" will result in the
retrieval of all workstation install jobs, and the job with the name
"ABC00123".


    Architecture filter
    -------------------
This uses one parameter, the value field. Additional documentation
will describe what values are allowed. For instance, "Personal Computer"
will result in machines of the Personal Computer architectures being
selected. "SMSEvent" will result in SMS event MIFs being selected.


    Package filter
    --------------
Currently, there is only one type of token for package filters, this
is the Type token. The type field should say "PackageType". The value field
is one of the following literal strings:
    "Workstation"
    "Server"
    "Inventory"
These can be combined by ORing them into a filter, in which case
you could retrieve, say, Workstation and Sharing packages.
If no package filter is applied, then the system defaults to returning
all packages that are in the datasource.


    Attribute filter
    ----------------
An attribute filter acts in the same way as an SMS query format. It
is used when enumerating/selecting machines and defines what machine
attributes should be accepted by the container. This has a significant
performance gain over using group filters.
For instance, if the user only wants to see the Name, SMSLocation,
and NetCardID from a machine's Identification group, then an
attribute filter containing tokens for each of these attributes will
result in a much faster folder selection than specifying a group
filter for then Identification group. Additionally, only the information
requested will be returned.

The name field should contain the groupclass (eg MICROSOFT|IDENTIFICATION|1.0).
The value field should contain the name of the attribute (eg "Name").
The operator is not currently used.

NOTE: attribute filters specifying attributes that exist in multiple
instance groups (eg the Environment group) will produce indeterminate
results. They should not be used in this case.


        Machine filter
        --------------
A machine filter is the API equivalent of an SMS query. To configure this
type of filter you must provide the following:

Architecture field: this must contain an architecture that is known to
    SMS, exam,ples are: "Personal Computer", "SMSEvent", "UserGroups".
    Consult the SMS documentation for full details about architectures.
    GroupClass field: a valid groupclass name such as
        "MICROSOFT|IDENTIFICATION|1.0".
Attribute name field: the name of an attribute that exists within the
    specified groupclass. For example "SystemRole".
Value: the value for the attribute.
Operator combobox: this is a dropdown listbox that contains operators that
    define the relationship between the attribute and the value.
    For example, "SystemRole" "is" "Server". In this case "is" denotes the
    string equality operator.

This filter can be applied to site, machine, and machine group containers.

For more details refer to your SMS documentation on SMS queries.


        Sitelimit filter
        ----------------
This filter can only be applied to a machine container. Using it you
can specify that you only want machines from a specific site and,
optionally, a specified domain to be included within the container.
Configure this filter as follows:

Site code field: the three letter site code
[optional] Domain: the name of the domain

