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
 * \file fs/fs.h
 * \author Davide Gessa
 * \date 11-18-09
 */
#ifndef FS_FS_H
#define FS_FS_H

#include <types.h>

#define MOUNT_POINT_NAME_SIZE	512		///< Dimensione massima path del mount point
#define NODE_NAME_SIZE	255				///< Dimensione massima nome inode

#define NODE_TYPE_FILE	1				///< Tipo nodo: file
#define NODE_TYPE_DIR	2				///< Tipo nodo: dir
#define NODE_TYPE_LINK	3				///< Tipo nodo: link



#define FS_ER_NT_FOUND	1				///< Non e' stato trovato un file
#define FS_ER_NT_LINK	2				///< Non e' un link
#define FS_ER_NT_PERM	3				///< Operazione non permessa per questo fs


#define NODE_MAX_NUMBER	1024

/**
 * Struttura di un inode
 */
typedef struct inode_p
{
	char name[NODE_NAME_SIZE];		///< Nome del nodo
	uint32_t inode_n;				///< Numero del nodo
	uint8_t type;					///< Tipo di nodo	
	
	uint8_t ow:1;					///< Indica se il nodo puo' essere cancellato dall'albero
	
	void *fs_node;					///< Nodo fs
	void *fs_driver;				///< Filesystem driver

	struct inode_p *link;			///< Se il nodo e' un link
	struct inode_p *next;			///< Prossimo nodo
	struct inode_p *prev;			///< Precedente nodo
	struct inode_p *parent;			///< Nodo padre
	struct inode_p *childs;			///< Nodo figlio
} inode_t;


/**
 * Struttura stat
 */
struct stat
{
	uint32_t st_dev;				///< Device id 
	uint32_t st_ino;				///< Numero di inode
	uid_t st_uid;					///< User id
	gid_t st_gid;					///< Group id
		
	uint64_t st_blksize;			///< Blocksize
	uint64_t st_blocks;				///< Numero di blocchi allocati

};

/**
 * Struttura di un elemento di una directory, posix compatible
 */
struct dirent
{
	char name[NODE_NAME_SIZE];		///< Nome
	uint32_t inode;					///< Numero nodo
};


#include <fs/mount.h>
#include <driver.h>
#include <fs/file.h>
#include <fs/dir.h>


/**
 * Struttura di splittaggio dei path
 */
typedef struct
{
	uint32_t i;						///< Numero di parti
	char list[32][512];				///< Lista parti
} fs_splitted_path;


inode_t *fs_root;					///< Radice del filesystem
uint32_t node_n;					///< Numero nodi ow
uint32_t cur_inode_n;				///< Numero corrente inode

void fs_init();
uint32_t fs_check_name(char *);
uint32_t fs_get_node(char *, inode_t **);
uint32_t fs_tree_cleanup(inode_t *, int);
uint32_t fs_path_split(char *, char **);
void fs_show_tree(inode_t *, uint32_t);
inode_t *fs_create_node(char *, inode_t *, uint8_t, uint8_t);
uint32_t fs_split_path(char *, fs_splitted_path *);
uint32_t fs_get_full_path(char *, char *, char *);
uint32_t fs_rm(char *);

#endif
