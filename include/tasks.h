
struct regs {
	int edi, esi, ebp, esp, ebx, edx, ecx, eax, eip, eflags;
};

struct task {
	struct regs context;
	int stack[1024];
};
