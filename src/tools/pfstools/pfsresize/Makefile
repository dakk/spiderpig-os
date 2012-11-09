all:
	gcc -c main.c -o main.o
	gcc main.o -o resize2fs.pfs

clean:
	rm *.o resize2fs.pfs


install:
	cp resize2fs.pfs /sbin/resize2fs.pfs
