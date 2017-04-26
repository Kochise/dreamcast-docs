/*++

  COPYRIGHT        (C) NEC        Corporation 1997 - 1999

  All rights reserved by NEC Corporation. This program must be
  used solely for the purpose for which it was furnished by NEC
  Corporation. No part of this program may be reproduced or
  disclosed to others, in any form, without the prior written
  permission of NEC Corporation.
  Use of copyright notice does not evidence publication of this
  program.

  Author     :		T.Hirata(NEC Software,Ltd.)
  Module Name:		km2api_clb.h

  Abstract:
	KAMUI = Kamui is abstruction model that is ultimate interface for PowerVR.
	'km2api_clb.h' define the function which is related with callback.

  Environment:
	ANSI C Compiler.

  Notes:
	This heder file defines the function which registers callback function.
	The factor of callback is shown bellow.
		- end of render
		- end of vertex
		- end of yuv
		- V-Sync
		- H-Sync

		- Texture Over flow
		- Waiting V-Sync()

		- Strip Buffer Overrun
		- Fatal Error

  Revision History:

--*/

#if !defined(__kamui2_callback_api_h__)
#define __kamui2_callback_api_h__

/*++
kmSetEORCallback

proto type:

	KMSTATUS 
	kmSetEORCallback(
			PKMCALLBACKFUNC pEORCallback,
			PVOID pCallbackArguments
		);

Description:
	�����_�����O�I�����ɌĂ΂��R�[���o�b�N�֐���o�^���܂��B
	�R�[���o�b�N�֐��́A�ȉ��̌`���ŃR�[�f�B���O���Ă��������B

		VOID EORCallbackFunc(PVOID pCallbackArguments);

	pCallbackArguments(����)�F�o�^���Ɏw�肳�ꂽ�p�����[�^�ւ̃|�C���^�ł��B

Arguments:
	IN	pEORCallback	�����_�����O�I�����ɌĂ΂��֐��̃|�C���^���w�肵�܂��B
	IN	pCallbackArguments
						callback ���Ɍďo�����֐��֓n���A�����ւ̃|�C���^���w�肵�܂��B


Result:
	KMSTATUS_SUCCESS		�o�^����

--*/

KMSTATUS  KMAPI
kmSetEORCallback(
		PKMCALLBACKFUNC pEORCallback,
		PVOID 			pCallbackArguments
	);

/*++
kmSetVSyncCallback

proto type:
	KMSTATUS
	kmSetVSyncCallback(
			PKMCALLBACKFUNC pVSyncCallback,
			PVOID pCallbackArguments
		);

Description:
	�����A�����(Vsync)�˓����ɌĂяo�����R�[���o�b�N�֐���o�^���܂��B
	�R�[���o�b�N�֐��́A�ȉ��̌`���ŃR�[�f�B���O���Ă��������B

		VOID VSyncCallbackFunc(PVOID pCallbackArguments);

	pCallbackArguments(����)�F�o�^���Ɏw�肳�ꂽ�p�����[�^�ւ̃|�C���^�ł��B

Arguments:
	IN	pVSyncCallback	Vsync�˓����ɌĂ΂��֐��̃|�C���^���w�肵�܂��B
	IN	pCallbackArguments
						callback ���Ɍďo�����֐��֓n���A�����ւ̃|�C���^���w�肵�܂��B

Result:
	KMSTATUS_SUCCESS		�o�^����

--*/

KMSTATUS KMAPI
kmSetVSyncCallback(
		PKMCALLBACKFUNC pVSyncCallback,
		PVOID 			pCallbackArguments
	);

/*++
kmSetHSyncCallback

proto type:
	KMSTATUS
	kmSetHSyncCallback(
			PKMCALLBACKFUNC pHSyncCallback,
			PVOID pCallbackArguments
		);

Description:
	�����A�����(Hsync)�˓����ɌĂяo�����R�[���o�b�N�֐���o�^���܂��B
	�R�[���o�b�N�֐��́A�ȉ��̌`���ŃR�[�f�B���O���Ă��������B

	VOID HSyncCallbackFunc(PVOID pCallbackArguments);

	pCallbackArguments(����)�F�o�^���Ɏw�肳�ꂽ�p�����[�^�ւ̃|�C���^�ł��B

Arguments:
	IN	pHSyncCallback		Hsync�˓����ɌĂ΂��֐��̃|�C���^���w�肵�܂��B

	pCallbackArguments		callback ���Ɍďo�����֐��֓n���A�����ւ̃|�C���^���w�肵�܂��B
							KmSetHSyncLine �Ŏw�肵�����C���ԍ��͓n����Ȃ��̂ŁA
							kmSetHSyncLine �Őݒ肵���l�����̃|�C���^�������̈�ɕێ����邩�A
							�܂��́AkmGetCurrentScanline()���g�p���āA���݂� Scanline �����擾���Ă��������B

Result:
	KMSTATUS_SUCCESS		�o�^����

--*/

