#ifndef __BVM_INTERNAL_OP
#define __BVM_INTERNAL_OP
#include "limits.h"
#include "vmem.h"
#include "instruction.h"
enum ENUM_OP{
    OP_MOV = 0,
    OP_EXIT = 1,
    OP_MOVVB = 2,
    OP_MOVVW = 3,
    OP_MOVVDW = 4,
    OP_MOVVQW = 5,
    OP_MOVMDW = 6,
    OP_MOVMQW = 7,
    OP_ADDB = 8,
    OP_ADDW = 9,
    OP_ADDDW = 10,
    OP_ADDQW = 11,
    OP_SUBB = 12,
    OP_SUBW = 13,
    OP_SUBDW = 14,
    OP_SUBQW = 15,
    OP_MULB = 16,
    OP_MULW = 17,
    OP_MULDW = 18,
    OP_MULQW = 19,
    OP_DIVB = 20,
    OP_DIVW = 21,
    OP_DIVDW = 22,
    OP_DIVQW = 23,
    OP_MODB = 24,
    OP_MODW = 25,
    OP_MODDW = 26,
    OP_MODQW = 27,
    OP_ANDB = 28,
    OP_ANDW = 29,
    OP_ANDDW = 30,
    OP_ANDQW = 31,
    OP_ORB = 32,
    OP_ORW = 33,
    OP_ORDW = 34,
    OP_ORQW = 35,
    OP_XORB = 36,
    OP_XORW = 37,
    OP_XORDW = 38,
    OP_XORQW = 39,
    OP_SHRB = 40,
    OP_SHRW = 41,
    OP_SHRDW = 42,
    OP_SHRQW = 43,
    OP_SHLB = 44,
    OP_SHLW = 45,
    OP_SHLDW = 46,
    OP_SHLQW = 47,
    OP_JMP = 48,
    OP_CMPB = 49,
    OP_CMPW = 50,
    OP_CMPDW = 51,
    OP_CMPQW = 52,
    OP_JE = 53,
    OP_JNE = 54,
    OP_JL = 55,
    OP_JG = 56,
    OP_SETM = 57,
    OP_REDM = 58,
    OP_MOVMB = 59,
    OP_MOVMW = 60,
    OP_LDB = 61,
    OP_LDW = 62,
    OP_LDDW = 63,
    OP_LDQW = 64,
    OP_CONVB = 65,
    OP_CONVW = 66,
    OP_CONVDW = 67,
    OP_CONVQW = 68,
    OP_PUSH = 69,
    OP_POP = 70,
    OP_SYSCALL = 71,
    OP_NEGB = 72,
    OP_NEGW = 73,
    OP_NEGDW = 74,
    OP_NEGQW = 75
};
typedef enum ENUM_OP OPCODE;
extern int (*FUNC_OP[OPCODE_MAX])(VMEM*,  INSTR);
void init_op_functions();
int FUNC_OP_NEGQW(VMEM *mem,INSTR instr);
int FUNC_OP_NEGDW(VMEM *mem,INSTR instr);
int FUNC_OP_NEGW(VMEM *mem,INSTR instr);
int FUNC_OP_NEGB(VMEM *mem,INSTR instr);
int FUNC_OP_POP(VMEM *mem,INSTR instr);
int FUNC_OP_PUSH(VMEM *mem,INSTR instr);
int FUNC_OP_CONVQW(VMEM *mem,INSTR instr);
int FUNC_OP_CONVDW(VMEM *mem,INSTR instr);
int FUNC_OP_CONVW(VMEM *mem,INSTR instr);
int FUNC_OP_CONVB(VMEM *mem,INSTR instr);
int FUNC_OP_LDQW(VMEM *mem,INSTR instr);
int FUNC_OP_LDDW(VMEM *mem,INSTR instr);
int FUNC_OP_LDW(VMEM *mem,INSTR instr);
int FUNC_OP_LDB(VMEM *mem,INSTR instr);
int FUNC_OP_JG(VMEM *mem,INSTR instr);
int FUNC_OP_JL(VMEM *mem,INSTR instr);
int FUNC_OP_JNE(VMEM *mem,INSTR instr);
int FUNC_OP_JE(VMEM *mem,INSTR instr);
int FUNC_OP_CMPQW(VMEM *mem,INSTR instr);
int FUNC_OP_CMPDW(VMEM *mem,INSTR instr);
int FUNC_OP_CMPW(VMEM *mem,INSTR instr);
int FUNC_OP_CMPB(VMEM *mem,INSTR instr);
int FUNC_OP_JMP(VMEM *mem,INSTR instr);
int FUNC_OP_SYSCALL(VMEM *mem,INSTR instr);
int FUNC_OP_REDM(VMEM *mem,INSTR instr);
int FUNC_OP_SETM(VMEM *mem,INSTR instr);
int FUNC_OP_SHLQW(VMEM *mem,INSTR instr);
int FUNC_OP_SHLDW(VMEM *mem,INSTR instr);
int FUNC_OP_SHLW(VMEM *mem,INSTR instr);
int FUNC_OP_SHLB(VMEM *mem,INSTR instr);
int FUNC_OP_SHRQW(VMEM *mem,INSTR instr);
int FUNC_OP_SHRDW(VMEM *mem,INSTR instr);
int FUNC_OP_SHRW(VMEM *mem,INSTR instr);
int FUNC_OP_SHRB(VMEM *mem,INSTR instr);
int FUNC_OP_XORQW(VMEM *mem,INSTR instr);
int FUNC_OP_XORDW(VMEM *mem,INSTR instr);
int FUNC_OP_XORW(VMEM *mem,INSTR instr);
int FUNC_OP_XORB(VMEM *mem,INSTR instr);
int FUNC_OP_ORQW(VMEM *mem,INSTR instr);
int FUNC_OP_ORDW(VMEM *mem,INSTR instr);
int FUNC_OP_ORW(VMEM *mem,INSTR instr);
int FUNC_OP_ORB(VMEM *mem,INSTR instr);
int FUNC_OP_ANDQW(VMEM *mem,INSTR instr);
int FUNC_OP_ANDDW(VMEM *mem,INSTR instr);
int FUNC_OP_ANDW(VMEM *mem,INSTR instr);
int FUNC_OP_ANDB(VMEM *mem,INSTR instr);
int FUNC_OP_MODQW(VMEM *mem,INSTR instr);
int FUNC_OP_MODDW(VMEM *mem,INSTR instr);
int FUNC_OP_MODW(VMEM *mem,INSTR instr);
int FUNC_OP_MODB(VMEM *mem,INSTR instr);
int FUNC_OP_DIVQW(VMEM *mem,INSTR instr);
int FUNC_OP_DIVDW(VMEM *mem,INSTR instr);
int FUNC_OP_DIVW(VMEM *mem,INSTR instr);
int FUNC_OP_DIVB(VMEM *mem,INSTR instr);
int FUNC_OP_MULQW(VMEM *mem,INSTR instr);
int FUNC_OP_MULDW(VMEM *mem,INSTR instr);
int FUNC_OP_MULW(VMEM *mem,INSTR instr);
int FUNC_OP_MULB(VMEM *mem,INSTR instr);
int FUNC_OP_SUBQW(VMEM *mem,INSTR instr);
int FUNC_OP_SUBDW(VMEM *mem,INSTR instr);
int FUNC_OP_SUBW(VMEM *mem,INSTR instr);
int FUNC_OP_SUBB(VMEM *mem,INSTR instr);
int FUNC_OP_ADDQW(VMEM *mem,INSTR instr);
int FUNC_OP_ADDDW(VMEM *mem,INSTR instr);
int FUNC_OP_ADDW(VMEM *mem,INSTR instr);
int FUNC_OP_ADDB(VMEM *mem,INSTR instr);
int FUNC_OP_EXIT(VMEM *mem,INSTR instr);
int FUNC_OP_MOVMQW(VMEM *mem,INSTR instr);
int FUNC_OP_MOVMDW(VMEM *mem,INSTR instr);
int FUNC_OP_MOVMW(VMEM *mem,INSTR instr);
int FUNC_OP_MOVMB(VMEM *mem,INSTR instr);
int FUNC_OP_MOVVQW(VMEM *mem,INSTR instr);
int FUNC_OP_MOVVDW(VMEM *mem,INSTR instr);
int FUNC_OP_MOVVW(VMEM *mem,INSTR instr);
int FUNC_OP_MOVVB(VMEM *mem,INSTR instr);
int FUNC_OP_MOV(VMEM *mem,INSTR instr);
int CHECK_IMMVAL(const char *opcode,INSTR instr);
int CHECK_TYPE(const char *opcode,BYTE type,BYTE type2);
int CHECK_REG(const char *opcode,BYTE reg);
int REG_EXISTS(BYTE reg);
int OPCODE_EXISTS(BYTE opcode);
#endif
