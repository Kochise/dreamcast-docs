/* Microsoft SQL Server - Scripting			*/
/* Server: RAINMAKER					*/
/* Database: HelpDesk					*/
/* Creation Date 1/29/98 10:01:45 AM 			*/

/****** Object:  Stored Procedure dbo.pcGet_ReqDet    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcGet_ReqDet') and sysstat & 0xf = 4)
	drop procedure dbo.pcGet_ReqDet
GO

/****** Object:  Stored Procedure dbo.pcLvw_ReqDets    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcLvw_ReqDets') and sysstat & 0xf = 4)
	drop procedure dbo.pcLvw_ReqDets
GO

/****** Object:  Stored Procedure dbo.pcSendStdTextResp    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcSendStdTextResp') and sysstat & 0xf = 4)
	drop procedure dbo.pcSendStdTextResp
GO

/****** Object:  Stored Procedure dbo.pcSendStdVoiceResp    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcSendStdVoiceResp') and sysstat & 0xf = 4)
	drop procedure dbo.pcSendStdVoiceResp
GO

/****** Object:  Stored Procedure dbo.pcSendTextReq    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcSendTextReq') and sysstat & 0xf = 4)
	drop procedure dbo.pcSendTextReq
GO

/****** Object:  Stored Procedure dbo.pcSendTextResp    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcSendTextResp') and sysstat & 0xf = 4)
	drop procedure dbo.pcSendTextResp
GO

/****** Object:  Stored Procedure dbo.pcSendVoiceReq    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcSendVoiceReq') and sysstat & 0xf = 4)
	drop procedure dbo.pcSendVoiceReq
GO

/****** Object:  Stored Procedure dbo.pcSendVoiceResp    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcSendVoiceResp') and sysstat & 0xf = 4)
	drop procedure dbo.pcSendVoiceResp
GO

/****** Object:  Stored Procedure dbo.pcShuffle_Reqs    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcShuffle_Reqs') and sysstat & 0xf = 4)
	drop procedure dbo.pcShuffle_Reqs
GO

/****** Object:  Stored Procedure dbo.pcClaim_Req    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcClaim_Req') and sysstat & 0xf = 4)
	drop procedure dbo.pcClaim_Req
GO

/****** Object:  Stored Procedure dbo.pcCommence_Req    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcCommence_Req') and sysstat & 0xf = 4)
	drop procedure dbo.pcCommence_Req
GO

/****** Object:  Stored Procedure dbo.pcDel_Domain    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcDel_Domain') and sysstat & 0xf = 4)
	drop procedure dbo.pcDel_Domain
GO

/****** Object:  Stored Procedure dbo.pcDel_technician    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcDel_technician') and sysstat & 0xf = 4)
	drop procedure dbo.pcDel_technician
GO

/****** Object:  Stored Procedure dbo.pcGet_Req    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcGet_Req') and sysstat & 0xf = 4)
	drop procedure dbo.pcGet_Req
GO

/****** Object:  Stored Procedure dbo.pcGetMostAvailableTech    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcGetMostAvailableTech') and sysstat & 0xf = 4)
	drop procedure dbo.pcGetMostAvailableTech
GO

/****** Object:  Stored Procedure dbo.pcIns_Domain    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcIns_Domain') and sysstat & 0xf = 4)
	drop procedure dbo.pcIns_Domain
GO

/****** Object:  Stored Procedure dbo.pcIns_Req    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcIns_Req') and sysstat & 0xf = 4)
	drop procedure dbo.pcIns_Req
GO

/****** Object:  Stored Procedure dbo.pcIns_SysParm    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcIns_SysParm') and sysstat & 0xf = 4)
	drop procedure dbo.pcIns_SysParm
GO

/****** Object:  Stored Procedure dbo.pcIns_technician    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcIns_technician') and sysstat & 0xf = 4)
	drop procedure dbo.pcIns_technician
GO

/****** Object:  Stored Procedure dbo.pcLvw_Requests    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcLvw_Requests') and sysstat & 0xf = 4)
	drop procedure dbo.pcLvw_Requests
GO

/****** Object:  Stored Procedure dbo.pcLvw_SysParms    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcLvw_SysParms') and sysstat & 0xf = 4)
	drop procedure dbo.pcLvw_SysParms
GO

/****** Object:  Stored Procedure dbo.pcNotConfRes    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcNotConfRes') and sysstat & 0xf = 4)
	drop procedure dbo.pcNotConfRes
GO

/****** Object:  Stored Procedure dbo.pcReAssign_Req    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcReAssign_Req') and sysstat & 0xf = 4)
	drop procedure dbo.pcReAssign_Req
GO

/****** Object:  Stored Procedure dbo.pcResConfirm    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcResConfirm') and sysstat & 0xf = 4)
	drop procedure dbo.pcResConfirm
GO

/****** Object:  Stored Procedure dbo.pcResolve_Req    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcResolve_Req') and sysstat & 0xf = 4)
	drop procedure dbo.pcResolve_Req
GO

/****** Object:  Stored Procedure dbo.pcSnap_Stat    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcSnap_Stat') and sysstat & 0xf = 4)
	drop procedure dbo.pcSnap_Stat
GO

/****** Object:  Stored Procedure dbo.pcSubmit_Req    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcSubmit_Req') and sysstat & 0xf = 4)
	drop procedure dbo.pcSubmit_Req
GO

/****** Object:  Stored Procedure dbo.pcUnclaim_Req    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcUnclaim_Req') and sysstat & 0xf = 4)
	drop procedure dbo.pcUnclaim_Req
GO

/****** Object:  Stored Procedure dbo.pcUpd_technician    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcUpd_technician') and sysstat & 0xf = 4)
	drop procedure dbo.pcUpd_technician
GO

/****** Object:  Stored Procedure dbo.pcGet_Tech    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcGet_Tech') and sysstat & 0xf = 4)
	drop procedure dbo.pcGet_Tech
GO

/****** Object:  Stored Procedure dbo.pcInitCurTech    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcInitCurTech') and sysstat & 0xf = 4)
	drop procedure dbo.pcInitCurTech
GO

/****** Object:  Stored Procedure dbo.pcLogoff_Tech    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcLogoff_Tech') and sysstat & 0xf = 4)
	drop procedure dbo.pcLogoff_Tech
GO

/****** Object:  Stored Procedure dbo.pcLogon_Tech    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcLogon_Tech') and sysstat & 0xf = 4)
	drop procedure dbo.pcLogon_Tech
GO

/****** Object:  Stored Procedure dbo.pcLvw_Techs    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcLvw_Techs') and sysstat & 0xf = 4)
	drop procedure dbo.pcLvw_Techs
GO

/****** Object:  Stored Procedure dbo.pcLvw_StdVoiceResp    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcLvw_StdVoiceResp') and sysstat & 0xf = 4)
	drop procedure dbo.pcLvw_StdVoiceResp
GO

/****** Object:  Stored Procedure dbo.pcGet_FirstSnapshotDate    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcGet_FirstSnapshotDate') and sysstat & 0xf = 4)
	drop procedure dbo.pcGet_FirstSnapshotDate
GO

/****** Object:  Stored Procedure dbo.pcGet_LastSnapshotDate    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcGet_LastSnapshotDate') and sysstat & 0xf = 4)
	drop procedure dbo.pcGet_LastSnapshotDate
GO

/****** Object:  Stored Procedure dbo.pcGet_SnapshotIDs    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcGet_SnapshotIDs') and sysstat & 0xf = 4)
	drop procedure dbo.pcGet_SnapshotIDs
GO

/****** Object:  Stored Procedure dbo.pcIns_Msg    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcIns_Msg') and sysstat & 0xf = 4)
	drop procedure dbo.pcIns_Msg
GO

/****** Object:  Stored Procedure dbo.pcIns_Snapshot    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcIns_Snapshot') and sysstat & 0xf = 4)
	drop procedure dbo.pcIns_Snapshot
GO

/****** Object:  Stored Procedure dbo.pcLvw_Locations    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcLvw_Locations') and sysstat & 0xf = 4)
	drop procedure dbo.pcLvw_Locations
GO

/****** Object:  Stored Procedure dbo.pcLvw_Priority    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcLvw_Priority') and sysstat & 0xf = 4)
	drop procedure dbo.pcLvw_Priority
GO

/****** Object:  Stored Procedure dbo.pcLvw_ReqDetTypes    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcLvw_ReqDetTypes') and sysstat & 0xf = 4)
	drop procedure dbo.pcLvw_ReqDetTypes
GO

/****** Object:  Stored Procedure dbo.pcLvw_Skills    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcLvw_Skills') and sysstat & 0xf = 4)
	drop procedure dbo.pcLvw_Skills
GO

/****** Object:  Stored Procedure dbo.pcLvw_SnapshotRange    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcLvw_SnapshotRange') and sysstat & 0xf = 4)
	drop procedure dbo.pcLvw_SnapshotRange
GO

/****** Object:  Stored Procedure dbo.pcLvw_Status    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcLvw_Status') and sysstat & 0xf = 4)
	drop procedure dbo.pcLvw_Status
GO

/****** Object:  Stored Procedure dbo.pcLvw_StdTxtResp    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcLvw_StdTxtResp') and sysstat & 0xf = 4)
	drop procedure dbo.pcLvw_StdTxtResp
GO

/****** Object:  Stored Procedure dbo.pcLvw_SysParmType    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcLvw_SysParmType') and sysstat & 0xf = 4)
	drop procedure dbo.pcLvw_SysParmType
GO

/****** Object:  Stored Procedure dbo.pcLvw_TechStat    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcLvw_TechStat') and sysstat & 0xf = 4)
	drop procedure dbo.pcLvw_TechStat
GO

/****** Object:  Stored Procedure dbo.pcUpd_domain    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcUpd_domain') and sysstat & 0xf = 4)
	drop procedure dbo.pcUpd_domain
GO

/****** Object:  Stored Procedure dbo.pcSnapshot    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcSnapshot') and sysstat & 0xf = 4)
	drop procedure dbo.pcSnapshot
GO

/****** Object:  Stored Procedure dbo.pcSnapshot_nomts    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.pcSnapshot_nomts') and sysstat & 0xf = 4)
	drop procedure dbo.pcSnapshot_nomts
GO

/****** Object:  Table dbo.tbReqDet    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbReqDet') and sysstat & 0xf = 3)
	drop table dbo.tbReqDet
GO

/****** Object:  Table dbo.tbReq    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbReq') and sysstat & 0xf = 3)
	drop table dbo.tbReq
GO

/****** Object:  Table dbo.tbReqHist    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbReqHist') and sysstat & 0xf = 3)
	drop table dbo.tbReqHist
GO

/****** Object:  Table dbo.tbSysParameters    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbSysParameters') and sysstat & 0xf = 3)
	drop table dbo.tbSysParameters
GO

/****** Object:  Table dbo.tbCurTech    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbCurTech') and sysstat & 0xf = 3)
	drop table dbo.tbCurTech
GO

/****** Object:  Table dbo.tbReqDetHist    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbReqDetHist') and sysstat & 0xf = 3)
	drop table dbo.tbReqDetHist
GO

/****** Object:  Table dbo.tbSysAudit    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbSysAudit') and sysstat & 0xf = 3)
	drop table dbo.tbSysAudit
GO

/****** Object:  Table dbo.tbTech    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbTech') and sysstat & 0xf = 3)
	drop table dbo.tbTech
GO

/****** Object:  Table dbo.tbAuditType    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbAuditType') and sysstat & 0xf = 3)
	drop table dbo.tbAuditType
GO

/****** Object:  Table dbo.tbLocation    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbLocation') and sysstat & 0xf = 3)
	drop table dbo.tbLocation
GO

/****** Object:  Table dbo.tbMsgIn    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbMsgIn') and sysstat & 0xf = 3)
	drop table dbo.tbMsgIn
GO

/****** Object:  Table dbo.tbPriority    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbPriority') and sysstat & 0xf = 3)
	drop table dbo.tbPriority
GO

/****** Object:  Table dbo.tbReqDetType    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbReqDetType') and sysstat & 0xf = 3)
	drop table dbo.tbReqDetType
GO

/****** Object:  Table dbo.tbResolType    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbResolType') and sysstat & 0xf = 3)
	drop table dbo.tbResolType
GO

/****** Object:  Table dbo.tbSkill    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbSkill') and sysstat & 0xf = 3)
	drop table dbo.tbSkill
GO

/****** Object:  Table dbo.tbSnapshot    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbSnapshot') and sysstat & 0xf = 3)
	drop table dbo.tbSnapshot
GO

/****** Object:  Table dbo.tbStatus    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbStatus') and sysstat & 0xf = 3)
	drop table dbo.tbStatus
GO

/****** Object:  Table dbo.tbStdTxtResp    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbStdTxtResp') and sysstat & 0xf = 3)
	drop table dbo.tbStdTxtResp
GO

/****** Object:  Table dbo.tbStdVoiceResp    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbStdVoiceResp') and sysstat & 0xf = 3)
	drop table dbo.tbStdVoiceResp
GO

/****** Object:  Table dbo.tbSysParmType    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbSysParmType') and sysstat & 0xf = 3)
	drop table dbo.tbSysParmType
GO

/****** Object:  Table dbo.tbTechStat    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbTechStat') and sysstat & 0xf = 3)
	drop table dbo.tbTechStat
GO

/****** Object:  Table dbo.tbTxtReq    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbTxtReq') and sysstat & 0xf = 3)
	drop table dbo.tbTxtReq
GO

/****** Object:  Table dbo.tbTxtReqHist    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbTxtReqHist') and sysstat & 0xf = 3)
	drop table dbo.tbTxtReqHist
GO

/****** Object:  Table dbo.tbTxtResp    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbTxtResp') and sysstat & 0xf = 3)
	drop table dbo.tbTxtResp
GO

/****** Object:  Table dbo.tbTxtRespHist    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbTxtRespHist') and sysstat & 0xf = 3)
	drop table dbo.tbTxtRespHist
GO

/****** Object:  Table dbo.tbVer    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbVer') and sysstat & 0xf = 3)
	drop table dbo.tbVer
GO

/****** Object:  Table dbo.tbVoiceReq    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbVoiceReq') and sysstat & 0xf = 3)
	drop table dbo.tbVoiceReq
GO

/****** Object:  Table dbo.tbVoiceReqHist    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbVoiceReqHist') and sysstat & 0xf = 3)
	drop table dbo.tbVoiceReqHist
GO

/****** Object:  Table dbo.tbVoiceResp    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbVoiceResp') and sysstat & 0xf = 3)
	drop table dbo.tbVoiceResp
GO

/****** Object:  Table dbo.tbVoiceRespHist    Script Date: 1/29/98 10:01:53 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.tbVoiceRespHist') and sysstat & 0xf = 3)
	drop table dbo.tbVoiceRespHist
GO

/****** Object:  Table dbo.tbAuditType    Script Date: 1/29/98 10:01:53 AM ******/
CREATE TABLE dbo.tbAuditType (
	PKId int IDENTITY (1, 1) NOT NULL ,
	Descr varchar (50) NOT NULL ,
	Code char (7) NOT NULL ,
	CONSTRAINT PK__tbAuditTyp__PKId__30F848ED PRIMARY KEY  CLUSTERED 
	(
		PKId
	)
)
GO

