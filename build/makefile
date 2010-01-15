GCC	= bcc32
CC	= bcc32

CFLAGS	= -I../include
LDFLAGS	= -Tlink.x
IMAGE	= windows95

OBJS	= ../dev/kbd.obj ../dev/vga.obj ../dev/pit.obj ../dev/pic.obj \
	../lib/prf.obj ../lib/main.obj ../lib/sys.obj\
	../machdep/startup.obj ../machdep/boot.obj ../machdep/l.obj ../machdep/mch.obj \
	../machdep/trap.obj ../dev/nic.obj ../dev/pci.obj \
	../tasks/kernel.obj ../lib/irq.obj


# targets

build: $(IMAGE)
	@echo Build complete.	

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
	rm -f ../*/*.obj
	rm -f $(IMAGE)
	rm -f snapshot.tar

# dependencies
# (some files need gcc, because it handles packed attribute correctly)

##../dev/pit.obj:		../include/param.h ../dev/pit.c
##../machdep/startup.obj:	../include/ia32.h ../machdep/startup.c
##	$(GCC) $(CFLAGS) -c -o ../machdep/startup.obj ../machdep/startup.c
##../machdep/boot.obj:	../machdep/boot.c
##	$(GCC) $(CFLAGS) -c -o ../machdep/boot.obj ../machdep/boot.c
