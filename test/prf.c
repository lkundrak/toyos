static char rcsid[]="$Id: prf.c,v 1.1.1.1 2004/11/21 17:01:59 lkundrak Exp $";

/*
 * see printf(3) manual in your libc documentation.
 * this version just implements small subset of standard printf's
 * abilities, just to satisfy kernel's needs, as you can see...
 */

printk (format, args)
	char *format;
{
	int *argp;
	char c;

	argp = &args;
	while (c = *format++)
		if (c == '%')
			switch (c = *format++) {
				case 'u':
				case 'd':
				case 'i': putn (*argp++, 10); break;
				case 'x': putn (*argp++, 16); break;
				case 'o': putn (*argp++, 8); break;
				case 's': puts (*argp++); break;
				case 'c': putchar (*argp++); break;
				case '%': putchar ('%'); break;
				case '\0': return;
			}
		else
			putchar (c);
}

/*
 * selfexplainatory ones, i think
 */

puts (string)
	char *string;
{
	while (*string)
		putchar (*string++);
}

putn (number, base)
	unsigned number;
{
	char *digits = "0123456789abcdef";

	printf ("putn (%u, %u)\n", number, base);

	if (number/base)	/* not a leftmost digit */
		putn (number/base, base);
	putchar (digits[number%base]);
}


fcuk (cis)
{
	printf ("[ %u ]\n", cis);
}

main ()
{

	unsigned n,b;

//	printf ("(((%u)))\n", 4008636142/10);
	printk ("(((%u)))\n", 4008636142);
}
