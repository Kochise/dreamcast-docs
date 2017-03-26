/* KallistiOS ##version##

   dc/vmufs.h
   Copyright (C)2003 Dan Potter

*/

#ifndef __DC_VMUFS_H
#define __DC_VMUFS_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <dc/maple.h>

#define __packed__ __attribute__((packed))
/** BCD timestamp, used several places below */
typedef struct {
	uint8	cent		__packed__;
	uint8	year		__packed__;
	uint8	month		__packed__;
	uint8	day		__packed__;
	uint8	hour		__packed__;
	uint8	min		__packed__;
	uint8	sec		__packed__;
	uint8	dow		__packed__;	/* Day of week (0 = monday, etc) */
} vmu_timestamp_t;

/** Root block layout */
typedef struct {
	uint8		magic[16]	__packed__;	/*< All should contain 0x55 */
	uint8		use_custom	__packed__;	/*< 0 = standard, 1 = custom */
	uint8		custom_color[4] __packed__;	/*< blue, green, red, alpha */
	uint8		pad1[27]	__packed__;	/*< All zeros */
	vmu_timestamp_t	timestamp	__packed__;	/*< BCD timestamp */
	uint8		pad2[8]		__packed__;	/*< All zeros */
	uint8		unk1[6]		__packed__;	/*< ??? */
	uint16		fat_loc		__packed__;	/*< FAT location */
	uint16		fat_size	__packed__;	/*< FAT size in blocks */
	uint16		dir_loc		__packed__;	/*< Directory location */
	uint16		dir_size	__packed__;	/*< Directory size in blocks */
	uint16		icon_shape	__packed__;	/*< Icon shape for this VMS */
	uint16		blk_cnt		__packed__;	/*< Number of user blocks */
	uint8		unk2[430]	__packed__;	/*< ??? */
} vmu_root_t;

/** Directory entries, 32 bytes each */
typedef struct {
	uint8		filetype	__packed__;	/*< 0x00 = no file; 0x33 = data; 0xcc = a game */
	uint8		copyprotect	__packed__;	/*< 0x00 = copyable; 0xff = copy protected */
	uint16		firstblk	__packed__;	/*< Location of the first block in the file */
	char		filename[12]	__packed__;	/*< Note: there is no null terminator */
	vmu_timestamp_t	timestamp	__packed__;	/*< File time */
	uint16		filesize	__packed__;	/*< Size of the file in blocks */
	uint16		hdroff		__packed__;	/*< Offset of header, in blocks from start of file */
	uint8		dirty		__packed__;	/*< See header notes */
	uint8		pad1[3]		__packed__;	/*< All zeros */
} vmu_dir_t;
#undef __packed__

/* Notes about the "dirty" field on vmu_dir_t :)

   This byte should always be zero when written out to the VMU. What this
   lets us do, though, is conserve on flash writes. If you only want to
   modify one single file (which is the standard case) then re-writing all
   of the dir blocks is a big waste. Instead, you should set the dirty flag
   on the in-mem copy of the directory, and writing it back out will only
   flush the containing block back to the VMU, setting it back to zero
   in the process. Loaded blocks should always have zero here (though we
   enforce that in the code to make sure) so it will be non-dirty by
   default.
 */


/* ****************** Low level functions ******************** */

/** Fill in the date on a vmu_dir_t for writing */
void vmufs_dir_fill_time(vmu_dir_t *d);

/** Reads a selected VMU's root block. Assumes the mutex is held. */
int vmufs_root_read(maple_device_t * dev, vmu_root_t * root_buf);

/** Writes a selected VMU's root block. Assumes the mutex is held. */
int vmufs_root_write(maple_device_t * dev, vmu_root_t * root_buf);

/** Given a VMU's root block, return the amount of space in bytes required
    to hold its directory. */
int vmufs_dir_blocks(vmu_root_t * root_buf);

/** Given a VMU's root block, return the amount of space in bytes required
    to hold its FAT. */
int vmufs_fat_blocks(vmu_root_t * root_buf);

/** Given a selected VMU's root block, read its directory. Assumes the mutex
    is held. There must be at least the number of bytes returned by
    vmufs_dir_blocks() available in the buffer for this to succeed. */
int vmufs_dir_read(maple_device_t * dev, vmu_root_t * root_buf, vmu_dir_t * dir_buf);

/** Given a selected VMU's root block and dir blocks, write the dirty dir blocks
    back to the VMU. Assumes the mutex is held. */
int vmufs_dir_write(maple_device_t * dev, vmu_root_t * root, vmu_dir_t * dir_buf);

/** Given a selected VMU's root block, read its FAT. Assumes the mutex is held.
    There must be at least the number of bytes returned by vmufs_fat_blocks()
    available in the buffer for this to succeed. */
int vmufs_fat_read(maple_device_t * dev, vmu_root_t * root, uint16 * fat_buf);

