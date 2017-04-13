
Sample: tree
============

DESCRIPTION:


This program illustrates the self-describing nature of the objects in the
API set. Using the SmsEnum APIs it stores lists of all containers, folders,
and filters known to the API engine.

It then scans each container in the container list, displaying first of all
information about the container, and then information about what is
contained within the container. The following information is displayed:

* the container tag and type
* the number of filters activated by this container
* a description of each of these filters

* the number of folder types that can be container in the container
* a description of each of these folders.

The information displayed for a filter is:
* the filter's tag and type
* the names of the fields used by the filter's tokens
  (these will be used as the labels for edit controls in a GUI program).

The information displayed for a folder is:
* the folder's tag and type
* filter details (as in container)
* the number of scalars along with their names, type, and access mode
* a recursive display of any sub-folders that can be contained within this
  folder.


API USAGE:
    SmsAPIVer
    SmsEnumContainers
    SmsEnumFilters
    SmsEnumFolders


Psuedo-code:
The following is a psuedo-code for this program.

begin
    Call the SmsEnum APIs to retrieve lists of
    containers, folders, and filters.


    for each container
    begin

        display container tag and type

        display count of filters activated by this container

        for each filter that can be activated here
        begin
            display filter
        end


        for each folder that can be contained here
        begin
            display folder
        end

    end

end


display filter
begin
    display filter tag and type
    display its properties (ie fields used in tokens)
end


display folder
begin
    locate folder in list returned by SmsEnumFolders
    display tag and type
    check if already displayed in this container hierarchy
    display number of filters activated by this folder
    display filters (as above)
    display scalars
    recursively display sub-folders
end



display scalars
begin
    display number of scalars

    for each scalar
        display its name, type, and access mode
    end
end