/****** Object:  Table dbo.tbLocation    Script Date: 1/29/98 10:01:56 AM ******/
CREATE TABLE dbo.tbLocation (
	PKId int IDENTITY (1, 1) NOT NULL ,
	Descr varchar (50) NOT NULL ,
	Code char (7) NOT NULL ,
	CONSTRAINT PK__tbLocation__PKId__1CF15040 PRIMARY KEY  CLUSTERED 
	(
		PKId
	)
)
GO

/****** Object:  Table dbo.tbMsgIn    Script Date: 1/29/98 10:01:56 AM ******/
CREATE TABLE dbo.tbMsgIn (
	PKId int IDENTITY (1, 1) NOT NULL ,
	EmailAlias varchar (12) NULL ,
	TrackingNo int NULL ,
	MsgDate datetime NULL ,
	MsgText text NULL ,
	MsgData image NULL ,
	CONSTRAINT PK__tbMsgIn__PKId__3C69FB99 PRIMARY KEY  CLUSTERED 
	(
		PKId
	)
)
GO

/****** Object:  Table dbo.tbPriority    Script Date: 1/29/98 10:01:56 AM ******/
CREATE TABLE dbo.tbPriority (
	PKId int IDENTITY (1, 1) NOT NULL ,
	Descr varchar (50) NOT NULL ,
	Code char (7) NOT NULL ,
	CONSTRAINT PK__tbPriority__PKId__22AA2996 PRIMARY KEY  CLUSTERED 
	(
		PKId
	)
)
GO

/****** Object:  Table dbo.tbReqDetType    Script Date: 1/29/98 10:01:57 AM ******/
CREATE TABLE dbo.tbReqDetType (
	PKId int IDENTITY (1, 1) NOT NULL ,
	Descr varchar (50) NOT NULL ,
	Code char (7) NOT NULL ,
	CONSTRAINT PK__tbReqDetTy__PKId__286302EC PRIMARY KEY  CLUSTERED 
	(
		PKId
	)
)
GO

/****** Object:  Table dbo.tbResolType    Script Date: 1/29/98 10:01:57 AM ******/
CREATE TABLE dbo.tbResolType (
	PKId int IDENTITY (1, 1) NOT NULL ,
	Descr varchar (50) NOT NULL ,
	Code char (7) NOT NULL ,
	CONSTRAINT PK__tbResolTyp__PKId__25869641 PRIMARY KEY  CLUSTERED 
	(
		PKId
	)
)
GO

/****** Object:  Table dbo.tbSkill    Script Date: 1/29/98 10:01:57 AM ******/
CREATE TABLE dbo.tbSkill (
	PKId int IDENTITY (1, 1) NOT NULL ,
	Descr varchar (50) NOT NULL ,
	Code char (7) NOT NULL ,
	CONSTRAINT PK__tbSkill__PKId__2B3F6F97 PRIMARY KEY  CLUSTERED 
	(
		PKId
	)
)
GO

/****** Object:  Table dbo.tbSnapshot    Script Date: 1/29/98 10:01:57 AM ******/
CREATE TABLE dbo.tbSnapshot (
	PKId int IDENTITY (1, 1) NOT NULL ,
	Date datetime NOT NULL ,
	SnapData text NOT NULL ,
	CONSTRAINT PK__tbSnapshot__PKId__11158940 PRIMARY KEY  CLUSTERED 
	(
		PKId
	)
)
GO

/****** Object:  Table dbo.tbStatus    Script Date: 1/29/98 10:01:57 AM ******/
CREATE TABLE dbo.tbStatus (
	PKId int IDENTITY (1, 1) NOT NULL ,
	Descr varchar (50) NOT NULL ,
	Code char (7) NOT NULL ,
	CONSTRAINT PK__tbStatus__PKId__4BE14953 PRIMARY KEY  CLUSTERED 
	(
		PKId
	)
)
GO

/****** Object:  Table dbo.tbStdTxtResp    Script Date: 1/29/98 10:01:58 AM ******/
CREATE TABLE dbo.tbStdTxtResp (
	PKId int IDENTITY (1, 1) NOT NULL ,
	Descr varchar (50) NOT NULL ,
	Code char (7) NOT NULL ,
	MsgText text NOT NULL ,
	CONSTRAINT PK__tbStdTxtRe__PKId__6EF57B66 PRIMARY KEY  CLUSTERED 
	(
		PKId
	)
)
GO

/****** Object:  Table dbo.tbStdVoiceResp    Script Date: 1/29/98 10:01:58 AM ******/
CREATE TABLE dbo.tbStdVoiceResp (
	PKId int IDENTITY (1, 1) NOT NULL ,
	Descr varchar (50) NOT NULL ,
	Code char (7) NOT NULL ,
	MsgData image NOT NULL ,
	MsgText text NOT NULL ,
	CONSTRAINT PK__tbStdVoice__PKId__71D1E811 PRIMARY KEY  CLUSTERED 
	(
		PKId
	)
)
GO

/****** Object:  Table dbo.tbSysParmType    Script Date: 1/29/98 10:01:58 AM ******/
CREATE TABLE dbo.tbSysParmType (
	PKId int IDENTITY (1, 1) NOT NULL ,
	Descr varchar (50) NOT NULL ,
	Code char (7) NOT NULL ,
	CONSTRAINT PK__tbSysParmT__PKId__2E1BDC42 PRIMARY KEY  CLUSTERED 
	(
		PKId
	)
)
GO

/****** Object:  Table dbo.tbTechStat    Script Date: 1/29/98 10:01:58 AM ******/
CREATE TABLE dbo.tbTechStat (
	PKId int IDENTITY (1, 1) NOT NULL ,
	Descr varchar (50) NOT NULL ,
	Code char (7) NOT NULL ,
	CONSTRAINT PK__tbTechStat__PKId__3D9329FC PRIMARY KEY  CLUSTERED 
	(
		PKId
	)
)
GO

