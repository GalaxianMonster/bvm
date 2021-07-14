#ifndef __BVM_INTERNAL_PROG_H
#define __BVM_INTERNAL_PROG_H
#include "limits.h"
#include "defines.h"
#include <stdlib.h>
#include "bytecode.h"
#include "eval.h"
#include "op.h"
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

void init_prog(PROG* prog, BYTE* bytecode, QWORD bytelen)
{
	init_vmem(&(prog->mem));
	prog->bytecode = bytecode;
	prog->bytelen = bytelen;
}


int exec_prog(PROG* prog)
{
	int prog_res = exec_bytecode(prog->bytecode, prog->bytelen, &(prog->mem));
	return prog_res;
}

void free_prog(PROG* prog)
{
	free_vmem(&(prog->mem));
	prog->bytelen = 0;
}

#endif
