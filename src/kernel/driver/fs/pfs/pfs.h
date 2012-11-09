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
 * \file kernel/fs/pfs/pfs.h
 * \author Davide Gessa
 * \date 11/22/2009
 * \note PFS e' pigfs, il filesystem creato appositamente per spiderpig
 * \note Caratteristiche:
 *        - 64 Bit di indirizzamento
 *        - Numero max di file: 2^64
 *        - Dimensione max file: 53
 *        - Dimensione max partizione: 
 */
#ifndef FS_PFS_H
#define FS_PFS_H

#include <types.h>
#include <fs/fs.h>
#include <driver.h>


extern driver_t driver_pfs;

/// Dimensione del blocco
#define PFS_BLOCKSIZE_512
//#define PFS_BLOCKSIZE_1024

/// Dimensione nomefile
#ifdef PFS_BLOCKSIZE_512
	#define PFS_FILE_NAME_SIZE	128
#endif
#ifdef PFS_BLOCKSIZE_1024
	#define PFS_FILE_NAME_SIZE	256
#endif


#define PFS_TYPE_DIR	0x01
#define PFS_TYPE_FILE	0x02
#define PFS_TYPE_LINK	0x03

/**
 * Il primo blocco del filesystem, sara' grande 512 byte sempre
 */
typedef struct
{
	/// Numero di identificazione, sara' 0xFEDCCDEF
	uint32_t magic_number;
	
	/// Mounts dall'ultimo check
	uint32_t mount_time; 			
	
	/// Mounts per l'autocheck
	uint32_t autocheck_time; 		
	
	/// Data ultimo check
	uint32_t check_date;			
	
	/// Dimensione della partizione kb
	uint64_t size;
	
	/// Posizione dei dati
	uint64_t data_pos;
	
	/// Dimensione dei dati
	uint64_t data_size;
					
	/// Posizione dei nodeblock
	uint64_t nodes_pos;
	
	/// Numero dei nodeblock
	uint64_t nodes_n;
	
	/// Checksum del blocco
	uint64_t checksum;					
} pfs_superblock_t;


/**
 * Sezione dove verranno memorizzate le info dei file e directory.
 */
typedef struct
{
	/// Check sum (ultimi bit)
	uint16_t checksum;			
	
	/// Nome del file
	char name[PFS_FILE_NAME_SIZE];
	
	/// Tipo
	uint8_t type;
	
	/// Partenza file (Primo blocco)
	uint64_t offset;
	
	/// Numero del nodo
	uint64_t number;
	
	/// Padre (0 se root)
	uint64_t parent_n;
	
	/// Dimensione file in kb
	uint64_t size;
} pfs_nodeblock_t;
	
/**
 * Blocco dati
 */
typedef struct pfs_datablock_p
{
	/// Check sum (ultimi bit)
	uint16_t checksum;
	
	/// Dati
	char data[502];		
	
	/// Prossimo blocco (NULL se ultimo)
	struct pfs_datablock_p *next;
	
	/// Precedente blocco (NULL se primo)
	struct pfs_datablock_p *prev;	
} pfs_datablock_t;


uint32_t pfs_mount(char *, uint32_t, inode_t *);
uint32_t pfs_umount(inode_t *);	
uint32_t pfs_readdir(inode_t *, uint32_t, struct dirent *);
uint32_t pfs_open(inode_t *, char *);
uint32_t pfs_read(inode_t *, char *, uint32_t, uint64_t);
uint32_t pfs_get_node(inode_t *, uint32_t, inode_t **);
uint32_t pfs_mkdir(inode_t *, char *);
uint32_t pfs_delete_node(inode_t *, char *);
uint32_t pfs_write(inode_t *, char *, uint32_t, uint64_t);
uint32_t pfs_close(inode_t *);
uint32_t pfs_link(inode_t *, char *, inode_t *, char *);
uint32_t pfs_unlink(inode_t *, char *);
	
#endif