/****** Object:  Table dbo.tbTxtReq    Script Date: 1/29/98 10:01:58 AM ******/
CREATE TABLE dbo.tbTxtReq (
	PKId int IDENTITY (1, 1) NOT NULL ,
	ReqText text NOT NULL ,
	CONSTRAINT PK__tbTxtReq__PKId__5812160E PRIMARY KEY  CLUSTERED 
	(
		PKId
	)
)
GO

/****** Object:  Table dbo.tbTxtReqHist    Script Date: 1/29/98 10:01:59 AM ******/
CREATE TABLE dbo.tbTxtReqHist (
	PKId int IDENTITY (1, 1) NOT NULL ,
	ReqText text NOT NULL ,
	CONSTRAINT PK__tbTxtReqHi__PKId__6383C8BA PRIMARY KEY  CLUSTERED 
	(
		PKId
	)
)
GO

/****** Object:  Table dbo.tbTxtResp    Script Date: 1/29/98 10:01:59 AM ******/
CREATE TABLE dbo.tbTxtResp (
	PKId int IDENTITY (1, 1) NOT NULL ,
	RespText text NOT NULL ,
	CONSTRAINT PK__tbTxtResp__PKId__5DCAEF64 PRIMARY KEY  CLUSTERED 
	(
		PKId
	)
)
GO

/****** Object:  Table dbo.tbTxtRespHist    Script Date: 1/29/98 10:01:59 AM ******/
CREATE TABLE dbo.tbTxtRespHist (
	PKId int IDENTITY (1, 1) NOT NULL ,
	RespText text NOT NULL ,
	CONSTRAINT PK__tbTxtRespH__PKId__693CA210 PRIMARY KEY  CLUSTERED 
	(
		PKId
	)
)
GO

/****** Object:  Table dbo.tbVer    Script Date: 1/29/98 10:01:59 AM ******/
CREATE TABLE dbo.tbVer (
	PKId int IDENTITY (1, 1) NOT NULL ,
	AppName varchar (50) NOT NULL ,
	AppVersion varchar (50) NOT NULL ,
	CONSTRAINT PK__tbVer__PKId__69FBBC1F PRIMARY KEY  CLUSTERED 
	(
		PKId
	)
)
GO

/****** Object:  Table dbo.tbVoiceReq    Script Date: 1/29/98 10:02:00 AM ******/
CREATE TABLE dbo.tbVoiceReq (
	PKId int IDENTITY (1, 1) NOT NULL ,
	ReqText text NOT NULL ,
	ReqData image NULL ,
	CONSTRAINT PK__tbVoiceReq__PKId__756D6ECB PRIMARY KEY  CLUSTERED 
	(
		PKId
	)
)
GO

/****** Object:  Table dbo.tbVoiceReqHist    Script Date: 1/29/98 10:02:00 AM ******/
CREATE TABLE dbo.tbVoiceReqHist (
	PKId int IDENTITY (1, 1) NOT NULL ,
	ReqText text NOT NULL ,
	ReqData image NULL ,
	CONSTRAINT PK__tbVoiceReq__PKId__6CD828CA PRIMARY KEY  CLUSTERED 
	(
		PKId
	)
)
GO

/****** Object:  Table dbo.tbVoiceResp    Script Date: 1/29/98 10:02:00 AM ******/
CREATE TABLE dbo.tbVoiceResp (
	PKId int IDENTITY (1, 1) NOT NULL ,
	RespText text NOT NULL ,
	RespData image NULL ,
	CONSTRAINT PK__tbVoiceRes__PKId__72910220 PRIMARY KEY  CLUSTERED 
	(
		PKId
	)
)
GO

/****** Object:  Table dbo.tbVoiceRespHist    Script Date: 1/29/98 10:02:01 AM ******/
CREATE TABLE dbo.tbVoiceRespHist (
	PKId int IDENTITY (1, 1) NOT NULL ,
	RespText text NOT NULL ,
	ReqData image NULL ,
	CONSTRAINT PK__tbVoiceRes__PKId__6FB49575 PRIMARY KEY  CLUSTERED 
	(
		PKId
	)
)
GO

/****** Object:  Table dbo.tbCurTech    Script Date: 1/29/98 10:02:02 AM ******/
CREATE TABLE dbo.tbCurTech (
	PKId int IDENTITY (1, 1) NOT NULL ,
	LocId int NOT NULL ,
	SkillId int NOT NULL ,
	CurTechId int NULL ,
	CONSTRAINT FK__tbCurTech__LocId__1273C1CD FOREIGN KEY 
	(
		LocId
	) REFERENCES dbo.tbLocation (
		PKId
	),
	CONSTRAINT FK__tbCurTech__Skill__1367E606 FOREIGN KEY 
	(
		SkillId
	) REFERENCES dbo.tbSkill (
		PKId
	)
)
GO

/****** Object:  Table dbo.tbReqDetHist    Script Date: 1/29/98 10:02:03 AM ******/
CREATE TABLE dbo.tbReqDetHist (
	PKId int IDENTITY (1, 1) NOT NULL ,
	ReqId int NOT NULL ,
	ReqDetTypeId int NOT NULL ,
	DetMsgId int NULL ,
	TechId int NULL ,
	DetDate datetime NOT NULL ,
	CONSTRAINT PK__tbReqDetHi__PKId__2B3F6F97 PRIMARY KEY  CLUSTERED 
	(
		PKId
	),
	CONSTRAINT FK__tbReqDetH__ReqDe__2D27B809 FOREIGN KEY 
	(
		ReqDetTypeId
	) REFERENCES dbo.tbReqDetType (
		PKId
	)
)
GO

/****** Object:  Table dbo.tbSysAudit    Script Date: 1/29/98 10:02:03 AM ******/
CREATE TABLE dbo.tbSysAudit (
	PKId int IDENTITY (1, 1) NOT NULL ,
	AuditTypeId int NOT NULL ,
	AuditDate datetime NOT NULL ,
	Descr varchar (255) NOT NULL ,
	ModuleName varchar (255) NOT NULL ,
	CONSTRAINT PK__tbSysAudit__PKId__33D4B598 PRIMARY KEY  CLUSTERED 
	(
		PKId
	),
	CONSTRAINT FK__tbSysAudi__Audit__34C8D9D1 FOREIGN KEY 
	(
		AuditTypeId
	) REFERENCES dbo.tbAuditType (
		PKId
	)
)
GO

/****** Object:  Table dbo.tbTech    Script Date: 1/29/98 10:02:05 AM ******/
CREATE TABLE dbo.tbTech (
	PKId int IDENTITY (1, 1) NOT NULL ,
	LocId int NOT NULL ,
	SkillId int NOT NULL ,
	EmailAlias varchar (12) NOT NULL ,
	StatusId int NOT NULL ,
	CONSTRAINT PK__tbTech__PKId__3F466844 PRIMARY KEY  CLUSTERED 
	(
		PKId
	),
	CONSTRAINT FK__tbTech__LocId__403A8C7D FOREIGN KEY 
	(
		LocId
	) REFERENCES dbo.tbLocation (
		PKId
	),
	CONSTRAINT FK__tbTech__SkillId__412EB0B6 FOREIGN KEY 
	(
		SkillId
	) REFERENCES dbo.tbSkill (
		PKId
	),
	CONSTRAINT FK__tbTech__StatusId__4222D4EF FOREIGN KEY 
	(
		StatusId
	) REFERENCES dbo.tbTechStat (
		PKId
	)
)
GO

/****** Object:  Table dbo.tbReq    Script Date: 1/29/98 10:02:06 AM ******/
CREATE TABLE dbo.tbReq (
	PKId int IDENTITY (1, 1) NOT NULL ,
	ReqDate datetime NOT NULL ,
	ResolDate datetime NULL ,
	LocId int NOT NULL ,
	PriorityId int NOT NULL ,
	ResolById int NULL ,
	ResolTypeId int NULL ,
	SkillId int NOT NULL ,
	StatusId int NOT NULL ,
	TechId int NULL ,
	TrackingNo int NOT NULL ,
	EmailAlias varchar (12) NOT NULL ,
	ResolOther text NULL ,
	Descr varchar (50) NULL ,
	CONSTRAINT PK__tbReq__PKId__44FF419A PRIMARY KEY  CLUSTERED 
	(
		PKId
	),
	CONSTRAINT FK__tbReq__LocId__45F365D3 FOREIGN KEY 
	(
		LocId
	) REFERENCES dbo.tbLocation (
		PKId
	),
	CONSTRAINT FK__tbReq__PriorityI__46E78A0C FOREIGN KEY 
	(
		PriorityId
	) REFERENCES dbo.tbPriority (
		PKId
	),
	CONSTRAINT FK__tbReq__ResolById__47DBAE45 FOREIGN KEY 
	(
		ResolById
	) REFERENCES dbo.tbTech (
		PKId
	),
	CONSTRAINT FK__tbReq__ResolType__48CFD27E FOREIGN KEY 
	(
		ResolTypeId
	) REFERENCES dbo.tbResolType (
		PKId
	),
	CONSTRAINT FK__tbReq__SkillId__49C3F6B7 FOREIGN KEY 
	(
		SkillId
	) REFERENCES dbo.tbSkill (
		PKId
	),
	CONSTRAINT FK__tbReq__StatusId__4AB81AF0 FOREIGN KEY 
	(
		StatusId
	) REFERENCES dbo.tbStatus (
		PKId
	),
	CONSTRAINT FK__tbReq__TechId__4BAC3F29 FOREIGN KEY 
	(
		TechId
	) REFERENCES dbo.tbTech (
		PKId
	)
)
GO

