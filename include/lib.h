/* CPU related */
void cli ();
void sti ();
int eflags ();
void load_gdt (void *);
void load_idt (void *);

/* Bus I/O */
char inb (short);
int inl (short);
char outb (short, char);
int outl (short, int);

/* Device initialization */
void pciinit ();
void kbstart ();
void nicstart ();
void picstart ();
void pitstart ();

/* Interrupt handling */
void picmask ();
void register_irq (int, void());

/* Task switching */
void resume (void *);
int save (void *);
void yield ();

/* Utility functions */
void startup ();
void panic (char *);
void reboot ();
void printf (char *, ...);
void putchar (char);
