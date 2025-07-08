	.file	"race_condition.c"
	.text
	.globl	mail
	.bss
	.align 4
mail:
	.space 4
	.globl	mutex
	.align 8
mutex:
	.space 8
	.text
	.globl	routine
	.def	routine;	.scl	2;	.type	32;	.endef
	.seh_proc	routine
routine:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L2
.L3:
	movl	mail(%rip), %eax
	addl	$1, %eax
	movl	%eax, mail(%rip)
	addl	$1, -4(%rbp)
.L2:
	cmpl	$999999, -4(%rbp)
	jle	.L3
	movl	$0, %eax
	addq	$16, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC0:
	.ascii "Failed to create thread 0\0"
.LC1:
	.ascii "Failed to create thread 1\0"
.LC2:
	.ascii "Failed to join thread 0\0"
.LC3:
	.ascii "Failed to join thread 1\0"
.LC4:
	.ascii "Final value of mail: %d\12\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	call	__main
	leaq	-16(%rbp), %rax
	movl	$0, %r9d
	leaq	routine(%rip), %r8
	movl	$0, %edx
	movq	%rax, %rcx
	call	pthread_create
	testl	%eax, %eax
	je	.L6
	leaq	.LC0(%rip), %rax
	movq	%rax, %rcx
	call	perror
	movl	$1, %ecx
	call	exit
.L6:
	leaq	-16(%rbp), %rax
	addq	$8, %rax
	movl	$0, %r9d
	leaq	routine(%rip), %r8
	movl	$0, %edx
	movq	%rax, %rcx
	call	pthread_create
	testl	%eax, %eax
	je	.L7
	leaq	.LC1(%rip), %rax
	movq	%rax, %rcx
	call	perror
	movl	$1, %ecx
	call	exit
.L7:
	movq	-16(%rbp), %rax
	movl	$0, %edx
	movq	%rax, %rcx
	call	pthread_join
	testl	%eax, %eax
	je	.L8
	leaq	.LC2(%rip), %rax
	movq	%rax, %rcx
	call	perror
	movl	$1, %ecx
	call	exit
.L8:
	movq	-8(%rbp), %rax
	movl	$0, %edx
	movq	%rax, %rcx
	call	pthread_join
	testl	%eax, %eax
	je	.L9
	leaq	.LC3(%rip), %rax
	movq	%rax, %rcx
	call	perror
	movl	$1, %ecx
	call	exit
.L9:
	movl	mail(%rip), %eax
	movl	%eax, %edx
	leaq	.LC4(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movl	$0, %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev2, Built by MSYS2 project) 14.2.0"
	.def	pthread_create;	.scl	2;	.type	32;	.endef
	.def	perror;	.scl	2;	.type	32;	.endef
	.def	exit;	.scl	2;	.type	32;	.endef
	.def	pthread_join;	.scl	2;	.type	32;	.endef
	.def	printf;	.scl	2;	.type	32;	.endef