/****** Object:  Table dbo.tbReqHist    Script Date: 1/29/98 10:02:06 AM ******/
CREATE TABLE dbo.tbReqHist (
	PKId int IDENTITY (1, 1) NOT NULL ,
	ReqDate datetime NOT NULL ,
	ResolDate datetime NULL ,
	LocId int NOT NULL ,
	PriorityId int NOT NULL ,
	ResolById int NULL ,
	ResolTypeId int NULL ,
	SkillId int NOT NULL ,
	StatusId int NOT NULL ,
	TechId int NULL ,
	TrackingNo int NOT NULL ,
	EmailAlias varchar (12) NOT NULL ,
	ResolOther text NULL ,
	Descr varchar (50) NULL ,
	CONSTRAINT PK__tbReqHist__PKId__7849DB76 PRIMARY KEY  CLUSTERED 
	(
		PKId
	),
	CONSTRAINT FK__tbReqHist__LocId__793DFFAF FOREIGN KEY 
	(
		LocId
	) REFERENCES dbo.tbLocation (
		PKId
	),
	CONSTRAINT FK__tbReqHist__Prior__7A3223E8 FOREIGN KEY 
	(
		PriorityId
	) REFERENCES dbo.tbPriority (
		PKId
	),
	CONSTRAINT FK__tbReqHist__Resol__7B264821 FOREIGN KEY 
	(
		ResolById
	) REFERENCES dbo.tbTech (
		PKId
	),
	CONSTRAINT FK__tbReqHist__Resol__7C1A6C5A FOREIGN KEY 
	(
		ResolTypeId
	) REFERENCES dbo.tbResolType (
		PKId
	),
	CONSTRAINT FK__tbReqHist__Skill__7D0E9093 FOREIGN KEY 
	(
		SkillId
	) REFERENCES dbo.tbSkill (
		PKId
	),
	CONSTRAINT FK__tbReqHist__Statu__7E02B4CC FOREIGN KEY 
	(
		StatusId
	) REFERENCES dbo.tbStatus (
		PKId
	),
	CONSTRAINT FK__tbReqHist__TechI__7EF6D905 FOREIGN KEY 
	(
		TechId
	) REFERENCES dbo.tbTech (
		PKId
	)
)
GO

/****** Object:  Table dbo.tbSysParameters    Script Date: 1/29/98 10:02:07 AM ******/
CREATE TABLE dbo.tbSysParameters (
	PKId int IDENTITY (1, 1) NOT NULL ,
	ChangedById int NOT NULL ,
	ParmTypeId int NOT NULL ,
	ChangeDate datetime NOT NULL ,
	Descr varchar (50) NOT NULL ,
	SysValue varchar (255) NOT NULL ,
	CONSTRAINT PK__tbSysParam__PKId__74AE54BC PRIMARY KEY  CLUSTERED 
	(
		PKId
	),
	CONSTRAINT FK__tbSysPara__Chang__75A278F5 FOREIGN KEY 
	(
		ChangedById
	) REFERENCES dbo.tbTech (
		PKId
	),
	CONSTRAINT FK__tbSysPara__ParmT__76969D2E FOREIGN KEY 
	(
		ParmTypeId
	) REFERENCES dbo.tbSysParmType (
		PKId
	)
)
GO

/****** Object:  Table dbo.tbReqDet    Script Date: 1/29/98 10:02:07 AM ******/
CREATE TABLE dbo.tbReqDet (
	PKId int IDENTITY (1, 1) NOT NULL ,
	ReqId int NOT NULL ,
	ReqDetTypeId int NOT NULL ,
	DetMsgId int NULL ,
	TechId int NULL ,
	DetDate datetime NOT NULL ,
	CONSTRAINT PK__tbReqDet__PKId__01D345B0 PRIMARY KEY  CLUSTERED 
	(
		PKId
	),
	CONSTRAINT FK__tbReqDet__ReqDet__03BB8E22 FOREIGN KEY 
	(
		ReqDetTypeId
	) REFERENCES dbo.tbReqDetType (
		PKId
	),
	CONSTRAINT FK__tbReqDet__ReqId__02C769E9 FOREIGN KEY 
	(
		ReqId
	) REFERENCES dbo.tbReq (
		PKId
	),
	CONSTRAINT FK__tbReqDet__TechId__04AFB25B FOREIGN KEY 
	(
		TechId
	) REFERENCES dbo.tbTech (
		PKId
	)
)
GO

/****** Object:  Stored Procedure dbo.pcSnapshot    Script Date: 1/29/98 10:02:08 AM ******/
CREATE PROCEDURE pcSnapshot AS
DECLARE @Monitor int
DECLARE @hr      int
DECLARE @Output varchar(255)
DECLARE @Source varchar(255)
DECLARE @Description varchar(255)

DECLARE @RetCode int
DECLARE @_error  int

SELECT @RetCode = 0

--Instantiate HDMonitor CSnapshot object
EXEC @hr = sp_OACreate 'HDMonSvr.CSnapshot', @Monitor OUT
IF @hr <> 0
BEGIN
    SELECT @Output = 'Could not instantiate HDMonSvr.CSnapshot.'
    EXEC @RetCode = sp_OAGetErrorInfo @Monitor, @Source OUT, @Description OUT
    IF @RetCode = 0
        SELECT @Output = @Output + '  Source: ' + @Source + '  Description: ' + @Description
    ELSE
        SELECT @Output = @Output + ' ErrorInfo failed'

    SELECT @_error = @@error
    SELECT  @RetCode = -(Abs(@_error))
    RAISERROR(@Output,16,4) 
    RETURN @RetCode
END

--Call SysSnapshot method
EXEC @hr = sp_OAMethod @Monitor, 'SysSnapshot'
IF @hr <> 0
BEGIN
    SELECT @Output = 'Could not execute HDMonSvr.CSnapshot.SysSnapshot.'
    EXEC @RetCode = sp_OAGetErrorInfo @Monitor, @Source OUT, @Description OUT
    IF @RetCode = 0
        SELECT @Output = @Output + '  Source: ' + @Source + '  Description: ' + @Description

    ELSE
        SELECT @Output = @Output + ' ErrorInfo failed'

    SELECT @_error = @@error
    SELECT  @RetCode = -(Abs(@_error))
    RAISERROR(@Output,16,4) 
    RETURN @RetCode
END
    
--Destroy the object
EXEC @hr = sp_OADestroy @Monitor
IF @hr <> 0
BEGIN
    SELECT @Output = 'Could not destroy HDMonSvr.CSnapshot.'
    EXEC @RetCode = sp_OAGetErrorInfo @Monitor, @Source OUT, @Description OUT
    IF @RetCode = 0
        SELECT @Output = @Output + '  Source: ' + @Source + '  Description: ' + @Description
    ELSE
        SELECT @Output = @Output + ' ErrorInfo failed'

    SELECT @_error = @@error
    SELECT  @RetCode = -(Abs(@_error))
    RAISERROR(@Output,16,4) 
    RETURN @RetCode

END

--Check for other errors
SELECT @_error = @@error
IF @_error <> 0
  BEGIN
    SELECT  @RetCode = -(Abs(@_error))
    RAISERROR('Could not take snaposhot.',16,4) 
    RETURN @RetCode
  END
ELSE
  RETURN @RetCode
GO

/****** Object:  Stored Procedure dbo.pcSnapshot_nomts    Script Date: 1/29/98 10:02:08 AM ******/
CREATE PROCEDURE pcSnapshot_nomts AS
DECLARE @Monitor int
DECLARE @hr      int
DECLARE @Output varchar(255)
DECLARE @Source varchar(255)
DECLARE @Description varchar(255)

DECLARE @RetCode int
DECLARE @_error  int

SELECT @RetCode = 0

--Instantiate HDMonitor CSnapshot object
EXEC @hr = sp_OACreate 'HDMonSvr_nomts.CSnapshot', @Monitor OUT
IF @hr <> 0
BEGIN
    SELECT @Output = 'Could not instantiate HDMonSvr_nomts.CSnapshot.'
    EXEC @RetCode = sp_OAGetErrorInfo @Monitor, @Source OUT, @Description OUT
    IF @RetCode = 0
        SELECT @Output = @Output + '  Source: ' + @Source + '  Description: ' + @Description
    ELSE
        SELECT @Output = @Output + ' ErrorInfo failed'

    SELECT @_error = @@error
    SELECT  @RetCode = -(Abs(@_error))
    RAISERROR(@Output,16,4) 
    RETURN @RetCode
END

--Call SysSnapshot method
EXEC @hr = sp_OAMethod @Monitor, 'SysSnapshot'
IF @hr <> 0
BEGIN
    SELECT @Output = 'Could not execute HDMonSvr_nomts.CSnapshot.SysSnapshot.'
    EXEC @RetCode = sp_OAGetErrorInfo @Monitor, @Source OUT, @Description OUT
    IF @RetCode = 0
        SELECT @Output = @Output + '  Source: ' + @Source + '  Description: ' + @Description
    ELSE
        SELECT @Output = @Output + ' ErrorInfo failed'

    SELECT @_error = @@error
    SELECT  @RetCode = -(Abs(@_error))
    RAISERROR(@Output,16,4) 
    RETURN @RetCode
END
    
--Destroy the object
EXEC @hr = sp_OADestroy @Monitor
IF @hr <> 0
BEGIN
    SELECT @Output = 'Could not destroy HDMonSvr_nomts.CSnapshot.'
    EXEC @RetCode = sp_OAGetErrorInfo @Monitor, @Source OUT, @Description OUT
    IF @RetCode = 0
        SELECT @Output = @Output + '  Source: ' + @Source + '  Description: ' + @Description
    ELSE
        SELECT @Output = @Output + ' ErrorInfo failed'

    SELECT @_error = @@error
    SELECT  @RetCode = -(Abs(@_error))
    RAISERROR(@Output,16,4) 
    RETURN @RetCode

END

--Check for other errors
SELECT @_error = @@error
IF @_error <> 0
  BEGIN
    SELECT  @RetCode = -(Abs(@_error))
    RAISERROR('Could not take snapshot.',16,4) 
    RETURN @RetCode
  END
ELSE
  RETURN @RetCode
GO

/****** Object:  Stored Procedure dbo.pcLvw_StdVoiceResp    Script Date: 1/29/98 10:02:08 AM ******/
CREATE PROCEDURE pcLvw_StdVoiceResp
AS
select * from tbStdVoiceResp


GO

/****** Object:  Stored Procedure dbo.pcGet_FirstSnapshotDate    Script Date: 1/29/98 10:02:08 AM ******/
CREATE PROCEDURE pcGet_FirstSnapshotDate AS
select min(Date) from tbSnapshot

GO

/****** Object:  Stored Procedure dbo.pcGet_LastSnapshotDate    Script Date: 1/29/98 10:02:08 AM ******/
CREATE PROCEDURE pcGet_LastSnapshotDate AS
select max(Date) from tbSnapshot

GO

/****** Object:  Stored Procedure dbo.pcGet_SnapshotIDs    Script Date: 1/29/98 10:02:08 AM ******/
CREATE PROCEDURE pcGet_SnapshotIDs
@StartDate datetime
,@EndDate  datetime
AS
declare @lDate datetime
declare @rDate datetime

