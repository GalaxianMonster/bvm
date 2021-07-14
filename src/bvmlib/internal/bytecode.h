#ifndef __BVM_INTERNAL_BYTECODE_H
#define __BVM_INTERNAL_BYTECODE_H
#include "defines.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BYTECODE_TYPE_OPERAND 1
#define BYTECODE_TYPE_OPCODE  0

/* 
Format:
Instruction: 3 bytes
0000 00000000 0000 0000 0000
^    ^        ^    ^    ^   
type opcode   reg1 reg2 reg3

Operand: 2 bytes
0000 00000000 0000
^    ^        ^
type val      empty

total bytes of instruction and operand: 5 bytes or up
*/

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

BYTE get_type(BYTE* bytecode, QWORD start)
{
	return (bytecode[start] & 0xF0) >> 4;
}

BYTE get_opcode(BYTE* bytecode, QWORD start)
{
	return ((bytecode[start] & 0x0F) << 4) | ((bytecode[start+1] & 0xF0) >> 4);
}

BYTE get_reg1(BYTE* bytecode, QWORD start)
{
	return (bytecode[start+1] & 0x0F);
}

BYTE get_reg2(BYTE* bytecode, QWORD start)
{
	return (bytecode[start+2] & 0xF0) >> 4;
}

BYTE get_reg3(BYTE* bytecode, QWORD start)
{
	return (bytecode[start+2] & 0x0F);
}

/* Will return the end of the instruction in QWORD */
QWORD decode_bytecode(BYTE* bytecode, DECODED_BYTECODE* decoded_bc,QWORD start, QWORD bytecode_end)
{
	QWORD end 				= start+2;
	if(bytecode_end < end)
	{
		return 0;
	}
	else if(get_type(bytecode, start) != BYTECODE_TYPE_OPCODE)
	{
		return 0;
	}
	BYTE opcode 	 		= get_opcode(bytecode, start);
	BYTE reg1   	 		= get_reg1(bytecode, start);
	BYTE reg2   	 		= get_reg2(bytecode, start);
	BYTE reg3        		= get_reg3(bytecode, start);
	decoded_bc->opcode 		= opcode;
	decoded_bc->reg1   		= reg1;
	decoded_bc->reg2   		= reg2;
	decoded_bc->reg3   		= reg3;
	decoded_bc->operand		= (BYTE*)malloc(0);
	QWORD operand_len 		= 0;
	while(bytecode_end > end)
	{
		end++;
		if(get_type(bytecode, end) != BYTECODE_TYPE_OPERAND)
		{
			end = end-1;
			break;
		}
		if(end+1 > bytecode_end)
		{
			return 0;
		}
		operand_len++;
		decoded_bc->operand = (BYTE*)realloc(decoded_bc->operand, sizeof(BYTE) * operand_len);
		decoded_bc->operand[operand_len-1] = ((bytecode[end] & 0x0F) << 4) | ((bytecode[end+1] & 0xF0) >> 4);
		end++;
	}
	decoded_bc->operand_len = operand_len;
	return end;
}
#endif
