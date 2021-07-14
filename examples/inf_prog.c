/* Build: cd <path to examples>; gcc -I../src -o inf_prog inf_prog.c */

/* BVM Library Interface */
#include <bvmlib/lib.h>

/* Standard I/O */
#include <stdio.h>

int main()
{

	/* Initialize BVM */
	BVM_init();

	/* Optional: BVM_on_debug(); */

	/* Bytecode: jmp 0 */
	/* Since 0 is the start address of the bytecode, it will run jmp 0 everytime */
	BYTE bytecode[3+2+(8*2)] = {
		0x03, 0x00, 0x00,

		0x10, 0x50,

		0x10, 0x00,
		0x10, 0x00,
		0x10, 0x00,
		0x10, 0x00,
		0x10, 0x00,
		0x10, 0x00,
		0x10, 0x00,
		0x10, 0x00,
	};

	/* Execute bytecode and check vm state */
	if(BVM_exec(bytecode, 3+2+16) == BVM_VMSTATE_FAIL)
	{
		printf("Failed\n");
	}

	/* Do some cleanup */
	BVM_cleanup();

	return 0;

}
