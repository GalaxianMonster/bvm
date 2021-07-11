/* Virtual Memory for the Program */
#ifndef __INTERNAL_VMEM_H
#define __INTERNAL_VMEM_H
#include "defines.h"
#include "limits.h"
#include "stack.h"
#ifndef __INTERNAL_VMEM_INST
#define __INTERNAL_VMEM_INST
struct REG_VAL_S
{
    BYTE* val;
    QWORD len;
};
struct VMEM_S
{
    struct REG_VAL_S registers[REGISTER_MAX];
    STACK stack;
    BYTE* memory;
    QWORD memory_len;
};
typedef struct VMEM_S VMEM;
typedef struct REG_VAL_S REG_VAL;
#endif
void init_vmem(VMEM* vmem)
{
    vmem->memory = (BYTE*)malloc(0);
    vmem->memory_len = 0;
    for(int i = 0; i < REGISTER_MAX; ++i)
    {
        vmem->registers[i].val = (BYTE*)malloc(0);
        vmem->registers[i].len = 0;
    }
    init_stack(&(vmem->stack));
}

void mov_reg(VMEM* vmem, BYTE reg, BYTE* val, QWORD len)
{
    vmem->registers[reg].len = len;
    vmem->registers[reg].val = (BYTE*)realloc(vmem->registers[reg].val,sizeof(BYTE) * len);
    for(QWORD i = 0; i < len; ++i)
    {
        vmem->registers[reg].val[i] = val[i];
    }
}
REG_VAL get_reg(VMEM* vmem, BYTE reg)
{
    return vmem->registers[reg];
}
void set_mem(VMEM* vmem, BYTE byte, QWORD mem_set)
{
    if(vmem->memory_len < mem_set+1)
    {
        vmem->memory = (BYTE*)realloc(vmem->memory, (mem_set+1)*sizeof(BYTE));
        vmem->memory_len = mem_set+1;
    }
    vmem->memory[mem_set] = byte;
}
int get_mem(BYTE* byte, VMEM* vmem, QWORD mem_set)
{
    if(vmem->memory_len < mem_set+1)
    {
        return -1;
    }
    *byte = vmem->memory[mem_set];
    return 0;
}
int red_mem(VMEM* vmem, QWORD mem_set)
{
    if(vmem->memory_len <= mem_set)
    {
        return -1;
    }
    vmem->memory = (BYTE*)realloc(vmem->memory, sizeof(BYTE)*mem_set);
    return 0;
}

void free_vmem(VMEM* vmem)
{
    free_stack(&(vmem->stack));
    for(DWORD i = 0; i < REGISTER_MAX; ++i)
    {
        vmem->registers[i].len = 0;
        free(vmem->registers[i].val);
    }
    free(vmem->memory);
    vmem->memory_len = 0;
}

STACK vmem_stack(VMEM* vmem)
{
    return vmem->stack;
}
STACK* vmem_pstack(VMEM* vmem)
{
    return &(vmem->stack);
}
#endif