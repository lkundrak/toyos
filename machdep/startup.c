static char rcsid[]="$Id: startup.c,v 1.1.1.1 2004/11/21 17:01:59 lkundrak Exp $";

#include <ia32.h>

extern int bss_start, bss_end;	/* todo: put in .h file. seg.h? */
struct gate idt[256];
struct segment gdt[3];

extern	trap0 (),
	trap1 (),
	trap2 (),
	trap3 (),
	trap4 (),
	trap5 (),
	trap6 (),
	trap7 (),
	trap8 (),
	trap9 (),
	trap10 (),
	trap11 (),
	trap12 (),
	trap13 (),
	trap14 (),
	trap15 (),
	trap16 (),
	trap17 (),
	trap18 ();
extern	irq0 (),
	irq1 ();
	irq2 ();
	irq3 ();
	irq4 ();
	irq5 ();
	irq6 ();
	irq7 ();
	irq8 ();
	irq9 ();
	irq10 ();
	irq11 ();
	irq12 ();
	irq13 ();
	irq14 ();
	irq15 ();
extern	trap128 ();

/*
 * Machine-dependent startup code
 */

startup()
{
	register *i;
	struct region r;

	/*
	 * zero all of bss and low 640K
	 */

	/* todo: relocate useful data from low memory (BDA, Multiboot info,...*/

	for (i = &bss_start; i < &bss_end; i++)
		*i=0;
	for (i = 0; i < (int *)(640*0x400); i++)
		*i=0;

	/*
	 * Set up segment descriptors in global descriptor table
	 */

	/* 0th descriptor is blank, because gdt resides in bss */
	setsegment (&gdt[1], 0x0, 0xfffff, IA32_DATA, 0, 1, 1);
	setsegment (&gdt[2], 0x0, 0xfffff, IA32_CODE, 0, 1, 1);

	r.r_base = (int)gdt;
	r.r_limit = 0x17;

	load_gdt (&r);

	/*
	 * Set up interrupt and trap handler descriptors in idt
	 */

	/* todo: some assembler routine/macros should do this */

	setgate (&idt[0], trap0, 0x10, IA32_TRAP, 0);
	setgate (&idt[1], trap1, 0x10, IA32_TRAP, 0);
	setgate (&idt[2], trap2, 0x10, IA32_TRAP, 0);
	setgate (&idt[3], trap3, 0x10, IA32_TRAP, 0);
	setgate (&idt[4], trap4, 0x10, IA32_TRAP, 0);
	setgate (&idt[5], trap5, 0x10, IA32_TRAP, 0);
	setgate (&idt[6], trap6, 0x10, IA32_TRAP, 0);
	setgate (&idt[7], trap7, 0x10, IA32_TRAP, 0);
	setgate (&idt[8], trap8, 0x10, IA32_TRAP, 0);
	setgate (&idt[9], trap9, 0x10, IA32_TRAP, 0);
	setgate (&idt[10], trap10, 0x10, IA32_TRAP, 0);
	setgate (&idt[11], trap11, 0x10, IA32_TRAP, 0);
	setgate (&idt[12], trap12, 0x10, IA32_TRAP, 0);
	setgate (&idt[13], trap13, 0x10, IA32_TRAP, 0);
	setgate (&idt[14], trap14, 0x10, IA32_TRAP, 0);
	setgate (&idt[15], trap15, 0x10, IA32_TRAP, 0);
	setgate (&idt[16], trap16, 0x10, IA32_TRAP, 0);
	setgate (&idt[17], trap17, 0x10, IA32_TRAP, 0);
	setgate (&idt[18], trap18, 0x10, IA32_TRAP, 0);

	setgate (&idt[32], irq0, 0x10, IA32_INT, 0);
	setgate (&idt[33], irq1, 0x10, IA32_INT, 0);
	setgate (&idt[34], irq2, 0x10, IA32_INT, 0);
	setgate (&idt[35], irq3, 0x10, IA32_INT, 0);
	setgate (&idt[36], irq4, 0x10, IA32_INT, 0);
	setgate (&idt[37], irq5, 0x10, IA32_INT, 0);
	setgate (&idt[38], irq6, 0x10, IA32_INT, 0);
	setgate (&idt[39], irq7, 0x10, IA32_INT, 0);
	setgate (&idt[40], irq8, 0x10, IA32_INT, 0);
	setgate (&idt[41], irq9, 0x10, IA32_INT, 0);
	setgate (&idt[42], irq10, 0x10, IA32_INT, 0);
	setgate (&idt[43], irq11, 0x10, IA32_INT, 0);
	setgate (&idt[44], irq12, 0x10, IA32_INT, 0);
	setgate (&idt[45], irq13, 0x10, IA32_INT, 0);
	setgate (&idt[46], irq14, 0x10, IA32_INT, 0);
	setgate (&idt[47], irq15, 0x10, IA32_INT, 0);

	setgate (&idt[128], trap128, 0x10, IA32_TRAP, 0);

	r.r_base = (int)idt;
	r.r_limit = 0x7ff;

	load_idt (&r);
}



/*
 * misc.
 */

setsegment (segment, base, limit, type, dpl, b32, pagegran)
	struct segment *segment;
{
	segment->s_limit_lo	= limit & 0xffff;
	segment->s_base_lo	= base & 0xffffff;
	segment->s_type		= type & 0x1f;
	segment->s_dpl		= dpl & 0x3;
	segment->s_present	= 1;
	segment->s_limit_hi	= (limit >> 16) & 0xf;
	segment->s_xx		= 0;
	segment->s_b32		= b32 & 0x1;
	segment->s_pagegran	= pagegran & 0x1;
	segment->s_base_hi	= (base >> 24) & 0xff;
}

setgate (gate, offset, selector, type, dpl)
	struct gate *gate;
{
	gate->g_offset_lo	= offset & 0xffff;
	gate->g_selector	= selector & 0xffff;
	gate->g_xx		= 0;
	gate->g_type		= type & 0x1f;
	gate->g_dpl		= dpl & 0x3;
	gate->g_present		= 1;
	gate->g_offset_hi	= (offset >> 16) & 0xffff;
}
