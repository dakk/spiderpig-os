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
 * \file fs/fsop.c
 * \author Davide Gessa
 * \date 23-01-10
 */
#include <fs/fs.h>
#include <fs/file.h>
#include <fs/dir.h>
#include <driver.h>
#include <debug.h>


/**
 * Restituisce la struttura driver_t di un filesystem montato dato il nodo
 */
driver_t *fs_get_fs_driver(char *path)
{
	char mp[128];
	
	fs_get_mount_point(path, mp);
	fs_get_mount_point_fs(mp, mp);

	return (driver_t *) driver_get(mp);	
}



/**
 * Crea una directory
 */
uint32_t fs_makedir(char *path_)
{	
	DEBUGP("fs_makedir()\n");
	
	fs_splitted_path sp;
	inode_t *node = NULL;
	char path[1024];
	char name[255];
	uint32_t i;
	
	fs_split_path(path_, &sp);
	strcpy(path, "/");
	for(i = 0; i < (sp.i - 1); i++)
	{
		strcat(path, sp.list[i]);
		strcat(path, "/");
	}
	
	strcpy(name, sp.list[sp.i - 1]);
	
	//printf("%s\n", name); //, path);
	
	fs_get_node(path, &node);
	
	if(node == NULL) 
		return 0;
	
	driver_t *drv = fs_get_fs_driver(path);
	driver_fs_t *filesystem_struct;
	
	if(drv != NULL)
		filesystem_struct = &drv->fs;
	else
		return 0;
		
	if(filesystem_struct->mkdir != NULL)
		return filesystem_struct->mkdir(node, name);

	return 0;	
}




/**
 * Elimina un nodo
 */
uint32_t fs_rm(char *path_)
{	
	DEBUGP("fs_rm()\n");
	
	fs_splitted_path sp;
	inode_t *node = NULL;
	char path[1024];
	char name[255];
	uint32_t i;
	
	fs_split_path(path_, &sp);
	strcpy(path, "/");
	for(i = 0; i < (sp.i - 1); i++)
	{
		strcat(path, sp.list[i]);
		strcat(path, "/");
	}
	
	strcpy(name, sp.list[sp.i - 1]);
	
	//printf("%s\n", name); //, path);
	
	fs_get_node(path, &node);
	
	if(node == NULL) 
		return 0;
	
	driver_t *drv = fs_get_fs_driver(path);
	driver_fs_t *filesystem_struct;
	
	if(drv != NULL)
		filesystem_struct = &drv->fs;
	else
		return 0;
	
	if(filesystem_struct->delete_node != NULL)
		return filesystem_struct->delete_node(node, name);

	return 0;	
}




/**
 * Apre un file
 * 
 * \param path path del file
 * \param flags modalita' di apertura
 * \return file descriptor
 */
file_t *fs_open(char *path_, char *flags)
{
	DEBUGP("fs_open()\n");
	
	file_t  *f = NULL;
	fs_splitted_path sp;
	char path[1024];
	char name[255];
	uint32_t i;
	struct dirent dir;
	
	fs_split_path(path_, &sp);
	strcpy(path, "/");
	for(i = 0; i < (sp.i - 1); i++)
	{
		strcat(path, sp.list[i]);
		strcat(path, "/");
	}
	
	strcpy(name, sp.list[sp.i - 1]);


	
	// Controlliamo se esiste il file
	inode_t *node = NULL;
	
	// Otteniamo l'inodenum
	fs_split_path(path, &sp);
	
	
	driver_t *drv = fs_get_fs_driver(path);
	driver_fs_t *filesystem_struct;
	
	if(drv == NULL)
		return (file_t *) NULL;

	filesystem_struct = &drv->fs;

	i = 0;
		
	while(fs_readdir2(path, i, &dir) != 0)
	{
		//printf("%s %d\n", dir.name, dir.inode);
		if(strcmp(dir.name, name) == 0)
			break;
		else
			dir.inode = 0;
		i++;
	}
	
	//printf("\n\n%s\n\n",dir.name);
	
	// Se il nodo non esiste e siamo in scrittura lo creo
	//  ps da sostituire con funzione del filesystem
	if((dir.inode == 0) && (flags[0] == 'w'))
	{
		fs_get_node(path, &node);
		if(node != NULL)
			fs_create_node(name, node, NODE_TYPE_FILE, 0); 
		else
			return 0;
	}
	else if(dir.inode == 0)
	{
		return 0;
	}
	else if(dir.inode != 0)
	{
		inode_t *node_tmp;
		fs_get_node(path, &node_tmp);
		if(filesystem_struct->get_node != NULL && node_tmp != NULL)
			filesystem_struct->get_node(node_tmp, dir.inode, &node);
	
		if(node == NULL || node->type != NODE_TYPE_FILE)
			return 0;
	}
	
	if(node == NULL)
			return 0;
	//else
	//	printf("nodo trovato\n");

		
	f->node->fs_driver = filesystem_struct;
	
	// Controlliamo se e' possibile aprirlo con quei flags
	
	if(filesystem_struct->open != NULL)
	{
		if(!filesystem_struct->open(node, flags))
			return (file_t *) NULL;
	}
	
	//printf("aperto\n\n");
	// Allocchiamo e mettiamolo in lista	
	f = (file_t *) malloc(sizeof(file_t));
	f->next = file_list;
	f->drv = (void *) drv;
	f->node = node;
	file_list = f;
	
	// Impostiamo i dati della struttura
	f->id = files_open_n++;
	f->seek_p = 0;
		
	return f;
}





