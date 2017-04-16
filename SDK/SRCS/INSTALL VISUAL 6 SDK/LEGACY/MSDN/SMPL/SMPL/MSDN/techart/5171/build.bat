@echo off

if @%1 == @ goto usage

set dbName=%1

echo _) BUILDING ------)----------)-----------)------------) Helpdesk Sample Database

isql -E /P /d %dbName% /n /i helpdesk.sql
isql -E /P /d %dbName% /n /i hddata.sql

echo _) BUILDING ------)----------)-----------)------------) Completed!
goto exit

:usage
echo Database name was not supplied

:exit
