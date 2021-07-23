#include <stdio.h>
#include "../../include/internal/debug.h"
int __INTERNAL_DEBUG;
int DEBUG(const char* func, const char* msg)
{
	if(__INTERNAL_DEBUG == 1)
	{
		return printf("[INTERNAL_DEBUG]<%s>: %s\n", func, msg);
	}
	else
	{
		return -1;
	}
}
