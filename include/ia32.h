/*
 * ia32 dependent
 */

/* descriptor types. others aren't used out there */
#define	IA32_INT	14	/* 32bit Interrupt Gate	[01110] */
#define	IA32_TRAP	15	/* 32bit Trap Gate	[01111] */
#define	IA32_DATA	18	/* 32bit Read/Write Mem	[10010] */
#define	IA32_CODE	26	/* 32bit Exec/Read Mem	[11010] */

struct gate
{
	unsigned g_offset_lo:16;
	unsigned g_selector:16;
	unsigned g_xx:8;
	unsigned g_type:5;
	unsigned g_dpl:2;
	unsigned g_present:1;
	unsigned g_offset_hi:16;
} __attribute__ ((packed));

struct segment
{
	unsigned s_limit_lo:16;
	unsigned s_base_lo:24;
	unsigned s_type:5;
	unsigned s_dpl:2;
	unsigned s_present:1;
	unsigned s_limit_hi:4;
	unsigned s_xx:2;
	unsigned s_b32:1;
	unsigned s_pagegran:1;
	unsigned s_base_hi:8;
} __attribute__ ((packed));

struct region				/* used by lidt and gidt */
{
	unsigned r_limit:16;
	unsigned r_base:32;
} __attribute__ ((packed));


/* eflags register */
#define	IF	0x00200		/* Interrupt Flag */
