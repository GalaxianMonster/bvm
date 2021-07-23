#include "../../include/internal/defines.h" // BYTE
#include "../../include/internal/bytecode.h" // DECODED_BYTECODE
#include "../../include/internal/disasm.h" // DISASM_BYTECODE
#include "../../include/internal/types.h" // types like TYPE_BYTE
#include "../../include/internal/instruction.h"
#include "../../include/internal/debug.h" // Debugging
#include <stdlib.h>

int new_instr(INSTR* instr, DISASM_BYTECODE disasm_bc, QWORD c)
{
    instr->opcode = disasm_bc.dec_bc[c].opcode;
    instr->reg1   = disasm_bc.dec_bc[c].reg1;
    instr->reg2   = disasm_bc.dec_bc[c].reg2;
    instr->reg3   = disasm_bc.dec_bc[c].reg3;
    int operand_len;
    int operand_exists = 0;
    if(disasm_bc.dec_bc[c].operand_len == 0)
    {
        operand_len = 0;
    }
    else
    {
        instr->immval_type = disasm_bc.dec_bc[c].operand[0];
        operand_len = (disasm_bc.dec_bc[c].operand_len)-1;
        operand_exists = 1;
    }
    instr->immval_len  = operand_len;
    BYTE* operands = (BYTE*)malloc(instr->immval_len * sizeof(BYTE));
    BYTE panic = 0;
    if(operand_exists == 1)
    {
        if(TYPE_EXISTS(disasm_bc.dec_bc[c].operand[0]) == 0)
        { 
            DEBUG("new_instr", "Operand type not supported");
            panic = 1;
        }
        if(panic == 0)
        {
            for(QWORD i = 1; i < ((instr->immval_len)+1); ++i)
            {
                operands[i-1] = disasm_bc.dec_bc[c].operand[i];
            }
        }
    }
    instr->immval = operands;
    if(panic == 1)
    {
        return -1;
    }
    return 0;
}