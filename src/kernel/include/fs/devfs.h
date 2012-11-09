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
 * \file kernel/fs/devfs/devfs.h
 * \author Davide Gessa
 * \date 12/08/2009
 */
#ifndef FS_DEVFS_H
#define FS_DEVFS_H

#include <types.h>
#include <fs/fs.h>
#include <driver.h>

extern driver_t driver_devfs;

inode_t *devfs_root;
inode_t *devfs_childs;

typedef struct
{
	driver_t *driver;
	device_t *device;
} devfs_node_t;

uint32_t devfs_reg_device(device_t *, driver_t *, char *);
uint32_t devfs_unreg_device(char *);
uint32_t devfs_mount(char *, uint32_t, inode_t *);
uint32_t devfs_umount(inode_t *);
uint32_t devfs_find_freen(char *, char *);
uint32_t devfs_readdir(inode_t *, uint32_t, struct dirent *);
uint32_t devfs_open(inode_t *, char *);
uint32_t devfs_read(inode_t *, char *, uint32_t, uint64_t);
uint32_t devfs_write(inode_t *, char *, uint32_t, uint64_t);
uint32_t devfs_get_node(inode_t *, uint32_t, inode_t **);
uint32_t devfs_close(inode_t *);

#endif
