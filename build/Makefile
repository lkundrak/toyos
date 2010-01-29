CC	= gcc
GCC	= gcc

CFLAGS ?= -Wall -g
INCLUDES = -I../include
override CFLAGS += $(INCLUDES) -ffreestanding
override LDFLAGS = -Tlink.x

QEMUFLAGS = -M pc
override QEMUFLAGS += -net nic,model=ne2k_pci -net user,tftp=.
override QEMUFLAGS += -fda grub.ok

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
	qemu $(QEMUFLAGS)

gdb: $(IMAGE)
	gdb -ex 'symbol-file $(IMAGE)' \
		-ex 'target remote |exec qemu -gdb stdio $(QEMUFLAGS)'

depend:
	makedepend $(INCLUDES) ../*/*.c

# Autogenrated stuff below
# DO NOT DELETE THIS LINE -- make depend depends on it.

../dev/kbd.o: ../include/ia32.h ../include/lib.h
../dev/nic.o: ../include/lib.h
../dev/pci.o: ../include/lib.h
../dev/pic.o: ../include/lib.h
../dev/pit.o: ../include/lib.h ../include/param.h
../dev/vga.o: ../include/ia32.h ../include/lib.h
../lib/cbuf.o: ../include/param.h ../include/types.h
../lib/irq.o: ../include/lib.h
../lib/main.o: ../include/tasks.h ../include/ia32.h ../include/lib.h
../lib/prf.o: ../include/lib.h
../lib/sys.o: ../include/lib.h
../machdep/startup.o: ../include/ia32.h ../include/lib.h
../machdep/trap.o: ../include/lib.h
../tasks/kernel.o: ../include/lib.h
../test/cbuf.o: ../include/param.h ../include/types.h
../test/main.o: ../include/types.h
