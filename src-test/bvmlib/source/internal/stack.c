#include <stdlib.h>
#include "../../include/internal/defines.h"
#include "../../include/internal/stack.h"
#include <string.h>
void init_stack(STACK* stack)
{
    stack->cidx = -1;
    stack->stk = (STACK_ITEM*)malloc(0);
}
int stack_empty(STACK stack)
{
    if(stack.cidx == -1)
    {
        return 1;
    }
    return 0;
}
BYTE* stack_pop(STACK* stack)
{

    if(!stack_empty(*stack))
    {
        QWORD bytelen = stack->stk[stack->cidx].len;
        BYTE* val = (BYTE*)malloc(sizeof(BYTE) * bytelen);
        for(QWORD i = 0; i < bytelen; ++i)
        {
            val[i] = stack->stk[stack->cidx].data[i];
        }
        free(stack->stk[stack->cidx].data);
        stack->stk[stack->cidx].len = 0;
        stack->stk = (STACK_ITEM*)realloc(stack->stk, (stack->cidx)*sizeof(STACK_ITEM));
        stack->cidx--;
        return val;
    }
    else
    {
        return NULL;
    }
}
void stack_push(STACK* stack, BYTE* val, QWORD len)
{
    if(stack->cidx == -1)
    {
        stack->cidx = 0;
    }
    else
    {
        stack->cidx++;
    }
    stack->stk = (STACK_ITEM*)realloc(stack->stk, sizeof(STACK_ITEM) * (stack->cidx+1));
    stack->stk[stack->cidx].data = (BYTE*)realloc(stack->stk[stack->cidx].data, len * sizeof(BYTE));
    for(QWORD i = 0; i < len; ++i)
    {    
        stack->stk[stack->cidx].data[i] = val[i];
    }
    stack->stk[stack->cidx].len = len;
}
void free_stack(STACK* stack)
{
    for(QWORD i = 0; i < (QWORD)(stack->cidx+1); ++i)
    {
        free(stack->stk[stack->cidx].data);
    }
    free(stack->stk);
}