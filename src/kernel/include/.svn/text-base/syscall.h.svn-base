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
 * \file kernel/include/syscall.h
 * \author Davide Gessa
 * \date 10-12-09
 */
#ifndef SYSCALL_H
#define SYSCALL_H

#include <types.h>

#define SYSCALL_INT				0x84


#define SYS_INFO_GET			0

#define SYS_KGETCHAR			5
#define SYS_KPUTCHAR			6

#define SYS_DEBUG_IOCTL			7

#define SYS_MILLISLEEP			10
		
#define SYS_FS_MOUNT			21
#define SYS_FS_UMOUNT			22
#define SYS_FS_IGET_MP			23

#define SYS_FS_READDIR			25
#define SYS_FS_OPENDIR			26	
#define SYS_FS_CLOSEDIR			27
#define SYS_FS_REWINDDIR		28
#define SYS_FS_MAKEDIR			29

#define SYS_FS_RM				30
		
#define SYS_FS_READ				32
#define SYS_FS_OPEN				33
#define SYS_FS_CLOSE			34
#define SYS_FS_WRITE			35
#define SYS_FS_SEEK				36

#define SYS_FS_LINK				40		
#define SYS_FS_UNLINK			41

#define SYS_TASK_MSG_CLEAR		70
#define SYS_TASK_MSG_SEND		71
#define SYS_TASK_MSG_RECV		72
		
#define SYS_TASK_GET_PID		73
#define SYS_TASK_KILL			74
#define SYS_TASK_PAUSE			75
#define SYS_TASK_RESUME			76
#define SYS_TASK_EXEC			77
#define SYS_TASK_SLEEPMS		78


#define DRIVER_ADD				90
#define DRIVER_DEL				91
#define DRIVER_IGET				92
#define DRIVER_INITD			93
#define DRIVER_FREED			94		
#define DRIVER_PUTS				95		
		
#define DEVICE_IGET				100
#define DEVICE_UPDATE			101



/**
 * Struttura di una syscall
 */
typedef struct
{
	uint32_t arg;			///< Numero di argomenti
	uint32_t (*call)();		///< Call
} syscall_t;


/**
 * Struttura dati per le info del kernel
 */
typedef struct 
{
	char name[32];		///< Nome del sistema
	char ver[16];		///< Versione del sistema
	char rev[16];		///< Revisione dell'svn
	char date[16];		///< Data di compiling
	char time[16];		///< Ora di compiling
	char arch[16];		///< Architettura
	char vend[16];		///< Cpu info
} sysinfo_t;


void syscall_callback(regs_t *);
int syscall_call(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
void syscall_init();

uint32_t syscall_info_get(sysinfo_t *);

#endif
