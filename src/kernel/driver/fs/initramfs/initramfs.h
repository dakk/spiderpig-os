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
 * \file kernel/driver/fs/initramfs/initramfs.h
 * \author Davide Gessa
 * \date 12/22/2009
 */
#ifndef FS_INITRAMFS_H
#define FS_INITRAMFS_H

#define INITRAMFS_IDENTIFY	0xABCDEF

#include <fs/fs.h>
#include <driver.h>
#include <types.h>

extern driver_t driver_initramfs;


/**
 * Un initramfs e' costituito da una serie di queste strutture
 */
typedef struct
{
	uint32_t identify;	///< Codice identificativo
	char name[32];		///< Nome file
	uint32_t n;			///< Numero del nodo
	uint32_t size;		///< Dimensione dei dati
	uint32_t data;		///< Offset dei dati
} initramfs_node_t;

uint32_t initramfs_mount(char *, uint32_t, inode_t *);
uint32_t initramfs_umount(inode_t *);	
uint32_t initramfs_readdir(inode_t *, uint32_t, struct dirent *);
uint32_t initramfs_open(inode_t *, char *);
uint32_t initramfs_read(inode_t *, char *, uint32_t, uint64_t);
uint32_t initramfs_get_node(inode_t *, uint32_t, inode_t **);

#endif
