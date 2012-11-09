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
 * \file kernel/driver/hid/keyboard.c
 * \author Davide Gessa
 * \date 10-12-09
 * \note Driver per i dispositivi tastiera ps2
 */
#include "keyboard.h"
#include <klibc/stdio.h>
#include <types.h>
#include <arch.h>
#include <video.h>
#include <driver.h>

driver_t driver_keyboard = 
{
	.name = "keyboard\0",
	.desc = "ps2 keyboard driver\0",
	.author = "Davide Gessa\0",
						
	.probe = keyboard_probe,
						
	.init = keyboard_init,
	.free = keyboard_free
};

///< Caratteri ascii
char keyboard_standard_charset[] = {
		0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\'', 0, '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',   
		0, 0, '\n', 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 0, 0, 0, 0, 0, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', 
		'-', 0, 0, 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'-', 0, '5', 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
	};
			
///< Caratteri ascii maiuscoli
char keyboard_standard_charset_shifted[] = {
		0, 0, '!', '"', 0, '$', '%', '&', '/', '(', ')', '=', '?', '^', 0, '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[',
		']', '\n', 0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '@', '#', 0, 0, '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ';', ':', '_', 0,
		0, 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'-', 0, '5', 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
	};



/**
 * 
 */
uint32_t keyboard_probe(device_t *dev)
{
	return 1;
}


/**
 * Restituisce un char dallo standard charset
 */
char keyboard_getchar()
{	
	if(bufsize > 0)
	{ 
		char ch = buf[bufwhere];
		bufwhere++;
		bufsize--;
		return ch;
	}
	else return 0;
}


/**
 * Handler della tastiera
 */
static void keyboard_callback(regs_t *reg)
{	
	unsigned code = io_inb(0x60);

	// Tasto rilasciato
    if (code & 0x80)
    {
		code &= 0x7F;
		switch(code)
		{
			case SHIFT_LEFT:
			case SHIFT_RIGHT:
				shift = 0;
				break;
		}
    }
    // Tasto premuto
    else
    {
		switch(code)
		{						
			case LOCK_CAPS:
				capslock = !capslock;
				keyboard_update_leds(LED_CAPS | LED_NUM);
				break;
				
			case LOCK_NUM:
				numlock = !numlock;
				keyboard_update_leds(LED_CAPS | LED_NUM);
				break;
				
			case SHIFT_LEFT:
			case SHIFT_RIGHT:
				shift = 1;
				break;
			
			default:
				if((shift && !capslock) || (!shift && capslock)) buf[bufpoint] = keyboard_standard_charset_shifted[code];
				else buf[bufpoint] = keyboard_standard_charset[code];
				bufsize++;
				bufpoint++;
				break;
		}
    }

}

/**
 * Aggiorna lo stato dei led della tastiera
 */
void keyboard_update_leds(uint8_t status)
{
 	uint8_t tmp;
 	while((io_inb(0x64)&2)!=0){}
 	io_outb(0x60,0xED);
 
 	while((io_inb(0x64)&2)!=0){}
 	io_outb(0x60,status);
 }
 

/**
 * Inizializza l'handler della tastiera
 */
uint32_t keyboard_init()
{	
	handler_reg(IRQ_KEYBOARD, &keyboard_callback);
	shift = alt = control = capslock = numlock = 0;
	bufwhere = bufsize = bufpoint = 0;	

	devfs_reg_device(NULL, &driver_keyboard, "keyb0");
	
	return DRV_OK;
}


/**
 * Nulla gli handlers
 */
uint32_t keyboard_free()
{
	handler_unreg(IRQ_KEYBOARD);
	return DRV_OK;
}


/**
 * Scrive in un buffer tot dati ricevuti dalla tastiera
 */
uint32_t keyboard_read(char *data, uint32_t size, uint64_t off)
{
	int i = 0;
	char c;
	
	while(((c = keyboard_getchar()) != 0) && (i < size))
	{
		data[i] = c;
		i++;
	} 

	return i;
}
