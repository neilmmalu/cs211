	.file	"second.c"
	.section	.rodata
.LC0:
	.string	"error"
.LC1:
	.string	"no"
.LC2:
	.string	"yes"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	cmpl	$2, -20(%rbp)
	je	.L2
	movl	$.LC0, %edi
	call	puts
	movl	$0, %eax
	jmp	.L3
.L2:
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, -8(%rbp)
	cmpl	$1, -8(%rbp)
	jne	.L4
	movl	$.LC1, %edi
	call	puts
	movl	$0, %eax
	jmp	.L3
.L4:
	cmpl	$2, -8(%rbp)
	jne	.L5
	movl	$.LC2, %edi
	call	puts
	movl	$0, %eax
	jmp	.L3
.L5:
	movl	$2, -4(%rbp)
	movl	$2, -4(%rbp)
	jmp	.L6
.L9:
	movl	-8(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jne	.L7
	movl	$.LC2, %edi
	call	puts
	movl	$0, %eax
	jmp	.L3
.L7:
	movl	-8(%rbp), %eax
	cltd
	idivl	-4(%rbp)
	movl	%edx, %eax
	testl	%eax, %eax
	jne	.L8
	movl	$.LC1, %edi
	call	puts
	movl	$0, %eax
	jmp	.L3
.L8:
	addl	$1, -4(%rbp)
.L6:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jle	.L9
	movl	$0, %eax
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-4)"
	.section	.note.GNU-stack,"",@progbits
