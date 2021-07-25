#ifndef __BVM_INTERNAL_TYPES
#define __BVM_INTERNAL_TYPES
#include "defines.h"
#include "exports.h"
#define TYPE_UNKNOWN 0
#define TYPE_BYTE 1
#define TYPE_WORD 2
#define TYPE_DWORD 4
#define TYPE_QWORD 5
BVMLIB_DECL BYTE *qw_to_bytes(QWORD qword);
BVMLIB_DECL BYTE *dw_to_bytes(DWORD dword);
BVMLIB_DECL BYTE *w_to_bytes(WORD word);
BVMLIB_DECL BYTE *b_to_bytes(BYTE byte);
BVMLIB_DECL BYTE get_val_type(QWORD len);
BVMLIB_DECL QWORD to_qword(BYTE *bytes);
BVMLIB_DECL DWORD to_dword(BYTE *bytes);
BVMLIB_DECL WORD to_word(BYTE *bytes);
BVMLIB_DECL BYTE to_byte(BYTE *bytes);
BVMLIB_DECL int TYPE_EXISTS(BYTE TYPE);
#endif
