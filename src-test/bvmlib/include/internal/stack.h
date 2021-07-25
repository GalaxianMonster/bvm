#ifndef __BVM_INTERNAL_STACK
#define __BVM_INTERNAL_STACK
#include "defines.h"
#include "exports.h"
#ifndef __BVM_INTERNAL_STACK_INST
#define __BVM_INTERNAL_STACK_INST
BVMLIB_DECL struct STACK_ITEM_S
{
    BYTE* data;
    QWORD len;
};
typedef struct STACK_ITEM_S STACK_ITEM;
BVMLIB_DECL struct STACK_S
{
    STACK_ITEM* stk;
    int32_t cidx;
};
typedef struct STACK_S STACK;
#endif
BVMLIB_DECL void free_stack(STACK *stack);
BVMLIB_DECL void stack_push(STACK *stack,BYTE *val,QWORD len);
BVMLIB_DECL BYTE *stack_pop(STACK *stack);
BVMLIB_DECL int stack_empty(STACK stack);
BVMLIB_DECL void init_stack(STACK *stack);
#endif
