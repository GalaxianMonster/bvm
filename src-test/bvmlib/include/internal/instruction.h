#ifndef __BVM_INTERNAL_INSTRUCTION
#define __BVM_INTERNAL_INSTRUCTION
#include "disasm.h"
#include "exports.h"
#ifndef __BVM_INTERNAL_INSTRUCTION_INST
#define __BVM_INTERNAL_INSTRUCTION_INST
BVMLIB_DECL struct INSTR_S
{
    BYTE opcode;
    BYTE reg1;
    BYTE reg2;
    BYTE reg3;
    BYTE immval_type;
    QWORD immval_len;
    BYTE* immval;
};

typedef struct INSTR_S INSTR;
#endif
BVMLIB_DECL int new_instr(INSTR *instr,DISASM_BYTECODE disasm_bc,QWORD c);
#endif