--Test for date immediately preceding requested range
select @lDate = max(Date) from tbSnapshot where Date < @StartDate

if @lDate is null
select @lDate = @StartDate

--Test for date immediately following requested range
select @rDate = min(Date) from tbSnapshot where Date > @EndDate
if @rDate is null
select @rDate = @StartDate

--Return the PKids for the resulting date range
select PKId from tbSnapshot
where Date >= @lDate and Date <= @rDate
order by Date

GO

/****** Object:  Stored Procedure dbo.pcIns_Msg    Script Date: 1/29/98 10:02:08 AM ******/
CREATE PROCEDURE pcIns_Msg
 @EmailAlias      varchar(12)   = NULL           
,@TrackingNo      int           = NULL          
,@MsgDate         datetime      = NULL       
,@MsgText         text          = NULL           
,@MsgData         image         = NULL    

AS

DECLARE @RetCode      int
DECLARE @_error       int
DECLARE @_rowcount    int

SELECT @RetCode = 0

INSERT INTO tbMsgIn
( EmailAlias    
,TrackingNo           
,MsgDate      
,MsgText       
,MsgData     
)
VALUES
(
 @EmailAlias   
,@TrackingNo          
,@MsgDate     
,@MsgText      
,@MsgData    
)

SELECT @_error = @@error ,@_rowcount = @@rowcount
IF (@_error <> 0) OR (@_rowcount <> 1)
  BEGIN
    IF (@_error = 0) SELECT @_error = 333
    SELECT  @RetCode = -(Abs(@_error))
    RAISERROR('Could not insert Msg record.',16,4) 
    SELECT @RetCode
    RETURN @RetCode
  END
ELSE
  BEGIN
    SELECT @RetCode
    RETURN @RetCode
  END

GO

/****** Object:  Stored Procedure dbo.pcIns_Snapshot    Script Date: 1/29/98 10:02:08 AM ******/
CREATE PROCEDURE pcIns_Snapshot @SnapDate DateTime = Null, @SnapData Char(255)
AS

DECLARE @RetCode      int
DECLARE @_error       int
DECLARE @_rowcount    int
DECLARE @StatusId     int

SELECT @RetCode = 0
SELECT @StatusId = 1

--Use system date if date was not provided
IF (@SnapDate Is NULL)
    SELECT @SnapDate = getdate()

insert into tbSnapshot(Date,SnapData)
    values(@SnapDate,@SnapData)

SELECT @_error = @@error ,@_rowcount = @@rowcount
IF (@_error <> 0) OR (@_rowcount <> 1)
  BEGIN
    IF (@_error = 0) SELECT @_error = 333
    SELECT  @RetCode = -(Abs(@_error))
    RAISERROR('Could not insert Snapshot record.',16,4) 
    SELECT @RetCode
    RETURN @RetCode
  END
ELSE
  BEGIN
    SELECT @RetCode
    RETURN @RetCode

  END

GO

/****** Object:  Stored Procedure dbo.pcLvw_Locations    Script Date: 1/29/98 10:02:08 AM ******/
CREATE PROCEDURE pcLvw_Locations AS
SELECT * from tbLocation


GO

/****** Object:  Stored Procedure dbo.pcLvw_Priority    Script Date: 1/29/98 10:02:08 AM ******/
CREATE PROCEDURE pcLvw_Priority
AS
SELECT * FROM tbPriority


GO

/****** Object:  Stored Procedure dbo.pcLvw_ReqDetTypes    Script Date: 1/29/98 10:02:08 AM ******/
CREATE PROCEDURE pcLvw_ReqDetTypes
AS
select * from tbReqDetType


GO

/****** Object:  Stored Procedure dbo.pcLvw_Skills    Script Date: 1/29/98 10:02:08 AM ******/
CREATE PROCEDURE pcLvw_Skills AS
SELECT * FROM tbSkill


GO

/****** Object:  Stored Procedure dbo.pcLvw_SnapshotRange    Script Date: 1/29/98 10:02:08 AM ******/
CREATE PROCEDURE pcLvw_SnapshotRange
@FirstId    int    = NULL
,@LastId    int    = NULL
AS

--Both FirstId and LastId are supplied
If @FirstId IS NOT NULL and @LastId IS NOT NULL  
    BEGIN    
    SELECT * FROM tbSnapshot
    WHERE (PKId >= @FirstId) and (PKId <= @LastId)
    ORDER BY Date
    RETURN 0
    END

--Only FirstId is supplied
If @FirstId IS NOT NULL and @LastId IS NULL  
    BEGIN    
    SELECT * FROM tbSnapshot
    WHERE (PKId >= @FirstId)
    ORDER BY Date
    RETURN 0
    END

--Only LastId is supplied
If @LastId IS NOT NULL and @FirstId IS NULL  
    BEGIN    
    SELECT * FROM tbSnapshot
    WHERE (PKId <= @LastId)
    ORDER BY Date
    RETURN 0
    END

--Neither FirstId or LastId are supplied
    SELECT * FROM tbSnapshot
    ORDER BY Date
    RETURN 0

GO

/****** Object:  Stored Procedure dbo.pcLvw_Status    Script Date: 1/29/98 10:02:08 AM ******/
CREATE PROCEDURE pcLvw_Status
AS
select * from tbStatus


GO

/****** Object:  Stored Procedure dbo.pcLvw_StdTxtResp    Script Date: 1/29/98 10:02:08 AM ******/
CREATE PROCEDURE pcLvw_StdTxtResp
AS
select * from tbStdTxtResp


GO

/****** Object:  Stored Procedure dbo.pcLvw_SysParmType    Script Date: 1/29/98 10:02:08 AM ******/
CREATE PROCEDURE pcLvw_SysParmType AS
SELECT * FROM tbSysParmType

GO

/****** Object:  Stored Procedure dbo.pcLvw_TechStat    Script Date: 1/29/98 10:02:08 AM ******/
CREATE PROCEDURE pcLvw_TechStat
AS
select * from tbTechStat


GO

/****** Object:  Stored Procedure dbo.pcUpd_domain    Script Date: 1/29/98 10:02:08 AM ******/
CREATE PROCEDURE pcUpd_domain
@Domain               varchar(12)
,@Code                varchar(7)
,@Descr               varchar(50)

AS
DECLARE @RetCode      int
DECLARE @_error       int
DECLARE @_rowcount    int

SELECT @RetCode = 0

IF @Domain ='tbSkill'
   BEGIN
      UPDATE tbSkill
             SET Descr=@Descr
             WHERE Code=@Code

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)
         BEGIN
            IF (@_error = 0)
               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not update Skill record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE
         BEGIN
            SELECT @RetCode
            RETURN @RetCode
         END
   END

IF @Domain ='tbAuditType'
   BEGIN
      UPDATE tbAuditType
             SET Descr=@Descr
             WHERE Code=@Code

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)
         BEGIN
            IF (@_error = 0)
               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not update Audit_Type record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE
         BEGIN
            SELECT @RetCode
            RETURN @RetCode
         END
   END

IF @Domain ='tbLocation'
   BEGIN
      UPDATE tbLocation
             SET Descr=@Descr
             WHERE Code=@Code

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)
         BEGIN
            IF (@_error = 0)
               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not update Location record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE
         BEGIN
            SELECT @RetCode
            RETURN @RetCode
         END
   END

IF @Domain ='tbPriority'
   BEGIN
      UPDATE tbPriority
             SET Descr=@Descr
             WHERE Code=@Code

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)
         BEGIN
            IF (@_error = 0)
               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not update Priority record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE
         BEGIN
            SELECT @RetCode
            RETURN @RetCode
         END
   END

IF @Domain ='tbReqDetType'
   BEGIN
      UPDATE tbReqDetType
             SET Descr=@Descr
             WHERE Code=@Code

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)
         BEGIN
            IF (@_error = 0)
               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not update Request_Detail_Type record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE
         BEGIN
            SELECT @RetCode
            RETURN @RetCode
         END
   END

IF @Domain ='tbResolType'
   BEGIN
      UPDATE tbResolType
             SET Descr=@Descr
             WHERE Code=@Code

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)
         BEGIN
            IF (@_error = 0)
               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not update Resolution_Type record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE
         BEGIN
            SELECT @RetCode
            RETURN @RetCode
         END
   END

IF @Domain ='tbStatus'
   BEGIN
      UPDATE tbStatus
             SET Descr=@Descr
             WHERE Code=@Code

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)
         BEGIN
            IF (@_error = 0)
               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not update Status record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE
         BEGIN
            SELECT @RetCode
            RETURN @RetCode
         END
   END

IF @Domain ='tbSysParmType'
   BEGIN
      UPDATE tbSysParmType
             SET Descr=@Descr
             WHERE Code=@Code

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)
         BEGIN
            IF (@_error = 0)
               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not update System_Parameter_Type record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE
         BEGIN
            SELECT @RetCode
            RETURN @RetCode
         END
   END


IF @Domain ='tbTechStat'
   BEGIN
      UPDATE tbTechStat
             SET Descr=@Descr
             WHERE Code=@Code

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)

         BEGIN
            IF (@_error = 0)
               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not update Technician_Status record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE
         BEGIN
            SELECT @RetCode
            RETURN @RetCode
         END
   END


GO

/****** Object:  Stored Procedure dbo.pcGet_Tech    Script Date: 1/29/98 10:02:08 AM ******/
CREATE PROCEDURE pcGet_Tech
@TechId int
AS
SELECT * FROM tbTech WHERE PKId = @TechId


GO

/****** Object:  Stored Procedure dbo.pcInitCurTech    Script Date: 1/29/98 10:02:08 AM ******/
CREATE PROCEDURE pcInitCurTech AS

--Clear current technician table
delete from tbCurTech

--Build current tech table for each combination of locatin and skill
insert into tbCurTech (LocId, SkillId)
(select tbLocation.PKId as LocId, tbSkill.PKId as SkillId from tbLocation, tbSkill)
GO

/****** Object:  Stored Procedure dbo.pcLogoff_Tech    Script Date: 1/29/98 10:02:08 AM ******/
CREATE PROCEDURE pcLogoff_Tech
@TechId int = null
AS
UPDATE tbTech SET StatusId = (SELECT PKId FROM tbTechStat WHERE Code = 'LOGOFF')
WHERE PKId = @TechId




GO

