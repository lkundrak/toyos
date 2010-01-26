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

$(IMAGE): $(OBJS)
	$(LD) $(LDFLAGS) -o $(IMAGE)  $(OBJS)

all: install snapshot

clean:
	rm -f ../*/*.o
	rm -f $(IMAGE)
	rm -f snapshot.tar

run: $(IMAGE)
	qemu -net nic,model=ne2k_pci -net user,tftp=. -fda grub.ok
