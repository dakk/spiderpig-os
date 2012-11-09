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
 * \file paged.c
 * \author Davide Gessa
 * \note Mappatura delle pagine virtuali
 * \date 10-12-09
 */

#include <mm/phys.h>
#include <mm/paged.h>
#include <types.h>
#include <debug.h>
#include <video.h>


/**
 * Dato un indirizzo virtuale, restituisce quello reale
 * 
 * \param virtual indirizzo virtuale
 * \return indirizzo fisico
 */
void *page_get_phys_addr(void *virtual)
{
	
}


/**
 * Viene mappato un indirizzo reale ad uno virtuale
 */
void page_map_page(void *real, void *virtual, uint32_t flags)
{

}


/**
 * Una pagina virtuale mappata in memoria viene smappata
 */
void page_unmap_page(void *virtual)
{
	
}


/**
 * Swap a page to the swap fs
 */
void page_swap()
{
	
}


/**
 * Get a page from the swap fs
 */
void page_unswap()
{
	
}


/**
 * Handler del page fault
 */
void page_fault_handler(regs_t regs)
{
	uint32_t fault_adr;
	
	asm volatile("mov %%cr2, %0" : "=r" (fault_adr));
    
    if(video_getx() != 0) printf("\n");
   	video_puts_colored(VIDEO_HI_BLUE_BLACK, "   -> ");
	printf("Page fault at 0x%x", fault_adr);
	
	if(!(regs.err_code & 0x1))
	{ 
		printf(" page not present");
		
		// Guarda se e' presente nello swap se e' in lettura
	}
	printf(" (");
	
	if(regs.err_code & 0x2) 
		printf("Write");
	else 
		printf("Read");

	if(regs.err_code & 0x4) 
		printf("/User");
	else 
		printf("/Kernel");
		
	
	// overwritting cpu reserved bits of page entry
	if(regs.err_code & 0x8) 
		printf("/Overwrite");
	
	// caused by an istruction fetch
	if(regs.err_code & 0x10) 
		printf("/Fetching");

	printf(")\n");
	return;
}


/**
 * Abilita la paginazione
 */
void page_init()
{
	DEBUGP("page_init()\n");
	
	uint32_t i;
	uint32_t address; 
	uint32_t page_aligned_end;
	uint32_t *page_directory;
	uint32_t *first_page_table;


	// Trova  un area di memoria allineata dopo il kernel (sostituisci 0x100000 con 
	//  la fine del kernel) dove poter mettere la pagedir 
	page_aligned_end = (((uint32_t) 0x1000000) & 0xFFFFF000) + 0x1000;
	page_directory = (uint32_t *) page_aligned_end;
	

	for(i = 0; i < 1024; i++)
	{
		//attribute: supervisor level, read/write, not present.
		page_directory[i] = 0 | 2; 
	}
	
	first_page_table = page_directory + 0x1000;
	
	address = 0;
	
	//we will fill all 1024 entries, mapping 4 megabytes
	for(i = 0; i < 1024; i++)
	{
		first_page_table[i] = address | 3; // attributes: supervisor level, read/write, present.
		address = address + 4096; //advance the address to the next page boundary
	}

	page_directory[0] = (uint32_t) first_page_table; 
	page_directory[0] |= 3;// attributes: supervisor level, read/write, present


	// Scriviamo le informazioni nei registri
	write_cr3(page_directory); 
	write_cr0(read_cr0() | 0x80000000);
}
