#include <lib.h>

/*
 * intel 8253/8254 programmable interval timer
 */

#include <param.h>

#define PIT_CTL		0x43
#define PIT_CNL0	0x40

void
pitintr()
{
	yield ();
}

void
pitstart ()
{
	int speed;
	speed = 1193182L / HZ;

	outb (PIT_CTL, 0x36);  		/* channel 0, LSB/MSB, mode 3, 16b */
	outb (PIT_CNL0, speed & 0xFF);
	outb (PIT_CNL0, speed >> 8);

	register_irq (0, pitintr);
}
