/* This file was automatically generated.  Do not edit! */
#ifndef __BVM_INTERNAL_SYSCALL
#define __BVM_INTERNAL_SYSCALL
#include "vmem.h"
#define SYSCALL_FAIL -1
#define SYSCALL_SUCCESS 0
extern DWORD SYSCALL_MAX;
extern int(**FUNC_SYSCALL)(VMEM*);
void SYSCALL_add(int(*func)(VMEM *));
void SYSCALL_init();
#endif