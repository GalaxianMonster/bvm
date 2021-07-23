#ifndef __BVM_INTERNAL_EVAL
#define __BVM_INTERNAL_EVAL
#include "vmem.h"
int exec_bytecode(BYTE *bytecode,QWORD bytelen,VMEM *mem);
#endif
