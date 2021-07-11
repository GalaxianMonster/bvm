# Cleanup BVM
After we initialize, execute and do all stuff
<br>
We should clean it up
<br><br>
We will be using the BVM_cleanup function to clean it up
<br>
The BVM_cleanup function does free syscalls and set syscall_max to 0

## Example of Cleanup BVM
```c
/* BVM Library Interface */
#include "bvmlib/lib.h"

int main()
{

    /* Initialize BVM */
    BVM_init();

    /* Do some execution here.. */

    /* Do BVM cleanup */
    BVM_cleanup();

    return 0;

}
```