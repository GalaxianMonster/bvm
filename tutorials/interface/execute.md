# Executing Bytecode with BVM
Now that we know how to initialize, debug and add syscalls it is time to execute bytecode
<br>
The function of execute bytecode needs BVM to be initialize
<br><br>
To execute bytecode, you just call BVM_exec and pass your bytecode and the length of your bytecode
<br><br>
The BVM_exec function starts a new vm and let the vm run the bytecode
<br><br>
After that it will return the state of the vm

## Example of Executing Bytecode with BVM
```c
/* BVM Library */
#include "bvmlib/lib.h"

int main()
{

    /* Our bytecode(Note that the BYTE type is defined from the bvmlib/internal/defines.h) */
    /* This bytecode will just do exit */
    BYTE bytecode[3] = {0x00, 0x10, 0x00};

    /* Initialize BVM */
    BVM_init();

    /* Optional: BVM_on_debug() for debugging */

    /* execute bytecode */
    VMState state = BVM_exec(bytecode, sizeof(bytecode));

    /* Check VM State if the Program failed */
    if(state == VMSTATE_FAIL)
    {
        printf("Program failed\n");
    }
    else
    {
        printf("Program successful\n");
    }

    /* Do BVM cleanup here */

    return 0;

}
```