KMSTATUS KMAPI
kmSetHSyncCallback(
		PKMCALLBACKFUNC pHSyncCallback,
		PVOID pCallbackArguments
	);

/*++
kmSetTexOverflowCallback

proto type:
	KMSTATUS
	kmSetTexOverflowCallback(
			PKMCALLBACKFUNC pTexOverflowCallback,
			PVOID pCallbackArguments
		);

Description:
	�e�N�X�`�����������c���Ă��Ȃ���ԂŁA�e�N�X�`����o�^���悤�Ƃ����ꍇ�ɌĂ΂��R�[���o�b�N�֐���
	�o�^���܂��B�R�[���o�b�N�֐��́A�ȉ��̌`���ŃR�[�f�B���O���Ă��������B

		VOID TexOverflowCallbackFunc(PVOID pCallbackArguments);

	pCallbackArguments(����)�F�o�^���Ɏw�肳�ꂽ�p�����[�^�ւ̃|�C���^�ł��B

Arguments:
	IN	pTexOverflowCallback	�e�N�X�`���I�[�o�[�t���[���̃R�[���o�b�N�֐��ւ̃|�C���^���w�肵�܂��B
	IN	pCallbackArguments		callback ���Ɍďo�����֐��֓n���A�����ւ̃|�C���^���w�肵�܂��B
	
Result:
	KMSTATUS_SUCCESS		�o�^����

--*/

KMSTATUS KMAPI
kmSetTexOverflowCallback(
		PKMCALLBACKFUNC pTexOverflowCallback,
		PVOID pCallbackArguments
	);

/*++
kmSetStripOverRunCallback

proto type:
	KMSTATUS
	kmSetStripOverRunCallback (
			PKMCALLBACKFUNC	pStripOverRunCallback,
			PVOID			pCallbackArguments
		);

Description:
	StripBuffer�̏c�T�C�Y�̕\�����Ԓ��Ɏ���Strip�̃����_�����O���I�����Ȃ������ꍇ�ɌĂ΂��
	�R�[���o�b�N�֐���o�^���܂��B�R�[���o�b�N�֐��́A�ȉ��̌`���ŃR�[�f�B���O���Ă��������B

			VOID StripOverRunCallbackFunc(PVOID pCallbackArguments);

	pCallbackArguments(����)�F�o�^���Ɏw�肳�ꂽ�p�����[�^�ւ̃|�C���^�ł��B

Arguments:
	IN	pStripOverRunCallback	�R�[���o�b�N�֐��ւ̃|�C���^���w�肵�܂��B
	IN	pCallbackArguments		callback ���Ɍďo�����֐��֓n���A�����ւ̃|�C���^���w�肵�܂��B

Result:
	KMSTATUS_SUCCESS		�o�^����

--*/

KMSTATUS KMAPI
kmSetStripOverRunCallback (
		PKMCALLBACKFUNC	pStripOverRunCallback,
		PVOID			pCallbackArguments
	);

/*++
kmSetEndOfVertexCallback

proto type:
	KMSTATUS
	kmSetEndOfVertexCallback (
			PKMCALLBACKFUNC pEndOfVertexCallback,
			PKMVOID			pCallbackArguments
		);

Description:
	�_�Ђ��烌���_�����O�n�[�h�E�F�A�ւ́A1�V�[���̃f�[�^�]�����I�������ꍇ�ɌĂ΂��R�[���o�b�N�֐���
	�o�^���܂��B�R�[���o�b�N�֐��́A�ȉ��̌`���ŃR�[�f�B���O���Ă��������B

			VOID EndOfVertexCallbackFunc(PVOID pCallbackArguments);

	pCallbackArguments(����)�F�o�^���Ɏw�肳�ꂽ�p�����[�^�ւ̃|�C���^�ł��B

Arguments:
	IN	pEndOfVertexCallback	�R�[���o�b�N�֐��ւ̃|�C���^���w�肵�܂��B
	IN	pCallbackArguments		callback ���Ɍďo�����֐��֓n���A�����ւ̃|�C���^���w�肵�܂��B

Result:
	KMSTATUS_SUCCESS		�o�^����

--*/

KMSTATUS KMAPI
kmSetEndOfVertexCallback (
		PKMCALLBACKFUNC pEndOfVertexCallback,
		PKMVOID 		pCallbackArguments
	);

/*++
kmSetEndOfYUVCallback

proto type:
	KMSTATUS
	kmSetEndOfYUVCallback(
			PKMCALLBACKFUNC pEndOfYUVCallback,
			PVOID pCallbackArguments
		);

Description:
	YUV�R���o�[�^���R���o�[�g���I�������ۂɔ��s����AYUV�I�����荞�݂ɑ΂���
	�R�[���o�b�N�֐���o�^���܂��B

		VOID EndOfYUVFunc(PVOID pCallbackArguments);

	pCallbackArguments(����)�F�o�^���Ɏw�肳�ꂽ�p�����[�^�ւ̃|�C���^�ł��B

Arguments:
	IN	pEndOfYUVCallback		YUV�R���o�[�g�I�����̃R�[���o�b�N�֐��ւ̃|�C���^���w�肵�܂��B
	IN	pCallbackArguments		callback ���Ɍďo�����֐��֓n���A�����ւ̃|�C���^���w�肵�܂��B
	
Result:
	KMSTATUS_SUCCESS		�o�^����

--*/

