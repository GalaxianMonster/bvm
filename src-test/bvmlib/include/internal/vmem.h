#ifndef __BVM_INTERNAL_VMEM
#define __BVM_INTERNAL_VMEM
#include "defines.h"
#include "limits.h"
#include "stack.h"
#include "exports.h"
#ifndef __BVM_INTERNAL_VMEM_INST
#define __BVM_INTERNAL_VMEM_INST
BVMLIB_DECL struct REG_VAL_S
{
    BYTE* val;
    QWORD len;
};
BVMLIB_DECL struct VMEM_S
{
    struct REG_VAL_S registers[REGISTER_MAX];
    STACK stack;
    BYTE* memory;
    QWORD memory_len;
};
typedef struct VMEM_S VMEM;
typedef struct REG_VAL_S REG_VAL;
#endif
BVMLIB_DECL STACK *vmem_pstack(VMEM *vmem);
BVMLIB_DECL STACK vmem_stack(VMEM *vmem);
BVMLIB_DECL void free_vmem(VMEM *vmem);
BVMLIB_DECL int red_mem(VMEM *vmem,QWORD mem_set);
BVMLIB_DECL int get_mem(BYTE *byte,VMEM *vmem,QWORD mem_set);
BVMLIB_DECL void set_mem(VMEM *vmem,BYTE byte,QWORD mem_set);
BVMLIB_DECL REG_VAL get_reg(VMEM *vmem,BYTE reg);
BVMLIB_DECL void mov_reg(VMEM *vmem,BYTE reg,BYTE *val,QWORD len);
BVMLIB_DECL void init_vmem(VMEM *vmem);
#endif