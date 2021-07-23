#include "../../include/internal/defines.h"
#include "../../include/internal/vmem.h"
#include "../../include/internal/syscall.h"
#include <stdlib.h>

DWORD SYSCALL_MAX;
int(**FUNC_SYSCALL)(VMEM*);

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