/****** Object:  Stored Procedure dbo.pcLogon_Tech    Script Date: 1/29/98 10:02:08 AM ******/
CREATE PROCEDURE pcLogon_Tech
@TechId int = null
AS
UPDATE tbTech SET StatusId = (SELECT PKId FROM tbTechStat WHERE Code = 'LOGON')
WHERE PKId = @TechId


GO

/****** Object:  Stored Procedure dbo.pcLvw_Techs    Script Date: 1/29/98 10:02:08 AM ******/
CREATE PROCEDURE pcLvw_Techs
@Working   int = NULL
, @SkillId int = NULL
, @LocId   int = NULL
AS
SELECT PKId, LocId, SkillId, EmailAlias FROM tbTech

GO

/****** Object:  Stored Procedure dbo.pcClaim_Req    Script Date: 1/29/98 10:02:08 AM ******/
CREATE PROCEDURE pcClaim_Req
@TechId     int
, @ReqId    int
AS

UPDATE tbReq
SET StatusId=(select PKId from tbStatus where Code='CLAIMED')
WHERE ((PKId = @ReqId AND TechId = @TechId) AND StatusId = (select PKId from tbStatus where Code='UNCLAIM'))

GO

/****** Object:  Stored Procedure dbo.pcCommence_Req    Script Date: 1/29/98 10:02:08 AM ******/
CREATE PROCEDURE pcCommence_Req
@ReqId int
,@TechId int
AS

UPDATE tbReq
SET StatusId=(select PKId from tbStatus where Code='INPROG')
WHERE ((PKId = @ReqId AND TechId = @TechId) AND StatusId = (select PKId from tbStatus where Code='CLAIMED'))

GO

