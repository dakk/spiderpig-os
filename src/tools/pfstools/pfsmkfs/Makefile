all:
	gcc -c main.c -o main.o -I"../../kernel" -I"../../kernel/include"
	gcc main.o -o mkfs.pfs

clean:
	rm *.o mkfs.pfs

install:
	cp mkfs.pfs /sbin/mkfs.pfs
