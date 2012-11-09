DIR = kernel

include Makefile.am

all:
	$(CD) kernel && make && cd ..
	$(CD) lib && make && cd ..
	$(CD) app && make && cd ..
	
clean:
	$(CD) kernel && make clean && cd ..
	$(CD) app && make clean && cd ..
	$(CD) lib && make clean && cd ..
