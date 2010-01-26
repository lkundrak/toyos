#include <lib.h>

#define	PIC1_PORT1	0x20
#define	PIC1_PORT2	0x21
#define	PIC2_PORT1	0xA0
#define	PIC2_PORT2	0xA1

/*
 * set up intel 8259/8259A pic controllers
 */

int irq_mask;

void
picmask ()
{
	outb (PIC1_PORT2, ~irq_mask & 0xff);		/* OCW1: irq mask */
	outb (PIC2_PORT2, (~irq_mask >> 8) & 0xff);	/* OCW1: irq mask */
}

void
picstart ()
{
	/*
	 * Master PIC
	 */

	outb (PIC1_PORT1, 0x11);	/* ICW1 */
	outb (PIC1_PORT2, 32);		/* ICW2: route to INTs 32-39 */
	outb (PIC1_PORT2, 0x04);	/* ICW3: Slave at IRQ 2 */
	outb (PIC1_PORT2, 0x01);	/* ICW4 80x86 mode */

	/*
	 * Slave PIC
	 */

	outb (PIC2_PORT1, 0x11);	/* ICW1 */
	outb (PIC2_PORT2, 40);		/* ICW2: route to INTs 40-47 */
	outb (PIC2_PORT2, 0x02);	/* ICW3: I am at master's IRQ 2 */
	outb (PIC2_PORT2, 0x01);	/* ICW4: 80x86 mode */
	irq_mask = (0x1 << 2);		/* enabling cascade */

	picmask ();
}
