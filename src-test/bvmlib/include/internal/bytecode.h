#ifndef __BVM_INTERNAL_BYTECODE
#define __BVM_INTERNAL_BYTECODE
#include "defines.h"
struct DECODED_BYTECODE_S
{
	BYTE opcode;
	BYTE reg1;
	BYTE reg2;
	BYTE reg3;
	QWORD operand_len;
	BYTE* operand;
};

typedef struct DECODED_BYTECODE_S DECODED_BYTECODE;
QWORD decode_bytecode(BYTE *bytecode,DECODED_BYTECODE *decoded_bc,QWORD start,QWORD bytecode_end);
BYTE get_reg3(BYTE *bytecode,QWORD start);
BYTE get_reg2(BYTE *bytecode,QWORD start);
BYTE get_reg1(BYTE *bytecode,QWORD start);
BYTE get_opcode(BYTE *bytecode,QWORD start);
BYTE get_type(BYTE *bytecode,QWORD start);
#endif