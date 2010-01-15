static char rcsid[]="$Id: main.c,v 1.4 2004/11/21 19:22:46 lkundrak Exp $";

#include <tasks.h>
#include <ia32.h>

struct task tasks[3];
char stack1[1024], stack2[1024], stack3[1024];
int curproc = 0;


extern	char *vgaframe;
extern	kernel_task ();

text2 ()
{
	while (1)
		*vgaframe = '0'+curproc;
}

yield ()
{
	if (save (&tasks[curproc].context))
		return;
	
	if (++curproc == 3)
		curproc = 0;

	resume (&tasks[curproc].context);
}

/*
 * This code is reached from asm routine start (in mch.s)
 */

main ()
{
	printf ("\nkernel built at "__TIME__", "__DATE__"\n");

	startup ();
	picstart ();
	pitstart ();
	
	tasks[0].context.eip = kernel_task;
	tasks[0].context.esp = stack1 + 1024;
	tasks[0].context.eflags = IF;

	tasks[1].context.eip = text2;
	tasks[1].context.esp = stack2 + 1024;
	tasks[1].context.eflags = IF;

	tasks[2].context.eip = text2;
	tasks[2].context.esp = stack3 + 1024;
	tasks[2].context.eflags = IF;

	printf ("Switching to kernel task.\n");
	resume (&tasks[0].context);

	panic ("[EOK]");
}
