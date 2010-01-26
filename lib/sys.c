#include <lib.h>

void
halt ()
{
	printf ("Kernel has halted.\n");
	printf ("Press ESC key to reboot.\n");
	cli ();
	while (inb (0x60) != 1);
	reboot ();
}

/*
 * I got me some bad news for you, Sunshine.
 */

void
panic (reason)
	char *reason;
{
	printf ("Panic: %s,\n", reason);
	halt ();
}
