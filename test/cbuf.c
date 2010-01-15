static char rcsid[]="$Id: cbuf.c,v 1.1.1.1 2004/11/21 17:01:59 lkundrak Exp $";

/*
 * Character buffers system
 *
 * Character buffers are LIFOs, represented by
 * cbuf structues. Each cbuf structure is a header
 * representing zero or more one-way linked cbucket
 * structs. Cbuckets, that are not in use are kept
 * linked in cfreelist list. If needed, cput () picks
 * new buffer and cget () returns one if possible.
 */
 
#include "../include/param.h"
#include "../include/types.h"

/*
 * this macro is used to determine, whether address
 * is an address of char in c_data array of some bucket
 * in the bucket pool
 */
#define	cisdata(a)	((((int)a - (int)&cpool[0]) % sizeof(struct cbucket)) >= 4)
/*
 * Which bucket contains data with this address
 */
#define	cbuckno(a)	(((int)a - (int)&cpool[0]) / sizeof(struct cbucket))

struct cbucket {
	struct cbucket *c_next;
	char c_data[CSIZE];
};

struct cbucket cpool[CBUFS];
struct cbucket *cfreelist;


char
cget (cb)
	struct cbuf *cb;
{
	char c;
	struct cbucket *buck;
	
	if (cb->c_count-- == 0)
		return -1;
	buck = &cpool[cbuckno(cb->c_first)];
	c = *(cb->c_first++);

	if (!cisdata(cb->c_first)) {
		if (buck->c_next)
			cb->c_first = buck->c_next->c_data;
		else
			cb->c_first = cb->c_last = 0;
		cfree (buck);
	}
	
	return c;
}

cput (c, cb)
	char c;
	struct cbuf *cb;
{
	struct cbucket *buck;

	if (!cisdata(cb->c_last++)) {
		printf ("need new bucket\n");
		if (buck = cpick ())
			cb->c_last = buck->c_data;
		else
			return 0;
		printf ("got new bucket at 0x%x\n", buck);
	} 


	if (cb->c_count++ == 0) 
		cb->c_first = cb->c_last;

	*(cb->c_last) = c;

	return 1;
}




/*
 * Put all buckets into list of free ones
 * called by startup ()
 */

cinit ()
{
	int i = CBUFS;
	
	while (i)
		cfree (&cpool[--i]);
}

/* following is only called internally within this file */
 
/*
 * Put bucket into list of free ones
 */

cfree (buck)
	struct cbucket *buck;
{
	buck->c_next = cfreelist;
	cfreelist = buck;
}

/*
 * Pick free buffer if any
 */

struct cbucket
*cpick ()
{
	struct cbucket *retval;
	
	printf ("cfreelist = 0x%x\n", cfreelist);
	dumpfree ();
	if (!cfreelist)
		return 0;	/* no free buckets */
	retval = cfreelist;
	cfreelist = cfreelist->c_next;
	dumpfree ();
	printf ("cfreelist = 0x%x\n\n", cfreelist);
	

	return retval;
}












dumpfree ()
{
	struct cbucket *b = cfreelist;

	printf ("{\n");
	while (b) {
		printf ("	Free bucket at 0x%x\n", b);
		b = b->c_next;
	}
	printf ("}\n");
}
