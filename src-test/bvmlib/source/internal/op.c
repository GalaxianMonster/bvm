#include "../../include/internal/defines.h"
#include "../../include/internal/limits.h"
#include "../../include/internal/instruction.h"
#include "../../include/internal/debug.h"
#include "../../include/internal/vmem.h"
#include "../../include/internal/syscall.h"
#include "../../include/internal/types.h"
#include "../../include/internal/op.h"
#include <stdio.h>
#include <stdlib.h>

int (*FUNC_OP[OPCODE_MAX])(VMEM*,  INSTR);

int OPCODE_EXISTS(BYTE opcode)
{
    if(opcode < OPCODE_MAX)
    {
        return 1;
    }
    return 0;
}
int REG_EXISTS(BYTE reg)
{
    if(reg < REGISTER_MAX)
    {
        return 1;
    }
    return 0;
}
int CHECK_REG(const char* opcode, BYTE reg)
{
    if(REG_EXISTS(reg))
    {
        char msg[1024];
        sprintf(msg, "%s: REGISTER %d EXISTS", opcode, reg);
        DEBUG("CHECK_REG", msg);
    }
    else
    {
        char msg[1024];
        sprintf(msg, "%s: REGISTER %d NOT EXISTS", opcode, reg);
        DEBUG("CHECK_REG", msg);
        return -1;
    }
    return 0;
}
int CHECK_TYPE(const char* opcode, BYTE type, BYTE type2)
{
    if(type != type2)
    {
        char msg[1024];
        sprintf(msg, "%s: type incompatible to operation", opcode);
        DEBUG("CHECK_TYPE", msg);
        return -1;
    }
    return 0;
}
int CHECK_IMMVAL(const char* opcode, INSTR instr)
{
    if(instr.immval_len == 0)
    {
        char msg[1024];
        sprintf(msg, "%s: operand required", opcode);
        DEBUG("CHECK_IMMVAL", msg);
        return -1;
    }
    return 0;
}
#define check_fail(res) if(res == -1) { return -1; }

