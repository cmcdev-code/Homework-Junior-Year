	.file	"arith.c"
	.text
	.globl	arith
	.type	arith, @function
arith:
	pushq	%rbp				//setting up stack frame
	movq	%rsp, %rbp			//setting up stack frame
	subq	$32, %rsp			//setting up stack frame
	movl	%edi, -20(%rbp)		//parameter 1 moved to stack
	movl	%esi, -24(%rbp)		//parameter 2 moved to stack
	movl	%edx, -28(%rbp)		//parameter 3 moved to stack
	movl	-20(%rbp), %edx		//move p1 into edx
	movl	-24(%rbp), %eax		//move p2 into eax 
	addl	%edx, %eax			//add p1+p2 and store in eax 
	movl	%eax, -4(%rbp)		//create a local variable at rbp-4 with p1+p2 (t1)
	movl	-28(%rbp), %edx		//move p3 into edx 
	movl	%edx, %eax			//move p3 into eax 
	addl	%eax, %eax			//eax = p3+p3 = 2(p3)
	addl	%edx, %eax			//eax = 2(p3)+p3
	sall	$4, %eax			//bit shift eax (multiply by 2^4)
	movl	%eax, -8(%rbp)		//create local variable t2 in rbp-8 on stack
	movl	-4(%rbp), %eax		//eax = t1 
	movzwl	%ax, %eax			//eax = last 2 bytes of eax
								//z=zero extend
								//wl=word into long
	movl	%eax, -12(%rbp)		//create local variable t3
	movl	-8(%rbp), %eax		//
	imull	-12(%rbp), %eax
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %eax
	leave
	ret
	.size	arith, .-arith
	.ident	"GCC: (GNU) 11.4.1 20230605 (Red Hat 11.4.1-2)"
	.section	.note.GNU-stack,"",@progbits
