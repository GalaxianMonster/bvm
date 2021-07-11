# Adding Syscalls to BVM
When your bytecode need to do a specific task and BVM does not have a opcode for it
<br>
You can add syscalls(which can be executed on op syscall)
<br>
But you will need to Initialize BVM first

## Example of Adding Syscalls to BVM

```c
/* BVM Library Interface */
#include "bvmlib/lib.h"

/* Standard I/O Library */
#include <stdio.h>

// our syscall function
int SYSCALL_HELLO_WORLD(VMEM* mem)
{

    /* Print "Hello, world!"*/
    printf("%s", "Hello, world!");

    /* return Success */
    return SYSCALL_SUCCESS;

}

int main()
{
    /* Intialize BVM */
    BVM_init();

    /* Add syscall */
    SYSCALL_add(SYSCALL_HELLO_WORLD);

    /* Optional: BVM_on_debug() for debugging */

    /* Execute Bytecode Here */

    /* Do BVM cleanup */

    return 0;

}
```