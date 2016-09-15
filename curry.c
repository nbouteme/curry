#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include "curry.h"
#include "funalloc.h"

long my_syscall();

t_value curry(void *f, t_value arg)
{
	//char *sp = (void*)my_syscall(SYS_mmap, 0, 1, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	char *sp = funalloc();
	ex_set(false);
	memcpy(sp,
		   "\x41\x51"						// push %r9; push potentially garbage
		   "\x4d\x89\xc1"					// mov %r8, %r9; "shift" each register from here to...
		   "\x49\x89\xc8"					// mov %rcx, %r8;
		   "\x48\x89\xd1"					// mov %rdx, %rcx;
		   "\x48\x89\xf2"					// mov %rsi, %rdx;
		   "\x48\x89\xfe"					// mov %rdi, %rsi; ...there
		   "\x48\x8b\x3d\x0F\x00\x00\x00"	// mov 15(%rip), %rdi; "bind" argument
		   "\x4c\x8b\x15\x10\x00\x00\x00"	// mov 16(%rip), %r10; load address
		   "\x41\xff\xd2"					// call *%r10
		   "\x48\x83\xc4\x08"				// add $8, %rsp; cleanup
		   "\xc3",							// retq
		   39);
	memcpy(sp + 39, &arg, sizeof(arg));
	memcpy(sp + 47, &f, sizeof(f));
	ex_set(true);
	//my_syscall(SYS_mprotect, sp, 1, PROT_READ | PROT_EXEC);
	return (t_value){sp};
}

void eat(void *curry)
{
	my_syscall(SYS_munmap, curry, 1);
}