/****** Object:  Stored Procedure dbo.pcDel_Domain    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcDel_Domain
@Domain               varchar(12)
,@Code                varchar(7)

AS
DECLARE @RetCode      int
DECLARE @_error       int

DECLARE @_rowcount    int

SELECT @RetCode = 0

IF @Domain ='tbSkill'
   BEGIN
      DELETE FROM tbSkill
             WHERE Code=@Code

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)
         BEGIN
            IF (@_error = 0)
               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not delete Skill record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE
         BEGIN
            --rebuild current technician table
            exec pcInitCurTech
            SELECT @RetCode
            RETURN @RetCode
         END
   END

IF @Domain ='tbAuditType'
   BEGIN
      DELETE FROM tbAuditType
             WHERE Code=@Code

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)
         BEGIN
            IF (@_error = 0)
               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not delete Audit_Type record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE
         BEGIN
            SELECT @RetCode
            RETURN @RetCode
         END
   END

IF @Domain ='tbLocation'
   BEGIN
      DELETE FROM tbLocation

             WHERE Code=@Code

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)
         BEGIN
            IF (@_error = 0)
               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not delete Location record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE
         BEGIN
            --rebuild current technician table
            exec pcInitCurTech
            SELECT @RetCode
            RETURN @RetCode
         END
   END

IF @Domain ='tbPriority'
   BEGIN
      DELETE FROM tbPriority
             WHERE Code=@Code

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)
         BEGIN
            IF (@_error = 0)
               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not delete Priority record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE
         BEGIN
            SELECT @RetCode
            RETURN @RetCode
         END
   END

IF @Domain ='tbReqDetType'
   BEGIN
      DELETE FROM tbReqDetType
             WHERE Code=@Code

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)
         BEGIN
            IF (@_error = 0)
               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not delete Request_Detail_Type record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE
         BEGIN
            SELECT @RetCode
            RETURN @RetCode
         END
   END

IF @Domain ='tbResolType'
   BEGIN
      DELETE FROM tbResolType
             WHERE Code=@Code

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)
         BEGIN
            IF (@_error = 0)
               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not delete Resolution_Type record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE
         BEGIN
            SELECT @RetCode
            RETURN @RetCode
         END
   END

IF @Domain ='tbStatus'
   BEGIN
      DELETE FROM tbStatus
             WHERE Code=@Code

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)
         BEGIN
            IF (@_error = 0)
               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not delete Status record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE
         BEGIN
            SELECT @RetCode
            RETURN @RetCode
         END
   END

IF @Domain ='tbSysParmType'
   BEGIN
      DELETE FROM tbSysParmType
             WHERE Code=@Code

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)
         BEGIN
            IF (@_error = 0)
               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not delete System_Parameter_Type record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE
         BEGIN
            SELECT @RetCode
            RETURN @RetCode
         END
   END


IF @Domain ='tbTechStat'
   BEGIN
      DELETE FROM tbTechStat
             WHERE Code=@Code

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)

         BEGIN
            IF (@_error = 0)
               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not delete Technician_Status record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE
         BEGIN
            SELECT @RetCode
            RETURN @RetCode
         END
   END
GO

/****** Object:  Stored Procedure dbo.pcDel_technician    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcDel_technician
@EmailAlias          varchar(12)

AS
DECLARE @RetCode      int
DECLARE @_error       int
DECLARE @_rowcount    int


SELECT @RetCode = 0

DELETE FROM tbTech
       WHERE EmailAlias = @EmailAlias

SELECT @_error = @@error ,@_rowcount = @@rowcount
IF (@_error <> 0) OR (@_rowcount <> 1)
  BEGIN
    IF (@_error = 0) SELECT @_error = 333
    SELECT  @RetCode = -(Abs(@_error))
    RAISERROR('Could not delete Technician record.',16,4) 
    SELECT @RetCode
    RETURN @RetCode
  END
ELSE
  BEGIN
    --rebuild current technician table
    exec pcInitCurTech
    SELECT @RetCode
    RETURN @RetCode
  END
GO

/****** Object:  Stored Procedure dbo.pcGet_Req    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcGet_Req
@ReqId        int = NULL
,@TrackingNo  int = NULL
AS

If @ReqId IS NULL and @TrackingNo IS NOT NULL  
    BEGIN    
    SELECT * FROM tbReq WHERE TrackingNo = @TrackingNo
    RETURN 0
    END
if @ReqId IS NOT NULL and @TrackingNo IS NULL
    BEGIN
    SELECT * FROM tbReq WHERE PKId = @ReqId    
    RETURN 0
    END

SELECT * FROM tbReq WHERE PKId=@ReqId and TrackingNo = @TrackingNo

GO

/****** Object:  Stored Procedure dbo.pcGetMostAvailableTech    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcGetMostAvailableTech
  @LocId   int
, @SkillId int
, @TechId  int OUTPUT AS


SET ROWCOUNT 1
SELECT @TechId=tbTech.PKId FROM tbTech,tbReq
WHERE tbTech.PKId <> @TechId
    AND tbTech.LocId = @LocId
    AND tbTech.SkillId = @SkillId
    AND tbTech.PKId *= tbReq.TechId
    AND tbReq.StatusId < (select PKId from tbStatus where Code = 'PENDING')
GROUP BY tbTech.PKId
ORDER BY Count(tbReq.PKId)

GO

/****** Object:  Stored Procedure dbo.pcIns_Domain    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcIns_Domain
@Domain               varchar(12)
,@Code                varchar(7)
,@Descr               varchar(50)

AS
DECLARE @RetCode      int
DECLARE @_error       int
DECLARE @_rowcount    int

SELECT @RetCode = 0

IF @Domain ='tbSkill'
   BEGIN
      INSERT INTO tbSkill
             (Descr, Code)
             VALUES
             (@Descr, @Code)

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)
         BEGIN

            IF (@_error = 0)
               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not insert Skill record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE
         BEGIN
            --rebuild current technician table
            exec pcInitCurTech
            SELECT @RetCode
            RETURN @RetCode
         END
   END

IF @Domain ='tbAuditType'
   BEGIN
      INSERT INTO  tbAuditType
             (Descr, Code)
             VALUES
             (@Descr, @Code)


      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)
         BEGIN
            IF (@_error = 0)
               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not insert Audit_Type record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE
         BEGIN
            SELECT @RetCode
            RETURN @RetCode
         END
   END

IF @Domain ='tbLocation'
   BEGIN
      INSERT INTO  tbLocation
             (Descr, Code)
             VALUES
             (@Descr, @Code)

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)
         BEGIN
            IF (@_error = 0)
               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not insert Location record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE

         BEGIN
            --rebuild current technician table
            exec pcInitCurTech
            SELECT @RetCode
            RETURN @RetCode
         END
   END

IF @Domain ='tbPriority'
   BEGIN
      INSERT INTO  tbPriority
             (Descr, Code)
             VALUES
             (@Descr, @Code)

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)
         BEGIN
            IF (@_error = 0)
               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not insert Priority record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE
         BEGIN
            SELECT @RetCode
            RETURN @RetCode
         END
   END

IF @Domain ='tbReqDetType'
   BEGIN
      INSERT INTO  tbReqDetType
             (Descr, Code)
             VALUES
             (@Descr, @Code)

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)
         BEGIN
            IF (@_error = 0)

               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not insert Request_Detail_Type record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE

         BEGIN
            SELECT @RetCode
            RETURN @RetCode
         END
   END

IF @Domain ='tbResolType'
   BEGIN
      INSERT INTO  tbResolType
             (Descr, Code)
             VALUES
             (@Descr, @Code)

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)
         BEGIN
            IF (@_error = 0)
               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not insert Resolution_Type record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE
         BEGIN
            SELECT @RetCode
            RETURN @RetCode
         END
   END

IF @Domain ='tbStatus'
   BEGIN
      INSERT INTO  tbStatus
             (Descr, Code)
             VALUES
             (@Descr, @Code)

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)
         BEGIN
            IF (@_error = 0)

               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not insert Status record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE
         BEGIN
            SELECT @RetCode
            RETURN @RetCode
         END
   END

IF @Domain ='tbSysParmType'
   BEGIN
      INSERT INTO  tbSysParmType
             (Descr, Code)
             VALUES
             (@Descr, @Code)

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)
         BEGIN
            IF (@_error = 0)
               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not insert System_Parameter_Type record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE
         BEGIN
            SELECT @RetCode
            RETURN @RetCode
         END
   END


IF @Domain ='tbTechStat'
   BEGIN
      INSERT INTO  tbTechStat
             (Descr, Code)
             VALUES
             (@Descr, @Code)

      SELECT @_error = @@error ,@_rowcount = @@rowcount
      IF (@_error <> 0) OR (@_rowcount <> 1)

         BEGIN
            IF (@_error = 0)
               SELECT @_error = 333
            SELECT  @RetCode = -(Abs(@_error))
            RAISERROR('Could not insert Technician_Status record.',16,4) 
            SELECT @RetCode
            RETURN @RetCode
         END
      ELSE
         BEGIN
            SELECT @RetCode
            RETURN @RetCode
         END
   END
GO

/****** Object:  Stored Procedure dbo.pcIns_Req    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcIns_Req
 @ReqDate             datetime      = NULL
,@LocId               int
,@PriorityId          int
,@SkillId             int
,@EmailAlias          varchar(12)
,@Description         varchar(50)   = NULL

AS
DECLARE @CurTechId    int
DECLARE @TechId       int
DECLARE @RetCode      int
DECLARE @_error       int
DECLARE @_rowcount    int
DECLARE @StatusId     int
DECLARE @TrackingNo   int

SELECT @RetCode = 0
SELECT @StatusId = 1

--Use system date if date was not provided
IF (@ReqDate Is NULL)
    SELECT @ReqDate = getdate()

--Get the most recently selected technician for Location and Skill
SELECT @CurTechId = CurTechId FROM tbCurTech
    WHERE (LocId = @LocId AND SkillId = @SkillId)

--Get next TechId for Loc and Skill
SELECT @TechId = Min(PKId) FROM tbTech
    WHERE (PKId > @CurTechId) AND  (LocId = @LocId AND SkillId = @SkillId)

If @TechId Is NULL
--Get first TechId for Loc and Skill
SELECT @TechId = Min(PKId) FROM tbTech WHERE LocId = @LocId AND SkillId = @SkillId

If @TechId Is NULL
--Get next TechId regardless of Loc and Skill
SELECT @TechId = Min(PKId) FROM tbTech WHERE PKId > @CurTechId

If @TechId Is NULL
--Get first TechId regardless of Loc and Skill
SELECT @TechId = Min(PKId) FROM tbTech

--Update CurTechId in tbNextTech 
If NOT @TechId IS NULL
UPDATE tbCurTech
SET CurTechId=@TechId
WHERE LocId = @LocId AND SkillId = @SkillId


IF @TechId IS NULL
    select @StatusId=PKId from tbStatus where Code = 'UNASSGN'
ELSE
    select @StatusId=PKId from tbStatus where Code = 'UNCLAIM'


INSERT INTO tbReq
(

ReqDate
,LocId
,PriorityId
,SkillId
,StatusId
,TechId
,EmailAlias
,Descr
,TrackingNo
)
VALUES
(
@ReqDate
,@LocId
,@PriorityId
,@SkillId

,@StatusId
,@TechId
,@EmailAlias
,@Description
,0
)

SELECT @_error = @@error ,@_rowcount = @@rowcount
IF (@_error <> 0) OR (@_rowcount <> 1)
  BEGIN
    IF (@_error = 0) SELECT @_error = 333
    SELECT  @RetCode = -(Abs(@_error))
    RAISERROR('Could not insert Req record.',16,4) 
    RETURN @RetCode
  END

SELECT @TrackingNo = @@IDENTITY
UPDATE tbReq set TrackingNo = @TrackingNo WHERE PKId = @TrackingNo

SELECT @_error = @@error ,@_rowcount = @@rowcount
IF (@_error <> 0) OR (@_rowcount <> 1)
  BEGIN
    IF (@_error = 0) SELECT @_error = 333
    SELECT  @RetCode = -(Abs(@_error))
    RAISERROR('Could not insert Req record.',16,4) 
    RETURN @RetCode
  END
ELSE
  BEGIN
    SELECT @TrackingNo
    RETURN @RetCode

  END
GO

/****** Object:  Stored Procedure dbo.pcIns_SysParm    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcIns_SysParm
 @ChangedById         int
,@ParmTypeId          int
,@ChangeDate          datetime
,@Descr               varchar(50)
,@SysValue            varchar(255)

AS
DECLARE @RetCode      int
DECLARE @_error       int
DECLARE @_rowcount    int

SELECT @RetCode = 0

--Use system date if date was not provided
IF (@ChangeDate Is NULL)
    SELECT @ChangeDate = getdate()

INSERT INTO tbSysParameters
(

ChangedById
,ParmTypeId
,ChangeDate
,Descr
,SysValue
)
VALUES

(
@ChangedById
,@ParmTypeId
,@ChangeDate
,@Descr
,@SysValue
)

SELECT @_error = @@error ,@_rowcount = @@rowcount
IF (@_error <> 0) OR (@_rowcount <> 1)
  BEGIN
    IF (@_error = 0) SELECT @_error = 333
    SELECT  @RetCode = -(Abs(@_error))
    RAISERROR('Could not insert SysParameter record.',16,4) 
    SELECT @RetCode
    RETURN @RetCode
  END

GO

/****** Object:  Stored Procedure dbo.pcIns_technician    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcIns_technician
@EmailAlias          varchar(12)
,@LocId               int
,@SkillId             int

AS
DECLARE @RetCode      int

DECLARE @_error       int
DECLARE @_rowcount    int
DECLARE @StatusId     int

SELECT @RetCode = 0
SELECT @StatusId = PKId FROM tbTechStat WHERE Code = 'LOGOFF'

INSERT INTO tbTech
(LocId
,SkillId
,EmailAlias
,StatusId
)
VALUES
(
@LocId
,@SkillId
,@EmailAlias
,@StatusId
)

SELECT @_error = @@error ,@_rowcount = @@rowcount
IF (@_error <> 0) OR (@_rowcount <> 1)
  BEGIN
    IF (@_error = 0) SELECT @_error = 333
    SELECT  @RetCode = -(Abs(@_error))
    RAISERROR('Could not insert Technician record.',16,4) 
    SELECT @RetCode
    RETURN @RetCode
  END
ELSE
  BEGIN
    --rebuild current technician table
    exec pcInitCurTech
    SELECT @RetCode
    RETURN @RetCode
  END
GO

/****** Object:  Stored Procedure dbo.pcLvw_Requests    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcLvw_Requests
@TechId       int         = NULL
, @EmailAlias VarChar(12) = NULL

AS
If @EmailAlias Is NULL
    If @TechId Is NULL
        select * from tbReq
    else
        select * from tbReq
        where TechId = @TechId
else
    If @TechId Is NULL
        select * from tbReq where EmailAlias=@EmailAlias
    else
        select * from tbReq where EmailAlias=@EmailAlias and TechId=@TechId

GO

/****** Object:  Stored Procedure dbo.pcLvw_SysParms    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcLvw_SysParms
AS
select * from tbSysParameters

GO

/****** Object:  Stored Procedure dbo.pcNotConfRes    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcNotConfRes 
@ReqId   int
AS

--Update request status
update tbReq set StatusId = (select PKId from tbStatus where Code = 'INPROG')
where (PKId = @ReqId) and (StatusId = (select PKId from tbStatus where Code = 'PENDING'))

GO

/****** Object:  Stored Procedure dbo.pcReAssign_Req    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcReAssign_Req
@ReqId           int
, @FromTechId    int = NULL
, @ToTechId      int = NULL
AS
UPDATE tbReq
SET TechId=@ToTechId
WHERE PKId = @ReqId AND TechId = @FromTechId

GO

/****** Object:  Stored Procedure dbo.pcResConfirm    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcResConfirm
@ReqId   int
AS


If Not @ReqId Is Null
--Update request status
update tbReq
set StatusId = (select PKId from tbStatus where Code = 'RESOLVD')
   ,ResolDate = getdate()
   ,ResolTypeId = (select PKId from tbResolType where Code = 'CONFREC')
where PKId = @ReqId

GO

/****** Object:  Stored Procedure dbo.pcResolve_Req    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcResolve_Req
@ReqId int
,@TechId int
AS

UPDATE tbReq
SET StatusId=(select PKId from tbStatus where Code='PENDING')
WHERE ((PKId = @ReqId AND TechId = @TechId) AND StatusId = (select PKId from tbStatus where Code='INPROG'))

GO

/****** Object:  Stored Procedure dbo.pcSnap_Stat    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcSnap_Stat
 AS
select ReqDate,PriorityId,SkillId,StatusId from tbReq

GO

/****** Object:  Stored Procedure dbo.pcSubmit_Req    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcSubmit_Req
@ReqId int
,@TechId int
AS

UPDATE tbReq
SET StatusId=(select PKId from tbStatus where Code='PENDING')
WHERE ((PKId = @ReqId AND TechId = @TechId) AND StatusId = (select PKId from tbStatus where Code='INPROG'))

GO

/****** Object:  Stored Procedure dbo.pcUnclaim_Req    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcUnclaim_Req
@ReqId int
,@TechId int
AS

UPDATE tbReq
SET StatusId=(select PKId from tbStatus where Code='UNCLAIM')
WHERE ((PKId = @ReqId AND TechId = @TechId))

GO

/****** Object:  Stored Procedure dbo.pcUpd_technician    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcUpd_technician
@EmailAlias          varchar(12)
,@LocId               int
,@SkillId             int

AS
DECLARE @RetCode      int

DECLARE @_error       int
DECLARE @_rowcount    int

SELECT @RetCode = 0

UPDATE tbTech
       SET SkillId=@SkillId, LocId=@LocId
       WHERE EmailAlias=@EmailAlias

SELECT @_error = @@error ,@_rowcount = @@rowcount
IF (@_error <> 0) OR (@_rowcount <> 1)
  BEGIN
    IF (@_error = 0) SELECT @_error = 333
    SELECT  @RetCode = -(Abs(@_error))
    RAISERROR('Could not insert Technician record.',16,4) 
    SELECT @RetCode
    RETURN @RetCode
  END
ELSE
  BEGIN
    --rebuild current technician table
    exec pcInitCurTech
    SELECT @RetCode
    RETURN @RetCode
  END
GO

/****** Object:  Stored Procedure dbo.pcGet_ReqDet    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcGet_ReqDet
@ReqDetId int
AS
declare @ReqDetType int

select @ReqDetType = ReqDetTypeId from tbReqDet where PKId = @ReqDetId

If @ReqDetType=(select PKId from tbReqDetType where Code = 'TXTREQ')
    select tbReqDet.PKId
         , tbReqDet.DetDate
         , tbReqDet.ReqDetTypeId
         , tbReqDet.TechId
         , Convert(varchar(255), tbTxtReq.ReqText) as DetMsg
    from tbReqDet,tbTxtReq where tbReqDet.PKId = @ReqDetId and tbTxtReq.PKId = tbReqDet.DetMsgId 

If @ReqDetType=(select PKId from tbReqDetType where Code = 'VOCREQ')
    select tbReqDet.PKId
         , tbReqDet.DetDate
         , tbReqDet.ReqDetTypeId
         , tbReqDet.TechId
         , Convert(varchar(255), tbVoiceReq.ReqText) as DetMsg
    from tbReqDet,tbVoiceReq where tbReqDet.PKId = @ReqDetId and tbVoiceReq.PKId = tbReqDet.DetMsgId 

If @ReqDetType=(select PKId from tbReqDetType where Code = 'TXTRSP')
    select tbReqDet.PKId
         , tbReqDet.DetDate
         , tbReqDet.ReqDetTypeId
         , tbReqDet.TechId
         , Convert(varchar(255), tbTxtResp.RespText) as DetMsg
    from tbReqDet,tbTxtResp where tbReqDet.PKId = @ReqDetId and tbTxtResp.PKId = tbReqDet.DetMsgId 

If @ReqDetType=(select PKId from tbReqDetType where Code = 'VOCRSP')
    select tbReqDet.PKId
         , tbReqDet.DetDate
         , tbReqDet.ReqDetTypeId
         , tbReqDet.TechId
         , Convert(varchar(255), tbVoiceResp.RespText) as DetMsg

   from tbReqDet,tbVoiceResp where tbReqDet.PKId = @ReqDetId and tbVoiceResp.PKId = tbReqDet.DetMsgId 

if @ReqDetType=(select PKId from tbReqDetType where Code = 'STDTXT')
    select tbReqDet.PKId
         , tbReqDet.DetDate
         , tbReqDet.ReqDetTypeId
         , tbReqDet.TechId
         , Convert(varchar(255), tbStdTxtResp.MsgText) as DetMsg
    from tbReqDet,tbStdTxtResp where tbReqDet.PKId = @ReqDetId and tbStdTxtResp.PKId = tbReqDet.DetMsgId 

if @ReqDetType=(select PKId from tbReqDetType where Code = 'STDVOC')
    select tbReqDet.PKId
         , tbReqDet.DetDate
         , tbReqDet.ReqDetTypeId
         , tbReqDet.TechId
         , Convert(varchar(255), tbStdVoiceResp.MsgText) as DetMsg
    from tbReqDet,tbStdVoiceResp where tbReqDet.PKId = @ReqDetId and tbStdVoiceResp.PKId = tbReqDet.DetMsgId

GO

/****** Object:  Stored Procedure dbo.pcLvw_ReqDets    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcLvw_ReqDets
@ReqId int
AS

SELECT tbReqDet.PKId
,tbReqDet.DetDate
,tbReqDet.ReqDetTypeId
,tbReqDet.TechId
,Convert(varchar, tbTxtReq.ReqText) as DetMsg
FROM tbReqDet,tbTxtReq
WHERE tbReqDet.ReqId = @ReqId
  and tbReqDet.ReqDetTypeId = (select PKId from tbReqDetType where Code = 'TXTREQ')
  and tbTxtReq.PKId = tbReqDet.DetMsgId

union all

SELECT tbReqDet.PKId
,tbReqDet.DetDate
,tbReqDet.ReqDetTypeId
,tbReqDet.TechId
,Convert(varchar, tbVoiceReq.ReqText) as DetMsg
FROM tbReqDet,tbVoiceReq
WHERE tbReqDet.ReqId = @ReqId
  and tbReqDet.ReqDetTypeId = (select PKId from tbReqDetType where Code = 'VOCREQ')
  and tbVoiceReq.PKId = tbReqDet.DetMsgId

union all

SELECT tbReqDet.PKId
,tbReqDet.DetDate
,tbReqDet.ReqDetTypeId
,tbReqDet.TechId
,Convert(varchar, tbTxtResp.RespText) as DetMsg
FROM tbReqDet,tbTxtResp
WHERE tbReqDet.ReqId = @ReqId
  and tbReqDet.ReqDetTypeId = (select PKId from tbReqDetType where Code = 'TXTRSP')
  and tbTxtResp.PKId = tbReqDet.DetMsgId

union all

SELECT tbReqDet.PKId
,tbReqDet.DetDate
,tbReqDet.ReqDetTypeId
,tbReqDet.TechId
,Convert(varchar, tbVoiceResp.RespText) as DetMsg
FROM tbReqDet,tbVoiceResp
WHERE tbReqDet.ReqId = @ReqId
  and tbReqDet.ReqDetTypeId = (select PKId from tbReqDetType where Code = 'VOCRSP')
  and tbVoiceResp.PKId = tbReqDet.DetMsgId

union all

SELECT tbReqDet.PKId
,tbReqDet.DetDate
,tbReqDet.ReqDetTypeId
,tbReqDet.TechId
,Convert(varchar, tbStdTxtResp.MsgText) as DetMsg
FROM tbReqDet,tbStdTxtResp

WHERE tbReqDet.ReqId = @ReqId
  and tbReqDet.ReqDetTypeId = (select PKId from tbReqDetType where Code = 'STDTXT')
  and tbStdTxtResp.PKId = tbReqDet.DetMsgId

union all

SELECT tbReqDet.PKId
,tbReqDet.DetDate
,tbReqDet.ReqDetTypeId
,tbReqDet.TechId
,Convert(varchar, tbStdVoiceResp.MsgText) as DetMsg
FROM tbReqDet,tbStdVoiceResp
WHERE tbReqDet.ReqId = @ReqId
  and tbReqDet.ReqDetTypeId = (select PKId from tbReqDetType where Code = 'STDVOC')
  and tbStdVoiceResp.PKId = tbReqDet.DetMsgId

ORDER by tbReqDet.DetDate

GO

/****** Object:  Stored Procedure dbo.pcSendStdTextResp    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcSendStdTextResp
@ReqId              int
, @TechId           int
, @StdTextRespId    int

AS
declare @ReqDetTypeId int

select @ReqDetTypeId=PKId from tbReqDetType where Code = 'STDTXT'

--Insert the reqDet record
    insert into tbReqDet(ReqId, ReqDetTypeId, DetMsgId, TechId, DetDate )
        values(@ReqId, @ReqDetTypeId, @StdTextRespId, @TechId, GetDate())

GO

/****** Object:  Stored Procedure dbo.pcSendStdVoiceResp    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcSendStdVoiceResp
@ReqId int
, @TechId int
, @StdVoiceRespId int

AS

declare @ReqDetTypeId int

select @ReqDetTypeId=PKId from tbReqDetType where Code = 'STDVOC'

--Insert the reqDet record
    insert into tbReqDet(ReqId, ReqDetTypeId, DetMsgId, TechId, DetDate )
        values(@ReqId, @ReqDetTypeId, @StdVoiceRespId, @TechId, GetDate())

GO

/****** Object:  Stored Procedure dbo.pcSendTextReq    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcSendTextReq
@ReqId       int
,@MsgText    text

AS

declare @ReqDetTypeId int
select @ReqDetTypeId=PKId from tbReqDetType where Code = 'TXTREQ'

--Insert the tbTxtReq record
    insert into tbTxtReq(ReqText) values(@MsgText)

--Insert the reqDet record
    insert into tbReqDet(ReqId, ReqDetTypeId, DetMsgId, DetDate )
        values(@ReqId, @ReqDetTypeId, @@IDENTITY, GetDate())


GO

/****** Object:  Stored Procedure dbo.pcSendTextResp    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcSendTextResp
@ReqId     int
,@TechId   int
,@MsgText  text

AS
declare @ReqDetTypeId int
select @ReqDetTypeId = PKId from tbReqDetType where Code='TXTRSP'

--Insert the tbTxtResp record
    insert into tbTxtResp(RespText) values(@MsgText)

--Insert the reqDet record
    insert into tbReqDet(ReqId, ReqDetTypeId, DetMsgId, TechId, DetDate )
        values(@ReqId, @ReqDetTypeId, @@IDENTITY, @TechId, GetDate())

GO

/****** Object:  Stored Procedure dbo.pcSendVoiceReq    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcSendVoiceReq
@ReqId  int
,@MsgText    text

AS

declare @ReqDetTypeId int
select @ReqDetTypeId=PKId from tbReqDetType where Code = 'VOCREQ'


--Insert the tbVoiceReq record
    insert into tbVoiceReq(ReqText) values(@MsgText)

--Insert the ReqDet record
    insert into tbReqDet(ReqId, ReqDetTypeId, DetMsgId, DetDate )
        values(@ReqId, @ReqDetTypeId, @@IDENTITY, GetDate())

GO

/****** Object:  Stored Procedure dbo.pcSendVoiceResp    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcSendVoiceResp
@ReqId       int
,@TechId     int
,@MsgText    text

AS

declare @ReqDetTypeId int

select @ReqDetTypeId=PKId from tbReqDetType where Code = 'VOCRSP'


--Insert the tbVoiceresp record
    insert into tbVoiceResp(RespText) values(@MsgText)

--Insert the reqDet record
    insert into tbReqDet(ReqId, ReqDetTypeId, DetMsgId, TechId, DetDate )
        values(@ReqId, @ReqDetTypeId, @@IDENTITY, @TechId, GetDate())

GO

/****** Object:  Stored Procedure dbo.pcShuffle_Reqs    Script Date: 1/29/98 10:02:09 AM ******/
CREATE PROCEDURE pcShuffle_Reqs AS
DECLARE @OldId      int
DECLARE @ReqId      int
DECLARE @ReqStr     VarChar(12)

