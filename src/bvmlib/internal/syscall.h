#ifndef __BVM_INTERNAL_SYSCALL_H
#define __BVM_INTERNAL_SYSCALL_H
#include "defines.h"
#include "vmem.h"
#include <stdlib.h>
#define SYSCALL_FAIL -1
#define SYSCALL_SUCCESS 0
static DWORD SYSCALL_MAX;
static int(**FUNC_SYSCALL)(VMEM*);

void SYSCALL_init()
{
    SYSCALL_MAX = 0;
    FUNC_SYSCALL = (int(**)(VMEM*))malloc(sizeof(int(*)(VMEM*)) * 0);
}
void SYSCALL_add(int(*func)(VMEM*))
{
    SYSCALL_MAX++;
    FUNC_SYSCALL = (int(**)(VMEM*))realloc(FUNC_SYSCALL,sizeof(int(*)(VMEM*)) * SYSCALL_MAX);
    FUNC_SYSCALL[SYSCALL_MAX-1] = func;
}
#endif