/**
 * Chiude un file
 * 
 * \param f file descriptor
 */
uint32_t fs_close(file_t *f)
{
	DEBUGP("fs_close()\n");
	
	free(f);
	
	return 0;
}



/**
 * Legge da file
 * 
 * \param f file descriptor
 * \param buf buffer dove mettere i dati letti
 * \param size quantita' da leggere
 * \return quantita' letta effettivamente
 */
uint32_t fs_read(file_t *f, char *buf, uint32_t size)
{	
	DEBUGP("fs_read()\n");
	
	driver_fs_t *filesystem_struct = NULL;
	unsigned av = 0;
	
	if(f->drv != NULL)
		filesystem_struct = &((driver_t *) (f->drv))->fs;
	else
		return 0;
		
	//printf("%s\n",(f->node)->name);
	if(filesystem_struct->read != NULL)
		av = filesystem_struct->read(f->node, buf, size, f->seek_p);
	
	f->seek_p = f->seek_p + av;
	
	return av;
}




/**
 * Scrive su file
 * 
 * \param f file descriptor
 * \param buf buffer dove prendere i dati
 * \param size quantita' da scrivere
 * \return quantita' scritta effettivamente
 */
uint32_t fs_write(file_t *f, char *buf, uint32_t size)
{
	DEBUGP("fs_write()\n");
	
	driver_fs_t *filesystem_struct = NULL;
	unsigned av = 0;
	
	if(f->drv != NULL)
		filesystem_struct = &((driver_t *) (f->drv))->fs;
	else
		return 0;
		
	//printf("%s\n",(f->node)->name);
	if(filesystem_struct->write != NULL)
		av = filesystem_struct->write(f->node, buf, size, f->seek_p);
	
	f->seek_p = f->seek_p + av;
	
	return av;
}





/**
 * Modifica il puntatore nel file
 * 
 * \param f file descriptor
 * \param mod modalita' di seek
 * \param offset offset di posizione
 */
uint32_t fs_seek(file_t *f, uint8_t mod, uint64_t offset)
{
	DEBUGP("fs_seek()\n");
	
	if(mod == FS_SEEK_CUR)
		f->seek_p = f->seek_p + offset;
	else if(mod == FS_SEEK_SET)
		f->seek_p = offset;
	else if(mod == FS_SEEK_END)
		f->seek_p = f->size - offset;
	
	return 0;
}




/**
 * Apre una directory
 */
dir_t *fs_opendir(char *path)
{
	DEBUGP("fs_opendir()\n");

	/*file_t *f = fs_open(path, "r");

	if(f == NULL)
		return (dir_t *) 0;	
	*/


	file_t  *f = NULL;
	fs_splitted_path sp;
	char name[255];
	uint32_t i;
	struct dirent dir;
	
	fs_split_path(path, &sp);
	strcpy(name, sp.list[sp.i - 1]);


	driver_t *drv = fs_get_fs_driver(path);
	if(drv == NULL) 
		return (dir_t *) 0;

	
	dir_t *d = (dir_t *) malloc(sizeof(dir_t));
	//((d->f)->node)->fs_driver =(void *) &drv->fs;
	d->d_name = name;//f->node->name;
	if(d->d_name[0] == '\0')
		strcpy(d->d_name, "/");
	
	strcpy(d->path, path);
		
	//printf("opened directory %s\n", d->d_name);
	d->f = f;
	d->cur_i = 0;
	
	return d;
}



/**
 * Legge l'elemento num della dir path
 */
uint32_t fs_readdir(dir_t *dr, struct dirent *dir)
{	
	DEBUGP("fs_readdir()\n");
	
	if(dr == NULL)
		return 0;
		
		
	dr->cur_i++;
	return fs_readdir2(dr->path, (dr->cur_i - 1), dir);
	/*inode_t *node = dr->f->node;
	
	if(node == NULL) 
		return 0;
		
	// Resettiamo il dirent
	strcpy(dir->name, "\0");
	dir->inode = 0;
	
	driver_fs_t *filesystem_struct = (driver_fs_t *) ((dr->f)->node)->fs_driver;
		
	dr->cur_i++;
	
	if(filesystem_struct->readdir != NULL)
		return filesystem_struct->readdir(node, (dr->cur_i - 1), dir);*/
}



/**
 * Chiude una dir aperta
 */