/** Given a selected VMU's root block and its FAT, write the FAT blocks
    back to the VMU. Assumes the mutex is held. */
int vmufs_fat_write(maple_device_t * dev, vmu_root_t * root, uint16 * fat_buf);

/** Given a previously-read directory, locate a file by filename. The index into
    the directory array will be returned on success, or <0 on failure. 'fn' will
    be checked up to 12 characters. */
int vmufs_dir_find(vmu_root_t * root, vmu_dir_t * dir, const char * fn);

/** Given a previously-read directory, add a new dirent to the dir. Another file
    with the same name should not exist (delete it first if it does). This function
    will _not_ check for dups! Returns 0 on success, or <0 on failure. */
int vmufs_dir_add(vmu_root_t * root, vmu_dir_t * dir, vmu_dir_t * newdirent);

/** Given a pointer to a directory struct and a previously loaded FAT, load
    the indicated file from the VMU. An appropriate amount of space must
    have been allocated previously in the buffer. Assumes the mutex is held.
    Returns 0 on success, <0 on failure. */
int vmufs_file_read(maple_device_t * dev, uint16 * fat, vmu_dir_t * dirent, void * outbuf);

/** Given a pointer to a mostly-filled directory struct and a previously loaded
    directory and FAT, write the indicated file to the VMU. The named file
    should not exist in the directory already. The directory and FAT will _not_
    be sync'd back to the VMU, this must be done manually. Assumes the mutex
    is held. Returns 0 on success, <0 on failure. The 'size' parameter is in
    blocks (512-bytes each). */
int vmufs_file_write(maple_device_t * dev, vmu_root_t * root, uint16 * fat,
	vmu_dir_t * dir, vmu_dir_t * newdirent, void * filebuf, int size);

/** Given a previously-read FAT and directory, delete the named file. No changes are
    made to the VMU itself, just the in-memory structs. */
int vmufs_file_delete(vmu_root_t * root, uint16 * fat, vmu_dir_t * dir, const char *fn);

/** Given a previously-read FAT, return the number of blocks available to write
    out new file data. */
int vmufs_fat_free(vmu_root_t * root, uint16 * fat);

/** Given a previously-read directory, return the number of dirents available
    for new files. */
int vmufs_dir_free(vmu_root_t * root, vmu_dir_t * dir);

/** Lock the mutex. This should be done before you attempt any low-level ops. */
int vmufs_mutex_lock();

/** Unlock the mutex. This should be done once you're done with any low-level ops. */
int vmufs_mutex_unlock();


/* ****************** Higher level functions ******************** */

/** Reads the directory from a VMU. The output buffer will be allocated for
    you using malloc(), and the number of entries will be returned. Returns
    0 on success, or <0 on failure. On failure, 'outbuf' will not contain
    a dangling buffer that needs to be freed (no further action required). */
int vmufs_readdir(maple_device_t * dev, vmu_dir_t ** outbuf, int * outcnt);

/** Reads a file from the VMU. The output buffer will be allocated for you
    using malloc(), and the size of the file will be returned. Returns 0 on
    success, or <0 on failure. On failure, 'outbuf' will not contain
    a dangling buffer that needs to be freed (no further action required). */
int vmufs_read(maple_device_t * dev, const char * fn, void ** outbuf, int * outsize);

/** Same as vmufs_read, but takes a pre-read dirent to speed things up when you
    have already done a lookup. */
int vmufs_read_dirent(maple_device_t * dev, vmu_dir_t * dirent, void ** outbuf, int * outsize);

/* Flags for vmufs_write */
#define VMUFS_OVERWRITE		1	/*< Overwrite existing files */
#define VMUFS_VMUGAME		2	/*< This file is a VMU game */
#define VMUFS_NOCOPY		4	/*< Set the no-copy flag */

/** Writes a file to the VMU. If the named file already exists, then the
    function checks 'flags'. If VMUFS_OVERWRITE is set, then the old
    file is deleted first before the new one is written (this all happens
    atomically). On partial failure, some data blocks may have been written,
    but in general the card should not be damaged. Returns 0 on success,
    or <0 for failure. */
int vmufs_write(maple_device_t * dev, const char * fn, void * inbuf, int insize, int flags);

/** Deletes a file from the VMU. Returns 0 on success, -1 if the file can't be
    found, or -2 for some other error. */
int vmufs_delete(maple_device_t * dev, const char * fn);

/** Returns the number of user blocks free for file writing. You should check this
    number before attempting to write. */
int vmufs_free_blocks(maple_device_t * dev);


/** Initialize vmufs. Must be called before anything else is useful. */
int vmufs_init();

/** Shutdown vmufs. Must be called after everything is finished. */
int vmufs_shutdown();

__END_DECLS

#endif	/* __DC_VMUFS_H */
