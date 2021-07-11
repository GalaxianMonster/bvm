/* Build: cd <path to examples>; gcc -I../src -o exit_bc exit_bc.c */

/* BVM Library Interface */
#include <bvmlib/lib.h>

/* Standard I/O */
#include <stdio.h>

int main()
{

	/* Initialize BVM */
    	BVM_init();

	/* Bytecode: exit */
	/* What it does is only exit */
    	BYTE bytecode[3] = {0x00, 0x10, 0x00};

	/* Execute Bytecode */
    	VMState state = BVM_exec(bytecode, 3);
    	
	/* Check vm state */
	if(state == VMSTATE_FAIL)
    	{
        	printf("Program failed\n");
    	}
    	else
    	{
        	printf("Program successful\n");
    	}

	/* Do some cleaning */
    	BVM_cleanup();
    	
	return 0;

}
