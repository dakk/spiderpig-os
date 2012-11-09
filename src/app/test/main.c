/**
 * \file app/test/main.c
 * \note Programma che testa tutte le funzioni del sistema, comprese 
 * le librerie di sistema
 * \author Davide Gessa
 * \date 10-16-09
 */
//#include <system/types.h>
//#include <system/syscall.h>

void main()
{
	//syscall_call(0x02, 0, 0, 0);
	asm("mov 1, %eax\nint $0x84\n");
	while(1);
/*	syscall_call1(0x01, 0x12);
	syscall_call1(0x01, 0x12);

	syscall_call1(0x02, 0x12);
	syscall_call1(0x03, 0x12);
	//syscall_call5(0x04, 0x12, 0, 0, 0, 0);
	syscall_call1(0x06, 'a');
	syscall_call1(0x06, 'b');
	syscall_call1(0x06, 'c');
	syscall_call1(0x06, '\n');
	*/
	return;
}



