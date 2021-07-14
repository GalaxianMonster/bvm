#ifndef __BVM_INTERNAL_TYPES_H
#define __BVM_INTERNAL_TYPES_H

#include "defines.h"
#include "limits.h"

#define TYPE_UNKNOWN 0
#define TYPE_BYTE 1
#define TYPE_WORD 2
#define TYPE_DWORD 4
#define TYPE_QWORD 5

int TYPE_EXISTS(BYTE TYPE)
{
    if(TYPE < TYPES_MAX)
    {
        return 1;
    }
    return 0;
}

BYTE to_byte(BYTE* bytes)
{
    return bytes[0];
}

WORD to_word(BYTE* bytes)
{
    WORD new_word = 0;
    new_word |= (WORD)bytes[0] << 8;
    new_word |= (WORD)bytes[1];
    return new_word;
}

DWORD to_dword(BYTE* bytes)
{
    DWORD new_dword = 0;
    new_dword |= (DWORD)bytes[0] << 3*8;
    new_dword |= (DWORD)bytes[1] << 2*8;
    new_dword |= (DWORD)bytes[2] << 8;
    new_dword |= (DWORD)bytes[3];
    return new_dword; 
}

QWORD to_qword(BYTE* bytes)
{
    QWORD new_qword = 0;
    new_qword |= (QWORD)bytes[0] << 7*8;
    new_qword |= (QWORD)bytes[1] << 6*8;
    new_qword |= (QWORD)bytes[2] << 5*8;
    new_qword |= (QWORD)bytes[3] << 4*8;
    new_qword |= (QWORD)bytes[4] << 3*8;
    new_qword |= (QWORD)bytes[5] << 2*8;
    new_qword |= (QWORD)bytes[6] << 8;
    new_qword |= (QWORD)bytes[7];
    return new_qword;
}

BYTE get_val_type(QWORD len)
{
    BYTE type = TYPE_UNKNOWN;
    switch(len)
    {
        case 1:
            type = TYPE_BYTE;
            break;
        case 2:
            type = TYPE_WORD;
            break;
        case 4:
            type = TYPE_DWORD;
            break;
        case 8:
            type = TYPE_QWORD;
            break;
        default:
            break;
    }
    return type;
}

BYTE* b_to_bytes(BYTE byte)
{
    BYTE* bytes = (BYTE*)malloc(sizeof(BYTE));
    bytes[0] = byte;
    return bytes;
}

BYTE* w_to_bytes(WORD word)
{
    BYTE* bytes = (BYTE*)malloc(sizeof(WORD));
    bytes[0] |= (word & 0xFF00) >> 8;
    bytes[1] |= (word & 0x00FF);
    return bytes;
}

BYTE* dw_to_bytes(DWORD dword)
{
    BYTE* bytes = (BYTE*)malloc(sizeof(DWORD));
    bytes[0] |= (dword & 0xFF000000) >> 3*8;
    bytes[1] |= (dword & 0x00FF0000) >> 2*8;
    bytes[2] |= (dword & 0x0000FF00) >> 8;
    bytes[3] |= (dword & 0x000000FF);
    return bytes;
}

BYTE* qw_to_bytes(QWORD qword)
{
    BYTE* bytes = (BYTE*)malloc(sizeof(QWORD));
    bytes[0] |= (qword & 0xFF00000000000000) >> 7*8;
    bytes[1] |= (qword & 0x00FF000000000000) >> 6*8;
    bytes[2] |= (qword & 0x0000FF0000000000) >> 5*8;
    bytes[3] |= (qword & 0x000000FF00000000) >> 4*8;
    bytes[4] |= (qword & 0x00000000FF000000) >> 3*8;
    bytes[5] |= (qword & 0x0000000000FF0000) >> 2*8;
    bytes[6] |= (qword & 0x000000000000FF00) >> 8;
    bytes[7] |= (qword & 0x00000000000000FF);
    return bytes;
}

#endif
