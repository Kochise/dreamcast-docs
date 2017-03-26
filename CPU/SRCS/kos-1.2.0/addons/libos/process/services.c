/* KallistiOS 1.2.0

   services.c
   (c)2001 Dan Potter
*/

#include <os/process.h>
#include <os/svcmpx.h>
#include <string.h>

CVSID("$Id: services.c,v 1.4 2002/02/22 07:36:18 bardtx Exp $");

/*

This module sets up services for all the common kernel items that should be
accessable from user programs. Each kernel module used to do this on its
own, but it's done here now so that the kernel doesn't depend on the process
stuff.
 
*/

/* Fundamental */
#include <stdio.h>
#include <malloc.h>
#include <os/abi/fundamental.h>
static abi_fundamental_t fabi;
static void basic_svc_init() {
	memset(&fabi, 0, sizeof(fabi));

	fabi.hdr.version = ABI_MAKE_VER(1,1,0);
	fabi.printf = printf;
	fabi.malloc = malloc;
	fabi.memalign = memalign;
	fabi.debug = NULL;

	svcmpx_add_handler("fundamental", &fabi);
}


#if 0	/* broken for now */
/* Maple */
#include <os/svcmpx.h>
#include <os/abi/maple.h>
static abi_maple_t mabi;
static void maple_svc_init() {
	memset(&mabi, 0, sizeof(mabi));
	
	mabi.hdr.version = ABI_MAKE_VER(1,0,0);

	mabi.create_addr = maple_create_addr;
	mabi.docmd_block = maple_docmd_block;
	mabi.rescan_bus = maple_rescan_bus;
	mabi.device_func = maple_device_func;
	mabi.first_device = maple_first_device;
	mabi.first_controller = maple_first_controller;
	mabi.first_mouse = maple_first_mouse;
	mabi.first_kb = maple_first_kb;
	mabi.first_lcd = maple_first_lcd;
	mabi.first_vmu = maple_first_vmu;
	
	mabi.cont_get_cond = cont_get_cond;
	
	mabi.kbd_get_cond = kbd_get_cond;
	mabi.kbd_set_queue = kbd_set_queue;
	mabi.kbd_enqueue = kbd_enqueue;
	mabi.kbd_get_key = kbd_get_key;
	mabi.kbd_poll = kbd_poll;
	
	mabi.mouse_get_cond = mouse_get_cond;
	
	mabi.vmu_draw_lcd = vmu_draw_lcd;
	mabi.vmu_block_read = vmu_block_read;
	mabi.vmu_block_write = vmu_block_write;

	svcmpx_add_handler("maple", &mabi);
}
#endif

/* SPU */
#include <os/svcmpx.h>
#include <os/abi/spu.h>
static abi_spu_t wasabi;	/* heh */
static void spu_svc_init() {
	memset(&wasabi, 0, sizeof(wasabi));
	
	wasabi.hdr.version = ABI_MAKE_VER(1,0,0);
	
	wasabi.write_wait = spu_write_wait;
	wasabi.memload = spu_memload;
	wasabi.memset = spu_memset;
	wasabi.enable = spu_enable;
	wasabi.disable = spu_disable;
	
	svcmpx_add_handler("spu", &wasabi);
}

/* TA */
#if 0	/* broken for now */
#include <os/svcmpx.h>
#include <os/abi/ta.h>
static abi_ta_t tabi;
static void ta_svc_init() {
	memset(&tabi, 0, sizeof(tabi));

	tabi.hdr.version = ABI_MAKE_VER(1,0,0);

	tabi.hw_init = ta_hw_init;
	tabi.hw_shutdown = ta_hw_shutdown;
	tabi.send_queue = ta_send_queue;
	tabi.begin_render = ta_begin_render;
	tabi.commit_poly_hdr = ta_commit_poly_hdr;
	tabi.commit_vertex = ta_commit_vertex;
	tabi.commit_eol = ta_commit_eol;
	tabi.finish_frame = ta_finish_frame;
	tabi.poly_hdr_col = ta_poly_hdr_col;
	tabi.poly_hdr_txr = ta_poly_hdr_txr;
	tabi.set_buffer_config = ta_set_buffer_config;
	tabi.txr_release_all = ta_txr_release_all;
	tabi.txr_allocate = ta_txr_allocate;
	tabi.txr_load = ta_txr_load;
	tabi.txr_map = ta_txr_map;
	tabi.begin_texture = ta_begin_texture;
	
	
	tabi.bkg = ta_bkg;
	
	svcmpx_add_handler("ta", &tabi);
}
#endif

/* Video */
#include <os/svcmpx.h>
#include <os/abi/video.h>
static abi_video_t vabi;
static void vid_svc_init() {
	memset(&vabi, 0, sizeof(vabi));
	
	vabi.hdr.version = ABI_MAKE_VER(1,0,0);
	
	vabi.check_cable = vid_check_cable;
	vabi.set_mode = vid_set_mode;
	vabi.set_start = vid_set_start;
	vabi.border_color = vid_border_color;
	vabi.clear = vid_clear;
	vabi.empty = vid_empty;
	vabi.waitvbl = vid_waitvbl;
	
	vabi.vram_l = vram_l;
	vabi.vram_s = vram_s;
	
	vabi.bfont_find_char = bfont_find_char;
	vabi.bfont_draw = bfont_draw;
	vabi.bfont_draw_str = bfont_draw_str;
	
	svcmpx_add_handler("video", &vabi);
}

#include <os/svcmpx.h>
#include <os/abi/fs.h>
static abi_fs_t fsabi;
static void fs_abi_init() {
	memset(&fsabi, 0, sizeof(fsabi));

	fsabi.hdr.version = ABI_MAKE_VER(1, 0, 0);
	
	fsabi.open = fs_open;
	fsabi.close = fs_close;
	fsabi.read = fs_read;
	fsabi.write = fs_write;
	fsabi.seek = fs_seek;
	fsabi.tell = fs_tell;
	fsabi.total = fs_total;
	fsabi.readdir = fs_readdir;
	fsabi.ioctl = fs_ioctl;
	fsabi.rename = fs_rename;
	fsabi.unlink = fs_unlink;
	fsabi.chdir = fs_chdir;
	fsabi.getwd = fs_getwd;
	
	fsabi.handler_add = fs_handler_add;
	fsabi.handler_remove = fs_handler_remove;
	
	svcmpx_add_handler("fs", &fsabi);
}

/* Threads */
#include <os/abi/thread.h>
static abi_thread_t thdabi;
static uint32 thd_jiffies() { return jiffies; }
static void thd_abi_init() {
	memset(&thdabi, 0, sizeof(thdabi));

	thdabi.hdr.version = ABI_MAKE_VER(1, 0, 0);

	thdabi.create = thd_create;
	thdabi.destroy = thd_destroy;
	thdabi.exit = thd_exit;
	thdabi.pass = thd_pass;
	thdabi.sleep_jiffies = thd_sleep_jiffies;
	thdabi.sleep = thd_sleep;
	thdabi.jiffies = thd_jiffies;

	svcmpx_add_handler("thread", &thdabi);
}

int services_init() {
	basic_svc_init();
	maple_svc_init();
	spu_svc_init();
	// ta_svc_init();
	vid_svc_init();
	fs_abi_init();
	thd_abi_init();
	
	return 0;
}

void services_shutdown() { }





