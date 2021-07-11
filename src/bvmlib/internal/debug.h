#ifndef __INTERNAL_DEBUG_H
#define __INTERNAL_DEBUG_H
#include <stdio.h>
static int __INTERNAL_DEBUG;

int DEBUG(char* func, char* msg)
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

#endif