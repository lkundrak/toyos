static char rcsid[]="$Id: sys.c,v 1.1.1.1 2004/11/21 17:01:59 lkundrak Exp $";

/*
 * I got me some bad news for you, Sunshine.
 */

panic (reason)
	char *reason;
{
	printf ("Panic: %s,\n", reason);
	halt ();
}

halt ()
{
	printf ("Kernel has halted.\n");
	printf ("Press ESC key to reboot.\n");
	cli ();
	while (inb (0x60) != 1);
	reboot ();
}
