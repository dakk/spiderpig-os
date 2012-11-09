#include <types.h>

void arch_video_move_cursor(uint8_t x, uint8_t y)
{
	asm(
		"movl  %0, %%eax   \n"
		"movl  %1, %%ebx   \n"
		"movl  $0x50, %%ecx   \n"
		"mul   %%ecx		  \n"
		"addl  %%ebx, %%eax   \n"
		"movw  $0x03d4, %%dx  \n"
		"pushl %%eax		  \n"
		"movb  $0x0f, %%al    \n"
		"out   %%al, %%dx     \n"
		"popl  %%eax		  \n"
		"movw  $0x03d5, %%dx  \n"
		"out   %%al, %%dx     \n"
		"shr   $0x08,%%eax      \n"
		"pushl %%eax		  \n"
		"movw  $0x03d4, %%dx  \n"
		"movb  $0x0e, %%al    \n"
		"out   %%al, %%dx     \n"
		"pop   %%eax		  \n"
		"movw  $0x03d5, %%dx  \n"
		"out   %%al, %%dx     \n"
		: : "g" (y), "g" (x)
	);
}
