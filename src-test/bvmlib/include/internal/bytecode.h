#ifndef __BVM_INTERNAL_BYTECODE
#define __BVM_INTERNAL_BYTECODE
#include "defines.h"
#include "exports.h"
BVMLIB_DECL struct DECODED_BYTECODE_S
{
	BYTE opcode;
	BYTE reg1;
	BYTE reg2;
	BYTE reg3;
	QWORD operand_len;
	BYTE* operand;
};

typedef struct DECODED_BYTECODE_S DECODED_BYTECODE;
BVMLIB_DECL QWORD decode_bytecode(BYTE *bytecode,DECODED_BYTECODE *decoded_bc,QWORD start,QWORD bytecode_end);
BVMLIB_DECL BYTE get_reg3(BYTE *bytecode,QWORD start);
BVMLIB_DECL BYTE get_reg2(BYTE *bytecode,QWORD start);
BVMLIB_DECL BYTE get_reg1(BYTE *bytecode,QWORD start);
BVMLIB_DECL BYTE get_opcode(BYTE *bytecode,QWORD start);
BVMLIB_DECL BYTE get_type(BYTE *bytecode,QWORD start);
#endif