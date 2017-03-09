	.file	1 "fibonacci.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=xx
	.module	nooddspreg
	.abicalls
	.text
	.align	2
	.globl	Fibonacci
	.set	nomips16
	.set	nomicromips
	.ent	Fibonacci
	.type	Fibonacci, @function
Fibonacci:
	.frame	$fp,48,$31		# vars= 8, regs= 3/0, args= 16, gp= 8
	.mask	0xc0010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-48
	sw	$31,44($sp)
	sw	$fp,40($sp)
	sw	$16,36($sp)
	move	$fp,$sp
	sw	$4,48($fp)
	lw	$2,48($fp)
	bne	$2,$0,$L2
	nop

	sw	$0,28($fp)
	b	$L3
	nop

$L2:
	lw	$3,48($fp)
	li	$2,1			# 0x1
	bne	$3,$2,$L4
	nop

	li	$2,1			# 0x1
	sw	$2,28($fp)
	b	$L3
	nop

$L4:
	lw	$2,48($fp)
	addiu	$2,$2,-1
	move	$4,$2
	.option	pic0
	jal	Fibonacci
	nop

	.option	pic2
	move	$16,$2
	lw	$2,48($fp)
	addiu	$2,$2,-2
	move	$4,$2
	.option	pic0
	jal	Fibonacci
	nop

	.option	pic2
	addu	$2,$16,$2
	sw	$2,28($fp)
$L3:
	lw	$2,28($fp)
	move	$sp,$fp
	lw	$31,44($sp)
	lw	$fp,40($sp)
	lw	$16,36($sp)
	addiu	$sp,$sp,48
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	Fibonacci
	.size	Fibonacci, .-Fibonacci
	.align	2
	.globl	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,40,$31		# vars= 8, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$fp,32($sp)
	move	$fp,$sp
	sw	$0,28($fp)
	li	$4,4			# 0x4
	.option	pic0
	jal	Fibonacci
	nop

	.option	pic2
	sw	$2,28($fp)
	lw	$2,28($fp)
	move	$sp,$fp
	lw	$31,36($sp)
	lw	$fp,32($sp)
	addiu	$sp,$sp,40
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.1) 5.4.0 20160609"
