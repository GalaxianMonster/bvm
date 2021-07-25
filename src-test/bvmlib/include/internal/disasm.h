#ifndef __BVM_INTERNAL_DISASM
#define __BVM_INTERNAL_DISASM
#include "defines.h"
#include "bytecode.h"
#include "exports.h"
#ifndef __BVM_INTERNAL_DISASM_INST
#define __BVM_INTERNAL_DISASM_INST
BVMLIB_DECL struct DISASM_BYTECODE_S
{
    QWORD dec_bclen;
    DECODED_BYTECODE* dec_bc;
};
typedef struct DISASM_BYTECODE_S DISASM_BYTECODE;
#endif
BVMLIB_DECL int disasm_bytecode(DISASM_BYTECODE *p_disasm_bytecode,BYTE *BYTECODE,QWORD BYTELEN);
#endif
