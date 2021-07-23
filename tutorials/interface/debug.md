# Debugging BVM
Debugging helps programmers catch bugs in the code
<br>
so BVM added debugging when it executes bytecode
<br>
You can on or off it everytime with BVM_on_debug and BVM_off_debug
<br>
You dont need to initialize bvm since it just set __INTERNAL_DEBUG to 1

## Example of Debugging BVM
```c
/* Include BVM Library Interface */
#include "bvmlib/lib.h"
#include <stdio.h>


int main()
{

    /* Lets just say where trying to execute bytecode */
    BVM_init();

    /* Turn on debugging(optional) */

    BVM_on_debug();

    /* Executing bytecode in here*/

    /* Turn off debugging since we are done(optional) */

    BVM_off_debug();

    /* Write to stdout if debugging is enabled */

    printf("Debugging: %s\n", (BVM_debugging() == 0) ? "False" : "True");

    /* some code for cleanup here */

    return 0;

}
```