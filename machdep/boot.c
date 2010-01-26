/*
 * Multiboot header
 * link.x: .multiboot_header is at the beginning of the core (1MB)
 */

#define MBF_NONE	0x00000000

#define MB_MAGIC	0x1badb002
#define MB_FLAGS	MBF_NONE
#define MB_CHECKSUM	(0 - (MB_MAGIC + MB_FLAGS))


struct {
	int	magic;
	int	flags;
	int	checksum;
} __attribute__ ((packed))
multiboot_header __attribute__ ((section (".multiboot_header"))) =
{
	.magic =	MB_MAGIC,
	.flags =	MB_FLAGS,
	.checksum =	MB_CHECKSUM
};

/*
 * Multiboot info structure
 * bootloader places it in low 640K, so startup routine in machdep.c
 * erases it. (todo: we relocate it, or use before erasing)
 */

char *multiboot_info;	/* ...char :-| */
