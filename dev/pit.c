static char rcsid[]="$Id: pit.c,v 1.1.1.1 2004/11/21 17:01:59 lkundrak Exp $";

/*
 * intel 8253/8254 programmable interval timer
 */

#include <param.h>

#define PIT_CTL		0x43
#define PIT_CNL0	0x40

pitintr()
{
	yield ();
}

pitstart ()
{
	int speed;
	speed = 1193182L / HZ;
	 
	outb (PIT_CTL, 0x36);  		/* channel 0, LSB/MSB, mode 3, 16b */
	outb (PIT_CNL0, speed & 0xFF);
	outb (PIT_CNL0, speed >> 8);     

	register_irq (0, pitintr);
}
