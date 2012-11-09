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
 * \file kernel/driver/fs/initramfs/initramfs.c
 * \author Davide Gessa
 * \date 12/22/2009
 */
#include "initramfs.h"
#include <driver.h>
#include <fs/fs.h>
#include <main.h>


driver_t driver_initramfs =
{
	.name = "initramfs\0",
	.author = "Davide Gessa\0",
	.probe = NULL,
	
	.type = DRV_TYPE_FS,
	.fs.ifdev = 0,
	
	// Fs
	.fs.mount = initramfs_mount,
	.fs.umount = initramfs_umount,
	
	.fs.readdir = initramfs_readdir,
	.fs.mkdir = NULL,
	
	.fs.open = initramfs_open,
	.fs.close = NULL,
	.fs.read = initramfs_read,
	.fs.write = NULL,
	
	.fs.get_node = initramfs_get_node,
	.fs.delete_node = NULL,
	.fs.create_node = NULL,
	
	.fs.write_stat = NULL,
	.fs.read_stat = NULL,
	
	.fs.link = NULL,
	.fs.unlink = NULL
};


/**
 * Legge il contenuto della dir principale
 */
uint32_t initramfs_readdir(inode_t *root, uint32_t n, struct dirent *d)
{
	uint32_t i;
	initramfs_node_t *node = (initramfs_node_t *) (mod_addr + (sizeof(initramfs_node_t) * n));
	
	strcpy(d->name, "\0");
	//printf("aa%s %d\n\n",node->name, n);
	
	if(node->identify == 0xABCDEF)
	{
		strcpy(d->name, node->name);
		d->inode = node->n;
		
		return 1;
	}
	else		
		return 0;
}


/**
 * Umonta il initramfs
 */
uint32_t initramfs_umount(inode_t *root)
{
	//root->childs = NULL;

	return MOUNT_STATE_OK;
}



/**
 * Monta il initramfs
 */
uint32_t initramfs_mount(char *dev, uint32_t flags, inode_t *root)
{
	return MOUNT_STATE_OK;
}



/**
 * Preleva un nodo
 */
uint32_t initramfs_get_node(inode_t *root, uint32_t node_n, inode_t **node)
{
	int i = 0;
	
	initramfs_node_t *nod;
	
	while(1)
	{
		nod = (initramfs_node_t *) (mod_addr + (sizeof(initramfs_node_t) * i));
		if(nod->identify == 0xABCDEF)
		{
			if(nod->n == node_n)
			{
				*node = fs_create_node(nod->name, root, NODE_TYPE_FILE, 1);
				(*node)->inode_n = nod->n;
				(*node)->fs_node = nod;
				return 1;
			}
		}
		i++;
	}
	return 0;
}


/**
 * Apre un file
 */
uint32_t initramfs_open(inode_t *node, char *flags)
{
	int i = 0;
	struct dirent dir;
	
	while(initramfs_readdir(0, i, &dir) != 0)
	{
		//printf("%d %d\n", node->inode_n, dir.inode);
		if(dir.inode == node->inode_n)
		{
			node->fs_node = (void *) (initramfs_node_t *) (mod_addr + (sizeof(initramfs_node_t) * i));
			
		
			//printf("f_open = %s\n\n", ((initramfs_node_t *) (node->fs_node))->name);
			//node->fs_node = (void *) (mod_addr + (sizeof(initramfs_node_t) * i));
			return 1;
		}
		i++;
	}
	
	// Analizziamo se i flags inidicano sola lettura
	
	// Altrimenti non e' possibile aprirlo
	//return 0;
	
	
	return 0;
}



/**
 * Legge da file
 */
uint32_t initramfs_read(inode_t *node, char *buf, uint32_t size, uint64_t offset)
{
	int i;
		
		
	char *data = (char *) (mod_addr + (((initramfs_node_t *) (node->fs_node))->data));
	data = data + (uint32_t) offset;
	
	//printf("%s\n",((initramfs_node_t *) (node->fs_node))->name);
	
	for(i = 0; i < size; i++)
	{
		if((offset + i) >= (((initramfs_node_t *) (node->fs_node))->size))
		{
			buf[i] = '\0';
			return i;
		}
		buf[i] = *data;
			
		data++;
	}
	
	buf[i] = '\0';
	return size;
}
