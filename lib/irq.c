static char rcsid[]="$Id: irq.c,v 1.1 2004/12/05 15:01:44 lkundrak Exp $";

extern int irq_mask;

struct {
	int (*func) ();
	int *data;
} irq_handlers[16];

register_irq (irq, func)
	int (*func) ();
{
	irq_handlers[irq].func = func;
	irq_mask |= (0x1 << irq);

	picmask ();
}

int hw_irq (irq)
{
	if (irq_handlers[irq].func)
		(*irq_handlers[irq].func) (irq);
	else {
		printf ("Interrupt at line %u: ", irq);
		panic ("No IRQ handler installed");
	}
}

