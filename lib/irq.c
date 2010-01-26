#include <lib.h>

extern int irq_mask;

struct {
	void (*func) ();
	int *data;
} irq_handlers[16];

void
register_irq (irq, func)
	void (*func) ();
{
	irq_handlers[irq].func = func;
	irq_mask |= (0x1 << irq);

	picmask ();
}

void
hw_irq (irq)
{
	if (irq_handlers[irq].func)
		(*irq_handlers[irq].func) (irq);
	else {
		printf ("Interrupt at line %u: ", irq);
		panic ("No IRQ handler installed");
	}
}

