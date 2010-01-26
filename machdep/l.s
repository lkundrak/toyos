/*
 * Wrappers for c trap/interrupt handlers
 */

.text

.macro	ent a
	.globl	trap\a
	trap\a:
		pushl	$0	/* no error code */
		pushl	$\a
		push	%esp
		call	stkdump
		pop	%esp
		pusha
		call	trap
		popl	%eax
		popl	%eax
		popa
		iret
.endm

.macro	ent_ec a
	.globl	trap\a
	trap\a:
		push	%esp
		call	stkdump
		pop	%esp
		pusha
		pushl	$\a
		call	trap
		popl	%eax
		popl	%eax	/* remove error code */
		popa
		iret
.endm

.macro	irq a
	.globl	irq\a
	irq\a:
		pusha
		movw	$0x20, %dx
		movb	$0x20, %al
		out	%al, %dx
/*		movw	$0xA0, %dx*/
/*		out	%al, %dx */
		push	$\a
		call	hw_irq
		pop	%eax
		popa
		iret
.endm

/*
 * exceptions internal to cpu
 */

ent	0
ent	1
ent	2
ent	3
ent	4
ent	5
ent	6
ent	7
ent_ec	8
ent	9
ent_ec	10
ent_ec	11
ent_ec	12
ent_ec	13
ent_ec	14
ent	15
ent	16
ent	17
ent	18

/*
 * interrupts external to cpu
 * (from i8259As)
 */

irq	0
irq	1
irq	2
irq	3
irq	4
irq	5
irq	6
irq	7
irq	8
irq	9
irq	10
irq	11
irq	12
irq	13
irq	14
irq	15

/*
 * system call trap
 */

ent	128

