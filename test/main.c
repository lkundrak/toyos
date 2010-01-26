static char rcsid[]="$Id: main.c,v 1.1.1.1 2004/11/21 17:01:59 lkundrak Exp $";

/*
 * FCUK
 */

#include "../include/types.h"

struct cbuf chars;
extern cpool[];

main ()
{
	int i = 0;

	cinit ();
	dumpfree ();
	while (cput(i++, &chars));
	printf ("[[%i]]", i);
}
