#ifndef __BVM_INTERNAL_STACK
#define __BVM_INTERNAL_STACK
#include "defines.h"
#ifndef __BVM_INTERNAL_STACK_INST
#define __BVM_INTERNAL_STACK_INST
struct STACK_ITEM_S
{
    BYTE* data;
    QWORD len;
};
typedef struct STACK_ITEM_S STACK_ITEM;
struct STACK_S
{
    STACK_ITEM* stk;
    int32_t cidx;
};
typedef struct STACK_S STACK;
#endif
void free_stack(STACK *stack);
void stack_push(STACK *stack,BYTE *val,QWORD len);
BYTE *stack_pop(STACK *stack);
int stack_empty(STACK stack);
void init_stack(STACK *stack);
#endif
