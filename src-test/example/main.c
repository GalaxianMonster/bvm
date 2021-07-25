#include "../bvmlib/include/lib.h"
#include <stdio.h>
#include <stdlib.h>

#if defined(WIN32) || defined(_WIN32)
#	error bruh
#endif

/* BBC file structure */
struct __bbc_file
{
    BYTE* bytecode;
    QWORD length;
};

typedef struct __bbc_file bbc_file;

/* Function to check file magic */
int is_bbc(BYTE* bytes)
{
    if(bytes[0] == 0xF5 && bytes[1] == (BYTE)'B' && bytes[2] == (BYTE)'V' && bytes[3] == (BYTE)'M')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/* Function for reading the BBC file */
bbc_file read_bbc_file(char* argv0, char* filename)
{
    FILE* file = fopen(filename, "rb");
    if(file == NULL)
    {
        printf("%s: ", argv0);
        fflush(stdout);   
        perror("fopen");
        exit(0);
    }
    fseek(file, 0, SEEK_END);
    QWORD file_length = ftell(file);
    fseek(file, 0, SEEK_SET);
    BYTE* magic = (BYTE*)malloc(4);
    size_t sz = fread((void*)magic, 1, 4, file);
    if(sz < 4 || is_bbc(magic) == 0)
    {
        printf("%s: invalid bbc file\n", argv0);
        exit(0);
    }
    QWORD length = file_length - 4;
    if(length == 0)
    {
        printf("%s: invalid bbc file\n", argv0);
        exit(0);
    }
    BYTE* bytecode = (BYTE*)malloc(file_length-4);
    sz = fread((void*)bytecode, 1, length, file);
    bbc_file l_bbc_file;
    l_bbc_file.bytecode = bytecode;
    l_bbc_file.length = length;
    return l_bbc_file;
}

/* Syscall 0 */
#define check_fail(res) if(res < 0) {return -1;}
#define get_reg_type(mem, reg) get_val_type(get_reg(mem, reg).len)
int SYSCALL_PRINTC(VMEM* mem)
{
    check_fail(CHECK_TYPE("syscall", get_reg_type(mem, R2), TYPE_BYTE));
    REG_VAL r2_val = get_reg(mem, R2);
    char ch = (char)(r2_val.val[0]);
    if(BVM_debugging())
    {
        printf("Output: %c\n", ch);
    }
    else
    {
        printf("%c", ch);
    }
    return SYSCALL_SUCCESS;
}

int CMP_VERSIONS(const char* ver1, const char* ver2)
{
    #define START_CHECK if(0) {
    #define N_GRT(v1, v2) } else if (v1 > v2) {
    #define END_CHECK }
    int major, minor, micro;
    int rmajor, rminor, rmicro;
    sscanf(ver1, "%d.%d.%d", &major, &minor, &micro);
    sscanf(ver2, "%d.%d.%d", &rmajor, &rminor, &rmicro);
    START_CHECK
    N_GRT(rmajor, major)
        return -1;
    N_GRT(rminor, minor)
        return -1;
    N_GRT(rmicro, micro)
        return -1;
    END_CHECK
    #undef START_CHECK
    #undef N_GRT
    #undef END_CHECK
    return 0;
}

int main(int argc, char **argv)
{

    /* Check Argument Count */
    if(argc < 2)
    {
        printf("%s: no files to execute\n", argv[0]);
        exit(0);
    }

    /* get environment variable BVMDEBUG */
    if(getenv("BVMDEBUG") != NULL)
    {
        BVM_on_debug();
    }

    /* Reading the file */
    bbc_file bc = read_bbc_file(argv[0], argv[1]);

    /* Initialize Basic Virtual Machine Library */
    BVM_init();

    /* Add some syscall */
    SYSCALL_add(SYSCALL_PRINTC); /* Syscall No: 0 */
    /* more syscalls here */

    /* Execute Bytecode in a VM and check VM State */
    if(BVM_exec(bc.bytecode, bc.length) == BVM_VMSTATE_FAIL)
    {

        printf("%s: failed at runtime\n", argv[0]);

    }

    /* Do cleanup */
    BVM_cleanup();

    /* Free bytecode */
    free(bc.bytecode);

    return 0;
}
