#ifndef __BVM_INTERNAL_DEBUG_H
#define __BVM_INTERNAL_DEBUG_H
#include <stdio.h>
static int __INTERNAL_DEBUG;

int DEBUG(const char* func, const char* msg)
{
	if(__INTERNAL_DEBUG == 1)
	{
		return printf("[BVM_INTERNAL_DEBUG]<%s>: %s\n", func, msg);
	}
	else
	{
		return -1;
	}
}

#endif
