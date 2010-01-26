/*
 * Routines handling PC terminal's keyboard
 */

/* todo: cursor keys,.... ansi escapes? */

#include <ia32.h>
#include <lib.h>

#define	IRQ		1

#define KBD_DATA	0x60
#define	KBD_CMD		0x64
#define KBD_STAT	0x64

#define K_CTRL		0x1D
#define K_RSHIFT	0x2A
#define K_LSHIFT	0x36
#define K_ALT		0x38
#define K_CAPS		0x3A
#define K_NUM		0x45
#define K_SCROLL	0x46
#define K_DEL		0x53

#define K_GRAY		0xe0

#define K_PRTSCR	0x37

#define	K_PAUSE		0xe1
#define K_BREAK		0x80

#define F(n)		('0'+n)
#define HOME		1
#define END		1
#define PGUP		1
#define PGDN		1
#define UP		1
#define DOWN		1
#define LEFT		1
#define RIGHT		1
#define INS		1
#define DEL		1

char	ctrl, alt, shift, altgr, caps, num, scroll;

char	convtab[K_BREAK] = {	/* conversion between scancodes and ascii */
		0,	0x1b,	'1',	'2',	'3',	'4',	'5',	'6',
		'7',	'8',	'9',	'0',	'-',	'=',	'\b',	'\t',
		'q',	'w',	'e',	'r',	't',	'y',	'u',	'i',
		'o',	'p',	'[',	']',	'\n',	0,	'a',	's',
		'd',	'f',	'g',	'h',	'j',	'k',	'l',	';',
		'\'',	'`',	0,	'\\',	'z',	'x',	'c',	'v',
		'b',	'n',	'm',	',',	'.',	'/',	0,	'*',
		0,	' ',	0,	F(1),	F(2),	F(3),	F(4),	F(5),
		F(6),	F(7),	F(8),	F(9),	F(10),	0,	0,	HOME,
		UP,	PGUP,	'-',	LEFT,	'5',	RIGHT,	'+',	END,
		DOWN,	PGDN,	INS,	DEL,	F(11),	F(12)
	};

char	convatab[K_BREAK] = {	/* alt-gr keys */
		0,	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,	0,	0,
		'@'
	};

char	convctab[K_BREAK] = {	/* capitals */
		0,	0,	'!',	'@',	'#',	'$',	'%',	'^',
		'&',	'*',	'(',	')',	'_',	'+',	0,	0,
		'Q',	'W',	'E',	'R',	'T',	'Y',	'U',	'I',
		'O',	'P',	'{',	'}',	'\n',	0,	'A',	'S',
		'D',	'F',	'G',	'H',	'J',	'K',	'L',	':',
		'|',	'~',	0,	'|',	'Z',	'X',	'C',	'V',
		'B',	'N',	'M',	'<',	'>',	'?'
	};

char	convntab[K_BREAK] = {	/* numeric keypad with numlock pressed */
		0,	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,	0,	'7',
		'8',	'9',	'-',	'4',	'5',	'6',	'+',	'1',
		'2',	'3',	'0',	'.'
	};

void
kbready ()
{
	while (inb (KBD_STAT) & 0x2);	/* beware busy waiting! */
}

void
kbleds ()
{
	kbready ();
	outb (KBD_DATA, 0xed);
	kbready ();
	outb (KBD_DATA, (scroll ? 1 : 0) | (num ? 2 : 0) | (caps ? 4 : 0));
}

int
kbconv (sc)
{
	if (sc>K_BREAK)
		return 0;

	if (caps && convctab[sc] && !shift)
		return convctab[sc];

	if (num && convntab[sc] && !shift)
		return convntab[sc];

	if (altgr && convatab[sc])
		return convatab[sc];

	if (shift && convctab[sc] && !caps)
		return convctab[sc];

	if (shift && convntab[sc] && !num)
		return convntab[sc];

	return convtab[sc];
}

void
reboot ()
{
	printf ("Rebooting...");
	kbready ();
	while (1)
		outb(KBD_CMD, 0xFE);
	/* anything smarter than trying forever in case of fault? */
}

void
kbintr ()
{
	int code;
	char gray = 0;

	code = inb (KBD_DATA);
	if (code == K_GRAY) {
		gray = 1;
		do {			/* polling... just a "quick hack" */
			code = inb (0x60);
		} while (code == K_GRAY);
	}

	switch (code) {
		case 0:		panic ("remove the apple from the keyboard");
		/* make codes */
		case K_LSHIFT:
		case K_RSHIFT:	shift = 1; break;
		case K_CTRL:	ctrl = 1; break;
		case K_ALT:	alt = 1; altgr |= gray; break;
		case K_CAPS:	caps = !caps; kbleds (); break;
		case K_NUM:	if (ctrl) 	/* pause */
					panic ("Daj si pauzu. Daj si kitkat.");
				num = !num; kbleds ();	break;
		case K_SCROLL:	scroll = !scroll; kbleds (); break;
		case K_DEL:	if (ctrl && alt) reboot ();
		/* break codes */
		case K_LSHIFT+K_BREAK:
		case K_RSHIFT+K_BREAK:	shift = 0; break;
		case K_CTRL+K_BREAK:	ctrl = 0; break;
		case K_ALT+K_BREAK:	altgr &= !gray; alt = 0; break;
	}

	if (kbconv (code))	/* has ascii representation */
		putchar (kbconv (code));
}

void
kbstart ()
{
	printf ("Keyboard and keyboard controller driver\n");
	kbleds ();
	register_irq (IRQ, kbintr);
}
