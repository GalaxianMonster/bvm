#include "../../include/internal/limits.h"
#include "../../include/internal/defines.h"
#include <stdlib.h>
#include "../../include/internal/bytecode.h"
#include "../../include/internal/eval.h"
#include "../../include/internal/vmem.h"
#include "../../include/internal/op.h"
#include "../../include/internal/program.h"

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