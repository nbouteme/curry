void my_syscall()
{
	__asm__ ("movq %rdi, %rax\n\t"
			 "movq %rsi, %rdi\n\t"
			 "movq %rdx, %rsi\n\t"
			 "movq %rcx, %rdx\n\t"
			 "movq %r8, %r10\n\t"
			 "movq %r9, %r8\n\t");
#ifdef __OPTIMIZE__
	__asm__("movq 0x8(%rsp), %r9");
#else
	__asm__ ("movq 0x10(%rbp), %r9");
#endif
	__asm__ ("syscall");
}
