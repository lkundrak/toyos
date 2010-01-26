static char rcsid[]="$Id: alloc.c,v 1.1.1.1 2004/11/21 17:01:59 lkundrak Exp $";

/*
 * memory allocation system
 * see malloc(3) manual
 */

char *
malloc (size)
{
}

calloc ()
{
	char *i, *end;

	begin = malloc (size);
	end = i + size;
	while (i < end)
		*i++ = '\0';
}
