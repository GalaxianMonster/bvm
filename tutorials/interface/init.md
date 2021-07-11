# Initializing BVM
Before using the interface's functions we need to initialize BVM first
<br>
What it does is initialize op functions and initialize syscalls
<br>
You will just need to call BVM_init()

## Example of Initializing BVM
```c
/* BVM Library Interface */
#include "bvmlib/lib.h"


int main()
{

    /* Initialize BVM */
    BVM_init();


    return 0;

}
```