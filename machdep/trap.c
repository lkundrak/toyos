#include <lib.h>

char *traps[]= {
	/* 0 */ "division by zero",
	/* 1 */ "debug exception",
	/* 2 */ "non-maskable interrupt (nmi)",
	/* 3 */ "breakpoint (int 3)",
	/* 4 */ "overflow (into with eflags[of] set)",
	/* 5 */ "bound exception (bound on out-of-bounds access)",
	/* 6 */ "invalid opcode",
	/* 7 */ "fpu not available",
	/* 8 */ "double fault",
	/* 9 */ "coprocessor segment overrun",
	/* 10 */ "invalid tss",
	/* 11 */ "segment not present",
	/* 12 */ "stack exception",
	/* 13 */ "general protection",
	/* 14 */ "page fault",
	/* 15 */ "reserved",
	/* 16 */ "floating point error",
	/* 17 */ "alignment check",
	/* 18 */ "machine check"
};
/*
trap (trapno, errcode, eip, cs, eflags)

{
	switch(trapno) {
		case 128:
			printf ("[SYSCALL]");
			break;

		case 8:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
			printf ("error code: %u\n", errcode);
		default:
			printf ("eflags = 0x%x\n", eflags);
			printf ("eip = 0x%x cs = 0x%x\n", eip, cs);
			if (trapno <= 18)
				panic (traps[trapno]);
			printf ("trap type %u\n", trapno);
			panic ("UNKNOWN TRAP");
	}
}
*/

int *i;

void
stkdump (esp)
	int *esp;
{
	i = esp;
	i--;
	printf ("Stack dump:\n");
	printf ("Address:\tData:\t\n");
	do {
		printf ("0x%x:\t0x%x\n", i, *i);
	} while (i++ < esp+5);
}

void
trap (stack)
{
	panic ("trap");
}
