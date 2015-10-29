#include <stdio.h>
#include <stdlib.h>

struct data
{
    int a;
    int b;
    int c;
};
int count[100];

#define __ACCESS_ONCE(x) ({(volatile typeof(x) *)&(x); })
#define ACCESS_ONCE(x) (*__ACCESS_ONCE(x))

int try_access(struct data *ddd)
{
    int v;

    while (1) {
        v = ACCESS_ONCE(ddd->a);
        if ((v == 1) && (ddd->b == 1)) {
            break;
        }
    }
}

int try_read(struct data *ddd)
{
    int v;

    while (1) {
        v = ddd->a;
        if ((v == 1) && (ddd->b == 1)) {
            break;
        }
    }
}

int main(void)
{
    int i;
    struct data testdata = {1, 2, 3};

    testdata.a = (random() % 6) + ((random() % 6) * 6);
    try_access(&testdata);
    try_read(&testdata);

    for (i = 0; i < 10; i++)
        printf("%d=>%d\n", i, count[i]);
    return 0;
}

/*
  gcc -S -O2 access_once.c
  ./a.out

  	.file	"access_once.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	try_access
	.type	try_access, @function
try_access:
.LFB39:
	.cfi_startproc
	movl	4(%esp), %edx
	movl	4(%edx), %ecx
	.p2align 4,,10
	.p2align 3

=================> read value again in the loop!!
.L2:
	movl	(%edx), %eax
	cmpl	$1, %eax
	jne	.L2
	cmpl	$1, %ecx
	jne	.L2
	rep ret
	.cfi_endproc
.LFE39:
	.size	try_access, .-try_access
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.section	.text.unlikely
.LCOLDB1:
	.text
.LHOTB1:
	.p2align 4,,15
	.globl	try_read
	.type	try_read, @function
try_read:
.LFB40:
	.cfi_startproc
	movl	4(%esp), %edx
	movl	(%edx), %eax
	movl	4(%edx), %edx
	.p2align 4,,10
	.p2align 3



=========================> do not read value again!!!
.L8:
	cmpl	$1, %eax
	jne	.L8
.L12:
	cmpl	$1, %edx
	jne	.L12
	rep ret
	.cfi_endproc
.LFE40:
	.size	try_read, .-try_read
	.section	.text.unlikely
.LCOLDE1:
	.text
.LHOTE1:
	.section	.text.unlikely
.LCOLDB2:
	.section	.text.startup,"ax",@progbits
.LHOTB2:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB41:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x74,0x6
	.cfi_escape 0x10,0x6,0x2,0x75,0x7c
	.cfi_escape 0x10,0x3,0x2,0x75,0x78
	subl	$28, %esp
	call	random
	movl	%eax, %esi
	call	random
	movl	$715827883, %ecx
	movl	%eax, %ebx
	movl	%esi, %eax
	imull	%ecx
	movl	%esi, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	leal	(%edx,%edx,2), %eax
	addl	%eax, %eax
	subl	%eax, %esi
	movl	%ebx, %eax
	imull	%ecx
	movl	%ebx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	leal	(%edx,%edx,2), %eax
	addl	%eax, %eax
	subl	%eax, %ebx
	leal	(%ebx,%ebx,2), %eax
	leal	(%esi,%eax,2), %eax
	movl	%eax, -36(%ebp)
	.p2align 4,,10
	.p2align 3
.L16:
	movl	-36(%ebp), %eax
	jmp	.L16
	.cfi_endproc
.LFE41:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE2:
	.section	.text.startup
.LHOTE2:
	.comm	count,400,64
	.ident	"GCC: (Ubuntu 4.9.2-10ubuntu13) 4.9.2"
	.section	.note.GNU-stack,"",@progbits

*/
  
