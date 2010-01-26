CC	= gcc
GCC	= gcc

CFLAGS ?= -Wall
override CFLAGS += -I../include -ffreestanding
override LDFLAGS = -Tlink.x

IMAGE	= kernel

OBJS	= ../dev/kbd.o ../dev/vga.o ../dev/pit.o ../dev/pic.o \
	../lib/prf.o ../lib/main.o ../lib/sys.o\
	../machdep/startup.o ../machdep/boot.o ../machdep/l.o ../machdep/mch.o \
	../machdep/trap.o ../dev/nic.o ../dev/pci.o \
	../tasks/kernel.o ../lib/irq.o

# targets

build: $(IMAGE)

install: build
	cp $(IMAGE) /tftpboot

snapshot.tar: clean
	cd ..; tar -cvf build/snapshot.tar *;

snapshot: snapshot.tar
	mount /dev/fd0a;
	cp snapshot.tar /floppy
	umount /dev/fd0a;

$(IMAGE): $(OBJS)
	$(LD) $(LDFLAGS) -o $(IMAGE)  $(OBJS)

all: install snapshot

clean:
	rm -f ../*/*.o
	rm -f $(IMAGE)
	rm -f snapshot.tar

# dependencies
# (some files need gcc, because it handles packed attribute correctly)

##../dev/pit.o:		../include/param.h ../dev/pit.c
##../machdep/startup.o:	../include/ia32.h ../machdep/startup.c
##	$(GCC) $(CFLAGS) -c -o ../machdep/startup.o ../machdep/startup.c
##../machdep/boot.o:	../machdep/boot.c
##	$(GCC) $(CFLAGS) -c -o ../machdep/boot.o ../machdep/boot.c
