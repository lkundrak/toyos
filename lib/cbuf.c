static char rcsid[]="$Id: cbuf.c,v 1.1.1.1 2004/11/21 17:01:59 lkundrak Exp $";

/*
 * Character buffers system
 */
 
#include <param.h>
#include <types.h>

struct cbucket {
	struct cbucket *c_next;
	char c_data[CSIZE];
};

struct cbucket cpool[CBUFS];
struct cbucket *cfreelist;
 
cfree (buck)
	struct cbucket *buck;
{
	buck->c_next = cfreelist;
	cfreelist = buck;
}

cinit ()
{
	int i = CBUFS;
	
	while (i)
		cfree (cpool[--i]);
}

dumpfree ()
{
	struct cbucket *b = cfreelist;

	while (b) {
		printf ("Free bucket at 0x%x\n", b);
		b = b->c_next;
	}
}
