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
#ifndef __BVM_LIB
#define __BVM_LIB
#ifdef __cplusplus
extern "C" {
#endif
#include "internal/debug.h"
#include "internal/defines.h"
#include "internal/bytecode.h"
#include "internal/limits.h"

#include "internal/vmem.h"
#include "internal/types.h"
#include "internal/eval.h"
#include "internal/program.h"

#include "internal/op.h"
#include "internal/instruction.h"
#include "internal/syscall.h"

#include "internal/vm.h"

#define BVM_HEADER_ONLY

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
#ifdef __cplusplus
}
#endif
#endif
