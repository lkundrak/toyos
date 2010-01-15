static char rcsid[]="$Id: main.c,v 1.3 2004/11/21 17:35:21 lkundrak Exp $";

/*
 * first running task
 * will run driver tasks and init, creator of all user tasks
 */

kernel_task ()
{
	sti ();		/* enabling interrupts. task can be preempted */

	pciinit ();
	printf ("Starting device drivers:\n");
	nicstart ();
	kbstart ();

	while (1);
}