uint32_t fs_closedir(dir_t *dr)
{
	DEBUGP("fs_closedir()\n");
	
	//free(dr->f);
	free(dr);
	return 0;	
}



/**
 * Riavvolge il puntatore della directory
 */
uint32_t fs_rewinddir(dir_t *dr)
{
	DEBUGP("fs_rewinddir()\n");
	
	dr->cur_i = 0;
	return 0;
}




/**
 * Legge l'elemento num della dir path
 * 
 * \param path il path della directory madre
 * \param inode_num inode della dir
 * \param dir struttura dirent per le info del file
 * \return stato dell'operazione
 */
uint32_t fs_readdir2(char *path, uint32_t in, struct dirent *dir)
{	
	inode_t *node = NULL;
	
	fs_get_node(path, &node);
	
	if(node == NULL) 
		return 0;
	
	if(node->type == NODE_TYPE_LINK)
		node = node->link;
		
	if(node == NULL) 
		return 0;
		
	// Resettiamo il dirent
	strcpy(dir->name, "\0");
	dir->inode = 0;
	
	
	driver_t *drv = fs_get_fs_driver(path);
	driver_fs_t *filesystem_struct;
	
	if(drv != NULL)
		filesystem_struct = &drv->fs;
	else
		return 0;
		
	if(filesystem_struct->readdir != NULL)
		return filesystem_struct->readdir(node, in, dir);
		
	return 0;
}





/**
 * Create link
 */
uint32_t fs_link(char *file_name, char *link_name)
{
	DEBUGP("fs_link()\n");
	
	fs_splitted_path sp;
	char path[1024];
	char name[255];
	uint32_t i;
	struct dirent dir;
	
	fs_split_path(file_name, &sp);
	strcpy(path, "/");
	for(i = 0; i < (sp.i - 1); i++)
	{
		strcat(path, sp.list[i]);
		strcat(path, "/");
	}
	
	strcpy(name, sp.list[sp.i - 1]);

	
	// Controlliamo se esiste il file
	inode_t *node = NULL;
	
	// Otteniamo l'inodenum
	fs_split_path(path, &sp);
	
	
	driver_t *drv = fs_get_fs_driver(path);
	driver_fs_t *filesystem_struct;
	
	if(drv == NULL)
		return FS_ER_NT_FOUND;

	filesystem_struct = &drv->fs;

	i = 0;
		
	while(fs_readdir2(path, i, &dir) != 0)
	{
		if(strcmp(dir.name, name) == 0)
			break;
		else
			dir.inode = 0;
		i++;
	}
	
	inode_t *node_tmp;
	if(dir.inode == 0)
	{
		return FS_ER_NT_FOUND;
	}
	else if(dir.inode != 0)
	{
		fs_get_node(path, &node_tmp);
		if(filesystem_struct->get_node != NULL && node_tmp != NULL)
			filesystem_struct->get_node(node_tmp, dir.inode, &node);
	}
	
	if(node == NULL)
		return FS_ER_NT_FOUND;
	//else
	//	printf("nodo trovato\n");
	
		
	if(filesystem_struct->link != NULL)
	{
		fs_splitted_path sp2;
		char path2[1024];
		char name2[255];
	
		fs_split_path(link_name, &sp2);
		strcpy(path2, "/");
		for(i = 0; i < (sp2.i - 1); i++)
		{
			strcat(path2, sp2.list[i]);
			strcat(path2, "/");
		}
		strcpy(name2, sp2.list[sp2.i - 1]);
		inode_t *dest_root;
		fs_get_node(path2, &dest_root);
		
		//printf("%s %s\n", path2, name2); 
		if(dest_root == NULL)
			return FS_ER_NT_FOUND;
		
		if(!filesystem_struct->link(node_tmp, name, dest_root, name2))
			return 0;
	}
	else
		return FS_ER_NT_PERM;
}


/**
 * Remove link
 */
uint32_t fs_unlink(char *path_)
{
	DEBUGP("fs_unlink()\n");
	
	fs_splitted_path sp;
	inode_t *node = NULL;
	char path[1024];
	char name[255];
	uint32_t i;
	
	fs_split_path(path_, &sp);
	strcpy(path, "/");
	for(i = 0; i < (sp.i - 1); i++)
	{
		strcat(path, sp.list[i]);
		strcat(path, "/");
	}
	
	strcpy(name, sp.list[sp.i - 1]);
	
	//printf("%s\n", name); //, path);
	
	fs_get_node(path, &node);
	
	if(node == NULL) 
		return 0;
	
	driver_t *drv = fs_get_fs_driver(path);
	driver_fs_t *filesystem_struct;
	
	if(drv != NULL)
		filesystem_struct = &drv->fs;
	else
		return 0;
	
	if(filesystem_struct->unlink != NULL)
		return filesystem_struct->unlink(node, name);
	else
	{
		//printf("filesystem di %s non permette il link\n", link_name);
		return FS_ER_NT_PERM;
	}	
}



