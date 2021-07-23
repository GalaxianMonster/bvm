#include "../../include/internal/bytecode.h"
#include "../../include/internal/defines.h"
#include "../../include/internal/disasm.h"
#include "../../include/internal/defines.h"
#include <stdlib.h>

#ifndef __BVM_INTERNAL_DISASM_INST
#define __BVM_INTERNAL_DISASM_INST
struct DISASM_BYTECODE_S
{
    QWORD dec_bclen;
    DECODED_BYTECODE* dec_bc;
};
typedef struct DISASM_BYTECODE_S DISASM_BYTECODE;
#endif

int disasm_bytecode(DISASM_BYTECODE* p_disasm_bytecode, BYTE* BYTECODE,  QWORD BYTELEN)
{
    QWORD end = BYTELEN - 1;
    DECODED_BYTECODE* decoded_bytecode = (DECODED_BYTECODE*)malloc(0);
    QWORD decoded_bclen = 0;
    for(QWORD i = 0; i < BYTELEN; ++i)
    {
        decoded_bclen++;
        DECODED_BYTECODE c_decoded_bc;
        i = decode_bytecode(BYTECODE, &c_decoded_bc, i, end);
        if(i == 0)
        {
            return -1;
        }
        decoded_bytecode = (DECODED_BYTECODE*)realloc(decoded_bytecode, sizeof(DECODED_BYTECODE) * decoded_bclen);
        decoded_bytecode[decoded_bclen-1] = c_decoded_bc;
    }
    // int isFirst = 1;
    // for(QWORD i = 0; i < decoded_bclen; ++i)
    // {
    //  if(isFirst == 1)
    //  {
    //      printf("----------------------------\n");
    //  }
    //  isFirst = 0;
    //  printf("Instruction Number: %d\n", i);
    //  printf("OP Code: %d\n", decoded_bytecode[i].opcode);
    //  printf("Register 1: %d\n", decoded_bytecode[i].reg1);
    //  printf("Register 2: %d\n", decoded_bytecode[i].reg2);
    //  printf("Register 3: %d\n", decoded_bytecode[i].reg3);
    //  printf("Operands Length: %d\n", decoded_bytecode[i].operand_len);
    //  for(QWORD i2 = 0; i2 < decoded_bytecode[i].operand_len; ++i2)
    //  {
    //      printf("Operand #%d: %d\n", i2,decoded_bytecode[i].operand[i2]);
    //  }
    //  printf("----------------------------\n");
    // }
    DISASM_BYTECODE disasm_bc;
    disasm_bc.dec_bc = decoded_bytecode;
    disasm_bc.dec_bclen = decoded_bclen;
    *p_disasm_bytecode = disasm_bc;
    return 1;
}
