	.file	"try.c"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	1
	.globl	fun
	.type	fun, @function
fun:
	mv	a5,a0
	mv	a0,a1
	bne	a5,zero,.L2
	mv	a0,a5
.L2:
	ret
	.size	fun, .-fun
	.align	1
	.globl	main
	.type	main, @function
main:
	li	a0,0
	ret
	.size	main, .-main
	.ident	"GCC: (SiFive GCC 10.1.0-2020.08.2) 10.1.0"
