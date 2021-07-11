#ifndef __INTERNAL_EVAL_H
#define __INTERNAL_EVAL_H
#include "op.h"
#include "instruction.h"
#include "debug.h"
#include "defines.h"
#include "vmem.h"
#include "bytecode.h"
#include "disasm.h"
#include <stdio.h>

int exec_bytecode(BYTE* bytecode, QWORD bytelen, VMEM* mem)
{
    DISASM_BYTECODE disasm_bc;
    int res = disasm_bytecode(&disasm_bc, bytecode, bytelen);
    if(res < 0)
    {
        DEBUG("exec_bytecode", "Invalid Bytecode");
        return -1;
    }
    for(QWORD i = 0; i < disasm_bc.dec_bclen;)
    {
        INSTR current_instr;
        int res = new_instr(&current_instr, disasm_bc, i);
        if(res < 0)
        {
            return -1;
        }
        if(OPCODE_EXISTS(current_instr.opcode) == 0)
        {
            DEBUG("exec_bytecode", "OP Code not supported");
            return -1;
        }
        res = FUNC_OP[current_instr.opcode](mem, current_instr);
        if(res == -1)
        {
            return -1;
        }
        else if(res == 0)
        {
            return 0;
        }
        else if(res == 2)
        {
            QWORD next = to_qword(current_instr.immval);
            if(next >= disasm_bc.dec_bclen)
            {
                DEBUG("exec_bytecode", "attempt to jump to the instruction number that doesn't exists");
                return -1;
            }
            i = next;
            continue;
        }
        ++i;
    }
    return 0;
}

#endif