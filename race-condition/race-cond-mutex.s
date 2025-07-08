	.file	"race-cond-mutex.c"
	.text
	.globl	mail
	.bss
	.align 4
mail:
	.space 4
	.globl	lock
	.align 4
lock:
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
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L2
.L3:
	leaq	mutex(%rip), %rax
	movq	%rax, %rcx
	call	pthread_mutex_lock
	movl	mail(%rip), %eax
	addl	$1, %eax
	movl	%eax, mail(%rip)
	leaq	mutex(%rip), %rax
	movq	%rax, %rcx
	call	pthread_mutex_unlock
	addl	$1, -4(%rbp)
.L2:
	cmpl	$999999, -4(%rbp)
	jle	.L3
	movl	$0, %eax
	addq	$48, %rsp
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
	subq	$64, %rsp
	.seh_stackalloc	64
	.seh_endprologue
	call	__main
	movl	$0, %edx
	leaq	mutex(%rip), %rax
	movq	%rax, %rcx
	call	pthread_mutex_init
	leaq	-32(%rbp), %rax
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
	leaq	-32(%rbp), %rax
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
	leaq	-32(%rbp), %rax
	addq	$16, %rax
	movl	$0, %r9d
	leaq	routine(%rip), %r8
	movl	$0, %edx
	movq	%rax, %rcx
	call	pthread_create
	testl	%eax, %eax
	je	.L8
	leaq	.LC0(%rip), %rax
	movq	%rax, %rcx
	call	perror
	movl	$1, %ecx
	call	exit
.L8:
	leaq	-32(%rbp), %rax
	addq	$24, %rax
	movl	$0, %r9d
	leaq	routine(%rip), %r8
	movl	$0, %edx
	movq	%rax, %rcx
	call	pthread_create
	testl	%eax, %eax
	je	.L9
	leaq	.LC1(%rip), %rax
	movq	%rax, %rcx
	call	perror
	movl	$1, %ecx
	call	exit
.L9:
	movq	-32(%rbp), %rax
	movl	$0, %edx
	movq	%rax, %rcx
	call	pthread_join
	testl	%eax, %eax
	je	.L10
	leaq	.LC2(%rip), %rax
	movq	%rax, %rcx
	call	perror
	movl	$1, %ecx
	call	exit
.L10:
	movq	-24(%rbp), %rax
	movl	$0, %edx
	movq	%rax, %rcx
	call	pthread_join
	testl	%eax, %eax
	je	.L11
	leaq	.LC3(%rip), %rax
	movq	%rax, %rcx
	call	perror
	movl	$1, %ecx
	call	exit
.L11:
	movq	-16(%rbp), %rax
	movl	$0, %edx
	movq	%rax, %rcx
	call	pthread_join
	testl	%eax, %eax
	je	.L12
	leaq	.LC2(%rip), %rax
	movq	%rax, %rcx
	call	perror
	movl	$1, %ecx
	call	exit
.L12:
	movq	-8(%rbp), %rax
	movl	$0, %edx
	movq	%rax, %rcx
	call	pthread_join
	testl	%eax, %eax
	je	.L13
	leaq	.LC3(%rip), %rax
	movq	%rax, %rcx
	call	perror
	movl	$1, %ecx
	call	exit
.L13:
	movl	mail(%rip), %eax
	movl	%eax, %edx
	leaq	.LC4(%rip), %rax
	movq	%rax, %rcx
	call	printf
	leaq	mutex(%rip), %rax
	movq	%rax, %rcx
	call	pthread_mutex_destroy
	movl	$0, %eax
	addq	$64, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev2, Built by MSYS2 project) 14.2.0"
	.def	pthread_mutex_lock;	.scl	2;	.type	32;	.endef
	.def	pthread_mutex_unlock;	.scl	2;	.type	32;	.endef
	.def	pthread_mutex_init;	.scl	2;	.type	32;	.endef
	.def	pthread_create;	.scl	2;	.type	32;	.endef
	.def	perror;	.scl	2;	.type	32;	.endef
	.def	exit;	.scl	2;	.type	32;	.endef
	.def	pthread_join;	.scl	2;	.type	32;	.endef
	.def	printf;	.scl	2;	.type	32;	.endef
	.def	pthread_mutex_destroy;	.scl	2;	.type	32;	.endef
