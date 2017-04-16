Insert into tbLocation (Descr, Code) values ('Main Office', 'MAIN')

Insert into tbPriority (Descr, Code) values ('Corporate Level', 'CORP')
Insert into tbPriority (Descr, Code) values ('Division Level', 'DIV')
Insert into tbPriority (Descr, Code) values ('Product level', 'PRODUCT')
Insert into tbPriority (Descr, Code) values ('Team level', 'TEAM')
Insert into tbPriority (Descr, Code) values ('Individual level', 'INDIV')

Insert into tbResolType (Descr, Code) values ('User cancelled', 'USRCAN')
Insert into tbResolType (Descr, Code) values ('User not responding', 'USRDROP')
Insert into tbResolType (Descr, Code) values ('User confirmed resolution', 'CONFREC')
Insert into tbResolType (Descr, Code) values ('Confirmation timed out', 'TIMEOUT')

Insert into tbReqDetType(Descr, Code) Values('Text request',  'TXTREQ')
Insert into tbReqDetType(Descr, Code) Values('Voice request', 'VOCREQ')
Insert into tbReqDetType(Descr, Code) Values('Text response',  'TXTRSP')
Insert into tbReqDetType(Descr, Code) Values('Voice response', 'VOCRSP')
Insert into tbReqDetType(Descr, Code) Values('Standard text response', 'STDTXT')
Insert into tbReqDetType(Descr, Code) Values('Standard voice response', 'STDVOC')

Insert into tbSkill (Descr, Code) values ('Administrator', 'ADMIN')

Insert into tbStatus (Descr, Code) values ('Unassigned', 'UNASSGN')
Insert into tbStatus (Descr, Code) values ('Unclaimed', 'UNCLAIM')
Insert into tbStatus (Descr, Code) values ('Claimed', 'CLAIMED')
Insert into tbStatus (Descr, Code) values ('In progress', 'INPROG')
Insert into tbStatus (Descr, Code) values ('Resolution pending confirmation', 'PENDING')
Insert into tbStatus (Descr, Code) values ('Resolved', 'RESOLVD')


INSERT into tbStdTxtResp(Descr, Code, MsgText)
Values('Request received',  'REQRCVD', 'Your help request has been received. A technician will contact you as soon as possible.')

INSERT into tbStdTxtResp(Descr, Code, MsgText)
Values('Request resolved?',  'REQCONF', 'Has your help request been resolved?')

INSERT into tbStdTxtResp(Descr, Code, MsgText)
Values('Please provide more detail',  'MOREDET', 'Please provide more detail, such as error messages or error numbers, for the technician. Thank you')

INSERT into tbStdTxtResp(Descr, Code, MsgText)
Values('Unable to reach you at phone number',  'UNABLPH', 'A technician has been unable to reach you at the phone number you provided. Can you be reached at another number?')

INSERT INTO tbStdVoiceResp (Descr,Code, MsgData, MsgText) Values('Request received', '0', 'REQRCVD', 'Your request has been received. A technician will contact you shortly.')
INSERT INTO tbStdVoiceResp (Descr,Code, MsgData, MsgText) Values('Provide more detail', '0', 'MOREDET', 'Please provide more detail such as eror messages received')
INSERT INTO tbStdVoiceResp (Descr,Code, MsgData, MsgText) Values('Confirm resolution', '0', 'CONFRES', 'Please confirm that your request has been resolved or that it remains un-resolved')

insert into tbTechStat (Descr, Code) Values('Tech Logon', 'LOGON')
insert into tbTechStat (Descr, Code) Values('Tech Logoff', 'LOGOFF')

Insert into tbVer (AppName, AppVersion) values ('Helpdesk Sample', 'RC1')















