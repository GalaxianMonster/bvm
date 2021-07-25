#ifndef __BVM_INTERNAL_PROG
#define __BVM_INTERNAL_PROG
#include "vmem.h"
#include "defines.h"
#include "exports.h"
#ifndef __BVM_INTERNAL_PROG_INST
#define __BVM_INTERNAL_PROG_INST
BVMLIB_DECL struct PROG_S
{
	VMEM mem;
	QWORD bytelen;
	BYTE* bytecode;
};
typedef struct PROG_S PROG;
#endif
BVMLIB_DECL void free_prog(PROG *prog);
BVMLIB_DECL int exec_prog(PROG *prog);
BVMLIB_DECL void init_prog(PROG *prog,BYTE *bytecode,QWORD bytelen);
#endif