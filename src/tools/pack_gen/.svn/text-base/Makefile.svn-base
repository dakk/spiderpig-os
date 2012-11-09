all:
	gcc -I../../kernel/include/ packet.c -c -o packet.o 
	gcc -I../../kernel/include/ main.c -c -o main.o
	gcc main.o packet.o -o pack_gen
