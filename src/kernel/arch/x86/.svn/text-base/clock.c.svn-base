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
 * \file kernel/arch/x86/clock.c
 * \author Davide Gessa
 * \date 10-19-09
 */
#include "archinc.h"
#include <arch.h>
#include <types.h>
#include <main.h>


/**
 * Legge i secondi
 */
uint8_t clock_get_seconds()
{
	io_outb(RTCaddress,0);
	return (uint8_t) bcd2bin(io_inb(RTCdata));
}


/**
 * Legge i minuti
 */
uint8_t clock_get_minutes()
{
	io_outb(RTCaddress,0x02);
	return (uint8_t) bcd2bin(io_inb(RTCdata));
}



/**
 * Legge le ore
 */
uint8_t clock_get_hours()
{
	io_outb(RTCaddress,0x04);
	return (uint8_t) bcd2bin(io_inb(RTCdata));
}



/**
 * Legge il giorno
 */
uint8_t clock_get_day()
{
	io_outb(RTCaddress,0x07);
	return (uint8_t) bcd2bin(io_inb(RTCdata));
}



/**
 * Legge il mese
 */
uint8_t clock_get_month()
{
	io_outb(RTCaddress,0x08);
	return (uint8_t) bcd2bin(io_inb(RTCdata));
}



/**
 * Legge l'anno
 */
uint8_t clock_get_year()
{
	io_outb(RTCaddress,0x09);
	return (uint8_t) bcd2bin(io_inb(RTCdata));
}


/**
 * Imposta l'ora del kernel, aggiornata dal pit
 */
static void clock_callback(regs_t *r)
{
	clock_data.hours = clock_get_hours();
	clock_data.minutes = clock_get_minutes();
	clock_data.seconds = clock_get_seconds();
	clock_data.month = clock_get_month();
	clock_data.year = clock_get_year();
	clock_data.day = clock_get_day();
}


/**
 * Inizializza l'rtc
 */
void clock_init()
{
	char prev;
	
	io_outb(0x70, 0x0B); 
	prev = io_inb(0x71); 
	io_outb(0x70, 0x0B); 
	io_outb(0x71, prev | 0x40);

	handler_reg(8, &clock_callback);
}



/**
 * Restituisce data e ora in formato univoco
 */
uint32_t arch_get_clock()
{
	return 0;
}
