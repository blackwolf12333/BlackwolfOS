# Make file for api directory

CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector
LDFLAGS=-Tlink.ld
ASFLAGS=-felf

SOURCES = linked_list.o

all: $(SOURCES)

clean:
	-rm *.o
