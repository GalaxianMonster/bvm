#ifndef __BVM_LIB
#define __BVM_LIB
#ifdef __cplusplus
extern "C" {
#endif
#include "internal/bytecode.h"
#include "internal/debug.h"
#include "internal/defines.h"
#include "internal/disasm.h"
#include "internal/eval.h"
#include "internal/instruction.h"
#include "internal/limits.h"
#include "internal/op.h"
#include "internal/program.h"
#include "internal/stack.h"
#include "internal/syscall.h"
#include "internal/types.h"
#include "internal/vm.h"
#include "internal/vmem.h"
#define BVMINCLUDE_VERSION "1.1.2"
BVM_VMState BVM_exec(BYTE *bytecode,QWORD length);
void BVM_off_debug();
void BVM_on_debug();
void BVM_cleanup();
void BVM_init();
int BVM_debugging();
char* BVM_get_lib_version();
#ifdef __cplusplus
}
#endif
#endif
