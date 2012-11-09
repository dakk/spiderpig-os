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
 * \file kernel/syscall.c
 * \author Davide Gessa
 * \date 10-12-09
 */
#include <syscall.h>
#include <types.h>
#include <arch.h>
#include <debug.h>
#include <task/task.h>
#include <task/term.h>
#include <task/message.h>
#include <driver.h>
#include <video.h>
#include <driver.h>
#include <fs/fs.h>
#include <fs/file.h>
#include <fs/dir.h>
#include <main.h>
#include <debug.h>
#include <config.h>
#include <video.h>
#include <klibc/stdio.h>



int sys_getch()
{
	return getchar();
}

int sys_putch(uint32_t c)
{
	putchar((char) c);
}

int sys_mount(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
	return fs_mount((char *) a, (char *) b, (char *) c, (uint32_t) d);
}

int sys_umount(uint32_t a)
{
	return fs_umount((char *) a);
}

int sys_iget_mount_point(uint32_t a, uint32_t b)
{
	return fs_iget_mount_point((uint32_t) a, (mount_point_t **) b);
}


int sys_readdir(uint32_t a, uint32_t b)
{
	return fs_readdir((dir_t *) a, (struct dirent *) b);
}

int sys_opendir(uint32_t a)
{
	return (int) fs_opendir((char *) a);
}

int sys_closedir(uint32_t a)
{
	return fs_closedir((dir_t *) a);
}

int sys_rewinddir(uint32_t a)
{
	return fs_rewinddir((dir_t *) a);
}

int sys_makedir(uint32_t a)
{
	return fs_makedir((char *) a);
}

int sys_rm(uint32_t a)
{
	return fs_rm((char *) a);
}

int sys_read(uint32_t a, uint32_t b, uint32_t c)
{
	return fs_read((file_t *) a, (char *) b, (uint32_t) c);
}

int sys_open(uint32_t a, uint32_t b)
{
	return (int) fs_open((char *) a, (char *) b);
}

int sys_close(uint32_t a)
{
	return fs_close((file_t *) a);
}

int sys_write(uint32_t a, uint32_t b, uint32_t c)
{
	return fs_write((file_t *) a, (char *) b, (uint32_t) c);
}

int sys_seek(uint32_t a, uint32_t b, uint32_t c)
{
	return fs_seek((file_t *) a, (uint32_t) b, (uint64_t) c);
}

uint32_t sys_info_get(uint32_t a)
{
	return syscall_info_get((sysinfo_t *) a);
}

uint32_t sys_link(uint32_t a, uint32_t b)
{
	return fs_link((char *) a, (char *) b);
}

uint32_t sys_unlink(uint32_t a)
{
	return fs_unlink((char *) a);
}

uint32_t sys_device_iget(uint32_t a, uint32_t b)
{
	return device_iget((uint32_t) a, (device_t **) b);
}

uint32_t sys_device_update()
{
	device_update();
	return 0;
}

uint32_t sys_message_clear()
{
	message_clear();
	return 0;
}

uint32_t sys_message_send(uint32_t a, uint32_t b, uint32_t c)
{
	return message_send((pid_t) a, (char *) b, (uint32_t) c); 
}

uint32_t sys_driver_add(uint32_t a)
{
	return driver_add((driver_t *) a);
}

uint32_t sys_driver_del(uint32_t a)
{
	return driver_del((char *) a);
}

uint32_t sys_driver_iget(uint32_t a, uint32_t b)
{
	return driver_iget((uint32_t) a, (driver_t **) b);
}

uint32_t sys_driver_initd(uint32_t a)
{
	return driver_initd((char *) a);
}

uint32_t sys_driver_freed(uint32_t a)
{
	return driver_freed((char *) a);
}

uint32_t sys_message_recv(uint32_t a, uint32_t b)
{
	return message_recv((char *) a, (pid_t *) b);
}

uint32_t sys_void()
{
	return 0;
}

uint32_t sys_test()
{
	asm("sti");
	bish();
	//printf("syscall test!\n");	
	return 0;
}

uint32_t sys_millisleep(uint32_t a)
{
	arch_sleep(a);
}

uint32_t sys_task_sleepms(uint32_t a)
{
	task_sleep_ms(a);
}

uint32_t sys_driver_puts(uint32_t a, uint32_t b, uint32_t c)
{
	driver_puts((driver_t *) a, b, (char *) c);
}

/**
 * Lista delle syscalls
 */