DECLARE @LocId      int
DECLARE @SkillId    int
DECLARE @FromTechId int
DECLARE @ToTechId   int
DECLARE @ShuffleId  int


SELECT @ShuffleId = PKId FROM tbStatus WHERE Code = 'UNCLAIM' 

--Select unclaimed request records
SET ROWCOUNT 1
SELECT @ReqId = PKId, @LocId = LocId, @SkillId = SkillId, @FromTechId = TechId FROM tbReq
    WHERE StatusId <= @ShuffleId

WHILE NOT @ReqId IS NULL
    BEGIN
    SET ROWCOUNT 0

    EXEC pcGetMostAvailableTech @LocId=@LocId, @SkillId=@SkillId, @TechId=@ToTechId OUTPUT
    
    IF NOT @ToTechId IS NULL
        BEGIN
        UPDATE tbReq
        SET TechId=@ToTechId, StatusId=@ShuffleId
        WHERE PKId = @ReqId
        END    
    SELECT @OldId = @ReqId
    SELECT @ReqId = NULL
    SET ROWCOUNT 1
    SELECT @ReqId = PKId, @LocId = LocId, @SkillId = SkillId, @FromTechId = TechId FROM tbReq
        WHERE PKId > @OldId AND StatusId <= @ShuffleId
    END

GO

