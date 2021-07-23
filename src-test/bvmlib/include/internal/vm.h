#ifndef __BVM_INTERNAL_VM
#define __BVM_INTERNAL_VM
#include "defines.h"
#include "program.h"
#define BVM_VMState BYTE
#define BVM_VMSTATE_NS 0
#define BVM_VMSTATE_OK 1
#define BVM_VMSTATE_FAIL 2

struct BVM_S
{
    PROG prog;
    BVM_VMState state;
};
typedef struct BVM_S BVM;
void run_vm(BVM *vm);
BVM new_vm(BYTE *bytecode,QWORD length);
#endif