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
 * \file kernel/main.c
 * \author Davide Gessa
 * \date 10-12-09
 */

/*! \mainpage SpiderPig Documentation
 *
 */


#include <main.h>
#include <video.h>
#include <arch.h>
#include <types.h>
#include <syscall.h>
#include <task/task.h>
#include <fs/fs.h>
#include <network/network.h>
#include <mm/mm.h>
#include <debug.h>
#include <log.h>
#include <driver.h>
#include <bish.h>
#include <config.h>
#include <driver/char/random.h>
#include <driver/video/vesa.h>
#include <driver/video/loadsplash/loadsplash.h>
#include <driver/net/rs232.h>
#include <driver/net/ne2k.h>
#include <driver/net/modem.h>



/**
 * Carica il sistema
 *
 * \param mb puntatore al multiboot header
 */
int main(multiboot_info_t *mb)
{
	#ifdef DEBUG
		debug_init();
		#ifdef DEBUG_REG_TRAC
			debug_reg_trace(1);
		#endif
	#endif
	
	
	DEBUGP("main()\n");

	mod_addr = (void *) ((multiboot_module_t *) mb->mods_addr)->mod_start;
	mboot = mb;

	video_set_color(VIDEO_HI_WHITE_BLACK);
	video_clear();

	#ifdef VERBOSE
	video_puts_colored(VIDEO_HI_BLUE_BLACK, "-> ");
	video_puts_colored(VIDEO_HI_BLUE_BLACK, MSG_WELCOME);
	video_puts_colored(VIDEO_HI_BLUE_BLACK, NAME);
	video_puts_colored(VIDEO_HI_BLUE_BLACK, " ");
	video_puts_colored(VIDEO_HI_BLUE_BLACK, VER);
	video_puts_colored(VIDEO_HI_BLUE_BLACK, " ");
	video_puts_colored(VIDEO_HI_BLUE_BLACK, REV);
	video_puts("\n");
	#endif
	#ifndef VERBOSE
	video_puts_colored(VIDEO_HI_BLUE_BLACK, "* ");
	printf("%s %s %s\n", NAME, VER, REV);
	printf("copyright 2010, Davide Gessa\n");
	printf("%s is open source software (spiderpig.osdev.it)\n", NAME);
	printf("loading...  ");
	int i;
	int s = 0;
	
	for(i = 0; i < 20000; i++)
	{
		video_gotoxy(video_getx() - 1, video_gety());
		
		switch(s)
		{
			case 0:
				printf("|");
				s++;
				break;
			case 1:
				printf("/");
				s++;
				break;
			case 2:
				printf("-");
				s++;
				break;
			case 3:
				printf("\\");
				s = 0;
				break;				
		}
	}
	video_gotoxy(video_getx() - 2, video_gety());
	printf("\n");
	
	#endif
	
	// Arch based
	arch_init();
	#ifdef VERBOSE
	video_puts_colored(VIDEO_HI_BLUE_BLACK, " -> ");
	video_puts(MSG_ARCH_INIT);
	printf("%s (%s)\n", ARCH, CPU_VENDOR);
	#endif
	
	// Memory manager
	mm_init(mb->mem_lower, mb->mem_upper);
	#ifdef VERBOSE
	video_puts_colored(VIDEO_HI_BLUE_BLACK, " -> ");
	video_puts(MSG_MM_INIT); 
	video_puts("(");
	video_putint((mm_get_total_mem() / 1024));
	video_puts("mb)\n");
	#endif
	
	// Driver manager
	#ifdef VERBOSE
	video_puts_colored(VIDEO_HI_BLUE_BLACK, " -> ");
	video_puts(MSG_DRV_INIT);
	#endif 
	driver_init();
	
			
	// Syscalls
	#ifdef VERBOSE
	video_puts_colored(VIDEO_HI_BLUE_BLACK, " -> ");
	video_puts(MSG_SYSCALL_INIT);
	#endif
	syscall_init();


	// Task Manager
	#ifdef VERBOSE
	video_puts_colored(VIDEO_HI_BLUE_BLACK, " -> ");
	video_puts(MSG_TASK_INIT);
	#endif	
	task_init(TASK_SWITCH_ROUND_ROBIN);	
	
	#ifdef SMP
		// Se e' supportato il multiprocessing
		uint32_t cpu_n = cpu_num();
		
		if(cpu_n > 0)
		{
			for(i = 0; i < cpu_n; i++)
			{
				cpu_whake(i);
				
				if(cpu_get_state(i) == CPU_READY)
				{
					printf("cpu%d: ready.\n", i);
				}
			}
		}
	#endif
	
	// File System Manager
	#ifdef VERBOSE
	video_puts_colored(VIDEO_HI_BLUE_BLACK, " -> ");
	video_puts(MSG_FS_INIT);
	#endif	
	fs_init();

	#ifdef LOG
		log_init();
	#endif
	
	// Update hardware
	device_update();
	
	#ifdef NETWORK
		// Network Manager
		#ifdef VERBOSE
		video_puts_colored(VIDEO_HI_BLUE_BLACK, " -> ");
		video_puts(MSG_NET_INIT);
		#endif	
		network_init();
	#endif
	
	// Kernel init
	kinit();

	// Spegnimento se init viene chiuso
	sd:
		shutdown();
		
		while(1);
}


