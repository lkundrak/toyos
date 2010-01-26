#include <tasks.h>
#include <ia32.h>
#include <lib.h>

struct task tasks[3];
char stack1[1024], stack2[1024], stack3[1024];
int curproc = 0;


extern char *vgaframe;
void kernel_task ();

void
text2 ()
{
	while (1)
		*vgaframe = '0'+curproc;
}

void
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

void
main ()
{
	printf ("\nkernel built at "__TIME__", "__DATE__"\n");

	startup ();
	picstart ();
	pitstart ();

	tasks[0].context.eip = (int)kernel_task;
	tasks[0].context.esp = (int)stack1 + 1024;
	tasks[0].context.eflags = IF;

	tasks[1].context.eip = (int)text2;
	tasks[1].context.esp = (int)stack2 + 1024;
	tasks[1].context.eflags = IF;

	tasks[2].context.eip = (int)text2;
	tasks[2].context.esp = (int)stack3 + 1024;
	tasks[2].context.eflags = IF;

	printf ("Switching to kernel task.\n");
	resume (&tasks[0].context);

	panic ("[EOK]");
}
