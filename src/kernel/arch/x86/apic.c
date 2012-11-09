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
 * \file apic.c
 * \author Davide Gessa
 * \date 11-12-09
 */
#include <types.h>
#include <klibc/stdio.h>
#include <klibc/string.h>

#define APIC_BASE_MSR			0x1B
#define APIC_BASE_MSR_ENABLE	0x800
 
 
/** 
 * Verifica se la cpu supporta l'apic
 */
uint32_t apic_probe()
{
	uint16_t a;
	uint16_t d;
	
	//cpuid(1,&a,&d);
	
	//return (d & CPUID_FLAG_APIC);
}
 
 
 
/** 
 * Indirizzo base dell'apic
 */
uint32_t apic_get_base()
{
	uint16_t a;
	uint16_t d;

	//cpuGetMSR(IA32_APIC_BASE_MSR,&a,&d);

	return (a&0xfffff000);
}
