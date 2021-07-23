/* 
 * 
 * Basic Virtual Machine
 * Library
 * 
 * Author: GalaxianMonster
 * File: lib.h
 * Description: Interface for interacting with BVM
 * 
 */

#include <stdlib.h>

#include "../include/internal/bytecode.h"
#include "../include/internal/debug.h"
#include "../include/internal/defines.h"
#include "../include/internal/disasm.h"
#include "../include/internal/eval.h"
#include "../include/internal/instruction.h"
#include "../include/internal/limits.h"
#include "../include/internal/op.h"
#include "../include/internal/program.h"
#include "../include/internal/stack.h"
#include "../include/internal/syscall.h"
#include "../include/internal/types.h"
#include "../include/internal/vmem.h"
#include "../include/internal/debug.h"
#include "../include/internal/vm.h"

#include "../include/lib.h"

#define BVMLIB_VERSION "1.1.2"

/* Initialize BVM */
void BVM_init()
{

    init_op_functions();

    SYSCALL_init();

}

/* Cleanup BVM */
void BVM_cleanup()
{

    free(FUNC_SYSCALL);

    SYSCALL_MAX = 0;

}

/* Allow BVM Debugging */
void BVM_on_debug()
{

    __INTERNAL_DEBUG = 1;

}

/* Disallow BVM Debugging */
void BVM_off_debug()
{

    __INTERNAL_DEBUG = 0;

}

/* Execute Bytecode to BVM */
BVM_VMState BVM_exec(BYTE* bytecode, QWORD length)
{

    BVM vm = new_vm(bytecode, length);

    run_vm(&vm);

    return vm.state;

}

int BVM_debugging()
{
    return __INTERNAL_DEBUG;
}
char* BVM_get_lib_version()
{
    return BVMLIB_VERSION;
}