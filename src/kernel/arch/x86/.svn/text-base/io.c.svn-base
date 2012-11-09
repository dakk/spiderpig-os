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
 * \file kernel/arch/x86/io.c
 * \author Davide Gessa
 * \date 10-19-09
 */
#include <types.h>


/**
 * Output di 8 bit su una porta
 */
void io_outb(uint16_t port, uint8_t value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}



/**
 * Input di 8 bit su una porta
 */
uint8_t io_inb(uint16_t port)
{
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}




/**
 * Input di 16 bit su una porta
 */
uint16_t io_inw(uint16_t port)
{
    uint16_t ret;
    asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}



/**
 * Output di 16 bit su una porta
 */	
void io_outw(uint16_t port, uint16_t value)
{
    asm volatile ("outw %1, %0" : : "dN" (port), "a" (value));	
}




/**
 * Output di 32 bit su una porta
 */
void io_outd(uint16_t port, uint32_t value)
{
	asm volatile ("out %1, %0" : : "dN" (port), "a" (value));
}



/**
 * Input di 32 bit su una porta
 */
uint32_t io_ind(uint16_t port)
{
    uint32_t ret;
	asm volatile ("in %1, %0" : "=a" (ret) : "dN" (port));

    return ret;	
}


/**
 * Output di 64 bit su una porta
 */
void io_outl(uint16_t port, uint64_t value)
{
	//asm volatile ("outl %1, %0\n" : : "dN" (port), "a" (value));
}




/**
 * Input di 64 bit su una porta
 */
uint64_t io_inl(uint16_t port)
{
    uint64_t ret;

	//asm volatile ("inl %1, %0\n" : "=a" (ret) : "dN" (port));
	
	return ret;	
}








static inline uint8_t inb( uint16_t port ) {
    register uint8_t value;
 
    __asm__ __volatile__(
        "inb %1, %0\n"
        : "=a" ( value )
        : "dN" ( port )
    );
 
    return value;
}
 
static inline void outb( uint8_t data, uint16_t port ) {
    __asm__ __volatile__(
        "outb %1, %0\n"
        :
        : "dN" ( port ), "a" ( data )
    );
}
 
static inline uint16_t inw( uint16_t port ) {
    register uint16_t value;
 
    __asm__ __volatile__(
        "inw %1, %0\n"
        : "=a" ( value )
        : "dN" ( port )
    );
 
    return value;
}
 
static inline void outw( uint16_t data, uint16_t port ) {
    __asm__ __volatile__(
        "outw %1, %0\n"
        :
        : "dN" ( port ), "a" ( data )
    );
}
 
static inline uint32_t inl( uint16_t port ) {
    register uint32_t value;
 
    __asm__ __volatile__(
        "inl %1, %0\n"
        : "=a" ( value )
        : "dN" ( port )
    );
 
    return value;
}
 
static inline void outl( uint32_t data, uint16_t port ) {
    __asm__ __volatile__(
        "outl %1, %0\n"
        :
        : "dN" ( port ), "a" ( data )
    );
}
