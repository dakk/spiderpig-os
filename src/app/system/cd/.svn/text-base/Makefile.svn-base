include ../../../Makefile.am

SOURCES = cd.o ../../../lib/libc/libc.a

all: $(SOURCES) link

clean:
	rm cd $(SOURCES)
	
link:
	$(LD) $(LDFLAGS) -o cd $(SOURCES) $(LIB)
