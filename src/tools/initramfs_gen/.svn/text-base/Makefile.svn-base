all:
	gcc -c main.c -o main.o -I"../kernel" -I"../kernel/include"
	gcc main.o -o initramfs_gen

clean:
	rm *.o initramfs_gen

