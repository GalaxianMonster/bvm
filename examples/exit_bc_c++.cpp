/* Build: cd <path to examples>; g++ -I../src -o exit_bc_c++ exit_bc_c++.cpp -Wall */

/* BVM Library Interface */
#include <bvmlib/lib.h>

/* I/O Streams for C++ */
#include <iostream>

int main()
{

    /* Initialize BVM */
    BVM_init();

    /* Optional if you wanna debug */
    BVM_on_debug();

    /* The bytecode that will just exit */
    BYTE bytecode[3] = {0,16,0};

    /* Get VM State after executing bytecode */
    BVM_VMState state = BVM_exec(bytecode, (QWORD)3);

    /* Print strings to std::cout(stdout) */
    std::cout << "State: ";
    std::cout << ((state == BVM_VMSTATE_FAIL) ? "Failed" : "Successful");
    std::cout << "\n";

    /* Cleanup after */
    BVM_cleanup();

    return 0;

}