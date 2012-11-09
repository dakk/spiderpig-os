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
 * \file kernel/driver/fs/tmpfs/tmpfs.h
 * \author Davide Gessa
 * \date 12/22/2009
 */
#ifndef FS_TMPFS_H
#define FS_TMPFS_H

#include <fs/fs.h>
#include <driver.h>

extern driver_t driver_tmpfs;

#define TMPFS_DATA_SIZE	1024				///< Dimensione di un blocco


/**
 * Nodo dati
 */
typedef struct tmpfs_data_node_p
{
	char data[TMPFS_DATA_SIZE];				///< Dati
	
	struct tmpfs_data_node_p *next;			///< Prossimo blocco dati
	struct tmpfs_data_node_p *prev;			///< Precedente blocco dati
} tmpfs_data_node_t;



/**
 * Nodo file
 */
typedef struct tmpfs_node_p
{
	uint32_t size;							///< Dimensione totale
	tmpfs_data_node_t *data;				///< Puntatore al primo blocco
} tmpfs_node_t;


uint32_t tmpfs_mount(char *, uint32_t, inode_t *);
uint32_t tmpfs_umount(inode_t *);	
uint32_t tmpfs_mkdir(inode_t *, char *);
uint32_t tmpfs_delete_node(inode_t *, char *);
uint32_t tmpfs_readdir(inode_t *, uint32_t, struct dirent *);
uint32_t tmpfs_open(inode_t *, char *);
uint32_t tmpfs_read(inode_t *, char *, uint32_t, uint64_t);
uint32_t tmpfs_write(inode_t *, char *, uint32_t, uint64_t);
uint32_t tmpfs_get_node(inode_t *, uint32_t, inode_t **);
uint32_t tmpfs_close(inode_t *);
uint32_t tmpfs_link(inode_t *, char *, inode_t *, char *);
uint32_t tmpfs_unlink(inode_t *, char *);

#endif