/**
 * Spegnimento del pc
 */
void shutdown()
{	
	DEBUGP("shutdown()\n");
	
	printf("\n");
	
	// Mandiamo il segnale di kill a tutti i processi
	/*DEBUGP("main.c -> killing all processes\n");*/
	video_puts_colored(VIDEO_HI_BLUE_BLACK, " -> ");
	video_puts(MSG_TASK_KILL);
	task_kill(0);
	
	
	// Umount di tutti i filesystem
	unsigned i;

	for(i = 0; i < MP_MAX; i++)
	{
		if(fs_mountpoints[i].used)
		{
			video_puts_colored(VIDEO_HI_BLUE_BLACK, " -> ");
			printf(MSG_UMOUNTING " %s\n", fs_mountpoints[i].path);
			fs_umount(fs_mountpoints[i].path);
		}
	}
	
	video_puts_colored(VIDEO_HI_BLUE_BLACK, "-> ");		
	video_puts(MSG_SHUTDOWN);
	
	arch_shutdown();
	while(1);
}



/**
 * KInit
 */
int kinit()
{	
	DEBUGP("kinit()\n");
	
	/// Troviamo il filesystem in cui c'e' l'init script
	
	// Initfs
	#ifdef FSINITRAMFS
		fs_makedir("/initr");
		fs_mount("\0", "/initr", "initramfs\0", 0);
	#endif
	
	// Numeri random
	#ifdef DRANDOM
		driver_initd("random");
	#endif
	
	// Controlliamo prima se e' possibile avviare lo splash
	#ifdef DVESA
		if(mboot->vbe_control_info != 0)
		{		
			vesa_init(mboot->vbe_control_info, mboot->vbe_mode_info);
			
			// Avviamo lo splash
			#ifdef LOADSPLASH
				if(mboot->vbe_control_info != 0)
				{
					loadsplash(vesa_get_mode_info()->width, vesa_get_mode_info()->height);
				}
			#endif
		}
	#endif	

	
	#ifdef TEST
	// Fs di prova
	fs_makedir("/bin");
	fs_makedir("/tmp");

	// Task test
	/*char *asd[1] = {"system"};
	char *asd2[1] = {"test"};  
	task_exec(task2, asd, 1);
	task_exec(task1, asd2, 1);
	*/
	//term_delete(task_get_from_pid(1)->term);
	#endif

	ne2k_probe(0);

	/// Avviamo l'init script
	// Se e' definita la shell, carichiamola
	#ifdef SHELL
		bish();
	#endif


	return 0;
}
