#include <stdlib.h>
#include "../../include/internal/defines.h"
#include "../../include/internal/program.h"
#include "../../include/internal/debug.h"
#include "../../include/internal/vm.h"

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