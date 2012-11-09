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
 * \note File System Manager
 * \file fs/fs.c
 * \author Davide Gessa
 * \date 11-18-09
 */
#include <driver.h>
#include <fs/devfs.h>
#include <fs/fs.h>
#include <fs/file.h>
#include <fs/dir.h>
#include <fs/mount.h>
#include <klibc/string.h>
#include <klibc/malloc.h>


/**
 * Inizializza il file system manager
 */
void fs_init()
{
	int i;
	
	// Azzera i mp
	for(i = 0; i < MP_MAX; i++)
		fs_mountpoints[i].used = 0;
		
	// Numero file aperti
	files_open_n = 1;

	// File aperti
	file_list = 0;
	
	cur_inode_n = 0;
	
	// Aggiungiamo i fs di default
	driver_add(&driver_devfs);
			
	// Numero nodi cancellabili inseriti
	node_n = 0;

	// Nodo root
	#ifdef VERBOSE
		printf("mounting root filesystem");
	#endif
	
	fs_root = fs_create_node("", NULL, NODE_TYPE_DIR, 0);
	fs_mount("\0", "/", "tmpfs\0", 0);
	
	// Crea la cartella per il devfs e fa il mount
	devfs_childs = NULL;
	devfs_root = fs_root;
	fs_makedir("/dev");
	fs_get_node("/dev", &devfs_root);
	fs_mount("\0", "/dev", "devfs", 0);

}



/**
 * 
 */
uint32_t fs_get_abs_path(char *path, char *cur, char *dest)
{
	
	
	
}

/**
 * Controlla se il nome del nodo e' adatto
 * 
 * \param name nome del nodo
 * \return stato della verifica
 */
uint32_t fs_check_name(char *name)
{
	char *c = name;
	
	while(*c != '\0')
	{
		if(	!(*c >= 97 && *c <= 122) && 
			!(*c >= 65 && *c <= 90) && 
			!(*c >= 48 && *c <= 57) && 
			!(*c == 46) &&
			!(*c == 95) && 
			!(*c == 45) )
			return 0;		
		
		c++;
	}
	return 1;
}


/**
 * Crea un nodo e restituisce il puntatore
 * 
 * \param name nome del nodo
 * \param parent padre del nodo
 * \param type tipo di nodo
 * \param ow se il nodo puo' essere cancellato
 * \return nodo allocato
 */
inode_t *fs_create_node(char *name, inode_t *parent, uint8_t type, uint8_t ow)
{
	if(!fs_check_name(name)) 
		return (inode_t *) NULL;
	
	inode_t *i = (inode_t *) malloc(sizeof(inode_t));
	strcpy(i->name, name);
	cur_inode_n++;
	i->inode_n = cur_inode_n;
	i->type = type;
	i->childs = NULL;
	i->fs_node = NULL;
		
	i->parent = parent;
	i->next = NULL;
	i->prev = NULL;
	
	if(parent != NULL)
	{
		i->next = parent->childs;
		i->next->prev = i;
		parent->childs = i;
	}
	
	if(ow == 1) node_n++;
	i->ow = ow;
	
	return i;
}




/**
 * Visualizza tutto l'albero
 */
void fs_show_tree(inode_t *start, uint32_t level)
{
	inode_t *childs = start->childs;

	int x;
	for(x = 0; x < level; x++) printf(" ");
	printf("/%s\n",start->name);

	if(start->type == NODE_TYPE_DIR)
	{
		while(childs != NULL)
		{
			fs_show_tree(childs, level+1);
			childs = childs->next;
		}
	}
}






/**
 * Dato un path, crea l'albero virtuale, restituendo il nodo
 *
 * \param path path del "file"
 * \param node puntatore a nodo, per l'output
 * \return numero del nodo
 */
uint32_t fs_get_node(char *path, inode_t **node)
{
	inode_t *nod;
	*node = NULL;
	uint32_t j;
	
	
	// Controlla se ci sono troppi nodi e pulisce
	if(node_n > NODE_MAX_NUMBER)
		fs_tree_cleanup(fs_root, 1);


	// Splitta il path
	fs_splitted_path sp;
	
	fs_split_path(path, &sp);
	
	
	// Se e' il nodo root
	if((strcmp(path, "/\0") == 0))
	{
		*node = fs_root;
		return 1;
	}
	
	
	// Scansiona fino a trovare il nodo (con readdir)
	nod = fs_root->childs;
	j = 0;
	
	while(nod != NULL)
	{
		//printf("%s\n",list[j]);
		if(strcmp(sp.list[j], nod->name) == 0)
		{
			if(strcmp(sp.list[j+1], "\0") == 0)
			{
				//printf("%s\n", list[j]);
				*node = nod;
				return 1;
			}
			//printf("%s\n", list[j]);
			*node = nod;
			nod = nod->childs;
			j++;
			continue;
		}
		nod = nod->next;
	}
	
	// Nodo non trovato 
	return 0;
}






/**
 * Ripulisce l'albero dai nodi virtuali
 * 
 * \param start nodo di partenza
 * \return nodi eliminati
 * 
 * \note il numero restituito e sballato
 */
uint32_t fs_tree_cleanup(inode_t *start, int attr)
{
	uint32_t removed = 0;
	
	if(start->next != NULL)
		removed = removed + fs_tree_cleanup(start->next, attr);	
		
	if(start->childs != NULL)
		removed = removed + fs_tree_cleanup(start->childs, attr);
	
	if(start->ow == 1 || !(attr))
		if(start->next == NULL)
		{
			start->parent->childs = start->next;
			free(start);
			removed++;
		}

	return removed;
}





/**
 * Splitta un path
 */
uint32_t fs_split_path(char *path, fs_splitted_path *split)
{
	
	// Splitta il path
	int i = 0;
	int j = 0;
	int x = 0;
	
	for(i = 0; i < 31; i++) split->list[i][0] = '\0';
	i = 0;
	
	if(path[0] == '/' && path[1] == '\0')
	{
		split->i = 1;
		strcpy(split->list[0], "/\0");
		return 1;
	}
	
	while(1)
	{
		if(path[i] == '/' || path[i] == '\0')
		{
			split->list[j][x] = '\0';
			
			if(i != 0 && x != 0)
			{
				j++;
			}
			x = 0;
			if(path[i] == '\0' || (path[i] == '/' && path[i+1] == '\0')) break;
		}
		else
		{
			split->list[j][x] = path[i];
			x++;
		}
		
		i++;		
	}
	
	split->i = j;
	
	return j;
}



/**
 * Crea il path globale
 */
uint32_t fs_get_full_path(char *cur, char *cur2, char *dest)
{
	if(cur2[0] != '/')
	{
		strcpy(dest, cur);
		if(dest[strlen(dest)-1] != '/')
			strcat(dest, "/");
		strcat(dest, cur2);
	}
	else strcpy(dest, cur2);	
}