static syscall_t syscalls[] =
	{
		////////////////////////////
		// System misc 1 : 20
		{ .arg = 1,		.call = (void *) sys_info_get },			// 0
		{ .arg = 0,		.call = (void *) sys_test },				// 1
		{ .arg = 0,		.call = (void *) sys_test },				// 2
		{ .arg = 0,		.call = (void *) sys_test },				// 3
		{ .arg = 0,		.call = (void *) shutdown },				// 4
		{ .arg = 0,		.call = (void *) sys_getch },				// 5
		{ .arg = 1,		.call = (void *) sys_putch },				// 6
	
	#ifdef DEBUG	
		{ .call = (void *) debug_ioctl },							// 7
	#endif
	#ifndef DEBUG
		{ .call = (void *) sys_void },								// 7
	#endif
	
		{ .call = (void *) sys_void },								// 8
		{ .call = (void *) sys_void },								// 9
		
		{ .arg = 1,		.call = (void *) sys_millisleep },			// 10
		
		{ .call = (void *) sys_void },								// 11
		{ .call = (void *) sys_void },								// 12
		{ .call = (void *) sys_void },								// 13
		{ .call = (void *) sys_void },								// 14
		{ .call = (void *) sys_void },								// 15
		{ .call = (void *) sys_void },								// 16
		{ .call = (void *) sys_void },								// 17
		{ .call = (void *) sys_void },								// 18
		{ .call = (void *) sys_void },								// 19
		{ .call = (void *) sys_void },								// 20
		
		
		///////////////////////////////
		// VFS 20 : 49
		{ .arg = 4, 	.call = (void *) sys_mount },				// 21
		{ .arg = 1,		.call = (void *) sys_umount },				// 22
		{ .arg = 2,		.call = (void *) sys_iget_mount_point },	// 23		
		{ .call = (void *) sys_void },								// 24

		
		// Directory
		{ .arg = 2,		.call = (void *) sys_readdir },				// 25
		{ .arg = 1,		.call = (void *) sys_opendir },				// 26
		{ .arg = 1,		.call = (void *) sys_closedir },			// 27
		{ .arg = 1,		.call = (void *) sys_rewinddir },			// 28
		{ .arg = 1,		.call = (void *) sys_makedir },				// 29
		
		
		{ .arg = 1,		.call = (void *) sys_rm },					// 30
		{ .call = (void *) sys_void },								// 31

		
		// File
		{ .arg = 3,		.call = (void *) sys_read },				// 32
		{ .arg = 2,		.call = (void *) sys_open },				// 33
		{ .arg = 1,		.call = (void *) sys_close },				// 34
		{ .arg = 3,		.call = (void *) sys_write },				// 35
		{ .arg = 3,		.call = (void *) sys_seek },				// 36
		{ .call = (void *) sys_void },								// 37
		{ .call = (void *) sys_void },								// 38
		{ .call = (void *) sys_void },								// 39
		
		// Link
		{ .arg = 2,		.call = (void *) sys_link },				// 40
		{ .arg = 1,		.call = (void *) sys_unlink },				// 41
		
		{ .call = (void *) sys_void },								// 42
		{ .call = (void *) sys_void },								// 43
		{ .call = (void *) sys_void },								// 44
		{ .call = (void *) sys_void },								// 45
		{ .call = (void *) sys_void },								// 46
		{ .call = (void *) sys_void },								// 47
		{ .call = (void *) sys_void },								// 48
		{ .call = (void *) sys_void },								// 49
		
		
		
		//////////////////////////////
		// Network 50 : 69
		{ .call = (void *) sys_void },								// 50
		{ .call = (void *) sys_void },								// 51
		{ .call = (void *) sys_void },								// 52
		{ .call = (void *) sys_void },								// 53
		{ .call = (void *) sys_void },								// 54
		{ .call = (void *) sys_void },								// 55
		{ .call = (void *) sys_void },								// 56
		{ .call = (void *) sys_void },								// 53
		{ .call = (void *) sys_void },								// 57
		{ .call = (void *) sys_void },								// 58
		{ .call = (void *) sys_void },								// 59
		{ .call = (void *) sys_void },								// 60
		{ .call = (void *) sys_void },								// 61
		{ .call = (void *) sys_void },								// 62
		{ .call = (void *) sys_void },								// 63
		{ .call = (void *) sys_void },								// 64
		{ .call = (void *) sys_void },								// 65
		{ .call = (void *) sys_void },								// 66
		{ .call = (void *) sys_void },								// 67
		{ .call = (void *) sys_void },								// 68
		{ .call = (void *) sys_void },								// 69
		
		
		
		//////////////////////////////
		// Task 70 : 89
		{ .arg = 0,		.call = (void *) sys_message_clear },		// 70
		{ .arg = 3,		.call = (void *) sys_message_send },		// 71
		{ .arg = 2,		.call = (void *) sys_message_recv },		// 72
		
		{ .call = (void *) task_get_pid },							// 73
		{ .call = (void *) task_kill },								// 74
		{ .call = (void *) task_pause },							// 75
		{ .call = (void *) task_resume },							// 76
		{ .call = (void *) task_exec },								// 77
		
		{ .arg = 1,		.call = (void *) sys_task_sleepms },		// 78
		
		{ .call = (void *) sys_void /*term_putch*/},				// 79
		{ .call = (void *) sys_void /*term_getch*/},				// 80
		{ .call = (void *) sys_void /*term_gotoxy*/},				// 81
		{ .call = (void *) sys_void /*term_getx*/},					// 82
		{ .call = (void *) sys_void /*term_gety*/},					// 83
		{ .call = (void *) sys_void /*term_setcolor*/},				// 84
		{ .call = (void *) sys_void /*term_getcolor*/},				// 85
		{ .call = (void *) sys_void /*term_clear*/},				// 86
		{ .call = (void *) sys_void },								// 87
		{ .call = (void *) sys_void },								// 88
		{ .call = (void *) sys_void },								// 89
			

		//////////////////////////////
		// Driver 90 : 99
		{ .arg = 1,		.call = (void *) sys_driver_add },			// 90
		{ .arg = 1,		.call = (void *) sys_driver_del },			// 91
		{ .arg = 2,		.call = (void *) sys_driver_iget },			// 92
		{ .arg = 1,		.call = (void *) sys_driver_initd },		// 93
		{ .arg = 1,		.call = (void *) sys_driver_freed },		// 94
		{ .arg = 3,		.call = (void *) sys_driver_puts },			// 95
		
		{ .call = (void *) sys_void },								// 96
		{ .call = (void *) sys_void },								// 97
		{ .call = (void *) sys_void },								// 98
		{ .call = (void *) sys_void },								// 99
		
		
		//////////////////////////////
		// Device 100 : 109
		{ .arg = 2,		.call = (void *) sys_device_iget },			// 100
		{ .arg = 0,		.call = (void *) sys_device_update }		// 101
				
	};


