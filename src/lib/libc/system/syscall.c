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
#include <system/syscall.h>
#include <system/types.h>


/**
 * Effetua una chiamata ad una call con 5 argomenti
 * 
 * \param call numero della syscall
 */
int syscall_call5(uint32_t call, uint32_t p1, uint32_t p2, uint32_t p3, uint32_t p4, uint32_t p5)
{
	int ret;
	
	asm ("int %0\n" : : "g" (SYSCALL_INT));
	asm ("movl %%eax, %0\n\t" : "=r" (ret));

	return ret;
}

/**
 * Effetua una chiamata ad una call con 4 argomenti
 * 
 * \param call numero della syscall
 */
int syscall_call4(uint32_t call, uint32_t p1, uint32_t p2, uint32_t p3, uint32_t p4)
{
	int ret;
	
	asm ("int %0\n" : : "g" (SYSCALL_INT));
	asm ("movl %%eax, %0\n\t" : "=r" (ret));

	return ret;
}


/**
 * Effetua una chiamata ad una call con 3 argomenti
 * 
 * \param call numero della syscall
 */
int syscall_call3(uint32_t call, uint32_t p1, uint32_t p2, uint32_t p3)
{
	int ret;
	
	asm ("int %0\n" : : "g" (SYSCALL_INT));
	asm ("movl %%eax, %0\n\t" : "=r" (ret));

	return ret;
}


/**
 * Effetua una chiamata ad una call con 2 argomenti
 * 
 * \param call numero della syscall
 */
int syscall_call2(uint32_t call, uint32_t p1, uint32_t p2)
{
	int ret;
	
	asm ("int %0\n" : : "g" (SYSCALL_INT));
	asm ("movl %%eax, %0\n\t" : "=r" (ret));

	return ret;
}

/**
 * Effetua una chiamata ad una call con 1 argomenti
 * 
 * \param call numero della syscall
 */
int syscall_call1(uint32_t call, uint32_t p1)
{
	int ret;
	
	asm ("int %0\n" : : "g" (SYSCALL_INT));
	asm ("movl %%eax, %0\n\t" : "=r" (ret));

	return ret;
}