int FUNC_OP_MOV(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_MOV", "mov: instruction started");
    check_fail(CHECK_REG("mov", instr.reg1));
    check_fail(CHECK_REG("mov", instr.reg2));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    mov_reg(mem, instr.reg1, reg2_val.val, reg2_val.len);
    return 1;
}
#define get_reg_len(mem, reg) get_reg(mem, reg).len
#define get_reg_type(mem, reg) get_val_type(get_reg_len(mem, reg))
int FUNC_OP_MOVVB(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_MOVVB", "movvb: instruction started");
    check_fail(CHECK_REG("movvb", instr.reg1));
    check_fail(CHECK_IMMVAL("movvb", instr));
    check_fail(CHECK_TYPE("movvb", get_reg_type(mem, instr.reg1), TYPE_BYTE));
    check_fail(CHECK_TYPE("movvb", instr.immval_type, TYPE_BYTE));
    mov_reg(mem, instr.reg1, instr.immval, instr.immval_len);
    return 1;
}
int FUNC_OP_MOVVW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_MOVVW", "movvw: instruction started");
    check_fail(CHECK_REG("movvw", instr.reg1));
    check_fail(CHECK_IMMVAL("movvw", instr));
    check_fail(CHECK_TYPE("movvw", get_reg_type(mem, instr.reg1), TYPE_WORD));
    check_fail(CHECK_TYPE("movvw", instr.immval_type, TYPE_WORD));
    mov_reg(mem, instr.reg1, instr.immval, instr.immval_len);
    return 1;
}
int FUNC_OP_MOVVDW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_MOVVDW", "movvdw: instruction started");
    check_fail(CHECK_REG("movvdw", instr.reg1));
    check_fail(CHECK_IMMVAL("movvdw", instr));
    check_fail(CHECK_TYPE("movvdw", get_reg_type(mem, instr.reg1), TYPE_DWORD));
    check_fail(CHECK_TYPE("movvdw", instr.immval_type, TYPE_DWORD));
    mov_reg(mem, instr.reg1, instr.immval, instr.immval_len);
    return 1;
}
int FUNC_OP_MOVVQW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_MOVVQW", "movvqw: instruction started");
    check_fail(CHECK_REG("movvqw", instr.reg1));
    check_fail(CHECK_IMMVAL("movvqw", instr));
    check_fail(CHECK_TYPE("movvqw", get_reg_type(mem, instr.reg1), TYPE_QWORD));
    check_fail(CHECK_TYPE("movvqw", instr.immval_type, TYPE_QWORD));
    mov_reg(mem, instr.reg1, instr.immval, instr.immval_len);
    return 1;
}
int FUNC_OP_MOVMB(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_MOVMB", "movmb: instruction started");
    check_fail(CHECK_REG("movmb", instr.reg1));
    check_fail(CHECK_IMMVAL("movmb", instr));
    check_fail(CHECK_TYPE("movmb", instr.immval_type, TYPE_QWORD));
    BYTE byte;
    QWORD mem_set = to_qword(instr.immval);
    int res = get_mem(&byte, mem, mem_set);
    check_fail(res);
    mov_reg(mem, instr.reg2, b_to_bytes(byte), 1);
    return 1;
}
int FUNC_OP_MOVMW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_MOVMW", "movmw: instruction started");
    check_fail(CHECK_REG("movmw", instr.reg1));
    check_fail(CHECK_IMMVAL("movmw", instr));
    check_fail(CHECK_TYPE("movmw", instr.immval_type, TYPE_QWORD));
    BYTE* bytes = (BYTE*)malloc(2);
    QWORD mem_set = to_qword(instr.immval);
    for(int i = 0; i < 2; ++i)
    {
        int res = get_mem(&bytes[i], mem, mem_set+i);
        check_fail(res);
    }
    mov_reg(mem, instr.reg2, w_to_bytes(to_word(bytes)), 2);
    return 1;
}
int FUNC_OP_MOVMDW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_MOVMDW", "movmdw: instruction started");
    check_fail(CHECK_REG("movmdw", instr.reg1));
    check_fail(CHECK_IMMVAL("movmdw", instr));
    check_fail(CHECK_TYPE("movmdw", instr.immval_type, TYPE_QWORD));
    BYTE* bytes = (BYTE*)malloc(4);
    QWORD mem_set = to_qword(instr.immval);
    for(int i = 0; i < 4; ++i)
    {
        int res = get_mem(&bytes[i], mem, mem_set+i);
        check_fail(res);
    }
    mov_reg(mem, instr.reg2, dw_to_bytes(to_dword(bytes)), 4);
    return 1;
}
int FUNC_OP_MOVMQW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_MOVMQW", "movmqw: instruction started");
    check_fail(CHECK_REG("movmqw", instr.reg1));
    check_fail(CHECK_IMMVAL("movmqw", instr));
    check_fail(CHECK_TYPE("movmqw", instr.immval_type, TYPE_QWORD));
    BYTE* bytes = (BYTE*)malloc(8);
    QWORD mem_set = to_qword(instr.immval);
    for(int i = 0; i < 8; ++i)
    {
        int res = get_mem(&bytes[i], mem, mem_set+i);
        check_fail(res);
    }
    mov_reg(mem, instr.reg2, qw_to_bytes(to_qword(bytes)), 8);
    return 1;
}
int FUNC_OP_EXIT(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_EXIT", "exit: instruction started");
    return 0;
}
int FUNC_OP_ADDB(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_ADDB", "addb: instruction started");
    check_fail(CHECK_REG("addb", instr.reg1));
    check_fail(CHECK_REG("addb", instr.reg2));
    check_fail(CHECK_REG("addb", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("addb", reg2_type, TYPE_BYTE));
    check_fail(CHECK_TYPE("addb", reg3_type, TYPE_BYTE));
    mov_reg(mem, instr.reg1, b_to_bytes(to_byte(reg2_val.val) + to_byte(reg3_val.val)), 1);
    return 1;
}
int FUNC_OP_ADDW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_ADDW", "addw: instruction started");
    check_fail(CHECK_REG("addw", instr.reg2));
    check_fail(CHECK_REG("addw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("addw", reg2_type, TYPE_WORD));
    check_fail(CHECK_TYPE("addw", reg3_type, TYPE_WORD));
    mov_reg(mem, instr.reg1, w_to_bytes(to_word(reg2_val.val) + to_word(reg3_val.val)), 2);
    return 1;
}
int FUNC_OP_ADDDW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_ADDDW", "adddw: instruction started");
    check_fail(CHECK_REG("adddw", instr.reg2));
    check_fail(CHECK_REG("adddw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("adddw", reg2_type, TYPE_DWORD));
    check_fail(CHECK_TYPE("adddw", reg3_type, TYPE_DWORD));
    mov_reg(mem, instr.reg1, dw_to_bytes(to_dword(reg2_val.val) + to_dword(reg3_val.val)), 4);
    return 1;
}
int FUNC_OP_ADDQW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_ADDQW", "addqw: instruction started");
    check_fail(CHECK_REG("addqw", instr.reg2));
    check_fail(CHECK_REG("addqw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("addqw", reg2_type, TYPE_QWORD));
    check_fail(CHECK_TYPE("addqw", reg3_type, TYPE_QWORD));
    mov_reg(mem, instr.reg1, qw_to_bytes(to_qword(reg2_val.val) + to_qword(reg3_val.val)), 8);
    return 1;
}
int FUNC_OP_SUBB(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_SUBB", "subb: instruction started");
    check_fail(CHECK_REG("subb", instr.reg1));
    check_fail(CHECK_REG("subb", instr.reg2));
    check_fail(CHECK_REG("subb", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("subb", reg2_type, TYPE_BYTE));
    check_fail(CHECK_TYPE("subb", reg3_type, TYPE_BYTE));
    mov_reg(mem, instr.reg1, b_to_bytes(to_byte(reg2_val.val) - to_byte(reg3_val.val)), 1);
    return 1;
}
int FUNC_OP_SUBW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_SUBW", "subw: instruction started");
    check_fail(CHECK_REG("subw", instr.reg2));
    check_fail(CHECK_REG("subw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("subw", reg2_type, TYPE_WORD));
    check_fail(CHECK_TYPE("subw", reg3_type, TYPE_WORD));
    mov_reg(mem, instr.reg1, w_to_bytes(to_word(reg2_val.val) - to_word(reg3_val.val)), 2);
    return 1;
}
int FUNC_OP_SUBDW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_SUBDW", "subdw: instruction started");
    check_fail(CHECK_REG("subdw", instr.reg2));
    check_fail(CHECK_REG("subdw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("subdw", reg2_type, TYPE_DWORD));
    check_fail(CHECK_TYPE("subdw", reg3_type, TYPE_DWORD));
    mov_reg(mem, instr.reg1, dw_to_bytes(to_dword(reg2_val.val) - to_dword(reg3_val.val)), 4);
    return 1;
}
int FUNC_OP_SUBQW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_SUBQW", "subqw: instruction started");
    check_fail(CHECK_REG("subqw", instr.reg2));
    check_fail(CHECK_REG("subqw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("subqw", reg2_type, TYPE_QWORD));
    check_fail(CHECK_TYPE("subqw", reg3_type, TYPE_QWORD));
    mov_reg(mem, instr.reg1, qw_to_bytes(to_qword(reg2_val.val) - to_qword(reg3_val.val)), 8);
    return 1;
}
int FUNC_OP_MULB(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_MULB", "mulb: instruction started");
    check_fail(CHECK_REG("mulb", instr.reg1));
    check_fail(CHECK_REG("mulb", instr.reg2));
    check_fail(CHECK_REG("mulb", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("mulb", reg2_type, TYPE_BYTE));
    check_fail(CHECK_TYPE("mulb", reg3_type, TYPE_BYTE));
    mov_reg(mem, instr.reg1, b_to_bytes(to_byte(reg2_val.val) * to_byte(reg3_val.val)), 1);
    return 1;
}
int FUNC_OP_MULW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_MULW", "mulw: instruction started");
    check_fail(CHECK_REG("mulw", instr.reg2));
    check_fail(CHECK_REG("mulw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("mulw", reg2_type, TYPE_WORD));
    check_fail(CHECK_TYPE("mulw", reg3_type, TYPE_WORD));
    mov_reg(mem, instr.reg1, w_to_bytes(to_word(reg2_val.val) * to_word(reg3_val.val)), 2);
    return 1;
}
int FUNC_OP_MULDW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_MULDW", "muldw: instruction started");
    check_fail(CHECK_REG("muldw", instr.reg2));
    check_fail(CHECK_REG("muldw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("muldw", reg2_type, TYPE_DWORD));
    check_fail(CHECK_TYPE("muldw", reg3_type, TYPE_DWORD));
    mov_reg(mem, instr.reg1, dw_to_bytes(to_dword(reg2_val.val) * to_dword(reg3_val.val)), 4);
    return 1;
}
int FUNC_OP_MULQW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_MULQW", "mulqw: instruction started");
    check_fail(CHECK_REG("mulqw", instr.reg2));
    check_fail(CHECK_REG("mulqw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("mulqw", reg2_type, TYPE_QWORD));
    check_fail(CHECK_TYPE("mulqw", reg3_type, TYPE_QWORD));
    mov_reg(mem, instr.reg1, qw_to_bytes(to_qword(reg2_val.val) * to_qword(reg3_val.val)), 8);
    return 1;
}
int FUNC_OP_DIVB(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_DIVB", "divb: instruction started");
    check_fail(CHECK_REG("divb", instr.reg1));
    check_fail(CHECK_REG("divb", instr.reg2));
    check_fail(CHECK_REG("divb", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("divb", reg2_type, TYPE_BYTE));
    check_fail(CHECK_TYPE("divb", reg3_type, TYPE_BYTE));
    mov_reg(mem, instr.reg1, b_to_bytes(to_byte(reg2_val.val) / to_byte(reg3_val.val)), 1);
    return 1;
}
int FUNC_OP_DIVW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_DIVW", "divw: instruction started");
    check_fail(CHECK_REG("divw", instr.reg2));
    check_fail(CHECK_REG("divw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("divw", reg2_type, TYPE_WORD));
    check_fail(CHECK_TYPE("divw", reg3_type, TYPE_WORD));
    mov_reg(mem, instr.reg1, w_to_bytes(to_word(reg2_val.val) / to_word(reg3_val.val)), 2);
    return 1;
}
int FUNC_OP_DIVDW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_DIVDW", "divdw: instruction started");
    check_fail(CHECK_REG("divdw", instr.reg2));
    check_fail(CHECK_REG("divdw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("divdw", reg2_type, TYPE_DWORD));
    check_fail(CHECK_TYPE("divdw", reg3_type, TYPE_DWORD));
    mov_reg(mem, instr.reg1, dw_to_bytes(to_dword(reg2_val.val) / to_dword(reg3_val.val)), 4);
    return 1;
}
int FUNC_OP_DIVQW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_DIVQW", "divqw: instruction started");
    check_fail(CHECK_REG("divqw", instr.reg2));
    check_fail(CHECK_REG("divqw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("divqw", reg2_type, TYPE_QWORD));
    check_fail(CHECK_TYPE("divqw", reg3_type, TYPE_QWORD));
    mov_reg(mem, instr.reg1, qw_to_bytes(to_qword(reg2_val.val) / to_qword(reg3_val.val)), 8);
    return 1;
}
int FUNC_OP_MODB(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_MODB", "modb: instruction started");
    check_fail(CHECK_REG("modb", instr.reg1));
    check_fail(CHECK_REG("modb", instr.reg2));
    check_fail(CHECK_REG("modb", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("modb", reg2_type, TYPE_BYTE));
    check_fail(CHECK_TYPE("modb", reg3_type, TYPE_BYTE));
    mov_reg(mem, instr.reg1, b_to_bytes(to_byte(reg2_val.val) % to_byte(reg3_val.val)), 1);
    return 1;
}
int FUNC_OP_MODW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_MODW", "modw: instruction started");
    check_fail(CHECK_REG("modw", instr.reg2));
    check_fail(CHECK_REG("modw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("modw", reg2_type, TYPE_WORD));
    check_fail(CHECK_TYPE("modw", reg3_type, TYPE_WORD));
    mov_reg(mem, instr.reg1, w_to_bytes(to_word(reg2_val.val) % to_word(reg3_val.val)), 2);
    return 1;
}
int FUNC_OP_MODDW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_MODDW", "moddw: instruction started");
    check_fail(CHECK_REG("moddw", instr.reg2));
    check_fail(CHECK_REG("moddw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("moddw", reg2_type, TYPE_DWORD));
    check_fail(CHECK_TYPE("moddw", reg3_type, TYPE_DWORD));
    mov_reg(mem, instr.reg1, dw_to_bytes(to_dword(reg2_val.val) % to_dword(reg3_val.val)), 4);
    return 1;
}
int FUNC_OP_MODQW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_MODQW", "modqw: instruction started");
    check_fail(CHECK_REG("modqw", instr.reg2));
    check_fail(CHECK_REG("modqw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("modqw", reg2_type, TYPE_QWORD));
    check_fail(CHECK_TYPE("modqw", reg3_type, TYPE_QWORD));
    mov_reg(mem, instr.reg1, qw_to_bytes(to_qword(reg2_val.val) % to_qword(reg3_val.val)), 8);
    return 1;
}
int FUNC_OP_ANDB(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_ANDB", "andb: instruction started");
    check_fail(CHECK_REG("andb", instr.reg2));
    check_fail(CHECK_REG("andb", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("andb", reg2_type, TYPE_BYTE));
    check_fail(CHECK_TYPE("andb", reg3_type, TYPE_BYTE));
    mov_reg(mem, instr.reg1, b_to_bytes(to_byte(reg2_val.val) & to_byte(reg3_val.val)), 1);
    return 1;
}
int FUNC_OP_ANDW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_ANDW", "andw: instruction started");
    check_fail(CHECK_REG("andw", instr.reg2));
    check_fail(CHECK_REG("andw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("andw", reg2_type, TYPE_WORD));
    check_fail(CHECK_TYPE("andw", reg3_type, TYPE_WORD));
    mov_reg(mem, instr.reg1, w_to_bytes(to_word(reg2_val.val) & to_word(reg3_val.val)), 2);
    return 1;
}
int FUNC_OP_ANDDW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_ANDDW", "anddw: instruction started");
    check_fail(CHECK_REG("anddw", instr.reg2));
    check_fail(CHECK_REG("anddw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("anddw", reg2_type, TYPE_DWORD));
    check_fail(CHECK_TYPE("anddw", reg3_type, TYPE_DWORD));
    mov_reg(mem, instr.reg1, dw_to_bytes(to_dword(reg2_val.val) & to_dword(reg3_val.val)), 4);
    return 1;
}
int FUNC_OP_ANDQW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_ANDQW", "andqw: instruction started");
    check_fail(CHECK_REG("andqw", instr.reg2));
    check_fail(CHECK_REG("andqw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("andqw", reg2_type, TYPE_QWORD));
    check_fail(CHECK_TYPE("andqw", reg3_type, TYPE_QWORD));
    mov_reg(mem, instr.reg1, qw_to_bytes(to_qword(reg2_val.val) & to_qword(reg3_val.val)), 8);
    return 1;
}
int FUNC_OP_ORB(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_ORB", "orb: instruction started");
    check_fail(CHECK_REG("orb", instr.reg2));
    check_fail(CHECK_REG("orb", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("orb", reg2_type, TYPE_BYTE));
    check_fail(CHECK_TYPE("orb", reg3_type, TYPE_BYTE));
    mov_reg(mem, instr.reg1, b_to_bytes(to_byte(reg2_val.val) | to_byte(reg3_val.val)), 1);
    return 1;
}
int FUNC_OP_ORW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_ORW", "orw: instruction started");
    check_fail(CHECK_REG("orw", instr.reg2));
    check_fail(CHECK_REG("orw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("orw", reg2_type, TYPE_WORD));
    check_fail(CHECK_TYPE("orw", reg3_type, TYPE_WORD));
    mov_reg(mem, instr.reg1, w_to_bytes(to_word(reg2_val.val) | to_word(reg3_val.val)), 2);
    return 1;
}
int FUNC_OP_ORDW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_ORDW", "ordw: instruction started");
    check_fail(CHECK_REG("ordw", instr.reg2));
    check_fail(CHECK_REG("ordw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("ordw", reg2_type, TYPE_DWORD));
    check_fail(CHECK_TYPE("ordw", reg3_type, TYPE_DWORD));
    mov_reg(mem, instr.reg1, dw_to_bytes(to_dword(reg2_val.val) | to_dword(reg3_val.val)), 4);
    return 1;
}
int FUNC_OP_ORQW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_ORQW", "orqw: instruction started");
    check_fail(CHECK_REG("orqw", instr.reg2));
    check_fail(CHECK_REG("orqw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("orqw", reg2_type, TYPE_QWORD));
    check_fail(CHECK_TYPE("orqw", reg3_type, TYPE_QWORD));
    mov_reg(mem, instr.reg1, qw_to_bytes(to_qword(reg2_val.val) | to_qword(reg3_val.val)), 8);
    return 1;
}
int FUNC_OP_XORB(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_XORB", "xorb: instruction started");
    check_fail(CHECK_REG("xorb", instr.reg2));
    check_fail(CHECK_REG("xorb", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("xorb", reg2_type, TYPE_BYTE));
    check_fail(CHECK_TYPE("xorb", reg3_type, TYPE_BYTE));
    mov_reg(mem, instr.reg1, b_to_bytes(to_byte(reg2_val.val) ^ to_byte(reg3_val.val)), 1);
    return 1;
}
int FUNC_OP_XORW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_XORW", "xorw: instruction started");
    check_fail(CHECK_REG("xorw", instr.reg2));
    check_fail(CHECK_REG("xorw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("xorw", reg2_type, TYPE_WORD));
    check_fail(CHECK_TYPE("xorw", reg3_type, TYPE_WORD));
    mov_reg(mem, instr.reg1, w_to_bytes(to_word(reg2_val.val) ^ to_word(reg3_val.val)), 2);
    return 1;
}
int FUNC_OP_XORDW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_XORDW", "xordw: instruction started");
    check_fail(CHECK_REG("xordw", instr.reg2));
    check_fail(CHECK_REG("xordw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("xordw", reg2_type, TYPE_DWORD));
    check_fail(CHECK_TYPE("xordw", reg3_type, TYPE_DWORD));
    mov_reg(mem, instr.reg1, dw_to_bytes(to_dword(reg2_val.val) ^ to_dword(reg3_val.val)), 4);
    return 1;
}
int FUNC_OP_XORQW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_XORQW", "xorqw: instruction started");
    check_fail(CHECK_REG("xorqw", instr.reg2));
    check_fail(CHECK_REG("xorqw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("xorqw", reg2_type, TYPE_QWORD));
    check_fail(CHECK_TYPE("xorqw", reg3_type, TYPE_QWORD));
    mov_reg(mem, instr.reg1, qw_to_bytes(to_qword(reg2_val.val) ^ to_qword(reg3_val.val)), 8);
    return 1;
}
int FUNC_OP_SHRB(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_SHRB", "shrb: instruction started");
    check_fail(CHECK_REG("shrb", instr.reg2));
    check_fail(CHECK_REG("shrb", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("shrb", reg2_type, TYPE_BYTE));
    check_fail(CHECK_TYPE("shrb", reg3_type, TYPE_BYTE));
    mov_reg(mem, instr.reg1, b_to_bytes(to_byte(reg2_val.val) >> to_byte(reg3_val.val)), 1);
    return 1;
}
int FUNC_OP_SHRW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_SHRW", "shrw: instruction started");
    check_fail(CHECK_REG("shrw", instr.reg2));
    check_fail(CHECK_REG("shrw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("shrw", reg2_type, TYPE_WORD));
    check_fail(CHECK_TYPE("shrw", reg3_type, TYPE_WORD));
    mov_reg(mem, instr.reg1, w_to_bytes(to_word(reg2_val.val) >> to_word(reg3_val.val)), 2);
    return 1;
}
int FUNC_OP_SHRDW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_SHRDW", "shrdw: instruction started");
    check_fail(CHECK_REG("shrdw", instr.reg2));
    check_fail(CHECK_REG("shrdw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("shrdw", reg2_type, TYPE_DWORD));
    check_fail(CHECK_TYPE("shrdw", reg3_type, TYPE_DWORD));
    mov_reg(mem, instr.reg1, dw_to_bytes(to_dword(reg2_val.val) >> to_dword(reg3_val.val)), 4);
    return 1;
}
int FUNC_OP_SHRQW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_SHRQW", "shrqw: instruction started");
    check_fail(CHECK_REG("shrqw", instr.reg2));
    check_fail(CHECK_REG("shrqw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("shrqw", reg2_type, TYPE_QWORD));
    check_fail(CHECK_TYPE("shrqw", reg3_type, TYPE_QWORD));
    mov_reg(mem, instr.reg1, qw_to_bytes(to_qword(reg2_val.val) >> to_qword(reg3_val.val)), 8);
    return 1;
}
int FUNC_OP_SHLB(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_SHLB", "shlb: instruction started");
    check_fail(CHECK_REG("shlb", instr.reg2));
    check_fail(CHECK_REG("shlb", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("shlb", reg2_type, TYPE_BYTE));
    check_fail(CHECK_TYPE("shlb", reg3_type, TYPE_BYTE));
    mov_reg(mem, instr.reg1, b_to_bytes(to_byte(reg2_val.val) << to_byte(reg3_val.val)), 1);
    return 1;
}
int FUNC_OP_SHLW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_SHLW", "shlw: instruction started");
    check_fail(CHECK_REG("shlw", instr.reg2));
    check_fail(CHECK_REG("shlw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("shlw", reg2_type, TYPE_WORD));
    check_fail(CHECK_TYPE("shlw", reg3_type, TYPE_WORD));
    mov_reg(mem, instr.reg1, w_to_bytes(to_word(reg2_val.val) << to_word(reg3_val.val)), 2);
    return 1;
}
int FUNC_OP_SHLDW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_SHLDW", "shldw: instruction started");
    check_fail(CHECK_REG("shldw", instr.reg2));
    check_fail(CHECK_REG("shldw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("shldw", reg2_type, TYPE_DWORD));
    check_fail(CHECK_TYPE("shldw", reg3_type, TYPE_DWORD));
    mov_reg(mem, instr.reg1, dw_to_bytes(to_dword(reg2_val.val) << to_dword(reg3_val.val)), 4);
    return 1;
}
int FUNC_OP_SHLQW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_SHLQW", "shlqw: instruction started");
    check_fail(CHECK_REG("shlqw", instr.reg2));
    check_fail(CHECK_REG("shlqw", instr.reg3));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    BYTE reg2_type = get_val_type(reg2_val.len);
    BYTE reg3_type = get_val_type(reg3_val.len);
    check_fail(CHECK_TYPE("shlqw", reg2_type, TYPE_QWORD));
    check_fail(CHECK_TYPE("shlqw", reg3_type, TYPE_QWORD));
    mov_reg(mem, instr.reg1, qw_to_bytes(to_qword(reg2_val.val) << to_qword(reg3_val.val)), 8);
    return 1;
}
int FUNC_OP_SETM(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_SETM", "setm: instruction started");
    check_fail(CHECK_REG("setm", instr.reg1));
    check_fail(CHECK_IMMVAL("setm", instr));
    REG_VAL reg1_val = get_reg(mem, instr.reg1);
    BYTE reg1_type = get_val_type(reg1_val.len);
    check_fail(CHECK_TYPE("setm", reg1_type, TYPE_BYTE));
    check_fail(CHECK_TYPE("setm", instr.immval_type, TYPE_QWORD));
    set_mem(mem, to_byte(reg1_val.val), to_qword(instr.immval));
    return 1;
}
int FUNC_OP_REDM(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_REDM", "redm: instruction started");
    check_fail(CHECK_IMMVAL("redm", instr));
    check_fail(CHECK_TYPE("redm", instr.immval_type, TYPE_QWORD));
    if(red_mem(mem, to_qword(instr.immval)) < 0)
    {
        DEBUG("FUNC_OP_REDM", "redm: operand is more than / same with memory length");
        return -1;
    }
    return 1;
}
int FUNC_OP_SYSCALL(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_SYSCALL", "syscall: instruction started");
    REG_VAL r1_val = get_reg(mem, R1);
    check_fail(CHECK_TYPE("syscall", get_val_type(r1_val.len), TYPE_BYTE));
    BYTE syscall_no = to_byte(r1_val.val);
    if(syscall_no >= SYSCALL_MAX)
    {
        DEBUG("FUNC_OP_SYSCALL", "syscall: unknown syscall");
        return -1;
    }
    int syscall_res = FUNC_SYSCALL[syscall_no](mem);
    if(syscall_res == SYSCALL_FAIL)
    {
        DEBUG("FUNC_OP_SYSCALL", "syscall: failed");
        return -1;
    }
    return 1;
}
int FUNC_OP_JMP(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_JMP", "jmp: instruction started");
    check_fail(CHECK_IMMVAL("jmp", instr));
    check_fail(CHECK_TYPE("jmp", instr.immval_type, TYPE_QWORD));
    return 2;
}
int FUNC_OP_CMPB(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_CMPB", "cmpb: instruction started");
    check_fail(CHECK_REG("cmpb", instr.reg1));
    check_fail(CHECK_REG("cmpb", instr.reg2));
    check_fail(CHECK_REG("cmpb", instr.reg3));
    REG_VAL reg1_val = get_reg(mem, instr.reg1);
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    check_fail(CHECK_TYPE("cmpb", get_val_type(reg1_val.len), TYPE_BYTE));
    check_fail(CHECK_TYPE("cmpb", get_val_type(reg2_val.len), TYPE_BYTE));
    check_fail(CHECK_TYPE("cmpb", get_val_type(reg3_val.len), TYPE_BYTE));
    BYTE val1 = to_byte(reg2_val.val);
    BYTE val2 = to_byte(reg3_val.val);
    if(val1 == val2)
    {
        mov_reg(mem, instr.reg1, b_to_bytes(1), 1);
    }
    else if(val1 > val2)
    {
        mov_reg(mem, instr.reg1, b_to_bytes(2), 1);
    }
    else if(val1 < val2)
    {
        mov_reg(mem, instr.reg2, b_to_bytes(3), 1);
    }
    return 1;
}
int FUNC_OP_CMPW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_CMPW", "cmpw: instruction started");
    check_fail(CHECK_REG("cmpw", instr.reg1));
    check_fail(CHECK_REG("cmpw", instr.reg2));
    check_fail(CHECK_REG("cmpw", instr.reg3));
    REG_VAL reg1_val = get_reg(mem, instr.reg1);
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    check_fail(CHECK_TYPE("cmpw", get_val_type(reg1_val.len), TYPE_BYTE));
    check_fail(CHECK_TYPE("cmpw", get_val_type(reg2_val.len), TYPE_WORD));
    check_fail(CHECK_TYPE("cmpw", get_val_type(reg3_val.len), TYPE_WORD));
    WORD val1 = to_word(reg2_val.val);
    WORD val2 = to_word(reg3_val.val);
    if(val1 == val2)
    {
        mov_reg(mem, instr.reg1, b_to_bytes(1), 1);
    }
    else if(val1 > val2)
    {
        mov_reg(mem, instr.reg1, b_to_bytes(2), 1);
    }
    else if(val1 < val2)
    {
        mov_reg(mem, instr.reg2, b_to_bytes(3), 1);
    }
    return 1;
}
int FUNC_OP_CMPDW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_CMPDW", "cmpdw: instruction started");
    check_fail(CHECK_REG("cmpdw", instr.reg1));
    check_fail(CHECK_REG("cmpdw", instr.reg2));
    check_fail(CHECK_REG("cmpdw", instr.reg3));
    REG_VAL reg1_val = get_reg(mem, instr.reg1);
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    check_fail(CHECK_TYPE("cmpdw", get_val_type(reg1_val.len), TYPE_BYTE));
    check_fail(CHECK_TYPE("cmpdw", get_val_type(reg2_val.len), TYPE_DWORD));
    check_fail(CHECK_TYPE("cmpdw", get_val_type(reg3_val.len), TYPE_DWORD));
    DWORD val1 = to_dword(reg2_val.val);
    DWORD val2 = to_dword(reg3_val.val);
    if(val1 == val2)
    {
        mov_reg(mem, instr.reg1, b_to_bytes(1), 1);
    }
    else if(val1 > val2)
    {
        mov_reg(mem, instr.reg1, b_to_bytes(2), 1);
    }
    else if(val1 < val2)
    {
        mov_reg(mem, instr.reg2, b_to_bytes(3), 1);
    }
    return 1;
}
int FUNC_OP_CMPQW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_CMPQW", "cmpqw: instruction started");
    check_fail(CHECK_REG("cmpqw", instr.reg1));
    check_fail(CHECK_REG("cmpqw", instr.reg2));
    check_fail(CHECK_REG("cmpqw", instr.reg3));
    REG_VAL reg1_val = get_reg(mem, instr.reg1);
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    REG_VAL reg3_val = get_reg(mem, instr.reg3);
    check_fail(CHECK_TYPE("cmpqw", get_val_type(reg1_val.len), TYPE_BYTE));
    check_fail(CHECK_TYPE("cmpqw", get_val_type(reg2_val.len), TYPE_QWORD));
    check_fail(CHECK_TYPE("cmpqw", get_val_type(reg3_val.len), TYPE_QWORD));
    QWORD val1 = to_qword(reg2_val.val);
    QWORD val2 = to_qword(reg3_val.val);
    if(val1 == val2)
    {
        mov_reg(mem, instr.reg1, b_to_bytes(1), 1);
    }
    else if(val1 > val2)
    {
        mov_reg(mem, instr.reg1, b_to_bytes(2), 1);
    }
    else if(val1 < val2)
    {
        mov_reg(mem, instr.reg2, b_to_bytes(3), 1);
    }
    return 1;
}
int FUNC_OP_JE(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_JE", "je: instruction started");
    check_fail(CHECK_REG("je", instr.reg1));
    REG_VAL reg1_val = get_reg(mem, instr.reg1);
    check_fail(CHECK_TYPE("je", get_val_type(reg1_val.len), TYPE_BYTE));
    check_fail(CHECK_IMMVAL("je", instr));
    check_fail(CHECK_TYPE("je", instr.immval_type, TYPE_QWORD));
    if(to_byte(reg1_val.val) == 1)
    {
        return 2;
    }
    return 1;
}
int FUNC_OP_JNE(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_JNE", "jne: instruction started");
    check_fail(CHECK_REG("jne", instr.reg1));
    REG_VAL reg1_val = get_reg(mem, instr.reg1);
    check_fail(CHECK_TYPE("jne", get_val_type(reg1_val.len), TYPE_BYTE));
    check_fail(CHECK_IMMVAL("jne", instr));
    check_fail(CHECK_TYPE("jne", instr.immval_type, TYPE_QWORD));
    if(to_byte(reg1_val.val) == 2 || to_byte(reg1_val.val) == 3)
    {
        return 2;
    }
    return 1;
}
int FUNC_OP_JL(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_JL", "jl: instruction started");
    check_fail(CHECK_REG("jl", instr.reg1));
    REG_VAL reg1_val = get_reg(mem, instr.reg1);
    check_fail(CHECK_TYPE("jl", get_val_type(reg1_val.len), TYPE_BYTE));
    check_fail(CHECK_IMMVAL("jl", instr));
    check_fail(CHECK_TYPE("jl", instr.immval_type, TYPE_QWORD));
    if(to_byte(reg1_val.val) == 3)
    {
        return 2;
    }
    return 1;
}
int FUNC_OP_JG(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_JG", "jg: instruction started");
    check_fail(CHECK_REG("jg", instr.reg1));
    REG_VAL reg1_val = get_reg(mem, instr.reg1);
    check_fail(CHECK_TYPE("jg", get_val_type(reg1_val.len), TYPE_BYTE));
    check_fail(CHECK_IMMVAL("jg", instr));
    check_fail(CHECK_TYPE("jg", instr.immval_type, TYPE_QWORD));
    if(to_byte(reg1_val.val) == 2)
    {
        return 2;
    }
    return 1;
}
int FUNC_OP_LDB(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_LDB", "ldb: instruction started");
    check_fail(CHECK_REG("ldb", instr.reg1));
    mov_reg(mem, instr.reg1, b_to_bytes((BYTE)0), 1);
    return 1;
}
int FUNC_OP_LDW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_LDW", "ldw: instruction started");
    check_fail(CHECK_REG("ldw", instr.reg1));
    mov_reg(mem, instr.reg1, w_to_bytes((WORD)0), 2);
    return 1;
}
int FUNC_OP_LDDW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_LDDW", "lddw: instruction started");
    check_fail(CHECK_REG("lddw", instr.reg1));
    mov_reg(mem, instr.reg1, dw_to_bytes((DWORD)0), 4);
    return 1;
}
int FUNC_OP_LDQW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_LDQW", "ldqw: instruction started");
    check_fail(CHECK_REG("ldqw", instr.reg1));
    mov_reg(mem, instr.reg1, qw_to_bytes((QWORD)0), 8);
    return 1;
}
int FUNC_OP_CONVB(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_CONVB", "convb: instruction started");
    check_fail(CHECK_REG("convb", instr.reg1));
    switch(get_reg_type(mem, instr.reg1))
    {
        case TYPE_BYTE: 
            break;
        case TYPE_WORD:
            mov_reg(mem, instr.reg1, b_to_bytes((get_reg(mem, instr.reg1)).val[0]), 1);
            break;
        case TYPE_DWORD:
            mov_reg(mem, instr.reg1, b_to_bytes((get_reg(mem, instr.reg1)).val[0]), 1);
            break;
        case TYPE_QWORD:
            mov_reg(mem, instr.reg1, b_to_bytes((get_reg(mem, instr.reg1)).val[0]), 1);
            break;
        default:
            mov_reg(mem, instr.reg1, b_to_bytes((BYTE)0), 1);
            break;
    }
    return 1;
}
int FUNC_OP_CONVW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_CONVW", "convw: instruction started");
    check_fail(CHECK_REG("convw", instr.reg1));
    switch(get_reg_type(mem, instr.reg1))
    {
        case TYPE_BYTE: 
            {
                REG_VAL reg1_val = get_reg(mem, instr.reg1);
                BYTE* bytes = (BYTE*)malloc(sizeof(BYTE)*2);
                bytes[0] = 0;
                bytes[1] = reg1_val.val[0];
                mov_reg(mem, instr.reg1, bytes, 2);
            }
            break;
        case TYPE_WORD:
            {
                REG_VAL reg1_val = get_reg(mem, instr.reg1);
                BYTE* bytes = (BYTE*)malloc(sizeof(BYTE)*2);
                bytes[0] = reg1_val.val[0];
                bytes[1] = reg1_val.val[1];
                mov_reg(mem, instr.reg1, bytes, 2);
            }
            break;
        case TYPE_DWORD:
            {
                REG_VAL reg1_val = get_reg(mem, instr.reg1);
                BYTE* bytes = (BYTE*)malloc(sizeof(BYTE)*2);
                bytes[0] = reg1_val.val[2];
                bytes[1] = reg1_val.val[3];
                mov_reg(mem, instr.reg1, bytes, 2);
            }
            break;
        case TYPE_QWORD:
            {
                REG_VAL reg1_val = get_reg(mem, instr.reg1);
                BYTE* bytes = (BYTE*)malloc(sizeof(BYTE)*2);
                bytes[0] = reg1_val.val[6];
                bytes[1] = reg1_val.val[7];
                mov_reg(mem, instr.reg1, bytes, 2);
            }
            break;
        default:
            mov_reg(mem, instr.reg1, w_to_bytes((WORD)0), 2);
            break;
    }
    return 1;
}
int FUNC_OP_CONVDW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_CONVDW", "convdw: instruction started");
    check_fail(CHECK_REG("convdw", instr.reg1));
    switch(get_reg_type(mem, instr.reg1))
    {
        case TYPE_BYTE: 
            {
                REG_VAL reg1_val = get_reg(mem, instr.reg1);
                BYTE* bytes = (BYTE*)malloc(sizeof(BYTE)*4);
                bytes[0] = 0;
                bytes[1] = 0;
                bytes[2] = 0;
                bytes[3] = reg1_val.val[0];
                mov_reg(mem, instr.reg1, bytes, 4);
            }
            break;
        case TYPE_WORD:
            {
                REG_VAL reg1_val = get_reg(mem, instr.reg1);
                BYTE* bytes = (BYTE*)malloc(sizeof(BYTE)*4);
                bytes[0] = 0;
                bytes[1] = 0;
                bytes[2] = reg1_val.val[0];
                bytes[3] = reg1_val.val[1];
                mov_reg(mem, instr.reg1, bytes, 4);
            }
            break;
        case TYPE_DWORD:
            {
                REG_VAL reg1_val = get_reg(mem, instr.reg1);
                BYTE* bytes = (BYTE*)malloc(sizeof(BYTE)*4);
                bytes[0] = reg1_val.val[0];
                bytes[1] = reg1_val.val[1];
                bytes[2] = reg1_val.val[2];
                bytes[3] = reg1_val.val[3];
                mov_reg(mem, instr.reg1, bytes, 4);
            }
            break;
        case TYPE_QWORD:
            {
                REG_VAL reg1_val = get_reg(mem, instr.reg1);
                BYTE* bytes = (BYTE*)malloc(sizeof(BYTE)*4);
                bytes[0] = reg1_val.val[4];
                bytes[1] = reg1_val.val[5];
                bytes[2] = reg1_val.val[6];
                bytes[3] = reg1_val.val[7];
                mov_reg(mem, instr.reg1, bytes, 4);
            }
            break;
        default:
            mov_reg(mem, instr.reg1, dw_to_bytes((DWORD)0), 4);
            break;
    }
    return 1;
}
int FUNC_OP_CONVQW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_CONVQW", "convqw: instruction started");
    check_fail(CHECK_REG("convqw", instr.reg1));
    switch(get_reg_type(mem, instr.reg1))
    {
        case TYPE_BYTE: 
            {
                REG_VAL reg1_val = get_reg(mem, instr.reg1);
                BYTE* bytes = (BYTE*)malloc(sizeof(BYTE)*8);
                bytes[0] = 0;
                bytes[1] = 0;
                bytes[2] = 0;
                bytes[3] = 0;
                bytes[4] = 0;
                bytes[5] = 0;
                bytes[6] = 0;
                bytes[7] = reg1_val.val[0];
                mov_reg(mem, instr.reg1, bytes, 8);
            }
            break;
        case TYPE_WORD:
            {
                REG_VAL reg1_val = get_reg(mem, instr.reg1);
                BYTE* bytes = (BYTE*)malloc(sizeof(BYTE)*8);
                bytes[0] = 0;
                bytes[1] = 0;
                bytes[2] = 0;
                bytes[3] = 0;
                bytes[4] = 0;
                bytes[5] = 0;
                bytes[6] = reg1_val.val[0];
                bytes[7] = reg1_val.val[1];
                mov_reg(mem, instr.reg1, bytes, 8);
            }
            break;
        case TYPE_DWORD:
            {
                REG_VAL reg1_val = get_reg(mem, instr.reg1);
                BYTE* bytes = (BYTE*)malloc(sizeof(BYTE)*8);
                bytes[0] = 0;
                bytes[1] = 0;
                bytes[2] = 0;
                bytes[3] = 0;
                bytes[4] = reg1_val.val[0];
                bytes[5] = reg1_val.val[1];
                bytes[6] = reg1_val.val[2];
                bytes[7] = reg1_val.val[3];
                mov_reg(mem, instr.reg1, bytes, 8);
            }
            break;
        case TYPE_QWORD:
            {
                REG_VAL reg1_val = get_reg(mem, instr.reg1);
                BYTE* bytes = (BYTE*)malloc(sizeof(BYTE)*8);
                bytes[0] = reg1_val.val[0];
                bytes[1] = reg1_val.val[1];
                bytes[2] = reg1_val.val[2];
                bytes[3] = reg1_val.val[3];
                bytes[4] = reg1_val.val[4];
                bytes[5] = reg1_val.val[5];
                bytes[6] = reg1_val.val[6];
                bytes[7] = reg1_val.val[7];
                mov_reg(mem, instr.reg1, bytes, 8);
            }
            break;
        default:
            mov_reg(mem, instr.reg1, dw_to_bytes((QWORD)0), 8);
            break;
    }
    return 1;
}
int FUNC_OP_PUSH(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_PUSH", "push: instruction started");
    check_fail(CHECK_REG("push", instr.reg1));
    check_fail(CHECK_TYPE("push", get_reg_type(mem, instr.reg1), TYPE_BYTE));
    stack_push(vmem_pstack(mem),get_reg(mem, instr.reg1).val, 1);
    return 1;
}
int FUNC_OP_POP(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_POP", "pop: instruction started");
    check_fail(CHECK_REG("pop", instr.reg1));
    check_fail(CHECK_TYPE("pop", get_reg_type(mem, instr.reg1), TYPE_BYTE));
    BYTE* bytes = stack_pop(vmem_pstack(mem));
    if(bytes == NULL)
    {
        DEBUG("FUNC_OP_POP", "pop: stack empty");
        return -1;
    }
    mov_reg(mem, instr.reg1, bytes, 1);
    return 1;
}
int FUNC_OP_NEGB(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_NEGB", "negb: instruction started");
    check_fail(CHECK_REG("negb", instr.reg1));
    check_fail(CHECK_TYPE("negb", get_reg_type(mem, instr.reg1), TYPE_BYTE));
    check_fail(CHECK_REG("negb", instr.reg2));
    check_fail(CHECK_TYPE("negb", get_reg_type(mem, instr.reg2), TYPE_BYTE));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    BYTE res = ~(to_byte(reg2_val.val));
    mov_reg(mem, instr.reg1, b_to_bytes(res), 1);
    return 1;
}
int FUNC_OP_NEGW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_NEGW", "negw: instruction started");
    check_fail(CHECK_REG("negw", instr.reg1));
    check_fail(CHECK_TYPE("negw", get_reg_type(mem, instr.reg1), TYPE_WORD));
    check_fail(CHECK_REG("negw", instr.reg2));
    check_fail(CHECK_TYPE("negw", get_reg_type(mem, instr.reg2), TYPE_WORD));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    WORD res = ~(to_word(reg2_val.val));
    mov_reg(mem, instr.reg1, w_to_bytes(res), 2);
    return 1;
}
int FUNC_OP_NEGDW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_NEGDW", "negdw: instruction started");
    check_fail(CHECK_REG("negdw", instr.reg1));
    check_fail(CHECK_TYPE("negdw", get_reg_type(mem, instr.reg1), TYPE_DWORD));
    check_fail(CHECK_REG("negdw", instr.reg2));
    check_fail(CHECK_TYPE("negdw", get_reg_type(mem, instr.reg2), TYPE_DWORD));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    DWORD res = ~(to_dword(reg2_val.val));
    mov_reg(mem, instr.reg1, dw_to_bytes(res), 4);
    return 1;
}
int FUNC_OP_NEGQW(VMEM* mem, INSTR instr)
{
    DEBUG("FUNC_OP_NEGQW", "negqw: instruction started");
    check_fail(CHECK_REG("negqw", instr.reg1));
    check_fail(CHECK_TYPE("negqw", get_reg_type(mem, instr.reg1), TYPE_QWORD));
    check_fail(CHECK_REG("negqw", instr.reg2));
    check_fail(CHECK_TYPE("negqw", get_reg_type(mem, instr.reg2), TYPE_QWORD));
    REG_VAL reg2_val = get_reg(mem, instr.reg2);
    QWORD res = ~(to_qword(reg2_val.val));
    mov_reg(mem, instr.reg1, qw_to_bytes(res), 8);
    return 1;
}
void init_op_functions()
{
    DEBUG("init_op_functions", "initializing op functions");
    FUNC_OP[OP_MOV] = FUNC_OP_MOV;
    FUNC_OP[OP_EXIT] = FUNC_OP_EXIT;
    FUNC_OP[OP_MOVVB] = FUNC_OP_MOVVB;
    FUNC_OP[OP_MOVVW] = FUNC_OP_MOVVW;
    FUNC_OP[OP_MOVVDW] = FUNC_OP_MOVVDW;
    FUNC_OP[OP_MOVVQW] = FUNC_OP_MOVVQW;
    FUNC_OP[OP_MOVMB] = FUNC_OP_MOVMB,
    FUNC_OP[OP_MOVMW] = FUNC_OP_MOVMW;
    FUNC_OP[OP_MOVMB] = FUNC_OP_MOVMB;
    FUNC_OP[OP_MOVMW] = FUNC_OP_MOVMW;
    FUNC_OP[OP_MOVMDW] = FUNC_OP_MOVMDW;
    FUNC_OP[OP_MOVMQW] = FUNC_OP_MOVMQW;
    FUNC_OP[OP_ADDB] = FUNC_OP_ADDB;
    FUNC_OP[OP_ADDW] = FUNC_OP_ADDW;
    FUNC_OP[OP_ADDDW] = FUNC_OP_ADDDW;
    FUNC_OP[OP_SUBB] = FUNC_OP_SUBB;
    FUNC_OP[OP_SUBW] = FUNC_OP_SUBW;
    FUNC_OP[OP_SUBDW] = FUNC_OP_SUBDW;
    FUNC_OP[OP_SUBQW] = FUNC_OP_SUBQW;
    FUNC_OP[OP_MULB] = FUNC_OP_MULB;
    FUNC_OP[OP_MULW] = FUNC_OP_MULW;
    FUNC_OP[OP_MULDW] = FUNC_OP_MULDW;
    FUNC_OP[OP_MULQW] = FUNC_OP_MULQW;
    FUNC_OP[OP_DIVB] = FUNC_OP_DIVB;
    FUNC_OP[OP_DIVW] = FUNC_OP_DIVW;
    FUNC_OP[OP_DIVDW] = FUNC_OP_DIVDW;
    FUNC_OP[OP_DIVQW] = FUNC_OP_DIVQW;
    FUNC_OP[OP_MODB] = FUNC_OP_MODB;
    FUNC_OP[OP_MODW] = FUNC_OP_MODW;
    FUNC_OP[OP_MODDW] = FUNC_OP_MODDW;
    FUNC_OP[OP_MODQW] = FUNC_OP_MODQW;
    FUNC_OP[OP_ANDB] = FUNC_OP_ANDB;
    FUNC_OP[OP_ANDW] = FUNC_OP_ANDW;
    FUNC_OP[OP_ANDDW] = FUNC_OP_ANDDW;
    FUNC_OP[OP_ANDQW] = FUNC_OP_ANDQW;
    FUNC_OP[OP_ORB] = FUNC_OP_ORB;
    FUNC_OP[OP_ORW] = FUNC_OP_ORW;
    FUNC_OP[OP_ORDW] = FUNC_OP_ORDW;
    FUNC_OP[OP_ORQW] = FUNC_OP_ORQW;
    FUNC_OP[OP_XORB] = FUNC_OP_XORB;
    FUNC_OP[OP_XORW] = FUNC_OP_XORW;
    FUNC_OP[OP_XORDW] = FUNC_OP_XORDW;
    FUNC_OP[OP_XORQW] = FUNC_OP_XORQW;
    FUNC_OP[OP_SHRB] = FUNC_OP_SHRB;
    FUNC_OP[OP_SHRW] = FUNC_OP_SHRW;
    FUNC_OP[OP_SHRDW] = FUNC_OP_SHRDW;
    FUNC_OP[OP_SHRQW] = FUNC_OP_SHRQW;
    FUNC_OP[OP_SHLB] = FUNC_OP_SHLB;
    FUNC_OP[OP_SHLW] = FUNC_OP_SHLW;
    FUNC_OP[OP_SHLDW] = FUNC_OP_SHLDW;
    FUNC_OP[OP_SHLQW] = FUNC_OP_SHLQW;
    FUNC_OP[OP_JMP] = FUNC_OP_JMP;
    FUNC_OP[OP_CMPB] = FUNC_OP_CMPB;
    FUNC_OP[OP_CMPW] = FUNC_OP_CMPW;
    FUNC_OP[OP_CMPDW] = FUNC_OP_CMPDW;
    FUNC_OP[OP_CMPQW] = FUNC_OP_CMPQW;
    FUNC_OP[OP_JE] = FUNC_OP_JE;
    FUNC_OP[OP_JNE] = FUNC_OP_JNE;
    FUNC_OP[OP_JL] = FUNC_OP_JL;
    FUNC_OP[OP_JG] = FUNC_OP_JG;
    FUNC_OP[OP_SETM] = FUNC_OP_SETM;
    FUNC_OP[OP_REDM] = FUNC_OP_REDM;
    FUNC_OP[OP_LDB] = FUNC_OP_LDB;
    FUNC_OP[OP_LDW] = FUNC_OP_LDW;
    FUNC_OP[OP_LDDW] = FUNC_OP_LDDW;
    FUNC_OP[OP_LDQW] = FUNC_OP_LDQW;
    FUNC_OP[OP_CONVB] = FUNC_OP_CONVB;
    FUNC_OP[OP_CONVW] = FUNC_OP_CONVW;
    FUNC_OP[OP_CONVDW] = FUNC_OP_CONVDW;
    FUNC_OP[OP_CONVQW] = FUNC_OP_CONVQW;
    FUNC_OP[OP_POP] = FUNC_OP_POP;
    FUNC_OP[OP_PUSH] = FUNC_OP_PUSH;
    FUNC_OP[OP_SYSCALL] = FUNC_OP_SYSCALL;
    FUNC_OP[OP_NEGB] = FUNC_OP_NEGB;
    FUNC_OP[OP_NEGW] = FUNC_OP_NEGW;
    FUNC_OP[OP_NEGDW] = FUNC_OP_NEGDW;
    FUNC_OP[OP_NEGQW] = FUNC_OP_NEGQW;
    DEBUG("init_op_functions", "operation done");
}
