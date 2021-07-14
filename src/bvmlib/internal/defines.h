#ifndef __BVM_INTERNAL_DEFINES_H
#define __BVM_INTERNAL_DEFINES_H
#include <stdint.h>

/* byte types */
#ifndef BYTE
typedef uint8_t BYTE;
#endif
#ifndef WORD
typedef uint16_t WORD;
#endif
#ifndef DWORD
typedef uint32_t DWORD;
#endif
#ifndef QWORD
typedef uint64_t QWORD;
#endif

/* registers */
#define R1 0
#define R2 1
#define R3 2
#define R4 3
#define R5 4
#define R6 5
#define R7 6
#define R8 7
#define R9 8
#define R10 9
#define R11 10
#define R12 11
#define R13 12
#define R14 13
#define R15 14
#define R16 15

#endif
