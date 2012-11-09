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
 * \file mm/mm.c
 * \author Davide Gessa
 * \note Gestione della memoria
 * \date 10-12-09
 */
#include <mm/mm.h>
#include <video.h>
#include <debug.h>
#include <mm/phys.h>
#include <mm/paged.h>
#include <config.h>

/**
 * Inizializza il gestore della memoria
 * 
 * \param low memoria bassa
 * \param high memoria alta
 */
void mm_init(uint32_t low, uint32_t high)
{
	DEBUGP("mm_init()\n");
		
	phys_init(low + high);
	
	#ifdef PAGING
		//page_init();
	#endif
}



/**
 * Alloca una pagina per il kernel
 * 
 * \param size pagine da allocare
 * \return puntatore all'area allocata
 */
void *mm_kalloc(size_t size)
{
	//DEBUGP("mm_kalloc()\n");
	
	unsigned bnum = (unsigned) ((size + 1) / (PHYS_PAGE_SIZE * 1024)) + 1; 
	// / PHYS_PAGE_SIZE + 1;
	//video_putint(bnum);
	//video_puts("\n");
	return (void *)phys_alloc(bnum);
}


/**
 * Libera una pagina per il kernel
 * 
 * \param addr indirizzzo della pagina
 */
void mm_kfree(void *addr)
{
	//DEBUGP("mm_kfree()\n");
	
	phys_free(addr);
}


/**
 * Restituisce la memoria totale del sistema (kb)
 * 
 * \return memoria totale
 */
uint32_t mm_get_total_mem(){ return phys_total; }


/**
 * Restituisce la memoria usata del sistema (kb)
 * 
 * \return memoria usata
 */
uint32_t mm_get_used_mem()
{ 
	return ((phys_page_number - phys_get_free_pages()) * PHYS_PAGE_SIZE);
}


#ifdef TEST

/**
 * Effettua un test sull'allocazione e deallocazione fisica e virtuale
 */
void mm_test()
{
	DEBUGP("mm_test()\n");
	
	show_used_memory();
	video_puts("Alloc 1000 blocks of 4*1024 bytes\n");
	char *data = phys_alloc(1000);
	show_used_memory();
	video_puts("Delloc 1000 blocks of 4*1024 bytes\n");
	phys_free(data);
	show_used_memory();	
}

/**
 * Visualizza la memoria
 */
void show_used_memory()
{
	video_puts_colored(VIDEO_HI_BLUE_BLACK, "\t-> ");
	printf("used: %dkb (%d%%);  ", mm_get_used_mem(), mm_get_used_mem() * 100 / mm_get_total_mem());
	printf("total: %dkb\n", mm_get_total_mem());
}


#endif




/**
 * Restituisce la dimensione di un allocazione
 */
uint32_t mm_get_usable_size(void *addr)
{
	int i = 0;
	for(i = 0; i < PHYS_MAX_BLOCKS; i++)
		if(phys_allocated[i].address == addr)
			return phys_allocated[i].dim;
	
	return 0;
}
