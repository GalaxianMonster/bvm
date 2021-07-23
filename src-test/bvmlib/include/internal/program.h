#ifndef __BVM_INTERNAL_PROG
#define __BVM_INTERNAL_PROG
#include "vmem.h"
#include "defines.h"
#ifndef __BVM_INTERNAL_PROG_INST
#define __BVM_INTERNAL_PROG_INST
struct PROG_S
{
	VMEM mem;
	QWORD bytelen;
	BYTE* bytecode;
};
typedef struct PROG_S PROG;
#endif
void free_prog(PROG *prog);
int exec_prog(PROG *prog);
void init_prog(PROG *prog,BYTE *bytecode,QWORD bytelen);
#endif