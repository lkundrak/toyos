static char rcsid[]="$Id: pci.c,v 1.3 2004/12/05 16:35:10 lkundrak Exp $";

#define	PCI_ADDR	0xcf8
#define	PCI_DATA	0xcfc

pcireadl (bus, dev, func, off)
{
	outl (PCI_ADDR,
		1 << 31 |
		bus << 16 |
		dev << 11 |
		func << 8 |
		off << 2
	);
	return (inl (PCI_DATA));
}


pciinit ()
{
	int bus, dev;	/* bus, device */

	printf ("Scanning PCI bus...\n");
	
	for (bus = 0; bus < 0xff; bus++)
		for (dev = 0; dev < 0x20; dev++){
			int dev_vend;

			dev_vend = pcireadl (bus, dev, 0, 0);
			if (dev_vend != 0xffffffff) {
				printf (" * device 0x%x at 0x%u:0x%u\n",
					dev_vend,
					bus,
					dev);
			}
		}

	printf ("...done.\n");
}
