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
 * \file kernel/driver.c
 * \author Davide Gessa
 * \note Gestore dei driver per hardware e altre features
 * \date 10-12-09
 */
#include <driver.h>
#include <mm/mm.h>
#include <debug.h>
#include <driver/input/keyboard.h>
#include <driver/input/mouse.h>
#include <driver/crypto/crc32.h>
#include <driver/net/modem.h>
#include <driver/net/rs232.h>
#include <driver/net/ne2k.h>
#include <driver/net/rtl8139.h>
#include <driver/crypto/md5.h>
#include <driver/smbios.h>
#include <driver/fs/pfs/pfs.h>
#include <driver/char/random.h>
#include <driver/fs/tmpfs/tmpfs.h>
#include <driver/fs/initramfs/initramfs.h>
#include <driver/block/ata_pio.h>
#include <config.h>
#include <driver/bus/pci/pci.h>
#include <driver/video/vesa.h>
#include <fs/devfs.h>
#include <video.h>


/**
 * Puts per i driver
 */
void driver_puts(driver_t *drv, uint32_t type, char *data)
{
	#ifdef VERBOSE
	printf("[");
	
	switch(type)
	{
		case MDRV_ER:
			video_puts_colored(VIDEO_RED_BLACK, drv->name);
			break;
			
		case MDRV_OK:
			video_puts_colored(VIDEO_GREEN_BLACK, drv->name);
			break;
		
		case MDRV_WR:
			video_puts_colored(VIDEO_YELLOW_BLACK, drv->name);
			break;
			
		case MDRV_IN:
			video_puts_colored(VIDEO_BLUE_BLACK, drv->name);
			break;
			
		default:
			video_puts_colored(VIDEO_BLUE_BLACK, drv->name);
			break;
	}		
	printf("] %s\n", data);
	#endif
}



/**
 * Inizializza il gestore dei driver
 */
void driver_init()
{
	DEBUGP("driver_init()\n");
	
	device_list = NULL;
	driver_list = NULL;

	// Bus
	#ifdef DPCI
		driver_add(&driver_pci);
	#endif

	#ifdef DSMBIOS
		driver_add(&driver_smbios);
	#endif

	// Hid
	#ifdef DKEYBOARD
		driver_add(&driver_keyboard);
	#endif
	#ifdef DMOUSE
		driver_add(&driver_mouse);
	#endif
	
	
	// CHAR
	#ifdef DRANDOM
		driver_add(&driver_random);
	#endif
	
	
	// Crypto
	#ifdef DMD5
		driver_add(&driver_md5);
	#endif
	#ifdef DCRC32
		driver_add(&driver_crc32);
	#endif
	
	
	// Network
	#ifdef DMODEM
		driver_add(&driver_modem);
	#endif
	#ifdef DRS232
		driver_add(&driver_rs232);
	#endif
	#ifdef DNE2K
		driver_add(&driver_ne2k);
	#endif
	#ifdef DRTL8139
		driver_add(&driver_rtl8139);
	#endif
	
		
	// Block
	#ifdef DATAPIO
		driver_add(&driver_ata_pio);
	#endif
	
	
	// Video
	#ifdef DVESA
		driver_add(&driver_vesa);
	#endif
	
	// Fs
	#ifdef FSPFS
		driver_add(&driver_pfs);
	#endif
	#ifdef FSTMPFS
		driver_add(&driver_tmpfs);
	#endif
	#ifdef FSINITRAMFS
		driver_add(&driver_initramfs);
	#endif
}


/**
 * Aggiune un driver alla lista
 * 
 * \param driver puntatore al driver da aggiungere alla lista
 * \return stato dell'operazione
 */
uint32_t driver_add(driver_t *driver)
{
	//printf("%s\n",driver->name);
	driver->next = driver_list;
	driver_list = driver;
	driver->loaded = 0;
	
	return DRV_OK;
}



/**
 * Elimina un driver
 * 
 * \param n nome del driver da eliminare
 * \return stato dell'eliminazione
 */
uint32_t driver_del(char *n)
{
	driver_t *m = driver_get(n);
	driver_t *pr = driver_list;
		
	if(m == NULL) return DRV_NF_ER;
	
	
	// Cerca il precedente
	if(m == driver_list)
	{
		driver_list = NULL;
	}
	else
	{
		while(pr != NULL && pr->next != NULL)
		{
			if(strcmp(pr->next->name, n) == 0) break; 
			pr = pr->next;
		}
		pr->next = m->next;
	}	
}



/**
 * Richiama direttamente la funzione ioctl di un driver
 */
uint32_t driver_ioctl(char *drv, device_t *dev, uint32_t call, uint32_t a, uint32_t b)
{
	driver_t *d = driver_get(drv);
	
	if(d == NULL || d->ioctl == NULL)
		return 0;
		
	else
		return d->ioctl(dev, call, a, b);
}


/**
 * Restituisce il nome del driver dato il num
 * 
 * \param x e' il numero del driver nella lista
 * \return nome del driver nella posizione x
 */
uint32_t driver_iget(uint32_t x, driver_t **dr)
{
	int i = 0;
	driver_t *m = driver_list;
	
	while(m != NULL)
	{
		if(i == x)
		{
			*dr = m;
			return 1;
		}
		
		m = m->next;
		i++;
	}	
	*dr = NULL;
}


/**
 * Inizializza
 */
uint8_t driver_initd(char *drv)
{
	driver_t *m = driver_get(drv);
	
	if(m == NULL)
		return DRV_NF_ER;
	
	if(m->loaded == 1)
		return DRV_AL_LD;
	
	if(m->init == 0)
		return DRV_NF_IN;
	
	if(m->init() == DRV_OK)
	{
		m->loaded = 1;
		
		driver_puts(m, MDRV_IN, "initialized");
	
		return DRV_OK;
	}
	
	return DRV_ER;
}


/**
 * Deinizializza
 */
uint8_t driver_freed(char *drv)
{
	driver_t *m = driver_get(drv);
	
	if(m == NULL)
		return DRV_NF_ER;
	
	if(m->loaded == 0)
		return DRV_NT_IN;
	
	if(m->free == 0)
		return DRV_NF_FR;
	
	if(m->free() == DRV_OK)
	{
		m->loaded = 0;

		driver_puts(m, MDRV_IN, "deinitialized");
		
		return DRV_OK;
	}
	
	return DRV_ER;	
}


/**
 * Restituisce il driver dato il nome
 * 
 * \param name nome del driver da prelevare
 * \return il driver richiesto se e' presente, altrimenti NULL
 */
driver_t *driver_get(char *name)
{
	driver_t *m = driver_list;
	
	while(m != NULL)
	{
		if(strcmp(m->name, name) == 0)
			return m;
			
		m = m->next;	
	}
	return NULL;	
}
