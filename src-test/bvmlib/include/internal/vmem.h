#ifndef __BVM_INTERNAL_VMEM
#define __BVM_INTERNAL_VMEM
#include "defines.h"
#include "limits.h"
#include "stack.h"
#ifndef __BVM_INTERNAL_VMEM_INST
#define __BVM_INTERNAL_VMEM_INST
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
STACK *vmem_pstack(VMEM *vmem);
STACK vmem_stack(VMEM *vmem);
void free_vmem(VMEM *vmem);
int red_mem(VMEM *vmem,QWORD mem_set);
int get_mem(BYTE *byte,VMEM *vmem,QWORD mem_set);
void set_mem(VMEM *vmem,BYTE byte,QWORD mem_set);
REG_VAL get_reg(VMEM *vmem,BYTE reg);
void mov_reg(VMEM *vmem,BYTE reg,BYTE *val,QWORD len);
void init_vmem(VMEM *vmem);
#endif