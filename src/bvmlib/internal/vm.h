#ifndef __INTERNAL_VM_H
#define __INTERNAL_VM_H
#include <stdlib.h>
#include "defines.h"
#include "program.h"

#define VMState BYTE
#define VMSTATE_NS 0
#define VMSTATE_OK 1
#define VMSTATE_FAIL 2

struct VM_S
{
    PROG prog;
    VMState state;
};
typedef struct VM_S VM;

VM new_vm(BYTE* bytecode, QWORD length)
{
    VM vm;
    vm.state = VMSTATE_NS;
    init_prog(&(vm.prog), bytecode, length);
    return vm;
}

void run_vm(VM* vm)
{
    DEBUG("run_vm", "starting vm");
    if(vm->state == VMSTATE_OK || vm->state == VMSTATE_FAIL)
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
            vm->state = VMSTATE_FAIL;
        }
        else
        {
            DEBUG("run_vm", "execution success");
            vm->state = VMSTATE_OK;
        }
        free_prog(&vm->prog);
    }
}

#endif