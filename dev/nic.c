#include <lib.h>

#define BASE	0xff80
#define IRQ	11

void
nicaddr ()
{
	int i;
	char eth_id[6];

	outb (BASE + 0x00, 0x21); /* cr -> stop & page 0 */
	outb (BASE + 0x0e, 0x59); /* dcr */
	outb (BASE + 0x0a, 0x06); /* rbcr0 */
	outb (BASE + 0x0b, 0x00); /* rbcr1 */
	outb (BASE + 0x08, 0x00); /* rsar0 */
	outb (BASE + 0x09, 0x00); /* rsar1 */
	outb (BASE + 0x00, 0x09); /* cr -> stop & remote read & page 0 */

	printf ("nic: Ethernet ID: ");
	for (i = 0; i < 6; i++)
		printf ("%x:", eth_id[i] = inb (BASE+0x10));
	printf ("\b\n");

	outb (BASE + 0x00, 0x61); /* cr -> stop & page 2 */
	for (i = 0; i < 6; i++)
		outb (BASE + 0x01 + i, eth_id[i]);

	outb (BASE + 0x00, 0x21); /* cr -> start & page 0 */
}

void
nicinit ()
{
	outb (BASE + 0x00, 0x21); /* cr -> stop & page 0 */
	outb (BASE + 0x0e, 0x59); /* dcr */
	outb (BASE + 0x0a, 0x00);
	outb (BASE + 0x0b, 0x00);
	outb (BASE + 0x0c, 0x1e); /* rcr */
	outb (BASE + 0x04, 0x20);
	outb (BASE + 0x0d, 0x02); /* tcr -> +loopback */
	outb (BASE + 0x01, 0x26);
	outb (BASE + 0x03, 0x40);
	outb (BASE + 0x02, 0x40);

	outb (BASE + 0x00, 0x61); /* cr -> stop & page 1 */
	outb (BASE + 0x07, 0x26);

	outb (BASE + 0x00, 0x22); /* cr -> start & page 0 */
	outb (BASE + 0x0f, 0xff); /* imr */	/* int occurs */
	outb (BASE + 0x0d, 0x00); /* tcr -> -loopback */
}

void
nicintr ()
{

	outb (BASE + 0x00, 0x22); /* cr -> stop & page 0 */

	printf ("nic: IRQ. ISR: 0x%x, RSR: 0x%x, BNRY: 0x%x, ",
		inb (BASE + 0x07),
		inb (BASE + 0x0c),
		inb (BASE + 0x03)
	);

	outb (BASE + 0x00, 0x62); /* cr -> start & page 1 */
	printf ("CURR: 0x%x\n", inb (BASE + 0x07));

	outb (BASE + 0x00, 0x22); /* cr -> start & page 0 */
	outb (BASE + 0x07, 0xff); /* isr */
}

void
nicstart ()
{
	register_irq (IRQ, nicintr);
	nicinit ();
	nicaddr ();
}

