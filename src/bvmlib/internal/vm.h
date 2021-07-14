#ifndef __BVM_INTERNAL_VM_H
#define __BVM_INTERNAL_VM_H
#include <stdlib.h>
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

BVM new_vm(BYTE* bytecode, QWORD length)
{
    BVM vm;
    vm.state = BVM_VMSTATE_NS;
    init_prog(&(vm.prog), bytecode, length);
    return vm;
}

void run_vm(BVM* vm)
{
    DEBUG("run_vm", "starting vm");
    if(vm->state != BVM_VMSTATE_NS)
    {
        DEBUG("run_vm", "already ended");
    }
    else
    {
        DEBUG("run_vm", "executing bytecode");
        int res = exec_prog(&vm->prog);
        DEBUG("run_vm", "execution done");
        if(res == -1)
        {
            DEBUG("run_vm", "execution failed");
            vm->state = BVM_VMSTATE_FAIL;
        }
        else
        {
            DEBUG("run_vm", "execution success");
            vm->state = BVM_VMSTATE_OK;
        }
        free_prog(&vm->prog);
    }
}

#endif