/**
 * Numero totale delle syscalls
 */
uint32_t syscalls_number = sizeof(syscalls) / sizeof(syscall_t);


/**
 * Effetua una chiamata ad una call con 5 argomenti
 * 
 * \param call numero della syscall
 * \param ebx parametro 1
 * \param ecx parametro 2
 * \param edx parametro 3
 */
int syscall_call5(uint32_t call, uint32_t p1, uint32_t p2, uint32_t p3, uint32_t p4, uint32_t p5)
{
	int ret;
	
	asm ("int %0\n" : : "g" (SYSCALL_INT));
	asm ("movl %%eax, %0\n\t" : "=r" (ret));
	return ret;
}


/**
 * Handler delle chiamate alla syscall
 * 
 * \param r tutti i registri salvati al momento dell'interruzione
 */
void syscall_callback(regs_t *r)
{	
	int ret;
	uint32_t p1, p2, p3, p4, p5, call;
		
	// Preleva gli argomenti
	//printf("%d\n", r->eax);
	//asm("pop %eax");
	asm("mov %%eax, %0\n" : "=r" (call));
	asm("mov %%ebx, %0\n" : "=r" (p1));
	asm("mov %%ecx, %0\n" : "=r" (p2));
	
	//printf("Call: %d %d %d\n", call, p1, p2);
	//while(1);
	if(call > syscalls_number)
		return;
		
	switch(syscalls[call].arg)
	{
		case 0:
			ret = syscalls[call].call();
			break;
		case 1:
			ret = syscalls[call].call(p1);
			break;
		case 2:
			ret = syscalls[call].call(p1, p2);
			break;
		case 3:
			ret = syscalls[call].call(p1, p2, p3);
			break;
		case 4:
			ret = syscalls[call].call(p1, p2, p3, p4);
			break;
		case 5:
			ret = syscalls[call].call(p1, p2, p3, p4, p5);	
			break;	
			
		default:
			ret = syscalls[call].call(p1, p2, p3);
	}
	
	// Restituisce il valore di ritorno
	asm("movl %0, %%eax\n\t": : "g" (ret));
	//asm("ret"); 
}



/**
 * Inizializza le syscall
 */
void syscall_init()
{
	DEBUGP("syscall_init()\n");
	//asm("mov %eax, 9\nint $0x84\n");
}





/**
 * Prende le info del sistema
 */
uint32_t syscall_info_get(sysinfo_t *ki)
{
	strcpy(ki->name, NAME);
	strcpy(ki->ver, VER);
	strcpy(ki->rev, REV);
	strcpy(ki->date, __DATE__);
	strcpy(ki->time, __TIME__);
	strcpy(ki->arch, ARCH);
	strcpy(ki->vend, CPU_VENDOR);
}
