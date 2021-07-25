#ifndef __BVM_INTERNAL_DEBUG
#define __BVM_INTERNAL_DEBUG
#include "exports.h"
extern int __INTERNAL_DEBUG;
BVMLIB_DECL int DEBUG(const char *func,const char *msg);
#endif
