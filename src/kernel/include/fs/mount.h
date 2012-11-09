/*
 * SpiderpigOS
 * Copyright (C) 2009 - 2010 Davide Gessa
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * \file fs/mount.h
 * \author Davide Gessa
 * \date 12-22-09
 */
#ifndef MOUNT_H
#define MOUNT_H

#include <fs/fs.h>
//#include <driver.h>

#define MP_MAX			16
#define MOUNT_STATE_OK	1
#define MOUNT_STATE_MP	2
#define MOUNT_STATE_MD	3
#define MOUNT_STATE_MF	4
#define MOUNT_STATE_FE	5
#define MOUNT_STATE_PM	6
#define MOUNT_STATE_DM	7


/**
 * Struttura per memorizzare i mount point
 */
typedef struct mount_point_p
{
	char path[MOUNT_POINT_NAME_SIZE];		///< Path del mountpoint
	char dev[MOUNT_POINT_NAME_SIZE];		///< Path del device file
	char fs[MOUNT_POINT_NAME_SIZE];			///< Filesystem
	
	void *fs_struct;						///< Filesystem
	
	inode_t *root;							///< Root node
	inode_t *childs;						///< Figli
	
	uint8_t used;							///< Usato?
} mount_point_t;


mount_point_t fs_mountpoints[MP_MAX];		///< Array mount points

mount_point_t *fs_get_mount_point_struct(char *);
uint32_t fs_mount(char *, char *, char *, uint32_t);
uint32_t fs_umount(char *);
uint32_t fs_get_mount_point(char *, char *);
uint32_t fs_get_mount_point_fs(char *, char *);
uint32_t fs_iget_mount_point(uint32_t, mount_point_t **);

#endif