KMSTATUS KMAPI
kmSetEndOfYUVCallback(
		PKMCALLBACKFUNC pEndOfYUVCallback,
		PVOID pCallbackArguments
	);

/*++
kmSetWaitVsyncCallback

proto type:
	KMSTATUS
	kmSetWaitVsyncCallback(
			PKMCALLBACKFUNC pWaitVsyncCallback,
			PVOID pCallbackArguments
		);

Description:
	Vsync��WAIT���ɌĂ΂��R�[���o�b�N�֐���o�^���܂��BCD-ROM����̓ǂݏo�����o�b�N�O���E���h
	���ōs���ꍇ��A���̑�V�񓯊��������s�����߂̃R�[���o�b�N���Ƃ��Ďg�p���܂��B
	�������A���܂�傫�Ȋ֐��A�R�[���o�b�N���ł̖������[�v���͍s��Ȃ��ł��������B
	
		VOID WaitVsyncCallbackFunc(PVOID pCallbackArguments);

	pCallbackArguments(����)�F�o�^���Ɏw�肳�ꂽ�p�����[�^�ւ̃|�C���^�ł��B

Arguments:
	IN	pWaitVsyncCallback		Vsync�E�F�C�g���̃R�[���o�b�N�֐��ւ̃|�C���^���w�肵�܂��B
	IN	pCallbackArguments		callback ���Ɍďo�����֐��֓n���A�����ւ̃|�C���^���w�肵�܂��B
	
Result:
	KMSTATUS_SUCCESS		�o�^����

--*/

KMSTATUS KMAPI
kmSetWaitVsyncCallback(
		PKMCALLBACKFUNC pWaitVsyncCallback,
		PVOID pCallbackArguments
	);

/*++
kmSetFatalErrorCallback

proto type:
	KMSTATUS
	kmSetFatalErrorCallback(
			PKMCALLBACKFUNC pFaltalErrorCallback,
			PVOID 			pCallbackArguments
		);

Description:
	�_�ЂQ�ł͉񕜕s�\�ȃG���[�����������ꍇ�ɌĂяo�����
	�R�[���o�b�N�֐���o�^���܂��B�ȉ��̌`���ŌĂяo����܂��B

		VOID FaltalErrorCallback(PVOID pCallbackArguments);

	pCallbackArguments(����)�F�o�^���Ɏw�肳�ꂽ�p�����[�^�ւ̃|�C���^�ł��B

Arguments:
	IN	pFaltalErrorCallback	�񕜕s�\�ȃG���[�����������ꍇ�ɌĂяo�����R�[���o�b�N�֐��ł��B
	IN	pCallbackArguments		callback ���Ɍďo�����֐��֓n���A�����ւ̃|�C���^���w�肵�܂��B

Result:
	KMSTATUS_SUCCESS		�o�^����

--*/

KMSTATUS KMAPI
kmSetFatalErrorCallback(
		IN	PKMCALLBACKFUNC pFaltalErrorCallback,
		IN	PVOID			pCallbackArguments
	);


/*++
kmSetPALEXTCallback

proto type:
	KMSTATUS
	kmSetPALEXTCallback(
			PKMCALLBACKFUNC pPalExtCallback,
			PVOID 			Reserved
		);

Description:
	kmSetDisplayMode ���Ăяo�����ۂɁA	PAL ??? EXT ���w�肵���ꍇ�A
	�c�̕\���䗦�����肷�邽�߂̒萔��Ԃ����߂̃R�[���o�b�N�֐��ł��B

		VOID pPalExtCallback(PVOID pData);

	pData �ɂ́A�V�X�e�������� KMPALEXTINFO �\���̂ւ̃|�C���^���n����܂��B
	nPALExtMode �����o�ɑ΂��ēK�؂Ȓl�������Ă��������B
	KMPALEXTINFO �\���̂� nDisplayMode�ɂ́AkmSetDisplayMode ��
	�������������Ă��܂��B

Arguments:
	IN	pFaltalErrorCallback	�񕜕s�\�ȃG���[�����������ꍇ�ɌĂяo�����R�[���o�b�N�֐��ł��B
	IN	reserved				NULL �����Ă��������B

Result:
	KMSTATUS_SUCCESS		�o�^����

--*/

KMSTATUS KMAPI
kmSetPALEXTCallback( 
		IN	PKMCALLBACKFUNC pPalExtCallback,
		IN	PVOID			pCallbackArguments
	);
#endif