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
 * \file kernel/fs/pfs/pfs.c
 * \author Davide Gessa
 * \date 11/22/2009
 */
#include "pfs.h"
#include <types.h>
#include <driver.h>

driver_t driver_pfs = 
{
	.name = "pfs\0",
	.desc = "pig file system\0",
	.author = "Davide Gessa\0",
	.type = DRV_TYPE_FS,
						
	.fs.ifdev = 1,
	.fs.mount = pfs_mount,
	.fs.umount = pfs_umount
};




/**
 * Umonta il tmpfs
 */
uint32_t pfs_umount(inode_t *root)
{
	//root->childs = NULL;

	return MOUNT_STATE_OK;
}



/**
 * Monta il tmpfs
 */
uint32_t pfs_mount(char *dev, uint32_t flags, inode_t *root)
{
	//root->childs = NULL;

	return MOUNT_STATE_OK;
}




/**
 * Legge un inode, dato il numero
 */
uint32_t pfs_read_node(int n, pfs_nodeblock_t *node)
{
	
	
}
