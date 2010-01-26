#include <lib.h>

/*
 * first running task
 * will run driver tasks and init, creator of all user tasks
 */

void
kernel_task ()
{
	sti ();		/* enabling interrupts. task can be preempted */

	pciinit ();
	printf ("Starting device drivers:\n");
	nicstart ();
	kbstart ();

	while (1);
}

