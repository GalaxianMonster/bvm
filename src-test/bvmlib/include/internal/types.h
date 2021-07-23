#ifndef __BVM_INTERNAL_TYPES
#define __BVM_INTERNAL_TYPES
#include "defines.h"
#define TYPE_UNKNOWN 0
#define TYPE_BYTE 1
#define TYPE_WORD 2
#define TYPE_DWORD 4
#define TYPE_QWORD 5
BYTE *qw_to_bytes(QWORD qword);
BYTE *dw_to_bytes(DWORD dword);
BYTE *w_to_bytes(WORD word);
BYTE *b_to_bytes(BYTE byte);
BYTE get_val_type(QWORD len);
QWORD to_qword(BYTE *bytes);
DWORD to_dword(BYTE *bytes);
WORD to_word(BYTE *bytes);
BYTE to_byte(BYTE *bytes);
int TYPE_EXISTS(BYTE TYPE);
#endif
